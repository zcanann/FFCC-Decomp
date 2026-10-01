#include "global.h"
#include "chunk.h"

const char gChunkFileName[] = "C:/FFF/miniGame/mgr/chunk.cpp";

void Chunk_Construct(struct Chunk *c)
{
}

struct Chunk *Chunk_Create(struct Chunk *c, const void *buf)
{
    Chunk_SetBuffer(c, buf);
    return c;
}

void Chunk_SetBuffer(struct Chunk *c, const void *buf)
{
    if (buf == NULL)
        AssertFailed(gChunkFileName, 41);
    c->base = (u8 *)buf;
    c->chunk = (u8 *)buf;
    c->offset = 0;
    c->size = -1;
}

u8 Chunk_Next(struct Chunk *c, struct ChunkHeader *hdr)
{
    s32 skip = c->size < 0 ? 0 : c->size + 8;

    c->offset += skip;
    c->chunk += skip;
    c->pos = c->chunk;
    hdr->id = Chunk_ReadU32(c);
    if (hdr->id == CHUNK_ID('E', 'N', 'D', ' '))
        return 0;
    hdr->size = Chunk_ReadU32(c);
    c->size = hdr->size;
    return 1;
}

void *Chunk_GetData(struct Chunk *c)
{
    return c->pos;
}

void Chunk_Read(struct Chunk *c, void *dst, u32 n)
{
    memcpy(dst, c->pos, n);
    c->pos += n;
}

u8 Chunk_ReadU8(struct Chunk *c)
{
    return *c->pos++;
}

u16 Chunk_ReadU16(struct Chunk *c)
{
    u16 v = *(u16 *)c->pos;

    c->pos += 2;
    return v;
}

u32 Chunk_ReadU32(struct Chunk *c)
{
    u32 v = *(u32 *)c->pos;

    c->pos += 4;
    return v;
}

u32 Chunk_ReadS32(struct Chunk *c)
{
    return Chunk_ReadU32(c);
}

u32 Chunk_ReadVarInt(struct Chunk *c)
{
    s32 shift = 0;
    u32 v = 0;
    u8 b;

    do {
        b = Chunk_ReadU8(c);
        v += b << shift;
        shift += 7;
    } while (b & 0x80);
    return v;
}

char *Chunk_ReadString(struct Chunk *c)
{
    char *str = (char *)c->pos;

    while (Chunk_ReadU8(c) != 0)
        ;
    return str;
}

void Chunk_Align(struct Chunk *c, u32 align)
{
    s32 n = c->pos - c->base;

    n += align - 1;
    n -= n % align;
    c->pos = c->base + n;
}

void Chunk_Skip(struct Chunk *c, s32 n)
{
    c->pos += n;
}
