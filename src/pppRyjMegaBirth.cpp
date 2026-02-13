#include "ffcc/pppRyjMegaBirth.h"
#include <string.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

static char s_pppRyjMegaBirth_cpp[] = "pppRyjMegaBirth.cpp";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_rand()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_noise(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VRyjMegaBirth*, PRyjMegaBirth*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void birth(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc(VRyjMegaBirth*, PRyjMegaBirth*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80082894
 * PAL Size: 636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirth(_pppPObject* pObject, PRyjMegaBirth* particleData, PRyjMegaBirthOffsets* offsets)
{
	bool hasRequiredMemory;
	u8* payload = (u8*)particleData;
	s32 colorOffset = offsets->m_serializedDataOffsets[1];
	VRyjMegaBirth* work =
		(VRyjMegaBirth*)((u8*)pObject + 8 + offsets->m_serializedDataOffsets[2]);

	if (work->m_particleBlock == 0)
	{
		work->m_numParticles = *(u16*)(payload + 0xC);

		work->m_particleBlock = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			work->m_numParticles * 0x60, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x262);
		if (work->m_particleBlock != 0)
		{
			memset(work->m_particleBlock, 0, work->m_numParticles * 0x60);
		}

		if ((payload[0xD8] == 1) || (payload[0xD8] == 2))
		{
			work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles * 0x30, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x269);
			if (work->m_worldMatrixBlock != 0)
			{
				memset(work->m_worldMatrixBlock, 0, work->m_numParticles * 0x30);
			}
		}

		if (payload[0xD5] != 0)
		{
			work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles << 5, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x271);
			if (work->m_colorBlock != 0)
			{
				memset(work->m_colorBlock, 0, work->m_numParticles << 5);
			}
		}

		work->m_accelerationAxis.x = *(float*)(payload + 0x9C);
		work->m_accelerationAxis.y = *(float*)(payload + 0xA0);
		work->m_accelerationAxis.z = *(float*)(payload + 0xA4);
		PSVECNormalize(&work->m_accelerationAxis, &work->m_accelerationAxis);
	}

	if (work->m_particleBlock == 0)
	{
		hasRequiredMemory = false;
	}
	else if (((payload[0xD8] == 1) || (payload[0xD8] == 2)) && (work->m_worldMatrixBlock == 0))
	{
		hasRequiredMemory = false;
	}
	else if ((payload[0xD5] == 0) || (work->m_colorBlock != 0))
	{
		hasRequiredMemory = true;
	}
	else
	{
		hasRequiredMemory = false;
	}

	if (hasRequiredMemory)
	{
		switch (payload[0x16])
		{
		default:
			PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_worldMatrix);
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
			PSMTXIdentity(work->m_worldMatrix);
			work->m_worldMatrix[0][0] = pppMngStPtr->m_scale.x;
			work->m_worldMatrix[1][1] = pppMngStPtr->m_scale.y;
			work->m_worldMatrix[2][2] = pppMngStPtr->m_scale.z;
			work->m_worldMatrix[0][3] = pppMngStPtr->m_position.x;
			work->m_worldMatrix[1][3] = pppMngStPtr->m_position.y;
			work->m_worldMatrix[2][3] = pppMngStPtr->m_position.z;
			break;
		}

		calc_particle(
			pObject, work, particleData, (VColor*)((u8*)pObject + 8 + colorOffset));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void set_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*, _PARTICLE_DATA*, _PARTICLE_WMAT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRyjDrawMegaBirth(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800822f4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthCon(void)
{
	// Constructor implementation
}

/*
 * --INFO--
 * PAL Address: 0x80082278
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthDes(void)
{
	// Destructor - cleanup particle memory allocations
}
