#ifndef OPENAO_TRANSPORT_CONNECTION_H
#define OPENAO_TRANSPORT_CONNECTION_H

#include <cstdint>
#include <vector>

#include <asio.hpp>

#include "ciphersuite.h"
#include "packetheader.h"
#include "transport/checksum.h"

using asio::async_read;
using asio::async_write;
using asio::awaitable;
using asio::buffer;
using asio::const_buffer;
using asio::io_context;
using asio::use_awaitable;
using asio::ip::tcp;

#include "transport/binarybuffer.h"
#include "transport/ciphersuite.h"
#include "transport/message.h"


class MessageStream {
public:
  MessageStream(io_context &ctx, CipherSet cipher)
      : ctx_(ctx), socket_(ctx), cipher_(std::move(cipher)){};

  tcp::socket &socket() { return socket_; }

  void close() {
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both);
    socket_.close();
  }

  asio::any_io_executor get_executor() { return socket_.get_executor(); }

  awaitable<void> init() {
    BinaryBuffer packet;
    packet.write(cipher_, 8);
    packet.write((uint16_t) (packet.size() - 8), 6);

    PacketHeader header;
    header.size = packet.size() - 6;
    header.sequence = -1;
    header.flags = 0;
    header.checksum =
            checksum((uint8_t *) packet.data() + 6, packet.size() - 6);

    packet.write(header, 0);
    co_await async_write(socket_, buffer(packet.data(), packet.size()),
                         use_awaitable);
  }

  /**
   *
   *
   * Could be optimized if every data type inherits from Message, so in reality
   * we don't construct a message before calling write, but instead pass a
   * reference that is latter serialized onto the already existing buffer
   *
   * @param message
   * @return
   */
  awaitable<void> write(Message message) {
    BinaryBuffer packet;

    packet.write(message, 6);

    PacketHeader header;
    header.size = packet.size() - 6;
    header.sequence = 1;
    header.flags = 0;
    header.checksum =
            checksum((uint8_t *) packet.data() + 6, packet.size() - 6);
    packet.write(header, 0);

    co_await async_write(socket_, buffer(packet.data(), packet.size()),
                         use_awaitable);
  }

  awaitable<Message> read() {

    if (read_buffer_.eof()) {
      read_buffer_ = BinaryBuffer(6, true);
      co_await async_read(socket_, buffer(read_buffer_.buffer_), use_awaitable);

      PacketHeader header;
      read_buffer_.read(header);

      int pending = header.size;
      if (header.flags & 0x01) pending = (((header.size + 15) >> 4) << 4);

      read_buffer_ = BinaryBuffer(pending, true);
      co_await async_read(socket_, buffer(read_buffer_.buffer_), use_awaitable);


      if (header.flags & 0x01) {
        // decrypt
      }

      if (header.checksum !=
          checksum((uint8_t *) read_buffer_.data(), header.size)) {
        throw "Data corrupted";
      }
    }

    // Unparsed message
    // Can delay as much as want but before thread safety
    Message message;
    read_buffer_.read(message);

    co_return message;
  }


private:
  CipherSet cipher_;

  io_context &ctx_;
  tcp::socket socket_;

  BinaryBuffer read_buffer_;
};

#endif// OPENAO_TRANSPORT_CONNECTION_H
