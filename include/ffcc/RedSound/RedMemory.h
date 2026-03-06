#ifndef _FFCC_REDSOUND_REDMEMORY_H
#define _FFCC_REDSOUND_REDMEMORY_H

extern int gRedMemoryDebugEnabled;
extern int gRedMainMemoryBase;
extern int gRedAMemoryBase;
extern int gRedMainMemorySize;
extern int gRedAMemorySize;
extern int* gRedMainMemoryBlockList;
extern int* gRedAMemoryBlockList;

extern char s_redMemoryLogPrefix_801E78A3;
extern char s_redMemoryLogSuffixA_80333D20;
extern char s_redMemoryLogSuffixB_80333D28;
extern char s__s_sMemory_Bank_Full____s_801e7888[];
extern char s__s_sA_Memory_Bank_Full____s_801e78b5[];

int RedNew(int);
void RedDelete(int);
void RedDelete(void*);
int RedNewA(int, int, int);
void RedDeleteA(int);
void RedDeleteA(void*);

class CRedMemory
{
public:
	CRedMemory();
	~CRedMemory();

	void Init(int, int, int, int);
	int GetMainBufferAddress();
	int GetMainBufferSize();
	int* GetMainBankAddress();
	int GetABufferAddress();
	int GetABufferSize();
	int* GetABankAddress();
};

#endif // _FFCC_REDSOUND_REDMEMORY_H
