#include "ffcc/pppLight.h"
#include "ffcc/p_light.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/linkage.h"
extern "C" {
extern u8 gPppDefaultValueBuffer[];
}
#include "dolphin/mtx.h"
#include <stddef.h>

struct pppLightTarget {
	int unk0;
	_pppPObject* obj;
	int unk8;
	int unkC;
};

struct PppLightWork {
	s16 color0R;
	s16 color0G;
	s16 color0B;
	s16 color0A;
	s16 color1R;
	s16 color1G;
	s16 color1B;
	s16 color1A;
	s16 color2R;
	s16 color2G;
	s16 color2B;
	s16 color2A;
	f32 attenFalloff;
	f32 attenFalloffVelocity;
	f32 attenFalloffAccel;
	f32 attenRadius;
	f32 attenRadiusVelocity;
	f32 attenRadiusAccel;
	f32 spotScale;
	f32 spotScaleVelocity;
	f32 spotScaleAccel;
	f32 specularScale;
	f32 specularScaleVelocity;
	f32 specularScaleAccel;
};

struct PppLightStep {
	s32 m_sourceId;
	u8 m_pad04[0x4];
	s16 m_colorDeltas[12];
	f32 m_attenFalloff;
	f32 m_attenFalloffVelocity;
	f32 m_attenFalloffAccel;
	f32 m_attenRadius;
	f32 m_attenRadiusVelocity;
	f32 m_attenRadiusAccel;
	f32 m_spotScale;
	f32 m_spotScaleVelocity;
	f32 m_spotScaleAccel;
	u32 m_targetIndex;
	u8 m_pad48[0x4];
	f32 m_specularScale;
	f32 m_specularScaleVelocity;
	f32 m_specularScaleAccel;
	u8 m_type;
	u8 m_color0Enabled;
	u8 m_color1Enabled;
	u8 m_color2Enabled;
};

struct PppLightMngProgramInfo {
	u8 unk0[0xD4];
	pppLightTarget* programInfoTable;
};

STATIC_ASSERT(offsetof(PppLightWork, attenFalloffAccel) == 0x20);
STATIC_ASSERT(offsetof(PppLightWork, attenRadiusAccel) == 0x2C);
STATIC_ASSERT(offsetof(PppLightWork, spotScaleAccel) == 0x38);
STATIC_ASSERT(offsetof(PppLightWork, specularScaleAccel) == 0x44);
STATIC_ASSERT(offsetof(PppLightStep, m_colorDeltas) == 0x8);
STATIC_ASSERT(offsetof(PppLightStep, m_attenFalloff) == 0x20);
STATIC_ASSERT(offsetof(PppLightStep, m_targetIndex) == 0x44);
STATIC_ASSERT(offsetof(PppLightStep, m_specularScale) == 0x4C);
STATIC_ASSERT(offsetof(PppLightStep, m_type) == 0x58);

static inline PppLightWork* GetPppLightWork(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<PppLightWork*>(object->m_workArea + ctrlTable->m_serializedDataOffsets[0]);
}

/*
 * --INFO--
 * PAL Address: 0x800dab00
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon3(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	PppLightWork* work = GetPppLightWork(object, ctrlTable);
	float zero = 0.0f;
	
	*(int*)&work->color2R = 0;
	*(int*)&work->color2B = 0;
	
	work->attenFalloffAccel = zero;
	work->attenRadiusAccel = zero;
	work->spotScaleAccel = zero;
	work->specularScaleAccel = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab34
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	PppLightWork* work = GetPppLightWork(object, ctrlTable);
	float zero = 0.0f;
	
	*(int*)&work->color0R = 0;
	*(int*)&work->color0B = 0;
	*(int*)&work->color1R = 0;
	*(int*)&work->color1B = 0;
	*(int*)&work->color2R = 0;
	*(int*)&work->color2B = 0;
	
	work->attenFalloffAccel = zero;
	work->attenFalloffVelocity = zero;
	work->attenFalloff = zero;
	work->attenRadiusAccel = zero;
	work->attenRadiusVelocity = zero;
	work->attenRadius = zero;
	work->spotScaleAccel = zero;
	work->spotScaleVelocity = zero;
	work->spotScale = zero;
	work->specularScaleAccel = zero;
	work->specularScaleVelocity = zero;
	work->specularScale = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab98
 * PAL Size: 1276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLight(_pppPObject* object, void* stepData, void* ctrlData)
{
	PppLightStep* step = (PppLightStep*)stepData;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)ctrlData;

	if (ppvUserStopPartF == 0) {
		PppLightWork* work = (PppLightWork*)(object->m_workArea + ctrlTable->m_serializedDataOffsets[0]);

		if (ppvUserStopPartF != 0) {
			goto create_light;
		}

		work->attenFalloffVelocity += work->attenFalloffAccel;
		work->attenFalloff += work->attenFalloffVelocity;
		work->attenRadiusVelocity += work->attenRadiusAccel;
		work->attenRadius += work->attenRadiusVelocity;
		work->spotScaleVelocity += work->spotScaleAccel;
		work->spotScale += work->spotScaleVelocity;
		work->specularScaleVelocity += work->specularScaleAccel;
		work->specularScale += work->specularScaleVelocity;

		work->color1R += work->color2R;
		work->color1G += work->color2G;
		work->color1B += work->color2B;
		work->color1A += work->color2A;

		work->color0R += work->color1R;
		work->color0G += work->color1G;
		work->color0B += work->color1B;
		work->color0A += work->color1A;

		if (step->m_sourceId == object->m_graphId) {
			work->color0R += step->m_colorDeltas[0];
			work->color0G += step->m_colorDeltas[1];
			work->color0B += step->m_colorDeltas[2];
			work->color0A += step->m_colorDeltas[3];
			work->color1R += step->m_colorDeltas[4];
			work->color1G += step->m_colorDeltas[5];
			work->color1B += step->m_colorDeltas[6];
			work->color1A += step->m_colorDeltas[7];
			work->color2R += step->m_colorDeltas[8];
			work->color2G += step->m_colorDeltas[9];
			work->color2B += step->m_colorDeltas[10];
			work->color2A += step->m_colorDeltas[11];
			work->attenFalloff += step->m_attenFalloff;
			work->attenFalloffVelocity += step->m_attenFalloffVelocity;
			work->attenFalloffAccel += step->m_attenFalloffAccel;
			work->attenRadius += step->m_attenRadius;
			work->attenRadiusVelocity += step->m_attenRadiusVelocity;
			work->attenRadiusAccel += step->m_attenRadiusAccel;
			work->spotScale += step->m_spotScale;
			work->spotScaleVelocity += step->m_spotScaleVelocity;
			work->spotScaleAccel += step->m_spotScaleAccel;
			work->specularScale += step->m_specularScale;
			work->specularScaleVelocity += step->m_specularScaleVelocity;
			work->specularScaleAccel += step->m_specularScaleAccel;
		}

	create_light:
		CLightPcs::CLight light;

		light.m_position.x = object->m_localMatrix.value[0][3];
		light.m_position.y = object->m_localMatrix.value[1][3];
		light.m_position.z = object->m_localMatrix.value[2][3];
		PSMTXMultVec(ppvMng->m_matrix.value, (Vec*)&light.m_position, (Vec*)&light.m_position);

		light.m_attenRadius = work->attenRadius;
		light.m_attenFalloff = work->attenFalloff;

		light.m_targetColor[0].r = (u8)(work->color0R >> 7);
		light.m_targetColor[0].g = (u8)(work->color0G >> 7);
		light.m_targetColor[0].b = (u8)(work->color0B >> 7);
		light.m_targetColor[0].a = (u8)(work->color0A >> 7);
		light.m_radius = 1.0f;
		*(u32*)&light.m_bumpShade[0] = 0;
		light.m_part = ppvMng;

		if (step->m_color1Enabled != 0) {
			light.m_targetColor[1] = light.m_targetColor[0];
		} else {
			*(u32*)&light.m_targetColor[1] = 0;
		}

		if (step->m_color2Enabled != 0) {
			light.m_targetColor[2] = light.m_targetColor[0];
		} else {
			*(u32*)&light.m_targetColor[2] = 0;
		}

		if (step->m_color0Enabled == 0) {
			*(u32*)&light.m_targetColor[0] = 0;
		}

		if (gPppInConstructor == 0 && gPppInSubFrameCalc == 0) {
			if (step->m_type == 0) {
				light.m_type = 0;
				light.m_direction.x = 0.0f;
				light.m_direction.y = 0.0f;
				light.m_direction.z = 1.0f;
				light.m_spotScale = 0.7853982f;
				LightPcs.Add(&light);
			} else {
				_pppPObject* obj;

				light.m_type = 1;
				obj = (step->m_targetIndex == 0xFFFFFFFF)
						  ? reinterpret_cast<_pppPObject*>(&gPppDefaultValueBuffer[0])
						  : ((PppLightMngProgramInfo*)ppvMng)->programInfoTable[step->m_targetIndex].obj;

					light.m_targetPosition.x = obj->m_localMatrix.value[0][3];
					light.m_targetPosition.y = obj->m_localMatrix.value[1][3];
					light.m_targetPosition.z = obj->m_localMatrix.value[2][3];
					PSMTXMultVec(ppvMng->m_matrix.value, (Vec*)&light.m_targetPosition, (Vec*)&light.m_targetPosition);

					PSVECSubtract((Vec*)&light.m_targetPosition, (Vec*)&light.m_position, (Vec*)&light.m_direction);
					PSVECNormalize((Vec*)&light.m_direction, (Vec*)&light.m_direction);
					light.m_spotScale = 0.017453292f * work->spotScale;

					if (step->m_type == 2) {
						light.m_specularScale = work->specularScale;
						light.m_specularMode = 1;
					}

					LightPcs.Add(&light);
				}
		}
	}
}
