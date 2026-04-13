#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "dolphin/gx/__gx.h"

extern const f32 GXIndTexMtxScale1024;

#if DEBUG
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
    __gxVerif->rasRegs[(b >> 24) & 0xFF] = b; \
} while (0)
#else
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
} while (0)
#endif

#pragma dont_inline on
void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format, GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t, GXBool add_prev, GXBool utc_lod, GXIndTexAlphaSel alpha_sel) {
    u32 reg;

    CHECK_GXBEGIN(146, "GXInitIndTexture");
    reg = ind_stage;
    reg = (reg & 0xFFFFFFF3U) | ((u32)format << 2);
    reg = (reg & 0xFFFFFF8FU) | ((u32)bias_sel << 4);
    reg = (reg & 0xFFFFFE7FU) | ((u32)alpha_sel << 7);
    reg = (reg & 0xFFFFE1FFU) | ((u32)matrix_sel << 9);
    reg = (reg & 0xFFFF1FFFU) | ((u32)wrap_s << 13);
    reg = (reg & 0xFFF8FFFFU) | ((u32)wrap_t << 16);
    reg = (reg & 0xFFF7FFFFU) | ((u32)utc_lod << 19);
    reg = (reg & 0xFFEFFFFFU) | ((u32)add_prev << 20);
    reg = (reg & 0x00FFFFFFU) | ((u32)(tev_stage + 16) << 24);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);
    __GXData->bpSentNot = 0;
}
#pragma dont_inline reset

void GXSetIndTexMtx(GXIndTexMtxID mtx_id, const f32 offset[2][3], s8 scale_exp) {
    u32 reg0;
    u32 reg1;
    u32 reg2;
    s32 mtx[2][3];

    CHECK_GXBEGIN(186, "GXSetIndTexMtx");

    switch (mtx_id) {
    case GX_ITM_0:
    case GX_ITM_1:
    case GX_ITM_2:
        mtx_id = (GXIndTexMtxID)(mtx_id - 1);
        break;
    case GX_ITM_S0:
    case GX_ITM_S1:
    case GX_ITM_S2:
        mtx_id = (GXIndTexMtxID)(mtx_id - 5);
        break;
    case GX_ITM_T0:
    case GX_ITM_T1:
    case GX_ITM_T2:
        mtx_id = (GXIndTexMtxID)(mtx_id - 9);
        break;
    default:
        mtx_id = (GXIndTexMtxID)0;
        break;
    }

    mtx_id = (GXIndTexMtxID)(mtx_id * 3);
    scale_exp += 17;

    mtx[0][0] = (s32)(GXIndTexMtxScale1024 * offset[0][0]);
    mtx[1][0] = (s32)(GXIndTexMtxScale1024 * offset[1][0]);
    reg0 = mtx[0][0] & 0x7FF;
    reg0 = (reg0 & 0xFFC007FF) | ((mtx[1][0] & 0x7FF) << 11);
    reg0 = (reg0 & 0xFF3FFFFF) | (((u32)(s8)scale_exp & 3) << 22);
    reg0 = (reg0 & 0x00FFFFFF) | ((mtx_id + 6) << 24);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg0);

    mtx[0][1] = (s32)(GXIndTexMtxScale1024 * offset[0][1]);
    mtx[1][1] = (s32)(GXIndTexMtxScale1024 * offset[1][1]);
    reg1 = mtx[0][1] & 0x7FF;
    reg1 = (reg1 & 0xFFC007FF) | ((mtx[1][1] & 0x7FF) << 11);
    reg1 = (reg1 & 0xFF3FFFFF) | (((u32)(s8)scale_exp & 0xC) << 20);
    reg1 = (reg1 & 0x00FFFFFF) | ((mtx_id + 7) << 24);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg1);

    mtx[0][2] = (s32)(GXIndTexMtxScale1024 * offset[0][2]);
    mtx[1][2] = (s32)(GXIndTexMtxScale1024 * offset[1][2]);
    reg2 = mtx[0][2] & 0x7FF;
    reg2 = (reg2 & 0xFFC007FF) | ((mtx[1][2] & 0x7FF) << 11);
    reg2 = (reg2 & 0xFF3FFFFF) | (((u32)(s8)scale_exp & 0x30) << 18);
    reg2 = (reg2 & 0x00FFFFFF) | ((mtx_id + 8) << 24);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg2);

    __GXData->bpSentNot = 0;
}

void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t) {
    CHECK_GXBEGIN(249, "GXSetIndTexScale");

    switch (ind_state) {
    case GX_INDTEXSTAGE0:
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0xFFFFFFF0) | (u32)scale_s;
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0xFFFFFF0F) | ((u32)scale_t << 4);
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0x00FFFFFF) | 0x25000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
        break;
    case GX_INDTEXSTAGE1:
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0xFFFFF0FF) | ((u32)scale_s << 8);
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0xFFFF0FFF) | ((u32)scale_t << 12);
        __GXData->IndTexScale0 = (__GXData->IndTexScale0 & 0x00FFFFFF) | 0x25000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
        break;
    case GX_INDTEXSTAGE2:
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0xFFFFFFF0) | (u32)scale_s;
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0xFFFFFF0F) | ((u32)scale_t << 4);
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0x00FFFFFF) | 0x26000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale1);
        break;
    case GX_INDTEXSTAGE3:
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0xFFFFF0FF) | ((u32)scale_s << 8);
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0xFFFF0FFF) | ((u32)scale_t << 12);
        __GXData->IndTexScale1 = (__GXData->IndTexScale1 & 0x00FFFFFF) | 0x26000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale1);
        break;
    default:
        ASSERTMSGLINE(277, 0, "GXSetIndTexCoordScale: Invalid Indirect Stage Id");
        break;
    }
    __GXData->bpSentNot = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801a4ebc
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map) {
    CHECK_GXBEGIN(302, "GXSetIndTexOrder");

    ASSERTMSGLINE(314, tex_map < GX_MAX_TEXMAP, "GXSetIndTexOrder: Invalid direct texture Id");
    ASSERTMSGLINE(315, tex_coord < GX_MAX_TEXCOORD, "GXSetIndTexOrder: Invalid texture coord");

    switch (ind_stage) {
    case GX_INDTEXSTAGE0:
        __GXData->iref = (__GXData->iref & 0xFFFFFFF8) | (u32)tex_map;
        __GXData->iref = (__GXData->iref & 0xFFFFFFC7) | ((u32)tex_coord << 3);
        break;
    case GX_INDTEXSTAGE1:
        __GXData->iref = (__GXData->iref & 0xFFFFFE3F) | ((u32)tex_map << 6);
        __GXData->iref = (__GXData->iref & 0xFFFFF1FF) | ((u32)tex_coord << 9);
        break;
    case GX_INDTEXSTAGE2:
        __GXData->iref = (__GXData->iref & 0xFFFF8FFF) | ((u32)tex_map << 12);
        __GXData->iref = (__GXData->iref & 0xFFFC7FFF) | ((u32)tex_coord << 15);
        break;
    case GX_INDTEXSTAGE3:
        __GXData->iref = (__GXData->iref & 0xFFE3FFFF) | ((u32)tex_map << 18);
        __GXData->iref = (__GXData->iref & 0xFF1FFFFF) | ((u32)tex_coord << 21);
        break;
    default:
        ASSERTMSGLINE(335, 0, "GXSetIndTexOrder: Invalid Indirect Stage Id");
        break;
    }
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->iref);
    __GXData->dirtyState |= 3;
    __GXData->bpSentNot = 0;
}

void GXSetNumIndStages(u8 nIndStages) {
    u32 reg;

    CHECK_GXBEGIN(353, "GXSetNumIndStages");
    ASSERTMSGLINE(355, nIndStages <= 4, "GXSetNumIndStages: Exceeds max. number of indirect texture stages");

    reg = __GXData->genMode;
    reg = (reg & 0xFFF8FFFFU) | ((u32)nIndStages << 16);
    __GXData->genMode = reg;

    __GXData->dirtyState |= 6;
}

void GXSetTevDirect(GXTevStageID tev_stage) {
    CHECK_GXBEGIN(373, "GXSetTevDirect");
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
}

void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u8 signed_offset, u8 replace_mode, GXIndTexMtxID matrix_sel) {
    GXIndTexWrap wrap = (replace_mode != 0) ? GX_ITW_0 : GX_ITW_OFF;

    CHECK_GXBEGIN(395, "GXSetTevIndWarp");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, (signed_offset != 0) ? GX_ITB_STU : GX_ITB_NONE, matrix_sel, wrap, wrap, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
}

void GXSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel) {
    CHECK_GXBEGIN(561, "GXSetTevIndBumpXYZ");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_STU, matrix_sel, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
}

void __GXUpdateBPMask(void) {
    int i;
    u32 texMap;
    u32 mask;
    u32 numStages;

    mask = 0;
    numStages = (__GXData->genMode >> 16) & 7;

    for (i = 0; i < numStages; i++) {
        switch (i) {
        case 0:
            texMap = __GXData->iref & 7;
            break;
        case 1:
            texMap = (__GXData->iref >> 6) & 7;
            break;
        case 2:
            texMap = (__GXData->iref >> 12) & 7;
            break;
        case 3:
            texMap = (__GXData->iref >> 18) & 7;
            break;
        }
        mask |= (1 << texMap);
    }

    if (((__GXData->bpMask & 0xFF) == mask)) {
        return;
    }

    __GXData->bpMask = (__GXData->bpMask & 0xFFFFFF00) | mask;
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}

void __GXFlushTextureState(void) {
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}
