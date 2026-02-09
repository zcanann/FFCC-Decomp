#include "ffcc/pppYmLaser.h"
#include "ffcc/math.h"

extern CMath math;
extern "C" float RandF__5CMathFf(float param, CMath* math);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);

struct YmLaserOffsets {
	int m_serializedDataOffsets[3];
};

/*
 * --INFO--
 * PAL Address: 0x800d3780
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserOffsets* offsets = (YmLaserOffsets*)param_2;
	float one = 1.0f;
	float* work = (float*)((unsigned char*)pppYmLaser + 0x88 + offsets->m_serializedDataOffsets[2]);

	*work = one;
	work[1] = one;
	work[2] = one;
	work[3] = one;
	work[4] = one;
	work[5] = one;
	work[6] = one;
	work[7] = 0.0f;
	work[8] = one;
	work[9] = one;
	work[10] = one;

	*((unsigned char*)work + 0x2c) = 0;
	*((unsigned char*)work + 0x2d) = 0;
	*((unsigned char*)work + 0x2e) = 0;
	*((unsigned short*)work + 0x18) = 0;
	*((unsigned short*)work + 0x19) = 0;
	*((unsigned short*)work + 0x1a) = 0;

	work[14] = RandF__5CMathFf(1.0f, &math);
}

/*
 * --INFO--
 * PAL Address: 0x800d373c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstruct2YmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserOffsets* offsets = (YmLaserOffsets*)param_2;
	float one = 1.0f;
	int dataOffset = offsets->m_serializedDataOffsets[2];

	*(float*)((unsigned char*)pppYmLaser + 0x98 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x94 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x90 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x8c + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x88 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x84 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa8 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa4 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa0 + dataOffset) = one;
	*((unsigned char*)pppYmLaser + 0xac + dataOffset) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800d36f0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppDestructYmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserOffsets* offsets = (YmLaserOffsets*)param_2;
	int dataOffset = offsets->m_serializedDataOffsets[2];
	void** stage = (void**)((unsigned char*)pppYmLaser + 0x9c + dataOffset);

	if (*stage != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage(*stage);
		*stage = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d31d4
 * PAL Size: 1308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmLaser(void* pppYmLaser, void* param_2, void* param_3)
{
	// TODO - Complex frame logic with particles and collision detection
}

/*
 * --INFO--
 * PAL Address: 0x800d2614
 * PAL Size: 3008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderYmLaser(void* pppYmLaser, void* param_2, void* param_3)
{
	// TODO - Complex rendering logic with GX calls
}
