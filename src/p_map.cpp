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
#include "ffcc/p_game.h"
#include "ffcc/p_light.h"
#include "ffcc/ptrarray.h"
#include "ffcc/mapocttree.h"

#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
CMapPcs MapPcs;
extern void* __vt__8CManager;
extern "C" void* __vt__7CMapPcs[];
extern "C" void create__7CMapPcsFv(CMapPcs*);
extern "C" void destroy__7CMapPcsFv(CMapPcs*);
extern "C" void calcInit__7CMapPcsFv(CMapPcs*);
extern "C" void calc__7CMapPcsFv(CMapPcs*);
extern "C" void drawShadow__7CMapPcsFv(CMapPcs*);
extern "C" void drawBefore__7CMapPcsFv(CMapPcs*);
extern "C" void draw__7CMapPcsFv(CMapPcs*);
extern "C" void drawAfter__7CMapPcsFv(CMapPcs*);
extern "C" void createViewer__7CMapPcsFv(CMapPcs*);
extern "C" void calcViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawBeforeViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawAfterViewer__7CMapPcsFv(CMapPcs*);

class CRelProfile
{
public:
    ~CRelProfile();
};

unsigned int m_table_desc0__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CMapPcsFv)};
unsigned int m_table_desc1__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int m_table_desc2__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int m_table_desc3__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__7CMapPcsFv)};
unsigned int m_table_desc4__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int m_table_desc5__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBefore__7CMapPcsFv)};
unsigned int m_table_desc6__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__7CMapPcsFv)};
unsigned int m_table_desc7__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfter__7CMapPcsFv)};
unsigned int m_table_desc8__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
unsigned int m_table_desc9__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int m_table_desc10__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int m_table_desc11__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
unsigned int m_table_desc12__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int m_table_desc13__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
unsigned int m_table_desc14__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
unsigned int m_table_desc15__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};
unsigned int m_table_desc16__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__7CMapPcsFv)};
unsigned int m_table_desc17__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CMapPcsFv)};
unsigned int m_table_desc18__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__7CMapPcsFv)};
unsigned int m_table_desc19__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__7CMapPcsFv)};
unsigned int m_table_desc20__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__7CMapPcsFv)};
unsigned int m_table_desc21__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBeforeViewer__7CMapPcsFv)};
unsigned int m_table_desc22__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__7CMapPcsFv)};
unsigned int m_table_desc23__7CMapPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__7CMapPcsFv)};

const char s_CMapPcs_GAME_801D76E0[] = "CMapPcs_GAME";
const char s_CMapPcs_VIEWER_801D76F0[] = "CMapPcs_VIEWER";
const char s_CMapPcs_PART_801D7700[] = "CMapPcs_PART";

unsigned int PTR_s_CMapPcs_GAME__801e8ad8[3][0x414 / 3 / sizeof(unsigned int)] = {
    {reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_GAME_801D76E0)), 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0x14, 0, 0, 0, 0, 0x1E, 0, 0, 0, 0, 0x2F, 1, 0, 0, 0, 0x35, 1, 0, 0, 0, 0x37, 1, 0, 0, 0,
     0x3F, 1},
    {reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_VIEWER_801D76F0)), 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0x14, 0, 0, 0, 0, 0x1E, 0, 0, 0, 0, 0x2F, 1, 0, 0, 0, 0x35, 1, 0, 0, 0, 0x37, 1, 0, 0, 0,
     0x3F, 1},
    {reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_PART_801D7700)), 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0x14, 0, 0, 0, 0, 0x1E, 0, 0, 0, 0, 0x2F, 1, 0, 0, 0, 0x35, 1, 0, 0, 0, 0x37, 1, 0, 0, 0,
     0x3F, 1},
};

CRelProfile g_hit_prof;
CRelProfile g_map_calc_prof;
CRelProfile g_map_draw_prof;
unsigned short s_loadedStageNo__7CMapPcs;
unsigned short s_loadedMapNo__7CMapPcs;
extern const float DrawRangeDefault;
char s_lastLoadedMapPath__7CMapPcs[0x100] = "";
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
static const char s_p_map_cpp_801d7728[] = "p_map.cpp";
static const char s_map_load_ok_fmt[] =
    "\n\n============================================================\n"
    "                LoadMap [%s] OK\n"
    "                 m_mapobj_n = %d\n"
    "                m_octtree_n = %d\n"
    "                 memFree=%d Kbyte\n"
    "============================================================\n\n\n";
static const char s_dvd_map_stage_map_fmt[] = "dvd/map/stg%03d/map%03d";
extern "C" void Destroy__7CMapMngFv(CMapMng*);
extern "C" void MapFileRead__7CMapMngFPcRUl(CMapMng*);
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);

extern "C" void __dl__FPv(void*);
extern "C" void DrawBound__8CGraphicFR6CBound8_GXColor(CGraphic*, void*, _GXColor);

struct CBoundHack {
    u32 p0;
    u32 p1;
    u32 p2;
    u32 p3;
    u32 p4;
    u32 p5;
};

struct CMapMngAsyncLoadState {
    void* m_mapLoadStart;
    void* m_mapLoadCursor;
    unsigned int m_mapLoadSize;
    int m_asyncReadIndex;
    int m_asyncOpenIndex;
    int m_mapReadMode;
    int m_fileSizes[16];
    unsigned int m_fileChecksums[16];
    CFile::CHandle* m_asyncHandles[16];
};

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
CMapPcs::CMapPcs()
{
    unsigned int* dst = &PTR_s_CMapPcs_GAME__801e8ad8[0][0];

    dst[0x004 / 4] = m_table_desc0__7CMapPcs[0];
    dst[0x008 / 4] = m_table_desc0__7CMapPcs[1];
    dst[0x00C / 4] = m_table_desc0__7CMapPcs[2];
    dst[0x010 / 4] = m_table_desc1__7CMapPcs[0];
    dst[0x014 / 4] = m_table_desc1__7CMapPcs[1];
    dst[0x018 / 4] = m_table_desc1__7CMapPcs[2];
    dst[0x01C / 4] = m_table_desc2__7CMapPcs[0];
    dst[0x020 / 4] = m_table_desc2__7CMapPcs[1];
    dst[0x024 / 4] = m_table_desc2__7CMapPcs[2];
    dst[0x030 / 4] = m_table_desc3__7CMapPcs[0];
    dst[0x034 / 4] = m_table_desc3__7CMapPcs[1];
    dst[0x038 / 4] = m_table_desc3__7CMapPcs[2];
    dst[0x044 / 4] = m_table_desc4__7CMapPcs[0];
    dst[0x048 / 4] = m_table_desc4__7CMapPcs[1];
    dst[0x04C / 4] = m_table_desc4__7CMapPcs[2];
    dst[0x058 / 4] = m_table_desc5__7CMapPcs[0];
    dst[0x05C / 4] = m_table_desc5__7CMapPcs[1];
    dst[0x060 / 4] = m_table_desc5__7CMapPcs[2];
    dst[0x06C / 4] = m_table_desc6__7CMapPcs[0];
    dst[0x070 / 4] = m_table_desc6__7CMapPcs[1];
    dst[0x074 / 4] = m_table_desc6__7CMapPcs[2];
    dst[0x080 / 4] = m_table_desc7__7CMapPcs[0];
    dst[0x084 / 4] = m_table_desc7__7CMapPcs[1];
    dst[0x088 / 4] = m_table_desc7__7CMapPcs[2];
    dst[0x160 / 4] = m_table_desc8__7CMapPcs[0];
    dst[0x164 / 4] = m_table_desc8__7CMapPcs[1];
    dst[0x168 / 4] = m_table_desc8__7CMapPcs[2];
    dst[0x16C / 4] = m_table_desc9__7CMapPcs[0];
    dst[0x170 / 4] = m_table_desc9__7CMapPcs[1];
    dst[0x174 / 4] = m_table_desc9__7CMapPcs[2];
    dst[0x178 / 4] = m_table_desc10__7CMapPcs[0];
    dst[0x17C / 4] = m_table_desc10__7CMapPcs[1];
    dst[0x180 / 4] = m_table_desc10__7CMapPcs[2];
    dst[0x18C / 4] = m_table_desc11__7CMapPcs[0];
    dst[0x190 / 4] = m_table_desc11__7CMapPcs[1];
    dst[0x194 / 4] = m_table_desc11__7CMapPcs[2];
    dst[0x1A0 / 4] = m_table_desc12__7CMapPcs[0];
    dst[0x1A4 / 4] = m_table_desc12__7CMapPcs[1];
    dst[0x1A8 / 4] = m_table_desc12__7CMapPcs[2];
    dst[0x1B4 / 4] = m_table_desc13__7CMapPcs[0];
    dst[0x1B8 / 4] = m_table_desc13__7CMapPcs[1];
    dst[0x1BC / 4] = m_table_desc13__7CMapPcs[2];
    dst[0x1C8 / 4] = m_table_desc14__7CMapPcs[0];
    dst[0x1CC / 4] = m_table_desc14__7CMapPcs[1];
    dst[0x1D0 / 4] = m_table_desc14__7CMapPcs[2];
    dst[0x1DC / 4] = m_table_desc15__7CMapPcs[0];
    dst[0x1E0 / 4] = m_table_desc15__7CMapPcs[1];
    dst[0x1E4 / 4] = m_table_desc15__7CMapPcs[2];
    dst[0x2BC / 4] = m_table_desc16__7CMapPcs[0];
    dst[0x2C0 / 4] = m_table_desc16__7CMapPcs[1];
    dst[0x2C4 / 4] = m_table_desc16__7CMapPcs[2];
    dst[0x2C8 / 4] = m_table_desc17__7CMapPcs[0];
    dst[0x2CC / 4] = m_table_desc17__7CMapPcs[1];
    dst[0x2D0 / 4] = m_table_desc17__7CMapPcs[2];
    dst[0x2D4 / 4] = m_table_desc18__7CMapPcs[0];
    dst[0x2D8 / 4] = m_table_desc18__7CMapPcs[1];
    dst[0x2DC / 4] = m_table_desc18__7CMapPcs[2];
    dst[0x2E8 / 4] = m_table_desc19__7CMapPcs[0];
    dst[0x2EC / 4] = m_table_desc19__7CMapPcs[1];
    dst[0x2F0 / 4] = m_table_desc19__7CMapPcs[2];
    dst[0x2FC / 4] = m_table_desc20__7CMapPcs[0];
    dst[0x300 / 4] = m_table_desc20__7CMapPcs[1];
    dst[0x304 / 4] = m_table_desc20__7CMapPcs[2];
    dst[0x310 / 4] = m_table_desc21__7CMapPcs[0];
    dst[0x314 / 4] = m_table_desc21__7CMapPcs[1];
    dst[0x318 / 4] = m_table_desc21__7CMapPcs[2];
    dst[0x324 / 4] = m_table_desc22__7CMapPcs[0];
    dst[0x328 / 4] = m_table_desc22__7CMapPcs[1];
    dst[0x32C / 4] = m_table_desc22__7CMapPcs[2];
    dst[0x338 / 4] = m_table_desc23__7CMapPcs[0];
    dst[0x33C / 4] = m_table_desc23__7CMapPcs[1];
    dst[0x340 / 4] = m_table_desc23__7CMapPcs[2];
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
	return reinterpret_cast<int>(PTR_s_CMapPcs_GAME__801e8ad8[tableIndex]);
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
    CMapMngAsyncLoadState* asyncLoadState =
        reinterpret_cast<CMapMngAsyncLoadState*>(reinterpret_cast<char*>(&MapMng) + 0x22994);
    unsigned short prevStageNo = s_loadedStageNo__7CMapPcs;
    unsigned short prevMapNo = s_loadedMapNo__7CMapPcs;
    Vec unusedVec;
    char mapPath[0x104];

    s_loadedStageNo__7CMapPcs = static_cast<unsigned short>(stageNo);
    s_loadedMapNo__7CMapPcs = static_cast<unsigned short>(mapNo);
    sprintf(mapPath, s_dvd_map_stage_map_fmt, stageNo, mapNo);

    if (mode != 2) {
        MapMng.DestroyMap();
        LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
        MapMng.SetDrawRangeOctTree(DrawRangeDefault);
        MapMng.SetDrawRangeMapObj(DrawRangeDefault);
    }

    asyncLoadState->m_asyncReadIndex = 0;
    asyncLoadState->m_asyncOpenIndex = 0;
    if (mapSize == 0) {
        asyncLoadState->m_mapReadMode = 0;
    } else if (mode == 1) {
        asyncLoadState->m_mapReadMode = 2;
    } else if (mode == 2) {
        asyncLoadState->m_mapReadMode = 3;
        asyncLoadState->m_asyncHandles[0] = 0;
        asyncLoadState->m_asyncHandles[1] = 0;
        asyncLoadState->m_asyncHandles[2] = 0;
        asyncLoadState->m_asyncHandles[3] = 0;
        asyncLoadState->m_asyncHandles[4] = 0;
        asyncLoadState->m_asyncHandles[5] = 0;
        asyncLoadState->m_asyncHandles[6] = 0;
        asyncLoadState->m_asyncHandles[7] = 0;
        asyncLoadState->m_asyncHandles[8] = 0;
        asyncLoadState->m_asyncHandles[9] = 0;
        asyncLoadState->m_asyncHandles[10] = 0;
        asyncLoadState->m_asyncHandles[11] = 0;
        asyncLoadState->m_asyncHandles[12] = 0;
        asyncLoadState->m_asyncHandles[13] = 0;
        asyncLoadState->m_asyncHandles[14] = 0;
        asyncLoadState->m_asyncHandles[15] = 0;
    } else {
        asyncLoadState->m_mapReadMode = 1;
    }

    asyncLoadState->m_mapLoadStart = mapPtr;
    asyncLoadState->m_mapLoadCursor = mapPtr;
    asyncLoadState->m_mapLoadSize = static_cast<unsigned int>(mapSize);

    MapMng.ReadMtx(mapPath);
    MapMng.ReadMpl(mapPath);
    MapMng.ReadOtm(mapPath);
    MapMng.ReadMid(mapPath);

    if ((mode != 1) && (mode != 2)) {
        if ((m_viewerMode != 0) &&
            (strcmp(s_lastLoadedMapPath__7CMapPcs, mapPath) != 0)) {
            strcpy(s_lastLoadedMapPath__7CMapPcs, mapPath);
            if (MapMng.GetDebugPlaySta(0, &unusedVec) == 0) {
                COctNode* rootNode =
                    *reinterpret_cast<COctNode**>(reinterpret_cast<char*>(&MapMng) + 0x18);
                if (rootNode != 0) {
                    unusedVec.x =
                        (rootNode->m_boundMinX + rootNode->m_boundMaxX) * kMapBoundsCenterScale;
                    unusedVec.y =
                        (rootNode->m_boundMinY + rootNode->m_boundMaxY) * kMapBoundsCenterScale;
                    unusedVec.z =
                        (rootNode->m_boundMinZ + rootNode->m_boundMaxZ) * kMapBoundsCenterScale;
                } else {
                    float* mapCenter =
                        reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0xAA8);
                    unusedVec.x = mapCenter[0];
                    unusedVec.y = mapCenter[1];
                    unusedVec.z = mapCenter[2];
                }
            }
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = unusedVec.y + kMapCameraCenterYOffset;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = unusedVec.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = unusedVec.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) > 2U) {
            CMemory::CStage* mapStage = *reinterpret_cast<CMemory::CStage**>(&MapMng);
            unsigned int heapUnuse = mapStage->GetHeapUnuse();

            Printf__7CSystemFPce(
                &System,
                s_map_load_ok_fmt,
                mapPath,
                (int)*reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0xC),
                (int)*reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0x8),
                ((int)heapUnuse >> 10) +
                    (unsigned int)(((int)heapUnuse < 0) && ((heapUnuse & 0x3FF) != 0)));
        }

        CPtrArray<CMapLightHolder*>* mapLightHolderArr =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<char*>(&MapMng) + 0x21450);
        int mapLightHolderCount = mapLightHolderArr[1].GetSize();
        if (mapLightHolderCount != 0) {
            mapLightHolderArr[1][0]->GetLightHolder(
                reinterpret_cast<_GXColor*>(reinterpret_cast<char*>(&CameraPcs) + 0x1E0), static_cast<Vec*>(0));
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
    char* mapMng = reinterpret_cast<char*>(&MapMng);
    unsigned int value = 0;

    for (int count = 2; count != 0; count--) {
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
        if (*reinterpret_cast<CFile::CHandle**>(mapMng + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng += 4;
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

    MapFileRead__7CMapMngFPcRUl(&MapMng);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

    if (m_useStoredViewMtx != 0) {
        memcpy(cameraMtx, m_viewMtx, sizeof(Mtx));
        memcpy(screenMtx, m_screenMtx, sizeof(Mtx44));
    } else {
        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    }
    MapMng.SetViewMtx(cameraMtx, screenMtx);

    if (m_forceMapReload != 0) {
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
        MapMng.ReadMtx(m_mapName);
        MapMng.ReadMpl(m_mapName);
        MapMng.ReadOtm(m_mapName);
        MapMng.ReadMid(m_mapName);
        if ((m_viewerMode != 0) &&
            (strcmp(s_lastLoadedMapPath__7CMapPcs, m_mapName) != 0)) {
            strcpy(s_lastLoadedMapPath__7CMapPcs, m_mapName);
            if (MapMng.GetDebugPlaySta(0, &cameraPos) == 0) {
                COctNode* rootNode =
                    *reinterpret_cast<COctNode**>(reinterpret_cast<char*>(&MapMng) + 0x18);
                if (rootNode != 0) {
                    cameraPos.x =
                        (rootNode->m_boundMinX + rootNode->m_boundMaxX) * kMapBoundsCenterScale;
                    cameraPos.y =
                        (rootNode->m_boundMinY + rootNode->m_boundMaxY) * kMapBoundsCenterScale;
                    cameraPos.z =
                        (rootNode->m_boundMinZ + rootNode->m_boundMaxZ) * kMapBoundsCenterScale;
                } else {
                    float* mapCenter =
                        reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0xAA8);
                    cameraPos.x = mapCenter[0];
                    cameraPos.y = mapCenter[1];
                    cameraPos.z = mapCenter[2];
                }
            }
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = cameraPos.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = cameraPos.y + kMapCameraCenterYOffset;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) > 2U) {
            CMemory::CStage* mapStage = *reinterpret_cast<CMemory::CStage**>(&MapMng);
            int heapUnuse = mapStage->GetHeapUnuse();
            int heapUnuseKB = (heapUnuse >> 10) + static_cast<int>((heapUnuse < 0) && ((heapUnuse & 0x3FF) != 0));

            Printf__7CSystemFPce(
                &System,
                s_map_load_ok_fmt,
                m_mapName,
                *reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0xC),
                *reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0x8),
                heapUnuseKB);
        }

        CPtrArray<CMapLightHolder*>* mapLightHolderArr =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<char*>(&MapMng) + 0x21450);
        if (mapLightHolderArr[1].GetSize() != 0) {
            mapLightHolderArr[1][0]->GetLightHolder(reinterpret_cast<_GXColor*>(reinterpret_cast<char*>(&MapMng) + 0x2298C),
                                                    static_cast<Vec*>(0));
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
    if ((m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.m_currentSceneId == 3) {
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
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
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

        if (Game.m_currentSceneId == 3) {
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
    if ((m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.m_currentSceneId == 3) {
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
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
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

        if (Game.m_currentSceneId == 3) {
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
    if ((m_drawEnabled != 0) &&
        (m_mapCalcReady == 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.m_currentSceneId == 3) {
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
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
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

        if (Game.m_currentSceneId == 3) {
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
    if ((m_drawEnabled != 0) &&
        (m_mapCalcReady == 0)) {
        Mtx cameraMtx;
        Mtx44 screenMtx;

        if (Game.m_currentSceneId == 3) {
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
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
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

        if (Game.m_currentSceneId == 3) {
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
    if (m_mapCalcReady == 0) {
        if (m_drawEnabled != 0) {
            CBoundHack bound;
            Mtx cameraMtx;
            Mtx44 screenMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

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
                CColor debugColor(0xFF, 0xFF, 0x80, 0xFF);
                bound = *reinterpret_cast<CBoundHack*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, debugColor.color);
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
            CBoundHack bound;
            Mtx cameraMtx;
            Mtx44 screenMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA6, 0xA);

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228DC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228E4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

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
                CColor debugColor(0xFF, 0xFF, 0x80, 0xFF);
                bound = *reinterpret_cast<CBoundHack*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, debugColor.color);
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
