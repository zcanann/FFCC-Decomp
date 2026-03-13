#include "ffcc/pppLight.h"
#include "ffcc/p_light.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"

extern unsigned char gPppInSubFrameCalc;

struct PppLightTarget {
    int unk0;
    unsigned char* obj;
    int unk8;
    int unkC;
};

struct PppLightObject {
    u8 unk0[0xC];
    s32 lightId;
    u8 unk10[0xC];
    f32 x;
    u8 unk20[0xC];
    f32 y;
    u8 unk30[0xC];
    f32 z;
};

struct PppLightWork {
    s16 color[4];
    s16 colorStep[4];
    s16 colorStep2[4];
    f32 attenFalloff;
    f32 attenFalloffStep;
    f32 attenFalloffStep2;
    f32 attenRadius;
    f32 attenRadiusStep;
    f32 attenRadiusStep2;
    f32 spotScale;
    f32 spotScaleStep;
    f32 spotScaleStep2;
    f32 specularScale;
    f32 specularScaleStep;
    f32 specularScaleStep2;
};

struct PppLightParam {
    s32 lightId;
    u8 unk4[0x4];
    s16 color[4];
    s16 colorStep[4];
    s16 colorStep2[4];
    f32 attenFalloff;
    f32 attenFalloffStep;
    f32 attenFalloffStep2;
    f32 attenRadius;
    f32 attenRadiusStep;
    f32 attenRadiusStep2;
    f32 spotScale;
    f32 spotScaleStep;
    f32 spotScaleStep2;
    s32 targetIndex;
    u8 unk48[0x4];
    f32 specularScale;
    f32 specularScaleStep;
    f32 specularScaleStep2;
    u8 lightType;
    u8 enableColor0;
    u8 enableColor1;
    u8 enableColor2;
};

struct PppLightLocal {
    u8 unk0[8];
    CLightPcs::CLight light;
};

extern "C" {
void __ct__Q29CLightPcs6CLightFv(void*);
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
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;

	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;

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
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;

	*(int*)((char*)base + 0x0) = 0;
	*(int*)((char*)base + 0x4) = 0;
	*(int*)((char*)base + 0x8) = 0;
	*(int*)((char*)base + 0xc) = 0;
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;

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
    _pppCtrlTable* ctrl = (_pppCtrlTable*)param3;
    PppLightObject* object = (PppLightObject*)param1;
    PppLightParam* lightParam = (PppLightParam*)param2;
    PppLightWork* work = (PppLightWork*)((u8*)param1 + *ctrl->m_serializedDataOffsets + 0x80);

    if (gPppCalcDisabled != 0) {
        return;
    }

    {
        PppLightLocal lightData;
        CLightPcs::CLight* light = &lightData.light;
        Vec* sourcePos = (Vec*)&light->m_position;

        work->attenFalloffStep += work->attenFalloffStep2;
        work->attenFalloff += work->attenFalloffStep;
        work->attenRadiusStep += work->attenRadiusStep2;
        work->attenRadius += work->attenRadiusStep;
        work->spotScaleStep += work->spotScaleStep2;
        work->spotScale += work->spotScaleStep;
        work->specularScaleStep += work->specularScaleStep2;
        work->specularScale += work->specularScaleStep;

        work->colorStep[0] += work->colorStep2[0];
        work->colorStep[1] += work->colorStep2[1];
        work->colorStep[2] += work->colorStep2[2];
        work->colorStep[3] += work->colorStep2[3];

        work->color[0] += work->colorStep[0];
        work->color[1] += work->colorStep[1];
        work->color[2] += work->colorStep[2];
        work->color[3] += work->colorStep[3];

        if (lightParam->lightId == object->lightId) {
            work->color[0] += lightParam->color[0];
            work->color[1] += lightParam->color[1];
            work->color[2] += lightParam->color[2];
            work->color[3] += lightParam->color[3];
            work->colorStep[0] += lightParam->colorStep[0];
            work->colorStep[1] += lightParam->colorStep[1];
            work->colorStep[2] += lightParam->colorStep[2];
            work->colorStep[3] += lightParam->colorStep[3];
            work->colorStep2[0] += lightParam->colorStep2[0];
            work->colorStep2[1] += lightParam->colorStep2[1];
            work->colorStep2[2] += lightParam->colorStep2[2];
            work->colorStep2[3] += lightParam->colorStep2[3];
            work->attenFalloff += lightParam->attenFalloff;
            work->attenFalloffStep += lightParam->attenFalloffStep;
            work->attenFalloffStep2 += lightParam->attenFalloffStep2;
            work->attenRadius += lightParam->attenRadius;
            work->attenRadiusStep += lightParam->attenRadiusStep;
            work->attenRadiusStep2 += lightParam->attenRadiusStep2;
            work->spotScale += lightParam->spotScale;
            work->spotScaleStep += lightParam->spotScaleStep;
            work->spotScaleStep2 += lightParam->spotScaleStep2;
            work->specularScale += lightParam->specularScale;
            work->specularScaleStep += lightParam->specularScaleStep;
            work->specularScaleStep2 += lightParam->specularScaleStep2;
        }

        __ct__Q29CLightPcs6CLightFv(light);

        sourcePos->x = object->x;
        sourcePos->y = object->y;
        sourcePos->z = object->z;
        PSMTXMultVec(pppMngStPtr->m_matrix.value, sourcePos, sourcePos);

        light->m_attenRadius = work->attenRadius;
        light->m_attenFalloff = work->attenFalloff;

        light->m_targetColor[0].r = (u8)(work->color[0] >> 7);
        light->m_targetColor[0].g = (u8)(work->color[1] >> 7);
        light->m_targetColor[0].b = (u8)(work->color[2] >> 7);
        light->m_targetColor[0].a = (u8)(work->color[3] >> 7);

        if (lightParam->enableColor1 != 0) {
            light->m_targetColor[1] = light->m_targetColor[0];
        } else {
            *(u32*)&light->m_targetColor[1] = 0;
        }

        if (lightParam->enableColor2 != 0) {
            light->m_targetColor[2] = light->m_targetColor[0];
        } else {
            *(u32*)&light->m_targetColor[2] = 0;
        }

        if (lightParam->enableColor0 == 0) {
            *(u32*)&light->m_targetColor[0] = 0;
        }

        if (gPppInConstructor == 0 && gPppInSubFrameCalc == 0) {
            if (lightParam->lightType == 0) {
                light->m_type = 0;
                light->m_direction.x = kPppLightZero;
                light->m_direction.y = kPppLightZero;
                light->m_direction.z = kPppLightOne;
                light->m_spotScale = kPppLightDefaultCosAtten;
                Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, light);
            } else {
                PppLightObject* targetObject;
                Vec* direction = (Vec*)&light->m_direction;

                light->m_type = 1;
                if (lightParam->targetIndex == -1) {
                    targetObject = (PppLightObject*)gPppDefaultValueBuffer;
                } else {
                    PppLightTarget* targetTable = (PppLightTarget*)pppMngStPtr->m_programInfoTable;
                    targetObject = (PppLightObject*)targetTable[lightParam->targetIndex].obj;
                }

                direction->x = targetObject->x;
                direction->y = targetObject->y;
                direction->z = targetObject->z;
                PSMTXMultVec(pppMngStPtr->m_matrix.value, direction, direction);

                PSVECSubtract(direction, sourcePos, direction);
                PSVECNormalize(direction, direction);
                light->m_spotScale = kPppLightSpotScale * work->spotScale;

                if (lightParam->lightType == 2) {
                    light->m_specularScale = work->specularScale;
                    light->m_specularMode = 1;
                }

                Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, light);
            }
        }
    }
}
