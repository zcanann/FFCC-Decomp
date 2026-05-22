#include "ffcc/p_chara.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/pad.h"
#include "ffcc/p_light.h"
#include "ffcc/p_usb.h"
#include "ffcc/ptrarray.h"
#include "ffcc/ref.h"
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

extern "C" void SRTToMatrix__5CMathFPA4_fP3SRT(void*, Mtx, void*);
extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void* createTextureSet__9CCharaPcsFPvi(void*, void*, int);
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

struct CharaViewerModelData {
    u8 _pad00[0x08];
    u16 nodeCount;
    u16 meshCount;
    u8 _pad0C[0x28];
    int frameShift;
};

struct CharaViewerModel {
    u8 _pad00[0xA4];
    CharaViewerModelData* data;
    u8 _padA8[0x08];
    CTextureSet* textureSet;
    float currentFrame;
    u8 _padB8[0x18];
    CChara::CAnim* anim;
    CTexAnimSet* texAnimSet;
};

typedef char CharaViewerModel_size_check[(sizeof(CharaViewerModel) == 0xD8) ? 1 : -1];

static inline CharaViewerModel* ViewerModel(CChara::CModel* model)
{
    return reinterpret_cast<CharaViewerModel*>(model);
}

template <class T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        CRef* ref = reinterpret_cast<CRef*>(ptr);
        if (--reinterpret_cast<int*>(ref)[1] == 0) {
            delete ref;
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

static inline float& ViewerModelTime(CChara::CModel* model)
{
    return ViewerModel(model)->currentFrame;
}

static inline CChara::CAnim*& ViewerModelAnim(CChara::CModel* model)
{
    return ViewerModel(model)->anim;
}

static inline CTexAnimSet*& ViewerModelTexAnimSet(CChara::CModel* model)
{
    return ViewerModel(model)->texAnimSet;
}

static inline CTextureSet*& ViewerModelTextureSet(CChara::CModel* model)
{
    return ViewerModel(model)->textureSet;
}

static inline int ViewerModelNodeCount(CChara::CModel* model)
{
    return ViewerModel(model)->data->nodeCount;
}

static inline int ViewerModelFrameShift(CChara::CModel* model)
{
    return ViewerModel(model)->data->frameShift;
}

extern "C" const char s_no_texture____801da7e8[0x188] =
    "no texture...\0\0\0"
    "p_chara_viewer.cpp\0\0"
    "GPU = %f.5%%(C = %.5f%% G = %.5f%%)\0"
    "CCharaPcs.calcViewer: %s\n\0\0\0"
    "%splot%d.cha\0\0\0\0"
    "FRAME = %.2f SPEED=%.2f\0"
    "I = %s IFRAME = %.2f %s\0"
    "CONT = %d\0\0\0"
    "CPU = %.5f%%(M = %.5f%% S = %.5f%%) %dNODES\0"
    "CCharaPcs LoadModel\0"
    "CCharaPcs LoadTexture\0\0\0"
    "CCharaPcs LoadAnim\0\0"
    "plot/kmitsuru/plot.chm\0\0"
    "plot/kmitsuru/plot.chd\0\0"
    "plot/kmitsuru/plot.cha\0\0"
    "plot/kmitsuru/plot.tex\0\0"
    "%sback.tex";
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
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetNumChans(0);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
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
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(GX_FALSE);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXColor color;
        color.r = 0x80;
        color.g = 0x80;
        color.b = 0x80;
        color.a = 0x20;
        GXLoadPosMtxImm(cameraMtx, 0);
        float gridMin = kCharaViewerGridMin;
        float gridMax = kCharaViewerGridMax;

        for (int i = -10; i <= 10; i++) {
            color.a = (i == 0) ? 0x60 : 0x20;
            GXSetChanMatColor(GX_COLOR0A0, color);
            GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 4);
            float x = (float)i * kCharaViewerGridSpacing;
            GXPosition3f32(x, kCharaViewerZero, gridMin);
            GXPosition3f32(x, kCharaViewerZero, gridMax);
            GXPosition3f32(gridMax, kCharaViewerZero, x);
            GXPosition3f32(gridMin, kCharaViewerZero, x);
        }
    }

    for (unsigned int i = 0; i < 2; i++) {
        CChara::CModel* model = self->m_viewerModel[i];
        if (model != 0) {
            if (ViewerModelTextureSet(model) == 0) {
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
                PSMTXCopy((const float(*)[4])(reinterpret_cast<unsigned char*>(model) + 8), scratchMtx);
                lightPos.x = scratchMtx[0][3];
                lightPos.y = scratchMtx[1][3];
                lightPos.z = scratchMtx[2][3];
                LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);

                model->Draw(cameraMtx, 0, 0);
                model->DrawFur(cameraMtx, 0);
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
            System.Printf(const_cast<char*>(s_calc_viewer_fmt), self->m_viewerModelPath);
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
                CChara::CModel* model =
                    new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_viewer_cpp), 0xEA) CChara::CModel;
                self->m_viewerModel[0] = model;
                self->m_viewerModel[0]->Create(File.m_readBuffer, self->m_viewerModelStage);
                *(reinterpret_cast<unsigned char*>(self->m_viewerModel[0]) + 0x10C) =
                    (*(reinterpret_cast<unsigned char*>(self->m_viewerModel[0]) + 0x10C) & 0xBF) | 0x40;
                File.Close(fileHandle);
            }
            self->m_viewerLoadModel = 0;
        }

        if ((self->m_viewerLoadDynamics != 0) && (self->m_viewerModel[0] != 0)) {
            System.Printf(const_cast<char*>(s_calc_viewer_fmt), self->m_viewerDynamicsPath);
            fileHandle = File.Open(self->m_viewerDynamicsPath, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                self->m_viewerModel[0]->CreateDynamics(File.m_readBuffer, self->m_viewerModelStage);
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

            if (self->m_viewerLoadAnim != 0) {
                System.Printf(const_cast<char*>(s_calc_viewer_fmt), self->m_viewerAnimPath);
                fileHandle = File.Open(self->m_viewerAnimPath, 0, CFile::PRI_LOW);
                if (fileHandle != 0) {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    CChara::CAnim* anim =
                        new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_viewer_cpp), 0x111) CChara::CAnim;
                    self->m_viewerAnim[0] = anim;
                    self->m_viewerAnim[0]->Create(File.m_readBuffer, self->m_viewerAnimStage);
                    File.Close(fileHandle);
                }
                self->m_viewerLoadAnim = 0;
            } else {
                for (i = 0; i < static_cast<unsigned int>(self->m_viewerAnimRequestedCount); i++) {
                    unsigned int idx = static_cast<unsigned int>(self->m_viewerAnimLoadedCount);
                    sprintf(pathBuf, s_anim_path_fmt, self->m_viewerAnimPath, idx);
                    System.Printf(const_cast<char*>(s_calc_viewer_fmt), pathBuf);
                    fileHandle = File.Open(pathBuf, 0, CFile::PRI_LOW);
                    if (fileHandle != 0) {
                        ReleaseShared(self->m_viewerAnimBank[idx]);
                        File.Read(fileHandle);
                        File.SyncCompleted(fileHandle);
                        CChara::CAnim* anim =
                            new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_viewer_cpp), 0x124) CChara::CAnim;
                        self->m_viewerAnimBank[idx] = anim;
                        self->m_viewerAnimBank[idx]->Create(File.m_readBuffer, self->m_viewerAnimStage);
                        File.Close(fileHandle);
                        if (idx == 0) {
                            self->m_viewerAnim[0] = self->m_viewerAnimBank[0];
                            AddSharedRef(self->m_viewerAnim[0]);
                        }
                        self->m_viewerAnimLoadedCount = self->m_viewerAnimLoadedCount + 1;
                    }
                }
                self->m_viewerLoadAnimContinuous = 0;
            }
        }

        if (self->m_viewerLoadTexture != 0) {
            System.Printf(const_cast<char*>(s_calc_viewer_fmt), self->m_viewerTexturePath);
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
            self->m_viewerModel[0]->AttachAnim(self->m_viewerAnim[0], -1, -1, -1);
            self->m_viewerModel[0]->AttachTextureSet(self->m_viewerTextureSet[0]);
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
        heldButtons = Pad.GetPadInputs()[0].button[0];
    }
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        triggerButtons = 0;
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        triggerButtons = Pad.GetPadInputs()[0].buttonDown[0];
    }

    if ((self->m_viewerModel[0] != 0) && (self->m_viewerResetIFrame != 0)) {
        if (self->m_viewerIFrameEnabled == 0) {
            self->m_viewerSavedAnimState = 0;
            self->m_viewerModel[0]->AttachAnim(self->m_viewerAnim[0], -1, -1, 0);
        } else {
            self->m_viewerSavedAnimState = 0;
            float frame = ViewerModelTime(self->m_viewerModel[0]);
            float animFrames = static_cast<float>(*reinterpret_cast<unsigned short*>(
                reinterpret_cast<unsigned char*>(self->m_viewerAnim[0]) + 0x10));
            self->m_viewerSavedFrame = static_cast<float>(fmod(static_cast<double>(frame), static_cast<double>(animFrames)));
            self->m_viewerModel[0]->AttachAnim(self->m_viewerAnim[0], -1, -1, 0);
        }
        self->m_viewerResetIFrame = 0;
    }

    if (((triggerButtons & 0x1000) != 0) && (self->m_viewerSavedAnim == 0) && (self->m_viewerModel[0] != 0)) {
        self->m_viewerModel[0]->AttachAnim(self->m_viewerAnim[0], -1, -1, -1);
    }

    if ((triggerButtons & 0x800) != 0) {
        self->m_viewerDrawGrid = (__cntlzw(self->m_viewerDrawGrid) >> 5) & 0xFF;
    }
    if ((triggerButtons & 0x400) != 0) {
        self->m_viewerStepMode = (__cntlzw(self->m_viewerStepMode) >> 5) & 0xFF;
    }

    float frameAdvance;
    if (self->m_viewerStepMode != 0) {
        float offsetA = kCharaViewerZero;
        if ((triggerButtons & 0x100) != 0) {
            offsetA = kCharaViewerUnitStep;
        }
        float offsetB = kCharaViewerZero;
        if ((triggerButtons & 0x200) != 0) {
            offsetB = kCharaViewerFineStep;
        }
        frameAdvance = kCharaViewerZero + offsetA + offsetB;
    } else {
        float deltaY = kCharaViewerUnitStep;
        if ((heldButtons & 0x200) != 0) {
            deltaY = kCharaViewerFineStep;
        }
        float speedScale = kCharaViewerUnitStep;
        if ((heldButtons & 0x100) != 0) {
            speedScale = kCharaViewerLerpScale;
        }
        frameAdvance = deltaY * speedScale;
    }

    for (unsigned int i = 0; i < 2; i++) {
        CChara::CModel* model = self->m_viewerModel[i];
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
                model->SetFrame(ViewerModelTime(model) + frameAdvance);
                float animFrames = (float)*(unsigned short*)(anim + 0x10);
                if (animFrames <= ViewerModelTime(self->m_viewerModel[0])) {
                    int nextIndex = self->m_viewerAnimLoopIndex + 1;
                    int animCount = self->m_viewerAnimLoadedCount;
                    self->m_viewerAnimLoopIndex = nextIndex - (nextIndex / animCount) * animCount;
                    self->m_viewerModel[0]->AttachAnim(self->m_viewerAnimBank[self->m_viewerAnimLoopIndex], -1, -1, 0);
                    ReleaseShared(self->m_viewerAnim[0]);
                    self->m_viewerAnim[0] = self->m_viewerAnimBank[self->m_viewerAnimLoopIndex];
                    AddSharedRef(self->m_viewerAnim[0]);
                }
            } else if ((i == 0) && (self->m_viewerIFrameEnabled != 0)) {
                float animFrames = static_cast<float>(*reinterpret_cast<unsigned short*>(
                    reinterpret_cast<unsigned char*>(self->m_viewerAnim[0]) + 0x10));
                if (self->m_viewerSavedAnimState == 0) {
                    if (self->m_viewerSavedFrame + animFrames <= ViewerModelTime(model)) {
                        self->m_viewerSavedAnimState = 1;
                        model->AttachAnim(self->m_viewerSavedAnim, -1, -1, -1);
                    }
                } else {
                    if (animFrames <= ViewerModelTime(model)) {
                        self->m_viewerSavedAnimState = 0;
                        model->AttachAnim(self->m_viewerAnim[0], -1, -1, 0);
                    }
                }
                model->SetFrame(ViewerModelTime(model) + frameAdvance);
            } else {
                model->SetFrame(ViewerModelTime(model) + frameAdvance);
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
        model->SetMatrix(modelMtx);

        CStopWatch matrixWatch(const_cast<char*>(kCharaViewerNoName));
        matrixWatch.Reset();
        matrixWatch.Start();
        model->CalcMatrix();
        matrixWatch.Stop();
        float matrixTime = matrixWatch.Get();

        matrixWatch.Reset();
        matrixWatch.Start();
        model->CalcSkin();
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
    unsigned int i;
    unsigned int j;

    Chara.Destroy();
    LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(0));
    gCharaPartWorkPtr = 0;

    ReleaseShared(m_viewerSavedAnim);

    i = 0;
    do {
        ReleaseShared(m_viewerModel[i]);
        ReleaseShared(m_viewerAnim[i]);
        ReleaseShared(m_viewerTextureSet[i]);
        i++;
    } while (i < 2);

    ReleaseShared(m_viewerBackTextureSet);

    j = 0;
    do {
        ReleaseShared(m_viewerAnimBank[j]);
        j++;
    } while (j < 0x40);

    Memory.DestroyStage(m_viewerModelStage);
    Memory.DestroyStage(m_viewerTextureStage);
    Memory.DestroyStage(m_viewerAnimStage);
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
    char pathBuf[256];
    CFile::CHandle* fileHandle;

    memset(&self->m_viewerModelStage, 0, 0x18);
    self->m_viewerModelStage = Memory.CreateStage(0x177000, const_cast<char*>(s_load_model), 0);
    self->m_viewerTextureStage = Memory.CreateStage(0x200000, const_cast<char*>(s_load_texture), 0);
    self->m_viewerAnimStage = Memory.CreateStage(0x190000, const_cast<char*>(s_load_anim), 0);

    self->m_viewerAmbientColor.r = 0x3F;
    self->m_viewerAmbientColor.g = 0x3F;
    self->m_viewerAmbientColor.b = 0x3F;
    self->m_viewerAmbientColor.a = 0xFF;

    for (i = 0; i < 3; i++) {
        unsigned char c = (i == 0) ? 0x3F : 0;

        self->m_viewerDiffuseColor[i].r = c;
        self->m_viewerDiffuseColor[i].g = c;
        self->m_viewerDiffuseColor[i].b = c;
        self->m_viewerDiffuseColor[i].a = 0xFF;
        self->m_viewerDiffusePos[i].x = kCharaViewerZero;
        self->m_viewerDiffusePos[i].y = kCharaViewerZero;
        self->m_viewerDiffusePos[i].z = kCharaViewerFineStep;
    }

    for (int colorIndex = 0; colorIndex < 5; colorIndex++) {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor colorTmp;
        float scale = static_cast<float>(colorIndex) * kCharaViewerLerpScale;
        colorTmp.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * scale));
        colorTmp.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.g) * scale));
        colorTmp.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.b) * scale));
        colorTmp.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * scale));
        CColor colorCopy(colorTmp);
        p[0x12C + colorIndex * 4 + 0] = colorCopy.color.r;
        p[0x12C + colorIndex * 4 + 1] = colorCopy.color.g;
        p[0x12C + colorIndex * 4 + 2] = colorCopy.color.b;
        p[0x12C + colorIndex * 4 + 3] = colorCopy.color.a;
    }

    _GXColor clearColor;
    clearColor.r = 0x40;
    clearColor.g = 0x40;
    clearColor.b = 0x40;
    clearColor.a = 0xFF;
    Graphic.SetCopyClear(clearColor, 0xFFFFFF);

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

    CLightPcs::CBumpLight bumpLight;
    bumpLight.m_type = 1;
    bumpLight.m_position.x = kCharaViewerLightPosX;
    bumpLight.m_position.y = kCharaViewerLightPosY;
    bumpLight.m_position.z = kCharaViewerLightPosZ;
    bumpLight.m_targetPosition.x = kCharaViewerLightTargetX;
    bumpLight.m_targetPosition.y = kCharaViewerLightTargetY;
    bumpLight.m_targetPosition.z = kCharaViewerLightTargetZ;
    PSVECSubtract(reinterpret_cast<Vec*>(&bumpLight.m_targetPosition), reinterpret_cast<Vec*>(&bumpLight.m_position),
                  reinterpret_cast<Vec*>(&bumpLight.m_direction));
    PSVECNormalize(reinterpret_cast<Vec*>(&bumpLight.m_direction), reinterpret_cast<Vec*>(&bumpLight.m_direction));
    bumpLight.m_bumpShade[0] = 0x80;
    bumpLight.m_bumpShade[1] = 0x80;
    bumpLight.m_bumpShade[2] = 0;
    bumpLight.m_bumpShade[3] = 0xFF;
    bumpLight.m_offsetX = kCharaViewerZero;
    bumpLight.m_offsetZ = kCharaViewerZero;
    gCharaPartWorkPtr = reinterpret_cast<u8*>(LightPcs.AddBump(
        &bumpLight, static_cast<CLightPcs::TARGET>(0),
        *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&Chara) + 0x2058), 4));

    Chara.Create();
}
