#ifndef HOTBAR_H
#define HOTBAR_H

#include "../block/block.h"
#include "../util/util.h"

#define HOTBAR_SLOTS 10

struct UIHotbar
{
  enum BlockId values[HOTBAR_SLOTS];
  size_t index;
};

#endif