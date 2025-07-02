#pragma once
#include "comp.h"
#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>

using namespace std;

// minimal bridge pattern (or pimpl idiom if only one implementation is needed):
// the implementation is encapsulated but not abstracted

struct CompMinImpl1 {
  string opImpl() const { return string("\nthis is implementation 1"); }
  string opx2Impl(string x) const { return x + x; }
};

struct CompMinImpl2 {
  string opImpl() const { return string("\nthis is implementation 2"); }
  string opx2Impl(string x) const {
    string y(x.size(), ' ');
    ranges::reverse_copy(x.begin(), x.end(), y.begin());
    return x + y;
  }
};

// this is where the implementation is chosen

template <typename ImplClassName>
  requires is_same_v<CompMinImpl1, ImplClassName> ||
           is_same_v<CompMinImpl2, ImplClassName>
class CompMin : public Comp<string> {
  shared_ptr<ImplClassName> impl_;

public:
  string op() const override { return impl_->opImpl(); }
  string opx2(string x) const override { return impl_->opx2Impl(x); }
};
