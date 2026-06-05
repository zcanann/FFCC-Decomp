#include "ffcc/pppScale.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

const float kPppScaleZero = 0.0f;

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
	int* data = ctrlTable->m_serializedDataOffsets;
	float* value = (float*)(obj->m_workArea + data[0]);
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

	int* data = ctrlTable->m_serializedDataOffsets;
	float* scale = (float*)(obj->m_workArea + data[0]);
	
	scale[0] += input->m_scale[0];
	scale[1] += input->m_scale[1];
	scale[2] += input->m_scale[2];
}
