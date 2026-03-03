#ifndef _FFCC_CFLAT_RUNTIME_H_
#define _FFCC_CFLAT_RUNTIME_H_

#include "global.h"

class CChunkFile;

class CFlatRuntime
{
public:
	struct CStack
	{
		u32 m_word;

		void operator=(const CStack&);
	};

	class CCodeIndex
	{
		void operator=(const CCodeIndex&);
	};

	class CClass
	{
	public:
		CClass();
        u8 m_unk0[0x228];
        u32 m_variableCount;
	};

	class CObject
	{
	public:
		CObject();
		~CObject();
		void onNewFinished();

		unsigned int m_id;         // 0x0
		void** m_freeListNode;     // 0x4
		unsigned int* m_sp;        // 0x8
		unsigned int* m_localBase; // 0xC
		unsigned int* m_thisBase;  // 0x10
		short m_classIndex;        // 0x14-0x16
		void* m_engineObject;      // 0x18
		unsigned int m_codePos;    // 0x1C
		CObject* m_previous;       // 0x20
		CObject* m_next;           // 0x24
		int m_waitCounter;	       // 0x28
		unsigned char m_reqFlag0;  // 0x2C
		unsigned char m_reqFlag1;  // 0x2D
		unsigned char m_reqFlag2;  // 0x2E
		unsigned char m_reqFlag3;  // 0x2F
		short m_particleId;        // 0x30
		short m_0x32;              // 0x32
		short m_0x34;              // 0x34-0x36
		short m_argCount;          // 0x36-0x38
		unsigned char m_flags;     // 0x38-0x3B
		int m_0x3C;                // 0x3C
		int m_0x40;                // 0x40
		int m_0x44;                // 0x44
	};

	class CFunc
	{
	public:
		CFunc();
		~CFunc();
	};

	class CVal
	{
		CVal();
		~CVal();
	};
	
	CFlatRuntime();
	~CFlatRuntime();

	void Init();
	void Quit();
	void Destroy();
	void clear();

	void Create(void*);
	int CreateDebug(void*, int);
	void createVal(CChunkFile&, int, CFlatRuntime::CVal*);
	int Frame(int, int);
	void AfterFrame(int);

	void deleteObject(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* createObject(int);
	void getTopBit(unsigned int);
	void searchFunc(int, int, int);

	void SystemCall(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);

	int request(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*);
	void callSetup(CFlatRuntime::CObject*, CFlatRuntime::CFunc*, int);
	void callCleanup(CFlatRuntime::CObject*);

	void ClearParmanent();
	void initVal(int, CFlatRuntime::CVal*, CFlatRuntime::CStack*, int);

	void push(CFlatRuntime::CObject*, int);
	void push(CFlatRuntime::CObject*, CFlatRuntime::CStack*, int);
	void pushAddress(CFlatRuntime::CObject*, CFlatRuntime::CStack*);
	void pop(CFlatRuntime::CObject*);

	void PrintCodeInfo();
	void GetCodeInfo(char*);

	void checkWB(void*);
	void calc(CFlatRuntime::CObject*, int);
	void systemVal(CFlatRuntime::CObject*, int, int);
	void setSystemVal(CFlatRuntime::CObject*, int);
	int objectFrame(CFlatRuntime::CObject*);

	void toFunc(CFlatRuntime::CCodeIndex&);
	void toCode(CFlatRuntime::CCodeIndex&);
	int systemFunc(CFlatRuntime::CObject*, int, int, int&);

	void ResetPerformance();
	void PrintPerformance();

	void reqFinished(int, CFlatRuntime::CObject*);
	void onDeleteObject(CFlatRuntime::CObject*);
	void onNewObject(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* getFreeObject(int);
	CFlatRuntime::CClass* intToClass(int);

	CFlatRuntime::CVal* onSystemVal(CFlatRuntime::CObject*, int);
	CFlatRuntime::CVal* onClassSystemVal(CFlatRuntime::CObject*, int);
	void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	void onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int);
	int onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	int onSystemFunc(CFlatRuntime::CObject*, int, int, int&);

private:
    void** m_vtable;                // 0x0000
    int m_permanentVarCount;        // 0x0004
    u8* m_permanentVarDefs;         // 0x0008
    u8* m_permanentVarValues;       // 0x000C
    void* m_initScratchA;           // 0x0010
    void* m_initScratchB;           // 0x0014
    CClass* m_classes;              // 0x0018
    int m_funcCount;                // 0x001C
    u8* m_funcs;                    // 0x0020
    void* m_0x24;                   // 0x0024
    void* m_0x28;                   // 0x0028
    void* m_0x2C;                   // 0x002C
    void* m_0x30;                   // 0x0030
    void* m_0x34;                   // 0x0034
    void* m_0x38;                   // 0x0038
    void* m_0x3C;                   // 0x003C
    void* m_0x40;                   // 0x0040
    void* m_0x44;                   // 0x0044
    u8 m_performanceBlock[0x804];   // 0x0048
    u8 m_pad_084C[0x80];            // 0x084C
    CObject m_objectSentinel;       // 0x08CC
    u8 m_pad_0914[0x64];            // 0x0914
    void** m_freeListPrev;          // 0x0978
    void** m_freeListNext;          // 0x097C
    int m_freeListCount;            // 0x0980
    void* m_0x984;                  // 0x0984
    void* m_objectPoolBase;         // 0x0988
    void** m_objectFreeListHead;    // 0x098C
    u8 m_pad_0990[0x704];           // 0x0990
    u8 m_0x1294;                    // 0x1294
    u8 m_pad_1295[3];               // 0x1295
    u8 m_0x1298;                    // 0x1298
    u8 m_pad_1299[3];               // 0x1299
};

#endif // _FFCC_CFLAT_RUNTIME_H_
