// #include "bbox_intersector.h"
#include "boost/di.hpp"
#include "comp_impl.h"
#include "comp_minimal.h"
#include <iostream>
#include <memory>
#include <variant>

namespace di = boost::di;

void test_minimal_bridge() {
  cout << "\nWith minimal bridge:\n";
  CompMin<CompMinImpl1> cm1;
  cout << cm1.op() << endl;
  cout << cm1.opx2("aBc") << endl << endl;
  CompMin<CompMinImpl2> cm2;
  cout << cm2.op() << endl;
  cout << cm2.opx2("aBc") << endl << endl;
}

void test_bridge_with_injector() {
  CompBuilder<int, CompImpled> builder1;
  cout << "With boost.di builder and injector:\n";
  auto injector1 = di::make_injector(di::bind<CompImpl<int>>().to<CompImpl1>());
  auto comp1 = builder1.build(injector1);

  CompBuilder<string, CompImpled> builder2;
  auto injector2 =
      di::make_injector(di::bind<CompImpl<string>>().to<CompImpl2>());
  auto comp2 = builder2.build(injector2);

  cout << "implementation 1: op() = " << comp1->op() << endl;
  cout << "implementation 2: op() = " << comp2->op() << endl;
  cout << "implementation 1: opx2(7) = " << comp1->opx2(7) << endl;
  cout << "implementation 2: opx2(\"abc4\") = " << comp2->opx2("abc4") << endl;
}

void test_bridge_with_factory() {
  cout << "\nWith factory only (no boost.di):\n";
  auto ImplFactory1 = []() { return make_shared<CompImpl1>(); };
  auto ImplFactory2 = []() { return make_shared<CompImpl2>(); };
  cout << "implementation 1: op() = " << ImplFactory1()->op() << endl;
  cout << "implementation 2: op() = " << ImplFactory2()->op() << endl << endl;
  cout << "implementation 1: opx2(7) = " << ImplFactory1()->opx2(7) << endl;
  cout << "implementation 2: opx2(\"abc4\") = " << ImplFactory2()->opx2("abc4")
       << endl;
}

void test_bridge_with_std_visit() {
  using ImplVariant = variant<CompMinImpl1, CompMinImpl2>;

  struct VariantSelector {
    VariantSelector(ImplVariant impl) : impl_(std::move(impl)) {}

    string op() const {
      return std::visit([](const auto &impl) { return impl.opImpl(); }, impl_);
    }

    string opx2(string x) const {
      return std::visit([x](const auto &impl) { return impl.opx2Impl(x); },
                        impl_);
    }

  private:
    ImplVariant impl_;
  };

  VariantSelector v1{CompMinImpl1{}};
  VariantSelector v2{CompMinImpl2{}};
  cout << "\nWith std::visit:\n";
  cout << v1.op() << endl;
  cout << v2.op() << endl << endl;
  string x("AbC");
  cout << v1.opx2(x) << endl;
  cout << v2.opx2(x) << endl << endl;
}

int main() {
  test_minimal_bridge();
  test_bridge_with_injector();
  test_bridge_with_factory();
  test_bridge_with_std_visit();
  return 0;
}
