#include "ffcc/pppScreenQuake.h"
#include "ffcc/p_camera.h"

extern float FLOAT_80331fc8;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConScreenQuake(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8013e50c
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenQuake(void)
{
	// TODO - needs parameter signature fix for non-zero match
}

/*
 * --INFO--
 * PAL Address: 0x8013e4b8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenQuake(void)
{
	double dVar1;
	
	dVar1 = (double)FLOAT_80331fc8;
	CameraPcs.SetQuakeParameter((int)dVar1, (int)dVar1, (short)dVar1, (short)dVar1, 
	                            (float)dVar1, (float)dVar1, (float)dVar1, (float)dVar1, 
	                            (float)dVar1, (float)dVar1, 1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameScreenQuake(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderScreenQuake(void)
{
	// TODO
}