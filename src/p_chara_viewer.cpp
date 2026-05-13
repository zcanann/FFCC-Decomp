#include "ffcc/p_chara.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/pad.h"
#include "ffcc/p_light.h"
#include "ffcc/p_usb.h"
#include "ffcc/ptrarray.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include "ffcc/texanim.h"
extern "C" {
extern u8* gCharaPartWorkPtr;
extern const double kCharaViewerColorCenterBias;
extern const float kCharaViewerZero;
extern const float kCharaViewerGridMax;
extern const float kCharaViewerUnitStep;
extern const float kCharaViewerGridSpacing;
extern const float kCharaViewerGridMin;
extern const double kCharaViewerColorWhiteBias;
extern const float kCharaViewerFineStep;
extern const float kCharaViewerLerpScale;
extern const char kCharaViewerDefaultModelPath[];
extern const float kCharaViewerLightPosX;
extern const float kCharaViewerLightPosY;
extern const float kCharaViewerLightPosZ;
extern const float kCharaViewerLightTargetX;
extern const float kCharaViewerLightTargetY;
extern const float kCharaViewerLightTargetZ;
}

extern "C" const float kCharaViewerUnitStep = 1.0f;
extern "C" const float kCharaViewerGridSpacing = 10.0f;
extern "C" const float kCharaViewerGridMin = 100.0f;
extern "C" const char kCharaViewerNoName[] = "no name";
extern "C" const double kCharaViewerColorWhiteBias = 4503599627370496.0;
extern "C" const char kCharaViewerSpinner[] = "|/-\\";
extern "C" const char kCharaViewerChoiceFmt[] = "[%c] %s";
extern "C" const float kCharaViewerFineStep = -1.0f;
extern "C" const float kCharaViewerLerpScale = 0.25f;
extern "C" const char kCharaViewerOrg[] = "ORG";
extern "C" const char kCharaViewerKeep[] = "KEEP";
extern "C" const char kCharaViewerOn[] = "ON";
extern "C" const char kCharaViewerOff[] = "OFF";
extern "C" const char kCharaViewerDefaultModelPath[] = "m1";
extern "C" const float kCharaViewerLightPosX = -533.0f;
extern "C" const float kCharaViewerLightPosY = -131.0f;
extern "C" const float kCharaViewerLightPosZ = -117.0f;
extern "C" const float kCharaViewerLightTargetX = 4391.0f;
extern "C" const float kCharaViewerLightTargetY = -1864.0f;
extern "C" const float kCharaViewerLightTargetZ = 7194.0f;
extern "C" const char kCharaViewerCRefName[] = "CRef";
extern "C" const float kCharaSharedZeroF = 0.0f;
extern "C" const float kCharaSharedOneF = 1.0f;
extern "C" const double kCharaSharedSignedIntBias = 4503601774854144.0;


#include "ffcc/textureman.h"
#include <dolphin/gx.h>
#include "dolphin/mtx.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int,
                                                                                unsigned char);
extern "C" void Draw__Q26CChara6CModelFPA4_fii(void*, Mtx, int, int);
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void*, Mtx, int);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(void*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(void*);
extern "C" void CalcSkin__Q26CChara6CModelFv(void*);
extern "C" void SRTToMatrix__5CMathFPA4_fP3SRT(void*, Mtx, void*);
extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void Destroy__6CCharaFv(CChara*);
extern "C" void Create__6CCharaFv(CChara*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void SetCopyClear__8CGraphicF8_GXColori(void*, void*, int);
extern "C" void* createTextureSet__9CCharaPcsFPvi(void*, void*, int);
extern "C" void Printf__7CSystemFPce(void*, const char*, ...);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" void* __ct__Q26CChara6CModelFv(void*);
extern "C" void Create__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void AttachTextureSet__Q26CChara6CModelFP11CTextureSet(void*, void*);
extern "C" void AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(void*, void*, int, int, int);
extern "C" void SetFrame__Q26CChara6CModelFf(float, void*);
extern "C" void* __ct__Q26CChara5CAnimFv(void*);
extern "C" void Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" int AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
    void*, void*, int, void*, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void __ct__6CColorFv(void*);
extern "C" void __ct__6CColorFR6CColor(void*, void*);
extern "C" float FLOAT_80330BEC;
extern "C" float FLOAT_80330BF0;
extern "C" double fmod(double, double);

struct CharaViewerSRT {
    float transX;
    float transY;
    float transZ;
    float rotX;
    float rotY;
    float rotZ;
    float scaleX;
    float scaleY;
    float scaleZ;
};

typedef char CharaViewerSRT_size_check[(sizeof(CharaViewerSRT) == 0x24) ? 1 : -1];

static inline void destroyRef(int* ref)
{
    (*reinterpret_cast<void (***)(void*, int)>(ref))[2](ref, 1);
}

template <class T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        int* ref = reinterpret_cast<int*>(ptr);
        if ((--ref[1] == 0) && (ref != 0)) {
            destroyRef(ref);
        }
        ptr = 0;
    }
}

template <class T>
static inline void AddSharedRef(T* ptr)
{
    if (ptr != 0) {
        int* ref = reinterpret_cast<int*>(ptr);
        ref[1] = ref[1] + 1;
    }
}

static inline float& ViewerModelTime(void* model)
{
    return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0xB4);
}

static inline CChara::CAnim*& ViewerModelAnim(void* model)
{
    return *reinterpret_cast<CChara::CAnim**>(reinterpret_cast<unsigned char*>(model) + 0xD0);
}

static inline CTexAnimSet*& ViewerModelTexAnimSet(void* model)
{
    return *reinterpret_cast<CTexAnimSet**>(reinterpret_cast<unsigned char*>(model) + 0xD4);
}

static inline int ViewerModelNodeCount(void* model)
{
    unsigned char* modelData = *reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(model) + 0xA4);
    return *reinterpret_cast<int*>(modelData + 8);
}

static inline int ViewerModelFrameShift(void* model)
{
    unsigned char* modelData = *reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(model) + 0xA4);
    return *reinterpret_cast<int*>(modelData + 0x34);
}

extern "C" const char s_no_texture____801da7e8[];
#define s_no_texture (viewerStrings + 0x0)
#define s_p_chara_viewer_cpp (viewerStrings + 0x10)
#define s_gpu_profile_fmt (viewerStrings + 0x24)
#define s_calc_viewer_fmt (viewerStrings + 0x48)
#define s_anim_path_fmt (viewerStrings + 0x64)
#define s_frame_speed_fmt (viewerStrings + 0x74)
#define s_iframe_fmt (viewerStrings + 0x8C)
#define s_cont_fmt (viewerStrings + 0xA4)
#define s_cpu_profile_fmt (viewerStrings + 0xB0)
#define s_load_model (viewerStrings + 0xDC)
#define s_load_texture (viewerStrings + 0xF0)
#define s_load_anim (viewerStrings + 0x108)
#define s_default_chm_path (viewerStrings + 0x11C)
#define s_default_chd_path (viewerStrings + 0x134)
#define s_default_cha_path (viewerStrings + 0x14C)
#define s_default_tex_path (viewerStrings + 0x164)
#define s_back_tex_fmt (viewerStrings + 0x17C)

/*
 * --INFO--
 * PAL Address: 0x800BD848
 * PAL Size: 1680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::drawViewer()
{
    CCharaPcs* self = this;
    unsigned char* p = reinterpret_cast<unsigned char*>(self);
    register const char* viewerStrings = s_no_texture____801da7e8;
    Mtx cameraMtx;
    Mtx scratchMtx;
    Mtx44 projMtx;
    Mtx texMtx;

    if ((self->m_viewerBackTextureSet != 0) &&
        (reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<unsigned char*>(self->m_viewerBackTextureSet) + 8)->GetSize() != 0)) {
        C_MTXOrtho(projMtx, kCharaViewerZero, FLOAT_80330BEC, kCharaViewerZero, FLOAT_80330BF0, kCharaViewerZero,
                   kCharaViewerGridMax);
        GXSetProjection(projMtx, GX_ORTHOGRAPHIC);
        PSMTXIdentity(cameraMtx);
        GXLoadPosMtxImm(cameraMtx, 0);
        GXSetCurrentMtx(0);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 0, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetNumChans(0);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);
        PSMTXIdentity(cameraMtx);
        GXLoadPosMtxImm(cameraMtx, 0);
        GXSetCullMode(GX_CULL_NONE);
        CTexture* texture =
            (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<unsigned char*>(self->m_viewerBackTextureSet) + 8))[0];
        TextureMan.SetTexture(GX_TEXMAP0, texture);
        unsigned int width = texture->m_width;
        unsigned int height = texture->m_height;
        PSMTXScale(texMtx, kCharaViewerUnitStep / static_cast<float>(width),
                   kCharaViewerUnitStep / static_cast<float>(height), kCharaViewerUnitStep);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3s16(0, 0, 0);
        GXTexCoord2s16(0, 0);
        GXPosition3s16(static_cast<short>(width), 0, 0);
        GXTexCoord2s16(static_cast<short>(width * 2), 0);
        GXPosition3s16(static_cast<short>(width), static_cast<short>(height), 0);
        GXTexCoord2s16(static_cast<short>(width * 2), static_cast<short>(height * 2));
        GXPosition3s16(0, static_cast<short>(height), 0);
        GXTexCoord2s16(0, static_cast<short>(height * 2));
        PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx);
        GXSetProjection(projMtx, GX_PERSPECTIVE);
    }

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx);
    GXSetProjection(projMtx, GX_PERSPECTIVE);

    if (self->m_viewerDrawGrid != 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        GXSetZCompLoc(GX_FALSE);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXLoadPosMtxImm(cameraMtx, 0);

        for (int i = -10; i <= 10; i++) {
            GXColor color = {0x80, 0x80, 0x80, static_cast<u8>((i == 0) ? 0x60 : 0x20)};
            GXSetChanMatColor(GX_COLOR0A0, color);
            float x = (float)i * kCharaViewerGridSpacing;
            GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 4);
            GXPosition3f32(x, kCharaViewerZero, kCharaViewerGridMin);
            GXPosition3f32(x, kCharaViewerZero, kCharaViewerGridMax);
            GXPosition3f32(kCharaViewerGridMax, kCharaViewerZero, x);
            GXPosition3f32(kCharaViewerGridMin, kCharaViewerZero, x);
        }
    }

    for (unsigned int i = 0; i < 2; i++) {
        unsigned char* model = reinterpret_cast<unsigned char*>(self->m_viewerModel[i]);
        if (model != 0) {
            if (*(int*)(model + 0xB0) == 0) {
                Printf__8CGraphicFPce(&Graphic, s_no_texture);
            } else {
                CStopWatch watch(const_cast<char*>(kCharaViewerNoName));
                watch.Reset();
                watch.Start();
                Graphic.SetFog(0, 0);
                LightPcs.SetAmbient(self->m_viewerAmbientColor);
                LightPcs.SetNumDiffuse(3);
                for (unsigned int lightIndex = 0; lightIndex < 3; lightIndex++) {
                    LightPcs.SetDiffuse(lightIndex, self->m_viewerDiffuseColor[lightIndex],
                                        &self->m_viewerDiffusePos[lightIndex],
                                        (__cntlzw(2 - lightIndex) >> 5) & 0xFF);
                }

                Vec lightPos;
                PSMTXCopy((const float(*)[4])(model + 8), scratchMtx);
                lightPos.x = scratchMtx[0][3];
                lightPos.y = scratchMtx[1][3];
                lightPos.z = scratchMtx[2][3];
                LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);

                Draw__Q26CChara6CModelFPA4_fii(model, cameraMtx, 0, 0);
                DrawFur__Q26CChara6CModelFPA4_fi(model, cameraMtx, 0);
                watch.Stop();
                float cpuTime = watch.Get();
                watch.Start();
                Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_viewer_cpp), 0x2A7);
                watch.Stop();
                if (i == 0) {
                    float totalTime = watch.Get();
                    float gpuTime = totalTime - cpuTime;
                    Printf__8CGraphicFPce(&Graphic, s_gpu_profile_fmt, totalTime, cpuTime, gpuTime);
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
void CCharaPcs::calcViewer()
{
    CCharaPcs* self = this;
    unsigned char* p = reinterpret_cast<unsigned char*>(self);
    register const char* viewerStrings = s_no_texture____801da7e8;
    char pathBuf[256];
    CFile::CHandle* fileHandle;

    if (self->m_viewerStoreSavedAnim != 0) {
        ReleaseShared(self->m_viewerSavedAnim);
        self->m_viewerSavedAnim = self->m_viewerAnim[0];
        AddSharedRef(self->m_viewerSavedAnim);
        self->m_viewerStoreSavedAnim = 0;
    }

    if ((self->m_viewerLoadModel != 0) || (self->m_viewerLoadAnim != 0) || (self->m_viewerLoadTexture != 0) ||
        (self->m_viewerLoadAnimContinuous != 0)) {
        if (self->m_viewerLoadModel != 0) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, self->m_viewerModelPath);
            fileHandle = File.Open(self->m_viewerModelPath, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                ReleaseShared(self->m_viewerModel[1]);
                ReleaseShared(self->m_viewerAnim[1]);
                ReleaseShared(self->m_viewerTextureSet[1]);

                self->m_viewerModel[1] = self->m_viewerModel[0];
                self->m_viewerAnim[1] = self->m_viewerAnim[0];
                self->m_viewerTextureSet[1] = self->m_viewerTextureSet[0];
                self->m_viewerModel[0] = 0;
                self->m_viewerAnim[0] = 0;
                self->m_viewerTextureSet[0] = 0;

                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                CChara::CModel* model = reinterpret_cast<CChara::CModel*>(__nw__FUlPQ27CMemory6CStagePci(
                    0x124, CharaPcs.m_stage,
                    const_cast<char*>(s_p_chara_viewer_cpp), 0xEA));
                if (model != 0) {
                    model = reinterpret_cast<CChara::CModel*>(__ct__Q26CChara6CModelFv(model));
                }
                self->m_viewerModel[0] = model;
                Create__Q26CChara6CModelFPvPQ27CMemory6CStage(
                    self->m_viewerModel[0], File.m_readBuffer, self->m_viewerModelStage);
                *(reinterpret_cast<unsigned char*>(self->m_viewerModel[0]) + 0x10C) =
                    (*(reinterpret_cast<unsigned char*>(self->m_viewerModel[0]) + 0x10C) & 0xBF) | 0x40;
                File.Close(fileHandle);
            }
            self->m_viewerLoadModel = 0;
        }

        if ((self->m_viewerLoadDynamics != 0) && (self->m_viewerModel[0] != 0)) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, self->m_viewerDynamicsPath);
            fileHandle = File.Open(self->m_viewerDynamicsPath, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(
                    self->m_viewerModel[0], File.m_readBuffer, self->m_viewerModelStage);
                File.Close(fileHandle);
            }
            self->m_viewerLoadDynamics = 0;
        }

        if ((self->m_viewerLoadAnim != 0) || (self->m_viewerLoadAnimContinuous != 0)) {
            unsigned int i;
            ReleaseShared(self->m_viewerAnim[0]);
            for (i = 0; i < 0x40; i++) {
                ReleaseShared(self->m_viewerAnimBank[i]);
            }
            self->m_viewerAnimLoopIndex = 0;
            self->m_viewerAnimLoadedCount = 0;

            if (self->m_viewerLoadAnim == 0) {
                for (i = 0; i < static_cast<unsigned int>(self->m_viewerAnimRequestedCount); i++) {
                    unsigned int idx = static_cast<unsigned int>(self->m_viewerAnimLoadedCount);
                    sprintf(pathBuf, s_anim_path_fmt, self->m_viewerAnimPath, idx);
                    Printf__7CSystemFPce(&System, s_calc_viewer_fmt, pathBuf);
                    fileHandle = File.Open(pathBuf, 0, CFile::PRI_LOW);
                    if (fileHandle != 0) {
                        File.Read(fileHandle);
                        File.SyncCompleted(fileHandle);
                        CChara::CAnim* anim = reinterpret_cast<CChara::CAnim*>(__nw__FUlPQ27CMemory6CStagePci(
                            0x30, CharaPcs.m_stage,
                            const_cast<char*>(s_p_chara_viewer_cpp), 0x124));
                        if (anim != 0) {
                            anim = reinterpret_cast<CChara::CAnim*>(__ct__Q26CChara5CAnimFv(anim));
                        }
                        self->m_viewerAnimBank[idx] = anim;
                        Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(
                            self->m_viewerAnimBank[idx], File.m_readBuffer, self->m_viewerAnimStage);
                        File.Close(fileHandle);
                        if (idx == 0) {
                            self->m_viewerAnim[0] = self->m_viewerAnimBank[0];
                            AddSharedRef(self->m_viewerAnim[0]);
                        }
                        self->m_viewerAnimLoadedCount = self->m_viewerAnimLoadedCount + 1;
                    }
                }
                self->m_viewerLoadAnimContinuous = 0;
            } else {
                Printf__7CSystemFPce(&System, s_calc_viewer_fmt, self->m_viewerAnimPath);
                fileHandle = File.Open(self->m_viewerAnimPath, 0, CFile::PRI_LOW);
                if (fileHandle != 0) {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    CChara::CAnim* anim = reinterpret_cast<CChara::CAnim*>(__nw__FUlPQ27CMemory6CStagePci(
                        0x30, CharaPcs.m_stage,
                        const_cast<char*>(s_p_chara_viewer_cpp), 0x111));
                    if (anim != 0) {
                        anim = reinterpret_cast<CChara::CAnim*>(__ct__Q26CChara5CAnimFv(anim));
                    }
                    self->m_viewerAnim[0] = anim;
                    Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(
                        self->m_viewerAnim[0], File.m_readBuffer, self->m_viewerAnimStage);
                    File.Close(fileHandle);
                }
                self->m_viewerLoadAnim = 0;
            }
        }

        if (self->m_viewerLoadTexture != 0) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, self->m_viewerTexturePath);
            fileHandle = File.Open(self->m_viewerTexturePath, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                ReleaseShared(self->m_viewerTextureSet[0]);
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                self->m_viewerTextureSet[0] =
                    reinterpret_cast<CTextureSet*>(createTextureSet__9CCharaPcsFPvi(self, File.m_readBuffer, 0));
                File.Close(fileHandle);
            }
            self->m_viewerLoadTexture = 0;
        }

        if (self->m_viewerModel[0] != 0) {
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                self->m_viewerModel[0], self->m_viewerAnim[0], -1, -1, -1);
            AttachTextureSet__Q26CChara6CModelFP11CTextureSet(
                self->m_viewerModel[0], self->m_viewerTextureSet[0]);
        }
    }

    static const char* pFan;
    static char initFan;
    static int alive;
    static char initAlive;
    if (initFan == 0) {
        pFan = kCharaViewerSpinner;
        initFan = 1;
    }
    if (initAlive == 0) {
        alive = 0;
        initAlive = 1;
    }
    alive++;
    Printf__8CGraphicFPce(&Graphic, kCharaViewerChoiceFmt,
                          (int)(char)pFan[(alive >> 4) % 4],
                          USBPcs.m_rootPath);

    unsigned short heldButtons;
    unsigned short triggerButtons;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        heldButtons = 0;
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        heldButtons = Pad._4_2_;
    }
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        triggerButtons = 0;
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        triggerButtons = Pad._8_2_;
    }

    if ((self->m_viewerModel[0] != 0) && (self->m_viewerResetIFrame != 0)) {
        if (self->m_viewerIFrameEnabled == 0) {
            self->m_viewerSavedAnimState = 0;
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                self->m_viewerModel[0], self->m_viewerAnim[0], -1, -1, 0);
        } else {
            self->m_viewerSavedAnimState = 0;
            float frame = ViewerModelTime(self->m_viewerModel[0]);
            float animFrames = static_cast<float>(*reinterpret_cast<unsigned short*>(
                reinterpret_cast<unsigned char*>(self->m_viewerAnim[0]) + 0x10));
            self->m_viewerSavedFrame = static_cast<float>(fmod(static_cast<double>(frame), static_cast<double>(animFrames)));
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                self->m_viewerModel[0], self->m_viewerAnim[0], -1, -1, 0);
        }
        self->m_viewerResetIFrame = 0;
    }

    if (((triggerButtons & 0x1000) != 0) && (self->m_viewerSavedAnim == 0) && (self->m_viewerModel[0] != 0)) {
        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
            self->m_viewerModel[0], self->m_viewerAnim[0], -1, -1, -1);
    }

    if ((triggerButtons & 0x800) != 0) {
        self->m_viewerDrawGrid = (__cntlzw(self->m_viewerDrawGrid) >> 5) & 0xFF;
    }
    if ((triggerButtons & 0x400) != 0) {
        self->m_viewerStepMode = (__cntlzw(self->m_viewerStepMode) >> 5) & 0xFF;
    }

    float frameAdvance;
    if (self->m_viewerStepMode == 0) {
        float deltaY = kCharaViewerUnitStep;
        if ((heldButtons & 0x200) != 0) {
            deltaY = kCharaViewerFineStep;
        }
        float speedScale = kCharaViewerUnitStep;
        if ((heldButtons & 0x100) != 0) {
            speedScale = kCharaViewerLerpScale;
        }
        frameAdvance = deltaY * speedScale;
    } else {
        float offsetA = kCharaViewerZero;
        if ((triggerButtons & 0x100) != 0) {
            offsetA = kCharaViewerUnitStep;
        }
        float offsetB = kCharaViewerZero;
        if ((triggerButtons & 0x200) != 0) {
            offsetB = kCharaViewerFineStep;
        }
        frameAdvance = kCharaViewerZero + offsetA + offsetB;
    }

    for (unsigned int i = 0; i < 2; i++) {
        unsigned char* model = reinterpret_cast<unsigned char*>(self->m_viewerModel[i]);
        if (model == 0) {
            continue;
        }

        float translateX = kCharaViewerZero;
        if ((i != 0) && (self->m_viewerModel[0] != 0)) {
            int frameShift = ViewerModelFrameShift(self->m_viewerModel[0]);
            translateX = static_cast<float>((1 << (15 - frameShift)) / 8);
        }

        if ((i == 0) && (self->m_viewerTexAnimDirty != 0)) {
            self->m_viewerTexAnimDirty = 0;
            CTexAnimSet* texAnimSet = ViewerModelTexAnimSet(model);
            if (texAnimSet != 0) {
                int texAnimFrame = self->m_viewerTexAnimFrame;
                int animType = -2;
                if (texAnimFrame >= 0) {
                    animType = -3;
                }
                texAnimSet->Change(
                    self->m_viewerTexAnimName, static_cast<float>((texAnimFrame < 0) ? 0 : texAnimFrame),
                    static_cast<CTexAnimSet::ANIM_TYPE>(animType));
            }
        }

        unsigned char* anim = reinterpret_cast<unsigned char*>(self->m_viewerAnim[i]);
        if (anim != 0) {
            if ((i == 0) && (self->m_viewerAnimLoadedCount != 0)) {
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
                float animFrames = (float)*(unsigned short*)(anim + 0x10);
                if (animFrames <= ViewerModelTime(self->m_viewerModel[0])) {
                    int nextIndex = self->m_viewerAnimLoopIndex + 1;
                    int animCount = self->m_viewerAnimLoadedCount;
                    self->m_viewerAnimLoopIndex = nextIndex - (nextIndex / animCount) * animCount;
                    AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                        self->m_viewerModel[0], self->m_viewerAnimBank[self->m_viewerAnimLoopIndex], -1, -1, 0);
                    ReleaseShared(self->m_viewerAnim[0]);
                    self->m_viewerAnim[0] = self->m_viewerAnimBank[self->m_viewerAnimLoopIndex];
                    AddSharedRef(self->m_viewerAnim[0]);
                }
            } else if ((i == 0) && (self->m_viewerIFrameEnabled != 0)) {
                float animFrames = static_cast<float>(*reinterpret_cast<unsigned short*>(
                    reinterpret_cast<unsigned char*>(self->m_viewerAnim[0]) + 0x10));
                if (self->m_viewerSavedAnimState == 0) {
                    if (self->m_viewerSavedFrame + animFrames <= *(float*)(model + 0xB4)) {
                        self->m_viewerSavedAnimState = 1;
                        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                            model, self->m_viewerSavedAnim, -1, -1, -1);
                    }
                } else {
                    if (animFrames <= *(float*)(model + 0xB4)) {
                        self->m_viewerSavedAnimState = 0;
                        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(
                            model, self->m_viewerAnim[0], -1, -1, 0);
                    }
                }
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
            } else {
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
            }
        }

        static CharaViewerSRT srt;
        static int bFirst;
        static char init;
        if (init == 0) {
            bFirst = 1;
            init = 1;
        }
        if (bFirst != 0) {
            srt.transZ = kCharaViewerZero;
            srt.transY = kCharaViewerZero;
            srt.rotZ = kCharaViewerZero;
            srt.rotY = kCharaViewerZero;
            srt.rotX = kCharaViewerZero;
            srt.scaleZ = kCharaViewerUnitStep;
            srt.scaleY = kCharaViewerUnitStep;
            srt.scaleX = kCharaViewerUnitStep;
            bFirst = 0;
        }

        float rotY = kCharaViewerZero;
        if (Pad._452_4_ == 0) {
            unsigned int padIndex = (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 31) & 4U);
            rotY = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x2C + padIndex * 0x54);
        }
        srt.rotY = srt.rotY + rotY;
        srt.transX = translateX;

        Mtx modelMtx;
        SRTToMatrix__5CMathFPA4_fP3SRT(&Math, modelMtx, &srt);
        SetMatrix__Q26CChara6CModelFPA4_f(model, modelMtx);

        CStopWatch matrixWatch(const_cast<char*>(kCharaViewerNoName));
        matrixWatch.Reset();
        matrixWatch.Start();
        CalcMatrix__Q26CChara6CModelFv(model);
        matrixWatch.Stop();
        float matrixTime = matrixWatch.Get();

        matrixWatch.Reset();
        matrixWatch.Start();
        CalcSkin__Q26CChara6CModelFv(model);
        matrixWatch.Stop();
        float skinTime = matrixWatch.Get();

        if (i == 0) {
            CChara::CAnim* modelAnim = ViewerModelAnim(model);
            if (modelAnim != 0) {
                float animFrames = (float)*reinterpret_cast<unsigned short*>(
                    reinterpret_cast<unsigned char*>(modelAnim) + 0x10);
                float frame = (float)fmod((double)ViewerModelTime(model), (double)(frameAdvance + animFrames));
                Printf__8CGraphicFPce(&Graphic, s_frame_speed_fmt, frame, frameAdvance);
            }
            if (self->m_viewerSavedAnim != 0) {
                const char* iframeMode = kCharaViewerOff;
                if (self->m_viewerIFrameEnabled != 0) {
                    iframeMode = kCharaViewerOn;
                }
                const char* iframeState = kCharaViewerKeep;
                if (self->m_viewerSavedAnimState == 0) {
                    iframeState = kCharaViewerOrg;
                }
                Printf__8CGraphicFPce(&Graphic, s_iframe_fmt, iframeMode, self->m_viewerSavedFrame, iframeState);
            }
            if (self->m_viewerAnimLoadedCount != 0) {
                Printf__8CGraphicFPce(&Graphic, s_cont_fmt, self->m_viewerAnimLoopIndex);
            }
            Printf__8CGraphicFPce(&Graphic, s_cpu_profile_fmt, matrixTime + skinTime, matrixTime, skinTime,
                                  ViewerModelNodeCount(model));
        }
    }
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
void CCharaPcs::destroyViewer()
{
    unsigned char* p = reinterpret_cast<unsigned char*>(this);
    int* ref;
    unsigned int i;

    Destroy__6CCharaFv(&Chara);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs, 0);
    gCharaPartWorkPtr = 0;

    ref = *(int**)(p + 0x1A0);
    if (ref != 0) {
        if ((--ref[1] == 0) && (ref != 0)) {
            destroyRef(ref);
        }
        *(void**)(p + 0x1A0) = 0;
    }

    i = 0;
    do {
        ref = *(int**)(p + 0x190 + i * 4);
        if (ref != 0) {
            if ((--ref[1] == 0) && (ref != 0)) {
                destroyRef(ref);
            }
            *(void**)(p + 0x190 + i * 4) = 0;
        }
        ref = *(int**)(p + 0x198 + i * 4);
        if (ref != 0) {
            if ((--ref[1] == 0) && (ref != 0)) {
                destroyRef(ref);
            }
            *(void**)(p + 0x198 + i * 4) = 0;
        }
        ref = *(int**)(p + 0x2B0 + i * 4);
        if (ref != 0) {
            if ((--ref[1] == 0) && (ref != 0)) {
                destroyRef(ref);
            }
            *(void**)(p + 0x2B0 + i * 4) = 0;
        }
        i++;
    } while (i < 2);

    ref = *(int**)(p + 0x2B8);
    if (ref != 0) {
        if ((--ref[1] == 0) && (ref != 0)) {
            destroyRef(ref);
        }
        *(void**)(p + 0x2B8) = 0;
    }

    i = 0;
    do {
        ref = *(int**)(p + 0x1B0 + i * 4);
        if (ref != 0) {
            if ((--ref[1] == 0) && (ref != 0)) {
                destroyRef(ref);
            }
            *(void**)(p + 0x1B0 + i * 4) = 0;
        }
        i++;
    } while (i < 0x40);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *(void**)(p + 0xCC));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *(void**)(p + 0xD0));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *(void**)(p + 0xD4));
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
void CCharaPcs::createViewer()
{
    CCharaPcs* self = this;
    unsigned char* p = reinterpret_cast<unsigned char*>(self);
    register const char* viewerStrings = s_no_texture____801da7e8;
    unsigned int i;
    unsigned int x;
    unsigned char colorTmp[4];
    unsigned char colorCopy[4];
    unsigned char white[4];
    char pathBuf[256];
    CFile::CHandle* fileHandle;
    unsigned char bumpLight[0x138];
    Vec lightPos;
    Vec lightTarget;
    Vec lightDir;

    memset(&self->m_viewerModelStage, 0, 0x18);
    self->m_viewerModelStage =
        reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x177000, s_load_model, 0));
    self->m_viewerTextureStage =
        reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x200000, s_load_texture, 0));
    self->m_viewerAnimStage =
        reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x190000, s_load_anim, 0));

    p[0xE8] = 0x3F;
    p[0xE9] = 0x3F;
    p[0xEA] = 0x3F;
    p[0xEB] = 0xFF;
    unsigned char c = (unsigned char)(0x3F & -((__cntlzw(0) >> 5) & 1));
    p[0xF0] = c;
    p[0xF1] = c;
    p[0xF2] = c;
    p[0xF3] = 0xFF;
    *(float*)(p + 0x108) = kCharaViewerZero;
    *(float*)(p + 0x10C) = kCharaViewerZero;
    *(float*)(p + 0x110) = kCharaViewerFineStep;

    c = (unsigned char)(0x3F & -((__cntlzw(1) >> 5) & 1));
    p[0xF4] = c;
    p[0xF5] = c;
    p[0xF6] = c;
    p[0xF7] = 0xFF;
    *(float*)(p + 0x114) = kCharaViewerZero;
    *(float*)(p + 0x118) = kCharaViewerZero;
    *(float*)(p + 0x11C) = kCharaViewerFineStep;

    c = (unsigned char)(0x3F & -((__cntlzw(2) >> 5) & 1));
    p[0xF8] = c;
    p[0xF9] = c;
    p[0xFA] = c;
    p[0xFB] = 0xFF;
    *(float*)(p + 0x120) = kCharaViewerZero;
    *(float*)(p + 0x124) = kCharaViewerZero;
    *(float*)(p + 0x128) = kCharaViewerFineStep;

    for (i = 0; i < 5; i++) {
        unsigned char* whiteChannels =
            reinterpret_cast<unsigned char*>(__ct__6CColorFUcUcUcUc(reinterpret_cast<CColor*>(white), 0xFF, 0xFF, 0xFF, 0xFF));
        __ct__6CColorFv(reinterpret_cast<CColor*>(colorTmp));
        x = i ^ 0x80000000;
        float scale = static_cast<float>(static_cast<double>(x) - kCharaViewerColorCenterBias) * kCharaViewerLerpScale;
        for (int c = 0; c < 4; c++) {
            float channel = static_cast<float>(static_cast<double>(whiteChannels[c]) - kCharaViewerColorWhiteBias);
            colorTmp[c] = static_cast<unsigned char>(static_cast<int>(channel * scale));
        }
        __ct__6CColorFR6CColor(reinterpret_cast<CColor*>(colorCopy), reinterpret_cast<CColor*>(colorTmp));
        p[0x12C + i * 4 + 0] = colorCopy[0];
        p[0x12C + i * 4 + 1] = colorCopy[1];
        p[0x12C + i * 4 + 2] = colorCopy[2];
        p[0x12C + i * 4 + 3] = colorCopy[3];
    }

    _GXColor clearColor;
    clearColor.r = 0x40;
    clearColor.g = 0x40;
    clearColor.b = 0x40;
    clearColor.a = 0xFF;
    SetCopyClear__8CGraphicF8_GXColori(&Graphic, &clearColor, 0xFFFFFF);

    self->m_viewerModel[0] = 0;
    self->m_viewerAnim[0] = 0;
    self->m_viewerTextureSet[0] = 0;
    self->m_viewerModel[1] = 0;
    self->m_viewerAnim[1] = 0;
    self->m_viewerTextureSet[1] = 0;
    self->m_viewerSavedAnim = 0;
    self->m_viewerBackTextureSet = 0;
    self->m_viewerLoadModel = 0;
    self->m_viewerLoadAnim = 0;
    self->m_viewerLoadTexture = 0;
    self->m_viewerTexAnimDirty = 0;
    self->m_viewerStepMode = 0;
    self->m_viewerDrawGrid = 1;
    self->m_viewerStoreSavedAnim = 0;
    self->m_viewerSavedFrame = kCharaViewerZero;
    self->m_viewerSavedAnimState = 0;
    self->m_viewerIFrameEnabled = 0;
    self->m_viewerResetIFrame = 0;
    self->m_viewerLoadAnimContinuous = 0;
    self->m_viewerAnimLoadedCount = 0;
    self->m_viewerAnimRequestedCount = 0;
    self->m_viewerAnimLoopIndex = 0;
    for (i = 0; i < 0x40; i++) {
        self->m_viewerAnimBank[i] = 0;
    }

    strcpy(self->m_viewerModelPath, s_default_chm_path);
    self->m_viewerLoadModel = 1;
    strcpy(self->m_viewerDynamicsPath, s_default_chd_path);
    self->m_viewerLoadDynamics = 1;
    strcpy(self->m_viewerAnimPath, s_default_cha_path);
    self->m_viewerLoadAnim = 1;
    strcpy(self->m_viewerTexturePath, s_default_tex_path);
    self->m_viewerLoadTexture = 1;
    strcpy(self->m_viewerTexAnimName, kCharaViewerDefaultModelPath);
    self->m_viewerTexAnimFrame = -1;
    self->m_viewerTexAnimDirty = 1;

    sprintf(pathBuf, s_back_tex_fmt, USBPcs.m_rootPath);
    fileHandle = File.Open(pathBuf, 0, CFile::PRI_LOW);
    if (fileHandle != 0) {
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);
        self->m_viewerBackTextureSet =
            reinterpret_cast<CTextureSet*>(createTextureSet__9CCharaPcsFPvi(self, File.m_readBuffer, 0));
        File.Close(fileHandle);
    }

    __ct__Q29CLightPcs10CBumpLightFv(bumpLight);
    *(int*)(bumpLight + 0x00) = 1;
    lightPos.x = kCharaViewerLightPosX;
    lightPos.y = kCharaViewerLightPosY;
    lightPos.z = kCharaViewerLightPosZ;
    lightTarget.x = kCharaViewerLightTargetX;
    lightTarget.y = kCharaViewerLightTargetY;
    lightTarget.z = kCharaViewerLightTargetZ;
    PSVECSubtract(&lightTarget, &lightPos, &lightDir);
    PSVECNormalize(&lightDir, &lightDir);
    *(unsigned char*)(bumpLight + 0x68) = 0x80;
    *(unsigned char*)(bumpLight + 0x69) = 0x80;
    *(unsigned char*)(bumpLight + 0x6A) = 0;
    *(unsigned char*)(bumpLight + 0x6B) = 0xFF;
    *(float*)(bumpLight + 0x2C) = kCharaViewerZero;
    *(float*)(bumpLight + 0x30) = kCharaViewerZero;
    gCharaPartWorkPtr = reinterpret_cast<u8*>(AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
        &LightPcs, bumpLight, 0, *(void**)(reinterpret_cast<unsigned char*>(&Chara) + 0x2058), 4));

    Create__6CCharaFv(&Chara);
}
