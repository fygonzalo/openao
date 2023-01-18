#include <gtest/gtest.h>

class Abstract {
public:
  virtual ~Abstract() = default;
};

class Concrete : public Abstract {
public:
  int number() { return 50; }
};


TEST(Test, demo) {
  std::unique_ptr<Abstract> abs = std::make_unique<Concrete>();
  std::cout << typeid(decltype(*abs)).name() << std::endl;
  ASSERT_EQ(typeid(decltype(*abs)), typeid(Abstract &));
}