#include "ffcc/p_chara_viewer.h"
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
extern "C" void SetFog__8CGraphicFii(void*, int, int);
extern "C" void SetAmbient__9CLightPcsF8_GXColor(void*, void*);
extern "C" void SetNumDiffuse__9CLightPcsFUl(void*, unsigned long);
extern "C" void SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(void*, unsigned long, void*, void*, int);
extern "C" void SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(void*, int, Vec*, unsigned long);
extern "C" void Draw__Q26CChara6CModelFPA4_fii(void*, Mtx, int, int);
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void*, Mtx, int);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(void*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(void*);
extern "C" void CalcSkin__Q26CChara6CModelFv(void*);
extern "C" void SRTToMatrix__5CMathFPA4_fP3SRT(void*, Mtx, void*);
extern "C" void Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE(void*, char*, float, int);
extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
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
extern "C" float FLOAT_80330BF4;
extern "C" float FLOAT_80330BF8;
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
    int pad;
};

extern "C" {
CharaViewerSRT gCharaViewerSrt;
const char* gCharaViewerSpinnerText;
char gCharaViewerSpinnerTextInitialized;
int gCharaViewerSpinnerFrame;
char gCharaViewerSpinnerFrameInitialized;
int gCharaViewerSrtNeedsInit;
char gCharaViewerSrtInitialized;
}

static inline void destroyRef(int* ref)
{
    void (*dtor)(void*, int) = (*reinterpret_cast<void (***)(void*, int)>(ref))[2];
    dtor(ref, 1);
}

template <class T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        int* ref = reinterpret_cast<int*>(ptr);
        int count = ref[1];
        ref[1] = count - 1;
        if ((count - 1 == 0) && (ref != 0)) {
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

static void releaseRef(unsigned char* p, int offset)
{
    int* ref = *(int**)(p + offset);
    if (ref != 0) {
        int count = ref[1];
        ref[1] = count - 1;
        if ((count - 1 == 0) && (ref != 0)) {
            destroyRef(ref);
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

static inline CMemory::CStage*& ViewerModelStage(CCharaPcs* self)
{
    return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(self) + 0xCC);
}

static inline CMemory::CStage*& ViewerTextureStage(CCharaPcs* self)
{
    return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(self) + 0xD0);
}

static inline CMemory::CStage*& ViewerAnimStage(CCharaPcs* self)
{
    return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(self) + 0xD4);
}

static inline CChara::CModel*& ViewerModel(CCharaPcs* self, int index)
{
    return reinterpret_cast<CChara::CModel**>(reinterpret_cast<unsigned char*>(self) + 0x190)[index];
}

static inline CChara::CAnim*& ViewerAnim(CCharaPcs* self, int index)
{
    return reinterpret_cast<CChara::CAnim**>(reinterpret_cast<unsigned char*>(self) + 0x198)[index];
}

static inline CTextureSet*& ViewerTextureSet(CCharaPcs* self, int index)
{
    return reinterpret_cast<CTextureSet**>(reinterpret_cast<unsigned char*>(self) + 0x2B0)[index];
}

static inline CChara::CAnim*& ViewerSavedAnim(CCharaPcs* self)
{
    return *reinterpret_cast<CChara::CAnim**>(reinterpret_cast<unsigned char*>(self) + 0x1A0);
}

static inline CChara::CAnim*& ViewerAnimBank(CCharaPcs* self, int index)
{
    return reinterpret_cast<CChara::CAnim**>(reinterpret_cast<unsigned char*>(self) + 0x1B0)[index];
}

static inline CTextureSet*& ViewerBackTextureSet(CCharaPcs* self)
{
    return *reinterpret_cast<CTextureSet**>(reinterpret_cast<unsigned char*>(self) + 0x2B8);
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

static const char s_p_chara_viewer_cpp[] = "p_chara_viewer.cpp";
static const char s_gpu_profile_fmt[] = "GPU = %f.5%%(C = %.5f%% G = %.5f%%)";
static const char s_no_texture[] = "no texture...";
static const char s_calc_viewer_fmt[] = "CCharaPcs.calcViewer: %s\n";
static const char s_anim_path_fmt[] = "%splot%d.cha";
static const char s_frame_speed_fmt[] = "FRAME = %.2f SPEED=%.2f";
static const char s_iframe_fmt[] = "I = %s IFRAME = %.2f %s";
static const char s_cont_fmt[] = "CONT = %d";
static const char s_cpu_profile_fmt[] = "CPU = %.5f%%(M = %.5f%% S = %.5f%%) %dNODES";
static const char s_load_model[] = "CCharaPcs LoadModel";
static const char s_load_texture[] = "CCharaPcs LoadTexture";
static const char s_load_anim[] = "CCharaPcs LoadAnim";
static const char s_default_chm_path[] = "plot/kmitsuru/plot.chm";
static const char s_default_chd_path[] = "plot/kmitsuru/plot.chd";
static const char s_default_cha_path[] = "plot/kmitsuru/plot.cha";
static const char s_default_tex_path[] = "plot/kmitsuru/plot.tex";
static const char s_back_tex_fmt[] = "%sback.tex";

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
    Mtx texMtx;

    if ((*(int*)(p + 0x2B8) != 0) &&
        (reinterpret_cast<CPtrArray<CTexture*>*>(*(unsigned char**)(p + 0x2B8) + 8)->GetSize() != 0)) {
        CTexture* texture =
            (*reinterpret_cast<CPtrArray<CTexture*>*>(*(unsigned char**)(p + 0x2B8) + 8))[0];

        C_MTXOrtho(projMtx, kCharaViewerZero, FLOAT_80330BEC, kCharaViewerZero, FLOAT_80330BF0, kCharaViewerZero,
                   FLOAT_80330BF4);
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
        TextureMan.SetTexture(GX_TEXMAP0, texture);
        PSMTXScale(texMtx, FLOAT_80330BF8 / static_cast<float>(texture->m_width),
                   FLOAT_80330BF8 / static_cast<float>(texture->m_height), FLOAT_80330BF8);
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
        GXPosition3s16(static_cast<short>(texture->m_width), 0, 0);
        GXTexCoord2s16(static_cast<short>(texture->m_width * 2), 0);
        GXPosition3s16(static_cast<short>(texture->m_width), static_cast<short>(texture->m_height), 0);
        GXTexCoord2s16(static_cast<short>(texture->m_width * 2), static_cast<short>(texture->m_height * 2));
        GXPosition3s16(0, static_cast<short>(texture->m_height), 0);
        GXTexCoord2s16(0, static_cast<short>(texture->m_height * 2));
        PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx);
        GXSetProjection(projMtx, GX_PERSPECTIVE);
    }

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
        unsigned char* model = *(unsigned char**)(p + 0x190 + i * 4);
        if (model != 0) {
            if (*(int*)(model + 0xB0) == 0) {
                Printf__8CGraphicFPce(&Graphic, s_no_texture);
            } else {
                CStopWatch watch(reinterpret_cast<char*>(-1));
                watch.Reset();
                watch.Start();
                SetFog__8CGraphicFii(&Graphic, 0, 0);
                SetAmbient__9CLightPcsF8_GXColor(&LightPcs, p + 0xE8);
                SetNumDiffuse__9CLightPcsFUl(&LightPcs, 3);
                for (unsigned int lightIndex = 0; lightIndex < 3; lightIndex++) {
                    SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs, lightIndex, p + 0xF0 + lightIndex * 4,
                                                             p + 0x108 + lightIndex * 12,
                                                             (__cntlzw(2 - lightIndex) >> 5) & 0xFF);
                }

                Vec lightPos;
                PSMTXCopy((const float(*)[4])(model + 8), scratchMtx);
                lightPos.x = scratchMtx[0][3];
                lightPos.y = scratchMtx[1][3];
                lightPos.z = scratchMtx[2][3];
                SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs, 0, &lightPos, 0xFFFFFFFF);

                Draw__Q26CChara6CModelFPA4_fii(model, cameraMtx, 0, 0);
                DrawFur__Q26CChara6CModelFPA4_fi(model, cameraMtx, 0);
                watch.Stop();
                float cpuTime = watch.Get();
                watch.Start();
                _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_chara_viewer_cpp, 0x2A7);
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
extern "C" void calcViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    char pathBuf[256];
    CFile::CHandle* fileHandle;

    if (*(int*)(p + 0x6FC) != 0) {
        releaseRef(p, 0x1A0);
        *(void**)(p + 0x1A0) = *(void**)(p + 0x198);
        addRef(p, 0x1A0);
        *(int*)(p + 0x6FC) = 0;
    }

    if ((*(int*)(p + 0x2BC) != 0) || (*(int*)(p + 0x3C0) != 0) || (*(int*)(p + 0x4C4) != 0) || (*(int*)(p + 0x710) != 0)) {
        if (*(int*)(p + 0x2BC) != 0) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, p + 0x2C0);
            fileHandle = File.Open((char*)(p + 0x2C0), 0, CFile::PRI_LOW);
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

                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                *(void**)(p + 0x190) = __nw__FUlPQ27CMemory6CStagePci(
                    0x124, *(void**)(reinterpret_cast<unsigned char*>(&Chara) + 0x2058),
                    const_cast<char*>(s_p_chara_viewer_cpp), 0xEA);
                if (*(void**)(p + 0x190) != 0) {
                    *(void**)(p + 0x190) = __ct__Q26CChara6CModelFv(*(void**)(p + 0x190));
                }
                Create__Q26CChara6CModelFPvPQ27CMemory6CStage(*(void**)(p + 0x190), File.m_readBuffer, *(void**)(p + 0xCC));
                *(unsigned char*)(*(unsigned char**)(p + 0x190) + 0x10C) = (*(unsigned char*)(*(unsigned char**)(p + 0x190) + 0x10C) & 0xBF) | 0x40;
                File.Close(fileHandle);
            }
            *(int*)(p + 0x2BC) = 0;
        }

        if ((*(int*)(p + 0x5F0) != 0) && (*(void**)(p + 0x190) != 0)) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, p + 0x5F4);
            fileHandle = File.Open((char*)(p + 0x5F4), 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(*(void**)(p + 0x190), File.m_readBuffer, *(void**)(p + 0xCC));
                File.Close(fileHandle);
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
                    sprintf(pathBuf, s_anim_path_fmt, p + 0x3C4, idx);
                    Printf__7CSystemFPce(&System, s_calc_viewer_fmt, pathBuf);
                    fileHandle = File.Open(pathBuf, 0, CFile::PRI_LOW);
                    if (fileHandle != 0) {
                        releaseRef(p, 0x1B0 + idx * 4);
                        File.Read(fileHandle);
                        File.SyncCompleted(fileHandle);
                        *(void**)(p + 0x1B0 + idx * 4) = __nw__FUlPQ27CMemory6CStagePci(
                            0x30, *(void**)(reinterpret_cast<unsigned char*>(&Chara) + 0x2058),
                            const_cast<char*>(s_p_chara_viewer_cpp), 0x124);
                        if (*(void**)(p + 0x1B0 + idx * 4) != 0) {
                            *(void**)(p + 0x1B0 + idx * 4) = __ct__Q26CChara5CAnimFv(*(void**)(p + 0x1B0 + idx * 4));
                        }
                        Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(*(void**)(p + 0x1B0 + idx * 4), File.m_readBuffer, *(void**)(p + 0xD4));
                        File.Close(fileHandle);
                        if (idx == 0) {
                            *(void**)(p + 0x198) = *(void**)(p + 0x1B0);
                            addRef(p, 0x198);
                        }
                        *(int*)(p + 0x1A4) = *(int*)(p + 0x1A4) + 1;
                    }
                }
                *(int*)(p + 0x710) = 0;
            } else {
                Printf__7CSystemFPce(&System, s_calc_viewer_fmt, p + 0x3C4);
                fileHandle = File.Open((char*)(p + 0x3C4), 0, CFile::PRI_LOW);
                if (fileHandle != 0) {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    *(void**)(p + 0x198) = __nw__FUlPQ27CMemory6CStagePci(
                        0x30, *(void**)(reinterpret_cast<unsigned char*>(&Chara) + 0x2058),
                        const_cast<char*>(s_p_chara_viewer_cpp), 0x111);
                    if (*(void**)(p + 0x198) != 0) {
                        *(void**)(p + 0x198) = __ct__Q26CChara5CAnimFv(*(void**)(p + 0x198));
                    }
                    Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(*(void**)(p + 0x198), File.m_readBuffer, *(void**)(p + 0xD4));
                    File.Close(fileHandle);
                }
                *(int*)(p + 0x3C0) = 0;
            }
        }

        if (*(int*)(p + 0x4C4) != 0) {
            Printf__7CSystemFPce(&System, s_calc_viewer_fmt, p + 0x4C8);
            fileHandle = File.Open((char*)(p + 0x4C8), 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                releaseRef(p, 0x2B0);
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                *(void**)(p + 0x2B0) = createTextureSet__9CCharaPcsFPvi(p, File.m_readBuffer, 0);
                File.Close(fileHandle);
            }
            *(int*)(p + 0x4C4) = 0;
        }

        if (*(void**)(p + 0x190) != 0) {
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, -1);
            AttachTextureSet__Q26CChara6CModelFP11CTextureSet(*(void**)(p + 0x190), *(void**)(p + 0x2B0));
        }
    }

    if (gCharaViewerSpinnerTextInitialized == 0) {
        gCharaViewerSpinnerText = kCharaViewerSpinner;
        gCharaViewerSpinnerTextInitialized = 1;
    }
    if (gCharaViewerSpinnerFrameInitialized == 0) {
        gCharaViewerSpinnerFrame = 0;
        gCharaViewerSpinnerFrameInitialized = 1;
    }
    gCharaViewerSpinnerFrame++;
    Printf__8CGraphicFPce(&Graphic, kCharaViewerChoiceFmt,
                          (int)(char)gCharaViewerSpinnerText[(gCharaViewerSpinnerFrame >> 4) % 4],
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

    if ((*(void**)(p + 0x190) != 0) && (*(int*)(p + 0x70C) != 0)) {
        if (*(int*)(p + 0x708) == 0) {
            *(int*)(p + 0x704) = 0;
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, 0);
        } else {
            *(int*)(p + 0x704) = 0;
            float frame = *(float*)(*(unsigned char**)(p + 0x190) + 0xB4);
            float animFrames = (float)*(unsigned short*)(*(unsigned char**)(p + 0x198) + 0x10);
            *(float*)(p + 0x700) = (float)fmod((double)frame, (double)animFrames);
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, 0);
        }
        *(int*)(p + 0x70C) = 0;
    }

    if (((triggerButtons & 0x1000) != 0) && (*(void**)(p + 0x1A0) == 0) && (*(void**)(p + 0x190) != 0)) {
        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190), *(void**)(p + 0x198), -1, -1, -1);
    }

    if ((triggerButtons & 0x800) != 0) {
        *(unsigned int*)(p + 0x6F8) = (__cntlzw(*(unsigned int*)(p + 0x6F8)) >> 5) & 0xFF;
    }
    if ((triggerButtons & 0x400) != 0) {
        *(unsigned int*)(p + 0x6F4) = (__cntlzw(*(unsigned int*)(p + 0x6F4)) >> 5) & 0xFF;
    }

    float frameAdvance;
    if (*(int*)(p + 0x6F4) == 0) {
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
        unsigned char* model = *(unsigned char**)(p + 0x190 + i * 4);
        if (model == 0) {
            continue;
        }

        unsigned char* anim = *(unsigned char**)(p + 0x198 + i * 4);
        if (anim != 0) {
            if ((i == 0) && (*(int*)(p + 0x1A4) != 0)) {
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
                float animFrames = (float)*(unsigned short*)(anim + 0x10);
                if (animFrames <= *(float*)(*(unsigned char**)(p + 0x190) + 0xB4)) {
                    int nextIndex = *(int*)(p + 0x1AC) + 1;
                    int animCount = *(int*)(p + 0x1A4);
                    *(int*)(p + 0x1AC) = nextIndex - (nextIndex / animCount) * animCount;
                    AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(*(void**)(p + 0x190),
                                                                      *(void**)(p + 0x1B0 + *(int*)(p + 0x1AC) * 4),
                                                                      -1, -1, 0);
                    releaseRef(p, 0x198);
                    *(void**)(p + 0x198) = *(void**)(p + 0x1B0 + *(int*)(p + 0x1AC) * 4);
                    addRef(p, 0x198);
                }
            } else if ((i == 0) && (*(int*)(p + 0x708) != 0)) {
                float animFrames = (float)*(unsigned short*)(*(unsigned char**)(p + 0x198) + 0x10);
                if (*(int*)(p + 0x704) == 0) {
                    if (*(float*)(p + 0x700) + animFrames <= *(float*)(model + 0xB4)) {
                        *(int*)(p + 0x704) = 1;
                        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(model, *(void**)(p + 0x1A0), -1, -1, -1);
                    }
                } else {
                    if (animFrames <= *(float*)(model + 0xB4)) {
                        *(int*)(p + 0x704) = 0;
                        AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii(model, *(void**)(p + 0x198), -1, -1, 0);
                    }
                }
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
            } else {
                SetFrame__Q26CChara6CModelFf(*(float*)(model + 0xB4) + frameAdvance, model);
            }
        }

        float translateX = kCharaViewerZero;
        if ((i != 0) && (*(void**)(p + 0x190) != 0)) {
            int frameShift = ViewerModelFrameShift(*(void**)(p + 0x190));
            translateX = static_cast<float>((1 << (15 - frameShift)) / 8);
        }

        if ((i == 0) && (*(int*)(p + 0x5C8) != 0)) {
            *(int*)(p + 0x5C8) = 0;
            CTexAnimSet* texAnimSet = ViewerModelTexAnimSet(model);
            if (texAnimSet != 0) {
                int texAnimFrame = *(int*)(p + 0x5EC);
                int animType = -2;
                if (texAnimFrame >= 0) {
                    animType = -3;
                }
                Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE(
                    texAnimSet, reinterpret_cast<char*>(p + 0x5CC),
                    static_cast<float>((texAnimFrame < 0) ? 0 : texAnimFrame), animType);
            }
        }

        if (gCharaViewerSrtInitialized == 0) {
            gCharaViewerSrtNeedsInit = 1;
            gCharaViewerSrtInitialized = 1;
        }
        if (gCharaViewerSrtNeedsInit != 0) {
            gCharaViewerSrt.transZ = kCharaViewerZero;
            gCharaViewerSrt.transY = kCharaViewerZero;
            gCharaViewerSrt.rotZ = kCharaViewerZero;
            gCharaViewerSrt.rotY = kCharaViewerZero;
            gCharaViewerSrt.rotX = kCharaViewerZero;
            gCharaViewerSrt.scaleZ = kCharaViewerUnitStep;
            gCharaViewerSrt.scaleY = kCharaViewerUnitStep;
            gCharaViewerSrt.scaleX = kCharaViewerUnitStep;
            gCharaViewerSrtNeedsInit = 0;
        }

        float rotY = kCharaViewerZero;
        if (Pad._452_4_ == 0) {
            unsigned int padIndex = (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 31) & 4U);
            rotY = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x2C + padIndex * 0x54);
        }
        gCharaViewerSrt.rotY = gCharaViewerSrt.rotY + rotY;
        gCharaViewerSrt.transX = translateX;

        Mtx modelMtx;
        SRTToMatrix__5CMathFPA4_fP3SRT(&Math, modelMtx, &gCharaViewerSrt);
        SetMatrix__Q26CChara6CModelFPA4_f(model, modelMtx);

        CStopWatch matrixWatch(reinterpret_cast<char*>(-1));
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
            if (*(void**)(p + 0x1A0) != 0) {
                const char* iframeMode = kCharaViewerOff;
                if (*(int*)(p + 0x708) != 0) {
                    iframeMode = kCharaViewerOn;
                }
                const char* iframeState = kCharaViewerKeep;
                if (*(int*)(p + 0x704) == 0) {
                    iframeState = kCharaViewerOrg;
                }
                Printf__8CGraphicFPce(&Graphic, s_iframe_fmt, iframeMode, *(float*)(p + 0x700), iframeState);
            }
            if (*(int*)(p + 0x1A4) != 0) {
                Printf__8CGraphicFPce(&Graphic, s_cont_fmt, *(int*)(p + 0x1AC));
            }
            Printf__8CGraphicFPce(&Graphic, s_cpu_profile_fmt, matrixTime + skinTime, matrixTime, skinTime,
                                  ViewerModelNodeCount(model));
        }
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
    CCharaPcs* self = reinterpret_cast<CCharaPcs*>(param_1);
    unsigned char* p = reinterpret_cast<unsigned char*>(self);
    unsigned int i;
    unsigned int x;
    CColor colorTmp;
    CColor colorCopy;
    CColor white;
    char pathBuf[256];
    CFile::CHandle* fileHandle;
    unsigned char bumpLight[0x138];
    Vec lightPos;
    Vec lightTarget;
    Vec lightDir;

    memset(p + 0xCC, 0, 0x18);
    ViewerModelStage(self) = reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x177000, s_load_model, 0));
    ViewerTextureStage(self) =
        reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x200000, s_load_texture, 0));
    ViewerAnimStage(self) = reinterpret_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, 0x190000, s_load_anim, 0));

    p[0xE8] = 0x3F;
    p[0xE9] = 0x3F;
    p[0xEA] = 0x3F;
    p[0xEB] = 0xFF;
    for (i = 0; i < 3; i++) {
        unsigned char c = (unsigned char)(-((__cntlzw(i) >> 5) & 1) & 0x3F);
        p[0xF0 + i * 4 + 0] = c;
        p[0xF0 + i * 4 + 1] = c;
        p[0xF0 + i * 4 + 2] = c;
        p[0xF0 + i * 4 + 3] = 0xFF;
    }
    *(float*)(p + 0x108) = kCharaViewerZero;
    *(float*)(p + 0x10C) = kCharaViewerZero;
    *(float*)(p + 0x110) = kCharaViewerFineStep;
    *(float*)(p + 0x114) = kCharaViewerZero;
    *(float*)(p + 0x118) = kCharaViewerZero;
    *(float*)(p + 0x11C) = kCharaViewerFineStep;
    *(float*)(p + 0x120) = kCharaViewerZero;
    *(float*)(p + 0x124) = kCharaViewerZero;
    *(float*)(p + 0x128) = kCharaViewerFineStep;

    for (i = 0; i < 5; i++) {
        unsigned char* whiteChannels =
            reinterpret_cast<unsigned char*>(__ct__6CColorFUcUcUcUc(&white, 0xFF, 0xFF, 0xFF, 0xFF));
        __ct__6CColorFv(&colorTmp);
        x = i ^ 0x80000000;
        for (int c = 0; c < 4; c++) {
            double v = (double)(float)(((double)(unsigned int)whiteChannels[c] - kCharaViewerColorWhiteBias) *
                                        ((float)((double)x - kCharaViewerColorCenterBias) * kCharaViewerLerpScale));
            reinterpret_cast<unsigned char*>(&colorTmp)[c] = (unsigned char)(int)v;
        }
        __ct__6CColorFR6CColor(&colorCopy, &colorTmp);
        p[0x12C + i * 4 + 0] = reinterpret_cast<unsigned char*>(&colorCopy)[0];
        p[0x12C + i * 4 + 1] = reinterpret_cast<unsigned char*>(&colorCopy)[1];
        p[0x12C + i * 4 + 2] = reinterpret_cast<unsigned char*>(&colorCopy)[2];
        p[0x12C + i * 4 + 3] = reinterpret_cast<unsigned char*>(&colorCopy)[3];
    }

    unsigned int clearColor = 0x404040FF;
    *(unsigned int*)(p + 0x0C) = 0x404040FF;
    SetCopyClear__8CGraphicF8_GXColori(&Graphic, &clearColor, 0xFFFF);

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
    *(float*)(p + 0x700) = kCharaViewerZero;
    *(int*)(p + 0x704) = 0;
    *(int*)(p + 0x708) = 0;
    *(int*)(p + 0x70C) = 0;
    *(int*)(p + 0x710) = 0;
    *(int*)(p + 0x1A4) = 0;
    *(int*)(p + 0x1A8) = 0;
    *(int*)(p + 0x1AC) = 0;
    for (i = 0; i < 0x40; i++) {
        *(int*)(p + 0x1B0 + i * 4) = 0;
    }

    strcpy((char*)(p + 0x2C0), s_default_chm_path);
    *(int*)(p + 0x2BC) = 1;
    strcpy((char*)(p + 0x5F4), s_default_chd_path);
    *(int*)(p + 0x5F0) = 1;
    strcpy((char*)(p + 0x3C4), s_default_cha_path);
    *(int*)(p + 0x3C0) = 1;
    strcpy((char*)(p + 0x4C8), s_default_tex_path);
    *(int*)(p + 0x4C4) = 1;
    strcpy((char*)(p + 0x5CC), kCharaViewerDefaultModelPath);
    *(int*)(p + 0x5EC) = -1;
    *(int*)(p + 0x5C8) = 1;

    sprintf(pathBuf, s_back_tex_fmt, USBPcs.m_rootPath);
    fileHandle = File.Open(pathBuf, 0, CFile::PRI_LOW);
    if (fileHandle != 0) {
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);
        ViewerBackTextureSet(self) = reinterpret_cast<CTextureSet*>(createTextureSet__9CCharaPcsFPvi(p, File.m_readBuffer, 0));
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
