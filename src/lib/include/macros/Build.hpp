#ifndef BUILD_HPP
#define BUILD_HPP

// Build macros
#define DOG_BUILD(X) DOG_BUILD_##X()
#define DOG_BUILD_UNITTEST() BUILD_UNITTEST
#define DOG_BUILD_LOGGING() BUILD_LOGGING

#endif
