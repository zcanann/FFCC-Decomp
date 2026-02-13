#include "ffcc/pppCharaBreak.h"

/*
 * --INFO--
 * PAL Address: 0x801411DC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" u32 CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(u32 value, void* modelData, void* meshData)
{
    if (*(u32*)((u8*)modelData + 0x44) == 0) {
        return value;
    }

    return (u32)__cntlzw(1 - (u32)*((u8*)meshData + 0x42)) >> 5;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2CharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderCharaBreak(void)
{
	// TODO
}
