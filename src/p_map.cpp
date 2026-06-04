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

class CRelProfile
{
public:
    ~CRelProfile();

private:
    unsigned int m_data;
};

CProcessTableCallback CMapPcs::m_table_desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc3 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc4 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc5 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBefore__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc6 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc7 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfter__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc8 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc9 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc10 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc11 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc12 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc13 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc14 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc15 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc16 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc17 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc18 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc19 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc20 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc21 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc22 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
CProcessTableCallback CMapPcs::m_table_desc23 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};

extern "C" const char s_CMapPcs_GAME_801D76E0[] = "CMapPcs(GAME)";
extern "C" const char s_CMapPcs_VIEWER_801D76F0[] = "CMapPcs(VIEWER)";
extern "C" const char s_CMapPcs_PART_801D7700[] = "CMapPcs(PART)";

CProcessTable CMapPcs::m_table[3] = {
    {
        const_cast<char*>(s_CMapPcs_GAME_801D76E0),
        CMapPcs::m_table_desc0.m_thisOffset,  CMapPcs::m_table_desc0.m_virtualOffset,  CMapPcs::m_table_desc0.m_function,
        CMapPcs::m_table_desc1.m_thisOffset,  CMapPcs::m_table_desc1.m_virtualOffset,  CMapPcs::m_table_desc1.m_function,
        CMapPcs::m_table_desc2.m_thisOffset,  CMapPcs::m_table_desc2.m_virtualOffset,  CMapPcs::m_table_desc2.m_function,
        0x14,                        0,                           CMapPcs::m_table_desc3.m_thisOffset,
        CMapPcs::m_table_desc3.m_virtualOffset,  CMapPcs::m_table_desc3.m_function,  0x1E,
        0,                           CMapPcs::m_table_desc4.m_thisOffset,  CMapPcs::m_table_desc4.m_virtualOffset,
        CMapPcs::m_table_desc4.m_function,  0x2F,                        1,
        CMapPcs::m_table_desc5.m_thisOffset,  CMapPcs::m_table_desc5.m_virtualOffset,  CMapPcs::m_table_desc5.m_function,
        0x35,                        1,                           CMapPcs::m_table_desc6.m_thisOffset,
        CMapPcs::m_table_desc6.m_virtualOffset,  CMapPcs::m_table_desc6.m_function,  0x37,
        1,                           CMapPcs::m_table_desc7.m_thisOffset,  CMapPcs::m_table_desc7.m_virtualOffset,
        CMapPcs::m_table_desc7.m_function,  0x3F,                        1,
    },
    {
        const_cast<char*>(s_CMapPcs_VIEWER_801D76F0),
        CMapPcs::m_table_desc8.m_thisOffset,  CMapPcs::m_table_desc8.m_virtualOffset,  CMapPcs::m_table_desc8.m_function,
        CMapPcs::m_table_desc9.m_thisOffset,  CMapPcs::m_table_desc9.m_virtualOffset,  CMapPcs::m_table_desc9.m_function,
        CMapPcs::m_table_desc10.m_thisOffset, CMapPcs::m_table_desc10.m_virtualOffset, CMapPcs::m_table_desc10.m_function,
        0x14,                        0,                           CMapPcs::m_table_desc11.m_thisOffset,
        CMapPcs::m_table_desc11.m_virtualOffset, CMapPcs::m_table_desc11.m_function, 0x1E,
        0,                           CMapPcs::m_table_desc12.m_thisOffset, CMapPcs::m_table_desc12.m_virtualOffset,
        CMapPcs::m_table_desc12.m_function, 0x2F,                        1,
        CMapPcs::m_table_desc13.m_thisOffset, CMapPcs::m_table_desc13.m_virtualOffset, CMapPcs::m_table_desc13.m_function,
        0x35,                        1,                           CMapPcs::m_table_desc14.m_thisOffset,
        CMapPcs::m_table_desc14.m_virtualOffset, CMapPcs::m_table_desc14.m_function, 0x37,
        1,                           CMapPcs::m_table_desc15.m_thisOffset, CMapPcs::m_table_desc15.m_virtualOffset,
        CMapPcs::m_table_desc15.m_function, 0x3F,                        1,
    },
    {
        const_cast<char*>(s_CMapPcs_PART_801D7700),
        CMapPcs::m_table_desc16.m_thisOffset, CMapPcs::m_table_desc16.m_virtualOffset, CMapPcs::m_table_desc16.m_function,
        CMapPcs::m_table_desc17.m_thisOffset, CMapPcs::m_table_desc17.m_virtualOffset, CMapPcs::m_table_desc17.m_function,
        CMapPcs::m_table_desc18.m_thisOffset, CMapPcs::m_table_desc18.m_virtualOffset, CMapPcs::m_table_desc18.m_function,
        0x14,                        0,                           CMapPcs::m_table_desc19.m_thisOffset,
        CMapPcs::m_table_desc19.m_virtualOffset, CMapPcs::m_table_desc19.m_function, 0x1E,
        0,                           CMapPcs::m_table_desc20.m_thisOffset, CMapPcs::m_table_desc20.m_virtualOffset,
        CMapPcs::m_table_desc20.m_function, 0x2F,                        1,
        CMapPcs::m_table_desc21.m_thisOffset, CMapPcs::m_table_desc21.m_virtualOffset, CMapPcs::m_table_desc21.m_function,
        0x35,                        1,                           CMapPcs::m_table_desc22.m_thisOffset,
        CMapPcs::m_table_desc22.m_virtualOffset, CMapPcs::m_table_desc22.m_function, 0x37,
        1,                           CMapPcs::m_table_desc23.m_thisOffset, CMapPcs::m_table_desc23.m_virtualOffset,
        CMapPcs::m_table_desc23.m_function, 0x3F,                        1,
    },
};

CMapPcs MapPcs;
extern unsigned int s_loadedStageNo__7CMapPcs;
extern unsigned int s_loadedMapNo__7CMapPcs;
CRelProfile g_mapStage;
CRelProfile g_mapSection;
CRelProfile g_hit_prof;
unsigned char g_map_calc_prof;
unsigned char g_map_draw_prof;
extern const float DrawRangeDefault;
extern const float kPMapBoundMinInit;
extern const float kPMapBoundMaxInit;
char s_lastLoadedMapPath__7CMapPcs[0x100] = "";
extern "C" const char s_p_map_cpp[] = "p_map.cpp";
extern "C" const char s_map_load_ok_fmt[] =
    "\n\n=============================================================\n"
    "                   LoadMap [%s] OK\n"
    "                   m_mapobj_n = %d\n"
    "                   m_octtree_n = %d\n"
    "                   memFree=%d Kbyte\n"
    "=============================================================\n\n\n";
extern "C" const char s_dvd_map_stage_map_fmt[] = "dvd/map/stg%03d/map%03d";
extern "C" void MapFileRead__7CMapMngFPcRUl(CMapMng*);

namespace {
struct PMapBound
{
    PMapBound()
    {
        float min = kPMapBoundMinInit;
        float max = kPMapBoundMaxInit;

        m_min.z = min;
        m_min.y = min;
        m_min.x = min;
        m_max.z = max;
        m_max.y = max;
        m_max.x = max;
    }

    void operator=(const CBound& other)
    {
        *this = *reinterpret_cast<const PMapBound*>(&other);
    }

    CBound& AsBound()
    {
        return *reinterpret_cast<CBound*>(this);
    }

    Vec m_min;
    Vec m_max;
};
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
CRelProfile::~CRelProfile()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::Init()
{
	m_forceMapReload = 0;
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
    unsigned int prevStageNo = s_loadedStageNo__7CMapPcs;
    unsigned int prevMapNo = s_loadedMapNo__7CMapPcs;
    Vec cameraPos;
    char mapPath[0x104];

    s_loadedStageNo__7CMapPcs = stageNo;
    s_loadedMapNo__7CMapPcs = mapNo;
    sprintf(mapPath, s_dvd_map_stage_map_fmt, stageNo, mapNo);

    if (mode != 2) {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(DrawRangeDefault);
        MapMng.SetDrawRangeMapObj(DrawRangeDefault);
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
        if ((m_viewerMode != 0) && (strcmp(s_lastLoadedMapPath__7CMapPcs, mapPath) != 0)) {
            strcpy(s_lastLoadedMapPath__7CMapPcs, mapPath);
            if (MapMng.GetDebugPlaySta(0, &cameraPos) == 0) {
                COctNode* rootNode = MapMng.GetOctTreeArray()->GetRootNode();
                if (rootNode != 0) {
                    float center = rootNode->m_boundMinX + rootNode->m_boundMaxX;
                    cameraPos.x = center * kMapBoundsCenterScale;
                    center = rootNode->m_boundMinY + rootNode->m_boundMaxY;
                    cameraPos.y = center * kMapBoundsCenterScale;
                    center = rootNode->m_boundMinZ + rootNode->m_boundMaxZ;
                    cameraPos.z = center * kMapBoundsCenterScale;
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localTranslateX;
                    cameraPos.y = mapObj->m_localTranslateY;
                    cameraPos.z = mapObj->m_localTranslateZ;
                }
            }
            cameraPos.y += kMapCameraCenterYOffset;
            CameraPcs.m_positionX = cameraPos.x;
            CameraPcs.m_positionY = cameraPos.y;
            CameraPcs.m_positionZ = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            System.Printf(
                const_cast<char*>(s_map_load_ok_fmt),
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
        s_loadedStageNo__7CMapPcs = prevStageNo;
        s_loadedMapNo__7CMapPcs = prevMapNo;
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
    unsigned int value = 0;
    CMapMng* map = &MapMng;

    for (int count = 2; count != 0; count--) {
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }
        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        if (map->m_asyncLoadState.m_asyncHandles[0] != 0) {
            return (unsigned long long)value;
        }

        map = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(map) + 4);
        value += 7;
    }

    return ((unsigned long long)1 << 32) | value;
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

    MapFileRead__7CMapMngFPcRUl(&MapMng);
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
        MapMng.SetDrawRangeOctTree(DrawRangeDefault);
        MapMng.SetDrawRangeMapObj(DrawRangeDefault);
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
            (strcmp(s_lastLoadedMapPath__7CMapPcs, m_mapName) != 0)) {
            strcpy(s_lastLoadedMapPath__7CMapPcs, m_mapName);
            if (MapMng.GetDebugPlaySta(0, &cameraPos) == 0) {
                COctNode* rootNode = MapMng.GetOctTreeArray()->GetRootNode();
                if (rootNode != 0) {
                    float center = rootNode->m_boundMinX + rootNode->m_boundMaxX;
                    cameraPos.x = center * kMapBoundsCenterScale;
                    center = rootNode->m_boundMinY + rootNode->m_boundMaxY;
                    cameraPos.y = center * kMapBoundsCenterScale;
                    center = rootNode->m_boundMinZ + rootNode->m_boundMaxZ;
                    cameraPos.z = center * kMapBoundsCenterScale;
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localTranslateX;
                    cameraPos.y = mapObj->m_localTranslateY;
                    cameraPos.z = mapObj->m_localTranslateZ;
                }
            }
            cameraPos.y += kMapCameraCenterYOffset;
            CameraPcs.m_positionX = cameraPos.x;
            CameraPcs.m_positionY = cameraPos.y;
            CameraPcs.m_positionZ = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            System.Printf(
                const_cast<char*>(s_map_load_ok_fmt),
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawShadow()
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
    if ((m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x298);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2B2);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2C4);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2E0);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x298);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2B2);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2C4);
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
            Graphic._WaitDrawDone(const_cast<char*>(s_p_map_cpp), 0x2E0);
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
                PMapBound bound;
                bound = CameraPcs.m_shadowRectBound;
                Graphic.DrawBound(bound.AsBound(), CColor(0xFF, 0xFF, 0x80, 0xFF).color);
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
                PMapBound bound;
                bound = CameraPcs.m_shadowRectBound;
                const CColor& colorObj = CColor(0xFF, 0xFF, 0x80, 0xFF);
                GXColor color = colorObj.color;
                Graphic.DrawBound(bound.AsBound(), color);
            }
        }
    }
}
