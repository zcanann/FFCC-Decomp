#include "ffcc/maptexanim.h"
#include "ffcc/system.h"

extern "C" void Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(CMapTexAnim*, CMaterialSet*, CTextureSet*);

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
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::~CMapTexAnimSet()
{
	// TODO
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
    int iter = reinterpret_cast<int>(this);
    const short count = S16At(this, 0x8);
    CMaterialSet* materialSet = *reinterpret_cast<CMaterialSet**>(Ptr(this, 0x10C));
    CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(Ptr(this, 0x110));

    for (int i = 0; i < count; i++) {
        Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(
            *reinterpret_cast<CMapTexAnim**>(iter + 0xC), materialSet, textureSet);
        iter += 4;
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
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnim::~CMapTexAnim()
{
	// TODO
}
