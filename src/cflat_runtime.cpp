#include "ffcc/cflat_runtime.h"

extern "C" {
void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
char s_cflat_runtime_cpp_801d8ef8[];
void* __vt__12CFlatRuntime[];
void* __vt__Q212CFlatRuntime7CObject[];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CFlatRuntime()
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);

	*reinterpret_cast<void***>(self) = __vt__12CFlatRuntime;
	*reinterpret_cast<void***>(self + 0x1204) = __vt__Q212CFlatRuntime7CObject;
	self[0x123C] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x124C) = __vt__Q212CFlatRuntime7CObject;
	self[0x1284] &= 0xEF;
	self[0x1294] = 0;
	self[0x1298] = 1;

	clear();
}

/*
 * --INFO--
 * PAL Address: 0x80069a2c
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::~CFlatRuntime()
{
	Quit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Init()
{
	typedef void* (*GetStageFn)(CFlatRuntime*);
	GetStageFn getStage = reinterpret_cast<GetStageFn>((*reinterpret_cast<void***>(this))[0x11]);

	*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0xC) =
		__nwa__FUlPQ27CMemory6CStagePci(0x3000, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x2A);
	*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x10) =
		__nwa__FUlPQ27CMemory6CStagePci(0x14880, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x2B);
}

/*
 * --INFO--
 * PAL Address: 0x8006996c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::Quit()
{
	delete[] (char*)*(void**)((char*)this + 0xC);
	delete[] (char*)*(void**)((char*)this + 0x10);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::clear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Create(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::CreateDebug(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::createVal(CChunkFile&, int, CFlatRuntime::CVal*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Frame(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::AfterFrame(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::deleteObject(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::createObject(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::getTopBit(unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::searchFunc(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::SystemCall(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::CStack::operator= (const CFlatRuntime::CStack&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::request(CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::callSetup(CFlatRuntime::CObject*, CFlatRuntime::CFunc*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::callCleanup(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::CCodeIndex::operator= (const CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::ClearParmanent()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::initVal(int, CFlatRuntime::CVal*, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::push(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::push(CFlatRuntime::CObject*, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::pushAddress(CFlatRuntime::CObject*, CFlatRuntime::CStack*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::pop(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::PrintCodeInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::GetCodeInfo(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::checkWB(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::calc(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::systemVal(CFlatRuntime::CObject*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::setSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::objectFrame(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::toFunc(CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::toCode(CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::systemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::ResetPerformance()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::PrintPerformance()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CClass::CClass()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::reqFinished(int, CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onDeleteObject(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onNewObject(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::getFreeObject(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::intToClass(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onClassSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSetSystemVal(int, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	// TODO
}
