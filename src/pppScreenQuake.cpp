#include "ffcc/pppScreenQuake.h"
#include "ffcc/p_camera.h"

extern float FLOAT_80331fc8;
extern int DAT_8032ed70;

void CalcGraphValue(float param1, pppScreenQuake *param2, int param3, float *param4, float *param5, float *param6, float *param7, float *param8);

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
	float val = FLOAT_80331fc8;
	CameraPcs.SetQuakeParameter((int)val, (int)val, (short)val, (short)val, 
	                            val, val, val, val, val, val, 1);
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
		float *data = (float *)((char *)&quake->field0_0x0 + 128 + *param3->m_serializedDataOffsets);
		
		CalcGraphValue((float)param2->m_dataValIndex, quake, param2->m_graphId, 
		               &data[0], &data[1], &data[2], &param2->m_initWOrk, &param2->m_stepValue);
		               
		CalcGraphValue((float)param2->m_arg3, quake, param2->m_graphId,
		               &data[3], &data[4], &data[5], &param2->m_payload[0], &param2->m_payload[1]);
		               
		CalcGraphValue(param2->m_payload[2], quake, param2->m_graphId,
		               &data[6], &data[7], &data[8], &param2->m_payload[3], &param2->m_payload[4]);
		               
		CameraPcs.SetQuakeParameter((int)data[0], (int)data[3], (short)data[6], (short)param2->m_payload[5],
		                            param2->m_payload[6], param2->m_payload[7], param2->m_payload[8], param2->m_payload[9],
		                            param2->m_payload[10], param2->m_payload[11], 1);
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