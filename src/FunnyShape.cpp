#include "ffcc/FunnyShape.h"
#include "types.h"

#include <string.h>

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);

namespace {
static inline u8* Ptr(CFunnyShape* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline void*& PtrAt(CFunnyShape* self, u32 offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline u32& U32At(CFunnyShape* self, u32 offset)
{
    return *reinterpret_cast<u32*>(Ptr(self, offset));
}
}

/*
 * --INFO--
 * PAL Address: 0x80051e4c
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFunnyShape::CFunnyShape()
{
    PtrAt(this, 0x6010) = 0;
    memset(this, 0, 0x6000);
    memset(Ptr(this, 0x6000), 0, 0x10);
    memset(Ptr(this, 0x60D8), 0, 0x10);
    memset(Ptr(this, 0x6014), 0, 0x40);

    for (s32 i = 0; i < 0x10; i++) {
        u32 offs = static_cast<u32>(i) * 4;
        PtrAt(this, 0x6014 + offs) = 0;
        PtrAt(this, 0x6054 + offs) = 0;
        PtrAt(this, 0x6094 + offs) = 0;
    }

    U32At(this, 0x60D4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80051d80
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFunnyShape::~CFunnyShape()
{
    if (PtrAt(this, 0x6010) != 0) {
        __dla__FPv(PtrAt(this, 0x6010));
        PtrAt(this, 0x6010) = 0;
    }

    if (PtrAt(this, 0x600C) != 0) {
        __dla__FPv(PtrAt(this, 0x600C));
        PtrAt(this, 0x600C) = 0;
    }

    for (s32 i = 0; i < 0x10; i++) {
        u32 offs = static_cast<u32>(i) * 4;
        if (PtrAt(this, 0x6094 + offs) != 0) {
            __dla__FPv(PtrAt(this, 0x6094 + offs));
            PtrAt(this, 0x6094 + offs) = 0;
        }

        if (PtrAt(this, 0x6014 + offs) != 0) {
            __dl__FPv(PtrAt(this, 0x6014 + offs));
            PtrAt(this, 0x6014 + offs) = 0;
        }

        if (PtrAt(this, 0x6054 + offs) != 0) {
            __dl__FPv(PtrAt(this, 0x6054 + offs));
            PtrAt(this, 0x6054 + offs) = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051d80
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CFunnyShape* dtor_80051D80(CFunnyShape* funnyShape, short shouldDelete)
{
    if (funnyShape != 0) {
        if (PtrAt(funnyShape, 0x6010) != 0) {
            __dla__FPv(PtrAt(funnyShape, 0x6010));
            PtrAt(funnyShape, 0x6010) = 0;
        }

        if (PtrAt(funnyShape, 0x600C) != 0) {
            __dla__FPv(PtrAt(funnyShape, 0x600C));
            PtrAt(funnyShape, 0x600C) = 0;
        }

        for (s32 i = 0; i < 0x10; i++) {
            u32 offs = static_cast<u32>(i) * 4;
            if (PtrAt(funnyShape, 0x6094 + offs) != 0) {
                __dla__FPv(PtrAt(funnyShape, 0x6094 + offs));
                PtrAt(funnyShape, 0x6094 + offs) = 0;
            }

            if (PtrAt(funnyShape, 0x6014 + offs) != 0) {
                __dl__FPv(PtrAt(funnyShape, 0x6014 + offs));
                PtrAt(funnyShape, 0x6014 + offs) = 0;
            }

            if (PtrAt(funnyShape, 0x6054 + offs) != 0) {
                __dl__FPv(PtrAt(funnyShape, 0x6054 + offs));
                PtrAt(funnyShape, 0x6054 + offs) = 0;
            }
        }

        if (shouldDelete > 0) {
            __dl__FPv(funnyShape);
        }
    }

    return funnyShape;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::InitAnmWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::Update()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::Render()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::RenderTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::RenderShape()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800510b0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::ClearAnmData()
{
    if (PtrAt(this, 0x600C) != 0) {
        __dla__FPv(PtrAt(this, 0x600C));
        PtrAt(this, 0x600C) = 0;
    }

    memset(this, 0, 0x30);
    memset(Ptr(this, 0x6000), 0, 0x10);
}

/*
 * --INFO--
 * PAL Address: 0x80051020
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::ClearTextureData()
{
    U32At(this, 0x60D4) = 0;
    u8* iter = reinterpret_cast<u8*>(this);
    for (s32 i = 0; i < 0x10; i++) {
        void** texData = reinterpret_cast<void**>(iter + 0x6094);
        if (*texData != 0) {
            __dla__FPv(*texData);
            *texData = 0;
        }

        void** texObj = reinterpret_cast<void**>(iter + 0x6014);
        if (*texObj != 0) {
            __dl__FPv(*texObj);
            *texObj = 0;
        }

        void** rawData = reinterpret_cast<void**>(iter + 0x6054);
        if (*rawData != 0) {
            __dl__FPv(*rawData);
            *rawData = 0;
        }
        iter += 4;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::RenderShape(FS_tagOAN3_SHAPE*, Vec2d&, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::SetDefaultStage()
{
	// TODO
}
