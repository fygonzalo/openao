
#include <gtest/gtest.h>

#include "experimental/events/game/message.h"
#include "experimental/reactor.h"


using namespace openao::experimental;
using openao::experimental::Reactor;


template<class C>
struct Handlers {

  Handlers(C &c) : c_(c){};

  template<class T>
  void add(uint16_t code) {
    handlers_[code] = [this](BinaryBuffer &buffer) {
      auto t = buffer.read<T>();
      this->c_(t);
    };

    mappers_[typeid(T)] = code;
  }

  void process(BinaryBuffer &buffer) {
    auto code = buffer.read<uint16_t>();
    handlers_[code](buffer);
  }

  template<class T>
  BinaryBuffer serialize(T &t) {
    uint16_t code = mappers_.at(typeid(T));

    BinaryBuffer buffer;
    buffer.write(code);
    buffer.write(t);
    return buffer;
  }


  C &c_;
  std::map<uint16_t, std::function<void(BinaryBuffer &)>> handlers_;
  std::map<std::type_index, uint16_t> mappers_;
};

template<typename I>
struct Client {

  Client(Handlers<I> &handlers) : handlers_(handlers){};

  void recv(BinaryBuffer &buffer) { handlers_.process(buffer); }

  template<class T>
  void send(const T &t) {
    BinaryBuffer b = handlers_.serialize(t);
    std::cout << std::to_string(b.read<uint16_t>()) << std::endl;
  }

  Handlers<I> &handlers_;
};

TEST(Reactor, Complet) {

  Reactor reactor;

  uint8_t result[] = {
          0x17, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6f, 0x70, 0x65, 0x6e, 0x61,
          0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x65, 0x78,
          0x70, 0x65, 0x72, 0x69, 0x6d, 0x65, 0x6e, 0x74, 0x61, 0x6c, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00,
  };
  BinaryBuffer buffer{};
  buffer.write((char *) result, sizeof(result));

  auto callback = [&reactor]<typename T>(const T &t) { reactor.react(t); };

  Handlers server_handlers{callback};
  server_handlers.add<events::game::Message>(23);

  Client client(server_handlers);

  reactor.add<events::game::Message>([&client](const events::game::Message &m) {
    std::cout << std::string(m.text.c_str()) << std::endl;
    client.send(m);
  });


  client.recv(buffer);
}

TEST(Reactor, Register_Functions_Test) {

  Reactor reactor;
  reactor.add<events::game::Message>([](const events::game::Message &m) {
    std::cout << std::string(m.text.c_str()) << std::endl;
  });


  events::game::Message message{};
  message.entity = 1;
  message.name = "openao";
  message.text = "testing reactor";

  reactor.react(message);
}
