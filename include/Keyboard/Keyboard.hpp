#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <Macros/Platform.hpp>

#if SEMPERVIRENS_PLATFORM(UNIX)
#include <Keyboard/Platform/Linux/LinuxKeyboard.hpp>

using Keyboard_t = sempervirens::keyboard::LinuxKeyboard;
#endif

#endif
