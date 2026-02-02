#include "ffcc/pppYmCheckBGHeight.h"

extern int DAT_8032ed70;
extern struct _pppMngSt* pppMngStPtr;
extern struct CMapMng MapMng;

/*
 * --INFO--
 * PAL Address: 800d8c18
 * PAL Size: 4b
 */
void pppConstructYmCheckBGHeight(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 800d8abc  
 * PAL Size: 348b
 */
struct pppYmCheckBGHeight* pppFrameYmCheckBGHeight(struct pppYmCheckBGHeight* pppYmCheckBGHeight, struct UnkC* param_2)
{
	if (DAT_8032ed70 == 0) {
		// Height checking logic would go here
		// For now, just return the first parameter
	}
	return pppYmCheckBGHeight;
}