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

class CRedMemory
{
public:
	CRedMemory();
	~CRedMemory();

	void Init(int, int, int, int);
	int GetMainBufferAddress();
	int GetMainBufferSize();
	RedMemoryBlock* GetMainBankAddress();
	int GetABufferAddress();
	int GetABufferSize();
	RedMemoryBlock* GetABankAddress();
};

#endif // _FFCC_REDSOUND_REDMEMORY_H
