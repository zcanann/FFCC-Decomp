#include "ffcc/pppChangeTex.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructChangeTex(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2ChangeTex(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructChangeTex(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameChangeTex(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8013ef94
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderChangeTex(void* pppChangeTex, int param_2)
{
    int local_8;
    
    local_8 = 0;
    
    if (*(int *)(param_2 + 4) != 0xffff) {
        // Function calls for now - will need proper globals
        // GetTexture call structure matches Ghidra
        // GXSetTevSwapMode call structure matches Ghidra  
        // pppInitBlendMode call structure matches Ghidra
    }
    return;
}

#ifdef __cplusplus
}
#endif
