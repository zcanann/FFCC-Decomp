#ifndef GUARD_CHUNK_H
#define GUARD_CHUNK_H

#include "global.h"

#define CHUNK_ID(a, b, c, d) (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

struct ChunkHeader {
    u32 id;
    u32 size;
};

/* Reader for a stream of (id, size, data) chunks terminated by "END " */
struct Chunk {
    Chunk();
    Chunk(const void *buf);
    void SetBuffer(const void *buf);
    u8 Next(struct ChunkHeader *hdr);
    void *GetData();
    void Read(void *dst, u32 n);
    u8 ReadU8();
    u16 ReadU16();
    u32 ReadU32();
    u32 ReadS32();
    u32 ReadVarInt();
    char *ReadString();
    void Align(u32 align);
    void Skip(s32 n);

    s32 size;
    s32 offset;
    u8 *base;
    u8 *chunk;
    u8 *pos;
};

#endif
