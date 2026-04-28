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

private:
    unsigned int m_data;
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

unsigned int m_table__7CMapPcs[3][0x414 / 3 / sizeof(unsigned int)] = {
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_GAME_801D76E0)),
        m_table_desc0__7CMapPcs[0],  m_table_desc0__7CMapPcs[1],  m_table_desc0__7CMapPcs[2],
        m_table_desc1__7CMapPcs[0],  m_table_desc1__7CMapPcs[1],  m_table_desc1__7CMapPcs[2],
        m_table_desc2__7CMapPcs[0],  m_table_desc2__7CMapPcs[1],  m_table_desc2__7CMapPcs[2],
        0x14,                        0,                           m_table_desc3__7CMapPcs[0],
        m_table_desc3__7CMapPcs[1],  m_table_desc3__7CMapPcs[2],  0x1E,
        0,                           m_table_desc4__7CMapPcs[0],  m_table_desc4__7CMapPcs[1],
        m_table_desc4__7CMapPcs[2],  0x2F,                        1,
        m_table_desc5__7CMapPcs[0],  m_table_desc5__7CMapPcs[1],  m_table_desc5__7CMapPcs[2],
        0x35,                        1,                           m_table_desc6__7CMapPcs[0],
        m_table_desc6__7CMapPcs[1],  m_table_desc6__7CMapPcs[2],  0x37,
        1,                           m_table_desc7__7CMapPcs[0],  m_table_desc7__7CMapPcs[1],
        m_table_desc7__7CMapPcs[2],  0x3F,                        1,
    },
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_VIEWER_801D76F0)),
        m_table_desc8__7CMapPcs[0],  m_table_desc8__7CMapPcs[1],  m_table_desc8__7CMapPcs[2],
        m_table_desc9__7CMapPcs[0],  m_table_desc9__7CMapPcs[1],  m_table_desc9__7CMapPcs[2],
        m_table_desc10__7CMapPcs[0], m_table_desc10__7CMapPcs[1], m_table_desc10__7CMapPcs[2],
        0x14,                        0,                           m_table_desc11__7CMapPcs[0],
        m_table_desc11__7CMapPcs[1], m_table_desc11__7CMapPcs[2], 0x1E,
        0,                           m_table_desc12__7CMapPcs[0], m_table_desc12__7CMapPcs[1],
        m_table_desc12__7CMapPcs[2], 0x2F,                        1,
        m_table_desc13__7CMapPcs[0], m_table_desc13__7CMapPcs[1], m_table_desc13__7CMapPcs[2],
        0x35,                        1,                           m_table_desc14__7CMapPcs[0],
        m_table_desc14__7CMapPcs[1], m_table_desc14__7CMapPcs[2], 0x37,
        1,                           m_table_desc15__7CMapPcs[0], m_table_desc15__7CMapPcs[1],
        m_table_desc15__7CMapPcs[2], 0x3F,                        1,
    },
    {
        reinterpret_cast<unsigned int>(const_cast<char*>(s_CMapPcs_PART_801D7700)),
        m_table_desc16__7CMapPcs[0], m_table_desc16__7CMapPcs[1], m_table_desc16__7CMapPcs[2],
        m_table_desc17__7CMapPcs[0], m_table_desc17__7CMapPcs[1], m_table_desc17__7CMapPcs[2],
        m_table_desc18__7CMapPcs[0], m_table_desc18__7CMapPcs[1], m_table_desc18__7CMapPcs[2],
        0x14,                        0,                           m_table_desc19__7CMapPcs[0],
        m_table_desc19__7CMapPcs[1], m_table_desc19__7CMapPcs[2], 0x1E,
        0,                           m_table_desc20__7CMapPcs[0], m_table_desc20__7CMapPcs[1],
        m_table_desc20__7CMapPcs[2], 0x2F,                        1,
        m_table_desc21__7CMapPcs[0], m_table_desc21__7CMapPcs[1], m_table_desc21__7CMapPcs[2],
        0x35,                        1,                           m_table_desc22__7CMapPcs[0],
        m_table_desc22__7CMapPcs[1], m_table_desc22__7CMapPcs[2], 0x37,
        1,                           m_table_desc23__7CMapPcs[0], m_table_desc23__7CMapPcs[1],
        m_table_desc23__7CMapPcs[2], 0x3F,                        1,
    },
};

unsigned int s_loadedStageNo__7CMapPcs;
unsigned int s_loadedMapNo__7CMapPcs;
CRelProfile s_mapRelProfile0__7CMapPcs;
CRelProfile s_mapRelProfile1__7CMapPcs;
CRelProfile s_mapRelProfile2__7CMapPcs;
extern const float DrawRangeDefault;
extern const float kPMapBoundMinInit;
extern const float kPMapBoundMaxInit;
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
	return reinterpret_cast<int>(m_table__7CMapPcs[tableIndex]);
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

    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A0) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A4) = 0;
    *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22994) = mapPtr;
    *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22998) = mapPtr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x2299C) = mapSize;
    if (mapSize != 0) {
        if (mode == 1) {
            *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 2;
        } else if (mode == 2) {
            *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 3;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A2C) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A30) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A34) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A38) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A3C) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A40) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A44) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A48) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A4C) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A50) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A54) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A58) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A5C) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A60) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A64) = 0;
            *reinterpret_cast<void**>(reinterpret_cast<char*>(&MapMng) + 0x22A68) = 0;
        } else {
            *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 1;
        }
    } else {
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&MapMng) + 0x229A8) = 0;
    }

    MapMng.ReadMtx(mapPath);
    MapMng.ReadMpl(mapPath);
    MapMng.ReadOtm(mapPath);
    MapMng.ReadMid(mapPath);

    if (static_cast<unsigned char>(mode - 1) > 1) {
        if ((m_viewerMode != 0) && (strcmp(s_lastLoadedMapPath__7CMapPcs, mapPath) != 0)) {
            strcpy(s_lastLoadedMapPath__7CMapPcs, mapPath);
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
            cameraPos.y += kMapCameraCenterYOffset;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = cameraPos.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = cameraPos.y;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            Printf__7CSystemFPce(
                &System,
                s_map_load_ok_fmt,
                mapPath,
                (int)*reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0xC),
                (int)*reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0x8),
                (*reinterpret_cast<CMemory::CStage**>(&MapMng))->GetHeapUnuse() / 1024);
        }

        CPtrArray<CMapLightHolder*>& mapLightHolderArr =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<char*>(&MapMng) + 0x21450)[1];
        if (static_cast<unsigned int>(mapLightHolderArr.GetSize()) != 0) {
            mapLightHolderArr[0]->GetLightHolder(
                reinterpret_cast<_GXColor*>(reinterpret_cast<char*>(&MapMng) + 0x2298C), static_cast<Vec*>(0));
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
    CMapMng* mapMng = &MapMng;
    unsigned int value = 0;

    for (int count = 2; count != 0; count--) {
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
        if (*reinterpret_cast<CFile::CHandle**>(reinterpret_cast<char*>(mapMng) + 0x22A2C) != 0) {
            return (unsigned long long)value;
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<char*>(mapMng) + 4);
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
                        kMapBoundsCenterScale * (rootNode->m_boundMinX + rootNode->m_boundMaxX);
                    cameraPos.y =
                        kMapBoundsCenterScale * (rootNode->m_boundMinY + rootNode->m_boundMaxY);
                    cameraPos.z =
                        kMapBoundsCenterScale * (rootNode->m_boundMinZ + rootNode->m_boundMaxZ);
                } else {
                    float* mapCenter =
                        reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0xAA8);
                    cameraPos.x = mapCenter[0];
                    cameraPos.y = mapCenter[1];
                    cameraPos.z = mapCenter[2];
                }
            }
            cameraPos.y += kMapCameraCenterYOffset;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0) = cameraPos.x;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4) = cameraPos.y;
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8) = cameraPos.z;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
            Printf__7CSystemFPce(
                &System,
                s_map_load_ok_fmt,
                m_mapName,
                *reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0xC),
                *reinterpret_cast<short*>(reinterpret_cast<char*>(&MapMng) + 0x8),
                (*reinterpret_cast<CMemory::CStage**>(&MapMng))->GetHeapUnuse() / 1024);
        }

        CPtrArray<CMapLightHolder*>& mapLightHolderArr =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<char*>(&MapMng) + 0x21450)[1];
        if (static_cast<unsigned int>(mapLightHolderArr.GetSize()) > 0) {
            mapLightHolderArr[0]->GetLightHolder(reinterpret_cast<_GXColor*>(reinterpret_cast<char*>(&MapMng) + 0x2298C),
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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22988), 0);

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

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22988), 0);

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
        (m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx44 screenMtx;
        Mtx cameraMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x298);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22988), 0);

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
        (m_mapCalcReady == 0) &&
        (m_drawEnabled != 0)) {
        Mtx44 screenMtx;
        Mtx cameraMtx;

        if (static_cast<int>(Game.m_currentSceneId) == 3) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_p_map_cpp_801d7728, 0x2C4);
        }

        MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
        *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

        PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<char*>(&CameraPcs) + 0x4), cameraMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        MapMng.SetViewMtx(cameraMtx, screenMtx);
        Graphic.SetFog(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&MapMng) + 0x22988), 0);

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
            Mtx cameraMtx;
            Mtx44 screenMtx;

            MaterialMan.InitVtxFmt(-1, GX_F32, 0, GX_RGBA4, 0xE, GX_RGBA4, 0xA);

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

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

            if ((*reinterpret_cast<u32*>(CFlat + 0x129C) & 0x02000000) != 0) {
                CBoundHack bound;
                bound = *reinterpret_cast<CBoundHack*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, CColor(0xFF, 0xFF, 0x80, 0xFF).color);
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

            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228EC) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE0);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F0) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE4);
            *reinterpret_cast<float*>(reinterpret_cast<char*>(&MapMng) + 0x228F4) =
                *reinterpret_cast<float*>(reinterpret_cast<char*>(&CameraPcs) + 0xE8);

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

            if ((*reinterpret_cast<u32*>(CFlat + 0x129C) & 0x02000000) != 0) {
                CBoundHack bound;
                bound = *reinterpret_cast<CBoundHack*>(reinterpret_cast<char*>(&CameraPcs) + 0x414);
                DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic, &bound, CColor(0xFF, 0xFF, 0x80, 0xFF).color);
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
