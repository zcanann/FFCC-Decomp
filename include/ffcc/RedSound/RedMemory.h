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

enum RedMemoryBlockLayoutSize {
	REDSOUND_MEMORY_BLOCK_ADDRESS_OFFSET = (unsigned int)&(((RedMemoryBlock*)0)->m_address),
	REDSOUND_MEMORY_BLOCK_SIZE_OFFSET = (unsigned int)&(((RedMemoryBlock*)0)->m_size),
	REDSOUND_MEMORY_BANK_BLOCK_COUNT = 0x400,
	REDSOUND_MEMORY_NEXT_BLOCK_INDEX = 1,
	REDSOUND_MEMORY_BANK_LAST_INDEX = REDSOUND_MEMORY_BANK_BLOCK_COUNT - 1,
	REDSOUND_MEMORY_BANK_ALIGN = 0x20,
	REDSOUND_MEMORY_BANK_ALIGN_MASK = REDSOUND_MEMORY_BANK_ALIGN - 1,
	REDSOUND_MEMORY_BLOCK_SIZE = sizeof(RedMemoryBlock),
	REDSOUND_MEMORY_BLOCK_INDEX_SHIFT = 3,
};

struct RedMemoryBankTable {
	RedMemoryBlock m_mainBank[REDSOUND_MEMORY_BANK_BLOCK_COUNT];
	RedMemoryBlock m_auxBank[REDSOUND_MEMORY_BANK_BLOCK_COUNT];
};

enum RedMemoryLayoutSize {
	REDSOUND_MEMORY_MAIN_BANK_OFFSET = (unsigned int)&(((RedMemoryBankTable*)0)->m_mainBank),
	REDSOUND_MEMORY_BANK_SIZE = sizeof(((RedMemoryBankTable*)0)->m_mainBank),
	REDSOUND_MEMORY_BANK_ALLOC_SIZE = REDSOUND_MEMORY_BANK_SIZE,
	REDSOUND_MEMORY_AUX_BANK_OFFSET = (unsigned int)&(((RedMemoryBankTable*)0)->m_auxBank),
	REDSOUND_MEMORY_BANK_TABLE_COUNT = 2,
	REDSOUND_MEMORY_BANK_TABLE_SIZE = sizeof(RedMemoryBankTable),
	REDSOUND_MEMORY_BANK_TABLE_ALLOC_SIZE = REDSOUND_MEMORY_BANK_TABLE_SIZE,
	REDSOUND_MEMORY_DATA_BUFFER_OFFSET = sizeof(RedMemoryBankTable),
	REDSOUND_MEMORY_ALLOC_FAILED = -1,
};

enum RedMemorySentinel {
	REDSOUND_MEMORY_ADDRESS_NONE = 0,
	REDSOUND_MEMORY_BLOCK_SIZE_EMPTY = 0,
	REDSOUND_MEMORY_BLOCK_COUNT_NONE = 0,
	REDSOUND_MEMORY_MAX_SIZE_ALL = 0,
	REDSOUND_MEMORY_ALLOC_MIN_SIZE = 1,
};

#define RedMemoryBankGetEnd(bank) ((bank) + REDSOUND_MEMORY_BANK_BLOCK_COUNT)
#define RedMemoryBankGetLast(bank) ((bank) + REDSOUND_MEMORY_BANK_LAST_INDEX)
#define RedMemoryBankGetTailCount(bank, block)                                                     \
	(RedMemoryBankGetEnd(bank) - ((block) + REDSOUND_MEMORY_NEXT_BLOCK_INDEX))
#define RedMemoryBlockGetNext(block) ((block) + REDSOUND_MEMORY_NEXT_BLOCK_INDEX)
#define RedMemoryBlockGetEndAddress(block) ((block)->m_address + (block)->m_size)
#define RedMemoryAddress(address) ((int)(address))

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
