#include "ffcc/map.h"
#include "ffcc/chunkfile.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/maptexanim.h"

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" float Spline1D__5CMathFifPfPfPf(CMath*, int, float, float*, float*, float*);
extern "C" float Line1D__5CMathFifPfPf(CMath*, int, float, float*, float*);
extern "C" void MakeSpline1Dtable__5CMathFiPfPfPf(CMath*, int, float*, float*, float*);
extern CMath Math;

static char s_map_cpp[] = "map.cpp";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::CMapKeyFrame()
{
    *reinterpret_cast<int*>(Ptr(this, 0)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 4)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 8)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0xC)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x10)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x14)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x18)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x1C)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x20)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x24)) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::~CMapKeyFrame()
{
    void*& junTable = *reinterpret_cast<void**>(Ptr(this, 0x18));
    void*& keyFrame = *reinterpret_cast<void**>(Ptr(this, 0x1C));
    void*& keyValue = *reinterpret_cast<void**>(Ptr(this, 0x20));
    void*& splineTable = *reinterpret_cast<void**>(Ptr(this, 0x24));

    if (junTable != 0) {
        __dla__FPv(junTable);
        junTable = 0;
    }
    if (keyFrame != 0) {
        __dla__FPv(keyFrame);
        keyFrame = 0;
    }
    if (keyValue != 0) {
        __dla__FPv(keyValue);
        keyValue = 0;
    }
    if (splineTable != 0) {
        __dla__FPv(splineTable);
        splineTable = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMapKeyFrame::Get()
{
    const int keyCount = static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2)));
    const int currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    float* keyValue = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)));
    float* keyFrame = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)));
    float* splineTable = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24)));

    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 1) {
        return Spline1D__5CMathFifPfPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame, splineTable);
    }
    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 0) {
        return Line1D__5CMathFifPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame);
    }
    return 0.0f;
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
 * PAL Address: 0x80033d24
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapLightHolder*>::Add(CMapLightHolder* item)
{
    bool success = setSize(m_numItems + 1);
    if (success) {
        m_items[m_numItems] = item;
        m_numItems++;
    }
    return success;
}

/*
 * --INFO--
 * PAL Address: 0x80033d94
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapLightHolder*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
template <>
void CPtrArray<CMapLightHolder*>::SetStage(CMemory::CStage* stage)
{
    *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(this) + 0x14) = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80033f54
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapAnim*>::Add(CMapAnim* item)
{
    bool success = setSize(m_numItems + 1);
    if (success) {
        m_items[m_numItems] = item;
        m_numItems++;
    }
    return success;
}

/*
 * --INFO--
 * PAL Address: 0x80033fc4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnim*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80033fcc
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnim*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034018
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034038
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnim*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034040
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapAnim*>::setSize(unsigned long newSize)
{
    CMapAnim** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            m_size = m_size << 1;
        }

        newItems = new CMapAnim*[m_size];
        if (newItems == 0) {
            return false;
        }

        if (m_items != 0) {
            for (unsigned long i = 0; i < m_numItems; i++) {
                newItems[i] = m_items[i];
            }
        }

        if (m_items != 0) {
            __dla__FPv(m_items);
            m_items = 0;
        }

        m_items = newItems;
    }

    return true;
}

/*
 * --INFO--
 * PAL Address: 0x80034260
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
template <>
int CPtrArray<CMapAnimRun*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x800340f0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimRun*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003413c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034170
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimRun*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034a44
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::Get(int& key0, int& key1, float& blend)
{
    const unsigned char mode = *reinterpret_cast<unsigned char*>(Ptr(this, 0));
    const int keyCount = static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2)));
    const int currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    unsigned char* junTable = *reinterpret_cast<unsigned char**>(Ptr(this, 0x18));
    float* keyFrame = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)));
    float* keyValue = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)));
    float* splineTable = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24)));

    if (mode == 1) {
        blend = Spline1D__5CMathFifPfPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame, splineTable);
    } else if (mode == 0) {
        blend = Line1D__5CMathFifPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame);
    } else {
        blend = 0.0f;
        key0 = junTable[0];
        key1 = key0;
        return 0;
    }

    if (blend > 0.0f) {
        const float junMax = static_cast<float>(*reinterpret_cast<unsigned char*>(Ptr(this, 1)) - 1);
        if (blend < junMax) {
            key0 = static_cast<int>(blend);
            key1 = static_cast<int>(1.0f + blend);
            blend = blend - static_cast<float>(key0);
            key0 = junTable[key0];
            if (blend == 0.0f) {
                key1 = key0;
                return 0;
            }
            key1 = junTable[key1];
            return 1;
        }

        key0 = junTable[*reinterpret_cast<unsigned char*>(Ptr(this, 1)) - 1];
        key1 = key0;
        blend = 1.0f;
        return 0;
    }

    key0 = junTable[0];
    key1 = key0;
    blend = 0.0f;
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Calc()
{
    int& currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    const int startFrame = *reinterpret_cast<int*>(Ptr(this, 0xC));
    const int endFrame = *reinterpret_cast<int*>(Ptr(this, 0x10));
    unsigned char& loop = *reinterpret_cast<unsigned char*>(Ptr(this, 3));
    unsigned char& isRun = *reinterpret_cast<unsigned char*>(Ptr(this, 4));

    currentFrame++;
    if (currentFrame <= endFrame) {
        return;
    }
    if (startFrame == endFrame) {
        isRun = 0;
        return;
    }
    if (loop != 0) {
        currentFrame = startFrame;
        return;
    }

    currentFrame = endFrame;
    isRun = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::IsRun()
{
    return *reinterpret_cast<unsigned char*>(Ptr(this, 4));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadJun(CChunkFile& chunkFile, int count)
{
    *reinterpret_cast<unsigned char*>(Ptr(this, 1)) = static_cast<unsigned char>(count);
    *reinterpret_cast<void**>(Ptr(this, 0x18)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(*reinterpret_cast<unsigned char*>(Ptr(this, 1))),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xC1);

    for (int i = 0; i < static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 1))); i++) {
        (*reinterpret_cast<unsigned char**>(Ptr(this, 0x18)))[i] = chunkFile.Get1();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadFrame(CChunkFile& chunkFile, int)
{
    const int startFrame = static_cast<int>(chunkFile.Get4());
    const int endFrame = static_cast<int>(chunkFile.Get4());

    *reinterpret_cast<int*>(Ptr(this, 0xC)) = startFrame;
    *reinterpret_cast<int*>(Ptr(this, 8)) = startFrame;
    *reinterpret_cast<int*>(Ptr(this, 0x10)) = endFrame;
    *reinterpret_cast<int*>(Ptr(this, 0x14)) = endFrame;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0)) = static_cast<unsigned char>(chunkFile.Get4());
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadKey(CChunkFile& chunkFile, int count)
{
    *reinterpret_cast<unsigned char*>(Ptr(this, 4)) = 1;
    *reinterpret_cast<unsigned char*>(Ptr(this, 2)) = static_cast<unsigned char>(count);
    *reinterpret_cast<void**>(Ptr(this, 0x1C)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xD5);
    *reinterpret_cast<void**>(Ptr(this, 0x20)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xD6);

    for (int i = 0; i < static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))); i++) {
        reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)))[i] = chunkFile.GetF4();
        reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)))[i] = chunkFile.GetF4();
    }

    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 1) {
        *reinterpret_cast<void**>(Ptr(this, 0x24)) = __nwa__FUlPQ27CMemory6CStagePci(
            static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
            *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xDE);
        MakeSpline1Dtable__5CMathFiPfPfPf(&Math, static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) - 1,
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20))),
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C))),
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24))));
    }
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
 * PAL Address: 0x8002f6d4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjMime(int mapObjIndex, int mode, int target, int type)
{
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
    mapObj->SetMime(mode, target, type);
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
