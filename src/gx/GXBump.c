#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "dolphin/gx/__gx.h"

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
    reg |= (u32)(tev_stage + 16) << 24;
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);
    __GXData->bpSentNot = 0;
}
#pragma dont_inline reset

void GXSetIndTexMtx(GXIndTexMtxID mtx_id, const f32 offset[2][3], s8 scale_exp) {
    u32 id;
    u32 scale;
    u32 reg;

    CHECK_GXBEGIN(186, "GXSetIndTexMtx");

    switch (mtx_id) {
    case GX_ITM_0:
    case GX_ITM_1:
    case GX_ITM_2:
        id = mtx_id - 1;
        break;
    case GX_ITM_S0:
    case GX_ITM_S1:
    case GX_ITM_S2:
        id = mtx_id - 5;
        break;
    case GX_ITM_T0:
    case GX_ITM_T1:
    case GX_ITM_T2:
        id = mtx_id - 9;
        break;
    default:
        id = 0;
        break;
    }

    id *= 3;
    scale = (u8)(s8)(scale_exp + 17);

    reg = ((s32)(1024.0f * offset[0][0]) & 0x7FF);
    reg |= ((s32)(1024.0f * offset[1][0]) & 0x7FF) << 11;
    reg |= (scale & 3) << 22;
    reg |= (id + 6) << 24;
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);

    reg = ((s32)(1024.0f * offset[0][1]) & 0x7FF);
    reg |= ((s32)(1024.0f * offset[1][1]) & 0x7FF) << 11;
    reg |= (scale & 0xC) << 20;
    reg |= (id + 7) << 24;
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);

    reg = ((s32)(1024.0f * offset[0][2]) & 0x7FF);
    reg |= ((s32)(1024.0f * offset[1][2]) & 0x7FF) << 11;
    reg |= (scale & 0x30) << 18;
    reg |= (id + 8) << 24;
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);

    __GXData->bpSentNot = 0;
}

void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t) {
    CHECK_GXBEGIN(249, "GXSetIndTexScale");

    switch (ind_state) {
    case GX_INDTEXSTAGE0:
        SET_REG_FIELD(253, __GXData->IndTexScale0, 4, 0, scale_s);
        SET_REG_FIELD(254, __GXData->IndTexScale0, 4, 4, scale_t);
        SET_REG_FIELD(254, __GXData->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
        break;
    case GX_INDTEXSTAGE1:
        SET_REG_FIELD(259, __GXData->IndTexScale0, 4, 8, scale_s);
        SET_REG_FIELD(260, __GXData->IndTexScale0, 4, 12, scale_t);
        SET_REG_FIELD(260, __GXData->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
        break;
    case GX_INDTEXSTAGE2:
        SET_REG_FIELD(265, __GXData->IndTexScale1, 4, 0, scale_s);
        SET_REG_FIELD(266, __GXData->IndTexScale1, 4, 4, scale_t);
        SET_REG_FIELD(266, __GXData->IndTexScale1, 8, 24, 0x26);
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale1);
        break;
    case GX_INDTEXSTAGE3:
        SET_REG_FIELD(0x10F, __GXData->IndTexScale1, 4, 8, scale_s);
        SET_REG_FIELD(0x110, __GXData->IndTexScale1, 4, 12, scale_t);
        SET_REG_FIELD(0x110, __GXData->IndTexScale1, 8, 24, 0x26);
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
    CHECK_GXBEGIN(353, "GXSetNumIndStages");
    ASSERTMSGLINE(355, nIndStages <= 4, "GXSetNumIndStages: Exceeds max. number of indirect texture stages");
    SET_REG_FIELD(356, __GXData->genMode, 3, 16, nIndStages);
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

void GXSetTevIndTile(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u16 tilesize_s,
    u16 tilesize_t, u16 tilespacing_s, u16 tilespacing_t, GXIndTexFormat format,
    GXIndTexMtxID matrix_sel, GXIndTexBiasSel bias_sel, GXIndTexAlphaSel alpha_sel)
{
    GXIndTexWrap wrap_s;
    GXIndTexWrap wrap_t;
    f32 mtx[2][3];

    CHECK_GXBEGIN(429, "GXSetTevIndTile");
    ASSERTMSGLINE(430, tev_stage < GX_MAX_TEVSTAGE, "GXSetTevIndTile: Invalid tev stage id");
    ASSERTMSGLINE(431, ind_stage < GX_MAX_INDTEXSTAGE, "GXSetTevIndTile: Invalid indirect stage id");

    switch (tilesize_s) {
    case 256:
        wrap_s = GX_ITW_256;
        break;
    case 128:
        wrap_s = GX_ITW_128;
        break;
    case 64:
        wrap_s = GX_ITW_64;
        break;
    case 32:
        wrap_s = GX_ITW_32;
        break;
    case 16:
        wrap_s = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(440, 0, "GXSetTevIndTile: Invalid tilesize for S coordinate");
        wrap_s = GX_ITW_OFF;
        break;
    }

    switch (tilesize_t) {
    case 256:
        wrap_t = GX_ITW_256;
        break;
    case 128:
        wrap_t = GX_ITW_128;
        break;
    case 64:
        wrap_t = GX_ITW_64;
        break;
    case 32:
        wrap_t = GX_ITW_32;
        break;
    case 16:
        wrap_t = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(452, 0, "GXSetTevIndTile: Invalid tilesize for T coordinate");
        wrap_t = GX_ITW_OFF;
        break;
    }

    mtx[0][0] = tilespacing_s / 1024.0f;
    mtx[0][1] = mtx[0][2] = 0.0f;
    mtx[1][1] = tilespacing_t / 1024.0f;
    mtx[1][0] = mtx[1][2] = 0.0f;
    GXSetIndTexMtx(matrix_sel, mtx, 10);
    GXSetTevIndirect(tev_stage, ind_stage, format, bias_sel, matrix_sel, wrap_s, wrap_t, GX_FALSE, GX_TRUE, alpha_sel);
}

void GXSetTevIndBumpST(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel) {
    GXIndTexMtxID sm;
    GXIndTexMtxID tm;

    CHECK_GXBEGIN(492, "GXSetTevIndBumpST");

    switch (matrix_sel) {
    case GX_ITM_0:
        sm = GX_ITM_S0;
        tm = GX_ITM_T0;
        break;
    case GX_ITM_1:
        sm = GX_ITM_S1;
        tm = GX_ITM_T1;
        break;
    case GX_ITM_2:
        sm = GX_ITM_S2;
        tm = GX_ITM_T2;
        break;
    default:
        ASSERTMSGLINE(509, 0, "GXSetTevIndBumpST: Invalid matrix selection");
        break;
    }

    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_ST, sm, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevIndirect(tev_stage + 1, ind_stage, GX_ITF_8, GX_ITB_ST, tm, GX_ITW_0, GX_ITW_0, GX_TRUE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevIndirect(tev_stage + 2, ind_stage, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, GX_TRUE, GX_FALSE, GX_ITBA_OFF);
}

void GXSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel) {
    CHECK_GXBEGIN(561, "GXSetTevIndBumpXYZ");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_STU, matrix_sel, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
}

void GXSetTevIndRepeat(GXTevStageID tev_stage) {
    CHECK_GXBEGIN(590, "GXSetTevIndRepeat");
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_0, GX_ITW_0, GX_TRUE, GX_FALSE, GX_ITBA_OFF);
}

void __GXUpdateBPMask(void) {
    u32 mask;
    int i;
    u32 numStages;
    u32 texMap;

    mask = 0;
    i = 0;
    numStages = (__GXData->genMode >> 16) & 3;

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
        default:
            texMap = 0;
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

void __GXSetIndirectMask(u32 mask) {
    SET_REG_FIELD(664, __GXData->bpMask, 8, ~0xFF, mask);

    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}

void __GXFlushTextureState(void) {
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}
