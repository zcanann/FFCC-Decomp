#ifndef _FFCC_CFLAT_RUNTIME_H_
#define _FFCC_CFLAT_RUNTIME_H_

class CChunkFile;

class CFlatRuntime
{
	class CStack
	{
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

		char placeholder[72];
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
