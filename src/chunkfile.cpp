#include "ffcc/chunkfile.h"

#include "string.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChunkFile::CChunkFile()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChunkFile::CChunkFile(void* filePtr)
{
    unsigned int header = *reinterpret_cast<unsigned int*>((unsigned char*)(filePtr) + 4);
    unsigned int scopeSize = header & 0x00FFFFFF;

    m_base = (unsigned char*)(filePtr);
    m_headerPtr = (unsigned char*)(filePtr);
    m_scopeSize = scopeSize;
    m_scopeOffset = 0;
    m_lastChunkSize = -1;
    m_stackDepth = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::SetBuf(void* filePtr)
{
    unsigned int header = *reinterpret_cast<unsigned int*>((unsigned char*)(filePtr) + 4);
    unsigned int scopeSize = header & 0x00FFFFFF;

    m_base = (unsigned char*)(filePtr);
    m_headerPtr = (unsigned char*)(filePtr);
    m_scopeSize = scopeSize;
    m_scopeOffset = 0;
    m_lastChunkSize = -1;
    m_stackDepth = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::PushChunk()
{
	m_chunkScopes[m_stackDepth].m_scopeSize = m_scopeSize;
	m_chunkScopes[m_stackDepth].m_lastChunkSize = m_lastChunkSize;
	m_chunkScopes[m_stackDepth].m_scopeOffset = m_scopeOffset;
	m_chunkScopes[m_stackDepth].m_base = m_headerPtr;
	m_chunkScopes[m_stackDepth].m_headerPtr = m_cursor;
	m_stackDepth = m_stackDepth + 1;
	m_scopeSize = m_lastChunkSize;
	m_scopeOffset = 0;
	m_lastChunkSize = -1;
	m_headerPtr = m_cursor;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::PopChunk()
{ 
	m_stackDepth = m_stackDepth - 1;
	m_scopeSize = m_chunkScopes[m_stackDepth].m_scopeSize;
	m_lastChunkSize = m_chunkScopes[m_stackDepth].m_lastChunkSize;
	m_scopeOffset = m_chunkScopes[m_stackDepth].m_scopeOffset;
	m_headerPtr = m_chunkScopes[m_stackDepth].m_base;
	m_cursor = m_chunkScopes[m_stackDepth].m_headerPtr;
}

/*
 * --INFO--
 * PAL Address: 80012988
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CChunkFile::GetNextChunk(CChunk& outChunk)
{
    int skip;
    int alignedSize;
    unsigned int roundUp;

    if (m_lastChunkSize < 0) {
        skip = 0;
    } else {
        alignedSize = m_lastChunkSize + 0xF;
        roundUp = 0;
        if (alignedSize < 0) {
            if ((alignedSize & 0xF) != 0) {
                roundUp = 1;
            }
        }
        skip = ((alignedSize >> 4) + static_cast<int>(roundUp)) * 0x10 + 0x10;
    }

    m_scopeOffset += skip;
    m_headerPtr += skip;
    m_cursor = m_headerPtr;

    if ((int)m_scopeSize <= m_scopeOffset) {
        return false;
    }

    unsigned int* word = reinterpret_cast<unsigned int*>(m_cursor);
    m_cursor = reinterpret_cast<unsigned char*>(word + 1);
    outChunk.m_id = *word;

    unsigned char* raw = m_cursor;
    m_cursor = raw + 4;
    outChunk.m_size = *reinterpret_cast<unsigned int*>(raw);

    int* value = reinterpret_cast<int*>(m_cursor);
    m_cursor = reinterpret_cast<unsigned char*>(value + 1);
    outChunk.m_arg0 = *value;

    value = reinterpret_cast<int*>(m_cursor);
    m_cursor = reinterpret_cast<unsigned char*>(value + 1);
    outChunk.m_version = *value;

    m_lastChunkSize = static_cast<int>(outChunk.m_size);

    return true;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char* CChunkFile::GetAddress()
{
	return m_cursor;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::Get(void* dest, long size)
{ 
	memcpy(dest, m_cursor, size);
	m_cursor += size;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char CChunkFile::Get1()
{
	unsigned char* value = m_cursor;

	m_cursor += sizeof(unsigned char);

	return *value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned short CChunkFile::Get2()
{
	unsigned short* value = (unsigned short*)m_cursor;

	m_cursor += sizeof(unsigned short);

	return *value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CChunkFile::Get4()
{
	unsigned int* value = (unsigned int*)m_cursor;

	m_cursor += sizeof(unsigned int);

	return *value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CChunkFile::GetF4()
{
    union {
        unsigned int bits;
        float value;
    } u;

    u.bits = Get4();
    return u.value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
char* CChunkFile::GetString()
{ 
    char* stringPtr = (char*)m_cursor;
    unsigned char currentChar;

    do
    {
        currentChar = *m_cursor++;
    } while (currentChar != 0);

    return stringPtr;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::Align(unsigned long alignment)
{ 
    unsigned long offset = (unsigned long)(m_cursor - m_base);
    offset += alignment - 1;
    offset -= offset % alignment;
    m_cursor = m_base + offset;
}
