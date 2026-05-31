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
#include "ffcc/ptrarray.h"
#include "ffcc/mapocttree.h"

#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
CMapPcs MapPcs;
extern const char __RTTI__8CManager_8032E508[];
extern const char __RTTI__8CProcess_8032E510[];

class CRelProfile
{
public:
    ~CRelProfile();

private:
    unsigned int m_data;
};

class CRelStopWatch
{
public:
    ~CRelStopWatch();

private:
    unsigned char m_data;
};

unsigned int CMapPcs::m_table_desc0[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc1[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc2[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc3[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc4[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc5[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBefore__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc6[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc7[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfter__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc8[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc9[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc10[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc11[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc12[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc13[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc14[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc15[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc16[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc17[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc18[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc19[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc20[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc21[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc22[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
unsigned int CMapPcs::m_table_desc23[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};

extern const char s_CMapPcs_GAME_801D76E0[];
extern const char s_CMapPcs_VIEWER_801D76F0[];
extern const char s_CMapPcs_PART_801D7700[];

unsigned int CMapPcs::m_table[3][0x414 / 3 / sizeof(unsigned int)] = {
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_GAME_801D76E0)),
        CMapPcs::m_table_desc0[0],  CMapPcs::m_table_desc0[1],  CMapPcs::m_table_desc0[2],
        CMapPcs::m_table_desc1[0],  CMapPcs::m_table_desc1[1],  CMapPcs::m_table_desc1[2],
        CMapPcs::m_table_desc2[0],  CMapPcs::m_table_desc2[1],  CMapPcs::m_table_desc2[2],
        0x14,                        0,                           CMapPcs::m_table_desc3[0],
        CMapPcs::m_table_desc3[1],  CMapPcs::m_table_desc3[2],  0x1E,
        0,                           CMapPcs::m_table_desc4[0],  CMapPcs::m_table_desc4[1],
        CMapPcs::m_table_desc4[2],  0x2F,                        1,
        CMapPcs::m_table_desc5[0],  CMapPcs::m_table_desc5[1],  CMapPcs::m_table_desc5[2],
        0x35,                        1,                           CMapPcs::m_table_desc6[0],
        CMapPcs::m_table_desc6[1],  CMapPcs::m_table_desc6[2],  0x37,
        1,                           CMapPcs::m_table_desc7[0],  CMapPcs::m_table_desc7[1],
        CMapPcs::m_table_desc7[2],  0x3F,                        1,
    },
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_VIEWER_801D76F0)),
        CMapPcs::m_table_desc8[0],  CMapPcs::m_table_desc8[1],  CMapPcs::m_table_desc8[2],
        CMapPcs::m_table_desc9[0],  CMapPcs::m_table_desc9[1],  CMapPcs::m_table_desc9[2],
        CMapPcs::m_table_desc10[0], CMapPcs::m_table_desc10[1], CMapPcs::m_table_desc10[2],
        0x14,                        0,                           CMapPcs::m_table_desc11[0],
        CMapPcs::m_table_desc11[1], CMapPcs::m_table_desc11[2], 0x1E,
        0,                           CMapPcs::m_table_desc12[0], CMapPcs::m_table_desc12[1],
        CMapPcs::m_table_desc12[2], 0x2F,                        1,
        CMapPcs::m_table_desc13[0], CMapPcs::m_table_desc13[1], CMapPcs::m_table_desc13[2],
        0x35,                        1,                           CMapPcs::m_table_desc14[0],
        CMapPcs::m_table_desc14[1], CMapPcs::m_table_desc14[2], 0x37,
        1,                           CMapPcs::m_table_desc15[0], CMapPcs::m_table_desc15[1],
        CMapPcs::m_table_desc15[2], 0x3F,                        1,
    },
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_PART_801D7700)),
        CMapPcs::m_table_desc16[0], CMapPcs::m_table_desc16[1], CMapPcs::m_table_desc16[2],
        CMapPcs::m_table_desc17[0], CMapPcs::m_table_desc17[1], CMapPcs::m_table_desc17[2],
        CMapPcs::m_table_desc18[0], CMapPcs::m_table_desc18[1], CMapPcs::m_table_desc18[2],
        0x14,                        0,                           CMapPcs::m_table_desc19[0],
        CMapPcs::m_table_desc19[1], CMapPcs::m_table_desc19[2], 0x1E,
        0,                           CMapPcs::m_table_desc20[0], CMapPcs::m_table_desc20[1],
        CMapPcs::m_table_desc20[2], 0x2F,                        1,
        CMapPcs::m_table_desc21[0], CMapPcs::m_table_desc21[1], CMapPcs::m_table_desc21[2],
        0x35,                        1,                           CMapPcs::m_table_desc22[0],
        CMapPcs::m_table_desc22[1], CMapPcs::m_table_desc22[2], 0x37,
        1,                           CMapPcs::m_table_desc23[0], CMapPcs::m_table_desc23[1],
        CMapPcs::m_table_desc23[2], 0x3F,                        1,
    },
};

extern unsigned int s_loadedStageNo__7CMapPcs;
extern unsigned int s_loadedMapNo__7CMapPcs;
CRelProfile g_mapStage;
CRelProfile g_mapSection;
CRelProfile g_hit_prof;
unsigned char g_map_calc_prof;
static unsigned char g_map_calc_prof_padding0;
static unsigned char g_map_calc_prof_padding1;
static unsigned char g_map_calc_prof_padding2;
unsigned char g_map_draw_prof;
extern const float DrawRangeDefault;
extern const float kPMapBoundMinInit;
extern const float kPMapBoundMaxInit;
char s_lastLoadedMapPath__7CMapPcs[0x100] = "";
unsigned int s_CMapPcsRttiBase0[3] = {reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E508)), 0, 0};
unsigned int s_CMapPcsRttiBase1[5] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E508)),
    0,
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CProcess_8032E510)),
    0,
    0,
};
extern const char s_p_map_cpp[];
extern const char s_map_load_ok_fmt[];
extern const char s_dvd_map_stage_map_fmt[];
extern "C" void MapFileRead__7CMapMngFPcRUl(CMapMng*);

struct CBoundHack {
    Vec m_min;
    Vec m_max;

    CBoundHack()
    {
        float min = kPMapBoundMinInit;
        m_min.z = min;
        m_min.y = min;
        m_min.x = min;

        float max = kPMapBoundMaxInit;
        m_max.z = max;
        m_max.y = max;
        m_max.x = max;
    }
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapPcs::CMapPcs()
{
    unsigned int* table = &CMapPcs::m_table[0][0];

    table[0x004 / 4] = CMapPcs::m_table_desc0[0];
    table[0x008 / 4] = CMapPcs::m_table_desc0[1];
    table[0x00C / 4] = CMapPcs::m_table_desc0[2];
    table[0x010 / 4] = CMapPcs::m_table_desc1[0];
    table[0x014 / 4] = CMapPcs::m_table_desc1[1];
    table[0x018 / 4] = CMapPcs::m_table_desc1[2];
    table[0x01C / 4] = CMapPcs::m_table_desc2[0];
    table[0x020 / 4] = CMapPcs::m_table_desc2[1];
    table[0x024 / 4] = CMapPcs::m_table_desc2[2];
    table[0x030 / 4] = CMapPcs::m_table_desc3[0];
    table[0x034 / 4] = CMapPcs::m_table_desc3[1];
    table[0x038 / 4] = CMapPcs::m_table_desc3[2];
    table[0x044 / 4] = CMapPcs::m_table_desc4[0];
    table[0x048 / 4] = CMapPcs::m_table_desc4[1];
    table[0x04C / 4] = CMapPcs::m_table_desc4[2];
    table[0x058 / 4] = CMapPcs::m_table_desc5[0];
    table[0x05C / 4] = CMapPcs::m_table_desc5[1];
    table[0x060 / 4] = CMapPcs::m_table_desc5[2];
    table[0x06C / 4] = CMapPcs::m_table_desc6[0];
    table[0x070 / 4] = CMapPcs::m_table_desc6[1];
    table[0x074 / 4] = CMapPcs::m_table_desc6[2];
    table[0x080 / 4] = CMapPcs::m_table_desc7[0];
    table[0x084 / 4] = CMapPcs::m_table_desc7[1];
    table[0x088 / 4] = CMapPcs::m_table_desc7[2];

    table[0x160 / 4] = CMapPcs::m_table_desc8[0];
    table[0x164 / 4] = CMapPcs::m_table_desc8[1];
    table[0x168 / 4] = CMapPcs::m_table_desc8[2];
    table[0x16C / 4] = CMapPcs::m_table_desc9[0];
    table[0x170 / 4] = CMapPcs::m_table_desc9[1];
    table[0x174 / 4] = CMapPcs::m_table_desc9[2];
    table[0x178 / 4] = CMapPcs::m_table_desc10[0];
    table[0x17C / 4] = CMapPcs::m_table_desc10[1];
    table[0x180 / 4] = CMapPcs::m_table_desc10[2];
    table[0x18C / 4] = CMapPcs::m_table_desc11[0];
    table[0x190 / 4] = CMapPcs::m_table_desc11[1];
    table[0x194 / 4] = CMapPcs::m_table_desc11[2];
    table[0x1A0 / 4] = CMapPcs::m_table_desc12[0];
    table[0x1A4 / 4] = CMapPcs::m_table_desc12[1];
    table[0x1A8 / 4] = CMapPcs::m_table_desc12[2];
    table[0x1B4 / 4] = CMapPcs::m_table_desc13[0];
    table[0x1B8 / 4] = CMapPcs::m_table_desc13[1];
    table[0x1BC / 4] = CMapPcs::m_table_desc13[2];
    table[0x1C8 / 4] = CMapPcs::m_table_desc14[0];
    table[0x1CC / 4] = CMapPcs::m_table_desc14[1];
    table[0x1D0 / 4] = CMapPcs::m_table_desc14[2];
    table[0x1DC / 4] = CMapPcs::m_table_desc15[0];
    table[0x1E0 / 4] = CMapPcs::m_table_desc15[1];
    table[0x1E4 / 4] = CMapPcs::m_table_desc15[2];

    table[0x2BC / 4] = CMapPcs::m_table_desc16[0];
    table[0x2C0 / 4] = CMapPcs::m_table_desc16[1];
    table[0x2C4 / 4] = CMapPcs::m_table_desc16[2];
    table[0x2C8 / 4] = CMapPcs::m_table_desc17[0];
    table[0x2CC / 4] = CMapPcs::m_table_desc17[1];
    table[0x2D0 / 4] = CMapPcs::m_table_desc17[2];
    table[0x2D4 / 4] = CMapPcs::m_table_desc18[0];
    table[0x2D8 / 4] = CMapPcs::m_table_desc18[1];
    table[0x2DC / 4] = CMapPcs::m_table_desc18[2];
    table[0x2E8 / 4] = CMapPcs::m_table_desc19[0];
    table[0x2EC / 4] = CMapPcs::m_table_desc19[1];
    table[0x2F0 / 4] = CMapPcs::m_table_desc19[2];
    table[0x2FC / 4] = CMapPcs::m_table_desc20[0];
    table[0x300 / 4] = CMapPcs::m_table_desc20[1];
    table[0x304 / 4] = CMapPcs::m_table_desc20[2];
    table[0x310 / 4] = CMapPcs::m_table_desc21[0];
    table[0x314 / 4] = CMapPcs::m_table_desc21[1];
    table[0x318 / 4] = CMapPcs::m_table_desc21[2];
    table[0x324 / 4] = CMapPcs::m_table_desc22[0];
    table[0x328 / 4] = CMapPcs::m_table_desc22[1];
    table[0x32C / 4] = CMapPcs::m_table_desc22[2];
    table[0x338 / 4] = CMapPcs::m_table_desc23[0];
    table[0x33C / 4] = CMapPcs::m_table_desc23[1];
    table[0x340 / 4] = CMapPcs::m_table_desc23[2];
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
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRelStopWatch::~CRelStopWatch()
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
	return reinterpret_cast<int>(CMapPcs::m_table[tableIndex]);
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
                    float* mapCenter =
                        reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0xAA8);
                    cameraPos.x = mapCenter[0];
                    cameraPos.y = mapCenter[1];
                    cameraPos.z = mapCenter[2];
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
                    float* mapCenter =
                        reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0xAA8);
                    cameraPos.x = mapCenter[0];
                    cameraPos.y = mapCenter[1];
                    cameraPos.z = mapCenter[2];
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
                CBoundHack bound;
                bound = *reinterpret_cast<CBoundHack*>(&CameraPcs.m_shadowRectBound);
                Graphic.DrawBound(*reinterpret_cast<CBound*>(&bound), CColor(0xFF, 0xFF, 0x80, 0xFF).color);
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
                CBoundHack bound;
                bound = *reinterpret_cast<CBoundHack*>(&CameraPcs.m_shadowRectBound);
                const CColor& colorObj = CColor(0xFF, 0xFF, 0x80, 0xFF);
                GXColor color = colorObj.color;
                Graphic.DrawBound(*reinterpret_cast<CBound*>(&bound), color);
            }
        }
    }
}
