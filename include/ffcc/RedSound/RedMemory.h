#ifndef _FFCC_REDSOUND_REDMEMORY_H
#define _FFCC_REDSOUND_REDMEMORY_H

int RedNew(int size);
void RedDelete(int address);
void RedDelete(void* address);
int RedResize(int address, int size);
void* RedResize(void* address, int size);
int RedNewA(int size, int offset, int maxSize);
void RedDeleteA(int address);
void RedDeleteA(void* address);
int RedResizeA(int address, int size);
void* RedResizeA(void* address, int size);

struct RedMemoryBlock {
	int m_address;
	int m_size;
};

enum RedMemoryLayoutSize {
	REDSOUND_MEMORY_BLOCK_ADDRESS_OFFSET = 0x00,
	REDSOUND_MEMORY_BLOCK_SIZE_OFFSET = 0x04,
	REDSOUND_MEMORY_BANK_BLOCK_COUNT = 0x400,
	REDSOUND_MEMORY_NEXT_BLOCK_INDEX = 1,
	REDSOUND_MEMORY_BANK_LAST_INDEX = REDSOUND_MEMORY_BANK_BLOCK_COUNT - 1,
	REDSOUND_MEMORY_BANK_ALIGN = 0x20,
	REDSOUND_MEMORY_BANK_ALIGN_MASK = REDSOUND_MEMORY_BANK_ALIGN - 1,
	REDSOUND_MEMORY_BLOCK_SIZE = sizeof(RedMemoryBlock),
	REDSOUND_MEMORY_BLOCK_INDEX_SHIFT = 3,
	REDSOUND_MEMORY_MAIN_BANK_OFFSET = 0x00,
	REDSOUND_MEMORY_BANK_SIZE = sizeof(RedMemoryBlock) * REDSOUND_MEMORY_BANK_BLOCK_COUNT,
	REDSOUND_MEMORY_BANK_ALLOC_SIZE = 0x2000,
	REDSOUND_MEMORY_AUX_BANK_OFFSET = REDSOUND_MEMORY_MAIN_BANK_OFFSET + REDSOUND_MEMORY_BANK_SIZE,
	REDSOUND_MEMORY_BANK_TABLE_COUNT = 2,
	REDSOUND_MEMORY_BANK_TABLE_SIZE = REDSOUND_MEMORY_BANK_SIZE * REDSOUND_MEMORY_BANK_TABLE_COUNT,
	REDSOUND_MEMORY_BANK_TABLE_ALLOC_SIZE = 0x4000,
	REDSOUND_MEMORY_DATA_BUFFER_OFFSET = REDSOUND_MEMORY_MAIN_BANK_OFFSET + REDSOUND_MEMORY_BANK_TABLE_SIZE,
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
