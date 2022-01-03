#ifndef TIME_H
#define TIME_H

#include "../gfx/gfx.h"

#define NS_PER_SECOND (1000000000)
#define NS_PER_MS (1000000)

#define NOW() glfwGetTime () * NS_PER_SECOND

#endif
