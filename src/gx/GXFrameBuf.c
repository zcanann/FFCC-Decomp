#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "dolphin/gx/__gx.h"

GXRenderModeObj GXNtsc240Ds = {
    1,
    640, 240, 240,
    40, 0,
    640, 480,
    0,
    0,
    0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240DsAa = {
    1, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240Int = {
    0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240IntAa = {
    0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntDf = {
    0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 }
};

GXRenderModeObj GXNtsc480Int = {
    0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntAa = {
    0, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXNtsc480Prog = {
    2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480ProgSoft = {
    2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 }
};

GXRenderModeObj GXNtsc480ProgAa = {
    2, 640, 242, 480, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXMpal240Ds = {9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240DsAa = {9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240Int = {8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240IntAa = {8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntDf = {8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXMpal480Int = {8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntAa = {8, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXPal264Ds = {5, 640, 264, 264, 40, 11, 640, 528, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264DsAa = {5, 640, 264, 264, 40, 11, 640, 528, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264Int = {4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264IntAa = {4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal528IntDf = {4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXPal528Int = {4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal524IntAa = {4, 640, 264, 524, 40, 23, 640, 524, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXEurgb60Hz240Ds = {21, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240DsAa = {21, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240Int = {20, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240IntAa = {20, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz480IntDf = {20, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXEurgb60Hz480Int = {20, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz480IntAa = {20, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXRmHW = {1, 320, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

void GXAdjustForOverscan(const GXRenderModeObj* rmin, GXRenderModeObj* rmout, u16 hor, u16 ver) {
    u16 hor2 = hor * 2;
    u16 ver2 = ver * 2;
    u32 verf;

    if (rmin != rmout) {
        *rmout = *rmin;
    }

    rmout->fbWidth = rmin->fbWidth - hor2;
    verf = (ver2 * rmin->efbHeight) / (u32)rmin->xfbHeight;
    rmout->efbHeight = rmin->efbHeight - verf;
    if (rmin->xFBmode == VI_XFBMODE_SF && (rmin->viTVmode & 2) != 2) {
        rmout->xfbHeight = rmin->xfbHeight - ver;
    } else {
        rmout->xfbHeight = rmin->xfbHeight - ver2;
    }

    rmout->viWidth = rmin->viWidth - hor2;
    rmout->viHeight = rmin->viHeight - ver2;
 
    rmout->viXOrigin = rmin->viXOrigin + hor;
    rmout->viYOrigin = rmin->viYOrigin + ver;
}

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht) {
    GXData* gx;

    CHECK_GXBEGIN(1235, "GXSetDispCopySrc");
    gx = __GXData;

    gx->cpDispSrc = 0;
    OLD_SET_REG_FIELD(1238, gx->cpDispSrc, 10, 0, left);
    OLD_SET_REG_FIELD(1239, gx->cpDispSrc, 10, 10, top);
    OLD_SET_REG_FIELD(1239, gx->cpDispSrc, 8, 24, 0x49);

    gx->cpDispSize = 0;
    OLD_SET_REG_FIELD(1243, gx->cpDispSize, 10, 0, wd - 1);
    OLD_SET_REG_FIELD(1244, gx->cpDispSize, 10, 10, ht - 1);
    OLD_SET_REG_FIELD(1244, gx->cpDispSize, 8, 24, 0x4A);
}


void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht) {
    GXData* gx;

    CHECK_GXBEGIN(1263, "GXSetTexCopySrc");
    gx = __GXData;

    gx->cpTexSrc = 0;
    OLD_SET_REG_FIELD(1266, gx->cpTexSrc, 10, 0, left);
    OLD_SET_REG_FIELD(1267, gx->cpTexSrc, 10, 10, top);
    OLD_SET_REG_FIELD(1267, gx->cpTexSrc, 8, 24, 0x49);

    gx->cpTexSize = 0;
    OLD_SET_REG_FIELD(1271, gx->cpTexSize, 10, 0, wd - 1);
    OLD_SET_REG_FIELD(1272, gx->cpTexSize, 10, 10, ht - 1);
    OLD_SET_REG_FIELD(1272, gx->cpTexSize, 8, 24, 0x4A);
}

/*
 * --INFO--
 * PAL Address: 0x801BD030
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetDispCopyDst(u16 wd, u16 ht) {
    ASSERTMSGLINE(1293, (wd & 0xF) == 0, "GXSetDispCopyDst: Width must be a multiple of 16");
    CHECK_GXBEGIN(1294, "GXSetDispCopyDst");
    __GXData->cpDispStride = 0;
    __GXData->cpDispStride = (__GXData->cpDispStride & 0xFFFFFC00) | ((u32)(wd & 0x7FF0) >> 4);
    __GXData->cpDispStride = (__GXData->cpDispStride & 0x00FFFFFF) | 0x4D000000;
}

void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap) {
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;

    CHECK_GXBEGIN(1327, "GXSetTexCopyDst");

    __GXData->cpTexZ = 0;
    peTexFmt = fmt & 0xF;
    ASSERTMSGLINEV(1358, peTexFmt < 13, "%s: invalid texture format", "GXSetTexCopyDst");

    if (fmt == GX_TF_Z16) {
        peTexFmt = 0xB;
    }

    switch (fmt) {
    case GX_TF_I4:
    case GX_TF_I8:
    case GX_TF_IA4:
    case GX_TF_IA8:
    case GX_CTF_YUVA8:
        __GXData->cpTex = (__GXData->cpTex & 0xFFFE7FFF) | 0x18000;
        break;
    default:
        __GXData->cpTex = (__GXData->cpTex & 0xFFFE7FFF) | 0x10000;
        break;
    }

    __GXData->cpTexZ = (u8)((u32)__cntlzw((fmt & _GX_TF_ZTF) - _GX_TF_ZTF) >> 5);
    __GXData->cpTex = (__GXData->cpTex & 0xFFFFFFF7) | (peTexFmt & 8);
    __GetImageTileCount(fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    __GXData->cpTexStride = 0;
    __GXData->cpTexStride = (__GXData->cpTexStride & 0xFFFFFC00) | (rowTiles * cmpTiles);
    __GXData->cpTexStride = (__GXData->cpTexStride & 0x00FFFFFF) | 0x4D000000;
    __GXData->cpTex = (__GXData->cpTex & 0xFFFFFDFF) | ((u32)mipmap << 9);
    __GXData->cpTex = (__GXData->cpTex & 0xFFFFFF8F) | ((peTexFmt & 7) << 4);
}

/*
 * --INFO--
 * PAL Address: 0x801A2BA4
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetDispCopyFrame2Field(GXCopyMode mode) {
    GXData* gx;
    u32* cpTex;
    u32 reg;

    CHECK_GXBEGIN(1410, "GXSetDispCopyFrame2Field");
    gx = __GXData;

    reg = gx->cpDisp;
    reg = (reg & 0xFFFFCFFF) | ((u32)mode << 12);
    gx->cpDisp = reg;

    cpTex = &gx->cpTex;
    reg = *cpTex;
    reg &= 0xFFFFCFFF;
    *cpTex = reg;
}

/*
 * --INFO--
 * PAL Address: 0x801A2BCC
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetCopyClamp(GXFBClamp clamp) {
    GXData* gx;
    u32 clmpB;
    u32 clmpT;

    CHECK_GXBEGIN(1431, "GXSetCopyClamp");
    gx = __GXData;

    clmpT = ((u32)__cntlzw((clamp & GX_CLAMP_TOP) - GX_CLAMP_TOP) >> 5) & 0xFF;
    clmpB = ((u32)__cntlzw((clamp & GX_CLAMP_BOTTOM) - GX_CLAMP_BOTTOM) >> 4) & 0x1FE;

    gx->cpDisp = (gx->cpDisp & ~1) | clmpT;
    gx->cpDisp = (gx->cpDisp & ~2) | clmpB;

    gx->cpTex = (gx->cpTex & ~1) | clmpT;
    gx->cpTex = (gx->cpTex & ~2) | clmpB;
}

static u32 __GXGetNumXfbLines(u32 efbHt, u32 iScale) {
    u32 count;
    u32 realHt;
    u32 iScaleD;

    count = (efbHt - 1) * 0x100;
    realHt = (count / iScale) + 1;

    iScaleD = iScale;

    if (iScaleD > 0x80 && iScaleD < 0x100) {
        while (iScaleD % 2 == 0) {
            iScaleD /= 2;
        }

        if (efbHt % iScaleD == 0) {
            realHt++;
        }
    }

    if (realHt > 0x400) {
        realHt = 0x400;
    }

    return realHt;
}

u16 GXGetNumXfbLines(u16 efbHeight, f32 yScale) {
    u32 iScale;
    ASSERTMSGLINE(1486, yScale >= 1.0f, "GXGetNumXfbLines: Vertical scale must be >= 1.0");

    iScale = (u32)(256.0f / yScale) & 0x1FF;
    return __GXGetNumXfbLines(efbHeight, iScale);
}

f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight) {
    f32 fScale;
    f32 yScale;
    u32 iScale;
    u32 tgtHt;
    u32 realHt;

    ASSERTMSGLINE(1510, xfbHeight <= 1024, "GXGetYScaleFactor: Display copy only supports up to 1024 lines.\n");
    ASSERTMSGLINE(1512, efbHeight <= xfbHeight, "GXGetYScaleFactor: EFB height should not be greater than XFB height.\n");

    tgtHt = xfbHeight;
    yScale = (f32)xfbHeight / (f32)efbHeight;
    iScale = (u32)(256.0f / yScale) & 0x1FF;
    realHt = __GXGetNumXfbLines(efbHeight, iScale);

    while (realHt > xfbHeight) {
        tgtHt--;
        yScale = (f32)tgtHt / (f32)efbHeight;
        iScale = (u32)(256.0f / yScale) & 0x1FF;
        realHt = __GXGetNumXfbLines(efbHeight, iScale);
    }

    fScale = yScale;
    while (realHt < xfbHeight) {
        fScale = yScale;
        tgtHt++;
        yScale = (f32)tgtHt / (f32)efbHeight;
        iScale = (u32)(256.0f / yScale) & 0x1FF;
        realHt = __GXGetNumXfbLines(efbHeight, iScale);
    }

    return fScale;
}

u32 GXSetDispCopyYScale(f32 vscale) {
    GXData* gx;
    u32 iScale;
    u32 copyYScaleEnable;

    CHECK_GXBEGIN(1557, "GXSetDispCopyYScale");

    ASSERTMSGLINE(1559, vscale >= 1.0f, "GXSetDispCopyYScale: Vertical scale must be >= 1.0");

    iScale = (u32)(256.0f / vscale) & 0x1FF;
    gx = __GXData;

    GX_WRITE_RAS_REG((iScale & 0x1FF) | 0x4E000000);
    copyYScaleEnable = (iScale != 0x100);
    gx->bpSentNot = 0;
    gx->cpDisp = (gx->cpDisp & ~0x400) | (copyYScaleEnable << 10);
    return __GXGetNumXfbLines((((u32)gx->cpDispSize >> 10) & 0x3FF) + 1, iScale);
}

void GXSetCopyClear(GXColor clear_clr, u32 clear_z) {
    u32 regA;
    u32 regGB;

    CHECK_GXBEGIN(1596, "GXSetCopyClear");
    ASSERTMSGLINE(1598, clear_z <= 0xFFFFFF, "GXSetCopyClear: Z clear value is out of range");

    regA = clear_clr.r;
    regA = (regA & ~0xFF00) | ((u32)clear_clr.a << 8);
    regA &= 0xFFFF;
    GX_WRITE_RAS_REG(regA | 0x4F000000);

    regGB = clear_clr.b;
    regGB = (regGB & ~0xFF00) | ((u32)clear_clr.g << 8);
    regGB &= 0xFFFF;
    GX_WRITE_RAS_REG(regGB | 0x50000000);

    GX_WRITE_RAS_REG((clear_z & 0xFFFFFF) | 0x51000000);

    __GXData->bpSentNot = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801A2F9C
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf, const u8 vfilter[7]) {
    const u8* sample;
    u32 msLoc0;
    u32 msLoc1;
    u32 msLoc2;
    u32 msLoc3;
    u32 coeff0;
    u32 coeff1;

    CHECK_GXBEGIN(1641, "GXSetCopyFilter");

    if (aa != 0) {
        sample = &sample_pattern[0][0];
        msLoc0 = (sample[0] & 0xF) | ((sample[1] & 0xF) << 4) | ((sample[2] & 0xF) << 8) | ((sample[3] & 0xF) << 12) |
                 ((sample[4] & 0xF) << 16) | ((sample[5] & 0xF) << 20) | 0x01000000;
        msLoc1 = (sample[6] & 0xF) | ((sample[7] & 0xF) << 4) | ((sample[8] & 0xF) << 8) | ((sample[9] & 0xF) << 12) |
                 ((sample[10] & 0xF) << 16) | ((sample[11] & 0xF) << 20) | 0x02000000;
        msLoc2 = (sample[12] & 0xF) | ((sample[13] & 0xF) << 4) | ((sample[14] & 0xF) << 8) | ((sample[15] & 0xF) << 12) |
                 ((sample[16] & 0xF) << 16) | ((sample[17] & 0xF) << 20) | 0x03000000;
        msLoc3 = (sample[18] & 0xF) | ((sample[19] & 0xF) << 4) | ((sample[20] & 0xF) << 8) | ((sample[21] & 0xF) << 12) |
                 ((sample[22] & 0xF) << 16) | ((sample[23] & 0xF) << 20) | 0x04000000;
    } else {
        msLoc0 = 0x01666666;
        msLoc1 = 0x02666666;
        msLoc2 = 0x03666666;
        msLoc3 = 0x04666666;
    }

    GX_WRITE_RAS_REG(msLoc0);
    GX_WRITE_RAS_REG(msLoc1);
    GX_WRITE_RAS_REG(msLoc2);
    GX_WRITE_RAS_REG(msLoc3);

    if (vf != 0) {
        coeff0 = (vfilter[0] & 0x3F) | ((vfilter[1] & 0x3F) << 6) | ((vfilter[2] & 0x3F) << 12) | ((vfilter[3] & 0x3F) << 18) |
                 0x53000000;
        coeff1 = (vfilter[4] & 0x3F) | ((vfilter[5] & 0x3F) << 6) | ((vfilter[6] & 0x3F) << 12) | 0x54000000;
    } else {
        coeff0 = 0x53595000;
        coeff1 = 0x54000015;
    }

    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);
    __GXData->bpSentNot = 0;
}

void GXSetDispCopyGamma(GXGamma gamma) {
    CHECK_GXBEGIN(1741, "GXSetDispCopyGamma");
    __GXData->cpDisp = (__GXData->cpDisp & 0xFFFFFE7F) | ((u32)gamma << 7);
}

#if DEBUG
static void __GXVerifCopy(void* dest, u8 clear) {
    u8 clmpT;
    u8 clmpB;
    u32 x0;
    u32 y0;
    u32 dx;
    u32 dy;

    CHECK_GXBEGIN(1762, "GXCopyDisp");

    clmpT = GET_REG_FIELD(__GXData->cpDisp, 1, 0);
    clmpB = (u32)GET_REG_FIELD(__GXData->cpDisp, 1, 1);
    x0 = GET_REG_FIELD(__GXData->cpDispSrc, 10, 0);
    dx = GET_REG_FIELD(__GXData->cpDispSize, 10, 0) + 1;
    y0 = GET_REG_FIELD(__GXData->cpDispSrc, 10, 10);
    dy = GET_REG_FIELD(__GXData->cpDispSize, 10, 10) + 1;

    ASSERTMSGLINE(1772, clmpT || y0 != 0, "GXCopy: Have to set GX_CLAMP_TOP if source top == 0");
    ASSERTMSGLINE(1774, clmpB || y0 + dy <= 528, "GXCopy: Have to set GX_CLAMP_BOTTOM if source bottom > 528");
    ASSERTMSGLINE(1779, (__GXData->peCtrl & 7) != 3 || clear == 0, "GXCopy: Can not do clear while pixel type is Z");
    
    if ((u32) (__GXData->peCtrl & 7) == 5) {
        ASSERTMSGLINE(1785, clear == 0, "GXCopy: Can not clear YUV framebuffer");
        ASSERTMSGLINE(1787, (x0 & 3) == 0, "GXCopy: Source x is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(1789, (y0 & 3) == 0, "GXCopy: Source y is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(1791, (dx & 3) == 0, "GXCopy: Source width is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(1793, (dy & 3) == 0, "GXCopy: Source height is not multiple of 4 for YUV copy");
    } else {
        ASSERTMSGLINE(1797, (x0 & 1) == 0, "GXCopy: Source x is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(1799, (y0 & 1) == 0, "GXCopy: Source y is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(1801, (dx & 1) == 0, "GXCopy: Source width is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(1803, (dy & 1) == 0, "GXCopy: Source height is not multiple of 2 for RGB copy");
    }

    ASSERTMSGLINE(1807, ((u32)dest & 0x1F) == 0, "GXCopy: Display destination address not 32B aligned");
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801A31E0
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXCopyDisp(void* dest, GXBool clear) {
    GXData* gx;
    u32 reg;
    GXBool changePeCtrl;

    CHECK_GXBEGIN(1833, "GXCopyDisp");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif

    gx = __GXData;
    if (clear) {
        GX_WRITE_U8(0x61);
        GX_WRITE_U32((gx->zmode & 0xFFFFFFF0) | 0xF);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->cmode0 & 0xFFFFFFFC);
    }

    changePeCtrl = FALSE;
    if (!clear) {
        if ((gx->peCtrl & 7) != 3) {
            goto skipPeCtrlWrite;
        }
    }

    if (((gx->peCtrl >> 6) & 1) == 1) {
        changePeCtrl = TRUE;
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->peCtrl & 0xFFFFFFBF);
    }

skipPeCtrlWrite:
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->cpDispSrc);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->cpDispSize);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->cpDispStride);

    reg = (((u32)dest >> 5) & 0xFFFFFF) | 0x4B000000;
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(reg);

    gx->cpDisp = (gx->cpDisp & 0xFFFFF7FF) | ((u32)clear << 11);
    gx->cpDisp = (gx->cpDisp & 0xFFFFBFFF) | 0x4000;
    gx->cpDisp = (gx->cpDisp & 0x00FFFFFF) | 0x52000000;
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->cpDisp);

    if (clear) {
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->zmode);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->cmode0);
    }

    if (changePeCtrl) {
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->peCtrl);
    }

    gx->bpSentNot = 0;
}

void GXCopyTex(void* dest, GXBool clear) {
    u32 reg;
    u32 tempPeCtrl;
    GXBool changePeCtrl;

    CHECK_GXBEGIN(1916, "GXCopyTex");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif
    if (clear) {
        reg = __GXData->zmode;
        reg = (reg & 0xFFFFFFF0) | 0xF;
        GX_WRITE_RAS_REG(reg);

        reg = __GXData->cmode0;
        reg &= 0xFFFFFFFC;
        GX_WRITE_RAS_REG(reg);
    }

    changePeCtrl = FALSE;
    tempPeCtrl = __GXData->peCtrl;

    if (__GXData->cpTexZ && ((tempPeCtrl & 7) != 3)) {
        changePeCtrl = TRUE;
        tempPeCtrl = (tempPeCtrl & 0xFFFFFFF8) | 3;
    }

    if ((clear || ((tempPeCtrl & 7) == 3)) && (((tempPeCtrl >> 6) & 1) == 1)) {
        changePeCtrl = TRUE;
        tempPeCtrl &= 0xFFFFFFBF;
    }

    if (changePeCtrl) {
        GX_WRITE_RAS_REG(tempPeCtrl);
    }

    GX_WRITE_RAS_REG(__GXData->cpTexSrc);
    GX_WRITE_RAS_REG(__GXData->cpTexSize);
    GX_WRITE_RAS_REG(__GXData->cpTexStride);

    reg = (((u32)dest >> 5) & 0xFFFFFF) | 0x4B000000;
    GX_WRITE_RAS_REG(reg);

    __GXData->cpTex = (__GXData->cpTex & 0xFFFFF7FF) | ((u32)clear << 11);
    __GXData->cpTex &= 0xFFFFBFFF;
    __GXData->cpTex = (__GXData->cpTex & 0x00FFFFFF) | 0x52000000;
    GX_WRITE_RAS_REG(__GXData->cpTex);

    if (clear) {
        GX_WRITE_RAS_REG(__GXData->zmode);
        GX_WRITE_RAS_REG(__GXData->cmode0);
    }

    if (changePeCtrl) {
        GX_WRITE_RAS_REG(__GXData->peCtrl);
    }

    __GXData->bpSentNot = 0;
}

void GXClearBoundingBox(void) {
    u32 reg;

    CHECK_GXBEGIN(2003, "GXClearBoundingBox");
    reg = 0x550003FF;
    GX_WRITE_RAS_REG(reg);
    reg = 0x560003FF;
    GX_WRITE_RAS_REG(reg);
    __GXData->bpSentNot = 0;
}

void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom) {
    *left = GX_GET_PE_REG(8);
    *top = GX_GET_PE_REG(10);
    *right = GX_GET_PE_REG(9);
    *bottom = GX_GET_PE_REG(11);
}
