#include "../world.h"
#include "worldgen.h"

void
worldgen_shrub (struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y,
                i64 z)
{
  enum BlockId under = get (chunk, x, y, z);
  if ((under == SAND || under == DIRT || under == GRASS)
      && get (chunk, x, y + 1, z) == AIR)
    {
      set (chunk, x, y + 1, z, SHRUB);
    }
}