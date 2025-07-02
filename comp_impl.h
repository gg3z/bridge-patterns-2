#pragma once
#include "comp.h"
#include <memory>
#include <string>

using namespace std;

// would be nice to create automatically
template <typename T> struct CompImpl {
  virtual ~CompImpl() = default;
  virtual T op() const = 0;
  virtual T opx2(T x) const = 0;
};

// CompImpled - short for Comp Implemented
template <typename T> struct CompImpled : Comp<T> {
  shared_ptr<CompImpl<T>> impl_;
  CompImpled(shared_ptr<CompImpl<T>> impl) : impl_(impl) {}
  virtual T op() const override { return impl_->op(); }
  virtual T opx2(T x) const override { return impl_->opx2(x); }
};

template <typename T, template <typename> class C>
  requires requires { typename C<T>; }
struct CompBuilder {
  template <class Injector> unique_ptr<C<T>> build(const Injector &injector) {
    auto impl = injector.template create<shared_ptr<CompImpl<T>>>();
    return make_unique<C<T>>(impl);
  }
};

template <typename T, template <typename> class C, template <typename> class O>
  requires requires {
    typename C<T>;
    typename O<T>;
  }
struct CompBuilder2 {
  template <class Injector> unique_ptr<C<T>> build(const Injector &injector) {
    auto cInst = injector.template create<shared_ptr<C<T>>>();
    return make_unique<O<T>>(cInst);
  }
};

class CompImpl1 : public CompImpl<int> {
public:
  virtual int op() const override { return 11; }
  virtual int opx2(int x) const override { return 2 * x; }
};

class CompImpl2 : public CompImpl<string> {
public:
  virtual string op() const override { return "2_2"; }
  virtual string opx2(string x) const override { return x + x; }
};
