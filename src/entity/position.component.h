#ifndef COMP_POSITION_H
#define COMP_POSITION_H

#include "../util/util.h"

struct PositionComponent
{
  vec3s position;

  ivec3s block, offset;
  bool block_changed, offset_changed;
};

#endif
