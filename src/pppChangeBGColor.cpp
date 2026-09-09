#include "ffcc/ptrarray.h"
#include "ffcc/pppChangeBGColor.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(offsetof(VColor, m_color) == 0x08);
STATIC_ASSERT(sizeof(ChangeBGColorDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(ChangeBGColorDataOffsets, m_colorWorkOffset) == 0x4);

static inline ChangeBGColorDataOffsets* GetChangeBGColorDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<ChangeBGColorDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline VColor* GetChangeBGColorWork(pppChangeBGColor* changeBGColor, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<VColor*>(
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

    VColor* work = GetChangeBGColorWork(changeBGColor, ctrlTable);
    MapMng.m_colorScaleEnable = 1;
    MapMng.m_colorScale.r = work->m_color.rgba[0];
    MapMng.m_colorScale.g = work->m_color.rgba[1];
    MapMng.m_colorScale.b = work->m_color.rgba[2];
    MapMng.m_colorScale.a = work->m_color.rgba[3];
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
