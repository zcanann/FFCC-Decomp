#include "global.h"
#include "chunk.h"

#define CHUNK_FILE "C:/FFF/miniGame/mgr/chunk.cpp"

Chunk::Chunk()
{
}

Chunk::Chunk(const void *buf)
{
    SetBuffer(buf);
}

void Chunk::SetBuffer(const void *buf)
{
    if (buf == NULL)
        AssertFailed(CHUNK_FILE, 41);
    base = (u8 *)buf;
    chunk = (u8 *)buf;
    offset = 0;
    size = -1;
}

u8 Chunk::Next(struct ChunkHeader *hdr)
{
    s32 skip = size < 0 ? 0 : size + 8;

    offset += skip;
    chunk += skip;
    pos = chunk;
    hdr->id = ReadU32();
    if (hdr->id == CHUNK_ID('E', 'N', 'D', ' '))
        return 0;
    hdr->size = ReadU32();
    size = hdr->size;
    return 1;
}

void *Chunk::GetData()
{
    return pos;
}

void Chunk::Read(void *dst, u32 n)
{
    memcpy(dst, pos, n);
    pos += n;
}

u8 Chunk::ReadU8()
{
    return *pos++;
}

u16 Chunk::ReadU16()
{
    u16 v = *(u16 *)pos;

    pos += 2;
    return v;
}

u32 Chunk::ReadU32()
{
    u32 v = *(u32 *)pos;

    pos += 4;
    return v;
}

u32 Chunk::ReadS32()
{
    return ReadU32();
}

u32 Chunk::ReadVarInt()
{
    s32 shift = 0;
    u32 v = 0;
    u8 b;

    do {
        b = ReadU8();
        v += b << shift;
        shift += 7;
    } while (b & 0x80);
    return v;
}

char *Chunk::ReadString()
{
    char *str = (char *)pos;

    while (ReadU8() != 0)
        ;
    return str;
}

void Chunk::Align(u32 align)
{
    s32 n = pos - base;

    n += align - 1;
    n -= n % align;
    pos = base + n;
}

void Chunk::Skip(s32 n)
{
    pos += n;
}
