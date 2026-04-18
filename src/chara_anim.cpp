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
	m_nodeCount = 0;
	m_nodes = 0;
	m_bank = 0;
	m_flags = static_cast<unsigned char>(__rlwimi(m_flags, 1, 7, 24, 24));
	m_flags = static_cast<unsigned char>(__rlwimi(m_flags, 0, 6, 25, 25));
	m_quantizeX = 5;
	m_quantizeY = 0xB;
	m_quantizeZ = 10;
	m_interp = 0;
	m_interpOffset = 0;
	m_bankAddress = 0;
	m_bankSize = 0;
	m_stage = reinterpret_cast<CMemory::CStage*>(0);
	m_lastFrame = 0;
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
	if (m_nodes != 0) {
		__destroy_new_array(m_nodes, (ConstructorDestructor)__dt__Q26CChara9CAnimNodeFv);
		m_nodes = 0;
	}

	if (m_bank != 0) {
		__dla__FPv(m_bank);
		m_bank = 0;
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
	CChunkFile chunkFile(data);
	CChunkFile::CChunk chunk;

	m_stage = stage;

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
				m_nodeCount = static_cast<unsigned short>(chunk.m_arg0);
				unsigned short nodeCount = m_nodeCount;

				void* nodeArray = __nwa__FUlPQ27CMemory6CStagePci(
				    (unsigned long)nodeCount * 0x18 + 0x10, stage, s_charaAnimSourceFile, 0x5F);
				nodeArray = __construct_new_array(
				    nodeArray, reinterpret_cast<ConstructorDestructor>(__ct__Q26CChara9CAnimNodeFv),
				    reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara9CAnimNodeFv), 0x18, nodeCount);
				m_nodes = reinterpret_cast<CChara::CAnimNode*>(nodeArray);

				int nodeOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x494E464F) {
						m_quantizeX = chunkFile.Get4();
						m_quantizeY = chunkFile.Get4();
						m_quantizeZ = chunkFile.Get4();
					} else if ((int)chunk.m_id < 0x494E464F) {
						if (chunk.m_id == 0x4652414D) {
							m_frameCount = static_cast<unsigned short>(static_cast<int>(chunkFile.Get4()));
						} else if (((int)chunk.m_id < 0x4652414D) && (chunk.m_id == 0x42414E4B)) {
							m_bankSize = (chunk.m_size + 0x1F) & 0xFFFFFFE0;
							m_bank = __nwa__FUlPQ27CMemory6CStagePci(chunk.m_size, stage, s_charaAnimSourceFile, 0x7C);
							chunkFile.Get(m_bank, chunk.m_size);

							Memory.CopyToAMemorySync(
								    m_bank, reinterpret_cast<void*>(S32At(Chara, 8308) + S32At((void*)S32At(Chara, 8284), 8)),
									    m_bankSize);

									m_bankAddress = S32At(Chara, 8308);
									S32At(Chara, 8308) = S32At(Chara, 8308) + m_bankSize;
							if (m_bank != 0) {
								__dl__FPv(m_bank);
								m_bank = 0;
							}
						}
					} else if (chunk.m_id == 0x4E4F4445) {
						CAnimNode& node = *reinterpret_cast<CAnimNode*>(Ptr(m_nodes, nodeOffset));
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
						m_interp = static_cast<char>(chunk.m_arg0);
						m_interpOffset = chunkFile.Get4();
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
	unsigned long qx = ((unsigned long)m_quantizeX << 0x18) | 0x70000 | ((unsigned long)m_quantizeX << 8) | 7;
	unsigned long qy = ((unsigned long)m_quantizeY << 0x18) | 0x70000 | ((unsigned long)m_quantizeY << 8) | 7;
	unsigned long qz = ((unsigned long)m_quantizeZ << 0x18) | 0x70000 | ((unsigned long)m_quantizeZ << 8) | 7;

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

	*reinterpret_cast<unsigned char*>(&m_flags) =
	    static_cast<unsigned char>(__rlwimi(*reinterpret_cast<unsigned char*>(&m_flags), zero, 7, 24, 24));
	m_flags = static_cast<unsigned int>(__rlwimi(static_cast<int>(m_flags), zero, 13, 1, 18));
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
	if (anim->m_bank == 0) {
		while (anim->m_bank == 0) {
			anim->m_bank = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, anim->m_bankSize, anim->m_stage, s_charaAnimSourceFile, 0x160, 1);

			if (anim->m_bank != 0) {
				break;
			}
			if (TryReleaseAnimBank__9CCharaPcsFi(&CharaPcs, anim->m_bankSize) == 0) {
				return;
			}
		}

	}

	SetGroup__7CMemoryFPvi(&Memory, anim->m_bank, 1);
	CopyFromAMemorySync__7CMemoryFPvPvUl(
	    &Memory, anim->m_bank,
	    reinterpret_cast<void*>(anim->m_bankAddress + S32At(reinterpret_cast<void*>(S32At(Chara, 8284)), 8)),
	    anim->m_bankSize);

	int frameInt = static_cast<int>(frame);
	anim->m_lastFrame = 0;

	register float frameFrac = frame - static_cast<float>(frameInt);
	if (frameInt == anim->m_frameCount - 1) {
		frameFrac = 0.0f;
	}

	register int flags = static_cast<int>((m_flags >> 0xD) & 0x3FFFF);
	register int frameOffset = frameInt * 2;
	register unsigned short* inData = reinterpret_cast<unsigned short*>(Ptr(anim->m_bank, m_dataOffset));
	register float* outData = reinterpret_cast<float*>(srt);

	for (int i = 0; i < 3; i++) {
		if ((flags & 3) != 0) {
			if ((flags & 3) == 1) {
				i2f_5(outData, inData);
				inData++;
			} else {
				i2f2_5(outData, reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + frameOffset), frameFrac);
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (anim->m_frameCount + 1) * 2);
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
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (anim->m_frameCount + 1) * 2);
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
				inData = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(inData) + (anim->m_frameCount + 1) * 2);
			}
		} else {
			*outData = 1.0f;
		}
		flags >>= 2;
		outData++;
	}
}
