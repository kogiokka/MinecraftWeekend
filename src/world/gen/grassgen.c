#include "../world.h"
#include "worldgen.h"

void
worldgen_grass (struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y,
                i64 z)
{
  i64 s = RAND (2, 10);
  i64 l = RAND (s - 1, s + 1);
  i64 h = RAND (s - 1, s + 1);

  for (i64 xx = (x - l); xx <= (x + l); xx++)
    {
      for (i64 zz = (z - h); zz <= (z + h); zz++)
        {
          enum BlockId block = get (chunk, xx, y + 1, zz),
                       under = get (chunk, xx, y, zz);
          if (block == AIR && under == GRASS && RANDCHANCE (0.5))
            {
              set (chunk, xx, y + 1, zz, TALLGRASS);
            }
        }
    }
}