#pragma once

#include <stdlib.h>

#include "direction.h"
#include "types.h"

#define PI_2 GLM_PI_2
#define PI GLM_PI
#define TAU (2 * PI)
#define F32_EPSILON FLT_EPSILON
#define F64_EPSILON DBL_EPSILON

static inline float
radians (float degrees)
{
  return degrees * (PI / 180.0f);
}

static inline float
degrees (float radians)
{
  return radians * (180.0f / PI);
}

static inline f32
sign (f32 x)
{
  return (f32)((i32)(x > 0.0f) - (i32)(x < 0.0f));
}

static inline float
safe_expf (float x, float e)
{
  return sign (x) * fabsf (powf (fabsf (x), e));
}

static inline float
lerpf (float a, float b, float t)
{
  return (a * (1 - t)) + (b * t);
}

#define template_minmax(T)                                                    \
  static inline T max##T (T _a, T _b) { return ((_a > _b) ? _a : _b); }       \
  static inline T min##T (T _a, T _b) { return ((_a < _b) ? _a : _b); }

#define template_clamp(T)                                                     \
  static inline T clamp##T (T _x, T _min, T _max)                             \
  {                                                                           \
    return max##T (_min, min##T (_max, _x));                                  \
  }

template_minmax (i64);
template_minmax (u64);
template_minmax (f32);
template_clamp (i64);
template_clamp (u64);
template_clamp (f32);

#define RAND(min, max) ((rand () % (max - min + 1)) + min)
#define RANDCHANCE(chance) ((RAND (0, 100000) / 100000.0) <= chance)

struct Ray
{
  vec3s origin, direction;
};

extern bool ray_block (struct Ray ray, f32 max_distance, void *arg,
                       bool (*f) (void *, ivec3s), ivec3s *out,
                       enum Direction *d_out);
