#include "ffcc/mapmesh.h"

class CMaterial;

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_size;
    int m_numItems;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    T GetAt(unsigned long index);
    T operator[](unsigned long index);
};

namespace {
static inline unsigned char* Ptr(CMapMesh* self, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(self) + offset;
}

static inline void*& PtrAt(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline int& S32At(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(self, offset));
}

static inline unsigned short& U16At(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(self, offset));
}
}

/*
 * --INFO--
 * PAL Address: 0x800287a0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMaterial* CPtrArray<CMaterial*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x800287c0
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMaterial* CPtrArray<CMaterial*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMesh::CMapMesh()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80028648
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapMesh::~CMapMesh()
{
    if (PtrAt(this, 0x24) != 0) {
        __dla__FPv(PtrAt(this, 0x24));
        PtrAt(this, 0x24) = 0;
    }

    if (PtrAt(this, 0x28) != 0) {
        __dla__FPv(PtrAt(this, 0x28));
        PtrAt(this, 0x28) = 0;
    }

    U16At(this, 0x0) = 0;
    U16At(this, 0x2) = 0;
    U16At(this, 0x4) = 0;
    U16At(this, 0x8) = 0;
    U16At(this, 0x6) = 0;
    U16At(this, 0xA) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800286e0
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Destroy()
{
    if (PtrAt(this, 0x24) != 0) {
        __dla__FPv(PtrAt(this, 0x24));
        PtrAt(this, 0x24) = 0;
    }

    if (PtrAt(this, 0x28) != 0) {
        __dla__FPv(PtrAt(this, 0x28));
        PtrAt(this, 0x28) = 0;
    }

    U16At(this, 0x0) = 0;
    U16At(this, 0x2) = 0;
    U16At(this, 0x4) = 0;
    U16At(this, 0x8) = 0;
    U16At(this, 0x6) = 0;
    U16At(this, 0xA) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800285dc
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Ptr2Off()
{
    if (S32At(this, 0x24) == 0) {
        return;
    }

    S32At(this, 0x2C) -= S32At(this, 0x24);
    S32At(this, 0x30) -= S32At(this, 0x24);
    S32At(this, 0x34) -= S32At(this, 0x24);
    S32At(this, 0x38) -= S32At(this, 0x24);
    S32At(this, 0x3C) -= S32At(this, 0x24);
    S32At(this, 0x40) -= S32At(this, 0x24);
}

/*
 * --INFO--
 * PAL Address: 0x80028540
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Off2Ptr()
{
    int iterOffset = 0;

    S32At(this, 0x2C) += S32At(this, 0x24);
    S32At(this, 0x30) += S32At(this, 0x24);
    S32At(this, 0x34) += S32At(this, 0x24);
    S32At(this, 0x38) += S32At(this, 0x24);
    S32At(this, 0x3C) += S32At(this, 0x24);
    S32At(this, 0x40) += S32At(this, 0x24);

    for (int i = 0; i < static_cast<int>(U16At(this, 0xA)); i++) {
        int entry = S32At(this, 0x40) + iterOffset;
        iterOffset += 0x10;
        *reinterpret_cast<int*>(entry + 4) = S32At(this, 0x24) + *reinterpret_cast<int*>(entry + 0xC);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::ReadOtmMesh(CChunkFile&, CMemory::CStage*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::SetRenderArray()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::DrawMesh(unsigned short, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::DrawMeshCharaShadow(unsigned short, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::Draw(CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::DrawPart(CMaterialSet*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::GetTexture(CMaterialSet*, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::SetDisplayListMaterial(CMaterialSet*, char **, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheLoadModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheUnLoadModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheRefCnt0UpModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheDumpModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}
