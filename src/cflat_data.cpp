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
	CFlatData* self = this;
	for (int i = 0; i < m_dataCount; i++)
	{
		if (self->m_data[0].m_data != nullptr)
		{
			operator delete(self->m_data[0].m_data);
			self->m_data[0].m_data = nullptr;
		}
		if (self->m_data[0].m_strings != nullptr)
		{
			operator delete(self->m_data[0].m_strings);
			self->m_data[0].m_strings = (char**)nullptr;
		}
		if (self->m_data[0].m_stringBuf != nullptr)
		{
			operator delete(self->m_data[0].m_stringBuf);
			self->m_data[0].m_stringBuf = (char*)nullptr;
		}
		self = (CFlatData*)&self->m_data[0].m_stringBuf;
	}
	m_dataCount = 0;

	self = this;
	for (int i = 0; i < m_tableCount; i++)
	{
		if (self->m_tabl[0].m_strings != nullptr)
		{
			operator delete(self->m_tabl[0].m_strings);
			self->m_tabl[0].m_strings = (char**)nullptr;
		}
		if (self->m_tabl[0].m_stringBuf != nullptr)
		{
			operator delete(self->m_tabl[0].m_stringBuf);
			self->m_tabl[0].m_stringBuf = (char*)nullptr;
		}
		self = (CFlatData*)&self->m_data[0].m_numStrings;
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
				self = this;
				for (int i = 0; i < m_mesCount; i++)
				{
					self->m_mesPtr[0] = m_mesBuffer + (chunkFile.GetAddress() - base);
					chunkFile.GetString();
					self = (CFlatData*)self->m_data;
				}
				continue;
			}

			if (chunk.m_id < 0x4D455320)
			{
				if (chunk.m_id == 0x44415441) // 'DATA'
				{
					m_data[m_dataCount].m_size = chunk.m_arg0;
					m_data[m_dataCount].m_data =
						new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x45) unsigned char[chunk.m_arg0];
					chunkFile.Get(m_data[m_dataCount].m_data, chunk.m_arg0);

					if (chunk.m_version == 0)
					{
						m_data[m_dataCount].m_numStrings = 0;
						m_data[m_dataCount].m_stringBuf = (char*)nullptr;
						m_data[m_dataCount].m_strings = (char**)nullptr;
					}
					else
					{
						m_data[m_dataCount].m_numStrings = chunkFile.Get4();
						m_data[m_dataCount].m_strings = (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4C)
							unsigned char[m_data[m_dataCount].m_numStrings * sizeof(char*)];
						m_data[m_dataCount].m_stringBuf =
							new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4D) char[m_data[m_dataCount].m_numStrings];
						memcpy(m_data[m_dataCount].m_stringBuf, chunkFile.GetAddress(), m_data[m_dataCount].m_numStrings);

						unsigned char* base = chunkFile.GetAddress();
						for (int i = 0; i < m_data[m_dataCount].m_numStrings; i++)
						{
							m_data[m_dataCount].m_strings[i] =
								m_data[m_dataCount].m_stringBuf + (chunkFile.GetAddress() - base);
							chunkFile.GetString();
						}
					}

					m_dataCount++;
				}
			}
			else if (chunk.m_id == 0x5441424C) // 'TABL'
			{
				m_tabl[m_tableCount].m_numEntries = chunk.m_arg0;
				m_tabl[m_tableCount].m_strings = (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x65)
					unsigned char[chunk.m_arg0 * sizeof(char*)];
				m_tabl[m_tableCount].m_stringBuf =
					new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x66) char[chunk.m_size];
				memcpy(m_tabl[m_tableCount].m_stringBuf, chunkFile.GetAddress(), chunk.m_size);

				unsigned char* base = chunkFile.GetAddress();
				for (int i = 0; i < m_tabl[m_tableCount].m_numEntries; i++)
				{
					m_tabl[m_tableCount].m_strings[i] = m_tabl[m_tableCount].m_stringBuf + (chunkFile.GetAddress() - base);
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
