#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"

extern char lbl_801DC4D0[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana2_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructMana2(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructMana2(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameMana2(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80107e48
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMana2(void)
{
    Graphic.Printf(lbl_801DC4D0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
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
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*) [4], void*, unsigned long, _GXColor*, S16Vec2d*, CChara::CNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreateWaterMesh(Vec*, Vec*, Vec2d*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateWaterMesh(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderWaterMesh(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalculateNormal(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcWaterReflectionVector(Vec*, Vec*, Vec*, long, Vec*, float (*) [4], _GXColor*, Vec2d*)
{
	// TODO
}
