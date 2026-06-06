#include "ffcc/ptrarray.h"
#include "ffcc/pppChangeBGColor.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/ppp_linkage.h"

struct ChangeBGColorWork {
    u8 m_pad[8];
    GXColor m_color;
};

STATIC_ASSERT(offsetof(ChangeBGColorWork, m_color) == 0x08);
STATIC_ASSERT(sizeof(ChangeBGColorDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(ChangeBGColorDataOffsets, m_colorWorkOffset) == 0x4);

static inline ChangeBGColorDataOffsets* GetChangeBGColorDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<ChangeBGColorDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline ChangeBGColorWork* GetChangeBGColorWork(pppChangeBGColor* changeBGColor, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<ChangeBGColorWork*>(
        changeBGColor->m_workArea + GetChangeBGColorDataOffsets(ctrlTable)->m_colorWorkOffset);
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
void pppFrameChangeBGColor(pppChangeBGColor* changeBGColor, pppNoStep* stepData, _pppCtrlTable* ctrlTable)
{
    (void)stepData;

    if (ppvUserStopPartF != 0) {
        return;
    }

    ChangeBGColorWork* work = GetChangeBGColorWork(changeBGColor, ctrlTable);
    MapMng.m_colorScaleEnable = 1;
    MapMng.m_colorScale.r = work->m_color.r;
    MapMng.m_colorScale.g = work->m_color.g;
    MapMng.m_colorScale.b = work->m_color.b;
    MapMng.m_colorScale.a = work->m_color.a;
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
