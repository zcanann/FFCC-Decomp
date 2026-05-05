#ifndef _FFCC_REDSOUND_REDMEMORY_H
#define _FFCC_REDSOUND_REDMEMORY_H

int RedNew(int);
void RedDelete(int);
void RedDelete(void*);
int RedNewA(int, int, int);
void RedDeleteA(int);
void RedDeleteA(void*);

struct RedMemoryBlock {
	int m_address;
	int m_size;
};

enum RedMemoryLayoutSize {
	REDSOUND_MEMORY_BANK_BLOCK_COUNT = 0x400,
	REDSOUND_MEMORY_BANK_LAST_INDEX = REDSOUND_MEMORY_BANK_BLOCK_COUNT - 1,
	REDSOUND_MEMORY_BANK_ALIGN = 0x20,
	REDSOUND_MEMORY_BANK_ALIGN_MASK = REDSOUND_MEMORY_BANK_ALIGN - 1,
	REDSOUND_MEMORY_BLOCK_SIZE = sizeof(RedMemoryBlock),
	REDSOUND_MEMORY_BLOCK_INDEX_SHIFT = 3,
	REDSOUND_MEMORY_BANK_SIZE = sizeof(RedMemoryBlock) * REDSOUND_MEMORY_BANK_BLOCK_COUNT,
	REDSOUND_MEMORY_BANK_TABLE_COUNT = 2,
	REDSOUND_MEMORY_ALLOC_FAILED = -1,
};

class CRedMemory
{
public:
	CRedMemory();
	~CRedMemory();

	void Init(int mainBuffer, int mainBufferSize, int auxBuffer, int auxBufferSize);
	int GetMainBufferAddress();
	int GetMainBufferSize();
	RedMemoryBlock* GetMainBankAddress();
	int GetABufferAddress();
	int GetABufferSize();
	RedMemoryBlock* GetABankAddress();
};

#endif // _FFCC_REDSOUND_REDMEMORY_H
