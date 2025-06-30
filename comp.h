#pragma once

// would be nice to create automatically
#include <string>
#include <type_traits>

using namespace std;

template <typename T>
concept fundamental_or_string = is_fundamental_v<T> || is_same_v<T, string>;

template <fundamental_or_string T> struct Comp {
  virtual ~Comp() = default;
  virtual T op() = 0;
};
