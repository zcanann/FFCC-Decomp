#include "ffcc/cflat_data.h"
#include "ffcc/chunkfile.h"
#include "ffcc/game.h"

#include <dolphin/types.h>
#include <string.h>

void* operator new[](unsigned long, CMemory::CStage*, char*, int);
extern "C" char s_cflat_data_cpp[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatData::Destroy()
{
	// First: free per-data entries
	for (int i = 0; i < m_dataCount; i++)
	{
		if (m_data[i].m_data != nullptr)
		{
			operator delete(m_data[i].m_data);
			m_data[i].m_data = nullptr;
		}
		if (m_data[i].m_strings != nullptr)
		{
			operator delete(m_data[i].m_strings);
			m_data[i].m_strings = (char**)nullptr;
		}
		if (m_data[i].m_stringBuf != nullptr)
		{
			operator delete(m_data[i].m_stringBuf);
			m_data[i].m_stringBuf = (char*)nullptr;
		}
	}
	m_dataCount = 0;

	// Next: free tables
	for (int i = 0; i < m_tableCount; i++)
	{
		if (m_tabl[i].m_strings != nullptr)
		{
			operator delete(m_tabl[i].m_strings);
			m_tabl[i].m_strings = (char**)nullptr;
		}
		if (m_tabl[i].m_stringBuf != nullptr)
		{
			operator delete(m_tabl[i].m_stringBuf);
			m_tabl[i].m_stringBuf = (char*)nullptr;
		}
	}
	m_tableCount = 0;

	// Finally: free mes buffer
	if (m_mesBuffer != nullptr)
	{
		operator delete(m_mesBuffer);
		m_mesBuffer = (char*)nullptr;
	}
	m_mesCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80097be8
 * PAL Size: 1228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatData::Create(void* filePtr)
{
	Destroy();

	CChunkFile chunkFile(filePtr);
	CChunkFile::CChunk chunk;
	while (chunkFile.GetNextChunk(chunk))
	{
		if (chunk.m_id == 0x43464C44) // 'CFLD'
		{
			chunkFile.PushChunk();
			while (chunkFile.GetNextChunk(chunk))
			{
				switch (chunk.m_id)
				{
				case 0x44415441: // 'DATA'
				{
					m_data[m_dataCount].m_size = chunk.m_arg0;
					m_data[m_dataCount].m_data = new (Game.m_mainStage, s_cflat_data_cpp, 0x45) unsigned char[chunk.m_arg0];
					chunkFile.Get(m_data[m_dataCount].m_data, chunk.m_arg0);

					if (chunk.m_version >= 1)
					{
						int iVar1;
						int iVar7;
						int numStrings;
						char* stringBase;

						numStrings = chunkFile.Get4();
						m_data[m_dataCount].m_numStrings = numStrings;
						m_data[m_dataCount].m_strings = new (Game.m_mainStage, s_cflat_data_cpp, 0x4C) char*[numStrings];
						m_data[m_dataCount].m_stringBuf = new (Game.m_mainStage, s_cflat_data_cpp, 0x4D) char[numStrings];

						memcpy(m_data[m_dataCount].m_stringBuf, chunkFile.GetAddress(), numStrings);
						stringBase = (char*)chunkFile.GetAddress();

						for (iVar7 = 0; (iVar1 = m_dataCount, iVar7 < m_data[iVar1].m_numStrings); iVar7++)
						{
							m_data[iVar1].m_strings[iVar7] =
							    &m_data[iVar1].m_stringBuf[(char*)chunkFile.GetAddress() - stringBase];
							chunkFile.GetString();
						}
					}
					else
					{
						m_data[m_dataCount].m_numStrings = 0;
						m_data[m_dataCount].m_stringBuf = (char*)nullptr;
						m_data[m_dataCount].m_strings = (char**)nullptr;
					}

					m_dataCount++;
					break;
				}
				case 0x5441424C: // 'TABL'
				{
					char** stringIndex;
					int iVar1;
					int iVar7;
					char* stringBase;

					m_tabl[m_tableCount].m_numEntries = chunk.m_arg0;
					stringIndex = (char**)new (Game.m_mainStage, s_cflat_data_cpp, 0x65) unsigned char[chunk.m_arg0 << 2];
					m_tabl[m_tableCount].m_strings = stringIndex;
					m_tabl[m_tableCount].m_stringBuf = new (Game.m_mainStage, s_cflat_data_cpp, 0x66) char[chunk.m_size];

					memcpy(m_tabl[m_tableCount].m_stringBuf, chunkFile.GetAddress(), chunk.m_size);

					stringBase = (char*)chunkFile.GetAddress();
					for (iVar7 = 0; (iVar1 = m_tableCount, iVar7 < m_tabl[iVar1].m_numEntries); iVar7++)
					{
						m_tabl[iVar1].m_strings[iVar7] =
						    &m_tabl[iVar1].m_stringBuf[(char*)chunkFile.GetAddress() - stringBase];
						chunkFile.GetString();
					}
					m_tableCount++;
					break;
				}
				case 0x4D455320: // 'MES '
				{
					int iVar7;
					char* stringBase;

					m_mesCount = chunk.m_arg0;
					m_mesBuffer = new (Game.m_mainStage, s_cflat_data_cpp, 0x76) char[chunk.m_size];
					memcpy(m_mesBuffer, chunkFile.GetAddress(), chunk.m_size);

					stringBase = (char*)chunkFile.GetAddress();
					for (iVar7 = 0; iVar7 < m_mesCount; iVar7++)
					{
						m_mesPtr[iVar7] = &m_mesBuffer[(char*)chunkFile.GetAddress() - stringBase];
						chunkFile.GetString();
					}
					break;
				}
				}
			}
			chunkFile.PopChunk();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800980b4
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatData::~CFlatData()
{
	int i;

	for (i = 0; i < m_dataCount; i++)
	{
		if (m_data[i].m_data != nullptr)
		{
			operator delete(m_data[i].m_data);
			m_data[i].m_data = nullptr;
		}
		if (m_data[i].m_strings != nullptr)
		{
			operator delete(m_data[i].m_strings);
			m_data[i].m_strings = (char**)nullptr;
		}
		if (m_data[i].m_stringBuf != nullptr)
		{
			operator delete(m_data[i].m_stringBuf);
			m_data[i].m_stringBuf = (char*)nullptr;
		}
	}
	m_dataCount = 0;

	for (i = 0; i < m_tableCount; i++)
	{
		if (m_tabl[i].m_strings != nullptr)
		{
			operator delete(m_tabl[i].m_strings);
			m_tabl[i].m_strings = (char**)nullptr;
		}
		if (m_tabl[i].m_stringBuf != nullptr)
		{
			operator delete(m_tabl[i].m_stringBuf);
			m_tabl[i].m_stringBuf = (char*)nullptr;
		}
	}
	m_tableCount = 0;

	if (m_mesBuffer != nullptr)
	{
		operator delete(m_mesBuffer);
		m_mesBuffer = (char*)nullptr;
	}
	m_mesCount = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatData::CFlatData()
{
	m_dataCount = 0;
	m_tableCount = 0;
	m_mesCount = 0;
	m_mesBuffer = (char*)nullptr;
}
