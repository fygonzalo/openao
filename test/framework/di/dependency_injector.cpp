#include <gtest/gtest.h>

#include "di/dependency_injector.h"

using namespace openao::framework::di;


class IService {
public:
  virtual ~IService() = default;

  virtual void test() = 0;
};

class Service : public IService {
public:
  void test() override{};
};

TEST(DependencyInjector, Basic) {

  std::unique_ptr<IService> a = std::make_unique<Service>();
  // std::cout << v.type().name() << std::endl;
  auto &s = static_cast<IService &>(*a);
  // DependencyInjector injector;
  // injector.insert<IService>(Service());
  // injector.get<IService&>();
}