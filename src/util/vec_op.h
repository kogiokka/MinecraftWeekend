#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

#include <cglm/cglm.h>
#include <cglm/struct.h>

#pragma GCC diagnostic pop

#include "ivec2s.h"
#include "types.h"

static inline vec2s vec2i2f(ivec2s v)
{
    return (vec2s) { { (float)v.x, (float)v.y } };
}

static inline ivec2s vec2f2i(vec2s v)
{
    return (ivec2s) { { (int)v.x, (int)v.y } };
}

static inline vec3s vec3i2f(ivec3s v)
{
    return (vec3s) { { (float)v.x, (float)v.y, (float)v.z } };
}

static inline ivec3s vec3f2i(vec3s v)
{
    return (ivec3s) { { (int)v.x, (int)v.y, (int)v.z } };
}

static inline ivec3s ivec2to3(ivec2s v)
{
    return (ivec3s) { { v.x, v.y, 0 } };
}

static inline int ivec3scmp(ivec3s a, ivec3s b)
{
    return memcmp(&a, &b, sizeof(ivec3s));
}

static inline s64 ivec3shash(ivec3s v)
{
    s64 h = 0;
    for (int i = 0; i < 3; i++) {
        h ^= v.raw[i] + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
}
