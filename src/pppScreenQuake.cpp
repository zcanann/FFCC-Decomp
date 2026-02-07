#include "ffcc/pppScreenQuake.h"
#include "ffcc/p_camera.h"
#include "ffcc/partMng.h"

extern float FLOAT_80331fc8;
extern int DAT_8032ed70;

void CalcGraphValue(float param1, _pppPObject *param2, int param3, float *param4, float *param5, float *param6, float *param7, float *param8);
extern "C" void SetQuakeParameter__10CCameraPcsFiissffffffi(CCameraPcs*, int, int, short, short, float, float, float, float, float, float, int);

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
	float val = FLOAT_80331fc8;
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
	float val = FLOAT_80331fc8;
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
	float value = FLOAT_80331fc8;
	SetQuakeParameter__10CCameraPcsFiissffffffi(&CameraPcs, 0, 0, 0, 0, value, value, value, value, value, value, 1);
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
	if (DAT_8032ed70 == 0) {
		float *value = (float *)((int)(&quake->field0_0x0 + 2) + *param3->m_serializedDataOffsets);
		
		CalcGraphValue((float)param2->m_dataValIndex, (_pppPObject*)&quake->field0_0x0, param2->m_graphId, 
		               value, value + 1, value + 2, &param2->m_initWOrk, &param2->m_stepValue);
		               
		CalcGraphValue((float)param2->m_arg3, (_pppPObject*)&quake->field0_0x0, param2->m_graphId,
		               value + 3, value + 4, value + 5, param2->m_payload, param2->m_payload + 4);
		               
		CalcGraphValue(*(float*)(param2->m_payload + 8), (_pppPObject*)&quake->field0_0x0, param2->m_graphId,
		               value + 6, value + 7, value + 8, param2->m_payload + 0xc, param2->m_payload + 0x10);
		               
		CameraPcs.SetQuakeParameter((int)*value, (int)value[3], (short)value[6], 
		                            (short)*(float*)(param2->m_payload + 0x14),
		                            *(float*)(param2->m_payload + 0x18),
		                            *(float*)(param2->m_payload + 0x1c),
		                            *(float*)(param2->m_payload + 0x20),
		                            *(float*)(param2->m_payload + 0x24),
		                            *(float*)(param2->m_payload + 0x28),
		                            *(float*)(param2->m_payload + 0x2c),
		                            1);
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
