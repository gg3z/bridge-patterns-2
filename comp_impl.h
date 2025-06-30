#pragma once
#include "comp.h"
#include <memory>

using namespace std;

// would be nice to create automatically
template <typename T> struct CompImpl {
  virtual ~CompImpl() = default;
  virtual T op() = 0;
};

// CompImpled - short for Comp Implemented
template <typename T> struct CompImpled : Comp<T> {
  shared_ptr<CompImpl<T>> impl_;
  CompImpled(shared_ptr<CompImpl<T>> impl) : impl_(impl) {}
  virtual T op() override { return impl_->op(); }
};

template <typename T, template <typename> class C>
  requires requires { typename C<T>; }
struct CompBuilder {
  template <class Injector> unique_ptr<C<T>> build(const Injector &injector) {
    auto impl = injector.template create<shared_ptr<CompImpl<T>>>();
    return make_unique<C<T>>(impl);
  }
};

template <typename T> class CompImpl1 : public CompImpl<T> {
public:
  virtual T op() override { return 11; }
};

template <typename T> class CompImpl2 : public CompImpl<T> {
public:
  virtual T op() override { return 22; }
};
