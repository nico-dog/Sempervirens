#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Macros/Platform.hpp>

#if SEMPERVIRENS_PLATFORM(UNIX)
#include <Window/Platform/Linux/LinuxWindow.hpp>

using Window_t = sempervirens::window::LinuxWindow;
#endif

#endif
