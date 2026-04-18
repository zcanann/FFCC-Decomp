#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "dolphin/gx/__gx.h"

typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

typedef struct __GXTexRegionInt_struct {
    u32 image1;
    u32 image2;
    u16 sizeEven;
    u16 sizeOdd;
    u8 is32bMipmap;
    u8 isCached;
} __GXTexRegionInt;

typedef struct __GXTlutObjInt_struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} __GXTlutObjInt;

typedef struct __GXTlutRegionInt_struct {
    u32 loadTlut1;
    __GXTlutObjInt tlutObj;
} __GXTlutRegionInt;

u8 HW2GXFiltConv[8] = { 0x00, 0x02, 0x04, 0x00, 0x01, 0x03, 0x05, 0x00 };

void* GXGetTexObjUserData(const GXTexObj* obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)obj;

    ASSERTMSGLINE(1075, obj, "Texture Object Pointer is null");
    return t->userData;
}

void GXGetTexObjAll(const GXTexObj* obj, void** image_ptr, u16* width, u16* height, GXTexFmt* format, GXTexWrapMode* wrap_s, GXTexWrapMode* wrap_t, u8* mipmap) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)obj;

    ASSERTMSGLINE(1095, obj, "Texture Object Pointer is null");
    *image_ptr = (void*)(GET_REG_FIELD(t->image3, 21, 0) << 5);
    *width = (u32)GET_REG_FIELD(t->image0, 10, 0) + 1;
    *height = (u32)GET_REG_FIELD(t->image0, 10, 10) + 1;
    *format = t->fmt;
    *wrap_s = GET_REG_FIELD(t->mode0, 2, 0);
    *wrap_t = GET_REG_FIELD(t->mode0, 2, 2);
    *mipmap = (t->flags & 1) == 1;
}

GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1132, to, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 0);
}

GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1138, to, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 2);
}

GXBool GXGetTexObjMipMap(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1144, to, "Texture Object Pointer is null");
    return (t->flags & 1) == 1;
}

void GXGetTexObjLODAll(const GXTexObj* tex_obj, GXTexFilter* min_filt, GXTexFilter* mag_filt, f32* min_lod, f32* max_lod, f32* lod_bias, u8* bias_clamp, u8* do_edge_lod, GXAnisotropy* max_aniso) {
    s16 tmp;
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1166, tex_obj, "Texture Object Pointer is null");
    *min_filt = HW2GXFiltConv[GET_REG_FIELD(t->mode0, 3, 5)];
    *mag_filt = GET_REG_FIELD(t->mode0, 1, 4);
    *min_lod = (u8)t->mode1 / 16.0f;
    *max_lod = (u32)GET_REG_FIELD(t->mode1, 8, 8) / 16.0f;
    tmp = (s32)GET_REG_FIELD(t->mode0, 8, 9);
    *lod_bias = (s8)tmp / 32.0f;
    *bias_clamp = (u32)GET_REG_FIELD(t->mode0, 1, 21);
    *do_edge_lod = !GET_REG_FIELD(t->mode0, 1, 8);
    *max_aniso = GET_REG_FIELD(t->mode0, 2, 19);
}

GXTexFilter GXGetTexObjMinFilt(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1182, tex_obj, "Texture Object Pointer is null");
    return HW2GXFiltConv[GET_REG_FIELD(t->mode0, 3, 5)];
}

GXTexFilter GXGetTexObjMagFilt(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1189, tex_obj, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 1, 4);
}

f32 GXGetTexObjMinLOD(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1195, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode1, 8, 0) / 16.0f;
}

f32 GXGetTexObjMaxLOD(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1201, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode1, 8, 8) / 16.0f;
}

f32 GXGetTexObjLODBias(const GXTexObj* tex_obj) {
    s16 tmp;
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1208, tex_obj, "Texture Object Pointer is null");
    tmp = (s32)GET_REG_FIELD(t->mode0, 8, 9);
    return (s8)tmp / 32.0f;
}

GXBool GXGetTexObjBiasClamp(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1215, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode0, 1, 21);
}

GXBool GXGetTexObjEdgeLOD(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1221, tex_obj, "Texture Object Pointer is null");
    return !GET_REG_FIELD(t->mode0, 1, 8);
}

GXAnisotropy GXGetTexObjMaxAniso(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1227, tex_obj, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 19);
}

u32 GXGetTexObjTlut(const GXTexObj* tex_obj) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)tex_obj;

    ASSERTMSGLINE(1233, tex_obj, "Texture Object Pointer is null");
    return t->tlutName;
}

void GXGetTlutObjAll(const GXTlutObj* tlut_obj, void** data, GXTlutFmt* format, u16* numEntries) {
    const __GXTlutObjInt* t = (const __GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1382, tlut_obj, "TLut Object Pointer is null");
    *data = (void*)(GET_REG_FIELD(t->loadTlut0, 21, 0) << 5);
    *format = GET_REG_FIELD(t->tlut, 2, 10);
    *numEntries = t->numEntries;
}

void* GXGetTlutObjData(const GXTlutObj* tlut_obj) {
    const __GXTlutObjInt* t = (const __GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1391, tlut_obj, "Texture Object Pointer is null");
    return (void*)(GET_REG_FIELD(t->loadTlut0, 21, 0) << 5);
}

GXTlutFmt GXGetTlutObjFmt(const GXTlutObj* tlut_obj) {
    const __GXTlutObjInt* t = (const __GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1398, tlut_obj, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->tlut, 2, 10);
}

u16 GXGetTlutObjNumEntries(const GXTlutObj* tlut_obj) {
    const __GXTlutObjInt* t = (const __GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1405, tlut_obj, "Texture Object Pointer is null");
    return t->numEntries;
}

void GXGetTexRegionAll(const GXTexRegion* region, u8* is_cached, u8* is_32b_mipmap, u32* tmem_even, u32* size_even, u32* tmem_odd, u32* size_odd) {
    const __GXTexRegionInt* t = (const __GXTexRegionInt*)region;

    ASSERTMSGLINE(1601, region, "TexRegion Object Pointer is null");
    *tmem_even = GET_REG_FIELD(t->image1, 15, 0) << 5;
    *tmem_odd = GET_REG_FIELD(t->image2, 15, 0) << 5;
    if (t->isCached) {
        switch (GET_REG_FIELD(t->image1, 3, 15)) {
        case 3:
            *size_even = 0x8000;
            break;
        case 4:
            *size_even = 0x20000;
            break;
        case 5:
            *size_even = 0x80000;
            break;
        default:
            *size_even = 0;
            break;
        }

        switch (GET_REG_FIELD(t->image2, 3, 15)) {
        case 3:
            *size_odd = 0x8000;
            break;
        case 4:
            *size_odd = 0x20000;
            break;
        case 5:
            *size_odd = 0x80000;
            break;
        default:
            *size_odd = 0;
            break;
        }
    } else {
        *size_even = t->sizeEven << 5;
        *size_odd = t->sizeOdd << 5;
    }

    *is_32b_mipmap = t->is32bMipmap;
    *is_cached = t->isCached;
}

void GXGetTlutRegionAll(const GXTlutRegion* region, u32* tmem_addr, GXTlutSize* tlut_size) {
    const __GXTlutRegionInt* t = (const __GXTlutRegionInt*)region;

    ASSERTMSGLINE(1682, region, "TLutRegion Object Pointer is null");
    *tmem_addr = (GET_REG_FIELD(t->loadTlut1, 10, 0) << 9) + 0x80000;
    *tlut_size = GET_REG_FIELD(t->loadTlut1, 11, 10);
}
