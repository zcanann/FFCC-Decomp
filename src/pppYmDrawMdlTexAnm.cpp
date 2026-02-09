#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "dolphin/os.h"

struct pppYmDrawMdlTexAnmWork {
    u32 m_frame;
    u32 m_wait;
    u32 m_tilesU;
    u32 m_tilesV;
    f32 m_perU;
    f32 m_perV;
};

struct CMapMeshUVLayout {
    u8 _pad0[0x06];
    u16 m_uvCount;
    u8 _pad1[0x30];
    s16* m_uvPairs;
};

extern f32 FLOAT_8033054c;
extern _pppEnvSt* pppEnvStPtr;
extern char DAT_801d9c54[];
extern char s_PerU___0_2f_PerV___0_2f_801d9c38[];

extern "C" {

/*
 * --INFO--
 * PAL Address: 0x8008aa84
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s16* uvPairs;
    int i;

    (void)param3;
    work = (pppYmDrawMdlTexAnmWork*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(DAT_801d9c54);

    work->m_perU = FLOAT_8033054c;
    work->m_perV = FLOAT_8033054c;

    mapMesh = pppEnvStPtr->m_mapMeshPtr;
    if (mapMesh != NULL) {
        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvPairs = uvLayout->m_uvPairs;
        for (i = 0; i < (int)uvLayout->m_uvCount; i++) {
            const f32 u = (f32)uvPairs[0];
            const f32 v = (f32)uvPairs[1];
            if (work->m_perU < u) {
                work->m_perU = u;
            }
            if (work->m_perV < v) {
                work->m_perV = v;
            }
            uvPairs += 2;
        }
        OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, work->m_perU, work->m_perV);
    }
}

/*
 * --INFO--
 * PAL Address: 8008a93c
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3)
{
    (void)param3;
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s16* uvPairs;
    u32 frameIndex;
    u32 frameU;
    u32 i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    frameIndex = work->m_frame;
    if ((frameIndex != 0) && ((mapMesh = pppEnvStPtr->m_mapMeshPtr) != NULL)) {
        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvPairs = uvLayout->m_uvPairs;
        frameU = frameIndex / work->m_tilesU;

        for (i = 0; i < (u32)uvLayout->m_uvCount; i++) {
            uvPairs[0] = (s16)(-((f32)(frameIndex - frameU * work->m_tilesU) * work->m_perU) - (f32)uvPairs[0]);
            uvPairs[1] = (s16)(-((f32)frameU * work->m_perV) - (f32)uvPairs[1]);
            uvPairs += 2;
        }

        DCFlushRange(uvLayout->m_uvPairs, (u32)uvLayout->m_uvCount << 2);
    }

    work->m_frame = 0;
    work->m_tilesV = 0;
    work->m_tilesU = 0;
    work->m_wait = 0x200;
}

/*
 * --INFO--
 * PAL Address: 8008a604
 * PAL Size: 824b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3)
{
    (void)param1;
    (void)param2;
    (void)param3;
    // Update texture animation frame
    // Handle UV coordinate updates and frame counting
}

/*
 * --INFO--
 * PAL Address: 8008a38c
 * PAL Size: 632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3)
{
    (void)param1;
    (void)param2;
    (void)param3;
    // Render texture animated models
    // Matrix transformations and model drawing
}

}
