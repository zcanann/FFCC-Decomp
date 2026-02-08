#include "ffcc/cflat_data.h"
#include "ffcc/chunkfile.h"
#include "ffcc/p_game.h"

#include <dolphin/types.h>
#include <string.h>

void* operator new[](unsigned long, CMemory::CStage*, char*, int);

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
	Destroy();
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
		if (chunk.m_id != 0x43464C44) // 'CFLD'
		{
			continue;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk))
		{
			if (chunk.m_id == 0x4D455320) // 'MES '
			{
				m_mesCount = chunk.m_arg0;
				m_mesBuffer = new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x76) char[chunk.m_size];
				memcpy(m_mesBuffer, chunkFile.GetAddress(), chunk.m_size);

				unsigned char* base = chunkFile.GetAddress();
				for (int i = 0; i < m_mesCount; i++)
				{
					m_mesPtr[i] = m_mesBuffer + (chunkFile.GetAddress() - base);
					chunkFile.GetString();
				}
				continue;
			}

			if (chunk.m_id == 0x44415441) // 'DATA'
			{
				DataEntry& entry = m_data[m_dataCount];
				entry.m_size = chunk.m_arg0;
				entry.m_data = new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x45) unsigned char[chunk.m_arg0];
				chunkFile.Get(entry.m_data, chunk.m_arg0);

				if (chunk.m_version == 0)
				{
					entry.m_numStrings = 0;
					entry.m_strings = (char**)nullptr;
					entry.m_stringBuf = (char*)nullptr;
				}
				else
				{
					entry.m_numStrings = chunkFile.Get4();
					entry.m_strings = (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4C)
						unsigned char[entry.m_numStrings * sizeof(char*)];
					entry.m_stringBuf = new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4D)
						char[entry.m_numStrings];
					memcpy(entry.m_stringBuf, chunkFile.GetAddress(), entry.m_numStrings);

					unsigned char* base = chunkFile.GetAddress();
					for (int i = 0; i < entry.m_numStrings; i++)
					{
						entry.m_strings[i] = entry.m_stringBuf + (chunkFile.GetAddress() - base);
						chunkFile.GetString();
					}
				}

				m_dataCount++;
				continue;
			}

			if (chunk.m_id == 0x5441424C) // 'TABL'
			{
				TableEntry& table = m_tabl[m_tableCount];
				table.m_numEntries = chunk.m_arg0;
				table.m_strings = (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x65)
					unsigned char[chunk.m_arg0 * sizeof(char*)];
				table.m_stringBuf = new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x66) char[chunk.m_size];
				memcpy(table.m_stringBuf, chunkFile.GetAddress(), chunk.m_size);

				unsigned char* base = chunkFile.GetAddress();
				for (int i = 0; i < table.m_numEntries; i++)
				{
					table.m_strings[i] = table.m_stringBuf + (chunkFile.GetAddress() - base);
					chunkFile.GetString();
				}

				m_tableCount++;
			}
		}
		chunkFile.PopChunk();
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
