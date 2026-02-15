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
 * PAL Address: 0x800980b4
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CFlatData* dtor_800980B4(CFlatData* flatData, short shouldDelete)
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

	FlatDataLayout* self;
	FlatDataLayout* layout;
	int i;

	if (flatData != nullptr)
	{
		layout = (FlatDataLayout*)flatData;
		self = layout;
		for (i = 0; i < layout->m_dataCount; i++)
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
			self = (FlatDataLayout*)&self->m_data[0].m_stringBuf;
		}
		layout->m_dataCount = 0;

		self = layout;
		for (i = 0; i < layout->m_tableCount; i++)
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
			self = (FlatDataLayout*)&self->m_data[0].m_numStrings;
		}
		layout->m_tableCount = 0;

		if (layout->m_mesBuffer != nullptr)
		{
			operator delete(layout->m_mesBuffer);
			layout->m_mesBuffer = (char*)nullptr;
		}
		layout->m_mesCount = 0;

		if (0 < shouldDelete)
		{
			operator delete(flatData);
		}
	}
	return flatData;
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
    int i;

    for (i = 0; i < m_dataCount; i++) {
        if (self->m_data[0].m_data != nullptr) {
            operator delete(self->m_data[0].m_data);
            self->m_data[0].m_data = nullptr;
        }
        if (self->m_data[0].m_strings != nullptr) {
            operator delete(self->m_data[0].m_strings);
            self->m_data[0].m_strings = (char**)nullptr;
        }
        if (self->m_data[0].m_stringBuf != nullptr) {
            operator delete(self->m_data[0].m_stringBuf);
            self->m_data[0].m_stringBuf = (char*)nullptr;
        }
        self = (CFlatData*)&self->m_data[0].m_stringBuf;
    }
    m_dataCount = 0;

    self = this;
    for (i = 0; i < m_tableCount; i++) {
        if (self->m_tabl[0].m_strings != nullptr) {
            operator delete(self->m_tabl[0].m_strings);
            self->m_tabl[0].m_strings = (char**)nullptr;
        }
        if (self->m_tabl[0].m_stringBuf != nullptr) {
            operator delete(self->m_tabl[0].m_stringBuf);
            self->m_tabl[0].m_stringBuf = (char*)nullptr;
        }
        self = (CFlatData*)&self->m_data[0].m_numStrings;
    }
    m_tableCount = 0;

    if (m_mesBuffer != nullptr) {
        operator delete(m_mesBuffer);
        m_mesBuffer = (char*)nullptr;
    }
    m_mesCount = 0;

    CChunkFile chunkFile(filePtr);
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id == 0x43464C44) { // 'CFLD'
            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 0x4D455320) { // 'MES '
                    m_mesCount = chunk.m_arg0;
                    m_mesBuffer = new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x76) char[chunk.m_size];
                    memcpy(m_mesBuffer, chunkFile.GetAddress(), chunk.m_size);

                    int baseAddress = (int)chunkFile.GetAddress();
                    self = this;
                    for (i = 0; i < m_mesCount; i++) {
                        int curAddress = (int)chunkFile.GetAddress();
                        self->m_mesPtr[0] = m_mesBuffer + (curAddress - baseAddress);
                        chunkFile.GetString();
                        self = (CFlatData*)self->m_data;
                    }
                } else if ((int)chunk.m_id < 0x4D455320) {
                    if (chunk.m_id == 0x44415441) { // 'DATA'
                        m_data[m_dataCount].m_size = chunk.m_arg0;
                        m_data[m_dataCount].m_data =
                            new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x45) unsigned char[chunk.m_arg0];
                        chunkFile.Get(m_data[m_dataCount].m_data, chunk.m_arg0);

                        if (chunk.m_version == 0) {
                            m_data[m_dataCount].m_numStrings = 0;
                            m_data[m_dataCount].m_stringBuf = (char*)nullptr;
                            m_data[m_dataCount].m_strings = (char**)nullptr;
                        } else {
                            int stringCount = chunkFile.Get4();
                            int offset = 0;

                            m_data[m_dataCount].m_numStrings = stringCount;
                            m_data[m_dataCount].m_strings =
                                (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4C)
                                    unsigned char[stringCount << 2];
                            m_data[m_dataCount].m_stringBuf =
                                new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x4D) char[stringCount];
                            memcpy(m_data[m_dataCount].m_stringBuf, chunkFile.GetAddress(), stringCount);

                            int baseAddress = (int)chunkFile.GetAddress();
                            for (i = 0; i < m_data[m_dataCount].m_numStrings; i++) {
                                int curAddress = (int)chunkFile.GetAddress();
                                *(char**)((int)m_data[m_dataCount].m_strings + offset) =
                                    m_data[m_dataCount].m_stringBuf + (curAddress - baseAddress);
                                chunkFile.GetString();
                                offset += 4;
                            }
                        }

                        m_dataCount++;
                    }
                } else if (chunk.m_id == 0x5441424C) { // 'TABL'
                    int offset = 0;
                    m_tabl[m_tableCount].m_numEntries = chunk.m_arg0;
                    m_tabl[m_tableCount].m_strings = (char**)new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x65)
                        unsigned char[chunk.m_arg0 << 2];
                    m_tabl[m_tableCount].m_stringBuf =
                        new (Game.game.m_mainStage, (char*)"cflat_data.cpp", 0x66) char[chunk.m_size];
                    memcpy(m_tabl[m_tableCount].m_stringBuf, chunkFile.GetAddress(), chunk.m_size);

                    int baseAddress = (int)chunkFile.GetAddress();
                    for (i = 0; i < m_tabl[m_tableCount].m_numEntries; i++) {
                        int curAddress = (int)chunkFile.GetAddress();
                        *(char**)((int)m_tabl[m_tableCount].m_strings + offset) =
                            m_tabl[m_tableCount].m_stringBuf + (curAddress - baseAddress);
                        chunkFile.GetString();
                        offset += 4;
                    }

                    m_tableCount++;
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
