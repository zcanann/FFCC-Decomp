#ifndef _FFCC_CFLAT_DATA_H_
#define _FFCC_CFLAT_DATA_H_

class CFlatData
{
public:
    struct DataEntry
    {
        unsigned int m_size; // 0x0
        void* m_data;        // 0x4
        int m_numStrings;    // 0x8
        char** m_strings;    // 0xC
        char* m_stringBuf;   // 0x10
    };

    struct TableEntry
    {
        int m_numEntries;  // 0x0
        char** m_strings;  // 0x4
        char* m_stringBuf; // 0x8
    };

	CFlatData();
	~CFlatData();

	void Create(void*);
	void Destroy();

    DataEntry& Data(int index) { return m_data[index]; }
    const DataEntry& Data(int index) const { return m_data[index]; }
    TableEntry& Table(int index) { return m_tabl[index]; }
    const TableEntry& Table(int index) const { return m_tabl[index]; }
    char** TableStrings(int index) { return Table(index).m_strings; }
    char* const* TableStrings(int index) const { return Table(index).m_strings; }
    char* Message(int index) { return m_mesPtr[index]; }
    const char* Message(int index) const { return m_mesPtr[index]; }

private:
    int m_dataCount;            // 0x0000
    DataEntry m_data[5];        // 0x0004
    int m_tableCount;           // 0x0068
    TableEntry m_tabl[8];       // 0x006C
    int m_mesCount;             // 0x00CC
    char* m_mesBuffer;          // 0x00D0
    char* m_mesPtr[1122];       // 0x00D4 .. 0x125B (1122 * 4 = 0x1188)
    int m_numMes;               // 0x125C
    char _pad_1260_1334[0xD4];  // 0x1260
    unsigned int m_mesVal[104]; // 0x1334 .. 0x14D3 (104 * 4 = 0x1A0)
};

#endif // _FFCC_CFLAT_DATA_H_
