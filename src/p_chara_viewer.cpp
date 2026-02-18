#include "ffcc/p_chara_viewer.h"
#include "ffcc/pad.h"
#include <dolphin/gx.h>
#include "dolphin/mtx.h"

extern "C" int DAT_8032edc0;
extern "C" unsigned char Chara[];
extern "C" unsigned char LightPcs[];
extern "C" unsigned char Memory[];
extern "C" unsigned char Graphic[];
extern "C" unsigned char File[];
extern "C" unsigned char USBPcs[];
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int,
                                                                                unsigned char);
extern "C" void SetFog__8CGraphicFii(void*, int, int);
extern "C" void SetAmbient__9CLightPcsF8_GXColor(void*, void*);
extern "C" void SetNumDiffuse__9CLightPcsFUl(void*, unsigned long);
extern "C" void SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(void*, unsigned long, void*, void*, int);
extern "C" void SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(void*, int, Vec*, unsigned long);
extern "C" void Draw__Q26CChara6CModelFPA4_fii(void*, Mtx, int, int);
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void*, Mtx, int);
extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" int __cntlzw(unsigned int);
extern "C" void Destroy__6CCharaFv(void*);
extern "C" void Create__6CCharaFv(void*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void SetCopyClear__8CGraphicF8_GXColori(void*, void*, int);
extern "C" void* Open__5CFileFPcUlQ25CFile3PRI(void*, char*, unsigned long, int);
extern "C" void Read__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void SyncCompleted__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void Close__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void* createTextureSet__9CCharaPcsFPvi(void*, void*, int);
extern "C" void Printf__7CSystemFPce(void*, const char*, ...);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" void* __ct__Q26CChara6CModelFv(void*);
extern "C" void Create__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void AttachTextureSet__Q26CChara6CModelFP11CTextureSet(void*, void*);
extern "C" void AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(void*, void*, int, int, int);
extern "C" void* __ct__Q26CChara5CAnimFv(void*);
extern "C" void Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" int AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
    void*, void*, int, void*, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void __ct__6CColorFv(void*);
extern "C" void __ct__6CColorFR6CColor(void*, void*);
extern "C" char lbl_801DA7E8[];
extern "C" void* System;
extern "C" float lbl_80330BE8;
extern "C" float lbl_80330BF4;
extern "C" float lbl_80330BF8;
extern "C" float lbl_80330BFC;
extern "C" float lbl_80330C00;
extern "C" float lbl_80330C28;
extern "C" float lbl_80330C2C;
extern "C" float lbl_80330C48;
extern "C" float lbl_80330C4C;
extern "C" float lbl_80330C50;
extern "C" float lbl_80330C54;
extern "C" float lbl_80330C58;
extern "C" float lbl_80330C5C;
extern "C" char lbl_80330C44[];
extern "C" double lbl_80330BE0;
extern "C" double lbl_80330C10;
extern "C" void* memset(void*, int, unsigned long);
extern "C" char* strcpy(char*, const char*);
extern "C" int sprintf(char*, const char*, ...);

static void releaseRef(unsigned char* p, int offset)
{
    int* ref = *(int**)(p + offset);
    if (ref != 0) {
        int count = ref[1];
        ref[1] = count - 1;
        if ((count - 1 == 0) && (ref != 0)) {
            (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
        }
        *(void**)(p + offset) = 0;
    }
}

static void addRef(unsigned char* p, int offset)
{
    int* ref = *(int**)(p + offset);
    if (ref != 0) {
        ref[1] = ref[1] + 1;
    }
}

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
} CameraPcs;

/*
 * --INFO--
 * PAL Address: 0x800BD848
 * PAL Size: 1680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void drawViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    Mtx cameraMtx;
    Mtx scratchMtx;
    Mtx44 projMtx;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx);
    GXSetProjection(projMtx, GX_PERSPECTIVE);

    if (*(int*)(p + 0x6F8) != 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        GXSetZCompLoc(GX_FALSE);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_SPEC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXLoadPosMtxImm(cameraMtx, 0);

        for (int i = -10; i < 11; i++) {
            GXColor color;
            color.r = 0x80;
            color.g = 0x80;
            color.b = 0x80;
            color.a = (i == 0) ? 0x60 : 0x20;
            GXSetChanMatColor(GX_COLOR0A0, color);
            float x = (float)i * lbl_80330BFC;
            GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 4);
            GXPosition3f32(x, lbl_80330BE8, lbl_80330C00);
            GXPosition3f32(x, lbl_80330BE8, lbl_80330BF4);
            GXPosition3f32(lbl_80330BF4, lbl_80330BE8, x);
            GXPosition3f32(lbl_80330C00, lbl_80330BE8, x);
        }
    }

    for (unsigned int i = 0; i < 2; i++) {
        unsigned char* model = *(unsigned char**)(p + 0x190 + i * 4);
        if (model != 0) {
            if (*(int*)(model + 0xB0) == 0) {
                Printf__8CGraphicFPce(Graphic, lbl_801DA7E8);
            } else {
                SetFog__8CGraphicFii(Graphic, 0, 0);
                SetAmbient__9CLightPcsF8_GXColor(LightPcs, p + 0xE8);
                SetNumDiffuse__9CLightPcsFUl(LightPcs, 3);
                for (unsigned int lightIndex = 0; lightIndex < 3; lightIndex++) {
                    SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(LightPcs, lightIndex, p + 0xF0 + lightIndex * 4,
                                                             p + 0x108 + lightIndex * 12,
                                                             (__cntlzw(2 - lightIndex) >> 5) & 0xFF);
                }

                Vec lightPos;
                PSMTXCopy((const float(*)[4])(model + 8), scratchMtx);
                lightPos.x = scratchMtx[0][3];
                lightPos.y = scratchMtx[1][3];
                lightPos.z = scratchMtx[2][3];
                SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(LightPcs, 0, &lightPos, 0xFFFFFFFF);

                Draw__Q26CChara6CModelFPA4_fii(model, cameraMtx, 0, 0);
                DrawFur__Q26CChara6CModelFPA4_fi(model, cameraMtx, 0);
                if (i == 0) {
                    _WaitDrawDone__8CGraphicFPci(Graphic, lbl_801DA7E8 + 0x10, 0x2A7);
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800BDED8
 * PAL Size: 3960b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void calcViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    char pathBuf[256];
    void* fileHandle;

    if (*(int*)(p + 0x6FC) != 0) {
        releaseRef(p, 0x1A0);
        *(void**)(p + 0x1A0) = *(void**)(p + 0x198);
        addRef(p, 0x1A0);
        *(int*)(p + 0x6FC) = 0;
    }

    if ((*(int*)(p + 0x2BC) != 0) || (*(int*)(p + 0x3C0) != 0) || (*(int*)(p + 0x4C4) != 0) || (*(int*)(p + 0x710) != 0)) {
        if (*(int*)(p + 0x2BC) != 0) {
            Printf__7CSystemFPce(System, lbl_801DA7E8 + 0x48, p + 0x2C0);
            fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, (char*)(p + 0x2C0), 0, 0);
            if (fileHandle != 0) {
                releaseRef(p, 0x194);
                releaseRef(p, 0x19C);
                releaseRef(p, 0x2B4);

                *(void**)(p + 0x194) = *(void**)(p + 0x190);
                *(void**)(p + 0x19C) = *(void**)(p + 0x198);
                *(void**)(p + 0x2B4) = *(void**)(p + 0x2B0);
                *(void**)(p + 0x190) = 0;
                *(void**)(p + 0x198) = 0;
                *(void**)(p + 0x2B0) = 0;

                Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
                SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
                *(void**)(p + 0x190) = __nw__FUlPQ27CMemory6CStagePci(0x124, *(void**)(Chara + 0x2058), lbl_801DA7E8 + 0x10, 0xEA);
                if (*(void**)(p + 0x190) != 0) {
                    *(void**)(p + 0x190) = __ct__Q26CChara6CModelFv(*(void**)(p + 0x190));
                }
                Create__Q26CChara6CModelFPvPQ27CMemory6CStage(*(void**)(p + 0x190), *(void**)(File + 8), *(void**)(p + 0xCC));
                *(unsigned char*)(*(unsigned char**)(p + 0x190) + 0x10C) = (*(unsigned char*)(*(unsigned char**)(p + 0x190) + 0x10C) & 0xBF) | 0x40;
                Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
            }
            *(int*)(p + 0x2BC) = 0;
        }

        if ((*(int*)(p + 0x5F0) != 0) && (*(void**)(p + 0x190) != 0)) {
            Printf__7CSystemFPce(System, lbl_801DA7E8 + 0x48, p + 0x5F4);
            fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, (char*)(p + 0x5F4), 0, 0);
            if (fileHandle != 0) {
                Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
                SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
                CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(*(void**)(p + 0x190), *(void**)(File + 8), *(void**)(p + 0xCC));
                Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
            }
            *(int*)(p + 0x5F0) = 0;
        }

        if ((*(int*)(p + 0x3C0) != 0) || (*(int*)(p + 0x710) != 0)) {
            unsigned int i;
            releaseRef(p, 0x198);
            for (i = 0; i < 0x40; i++) {
                releaseRef(p, 0x1B0 + i * 4);
            }
            *(int*)(p + 0x1AC) = 0;
            *(int*)(p + 0x1A4) = 0;

            if (*(int*)(p + 0x3C0) == 0) {
                for (i = 0; i < *(unsigned int*)(p + 0x1A8); i++) {
                    unsigned int idx = *(unsigned int*)(p + 0x1A4);
                    sprintf(pathBuf, lbl_801DA7E8 + 0x64, p + 0x3C4, idx);
                    Printf__7CSystemFPce(System, lbl_801DA7E8 + 0x48, pathBuf);
                    fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, pathBuf, 0, 0);
                    if (fileHandle != 0) {
                        releaseRef(p, 0x1B0 + idx * 4);
                        Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
                        SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
                        *(void**)(p + 0x1B0 + idx * 4) = __nw__FUlPQ27CMemory6CStagePci(0x30, *(void**)(Chara + 0x2058), lbl_801DA7E8 + 0x10, 0x124);
                        if (*(void**)(p + 0x1B0 + idx * 4) != 0) {
                            *(void**)(p + 0x1B0 + idx * 4) = __ct__Q26CChara5CAnimFv(*(void**)(p + 0x1B0 + idx * 4));
                        }
                        Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(*(void**)(p + 0x1B0 + idx * 4), *(void**)(File + 8), *(void**)(p + 0xD4));
                        Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
                        if (idx == 0) {
                            *(void**)(p + 0x198) = *(void**)(p + 0x1B0);
                            addRef(p, 0x198);
                        }
                        *(int*)(p + 0x1A4) = *(int*)(p + 0x1A4) + 1;
                    }
                }
                *(int*)(p + 0x710) = 0;
            } else {
                Printf__7CSystemFPce(System, lbl_801DA7E8 + 0x48, p + 0x3C4);
                fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, (char*)(p + 0x3C4), 0, 0);
                if (fileHandle != 0) {
                    Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
                    SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
                    *(void**)(p + 0x198) = __nw__FUlPQ27CMemory6CStagePci(0x30, *(void**)(Chara + 0x2058), lbl_801DA7E8 + 0x10, 0x111);
                    if (*(void**)(p + 0x198) != 0) {
                        *(void**)(p + 0x198) = __ct__Q26CChara5CAnimFv(*(void**)(p + 0x198));
                    }
                    Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(*(void**)(p + 0x198), *(void**)(File + 8), *(void**)(p + 0xD4));
                    Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
                }
                *(int*)(p + 0x3C0) = 0;
            }
        }

        if (*(int*)(p + 0x4C4) != 0) {
            Printf__7CSystemFPce(System, lbl_801DA7E8 + 0x48, p + 0x4C8);
            fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, (char*)(p + 0x4C8), 0, 0);
            if (fileHandle != 0) {
                releaseRef(p, 0x2B0);
                Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
                SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
                *(void**)(p + 0x2B0) = createTextureSet__9CCharaPcsFPvi(p, *(void**)(File + 8), 0);
                Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
            }
            *(int*)(p + 0x4C4) = 0;
        }

        if (*(void**)(p + 0x190) != 0) {
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, -1);
            AttachTextureSet__Q26CChara6CModelFP11CTextureSet(*(void**)(p + 0x190), *(void**)(p + 0x2B0));
        }
    }

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        if ((Pad._8_2_ & 0x800) != 0) {
            *(unsigned int*)(p + 0x6F8) = (__cntlzw(*(unsigned int*)(p + 0x6F8)) >> 5) & 0xFF;
        }
        if ((Pad._8_2_ & 0x400) != 0) {
            *(unsigned int*)(p + 0x6F4) = (__cntlzw(*(unsigned int*)(p + 0x6F4)) >> 5) & 0xFF;
        }
    }

    if ((*(void**)(p + 0x190) != 0) && (*(int*)(p + 0x70C) != 0)) {
        *(int*)(p + 0x704) = 0;
        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, 0);
        *(int*)(p + 0x70C) = 0;
    }

    if (*(int*)(p + 0x6F4) == 0) {
        float deltaY = lbl_80330BF8;
        if ((Pad._4_2_ & 0x200) != 0) {
            deltaY = lbl_80330C28;
        }
        if ((Pad._4_2_ & 0x100) != 0) {
            deltaY = deltaY * lbl_80330C2C;
        }
        *(float*)(p + 0x700) = *(float*)(p + 0x700) + deltaY;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800BF094
 * PAL Size: 1420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void createViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    unsigned int i;
    unsigned int x;
    unsigned char colorTmp[4];
    unsigned char white[4];
    char pathBuf[256];
    void* fileHandle;
    unsigned char bumpLight[0x138];
    Vec lightPos;
    Vec lightTarget;
    Vec lightDir;

    memset(p + 0xCC, 0, 0x18);
    *(void**)(p + 0xCC) = CreateStage__7CMemoryFUlPci(Memory, 0x177000, lbl_801DA7E8 + 0xDC, 0);
    *(void**)(p + 0xD0) = CreateStage__7CMemoryFUlPci(Memory, 0x200000, lbl_801DA7E8 + 0xF0, 0);
    *(void**)(p + 0xD4) = CreateStage__7CMemoryFUlPci(Memory, 0x190000, lbl_801DA7E8 + 0x108, 0);

    p[0xE8] = 0x3F;
    p[0xE9] = 0x3F;
    p[0xEA] = 0x3F;
    p[0xEB] = 0xFF;
    p[0xF0] = 0x3F;
    p[0xF1] = 0x3F;
    p[0xF2] = 0x3F;
    p[0xF3] = 0xFF;
    p[0xF4] = 0;
    p[0xF5] = 0;
    p[0xF6] = 0;
    p[0xF7] = 0xFF;
    p[0xF8] = 0;
    p[0xF9] = 0;
    p[0xFA] = 0;
    p[0xFB] = 0xFF;
    *(float*)(p + 0x108) = lbl_80330BE8;
    *(float*)(p + 0x10C) = lbl_80330BE8;
    *(float*)(p + 0x110) = lbl_80330C28;
    *(float*)(p + 0x114) = lbl_80330BE8;
    *(float*)(p + 0x118) = lbl_80330BE8;
    *(float*)(p + 0x11C) = lbl_80330C28;
    *(float*)(p + 0x120) = lbl_80330BE8;
    *(float*)(p + 0x124) = lbl_80330BE8;
    *(float*)(p + 0x128) = lbl_80330C28;

    for (i = 0; i < 5; i++) {
        __ct__6CColorFUcUcUcUc(white, 0xFF, 0xFF, 0xFF, 0xFF);
        __ct__6CColorFv(colorTmp);
        x = i ^ 0x80000000;
        for (int c = 0; c < 4; c++) {
            double v = (double)(float)(((double)(unsigned int)white[c] - lbl_80330C10) *
                                        ((float)((double)x - lbl_80330BE0) * lbl_80330C2C));
            colorTmp[c] = (unsigned char)(int)v;
        }
        __ct__6CColorFR6CColor(p + 0x12C + i * 4, colorTmp);
    }

    *(unsigned int*)(p + 0x0C) = 0x404040FF;
    SetCopyClear__8CGraphicF8_GXColori(Graphic, p + 0x0C, 0xFFFF);

    *(int*)(p + 0x190) = 0;
    *(int*)(p + 0x194) = 0;
    *(int*)(p + 0x198) = 0;
    *(int*)(p + 0x19C) = 0;
    *(int*)(p + 0x1A0) = 0;
    *(int*)(p + 0x2B0) = 0;
    *(int*)(p + 0x2B4) = 0;
    *(int*)(p + 0x2B8) = 0;
    *(int*)(p + 0x2BC) = 0;
    *(int*)(p + 0x3C0) = 0;
    *(int*)(p + 0x4C4) = 0;
    *(int*)(p + 0x5C8) = 0;
    *(int*)(p + 0x6F4) = 0;
    *(int*)(p + 0x6F8) = 1;
    *(int*)(p + 0x6FC) = 0;
    *(float*)(p + 0x700) = lbl_80330BE8;
    *(int*)(p + 0x704) = 0;
    *(int*)(p + 0x708) = 0;
    *(int*)(p + 0x70C) = 0;
    *(int*)(p + 0x710) = 0;
    *(int*)(p + 0x1A4) = 0;
    *(int*)(p + 0x1A8) = 0;
    *(int*)(p + 0x1AC) = 0;
    memset(p + 0x1B0, 0, 0x100);

    strcpy((char*)(p + 0x2C0), lbl_801DA7E8 + 0x11C);
    *(int*)(p + 0x2BC) = 1;
    strcpy((char*)(p + 0x5F4), lbl_801DA7E8 + 0x134);
    *(int*)(p + 0x5F0) = 1;
    strcpy((char*)(p + 0x3C4), lbl_801DA7E8 + 0x14C);
    *(int*)(p + 0x3C0) = 1;
    strcpy((char*)(p + 0x4C8), lbl_801DA7E8 + 0x164);
    *(int*)(p + 0x4C4) = 1;
    strcpy((char*)(p + 0x5CC), lbl_80330C44);
    *(int*)(p + 0x5EC) = -1;
    *(int*)(p + 0x5C8) = 1;

    sprintf(pathBuf, lbl_801DA7E8 + 0x17C, *(unsigned int*)(USBPcs + 4));
    fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, pathBuf, 0, 0);
    if (fileHandle != 0) {
        Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
        *(void**)(p + 0x2B8) = createTextureSet__9CCharaPcsFPvi(p, *(void**)(File + 8), 0);
        Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
    }

    __ct__Q29CLightPcs10CBumpLightFv(bumpLight);
    *(int*)(bumpLight + 0x00) = 1;
    lightPos.x = lbl_80330C48;
    lightPos.y = lbl_80330C4C;
    lightPos.z = lbl_80330C50;
    lightTarget.x = lbl_80330C54;
    lightTarget.y = lbl_80330C58;
    lightTarget.z = lbl_80330C5C;
    PSVECSubtract(&lightTarget, &lightPos, &lightDir);
    PSVECNormalize(&lightDir, &lightDir);
    *(unsigned char*)(bumpLight + 0x68) = 0x80;
    *(unsigned char*)(bumpLight + 0x69) = 0x80;
    *(unsigned char*)(bumpLight + 0x6A) = 0;
    *(unsigned char*)(bumpLight + 0x6B) = 0xFF;
    *(float*)(bumpLight + 0x2C) = lbl_80330BE8;
    *(float*)(bumpLight + 0x30) = lbl_80330BE8;
    DAT_8032edc0 = AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
        LightPcs, bumpLight, 0, *(void**)(Chara + 0x2058), 4);

    Create__6CCharaFv(Chara);
}

/*
 * --INFO--
 * PAL Address: 0x800BEE50
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void destroyViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    int* ref;
    int count;
    unsigned int i;

    Destroy__6CCharaFv(Chara);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(LightPcs, 0);
    DAT_8032edc0 = 0;

    ref = *(int**)(p + 0x1A0);
    if (ref != 0) {
        count = ref[1];
        ref[1] = count - 1;
        if ((count - 1 == 0) && (ref != 0)) {
            (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
        }
        *(void**)(p + 0x1A0) = 0;
    }

    i = 0;
    do {
        ref = *(int**)(p + 0x190 + i * 4);
        if (ref != 0) {
            count = ref[1];
            ref[1] = count - 1;
            if ((count - 1 == 0) && (ref != 0)) {
                (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
            }
            *(void**)(p + 0x190 + i * 4) = 0;
        }
        ref = *(int**)(p + 0x198 + i * 4);
        if (ref != 0) {
            count = ref[1];
            ref[1] = count - 1;
            if ((count - 1 == 0) && (ref != 0)) {
                (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
            }
            *(void**)(p + 0x198 + i * 4) = 0;
        }
        ref = *(int**)(p + 0x2B0 + i * 4);
        if (ref != 0) {
            count = ref[1];
            ref[1] = count - 1;
            if ((count - 1 == 0) && (ref != 0)) {
                (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
            }
            *(void**)(p + 0x2B0 + i * 4) = 0;
        }
        i++;
    } while (i < 2);

    ref = *(int**)(p + 0x2B8);
    if (ref != 0) {
        count = ref[1];
        ref[1] = count - 1;
        if ((count - 1 == 0) && (ref != 0)) {
            (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
        }
        *(void**)(p + 0x2B8) = 0;
    }

    i = 0;
    do {
        ref = *(int**)(p + 0x1B0 + i * 4);
        if (ref != 0) {
            count = ref[1];
            ref[1] = count - 1;
            if ((count - 1 == 0) && (ref != 0)) {
                (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
            }
            *(void**)(p + 0x1B0 + i * 4) = 0;
        }
        i++;
    } while (i < 0x40);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xCC));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD0));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD4));
}
