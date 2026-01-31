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
	};

	class CObject
	{
	public:
		CObject();
		~CObject();

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
	void CreateDebug(void*, int);
	void createVal(CChunkFile&, int, CFlatRuntime::CVal*);
	void Frame(int, int);
	void AfterFrame(int);

	void deleteObject(CFlatRuntime::CObject*);
	void createObject(int);
	void getTopBit(unsigned int);
	void searchFunc(int, int, int);

	void SystemCall(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);

	void request(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*);
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
	void objectFrame(CFlatRuntime::CObject*);

	void toFunc(CFlatRuntime::CCodeIndex&);
	void toCode(CFlatRuntime::CCodeIndex&);
	void systemFunc(CFlatRuntime::CObject*, int, int, int&);

	void ResetPerformance();
	void PrintPerformance();

	void reqFinished(int, CFlatRuntime::CObject*);
	void onDeleteObject(CFlatRuntime::CObject*);
	void onNewObject(CFlatRuntime::CObject*);
	void getFreeObject(int);
	void intToClass(int);

	void onSystemVal(CFlatRuntime::CObject*, int);
	void onClassSystemVal(CFlatRuntime::CObject*, int);
	void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	void onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int);
	void onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	void onSystemFunc(CFlatRuntime::CObject*, int, int, int&);
};

#endif // _FFCC_CFLAT_RUNTIME_H_
