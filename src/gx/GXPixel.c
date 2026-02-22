#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "dolphin/gx/__gx.h"

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color) {
    u32 fogclr;
    u32 fog0;
    u32 fog1;
    u32 fog2;
    u32 fog3;
    f32 A;
    f32 B;
    f32 B_mant;
    f32 C;
    f32 a;
    f32 c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;
    u32 fsel;
    u32 proj;
    u32 rgba;

    fogclr = 0;
    fog0 = 0;
    fog1 = 0;
    fog2 = 0;
    fog3 = 0;

    CHECK_GXBEGIN(138, "GXSetFog");

    ASSERTMSGLINE(140, farz >= 0.0f, "GXSetFog: The farz should be positive value");
    ASSERTMSGLINE(141, farz >= nearz, "GXSetFog: The farz should be larger than nearz");

    fsel = type & 7;
    proj = (type >> 3) & 1;
    
    if (proj) {
        if (farz == nearz || endz == startz) {
            a = 0.0f;
            c = 0.0f;
        } else {
            A = (1.0f / (endz - startz));
            a = A * (farz - nearz);
            c = A * (startz - nearz);
        }
    } else {
        if (farz == nearz || endz == startz) {
            A = 0.0f;
            B = 0.5f;
            C = 0.0f;
        } else {
            A = (farz * nearz) / ((farz - nearz) * (endz - startz));
            B = farz / (farz - nearz);
            C = startz / (endz - startz);
        }

        B_mant = B;
        B_expn = 0;
        while (B_mant > 1.0) {
            B_mant /= 2.0f;
            B_expn++;
        }
        while (B_mant > 0.0f && B_mant < 0.5) {
            B_mant *= 2.0f;
            B_expn--;
        }

        a = A / (f32) (1 << (B_expn + 1));
        b_m = 8.388638e6f * B_mant;
        b_s = B_expn + 1;
        c = C;

        fog1 = (b_m & 0x00FFFFFF) | 0xEF000000;
        fog2 = (b_s & 0x1F) | 0xF0000000;
    }

    a_hex = *(u32*)&a;
    c_hex = *(u32*)&c;

    fog0 = ((a_hex >> 12) & 0x7FF) | ((a_hex >> 12) & 0x7F800) | ((a_hex >> 12) & 0x80000) |
           0xEE000000;
    fog3 = ((c_hex >> 12) & 0x7FF) | ((c_hex >> 12) & 0x7F800) | ((c_hex >> 12) & 0x80000) |
           (proj << 20) | (fsel << 21) | 0xF1000000;

    rgba = *(u32*)&color;
    fogclr = (rgba >> 8) | 0xF2000000;

    GX_WRITE_RAS_REG(fog0);
    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);
    GX_WRITE_RAS_REG(fog3);
    GX_WRITE_RAS_REG(fogclr);

    __GXData->bpSentNot = 0;
}

void GXSetFogColor(GXColor color) {
    u32 rgba;
    u32 fogclr = 0xF2000000;

    rgba = *(u32*)&color;
    SET_REG_FIELD(250, fogclr, 24, 0, rgba >> 8);
    GX_WRITE_RAS_REG(fogclr);
    __GXData->bpSentNot = 0;
}

void GXInitFogAdjTable(GXFogAdjTable *table, u16 width, const f32 projmtx[4][4]) {
    f32 xi;
    f32 iw;
    f32 rangeVal;
    f32 nearZ;
    f32 sideX;
    u32 i;

    CHECK_GXBEGIN(275, "GXInitFogAdjTable");
    ASSERTMSGLINE(276, table != NULL, "GXInitFogAdjTable: table pointer is null");
    ASSERTMSGLINE(277, width <= 640, "GXInitFogAdjTable: invalid width value");

    if (0.0 == projmtx[3][3]) {
        nearZ = projmtx[2][3] / (projmtx[2][2] - 1.0f);
        sideX = nearZ / projmtx[0][0];
    } else {
        sideX = 1.0f / projmtx[0][0];
        nearZ = 1.73205f * sideX;
    }

    iw = 2.0f / width;
    for (i = 0; i < 10; i++) {
        xi = (i + 1) << 5;
        xi *= iw;
        xi *= sideX;
        rangeVal = sqrtf(1.0f + ((xi * xi) / (nearZ * nearZ)));
        table->r[i] = (u32)(256.0f * rangeVal) & 0xFFF;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801a5bd8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable *table) {
    const u16* r;
    u32 cmd;
    u32 range_adj;

    CHECK_GXBEGIN(331, "GXSetFogRangeAdj");

    if (enable) {
        ASSERTMSGLINE(334, table != NULL, "GXSetFogRangeAdj: table pointer is null");
        r = table->r;
        cmd = 0xE9000000;

        range_adj = (r[0] & 0xFFF) | ((u32)(r[1] & 0xFFF) << 12) | cmd;
        GX_WRITE_RAS_REG(range_adj);
        cmd += 0x01000000;

        range_adj = (r[2] & 0xFFF) | ((u32)(r[3] & 0xFFF) << 12) | cmd;
        GX_WRITE_RAS_REG(range_adj);
        cmd += 0x01000000;

        range_adj = (r[4] & 0xFFF) | ((u32)(r[5] & 0xFFF) << 12) | cmd;
        GX_WRITE_RAS_REG(range_adj);
        cmd += 0x01000000;

        range_adj = (r[6] & 0xFFF) | ((u32)(r[7] & 0xFFF) << 12) | cmd;
        GX_WRITE_RAS_REG(range_adj);
        cmd += 0x01000000;

        range_adj = (r[8] & 0xFFF) | ((u32)(r[9] & 0xFFF) << 12) | cmd;
        GX_WRITE_RAS_REG(range_adj);
    }

    range_adj = ((center + 342) & 0x00FFFBFF) | ((u32)(u8)enable << 10) | 0xE8000000;
    GX_WRITE_RAS_REG(range_adj);
    __GXData->bpSentNot = 0;
}

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) {
    u32 reg;
    u32 blend_en;

    CHECK_GXBEGIN(375, "GXSetBlendMode");

    reg = __GXData->cmode0;

#if DEBUG
    blend_en = type == GX_BM_BLEND || type == GX_BM_SUBTRACT;
#endif

    SET_REG_FIELD(389, reg, 1, 11, (type == GX_BM_SUBTRACT));
#if DEBUG
    SET_REG_FIELD(392, reg, 1, 0, blend_en);
#else
    SET_REG_FIELD(392, reg, 1, 0, type);
#endif
    SET_REG_FIELD(393, reg, 1, 1, (type == GX_BM_LOGIC));
    SET_REG_FIELD(394, reg, 4, 12, op);
    SET_REG_FIELD(395, reg, 3, 8, src_factor);
    SET_REG_FIELD(396, reg, 3, 5, dst_factor);
    GX_WRITE_RAS_REG(reg);

    __GXData->cmode0 = reg;
    __GXData->bpSentNot = 0;
}

void GXSetColorUpdate(GXBool update_enable) {
    u32 reg;
    CHECK_GXBEGIN(419, "GXSetColorUpdate");

    reg = __GXData->cmode0;

    SET_REG_FIELD(421, reg, 1, 3, update_enable);
    GX_WRITE_RAS_REG(reg);

    __GXData->cmode0 = reg;
    __GXData->bpSentNot = 0;
}

void GXSetAlphaUpdate(GXBool update_enable) {
    u32 reg;
    CHECK_GXBEGIN(432, "GXSetAlphaUpdate");

    reg = __GXData->cmode0;

    SET_REG_FIELD(434, reg, 1, 4, update_enable);
    GX_WRITE_RAS_REG(reg);

    __GXData->cmode0 = reg;
    __GXData->bpSentNot = 0;
}

void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable) {
    u32 reg;
    CHECK_GXBEGIN(459, "GXSetZMode");

    reg = __GXData->zmode;

    SET_REG_FIELD(462, reg, 1, 0, compare_enable);
    SET_REG_FIELD(463, reg, 3, 1, func);
    SET_REG_FIELD(464, reg, 1, 4, update_enable);
    GX_WRITE_RAS_REG(reg);

    __GXData->zmode = reg;
    __GXData->bpSentNot = 0;
}

void GXSetZCompLoc(GXBool before_tex) {
    GXData *gx;

    CHECK_GXBEGIN(474, "GXSetZCompLoc");

    gx = __GXData;
    gx->peCtrl = (gx->peCtrl & 0xFFFFFFBF) | ((u32)(u8)before_tex << 6);
    GX_WRITE_RAS_REG(gx->peCtrl);
    gx->bpSentNot = 0;
}

void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt) {
    u32 oldPeCtrl;
    static u32 p2f[8] = { 0, 1, 2, 3, 4, 4, 4, 5 };

    CHECK_GXBEGIN(511, "GXSetPixelFmt");
    oldPeCtrl = __GXData->peCtrl;
    ASSERTMSGLINE(515, pix_fmt >= GX_PF_RGB8_Z24 && pix_fmt <= GX_PF_YUV420, "Invalid Pixel format");
    __GXData->peCtrl = (__GXData->peCtrl & ~0x7) | p2f[pix_fmt];
    __GXData->peCtrl = (__GXData->peCtrl & ~0x38) | ((u32)z_fmt << 3);

    if (oldPeCtrl != __GXData->peCtrl) {
        GX_WRITE_RAS_REG(__GXData->peCtrl);
        __GXData->genMode = (__GXData->genMode & ~0x200) | ((u32)(pix_fmt == GX_PF_RGB565_Z16) << 9);
        __GXData->dirtyState |= 4;
    }

    if (p2f[pix_fmt] == 4) {
        __GXData->cmode1 = (__GXData->cmode1 & ~0x600) | (((pix_fmt - 4) << 9) & 0x600);
        __GXData->cmode1 = (__GXData->cmode1 & ~0xFF000000) | 0x42000000;
        GX_WRITE_RAS_REG(__GXData->cmode1);
    }

    __GXData->bpSentNot = 0;
}

void GXSetDither(GXBool dither) {
    u32 reg;
    CHECK_GXBEGIN(556, "GXSetDither");

    reg = __GXData->cmode0;

    SET_REG_FIELD(559, reg, 1, 2, dither);
    GX_WRITE_RAS_REG(reg);

    __GXData->cmode0 = reg;
    __GXData->bpSentNot = 0;
}

void GXSetDstAlpha(GXBool enable, u8 alpha) {
    u32 reg;
    CHECK_GXBEGIN(581, "GXSetDstAlpha");

    reg = __GXData->cmode1;

    SET_REG_FIELD(584, reg, 8, 0, alpha);
    SET_REG_FIELD(585, reg, 1, 8, enable);
    GX_WRITE_RAS_REG(reg);

    __GXData->cmode1 = reg;
    __GXData->bpSentNot = 0;
}

void GXSetFieldMask(GXBool odd_mask, GXBool even_mask) {
    u32 reg;

    CHECK_GXBEGIN(608, "GXSetFieldMask");

    reg = (u32)(u8)even_mask;
    reg = (reg & ~2) | ((u32)(u8)odd_mask << 1);
    reg = (reg & 0x00FFFFFF) | 0x44000000;
    GX_WRITE_RAS_REG(reg);
    __GXData->bpSentNot = 0;
}

void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio) {
    GXData* gx;
    u32 reg;

    CHECK_GXBEGIN(637, "GXSetFieldMode");
    gx = __GXData;
    gx->lpSize = (gx->lpSize & ~0x00400000) | ((u32)(u8)half_aspect_ratio << 22);
    GX_WRITE_RAS_REG(gx->lpSize);
    __GXFlushTextureState();
    reg = (u32)(u8)field_mode | 0x68000000;
    GX_WRITE_RAS_REG(reg);
    __GXFlushTextureState();
}
