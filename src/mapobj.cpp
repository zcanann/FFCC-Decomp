#include "ffcc/mapobj.h"

#include "ffcc/ptrarray.h"

#include "ffcc/map.h"
#include "ffcc/mapanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/mapshadow.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/p_light.h"
#include "ffcc/system.h"
#include "ffcc/memory.h"
#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

extern const char s_mapobj_cpp[] = "mapobj.cpp";
extern const char sMapObjScaleWithoutNameWarn[] = "エラー！！！ ground_a or obj_a ノード のスケールが １ ではない。\n     古いバージョンの ＯＴＭなのでノード名は不明です。";
extern const char sMapObjScaleWithNameWarn[] = "エラー！！！ ground_a or obj_a ノード %s のスケールが １ ではない。\n";
extern const char sMapObjTooManyAttributesWarn[] = "node %d はこれ以上アトリビュートを追加できません。\n";
_GXColor s_mapObjLightColor = {0xFF, 0xFF, 0xFF, 0xFF};

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

/*
 * --INFO--
 * PAL Address: 0x8002BE34
 * PAL Size: 72b
 * EN Address: 0x800364A4
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtr::~CMapObjAtr()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002BFF0
 * PAL Size: 92b
 * EN Address: 0x80036B30
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrPlaySta::~CMapObjAtrPlaySta()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002C04C
 * PAL Size: 292b
 * EN Address: 0x80036A50
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrMime::~CMapObjAtrMime()
{
    int i = 0;

    while (i < static_cast<int>(m_vertexListCount)) {
        if (m_vertexLists[i] != 0) {
            delete m_vertexLists[i];
            m_vertexLists[i] = 0;
        }

        i++;
    }

    if (m_vertexLists != 0) {
        delete m_vertexLists;
        m_vertexLists = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002C170
 * PAL Size: 316b
 * EN Address: 0x800369D4
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrSpotLight::~CMapObjAtrSpotLight()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002C2AC
 * PAL Size: 316b
 * EN Address: 0x80036958
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrPointLight::~CMapObjAtrPointLight()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002C3E8
 * PAL Size: 92b
 * EN Address: 0x800368F4
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrMeshName::~CMapObjAtrMeshName()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002BEFC
 * PAL Size: 48b
 * EN Address: 0x80033780
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::CMapObj()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BE7C
 * PAL Size: 128b
 * EN Address: 0x800337B4
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::~CMapObj()
{
    if (m_attribute != 0) {
        delete m_attribute;
        m_attribute = 0;
    }

    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BF2C
 * PAL Size: 196b
 * EN Address: 0x80033658
 * EN Size: 296b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Init()
{
    m_calcMtxPending = 1;
    m_localMtxDirty = 1;
    m_parent = 0;
    m_mapData = 0;
    m_attribute = 0;

    m_drawPriority = 0x7E;
    m_baseDrawPriority = 0x7E;
    m_octTreeIndex = -1;
    m_unknown20 = 0;
    m_disableZWrite = 0;
    m_useAmbientColor = 0;

    m_objId = 0xFFFF;
    m_effectId = 0xFFFF;
    m_groupId = 0xFFFF;
    m_showFlags = 1;
    m_unknown19 = 1;
    m_meshId = 0xFFFF;

    m_cameraSemiTransFar = 1000000000000000.0f;
    m_cameraSemiTransNear = 1000000000000000.0f;
    m_cameraSemiTransMinAlpha = 1000000000000000.0f;
    m_cameraSemiTransMaxAlpha = -1.0f;

    m_cameraSemiTransStep = 0;
    m_cameraSemiTransTargetAlpha = 0;
    m_cameraSemiTransAlpha = 0;
    m_colorAlphaRate = 0xFF;
    m_lightAlpha = 0xFF;
    m_bumpLight = 0;
    m_bumpObjId = -1;
    m_enableFullScreenShadow = 1;
    m_shadowTarget = -1;

    m_transRateZ = 0.0f;
    m_transRateY = 0.0f;
    m_transRateX = 0.0f;
    m_bumpTexMatrixMode = 0;
    m_zBufferOffset = 0.0f;
    m_cameraSemiTransBeyondMax = 1;
    m_cameraSemiTransActive = 0;
    m_lightSetIndex = -1;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x80036544
 * EN Size: 16b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtr::CMapObjAtr()
{
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x800364FC
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrPlaySta::CMapObjAtrPlaySta()
{
    m_type = CMapObjAtr::PLAY_STA;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x80036554
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrMime::CMapObjAtrMime()
{
    m_type = CMapObjAtr::MIME;
    m_vertexLists = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8003687C
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapObjAtrMeshName::CMapObjAtrMeshName()
{
    m_type = CMapObjAtr::MESH_NAME;
}

/*
 * --INFO--
 * PAL Address: 0x8002A5B0
 * PAL Size: 6240b
 * EN Address: 0x8003384C
 * EN Size: 6764b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::ReadOtmObj(CChunkFile& chunkFile)
{
    enum {
        CHUNK_AMBI = 0x414D4249,
        CHUNK_ANIM = 0x414E494D,
        CHUNK_BOBJ = 0x424F424A,
        CHUNK_EFID = 0x45464944,
        CHUNK_FSDW = 0x46534457,
        CHUNK_GBID = 0x47424944,
        CHUNK_GEOM = 0x47454F4D,
        CHUNK_ID = 0x49442020,
        CHUNK_LTST = 0x4C545354,
        CHUNK_LDAT = 0x4C444154,
        CHUNK_LSDW = 0x4C534457,
        CHUNK_MIME = 0x4D494D45,
        CHUNK_MSID = 0x4D534944,
        CHUNK_PIDX = 0x50494458,
        CHUNK_PLIT = 0x504C4954,
        CHUNK_PSTA = 0x50535441,
        CHUNK_PRIO = 0x5052494F,
        CHUNK_SDST = 0x53445354,
        CHUNK_SHKI = 0x53484B49,
        CHUNK_SLIT = 0x534C4954,
        CHUNK_TFRM = 0x5446524D,
        CHUNK_TRNS = 0x54524E53,
        CHUNK_CFRM = 0x4346524D,
        CHUNK_CJUN = 0x434A554E,
        CHUNK_CKEY = 0x434B4559,
        CHUNK_FRAM = 0x4652414D,
        CHUNK_JUN = 0x4A554E20,
        CHUNK_KEY = 0x4B455920,
        CHUNK_MFRM = 0x4D46524D,
        CHUNK_MJUN = 0x4D4A554E,
        CHUNK_MKEY = 0x4D4B4559,
        CHUNK_VTX = 0x56545820,
        CHUNK_VTXL = 0x5654584C,
    };

    CMapMng& mng = MapMng;

    Init();

    chunkFile.PushChunk();
    int objIndex = this - MapMng.GetMapObjArray();
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case CHUNK_PIDX: {
            short parentIdx = static_cast<short>(chunkFile.Get2());
            int meshOrHitIdx = static_cast<short>(chunkFile.Get2());

            m_meshType = chunkFile.Get1();
            m_mapDataType = chunkFile.Get1();

            if (parentIdx == -1) {
                m_parent = 0;
            } else {
                m_parent = &mng.m_mapObjArray[parentIdx];
            }

            if (meshOrHitIdx == -1) {
                m_mapData = 0;
            } else if (m_mapDataType == 1) {
                m_mapData = &mng.m_mapMeshArray[meshOrHitIdx];
                m_baseDrawPriority = 0;
                m_drawPriority = 0;
            } else if ((m_mapDataType == 2) || (m_mapDataType == 3)) {
                if (meshOrHitIdx != -2) {
                    m_mapData = &mng.m_mapHitArray[meshOrHitIdx];
                } else {
                    CMapObjAtrMeshName* meshName =
                        new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x84) CMapObjAtrMeshName();
                    m_attribute = meshName;
                    char* name = chunkFile.GetString();
                    strncpy(meshName->m_name, name, 0x20);
                }
            }

            if (Game.m_currentSceneId == 4) {
                goto checkScaleMeshType;
            }
            goto checkScaleScene7;
        checkScaleMeshType:
            switch (m_meshType) {
            case 8:
            case 9:
                m_transRateX = 1.0f;
                m_transRateY = 0.0f;
                m_transRateZ = 1.0f;
                break;
            }
            break;
        checkScaleScene7:
            if (Game.m_currentSceneId == 7) {
                goto checkScaleMeshType;
            }
            break;
        }
        case CHUNK_BOBJ: {
            m_bumpObjId = chunkFile.Get2();
            break;
        }
        case CHUNK_TFRM: {
            m_localPosition.x = chunkFile.GetF4();
            m_localPosition.y = chunkFile.GetF4();
            m_localPosition.z = chunkFile.GetF4();
            m_localRotation.x = chunkFile.GetF4();
            m_localRotation.y = chunkFile.GetF4();
            m_localRotation.z = chunkFile.GetF4();
            m_localScale.x = chunkFile.GetF4();
            m_localScale.y = chunkFile.GetF4();
            m_localScale.z = chunkFile.GetF4();

            if (((m_mapDataType == 2) || (m_mapDataType == 3)) &&
                ((1.0f != m_localScale.x) || (1.0f != m_localScale.y) || (1.0f != m_localScale.z))) {
                if (m_attribute == 0) {
                    System.Printf(const_cast<char*>(sMapObjScaleWithoutNameWarn));
                } else {
                    System.Printf(const_cast<char*>(sMapObjScaleWithNameWarn),
                                  reinterpret_cast<CMapObjAtrMeshName*>(m_attribute)->m_name);
                }
                m_localScale.x = 1.0f;
                m_localScale.y = 1.0f;
                m_localScale.z = 1.0f;
            }

            m_localMtxDirty = 1;
            m_calcMtxPending = 1;
            break;
        }
        case CHUNK_PLIT: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrPointLight* pointLight =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0xD4) CMapObjAtrPointLight();

            if (chunk.m_version == 2) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk) != 0) {
                    switch (chunk.m_id) {
                    case CHUNK_LDAT: {
                        pointLight->m_radius = chunkFile.GetF4();
                        pointLight->m_intensity = chunkFile.GetF4();
                        pointLight->m_colorMode = chunkFile.Get1();
                        pointLight->m_useAltColor = chunkFile.Get1();
                        pointLight->m_unknown20 = chunkFile.Get1();
                        chunkFile.Get1();

                        pointLight->m_colorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(pointLight->m_colorCount); i++) {
                            pointLight->m_colors[i].r = chunkFile.Get1();
                            pointLight->m_colors[i].g = chunkFile.Get1();
                            pointLight->m_colors[i].b = chunkFile.Get1();
                            pointLight->m_colors[i].a = chunkFile.Get1();
                        }

                        pointLight->m_altColorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(pointLight->m_altColorCount); i++) {
                            pointLight->m_altColors[i].r = chunkFile.Get1();
                            pointLight->m_altColors[i].g = chunkFile.Get1();
                            pointLight->m_altColors[i].b = chunkFile.Get1();
                            pointLight->m_altColors[i].a = chunkFile.Get1();
                        }

                        pointLight->m_color = pointLight->m_colors[0];
                        pointLight->m_altColor = pointLight->m_altColors[0];
                        break;
                    }
                    case CHUNK_MJUN:
                        pointLight->m_colorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MFRM:
                        pointLight->m_colorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MKEY:
                        pointLight->m_colorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CJUN:
                        pointLight->m_altColorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CFRM:
                        pointLight->m_altColorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CKEY:
                        pointLight->m_altColorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    }
                }
                chunkFile.PopChunk();
            } else if (chunk.m_version == 1) {
                pointLight->m_color.r = chunkFile.Get1();
                pointLight->m_color.g = chunkFile.Get1();
                pointLight->m_color.b = chunkFile.Get1();
                pointLight->m_color.a = chunkFile.Get1();
                pointLight->m_altColor.r = chunkFile.Get1();
                pointLight->m_altColor.g = chunkFile.Get1();
                pointLight->m_altColor.b = chunkFile.Get1();
                pointLight->m_altColor.a = chunkFile.Get1();
                pointLight->m_radius = chunkFile.GetF4();
                pointLight->m_intensity = chunkFile.GetF4();
                pointLight->m_colorMode = chunkFile.Get1();
            }
            m_attribute = pointLight;
            break;
        }
        case CHUNK_SLIT: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrSpotLight* spotLight =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x139) CMapObjAtrSpotLight();

            if (chunk.m_version == 6) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk) != 0) {
                    switch (chunk.m_id) {
                    case CHUNK_LDAT: {
                        spotLight->m_baseColor.r = chunkFile.Get1();
                        spotLight->m_baseColor.g = chunkFile.Get1();
                        spotLight->m_baseColor.b = chunkFile.Get1();
                        spotLight->m_baseColor.a = chunkFile.Get1();
                        spotLight->m_radius = chunkFile.GetF4();
                        spotLight->m_nearRange = chunkFile.GetF4();
                        spotLight->m_farRange = chunkFile.GetF4();
                        spotLight->m_intensity = chunkFile.GetF4();
                        chunkFile.GetF4();
                        spotLight->m_falloff = chunkFile.GetF4();
                        unsigned short targetIndex = chunkFile.Get2();
                        spotLight->m_target = &MapMng.m_mapObjArray[targetIndex];
                        spotLight->m_colorMode = chunkFile.Get1();
                        spotLight->m_useAltColor = chunkFile.Get1();
                        spotLight->m_angle = chunkFile.GetF4();
                        spotLight->m_unknown2E = chunkFile.Get1();
                        spotLight->m_unknown2F = chunkFile.Get1();
                        spotLight->m_keyFrameCount = chunkFile.Get1();
                        chunkFile.Get1();
                        chunkFile.Get4();
                        chunkFile.Get4();
                        chunkFile.Get4();
                        chunkFile.Get4();

                        spotLight->m_colorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(spotLight->m_colorCount); i++) {
                            spotLight->m_colors[i].r = chunkFile.Get1();
                            spotLight->m_colors[i].g = chunkFile.Get1();
                            spotLight->m_colors[i].b = chunkFile.Get1();
                            spotLight->m_colors[i].a = chunkFile.Get1();
                        }

                        spotLight->m_altColorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(spotLight->m_altColorCount); i++) {
                            spotLight->m_altColors[i].r = chunkFile.Get1();
                            spotLight->m_altColors[i].g = chunkFile.Get1();
                            spotLight->m_altColors[i].b = chunkFile.Get1();
                            spotLight->m_altColors[i].a = chunkFile.Get1();
                        }

                        spotLight->m_color = spotLight->m_colors[0];
                        spotLight->m_altColor = spotLight->m_altColors[0];
                        break;
                    }
                    case CHUNK_MJUN:
                        spotLight->m_colorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MFRM:
                        spotLight->m_colorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MKEY:
                        spotLight->m_colorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CJUN:
                        spotLight->m_altColorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CFRM:
                        spotLight->m_altColorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CKEY:
                        spotLight->m_altColorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    }
                }
                chunkFile.PopChunk();
            } else if (chunk.m_version == 5) {
                spotLight->m_color.r = chunkFile.Get1();
                spotLight->m_color.g = chunkFile.Get1();
                spotLight->m_color.b = chunkFile.Get1();
                spotLight->m_color.a = chunkFile.Get1();
                spotLight->m_altColor.r = chunkFile.Get1();
                spotLight->m_altColor.g = chunkFile.Get1();
                spotLight->m_altColor.b = chunkFile.Get1();
                spotLight->m_altColor.a = chunkFile.Get1();
                spotLight->m_baseColor.r = chunkFile.Get1();
                spotLight->m_baseColor.g = chunkFile.Get1();
                spotLight->m_baseColor.b = chunkFile.Get1();
                spotLight->m_baseColor.a = chunkFile.Get1();
                spotLight->m_radius = chunkFile.GetF4();
                spotLight->m_nearRange = chunkFile.GetF4();
                spotLight->m_farRange = chunkFile.GetF4();
                spotLight->m_intensity = chunkFile.GetF4();
                chunkFile.GetF4();
                spotLight->m_falloff = chunkFile.GetF4();
                unsigned short targetIndex = chunkFile.Get2();
                spotLight->m_target = &MapMng.m_mapObjArray[targetIndex];
                spotLight->m_colorMode = chunkFile.Get1();
                spotLight->m_useAltColor = chunkFile.Get1();
                spotLight->m_angle = chunkFile.GetF4();
                spotLight->m_unknown2E = chunkFile.Get1();
            } else if (chunk.m_version == 4) {
                spotLight->m_color.r = chunkFile.Get1();
                spotLight->m_color.g = chunkFile.Get1();
                spotLight->m_color.b = chunkFile.Get1();
                spotLight->m_color.a = chunkFile.Get1();
                spotLight->m_altColor.r = chunkFile.Get1();
                spotLight->m_altColor.g = chunkFile.Get1();
                spotLight->m_altColor.b = chunkFile.Get1();
                spotLight->m_altColor.a = chunkFile.Get1();
                spotLight->m_baseColor.r = chunkFile.Get1();
                spotLight->m_baseColor.g = chunkFile.Get1();
                spotLight->m_baseColor.b = chunkFile.Get1();
                spotLight->m_baseColor.a = chunkFile.Get1();
                spotLight->m_radius = chunkFile.GetF4();
                spotLight->m_nearRange = chunkFile.GetF4();
                spotLight->m_farRange = chunkFile.GetF4();
                spotLight->m_intensity = chunkFile.GetF4();
                chunkFile.GetF4();
                spotLight->m_falloff = chunkFile.GetF4();
                unsigned short targetIndex = chunkFile.Get2();
                spotLight->m_target = &MapMng.m_mapObjArray[targetIndex];
                spotLight->m_colorMode = chunkFile.Get1();
                spotLight->m_useAltColor = chunkFile.Get1();
                spotLight->m_angle = 48.0f;
                spotLight->m_unknown2E = 0;
            }
            m_attribute = spotLight;
            break;
        }
        case CHUNK_ANIM: {
            CMapAnimRun* animRun = static_cast<CMapAnimRun*>(
                operator new(sizeof(CMapAnimRun), MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x21E));
            if (animRun != 0) {
                animRun->m_currentFrame = -1;
            }
            animRun->m_mapAnimIndex = static_cast<unsigned short>(chunkFile.Get4());
            animRun->m_startFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_endFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_triggerFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_loop = chunkFile.Get1();
            if (chunk.m_version == 1) {
                animRun->m_animId = chunkFile.Get1();
            } else {
                animRun->m_animId = 0;
            }
            MapMng.GetMapAnimRunArray().Add(animRun);
            break;
        }
        case CHUNK_AMBI: {
            m_ambientColor.r = chunkFile.Get1();
            m_ambientColor.g = chunkFile.Get1();
            m_ambientColor.b = chunkFile.Get1();
            m_ambientColor.a = chunkFile.Get1();
            m_useAmbientColor = 1;
            break;
        }
        case CHUNK_LSDW: {
            CMapShadow* shadow =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x241) CMapShadow();
            shadow->m_yFilterMode = 0;

            if (chunk.m_version == 4) {
                shadow->m_materialIndex = static_cast<unsigned short>(chunkFile.Get4());
                shadow->m_modelA = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_modelB = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_modelC = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_useFrustum = chunkFile.Get1();
                shadow->m_shadowMaterialType = chunkFile.Get1();
                shadow->m_targetEnabled[1] = (chunkFile.Get1() == 0);
                shadow->m_targetEnabled[0] = (chunkFile.Get1() == 0);
                shadow->m_yFilterMode = chunkFile.Get1();
                chunkFile.Get1();
                shadow->m_targetBoundsScale = chunkFile.GetF4();
                shadow->m_shadowScale = chunkFile.GetF4();
                shadow->m_frustumNear = chunkFile.GetF4();
                shadow->m_frustumFar = chunkFile.GetF4();
                shadow->m_scrollStepX = chunkFile.GetF4();
                shadow->m_scrollStepY = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.x = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.y = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.z = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.x = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.y = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.z = chunkFile.GetF4();
            } else if (chunk.m_version == 3) {
                shadow->m_materialIndex = static_cast<unsigned short>(chunkFile.Get4());
                shadow->m_modelA = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_modelB = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_modelC = &MapMng.m_mapObjArray[chunkFile.Get2()];
                shadow->m_useFrustum = chunkFile.Get1();
                shadow->m_shadowMaterialType = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                shadow->m_shadowScale = chunkFile.GetF4();
                shadow->m_frustumNear = chunkFile.GetF4();
                shadow->m_frustumFar = chunkFile.GetF4();
                shadow->m_scrollStepX = chunkFile.GetF4();
                shadow->m_scrollStepY = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.x = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.y = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_min.z = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.x = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.y = chunkFile.GetF4();
                shadow->m_targetBounds[0].m_max.z = chunkFile.GetF4();
                shadow->m_targetEnabled[1] = 1;
                shadow->m_targetEnabled[0] = 1;
                shadow->m_targetBoundsScale = 1.0f;
            }

            shadow->m_targetBounds[1].m_min.x = shadow->m_targetBounds[0].m_min.x * shadow->m_targetBoundsScale;
            shadow->m_targetBounds[1].m_min.y = shadow->m_targetBounds[0].m_min.y * shadow->m_targetBoundsScale;
            shadow->m_targetBounds[1].m_min.z = shadow->m_targetBounds[0].m_min.z * shadow->m_targetBoundsScale;
            shadow->m_targetBounds[1].m_max.x = shadow->m_targetBounds[0].m_max.x * shadow->m_targetBoundsScale;
            shadow->m_targetBounds[1].m_max.y = shadow->m_targetBounds[0].m_max.y * shadow->m_targetBoundsScale;
            shadow->m_targetBounds[1].m_max.z = shadow->m_targetBounds[0].m_max.z * shadow->m_targetBoundsScale;

            MapMng.GetMapShadowArray().Add(shadow);
            break;
        }
        case CHUNK_PRIO: {
            unsigned char priority = chunkFile.Get1();
            m_drawPriority = priority;
            m_baseDrawPriority = priority;
            break;
        }
        case CHUNK_FSDW: {
            CameraPcs.m_fullScreenShadowEnabled = chunkFile.Get1();
            break;
        }
        case CHUNK_SDST: {
            if (chunk.m_version == 2) {
                m_enableFullScreenShadow = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                m_shadowTarget = static_cast<int>(chunkFile.Get4());
            } else if (chunk.m_version == 1) {
                m_enableFullScreenShadow = chunkFile.Get1();
                if (chunkFile.Get1() != 0) {
                    m_shadowTarget = -1;
                } else {
                    m_shadowTarget = 0;
                }
            } else {
                m_enableFullScreenShadow = chunkFile.Get1();
                m_shadowTarget = -1;
            }
            break;
        }
        case CHUNK_LTST: {
            if (chunk.m_version == 1) {
                m_lightSetIndex = static_cast<int>(chunkFile.Get4());
            } else if (chunkFile.Get1() == 0) {
                m_lightSetIndex = 0;
            }
            break;
        }
        case CHUNK_GEOM: {
            m_zBufferOffset = chunkFile.GetF4();
            m_bumpTexMatrixMode = chunkFile.Get1();
            m_disableZWrite = chunkFile.Get1();
            break;
        }
        case CHUNK_ID: {
            m_objId = chunkFile.Get2();
            break;
        }
        case CHUNK_EFID: {
            m_effectId = chunkFile.Get2();
            break;
        }
        case CHUNK_GBID: {
            m_groupId = chunkFile.Get2();
            break;
        }
        case CHUNK_MSID: {
            m_meshId = static_cast<unsigned short>(chunkFile.Get4());
            break;
        }
        case CHUNK_MIME: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrMime* mimeAttr =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x33B) CMapObjAtrMime();
            CMapObjAtrMime* mime = mimeAttr;

            chunkFile.PushChunk();
            CChunkFile::CChunk mimeChunk;
            while (chunkFile.GetNextChunk(mimeChunk) != 0) {
                switch (mimeChunk.m_id) {
                case CHUNK_VTXL: {
                    mime->m_vertexListCount = static_cast<unsigned char>(mimeChunk.m_arg0);
                    mime->m_vertexLists = reinterpret_cast<float**>(
                        operator new[](static_cast<unsigned long>(mime->m_vertexListCount) << 2,
                                       MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x348));

                    chunkFile.PushChunk();
                    CChunkFile::CChunk vtxChunk;
                    int vtxTableIndex = 0;
                    while (chunkFile.GetNextChunk(vtxChunk) != 0) {
                        switch (vtxChunk.m_id) {
                        case CHUNK_VTX: {
                            float* vtx;
                            mime->m_vertexLists[vtxTableIndex++] = vtx = reinterpret_cast<float*>(operator new[](
                                static_cast<unsigned long>(vtxChunk.m_arg0) * 0xC,
                                MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x353));
                            mime->m_vertexCount = static_cast<int>(vtxChunk.m_arg0);

                            for (int i = 0; i < mime->m_vertexCount; i++) {
                                vtx[0] = chunkFile.GetF4();
                                vtx[1] = chunkFile.GetF4();
                                vtx[2] = chunkFile.GetF4();
                                vtx += 3;
                            }
                            break;
                        }
                        }
                    }
                    chunkFile.PopChunk();
                    break;
                }
                case CHUNK_JUN:
                    mime->m_keyFrame.ReadJun(chunkFile, static_cast<char>(mimeChunk.m_arg0));
                    break;
                case CHUNK_FRAM:
                    mime->m_keyFrame.ReadFrame(chunkFile, mimeChunk.m_arg0);
                    break;
                case CHUNK_KEY:
                    mime->m_keyFrame.ReadKey(chunkFile, mimeChunk.m_arg0);
                    break;
                }
            }
            chunkFile.PopChunk();
            m_attribute = mimeAttr;
            break;
        }
        case CHUNK_TRNS: {
            m_transRateX = chunkFile.GetF4();
            m_transRateY = chunkFile.GetF4();
            m_transRateZ = chunkFile.GetF4();
            break;
        }
        case CHUNK_SHKI: {
            if (MapMng.m_shadowKeyInfoCount >= 4) {
                break;
            }
            CMapShadowKeyInfo* keyInfo = &MapMng.m_shadowKeyInfos[MapMng.m_shadowKeyInfoCount++];
            keyInfo->m_key = chunkFile.Get4();
            keyInfo->m_frame = static_cast<short>(static_cast<int>(chunkFile.GetF4()));
            keyInfo->m_unknown06 = chunkFile.Get1();
            keyInfo->m_unknown07 = chunkFile.Get1();
            keyInfo->m_primaryColor.r = chunkFile.Get1();
            keyInfo->m_primaryColor.g = chunkFile.Get1();
            keyInfo->m_primaryColor.b = chunkFile.Get1();
            keyInfo->m_primaryColor.a = chunkFile.Get1();
            keyInfo->m_secondaryColor.r = chunkFile.Get1();
            keyInfo->m_secondaryColor.g = chunkFile.Get1();
            keyInfo->m_secondaryColor.b = chunkFile.Get1();
            keyInfo->m_secondaryColor.a = chunkFile.Get1();
            break;
        }
        case CHUNK_PSTA: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrPlaySta* playSta =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x39B) CMapObjAtrPlaySta();
            playSta->m_playStaNo = chunkFile.Get1();
            m_attribute = playSta;
            break;
        }
        }
    }
    chunkFile.PopChunk();
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8002A258
 * PAL Size: 856b
 * EN Address: 0x800352B8
 * EN Size: 344b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CalcMtx(float (*parentMtx)[4], unsigned char inDirty)
{
    Mtx mtx;
    CMapObj* obj = this;

    do {
        unsigned char dirty = inDirty;

        if (obj->m_calcMtxPending != 0) {
            obj->m_calcMtxPending = 0;
            if (obj->m_localMtxDirty != 0) {
                PSMTXScale(obj->m_localMtx, obj->m_localScale.x, obj->m_localScale.y, obj->m_localScale.z);
                PSMTXRotRad(mtx, 'x', 0.017453292f * obj->m_localRotation.x);
                PSMTXConcat(mtx, obj->m_localMtx, obj->m_localMtx);
                PSMTXRotRad(mtx, 'y', 0.017453292f * obj->m_localRotation.y);
                PSMTXConcat(mtx, obj->m_localMtx, obj->m_localMtx);
                PSMTXRotRad(mtx, 'z', 0.017453292f * obj->m_localRotation.z);
                PSMTXConcat(mtx, obj->m_localMtx, obj->m_localMtx);
                PSMTXTrans(mtx, obj->m_localPosition.x, obj->m_localPosition.y, obj->m_localPosition.z);
                PSMTXConcat(mtx, obj->m_localMtx, obj->m_localMtx);
            }

            dirty = 1;
        }

        if (dirty != 0) {
            PSMTXConcat(*reinterpret_cast<Mtx*>(parentMtx), obj->m_localMtx, obj->m_worldMtx);
        }

        if (obj->m_child != 0) {
            obj->m_child->CalcMtx(obj->m_worldMtx, dirty);
        }

        obj = obj->m_next;
    } while (obj != 0);
}

/*
 * --INFO--
 * PAL Address: 0x8002A008
 * PAL Size: 592b
 * EN Address: 0x80035410
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow_r(int show)
{
    CMapObj* obj = this;

    do {
        if (show != 0) {
            obj->m_showFlags |= 1;
        } else {
            obj->m_showFlags &= 0xFE;
        }

        if (obj->m_child != 0) {
            obj->m_child->SetShow_r(show);
        }

        obj = obj->m_next;
    } while (obj != 0);
}

/*
 * --INFO--
 * PAL Address: 0x80029FB8
 * PAL Size: 80b
 * EN Address: 0x80035498
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow(int show)
{
    if (show != 0) {
        m_showFlags |= 1;
    } else {
        m_showFlags &= 0xFE;
    }

    if (m_child != 0) {
        m_child->SetShow_r(show);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80029D18
 * PAL Size: 672b
 * EN Address: 0x80035510
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetLink()
{
    CMapObj* cursor = MapMng.m_mapObjArray;
    CMapObj* head = 0;

    while ((cursor = MapMng.SearchChildMapObj(cursor, this)) != 0) {
        CMapObj* child = cursor;

        child->m_next = head;
        head = child;
        child->SetLink();
        cursor = cursor + 1;
    }

    m_child = head;
}

static inline void calcRunningColorKeyFrame(CMapKeyFrame* keyFrame, _GXColor& out, _GXColor* colors)
{
    float blend;
    int key0;
    int key1;
    if (keyFrame->Get(key0, key1, blend) != 0) {
        int blendRate = static_cast<int>(255.0f * blend);
        _GXColor c0 = colors[key0];
        _GXColor c1 = colors[key1];

        c0.r = static_cast<unsigned char>(
            c0.r + ((blendRate * (static_cast<int>(c1.r) - static_cast<int>(c0.r))) >> 8));
        c0.g = static_cast<unsigned char>(
            c0.g + ((blendRate * (static_cast<int>(c1.g) - static_cast<int>(c0.g))) >> 8));
        c0.b = static_cast<unsigned char>(
            c0.b + ((blendRate * (static_cast<int>(c1.b) - static_cast<int>(c0.b))) >> 8));
        c0.a = static_cast<unsigned char>(
            c0.a + ((blendRate * (static_cast<int>(c1.a) - static_cast<int>(c0.a))) >> 8));
        out = c0;
    } else {
        out = colors[key0];
    }

    keyFrame->Calc();
}

static inline void calcColorKeyFrame(CMapKeyFrame* keyFrame, _GXColor& out, _GXColor* colors)
{
    if (keyFrame->IsRun() == 0) {
        return;
    }

    float blend;
    int key0;
    int key1;
    if (keyFrame->Get(key0, key1, blend) != 0) {
        int blendRate = static_cast<int>(255.0f * blend);
        _GXColor c0 = colors[key0];
        _GXColor c1 = colors[key1];

        c0.r = static_cast<unsigned char>(
            c0.r + ((blendRate * (static_cast<int>(c1.r) - static_cast<int>(c0.r))) >> 8));
        c0.g = static_cast<unsigned char>(
            c0.g + ((blendRate * (static_cast<int>(c1.g) - static_cast<int>(c0.g))) >> 8));
        c0.b = static_cast<unsigned char>(
            c0.b + ((blendRate * (static_cast<int>(c1.b) - static_cast<int>(c0.b))) >> 8));
        c0.a = static_cast<unsigned char>(
            c0.a + ((blendRate * (static_cast<int>(c1.a) - static_cast<int>(c0.a))) >> 8));
        out = c0;
    } else {
        out = colors[key0];
    }

    keyFrame->Calc();
}

/*
 * --INFO--
 * PAL Address: 0x80029538
 * PAL Size: 2016b
 * EN Address: 0x80035724
 * EN Size: 772b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Calc()
{
    Vec delta;
    Vec posCam;
    Vec pos;
    Mtx cameraMtx;

    if (m_cameraSemiTransStep != 0) {
        m_cameraSemiTransAlpha = static_cast<short>(m_cameraSemiTransAlpha + m_cameraSemiTransStep);
        if (m_cameraSemiTransStep > 0) {
            if (m_cameraSemiTransAlpha >= m_cameraSemiTransTargetAlpha) {
                m_cameraSemiTransAlpha = m_cameraSemiTransTargetAlpha;
                m_cameraSemiTransStep = 0;
            }
        } else if (m_cameraSemiTransAlpha <= m_cameraSemiTransTargetAlpha) {
            m_cameraSemiTransAlpha = m_cameraSemiTransTargetAlpha;
            m_cameraSemiTransStep = 0;
        }

        if (m_cameraSemiTransAlpha != 0) {
            m_drawPriority = 2;
        } else {
            m_drawPriority = m_baseDrawPriority;
        }
    }

    if ((static_cast<unsigned int>(m_mapDataType) == 1U) && (m_mapData != 0) &&
        (m_octTreeIndex == -1) &&
        ((m_showFlags & 1) != 0)) {
        if ((m_cameraSemiTransMaxAlpha < 0.0f) && (m_cameraSemiTransMinAlpha >= 1000000000000000.0f)) {
            m_drawPriority = m_baseDrawPriority;
            m_cameraSemiTransBeyondMax = 1;
            m_cameraSemiTransActive = 0;
        } else {
            pos.x = m_worldMtx[0][3];
            pos.y = m_worldMtx[1][3];
            pos.z = m_worldMtx[2][3];
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTXMultVec(cameraMtx, &pos, &posCam);
            posCam.z = -posCam.z;

            m_cameraSemiTransBeyondMax = static_cast<unsigned char>(posCam.z > m_cameraSemiTransMaxAlpha);
            if (posCam.z < m_cameraSemiTransMinAlpha) {
                m_cameraSemiTransActive = 1;
                m_drawPriority = 2;
            } else {
                m_cameraSemiTransActive = 1;
                m_drawPriority = m_baseDrawPriority;
            }
        }
    }

    CMapObjAtr* attr = m_attribute;
    if (attr != 0) {
        int attrType = attr->m_type;
        switch (attrType) {
        case CMapObjAtr::MIME:
            if (reinterpret_cast<CMapObjAtrMime*>(attr)->m_keyFrame.IsRun() != 0) {
                CMapObjAtrMime* mime = reinterpret_cast<CMapObjAtrMime*>(attr);
                float blend;
                int key0;
                int key1;
                Vec* outVerts = *reinterpret_cast<Vec**>(reinterpret_cast<unsigned char*>(m_mapData) + 0x2C);

                if (mime->m_keyFrame.Get(key0, key1, blend) != 0) {
                    Vec* src0 = reinterpret_cast<Vec*>(mime->m_vertexLists[key0]);
                    Vec* src1 = reinterpret_cast<Vec*>(mime->m_vertexLists[key1]);
                    Vec* dst = outVerts;
                    for (int i = 0; i < mime->m_vertexCount; i++) {
                        PSVECSubtract(src1, src0, &delta);
                        PSVECScale(&delta, &delta, blend);
                        PSVECAdd(src0, &delta, dst);
                        src0++;
                        src1++;
                        dst++;
                    }
                } else {
                    float* src = mime->m_vertexLists[key0];
                    for (int i = 0; i < mime->m_vertexCount; i++) {
                        outVerts[i].x = src[0];
                        outVerts[i].y = src[1];
                        outVerts[i].z = src[2];
                        src += 3;
                    }
                }

                DCFlushRange(outVerts, static_cast<unsigned long>(mime->m_vertexCount * 0xC));
                mime->m_keyFrame.Calc();
            }
            break;
        case CMapObjAtr::POINT_LIGHT: {
            CMapObjAtrPointLight* pointLight = reinterpret_cast<CMapObjAtrPointLight*>(attr);

            if (pointLight->m_colorKeyFrame.IsRun() != 0) {
                calcRunningColorKeyFrame(&pointLight->m_colorKeyFrame, pointLight->m_color, pointLight->m_colors);
                if (pointLight->m_useAltColor != 0) {
                    pointLight->m_altColor = pointLight->m_color;
                }
            }

            calcColorKeyFrame(&pointLight->m_altColorKeyFrame, pointLight->m_color, pointLight->m_colors);
            break;
        }
        case CMapObjAtr::SPOT_LIGHT: {
            CMapObjAtrSpotLight* spotLight = reinterpret_cast<CMapObjAtrSpotLight*>(attr);

            if (spotLight->m_colorKeyFrame.IsRun() != 0) {
                calcRunningColorKeyFrame(&spotLight->m_colorKeyFrame, spotLight->m_color, spotLight->m_colors);
                if (spotLight->m_unknown2F != 0) {
                    spotLight->m_altColor = spotLight->m_color;
                }
            }

            calcColorKeyFrame(&spotLight->m_altColorKeyFrame, spotLight->m_color, spotLight->m_colors);
            break;
        }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800293C8
 * PAL Size: 368b
 * EN Address: 0x80035A28
 * EN Size: 496b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetDrawEnv()
{
    _GXColor mapColor;

    s_mapObjLightColor.a = m_lightAlpha;

    if (m_useAmbientColor != 0) {
        mapColor = m_ambientColor;
    } else {
        mapColor = MapMng.m_mapColor;
    }

    if (MapMng.m_colorScaleEnable != 0) {
        mapColor.r = static_cast<unsigned char>((mapColor.r * MapMng.m_colorScale.r) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * MapMng.m_colorScale.g) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * MapMng.m_colorScale.b) >> 8);
        mapColor.a = static_cast<unsigned char>((mapColor.a * MapMng.m_colorScale.a) >> 8);
    }

    if (m_colorAlphaRate != 0xFF) {
        int alphaRate = m_colorAlphaRate;
        mapColor.r = static_cast<unsigned char>((mapColor.r * alphaRate) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * alphaRate) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * alphaRate) >> 8);
    }

    _GXColor lightColor = s_mapObjLightColor;
    LightPcs.SetMapColorAlpha(m_worldMtx, mapColor, lightColor, m_cameraSemiTransActive, m_cameraSemiTransNear,
                              m_cameraSemiTransFar, m_cameraSemiTransFadeRange,
                              static_cast<unsigned char>(m_cameraSemiTransAlpha >> 7));
}

/*
 * --INFO--
 * PAL Address: 0x80029094
 * PAL Size: 820b
 * EN Address: 0x80035D24
 * EN Size: 416b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Draw(unsigned char priority)
{
    if (m_drawPriority != priority) {
        return;
    }
    if ((m_showFlags & 4) == 0) {
        return;
    }

    Vec lightPos;
    lightPos.x = m_worldMtx[0][3];
    lightPos.y = m_worldMtx[1][3];
    lightPos.z = m_worldMtx[2][3];
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(1), &lightPos, m_lightSetIndex);

    MaterialMan.InitEnv();

    if (m_enableFullScreenShadow != 0) {
        CameraPcs.SetFullScreenShadow(m_worldMtx, 0);
    }
    if (m_shadowTarget != 0) {
        MaterialMan.SetShadowBound(static_cast<CMapShadow::TARGET>(1),
                                   reinterpret_cast<CMapMesh*>(m_mapData)->GetBound(),
                                   m_worldMtx);
    }

    MaterialMan.LockEnv();

    SetDrawEnv();
    LightPcs.SetBumpTexMatirx(m_worldMtx, reinterpret_cast<CLightPcs::CBumpLight*>(m_bumpLight),
                              reinterpret_cast<Vec*>(&m_transRateX), m_bumpTexMatrixMode);

    if (0.0f != m_zBufferOffset) {
        CameraPcs.SetOffsetZBuff(m_zBufferOffset);
    }
    if (m_disableZWrite != 0) {
        GXSetZMode(1, GX_LEQUAL, 0);
    }

    reinterpret_cast<CMapMesh*>(m_mapData)->SetRenderArray();
    reinterpret_cast<CMapMesh*>(m_mapData)->Draw(0);

    if (m_disableZWrite != 0) {
        GXSetZMode(1, GX_LEQUAL, 1);
    }
    if (0.0f != m_zBufferOffset) {
        CameraPcs.SetOffsetZBuff(m_zBufferOffset);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028FD8
 * PAL Size: 188b
 * EN Address: 0x80035EC4
 * EN Size: 212b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetDrawFlag()
{
    m_showFlags &= ~4;

    if ((m_mapDataType == 1) && (m_mapData != 0)) {
        if ((m_octTreeIndex == -1) && ((m_showFlags & 1) != 0)) {
            Mtx concatMtx;

            PSMTXConcat(MapMng.m_scaledViewMtxSecondary, m_worldMtx, concatMtx);
            if (reinterpret_cast<CMapMesh*>(m_mapData)->GetBound()->CheckFrustum(
                    MapMng.m_cameraPosition, concatMtx, MapMng.m_octTreeFrustumRange) != 0) {
                m_showFlags |= 4;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028F70
 * PAL Size: 104b
 * EN Address: 0x80035F98
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHit()
{
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapMng.m_viewMtx, m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->Draw();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028F08
 * PAL Size: 104b
 * EN Address: 0x80036000
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHitWire()
{
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapMng.m_viewMtx, m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->DrawWire();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028EA0
 * PAL Size: 104b
 * EN Address: 0x80036068
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHitNormal()
{
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapMng.m_viewMtx, m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->DrawNormal();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028BC0
 * PAL Size: 736b
 * EN Address: 0x800360D0
 * EN Size: 264b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::CheckHitCylinder(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((m_mapDataType == 2) && (m_mapData != 0) && (m_octTreeIndex == -1)) {
        Mtx inverseMtx;

        PSMTXInverse(m_worldMtx, inverseMtx);
        CMapCylinder localCylinder;
        PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
        PSMTXMultVec(inverseMtx, &cylinder->m_top, &localCylinder.m_top);

        localCylinder.m_radius = cylinder->m_radius;
        localCylinder.CalcBound();

        CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
        if (mapHit->m_bound.CheckCross(localCylinder.m_bound)) {
            Vec localMove;
            PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &localCylinder.m_axis);
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            if (reinterpret_cast<CMapHit*>(m_mapData)->CheckHitCylinder(&localCylinder, &localMove, mask) != 0) {
                return 1;
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800288F4
 * PAL Size: 716b
 * EN Address: 0x800361D8
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((m_mapDataType == 2) && (m_mapData != 0) && (m_octTreeIndex == -1)) {
        Mtx inverseMtx;
        Vec localMove;

        PSMTXInverse(m_worldMtx, inverseMtx);
        CMapCylinder localCylinder;
        PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
        PSMTXMultVec(inverseMtx, &cylinder->m_top, &localCylinder.m_top);

        localCylinder.m_radius = cylinder->m_radius;
        localCylinder.CalcBound();

        CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
        if (mapHit->m_bound.CheckCross(localCylinder.m_bound)) {
            PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &localCylinder.m_axis);
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            reinterpret_cast<CMapHit*>(m_mapData)->CheckHitCylinderNear(&localCylinder, &localMove, mask);
        }
    }

}

/*
 * --INFO--
 * PAL Address: 0x800288A8
 * PAL Size: 76b
 * EN Address: 0x800362CC
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::GetHitFaceNormal(Vec* out)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    mapHit->GetHitFaceNormal(out);
    PSMTXMultVecSR(m_worldMtx, out, out);
}

/*
 * --INFO--
 * PAL Address: 0x8002884C
 * PAL Size: 92b
 * EN Address: 0x8003631C
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::CalcHitSlide(Vec* out, float y)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    int hit = mapHit->CalcHitSlide(out, y);
    PSMTXMultVecSR(m_worldMtx, out, out);
    return hit;
}

/*
 * --INFO--
 * PAL Address: 0x80028800
 * PAL Size: 76b
 * EN Address: 0x80036384
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CalcHitPosition(Vec* out)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    mapHit->CalcHitPosition(out);
    PSMTXMultVec(m_worldMtx, out, out);
}

/*
 * --INFO--
 * PAL Address: 0x800287D0
 * PAL Size: 48b
 * EN Address: 0x800363D4
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetMime(int mode, int target, int type)
{
    CMapObjAtrMime* mime = reinterpret_cast<CMapObjAtrMime*>(m_attribute);

    mime->m_keyFrame.m_startFrame = mode;
    mime->m_keyFrame.m_currentFrame = mode;

    if (target > mime->m_keyFrame.m_frameCount) {
        target = mime->m_keyFrame.m_frameCount;
    }

    mime->m_keyFrame.m_endFrame = target;
    mime->m_keyFrame.m_loop = static_cast<unsigned char>(type);
    mime->m_keyFrame.m_isRun = 1;
}
