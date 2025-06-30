// #include "bbox_intersector.h"
#include "boost/di.hpp"
#include "comp_impl.h"
#include "comp_minimal.h"
#include <iostream>
#include <memory>

namespace di = boost::di;

void test_minimal_bridge() {
  cout << "With minimal bridge:\n";
  CompMin cm;
  cout << cm.op() << std::endl;
}

void test_bridge_with_builder() {
  CompBuilder<int, CompImpled> builder;
  cout << "With builder and injector:\n";
  auto injector1 =
      di::make_injector(di::bind<CompImpl<int>>().to<CompImpl1<int>>());
  auto comp1 = builder.build(injector1);
  std::cout << "implementation 1: op() = " << comp1->op() << endl;
  auto injector2 =
      di::make_injector(di::bind<CompImpl<int>>().to<CompImpl2<int>>());
  auto comp2 = builder.build(injector2);
  std::cout << "implementation 2: op() = " << comp2->op() << endl;
}

#if 0
void test_bridge_with_factory_injection() {
  CompBuilder<int, Comp<int>> builder;
  cout << "With builder and injector:\n";
  auto injector = di::make_injector(
      di::bind<ImplFactory>.to([]() { return make_unique<CompImpl1<int>>(); }));
  auto comp1 = builder.build(injector);
  std::cout << "implementation 1 from factory: op() = " << comp1->op() << endl;
}
#endif

int main() {
  test_minimal_bridge();
  test_bridge_with_builder();
  // test_bridge_with_factory_injection();
  return 0;
}
