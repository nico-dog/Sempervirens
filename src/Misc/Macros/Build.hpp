#ifndef BUILD_HPP
#define BUILD_HPP

#define SEMPERVIRENS_BUILD(X) SEMPERVIRENS_BUILD_##X()
#define SEMPERVIRENS_BUILD_UNITTESTING() BUILD_UNITTESTING
#define SEMPERVIRENS_BUILD_LOGGING() BUILD_LOGGING
#define SEMPERVIRENS_BUILD_ASSERT() BUILD_ASSERT

#endif
