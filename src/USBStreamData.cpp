#include "ffcc/USBStreamData.h"

#include "ffcc/File.h"

/*
 * --INFO--
 * PAL Address: 0x800503FC
 * PAL Size: 16b
 * EN Address: 0x800501F0
 * EN Size: 16b
 * JP Address: 0x8004FC78
 * JP Size: 16b
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
 * EN Address: 0x80050200
 * EN Size: 40b
 * JP Address: 0x8004FC88
 * JP Size: 40b
 */
int CUSBStreamData::IsUSBStreamDataDone()
{ 
	if (m_dataReady != 0 && m_headerReady != 0)
	{
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80050434
 * PAL Size: 84b
 * EN Address: 0x80050228
 * EN Size: 84b
 * JP Address: 0x8004FCB0
 * JP Size: 84b
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
 * EN Address: 0x8005027C
 * EN Size: 20b
 * JP Address: 0x8004FD04
 * JP Size: 20b
 */
void CUSBStreamData::CreateBuffer()
{ 
	m_data = (unsigned char*)File.m_readBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x8005049C
 * PAL Size: 100b
 * EN Address: 0x80050290
 * EN Size: 100b
 * JP Address: 0x8004FD18
 * JP Size: 100b
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
 * EN Address: 0x800502F4
 * EN Size: 28b
 * JP Address: 0x8004FD7C
 * JP Size: 28b
 */
CUSBStreamData::CUSBStreamData()
{ 
	m_data = (unsigned char*)nullptr;
	m_headerReady = 0;
	m_dataReady = 0;
	m_sizeBytes = 0;
	m_packetCode = 0;
}
