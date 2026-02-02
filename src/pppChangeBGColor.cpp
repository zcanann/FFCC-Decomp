#include "ffcc/pppChangeBGColor.h"
#include "ffcc/map.h"

// External global variables 
extern int DAT_8032ed70;

/*
 * --INFO--
 * PAL Address: 0x8012d454
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConChangeBGColor(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8012d450
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesChangeBGColor(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8012d3fc
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameChangeBGColor(struct pppChangeBGColor* pppChangeBGColor, struct UnkB* param_2, struct UnkC* param_3)
{
	if (DAT_8032ed70 != 0) {
		return;
	}
	
	int iVar1 = param_3->m_serializedDataOffsets[1];
	iVar1 += 0x80;  // Add offset first
	
	// Access MapMng fields using byte pointer arithmetic to match assembly
	char* mapMngPtr = (char*)&MapMng;
	char* indexedPtr = (char*)pppChangeBGColor + iVar1;
	
	*(mapMngPtr + 0x22989) = 1;  // _141705_1_
	*(mapMngPtr + 0x22990) = *(indexedPtr + 0x8);  // _141712_1_
	*(mapMngPtr + 0x22991) = *(indexedPtr + 0x9);  // _141713_1_
	*(mapMngPtr + 0x22992) = *(indexedPtr + 0xa);  // _141714_1_
	*(mapMngPtr + 0x22993) = *(indexedPtr + 0xb);  // _141715_1_
	return;
}
