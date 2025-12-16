#include "ffcc/USBStreamData.h"

#include "ffcc/File.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CUSBStreamData::CUSBStreamData()
{ 
	m_data = (unsigned char*)nullptr;
	m_headerReady = 0;
	m_dataReady = 0;
	m_sizeBytes = 0;
	m_packetCode = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CUSBStreamData::~CUSBStreamData()
{                                               
	if (m_data != (unsigned char*)nullptr)
	{
		delete[] m_data;
		m_data = (unsigned char*)nullptr;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBStreamData::CreateBuffer()
{ 
	m_data = (unsigned char*)File.m_readBuffer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBStreamData::DeleteBuffer()
{ 
	if (m_data != (unsigned char*)nullptr)
	{
		delete[] m_data;
		m_data = (unsigned char*)nullptr;
	}

	m_headerReady = 0;
	m_dataReady = 0;
	m_sizeBytes = 0;
	m_packetCode = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CUSBStreamData::IsUSBStreamDataDone()
{ 
	if (m_dataReady != 0 && m_headerReady != 0)
	{
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBStreamData::SetUSBStreamDataDone()
{ 
	m_headerReady = 0;
	m_dataReady = 0;
}
