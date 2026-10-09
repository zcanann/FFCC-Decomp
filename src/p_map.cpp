#include "ffcc/ptrarray.h"
#include "ffcc/p_map.h"
#include "ffcc/gxfunc.h"
#include "ffcc/graphic.h"
#include "ffcc/file.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/color.h"
#include "ffcc/materialman.h"
#include "ffcc/maplight.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/p_light.h"
#include "ffcc/mapocttree.h"

#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: UNUSED
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void MTXConcatVec(Mtx src, Vec* trans, Mtx dst)
{
    static Mtx m = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };

    m[0][3] = trans->x;
    m[1][3] = trans->y;
    m[2][3] = trans->z;
    MTXConcat(src, m, dst);
}

class CRelProfile
{
public:
    ~CRelProfile();
};

inline CMapPcs::CMapPcs()
{
}

CMapPcs MapPcs;

CProcessCallbackTable CMapPcs::m_table[3] = {
    {
        const_cast<char*>("CMapPcs(GAME)"),
        static_cast<CProcessCallback>(&CMapPcs::create),
        static_cast<CProcessCallback>(&CMapPcs::destroy),
        {
            {static_cast<CProcessCallback>(&CMapPcs::calcInit), 0x14, 0},
            {static_cast<CProcessCallback>(&CMapPcs::calc), 0x1E, 0},
            {static_cast<CProcessCallback>(&CMapPcs::drawShadow), 0x2F, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawBefore), 0x35, 1},
            {static_cast<CProcessCallback>(&CMapPcs::draw), 0x37, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawAfter), 0x3F, 1},
        },
    },
    {
        const_cast<char*>("CMapPcs(VIEWER)"),
        static_cast<CProcessCallback>(&CMapPcs::createViewer),
        static_cast<CProcessCallback>(&CMapPcs::destroy),
        {
            {static_cast<CProcessCallback>(&CMapPcs::calcInit), 0x14, 0},
            {static_cast<CProcessCallback>(&CMapPcs::calcViewer), 0x1E, 0},
            {static_cast<CProcessCallback>(&CMapPcs::drawShadow), 0x2F, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawBeforeViewer), 0x35, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawViewer), 0x37, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawAfterViewer), 0x3F, 1},
        },
    },
    {
        const_cast<char*>("CMapPcs(PART)"),
        static_cast<CProcessCallback>(&CMapPcs::createViewer),
        static_cast<CProcessCallback>(&CMapPcs::destroy),
        {
            {static_cast<CProcessCallback>(&CMapPcs::calcInit), 0x14, 0},
            {static_cast<CProcessCallback>(&CMapPcs::calcViewer), 0x1E, 0},
            {static_cast<CProcessCallback>(&CMapPcs::drawShadow), 0x2F, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawBeforeViewer), 0x35, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawViewer), 0x37, 1},
            {static_cast<CProcessCallback>(&CMapPcs::drawAfterViewer), 0x3F, 1},
        },
    },
};

unsigned int g_mapStage;
unsigned int g_mapSection;
CRelProfile g_hit_prof ATTRIBUTE_ALIGN(4);
CRelProfile g_map_calc_prof ATTRIBUTE_ALIGN(4);
CRelProfile g_map_draw_prof ATTRIBUTE_ALIGN(4);

static char oldMapFileName[0x100] = "";

/*
 * --INFO--
 * PAL Address: 0x80036254
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CRelProfile::~CRelProfile()
{
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void mapInitDrawEnv()
{
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
}

/*
 * --INFO--
 * PAL Address: 0x80035E78
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::Init()
{
	m_forceMapReload = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80035E74
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::Quit()
{
}

/*
 * --INFO--
 * PAL Address: 0x80035E60
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapPcs::GetTable(unsigned long tableIndex)
{
	return reinterpret_cast<int>(&CMapPcs::m_table[tableIndex]);
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
    m_viewerMode = 0;
    m_drawEnabled = 1;
    m_useStoredViewMtx = 0;

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
    m_viewerMode = 0;
    m_drawEnabled = 1;
    m_useStoredViewMtx = 0;

    MapMng.Create();

    m_viewerMode = 1;
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
    unsigned int prevStageNo = g_mapStage;
    unsigned int prevMapNo = g_mapSection;
    Vec cameraPos;
    char mapPath[0x104];

    g_mapStage = stageNo;
    g_mapSection = mapNo;
    sprintf(mapPath, "dvd/map/stg%03d/map%03d", stageNo, mapNo);

    if (mode != 2) {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(1000000000.0f);
        MapMng.SetDrawRangeMapObj(1000000000.0f);
    }

    MapMng.m_asyncLoadState.m_mapLoadStart = mapPtr;
    MapMng.m_asyncLoadState.m_mapLoadCursor = mapPtr;
    MapMng.m_asyncLoadState.m_mapLoadSize = mapSize;
    MapMng.m_asyncLoadState.m_asyncReadIndex = 0;
    MapMng.m_asyncLoadState.m_asyncOpenIndex = 0;
    if (mapSize != 0) {
        if (mode == 1) {
            MapMng.m_asyncLoadState.m_mapReadMode = 2;
        } else if (mode == 2) {
            MapMng.m_asyncLoadState.m_mapReadMode = 3;
            for (int i = 0; i < 0x10; i++) {
                MapMng.m_asyncLoadState.m_asyncHandles[i] = 0;
            }
        } else {
            MapMng.m_asyncLoadState.m_mapReadMode = 1;
        }
    } else {
        MapMng.m_asyncLoadState.m_mapReadMode = 0;
    }

    MapMng.ReadMtx(mapPath);
    MapMng.ReadMpl(mapPath);
    MapMng.ReadOtm(mapPath);
    MapMng.ReadMid(mapPath);

    if (static_cast<unsigned char>(mode - 1) > 1) {
        if ((m_viewerMode != 0) && (strcmp(oldMapFileName, mapPath) != 0)) {
            strcpy(oldMapFileName, mapPath);
            if (MapMng.GetDebugPlaySta(0, &cameraPos) == 0) {
                COctNode* rootNode = MapMng.GetOctTreeArray()->GetRootNode();
                if (rootNode != 0) {
                    float center = rootNode->m_bound.m_min.x + rootNode->m_bound.m_max.x;
                    center *= 0.5f;
                    cameraPos.x = center;
                    center = rootNode->m_bound.m_min.y + rootNode->m_bound.m_max.y;
                    center *= 0.5f;
                    cameraPos.y = center;
                    center = rootNode->m_bound.m_min.z + rootNode->m_bound.m_max.z;
                    center *= 0.5f;
                    cameraPos.z = center;
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localPosition.x;
                    cameraPos.y = mapObj->m_localPosition.y;
                    cameraPos.z = mapObj->m_localPosition.z;
                }
            }
            cameraPos.y += 1.0f;
            CameraPcs.m_positionX = cameraPos.x;
            CameraPcs.m_positionY = cameraPos.y;
            CameraPcs.m_positionZ = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            System.Printf(
                const_cast<char*>("\n\n=============================================================\n"
    "                   LoadMap [%s] OK\n"
    "                   m_mapobj_n = %d\n"
    "                   m_octtree_n = %d\n"
    "                   memFree=%d Kbyte\n"
    "=============================================================\n\n\n"),
                mapPath,
                static_cast<int>(MapMng.m_mapObjCount),
                static_cast<int>(MapMng.m_octTreeCount),
                MapMng.m_stage->GetHeapUnuse() / 1024);
        }

        CPtrArray<CMapLightHolder*>& mapLightHolderArr = MapMng.GetMapLightHolderArray(1);
        unsigned int mapLightHolderIndex = 0;
        if (static_cast<unsigned int>(mapLightHolderArr.GetSize()) > mapLightHolderIndex) {
            mapLightHolderArr[mapLightHolderIndex]->GetLightHolder(
                &MapMng.m_mapColor, static_cast<Vec*>(0));
        }
    }

    if (mode == 2) {
        g_mapStage = prevStageNo;
        g_mapSection = prevMapNo;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80035980
 * PAL Size: 260b
 * EN Address: 0x8003F834
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapPcs::IsLoadMapCompleted()
{
    return MapMng.IsLoadMap();
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
    MapMng.Destroy();
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
    MapMng.m_colorScaleEnable = 0;
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

    MapMng.LoadMapNoSyncCalc();
    MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
    MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
    MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

    if (m_useStoredViewMtx != 0) {
        memcpy(cameraMtx, m_viewMtx, sizeof(Mtx));
        memcpy(screenMtx, m_screenMtx, sizeof(Mtx44));
    } else {
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    }
    MapMng.SetViewMtx(cameraMtx, screenMtx);

    if (m_forceMapReload != 0) {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(1000000000.0f);
        MapMng.SetDrawRangeMapObj(1000000000.0f);
        MapMng.m_asyncLoadState.m_mapLoadStart = 0;
        MapMng.m_asyncLoadState.m_mapLoadCursor = 0;
        MapMng.m_asyncLoadState.m_mapLoadSize = 0;
        MapMng.m_asyncLoadState.m_asyncReadIndex = 0;
        MapMng.m_asyncLoadState.m_asyncOpenIndex = 0;
        MapMng.m_asyncLoadState.m_mapReadMode = 0;
        MapMng.ReadMtx(m_mapName);
        MapMng.ReadMpl(m_mapName);
        MapMng.ReadOtm(m_mapName);
        MapMng.ReadMid(m_mapName);
        if ((m_viewerMode != 0) &&
            (strcmp(oldMapFileName, m_mapName) != 0)) {
            strcpy(oldMapFileName, m_mapName);
            if (MapMng.GetDebugPlaySta(0, &cameraPos) == 0) {
                COctNode* rootNode = MapMng.GetOctTreeArray()->GetRootNode();
                if (rootNode != 0) {
                    float center = rootNode->m_bound.m_min.x + rootNode->m_bound.m_max.x;
                    center *= 0.5f;
                    cameraPos.x = center;
                    center = rootNode->m_bound.m_min.y + rootNode->m_bound.m_max.y;
                    center *= 0.5f;
                    cameraPos.y = center;
                    center = rootNode->m_bound.m_min.z + rootNode->m_bound.m_max.z;
                    center *= 0.5f;
                    cameraPos.z = center;
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localPosition.x;
                    cameraPos.y = mapObj->m_localPosition.y;
                    cameraPos.z = mapObj->m_localPosition.z;
                }
            }
            cameraPos.y += 1.0f;
            CameraPcs.m_positionX = cameraPos.x;
            CameraPcs.m_positionY = cameraPos.y;
            CameraPcs.m_positionZ = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            System.Printf(
                const_cast<char*>("\n\n=============================================================\n"
    "                   LoadMap [%s] OK\n"
    "                   m_mapobj_n = %d\n"
    "                   m_octtree_n = %d\n"
    "                   memFree=%d Kbyte\n"
    "=============================================================\n\n\n"),
                m_mapName,
                MapMng.m_mapObjCount,
                MapMng.m_octTreeCount,
                MapMng.m_stage->GetHeapUnuse() / 1024);
        }

        CPtrArray<CMapLightHolder*>* mapLightHolderArr = &MapMng.GetMapLightHolderArray(1);
        unsigned int mapLightHolderIndex = 0;
        if (static_cast<unsigned int>(mapLightHolderArr->GetSize()) > mapLightHolderIndex) {
            (*mapLightHolderArr)[mapLightHolderIndex]->GetLightHolder(
                &MapMng.m_mapColor, static_cast<Vec*>(0));
        }

        m_forceMapReload = 0;
        m_mapCalcReady = 1;
    } else {
        m_mapCalcReady = 0;
        MapMng.Calc();
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
 * PAL Address: 0x80035600
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapPcs::drawShadow()
{
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
    if ((m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
        MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
        MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(MapMng.m_fogEnable, 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_FRONT);
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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2B2);
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
    if ((m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
        MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
        MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(MapMng.m_fogEnable, 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_FRONT);
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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2E0);
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
    if ((m_drawEnabled != 0) &&
        (m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx44 screenMtx;
        Mtx cameraMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
        MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
        MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(MapMng.m_fogEnable, 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_FRONT);
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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2B2);
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
    if ((m_drawEnabled != 0) &&
        (m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx44 screenMtx;
        Mtx cameraMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
        MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
        MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(MapMng.m_fogEnable, 0);

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetCullMode(GX_CULL_FRONT);
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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>("p_map.cpp"), 0x2E0);
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
    if (m_mapCalcReady == 0) {
        if (m_drawEnabled != 0) {
            Mtx cameraMtx;
            Mtx44 screenMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

            MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
            MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
            MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

            GXSetColorUpdate(GX_TRUE);
            GXSetAlphaUpdate(GX_FALSE);
            GXSetCullMode(GX_CULL_FRONT);
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

            if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_MapBounds) != 0) {
                CBound bound;
                bound = CameraPcs.m_shadowRectBound;
                Graphic.DrawBound(bound, CColor(0xFF, 0xFF, 0x80, 0xFF).color);
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
    if (m_mapCalcReady == 0) {
        if (m_drawEnabled != 0) {
            Mtx44 screenMtx;
            Mtx cameraMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

            MapMng.m_cameraPosition.x = CameraPcs.m_positionX;
            MapMng.m_cameraPosition.y = CameraPcs.m_positionY;
            MapMng.m_cameraPosition.z = CameraPcs.m_positionZ;

            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

            GXSetColorUpdate(GX_TRUE);
            GXSetAlphaUpdate(GX_FALSE);
            GXSetCullMode(GX_CULL_FRONT);
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

            if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_MapBounds) != 0) {
                CBound bound;
                bound = CameraPcs.m_shadowRectBound;
                const CColor& colorObj = CColor(0xFF, 0xFF, 0x80, 0xFF);
                GXColor color = colorObj.color;
                Graphic.DrawBound(bound, color);
            }
        }
    }
}
