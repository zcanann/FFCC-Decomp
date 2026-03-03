#include "ffcc/USBStreamData.h"

#include "ffcc/File.h"

/*
 * --INFO--
 * PAL Address: 0x800503FC
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBStreamData::SetUSBStreamDataDone()
{ 
	m_headerReady = 0;
	m_dataReady = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005040C
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x80050434
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x80050488
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBStreamData::CreateBuffer()
{ 
	m_data = (unsigned char*)File.m_readBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x8005049C
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x80050500
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CUSBStreamData::CUSBStreamData()
{ 
	m_data = (unsigned char*)nullptr;
	m_headerReady = 0;
	m_dataReady = 0;
	m_sizeBytes = 0;
	m_packetCode = 0;
}
