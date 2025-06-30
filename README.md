# bridge-patterns-2

This repo covers various ways of implementing a bridge pattern in c++17/20.
Compared to the neighboring repo bridge-patterns, it is more advanced, including usage of templates, factories and even nested templates.

This repo is part of my deeper practice on design patterns and will hopefully be of benefit to some visitors.
The code is intentionally simplified and skeleton-like, so that the particular flavor of the bridge pattern comes through.

DISCLOSURE: all of the code in this repo is my own original code (though inspired by research I've done online and in large LLMs)

A couple of implementations of the bridge pattern are coded and explained:

- minimal bridge (where the implementation is encapsulated)
- bridge with injector and builder (using boost/di)

I plan to add a number of further implementations of the bridge pattern because there is a wide range of applications and each tends to benefit most from a particular flavor of the pattern.

Buid notes:

- I used clang 19.1.2 to build with CMake in VS code.
- also builds with gcc compiler on Linux
