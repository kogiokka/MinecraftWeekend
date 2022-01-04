#include "fmath.h"

#include "../util/util.h"

// finds the smallest possible t such that s + t * ds is an integer
static vec3s
intbound (vec3s s, vec3s ds)
{
  vec3s v;
#if defined(__clang__)
#pragma clang loop unroll_count(3)
#elif defined(__GNUC__)
#pragma GCC unroll 3
#endif
  for (size_t i = 0; i < 3; i++)
    {
      v.raw[i] = (ds.raw[i] > 0 ? (ceilf (s.raw[i]) - s.raw[i])
                                : (s.raw[i] - floorf (s.raw[i])))
                 / fabsf (ds.raw[i]);
    }
  return v;
}

// Check if a ray intersects a "block" where blocks are retrieved via a
// function
bool
ray_block (struct Ray ray, f32 max_distance, void *arg,
           bool (*f) (void *, ivec3s), ivec3s *out, enum Direction *d_out)
{
  ivec3s p, step;
  vec3s d, tmax, tdelta;
  f32 radius;

  p = (ivec3s){ { (int)floorf (ray.origin.x), (int)floorf (ray.origin.y),
                  (int)floorf (ray.origin.z) } };
  d = ray.direction;
  step = (ivec3s){ { sign (d.x), sign (d.y), sign (d.z) } };
  tmax = intbound (ray.origin, d);
  tdelta = glms_vec3_div (vec3i2f (step), d);
  radius = max_distance / glms_vec3_norm (d);

  while (true)
    {
      if (f (arg, p))
        {
          *out = p;
          return true;
        }

      if (tmax.x < tmax.y)
        {
          if (tmax.x < tmax.z)
            {
              if (tmax.x > radius)
                {
                  break;
                }

              p.x += step.x;
              tmax.x += tdelta.x;
              *d_out = IVEC3S2DIR (((ivec3s){ { -step.x, 0, 0 } }));
            }
          else
            {
              if (tmax.z > radius)
                {
                  break;
                }

              p.z += step.z;
              tmax.z += tdelta.z;
              *d_out = IVEC3S2DIR (((ivec3s){ { 0, 0, -step.z } }));
            }
        }
      else
        {
          if (tmax.y < tmax.z)
            {
              if (tmax.y > radius)
                {
                  break;
                }

              p.y += step.y;
              tmax.y += tdelta.y;
              *d_out = IVEC3S2DIR (((ivec3s){ { 0, -step.y, 0 } }));
            }
          else
            {
              if (tmax.z > radius)
                {
                  break;
                }

              p.z += step.z;
              tmax.z += tdelta.z;
              *d_out = IVEC3S2DIR (((ivec3s){ { 0, 0, -step.z } }));
            }
        }
    }

  return false;
}
