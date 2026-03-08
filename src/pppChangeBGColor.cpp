#include "ffcc/pppChangeBGColor.h"
#include "ffcc/ppp_linkage.h"

class CMapMng;
extern CMapMng MapMng;

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
    unsigned char* data;
    unsigned char* mapMng;
    int dataOffset;

    if (gPppCalcDisabled != 0) {
        return;
    }

    dataOffset = param_3->m_serializedDataOffsets[1];
    data = reinterpret_cast<unsigned char*>(pppChangeBGColor) + dataOffset + 0x80;
    mapMng = reinterpret_cast<unsigned char*>(&MapMng);
    mapMng[0x22989] = 1;
    mapMng[0x22990] = data[8];
    mapMng[0x22991] = data[9];
    mapMng[0x22992] = data[10];
    mapMng[0x22993] = data[11];
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
