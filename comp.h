#pragma once

// would be nice to create automatically
template <typename T> struct Comp {
  virtual ~Comp() = default;
  virtual T op() = 0;
};
