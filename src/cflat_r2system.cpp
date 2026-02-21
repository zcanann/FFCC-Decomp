#include "ffcc/cflat_r2system.h"
#include "ffcc/color.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/mes.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_map.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/vector.h"
#include <math.h>
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
int GetWait__4CMesFv(void*);
unsigned char lbl_8032ECB8;
}
extern "C" double fmod(double, double);
extern "C" double atan2(double, double);
extern "C" double cos(double);
extern "C" double sin(double);
extern float FLOAT_80330cec;
extern float FLOAT_80330cf0;
extern float FLOAT_80330d10;
extern float FLOAT_80330d30;
extern float DAT_8032ec20;

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
    switch (id) {
    case 0x2000:
        return *(signed char*)((char*)this + 0x6498);
    case 0x2001:
        return *(signed char*)((char*)this + 0x6499);
    case 0x2002:
        return *(signed char*)((char*)this + 0x649A);
    case 0x2003:
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
 * PAL Address: 0x800B91EC
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetShadowAuto__10CCameraPcsFi(void* camera, int enable)
{
    *(int*)((char*)camera + 0x434) = enable;
}

/*
 * --INFO--
 * PAL Address: 0x800B91F4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetTexShadowRadius__9CCharaPcsFf(void* charaPcs, float texShadowRadius)
{
    *(float*)((char*)charaPcs + 0x188) = texShadowRadius;
}

/*
 * --INFO--
 * PAL Address: 0x800B91FC
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetTexShadowColor__9CCharaPcsF8_GXColor(void* charaPcs, const unsigned char* color)
{
    unsigned char* self = (unsigned char*)charaPcs;
    unsigned char v;

    v = color[0];
    self[0x18C] = v;
    v = color[1];
    self[0x18D] = v;
    v = color[2];
    self[0x18E] = v;
    v = color[3];
    self[0x18F] = v;
}

/*
 * --INFO--
 * PAL Address: 0x800B9220
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CColor::operator _GXColor()
{
    return color;
}

/*
 * --INFO--
 * PAL Address: 0x800B9224
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" _GXColor* __opP8_GXColor__6CColorFv(CColor* self)
{
    return &self->color;
}

/*
 * --INFO--
 * PAL Address: 0x800B9228
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetTexShadowPos__9CCharaPcsFP3Vec(void* charaPcs, Vec* vec)
{
    float* self = (float*)((char*)charaPcs + 0x17C);

    self[0] = vec->x;
    self[1] = vec->y;
    self[2] = vec->z;
}

/*
 * --INFO--
 * PAL Address: 0x800B9244
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetEvtWord__12CCaravanWorkFis(CCaravanWork* caravanWork, int evtWordIndex, short evtWord)
{
    caravanWork->m_evtWordArr[evtWordIndex] = evtWord;
}

/*
 * --INFO--
 * PAL Address: 0x800B9254
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int GetEvtWord__12CCaravanWorkFi(CCaravanWork* caravanWork, int evtWordIndex)
{
    return caravanWork->m_evtWordArr[evtWordIndex];
}

/*
 * --INFO--
 * PAL Address: 0x800B9264
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetEvtFlag__12CCaravanWorkFii(CCaravanWork* caravanWork, int evtFlagIndex, int value)
{
    unsigned char* evtFlags = reinterpret_cast<unsigned char*>(caravanWork->m_evtWorkArr);
    int sign = evtFlagIndex >> 31;
    int byteIndex = (evtFlagIndex >> 3) + (int)(evtFlagIndex < 0 && (evtFlagIndex & 7) != 0);
    int bitIndex =
        ((sign * 8) | ((int)(((unsigned int)evtFlagIndex * 0x20000000u + (unsigned int)sign) >> 29))) - sign;
    unsigned char mask = (unsigned char)(1u << bitIndex);

    if (value != 0) {
        evtFlags[byteIndex] |= mask;
    } else {
        evtFlags[byteIndex] &= (unsigned char)~mask;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800B92DC
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int GetEvtFlag__12CCaravanWorkFi(CCaravanWork* caravanWork, int evtFlagIndex)
{
    unsigned char* evtFlags = reinterpret_cast<unsigned char*>(caravanWork->m_evtWorkArr);
    int byteIndex = evtFlagIndex / 8;
    int bitIndex = evtFlagIndex - byteIndex * 8;
    unsigned char mask = (unsigned char)(1u << bitIndex);

    return (evtFlags[byteIndex] & mask) != 0;
}

extern "C" int m_tempVar__4CMes[];

/*
 * --INFO--
 * PAL Address: 0x800B931C
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetTempValue__4CMesFii(int index, int value)
{
    m_tempVar__4CMes[index] = value;
}

/*
 * --INFO--
 * PAL Address: 0x800B9330
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned short GetGbaButtonDown__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        int activePad = *(int*)((char*)pad + 0x1C0);
        int idx;
        char* slot;

        padIndex = padIndex &
                   ~((int)~(activePad - padIndex | padIndex - activePad) >> 31);
        idx = (int)padIndex * 0x54;
        slot = (char*)pad + idx;
        result = *(unsigned short*)(slot + 0xA);
    }

    return (unsigned short)result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9960
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" double GetRightStickY__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return (double)0.0f;
    }

    return (double)*(float*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                        padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                          31)) *
                                               0x54 +
                             0x30);
}

/*
 * --INFO--
 * PAL Address: 0x800B99C0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" double GetRightStickX__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return (double)0.0f;
    }

    return (double)*(float*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                        padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                          31)) *
                                               0x54 +
                             0x2C);
}

/*
 * --INFO--
 * PAL Address: 0x800B9A20
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" double GetLeftStickY__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return (double)0.0f;
    }

    return (double)*(float*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                        padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                          31)) *
                                               0x54 +
                             0x28);
}

/*
 * --INFO--
 * PAL Address: 0x800B9A80
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" double GetLeftStickX__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return (double)0.0f;
    }

    return (double)*(float*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                        padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                          31)) *
                                               0x54 +
                             0x24);
}

/*
 * --INFO--
 * PAL Address: 0x800B9AE0
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned short GetButtonRepeat__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        result = *(unsigned short*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                               padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                                 31)) *
                                                  0x54 +
                                    0x14);
    }

    return (unsigned short)result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9BB8
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned short GetButton__4CPadFl(void* pad, long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (*(int*)((char*)pad + 0x1C4) == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (*(int*)((char*)pad + 0x1C0) == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        result = *(unsigned short*)((char*)pad + (padIndex & ~((int)~(*(int*)((char*)pad + 0x1C0) - padIndex |
                                                               padIndex - *(int*)((char*)pad + 0x1C0)) >>
                                                 31)) *
                                                  0x54 +
                                    4);
    }

    return (unsigned short)result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9394
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetMapShadeColor__9CCharaPcsFi6CColor(void* charaPcs, int shadeIndex, const unsigned char* color)
{
    unsigned int self = (unsigned int)charaPcs + shadeIndex * 4;
    unsigned char value1;
    unsigned char value2;

    value1 = color[1];
    *(unsigned char*)(self + 0x12C) = color[0];
    value2 = color[2];
    *(unsigned char*)(self + 0x12D) = value1;
    value1 = color[3];
    *(unsigned char*)(self + 0x12E) = value2;
    *(unsigned char*)(self + 0x12F) = value1;
}

/*
 * --INFO--
 * PAL Address: 0x800B93C0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetNoFreeMergeMask__9CCharaPcsFi(void* charaPcs, int mask)
{
    *(int*)((char*)charaPcs + 0x718) = mask;
}

/*
 * --INFO--
 * PAL Address: 0x800B93C8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ResetDefaultGroup__7CMemoryFv(void* memory)
{
    *(int*)((char*)memory + 0x779C) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800B93D4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetDefaultGroup__7CMemoryFi(void* memory, int group)
{
    *(int*)((char*)memory + 0x779C) = group;
}

/*
 * --INFO--
 * PAL Address: 0x800B93DC
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetCharaAllocStage__9CCharaPcsFi(void* charaPcs, int stage)
{
    *(int*)((char*)charaPcs + 0xE4) = stage;
}

/*
 * --INFO--
 * PAL Address: 0x800B93E4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetUseDOF__11CGraphicPcsFi(void* graphicPcs, int enabled)
{
    *(int*)((char*)graphicPcs + 0xC0) = enabled;
}

/*
 * --INFO--
 * PAL Address: 0x800B93EC
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void Close__Q25CFile7CHandleFv(CFile::CHandle* fileHandle)
{
    File.Close(fileHandle);
}

/*
 * --INFO--
 * PAL Address: 0x800B9418
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CFile::GetBuffer()
{
    return m_readBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x800B9420
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::CHandle::SyncCompleted()
{
    File.SyncCompleted(this);
}

/*
 * --INFO--
 * PAL Address: 0x800B944C
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::CHandle::Read()
{
    File.Read(this);
}

extern "C" int GetWait__4CMesFv(void*);

/*
 * --INFO--
 * PAL Address: 0x800B9478
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ReqScreenCapture__11CGraphicPcsFv(void* graphicPcs)
{
    *(int*)((char*)graphicPcs + 0xBC) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800B9484
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int IsUse__8CMesMenuFv(void* mesMenu)
{
    if (*(int*)((char*)mesMenu + 8) != 0 && *(int*)((char*)mesMenu + 0xC) < 2 &&
        GetWait__4CMesFv((char*)mesMenu + 0x1C) != 4) {
        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800B94DC
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int GetErrorLevel__7CSystemFv(void* system, int index)
{
    return ((int*)((char*)system + 0x3CDC))[index];
}

/*
 * --INFO--
 * PAL Address: 0x800B94EC
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void GetMes__9CFlatDataFi(void* flatData, int index, int value)
{
    ((int*)((char*)flatData + 0x3CDC))[index] = value;
}

/*
 * --INFO--
 * PAL Address: 0x800B94FC
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int GetNumMes__9CFlatDataFv(void* flatData)
{
    return *(int*)((char*)flatData + 0x125C);
}

/*
 * --INFO--
 * PAL Address: 0x800B9504
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int GetSysMes__5CGameFi(void* game, int index)
{
    return ((int*)((char*)game + 0x3CDC))[index + 1];
}

/*
 * --INFO--
 * PAL Address: 0x800B9514
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" char* GetNumSysMes__5CGameFv(void* game, int index)
{
    return ((char**)((char*)game + 0xE1E0))[index];
}

/*
 * --INFO--
 * PAL Address: 0x800B9538
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__14PPPCREATEPARAMFv2(PPPCREATEPARAM* pppCreateParam);

extern "C" void __ct__14PPPCREATEPARAMFv(PPPCREATEPARAM* pppCreateParam)
{
    __ct__14PPPCREATEPARAMFv2(pppCreateParam);
}

/*
 * --INFO--
 * PAL Address: 0x800B9548
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__14PPPCREATEPARAMFv2(PPPCREATEPARAM* pppCreateParam)
{
    pppCreateParam->m_soundEffectParams.m_soundEffectHandle = -1;
    pppCreateParam->m_soundEffectParams.m_soundEffectSlot = -1;
    pppCreateParam->m_soundEffectParams.m_soundEffectStopFlag = 0;
    pppCreateParam->m_soundEffectParams.m_soundEffectKind = 1;
    pppCreateParam->m_soundEffectParams.m_soundEffectStartFrame = 0;
    pppCreateParam->m_soundEffectParams.m_soundEffectStartedOnce = 0;
    pppCreateParam->m_soundEffectParams.m_soundEffectFadeFrames = 30;
    pppCreateParam->m_hitParamA = 0;
    pppCreateParam->m_hitParamB = 0;
    pppCreateParam->m_hitObjectCount = 0;
    pppCreateParam->m_hitFlags = 0;
    pppCreateParam->m_positionOffsetPtr = 0;
    pppCreateParam->m_rotationPtr = 0;
    pppCreateParam->m_scalePtr = 0;
    pppCreateParam->m_extraPositionPtr = 0;
    pppCreateParam->m_paramA = 0;
    pppCreateParam->m_paramB = 0;
    pppCreateParam->m_lookTargetPtr = 0;
    pppCreateParam->m_objectHitMask = 0;
    pppCreateParam->m_cylinderAttribute = 0;
    pppCreateParam->m_paramC = 1.0f;
    pppCreateParam->m_paramD = 1.0f;
    *(unsigned char*)&pppCreateParam->m_owner = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800B95AC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __opR3Vec__7CVectorFv(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x800B95B0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetWorldMapMatrix__10CCameraPcsFPA4_f(void* camera, Mtx matrix)
{
    PSMTXCopy(matrix, (MtxPtr)((char*)camera + 0x34));
    PSMTXInverse(matrix, (MtxPtr)((char*)camera + 0x64));
}

/*
 * --INFO--
 * PAL Address: 0x800B95FC
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void GetWorldMapMatrix__10CCameraPcsFPA4_f(void* camera, Mtx matrix)
{
    PSMTXCopy((MtxPtr)((char*)camera + 0x34), matrix);
}

/*
 * --INFO--
 * PAL Address: 0x800B9620
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void IsHitDrawMode__7CMapPcsFc(CMapPcs*, unsigned char drawMode)
{
    lbl_8032ECB8 = drawMode;
}

/*
 * --INFO--
 * PAL Address: 0x800B9628
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetFullScreenShadowRot(float rotX, float rotY)
{
    *(float*)((char*)this + 0x364) = rotX;
    *(float*)((char*)this + 0x368) = rotY;
}

/*
 * --INFO--
 * PAL Address: 0x800B9634
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetFullScreenShadowPos(Vec* position, float len)
{
    *(float*)((char*)this + 0x408) = *(float*)((char*)position + 0x0);
    *(float*)((char*)this + 0x40C) = *(float*)((char*)position + 0x4);
    *(float*)((char*)this + 0x410) = *(float*)((char*)position + 0x8);
    *(float*)((char*)this + 0x370) = len;
}

/*
 * --INFO--
 * PAL Address: 0x800B9654
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetFullScreenShadowEnable(unsigned char enable)
{
    *(unsigned char*)((char*)this + 0x404) = enable;
}

/*
 * --INFO--
 * PAL Address: 0x800B965C
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void GetViewMatrix__10CCameraPcsFPA4_f(void* camera, Mtx matrix)
{
    PSMTXCopy((MtxPtr)((char*)camera + 4), matrix);
}

/*
 * --INFO--
 * PAL Address: 0x800B9680
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void VECLerp(Vec* a, Vec* b, Vec* out, float t)
{
    Vec scaledA;
    Vec scaledB;

    PSVECScale(a, &scaledA, 1.0f - t);
    PSVECScale(b, &scaledB, t);
    PSVECAdd(&scaledA, &scaledB, out);
}

/*
 * --INFO--
 * PAL Address: 0x800B96F8
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetDiffuse__9CCharaPcsFiUlP8_GXColorP3Vec(
    CCharaPcs* chara, int lightIndex, unsigned long lightSet, _GXColor* color, Vec* direction)
{
    char* colorBase = (char*)chara + lightIndex * 0xC + lightSet * 4;
    colorBase[0xF0] = color->r;
    colorBase[0xF1] = color->g;
    colorBase[0xF2] = color->b;
    colorBase[0xF3] = color->a;

    if (lightIndex != 0) {
        return;
    }

    char* dirBase = (char*)chara + lightSet * 0xC;
    *(float*)(dirBase + 0x108) = direction->x;
    *(float*)(dirBase + 0x10C) = direction->y;
    *(float*)(dirBase + 0x110) = direction->z;
}

/*
 * --INFO--
 * PAL Address: 0x800B9754
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetAmbient__9CCharaPcsFiP8_GXColor(CCharaPcs* chara, int index, _GXColor* color)
{
    char* base = (char*)chara + index * 4;
    base[0xE8] = color->r;
    base[0xE9] = color->g;
    base[0xEA] = color->b;
    base[0xEB] = color->a;
}

/*
 * --INFO--
 * PAL Address: 0x800B9784
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void VECMultAdd(Vec* a, Vec* b, Vec* out, float scale)
{
    Vec scaled;

    PSVECScale(b, &scaled, scale);
    PSVECAdd(a, &scaled, out);
}

/*
 * --INFO--
 * PAL Address: 0x800B97D8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __opP3Vec__7CVectorFv(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x800B97DC
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CVector CVector::operator+(const CVector& other) const
{
    CVector out;

    PSVECAdd((const Vec*)this, (const Vec*)&other, (Vec*)&out);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x800B984C
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CVector::operator=(const CVector& other)
{
    float y = other.y;
    x = other.x;
    float z = other.z;
    this->y = y;
    this->z = z;
}

/*
 * --INFO--
 * PAL Address: 0x800B9868
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CVector::CVector(const CVector& other)
{
    float y = other.y;
    x = other.x;
    float z = other.z;
    this->y = y;
    this->z = z;
}

/*
 * --INFO--
 * PAL Address: 0x800B9884
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CVector CVector::operator-(const CVector& other) const
{
    CVector out;

    PSVECSubtract((const Vec*)this, (const Vec*)&other, (Vec*)&out);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x800B98F4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" float fmodf__3stdFff(float x, float y)
{
    return (float)fmod((double)x, (double)y);
}

/*
 * --INFO--
 * PAL Address: 0x800B9918
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetFov__10CCameraPcsFf(CCameraPcs* camera, float fov)
{
    *(float*)((char*)camera + 0xFC) = fov;
}

/*
 * --INFO--
 * PAL Address: 0x800B9920
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetZRotate(float zRotate)
{
    *(float*)((char*)this + 0x108) = zRotate;
}

/*
 * --INFO--
 * PAL Address: 0x800B9928
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SetNextScript(CGame::CNextScript* nextScript)
{
    unsigned int* dst = (unsigned int*)&m_nextScript;
    unsigned int* src = (unsigned int*)nextScript;
    int count = 0x20;

    do {
        *dst++ = *src++;
        *dst++ = *src++;
        count--;
    } while (count != 0);

    m_newGameFlag = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800B9BB0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CDbgMenuPcs::GetDbgFlag()
{
    return *(int*)((char*)this + 0x4);
}

/*
 * --INFO--
 * PAL Address: 0x800B9B44
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" float atan2__3stdFff(float y, float x)
{
    return (float)atan2((double)y, (double)x);
}

/*
 * --INFO--
 * PAL Address: 0x800B9B68
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" float cosf__3stdFf(float x)
{
    return (float)cos((double)x);
}

/*
 * --INFO--
 * PAL Address: 0x800B9B8C
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" float sinf__3stdFf(float x)
{
    return (float)sin((double)x);
}

/*
 * --INFO--
 * PAL Address: 0x800B9C1C
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetFromScript__10CCameraPcsFv(CCameraPcs* camera)
{
    *(int*)((char*)camera + 0x438) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800B9C28
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetPosition(Vec* position)
{
    *(float*)((char*)this + 0xE0) = *(float*)((char*)position + 0x0);
    *(float*)((char*)this + 0xE4) = *(float*)((char*)position + 0x4);
    *(float*)((char*)this + 0xE8) = *(float*)((char*)position + 0x8);
}

/*
 * --INFO--
 * PAL Address: 0x800B9C44
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetRefPosition(Vec* position)
{
    *(float*)((char*)this + 0xD4) = *(float*)((char*)position + 0x0);
    *(float*)((char*)this + 0xD8) = *(float*)((char*)position + 0x4);
    *(float*)((char*)this + 0xDC) = *(float*)((char*)position + 0x8);
}

/*
 * --INFO--
 * PAL Address: 0x800B9C60
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __as__3VecFRC3Vec(Vec* self, const Vec* other)
{
    float x = other->x;
    float y = other->y;
    self->x = x;
    float z = other->z;
    self->y = y;
    self->z = z;
}

/*
 * --INFO--
 * PAL Address: 0x800B9C7C
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int IsAbsolute__10CCameraPcsFv(CCameraPcs* camera)
{
    return *(int*)((char*)camera + 0x444);
}

/*
 * --INFO--
 * PAL Address: 0x800B9C84
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <int count>
class CLine;

struct CLineSegment64
{
    Vec delta;
    Vec normal;
    float length;
    float startLength;
};

template <>
class CLine<64>
{
public:
    int Calc(Vec* nearestPosition, float* nearestDistance, unsigned long* nearestSegment,
             float* nearestSegmentRatio, Vec* targetPosition, float maxDistance);
    int IsInner(Vec* position, float margin);

    Vec m_min;
    Vec m_max;
    unsigned int m_numPoints;
    unsigned int m_unused;
    float m_0x20[4];
    Vec m_points[64];
    CLineSegment64 m_segments[63];
    float m_totalLength;
};

int CLine<64>::Calc(Vec* nearestPosition, float* nearestDistance, unsigned long* nearestSegment,
                    float* nearestSegmentRatio, Vec* targetPosition, float maxDistance)
{
    const bool infiniteRange = (maxDistance == FLOAT_80330cec);
    float bestDistance = infiniteRange ? FLOAT_80330d10 : maxDistance;
    const float maxDistanceSq = maxDistance * maxDistance;
    int found = 0;
    unsigned int bestIndex = 0;
    float bestT = FLOAT_80330cec;
    Vec bestPosition;

    for (unsigned int i = 0; i + 1 < m_numPoints; i++) {
        Vec candidate = m_points[i];
        float distanceSq = PSVECSquareDistance(&candidate, targetPosition);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            float distance = distanceSq;
            if (distanceSq <= FLOAT_80330cec) {
                distance = DAT_8032ec20;
            } else {
                distance = (float)sqrt(distanceSq);
            }

            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosition = candidate;
                bestIndex = i;
                bestT = FLOAT_80330cec;
                found = 1;
            }
        }

        if (i + 1 == m_numPoints - 1) {
            candidate = m_points[i + 1];
            distanceSq = PSVECSquareDistance(&candidate, targetPosition);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                float distance = distanceSq;
                if (distanceSq <= FLOAT_80330cec) {
                    distance = DAT_8032ec20;
                } else {
                    distance = (float)sqrt(distanceSq);
                }

                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPosition = candidate;
                    bestIndex = i;
                    bestT = FLOAT_80330cf0;
                    found = 1;
                }
            }
        }

        CLineSegment64& segment = m_segments[i];
        float dotTarget = PSVECDotProduct(targetPosition, &segment.delta);
        float dotPoint = PSVECDotProduct(&m_points[i], &segment.delta);
        float segmentT = (dotTarget - dotPoint) / (segment.length * segment.length);
        if (((FLOAT_80330cec <= segmentT) && (segmentT <= FLOAT_80330cf0)) || infiniteRange) {
            Vec scaled;
            Vec projected;
            PSVECScale(&segment.delta, &scaled, segmentT);
            PSVECAdd(&m_points[i], &scaled, &projected);
            float distance = PSVECDistance(targetPosition, &projected);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosition = projected;
                bestIndex = i;
                bestT = segmentT;
                found = 1;
            }
        }
    }

    if (found != 0) {
        if (nearestPosition != nullptr) {
            *nearestPosition = bestPosition;
        }
        if (nearestDistance != nullptr) {
            *nearestDistance = bestDistance;
        }
        if (nearestSegment != nullptr) {
            *nearestSegment = bestIndex;
        }
        if (nearestSegmentRatio != nullptr) {
            *nearestSegmentRatio = bestT;
        }
    }

    return found;
}

int CLine<64>::IsInner(Vec* position, float margin)
{
    float* values = (float*)this;
    if (values[6] == 0.0f) {
        return 0;
    }

    if ((values[0] - margin) <= position->x && (values[1] - margin) <= position->y &&
        (values[2] - margin) <= position->z && position->x <= (values[3] + margin) &&
        position->y <= (values[4] + margin) && position->z <= (values[5] + margin)) {
        return 1;
    }

    return 0;
}

extern "C" void CalcBound__9CLine(CLine<64>* line)
{
    line->m_min.x = FLOAT_80330d10;
    line->m_min.y = FLOAT_80330d10;
    line->m_min.z = FLOAT_80330d10;
    line->m_max.x = FLOAT_80330d30;
    line->m_max.y = FLOAT_80330d30;
    line->m_max.z = FLOAT_80330d30;
    line->m_totalLength = FLOAT_80330cec;

    for (unsigned int i = 0; i < line->m_numPoints; i++) {
        const Vec& point = line->m_points[i];

        if (point.x < line->m_min.x) {
            line->m_min.x = point.x;
        }
        if (point.y < line->m_min.y) {
            line->m_min.y = point.y;
        }
        if (point.z < line->m_min.z) {
            line->m_min.z = point.z;
        }

        if (line->m_max.x < point.x) {
            line->m_max.x = point.x;
        }
        if (line->m_max.y < point.y) {
            line->m_max.y = point.y;
        }
        if (line->m_max.z < point.z) {
            line->m_max.z = point.z;
        }

        if (i != 0) {
            CLineSegment64& segment = line->m_segments[i - 1];
            PSVECSubtract(&line->m_points[i], &line->m_points[i - 1], &segment.delta);
            segment.length = PSVECMag(&segment.delta);
            segment.startLength = line->m_totalLength;
            line->m_totalLength += segment.length;
            if (segment.length != FLOAT_80330cec) {
                PSVECNormalize(&segment.delta, &segment.normal);
            }
        }
    }
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
