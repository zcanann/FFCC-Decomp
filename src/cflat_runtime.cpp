#include "ffcc/cflat_runtime.h"
#include <string.h>

extern "C" {
void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void __dl__FPv(void*);
void __dla__FPv(void*);
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
 * PAL Address: 0x80069a2c
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CFlatRuntime* dtor_80069A2C(CFlatRuntime* flatRuntime, short shouldDelete)
{
	if (flatRuntime != 0) {
		typedef void (*QuitFn)(CFlatRuntime*);

		*(void***)flatRuntime = __vt__12CFlatRuntime;
		reinterpret_cast<QuitFn>((*reinterpret_cast<void***>(flatRuntime))[4])(flatRuntime);
		if (0 < shouldDelete) {
			__dl__FPv(flatRuntime);
		}
	}

	return flatRuntime;
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
 * PAL Address: 0x800697CC
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::Destroy()
{
	typedef void (*OnDeleteFn)(CFlatRuntime*, CFlatRuntime::CObject*);

	u8* const self = reinterpret_cast<u8*>(this);
	CObject* const root = reinterpret_cast<CObject*>(self + 0x8CC);
	CObject* object = *reinterpret_cast<CObject**>(self + 0x8F0);

	while (object != root) {
		CObject* const next = object->m_next;

		object->m_previous->m_next = object->m_next;
		object->m_next->m_previous = object->m_previous;

		*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
		*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

		object->m_freeListNode[1] = *reinterpret_cast<void***>(self + 0x98C);
		*reinterpret_cast<void***>(self + 0x98C) = object->m_freeListNode;

		object->m_flags &= 0xEF;

		OnDeleteFn onDelete = reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7]);
		onDelete(this, object);

		object = next;
	}

	void* ptr = *reinterpret_cast<void**>(self + 0x08);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	u8* funcs = *reinterpret_cast<u8**>(self + 0x20);
	const int funcCount = *reinterpret_cast<int*>(self + 0x1C);
	for (int i = 0, off = 0; i < funcCount; i++, off += 0x50) {
		__dla__FPv(*reinterpret_cast<void**>(funcs + off + 0x34));
		__dla__FPv(*reinterpret_cast<void**>(funcs + off + 0x3C));
	}

	ptr = *reinterpret_cast<void**>(self + 0x20);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x18);
	if (ptr != 0) {
		__dla__FPv(reinterpret_cast<u8*>(ptr) - 0x10);
	}

	ptr = *reinterpret_cast<void**>(self + 0x28);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x2C);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x34);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x38);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x40);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = *reinterpret_cast<void**>(self + 0x44);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	clear();
}

/*
 * --INFO--
 * PAL Address: 0x80069608
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::clear()
{
	u8* const self = reinterpret_cast<u8*>(this);
	const short clearMaskBits = static_cast<short>(-1);

	*reinterpret_cast<void**>(self + 0x08) = 0;
	*reinterpret_cast<void**>(self + 0x20) = 0;
	*reinterpret_cast<void**>(self + 0x1C) = 0;
	*reinterpret_cast<void**>(self + 0x18) = 0;
	*reinterpret_cast<void**>(self + 0x14) = 0;
	*reinterpret_cast<void**>(self + 0x2C) = 0;
	*reinterpret_cast<void**>(self + 0x28) = 0;
	*reinterpret_cast<void**>(self + 0x24) = 0;
	*reinterpret_cast<void**>(self + 0x38) = 0;
	*reinterpret_cast<void**>(self + 0x34) = 0;
	*reinterpret_cast<void**>(self + 0x30) = 0;
	*reinterpret_cast<void**>(self + 0x44) = 0;
	*reinterpret_cast<void**>(self + 0x40) = 0;
	*reinterpret_cast<void**>(self + 0x3C) = 0;

	*reinterpret_cast<short*>(self + 0x964) =
	    static_cast<short>((*reinterpret_cast<short*>(self + 0x964) & 0x000F) | (clearMaskBits << 4));
	*reinterpret_cast<short*>(self + 0x968) =
	    static_cast<short>((*reinterpret_cast<short*>(self + 0x968) & 0x000F) | (clearMaskBits << 4));

	*reinterpret_cast<void**>(self + 0x8EC) = self + 0x8CC;
	*reinterpret_cast<void**>(self + 0x8F0) = self + 0x8CC;
	*reinterpret_cast<short*>(self + 0x8FE) = 0x10;

	*reinterpret_cast<void**>(self + 0x978) = self + 0x978;
	*reinterpret_cast<void**>(self + 0x97C) = self + 0x978;
	*reinterpret_cast<int*>(self + 0x980) = 0x5220;
	*reinterpret_cast<void**>(self + 0x984) = 0;

	*reinterpret_cast<void**>(self + 0x988) = self + 0x1288;
	*reinterpret_cast<void**>(self + 0x98C) = self + 0x998;

	u8* const freeNodes = self + 0x998;
	for (int block = 0; block < 0x30; block++) {
		const int baseIndex = block * 3;
		u8* const node = freeNodes + block * 0x30;

		*reinterpret_cast<void**>(node + 0x00) =
		    (baseIndex == 0) ? static_cast<void*>(self + 0x988)
		                     : static_cast<void*>(freeNodes + (baseIndex - 1) * 0x10);
		*reinterpret_cast<void**>(node + 0x04) =
		    (baseIndex == 0x8F) ? static_cast<void*>(self + 0x988)
		                        : static_cast<void*>(freeNodes + (baseIndex + 1) * 0x10);

		*reinterpret_cast<void**>(node + 0x10) =
		    ((baseIndex + 1) == 0) ? static_cast<void*>(self + 0x988)
		                           : static_cast<void*>(freeNodes + baseIndex * 0x10);
		*reinterpret_cast<void**>(node + 0x14) =
		    ((baseIndex + 1) == 0x8F) ? static_cast<void*>(self + 0x988)
		                              : static_cast<void*>(freeNodes + (baseIndex + 2) * 0x10);

		*reinterpret_cast<void**>(node + 0x20) =
		    ((baseIndex + 2) == 0) ? static_cast<void*>(self + 0x988)
		                           : static_cast<void*>(freeNodes + (baseIndex + 1) * 0x10);
		*reinterpret_cast<void**>(node + 0x24) =
		    ((baseIndex + 2) == 0x8F) ? static_cast<void*>(self + 0x988)
		                              : static_cast<void*>(freeNodes + (baseIndex + 3) * 0x10);
	}

	memset(self + 0x48, 0, 0x804);
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
 * PAL Address: 0x8006879c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::deleteObject(CFlatRuntime::CObject* object)
{
	object->m_previous->m_next = object->m_next;
	object->m_next->m_previous = object->m_previous;

	*(void**)((char*)*object->m_freeListNode + 4) = object->m_freeListNode[1];
	*(void**)object->m_freeListNode[1] = *object->m_freeListNode;

	object->m_freeListNode[1] = *(void***)((char*)this + 0x98C);
	*(void***)((char*)this + 0x98C) = object->m_freeListNode;

	object->m_flags &= 0xEF;

	typedef void (*OnDeleteFn)(CFlatRuntime*);
	reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7])(this);
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
 * PAL Address: 0x80065cf0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::ResetPerformance()
{
	memset((u8*)this + 0x48, 0, 0x804);
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
 * PAL Address: 0x800695fc
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CClass::CClass()
{
	*(u32*)((u8*)this + 0x228) = 2;
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
CFlatRuntime::CObject* CFlatRuntime::getFreeObject(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CClass* CFlatRuntime::intToClass(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CVal* CFlatRuntime::onSystemVal(CFlatRuntime::CObject* object, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(object) + 0x96C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CVal* CFlatRuntime::onClassSystemVal(CFlatRuntime::CObject* object, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(object) + 0x96C);
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
int CFlatRuntime::onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFlatRuntime::onSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	return 0;
}
