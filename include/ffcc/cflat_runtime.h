#ifndef _FFCC_CFLAT_RUNTIME_H_
#define _FFCC_CFLAT_RUNTIME_H_

#include "global.h"
#include "ffcc/memory.h"

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
		s32 m_index;              // 0x000
		char m_name[0x20];        // 0x004
		s32 m_functionTable[0x80]; // 0x024
		s32 m_localCount;         // 0x224
		s32 m_variableCount;      // 0x228
	};

	class CObject
	{
	public:
		void onNewFinished();

		unsigned int m_id;         // 0x0
		void** m_freeListNode;     // 0x4
		unsigned int* m_sp;        // 0x8
		unsigned int* m_localBase; // 0xC
		unsigned int* m_thisBase;  // 0x10
		short m_classIndex;        // 0x14
		short m_activeClassIndex;  // 0x16
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
		union {
			unsigned char m_flags;     // 0x38-0x3B
			struct {
				unsigned char m_flagBits0 : 3;
				unsigned char m_constructFlag : 1;
				unsigned char m_flagBits1 : 4;
			} m_flagBits;
		};
		int m_0x3C;                // 0x3C
		int m_0x40;                // 0x40
		int m_0x44;                // 0x44
	};

	class CFunc
	{
	public:
		CFunc();
		~CFunc();

		s32 m_index;         // 0x00
		char m_name[0x20];   // 0x04
		s32 m_argCount;      // 0x24
		s32 m_localCount;    // 0x28
		u8 m_returnType;     // 0x2C
		u8 m_returnFlags;    // 0x2D
		u16 m_returnValue;   // 0x2E
		s32 m_codeSize;      // 0x30
		u8* m_code;          // 0x34
		s32 m_codeOffset;    // 0x38
		s32 m_codePos;       // 0x3C
		s32 m_systemKind;    // 0x40
		s32 m_systemIndex;   // 0x44
		s32 m_reqFlagIndex;  // 0x48
		s32 m_useCallerArgs; // 0x4C
	};

	class CVal
	{
		CVal();
		~CVal();
	};
	
	CFlatRuntime();
	~CFlatRuntime();

	virtual void Init();
	virtual void Quit();
	virtual void Destroy();
	virtual int Frame(int, int);
	virtual void onNewObject(CFlatRuntime::CObject*);
	virtual void onDeleteObject(CFlatRuntime::CObject*);
	virtual int onSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	virtual int onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	virtual CFlatRuntime::CVal* onSystemVal(CFlatRuntime::CObject*, int);
	virtual CFlatRuntime::CVal* onClassSystemVal(CFlatRuntime::CObject*, int);
	virtual void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	virtual void onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int);
	virtual CFlatRuntime::CObject* getFreeObject(int);
	virtual void* intToClass(int);
	virtual void reqFinished(int, CFlatRuntime::CObject*);
	virtual CMemory::CStage* getStage() = 0;
	virtual CMemory::CStage* getDebugStage() = 0;

	void clear();

	void Create(void*);
	int CreateDebug(void*, int);
	void createVal(CChunkFile&, int, CFlatRuntime::CVal*);
	void AfterFrame(int);

	void deleteObject(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* createObject(int);
	int getTopBit(unsigned int);
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

private:
	struct CObjectSentinel : public CObject
	{
		CObjectSentinel()
		{
			m_flagBits.m_constructFlag = 0;
		}
	};

    int m_permanentVarCount;        // 0x0004
    u8* m_permanentVarDefs;         // 0x0008
    u8* m_permanentVarValues;       // 0x000C
    void* m_initScratchA;           // 0x0010
    void* m_initScratchB;           // 0x0014
    CClass* m_classes;              // 0x0018
    int m_funcCount;                // 0x001C
    u8* m_funcs;                    // 0x0020
    int m_strCount;                 // 0x0024
    char* m_strBlob;                // 0x0028
    u16* m_strOffsets;              // 0x002C
    int m_fstrCount;                // 0x0030
    char* m_fstrBlob;               // 0x0034
    u16* m_fstrOffsets;             // 0x0038
    int m_vstrCount;                // 0x003C
    char* m_vstrBlob;               // 0x0040
    u16* m_vstrOffsets;             // 0x0044
    u8 m_performanceBlock[0x804];   // 0x0048
    u8 m_pad_084C[0x80];            // 0x084C
    CObjectSentinel m_objectSentinel;       // 0x08CC
    CObjectSentinel m_freeObjectSentinel;   // 0x0918
    u8 m_pad_0964[0xC];             // 0x0964
    int m_0x970;                    // 0x0970
    u8 m_pad_0974[4];               // 0x0974
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

STATIC_ASSERT(sizeof(CFlatRuntime::CClass) == 0x22C);
STATIC_ASSERT(offsetof(CFlatRuntime::CClass, m_functionTable) == 0x24);
STATIC_ASSERT(offsetof(CFlatRuntime::CClass, m_localCount) == 0x224);
STATIC_ASSERT(offsetof(CFlatRuntime::CClass, m_variableCount) == 0x228);
STATIC_ASSERT(sizeof(CFlatRuntime::CFunc) == 0x50);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_argCount) == 0x24);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_localCount) == 0x28);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_code) == 0x34);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_systemKind) == 0x40);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_reqFlagIndex) == 0x48);
STATIC_ASSERT(offsetof(CFlatRuntime::CFunc, m_useCallerArgs) == 0x4C);
STATIC_ASSERT(sizeof(CFlatRuntime::CObject) == 0x48);

#endif // _FFCC_CFLAT_RUNTIME_H_
