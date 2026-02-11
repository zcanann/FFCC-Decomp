#include "ffcc/pppScreenBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

struct PScreenBreak {
    float field0_0x0;
    u8 _pad0[0x84];
    u8 field_0x88;
    u8 field_0x89;
    u8 field_0x8a;
    u8 field_0x8b;
};

struct VScreenBreak {
    u8 _pad0[0x100];
};

struct UnkB {
    float m_dataValIndex;
    u16 m_initWOrk;
    u16 _pad6;
    float m_stepValue;
    s32 m_graphId;
    float m_arg3;
    u8* m_payload;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

extern int DAT_8032ed70;
extern int DAT_802381a0;
extern float FLOAT_80331cc0;
extern char s_pppScreenBreak_cpp_801dd4d4[];
extern CGraphic GraphicsPcs;
extern _pppMngSt* pppMngStPtr;
extern _pppEnvSt* pppEnvStPtr;

extern "C" {
void SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(CGraphic*, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConScreenBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCon2ScreenBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDesScreenBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameScreenBreak(PScreenBreak* pppScreenBreak, UnkB* param_2, UnkC* param_3)
{
    if (DAT_8032ed70 != 0) {
        return;
    }

    if (DAT_802381a0 != 0) {
        SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(&GraphicsPcs, 0, 0, 0, 0, 0, 0, 0);
    }

    s32 index = param_3->m_serializedDataOffsets[0];
    float* value = (float*)((u8*)&pppScreenBreak->field0_0x0 + 8 + param_3->m_serializedDataOffsets[2]);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(float**)(model + 0xE4) = value;
    *(UnkB**)(model + 0xE8) = param_2;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    u8* color = (u8*)(value + 10);
    color[0] = (&pppScreenBreak->field_0x88)[index];
    color[1] = (&pppScreenBreak->field_0x89)[index];
    color[2] = (&pppScreenBreak->field_0x8a)[index];
    color[3] = (&pppScreenBreak->field_0x8b)[index];
    DCFlushRange(value + 10, 4);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param_2->m_stepValue, &pppScreenBreak->field0_0x0, param_2->m_graphId,
                                                 value, value + 1, value + 2, &param_2->m_arg3, (float*)param_2->m_payload);

    u32 pieceCount = *(u32*)(*(u8**)(model + 0xA4) + 0xC);
    if (*(void**)&value[3] == NULL) {
        *(void**)&value[3] = pppMemAlloc__FUlPQ27CMemory6CStagePci(pieceCount * 0x3C, pppEnvStPtr->m_stagePtr,
                                                                    s_pppScreenBreak_cpp_801dd4d4, 0x25E);
        *(void**)&value[4] = pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr,
                                                                    s_pppScreenBreak_cpp_801dd4d4, 0x25F);
        InitPieceData((CChara::CModel*)model, pppScreenBreak, (VScreenBreak*)param_2);
        PSVECNormalize((Vec*)(param_2->m_payload + 0xC), (Vec*)(param_2->m_payload + 0xC));
    }

    float sx = FLOAT_80331cc0 * value[6];
    float sy = FLOAT_80331cc0 * value[7];
    u8* piece = (u8*)*(void**)&value[3];
    for (u32 i = 0; i < pieceCount; i++) {
        switch ((u8)param_2->m_initWOrk) {
        case 0:
            piece[0x38] = 1;
            break;
        case 1:
            if (-*(float*)(piece + 0x28) < (*value * sy) - value[7]) {
                piece[0x38] = 1;
            }
            break;
        case 2:
            if (-((*value * sy) - value[7]) < -*(float*)(piece + 0x28)) {
                piece[0x38] = 1;
            }
            break;
        case 3:
            if (-*(float*)(piece + 0x24) < (*value * sx) - value[6]) {
                piece[0x38] = 1;
            }
            break;
        case 4:
            if (-((*value * sx) - value[6]) < -*(float*)(piece + 0x24)) {
                piece[0x38] = 1;
            }
            break;
        case 5: {
            float x = *value * value[6];
            float y = *value * value[7];
            if ((*(float*)(piece + 0x24) <= x) && (-*(float*)(piece + 0x24) <= x) &&
                (*(float*)(piece + 0x28) <= y) && (-*(float*)(piece + 0x28) <= y)) {
                piece[0x38] = 1;
            }
            break;
        }
        case 6: {
            float x = *value * value[6];
            float y = *value * value[7];
            if (((value[6] - x <= -*(float*)(piece + 0x24)) || (-*(float*)(piece + 0x24) <= -value[6] + x) ||
                 (value[7] - y <= -*(float*)(piece + 0x28)) || (-*(float*)(piece + 0x28) <= -value[7] + y))) {
                piece[0x38] = 1;
            }
            break;
        }
        default:
            break;
        }
        piece += 0x3C;
    }

    pppSetFpMatrix(pppMngStPtr);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderScreenBreak(void)
{
	// TODO
}
