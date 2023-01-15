
#ifndef OPENAO_BINARYBUFFER_H
#define OPENAO_BINARYBUFFER_H

#include <cstring>
#include <type_traits>
#include <bitset>
#include <vector>
#include <array>

class BinaryBuffer {
public:
  BinaryBuffer(int size) { buffer_.resize(size); };
  BinaryBuffer() { buffer_.resize(65536); }

  int size() const { return len_; }
  bool eof() const { return off_ >= len_; }

  const char *data() { return buffer_.data(); }

  /**
   * Reads the content of this object into the given buffer.
   *
   * If the receiving buffer available space is smaller than the content of this
   * instance, then is filled with what can.
   * If the receiving buffer available space is bigger than the content of this
   * instance, then all will be written into it.
   *
   * @param buffer
   */
  void read(BinaryBuffer &buffer) {
    int amount = buffer.buffer_.size() - buffer.len_;
    read_(buffer.data_(), amount);
    buffer.len_ += amount;
  }

  /**
   *
   *
   * @param buffer
   */
  void write(BinaryBuffer buffer) {
    if (len_ + buffer.len_ > buffer_.size())
      throw "Cannot exceed max buffer size";

    memcpy(buffer_.data() + len_, buffer.buffer_.data(), buffer.len_);
    len_ += buffer.len_;
  }

  /**
   * Writes the amount of bytes at offset.
   *
   * The size of the buffer will remain the same if the offset plus input length
   * isn't bigger than the current size.
   *
   * @param src
   * @param len
   * @param off
   */
  void write(const char *src, int len, int off) {
    int amount = off + len;
    if (amount > buffer_.size()) throw "Cannot exceed buffer limits";

    memcpy(buffer_.data() + off, src, len);

    if (amount > len_) len_ = amount;
  }

  /**
   * Writes the amount of bytes at the end of the data.
   *
   * @param src
   * @param len
   */
  void write(const char *src, int len) {
    if (len_ + len > buffer_.size()) throw "Cannot exceed max buffer size";

    memcpy(buffer_.data() + len_, src, len);
    len_ += len;
  }

  void write(bool value) { write_(value); }
  void write(uint8_t value) { write_(value); }
  void write(uint16_t value) { write_(value); }
  void write(uint16_t value, int offset) { write_(value, offset); }
  void write(uint32_t value) { write_(value); }
  void write(uint64_t value) { write_(value); }
  void write(int8_t value) { write_(value); }
  void write(int16_t value) { write_(value); }
  void write(int32_t value) { write_(value); }
  void write(int64_t value) { write_(value); }
  void set(char c, int len) {
    if (len_ + len > buffer_.size()) throw "Unable to exceed buffer size";

    memset(buffer_.data() + len_, c, len);
    len_ += len;
  }
  void write(std::string &var) { write(var.c_str(), var.size() + 1, len_); };

  template<typename T, size_t N>
  void write(std::array<T, N> &values) {
    int a = values.size();
    for (T &t: values) write(t);
  }


  void read(bool &var) { read_(var); }
  void read(uint8_t &var) { read_(var); }
  void read(uint16_t &var) { read_(var); }
  void read(uint32_t &var) { read_(var); }
  void read(int8_t &var) { read_(var); }
  void read(int16_t &var) { read_(var); }
  void read(int32_t &var) { read_(var); }

  void read(char * dst, int len) {
    if (len > len_) len = len_;

    memmove(dst, buffer_.data() + off_, len);
    off_ += len;
  }
  void skip(int n) { off_ += n; }

  // TODO: Test this
  template<typename T, std::size_t N>
  void read(std::array<T, N> &var) {
    memcpy(var.data(), buffer_.data(), sizeof(T) * N);
    off_ += sizeof(T) * N;
  }


  template<class T>
  void write(T &t) {
    t.serialize(*this);
  }

  template<class T>
  void write(T &t, int offset) {
    int last = len_;

    // Seek to the desired position
    len_ = offset;
    t.serialize(*this);

    // The write didn't overpass the current size, so treat it as an overwrite
    if (last > len_) len_ = last;
  }

  template<class T>
  void read(T &t) {
    t.deserialize(*this);
  }


private:
  BinaryBuffer(int size, bool fixed) {
    if (fixed) len_ = size;

    buffer_.resize(size);
  }

  friend class MessageStream;

  char *data_() { return buffer_.data(); }
  void commit(int size) { len_ = size; }


  template<typename T>
  void read_(T &t) {
    t = *(T *) (buffer_.data() + off_);
    off_ += sizeof(T);
  }

  void read_(char *dst, int len) {
    if (len > len_) len = len_;

    memmove(dst, buffer_.data() + off_, len);
    off_ += len;
  }

  template<typename T>
  void write_(T t) {
    write((char *) &t, sizeof(T));
  }

  template<typename T>
  void write_(T t, int offset) {
    write((char *) &t, sizeof(T), offset);
  }


  int off_ = 0;
  int len_ = 0;
  std::vector<char> buffer_;
};

#endif// OPENAO_BINARYBUFFER_H
