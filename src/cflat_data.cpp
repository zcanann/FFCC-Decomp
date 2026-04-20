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
	struct DataEntryLayout
	{
		unsigned int m_size;
		void* m_data;
		int m_numStrings;
		char** m_strings;
		char* m_stringBuf;
	};

	struct TableEntryLayout
	{
		int m_numEntries;
		char** m_strings;
		char* m_stringBuf;
	};

	struct FlatDataLayout
	{
		int m_dataCount;
		DataEntryLayout m_data[5];
		int m_tableCount;
		TableEntryLayout m_tabl[8];
		int m_mesCount;
		char* m_mesBuffer;
		char* m_mesPtr[1122];
	};

	int iVar10;
	FlatDataLayout* dataIter;

	dataIter = (FlatDataLayout*)this;
	for (iVar10 = 0; iVar10 < ((FlatDataLayout*)this)->m_dataCount; iVar10++)
	{
		if (dataIter->m_data[0].m_data != nullptr)
		{
			operator delete(dataIter->m_data[0].m_data);
			dataIter->m_data[0].m_data = nullptr;
		}
		if (dataIter->m_data[0].m_strings != nullptr)
		{
			operator delete(dataIter->m_data[0].m_strings);
			dataIter->m_data[0].m_strings = (char**)nullptr;
		}
		if (dataIter->m_data[0].m_stringBuf != nullptr)
		{
			operator delete(dataIter->m_data[0].m_stringBuf);
			dataIter->m_data[0].m_stringBuf = (char*)nullptr;
		}
		dataIter = (FlatDataLayout*)&dataIter->m_data[0].m_stringBuf;
	}
	((FlatDataLayout*)this)->m_dataCount = 0;

	FlatDataLayout* tableIter;
	tableIter = (FlatDataLayout*)this;
	for (iVar10 = 0; iVar10 < ((FlatDataLayout*)this)->m_tableCount; iVar10++)
	{
		if (tableIter->m_tabl[0].m_strings != nullptr)
		{
			operator delete(tableIter->m_tabl[0].m_strings);
			tableIter->m_tabl[0].m_strings = (char**)nullptr;
		}
		if (tableIter->m_tabl[0].m_stringBuf != nullptr)
		{
			operator delete(tableIter->m_tabl[0].m_stringBuf);
			tableIter->m_tabl[0].m_stringBuf = (char*)nullptr;
		}
		tableIter = (FlatDataLayout*)&tableIter->m_data[0].m_numStrings;
	}
	((FlatDataLayout*)this)->m_tableCount = 0;

	if (((FlatDataLayout*)this)->m_mesBuffer != nullptr)
	{
		operator delete(((FlatDataLayout*)this)->m_mesBuffer);
		((FlatDataLayout*)this)->m_mesBuffer = (char*)nullptr;
	}
	((FlatDataLayout*)this)->m_mesCount = 0;

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
extern "C" CFlatData* __dt__9CFlatDataFv(CFlatData* flatData, short shouldDelete)
{
	struct DataEntryLayout
	{
		unsigned int m_size;
		void* m_data;
		int m_numStrings;
		char** m_strings;
		char* m_stringBuf;
	};

	struct TableEntryLayout
	{
		int m_numEntries;
		char** m_strings;
		char* m_stringBuf;
	};

	struct FlatDataLayout
	{
		int m_dataCount;
		DataEntryLayout m_data[5];
		int m_tableCount;
		TableEntryLayout m_tabl[8];
		int m_mesCount;
		char* m_mesBuffer;
	};

	int iVar2;
	FlatDataLayout* dataIter;
	FlatDataLayout* tableIter;

	if (flatData != nullptr)
	{
		dataIter = (FlatDataLayout*)flatData;
		for (iVar2 = 0; iVar2 < ((FlatDataLayout*)flatData)->m_dataCount; iVar2++)
		{
			if (dataIter->m_data[0].m_data != nullptr)
			{
				operator delete(dataIter->m_data[0].m_data);
				dataIter->m_data[0].m_data = nullptr;
			}
			if (dataIter->m_data[0].m_strings != nullptr)
			{
				operator delete(dataIter->m_data[0].m_strings);
				dataIter->m_data[0].m_strings = (char**)nullptr;
			}
			if (dataIter->m_data[0].m_stringBuf != nullptr)
			{
				operator delete(dataIter->m_data[0].m_stringBuf);
				dataIter->m_data[0].m_stringBuf = (char*)nullptr;
			}
			dataIter = (FlatDataLayout*)&dataIter->m_data[0].m_stringBuf;
		}
		((FlatDataLayout*)flatData)->m_dataCount = 0;

		tableIter = (FlatDataLayout*)flatData;
		for (iVar2 = 0; iVar2 < ((FlatDataLayout*)flatData)->m_tableCount; iVar2++)
		{
			if (tableIter->m_tabl[0].m_strings != nullptr)
			{
				operator delete(tableIter->m_tabl[0].m_strings);
				tableIter->m_tabl[0].m_strings = (char**)nullptr;
			}
			if (tableIter->m_tabl[0].m_stringBuf != nullptr)
			{
				operator delete(tableIter->m_tabl[0].m_stringBuf);
				tableIter->m_tabl[0].m_stringBuf = (char*)nullptr;
			}
			tableIter = (FlatDataLayout*)&tableIter->m_data[0].m_numStrings;
		}
		((FlatDataLayout*)flatData)->m_tableCount = 0;

		if (((FlatDataLayout*)flatData)->m_mesBuffer != nullptr)
		{
			operator delete(((FlatDataLayout*)flatData)->m_mesBuffer);
			((FlatDataLayout*)flatData)->m_mesBuffer = (char*)nullptr;
		}
		((FlatDataLayout*)flatData)->m_mesCount = 0;

		if (0 < shouldDelete)
		{
			operator delete(flatData);
		}
	}

	return flatData;
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
