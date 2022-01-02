#ifndef WORLDGEN_H
#define WORLDGEN_H

#include "../../util/util.h"

// forward declarations
struct Chunk;

typedef void (*FWGSet)(struct Chunk *, i32, i32, i32, u32);
typedef u32 (*FWGGet)(struct Chunk *, i32, i32, i32);
typedef void (*FWGDecorate)(struct Chunk  *, FWGGet, FWGSet, i64, i64, i64);

struct WorldgenData {
    f32 h_b;
    i64 h, b;
};

void worldgen_generate(struct Chunk *chunk);

void worldgen_pine(struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y, i64 z);
void worldgen_tree(struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y, i64 z);
void worldgen_flowers(struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y, i64 z);
void worldgen_grass(struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y, i64 z);
void worldgen_shrub(struct Chunk *chunk, FWGGet get, FWGSet set, i64 x, i64 y, i64 z);

#endif