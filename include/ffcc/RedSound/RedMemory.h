#ifndef _FFCC_REDSOUND_REDMEMORY_H
#define _FFCC_REDSOUND_REDMEMORY_H

void RedNew(int);
void RedDelete(int);
void RedDelete(void*);
void RedNewA(int, int, int);
void RedDeleteA(int);
void RedDeleteA(void*);

class CRedMemory
{
public:
	CRedMemory();
	~CRedMemory();

	void Init(int, int, int, int);
	void GetMainBufferAddress();
	void GetMainBufferSize();
	void GetMainBankAddress();
	void GetABufferAddress();
	void GetABufferSize();
	void GetABankAddress();
};

#endif // _FFCC_REDSOUND_REDMEMORY_H
