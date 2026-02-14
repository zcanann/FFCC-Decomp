#include "ffcc/map.h"
#include "ffcc/maptexanim.h"

extern "C" unsigned long UnkMaterialSetGetter(void*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::CMapKeyFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::~CMapKeyFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Get()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80033d0c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned long UnkMaterialSetGetter(void* ptrArray)
{
    return *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(ptrArray) + 4);
}

/*
 * --INFO--
 * PAL Address: 0x80033d14
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMaterial*>::SetDefaultSize(unsigned long defaultSize)
{
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 8) = defaultSize;
}

/*
 * --INFO--
 * PAL Address: 0x80033d1c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMaterial*>::SetGrow(int growCapacity)
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x14) = growCapacity;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Get(int&, int&, float&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::IsRun()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadJun(CChunkFile&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadFrame(CChunkFile&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadKey(CChunkFile&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyOctTree()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapMesh()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMaterialSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyAnimation()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapLightHolder()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::MapFileRead(char*, unsigned long&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::MapCheckFileRead(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::LoadMapNoSyncCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SearchChildMapObj(CMapObj*, CMapObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SearchAtribMapObj(CMapObj*, CMapObjAtr::TYPE)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::AttachMapHit(CMapHit*, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetDebugPlaySta(int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetLightSource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetBumpLightSource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::InitMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMtx(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMpl(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadOtm(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMid(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setDbgLight(int, Vec&, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawBefore()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawAfter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::CheckHitCylinder(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunMapObj(CMapObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunID(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetViewMtx(float (*) [4], float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetIdGrpMask(int, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetIdGrpColor(int, int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMeshCameraSemiTransRange(unsigned short, float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMeshCameraSemiTransAlpha(unsigned short, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjIdx(unsigned short id)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == id) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
    }

    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterial* CMapMng::GetMaterialID(unsigned char materialId)
{
    unsigned long index = 0;
    unsigned char* materialSet = *reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x213D4);
    CPtrArray<CMaterial*>* materials = reinterpret_cast<CPtrArray<CMaterial*>*>(materialSet + 8);

    while (index < UnkMaterialSetGetter(materials)) {
        CMaterial* material = (*materials)[index];
        if (material != 0 && reinterpret_cast<unsigned char*>(material)[0xA6] == materialId) {
            return (*materials)[index];
        }
        index++;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjEffectIdx(unsigned short effectId)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x984) == effectId) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
    }

    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjLMtx(int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetMapObjWMtx(int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjAnim(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapAnimID(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjMime(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapTexAnim(int materialId, int frameStart, int frameEnd, int wrapMode)
{
    CMapTexAnimSet* mapTexAnimSet = *reinterpret_cast<CMapTexAnimSet**>(reinterpret_cast<unsigned char*>(this) + 0x213DC);
    mapTexAnimSet->SetMapTexAnim(materialId, frameStart, frameEnd, wrapMode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObj(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjID(int id, int show)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < objCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == static_cast<unsigned int>(id)) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapObj += 0xF0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjChild(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjChildID(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapMeshID(int id, int show)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < objCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == static_cast<unsigned int>(id)) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapObj += 0xF0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjPrioID(int id, unsigned char prio)
{
    int i = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC)) {
        if (static_cast<int>(*reinterpret_cast<unsigned short*>(mapObj + 0x982)) == id) {
            *reinterpret_cast<unsigned char*>(mapObj + 0x969) = prio;
            *reinterpret_cast<unsigned char*>(mapObj + 0x968) = prio;
        }
        mapObj += 0xF0;
        i++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjTransRate(int mapObjIndex, float x, float y, float z)
{
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954;
    *reinterpret_cast<float*>(mapObj + 0x58) = x;
    *reinterpret_cast<float*>(mapObj + 0x5C) = y;
    *reinterpret_cast<float*>(mapObj + 0x60) = z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjWorldMapLightIdx(int, _GXColor, Vec)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002f47c
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjWorldMapLightID(int id, _GXColor color, Vec position)
{
    int objIndex = 0;
    int numMapObj = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* scan = reinterpret_cast<unsigned char*>(this);

    while (0 < numMapObj) {
        if (*reinterpret_cast<unsigned short*>(scan + 0x982) == static_cast<unsigned short>(id)) {
            goto found;
        }
        scan += 0xF0;
        objIndex++;
        numMapObj--;
    }
    objIndex = -1;

found:
    const unsigned int packedColor = *reinterpret_cast<unsigned int*>(&color);
    const float posX = position.x;
    const float posY = position.y;
    const float posZ = position.z;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (objIndex * 0xF0) + 0x954;
    unsigned char* mapObjLight = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);

    if (*reinterpret_cast<int*>(mapObjLight + 4) == 1) {
        const unsigned char* colorBytes = reinterpret_cast<const unsigned char*>(&packedColor);
        *reinterpret_cast<unsigned char*>(mapObjLight + 8) = colorBytes[0];
        *reinterpret_cast<unsigned char*>(mapObjLight + 9) = colorBytes[1];
        *reinterpret_cast<unsigned char*>(mapObjLight + 10) = colorBytes[2];
        *reinterpret_cast<unsigned char*>(mapObjLight + 11) = colorBytes[3];
        *reinterpret_cast<float*>(mapObj + 0x70) = posX;
        *reinterpret_cast<float*>(mapObj + 0x74) = posY;
        *reinterpret_cast<float*>(mapObj + 0x78) = posZ;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1C) = 1;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1B) = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002f46c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeOctTree(float drawRange)
{
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x22A70) = -drawRange;
}

/*
 * --INFO--
 * PAL Address: 0x8002f45c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeMapObj(float drawRange)
{
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x22A74) = -drawRange;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetDraw(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetFogEnable()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMng::~CMapMng()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMng::CMapMng()
{
	// TODO
}
