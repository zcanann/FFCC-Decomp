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

extern "C" {
void create__7CMapPcsFv(CMapPcs*);
void destroy__7CMapPcsFv(CMapPcs*);
void calcInit__7CMapPcsFv(CMapPcs*);
void calc__7CMapPcsFv(CMapPcs*);
void drawShadow__7CMapPcsFv(CMapPcs*);
void drawBefore__7CMapPcsFv(CMapPcs*);
void draw__7CMapPcsFv(CMapPcs*);
void drawAfter__7CMapPcsFv(CMapPcs*);
void createViewer__7CMapPcsFv(CMapPcs*);
void calcViewer__7CMapPcsFv(CMapPcs*);
void drawBeforeViewer__7CMapPcsFv(CMapPcs*);
void drawViewer__7CMapPcsFv(CMapPcs*);
void drawAfterViewer__7CMapPcsFv(CMapPcs*);
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

static CProcessTableCallback s_mapTableDescCreate = {0, 0xFFFFFFFF,
                                                      reinterpret_cast<unsigned int>(create__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescDestroy = {0, 0xFFFFFFFF,
                                                       reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescCalcInit = {0, 0xFFFFFFFF,
                                                        reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescCalc = {0, 0xFFFFFFFF,
                                                    reinterpret_cast<unsigned int>(calc__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescDrawShadow = {0, 0xFFFFFFFF,
                                                          reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescDrawBefore = {0, 0xFFFFFFFF,
                                                          reinterpret_cast<unsigned int>(drawBefore__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescDraw = {0, 0xFFFFFFFF,
                                                    reinterpret_cast<unsigned int>(draw__7CMapPcsFv)};
static CProcessTableCallback s_mapTableDescDrawAfter = {0, 0xFFFFFFFF,
                                                         reinterpret_cast<unsigned int>(drawAfter__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescCreate = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescDestroy = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescCalcInit = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescCalc = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescDrawShadow = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescDrawBefore = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescDraw = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapViewerTableDescDrawAfter = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescCreate = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescDestroy = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescCalcInit = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescCalc = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescDrawShadow = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescDrawBefore = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescDraw = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
static CProcessTableCallback s_mapPartTableDescDrawAfter = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};

static const char sMapPcsGameTableName[] = "CMapPcs(GAME)";
static const char sMapPcsViewerTableName[] = "CMapPcs(VIEWER)";
static const char sMapPcsPartTableName[] = "CMapPcs(PART)";
static const char sMapPcsManagerClassName[] = "CManager";
static const char sMapPcsProcessClassName[] = "CProcess";

CProcessTable CMapPcs::m_table[3] = {
    {
        const_cast<char*>(sMapPcsGameTableName),
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0x14,                        0,                           0, 0, 0,  0x1E,
        0,                           0, 0, 0,  0x2F,                        1,
        0, 0, 0,
        0x35,                        1,                           0, 0, 0,  0x37,
        1,                           0, 0, 0,  0x3F,                        1,
    },
    {
        const_cast<char*>(sMapPcsViewerTableName),
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0x14,                        0,                           0, 0, 0, 0x1E,
        0,                           0, 0, 0, 0x2F,                        1,
        0, 0, 0,
        0x35,                        1,                           0, 0, 0, 0x37,
        1,                           0, 0, 0, 0x3F,                        1,
    },
    {
        const_cast<char*>(sMapPcsPartTableName),
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0x14,                        0,                           0, 0, 0, 0x1E,
        0,                           0, 0, 0, 0x2F,                        1,
        0, 0, 0,
        0x35,                        1,                           0, 0, 0, 0x37,
        1,                           0, 0, 0, 0x3F,                        1,
    },
};

#pragma inline_max_size(10000)
inline CMapPcs::CMapPcs()
{
    CProcessTable* table = reinterpret_cast<CProcessTable*>(m_table);

    table[0].m_fields.m_create = s_mapTableDescCreate;
    table[0].m_fields.m_destroy = s_mapTableDescDestroy;
    table[0].m_fields.m_entries[0].m_callback = s_mapTableDescCalcInit;
    table[0].m_fields.m_entries[1].m_callback = s_mapTableDescCalc;
    table[0].m_fields.m_entries[2].m_callback = s_mapTableDescDrawShadow;
    table[0].m_fields.m_entries[3].m_callback = s_mapTableDescDrawBefore;
    table[0].m_fields.m_entries[4].m_callback = s_mapTableDescDraw;
    table[0].m_fields.m_entries[5].m_callback = s_mapTableDescDrawAfter;

    table[1].m_fields.m_create = s_mapViewerTableDescCreate;
    table[1].m_fields.m_destroy = s_mapViewerTableDescDestroy;
    table[1].m_fields.m_entries[0].m_callback = s_mapViewerTableDescCalcInit;
    table[1].m_fields.m_entries[1].m_callback = s_mapViewerTableDescCalc;
    table[1].m_fields.m_entries[2].m_callback = s_mapViewerTableDescDrawShadow;
    table[1].m_fields.m_entries[3].m_callback = s_mapViewerTableDescDrawBefore;
    table[1].m_fields.m_entries[4].m_callback = s_mapViewerTableDescDraw;
    table[1].m_fields.m_entries[5].m_callback = s_mapViewerTableDescDrawAfter;

    table[2].m_fields.m_create = s_mapPartTableDescCreate;
    table[2].m_fields.m_destroy = s_mapPartTableDescDestroy;
    table[2].m_fields.m_entries[0].m_callback = s_mapPartTableDescCalcInit;
    table[2].m_fields.m_entries[1].m_callback = s_mapPartTableDescCalc;
    table[2].m_fields.m_entries[2].m_callback = s_mapPartTableDescDrawShadow;
    table[2].m_fields.m_entries[3].m_callback = s_mapPartTableDescDrawBefore;
    table[2].m_fields.m_entries[4].m_callback = s_mapPartTableDescDraw;
    table[2].m_fields.m_entries[5].m_callback = s_mapPartTableDescDrawAfter;
}

CMapPcs MapPcs;
extern unsigned int s_loadedStageNo__7CMapPcs;
extern unsigned int s_loadedMapNo__7CMapPcs;
CRelProfile g_mapStage;
CRelProfile g_mapSection;
unsigned char g_hit_prof ATTRIBUTE_ALIGN(4);
unsigned char g_map_calc_prof ATTRIBUTE_ALIGN(4);
unsigned char g_map_draw_prof ATTRIBUTE_ALIGN(4);
static const float kPMapBoundMinInit = 10000000000.0f;
static const float kPMapBoundMaxInit = -10000000000.0f;
extern "C" const float DrawRangeDefault;
extern "C" const float kMapBoundsCenterScale;
extern "C" const float kMapCameraCenterYOffset;

static inline float LoadFloat(const float& value)
{
    return value;
}
char s_lastLoadedMapPath__7CMapPcs[0x100] = "";
static const char s_p_map_cpp[] = "p_map.cpp";
static const char s_map_load_ok_fmt[] =
    "\n\n=============================================================\n"
    "                   LoadMap [%s] OK\n"
    "                   m_mapobj_n = %d\n"
    "                   m_octtree_n = %d\n"
    "                   memFree=%d Kbyte\n"
    "=============================================================\n\n\n";
static const char s_dvd_map_stage_map_fmt[] = "dvd/map/stg%03d/map%03d";
extern "C" void MapFileRead__7CMapMngFPcRUl(CMapMng*);

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
        MapMng.SetDrawRangeOctTree(LoadFloat(DrawRangeDefault));
        MapMng.SetDrawRangeMapObj(LoadFloat(DrawRangeDefault));
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
                    float center = rootNode->m_bound.m_min.x + rootNode->m_bound.m_max.x;
                    cameraPos.x = center * LoadFloat(kMapBoundsCenterScale);
                    center = rootNode->m_bound.m_min.y + rootNode->m_bound.m_max.y;
                    cameraPos.y = center * LoadFloat(kMapBoundsCenterScale);
                    center = rootNode->m_bound.m_min.z + rootNode->m_bound.m_max.z;
                    cameraPos.z = center * LoadFloat(kMapBoundsCenterScale);
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localTranslateX;
                    cameraPos.y = mapObj->m_localTranslateY;
                    cameraPos.z = mapObj->m_localTranslateZ;
                }
            }
            cameraPos.y += LoadFloat(kMapCameraCenterYOffset);
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
        MapMng.SetDrawRangeOctTree(LoadFloat(DrawRangeDefault));
        MapMng.SetDrawRangeMapObj(LoadFloat(DrawRangeDefault));
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
                    float center = rootNode->m_bound.m_min.x + rootNode->m_bound.m_max.x;
                    cameraPos.x = center * LoadFloat(kMapBoundsCenterScale);
                    center = rootNode->m_bound.m_min.y + rootNode->m_bound.m_max.y;
                    cameraPos.y = center * LoadFloat(kMapBoundsCenterScale);
                    center = rootNode->m_bound.m_min.z + rootNode->m_bound.m_max.z;
                    cameraPos.z = center * LoadFloat(kMapBoundsCenterScale);
                } else {
                    CMapObj* mapObj = MapMng.GetMapObj(1);
                    cameraPos.x = mapObj->m_localTranslateX;
                    cameraPos.y = mapObj->m_localTranslateY;
                    cameraPos.z = mapObj->m_localTranslateZ;
                }
            }
            cameraPos.y += LoadFloat(kMapCameraCenterYOffset);
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
                CBound bound(kPMapBoundMinInit, kPMapBoundMaxInit);
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
                CBound bound(kPMapBoundMinInit, kPMapBoundMaxInit);
                bound = CameraPcs.m_shadowRectBound;
                const CColor& colorObj = CColor(0xFF, 0xFF, 0x80, 0xFF);
                GXColor color = colorObj.color;
                Graphic.DrawBound(bound, color);
            }
        }
    }
}
