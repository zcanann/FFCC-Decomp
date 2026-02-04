#include "ffcc/chunkfile.h"

#include "string.h"

/*
 * --INFO--
 * Address:	800A0080
 * Size:	4
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
 * Address:	TODO
 * Size:	TODO
 */
bool CChunkFile::GetNextChunk(CChunk& outChunk)
{
    int skip;

	if (m_lastChunkSize < 0)
	{
		skip = 0;
	}
	else {
		skip = ((m_lastChunkSize + 15) / 16) * 16 + 16;
	}

    m_scopeOffset += skip;
    m_headerPtr += skip;
    m_cursor = m_headerPtr;

    if (m_scopeSize <= m_scopeOffset)
	{
        return false;
	}

    outChunk.m_id = *(unsigned int*)m_cursor;
    m_cursor += 4;

    outChunk.m_size = *(unsigned int*)m_cursor;
    m_cursor += 4;

    outChunk.m_arg0 = *(unsigned int*)m_cursor;
    m_cursor += 4;

    outChunk.m_version = *(unsigned int*)m_cursor;
    m_cursor += 4;

    m_lastChunkSize = outChunk.m_size;

    return true;
}

/*
 * --INFO--
 * Address:	800A0060
 * Size:	8
 */
unsigned char* CChunkFile::GetAddress()
{
	return m_cursor;
}

/*
 * --INFO--
 * Address:	800A00E0
 * Size:	20
 */
void CChunkFile::Get(void* dest, long size)
{ 
	memcpy(dest, m_cursor, size);
	m_cursor += size;
}

/*
 * --INFO--
 * Address:	800A0000
 * Size:	12
 */
unsigned char CChunkFile::Get1()
{
	unsigned char value = *m_cursor;
	m_cursor++;
	return value;
}

/*
 * --INFO--
 * Address:	800A0020
 * Size:	16
 */
unsigned short CChunkFile::Get2()
{
	unsigned short value = *(unsigned short*)m_cursor;
	m_cursor += 2;
	return value;
}

/*
 * --INFO--
 * Address:	800A0040
 * Size:	16
 */
unsigned int CChunkFile::Get4()
{
	unsigned int value = *(unsigned int*)m_cursor;
	m_cursor += 4;
	return value;
}

/*
 * --INFO--
 * Address:	800A00C0
 * Size:	16
 */
float CChunkFile::GetF4()
{
    float value = *(float*)m_cursor;
    m_cursor += 4;
    return value;
}

/*
 * --INFO--
 * Address:	800A00A0
 * Size:	24
 */
char* CChunkFile::GetString()
{ 
    char* stringPtr = (char*)m_cursor;
    
    while (*m_cursor != 0) {
        m_cursor++;
    }
    m_cursor++; // skip null terminator
    
    return stringPtr;
}

/*
 * --INFO--
 * Address:	800A0100
 * Size:	32
 */
void CChunkFile::Align(unsigned long alignment)
{ 
    unsigned long offset = (unsigned long)(m_cursor - m_base);
    offset = (offset + alignment - 1) & ~(alignment - 1);
    m_cursor = m_base + offset;
}
