
#ifndef OPENAO_MESSAGE_H
#define OPENAO_MESSAGE_H

#include "utils/binarybuffer.h"
#include <cstdint>

struct Message {
  struct MessageHeader {
    uint16_t size = 0;
    uint16_t type = 0;

    void deserialize(BinaryBuffer &buffer) {
      buffer.read(size);
      buffer.read(type);
    }

    void serialize(BinaryBuffer &buffer) {
      buffer.write(size);
      buffer.write(type);
    }
  };

  Message() {}

  /**
   * Creates a Message based on any serializable type that includes a type code
   *
   * @tparam T
   * @param t
   */
  template<typename T>
  Message(T t) {
    payload.write(t);
    header.size = payload.size() + 2;
    header.type = static_cast<uint16_t>(T::type);
  }

  template<typename T>
  T read() {
    T t;
    payload.read(t);
    return t;
  }

  MessageHeader header;
  BinaryBuffer payload;

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(header);

    // Substract because the type is already on the header
    int payload_size = header.size - sizeof(MessageHeader::type);
    payload = BinaryBuffer(payload_size);
    buffer.read(payload);
  }

  void serialize(BinaryBuffer &buffer) {
    buffer.write(header);
    buffer.write(payload);
  }
};
#endif// OPENAO_MESSAGE_H
