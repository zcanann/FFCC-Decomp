#include "ffcc/maptexanim.h"
#include "ffcc/system.h"

extern "C" void Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(CMapTexAnim*, CMaterialSet*, CTextureSet*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __dl__FPv(void*);
extern "C" void* PTR_PTR_s_CMapTexAnimSet_801e896c;
extern "C" void* PTR_PTR_s_CMapTexAnim_801ea9a4;

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline short& S16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<short*>(Ptr(p, offset));
}

static inline int& S32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(p, offset));
}

static inline float& F32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(p, offset));
}

static inline unsigned char& U8At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(p, offset));
}

static inline CMapTexAnim*& AnimAt(CMapTexAnimSet* self, int index)
{
    return *reinterpret_cast<CMapTexAnim**>(reinterpret_cast<unsigned char*>(self) + 0xC + (index * 4));
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::CMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800335d0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnimSet::~CMapTexAnimSet()
{
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);
    const short count = *reinterpret_cast<short*>(p + 8);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnimSet_801e896c;

    for (int i = 0; i < count; i++) {
        int* entry = *reinterpret_cast<int**>(p + 0xC + (i * 4));
        if (entry != 0) {
            const int refCount = entry[1];
            entry[1] = refCount - 1;
            if ((refCount - 1) == 0 && entry != 0) {
                (*reinterpret_cast<void (**)(int*, int)>(*entry + 8))(entry, 1);
            }
            *reinterpret_cast<int**>(p + 0xC + (i * 4)) = 0;
        }
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapTexAnimSet::Create(CChunkFile&, CMaterialSet*, CTextureSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapTexAnim::Calc(CMaterialSet*, CTextureSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapTexAnim::SetMapTexAnim(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004fa24
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnimSet::Calc()
{
    int param_1;
    int iVar1;
    int iVar2;

    param_1 = (int)this;
    iVar2 = param_1;
    for (iVar1 = 0; iVar1 < *(short*)(param_1 + 8); iVar1 = iVar1 + 1) {
        Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(
            *(CMapTexAnim**)(iVar2 + 0xC), *(CMaterialSet**)(param_1 + 0x10C),
            *(CTextureSet**)(param_1 + 0x110));
        iVar2 = iVar2 + 4;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004f910
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnimSet::SetMapTexAnim(int materialId, int frameStart, int frameEnd, int wrapMode)
{
    bool found = false;
    const short count = S16At(this, 0x8);

    for (int i = 0; i < count; i++) {
        CMapTexAnim* anim = AnimAt(this, i);
        if (S16At(anim, 0x12) != static_cast<short>(materialId)) {
            continue;
        }

        if (U8At(anim, 0x15) == 0) {
            S16At(anim, 0xE) = static_cast<short>(frameStart);
            F32At(anim, 0x1C) = static_cast<float>(S16At(anim, 0xE));
            int clampedEnd = frameEnd;
            if (S16At(anim, 0xC) < frameEnd) {
                clampedEnd = S16At(anim, 0xC);
            }
            S16At(anim, 0x10) = static_cast<short>(clampedEnd);
            U8At(anim, 0x16) = static_cast<unsigned char>(wrapMode);
        } else {
            S32At(anim, 0x30) = frameStart;
            S32At(anim, 0x2C) = frameStart;
            int clampedKeyEnd = frameEnd;
            if (S32At(anim, 0x38) < frameEnd) {
                clampedKeyEnd = S32At(anim, 0x38);
            }
            S32At(anim, 0x34) = clampedKeyEnd;
            U8At(anim, 0x27) = static_cast<unsigned char>(wrapMode);
            U8At(anim, 0x28) = 1;
        }

        found = true;
    }

    if (!found && System.m_execParam != 0) {
        System.Printf("%s: material id (%d) not found\n", "SetMapTexAnim", materialId);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnim::CMapTexAnim()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80050320
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnim::~CMapTexAnim()
{
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnim_801ea9a4;

    __dl__FPv(*reinterpret_cast<void**>(p + 0x20));
    *reinterpret_cast<void**>(p + 0x20) = 0;

    if (this != reinterpret_cast<CMapTexAnim*>(-0x24)) {
        if (*reinterpret_cast<void**>(p + 0x3C) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(p + 0x3C));
            *reinterpret_cast<void**>(p + 0x3C) = 0;
        }
        if (*reinterpret_cast<void**>(p + 0x40) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(p + 0x40));
            *reinterpret_cast<void**>(p + 0x40) = 0;
        }
        if (*reinterpret_cast<void**>(p + 0x44) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(p + 0x44));
            *reinterpret_cast<void**>(p + 0x44) = 0;
        }
        if (*reinterpret_cast<void**>(p + 0x48) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(p + 0x48));
            *reinterpret_cast<void**>(p + 0x48) = 0;
        }
    }

    __dt__4CRefFv(this, 0);
}
