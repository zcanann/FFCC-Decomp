#include "ffcc/pppChangeBGColor.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/ppp_linkage.h"

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
    int dataOffset;

    if (gPppCalcDisabled != 0) {
        return;
    }

    dataOffset = param_3->m_serializedDataOffsets[1];
    data = reinterpret_cast<unsigned char*>(pppChangeBGColor) + dataOffset + 0x80;
    MapMng.m_colorScaleEnable = 1;
    MapMng.m_colorScale.r = data[8];
    MapMng.m_colorScale.g = data[9];
    MapMng.m_colorScale.b = data[10];
    MapMng.m_colorScale.a = data[11];
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
