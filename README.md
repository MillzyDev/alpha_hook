# alpha_hook
A utility library for hooking IL2CPP-generated functions, designed for alpha1.

### TODO
* Safe exit macro for null/nullptr/false values, should hopefully be able to provide debug info before safely quitting/crashing the game.
* Utility functions for finding: MethodInfo, Classes, Fields..etc.
  * Cache values
* Macros for creating and installing hooks on IL2CPP functions.
* Functions for creating IL2CPP-specific types with no standard C++ equivalent, such as strings, arrays and lists.
