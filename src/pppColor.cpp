#include "global.h"
#include "ffcc/pppColor.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(VColor) == 0xC);
STATIC_ASSERT(offsetof(VColor, m_red) == 0x0);
STATIC_ASSERT(offsetof(VColor, m_green) == 0x2);
STATIC_ASSERT(offsetof(VColor, m_blue) == 0x4);
STATIC_ASSERT(offsetof(VColor, m_alpha) == 0x6);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x8);

STATIC_ASSERT(sizeof(PppColorDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(PppColorDataOffsets, m_workOffset) == 0x0);

static inline PppColorDataOffsets* GetPppColorDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<PppColorDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline VColor* GetPppColorWork(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(obj->m_workArea + GetPppColorDataOffsets(ctrl)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x8005FF8C
 * PAL Size: 40b
 * EN Address: 0x8005F8F4
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColorCon(_pppPObject* param1, _pppCtrlTable* param2)
{
    VColor* work = GetPppColorWork(param1, param2);

    work->m_alpha = 0;
    work->m_blue = 0;
    work->m_green = 0;
    work->m_red = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 * EN Address: 0x8005F91C
 * EN Size: 416b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColor(_pppPObject* param1, pppColorStep* step, _pppCtrlTable* param3)
{
    VColor* work = GetPppColorWork(param1, param3);

    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 id1 = step->m_graphId;
    s32 id2 = param1->m_graphId;

    if (id1 == id2) {
        work->m_red += step->m_colors[0];
        work->m_green += step->m_colors[1];
        work->m_blue += step->m_colors[2];
        work->m_alpha += step->m_colors[3];
    }

    if (ppvMng->m_useOwnerScaleSign != 0) {
        work->m_color.rgba[0] = (u8)((float)(work->m_red >> 7) * ppvMng->m_userFloat0);
        work->m_color.rgba[1] = (u8)((float)(work->m_green >> 7) * ppvMng->m_userFloat1);
        work->m_color.rgba[2] = (u8)((float)(work->m_blue >> 7) * ppvMng->m_scaleFactor);
        work->m_color.rgba[3] = (u8)((float)(work->m_alpha >> 7) * ppvMng->m_ownerScale);
        return;
    }

    work->m_color.rgba[0] = (u8)(work->m_red >> 7);
    work->m_color.rgba[1] = (u8)(work->m_green >> 7);
    work->m_color.rgba[2] = (u8)(work->m_blue >> 7);
    work->m_color.rgba[3] = (u8)(work->m_alpha >> 7);
}
