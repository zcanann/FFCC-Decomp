#include "ffcc/p_map.h"
#include "ffcc/gxfunc.h"
#include "ffcc/graphic.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"
#include "ffcc/maplight.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/p_light.h"
#include "ffcc/ptrarray.h"

#include <dolphin/mtx.h>
extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801E900C;

extern unsigned char MapPcs[];

extern unsigned int lbl_801E89B8[];
extern unsigned int lbl_801E89C4[];
extern unsigned int lbl_801E89D0[];
extern unsigned int lbl_801E89DC[];
extern unsigned int lbl_801E89E8[];
extern unsigned int lbl_801E89F4[];
extern unsigned int lbl_801E8A00[];
extern unsigned int lbl_801E8A0C[];
extern unsigned int lbl_801E8A18[];
extern unsigned int lbl_801E8A24[];
extern unsigned int lbl_801E8A30[];
extern unsigned int lbl_801E8A3C[];
extern unsigned int lbl_801E8A48[];
extern unsigned int lbl_801E8A54[];
extern unsigned int lbl_801E8A60[];
extern unsigned int lbl_801E8A6C[];
extern unsigned int lbl_801E8A78[];
extern unsigned int lbl_801E8A84[];
extern unsigned int lbl_801E8A90[];
extern unsigned int lbl_801E8A9C[];
extern unsigned int lbl_801E8AA8[];
extern unsigned int lbl_801E8AB4[];
extern unsigned int lbl_801E8AC0[];
extern unsigned int lbl_801E8ACC[];
extern unsigned int lbl_801E8AD8[];

extern unsigned int lbl_8032ECC8;
extern unsigned int lbl_8032ECCC;
extern unsigned int lbl_8032ECD0;
extern unsigned int lbl_8032ECC0;
extern unsigned int lbl_8032ECC4;
extern float DrawRangeDefault;
extern float lbl_8032FA10;
extern "C" char lbl_801E8EEC[];
extern "C" const char lbl_801D7844[];
extern unsigned int CFlatFlags;
extern CMaterialMan MaterialMan;
extern CLightPcs LightPcs;
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
extern "C" const char s_p_map_cpp_801d7728[];
extern "C" void Destroy__7CMapMngFv(CMapMng*);
extern "C" void _MapFileRead__7CMapMngFPcRUl(CMapMng*);

extern "C" void __dl__FPv(void*);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void DrawBound__8CGraphicFR6CBound8_GXColor(CGraphic*, void*, _GXColor);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" void* memset(void*, int, unsigned long);
extern "C" int strcmp(const char*, const char*);
extern "C" char* strcpy(char*, const char*);

struct CRelProfile;
extern "C" CRelProfile* __dt__11CRelProfileFv(CRelProfile* self, short shouldDelete);

struct CBoundHack {
    float p0;
    float p1;
    float p2;
    float p3;
    float p4;
    float p5;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapPcs::CMapPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::Init()
{
	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x174) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* CMapPcs::GetTable(unsigned long tableIndex)
{
	return lbl_801E8AD8 + tableIndex * 0x57;
}

/*
 * --INFO--
 * PAL Address: 0x80035E20
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::create()
{
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17C) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) = 1;
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x184) = 0;

    MapMng.Create();
}

/*
 * --INFO--
 * PAL Address: 0x80035DD0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::createViewer()
{
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17C) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) = 1;
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x184) = 0;

    MapMng.Create();

    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17C) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::LoadMap(char*, void*, unsigned long, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80035A84
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::LoadMap(int stageNo, int mapNo, void* mapPtr, unsigned long mapSize, unsigned char mode)
{
    unsigned int prevStageNo = lbl_8032ECC0;
    unsigned int prevMapNo = lbl_8032ECC4;
    Vec unusedVec;
    char mapPath[0x104];

    lbl_8032ECC0 = static_cast<unsigned int>(stageNo);
    lbl_8032ECC4 = static_cast<unsigned int>(mapNo);
    sprintf(mapPath, lbl_801D7844, stageNo, mapNo);

    if (mode != 2) {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(DrawRangeDefault);
        MapMng.SetDrawRangeMapObj(DrawRangeDefault);
    }

    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A0) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A4) = 0;
    if (mapSize == 0) {
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 0;
    } else if (mode == 1) {
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 2;
    } else if (mode == 2) {
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 3;
        memset(reinterpret_cast<char*>(&MapMng) + 0x22A2C, 0, 0x40);
    } else {
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 1;
    }

    *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22994) = mapPtr;
    *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22998) = mapPtr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x2299C) = static_cast<unsigned int>(mapSize);

    MapMng.ReadMtx(mapPath);
    MapMng.ReadMpl(mapPath);
    MapMng.ReadOtm(mapPath);
    MapMng.ReadMid(mapPath);

    if ((mode != 1) && (mode != 2)) {
        if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17C) != 0) &&
            (strcmp(lbl_801E8EEC, mapPath) != 0)) {
            strcpy(lbl_801E8EEC, mapPath);
            unusedVec.x = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            unusedVec.y = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            unusedVec.z = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);
            MapMng.GetDebugPlaySta(0, &unusedVec);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = unusedVec.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = unusedVec.y + lbl_8032FA10;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = unusedVec.z;
        }

        CPtrArray<CMapLightHolder*>* mapLightHolderArr =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<char*>(&MapMng) + 0x21450);
        if (mapLightHolderArr[1].GetSize() != 0) {
            mapLightHolderArr[1][0]->GetLightHolder(
                reinterpret_cast<_GXColor*>(reinterpret_cast<char*>(&CameraPcs) + 0x1E0), static_cast<Vec*>(0));
        }
    }

    if (mode == 2) {
        lbl_8032ECC0 = prevStageNo;
        lbl_8032ECC4 = prevMapNo;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80035980
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long long CMapPcs::IsLoadMapCompleted()
{
    int* busy = reinterpret_cast<int*>(&MapMng);
    busy += 0x22A2C / sizeof(int);
    unsigned int result = 0;
    int i;

    for (i = 0; i < 2; i++) {
        if (busy[0] != 0) {
            return result;
        }
        if (busy[1] != 0) {
            return result;
        }
        if (busy[2] != 0) {
            return result;
        }
        if (busy[3] != 0) {
            return result;
        }
        if (busy[4] != 0) {
            return result;
        }
        if (busy[5] != 0) {
            return result;
        }
        if (busy[6] != 0) {
            return result;
        }
        if (busy[7] != 0) {
            break;
        }

        busy += 7;
        result += 7;
        if (i == 1) {
            return (static_cast<unsigned long long>(1) << 32) | result;
        }
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x80035958
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::destroy()
{
    Destroy__7CMapMngFv(&MapMng);
}

/*
 * --INFO--
 * PAL Address: 0x80035940
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::calcInit()
{
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22989) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80035624
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::calc()
{
    Vec cameraPos;
    Mtx cameraMtx;
    Mtx44 screenMtx;

    _MapFileRead__7CMapMngFPcRUl(&MapMng);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

    if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x184) == 0) {
        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);
    } else {
        memcpy(cameraMtx, reinterpret_cast<char*>(this) + 0x4, 0x30);
        memcpy(screenMtx, reinterpret_cast<char*>(this) + 0x34, 0x40);
    }
    MapMng.SetViewMtx(cameraMtx, screenMtx);

    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x174) == 0) {
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) = 0;
        MapMng.Calc();
    } else {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(DrawRangeDefault);
        MapMng.SetDrawRangeMapObj(DrawRangeDefault);
        *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22994) = 0;
        *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22998) = 0;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x2299C) = 0;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A0) = 0;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A4) = 0;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 0;
        MapMng.ReadMtx(reinterpret_cast<char*>(this) + 0x74);
        MapMng.ReadMpl(reinterpret_cast<char*>(this) + 0x74);
        MapMng.ReadOtm(reinterpret_cast<char*>(this) + 0x74);
        MapMng.ReadMid(reinterpret_cast<char*>(this) + 0x74);
        if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17C) != 0) &&
            (strcmp(lbl_801E8EEC, reinterpret_cast<char*>(this) + 0x74) != 0)) {
            strcpy(lbl_801E8EEC, reinterpret_cast<char*>(this) + 0x74);
            MapMng.GetDebugPlaySta(0, &cameraPos);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = cameraPos.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = cameraPos.y + lbl_8032FA10;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = cameraPos.z;
        }
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x174) = 0;
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80035604
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::calcViewer()
{
    CMapPcs::calc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void mapInitDrawEnv()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800353f4
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawBefore()
{
    if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0) &&
        (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22978), 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

        MapMng.DrawBefore();

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2B2);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800351e8
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::draw()
{
    if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0) &&
        (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22978), 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

        MapMng.Draw();

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2E0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80034fd4
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawBeforeViewer()
{
    if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0) &&
        (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22978), 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

        MapMng.DrawBefore();

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2B2);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80034dc0
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawViewer()
{
    if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0) &&
        (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22978), 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

        MapMng.Draw();

        if (Game.game.m_currentSceneId == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2E0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80034ba4
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawAfter()
{
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0) {
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0) {
            CBoundHack bound;
            _GXColor debugColor;
            Mtx cameraMtx;
            Mtx44 screenMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

            PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
            PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<char*>(&CameraPcs) + 0x48), screenMtx);

            GXSetColorUpdate(GX_TRUE);
            GXSetAlphaUpdate(GX_FALSE);
            GXSetCullMode(GX_CULL_BACK);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

            _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

            MapMng.DrawAfter();

            if ((CFlatFlags & 0x02000000) != 0) {
                debugColor.r = 0xFF;
                debugColor.g = 0xFF;
                debugColor.b = 0x80;
                debugColor.a = 0xFF;

                bound.p0 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                bound.p1 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x418);
                bound.p2 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x41C);
                bound.p3 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x420);
                bound.p4 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x424);
                bound.p5 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x428);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, debugColor);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80034988
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawAfterViewer()
{
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x178) == 0) {
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x180) != 0) {
            CBoundHack bound;
            _GXColor debugColor;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

            GXSetColorUpdate(GX_TRUE);
            GXSetAlphaUpdate(GX_FALSE);
            GXSetCullMode(GX_CULL_BACK);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

            _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

            MapMng.DrawAfter();

            if ((CFlatFlags & 0x02000000) != 0) {
                debugColor.r = 0xFF;
                debugColor.g = 0xFF;
                debugColor.b = 0x80;
                debugColor.a = 0xFF;

                bound.p0 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                bound.p1 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x418);
                bound.p2 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x41C);
                bound.p3 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x420);
                bound.p4 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x424);
                bound.p5 = *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0x428);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, debugColor);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::GetMapLightHolder(long, _GXColor*, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80035e84
 * PAL Size: 976b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_map_cpp(void)
{
	volatile void** base = reinterpret_cast<volatile void**>(MapPcs);
	*base = &__vt__8CManager;
	*base = &lbl_801E8668;
	*base = &lbl_801E900C;

	unsigned int* dst = lbl_801E8AD8;

	dst[0x004 / 4] = lbl_801E89B8[0];
	dst[0x008 / 4] = lbl_801E89B8[1];
	dst[0x00C / 4] = lbl_801E89B8[2];
	dst[0x010 / 4] = lbl_801E89C4[0];
	dst[0x014 / 4] = lbl_801E89C4[1];
	dst[0x018 / 4] = lbl_801E89C4[2];
	dst[0x01C / 4] = lbl_801E89D0[0];
	dst[0x020 / 4] = lbl_801E89D0[1];
	dst[0x024 / 4] = lbl_801E89D0[2];
	dst[0x030 / 4] = lbl_801E89DC[0];
	dst[0x034 / 4] = lbl_801E89DC[1];
	dst[0x038 / 4] = lbl_801E89DC[2];
	dst[0x044 / 4] = lbl_801E89E8[0];
	dst[0x048 / 4] = lbl_801E89E8[1];
	dst[0x04C / 4] = lbl_801E89E8[2];
	dst[0x058 / 4] = lbl_801E89F4[0];
	dst[0x05C / 4] = lbl_801E89F4[1];
	dst[0x060 / 4] = lbl_801E89F4[2];
	dst[0x06C / 4] = lbl_801E8A00[0];
	dst[0x070 / 4] = lbl_801E8A00[1];
	dst[0x074 / 4] = lbl_801E8A00[2];
	dst[0x080 / 4] = lbl_801E8A0C[0];
	dst[0x084 / 4] = lbl_801E8A0C[1];
	dst[0x088 / 4] = lbl_801E8A0C[2];
	dst[0x160 / 4] = lbl_801E8A18[0];
	dst[0x164 / 4] = lbl_801E8A18[1];
	dst[0x168 / 4] = lbl_801E8A18[2];

	dst[0x16C / 4] = lbl_801E8A24[0];
	dst[0x170 / 4] = lbl_801E8A24[1];
	dst[0x174 / 4] = lbl_801E8A24[2];
	dst[0x178 / 4] = lbl_801E8A30[0];
	dst[0x17C / 4] = lbl_801E8A30[1];
	dst[0x180 / 4] = lbl_801E8A30[2];
	dst[0x18C / 4] = lbl_801E8A3C[0];
	dst[0x190 / 4] = lbl_801E8A3C[1];
	dst[0x194 / 4] = lbl_801E8A3C[2];
	dst[0x1A0 / 4] = lbl_801E8A48[0];
	dst[0x1A4 / 4] = lbl_801E8A48[1];
	dst[0x1A8 / 4] = lbl_801E8A48[2];
	dst[0x1B4 / 4] = lbl_801E8A54[0];
	dst[0x1B8 / 4] = lbl_801E8A54[1];
	dst[0x1BC / 4] = lbl_801E8A54[2];
	dst[0x1C8 / 4] = lbl_801E8A60[0];
	dst[0x1CC / 4] = lbl_801E8A60[1];
	dst[0x1D0 / 4] = lbl_801E8A60[2];
	dst[0x1DC / 4] = lbl_801E8A6C[0];
	dst[0x1E0 / 4] = lbl_801E8A6C[1];
	dst[0x1E4 / 4] = lbl_801E8A6C[2];
	dst[0x2BC / 4] = lbl_801E8A78[0];
	dst[0x2C0 / 4] = lbl_801E8A78[1];
	dst[0x2C4 / 4] = lbl_801E8A78[2];
	dst[0x2C8 / 4] = lbl_801E8A84[0];
	dst[0x2CC / 4] = lbl_801E8A84[1];
	dst[0x2D0 / 4] = lbl_801E8A84[2];
	dst[0x2D4 / 4] = lbl_801E8A90[0];
	dst[0x2D8 / 4] = lbl_801E8A90[1];
	dst[0x2DC / 4] = lbl_801E8A90[2];
	dst[0x2E8 / 4] = lbl_801E8A9C[0];
	dst[0x2EC / 4] = lbl_801E8A9C[1];
	dst[0x2F0 / 4] = lbl_801E8A9C[2];

	dst[0x2FC / 4] = lbl_801E8AA8[0];
	dst[0x300 / 4] = lbl_801E8AA8[1];
	dst[0x304 / 4] = lbl_801E8AA8[2];
	dst[0x310 / 4] = lbl_801E8AB4[0];
	dst[0x314 / 4] = lbl_801E8AB4[1];
	dst[0x318 / 4] = lbl_801E8AB4[2];
	dst[0x324 / 4] = lbl_801E8AC0[0];
	dst[0x328 / 4] = lbl_801E8AC0[1];
	dst[0x32C / 4] = lbl_801E8AC0[2];
	dst[0x338 / 4] = lbl_801E8ACC[0];
	dst[0x33C / 4] = lbl_801E8ACC[1];
	dst[0x340 / 4] = lbl_801E8ACC[2];

	__register_global_object(&lbl_8032ECC8, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x188);
	__register_global_object(&lbl_8032ECCC, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x194);
	__register_global_object(&lbl_8032ECD0, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x1A0);
}

/*
 * --INFO--
 * PAL Address: 0x80036254
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CRelProfile* __dt__11CRelProfileFv(CRelProfile* self, short shouldDelete)
{
	if ((self != 0) && (shouldDelete > 0))
	{
		__dl__FPv(self);
	}
	return self;
}
