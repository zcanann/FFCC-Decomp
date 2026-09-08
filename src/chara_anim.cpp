#include "ffcc/chara_anim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"
#include "ffcc/system.h"

#include <string.h>

namespace {
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
	m_flagsBits.m_blendEnabled = 1;
	m_flagsBits.m_clampFrames = 0;
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
		delete[] m_nodes;
		m_nodes = 0;
	}

	if (m_bank != 0) {
		delete[] static_cast<unsigned char*>(m_bank);
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

	while (chunkFile.GetNextChunk(chunk)) {
		int chunkId = static_cast<int>(chunk.m_id);
		if (chunkId != 0x43484120) {
			continue;
		}
		if (chunk.m_version < 2) {
			if ((unsigned int)System.m_execParam >= 2) {
				System.Printf("\214\303\202\242\203\101\203\152\203\201\201\133\203\126\203\207\203\223"
				              "\214\140\216\256\202\305\202\267\201\102\n");
			}
			return;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			chunkId = static_cast<int>(chunk.m_id);
			if (chunkId != 0x414E494D) {
				continue;
			}

			m_nodeCount = static_cast<unsigned short>(chunk.m_arg0);
			unsigned short nodeCount = m_nodeCount;

			m_nodes = new (stage, "chara_anim.cpp", 0x5F) CChara::CAnimNode[nodeCount];

			unsigned int nodeIndex = 0;
			chunkFile.PushChunk();
			while (chunkFile.GetNextChunk(chunk)) {
				chunkId = static_cast<int>(chunk.m_id);
				switch (chunkId) {
				case 0x494E5450:
					m_interp = static_cast<char>(chunk.m_arg0);
					m_interpOffset = chunkFile.Get4();
					break;
				case 0x4652414D:
					{
						float frameCount = chunkFile.Get4();
						m_frameCount = static_cast<unsigned short>(static_cast<int>(frameCount));
					}
					break;
				case 0x494E464F:
					m_quantizeX = static_cast<unsigned char>(chunkFile.Get4());
					m_quantizeY = static_cast<unsigned char>(chunkFile.Get4());
					m_quantizeZ = static_cast<unsigned char>(chunkFile.Get4());
					break;
				case 0x4E4F4445: {
					m_nodes[nodeIndex++].Create(chunkFile);
					break;
				}
				case 0x42414E4B:
					m_bankSize = (chunk.m_size + 0x1F) & 0xFFFFFFE0;
					m_bank = new (stage, "chara_anim.cpp", 0x7C) unsigned char[chunk.m_size];
					chunkFile.Get(m_bank, chunk.m_size);

					Memory.CopyToAMemorySync(
					    m_bank,
					    reinterpret_cast<void*>(Chara.AmemAnimSize() + Chara.GetAmemBaseAddress()),
					    m_bankSize);

					m_bankAddress = Chara.AmemAnimSize();
					Chara.AmemAnimSize() += m_bankSize;
					if (m_bank != 0) {
						delete static_cast<unsigned char*>(m_bank);
						m_bank = 0;
					}
					break;
				}
			}
			chunkFile.PopChunk();
		}
		chunkFile.PopChunk();
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

	Chara.gqrInit(qx, qy, qz);
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
	m_flagsBits.m_hasScale = 0;
	m_flagsBits.m_channelModes = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CAnimNode::Create(CChunkFile& chunkFile)
{
	CChunkFile::CChunk chunk;

	chunkFile.PushChunk();
	while (chunkFile.GetNextChunk(chunk)) {
		int chunkId = static_cast<int>(chunk.m_id);
		switch (chunkId) {
		case 0x4E414D45:
			strcpy(m_name, chunkFile.GetString());
			break;
		case 0x44415441: {
			int type;
			int mode;
			int i = 0;
			int shift = 0;
			do {
				type = chunkFile.Get4();

				if (type == 0) {
					mode = 0;
				} else if (type == 1) {
					mode = 1;
				} else {
					mode = 2;
				}

				unsigned int dataOffset = chunkFile.Get4();
				if (i == 0) {
					m_dataOffset = dataOffset;
				}

				m_flagsBits.m_channelModes |= static_cast<unsigned int>(mode) << shift;

				if ((i >= 6) && (type != 0)) {
					m_flagsBits.m_hasScale = 1;
				}

				i++;
				shift += 2;
			} while (i < 9);
			break;
		}
		}
	}
	chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CAnimNode::mapping(CChara::CAnim*)
{
}

/*
 * --INFO--
 * PAL Address: 0x800BF8B4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnimNode::~CAnimNode()
{
}

/*
 * --INFO--
 * PAL Address: 0x800BF620
 * PAL Size: 660b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CAnimNode::Interp(CChara::CAnim* anim, SRT* srt, float frame)
{
	if (anim->m_bank == 0) {
		while (anim->m_bank == 0) {
			anim->m_bank =
			    Memory._Alloc(anim->m_bankSize, anim->m_stage, "chara_anim.cpp", 0x160, 1);

			if (anim->m_bank != 0) {
				break;
			}
			if (CharaPcs.TryReleaseAnimBank(anim->m_bankSize) == 0) {
				return;
			}
		}

		Memory.SetGroup(anim->m_bank, 1);
		Memory.CopyFromAMemorySync(anim->m_bank,
		                           reinterpret_cast<void*>(anim->m_bankAddress + Chara.GetAmemBaseAddress()),
		                           anim->m_bankSize);
	}

	int frameInt = static_cast<int>(frame);
	anim->m_lastFrame = 0;

	float frameFrac = frame - static_cast<float>(frameInt);
	if (frameInt == anim->m_frameCount - 1) {
		frameFrac = 0.0f;
	}

	register int flags = static_cast<int>(m_flagsBits.m_channelModes);
	register unsigned int dataOffset = m_dataOffset;
	register unsigned short* inData =
	    reinterpret_cast<unsigned short*>(static_cast<unsigned char*>(anim->m_bank) + dataOffset);
	register float* outData = reinterpret_cast<float*>(srt);

	for (int i = 0; i < 3; i++) {
		if ((flags & 3) != 0) {
			if ((flags & 3) == 1) {
				i2f_5(outData, inData);
				inData++;
			} else {
				i2f2_5(outData, inData + frameInt, frameFrac);
				inData += anim->m_frameCount + 1;
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
				i2f2_6(outData, inData + frameInt, frameFrac);
				inData += anim->m_frameCount + 1;
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
				i2f2_7(outData, inData + frameInt, frameFrac);
				inData += anim->m_frameCount + 1;
			}
		} else {
			*outData = 1.0f;
		}
		flags >>= 2;
		outData++;
	}
}
