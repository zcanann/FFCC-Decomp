#include "ffcc/pppChangeBGColor.h"
#include "ffcc/ppp_linkage.h"

class CMapMng;
extern CMapMng MapMng;

namespace {
static inline unsigned char* Ptr(void* ptr, int offset)
{
    return reinterpret_cast<unsigned char*>(ptr) + offset;
}
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
void pppFrameChangeBGColor(struct pppChangeBGColor* pppChangeBGColor, struct pppChangeBGColorUnkB* param_2,
                           _pppCtrlTable* param_3)
{
	int* serializedDataOffsets;
	unsigned char* mapMng;
	unsigned char* data;

	if (gPppCalcDisabled != 0) {
		return;
	}

	serializedDataOffsets = param_3->m_serializedDataOffsets;
	mapMng = Ptr(&MapMng, 0x20000);
	data = reinterpret_cast<unsigned char*>(pppChangeBGColor) + serializedDataOffsets[1] + 0x80;
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
void pppDesChangeBGColor(_pppPObjLink*, _pppCtrlTable*)
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
void pppConChangeBGColor(_pppPObjLink*, _pppCtrlTable*)
{
	return;
}
