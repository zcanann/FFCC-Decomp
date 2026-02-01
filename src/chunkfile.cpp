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
 * Address:	TODO
 * Size:	TODO
 */
bool CChunkFile::GetNextChunk(CChunk& outChunk)
{
    int skip = 0;
    
    if (m_lastChunkSize >= 0)
    {
        skip = ((m_lastChunkSize + 15) & ~15) + 16;
    }

    m_scopeOffset += skip;
    m_headerPtr += skip;
    m_cursor = m_headerPtr;

    if (m_scopeOffset >= m_scopeSize)
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
	unsigned char result = *m_cursor;
	m_cursor += 1;
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned short CChunkFile::Get2()
{
	unsigned short result = *(unsigned short*)m_cursor;
	m_cursor += 2;
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CChunkFile::Get4()
{
	unsigned int result = *(unsigned int*)m_cursor;
	m_cursor += 4;
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CChunkFile::GetF4()
{
    float* value = (float*)m_cursor;
    m_cursor += 4;
    return *value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
char* CChunkFile::GetString()
{ 
    char* stringPtr = (char*)m_cursor;
    
    while (*m_cursor != 0)
    {
        m_cursor++;
    }
    m_cursor++; // Skip null terminator
    
    return stringPtr;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChunkFile::Align(unsigned long alignment)
{
    // Pattern to generate andc instruction for efficient alignment
    unsigned long alignMask = alignment - 1;
    unsigned long offset = (unsigned long)(m_cursor - m_base);
    offset = (offset + alignMask) & ~alignMask;
    m_cursor = m_base + offset;
}
