#pragma once
#include "comp.h"
#include <memory>
#include <string>

using namespace std;

// minimal bridge pattern (or pimpl idiom if only one implementation is needed):
// the implementation is encapsulated but not abstracted

struct CompMinImpl1 {
  string opImpl() { return string("this is implementation 1\n"); }
};

struct CompMinImpl2 {
  string opImpl() { return string("this is implementation 2\n"); }
};

// this is where the implementation is chosen
using ImplType = CompMinImpl2;

class CompMin : public Comp<string> {
  shared_ptr<ImplType> impl_;

public:
  string op() override { return impl_->opImpl(); }
};
