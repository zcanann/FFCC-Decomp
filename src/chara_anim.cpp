#include "ffcc/chara_anim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <string.h>

extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __ct__Q26CChara9CAnimNodeFv(void*);
extern "C" void __dt__Q26CChara9CAnimNodeFv(void*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void SetGroup__7CMemoryFPvi(CMemory*, void*, int);
extern "C" void CopyFromAMemorySync__7CMemoryFPvPvUl(CMemory*, void*, void*, unsigned long);
extern "C" int TryReleaseAnimBank__9CCharaPcsFi(void*, int);

extern "C" unsigned char Chara[];
extern unsigned char CharaPcs[];
extern "C" void* PTR_PTR_s_CChara_CAnim_80210534;
extern "C" char s_chara_anim_cpp_801da980[];
extern "C" char DAT_801da990[];

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
	return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline int& S32At(void* p, unsigned int offset)
{
	return *reinterpret_cast<int*>(Ptr(p, offset));
}

static inline unsigned int& U32At(void* p, unsigned int offset)
{
	return *reinterpret_cast<unsigned int*>(Ptr(p, offset));
}

static inline unsigned short& U16At(void* p, unsigned int offset)
{
	return *reinterpret_cast<unsigned short*>(Ptr(p, offset));
}

static inline unsigned char& U8At(void* p, unsigned int offset)
{
	return *reinterpret_cast<unsigned char*>(Ptr(p, offset));
}

static inline unsigned int FourCC(char a, char b, char c, char d)
{
	return (static_cast<unsigned int>(a) << 24) | (static_cast<unsigned int>(b) << 16) |
	       (static_cast<unsigned int>(c) << 8) | static_cast<unsigned int>(d);
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_7(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_7(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_6(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_6(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_5(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_5(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800BFDE0
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnim::CAnim()
{
	unsigned char* const p = (unsigned char*)this;

	__ct__4CRefFv(this);
	*(void**)p = &PTR_PTR_s_CChara_CAnim_80210534;
	*(unsigned short*)(p + 0xE) = 0;
	*(int*)(p + 0x14) = 0;
	*(void**)(p + 0x20) = 0;
	p[8] = (unsigned char)((p[8] & 0x7F) | 0x80);
	p[8] = (unsigned char)(p[8] & 0xBF);
	p[0xA] = 5;
	p[0xB] = 0xB;
	p[0xC] = 10;
	p[0xD] = 0;
	*(void**)(p + 0x18) = 0;
	*(void**)(p + 0x28) = 0;
	*(int*)(p + 0x1C) = 0;
	*(int*)(p + 0x24) = 0;
	*(void**)(p + 0x2C) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800BFD44
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnim::~CAnim()
{
	unsigned char* const p = (unsigned char*)this;
	void* nodeArray;
	void* bank;

	*(void**)p = &PTR_PTR_s_CChara_CAnim_80210534;

	nodeArray = *(void**)(p + 0x14);
	if (nodeArray != 0) {
		__destroy_new_array(nodeArray, (ConstructorDestructor)__dt__Q26CChara9CAnimNodeFv);
		*(void**)(p + 0x14) = 0;
	}

	bank = *(void**)(p + 0x20);
	if (bank != 0) {
		__dla__FPv(bank);
		*(void**)(p + 0x20) = 0;
	}

	__dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800BF984
 * PAL Size: 960b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CAnim::Create(void* data, CMemory::CStage* stage)
{
	unsigned char* p = (unsigned char*)this;
	CChunkFile chunkFile(data);
	CChunkFile::CChunk chunk;

	*(CMemory::CStage**)(p + 0x2C) = stage;

	while (true) {
		do {
			if (!chunkFile.GetNextChunk(chunk)) {
				return;
			}
		} while (chunk.m_id != 0x43484120);

		if (chunk.m_arg0 < 2) {
			break;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			if (chunk.m_id == 0x414E494D) {
				*(unsigned short*)(p + 0xE) = (unsigned short)chunk.m_arg0;
				unsigned short nodeCount = *(unsigned short*)(p + 0xE);

				void* nodeArray = __nwa__FUlPQ27CMemory6CStagePci(
				    (unsigned long)nodeCount * 0x18 + 0x10, stage, s_chara_anim_cpp_801da980, 0x5F);
				nodeArray = __construct_new_array(
				    nodeArray, reinterpret_cast<ConstructorDestructor>(__ct__Q26CChara9CAnimNodeFv),
				    reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara9CAnimNodeFv), 0x18, nodeCount);
				*(void**)(p + 0x14) = nodeArray;

				int nodeOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x494E464F) {
						*(unsigned char*)(p + 0xA) = chunkFile.Get4();
						*(unsigned char*)(p + 0xB) = chunkFile.Get4();
						*(unsigned char*)(p + 0xC) = chunkFile.Get4();
					} else if ((int)chunk.m_id < 0x494E464F) {
						if (chunk.m_id == 0x4652414D) {
							*(short*)(p + 0x10) = (short)(int)chunkFile.Get4();
						} else if (((int)chunk.m_id < 0x4652414D) && (chunk.m_id == 0x42414E4B)) {
							*(unsigned int*)(p + 0x1C) = (chunk.m_size + 0x1F) & 0xFFFFFFE0;
							*(void**)(p + 0x20) =
						    __nwa__FUlPQ27CMemory6CStagePci(chunk.m_size, stage, s_chara_anim_cpp_801da980, 0x7C);
							chunkFile.Get(*(void**)(p + 0x20), chunk.m_size);

							Memory.CopyToAMemorySync(
							    *(void**)(p + 0x20), (void*)(S32At(Chara, 8308) + S32At((void*)S32At(Chara, 8284), 8)),
							    *(unsigned int*)(p + 0x1C));

							*(int*)(p + 0x28) = S32At(Chara, 8308);
							S32At(Chara, 8308) = S32At(Chara, 8308) + *(int*)(p + 0x1C);

							if (*(void**)(p + 0x20) != 0) {
								__dl__FPv(*(void**)(p + 0x20));
								*(void**)(p + 0x20) = 0;
							}
						}
					} else if (chunk.m_id == 0x4E4F4445) {
						unsigned char* node = (unsigned char*)*(void**)(p + 0x14) + nodeOffset;
						CChunkFile::CChunk nodeChunk;
						nodeOffset += 0x18;

						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(nodeChunk)) {
							if (nodeChunk.m_id == 0x4E414D45) {
								strcpy((char*)node, chunkFile.GetString());
							} else if (((int)nodeChunk.m_id < 0x4E414D45) && (nodeChunk.m_id == 0x44415441)) {
								int i = 0;
								int shift = 0;
								do {
									int type = (int)chunkFile.Get4();
									int mode;

									if (type == 0) {
										mode = 0;
									} else if (type == 1) {
										mode = 1;
									} else {
										mode = 2;
									}

									unsigned int dataOffset = chunkFile.Get4();
									if (i == 0) {
										*(unsigned int*)(node + 0x10) = dataOffset;
									}

									*(unsigned int*)(node + 0x14) = ((*(unsigned int*)(node + 0x14) >> 0xD & 0x3FFFF) |
									                                 ((mode << shift) & 0x3FFFFU))
									                                << 0xD |
									                                (*(unsigned int*)(node + 0x14) & 0x80001FFF);

									if ((5 < i) && (type != 0)) {
										*(unsigned char*)(node + 0x14) = *(unsigned char*)(node + 0x14) & 0x7F | 0x80;
									}

									i++;
									shift += 2;
								} while (i < 9);
							}
						}
						chunkFile.PopChunk();
					} else if (((int)chunk.m_id < 0x4E4F4445) && (chunk.m_id == 0x494E5450)) {
						*(char*)(p + 9) = (char)chunk.m_arg0;
						*(unsigned int*)(p + 0x18) = chunkFile.Get4();
					}
				}
				chunkFile.PopChunk();
			}
		}
		chunkFile.PopChunk();
	}

	if ((unsigned int)System.m_execParam >= 2) {
		System.Printf(DAT_801da990);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800BF910
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CAnim::InitQuantize()
{
	unsigned char* const p = (unsigned char*)this;
	unsigned long qx = ((unsigned long)p[0xA] << 0x18) | 0x70000 | ((unsigned long)p[0xA] << 8) | 7;
	unsigned long qy = ((unsigned long)p[0xB] << 0x18) | 0x70000 | ((unsigned long)p[0xB] << 8) | 7;
	unsigned long qz = ((unsigned long)p[0xC] << 0x18) | 0x70000 | ((unsigned long)p[0xC] << 8) | 7;

	gqrInit__6CCharaFUlUlUl(Chara, qx, qy, qz);
}

/*
 * --INFO--
 * PAL Address: 0x800BF8F0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnimNode::CAnimNode()
{
	unsigned char* const p = (unsigned char*)this;
	p[0x14] = (unsigned char)(p[0x14] & 0x7F);
	*(unsigned int*)(p + 0x14) &= 0x80001FFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CAnimNode::~CAnimNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnimNode::Create(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnimNode::Interp(CChara::CAnim* anim, SRT* srt, float frame)
{
	if (S32At(anim, 0x20) == 0) {
		while (true) {
			if (S32At(anim, 0x20) != 0) {
				void* bank = *reinterpret_cast<void**>(Ptr(anim, 0x20));
				SetGroup__7CMemoryFPvi(&Memory, bank, 1);
				CopyFromAMemorySync__7CMemoryFPvPvUl(
				    &Memory, bank, reinterpret_cast<void*>(S32At(anim, 0x28) + S32At(reinterpret_cast<void*>(S32At(Chara, 8284)), 8)),
				    U32At(anim, 0x1C));
				break;
			}

			*reinterpret_cast<void**>(Ptr(anim, 0x20)) = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, U32At(anim, 0x1C), *reinterpret_cast<CMemory::CStage**>(Ptr(anim, 0x2C)), s_chara_anim_cpp_801da980, 0x160, 1);

			if (S32At(anim, 0x20) != 0) {
				continue;
			}
			if (TryReleaseAnimBank__9CCharaPcsFi(CharaPcs, S32At(anim, 0x1C)) == 0) {
				return;
			}
		}
	}

	S32At(anim, 0x24) = 0;

	const unsigned int frameInt = static_cast<unsigned int>(frame);
	float frameFrac = frame - static_cast<float>(frameInt);
	if (frameInt == static_cast<unsigned int>(U16At(anim, 0x10) - 1)) {
		frameFrac = 0.0f;
	}

	unsigned int animFlags = (U32At(this, 0x14) >> 0xD) & 0x3FFFF;
	const int frameByteOffset = static_cast<int>(frameInt * 2);
	float* animData = reinterpret_cast<float*>(S32At(this, 0x10) + S32At(anim, 0x20));
	float* outData = reinterpret_cast<float*>(srt);

	float baseValue = 0.0f;
	for (int i = 0; i < 3; i++) {
		if ((animFlags & 3) == 0) {
			*outData = baseValue;
		} else if ((animFlags & 3) == 1) {
			*outData = *animData;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + 2);
		} else {
			const float v1 = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset);
			*outData = (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset + 2) - v1) * frameFrac + v1;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + (U16At(anim, 0x10) + 1) * 2);
		}

		baseValue = 0.0f;
		animFlags = static_cast<unsigned int>(static_cast<int>(animFlags) >> 2);
		outData++;
	}

	float scaleDefault = 0.0f;
	for (int i = 0; i < 3; i++) {
		if ((animFlags & 3) == 0) {
			*outData = baseValue;
		} else if ((animFlags & 3) == 1) {
			*outData = *animData;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + 2);
		} else {
			const float v1 = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset);
			*outData = (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset + 2) - v1) * frameFrac + v1;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + (U16At(anim, 0x10) + 1) * 2);
		}

		scaleDefault = 1.0f;
		animFlags = static_cast<unsigned int>(static_cast<int>(animFlags) >> 2);
		outData++;
	}

	for (int i = 0; i < 3; i++) {
		if ((animFlags & 3) == 0) {
			*outData = scaleDefault;
		} else if ((animFlags & 3) == 1) {
			*outData = *animData;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + 2);
		} else {
			const float v1 = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset);
			*outData = (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + frameByteOffset + 2) - v1) * frameFrac + v1;
			animData = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(animData) + (U16At(anim, 0x10) + 1) * 2);
		}

		animFlags = static_cast<unsigned int>(static_cast<int>(animFlags) >> 2);
		outData++;
	}
}
