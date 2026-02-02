#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_rand()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VYmMegaBirthShpTail2* vdata, PYmMegaBirthShpTail2* param)
{
	vdata->m_maxParticles = *(unsigned short*)((char*)&param->m_matrix + 0xe);
	// TODO: Proper memory allocation
	vdata->m_particles = (_PARTICLE_DATA*)0;
	vdata->m_wmats = (_PARTICLE_WMAT*)0;
	vdata->m_colors = (_PARTICLE_COLOR*)0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructYmMegaBirthShpTail2(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructYmMegaBirthShpTail2(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 */
void pppFrameYmMegaBirthShpTail2(void)
{
	// TODO: Implement frame processing
}

/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 */
void pppRenderYmMegaBirthShpTail2(void)
{
	// TODO: Implement rendering
}
