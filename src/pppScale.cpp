#include "global.h"
#include "ffcc/pppScale.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

const float kPppScaleZero = 0.0f;

struct PppScaleDataOffsets
{
	s32 m_scaleOffset;
};

STATIC_ASSERT(offsetof(PppScaleDataOffsets, m_scaleOffset) == 0x0);

static inline PppScaleDataOffsets* GetPppScaleDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<PppScaleDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800630cc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleCon(_pppPObject* obj, _pppCtrlTable* ctrlTable)
{
	PppScaleDataOffsets* data = GetPppScaleDataOffsets(ctrlTable);
	float* value = (float*)(obj->m_workArea + data->m_scaleOffset);
	float zero = kPppScaleZero;

	value[2] = zero;
	value[1] = zero;
	value[0] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800630f0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScale(_pppPObject* obj, PppScaleInput* input, _pppCtrlTable* ctrlTable)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	if (input->m_graphId != obj->m_graphId) {
		return;
	}

	PppScaleDataOffsets* data = GetPppScaleDataOffsets(ctrlTable);
	float* scale = (float*)(obj->m_workArea + data->m_scaleOffset);

	scale[0] += input->m_scale[0];
	scale[1] += input->m_scale[1];
	scale[2] += input->m_scale[2];
}
