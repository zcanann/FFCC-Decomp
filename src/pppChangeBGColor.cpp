#include "ffcc/pppChangeBGColor.h"
#include "ffcc/map.h"

// External global variables 
extern int DAT_8032ed70;

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

	unsigned char* mapMng = (unsigned char*)&MapMng;
	unsigned char* data = (unsigned char*)pppChangeBGColor + param_3->m_serializedDataOffsets[1] + 0x80;

	mapMng += 0x20000;
	mapMng[0x2989] = 1;
	mapMng[0x2990] = data[8];
	mapMng[0x2991] = data[9];
	mapMng[0x2992] = data[10];
	mapMng[0x2993] = data[11];
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
