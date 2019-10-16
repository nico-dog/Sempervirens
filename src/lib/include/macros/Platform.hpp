#ifndef PLATFORM_HPP
#define PLATFORM_HPP

// Platform macros
#define DOG_PLATFORM(X) DOG_PLATFORM_##X()
#define DOG_PLATFORM_LINUX() LINUX

#endif
