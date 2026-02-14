#include "ffcc/cflat_r2system.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_map.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/USBStreamData.h"
#include <string.h>

static inline CUSBStreamData* UsbStream(CPartPcs* self)
{
    return reinterpret_cast<CUSBStreamData*>((char*)self + 0x8);
}

struct CMapCylinderRaw
{
    Vec m_bottom;
    Vec m_direction;
    float m_radius;
    float m_height;
    Vec m_top;
    Vec m_direction2;
    float m_radius2;
    float m_height2;
};

extern "C" {
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned long);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
}

/*
 * --INFO--
 * PAL Address: 0x800B8F80
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SetNextScriptNewGame()
{
    m_nextScript.m_flags = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800B8F90
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetFullScreenShadowCamLen(float len)
{
    *(float*)((char*)this + 0x430) = len;
}

/*
 * --INFO--
 * PAL Address: 0x800B8F98
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFont* CMenuPcs::GetFont22()
{
    return *(CFont**)((char*)this + 0xF8);
}

/*
 * --INFO--
 * PAL Address: 0x800B8FA0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SeMaxVolume(int volume)
{
    *(int*)((char*)this + 0x22BC) = volume;
}

/*
 * --INFO--
 * PAL Address: 0x800B8FA8
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::pppSetDebugHide(unsigned char hide)
{
    UsbStream(this)->m_disableShokiDraw = hide;
}

/*
 * --INFO--
 * PAL Address: 0x800B8FB0
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CalcHitPosition__7CMapPcsFP3Vec(CMapPcs*, Vec* hitPosition)
{
    CalcHitPosition__7CMapObjFP3Vec(*(void**)((char*)&MapMng + 0x22A78), hitPosition);
}

/*
 * --INFO--
 * PAL Address: 0x800B8FE0
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl(
    CMapPcs*, Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
    CMapCylinderRaw cylinder;

    cylinder.m_direction.x = 0.0f;
    cylinder.m_direction.y = 0.0f;
    cylinder.m_direction.z = 0.0f;
    cylinder.m_direction2.x = 1.0f;
    cylinder.m_direction2.y = 1.0f;
    cylinder.m_direction2.z = 1.0f;

    cylinder.m_bottom = *cylinderBottom;
    cylinder.m_top = *direction;
    cylinder.m_radius = radius;
    cylinder.m_height = 0.0f;
    cylinder.m_radius2 = 0.0f;
    cylinder.m_height2 = 0.0f;

    return CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
        &MapMng, reinterpret_cast<CMapCylinder*>(&cylinder), direction, hitMask);
}

/*
 * --INFO--
 * PAL Address: 0x800B9060
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned char* GetTmpFrameBuffer__8CGraphicFv(CGraphic* graphic)
{
    return *(unsigned char**)((char*)graphic + 0x7208);
}

/*
 * --INFO--
 * PAL Address: 0x800B9068
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMiniGamePcs::GetMiniGameParam(int id)
{
    if (id == 0x2002) {
        return *(signed char*)((char*)this + 0x649A);
    }
    if (id < 0x2002) {
        if (id == 0x2000) {
            return *(signed char*)((char*)this + 0x6498);
        }
        if (id > 0x1FFF) {
            return *(signed char*)((char*)this + 0x6499);
        }
    } else if (id < 0x2004) {
        return *(signed char*)((char*)this + 0x649B);
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800B90C8
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::SetMiniGameParam(int id, int value)
{
    if ((unsigned int)System.m_execParam > 2U) {
        System.Printf("SetMiniGameParam no 0x%04x data[%d]\n", id, value);
    }

    if (id == 0x1202) {
        *(unsigned char*)((char*)this + 0x134B) |= (unsigned char)(1 << value);
    } else if (id < 0x1202) {
        if (id == 0x1102) {
            *(unsigned char*)((char*)this + 0x1348) = 1;
        } else if (id > 0x1100 && id < 0x1102) {
            *(signed char*)((char*)this + 0x1350) = (signed char)value;
        }
    } else if (id < 0x1204) {
        *(unsigned char*)((char*)this + 0x134B) &= (unsigned char)~(1 << value);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800B91A4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::CGameWork::ClearEvtWork()
{
    memset(m_eventFlags, 0, sizeof(m_eventFlags));
    memset(m_eventWork, 0, sizeof(m_eventWork));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSetSystemVal(int, CFlatRuntime::CStack*, int)
{
	// TODO
}
