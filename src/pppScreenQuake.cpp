#include "ffcc/pppScreenQuake.h"
#include "ffcc/p_camera.h"
#include "ffcc/partMng.h"

extern float lbl_80331FC8;
extern int lbl_8032ED70;

void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, _pppPObject*, int, float*, float*, float*, float*, float*);

/*
 * --INFO--
 * PAL Address: 0x8013e548
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenQuake(pppScreenQuake *quake, UnkC *param2)
{
	float val = lbl_80331FC8;
	float *data = (float *)((char *)&quake->field0_0x0 + 128 + *param2->m_serializedDataOffsets);
	
	data[0] = val;
	data[1] = val;
	data[2] = val;
	data[3] = val;
	data[4] = val;
	data[5] = val;
	data[6] = val;
	data[7] = val;
	data[8] = val;
}

/*
 * --INFO--
 * PAL Address: 0x8013e50c
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenQuake(pppScreenQuake *quake, UnkC *param2)
{
	float val = lbl_80331FC8;
	float *data = (float *)((char *)&quake->field0_0x0 + 128 + *param2->m_serializedDataOffsets);
	
	data[0] = val;
	data[1] = val;
	data[2] = val;
	data[3] = val;
	data[4] = val;
	data[5] = val;
	data[6] = val;
	data[7] = val;
	data[8] = val;
}

/*
 * --INFO--
 * PAL Address: 0x8013e4b8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenQuake(void)
{
	float value = lbl_80331FC8;
	CameraPcs.SetQuakeParameter(0, 0, 0, 0, value, value, value, value, value, value, 1);
}

/*
 * --INFO--
 * PAL Address: 0x8013e3c0
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameScreenQuake(pppScreenQuake *quake, UnkB *param2, UnkC *param3)
{
	if (lbl_8032ED70 == 0) {
		float *value = (float *)((int)(&quake->field0_0x0 + 2) + *param3->m_serializedDataOffsets);
		
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param2->m_dataValIndex, (_pppPObject*)&quake->field0_0x0, param2->m_graphId, 
		               value, value + 1, value + 2, &param2->m_initWOrk, &param2->m_stepValue);
		               
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param2->m_arg3, (_pppPObject*)&quake->field0_0x0, param2->m_graphId,
		               value + 3, value + 4, value + 5, &param2->m_initWOrk2, &param2->m_stepValue2);
		               
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param2->m_arg4, (_pppPObject*)&quake->field0_0x0, param2->m_graphId,
		               value + 6, value + 7, value + 8, &param2->m_initWOrk3, &param2->m_stepValue3);
		               
		CameraPcs.SetQuakeParameter(1, 0, 0, 0, *value, value[3], value[6], param2->m_quakeParam0, param2->m_quakeParam1,
		                            param2->m_quakeParam2, 1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013e3bc
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenQuake(void)
{
}
