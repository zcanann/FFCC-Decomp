#include "ffcc/chara_anim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <string.h>

extern "C" void __ct__Q26CChara9CAnimNodeFv(void*);
extern "C" void __dt__Q26CChara9CAnimNodeFv(void*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" char s_charaAnimSourceFile[];
extern "C" char s_charaAnimAllocWarn[];
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void SetGroup__7CMemoryFPvi(CMemory*, void*, int);
extern "C" void CopyFromAMemorySync__7CMemoryFPvPvUl(CMemory*, void*, void*, unsigned long);
extern "C" int TryReleaseAnimBank__9CCharaPcsFi(void*, int);
class CCharaPcs;
extern unsigned char Chara[];
extern CCharaPcs CharaPcs;

namespace {
struct CAnimFields {
	void* m_vtable;
	int m_refCount;
	unsigned char m_flags;
	char m_interp;
	unsigned char m_quantizeX;
	unsigned char m_quantizeY;
	unsigned char m_quantizeZ;
	unsigned char _padD;
	unsigned short m_nodeCount;
	unsigned short m_frameCount;
	CChara::CAnimNode* m_nodes;
	unsigned int m_interpOffset;
	unsigned int m_bankSize;
	void* m_bank;
	int m_lastFrame;
	int m_bankAddress;
	CMemory::CStage* m_stage;
};

struct CAnimNodeFields {
	char m_name[16];
	unsigned int m_dataOffset;
	unsigned int m_flags;
};

static inline CAnimFields& Anim(CChara::CAnim* anim)
{
	return *reinterpret_cast<CAnimFields*>(anim);
}

static inline CAnimNodeFields& AnimNode(CChara::CAnimNode* node)
{
	return *reinterpret_cast<CAnimNodeFields*>(node);
}

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

static inline void i2f_5(float* out, register const unsigned short* in)
{
	register float value;

	asm {
		psq_l value, 0(in), 1, 5
	}

	*out = value;
}

static inline void i2f2_5(float* out, register const unsigned short* in, float t)
{
	register float a;
	register float b;

	asm {
		psq_l a, 0(in), 1, 5
		psq_l b, 2(in), 1, 5
	}

	*out = (b - a) * t + a;
}

static inline void i2f_6(float* out, register const unsigned short* in)
{
	register float value;

	asm {
		psq_l value, 0(in), 1, 6
	}

	*out = value;
}

static inline void i2f2_6(float* out, register const unsigned short* in, float t)
{
	register float a;
	register float b;

	asm {
		psq_l a, 0(in), 1, 6
		psq_l b, 2(in), 1, 6
	}

	*out = (b - a) * t + a;
}

static inline void i2f_7(float* out, register const unsigned short* in)
{
	register float value;

	asm {
		psq_l value, 0(in), 1, 7
	}

	*out = value;
}

static inline void i2f2_7(float* out, register const unsigned short* in, float t)
{
	register float a;
	register float b;

	asm {
		psq_l a, 0(in), 1, 7
		psq_l b, 2(in), 1, 7
	}

	*out = (b - a) * t + a;
}
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
	CAnimFields& anim = Anim(this);

	anim.m_nodeCount = 0;
	anim.m_nodes = 0;
	anim.m_bank = 0;
	anim.m_flags = static_cast<unsigned char>(__rlwimi(anim.m_flags, 1, 7, 24, 24));
	anim.m_flags = static_cast<unsigned char>(__rlwimi(anim.m_flags, 0, 6, 25, 25));
	anim.m_quantizeX = 5;
	anim.m_quantizeY = 0xB;
	anim.m_quantizeZ = 10;
	anim.m_interp = 0;
	anim.m_interpOffset = 0;
	anim.m_bankAddress = 0;
	anim.m_bankSize = 0;
	anim.m_stage = reinterpret_cast<CMemory::CStage*>(0);
	anim.m_lastFrame = 0;
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
	CAnimFields& anim = Anim(this);

	if (anim.m_nodes != 0) {
		__destroy_new_array(anim.m_nodes, (ConstructorDestructor)__dt__Q26CChara9CAnimNodeFv);
		anim.m_nodes = 0;
	}

	if (anim.m_bank != 0) {
		__dla__FPv(anim.m_bank);
		anim.m_bank = 0;
	}
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
	CAnimFields& anim = Anim(this);
	CChunkFile chunkFile(data);
	CChunkFile::CChunk chunk;

	anim.m_stage = stage;

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
				anim.m_nodeCount = static_cast<unsigned short>(chunk.m_arg0);
				unsigned short nodeCount = anim.m_nodeCount;

				void* nodeArray = __nwa__FUlPQ27CMemory6CStagePci(
				    (unsigned long)nodeCount * 0x18 + 0x10, stage, s_charaAnimSourceFile, 0x5F);
				nodeArray = __construct_new_array(
				    nodeArray, reinterpret_cast<ConstructorDestructor>(__ct__Q26CChara9CAnimNodeFv),
				    reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara9CAnimNodeFv), 0x18, nodeCount);
				anim.m_nodes = reinterpret_cast<CChara::CAnimNode*>(nodeArray);

				int nodeOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x494E464F) {
						anim.m_quantizeX = chunkFile.Get4();
						anim.m_quantizeY = chunkFile.Get4();
						anim.m_quantizeZ = chunkFile.Get4();
					} else if ((int)chunk.m_id < 0x494E464F) {
						if (chunk.m_id == 0x4652414D) {
							anim.m_frameCount = static_cast<unsigned short>(static_cast<int>(chunkFile.Get4()));
						} else if (((int)chunk.m_id < 0x4652414D) && (chunk.m_id == 0x42414E4B)) {
							anim.m_bankSize = (chunk.m_size + 0x1F) & 0xFFFFFFE0;
							anim.m_bank = __nwa__FUlPQ27CMemory6CStagePci(chunk.m_size, stage, s_charaAnimSourceFile, 0x7C);
							chunkFile.Get(anim.m_bank, chunk.m_size);

							Memory.CopyToAMemorySync(
								    anim.m_bank, reinterpret_cast<void*>(S32At(Chara, 8308) + S32At((void*)S32At(Chara, 8284), 8)),
									    anim.m_bankSize);

									anim.m_bankAddress = S32At(Chara, 8308);
									S32At(Chara, 8308) = S32At(Chara, 8308) + anim.m_bankSize;
							if (anim.m_bank != 0) {
								__dl__FPv(anim.m_bank);
								anim.m_bank = 0;
							}
						}
					} else if (chunk.m_id == 0x4E4F4445) {
						CAnimNodeFields& node = *reinterpret_cast<CAnimNodeFields*>(Ptr(anim.m_nodes, nodeOffset));
						CChunkFile::CChunk nodeChunk;
						nodeOffset += 0x18;

						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(nodeChunk)) {
							if (nodeChunk.m_id == 0x4E414D45) {
								strcpy(node.m_name, chunkFile.GetString());
							} else if ((int)nodeChunk.m_id < 0x4E414D45) {
								if (nodeChunk.m_id == 0x44415441) {
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
											node.m_dataOffset = dataOffset;
										}

										unsigned int nodeFlags = node.m_flags;
										node.m_flags =
										    (((nodeFlags >> 0xD) & 0x3FFFF) | ((mode << shift) & 0x3FFFFU)) << 0xD |
										    (nodeFlags & 0x80001FFF);

										if ((5 < i) && (type != 0)) {
											unsigned char flags = *reinterpret_cast<unsigned char*>(&node.m_flags);
											*reinterpret_cast<unsigned char*>(&node.m_flags) =
											    static_cast<unsigned char>(__rlwimi(flags, 1, 7, 24, 24));
										}

										i++;
										shift += 2;
									} while (i < 9);
								}
							}
						}
						chunkFile.PopChunk();
					} else if (((int)chunk.m_id < 0x4E4F4445) && (chunk.m_id == 0x494E5450)) {
						anim.m_interp = static_cast<char>(chunk.m_arg0);
						anim.m_interpOffset = chunkFile.Get4();
					}
				}
				chunkFile.PopChunk();
			}
		}
		chunkFile.PopChunk();
	}

	if ((unsigned int)System.m_execParam >= 2) {
		System.Printf(s_charaAnimAllocWarn);
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
	CAnimFields& anim = Anim(this);
	unsigned long qx = ((unsigned long)anim.m_quantizeX << 0x18) | 0x70000 | ((unsigned long)anim.m_quantizeX << 8) | 7;
	unsigned long qy = ((unsigned long)anim.m_quantizeY << 0x18) | 0x70000 | ((unsigned long)anim.m_quantizeY << 8) | 7;
	unsigned long qz = ((unsigned long)anim.m_quantizeZ << 0x18) | 0x70000 | ((unsigned long)anim.m_quantizeZ << 8) | 7;

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
	int zero = 0;
	CAnimNodeFields& node = AnimNode(this);

	*reinterpret_cast<unsigned char*>(&node.m_flags) =
	    static_cast<unsigned char>(__rlwimi(*reinterpret_cast<unsigned char*>(&node.m_flags), zero, 7, 24, 24));
	node.m_flags = static_cast<unsigned int>(__rlwimi(static_cast<int>(node.m_flags), zero, 13, 1, 18));
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
	CAnimFields& animFields = Anim(anim);
	CAnimNodeFields& node = AnimNode(this);

	if (animFields.m_bank == 0) {
		while (animFields.m_bank == 0) {
			animFields.m_bank = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, animFields.m_bankSize, animFields.m_stage, s_charaAnimSourceFile, 0x160, 1);

			if (animFields.m_bank != 0) {
				break;
			}
			if (TryReleaseAnimBank__9CCharaPcsFi(&CharaPcs, animFields.m_bankSize) == 0) {
				return;
			}
		}

	}

	SetGroup__7CMemoryFPvi(&Memory, animFields.m_bank, 1);
	CopyFromAMemorySync__7CMemoryFPvPvUl(
	    &Memory, animFields.m_bank,
	    reinterpret_cast<void*>(animFields.m_bankAddress + S32At(reinterpret_cast<void*>(S32At(Chara, 8284)), 8)),
	    animFields.m_bankSize);

	int frameInt = static_cast<int>(frame);
	animFields.m_lastFrame = 0;

	register float frameFrac = frame - static_cast<float>(frameInt);
	if (frameInt == animFields.m_frameCount - 1) {
		frameFrac = 0.0f;
	}

	register int flags = static_cast<int>((node.m_flags >> 0xD) & 0x3FFFF);
	register int frameOffset = frameInt * 2;
	register unsigned short* inData = reinterpret_cast<unsigned short*>(Ptr(animFields.m_bank, node.m_dataOffset));
	register float* outData = reinterpret_cast<float*>(srt);

	for (int i = 0; i < 3; i++) {
		if ((flags & 3) != 0) {
			if ((flags & 3) == 1) {
				i2f_5(outData, inData);
				inData++;
			} else {
				i2f2_5(outData, reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + frameOffset), frameFrac);
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (animFields.m_frameCount + 1) * 2);
			}
		} else {
			*outData = 0.0f;
		}
		flags >>= 2;
		outData++;
	}

	for (int i = 0; i < 3; i++) {
		if ((flags & 3) != 0) {
			if ((flags & 3) == 1) {
				i2f_6(outData, inData);
				inData++;
			} else {
				i2f2_6(outData, reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + frameOffset), frameFrac);
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (animFields.m_frameCount + 1) * 2);
			}
		} else {
			*outData = 0.0f;
		}
		flags >>= 2;
		outData++;
	}

	for (int i = 0; i < 3; i++) {
		if ((flags & 3) != 0) {
			if ((flags & 3) == 1) {
				i2f_7(outData, inData);
				inData++;
			} else {
				i2f2_7(outData, reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + frameOffset), frameFrac);
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (animFields.m_frameCount + 1) * 2);
			}
		} else {
			*outData = 1.0f;
		}
		flags >>= 2;
		outData++;
	}
}
