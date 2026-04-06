#include "ffcc/cflat_data.h"
#include "ffcc/chunkfile.h"
#include "ffcc/p_game.h"

#include <dolphin/types.h>
#include <string.h>

void* operator new[](unsigned long, CMemory::CStage*, char*, int);
extern "C" extern char s_cflat_data_cpp[];

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
	CFlatData* flatData;
	int iVar2;

	flatData = this;
	for (iVar2 = 0; iVar2 < m_dataCount; iVar2++)
	{
		if (flatData->m_data[0].m_data != nullptr)
		{
			operator delete(flatData->m_data[0].m_data);
			flatData->m_data[0].m_data = nullptr;
		}
		if (flatData->m_data[0].m_strings != nullptr)
		{
			operator delete(flatData->m_data[0].m_strings);
			flatData->m_data[0].m_strings = (char**)nullptr;
		}
		if (flatData->m_data[0].m_stringBuf != nullptr)
		{
			operator delete(flatData->m_data[0].m_stringBuf);
			flatData->m_data[0].m_stringBuf = (char*)nullptr;
		}
		flatData = (CFlatData*)&flatData->m_data[0].m_stringBuf;
	}
	m_dataCount = 0;

	flatData = this;
	for (iVar2 = 0; iVar2 < m_tableCount; iVar2++)
	{
		if (flatData->m_tabl[0].m_strings != nullptr)
		{
			operator delete(flatData->m_tabl[0].m_strings);
			flatData->m_tabl[0].m_strings = (char**)nullptr;
		}
		if (flatData->m_tabl[0].m_stringBuf != nullptr)
		{
			operator delete(flatData->m_tabl[0].m_stringBuf);
			flatData->m_tabl[0].m_stringBuf = (char*)nullptr;
		}
		flatData = (CFlatData*)&flatData->m_data[0].m_numStrings;
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
 * PAL Address: 0x80097be8
 * PAL Size: 1228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatData::Create(void* filePtr)
{
	CFlatData* flatData;
	int iVar1;
	int iVar10;

	flatData = this;
	for (iVar10 = 0; iVar10 < m_dataCount; iVar10++)
	{
		if (flatData->m_data[0].m_data != nullptr)
		{
			operator delete(flatData->m_data[0].m_data);
			flatData->m_data[0].m_data = nullptr;
		}
		if (flatData->m_data[0].m_strings != nullptr)
		{
			operator delete(flatData->m_data[0].m_strings);
			flatData->m_data[0].m_strings = (char**)nullptr;
		}
		if (flatData->m_data[0].m_stringBuf != nullptr)
		{
			operator delete(flatData->m_data[0].m_stringBuf);
			flatData->m_data[0].m_stringBuf = (char*)nullptr;
		}
		flatData = (CFlatData*)&flatData->m_data[0].m_stringBuf;
	}
	m_dataCount = 0;

	flatData = this;
	for (iVar10 = 0; iVar10 < m_tableCount; iVar10++)
	{
		if (flatData->m_tabl[0].m_strings != nullptr)
		{
			operator delete(flatData->m_tabl[0].m_strings);
			flatData->m_tabl[0].m_strings = (char**)nullptr;
		}
		if (flatData->m_tabl[0].m_stringBuf != nullptr)
		{
			operator delete(flatData->m_tabl[0].m_stringBuf);
			flatData->m_tabl[0].m_stringBuf = (char*)nullptr;
		}
		flatData = (CFlatData*)&flatData->m_data[0].m_numStrings;
	}
	m_tableCount = 0;

	if (m_mesBuffer != nullptr)
	{
		operator delete(m_mesBuffer);
		m_mesBuffer = (char*)nullptr;
	}
	m_mesCount = 0;

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
						char* charPtr;
						char** stringIndex;
						int indexOffset;
						int iVar6;
						int iVar7;
						int iVar8;

						iVar10 = chunkFile.Get4();
						m_data[m_dataCount].m_numStrings = iVar10;
						stringIndex = (char**)new (Game.m_mainStage, s_cflat_data_cpp, 0x4C) unsigned char[iVar10 << 2];
						m_data[m_dataCount].m_strings = stringIndex;
						charPtr = new (Game.m_mainStage, s_cflat_data_cpp, 0x4D) char[iVar10];
						m_data[m_dataCount].m_stringBuf = charPtr;

						memcpy(m_data[m_dataCount].m_stringBuf, chunkFile.GetAddress(), iVar10);
						iVar10 = (int)chunkFile.GetAddress();
						indexOffset = 0;

						for (iVar7 = 0; (iVar1 = m_dataCount, iVar7 < m_data[iVar1].m_numStrings); iVar7++)
						{
							iVar6 = (int)chunkFile.GetAddress();
							*(char**)((int)m_data[iVar1].m_strings + indexOffset) = m_data[iVar1].m_stringBuf + (iVar6 - iVar10);
							chunkFile.GetString();
							indexOffset += 4;
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
					int iVar6;
					int iVar7;
					int indexOffset;
					int stringBase;

					m_tabl[m_tableCount].m_numEntries = chunk.m_arg0;
					stringIndex = (char**)new (Game.m_mainStage, s_cflat_data_cpp, 0x65) unsigned char[chunk.m_arg0 << 2];
					m_tabl[m_tableCount].m_strings = stringIndex;
					m_tabl[m_tableCount].m_stringBuf = new (Game.m_mainStage, s_cflat_data_cpp, 0x66) char[chunk.m_size];

					memcpy(m_tabl[m_tableCount].m_stringBuf, chunkFile.GetAddress(), chunk.m_size);

					stringBase = (int)chunkFile.GetAddress();
					iVar7 = 0;
					indexOffset = 0;
					while (iVar7 < m_tabl[m_tableCount].m_numEntries)
					{
						iVar6 = (int)chunkFile.GetAddress();
						*(char**)((int)m_tabl[m_tableCount].m_strings + indexOffset) =
							m_tabl[m_tableCount].m_stringBuf + (iVar6 - stringBase);
						chunkFile.GetString();
						indexOffset += 4;
						iVar7++;
					}
					m_tableCount++;
					break;
				}
				case 0x4D455320: // 'MES '
				{
					int iVar7;
					int iVar8;
					char* charPtr;

					m_mesCount = chunk.m_arg0;
					charPtr = new (Game.m_mainStage, s_cflat_data_cpp, 0x76) char[chunk.m_size];
					m_mesBuffer = charPtr;
					memcpy(m_mesBuffer, chunkFile.GetAddress(), chunk.m_size);

					iVar10 = (int)chunkFile.GetAddress();
					flatData = this;
					for (iVar7 = 0; iVar7 < m_mesCount; iVar7++)
					{
						iVar8 = (int)chunkFile.GetAddress();
						flatData->m_mesPtr[0] = m_mesBuffer + (iVar8 - iVar10);
						chunkFile.GetString();
						flatData = (CFlatData*)flatData->m_data;
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
