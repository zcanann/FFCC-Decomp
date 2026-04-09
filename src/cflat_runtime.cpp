#include "ffcc/cflat_runtime.h"
#include "ffcc/chunkfile.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include <string.h>

extern "C" {
void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void __dl__FPv(void*);
void __dla__FPv(void*);
void __ct__Q212CFlatRuntime6CClassFv(void*);
void* __construct_new_array(void*, void*, void*, unsigned long, unsigned long);
char s_cflat_runtime_cpp_801d8ef8[] = "cflat_runtime.cpp";
char DAT_80330118[];
void* __vt__12CFlatRuntime[];
void* __vt__Q212CFlatRuntime7CObject[];
int __cntlzw(unsigned int);
void Printf__7CSystemFPce(CSystem*, char*, ...);
int sprintf(char*, const char*, ...);
double fmod(double, double);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    CFlatRuntime*, CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);
}
static void appendString(char* dst, const char* src)
{
	while (*dst != '\0') {
		dst++;
	}
	while ((*src) != '\0') {
		*dst++ = *src++;
	}
	*dst = '\0';
}

struct CFlatRuntimeLifecycleProxy
{
    virtual void Init();
    virtual void Destroy();
    virtual void Quit();
};


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
	*reinterpret_cast<void***>(this) = __vt__12CFlatRuntime;
	reinterpret_cast<CFlatRuntimeLifecycleProxy*>(this)->Quit();
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

	m_permanentVarValues = static_cast<u8*>(
	    __nwa__FUlPQ27CMemory6CStagePci(0x3000, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x2A));
	m_initScratchA = __nwa__FUlPQ27CMemory6CStagePci(0x14880, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x2B);
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
	delete[] (char*)m_permanentVarValues;
	delete[] (char*)m_initScratchA;
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
	CObject* const root = &m_objectSentinel;
	CObject* object = m_objectSentinel.m_next;

	while (object != root) {
		CObject* const next = object->m_next;

		object->m_previous->m_next = object->m_next;
		object->m_next->m_previous = object->m_previous;

		*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
		*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

		object->m_freeListNode[1] = *m_objectFreeListHead;
		*m_objectFreeListHead = object->m_freeListNode;

		object->m_flags &= 0xEF;

		OnDeleteFn onDelete = reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7]);
		onDelete(this, object);

		object = next;
	}

	void* ptr = *reinterpret_cast<void**>(self + 0x08);
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	u8* funcs = m_funcs;
	const int funcCount = m_funcCount;
	for (int i = 0, off = 0; i < funcCount; i++, off += 0x50) {
		__dla__FPv(*reinterpret_cast<void**>(funcs + off + 0x34));
		__dla__FPv(*reinterpret_cast<void**>(funcs + off + 0x3C));
	}

	ptr = m_funcs;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_classes;
	if (ptr != 0) {
		__dla__FPv(reinterpret_cast<u8*>(ptr) - 0x10);
	}

	ptr = m_0x28;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_0x2C;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_0x34;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_0x38;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_0x40;
	if (ptr != 0) {
		__dla__FPv(ptr);
	}

	ptr = m_0x44;
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
	m_funcs = 0;
	m_funcCount = 0;
	m_classes = 0;
	m_initScratchB = 0;
	m_0x2C = 0;
	m_0x28 = 0;
	m_0x24 = 0;
	m_0x38 = 0;
	m_0x34 = 0;
	m_0x30 = 0;
	m_0x44 = 0;
	m_0x40 = 0;
	m_0x3C = 0;

	*reinterpret_cast<short*>(self + 0x964) =
	    static_cast<short>((*reinterpret_cast<short*>(self + 0x964) & 0x000F) | (clearMaskBits << 4));
	*reinterpret_cast<short*>(self + 0x968) =
	    static_cast<short>((*reinterpret_cast<short*>(self + 0x968) & 0x000F) | (clearMaskBits << 4));

	*reinterpret_cast<void**>(self + 0x8EC) = self + 0x8CC;
	*reinterpret_cast<void**>(self + 0x8F0) = self + 0x8CC;
	*reinterpret_cast<short*>(self + 0x8FE) = 0x10;

	m_freeListPrev = reinterpret_cast<void**>(self + 0x978);
	m_freeListNext = reinterpret_cast<void**>(self + 0x978);
	m_freeListCount = 0x5220;
	m_0x984 = 0;
	m_objectPoolBase = self + 0x1288;

	*reinterpret_cast<void**>(self + 0x988) = self + 0x1288;
	m_objectFreeListHead = reinterpret_cast<void**>(self + 0x998);

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

	memset(m_performanceBlock, 0, sizeof(m_performanceBlock));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Create(void* filePtr)
{
	typedef void (*ResetFn)(CFlatRuntime*);
	typedef void* (*GetStageFn)(CFlatRuntime*);

	CChunkFile::CChunk chunk;
	CChunkFile chunkFile(filePtr);
	u8* const self = reinterpret_cast<u8*>(this);
	GetStageFn getStage = reinterpret_cast<GetStageFn>((*reinterpret_cast<void***>(this))[0x11]);

	reinterpret_cast<ResetFn>((*reinterpret_cast<void***>(this))[0x10])(this);

	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != 'CFLT') {
			continue;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			if (chunk.m_id == 'NAME') {
				strcpy(reinterpret_cast<char*>(self + 0x00), chunkFile.GetString());
				continue;
			}

			if (chunk.m_id == 'CLAS') {
				const int classCount = chunk.m_arg0;
				*reinterpret_cast<int*>(self + 0x14) = classCount;

				void* classMem =
				    __nwa__FUlPQ27CMemory6CStagePci(classCount * 0x22C + 0x10, getStage(this),
				                                    s_cflat_runtime_cpp_801d8ef8, 0x9E);
				*reinterpret_cast<void**>(self + 0x18) =
				    __construct_new_array(classMem, reinterpret_cast<void*>(__ct__Q212CFlatRuntime6CClassFv),
				                          0, 0x22C, classCount);

				int classIndex = 0;
				int classOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id != 'BLCK') {
						continue;
					}

					int* classBase = reinterpret_cast<int*>(*reinterpret_cast<u8**>(self + 0x18) + classOffset);
					classBase[0] = classIndex;
					chunkFile.PushChunk();
					while (chunkFile.GetNextChunk(chunk)) {
						if (chunk.m_id == 'VAL ') {
							classBase[0x89] = chunk.m_arg0;
						} else if (chunk.m_id == 'NAME') {
							strcpy(reinterpret_cast<char*>(classBase + 1), chunkFile.GetString());
						} else if (chunk.m_id == 'INFO') {
							classBase[0x8A] = chunkFile.Get4();
						} else if (chunk.m_id == 'VTBL') {
							for (int i = 0; i < 0x80; i++) {
								classBase[9 + i] = chunkFile.Get4();
							}
						}
					}
					chunkFile.PopChunk();

					classOffset += 0x22C;
					classIndex++;
				}
				chunkFile.PopChunk();
				continue;
			}

			if (chunk.m_id == 'FUNC') {
				const int funcCount = chunk.m_arg0;
				*reinterpret_cast<int*>(self + 0x1C) = funcCount;
				*reinterpret_cast<void**>(self + 0x20) = __nwa__FUlPQ27CMemory6CStagePci(
				    funcCount * 0x50, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0xD9);

				int funcIndex = 0;
				int funcOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id != 'BLCK') {
						continue;
					}

					int* funcBase = reinterpret_cast<int*>(*reinterpret_cast<u8**>(self + 0x20) + funcOffset);
					funcBase[0] = funcIndex;
					chunkFile.PushChunk();
					while (chunkFile.GetNextChunk(chunk)) {
						if (chunk.m_id == 'NAME') {
							strcpy(reinterpret_cast<char*>(funcBase + 1), chunkFile.GetString());
						} else if (chunk.m_id == 'INFO') {
							funcBase[9] = chunkFile.Get4();
							funcBase[0x10] = chunkFile.Get4();
							funcBase[0x11] = chunkFile.Get4();
							funcBase[0x12] = chunkFile.Get4();
							funcBase[0x13] = chunkFile.Get4();
						} else if (chunk.m_id == 'CODE') {
							funcBase[0xC] = chunk.m_size;
							funcBase[0xF] = 0;
							funcBase[0xE] = 0;
							if (funcBase[0xC] == 0) {
								funcBase[0xD] = 0;
							} else {
								funcBase[0xD] = reinterpret_cast<int>(__nwa__FUlPQ27CMemory6CStagePci(
								    chunk.m_size, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x109));
								memcpy(reinterpret_cast<void*>(funcBase[0xD]), chunkFile.GetAddress(),
								       chunk.m_size);
							}
						} else if (chunk.m_id == 'VAL ') {
							funcBase[10] = chunk.m_arg0;
						} else if (chunk.m_id == 'RET ') {
							*reinterpret_cast<u8*>(funcBase + 0xB) = chunkFile.Get1();
							*reinterpret_cast<u8*>(reinterpret_cast<u8*>(funcBase) + 0x2D) = chunkFile.Get1();
							*reinterpret_cast<u16*>(reinterpret_cast<u8*>(funcBase) + 0x2E) = chunkFile.Get2();
						}
					}
					chunkFile.PopChunk();

					funcOffset += 0x50;
					funcIndex++;
				}
				chunkFile.PopChunk();
				continue;
			}

			if (chunk.m_id == 'VAL ') {
				const int variableCount = chunk.m_arg0;
				*reinterpret_cast<int*>(self + 0x24) = variableCount;
				*reinterpret_cast<void**>(self + 0x28) = __nwa__FUlPQ27CMemory6CStagePci(
				    variableCount << 2, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x96);

				u8* variableDef = *reinterpret_cast<u8**>(self + 0x28);
				for (int i = 0; i < variableCount; i++) {
					variableDef[0] = chunkFile.Get1();
					variableDef[1] = chunkFile.Get1();
					*reinterpret_cast<u16*>(variableDef + 2) = chunkFile.Get2();
					variableDef += 4;
				}
				continue;
			}

			if (chunk.m_id == 'STR ') {
				const int strCount = chunk.m_arg0;
				*reinterpret_cast<int*>(self + 0x30) = strCount;
				*reinterpret_cast<void**>(self + 0x34) = __nwa__FUlPQ27CMemory6CStagePci(
				    strCount << 1, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x121);
				*reinterpret_cast<void**>(self + 0x38) = __nwa__FUlPQ27CMemory6CStagePci(
				    chunk.m_size, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x122);

				memcpy(*reinterpret_cast<void**>(self + 0x38), chunkFile.GetAddress(), chunk.m_size);
				const short base = *reinterpret_cast<short*>(chunkFile.GetAddress());
				int offset = 0;
				for (int i = 0; i < strCount; i++) {
					const short cur = *reinterpret_cast<short*>(chunkFile.GetAddress());
					*reinterpret_cast<short*>(*reinterpret_cast<u8**>(self + 0x34) + offset) = cur - base;
					chunkFile.GetString();
					offset += 2;
				}
				continue;
			}

			if (chunk.m_id == 'FSTR') {
				const int fstrCount = chunk.m_arg0;
				*reinterpret_cast<int*>(self + 0x3C) = fstrCount;
				*reinterpret_cast<void**>(self + 0x40) = __nwa__FUlPQ27CMemory6CStagePci(
				    fstrCount << 1, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x12F);
				*reinterpret_cast<void**>(self + 0x44) = __nwa__FUlPQ27CMemory6CStagePci(
				    chunk.m_size, getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x130);

				memcpy(*reinterpret_cast<void**>(self + 0x44), chunkFile.GetAddress(), chunk.m_size);
				const short base = *reinterpret_cast<short*>(chunkFile.GetAddress());
				int offset = 0;
				for (int i = 0; i < fstrCount; i++) {
					const short cur = *reinterpret_cast<short*>(chunkFile.GetAddress());
					*reinterpret_cast<short*>(*reinterpret_cast<u8**>(self + 0x40) + offset) = cur - base;
					chunkFile.GetString();
					offset += 2;
				}
			}
		}
		chunkFile.PopChunk();
	}

	createObject(-1);
	self[0x1294] = 1;
	*reinterpret_cast<u8*>(self + 0x974) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80068c04
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::CreateDebug(void* filePtr, int debugChunkIndex)
{
	CChunkFile chunkFile(filePtr);
	CChunkFile::CChunk chunk;
	u8* const self = reinterpret_cast<u8*>(this);
	int debugOffset = debugChunkIndex * 0x50;
	int hasChunk = 0;

	while ((hasChunk = chunkFile.GetNextChunk(chunk), hasChunk != 0)) {
		if (chunk.m_id == 'CFLT') {
			chunkFile.PushChunk();
			int funcOffset = debugOffset;

			while ((hasChunk = chunkFile.GetNextChunk(chunk), hasChunk != 0)) {
				if (((chunk.m_id != 'NAME') && (static_cast<int>(chunk.m_id) < static_cast<int>('NAME')))
				    && (chunk.m_id == 'FUNC')) {
					chunkFile.PushChunk();
					int blockOffset = funcOffset;

					while ((hasChunk = chunkFile.GetNextChunk(chunk), hasChunk != 0)) {
						void* funcs = *reinterpret_cast<void**>(self + 0x20);
						if (chunk.m_id == 'BLCK') {
							chunkFile.PushChunk();

							while ((hasChunk = chunkFile.GetNextChunk(chunk), hasChunk != 0)) {
								if (((chunk.m_id != 'NAME')
								     && (static_cast<int>(chunk.m_id) < static_cast<int>('NAME')))
								    && (chunk.m_id == 'CODE')) {
									if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(funcs) + blockOffset + 0x30)
									    == 0) {
										*reinterpret_cast<void**>(reinterpret_cast<u8*>(funcs) + blockOffset + 0x3C)
										    = 0;
										*reinterpret_cast<void**>(reinterpret_cast<u8*>(funcs) + blockOffset + 0x38)
										    = 0;
									} else {
										typedef void* (*GetStageFn)(CFlatRuntime*);
										GetStageFn getStage =
											reinterpret_cast<GetStageFn>((*reinterpret_cast<void***>(this))[0x12]);
										*reinterpret_cast<unsigned int*>(
											reinterpret_cast<u8*>(funcs) + blockOffset + 0x38) = chunk.m_size >> 3;
										*reinterpret_cast<void**>(reinterpret_cast<u8*>(funcs) + blockOffset + 0x3C)
										    = __nwa__FUlPQ27CMemory6CStagePci(
											    *reinterpret_cast<int*>(reinterpret_cast<u8*>(funcs) + blockOffset
											                            + 0x38)
											        << 3,
											    getStage(this), s_cflat_runtime_cpp_801d8ef8, 0x181);
										memcpy(
											*reinterpret_cast<void**>(reinterpret_cast<u8*>(funcs) + blockOffset + 0x3C),
											chunkFile.GetAddress(), chunk.m_size);
									}
								}
							}

							chunkFile.PopChunk();
							blockOffset += 0x50;
							funcOffset += 0x50;
							debugOffset += 0x50;
							debugChunkIndex++;
						}
					}

					chunkFile.PopChunk();
				}
			}

			chunkFile.PopChunk();
		}
	}

	hasChunk = -1;
	if (debugChunkIndex < *reinterpret_cast<int*>(self + 0x1C)) {
		hasChunk = debugChunkIndex;
	}
	return hasChunk;
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
 * PAL Address: 0x80068910
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::Frame(int unused, int mode)
{
	u8* const self = reinterpret_cast<u8*>(this);
	CObject* const root = reinterpret_cast<CObject*>(self + 0x8CC);
	CObject* object = root->m_next;
	int hasParticle = 0;

	while (object != root) {
		CObject* const next = object->m_next;

		if ((static_cast<s8>(object->m_flags) >= 0) && (mode != 0)) {
			object->m_flags &= 0xBF;
			if (objectFrame(object) != 0) {
				int scriptIndex = -1;
				if (object->m_0x34 != 0) {
					do {
						object->m_sp--;

						if (object->m_0x34 != 0) {
							scriptIndex = 31 - __cntlzw(static_cast<unsigned int>(static_cast<u16>(object->m_0x34)));
						} else {
							scriptIndex = -1;
						}

						typedef void (*ReqFinishedFn)(CFlatRuntime*, int, CObject*);
						reinterpret_cast<ReqFinishedFn>((*reinterpret_cast<void***>(this))[0x10])(this, scriptIndex, object);

						if (scriptIndex >= 0) {
							object->m_0x34 = static_cast<s16>(object->m_0x34 & ~(1U << scriptIndex));
							if (object->m_0x34 != 0) {
								scriptIndex = 31 - __cntlzw(static_cast<unsigned int>(static_cast<u16>(object->m_0x34)));
							} else {
								scriptIndex = -1;
							}
						}
					} while (scriptIndex >= 0);
				}

				object->m_flags = static_cast<u8>((object->m_flags & 0x7F) | 0x80);
				if (object->m_particleId == 1) {
					hasParticle = 1;
				}
			}
		}

		if (static_cast<s8>(object->m_flags) < 0) {
			object->m_previous->m_next = object->m_next;
			object->m_next->m_previous = object->m_previous;

			*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
			*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

			object->m_freeListNode[1] = *reinterpret_cast<void***>(self + 0x98C);
			*reinterpret_cast<void***>(self + 0x98C) = object->m_freeListNode;

			object->m_flags &= 0xEF;

			typedef void (*OnDeleteFn)(CFlatRuntime*, CObject*);
			reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7])(this, object);
		}

		object = next;
	}

	return hasParticle;
}

/*
 * --INFO--
 * PAL Address: 0x80068824
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::AfterFrame(int mode)
{
	CObject* object = m_objectSentinel.m_next;

	while (object != &m_objectSentinel) {
		CObject* const next = object->m_next;

		if ((mode != 0) || (static_cast<s8>(object->m_flags) < 0)) {
			object->m_previous->m_next = object->m_next;
			object->m_next->m_previous = object->m_previous;

			*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
			*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

			object->m_freeListNode[1] = *m_objectFreeListHead;
			*m_objectFreeListHead = object->m_freeListNode;

			object->m_flags &= 0xEF;

			typedef void (*OnDeleteFn)(CFlatRuntime*, CObject*);
			reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7])(this, object);
		}

		object = next;
	}
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

	object->m_freeListNode[1] = *m_objectFreeListHead;
	*m_objectFreeListHead = object->m_freeListNode;

	object->m_flags &= 0xEF;

	typedef void (*OnDeleteFn)(CFlatRuntime*, CObject*);
	reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7])(this, object);
}

/*
 * --INFO--
 * PAL Address: 0x800684c8
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CObject* CFlatRuntime::createObject(int classIndex)
{
	u8* const self = reinterpret_cast<u8*>(this);
	u8* classBase = 0;
	if (classIndex != -1) {
		classBase = *reinterpret_cast<u8**>(self + 0x18) + (classIndex * 0x22C);
	}

	int varCount = 0;
	if (classBase != 0) {
		varCount = reinterpret_cast<CClass*>(classBase)->m_variableCount;
	}

	typedef CObject* (*GetFreeObjectFn)(CFlatRuntime*, int);
	CObject* object = reinterpret_cast<GetFreeObjectFn>((*reinterpret_cast<void***>(this))[0xE])(this, varCount);

	object->m_previous = reinterpret_cast<CObject*>(self + 0x8CC)->m_previous;
	object->m_next = reinterpret_cast<CObject*>(self + 0x8CC);
	reinterpret_cast<CObject*>(self + 0x8CC)->m_previous->m_next = object;
	reinterpret_cast<CObject*>(self + 0x8CC)->m_previous = object;

	object->m_flags &= 0x7F;
	object->m_flags &= 0xDF;
	object->m_flags = static_cast<u8>((object->m_flags & 0xEF) | 0x10);
	object->m_0x32 = 0;
	object->m_particleId = 0xF;
	object->m_waitCounter = 0;
	object->m_reqFlag0 = 0;
	object->m_reqFlag1 = 0;
	object->m_reqFlag2 = 0;
	object->m_reqFlag3 = 0;
	object->m_classIndex = static_cast<s16>(classIndex);
	object->m_classIndex = object->m_classIndex;
	object->m_flags = static_cast<u8>((object->m_flags & 0xBF) | 0x40);

	int classLocalCount = 0;
	if (classIndex != -1) {
		classLocalCount = *reinterpret_cast<int*>(classBase + 0x224);
	}

	u8* scanNode = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(self + 0x984) + 4);
	const s32 scanDelta = static_cast<s32>((self + 0x978) - scanNode);
	u32 noScan = static_cast<u32>(__cntlzw(static_cast<u32>(scanDelta))) >> 5 & 0xFF;
	while (noScan == 0) {
		u8* const prev = scanNode;
		scanNode = *reinterpret_cast<u8**>(prev + 4);
		if (*reinterpret_cast<int*>(*reinterpret_cast<u8**>(prev + 4) + 8)
		    >= (classLocalCount + 0x60 + *reinterpret_cast<int*>(prev + 8) + *reinterpret_cast<int*>(prev + 0xC))) {
			scanNode = prev;
			break;
		}
	}

	void** const freeNode = *reinterpret_cast<void***>(self + 0x98C);
	*reinterpret_cast<void***>(self + 0x98C) = reinterpret_cast<void**>(freeNode[1]);
	freeNode[0] = scanNode;
	freeNode[1] = *reinterpret_cast<void**>(scanNode + 4);
	*reinterpret_cast<void***>(freeNode[1]) = freeNode;
	*reinterpret_cast<void**>(scanNode + 4) = freeNode;

	int baseWords = 0;
	if (noScan == 0) {
		baseWords = *reinterpret_cast<int*>(scanNode + 8);
	}
	freeNode[2] = reinterpret_cast<void*>(static_cast<int>(*reinterpret_cast<int*>(scanNode + 0xC) + baseWords));
	freeNode[3] = reinterpret_cast<void*>(classLocalCount + 0x60);

	object->m_freeListNode = freeNode;
	object->m_id = reinterpret_cast<u32>(*reinterpret_cast<u8**>(self + 0x0C) + (reinterpret_cast<s32>(freeNode[2]) * 4));

	unsigned int* varBase = 0;
	if (classIndex == -1) {
		varBase = *reinterpret_cast<unsigned int**>(self + 0x2C);
	} else {
		varBase = reinterpret_cast<unsigned int*>(object->m_id);
	}
	object->m_thisBase = varBase;

	if (classIndex == -1) {
		varBase = reinterpret_cast<unsigned int*>(object->m_id);
	} else {
		varBase = object->m_thisBase + *reinterpret_cast<int*>(classBase + 0x224);
	}
	object->m_sp = varBase;
	object->m_localBase = 0;
	object->m_engineObject = object;
	object->m_codePos = (object->m_codePos & 0x000F) | 0xFFF0;
	object->m_argCount = 0;

	u32 allowKeep = 1;
	if (classIndex == -1) {
		allowKeep = static_cast<u32>(__cntlzw(*reinterpret_cast<u32*>(self + 0x1294))) >> 5 & 0xFF;
	}

	u8* defs = 0;
	int clearCount = 0;
	if (classIndex == -1) {
		defs = *reinterpret_cast<u8**>(self + 0x28);
		clearCount = *reinterpret_cast<int*>(self + 0x24);
	} else {
		clearCount = *reinterpret_cast<int*>(classBase + 0x224);
	}

	unsigned int* write = object->m_thisBase;
	while (clearCount > 0) {
		if ((allowKeep != 0) || ((defs[1] & 0x20) == 0)) {
			*write = 0;
		}
		defs += 4;
		write++;
		clearCount--;
	}

	if (classIndex == -1) {
		request(object, 1, 0, 0, 0);
	}

	typedef void (*OnNewFn)(CFlatRuntime*, CObject*);
	reinterpret_cast<OnNewFn>((*reinterpret_cast<void***>(this))[6])(this, object);

	return object;
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
 * PAL Address: 0x800680b4
 * PAL Size: 1044b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::SystemCall(CFlatRuntime::CObject* objectParam, int systemKind, int systemIndex, int argCount,
                              CFlatRuntime::CStack* args, CFlatRuntime::CStack* outArg)
{
	typedef CObject* (*GetFreeObjectFn)(CFlatRuntime*, int);

	if (objectParam == 0) {
		objectParam = reinterpret_cast<GetFreeObjectFn>((*reinterpret_cast<void***>(this))[0xF])(this, 1);
	}

	CObject* const object = reinterpret_cast<CObject*>(objectParam->m_engineObject);
	if ((static_cast<int>(object->m_flags) << 24) < 0) {
		return;
	}

	u8* func = 0;
	if ((*reinterpret_cast<s16*>(&object->m_classIndex) < 0)
	    || (((systemKind != 2) && (systemKind != 3)) || (systemIndex < 0))) {
		u8* searchFunc = m_funcs;
		int funcCount = m_funcCount;

		for (; funcCount > 0; funcCount--, searchFunc += 0x50) {
			if ((*reinterpret_cast<int*>(searchFunc + 0x40) == systemKind)
			    && (*reinterpret_cast<int*>(searchFunc + 0x44) == systemIndex)) {
				func = searchFunc;
				break;
			}
		}
	} else {
		const s16 classIndex = *reinterpret_cast<s16*>(&object->m_classIndex);
		u8* const classes = reinterpret_cast<u8*>(m_classes);
		const int funcPos = *reinterpret_cast<int*>(classes + (classIndex * 0x22C) + 0x24 + (systemIndex * 4));
		if (funcPos >= 0) {
			func = m_funcs + (funcPos * 0x50);
		}
	}

	if ((func == 0) || (*reinterpret_cast<int*>(func + 0x30) == 0)) {
		return;
	}

	if (argCount > 0) {
		unsigned int* dst = object->m_sp;
		for (int i = 0; i < argCount; i++) {
			dst[i] = args[i].m_word;
		}
		object->m_sp = dst + argCount;
	}

	const unsigned int prevCodePos = object->m_codePos;
	const u8 prevFlags = object->m_flags;
	unsigned int* const prevLocalBase = object->m_localBase;
	const int prevWaitCounter = object->m_waitCounter;
	const int prevReqFlags = *reinterpret_cast<int*>(&object->m_reqFlag0);
	const s16 prevArgCount = object->m_argCount;

	if (*reinterpret_cast<int*>(func + 0x4C) == 0) {
		object->m_localBase = object->m_sp - *reinterpret_cast<int*>(func + 0x24);
		object->m_sp = object->m_localBase + *reinterpret_cast<int*>(func + 0x28);
	} else {
		object->m_sp--;
		object->m_argCount = static_cast<s16>(*object->m_sp);
		object->m_localBase = object->m_sp - object->m_argCount;
		object->m_sp = object->m_localBase + object->m_argCount;
	}

	*reinterpret_cast<u16*>(&object->m_codePos) =
	    static_cast<u16>((static_cast<s16>(*reinterpret_cast<int*>(func + 0x00)) << 4)
	                     | (*reinterpret_cast<u16*>(&object->m_codePos) & 0x000F));
	object->m_codePos &= 0xFFF00000;
	object->m_flags = static_cast<u8>((object->m_flags & 0xDF) | 0x20);
	object->m_waitCounter = 0;
	object->m_reqFlag0 = 0;
	object->m_reqFlag1 = 0;
	object->m_reqFlag2 = 0;
	object->m_reqFlag3 = 0;

	*object->m_sp++ = reinterpret_cast<unsigned int>(prevLocalBase);
	*object->m_sp++ = prevCodePos;
	*object->m_sp++ =
	    static_cast<int>((static_cast<unsigned int>(prevFlags) << 26) | (static_cast<unsigned int>(prevFlags) >> 6)) >> 31;
	*object->m_sp++ = static_cast<unsigned int>(prevArgCount) | (static_cast<unsigned int>(prevWaitCounter) << 16)
	                | (static_cast<unsigned int>(prevReqFlags) << 15);

	int clearCount = *reinterpret_cast<int*>(func + 0x28) - *reinterpret_cast<int*>(func + 0x24);
	for (unsigned int* clear = object->m_localBase + *reinterpret_cast<int*>(func + 0x24); clearCount > 0; clearCount--) {
		*clear++ = 0;
	}

	objectFrame(object);
	object->m_sp--;

	if (outArg != 0) {
		outArg->m_word = *object->m_sp;
	}
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
 * PAL Address: 0x80067c3c
 * PAL Size: 1144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::request(CFlatRuntime::CObject* object, int systemKind, int systemIndex, int argCount,
                          CFlatRuntime::CStack* args)
{
	u8* const self = reinterpret_cast<u8*>(this);
	u8* const targetObject = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(object) + 0x18);
	u8* func = 0;

	if (static_cast<s8>(targetObject[0x38]) < 0) {
		return 1;
	}

	if ((*reinterpret_cast<s16*>(targetObject + 0x16) < 0)
	    || (((systemKind != 2) && (systemKind != 3)) || (systemIndex < 0))) {
		u8* searchFunc = *reinterpret_cast<u8**>(self + 0x20);
		int funcCount = *reinterpret_cast<int*>(self + 0x1C);

		for (int i = 0; i < funcCount; i++, searchFunc += 0x50) {
			if ((*reinterpret_cast<int*>(searchFunc + 0x40) == systemKind)
			    && (*reinterpret_cast<int*>(searchFunc + 0x44) == systemIndex)) {
				func = searchFunc;
				break;
			}
		}
	} else {
		const s16 classIndex = *reinterpret_cast<s16*>(targetObject + 0x16);
		u8* const classes = *reinterpret_cast<u8**>(self + 0x14);
		const int funcIndex = *reinterpret_cast<int*>(classes + (classIndex * 0x22C) + 0x24 + (systemIndex * 4));
		if (funcIndex >= 0) {
			func = *reinterpret_cast<u8**>(self + 0x20) + (funcIndex * 0x50);
		}
	}

	if (func == 0) {
		return 0;
	}

	const int reqFlagIndex = *reinterpret_cast<int*>(func + 0x48);
	if (reqFlagIndex >= 0) {
		const u16 reqFlags = *reinterpret_cast<u16*>(targetObject + 0x34);
		int highestBit = -1;
		for (int bit = 31; bit >= 0; bit--) {
			if ((reqFlags & (1U << bit)) != 0) {
				highestBit = bit;
				break;
			}
		}
		if (reqFlagIndex <= highestBit) {
			return 0;
		}
		*reinterpret_cast<u16*>(targetObject + 0x34) |= static_cast<u16>(1 << reqFlagIndex);
	}

	u32 copiedArgs = 0;
	if (argCount > 0) {
		u32* sp = *reinterpret_cast<u32**>(targetObject + 0x08);
		while (copiedArgs < static_cast<u32>(argCount)) {
			*sp++ = args[copiedArgs].m_word;
			copiedArgs++;
		}
		*reinterpret_cast<u32**>(targetObject + 0x08) = sp;
	}

	const u32 prevCodePos = *reinterpret_cast<u32*>(targetObject + 0x1C);
	const u8 prevFlags = targetObject[0x38];
	const u32 prevLocalBase = *reinterpret_cast<u32*>(targetObject + 0x0C);
	const int prevWaitCounter = *reinterpret_cast<int*>(targetObject + 0x28);
	const int prevReqFlag0 = *reinterpret_cast<int*>(targetObject + 0x2C);
	const s16 prevArgCount = *reinterpret_cast<s16*>(targetObject + 0x36);

	if (*reinterpret_cast<int*>(func + 0x4C) == 0) {
		*reinterpret_cast<u32*>(targetObject + 0x0C) =
		    *reinterpret_cast<u32*>(targetObject + 0x08) - (static_cast<u32>(*reinterpret_cast<int*>(func + 0x24)) * 4);
		*reinterpret_cast<u32*>(targetObject + 0x08) =
		    *reinterpret_cast<u32*>(targetObject + 0x0C) + (static_cast<u32>(*reinterpret_cast<int*>(func + 0x28)) * 4);
	} else {
		*reinterpret_cast<u32*>(targetObject + 0x08) -= 4;
		*reinterpret_cast<s16*>(targetObject + 0x36) = static_cast<s16>(**reinterpret_cast<u32**>(targetObject + 0x08));
		*reinterpret_cast<u32*>(targetObject + 0x0C) =
		    *reinterpret_cast<u32*>(targetObject + 0x08) - (static_cast<u32>(*reinterpret_cast<s16*>(targetObject + 0x36)) * 4);
		*reinterpret_cast<u32*>(targetObject + 0x08) =
		    *reinterpret_cast<u32*>(targetObject + 0x0C) + (static_cast<u32>(*reinterpret_cast<s16*>(targetObject + 0x36)) * 4);
	}

	*reinterpret_cast<u16*>(targetObject + 0x1C) =
	    static_cast<u16>((*reinterpret_cast<u16*>(targetObject + 0x1C) & 0x000F)
	                     | (static_cast<u16>(*reinterpret_cast<s16*>(func + 0x00)) << 4));
	*reinterpret_cast<u32*>(targetObject + 0x1C) &= 0xFFF00000;

	targetObject[0x38] = static_cast<u8>((targetObject[0x38] & 0xDF) | 0x20);
	*reinterpret_cast<int*>(targetObject + 0x28) = 0;
	*reinterpret_cast<int*>(targetObject + 0x2C) = 0;

	**reinterpret_cast<u32**>(targetObject + 0x08) = prevLocalBase;
	*reinterpret_cast<u32*>(targetObject + 0x08) += 4;
	**reinterpret_cast<u32**>(targetObject + 0x08) = prevCodePos;
	*reinterpret_cast<u32*>(targetObject + 0x08) += 4;
	**reinterpret_cast<int**>(targetObject + 0x08) =
	    static_cast<int>((static_cast<u32>(prevFlags) << 26) | (static_cast<u32>(prevFlags) >> 6)) >> 31;
	*reinterpret_cast<u32*>(targetObject + 0x08) += 4;
	**reinterpret_cast<u32**>(targetObject + 0x08) =
	    static_cast<u32>(prevArgCount) | (static_cast<u32>(prevWaitCounter) << 16) | (static_cast<u32>(prevReqFlag0) << 15);
	*reinterpret_cast<u32*>(targetObject + 0x08) += 4;

	int clearCount = *reinterpret_cast<int*>(func + 0x28) - *reinterpret_cast<int*>(func + 0x24);
	if (clearCount > 0) {
		u32* clearPtr =
		    reinterpret_cast<u32*>(*reinterpret_cast<u32*>(targetObject + 0x0C) + (*reinterpret_cast<int*>(func + 0x24) * 4));
		while (clearCount > 0) {
			*clearPtr++ = 0;
			clearCount--;
		}
	}

	return 1;
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
 * PAL Address: 0x80067bf8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::ClearParmanent()
{
	int varIndex = 0;

	while (varIndex < m_permanentVarCount) {
		int valueOffset = varIndex * 4;
		if ((m_permanentVarDefs[valueOffset + 1] & 0x20) != 0) {
			*reinterpret_cast<u32*>(m_permanentVarValues + valueOffset) = 0;
		}
		varIndex += 1;
	}
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
 * PAL Address: 0x80067be0
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::push(CFlatRuntime::CObject* object, int value)
{
	*object->m_sp = static_cast<u32>(value);
	object->m_sp++;
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
 * PAL Address: 0x800679DC
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::GetCodeInfo(char* codeInfo)
{
	union CodeWord {
		u32 u;
		s32 s;
		float f;
	};

	CObject* object = reinterpret_cast<CObject*>(codeInfo);
	register int op;
	CodeWord rhs;
	CodeWord lhs;
	CodeWord result;

#ifdef __MWERKS__
	asm { mr op, r5 };
#else
	op = 0;
#endif

	object->m_sp--;
	rhs.u = *object->m_sp;

	if ((op == 0x20) || (op == 0x23) || (op == 0x25) || (op == 0x2B)) {
		switch (op) {
		case 0x20:
			result.s = -rhs.s;
			break;
		case 0x23:
			result.u = static_cast<u32>((__cntlzw(rhs.u) >> 5) & 0xFF);
			break;
		case 0x25:
			result.u = ~rhs.u;
			break;
		case 0x2B:
			result.f = -rhs.f;
			break;
		}
	} else {
		object->m_sp--;
		lhs.u = *object->m_sp;

		switch (op) {
		case 0x19:
			result.s = lhs.s + rhs.s;
			break;
		case 0x1A:
			result.s = lhs.s - rhs.s;
			break;
		case 0x1B:
			result.s = lhs.s * rhs.s;
			break;
		case 0x1C:
			result.s = lhs.s / rhs.s;
			break;
		case 0x1D:
			result.s = lhs.s - ((lhs.s / rhs.s) * rhs.s);
			break;
		case 0x1E:
			result.u = lhs.u | rhs.u;
			break;
		case 0x1F:
			result.u = lhs.u & rhs.u;
			break;
		case 0x21:
			result.s = lhs.s >> (rhs.u & 0x3F);
			break;
		case 0x22:
			result.s = lhs.s << rhs.s;
			break;
		case 0x24:
			result.u = lhs.u ^ rhs.u;
			break;
		case 0x26:
			result.f = lhs.f + rhs.f;
			break;
		case 0x27:
			result.f = lhs.f - rhs.f;
			break;
		case 0x28:
			result.f = lhs.f * rhs.f;
			break;
		case 0x29:
			result.f = lhs.f / rhs.f;
			break;
		case 0x2A:
			result.f = static_cast<float>(fmod(static_cast<double>(lhs.f), static_cast<double>(rhs.f)));
			break;
		}
	}

	*object->m_sp = result.u;
	object->m_sp++;
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
 * PAL Address: 0x800663fc
 * PAL Size: 5600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::objectFrame(CFlatRuntime::CObject* object)
{
	CStopWatch watch(reinterpret_cast<char*>(-1));
	System.DumpMapFile(&watch);
	watch.Reset();
	watch.Start();

	if (object->m_waitCounter != 0) {
		object->m_waitCounter--;
		watch.Stop();
		return 1;
	}

	u8* const self = reinterpret_cast<u8*>(this);
	u8* funcs = *reinterpret_cast<u8**>(self + 0x20);
	u8* code = *reinterpret_cast<u8**>(
	    funcs + ((static_cast<int>(static_cast<s16>(object->m_codePos >> 16)) >> 4) * 0x50) + 0x34)
	    + (static_cast<int>(object->m_codePos << 12) >> 12);

	typedef unsigned int* (*GetValueFn)(CFlatRuntime*, CFlatRuntime::CObject*, int);
	GetValueFn getSystemVal = reinterpret_cast<GetValueFn>((*reinterpret_cast<void***>(this))[10]);
	GetValueFn getClassSystemVal = reinterpret_cast<GetValueFn>((*reinterpret_cast<void***>(this))[11]);

	while (true) {
		*reinterpret_cast<u16*>(self + 0x968) = *reinterpret_cast<u16*>(self + 0x964);
		*reinterpret_cast<u16*>(self + 0x96A) = *reinterpret_cast<u16*>(self + 0x966);
		*reinterpret_cast<u16*>(self + 0x964) = static_cast<u16>(object->m_codePos);
		*reinterpret_cast<u16*>(self + 0x966) = static_cast<u16>(object->m_codePos >> 16);

		switch (code[0]) {
		case 0: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const int index = static_cast<int>(arg) >> 8;
			unsigned int* value = 0;
			if ((arg & 1) != 0) {
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index) : getClassSystemVal(this, object, index);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + (index * 4));
				} else {
					value = object->m_thisBase + index;
				}
				*object->m_sp++ = *value;
			} else if ((arg & 2) != 0) {
				--object->m_sp;
				const int stackIndex = static_cast<int>(*object->m_sp);
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index + stackIndex)
					                          : getClassSystemVal(this, object, index + stackIndex);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index + stackIndex;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + ((index + stackIndex) * 4));
				} else {
					value = object->m_thisBase + index + stackIndex;
				}
				*object->m_sp++ = *value;
			} else if ((arg & 4) != 0) {
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index) : getClassSystemVal(this, object, index);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + (index * 4));
				} else {
					value = object->m_thisBase + index;
				}
				--object->m_sp;
				*object->m_sp = *reinterpret_cast<unsigned int*>(*value + (*object->m_sp * 4));
				++object->m_sp;
			}
			break;
		}
		case 1: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const int index = static_cast<int>(arg) >> 8;
			unsigned int* value = 0;
			if ((arg & 1) != 0) {
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index) : getClassSystemVal(this, object, index);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + (index * 4));
				} else {
					value = object->m_thisBase + index;
				}
				*object->m_sp++ = reinterpret_cast<u32>(value);
			} else if ((arg & 2) != 0) {
				--object->m_sp;
				const int stackIndex = static_cast<int>(*object->m_sp);
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index + stackIndex)
					                          : getClassSystemVal(this, object, index + stackIndex);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index + stackIndex;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + ((index + stackIndex) * 4));
				} else {
					value = object->m_thisBase + index + stackIndex;
				}
				*object->m_sp++ = reinterpret_cast<u32>(value);
			} else if ((arg & 4) != 0) {
				if (index < 0) {
					value = (arg & 0x10) == 0 ? getSystemVal(this, object, index) : getClassSystemVal(this, object, index);
				} else if ((arg & 8) == 0) {
					value = object->m_localBase + index;
				} else if ((arg & 0x10) == 0) {
					value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x28) + (index * 4));
				} else {
					value = object->m_thisBase + index;
				}
				--object->m_sp;
				*object->m_sp = reinterpret_cast<u32>(value) + (*object->m_sp * 4);
				++object->m_sp;
			}
			break;
		}
		case 2: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const u32 classId = object->m_engineObject == 0 ? 1U : static_cast<u32>(*reinterpret_cast<s16*>(reinterpret_cast<u8*>(object->m_engineObject) + 0x30));
			if ((arg & 1) != 0) {
				*object->m_sp++ = (static_cast<u32>(static_cast<int>(arg) >> 8) << 13) | (classId & 0xFFF) | (-(arg >> 4 & 1) & 0x1000);
			} else if ((arg & 2) != 0) {
				--object->m_sp;
				*object->m_sp = (-(arg >> 4 & 1) & 0x1000) | (classId & 0xFFF) |
				                ((static_cast<int>(arg) >> 8) + *object->m_sp) * 0x2000;
				++object->m_sp;
			}
			break;
		}
		case 3:
		case 4:
		case 5:
			*object->m_sp = *reinterpret_cast<unsigned int*>(code + 1);
			object->m_sp++;
			break;
		case 6: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			if ((static_cast<int>(arg) >> 16) == 0) {
				object->m_sp += 2;
			} else {
				unsigned int* frameBase = object->m_sp + (-3 - static_cast<int>(arg & 0xFFFF));
				frameBase[1] = reinterpret_cast<u32>(object->m_thisBase);
				u32 classIndex = 0xFFFF;
				if (object->m_classIndex >= 0) {
					classIndex = static_cast<u32>(object->m_classIndex);
				}
				frameBase[2] = (static_cast<u32>(*reinterpret_cast<s16*>(reinterpret_cast<u8*>(object->m_engineObject) + 0x30)) << 16)
				               | classIndex;
				u8* classData = reinterpret_cast<u8*>(intToClass(static_cast<int>(*frameBase)));
				object->m_thisBase = reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(classData));
				object->m_classIndex = *reinterpret_cast<s16*>(classData + 0x14);
				object->m_engineObject = classData;
			}
			break;
		}
		case 7: {
			const u32 codePos = object->m_codePos;
			const int current = static_cast<int>(codePos << 12) >> 12;
			const int delta = static_cast<int>(*reinterpret_cast<u32*>(code + 1) & 0x00FFFFFF) - current;
			code += delta;
			object->m_codePos = (codePos & 0xFFF00000) | ((current + delta) & 0x000FFFFF);
			continue;
		}
		case 8: {
			--object->m_sp;
			if (*object->m_sp == 0) {
				const u32 jumpArg = *reinterpret_cast<u32*>(code + 1);
				if ((static_cast<int>(jumpArg) >> 24) != 0) {
					*object->m_sp++ = 0;
				}
				const u32 codePos = object->m_codePos;
				const int current = static_cast<int>(codePos << 12) >> 12;
				const int delta = static_cast<int>(jumpArg & 0x00FFFFFF) - current;
				code += delta;
				object->m_codePos = (codePos & 0xFFF00000) | ((current + delta) & 0x000FFFFF);
				continue;
			}
			break;
		}
		case 9: {
			--object->m_sp;
			if (*object->m_sp != 0) {
				const u32 jumpArg = *reinterpret_cast<u32*>(code + 1);
				if ((static_cast<int>(jumpArg) >> 24) != 0) {
					*object->m_sp++ = 1;
				}
				const u32 codePos = object->m_codePos;
				const int current = static_cast<int>(codePos << 12) >> 12;
				const int delta = static_cast<int>(jumpArg & 0x00FFFFFF) - current;
				code += delta;
				object->m_codePos = (codePos & 0xFFF00000) | ((current + delta) & 0x000FFFFF);
				continue;
			}
			break;
		}
		default:
			break;
		}
		break;
	}

	watch.Stop();
	return 1;
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
 * PAL Address: 0x80065d1c
 * PAL Size: 1760b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::systemFunc(CFlatRuntime::CObject* object, int systemKind, int systemIndex, int& result)
{
	u8* const self = reinterpret_cast<u8*>(this);
	int ret = 1;
	result = 1;

	if (systemKind == 1) {
		if (systemIndex == -1) {
			if (static_cast<int>(*object->m_localBase) <= object->m_waitCounter) {
				*object->m_sp++ = 0;
				result = 0;
			}
		} else if ((systemIndex < -1) && (-3 < systemIndex)) {
			if (*reinterpret_cast<u8*>(self + 0x1298) != 0) {
				const u16* const strOffs = *reinterpret_cast<u16**>(self + 0x34);
				char* const strBlob = *reinterpret_cast<char**>(self + 0x38);
				char* format = strBlob + strOffs[*object->m_localBase];

				if (object->m_argCount == 1) {
					Printf__7CSystemFPce(&System, format);
					Printf__7CSystemFPce(&System, DAT_80330118);
				} else {
					char spec[256];
					char rendered[256];
					char line[264];
					line[0] = '\0';

					for (int i = 0; i < object->m_argCount - 1; i++) {
						while (true) {
							int specLen = 0;
							while ((format[specLen] != '\0') && ((specLen == 0) || (format[specLen] != '%'))) {
								spec[specLen] = format[specLen];
								specLen++;
							}
							spec[specLen] = '\0';
							format += specLen;

							if (spec[0] == '%') {
								break;
							}
							appendString(line, spec);
						}

						const int argIndex = i + 1;
						char* scan = spec + 1;
						if (spec[0] == '%') {
							int fmtIndex = 1;
							int width = 0;
							u32 started = static_cast<u32>(__cntlzw(static_cast<u32>(0x30 - spec[1]))) >> 5 & 0xFF;
							for (; (*scan >= '0') && (*scan <= '9'); scan++) {
								fmtIndex++;
								width = width * 10 + (*scan - '0');
							}

							if (spec[fmtIndex] == 'b') {
								char* out = rendered;
								u32 value = object->m_localBase[argIndex];
								int outLen = 0;

								for (int bit = 0; bit < width; bit++) {
									const u32 cur = (value >> ((width - bit) - 1U)) & 1U;
									if ((started == 0) && (cur != 0)) {
										started = 1;
									}
									if (started != 0) {
										*out++ = static_cast<char>(cur + '0');
										outLen++;
									}
								}
								rendered[outLen] = '\0';
								appendString(rendered, spec + fmtIndex + 1);
							} else {
								while (*scan != '\0') {
									switch (*scan) {
									case 'd':
									case 'x':
										sprintf(rendered, spec, object->m_localBase[argIndex]);
										scan = const_cast<char*>("");
										break;
									case 'f': {
										union {
											u32 u;
											float f;
										} value;
										value.u = object->m_localBase[argIndex];
										sprintf(rendered, spec, static_cast<double>(value.f));
										scan = const_cast<char*>("");
										break;
									}
									case 's':
										sprintf(rendered, spec, strBlob + strOffs[object->m_localBase[argIndex]]);
										scan = const_cast<char*>("");
										break;
									default:
										scan++;
										break;
									}
								}
							}
						}

						appendString(line, rendered);
					}

					Printf__7CSystemFPce(&System, line);
					Printf__7CSystemFPce(&System, DAT_80330118);
				}
			}

			*object->m_sp++ = 0;
			result = 0;
		} else {
			CStopWatch watch(reinterpret_cast<char*>(-1));
			System.DumpMapFile(&watch);
			watch.Reset();
			watch.Start();
			typedef int (*OnClassSystemFuncFn)(CFlatRuntime*, CFlatRuntime::CObject*, int, int, int*);
			ret = reinterpret_cast<OnClassSystemFuncFn>((*reinterpret_cast<void***>(this))[8])(
			    this, object, 1, systemIndex, &result);
			watch.Stop();
			*reinterpret_cast<float*>(self + ((-systemIndex) * 4) + 0x4C) += watch.Get();
			*reinterpret_cast<int*>(self + ((-systemIndex) * 4) + 0x44C) += 1;
		}
	} else if (systemIndex == -2) {
		CObject* const engineObject = reinterpret_cast<CObject*>(object->m_engineObject);
		const u32 scriptGroup = *object->m_localBase;

		engineObject->m_next->m_previous = engineObject->m_previous;
		engineObject->m_previous->m_next = engineObject->m_next;

		CObject* const root = reinterpret_cast<CObject*>(self + 0x8CC);
		CObject* begin = root->m_next;
		CObject* it = begin;
		do {
			if (static_cast<int>(scriptGroup) < it->m_0x32) {
				break;
			}
			it = it->m_next;
		} while (it != begin);

		it = it->m_previous;
		engineObject->m_next = it;
		engineObject->m_previous = it->m_previous;
		it->m_previous->m_next = engineObject;
		it->m_previous = engineObject;
		engineObject->m_0x32 = static_cast<s16>(scriptGroup);

		*object->m_sp++ = 0;
		result = 0;
	} else {
		if (systemIndex < -2) {
			if (systemIndex == -4) {
				SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				    this, object, 2, *object->m_localBase, object->m_argCount - 1,
				    reinterpret_cast<CStack*>(object->m_localBase + 1), 0);
				*object->m_sp++ = 0;
				result = 0;
				return 1;
			}

			if (-5 < systemIndex) {
				u8* const engineObject = reinterpret_cast<u8*>(object->m_engineObject);
				if (engineObject != reinterpret_cast<u8*>(object)) {
					*reinterpret_cast<void**>(*reinterpret_cast<u8**>(engineObject + 0x20) + 0x24) =
					    *reinterpret_cast<void**>(engineObject + 0x24);
					*reinterpret_cast<void**>(*reinterpret_cast<u8**>(engineObject + 0x24) + 0x20) =
					    *reinterpret_cast<void**>(engineObject + 0x20);
					*reinterpret_cast<void**>(*reinterpret_cast<u8**>(*reinterpret_cast<u8**>(engineObject + 0x04) + 0x00) + 0x04) =
					    *reinterpret_cast<void**>(*reinterpret_cast<u8**>(engineObject + 0x04) + 0x04);
					*reinterpret_cast<void**>(*reinterpret_cast<u8**>(*reinterpret_cast<u8**>(engineObject + 0x04) + 0x04) + 0x00) =
					    *reinterpret_cast<void**>(*reinterpret_cast<u8**>(engineObject + 0x04) + 0x00);

					*reinterpret_cast<void**>(*reinterpret_cast<u8**>(engineObject + 0x04) + 0x04) =
					    *reinterpret_cast<void**>(self + 0x98C);
					*reinterpret_cast<void**>(self + 0x98C) = *reinterpret_cast<void**>(engineObject + 0x04);
					*reinterpret_cast<u8*>(engineObject + 0x38) &= 0xEF;

					typedef void (*OnDeleteFn)(CFlatRuntime*, CFlatRuntime::CObject*);
					reinterpret_cast<OnDeleteFn>((*reinterpret_cast<void***>(this))[7])(
					    this, reinterpret_cast<CFlatRuntime::CObject*>(engineObject));
				} else {
					object->m_flags = static_cast<u8>((object->m_flags & 0x7F) | 0x80);
				}

				*object->m_sp++ = 0;
				result = 0;
				return 1;
			}
		} else if (systemIndex < 0) {
			const u32 reqFlags = *reinterpret_cast<u32*>(&object->m_reqFlag0);
			if (reqFlags != 0) {
				*object->m_sp++ = 0;
				result = 0;
				return 1;
			}

			const u32 requestIndex = object->m_localBase[0];
			const u32 noPush = object->m_localBase[1];
			object->m_waitCounter = 1;
			object->m_reqFlag0 = 0;
			object->m_reqFlag1 = 0;
			object->m_reqFlag2 = 0;
			object->m_reqFlag3 = 1;

			if (request(object, 2, requestIndex, object->m_argCount - 2,
			            reinterpret_cast<CStack*>(object->m_localBase + 2)) != 0) {
				if (object == reinterpret_cast<CObject*>(object->m_engineObject)) {
					result = 2;
					return 1;
				}

				*object->m_sp++ = 0;
				result = 0;
				return 1;
			}

			object->m_reqFlag0 = 0;
			object->m_reqFlag1 = 0;
			object->m_reqFlag2 = 0;
			object->m_reqFlag3 = 0;

			if (noPush != 0) {
				return 1;
			}

			*object->m_sp++ = 0;
			result = 0;
			return 1;
		}

		CStopWatch watch(reinterpret_cast<char*>(-1));
		System.DumpMapFile(&watch);
		watch.Reset();
		watch.Start();
		typedef int (*OnSystemFuncFn)(CFlatRuntime*, CFlatRuntime::CObject*, int, int, int*);
		ret = reinterpret_cast<OnSystemFuncFn>((*reinterpret_cast<void***>(this))[9])(
		    this, object, systemKind, systemIndex, &result);
		watch.Stop();
		*reinterpret_cast<float*>(self + ((-systemIndex) * 4) + 0x24C) += watch.Get();
		*reinterpret_cast<int*>(self + ((-systemIndex) * 4) + 0x64C) += 1;
	}

	return ret;
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
	memset(m_performanceBlock, 0, sizeof(m_performanceBlock));
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
	m_variableCount = 2;
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
CFlatRuntime::CVal* CFlatRuntime::onSystemVal(CFlatRuntime::CObject*, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(this) + 0x96C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CVal* CFlatRuntime::onClassSystemVal(CFlatRuntime::CObject*, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(this) + 0x96C);
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
