#ifndef GUARD_CHUNK_H
#define GUARD_CHUNK_H

#include "global.h"

#define CHUNK_ID(a, b, c, d) (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

/* Reader for a stream of (id, size, data) chunks terminated by "END " */
struct Chunk {
    s32 size;
    s32 offset;
    u8 *base;
    u8 *chunk;
    u8 *pos;
};

struct ChunkHeader {
    u32 id;
    u32 size;
};


void Chunk_Construct(struct Chunk *c);
struct Chunk *Chunk_Create(struct Chunk *c, const void *buf);
void Chunk_SetBuffer(struct Chunk *c, const void *buf);
u8 Chunk_Next(struct Chunk *c, struct ChunkHeader *hdr);
void *Chunk_GetData(struct Chunk *c);
void Chunk_Read(struct Chunk *c, void *dst, u32 n);
u8 Chunk_ReadU8(struct Chunk *c);
u16 Chunk_ReadU16(struct Chunk *c);
u32 Chunk_ReadU32(struct Chunk *c);
u32 Chunk_ReadS32(struct Chunk *c);
u32 Chunk_ReadVarInt(struct Chunk *c);
char *Chunk_ReadString(struct Chunk *c);
void Chunk_Align(struct Chunk *c, u32 align);
void Chunk_Skip(struct Chunk *c, s32 n);

#endif
