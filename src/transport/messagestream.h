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
using asio::co_spawn;
using asio::const_buffer;
using asio::detached;
using asio::io_context;
using asio::use_awaitable;
using asio::ip::tcp;

#include "transport/ciphersuite.h"
#include "transport/message.h"
#include "utils/binarybuffer.h"

/**
 * Provides stream-oriented message communication over socket.
 */
class MessageStream {
public:
  MessageStream(io_context &ctx, CipherSet cipher)
      : socket_(ctx), cipher_(std::move(cipher)) {
  }

  tcp::socket &socket() { return socket_; }

  const tcp::socket &socket() const { return socket_; }

  void close() {
    std::error_code ec;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    if (ec) {

    }
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
   * Must ensure that there is only one outstanding write operation at any time.
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

  /**
   * Must ensure that there is only one outstanding read operation at any time.
   *
   * @return
   */
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
        cipher_.decrypt(read_buffer_.buffer_);
        read_buffer_.len_ = header.size;
      }

      if (header.sequence != 2 &&
          header.checksum != checksum((uint8_t *) read_buffer_.data(),
                                      read_buffer_.size())) {
        throw "Invalid packet received";
      }
    }

    Message message;
    read_buffer_.read(message);
    co_return message;
  }


private:
  CipherSet cipher_;

  tcp::socket socket_;

  BinaryBuffer read_buffer_;
};

#endif// OPENAO_TRANSPORT_CONNECTION_H
