#include "ffcc/p_map.h"

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801E900C;

extern unsigned char MapPcs[];

extern unsigned int lbl_801E89B8[];
extern unsigned int lbl_801E89C4[];
extern unsigned int lbl_801E89D0[];
extern unsigned int lbl_801E89DC[];
extern unsigned int lbl_801E89E8[];
extern unsigned int lbl_801E89F4[];
extern unsigned int lbl_801E8A00[];
extern unsigned int lbl_801E8A0C[];
extern unsigned int lbl_801E8A18[];
extern unsigned int lbl_801E8A24[];
extern unsigned int lbl_801E8A30[];
extern unsigned int lbl_801E8A3C[];
extern unsigned int lbl_801E8A48[];
extern unsigned int lbl_801E8A54[];
extern unsigned int lbl_801E8A60[];
extern unsigned int lbl_801E8A6C[];
extern unsigned int lbl_801E8A78[];
extern unsigned int lbl_801E8A84[];
extern unsigned int lbl_801E8A90[];
extern unsigned int lbl_801E8A9C[];
extern unsigned int lbl_801E8AA8[];
extern unsigned int lbl_801E8AB4[];
extern unsigned int lbl_801E8AC0[];
extern unsigned int lbl_801E8ACC[];
extern unsigned int lbl_801E8AD8[];

extern unsigned int lbl_8032ECC8;
extern unsigned int lbl_8032ECCC;
extern unsigned int lbl_8032ECD0;

extern "C" void __dl__FPv(void*);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);

struct CRelProfile;
extern "C" CRelProfile* __dt__11CRelProfileFv(CRelProfile* self, short shouldDelete);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapPcs::CMapPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::Init()
{
	// TODO
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
void CMapPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::createViewer()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::LoadMap(int, int, void*, unsigned long, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::IsLoadMapCompleted()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::calcInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::calcViewer()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawBefore()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawBeforeViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawAfter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapPcs::drawAfterViewer()
{
	// TODO
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

/*
 * --INFO--
 * PAL Address: 0x80035e84
 * PAL Size: 976b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_map_cpp(void)
{
	volatile void** base = reinterpret_cast<volatile void**>(MapPcs);
	*base = &__vt__8CManager;
	*base = &lbl_801E8668;
	*base = &lbl_801E900C;

	unsigned int* dst = lbl_801E8AD8;

	dst[0x004 / 4] = lbl_801E89B8[0];
	dst[0x008 / 4] = lbl_801E89B8[1];
	dst[0x00C / 4] = lbl_801E89B8[2];
	dst[0x010 / 4] = lbl_801E89C4[0];
	dst[0x014 / 4] = lbl_801E89C4[1];
	dst[0x018 / 4] = lbl_801E89C4[2];
	dst[0x01C / 4] = lbl_801E89D0[0];
	dst[0x020 / 4] = lbl_801E89D0[1];
	dst[0x024 / 4] = lbl_801E89D0[2];
	dst[0x030 / 4] = lbl_801E89DC[0];
	dst[0x034 / 4] = lbl_801E89DC[1];
	dst[0x038 / 4] = lbl_801E89DC[2];
	dst[0x044 / 4] = lbl_801E89E8[0];
	dst[0x048 / 4] = lbl_801E89E8[1];
	dst[0x04C / 4] = lbl_801E89E8[2];
	dst[0x058 / 4] = lbl_801E89F4[0];
	dst[0x05C / 4] = lbl_801E89F4[1];
	dst[0x060 / 4] = lbl_801E89F4[2];
	dst[0x06C / 4] = lbl_801E8A00[0];
	dst[0x070 / 4] = lbl_801E8A00[1];
	dst[0x074 / 4] = lbl_801E8A00[2];
	dst[0x080 / 4] = lbl_801E8A0C[0];
	dst[0x084 / 4] = lbl_801E8A0C[1];
	dst[0x088 / 4] = lbl_801E8A0C[2];
	dst[0x160 / 4] = lbl_801E8A18[0];
	dst[0x164 / 4] = lbl_801E8A18[1];
	dst[0x168 / 4] = lbl_801E8A18[2];

	dst[0x16C / 4] = lbl_801E8A24[0];
	dst[0x170 / 4] = lbl_801E8A24[1];
	dst[0x174 / 4] = lbl_801E8A24[2];
	dst[0x178 / 4] = lbl_801E8A30[0];
	dst[0x17C / 4] = lbl_801E8A30[1];
	dst[0x180 / 4] = lbl_801E8A30[2];
	dst[0x18C / 4] = lbl_801E8A3C[0];
	dst[0x190 / 4] = lbl_801E8A3C[1];
	dst[0x194 / 4] = lbl_801E8A3C[2];
	dst[0x1A0 / 4] = lbl_801E8A48[0];
	dst[0x1A4 / 4] = lbl_801E8A48[1];
	dst[0x1A8 / 4] = lbl_801E8A48[2];
	dst[0x1B4 / 4] = lbl_801E8A54[0];
	dst[0x1B8 / 4] = lbl_801E8A54[1];
	dst[0x1BC / 4] = lbl_801E8A54[2];
	dst[0x1C8 / 4] = lbl_801E8A60[0];
	dst[0x1CC / 4] = lbl_801E8A60[1];
	dst[0x1D0 / 4] = lbl_801E8A60[2];
	dst[0x1DC / 4] = lbl_801E8A6C[0];
	dst[0x1E0 / 4] = lbl_801E8A6C[1];
	dst[0x1E4 / 4] = lbl_801E8A6C[2];
	dst[0x2BC / 4] = lbl_801E8A78[0];
	dst[0x2C0 / 4] = lbl_801E8A78[1];
	dst[0x2C4 / 4] = lbl_801E8A78[2];
	dst[0x2C8 / 4] = lbl_801E8A84[0];
	dst[0x2CC / 4] = lbl_801E8A84[1];
	dst[0x2D0 / 4] = lbl_801E8A84[2];
	dst[0x2D4 / 4] = lbl_801E8A90[0];
	dst[0x2D8 / 4] = lbl_801E8A90[1];
	dst[0x2DC / 4] = lbl_801E8A90[2];
	dst[0x2E8 / 4] = lbl_801E8A9C[0];
	dst[0x2EC / 4] = lbl_801E8A9C[1];
	dst[0x2F0 / 4] = lbl_801E8A9C[2];

	dst[0x2FC / 4] = lbl_801E8AA8[0];
	dst[0x300 / 4] = lbl_801E8AA8[1];
	dst[0x304 / 4] = lbl_801E8AA8[2];
	dst[0x310 / 4] = lbl_801E8AB4[0];
	dst[0x314 / 4] = lbl_801E8AB4[1];
	dst[0x318 / 4] = lbl_801E8AB4[2];
	dst[0x324 / 4] = lbl_801E8AC0[0];
	dst[0x328 / 4] = lbl_801E8AC0[1];
	dst[0x32C / 4] = lbl_801E8AC0[2];
	dst[0x338 / 4] = lbl_801E8ACC[0];
	dst[0x33C / 4] = lbl_801E8ACC[1];
	dst[0x340 / 4] = lbl_801E8ACC[2];

	__register_global_object(&lbl_8032ECC8, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x188);
	__register_global_object(&lbl_8032ECCC, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x194);
	__register_global_object(&lbl_8032ECD0, reinterpret_cast<void*>(__dt__11CRelProfileFv), MapPcs + 0x1A0);
}

/*
 * --INFO--
 * PAL Address: 0x80036254
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CRelProfile* __dt__11CRelProfileFv(CRelProfile* self, short shouldDelete)
{
	if ((self != 0) && (shouldDelete > 0))
	{
		__dl__FPv(self);
	}
	return self;
}
