static const char s_p_chara_ptrarray_grow_error[] = "CPtrArray grow error";
static const char s_p_chara_collection_ptrarray_h[] = "collection_ptrarray.h";

#define FFCC_PTRARRAY_GROW_ERROR s_p_chara_ptrarray_grow_error
#define FFCC_PTRARRAY_FILE s_p_chara_collection_ptrarray_h
#include "ffcc/ptrarray.h"
#include "ffcc/p_chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/color.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/partMng.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/ref.h"
#include "ffcc/sound.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "ffcc/vector.h"

extern const float kCharaZero;
extern const float kCharaOne;
extern const float FLOAT_80330290;
extern const double DOUBLE_80330298;
extern const float FLOAT_803302A4;
extern const float FLOAT_803302A8;
extern const float FLOAT_803302C8;
extern const float FLOAT_803302CC;
extern const float FLOAT_803302D0;
extern const float FLOAT_803302D4;
extern const float FLOAT_803302D8;
extern const float FLOAT_803302DC;
extern const float FLOAT_803302E0;
extern const float kCharaBumpLightPosX;
extern const float kCharaBumpLightPosY;
extern const float kCharaBumpLightPosZ;
extern const float kCharaBumpLightTargetX;
extern const float kCharaBumpLightTargetY;
extern const float kCharaBumpLightTargetZ;

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <math.h>

CCharaPcs CharaPcs;
CLightPcs::CBumpLight* gCharaPartWorkPtr = 0;

extern "C" void create__9CCharaPcsFv(CCharaPcs*);
extern "C" void destroy__9CCharaPcsFv(CCharaPcs*);
extern "C" void calc__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawBefore__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawShadow__9CCharaPcsFv(CCharaPcs*);
extern "C" void draw__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawOverlap__9CCharaPcsFv(CCharaPcs*);
extern "C" void calcAfter__9CCharaPcsFv(CCharaPcs*);
extern "C" void createViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void destroyViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void calcViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawViewer__9CCharaPcsFv(CCharaPcs*);

static const char s_CCharaPcs_GAME[] = "CCharaPcs GAME";
static const char s_CCharaPcs_VIEWER[] = "CCharaPcs VIEWER";
static const char s_CCharaPcs_PART[] = "CCharaPcs PART";

static CProcessTableCallback s_charaTableDescCreate = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDestroy = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescCalc = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDrawBefore = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBefore__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDrawShadow = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDraw = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDrawOverlap = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawOverlap__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescCalcAfter = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescCreateViewer = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDestroyViewer = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescCalcViewer = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescDrawViewer = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescViewerCalcAfter = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescPartCreate = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescPartDestroy = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescPartCalc = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescPartDraw = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CCharaPcsFv)};
static CProcessTableCallback s_charaTableDescPartCalcAfter = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};

CProcessTable PTR_s_CCharaPcs_GAME_[3] = {
    {
        const_cast<char*>(s_CCharaPcs_GAME),
        {
            s_charaTableDescCreate.m_thisOffset, s_charaTableDescCreate.m_virtualOffset, s_charaTableDescCreate.m_function,
            s_charaTableDescDestroy.m_thisOffset, s_charaTableDescDestroy.m_virtualOffset, s_charaTableDescDestroy.m_function,
            s_charaTableDescCalc.m_thisOffset, s_charaTableDescCalc.m_virtualOffset, s_charaTableDescCalc.m_function,
            0x1F, 0,
            s_charaTableDescDrawBefore.m_thisOffset, s_charaTableDescDrawBefore.m_virtualOffset, s_charaTableDescDrawBefore.m_function,
            0x36, 1,
            s_charaTableDescDrawShadow.m_thisOffset, s_charaTableDescDrawShadow.m_virtualOffset, s_charaTableDescDrawShadow.m_function,
            0x30, 1,
            s_charaTableDescDraw.m_thisOffset, s_charaTableDescDraw.m_virtualOffset, s_charaTableDescDraw.m_function,
            0x3B, 1,
            s_charaTableDescDrawOverlap.m_thisOffset, s_charaTableDescDrawOverlap.m_virtualOffset, s_charaTableDescDrawOverlap.m_function,
            0x46, 1,
            s_charaTableDescCalcAfter.m_thisOffset, s_charaTableDescCalcAfter.m_virtualOffset, s_charaTableDescCalcAfter.m_function,
            0x4D, 8,
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_VIEWER),
        {
            s_charaTableDescCreateViewer.m_thisOffset, s_charaTableDescCreateViewer.m_virtualOffset, s_charaTableDescCreateViewer.m_function,
            s_charaTableDescDestroyViewer.m_thisOffset, s_charaTableDescDestroyViewer.m_virtualOffset, s_charaTableDescDestroyViewer.m_function,
            s_charaTableDescCalcViewer.m_thisOffset, s_charaTableDescCalcViewer.m_virtualOffset, s_charaTableDescCalcViewer.m_function,
            0x1F, 0,
            s_charaTableDescDrawViewer.m_thisOffset, s_charaTableDescDrawViewer.m_virtualOffset, s_charaTableDescDrawViewer.m_function,
            0x3B, 1,
            s_charaTableDescViewerCalcAfter.m_thisOffset, s_charaTableDescViewerCalcAfter.m_virtualOffset,
            s_charaTableDescViewerCalcAfter.m_function,
            0x4D, 0,
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_PART),
        {
            s_charaTableDescPartCreate.m_thisOffset, s_charaTableDescPartCreate.m_virtualOffset, s_charaTableDescPartCreate.m_function,
            s_charaTableDescPartDestroy.m_thisOffset, s_charaTableDescPartDestroy.m_virtualOffset, s_charaTableDescPartDestroy.m_function,
            s_charaTableDescPartCalc.m_thisOffset, s_charaTableDescPartCalc.m_virtualOffset, s_charaTableDescPartCalc.m_function,
            0x1F, 0,
            s_charaTableDescPartDraw.m_thisOffset, s_charaTableDescPartDraw.m_virtualOffset, s_charaTableDescPartDraw.m_function,
            0x3B, 1,
            s_charaTableDescPartCalcAfter.m_thisOffset, s_charaTableDescPartCalcAfter.m_virtualOffset, s_charaTableDescPartCalcAfter.m_function,
            0x4D, 0,
        },
    },
};

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

static const char s_p_chara_cpp[] = "p_chara.cpp";
static const char s_CCharaPcs_stage[] = "CCharaPcs";
static const char s_CCharaPcs_amem[] = "CCharaPcs amem";
static const char s_CCharaPcs_amemw[] = "CCharaPcs amemw";
static const char s_CCharaPcs_loadModel[] = "CCharaPcs LoadModel";
static const char s_CCharaPcs_loadTex[] = "CCharaPcs LoadTex";
static const char s_CCharaPcs_loadWepTex[] = "CCharaPcs LoadWepTex";
static const char s_CCharaPcs_loadWepModel[] = "CCharaPcs LoadWepModel";
static const char s_CCharaPcs_loadFaModel[] = "CCharaPcs LoadFaModel";
static const char s_CCharaPcs_loadAnim[] = "CCharaPcs LoadAnim";
static const char s_charaMergePathFmt[] = "dvd/mrg/m%04d_%02d.mrg";
static const char s_charaMergeDupFmt[] =
    "\x43\x43\x68\x61\x72\x61\x50\x63\x73\x2e\x4c\x6f\x61\x64\x4d\x65\x72\x67\x65\x46\x69\x6c\x65\x3a\x20\x25\x64\x82"
    "\xcd\x82\xb7\x82\xc5\x82\xc9\x83\x4c\x83\x83\x83\x62\x83\x56\x83\x93\x83\x4f\x82\xb3\x82\xea\x82\xc4\x82\xa2\x82"
    "\xdc\x82\xb7\x81\x42\x0a";
static const char s_charaMergeOpenFmt[] =
    "\x43\x43\x68\x61\x72\x61\x50\x63\x73\x2e\x4c\x6f\x61\x64\x4d\x65\x72\x67\x65\x46\x69\x6c\x65\x3a\x20\x25\x64\x82"
    "\xcd\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1\x81\x42\x0a";
static const char s_charaMergeDoneFmt[] = "CCharaPcs.LoadMergeFile: %d 0x%08x\n";
static const char s_charaModelLoadAmemFmt[] =
    "\x4d\x65\x72\x67\x65\x3a\x20\x1b\x5b\x33\x32\x6d\x83\x82\x83\x66\x83\x8b\x82\xf0\x41\x4d\x45\x4d\x82\xa9\x82"
    "\xe7\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81\x42\x74\x79\x70\x65\x20\x3d\x20\x25\x64\x20"
    "\x6e\x75\x6d\x62\x65\x72\x20\x3d\x20\x25\x64\x0a\x1b\x5b\x30\x6d";
static const char s_charaModelLoadDvdFmt[] =
    "\x1b\x5b\x33\x31\x6d\x4d\x65\x72\x67\x65\x3a\x20\x83\x82\x83\x66\x83\x8b\x82\xf0\x44\x56\x44\x82\xa9\x82\xe7"
    "\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81\x42\x74\x79\x70\x65\x20\x3d\x20\x25\x64\x20\x6e"
    "\x75\x6d\x62\x65\x72\x20\x3d\x20\x25\x64\x0a\x1b\x5b\x30\x6d";
static const char s_charaDynamicsLoadDvdFmt[] =
    "\x1b\x5b\x33\x31\x6d\x4d\x65\x72\x67\x65\x3a\x20\x83\x5f\x83\x43\x83\x69\x83\x7e\x83\x4e\x83\x58\x82\xf0\x44"
    "\x56\x44\x82\xa9\x82\xe7\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81\x42\x74\x79\x70\x65\x20"
    "\x3d\x20\x25\x64\x20\x6e\x75\x6d\x62\x65\x72\x20\x3d\x20\x25\x64\x0a";
static const char s_charaTexLoadAmemFmt[] =
    "\x4d\x65\x72\x67\x65\x3a\x20\x1b\x5b\x33\x32\x6d\x83\x65\x83\x4e\x83\x58\x83\x60\x83\x83\x82\xf0\x41\x4d\x45"
    "\x4d\x82\xa9\x82\xe7\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81\x42\x74\x79\x70\x65\x20\x3d"
    "\x20\x25\x64\x20\x6e\x75\x6d\x62\x65\x72\x20\x3d\x20\x25\x64\x20\x74\x65\x78\x20\x3d\x20\x25\x64\x0a\x1b\x5b"
    "\x30\x6d";
static const char s_charaTexLoadDvdFmt[] =
    "\x1b\x5b\x33\x31\x6d\x4d\x65\x72\x67\x65\x3a\x20\x83\x65\x83\x4e\x83\x58\x83\x60\x83\x83\x82\xf0\x44\x56\x44"
    "\x82\xa9\x82\xe7\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81\x42\x74\x79\x70\x65\x20\x3d\x20"
    "\x25\x64\x20\x6e\x75\x6d\x62\x65\x72\x20\x3d\x20\x25\x64\x20\x74\x65\x78\x20\x3d\x20\x25\x64\x0a\x1b\x5b\x30"
    "\x6d";
static const char s_charaTexMissingFmt[] =
    "\x83\x65\x83\x4e\x83\x58\x83\x60\x83\x83\x82\xaa\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1\x81\x42\x8f\xea\x8d"
    "\x87\x82\xc9\x82\xe6\x82\xc1\x82\xc4\x82\xcd\x83\x6e\x83\x93\x83\x4f\x82\xb7\x82\xe9\x82\xa9\x82\xe0\x82\xb5"
    "\x82\xea\x82\xdc\x82\xb9\x82\xf1\x81\x42\x25\x73\x0a";
static const char s_charaFreeMergeFmt[] = "CCharaPcs.FreeMergeFile: 0x%08x\n";
static const char s_charaAmemAnimCompactStart[] =
    "\x61\x6d\x65\x6d\x20\x61\x6e\x69\x6d\x20\x83\x4b\x83\x78\x81\x5b\x83\x57"
    "\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93\x8a\x4a\x8e\x6e\x81\x42"
    "\x0a";
static const char s_charaAmemAnimCompactAllocFailed[] =
    "\x1b\x5b\x33\x31\x6d\x61\x6d\x65\x6d\x20\x61\x6e\x69\x6d\x20\x83\x4b\x83"
    "\x78\x81\x5b\x83\x57\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93\x82"
    "\xcc\x82\xbd\x82\xdf\x82\xcc\x83\x65\x83\x93\x83\x7c\x83\x89\x83\x8a\x83"
    "\x6f\x83\x62\x83\x74\x83\x40\x82\xaa\x8a\x6d\x95\xdb\x82\xc5\x82\xab\x82"
    "\xdc\x82\xb9\x82\xf1\x81\x42\x0a\x1b\x5b\x30\x6d";
static const char s_charaAmemAnimCompactCountFmt[] =
    "\x61\x6d\x65\x6d\x20\x61\x6e\x69\x6d\x20\x83\x4b\x83\x78\x81\x5b\x83\x57"
    "\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93\x82\xb5\x82\xe6\x82\xa4"
    "\x82\xc6\x82\xb5\x82\xc4\x82\xa2\x82\xe9\x83\x41\x83\x6a\x83\x81\x5b\x83"
    "\x56\x83\x87\x83\x93\x82\xcc\x91\x8d\x90\x94\x82\xcd\x25\x64\x82\xc5\x82"
    "\xb7\x81\x42\x0a";
static const char s_charaAmemAnimCompactWritebackFmt[] =
    "\x8f\x91\x82\xab\x96\xdf\x82\xb5\x20\x25\x64\x8c\xc2\x20\x25\x78\x20\x2d"
    "\x20\x25\x78\x0a";
static const char s_charaAmemAnimCompactDoneFmt[] =
    "\x61\x6d\x65\x6d\x20\x61\x6e\x69\x6d\x20\x83\x4b\x83\x78\x81\x5b\x83\x57"
    "\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93\x8f\x49\x97\xb9\x81\x42"
    "\x6e\x65\x77\x20\x73\x69\x7a\x65\x20\x3d\x25\x64\x62\x79\x74\x65\x0a";
static const char s_charaAmemCompactFailed[] =
    "\x83\x4b\x83\x78\x81\x5b\x83\x57\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87"
    "\x83\x93\x82\xc9\x8e\xb8\x94\x73\x82\xb5\x82\xbd\x82\xcc\x82\xc5\x81\x41"
    "\x91\x53\x82\xc4\x8f\xc1\x8b\x8e\x82\xb5\x82\xdc\x82\xb7\x81\x42\n";
static const char s_charaBasePathFmt[] = "dvd/char/%s/%s%03d/%s%03d%s";
static const char s_charaAnimPathFmt[] = "dvd/char/%s/%s%03d/%s.cha";
static const char s_charaModelSuffix[] = ".mdl";
static const char s_charaDynamicsSuffix[] = ".dyn";
static const char s_charaTextureSuffix[] = ".tex";
static const char s_charaTextureVariantFmt[] = "%s_%c";
static const char s_mogFurTextureName[] = "mog_hair";
static const char s_charaSetAnimMissingFmt[] = "CCharaPcs missing anim %d %d %d\n";
static const char s_charaLoadAnimLogFmt[] = "CCharaPcs LoadAnim %s %d %d\n";
static const char s_charaLoadPdtLogFmt[] =
    "\x1b[31mMerge: \x83\x82\x83\x93\x83X\x83^\x81[PDT\x82\xf0" "DVD\x82\xa9\x82\xe7\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x82\xdc\x82\xb5\x82\xbd\x81" "Btype = %d number = %d idxTexture = %d\n\x1b[0m";
static const char s_charaReleaseAnimBankFmt[] = "bank release %d %s\n";
static const char s_charaAsyncCancelFmt[] =
    "\x83\x82\x83\x66\x83\x8b\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd"
    "\x8d\x9e\x82\xdd\x92\x86\x82\xc9\x83\x4c\x83\x83\x83\x93\x83\x5a"
    "\x83\x8b\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42\n";
static const char s_charaAsyncCompleteFmt[] =
    "\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x8a\xae"
    "\x97\xb9\n";
static const char s_charaAsyncEntryFmt[] =
    "\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x83\x47"
    "\x83\x93\x83\x67\x83\x8a\x81\x5b\n";
static const char s_charaDumpModelHdr1[] = "MODEL\n";
static const char s_charaDumpModelHdr2[] = " no t num lv mask addr a? a_addr a_size\n";
static const char s_charaDumpLineSep[] = "----------------------------------------\n";
static const char s_charaDumpModelFmt[] = "%3d %1d %3d %3d %08x %08x %d %08x %08x\n";
static const char s_charaDumpTextureHdr1[] = "TEXTURE\n";
static const char s_charaDumpTextureHdr2[] = " no t num t lv mask addr a? a_addr a_size\n";
static const char s_charaDumpTextureFmt[] = "%3d %1d %3d %1d %3d %08x %08x %d %08x %08x\n";
static const char s_charaDumpPdtHdr1[] = "PDT\n";
static const char s_charaDumpPdtHdr2[] = " no t num t pdt hdl lv mask\n";
static const char s_charaDumpPdtFmt[] = "%3d %1d %3d %1d %8d %3d %08x\n";
static const char s_charaDumpAnimHdr1[] = "ANIM\n";
static const char s_charaDumpAnimHdr2[] = " no t num name lv mask addr banksz sum bankaddr\n";
static const char s_charaDumpAnimFmt[] = "%3d %1d %3d %-14s %3d %08x %08x %d %08x\n";
static const char s_charaKindPath0[] = "k00";
static const char s_charaKindPath1[] = "k01";
static const char s_charaKindPath2[] = "k02";
static const char s_charaKindPath3[] = "k03";
static const char s_charaKindPath4[] = "k04";
static const char s_charaKindPath5[] = "k05";
static const char s_charaKindFile[] = "chara";
static const char s_charaKindSuffix[] = "";
static const char* s_charaKindPathParts[][3] = {
    {s_charaKindPath0, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath1, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath2, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath3, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath4, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath5, s_charaKindFile, s_charaKindSuffix},
};

#pragma dont_inline on
template class CPtrArray<CCharaPcs::CLoadPdt*>;
template class CPtrArray<CCharaPcs::CLoadTexture*>;
template class CPtrArray<CCharaPcs::CLoadAnim*>;
template class CPtrArray<CCharaPcs::CLoadModel*>;

STATIC_ASSERT(sizeof(CCharaPcs::CLoadModel) == 0x28);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadAnim) == 0x30);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadTexture) == 0x2C);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadPdt) == 0x20);
STATIC_ASSERT(sizeof(CCharaPcs::CCameraFrame) == 0x20);
STATIC_ASSERT(offsetof(CCharaPcs, m_cameraFrameCount) == 0x04);
STATIC_ASSERT(offsetof(CCharaPcs, m_cameraData) == 0x14);
STATIC_ASSERT(offsetof(CCharaPcs, m_overlapEyePos) == 0x2C);
STATIC_ASSERT(offsetof(CCharaPcs, m_overlapTargetPos) == 0x38);
STATIC_ASSERT(offsetof(CCharaPcs, m_handleList) == 0x4C);
STATIC_ASSERT(offsetof(CCharaPcs, m_stage) == 0xC0);
STATIC_ASSERT(offsetof(CCharaPcs, m_amemStage) == 0xC4);
STATIC_ASSERT(offsetof(CCharaPcs, m_amemWorkStage) == 0xC8);
STATIC_ASSERT(offsetof(CCharaPcs, m_viewerModelStage) == 0xCC);
STATIC_ASSERT(offsetof(CCharaPcs, m_viewerTextureStage) == 0xD0);
STATIC_ASSERT(offsetof(CCharaPcs, m_viewerAnimStage) == 0xD4);
STATIC_ASSERT(offsetof(CCharaPcs, m_weaponTextureStage) == 0xD8);
STATIC_ASSERT(offsetof(CCharaPcs, m_weaponModelStage) == 0xDC);
STATIC_ASSERT(offsetof(CCharaPcs, m_familyModelStage) == 0xE0);
STATIC_ASSERT(offsetof(CCharaPcs, m_charaAllocStage) == 0xE4);

#pragma dont_inline reset

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline CPtrArray<CCharaPcs::CLoadModel*>* LoadModelArray(CCharaPcs* self)
{
    return &self->m_loadModels;
}

static inline CPtrArray<CCharaPcs::CLoadAnim*>* LoadAnimArray(CCharaPcs* self)
{
    return &self->m_loadAnims;
}

static inline CPtrArray<CCharaPcs::CLoadTexture*>* LoadTextureArray(CCharaPcs* self)
{
    return &self->m_loadTextures;
}

static inline CPtrArray<CCharaPcs::CLoadPdt*>* LoadPdtArray(CCharaPcs* self)
{
    return &self->m_loadPdts;
}

static inline u32& FreeMergeMask(CCharaPcs* self)
{
    return self->m_noFreeMergeMask;
}

static inline int& LoadStageMode(CCharaPcs* self)
{
    return self->m_charaAllocStage;
}

static inline u32& LoadStreamCursor(CCharaPcs* self)
{
    return self->m_loadStreamCursor;
}

static inline u32 CurrentSceneId()
{
    return Game.m_currentSceneId;
}

static inline u32& CharaAmemSize()
{
    return Chara.AmemSize();
}

static inline void SetupCharaTevSwap()
{
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
}

static inline void SetupBaseCharaLights(CCharaPcs* self)
{
    Graphic.SetFog(1, 0);
    LightPcs.SetAmbient(self->m_viewerAmbientColor[0]);
    LightPcs.SetNumDiffuse(3);

    for (unsigned long lightIndex = 0; lightIndex < 3; lightIndex++) {
        LightPcs.SetDiffuse(lightIndex, self->m_viewerDiffuseColor[0][lightIndex],
                            &self->m_viewerDiffusePos[lightIndex], static_cast<int>(lightIndex == 2));
    }
}

static inline void* StageBase(CMemory::CStage* stage)
{
    return reinterpret_cast<void*>(stage->m_heapTop);
}

static inline CMemory::CStage* SelectLoadStage(CCharaPcs* self, CMemory::CStage* fallback)
{
    return GET_CHARA_ALLOC_STAGE_S(LoadStageMode(self), fallback);
}

template <typename T>
static inline void ReleaseSharedNonNull(T* ptr)
{
    CRef* ref = reinterpret_cast<CRef*>(ptr);
    if (ref->DecRef() == 0) {
        delete ref;
    }
}

template <typename T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        ReleaseSharedNonNull(ptr);
        ptr = 0;
    }
}

template <typename T>
static inline void AddSharedRef(T* ptr)
{
    if (ptr != 0) {
        reinterpret_cast<CRef*>(ptr)->AddRef();
    }
}

static inline CCharaPcs::CLoadAnim* FindLoadedAnim(CCharaPcs* self, int charaKind, int charaNo, const char* animName)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(LoadAnimArray(self)->GetSize()); i++) {
        CCharaPcs::CLoadAnim* loadAnim = (*LoadAnimArray(self))[i];
        if (reinterpret_cast<int>(loadAnim->m_keyTag) == charaKind &&
            loadAnim->m_keyId == static_cast<unsigned long>(charaNo) &&
            strcmp(animName, loadAnim->m_name) == 0) {
            return loadAnim;
        }
    }

    return 0;
}

static CCharaPcs::CLoadAnim* LoadAnimFromDisk(
    CCharaPcs* self, int charaKind, int charaNo, const char* animName, int mergeFileId, int mergeFlags)
{
    char path[0x100];
    const char** pathParts = s_charaKindPathParts[charaKind];
    sprintf(path, s_charaAnimPathFmt, pathParts[0], pathParts[1], charaNo, animName);

    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle != 0) {
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        void* animBuffer = File.m_readBuffer;
        CChara::CAnim* anim = new (self->m_stage, const_cast<char*>(s_p_chara_cpp), 0x62A) CChara::CAnim;
        anim->Create(animBuffer, self->m_viewerAnimStage);

        CCharaPcs::CLoadAnim* loadAnim = new (self->m_stage, const_cast<char*>(s_p_chara_cpp), 0x62D) CCharaPcs::CLoadAnim;
        loadAnim->m_keyId = charaNo;
        loadAnim->m_keyTag = reinterpret_cast<void*>(charaKind);
        strcpy(loadAnim->m_name, animName);
        loadAnim->m_anim = anim;
        loadAnim->m_mergeFileId = mergeFileId;
        loadAnim->m_mergeFlags = mergeFlags;
        LoadAnimArray(self)->Add(loadAnim);

        File.Close(fileHandle);

        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_charaLoadAnimLogFmt), animName, charaKind, charaNo);
        }

        return loadAnim;
    }

    return 0;
}

static inline void ReleaseHandleAnimSlot(CCharaPcs::CHandle* handle, int slot)
{
    CRef* animRef = handle->m_animSlot[slot];
    if (animRef != 0) {
        ReleaseShared(handle->m_animSlot[slot]);
    }
}

static inline void PruneUnsharedAnimRefs(CCharaPcs* self, CCharaPcs::CLoadAnim* target)
{
    for (int i = LoadAnimArray(self)->GetSize() - 1; i >= 0; i--) {
        CCharaPcs::CLoadAnim* loadAnim = (*LoadAnimArray(self))[static_cast<unsigned long>(i)];
        if (loadAnim->m_mergeFileId >= 0) {
            continue;
        }
        if (loadAnim->GetRef() == 1) {
            if (target == 0 || target == loadAnim) {
                CCharaPcs::CLoadAnim* releasedAnim = loadAnim;
                ReleaseSharedNonNull(releasedAnim);
                LoadAnimArray(self)->RemoveAt(static_cast<unsigned long>(i));
                if (target != 0) {
                    break;
                }
            }
        }
    }
}

static inline void BuildCharaBasePath(int charaKind, unsigned long charaNo, char* outPath)
{
    const char** pathParts = s_charaKindPathParts[charaKind];
    sprintf(outPath, s_charaBasePathFmt, pathParts[0], pathParts[1], static_cast<int>(charaNo), pathParts[1],
            static_cast<int>(charaNo), pathParts[2]);
}

static inline CMemory::CStage* HandleModelStage(int charaKind, int specialModelStage)
{
    CMemory::CStage* stage = CharaPcs.m_viewerModelStage;
    if (specialModelStage != 0) {
        stage = charaKind == 3 ? CharaPcs.m_familyModelStage : CharaPcs.m_weaponModelStage;
    }
    return SelectLoadStage(&CharaPcs, stage);
}

static inline CMemory::CStage* HandleTextureStage(int charaKind)
{
    int allocStageMode = CharaPcs.m_charaAllocStage;
    int index = charaKind == 4 ? 3 : 1;
    return GET_CHARA_ALLOC_STAGE_S(allocStageMode, (&CharaPcs.m_viewerModelStage)[index]);
}

static inline Mtx* ModelLocalMtx(CChara::CModel* model)
{
    return reinterpret_cast<Mtx*>(Ptr(model, 8));
}

static inline _GXColor BlendColor(const _GXColor& a, const _GXColor& b, float t)
{
    _GXColor out;
    out.r = static_cast<unsigned char>(a.r + static_cast<int>((b.r - a.r) * t));
    out.g = static_cast<unsigned char>(a.g + static_cast<int>((b.g - a.g) * t));
    out.b = static_cast<unsigned char>(a.b + static_cast<int>((b.b - a.b) * t));
    out.a = static_cast<unsigned char>(a.a + static_cast<int>((b.a - a.a) * t));
    return out;
}

static inline _GXColor ModulateColor(const _GXColor& src, const _GXColor& shade)
{
    _GXColor out;
    out.r = static_cast<unsigned char>((static_cast<unsigned int>(src.r) * shade.r) / 255);
    out.g = static_cast<unsigned char>((static_cast<unsigned int>(src.g) * shade.g) / 255);
    out.b = static_cast<unsigned char>((static_cast<unsigned int>(src.b) * shade.b) / 255);
    out.a = src.a;
    return out;
}

}

/*
 * --INFO--
 * PAL Address: 0x8007a42c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMemory::CStage* GET_CHARA_ALLOC_STAGE_S(int stageIndex, CMemory::CStage* stage)
{
    switch (stageIndex) {
    case 1:
        return MapMng.m_stage;
    case 2:
        return PartPcs.m_usbStreamState.m_stageLoad;
    case 3:
        return PartMng.m_pppEnvSt.m_stagePtr;
    case 4:
        return CharaPcs.m_viewerAnimStage;
    default:
        return stage;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CCharaPcs()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::~CCharaPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x8007a51c
 * PAL Size: 1124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::Init()
{
    m_stage = Memory.CreateStage(0x38000, const_cast<char*>(s_CCharaPcs_stage), 0);
    m_amemStage = Memory.CreateStage(0x380000, const_cast<char*>(s_CCharaPcs_amem), 2);
    m_amemWorkStage = Memory.CreateStage(0x70000, const_cast<char*>(s_CCharaPcs_amemw), 2);
    Chara.SetAmemStage(m_amemStage);

    LoadModelArray(this)->SetStage(m_stage);
    LoadModelArray(this)->SetDefaultSize(0x80);
    LoadModelArray(this)->SetGrow(0);

    LoadAnimArray(this)->SetStage(m_stage);
    LoadAnimArray(this)->SetDefaultSize(0x200);
    LoadAnimArray(this)->SetGrow(0);

    LoadTextureArray(this)->SetStage(m_stage);
    LoadTextureArray(this)->SetDefaultSize(0x100);
    LoadTextureArray(this)->SetGrow(0);

    LoadPdtArray(this)->SetStage(m_stage);
    LoadPdtArray(this)->SetDefaultSize(0x80);
    LoadPdtArray(this)->SetGrow(0);

    for (unsigned int i = 0; i < 2; i++) {
        _GXColor& ambientColor = m_viewerAmbientColor[i];
        ambientColor.r = 0x3F;
        ambientColor.g = 0x3F;
        ambientColor.b = 0x3F;
        ambientColor.a = 0xFF;

        for (int lightIndex = 0; lightIndex < 3; lightIndex++) {
            _GXColor& lightColor = m_viewerDiffuseColor[i][lightIndex];
            const unsigned char intensity = static_cast<unsigned char>(lightIndex == 0 ? 0x3F : 0x00);
            lightColor.r = intensity;
            lightColor.g = intensity;
            lightColor.b = intensity;
            lightColor.a = 0xFF;
            if (i == 0) {
                m_viewerDiffusePos[lightIndex].x = 0.0f;
                m_viewerDiffusePos[lightIndex].y = 0.0f;
                m_viewerDiffusePos[lightIndex].z = 1.0f;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor shade;

        float scale = static_cast<float>(i) * 0.25f;
        shade.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * scale));
        shade.color.g = static_cast<unsigned char>(static_cast<unsigned int>(static_cast<float>(white.color.g) * scale));
        shade.color.b = static_cast<unsigned char>(static_cast<unsigned int>(static_cast<float>(white.color.b) * scale));
        shade.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * scale));
        CColor shadeCopy(shade);

        m_viewerChoiceColor[i].color.r = shadeCopy.color.r;
        m_viewerChoiceColor[i].color.g = shadeCopy.color.g;
        m_viewerChoiceColor[i].color.b = shadeCopy.color.b;
        m_viewerChoiceColor[i].color.a = shadeCopy.color.a;
    }

    m_charaAllocStage = 0;
    m_overlapEnabled = 0;
    CColor baseColor(0x00, 0x00, 0x40, 0x40);
    m_texShadowColor = baseColor.color;

    CVector baseVec(0.0f, 10.0f, 0.0f);
    Vec* constructedVec = reinterpret_cast<Vec*>(&baseVec);
    m_texShadowPos.x = constructedVec->x;
    m_texShadowPos.y = constructedVec->y;
    m_texShadowPos.z = constructedVec->z;
    m_texShadowRadius = 120.0f;
    m_texShadowSize = 0x80;
    m_texShadowDistance = 100;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Quit()
{
    CharaAmemSize() = 0;
    Memory.DestroyStage(m_amemWorkStage);
    Memory.DestroyStage(m_amemStage);
    Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&PTR_s_CCharaPcs_GAME_[index]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::create()
{
    FreeMergeMask(this) = 0;

    m_viewerModelStage = Memory.CreateStage(0x177000, const_cast<char*>(s_CCharaPcs_loadModel), 0);
    m_viewerTextureStage = Memory.CreateStage(0x130000, const_cast<char*>(s_CCharaPcs_loadTex), 0);
    m_weaponTextureStage = Memory.CreateStage(0x8400, const_cast<char*>(s_CCharaPcs_loadWepTex), 0);
    m_weaponModelStage = Memory.CreateStage(0x18000, const_cast<char*>(s_CCharaPcs_loadWepModel), 0);
    m_familyModelStage = Memory.CreateStage(0x10000, const_cast<char*>(s_CCharaPcs_loadFaModel), 0);
    m_viewerAnimStage =
        Memory.CreateStage(static_cast<s32>(CurrentSceneId()) == 4 ? 0x190000UL : 0x1E0000UL,
                           const_cast<char*>(s_CCharaPcs_loadAnim), 0);

    CHandle* sentinel = reinterpret_cast<CHandle*>(
        Memory._Alloc(0x194, CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0xDB, 0));
    if (sentinel != 0) {
        sentinel->m_previous = 0;
        sentinel->m_next = 0;
        sentinel->m_model = 0;
        sentinel->m_textureSet = 0;
        sentinel->m_modelLoadRef = 0;
        sentinel->m_texLoadRef = 0;

        for (int i = 0; i < 64; i++) {
            sentinel->m_animSlot[i] = 0;
        }

        sentinel->m_pdtLoadRef = 0;
        sentinel->m_currentAnimIndex = -1;
        sentinel->m_flags = 0;
        sentinel->m_colorPhase = kCharaOne;
        sentinel->m_sortZ = kCharaZero;
        sentinel->m_shadowTexturePtr = 0;
        sentinel->m_asyncState = 0;
        sentinel->m_asyncFileHandle = 0;
        sentinel->m_fogBlend = kCharaZero;
        sentinel->m_unk0x158 = 0;
        sentinel->m_drawListFlags = static_cast<unsigned char>(__rlwimi(sentinel->m_drawListFlags, 1, 7, 24, 24));
    }

    m_handleList = sentinel;
    m_handleList->m_previous = m_handleList;
    m_handleList->m_next = m_handleList;

    for (int i = 0; i < 4; i++) {
        m_cameraFrameCount[i] = 0;
        m_cameraData[i] = 0;
    }

    CLightPcs::CBumpLight bumpLight;

    bumpLight.m_type = 1;
    bumpLight.m_position.x = kCharaBumpLightPosX;
    bumpLight.m_position.y = kCharaBumpLightPosY;
    bumpLight.m_position.z = kCharaBumpLightPosZ;
    bumpLight.m_targetPosition.x = kCharaBumpLightTargetX;
    bumpLight.m_targetPosition.y = kCharaBumpLightTargetY;
    bumpLight.m_targetPosition.z = kCharaBumpLightTargetZ;
    PSVECSubtract(reinterpret_cast<Vec*>(&bumpLight.m_targetPosition), reinterpret_cast<Vec*>(&bumpLight.m_position),
                  reinterpret_cast<Vec*>(&bumpLight.m_direction));
    PSVECNormalize(reinterpret_cast<Vec*>(&bumpLight.m_direction), reinterpret_cast<Vec*>(&bumpLight.m_direction));
    bumpLight.m_bumpShade[0] = 0x80;
    bumpLight.m_bumpShade[1] = 0x80;
    bumpLight.m_bumpShade[2] = 0x00;
    bumpLight.m_bumpShade[3] = 0xFF;
    bumpLight.m_offsetX = kCharaZero;
    bumpLight.m_offsetZ = kCharaZero;

    gCharaPartWorkPtr = LightPcs.AddBump(&bumpLight, static_cast<CLightPcs::TARGET>(0), Chara.GetMemoryStage(), 4);
    Chara.Create();
}

/*
 * --INFO--
 * PAL Address: 0x8007a0a4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::createLoad()
{
    CharaPcs.m_loadStreamCursor = 0;
    Memory.DefaultGroup() = 2;
    CharaPcs.LoadMergeFile(0, 0x10000000, 1);
    Memory.DefaultGroup() = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80079fd4
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::destroy()
{
    Reset(static_cast<RESET>(1));
    LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(0));
    gCharaPartWorkPtr = 0;

    if (m_handleList != 0) {
        delete m_handleList;
        m_handleList = 0;
    }

    Memory.DestroyStage(m_viewerModelStage);
    Memory.DestroyStage(m_viewerTextureStage);
    Memory.DestroyStage(m_weaponTextureStage);
    Memory.DestroyStage(m_weaponModelStage);
    Memory.DestroyStage(m_familyModelStage);
    Memory.DestroyStage(m_viewerAnimStage);
    Chara.Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x80079d9c
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::Reset(CCharaPcs::RESET mode)
{
    const int resetMode = static_cast<int>(mode);

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;
        if (anim->m_bank != 0) {
            operator delete(anim->m_bank);
            anim->m_bank = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        m_cameraFrameCount[i] = 0;
        if (m_cameraData[i] != 0) {
            delete[] m_cameraData[i];
            m_cameraData[i] = 0;
        }
    }

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        CHandle* next = handle->m_next;
        delete handle;
        handle = next;
    }

    switch (resetMode) {
    case 1:
    releaseAllArrays:
        LoadModelArray(this)->ReleaseAndRemoveAll();
        LoadAnimArray(this)->ReleaseAndRemoveAll();
        LoadTextureArray(this)->ReleaseAndRemoveAll();
        LoadPdtArray(this)->ReleaseAndRemoveAll();
        CharaAmemSize() = 0;
        break;
    case 0: {
        const unsigned int releaseMask = ~(FreeMergeMask(this) | 0x10000000U);
        releaseUnuseLoadModel(static_cast<int>(releaseMask));

        for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
            CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
            if (!(((loadAnim->m_mergeFileId < 0) && (loadAnim->GetRef() == 1)) ||
                  ((loadAnim->m_mergeFileId >= 0) && ((releaseMask & static_cast<unsigned int>(loadAnim->m_mergeFlags)) != 0)))) {
                continue;
            }

            CRef* loadAnimRef = loadAnim;
            if (loadAnimRef->DecRef() == 0) {
                delete loadAnimRef;
            }
            LoadAnimArray(this)->RemoveAt(static_cast<unsigned long>(i));
        }

        System.Printf(const_cast<char*>(s_charaFreeMergeFmt), releaseMask);
        LoadPdtArray(this)->ReleaseAndRemoveAll();
        int charaAmemSize = correctLoadAnimAmem();
        if (charaAmemSize < 0) {
            if (static_cast<unsigned int>(System.m_execParam) >= 2) {
                System.Printf(const_cast<char*>(s_charaAmemCompactFailed));
            }
            goto releaseAllArrays;
        }

        CharaAmemSize() = static_cast<unsigned int>(charaAmemSize);
        goto complete;
    }
    }

complete:
    gCharaPartWorkPtr->m_bumpShade[3] = 0xFF;
    FreeMergeMask(this) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80079B40
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::correctLoadAnimAmem()
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_charaAmemAnimCompactStart));
    }

    unsigned char* tempBuffer = reinterpret_cast<unsigned char*>(
        Memory._Alloc(0x80000, m_viewerAnimStage, const_cast<char*>(s_p_chara_cpp), 0x162, 1));
    if (tempBuffer == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 2U) {
            System.Printf(const_cast<char*>(s_charaAmemAnimCompactAllocFailed));
        }
        return -1;
    }

    int loadAnimCount = LoadAnimArray(this)->GetSize();
    int validAnimCount = 0;
    int maxEnd = 0;
    for (int i = 0; i < loadAnimCount; i++) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;
        const int animEnd = static_cast<int>(anim->m_bankSize) + anim->m_bankAddress;
        if (maxEnd < animEnd) {
            maxEnd = animEnd;
        }
        validAnimCount++;
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_charaAmemAnimCompactCountFmt), validAnimCount);
    }

    int compactedSize = 0;
    int scanOffset = 0;
    do {
        int chunkLoadCount = 0;
        int chunkSize = 0;
        unsigned int nextOffset = scanOffset;
        const unsigned int scanEnd = static_cast<unsigned int>(scanOffset + 0x80000);

        for (int i = 0; i < loadAnimCount; i++) {
            CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
            const unsigned int animOffset = static_cast<unsigned int>(loadAnim->m_anim->m_bankAddress);
            const int animSize = static_cast<int>(loadAnim->m_anim->m_bankSize);
            if (animOffset < static_cast<unsigned int>(scanOffset)) {
                continue;
            }
            const unsigned int animEnd = animOffset + static_cast<unsigned int>(animSize);
            if (animEnd >= scanEnd) {
                continue;
            }

            if (nextOffset < static_cast<int>(animEnd)) {
                nextOffset = static_cast<int>(animEnd);
            }
            chunkLoadCount++;

            Memory.CopyFromAMemorySync(
                tempBuffer + chunkSize,
                reinterpret_cast<void*>(m_amemStage->m_heapTop + static_cast<int>(animOffset)),
                static_cast<unsigned long>(animSize));

            loadAnim->m_anim->m_bankAddress = compactedSize + chunkSize;
            chunkSize += animSize;
        }

        if (chunkLoadCount != 0) {
            const int writeBase = m_amemStage->m_heapTop + compactedSize;
            Memory.CopyToAMemorySync(
                tempBuffer, reinterpret_cast<void*>(writeBase),
                static_cast<unsigned long>(chunkSize));
            if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
                System.Printf(
                    const_cast<char*>(s_charaAmemAnimCompactWritebackFmt), chunkLoadCount, writeBase, writeBase + chunkSize);
            }
        }

        compactedSize += chunkSize;
        scanOffset = nextOffset;
    } while (scanOffset < maxEnd);

    delete tempBuffer;
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_charaAmemAnimCompactDoneFmt), compactedSize);
    }
    return compactedSize;
}

/*
 * --INFO--
 * PAL Address: 0x8007999c
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::onScriptChanging(char*)
{
    for (int i = 0; i < 5; i++) {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor shade;

        float scale = static_cast<float>(i) * 0.25f;
        shade.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * scale));
        shade.color.g = static_cast<unsigned char>(static_cast<unsigned int>(static_cast<float>(white.color.g) * scale));
        shade.color.b = static_cast<unsigned char>(static_cast<unsigned int>(static_cast<float>(white.color.b) * scale));
        shade.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * scale));
        CColor shadeCopy(shade);

        m_viewerChoiceColor[i].color.r = shadeCopy.color.r;
        m_viewerChoiceColor[i].color.g = shadeCopy.color.g;
        m_viewerChoiceColor[i].color.b = shadeCopy.color.b;
        m_viewerChoiceColor[i].color.a = shadeCopy.color.a;
    }

    m_overlapEnabled = 0;
    m_charaAllocStage = 0;
    m_texShadowSize = 0x80;
    m_texShadowDistance = 100;
}

/*
 * --INFO--
 * PAL Address: 0x80079938
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::calc()
{
    CHandle* handle = m_handleList->m_next;

    while (m_handleList != handle) {
        CHandle* next = handle->m_next;
        handle->m_shadowTexturePtr = 0;
        handle->loadModelASyncFrame();
        handle = next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::calcAfter()
{
    Chara.FlipDBuffer();

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;
        if (anim->GetRef() == 1 && anim->m_bank != 0) {
            operator delete(anim->m_bank);
            anim->m_bank = 0;
        }
    }

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1) {
            loadAnim->m_anim->m_lastFrame++;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseAllAnimBank()
{
    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        void*& bankPtr = loadAnim->m_anim->m_bank;
        if (bankPtr != 0) {
            operator delete(bankPtr);
            bankPtr = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseUnusedAnimBank()
{
    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        void*& bankPtr = loadAnim->m_anim->m_bank;
        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1 && bankPtr != 0) {
            operator delete(bankPtr);
            bankPtr = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80079760
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::TryReleaseAnimBank(int requiredSize)
{
    (void)requiredSize;

    int i = LoadAnimArray(this)->GetSize() - 1;
    int releaseSize = -1;
    CLoadAnim* releaseAnim = 0;

    for (; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;

        if (anim->m_bank && releaseSize < anim->m_lastFrame) {
            releaseSize = anim->m_lastFrame;
            releaseAnim = loadAnim;
        }
    }

    if (releaseAnim != 0) {
        CChara::CAnim* releaseAnimData = releaseAnim->m_anim;
        void* bankPtr = releaseAnimData->m_bank;
        if (bankPtr != 0) {
            operator delete(bankPtr);
            releaseAnimData->m_bank = 0;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_charaReleaseAnimBankFmt), releaseSize, releaseAnim->m_name);
        }

        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80079754
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::SetSpecularAlpha(int alpha)
{
    gCharaPartWorkPtr->m_bumpShade[3] = (u8)alpha;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::InitEnv(int envMode)
{
    SetupCharaTevSwap();

    if (envMode == 1 || envMode == 2) {
        LightPcs.SetAmbient(CColor(0x00, 0x00, 0x00, 0xFF).color);
        LightPcs.SetNumDiffuse(0);
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
    } else {
        SetupBaseCharaLights(this);
    }

    if (envMode == 4) {
        GXSetProjection(CameraPcs.m_screenMatrix, GX_PERSPECTIVE);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80079590
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::GetNumTexShadow()
{
    int count = 0;
    CHandle* head = m_handleList;
    CHandle* current = head->m_next;

    while (head != current) {
        if (((current->m_flags & 0x200) != 0) && (current->m_shadowTexturePtr != 0)) {
            count++;
        }
        current = current->m_next;
    }

    return count;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetTexShadow(int startIndex, int maxCount, _GXTexObj* texObjs, Vec* worldPositions, float (*shadowMatrices)[3][4])
{
    int shadowIndex = 0;
    CHandle* handle = m_handleList->m_next;

    while (m_handleList != handle) {
        if ((handle->m_flags & 0x200) != 0 && handle->m_shadowTexturePtr != 0) {
            if (startIndex <= shadowIndex) {
                const int outIndex = shadowIndex - startIndex;
                PSMTXConcat(m_texShadowProjectionMtx, handle->m_shadowViewMtx, reinterpret_cast<MtxPtr>(shadowMatrices[outIndex]));

                const unsigned short texSize = static_cast<unsigned short>(m_texShadowSize);
                GXInitTexObj(
                    &texObjs[outIndex], handle->m_shadowTexturePtr, texSize, texSize, GX_TF_I4, GX_CLAMP, GX_CLAMP,
                    GX_FALSE);

                Mtx modelMtx;
                PSMTXCopy(*ModelLocalMtx(handle->m_model), modelMtx);
                worldPositions[outIndex].x = modelMtx[0][3];
                worldPositions[outIndex].y = modelMtx[1][3];
                worldPositions[outIndex].z = modelMtx[2][3];
            }

            shadowIndex++;
            if (startIndex + maxCount <= shadowIndex) {
                return;
            }
        }

        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::draw()
{
    SetupCharaTevSwap();
    SetupBaseCharaLights(this);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(0, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawBefore()
{
    CameraPcs.SetStdProjectionMatrix();
    SetupCharaTevSwap();
    SetupBaseCharaLights(this);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(3, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawMakeTexShadow()
{
    CHandle* handle = m_handleList->m_next;
    int shadowCount = 0;
    for (; m_handleList != handle; handle = handle->m_next) {
        if ((handle->m_flags & 0x200) != 0) {
            shadowCount++;
        }
    }
    if (shadowCount == 0) {
        return;
    }

    _GXTexObj backBufferTexObj;

    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backBufferTexObj, 0, 0, m_texShadowSize, m_texShadowSize, 0, GX_NEAR, GX_TF_RGBA8, 0);

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    LightPcs.SetAmbient(CColor(0x00, 0x00, 0x00, 0xFF).color);
    LightPcs.SetNumDiffuse(0);
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);

    GXSetPixelFmt((GXPixelFmt)1, GX_ZC_LINEAR);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetViewport(kCharaZero, kCharaZero, static_cast<float>(m_texShadowSize), static_cast<float>(m_texShadowSize), kCharaZero, kCharaOne);
    GXSetScissor(0, 0, static_cast<unsigned int>(m_texShadowSize), static_cast<unsigned int>(m_texShadowSize));
    CColor clearColor(0x00, 0x00, 0x00, 0x00);
    Graphic.SetCopyClear(clearColor.color, 0xFFFFFF);

    m_texShadowTextureOffset = 0;
    m_texShadowTextureBase = Graphic.m_scratchTextureBuffer;
    m_texShadowTextureSize = 0xD2000;
    m_texShadowTextureOffset += m_texShadowSize * m_texShadowSize * 4;
    C_MTXLightPerspective(m_texShadowProjectionMtx, CameraPcs.m_fov, 1.3333334f, 0.5f, -0.5f, 0.5f, 0.5f);

    handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(2, 1);
        }
        handle = handle->m_next;
    }

    Graphic.SetViewport();
    Graphic.SetStdPixelFmt();
    Graphic.SetCopyClear(clearColor.color, 0xFFFFFF);
    gUtil.RenderTextureQuad(
        0.0f, 0.0f, static_cast<float>(m_texShadowSize), static_cast<float>(m_texShadowSize), &backBufferTexObj, 0, 0, 0,
        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawShadow()
{
    if (static_cast<int>(CameraPcs.m_fullScreenShadowEnabled) == 0) {
        return;
    }

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);

    LightPcs.SetAmbient(CColor(0x00, 0x00, 0x00, 0xFF).color);
    LightPcs.SetNumDiffuse(0);
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(1, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTextureSet* CCharaPcs::createTextureSet(void* textureData, int useWeaponStage)
{
    CTextureSet* textureSet = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;

    int allocStageMode = CharaPcs.m_charaAllocStage;
    textureSet->Create(textureData, GET_CHARA_ALLOC_STAGE_S(allocStageMode, (&CharaPcs.m_viewerModelStage)[useWeaponStage != 0 ? 3 : 1]), 0, 0, 0, 0);

    return textureSet;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::releaseUnuseLoadModel(int releaseMask)
{
    int activeCount = 0;

    for (int i = LoadModelArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadModel* loadModel = (*LoadModelArray(this))[static_cast<unsigned long>(i)];
        if ((((loadModel->m_mergeFileId < 0) || (loadModel->m_streamMode != 0)) && loadModel->GetRef() == 1) ||
            (loadModel->m_mergeFileId >= 0 && (releaseMask & loadModel->m_mergeFlags) != 0)) {
            if (loadModel->m_streamMode != 0 && loadModel->GetRef() == 1) {
                ReleaseShared(loadModel->m_model);
            } else {
                CLoadModel* releasedModel = loadModel;
                ReleaseSharedNonNull(releasedModel);
                LoadModelArray(this)->RemoveAt(static_cast<unsigned long>(i));
            }
        } else {
            activeCount++;
        }
    }

    for (int i = LoadTextureArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadTexture* loadTexture = (*LoadTextureArray(this))[static_cast<unsigned long>(i)];
        if ((((loadTexture->m_mergeFileId < 0) || (loadTexture->m_streamMode != 0)) && loadTexture->GetRef() == 1) ||
            (loadTexture->m_mergeFileId >= 0 && (releaseMask & loadTexture->m_mergeFlags) != 0)) {
            if (loadTexture->m_streamMode != 0 && loadTexture->GetRef() == 1) {
                ReleaseShared(loadTexture->m_textureSet);
            } else {
                CLoadTexture* releasedTexture = loadTexture;
                ReleaseSharedNonNull(releasedTexture);
                LoadTextureArray(this)->RemoveAt(static_cast<unsigned long>(i));
            }
        } else {
            activeCount++;
        }
    }

    for (int i = LoadPdtArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadPdt* loadPdt = (*LoadPdtArray(this))[static_cast<unsigned long>(i)];
        if ((loadPdt->m_mergeFileId < 0 && loadPdt->GetRef() == 1) ||
            (loadPdt->m_mergeFileId >= 0 && (releaseMask & loadPdt->m_mergeFlags) != 0)) {
            CLoadPdt* releasedPdt = loadPdt;
            ReleaseSharedNonNull(releasedPdt);
            LoadPdtArray(this)->RemoveAt(static_cast<unsigned long>(i));
        } else {
            activeCount++;
        }
    }

    return activeCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadAnim(CCharaPcs::CLoadAnim*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::DumpLoad()
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpModelHdr1));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpModelHdr2));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpLineSep));
    }
    int modelCount = LoadModelArray(this)->GetSize();
    for (int i = 0; i < modelCount; i++) {
        CLoadModel* loadModel = (*LoadModelArray(this))[static_cast<unsigned long>(i)];
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            int streamMode = loadModel->m_streamMode;
            unsigned int streamSize = streamMode != 0 ? static_cast<unsigned int>(loadModel->m_streamSize) : 0;
            unsigned int streamAddr = streamMode != 0 ? reinterpret_cast<unsigned int>(loadModel->m_streamOffset) : 0;

            System.Printf(
                const_cast<char*>(s_charaDumpModelFmt), i, reinterpret_cast<int>(loadModel->m_keyTag), loadModel->m_keyId,
                loadModel->m_mergeFileId, loadModel->m_mergeFlags, reinterpret_cast<unsigned int>(loadModel->m_model),
                streamMode, streamAddr, streamSize);
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpTextureHdr1));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpTextureHdr2));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpLineSep));
    }
    int textureCount = LoadTextureArray(this)->GetSize();
    for (int i = 0; i < textureCount; i++) {
        CLoadTexture* loadTexture = (*LoadTextureArray(this))[static_cast<unsigned long>(i)];
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            int streamMode = loadTexture->m_streamMode;
            unsigned int streamSize = streamMode != 0 ? static_cast<unsigned int>(loadTexture->m_streamSize) : 0;
            unsigned int streamAddr = streamMode != 0 ? reinterpret_cast<unsigned int>(loadTexture->m_streamOffset) : 0;

            System.Printf(
                const_cast<char*>(s_charaDumpTextureFmt), i, reinterpret_cast<int>(loadTexture->m_keyTag), loadTexture->m_keyId,
                reinterpret_cast<int>(loadTexture->m_variantTag), loadTexture->m_mergeFileId, loadTexture->m_mergeFlags,
                reinterpret_cast<unsigned int>(loadTexture->m_textureSet), streamMode, streamAddr, streamSize);
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpPdtHdr1));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpPdtHdr2));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpLineSep));
    }
    int pdtCount = LoadPdtArray(this)->GetSize();
    for (int i = 0; i < pdtCount; i++) {
        CLoadPdt* loadPdt = (*LoadPdtArray(this))[static_cast<unsigned long>(i)];
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(
                const_cast<char*>(s_charaDumpPdtFmt), i, reinterpret_cast<int>(loadPdt->m_keyTag), loadPdt->m_keyId,
                reinterpret_cast<int>(loadPdt->m_variantTag), loadPdt->m_pdtSlot, loadPdt->m_mergeFileId,
                loadPdt->m_mergeFlags);
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpAnimHdr1));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpAnimHdr2));
    }
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_charaDumpLineSep));
    }
    int animCount = LoadAnimArray(this)->GetSize();
    int totalBankSize = 0;
    for (int i = 0; i < animCount; i++) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            CChara::CAnim* anim = loadAnim->m_anim;
            System.Printf(
                const_cast<char*>(s_charaDumpAnimFmt), i, reinterpret_cast<int>(loadAnim->m_keyTag), loadAnim->m_keyId,
                loadAnim->m_name, loadAnim->m_mergeFileId, loadAnim->m_mergeFlags,
                reinterpret_cast<unsigned int>(anim), anim->m_bankSize, totalBankSize, anim->m_lastFrame);
        }
        totalBankSize += loadAnim->m_anim->m_bankSize;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchModel(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchTexture(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchAnim(int, int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchPdt(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 800783d0
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadCam(int index, char* fileName)
{
    char path[0x104];
    CChunkFile::CChunk chunk;

#define cameraBuffer m_cameraData[index]

    if (cameraBuffer != 0) {
        delete[] cameraBuffer;
        cameraBuffer = 0;
    }

    sprintf(path, "dvd/cft/%s.cmd", fileName);
    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle == 0) {
        return;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    CChunkFile chunkFile(File.m_readBuffer);
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'CAM ': {
            m_cameraFrameCount[index] = static_cast<int>(chunk.m_arg0);

            cameraBuffer = new (CharaPcs.m_viewerAnimStage, const_cast<char*>(s_p_chara_cpp), 0x4D4)
                CCameraFrame[static_cast<unsigned long>(m_cameraFrameCount[index])];

            int byteOffset = 0;
            for (int frame = 0; frame < m_cameraFrameCount[index]; frame++) {
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x00) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x04) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x08) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x0C) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x10) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x14) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x18) = chunkFile.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<char*>(cameraBuffer) + byteOffset + 0x1C) = chunkFile.GetF4();
                byteOffset += 0x20;
            }
            break;
        }
        }
    }

    File.Close(fileHandle);
#undef cameraBuffer
}

/*
 * --INFO--
 * PAL Address: 0x800778dc
 * PAL Size: 2804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadMergeFile(int mergeFileId, int mergeFlags, int streamToAmem)
{
    unsigned int hasLoaded;
    unsigned int i;

    for (i = 0; i < LoadModelArray(this)->GetSize(); i++) {
        CLoadModel* loadModel = (*LoadModelArray(this))[i];
        if (loadModel->m_mergeFileId == mergeFileId) {
            hasLoaded = 1;
            goto checkLoaded;
        }
    }

    for (i = 0; i < LoadTextureArray(this)->GetSize(); i++) {
        CLoadTexture* loadTexture = (*LoadTextureArray(this))[i];
        if (loadTexture->m_mergeFileId == mergeFileId) {
            hasLoaded = 1;
            goto checkLoaded;
        }
    }

    for (i = 0; i < LoadPdtArray(this)->GetSize(); i++) {
        CLoadPdt* loadPdt = (*LoadPdtArray(this))[i];
        if (loadPdt->m_mergeFileId == mergeFileId) {
            hasLoaded = 1;
            goto checkLoaded;
        }
    }

    for (i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[i];
        if (loadAnim->m_mergeFileId == mergeFileId) {
            hasLoaded = 1;
            goto checkLoaded;
        }
    }

    hasLoaded = 0;

checkLoaded:
    if (hasLoaded) {
        System.Printf(const_cast<char*>(s_charaMergeDupFmt), mergeFileId);
        return;
    }

    CCharaPcs* pcs = &CharaPcs;
    int mergePartCount = 1;
    for (int mergePartIndex = 0; mergePartIndex < mergePartCount; mergePartIndex++) {
        char path[0x100];
        sprintf(path, s_charaMergePathFmt, mergeFileId, mergePartIndex);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {

            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CChunkFile chunkFile(File.m_readBuffer);
            CChunkFile::CChunk chunk;
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 'MRG ':
                    break;
                default:
                    continue;
                }

                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 'INFO':
                        mergePartCount = static_cast<int>(chunkFile.Get4());
                        continue;
                    case 'DATA':
                        break;
                    default:
                        continue;
                    }

                    int dataType = -1;
                    void* keyTag = reinterpret_cast<void*>(-1);
                    int keyId = -1;
                    void* variantTag = reinterpret_cast<void*>(-1);
                    int hasDynamics = 0;
                    char* animName = 0;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk)) {
                        switch (chunk.m_id) {
                        case 'NAME':
                            animName = chunkFile.GetString();
                            continue;
                        case 'INFO':
                            dataType = static_cast<int>(chunkFile.Get4());
                            keyTag = reinterpret_cast<void*>(chunkFile.Get4());
                            keyId = static_cast<int>(chunkFile.Get4());
                            variantTag = reinterpret_cast<void*>(chunkFile.Get4());
                            hasDynamics = static_cast<int>(chunkFile.Get4());
                            continue;
                        case 'RAW ':
                            break;
                        default:
                            continue;
                        }

                        const unsigned int rawSize = static_cast<int>(chunk.m_size);

                        switch (dataType) {
                        case 0: {
                            CLoadModel* loadModel = 0;
                            for (unsigned int i = 0; i < static_cast<unsigned int>(LoadModelArray(pcs)->GetSize()); i++) {
                                CLoadModel* it = (*LoadModelArray(pcs))[i];
                                if (reinterpret_cast<int>(it->m_keyTag) == reinterpret_cast<int>(keyTag) &&
                                    static_cast<unsigned int>(it->m_keyId) == static_cast<unsigned int>(keyId)) {
                                    loadModel = it;
                                    break;
                                }
                            }

                            if (loadModel == 0) {
                                void* rawAddr = chunkFile.GetAddress();
                                loadModel = new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
                                loadModel->m_keyTag = keyTag;
                                loadModel->m_keyId = keyId;
                                loadModel->m_mergeFileId = mergeFileId;
                                loadModel->m_mergeFlags = mergeFlags;
                                LoadModelArray(pcs)->Add(loadModel);

                                if (streamToAmem == 0) {
                                    CChara::CModel* model =
                                        new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
                                    model->Create(rawAddr, SelectLoadStage(pcs, pcs->m_viewerModelStage));
                                    loadModel->m_model = model;
                                } else {
                                    loadModel->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadModel->m_streamSize = rawSize;
                                    loadModel->m_streamMode = 1;
                                    Memory.CopyToAMemorySync(
                                        rawAddr, reinterpret_cast<unsigned char*>(StageBase(m_amemWorkStage)) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }

                                if (hasDynamics != 0) {
                                    chunkFile.GetNextChunk(chunk);
                                    CMemory::CStage* dynStage = SelectLoadStage(pcs, pcs->m_viewerModelStage);
                                    loadModel->m_model->CreateDynamics(chunkFile.GetAddress(), dynStage);
                                }
                            }
                            break;
                        }
                        case 1: {
                            CLoadTexture* loadTexture = 0;
                            for (unsigned int i = 0; i < static_cast<unsigned int>(LoadTextureArray(pcs)->GetSize()); i++) {
                                CLoadTexture* it = (*LoadTextureArray(pcs))[i];
                                if (reinterpret_cast<int>(it->m_keyTag) == reinterpret_cast<int>(keyTag) &&
                                    static_cast<unsigned int>(it->m_keyId) == static_cast<unsigned int>(keyId) &&
                                    it->m_variantTag == variantTag) {
                                    loadTexture = it;
                                    break;
                                }
                            }

                            if (loadTexture == 0) {
                                void* rawAddr = chunkFile.GetAddress();
                                loadTexture = new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
                                loadTexture->m_keyTag = keyTag;
                                loadTexture->m_keyId = keyId;
                                loadTexture->m_variantTag = variantTag;
                                loadTexture->m_mergeFileId = mergeFileId;
                                loadTexture->m_mergeFlags = mergeFlags;
                                LoadTextureArray(pcs)->Add(loadTexture);

                                if (streamToAmem == 0) {
                                    CTextureSet* textureSet =
                                        new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
                                    CMemory::CStage* textureStage =
                                        reinterpret_cast<int>(keyTag) == 4 ? pcs->m_weaponTextureStage
                                                                           : pcs->m_viewerTextureStage;
                                    textureSet->Create(rawAddr, SelectLoadStage(pcs, textureStage), 0, 0, 0, 0);
                                    loadTexture->m_textureSet = textureSet;
                                } else {
                                    loadTexture->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadTexture->m_streamSize = rawSize;
                                    loadTexture->m_streamMode = 1;
                                    Memory.CopyToAMemorySync(
                                        rawAddr, reinterpret_cast<unsigned char*>(StageBase(m_amemWorkStage)) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }
                            }
                            break;
                        }
                        case 2: {
                            CLoadAnim* loadAnim = 0;
                            for (unsigned int i = 0; i < static_cast<unsigned int>(LoadAnimArray(pcs)->GetSize()); i++) {
                                CLoadAnim* it = (*LoadAnimArray(pcs))[i];
                                if (reinterpret_cast<int>(it->m_keyTag) == reinterpret_cast<int>(keyTag) &&
                                    static_cast<unsigned int>(it->m_keyId) == static_cast<unsigned int>(keyId) &&
                                    strcmp(animName, it->m_name) == 0) {
                                    loadAnim = it;
                                    break;
                                }
                            }

                            if (loadAnim == 0) {
                                void* rawAddr = chunkFile.GetAddress();
                                CChara::CAnim* anim =
                                    new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x62A) CChara::CAnim;
                                anim->Create(rawAddr, pcs->m_viewerAnimStage);

                                loadAnim = new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x62D) CLoadAnim;
                                loadAnim->m_keyId = keyId;
                                loadAnim->m_keyTag = keyTag;
                                strcpy(loadAnim->m_name, animName);
                                loadAnim->m_anim = anim;
                                loadAnim->m_mergeFileId = mergeFileId;
                                loadAnim->m_mergeFlags = mergeFlags;
                                LoadAnimArray(pcs)->Add(loadAnim);
                            }
                            break;
                        }
                        case 3: {
                            Sound.LoadSe(chunkFile.GetAddress());
                            break;
                        }
                        case 4: {
                            Sound.LoadWave(chunkFile.GetAddress());
                            break;
                        }
                        case 5: {
                            CLoadPdt* loadPdt = 0;
                            for (unsigned int i = 0; i < static_cast<unsigned int>(LoadPdtArray(pcs)->GetSize()); i++) {
                                CLoadPdt* it = (*LoadPdtArray(pcs))[i];
                                if (reinterpret_cast<int>(it->m_keyTag) == reinterpret_cast<int>(keyTag) &&
                                    it->m_keyId == keyId &&
                                    reinterpret_cast<int>(it->m_variantTag) == reinterpret_cast<int>(variantTag)) {
                                    loadPdt = it;
                                    break;
                                }
                            }

                            void* primaryData = chunkFile.GetAddress();
                            const int primarySize = rawSize;
                            if (loadPdt == 0) {
                                chunkFile.GetNextChunk(chunk);
                                void* secondaryData = chunkFile.GetAddress();
                                const int secondarySize = static_cast<int>(chunk.m_size);
                                loadPdt = new (pcs->m_stage, const_cast<char*>(s_p_chara_cpp), 0x572) CLoadPdt;
                                loadPdt->m_keyTag = keyTag;
                                loadPdt->m_keyId = keyId;
                                loadPdt->m_variantTag = variantTag;
                                loadPdt->m_mergeFileId = mergeFileId;
                                loadPdt->m_mergeFlags = mergeFlags;
                                loadPdt->m_pdtSlot = PartPcs.LoadMonsterPdt(
                                    keyId, reinterpret_cast<int>(variantTag), primaryData, primarySize, secondaryData, secondarySize);
                                LoadPdtArray(pcs)->Add(loadPdt);
                            }
                            break;
                        }
                        }
                    }
                    chunkFile.PopChunk();
                }
                chunkFile.PopChunk();
            }

            File.Close(fileHandle);
        } else {
            System.Printf(const_cast<char*>(s_charaMergeOpenFmt), mergeFileId);
            break;
        }
    }

    System.Printf(const_cast<char*>(s_charaMergeDoneFmt), mergeFileId, mergeFlags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::FreeMergeFile(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::isCached(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadModel(void*, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadTexture(void*, int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadAnimBuffer(void*, char*, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawOverlap()
{
    if (m_overlapEnabled == 0) {
        return;
    }

    int left = 0;
    int top = 0;
    int width = 0x280;
    int height = 0x1C0;
    _GXTexObj* backBufferTex = Graphic.GetBackBufferRect(left, top, width, height, 0);

    Mtx savedCameraMtx;
    Mtx lookAtMtx;
    Mtx identityMtx;
    Mtx texMtx;
    Mtx44 projectionMtx;

    PSMTXCopy(CameraPcs.m_cameraMatrix, savedCameraMtx);

    C_MTXOrtho(projectionMtx, kCharaZero, FLOAT_803302C8, kCharaZero, FLOAT_803302CC, FLOAT_803302A8, FLOAT_803302D0);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    CColor black(0x00, 0x00, 0x00, 0xFF);
    GXSetChanMatColor(GX_COLOR0A0, black.color);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumTevStages(1);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    Graphic.SetFog(0, 0);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(kCharaZero, kCharaZero, FLOAT_803302D4);
    GXPosition3f32(FLOAT_803302CC, kCharaZero, FLOAT_803302D4);
    GXPosition3f32(kCharaZero, FLOAT_803302C8, FLOAT_803302D4);
    GXPosition3f32(FLOAT_803302CC, FLOAT_803302C8, FLOAT_803302D4);

    PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);

    Vec up;
    up.x = kCharaZero;
    up.y = kCharaOne;
    up.z = kCharaZero;
    C_MTXLookAt(lookAtMtx, &m_overlapEyePos, &up, &m_overlapTargetPos);
    PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);

    SetupCharaTevSwap();
    SetupBaseCharaLights(this);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(0, 1);
        }
        handle = handle->m_next;
    }

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    CColor blendBlack(0x00, 0x00, 0x00, static_cast<unsigned char>(m_overlapAlpha & 0xFF));
    GXSetChanMatColor(GX_COLOR0A0, blendBlack.color);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    C_MTXOrtho(projectionMtx, kCharaZero, FLOAT_803302C8, kCharaZero, FLOAT_803302CC, kCharaZero, FLOAT_803302D8);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumTevStages(1);
    Graphic.SetFog(0, 0);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(kCharaZero, kCharaZero, kCharaZero);
    GXPosition3f32(FLOAT_803302CC, kCharaZero, kCharaZero);
    GXPosition3f32(kCharaZero, FLOAT_803302C8, kCharaZero);
    GXPosition3f32(FLOAT_803302CC, FLOAT_803302C8, kCharaZero);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    GXSetChanMatColor(GX_COLOR0A0, white.color);
    GXLoadTexObj(backBufferTex, GX_TEXMAP0);
    PSMTXScale(texMtx, FLOAT_803302DC, FLOAT_803302E0, kCharaOne);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(kCharaZero, kCharaZero, kCharaZero);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(FLOAT_803302CC, kCharaZero, kCharaZero);
    GXTexCoord2u16(0x280, 0);
    GXPosition3f32(kCharaZero, FLOAT_803302C8, kCharaZero);
    GXTexCoord2u16(0, 0x1C0);
    GXPosition3f32(FLOAT_803302CC, FLOAT_803302C8, kCharaZero);
    GXTexCoord2u16(0x280, 0x1C0);

    PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);
    PSMTXCopy(savedCameraMtx, CameraPcs.m_cameraMatrix);
}

/*
 * --INFO--
 * PAL Address: 8007717c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CCharaPcs::CHandle::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, CharaPcs.m_stage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 80077080
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCharaPcs::CHandle::CHandle()
{
	m_previous = (CCharaPcs::CHandle*)nullptr;
	m_next = (CCharaPcs::CHandle*)nullptr;
	m_model = (CChara::CModel*)nullptr;
	m_textureSet = (CTextureSet*)nullptr;
	m_modelLoadRef = (CRef*)nullptr;
	m_texLoadRef = (CRef*)nullptr;

	for (int i = 0; i < 64; ++i)
	{
		m_animSlot[i] = (CRef*)nullptr;
	}

	// PDT load ref
	m_pdtLoadRef = (CLoadPdt*)nullptr;

	// Playback / state
	m_currentAnimIndex = -1;
	m_flags = 0;

	m_colorPhase = kCharaOne;
	m_sortZ = kCharaZero;
	m_shadowTexturePtr = nullptr;

	m_asyncState = 0;
	m_asyncFileHandle = (CFile::CHandle*)nullptr;

	m_fogBlend = kCharaZero;
	m_unk0x158 = 0;
	m_drawListFlags = static_cast<unsigned char>(__rlwimi(m_drawListFlags, 1, 7, 24, 24));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CHandle::~CHandle()
{
    if (m_asyncFileHandle != 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 2U) {
            System.Printf(const_cast<char*>(s_charaAsyncCancelFmt));
        }
        File.Close(m_asyncFileHandle);
        m_asyncFileHandle = 0;
    }

    m_asyncState = 0;
    PartMng.pppDeleteCHandle(this);

    if (m_next != 0 && m_previous != 0) {
        m_previous->m_next = m_next;
        m_next->m_previous = m_previous;
        m_previous = 0;
        m_next = 0;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x717);
    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x8C9);
    PartMng.pppDeleteCHandle(this);

    ReleaseShared(m_model);
    ReleaseShared(m_textureSet);
    ReleaseShared(m_modelLoadRef);
    ReleaseShared(m_texLoadRef);
    ReleaseShared(m_pdtLoadRef);

    CharaPcs.releaseUnuseLoadModel(0);
    {
        CRef** slotPtr = &m_animSlot[0];
        for (int i = 0; i < 64; i++, slotPtr++) {
            ReleaseShared(*slotPtr);
        }
    }
    PruneUnsharedAnimRefs(&CharaPcs, 0);
}

/*
 * --INFO--
 * PAL Address: 80076cf4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::Add()
{
    if (m_next != nullptr) {
        return;
    }
    if (m_previous != nullptr) {
        return;
    }

    CCharaPcs::CHandle* head = CharaPcs.m_handleList->m_previous;

    m_previous = head;
    m_next = head->m_next;
    head->m_next->m_previous = this;
    head->m_next = this;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::ChangeTexture(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, int mergeFileId, int mergeFlags)
{
    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x749);
    m_model->AttachTextureSet(0);

    ReleaseShared(m_textureSet);
    ReleaseShared(m_texLoadRef);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadTexture* loadTexture;
    for (unsigned int i = 0; i < static_cast<unsigned int>(LoadTextureArray(&CharaPcs)->GetSize()); i++) {
        CLoadTexture* it = (*LoadTextureArray(&CharaPcs))[i];
        if (reinterpret_cast<int>(it->m_keyTag) == charaKind && static_cast<unsigned long>(it->m_keyId) == charaNo &&
            it->m_variantTag == reinterpret_cast<void*>(textureVariant)) {
            loadTexture = it;
            goto foundTexture;
        }
    }
    loadTexture = 0;
foundTexture:

    if (loadTexture != 0) {
        if (loadTexture->m_streamMode != 0 && loadTexture->GetRef() == 1) {
            File.LockBuffer();
            Memory.CopyFromAMemorySync(
                File.m_readBuffer,
                reinterpret_cast<unsigned char*>(StageBase(CharaPcs.m_amemWorkStage)) +
                    reinterpret_cast<unsigned int>(loadTexture->m_streamOffset),
                static_cast<unsigned long>(loadTexture->m_streamSize));
            void* readBuffer = File.m_readBuffer;
            CTextureSet* textureSet = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
            textureSet->Create(readBuffer, HandleTextureStage(charaKind), 0, 0, 0, 0);
            loadTexture->m_textureSet = textureSet;
            File.UnlockBuffer();
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_charaTexLoadAmemFmt), charaKind, static_cast<unsigned int>(charaNo),
                          static_cast<int>(textureVariant));
        }

        m_texLoadRef = loadTexture;
        loadTexture->AddRef();
        m_textureSet = loadTexture->m_textureSet;
        m_textureSet->AddRef();
        goto attach;
    } else {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_charaTexLoadDvdFmt), charaKind, static_cast<unsigned int>(charaNo),
                          static_cast<int>(textureVariant));
        }

        if (textureVariant >= 1) {
            sprintf(path, s_charaTextureVariantFmt, basePath, static_cast<int>(textureVariant) + 0x61);
        } else {
            strcpy(path, basePath);
        }
        strcat(path, s_charaTextureSuffix);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* readBuffer = File.m_readBuffer;
            loadTexture = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
            loadTexture->m_keyTag = reinterpret_cast<void*>(charaKind);
            loadTexture->m_keyId = static_cast<int>(charaNo);
            loadTexture->m_variantTag = reinterpret_cast<void*>(textureVariant);
            loadTexture->m_mergeFileId = mergeFileId;
            loadTexture->m_mergeFlags = mergeFlags;
            LoadTextureArray(&CharaPcs)->Add(loadTexture);

            CTextureSet* textureSet = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
            textureSet->Create(readBuffer, HandleTextureStage(charaKind), 0, 0, 0, 0);
            loadTexture->m_textureSet = textureSet;

            File.Close(fileHandle);
        } else {
            m_textureSet = 0;
            if (charaKind != 5 && static_cast<unsigned int>(System.m_execParam) >= 2) {
                System.Printf(const_cast<char*>(s_charaTexMissingFmt), path);
            }
            goto attach;
        }
    }

    m_texLoadRef = loadTexture;
    m_texLoadRef->AddRef();
    m_textureSet = reinterpret_cast<CLoadTexture*>(m_texLoadRef)->m_textureSet;
    m_textureSet->AddRef();
attach:
    m_model->AttachTextureSet(m_textureSet);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadModel(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, unsigned long unusedArg, int mergeFileId,
    int mergeFlags, int specialModelStage)
{
    (void)unusedArg;

    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x8C9);
    PartMng.pppDeleteCHandle(this);

    ReleaseShared(m_model);
    ReleaseShared(m_textureSet);
    ReleaseShared(m_modelLoadRef);
    ReleaseShared(m_texLoadRef);
    ReleaseShared(m_pdtLoadRef);

    CharaPcs.releaseUnuseLoadModel(0);

    m_charaKind = charaKind;
    m_charaNo = static_cast<int>(charaNo);
    m_textureVariant = static_cast<unsigned int>(textureVariant);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadModel* loadModel;
    for (unsigned int i = 0; i < static_cast<unsigned int>(LoadModelArray(&CharaPcs)->GetSize()); i++) {
        CLoadModel* it = (*LoadModelArray(&CharaPcs))[i];
        if (reinterpret_cast<int>(it->m_keyTag) == charaKind && static_cast<unsigned long>(it->m_keyId) == charaNo) {
            loadModel = it;
            goto foundModel;
        }
    }
    loadModel = 0;
foundModel:

    if (loadModel != 0) {
        m_modelLoadRef = loadModel;

        int modelStageIndex;
        if (specialModelStage != 0) {
            modelStageIndex = 4;
            if (m_charaKind == 3) {
                modelStageIndex = 5;
            }
        } else {
            modelStageIndex = 0;
        }
#define modelStage ((&CharaPcs.m_viewerModelStage)[modelStageIndex])

        if (loadModel->GetRef() == 1) {
            if (loadModel->m_streamMode != 0) {
                File.LockBuffer();
                Memory.CopyFromAMemorySync(
                    File.m_readBuffer,
                    reinterpret_cast<unsigned char*>(StageBase(CharaPcs.m_amemWorkStage)) +
                        reinterpret_cast<unsigned int>(loadModel->m_streamOffset),
                    static_cast<unsigned long>(loadModel->m_streamSize));
                CChara::CModel* model =
                    new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x7C7) CChara::CModel;
                void* amemBuffer = File.m_readBuffer;
                model->Create(amemBuffer, SelectLoadStage(&CharaPcs, modelStage));
                loadModel->m_model = model;
                File.UnlockBuffer();
            }

            if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                System.Printf(const_cast<char*>(s_charaModelLoadAmemFmt), charaKind, static_cast<int>(charaNo));
            }

            loadModel->AddRef();
            m_model = loadModel->m_model;
            m_model->AddRef();
            m_model->Init();
        } else {
            loadModel->AddRef();
            m_model = loadModel->m_model->Duplicate(SelectLoadStage(&CharaPcs, modelStage));
        }
#undef modelStage
    } else {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_charaModelLoadDvdFmt), charaKind, static_cast<int>(charaNo));
        }

        strcpy(path, basePath);
        strcat(path, s_charaModelSuffix);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            return;
        }

        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        void* readBuffer = File.m_readBuffer;
        loadModel = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
        loadModel->m_keyTag = reinterpret_cast<void*>(charaKind);
        loadModel->m_keyId = static_cast<int>(charaNo);
        loadModel->m_mergeFileId = mergeFileId;
        loadModel->m_mergeFlags = mergeFlags;
        LoadModelArray(&CharaPcs)->Add(loadModel);

        CChara::CModel* model =
            new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
        model->Create(readBuffer, HandleModelStage(charaKind, 0));
        loadModel->m_model = model;

        m_modelLoadRef = loadModel;
        File.Close(fileHandle);
        m_modelLoadRef->AddRef();
        m_model = reinterpret_cast<CLoadModel*>(m_modelLoadRef)->m_model;
        m_model->AddRef();

        strcpy(path, basePath);
        strcat(path, s_charaDynamicsSuffix);
        fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);
            void* dynamicsBuffer = File.m_readBuffer;
            m_model->CreateDynamics(dynamicsBuffer, HandleModelStage(charaKind, 0));
            File.Close(fileHandle);
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(s_charaDynamicsLoadDvdFmt), charaKind, static_cast<int>(charaNo));
            }
        }
    }

    ChangeTexture(charaKind, charaNo, textureVariant, mergeFileId, mergeFlags);
    if (m_textureSet != 0 && m_textureSet->Find(const_cast<char*>(s_mogFurTextureName)) >= 0) {
        m_model->InitMogFurTex();
    }

    if (static_cast<s32>(CurrentSceneId()) != 7 && charaKind == 1) {
        CLoadPdt* loadPdt;
        for (unsigned int i = 0; i < static_cast<unsigned int>(LoadPdtArray(&CharaPcs)->GetSize()); i++) {
            CLoadPdt* it = (*LoadPdtArray(&CharaPcs))[i];
            if (reinterpret_cast<int>(it->m_keyTag) == charaKind && it->m_keyId == static_cast<int>(charaNo) &&
                reinterpret_cast<int>(it->m_variantTag) == static_cast<int>(textureVariant)) {
                loadPdt = it;
                goto foundPdt;
            }
        }
        loadPdt = 0;
    foundPdt:

        if (loadPdt != 0) {
            m_pdtLoadRef = loadPdt;
            m_pdtLoadRef->AddRef();
        } else {
            loadPdt = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x868) CLoadPdt;
            m_pdtLoadRef = loadPdt;
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_keyTag = reinterpret_cast<void*>(charaKind);
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_keyId = static_cast<unsigned int>(charaNo);
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_variantTag = reinterpret_cast<void*>(textureVariant);
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_mergeFileId = mergeFileId;
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_mergeFlags = mergeFlags;
            reinterpret_cast<CLoadPdt*>(m_pdtLoadRef)->m_pdtSlot =
                PartPcs.LoadMonsterPdt(static_cast<int>(charaNo), static_cast<int>(textureVariant), 0, 0, 0, 0);
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(s_charaLoadPdtLogFmt), charaKind, static_cast<int>(charaNo), static_cast<int>(textureVariant));
            }
            LoadPdtArray(&CharaPcs)->Add(reinterpret_cast<CLoadPdt*>(m_pdtLoadRef));
            m_pdtLoadRef->AddRef();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::CHandle::LoadAnim(
    char* animName, int animIndex, int animFlags, int charaKind, int charaNo, int mergeFileId, int mergeFlags)
{
    if (animIndex == -1) {
        CRef** slotPtr = &m_animSlot[0];
        for (int i = 0; i < 64; i++, slotPtr++) {
            ReleaseShared(*slotPtr);
        }
        PruneUnsharedAnimRefs(&CharaPcs, 0);
    } else {
        CLoadAnim* previousAnim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]);
        if (previousAnim != 0) {
            ReleaseSharedNonNull(m_animSlot[animIndex]);
            PruneUnsharedAnimRefs(&CharaPcs, reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]));
            m_animSlot[animIndex] = 0;
        }
    }

    const int resolvedKind = charaKind == -1 ? m_charaKind : charaKind;
    const int resolvedNo = charaNo == -1 ? m_charaNo : charaNo;

    CLoadAnim* loadAnim = FindLoadedAnim(&CharaPcs, resolvedKind, resolvedNo, animName);
    if (loadAnim == 0) {
        loadAnim = LoadAnimFromDisk(&CharaPcs, resolvedKind, resolvedNo, animName, mergeFileId, mergeFlags);
    }
    if (loadAnim == 0) {
        return 0;
    }

    m_animSlot[animIndex] = loadAnim;
    reinterpret_cast<CRef*>(loadAnim)->AddRef();

    *reinterpret_cast<unsigned int*>(Ptr(m_animSlot[animIndex], 0x70)) = static_cast<unsigned int>(animFlags);
    {
        unsigned char& flags1 = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex])->m_anim->m_flags;
        flags1 = static_cast<unsigned char>(__rlwimi(flags1, animFlags, 7, 24, 24));
        unsigned char& flags2 = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex])->m_anim->m_flags;
        flags2 = static_cast<unsigned char>(__rlwimi(flags2, animFlags, 5, 25, 25));
    }

    return 1;
}

int CCharaPcs::CHandle::IsModelLoaded(int checkModelField)
{
	if ((m_asyncState == 0 || m_asyncState == 7)
		&& m_model != nullptr
		&& (checkModelField == 0 || m_model->m_texSet != 0))
	{
			return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::LoadAnim(int charaKind, int charaNo, char* animName, int unusedArg, int mergeFileId, int mergeFlags)
{
    (void)unusedArg;

    CLoadAnim* loadAnim = FindLoadedAnim(&CharaPcs, charaKind, charaNo, animName);
    if (loadAnim == 0) {
        loadAnim = LoadAnimFromDisk(&CharaPcs, charaKind, charaNo, animName, mergeFileId, mergeFlags);
        if (loadAnim == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeAnim(int animIndex)
{
    if (animIndex == -1) {
        for (int i = 0; i < 64; i++) {
            ReleaseHandleAnimSlot(this, i);
        }
        PruneUnsharedAnimRefs(&CharaPcs, 0);
        return;
    }

    CLoadAnim* previousAnim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]);
    if (previousAnim == 0) {
        return;
    }

    ReleaseSharedNonNull(m_animSlot[animIndex]);
    PruneUnsharedAnimRefs(&CharaPcs, reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]));
    m_animSlot[animIndex] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::CHandle::SetAnim(int animIndex, int startFrame, int endFrame, int blendMode, int forceSet)
{
    if (m_model == 0) {
        return 0;
    }
    if (m_currentAnimIndex == animIndex && forceSet == 0) {
        goto fail;
    }

    {
        CChara::CAnim* anim;
        if (animIndex == -1) {
            anim = 0;
        } else {
            CLoadAnim* loadAnim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]);
            anim = loadAnim != 0 ? loadAnim->m_anim : 0;
        }

        if (anim == 0) {
            if (m_charaKind != 3 && static_cast<unsigned int>(System.m_execParam) >= 2) {
                System.Printf(const_cast<char*>(s_charaSetAnimMissingFmt), m_charaKind, m_charaNo, animIndex);
            }
            return 0;
        }

        m_model->AttachAnim(anim, startFrame, endFrame, blendMode);
        m_currentAnimIndex = animIndex;
        return 1;
    }

fail:
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Draw(int drawPass)
{
	unsigned int dbgMenuFlags = DbgMenuPcs.GetDbgFlagsRaw();
	if ((dbgMenuFlags & 0x8000) != 0) {
		if ((drawPass == 4) && ((m_flags & 0x10000) != 0)) {
			draw(3, 0);
		}
		draw(drawPass, (4U - drawPass | drawPass - 4U) >> 0x1F);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::draw(int drawPass, int immediatePass)
{
    if (m_model == 0) {
        return;
    }

    const unsigned int flags = m_flags;
    if ((flags & 1) == 0) {
        return;
    }
    if ((flags & 0x400000) != 0) {
        return;
    }
    if (kCharaZero == m_model->m_lightAlpha && (flags & 0x80) == 0) {
        return;
    }
    if ((flags & 0x100) != 0 && drawPass != 5) {
        return;
    }
    if (drawPass == 1 && (flags & 0x40) != 0) {
        return;
    }
    if (drawPass == 2 && (flags & 0x200) == 0) {
        return;
    }
    if (drawPass == 0 && (flags & 0x4000) != 0) {
        return;
    }

    if (immediatePass != 0 && drawPass == 0 && (m_model->m_lightAlpha < kCharaOne || (flags & 0x40000) != 0)) {
        if (immediatePass != 0) {
            ppvDrawMng.AddPrim(-m_sortZ, this);
            return;
        }
    }

    if (drawPass == 3 && (flags & 0x81C) == 0) {
        return;
    }
    if ((drawPass == 0 || drawPass == 4) && (flags & 0x10) != 0) {
        return;
    }

    if (drawPass != 1 && drawPass != 2 && (flags & 0x200000) == 0) {
        const unsigned int lightBank = (flags >> 19) & 1;
        const float phase = m_colorPhase * FLOAT_80330290;
        unsigned int phaseIndex = static_cast<int>(phase);
        const float blendT = static_cast<float>(fmod(static_cast<double>(phase), DOUBLE_80330298));
        CColor shade;
        if ((m_flags & 0x20000) != 0 && drawPass != 3) {
            CColor white(0xFF, 0xFF, 0xFF, 0xFF);
            shade.color.r = white.color.r;
            shade.color.g = white.color.g;
            shade.color.b = white.color.b;
            shade.color.a = white.color.a;
        } else {
            CColor next;
            next.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex + 1].color.r) * blendT));
            next.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex + 1].color.g) * blendT));
            next.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex + 1].color.b) * blendT));
            next.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex + 1].color.a) * blendT));
            CColor nextCopy(next);

            const float inv = kCharaOne - blendT;
            CColor cur;
            cur.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex].color.r) * inv));
            cur.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex].color.g) * inv));
            cur.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex].color.b) * inv));
            cur.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(CharaPcs.m_viewerChoiceColor[phaseIndex].color.a) * inv));
            CColor curCopy(cur);

            CColor blended;
            blended.color.r = static_cast<unsigned char>(curCopy.color.r + nextCopy.color.r);
            blended.color.g = static_cast<unsigned char>(curCopy.color.g + nextCopy.color.g);
            blended.color.b = static_cast<unsigned char>(curCopy.color.b + nextCopy.color.b);
            blended.color.a = static_cast<unsigned char>(curCopy.color.a + nextCopy.color.a);
            CColor blendedCopy(blended);
            shade.color.r = blendedCopy.color.r;
            shade.color.g = blendedCopy.color.g;
            shade.color.b = blendedCopy.color.b;
            shade.color.a = blendedCopy.color.a;
        }

        CColor3 ambientBase(CharaPcs.m_viewerAmbientColor[lightBank]);
        CColor3 ambientShade;
        ambientShade.color.r = static_cast<signed char>((static_cast<unsigned int>(ambientBase.color.r) * shade.color.r) / 255);
        ambientShade.color.g = static_cast<signed char>((static_cast<unsigned int>(ambientBase.color.g) * shade.color.g) / 255);
        ambientShade.color.b = static_cast<unsigned char>((static_cast<unsigned int>(ambientBase.color.b) * shade.color.b) / 255);
        ambientShade.color.a = ambientBase.color.a;
        CColor3 ambientColor(ambientShade);
        _GXColor ambientGX = ambientColor.color;
        LightPcs.SetAmbient(ambientGX);

        for (unsigned long i = 0; i < 3; i++) {
            CColor3 diffuseBase(CharaPcs.m_viewerDiffuseColor[lightBank][i]);
            CColor3 diffuseShade;
            diffuseShade.color.r = static_cast<signed char>((static_cast<unsigned int>(diffuseBase.color.r) * shade.color.r) / 255);
            diffuseShade.color.g = static_cast<unsigned char>((static_cast<int>(diffuseBase.color.g) * shade.color.g) / 255);
            diffuseShade.color.b = static_cast<unsigned char>((static_cast<int>(diffuseBase.color.b) * shade.color.b) / 255);
            diffuseShade.color.a = diffuseBase.color.a;
            CColor3 diffuseColor(diffuseShade);
            _GXColor diffuseGX = diffuseColor.color;
            LightPcs.SetDiffuseColor(i, diffuseGX);
        }

        Vec lightPos;
        Mtx modelMtx;
        PSMTXCopy(*ModelLocalMtx(m_model), modelMtx);
        lightPos.x = modelMtx[0][3];
        lightPos.y = modelMtx[1][3];
        lightPos.z = modelMtx[2][3];
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);
    }

    Mtx viewMtx;
    PSMTXCopy(CameraPcs.m_cameraMatrix, viewMtx);

    if (drawPass == 3) {
        if ((m_flags & 4) != 0) {
            const float offsetY = 0.25f * (m_worldPosY - m_bgCharmPlaneY);
            viewMtx[0][3] += viewMtx[0][1] * offsetY;
            viewMtx[1][3] += viewMtx[1][1] * offsetY;
            viewMtx[2][3] += viewMtx[2][1] * offsetY;
            viewMtx[1][1] *= 0.5f;
            viewMtx[0][1] *= 0.5f;
            viewMtx[2][1] *= 0.5f;
        } else if ((m_flags & 8) != 0) {
            PSMTXConcat(viewMtx, CFlatCenterMatrix(), viewMtx);
        }
    } else if (drawPass == 2) {
        CVector modelPos;
        Mtx modelMtx;
        PSMTXCopy(*ModelLocalMtx(m_model), modelMtx);
        modelPos.x = modelMtx[0][3];
        modelPos.y = modelMtx[1][3];
        modelPos.z = modelMtx[2][3];

        CVector focusPos(CharaPcs.m_texShadowPos);
        CVector deltaTmp;
        PSVECSubtract(focusPos, modelPos, deltaTmp);
        Vec delta;
        delta.x = deltaTmp.x;
        delta.y = deltaTmp.y;
        delta.z = deltaTmp.z;
        if (delta.x == kCharaZero && delta.z == kCharaZero) {
            return;
        }

        const float distRatio = PSVECMag(&delta) / CharaPcs.m_texShadowRadius;
        if (distRatio > kCharaOne) {
            return;
        }
        const float shadowFade = kCharaOne - distRatio;

        reinterpret_cast<CVector*>(&delta)->Normalize();

        Vec eye;
        {
            CVector up(kCharaZero, 10.0f, kCharaZero);
            CVector eyeTmp;
            PSVECAdd(modelPos, up, eyeTmp);
            eye.x = eyeTmp.x;
            eye.y = eyeTmp.y;
            eye.z = eyeTmp.z;
        }

        CVector lookAtUp(kCharaZero, kCharaOne, kCharaZero);
        CVector shadowUp(kCharaZero, 10.0f, kCharaZero);

        const float shadowDistance = static_cast<float>(CharaPcs.m_texShadowDistance);
        CVector scaledDelta;
        PSVECScale(&delta, scaledDelta, shadowDistance);

        Vec shadowBase;
        {
            Vec scaledDeltaCopy;
            scaledDeltaCopy.x = scaledDelta.x;
            scaledDeltaCopy.y = scaledDelta.y;
            scaledDeltaCopy.z = scaledDelta.z;
            CVector baseTmp;
            PSVECAdd(modelPos, &scaledDeltaCopy, baseTmp);
            shadowBase.x = baseTmp.x;
            shadowBase.y = baseTmp.y;
            shadowBase.z = baseTmp.z;
        }

        Vec shadowPos;
        {
            CVector posTmp;
            PSVECAdd(&shadowBase, shadowUp, posTmp);
            shadowPos.x = posTmp.x;
            shadowPos.y = posTmp.y;
            shadowPos.z = posTmp.z;
        }

        C_MTXLookAt(m_shadowViewMtx, reinterpret_cast<Point3d*>(&shadowPos),
                    static_cast<Vec*>(lookAtUp), reinterpret_cast<Point3d*>(&eye));
        PSMTXCopy(m_shadowViewMtx, viewMtx);

        const float nearZ = CameraPcs.m_nearZ;
        const float farZ = CameraPcs.m_farZ;
        CColor shadowFog;
        shadowFog.color.a = 0xFF;
        shadowFog.color.b = static_cast<unsigned char>(static_cast<int>(255.0f * shadowFade));
        shadowFog.color.g = shadowFog.color.b;
        shadowFog.color.r = shadowFog.color.b;
        _GXColor shadowFogGX = shadowFog.color;
        GXSetFog(GX_FOG_PERSP_LIN, nearZ, nearZ + kCharaOne, nearZ, farZ, shadowFogGX);
    }

    bool restoreFog = false;
    if ((drawPass == 0 || drawPass == 4) && kCharaZero < m_fogBlend) {
        float invBlend = kCharaOne - m_fogBlend;
        float fogBlend = kCharaOne - invBlend * invBlend;
        float fogRemainder = kCharaOne - fogBlend;

        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor whitePart;
        whitePart.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * fogBlend));
        whitePart.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.g) * fogBlend));
        whitePart.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.b) * fogBlend));
        whitePart.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * fogBlend));
        CColor whitePartCopy(whitePart);

        _GXColor graphicFogColor = Graphic.m_fogColor;
        CColor fogBase(graphicFogColor);
        CColor fogPart;
        fogPart.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(fogBase.color.r) * fogRemainder));
        fogPart.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(fogBase.color.g) * fogRemainder));
        fogPart.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(fogBase.color.b) * fogRemainder));
        fogPart.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(fogBase.color.a) * fogRemainder));
        CColor fogPartCopy(fogPart);

        CColor blendedFog;
        blendedFog.color.r = fogPartCopy.color.r + whitePartCopy.color.r;
        blendedFog.color.g = fogPartCopy.color.g + whitePartCopy.color.g;
        blendedFog.color.b = fogPartCopy.color.b + whitePartCopy.color.b;
        blendedFog.color.a = fogPartCopy.color.a + whitePartCopy.color.a;
        CColor blendedFogCopy(blendedFog);

        float nearZ = CameraPcs.m_nearZ;
        float farZ = CameraPcs.m_farZ;
        _GXColor fogColor = blendedFogCopy.color;
        GXSetFog(GX_FOG_PERSP_LIN,
                 Graphic.m_fogStart * fogRemainder + nearZ * fogBlend,
                 (Graphic.m_fogEnd + kCharaOne) * fogRemainder + (nearZ + kCharaOne) * fogBlend,
                 nearZ,
                 farZ,
                 fogColor);
        restoreFog = true;
    }

    if (drawPass == 1 || drawPass == 2) {
        if (drawPass == 2) {
            const unsigned short shadowSize = static_cast<unsigned short>(CharaPcs.m_texShadowSize);
            GXSetTexCopySrc(0, 0, shadowSize, shadowSize);
            GXSetTexCopyDst(static_cast<unsigned short>(CharaPcs.m_texShadowSize),
                            static_cast<unsigned short>(CharaPcs.m_texShadowSize), GX_CTF_R4, GX_FALSE);
            m_shadowTexturePtr = reinterpret_cast<unsigned char*>(CharaPcs.m_texShadowTextureBase) +
                                 CharaPcs.m_texShadowTextureOffset;
            DCInvalidateRange(m_shadowTexturePtr, (CharaPcs.m_texShadowSize * CharaPcs.m_texShadowSize) / 2);
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
        }

        const int shadowMode = static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(1 - drawPass))) >> 5;
        m_model->DrawShadow(viewMtx, shadowMode);

        if (drawPass == 2) {
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
            CharaPcs.m_texShadowTextureOffset += (CharaPcs.m_texShadowSize * CharaPcs.m_texShadowSize) / 2;
            GXPixModeSync();
        }
    } else {
        int modelDrawFlags = 0;
        if (drawPass == 3 && (m_flags & 0x0C) != 0) {
            modelDrawFlags |= 1;
        }
        const unsigned int drawFlags = m_flags;
        modelDrawFlags |= ((drawFlags & 0x400) != 0) ? 2 : 0;
        modelDrawFlags |= ((drawFlags & 0x2000) != 0) ? 4 : 0;
        if (drawPass == 3 && (drawFlags & 0x8000) != 0) {
            modelDrawFlags |= 8;
        }
        modelDrawFlags |= ((drawFlags & 0x100000) != 0) ? 0x10 : 0;
        m_model->Draw(viewMtx, modelDrawFlags, 0);
    }

    if (drawPass == 0 || drawPass == 4) {
        m_model->DrawFur(viewMtx, static_cast<int>((m_flags >> 23) & 1));
    }

    if (restoreFog) {
        Graphic.SetFog(1, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 8007435c
 * PAL Size: 572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::LoadModelASync(int charaKind, unsigned long charaNo, unsigned long textureVariant)
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3)
    {
        System.Printf(const_cast<char*>(s_charaAsyncEntryFmt));
    }

    if (m_asyncFileHandle != 0)
	{
        if (static_cast<unsigned int>(System.m_execParam) >= 2)
        {
            System.Printf(const_cast<char*>(s_charaAsyncCancelFmt));
        }
		File.Close(m_asyncFileHandle);
		m_asyncFileHandle = (CFile::CHandle*)0;
	}

	m_asyncState = 0;
	Graphic._WaitDrawDone((char*)"p_chara.cpp", 0x8C9);
	PartMng.pppDeleteCHandle(this);

	ReleaseShared(m_model);
	ReleaseShared(m_textureSet);
	ReleaseShared(m_modelLoadRef);
	ReleaseShared(m_texLoadRef);
	ReleaseShared(m_pdtLoadRef);

	CharaPcs.releaseUnuseLoadModel(0);
	m_asyncCharaKind = charaKind;
	m_asyncCharaNo = static_cast<int>(charaNo);
	m_asyncTextureVariant = static_cast<int>(textureVariant);
	m_asyncState = 1;
	loadModelASyncFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::loadModelASyncFrame()
{
    char basePath[0x100];
    char path[0x100];
    const int asyncState = m_asyncState;

    if (asyncState == 1 || asyncState == 3 || asyncState == 5) {
        BuildCharaBasePath(m_asyncCharaKind, static_cast<unsigned long>(m_asyncCharaNo), basePath);
        if (m_asyncState == 1) {
            strcpy(path, basePath);
            strcat(path, s_charaModelSuffix);
        } else if (m_asyncState == 3) {
            strcpy(path, basePath);
            strcat(path, s_charaDynamicsSuffix);
        } else {
            if (m_asyncTextureVariant >= 1) {
                sprintf(path, s_charaTextureVariantFmt, basePath, m_asyncTextureVariant + 0x61);
            } else {
                strcpy(path, basePath);
            }
            strcat(path, s_charaTextureSuffix);
        }

        m_asyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (m_asyncFileHandle == 0 && m_asyncState == 3) {
            m_asyncState = 5;
            loadModelASyncFrame();
            return;
        }
        File.ReadASync(m_asyncFileHandle);
        m_asyncState++;
        return;
    }

    if (asyncState != 2 && asyncState != 4 && asyncState != 6) {
        return;
    }
    if (!File.IsCompleted(m_asyncFileHandle)) {
        return;
    }

    if (m_asyncState == 2) {
        void* readBuffer = File.m_readBuffer;
        int keyId = m_asyncCharaNo;
        void* keyTag = reinterpret_cast<void*>(m_asyncCharaKind);
        CLoadModel* loadModel = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
        loadModel->m_keyTag = keyTag;
        loadModel->m_keyId = keyId;
        loadModel->m_mergeFileId = -1;
        loadModel->m_mergeFlags = 0;
        LoadModelArray(&CharaPcs)->Add(loadModel);
        CChara::CModel* model =
            new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
        model->Create(readBuffer, HandleModelStage(m_asyncCharaKind, 0));
        loadModel->m_model = model;
        m_modelLoadRef = loadModel;
        m_modelLoadRef->AddRef();
        m_model = reinterpret_cast<CLoadModel*>(m_modelLoadRef)->m_model;
        m_model->AddRef();
        m_charaKind = m_asyncCharaKind;
        m_charaNo = m_asyncCharaNo;
    } else if (m_asyncState == 4) {
        void* readBuffer = File.m_readBuffer;
        m_model->CreateDynamics(readBuffer, HandleModelStage(m_asyncCharaKind, 0));
    } else {
        void* readBuffer = File.m_readBuffer;
        int charaKind = m_asyncCharaKind;
        int keyId = m_asyncCharaNo;
        void* keyTag = reinterpret_cast<void*>(charaKind);
        CLoadTexture* loadTexture = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
        loadTexture->m_keyTag = keyTag;
        loadTexture->m_keyId = keyId;
        loadTexture->m_variantTag = reinterpret_cast<void*>(m_asyncTextureVariant);
        loadTexture->m_mergeFileId = -1;
        loadTexture->m_mergeFlags = 0;
        LoadTextureArray(&CharaPcs)->Add(loadTexture);
        CTextureSet* textureSet = new (CharaPcs.m_stage, const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
        textureSet->Create(readBuffer, HandleTextureStage(charaKind), 0, 0, 0, 0);
        loadTexture->m_textureSet = textureSet;
        m_texLoadRef = loadTexture;
        m_texLoadRef->AddRef();
        m_textureSet = reinterpret_cast<CLoadTexture*>(m_texLoadRef)->m_textureSet;
        m_textureSet->AddRef();
        m_model->AttachTextureSet(m_textureSet);
        m_textureVariant = m_asyncTextureVariant;
    }

    File.Close(m_asyncFileHandle);
    m_asyncFileHandle = 0;
    if (m_asyncState == 6) {
        m_asyncState = 7;
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_charaAsyncCompleteFmt));
        }
    } else {
        m_asyncState++;
        loadModelASyncFrame();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::CHandle::IsLoadModelASyncCompleted()
{
    return m_asyncState == 7;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::CancelLoadModelASync()
{
    if (m_asyncFileHandle != 0) {
        File.Close(m_asyncFileHandle);
        m_asyncFileHandle = 0;
    }

    m_asyncState = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::CLoadModel()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
    m_model = 0;
    m_streamMode = 0;
    m_streamOffset = 0;
    m_streamSize = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::~CLoadModel()
{
    ReleaseShared(m_model);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::~CLoadAnim()
{
    ReleaseShared(m_anim);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::CLoadTexture()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
    m_variantTag = 0;
    m_textureSet = 0;
    m_streamMode = 0;
    m_streamOffset = 0;
    m_streamSize = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::~CLoadTexture()
{
    ReleaseShared(m_textureSet);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::CLoadPdt()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_variantTag = 0;
    m_pdtSlot = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::~CLoadPdt()
{
    if (m_pdtSlot >= 0) {
        PartPcs.ReleasePdt(m_pdtSlot);
        m_pdtSlot = -1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetAnimStage()
{
	// TODO
}
