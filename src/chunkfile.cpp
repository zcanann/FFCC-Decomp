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
	m_stackDepth = m_stackDepth + -1;
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
		int s = m_lastChunkSize + 0xF;

		skip = (s / 16) * 16 + 0x10;
	}

    m_scopeOffset += skip;
    m_headerPtr += skip;
    m_cursor = m_headerPtr;

    if ((int)m_scopeSize <= m_scopeOffset)
	{
        return false;
	}

    unsigned int* cursorPtr = (unsigned int*)m_cursor;

    m_cursor += sizeof(unsigned int);
    outChunk.m_id = *cursorPtr;

    cursorPtr = (unsigned int*)m_cursor;
    m_cursor += sizeof(unsigned int);
    outChunk.m_size = *cursorPtr;

    cursorPtr = (unsigned int*)m_cursor;
    m_cursor += sizeof(unsigned int);
    outChunk.m_arg0 = *cursorPtr;

    cursorPtr = (unsigned int*)m_cursor;
    m_cursor += sizeof(unsigned int);
    outChunk.m_version = *cursorPtr;

    m_lastChunkSize = (int)outChunk.m_size;

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
void CChunkFile::Get(void* param_2, long param_3)
{ 
	memcpy(param_2, m_cursor, param_3);

	m_cursor = m_cursor + param_3;
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
    float value;
    unsigned char* cursorPtr = m_cursor;

    m_cursor += 4;
    *(unsigned int*)&value = *(unsigned int*)cursorPtr;

    return value;
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
    unsigned long delta = (unsigned long)(m_cursor - m_base);

    delta += alignment - 1;
    delta -= (delta % alignment);

    m_cursor = m_base + delta;
}
