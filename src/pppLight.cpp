#include "ffcc/pppLight.h"
#include "ffcc/p_light.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"

struct pppLightTarget {
	int unk0;
	unsigned char* obj;
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
	s32 sourceId;
	u8 unk4[0x40];
	u32 targetIndex;
	u8 unk48[0x10];
	u8 type;
	u8 color0Enabled;
	u8 color1Enabled;
	u8 color2Enabled;
};

struct PppLightMngProgramInfo {
	u8 unk0[0xD4];
	u32 programInfoTable;
};

extern "C" {
void Add__9CLightPcsFPQ29CLightPcs6CLight(void*, void*);
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
void pppLightCon3(void* param1, void* param2)
{
	// Based on assembly: accesses param2+0xc, then deref twice, then +0x80
	// Stores zeros and a float constant to various offsets
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;
	
	// Clear some integer values
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Set float values to 0.0f
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x44) = zero;
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
void pppLightCon(void* param1, void* param2)
{
	// Similar pattern to pppLightCon3 but clears more values
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;
	
	// Clear integer values
	*(int*)((char*)base + 0x0) = 0;
	*(int*)((char*)base + 0x4) = 0;
	*(int*)((char*)base + 0x8) = 0;
	*(int*)((char*)base + 0xc) = 0;
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Clear float values
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x1c) = zero;
	*(float*)((char*)base + 0x18) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x28) = zero;
	*(float*)((char*)base + 0x24) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x34) = zero;
	*(float*)((char*)base + 0x30) = zero;
	*(float*)((char*)base + 0x44) = zero;
	*(float*)((char*)base + 0x40) = zero;
	*(float*)((char*)base + 0x3c) = zero;
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
void pppLight(void* param1, void* param2, void* param3)
{
	u8* pObject = (u8*)param1;
	PppLightStep* step = (PppLightStep*)param2;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)param3;

	if (gPppCalcDisabled == 0) {
		PppLightWork* work = (PppLightWork*)(pObject + ctrlTable->m_serializedDataOffsets[0] + 0x80);

		if (gPppCalcDisabled != 0) {
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

		if (step->sourceId == *(s32*)(pObject + 0xc)) {
			const s16* stepColor = (const s16*)((u8*)step + 0x8);
			const f32* stepFloat = (const f32*)((u8*)step + 0x20);

			work->color0R += stepColor[0];
			work->color0G += stepColor[1];
			work->color0B += stepColor[2];
			work->color0A += stepColor[3];
			work->color1R += stepColor[4];
			work->color1G += stepColor[5];
			work->color1B += stepColor[6];
			work->color1A += stepColor[7];
			work->color2R += stepColor[8];
			work->color2G += stepColor[9];
			work->color2B += stepColor[10];
			work->color2A += stepColor[11];
			work->attenFalloff += stepFloat[0];
			work->attenFalloffVelocity += stepFloat[1];
			work->attenFalloffAccel += stepFloat[2];
			work->attenRadius += stepFloat[3];
			work->attenRadiusVelocity += stepFloat[4];
			work->attenRadiusAccel += stepFloat[5];
			work->spotScale += stepFloat[6];
			work->spotScaleVelocity += stepFloat[7];
			work->spotScaleAccel += stepFloat[8];
			work->specularScale += *(f32*)((u8*)step + 0x4c);
			work->specularScaleVelocity += *(f32*)((u8*)step + 0x50);
			work->specularScaleAccel += *(f32*)((u8*)step + 0x54);
		}

	create_light:
		CLightPcs::CLight light;

		light.m_position.x = *(f32*)(pObject + 0x1c);
		light.m_position.y = *(f32*)(pObject + 0x2c);
		light.m_position.z = *(f32*)(pObject + 0x3c);
		PSMTXMultVec(pppMngStPtr->m_matrix.value, (Vec*)&light.m_position, (Vec*)&light.m_position);

		light.m_attenRadius = work->attenRadius;
		light.m_attenFalloff = work->attenFalloff;

		light.m_targetColor[0].r = (u8)(work->color0R >> 7);
		light.m_targetColor[0].g = (u8)(work->color0G >> 7);
		light.m_targetColor[0].b = (u8)(work->color0B >> 7);
		light.m_targetColor[0].a = (u8)(work->color0A >> 7);
		light.m_radius = kPppLightOne;
		*(u32*)&light.m_bumpShade[0] = 0;
		light.m_part = pppMngStPtr;

		if (step->color1Enabled != 0) {
			light.m_targetColor[1] = light.m_targetColor[0];
		} else {
			*(u32*)&light.m_targetColor[1] = 0;
		}

		if (step->color2Enabled != 0) {
			light.m_targetColor[2] = light.m_targetColor[0];
		} else {
			*(u32*)&light.m_targetColor[2] = 0;
		}

		if (step->color0Enabled == 0) {
			*(u32*)&light.m_targetColor[0] = 0;
		}

		if (gPppInConstructor == 0 && gPppInSubFrameCalc == 0) {
			if (step->type == 0) {
				light.m_type = 0;
				light.m_direction.x = kPppLightZero;
				light.m_direction.y = kPppLightZero;
				light.m_direction.z = kPppLightOne;
				light.m_spotScale = kPppLightDefaultCosAtten;
				Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, &light);
			} else {
				light.m_type = 1;
				u32 targetIndex = step->targetIndex;
				unsigned char* obj = gPppDefaultValueBuffer;

				if (targetIndex != 0xFFFFFFFF) {
					pppLightTarget* targetTable =
						(pppLightTarget*)((PppLightMngProgramInfo*)pppMngStPtr)->programInfoTable;
					obj = targetTable[targetIndex].obj;
				}

					light.m_targetPosition.x = *(f32*)(obj + 0x1c);
					light.m_targetPosition.y = *(f32*)(obj + 0x2c);
					light.m_targetPosition.z = *(f32*)(obj + 0x3c);
					PSMTXMultVec(pppMngStPtr->m_matrix.value, (Vec*)&light.m_targetPosition, (Vec*)&light.m_targetPosition);

					PSVECSubtract((Vec*)&light.m_targetPosition, (Vec*)&light.m_position, (Vec*)&light.m_direction);
					PSVECNormalize((Vec*)&light.m_direction, (Vec*)&light.m_direction);
					light.m_spotScale = kPppLightSpotScale * work->spotScale;

					if (step->type == 2) {
						light.m_specularScale = work->specularScale;
						light.m_specularMode = 1;
					}

					Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, &light);
				}
		}
	}
}
