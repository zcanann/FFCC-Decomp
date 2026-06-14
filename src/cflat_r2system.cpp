#include "ffcc/ptrarray.h"
#include "ffcc/cflat_r2system.h"
#include "ffcc/astar.h"
#include "ffcc/line_constants.h"
#include "ffcc/linkage.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/itemobj.h"
#include "ffcc/joybus.h"
#include "ffcc/line.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/memorycard.h"
#include "ffcc/mes.h"
#include "ffcc/mesmenu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_gba.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_map.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/partyobj.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/util.h"
#include "ffcc/vector.h"
#include "ffcc/wind.h"
#include "ffcc/wm_menu.h"
#include <dolphin/os.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" char* strcat(char*, const char*);

extern "C" void CrossCheckEllipseCapsule__5CMathFP3VecPfP3VecP3VecfP3Vecff(
    float scaleA, float scaleB, float scaleC, float radius, float scale, CMath* math, float* outResult,
    Vec* p0, Vec* p1, Vec* p2, Vec* p3);

namespace std {
float sinf(float x);
float cosf(float x);
float atan2(float y, float x);
float fmodf(float x, float y);
}

static inline CUSBStreamDataState* UsbStream(CPartPcs* self)
{
    return &self->m_usbStreamState;
}

extern const float kCFlatPadStickZero;
extern const float kCFlatAlphaMax;
extern const float kCFlatPi;
extern const float kCFlatDegrees180;
extern const float kCFlatOneF;
extern const float FLOAT_80330B38;
extern const float kCFlatHalfF;
extern const float FLOAT_80330B40;
extern const float FLOAT_80330B44;
extern const float FLOAT_80330B48;
extern const float FLOAT_80330B4C;
extern const float FLOAT_80330B5C;
extern const float FLOAT_80330B88;
extern const float FLOAT_80330B8C;
extern const float FLOAT_80330B90;
extern const float FLOAT_80330BC0;
extern const float kCFlatHalfPi;
extern const float kCFlatPi;
extern const float kCFlatThreeHalfPi;


static inline int RemapPadSlot(CPad* pad, int padIndex)
{
    int activePad = pad->m_debugPadPort;
    return static_cast<int>(padIndex & ~(static_cast<int>(~((activePad - padIndex) | (padIndex - activePad))) >> 31));
}

static inline void StoreSetU32(CFlatRuntime::CStack* stack, int setMode, unsigned int* value)
{
    stack[-1].m_word = *value;

    if (setMode == 0) {
        *value = stack->m_word;
    } else if (setMode == 1) {
        *value += stack->m_word;
    } else if (setMode == -1) {
        *value -= stack->m_word;
    }
}

static inline void StoreSetS16(CFlatRuntime::CStack* stack, int setMode, short* value)
{
    stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(*value));

    if (setMode == 0) {
        *value = static_cast<short>(stack->m_word);
    } else if (setMode == 1) {
        *value = static_cast<short>(*value + static_cast<short>(stack->m_word));
    } else if (setMode == -1) {
        *value = static_cast<short>(*value - static_cast<short>(stack->m_word));
    }
}

static inline void StoreSetU16(CFlatRuntime::CStack* stack, int setMode, unsigned short* value)
{
    stack[-1].m_word = static_cast<unsigned int>(*value);

    if (setMode == 0) {
        *value = static_cast<unsigned short>(stack->m_word);
    } else if (setMode == 1) {
        *value = static_cast<unsigned short>(*value + static_cast<unsigned short>(stack->m_word));
    } else if (setMode == -1) {
        *value = static_cast<unsigned short>(*value - static_cast<unsigned short>(stack->m_word));
    }
}

static inline void StoreSetU8(CFlatRuntime::CStack* stack, int setMode, unsigned char* value)
{
    stack[-1].m_word = static_cast<unsigned int>(*value);

    if (setMode == 0) {
        *value = static_cast<unsigned char>(stack->m_word);
    } else if (setMode == 1) {
        *value = static_cast<unsigned char>(*value + static_cast<unsigned char>(stack->m_word));
    } else if (setMode == -1) {
        *value = static_cast<unsigned char>(*value - static_cast<unsigned char>(stack->m_word));
    }
}

static inline int ClampIndex(int index, int maxIndex)
{
    if (index < 0) {
        return 0;
    }
    if (index > maxIndex) {
        return maxIndex;
    }
    return index;
}


static inline void LerpVec(Vec& out, const Vec& a, const Vec& b, float t)
{
    out.x = a.x + (b.x - a.x) * t;
    out.y = a.y + (b.y - a.y) * t;
    out.z = a.z + (b.z - a.z) * t;
}

static inline unsigned int* GetGameWorkLinkTableWords(CGame::CGameWork& gameWork)
{
    return reinterpret_cast<unsigned int*>(&gameWork.m_linkTable[0][0][0][0]);
}

static inline const unsigned int* GetGameWorkLinkTableWords(const CGame::CGameWork& gameWork)
{
    return reinterpret_cast<const unsigned int*>(&gameWork.m_linkTable[0][0][0][0]);
}

static inline unsigned int* GetGameWorkScriptSysVals(CGame::CGameWork& gameWork)
{
    return reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0);
}

static inline const unsigned int* GetGameWorkScriptSysVals(const CGame::CGameWork& gameWork)
{
    return reinterpret_cast<const unsigned int*>(&gameWork.m_scriptSysVal0);
}

static inline unsigned int& FlatLastResult(CFlatRuntime2* self)
{
    return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(self) + 0x96C);
}

static inline u32& RuntimeDebugFlags(CFlatRuntime2* self)
{
    return self->m_debugFlags;
}

static inline const unsigned short* GetGameCFlatSystemRows()
{
    return reinterpret_cast<const unsigned short*>(Game.unkCFlatData0[2]);
}

static inline unsigned int ReadGameCFlatSystemValue(int systemValue)
{
    if (systemValue >= -0xFFF) {
        return 0;
    }

    int valueIndex = -0x1000 - systemValue;
    int valueGroup = valueIndex / 0x600;
    int rowIndex = 0x5FF - (valueIndex - valueGroup * 0x600);
    const unsigned short* rows = GetGameCFlatSystemRows();
    if (rows == 0 || static_cast<unsigned int>(valueGroup) > 0x23) {
        return 0;
    }

    return rows[rowIndex * 0x24 + valueGroup];
}

static inline unsigned int GetGameWorkEventFlagBitIndex(int systemValue)
{
    return static_cast<unsigned int>(systemValue + 0x9F3);
}

static inline int GetGameWorkEventFlagByteIndex(unsigned int bitIndex)
{
    return (static_cast<int>(bitIndex) >> 3) +
           static_cast<int>((static_cast<int>(bitIndex) < 0) && ((bitIndex & 7) != 0)) + 8;
}

static inline unsigned int GetGameWorkEventFlagMask(unsigned int bitIndex)
{
    int sign = static_cast<int>(bitIndex) >> 31;
    return 1U << ((sign * 8 | static_cast<int>(bitIndex * 0x20000000U + (sign >> 29))) - sign);
}

static inline unsigned int ReadGameWorkEventFlag(const CGame::CGameWork& gameWork, int systemValue)
{
    unsigned int bitIndex = GetGameWorkEventFlagBitIndex(systemValue);
    const unsigned char* eventFlags = reinterpret_cast<const unsigned char*>(gameWork.m_eventFlags);
    unsigned int mask = GetGameWorkEventFlagMask(bitIndex);
    return ((eventFlags[GetGameWorkEventFlagByteIndex(bitIndex)] & mask) != 0);
}

static inline CFlatRuntime::CObject* ResolveRuntimeObjectById(CFlatRuntime2* runtime, int objectId)
{
    CFlatRuntime::CObject* const root =
        reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(runtime) + 0x1204);
    CFlatRuntime::CObject* object = root->m_next;

    while (object != root) {
        if (static_cast<int>(object->m_id) == objectId) {
            return object;
        }
        object = object->m_next;
    }

    return 0;
}

static inline void WriteGameWorkEventFlag(CGame::CGameWork& gameWork, int systemValue, unsigned int value)
{
    unsigned int bitIndex = GetGameWorkEventFlagBitIndex(systemValue);
    unsigned char* eventFlags = reinterpret_cast<unsigned char*>(gameWork.m_eventFlags);
    unsigned char& flagByte = eventFlags[GetGameWorkEventFlagByteIndex(bitIndex)];
    unsigned int mask = GetGameWorkEventFlagMask(bitIndex);

    if (value == 0) {
        flagByte &= static_cast<unsigned char>(~mask);
    } else {
        flagByte |= static_cast<unsigned char>(mask);
    }
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
    m_nextScriptFlags = 1;
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
    m_fullScreenShadowCamLen = len;
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
    return m_fonts[0];
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
    m_seMaxVolume = volume;
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
void CMapPcs::CalcHitPosition(Vec* hitPosition)
{
    MapMng.m_hitMapObj->CalcHitPosition(hitPosition);
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
int CMapPcs::CheckHitCylinderNear(Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
    float max = -10000000000.0f;
    float min = 10000000000.0f;
    CMapCylinder cylinder(min, max);

    cylinder.m_bottom = *cylinderBottom;
    cylinder.m_axis = *direction;
    cylinder.m_radius = radius;

    return MapMng.CheckHitCylinderNear(&cylinder, direction, hitMask);
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
unsigned char* CGraphic::GetTmpFrameBuffer()
{
    return static_cast<unsigned char*>(m_scratchTextureBuffer);
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
        return m_miniGameParams[0];
    case 0x2001:
        return m_miniGameParams[1];
    case 0x2002:
        return m_miniGameParams[2];
    case 0x2003:
        return m_miniGameParams[3];
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
__declspec(section ".rodata") static const char sMiniGameParamDebugFmt[] =
    "SetMiniGameParam no 0x%04x data[%d]\n";

void CMiniGamePcs::SetMiniGameParam(int id, int value)
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(sMiniGameParamDebugFmt), id, value);
    }

    switch (id) {
    case 0x1101:
        m_managerIndex = static_cast<char>(value);
        break;
    case 0x1102:
        m_managerState = 1;
        break;
    case 0x1202:
        m_playerMask |= 1 << value;
        break;
    case 0x1203:
        m_playerMask &= ~(1 << value);
        break;
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
void CCameraPcs::SetShadowAuto(int enable)
{
    m_shadowAuto = enable;
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
void CCharaPcs::SetTexShadowRadius(float texShadowRadius)
{
    m_texShadowRadius = texShadowRadius;
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
void CCharaPcs::SetTexShadowColor(_GXColor color)
{
    const unsigned char* colorBytes = reinterpret_cast<const unsigned char*>(&color);
    unsigned char c1;
    unsigned char c2;

    c1 = colorBytes[0];
    c2 = colorBytes[1];
    m_texShadowColor.r = c1;
    c1 = colorBytes[2];
    m_texShadowColor.g = c2;
    c2 = colorBytes[3];
    m_texShadowColor.b = c1;
    m_texShadowColor.a = c2;
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
CColor::operator _GXColor*()
{
    return &color;
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
void CCharaPcs::SetTexShadowPos(Vec* vec)
{
    m_texShadowPos = *vec;
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
void CCaravanWork::SetEvtWord(int evtWordIndex, short evtWord)
{
    m_evtWordArr[evtWordIndex] = evtWord;
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
int CCaravanWork::GetEvtWord(int evtWordIndex)
{
    return m_evtWordArr[evtWordIndex];
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
void CCaravanWork::SetEvtFlag(int evtFlagIndex, int value)
{
    if (value != 0) {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        reinterpret_cast<unsigned char*>(m_evtWorkArr)[byteIndex] |= bit;
        return;
    }

    {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        reinterpret_cast<unsigned char*>(m_evtWorkArr)[byteIndex] &= ~bit;
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
int CCaravanWork::GetEvtFlag(int evtFlagIndex)
{
    unsigned char* evtFlags = reinterpret_cast<unsigned char*>(m_evtWorkArr);
    int byteIndex = evtFlagIndex / 8;
    unsigned char value = evtFlags[byteIndex];
    int mask = 1 << (evtFlagIndex % 8);
    unsigned int flag = value & mask;

    return (-flag | flag) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800B931C
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::SetTempValue(int index, int value)
{
    m_tempVar[index] = value;
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
unsigned short CPad::GetGbaButtonDown(long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        int slot = RemapPadSlot(this, padIndex);
        result = GetPadInputs()[slot].buttonDown[1];
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
float CPad::GetRightStickY(long padIndex)
{
    bool isInvalidPad = false;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return kCFlatPadStickZero;
    }

    int slot = RemapPadSlot(this, padIndex);
    return GetPadInputs()[slot].substickYF;
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
float CPad::GetRightStickX(long padIndex)
{
    bool isInvalidPad = false;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return kCFlatPadStickZero;
    }

    int slot = RemapPadSlot(this, padIndex);
    return GetPadInputs()[slot].substickXF;
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
float CPad::GetLeftStickY(long padIndex)
{
    bool isInvalidPad = false;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return kCFlatPadStickZero;
    }

    int slot = RemapPadSlot(this, padIndex);
    return GetPadInputs()[slot].stickYF;
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
float CPad::GetLeftStickX(long padIndex)
{
    bool isInvalidPad = false;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return kCFlatPadStickZero;
    }

    int slot = RemapPadSlot(this, padIndex);
    return GetPadInputs()[slot].stickXF;
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
unsigned short CPad::GetButtonRepeat(long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        int slot = RemapPadSlot(this, padIndex);
        result = GetPadInputs()[slot].repeatButton;
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
unsigned short CPad::GetButton(long padIndex)
{
    bool isInvalidPad = false;
    unsigned int result;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (m_debugPadPort == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        result = 0;
    } else {
        int slot = RemapPadSlot(this, padIndex);
        result = GetPadInputs()[slot].button[0];
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
void CCharaPcs::SetMapShadeColor(int shadeIndex, CColor color)
{
    const unsigned char* src = &color.color.r;
    unsigned char r = *src++;
    unsigned char g = *src++;
    m_viewerChoiceColor[shadeIndex].color.r = r;
    unsigned char b = *src++;
    m_viewerChoiceColor[shadeIndex].color.g = g;
    unsigned char a = *src;
    m_viewerChoiceColor[shadeIndex].color.b = b;
    m_viewerChoiceColor[shadeIndex].color.a = a;
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
void CCharaPcs::SetNoFreeMergeMask(int mask)
{
    m_noFreeMergeMask = mask;
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
void CMemory::ResetDefaultGroup()
{
    m_defaultGroup = 0;
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
void CMemory::SetDefaultGroup(int group)
{
    m_defaultGroup = group;
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
void CCharaPcs::SetCharaAllocStage(int stage)
{
    m_charaAllocStage = stage;
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
void CGraphicPcs::SetUseDOF(int enabled)
{
    m_dofFlag = enabled;
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
void CFile::CHandle::Close()
{
    File.Close(this);
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

/*
 * --INFO--
 * PAL Address: 0x800B9478
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::ReqScreenCapture()
{
    m_copySaveFlag = 1;
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
int CMesMenu::IsUse()
{
    unsigned char result = 0;
    if (m_active != 0 && m_state <= 1 && m_mes.GetWait() != 4) {
        result = 1;
    }

    return result;
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
    return ((int*)((char*)game + 0xD4))[index];
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
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMesMenu* CMenuPcs::GetMesMenu(int index)
{
    return reinterpret_cast<CMesMenu**>(reinterpret_cast<char*>(this) + 0x10C)[index];
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
void CCameraPcs::SetWorldMapMatrix(float (*matrix)[4])
{
    PSMTXCopy(matrix, (MtxPtr)((char*)this + 0x34));
    PSMTXInverse(matrix, (MtxPtr)((char*)this + 0x64));
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
void CCameraPcs::GetWorldMapMatrix(float (*matrix)[4])
{
    PSMTXCopy((MtxPtr)((char*)this + 0x34), matrix);
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
void CMapPcs::IsHitDrawMode(char drawMode)
{
    s_bitMask = drawMode;
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
    m_fullScreenShadow.m_rotX = rotX;
    m_fullScreenShadow.m_rotY = rotY;
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
    m_fullScreenShadowPosition.x = position->x;
    m_fullScreenShadowPosition.y = position->y;
    m_fullScreenShadowPosition.z = position->z;
    m_fullScreenShadow.m_scale = len;
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
    m_fullScreenShadowEnabled = enable;
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
void CCameraPcs::GetViewMatrix(float (*matrix)[4])
{
    PSMTXCopy((MtxPtr)((char*)this + 4), matrix);
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

    PSVECScale(a, &scaledA, kCFlatOneF - t);
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
void CCharaPcs::SetDiffuse(int lightIndex, unsigned long lightSet, _GXColor* color, Vec* direction)
{
    m_viewerDiffuseColor[lightIndex][lightSet].r = color->r;
    m_viewerDiffuseColor[lightIndex][lightSet].g = color->g;
    m_viewerDiffuseColor[lightIndex][lightSet].b = color->b;
    m_viewerDiffuseColor[lightIndex][lightSet].a = color->a;

    if (lightIndex != 0) {
        return;
    }

    m_viewerDiffusePos[lightSet].x = direction->x;
    m_viewerDiffusePos[lightSet].y = direction->y;
    m_viewerDiffusePos[lightSet].z = direction->z;
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
void CCharaPcs::SetAmbient(int index, _GXColor* color)
{
    m_viewerAmbientColor[index].r = color->r;
    m_viewerAmbientColor[index].g = color->g;
    m_viewerAmbientColor[index].b = color->b;
    m_viewerAmbientColor[index].a = color->a;
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
    const float* src = &other.x;
    float x = *src++;
    float y = *src++;
    this->x = x;
    float z = *src;
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
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
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
float std::fmodf(float x, float y)
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
void CCameraPcs::SetFov(float fov)
{
    m_fov = fov;
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
    m_zRotate = zRotate;
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
    m_nextScript = *nextScript;
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
    return m_dbgFlags;
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
float std::atan2(float y, float x)
{
    return (float)::atan2((double)y, (double)x);
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
float std::cosf(float x)
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
float std::sinf(float x)
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
void CCameraPcs::SetFromScript()
{
    m_fromScript = 1;
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
    m_positionX = position->x;
    m_positionY = position->y;
    m_positionZ = position->z;
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
    m_targetX = position->x;
    m_targetY = position->y;
    m_targetZ = position->z;
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
    const float* src = &other->x;
    float x = *src++;
    float y = *src++;
    self->x = x;
    float z = *src;
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
int CCameraPcs::IsAbsolute()
{
    return m_isAbsolute;
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
#pragma push
#pragma opt_common_subs off
int CLine<64>::Calc(Vec* nearestPosition, float* nearestDistance, unsigned long* nearestSegment,
                    float* nearestSegmentRatio, Vec* targetPosition, float maxDistance)
{
    float bestPosX;
    float bestPosY;
    float bestPosZ;
    float bestT = kCFlatPadStickZero;
    const int infiniteRange = (kCFlatPadStickZero == maxDistance);
    float bestDistance = infiniteRange ? FLOAT_80330B5C : maxDistance;
    const float maxDistanceSq = maxDistance * maxDistance;
    unsigned int bestIndex;
    int found = 0;
    Vec candidatePosition;

    for (unsigned int i = 0; i < pointCount - 1; i++) {
        float distanceSq = PSVECSquareDistance(&points[i], targetPosition);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            candidatePosition = points[i];
            float distance = sqrtf(distanceSq);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosX = candidatePosition.x;
                bestPosY = candidatePosition.y;
                bestPosZ = candidatePosition.z;
                bestIndex = i;
                bestT = kCFlatPadStickZero;
                found = 1;
            }
        }

        if (i == pointCount - 2) {
            distanceSq = PSVECSquareDistance(&points[i + 1], targetPosition);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                candidatePosition = points[i + 1];
                float distance = sqrtf(distanceSq);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPosX = candidatePosition.x;
                    bestPosY = candidatePosition.y;
                    bestPosZ = candidatePosition.z;
                    bestIndex = i;
                    bestT = kCFlatOneF;
                    found = 1;
                }
            }
        }

        const float dotTarget = PSVECDotProduct(targetPosition, &segments[i].delta);
        const float dotPoint = PSVECDotProduct(&points[i], &segments[i].delta);
        const float segmentT = (-dotPoint + dotTarget) / (segments[i].length * segments[i].length);
        if (((segmentT >= kCFlatPadStickZero) && (segmentT <= kCFlatOneF)) || infiniteRange) {
            Vec scaled;
            PSVECScale(&segments[i].delta, &scaled, segmentT);
            PSVECAdd(&points[i], &scaled, &candidatePosition);
            const float distance = PSVECDistance(targetPosition, &candidatePosition);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosX = candidatePosition.x;
                bestPosY = candidatePosition.y;
                bestPosZ = candidatePosition.z;
                bestIndex = i;
                bestT = segmentT;
                found = 1;
            }
        }
    }

    if (found != 0) {
        if (nearestPosition != nullptr) {
            nearestPosition->x = bestPosX;
            nearestPosition->y = bestPosY;
            nearestPosition->z = bestPosZ;
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
#pragma pop

int CLine<64>::IsInner(Vec* position, float margin)
{
    if (pointCount != 0) {
        if ((min.x - margin) <= position->x && (min.y - margin) <= position->y &&
            (min.z - margin) <= position->z && (max.x + margin) >= position->x &&
            (max.y + margin) >= position->y && (max.z + margin) >= position->z) {
            return 1;
        }
    }

    return 0;
}

void CLine<64>::CalcBound()
{
    min.x = FLOAT_80330B5C;
    min.y = FLOAT_80330B5C;
    min.z = FLOAT_80330B5C;
    max.x = FLOAT_80330BC0;
    max.y = FLOAT_80330BC0;
    max.z = FLOAT_80330BC0;
    totalLength = kCFlatPadStickZero;

    for (u32 i = 0; i < pointCount; i++) {
        if (points[i].x < min.x) {
            min.x = points[i].x;
        }
        if (points[i].y < min.y) {
            min.y = points[i].y;
        }
        if (points[i].z < min.z) {
            min.z = points[i].z;
        }

        if (points[i].x > max.x) {
            max.x = points[i].x;
        }
        if (points[i].y > max.y) {
            max.y = points[i].y;
        }
        if (points[i].z > max.z) {
            max.z = points[i].z;
        }

        if (i != 0) {
            PSVECSubtract(&points[i], &points[i - 1], &segments[i - 1].delta);
            segments[i - 1].length = PSVECMag(&segments[i - 1].delta);
            segments[i - 1].startLength = totalLength;
            totalLength += segments[i - 1].length;
            if (kCFlatPadStickZero != segments[i - 1].length) {
                PSVECNormalize(&segments[i - 1].delta, &segments[i - 1].normal);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800B3310
 * PAL Size: 23664b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma pool_strings on
int CFlatRuntime2::onSystemFunc(CFlatRuntime::CObject* object, int, int systemFunc, int& outResult)
{
    char* gbaPath = const_cast<char*>("dvd/gba/");

    switch (systemFunc) {
    case -3:
        this->push(object, getNumFreeObject(5));
        outResult = 0;
        break;
    case -4:
        if (CameraPcs.IsAbsolute() != 0) {
            Vec refPosition;
            refPosition.x = reinterpret_cast<float*>(object->m_localBase)[0];
            refPosition.y = reinterpret_cast<float*>(object->m_localBase)[1];
            refPosition.z = reinterpret_cast<float*>(object->m_localBase)[2];
            if (m_cameraScriptTargetMode != 0) {
                CharaPcs.m_overlapTargetPos = refPosition;
            } else {
                CameraPcs.SetRefPosition(&refPosition);
            }

            Vec position;
            position.x = reinterpret_cast<float*>(object->m_localBase)[3];
            position.y = reinterpret_cast<float*>(object->m_localBase)[4];
            position.z = reinterpret_cast<float*>(object->m_localBase)[5];
            if (m_cameraScriptTargetMode != 0) {
                CharaPcs.m_overlapEyePos = position;
            } else {
                CameraPcs.SetPosition(&position);
            }
            CameraPcs.SetFromScript();
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -5: {
        short buttons;
        if (((1 << *object->m_localBase) & m_padInputDisableMask) != 0) {
            buttons = 0;
        } else {
            buttons = Pad.GetButton(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= ~0xC00;
        }
        this->push(object, static_cast<short>(buttons));
        outResult = 0;
        break;
    }
    case -6: {
        float value = std::sinf(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -7: {
        float value = std::cosf(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -8: {
        const unsigned int x = object->m_localBase[0];
        const unsigned int y = object->m_localBase[1];
        char* format = this->m_strBlob + this->m_strOffsets[object->m_localBase[2]];

        if (object->m_argCount == 3) {
            Graphic.Printf(x, y, format);
        } else {
            char spec[256];
            char rendered[256];
            char line[264];
            char* specBody = spec + 1;
            line[0] = '\0';

            for (int i = 0; i < object->m_argCount - 3; i++) {
                while (true) {
                    char* dst = spec;
                    char c;
                    int specLen = 0;
                    while (((c = *format) != '\0') && ((specLen == 0) || ((specLen != 0) && (c != '%')))) {
                        *dst = c;
                        format++;
                        specLen++;
                        dst++;
                    }
                    spec[specLen] = '\0';

                    if (spec[0] == '%') {
                        break;
                    }
                    strcat(line, spec);
                }

                const int argIndex = i + 3;
                unsigned int* localArgs = object->m_localBase;
                unsigned int* slot = &localArgs[argIndex];
                char* scan = specBody;
                if (spec[0] == '%') {
                    int fmtIndex = 1;
                    int width = 0;
                    int started = spec[1] == '0';
                    for (char* digits = specBody; (*digits >= '0') && (*digits <= '9'); digits++) {
                        fmtIndex++;
                        width = (*digits - '0') + width * 10;
                    }

                    if (spec[fmtIndex] != 'b') {
                        goto formatScan;
                    }

                    {
                        char* out = rendered;
                        int value = static_cast<int>(*slot);
                        int outLen = 0;
                        for (int bit = 0; bit < width; bit++) {
                            const int cur = (value >> ((width - bit) - 1)) & 1;
                            if (started == 0 && cur != 0) {
                                started = 1;
                            }
                            if (started != 0) {
                                *out++ = static_cast<char>(cur + '0');
                                outLen++;
                            }
                        }
                        rendered[outLen] = '\0';
                        strcat(rendered, spec + fmtIndex + 1);
                    }
                } else {
formatScan:
                    while (*scan != '\0') {
                        switch (*scan) {
                        case 'd':
                        case 'x':
                            sprintf(rendered, spec, *slot);
                            goto renderedDone;
                        case 'f':
                            sprintf(rendered, spec,
                                    static_cast<double>(*reinterpret_cast<float*>(slot)));
                            goto renderedDone;
                        case 's':
                            sprintf(rendered, spec, this->m_strBlob + this->m_strOffsets[*slot]);
                            goto renderedDone;
                        default:
                            scan++;
                            break;
                        }
                    }
                }

renderedDone:
                strcat(line, rendered);
            }

            Graphic.Printf(x, y, line);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -9:
        Game.ChangeMap(*object->m_localBase, object->m_localBase[1], 0, 1);
        this->push(object, 0);
        outResult = 0;
        break;
    case -10: {
        float value = std::atan2(
            *reinterpret_cast<float*>(object->m_localBase),
            *reinterpret_cast<float*>(object->m_localBase + 1));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -0x0B: {
        short buttons;
        if (((1 << *object->m_localBase) & m_padInputDisableMask) != 0) {
            buttons = 0;
        } else {
            buttons = Pad.GetButtonDown(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= ~0xC00;
        }
        this->push(object, static_cast<short>(buttons));
        outResult = 0;
        break;
    }
    case -0x0C: {
        short buttons;
        if (((1 << *object->m_localBase) & m_padInputDisableMask) != 0) {
            buttons = 0;
        } else {
            buttons = Pad.GetButtonRepeat(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= ~0xC00;
        }
        this->push(object, static_cast<short>(buttons));
        outResult = 0;
        break;
    }
    case -0x0D: {
        float* values = reinterpret_cast<float*>(object->m_localBase);
        Vec a;
        Vec b;
        a.x = values[0];
        a.y = values[1];
        a.z = values[2];
        b.x = values[3];
        b.y = values[4];
        b.z = values[5];
        float value = PSVECDistance(&a, &b);
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -0x0E: {
        int result = Math.Rand(*object->m_localBase);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x0F: {
        float value = Math.RandF(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -0x10: {
        int result = Math.RandPM(*object->m_localBase);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x11: {
        float value = Math.RandFPM(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -0x12:
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            *reinterpret_cast<float*>(object->m_localBase[1]) = kCFlatPadStickZero;
            *reinterpret_cast<float*>(object->m_localBase[2]) = kCFlatPadStickZero;
        } else {
            const float stickX = Pad.GetLeftStickX(*object->m_localBase);
            const float stickY = Pad.GetLeftStickY(*object->m_localBase);
            *reinterpret_cast<float*>(object->m_localBase[1]) = stickX;
            *reinterpret_cast<float*>(object->m_localBase[2]) = stickY;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xFD: {
        const float stickX = Pad.GetLeftStickX(*object->m_localBase);
        const float stickY = Pad.GetLeftStickY(*object->m_localBase);
        *reinterpret_cast<float*>(object->m_localBase[1]) = stickX;
        *reinterpret_cast<float*>(object->m_localBase[2]) = stickY;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x13:
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            *reinterpret_cast<float*>(object->m_localBase[1]) = kCFlatPadStickZero;
            *reinterpret_cast<float*>(object->m_localBase[2]) = kCFlatPadStickZero;
        } else {
            const float stickX = Pad.GetRightStickX(*object->m_localBase);
            const float stickY = Pad.GetRightStickY(*object->m_localBase);
            *reinterpret_cast<float*>(object->m_localBase[1]) = stickX;
            *reinterpret_cast<float*>(object->m_localBase[2]) = stickY;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x14: {
        const int value = *object->m_localBase;
        this->push(object, value < 0 ? -value : value);
        outResult = 0;
        break;
    }
    case -0x15: {
        float value = (float)__fabs((double)*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        break;
    }
    case -0x16: {
        CGame::CNextScript nextScript;
        strcpy(nextScript.m_name, this->m_strBlob + this->m_strOffsets[*object->m_localBase]);
        Game.SetNextScript(&nextScript);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x17:
        CameraPcs.SetZRotate(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x18:
        CameraPcs.SetFov(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x19: {
        if (m_pathPointCount < 0x40U) {
            if (*reinterpret_cast<int*>(object->m_localBase) != 0) {
                m_pathPointCount = 0;
                m_pathTotalDistance = kCFlatPadStickZero;
            }

            m_pathPoints[m_pathPointCount].m_position.x = reinterpret_cast<float*>(object->m_localBase)[1];
            m_pathPoints[m_pathPointCount].m_position.y = reinterpret_cast<float*>(object->m_localBase)[2];
            m_pathPoints[m_pathPointCount].m_position.z = reinterpret_cast<float*>(object->m_localBase)[3];

            if (m_pathPointCount != 0) {
                m_pathTotalDistance += PSVECDistance(
                    &m_pathPoints[m_pathPointCount].m_position,
                    &m_pathPoints[m_pathPointCount - 1].m_position);
            }

            m_pathPoints[m_pathPointCount].m_distance = m_pathTotalDistance;
            m_pathPointCount = m_pathPointCount + 1;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x1A: {
        const int mode = *object->m_localBase;
        const int modeBits = mode & 3;

        float t = static_cast<float>(static_cast<int>(object->m_localBase[1])) /
                  static_cast<float>(static_cast<int>(object->m_localBase[2]));

        if ((mode & 4) != 0) {
            const int lowBit = mode & 1;
            const int highBit = (mode >> 1) & 1;
            const int segmentCount = m_pathPointCount + 1 - lowBit - highBit;
            const float scaled = t * static_cast<float>(segmentCount);
            const int baseIndex = lowBit + static_cast<int>(scaled);
            const float segmentT = std::fmodf(scaled, kCFlatOneF);

            CVector delta = CVector(m_pathPoints[1].m_position) - CVector(m_pathPoints[0].m_position);
            CVector startPhantom1 = CVector(m_pathPoints[0].m_position) - delta;
            CVector startPhantom2 = startPhantom1 - delta;
            delta = CVector(m_pathPoints[m_pathPointCount - 1].m_position) -
                    CVector(m_pathPoints[m_pathPointCount - 2].m_position);
            CVector endPhantom1 = CVector(m_pathPoints[m_pathPointCount - 1].m_position) + delta;
            CVector endPhantom2 = endPhantom1 + delta;

            Vec* p0;
            Vec* p1;
            Vec* p2;
            Vec* p3;

            if (lowBit != 0) {
                if (baseIndex == 0) {
                    p0 = startPhantom2;
                } else if (baseIndex == 1) {
                    p0 = startPhantom1;
                } else {
                    p0 = &m_pathPoints[(baseIndex - 2) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex - 2) ? m_pathPointCount - 1 : (baseIndex - 2))].m_position;
                }
                if (baseIndex == 0) {
                    p1 = startPhantom1;
                } else {
                    p1 = &m_pathPoints[(baseIndex - 1) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex - 1) ? m_pathPointCount - 1 : (baseIndex - 1))].m_position;
                }
            } else {
                p0 = &m_pathPoints[(baseIndex - 2) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex - 2) ? m_pathPointCount - 1 : (baseIndex - 2))].m_position;
                p1 = &m_pathPoints[(baseIndex - 1) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex - 1) ? m_pathPointCount - 1 : (baseIndex - 1))].m_position;
            }

            if (highBit != 0) {
                if (baseIndex == m_pathPointCount) {
                    p2 = endPhantom1;
                } else {
                    p2 = &m_pathPoints[(baseIndex) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex) ? m_pathPointCount - 1 : (baseIndex))].m_position;
                }
                if (baseIndex == m_pathPointCount - 1) {
                    p3 = endPhantom1;
                } else if (baseIndex == m_pathPointCount) {
                    p3 = endPhantom2;
                } else {
                    p3 = &m_pathPoints[(baseIndex + 1) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex + 1) ? m_pathPointCount - 1 : (baseIndex + 1))].m_position;
                }
            } else {
                p2 = &m_pathPoints[(baseIndex) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex) ? m_pathPointCount - 1 : (baseIndex))].m_position;
                p3 = &m_pathPoints[(baseIndex + 1) < 0 ? 0 : (m_pathPointCount - 1 < (baseIndex + 1) ? m_pathPointCount - 1 : (baseIndex + 1))].m_position;
            }

            Vec result;
            Vec c2;
            Vec c1;
            Vec c0;

            PSVECScale(p0, &result, FLOAT_80330B38);
            VECMultAdd(&result, p1, &result, kCFlatHalfF);
            VECMultAdd(&result, p2, &result, FLOAT_80330B40);
            VECMultAdd(&result, p3, &result, FLOAT_80330B44);

            PSVECScale(p0, &c2, kCFlatHalfF);
            VECMultAdd(&c2, p1, &c2, FLOAT_80330B48);
            VECMultAdd(&c2, p2, &c2, kCFlatHalfF);

            PSVECScale(p0, &c1, FLOAT_80330B40);
            VECMultAdd(&c1, p2, &c1, kCFlatHalfF);

            PSVECScale(p0, &c0, FLOAT_80330B44);
            VECMultAdd(&c0, p1, &c0, FLOAT_80330B4C);
            VECMultAdd(&c0, p2, &c0, FLOAT_80330B44);

            PSVECScale(&result, &result, segmentT);
            PSVECAdd(&result, &c2, &result);
            PSVECScale(&result, &result, segmentT);
            PSVECAdd(&result, &c1, &result);
            PSVECScale(&result, &result, segmentT);
            PSVECAdd(&result, &c0, &result);

            *reinterpret_cast<float*>(object->m_localBase[3]) = result.x;
            *reinterpret_cast<float*>(object->m_localBase[4]) = result.y;
            *reinterpret_cast<float*>(object->m_localBase[5]) = result.z;
        } else {
            if (modeBits == 3) {
                float s = std::sinf(kCFlatPi * t + kCFlatHalfPi);
                t = kCFlatOneF - kCFlatHalfF * (kCFlatOneF + s);
            } else if (modeBits == 1) {
                t = kCFlatOneF + std::sinf(kCFlatHalfPi * t + kCFlatThreeHalfPi);
            } else if (modeBits == 2) {
                t = std::sinf(kCFlatHalfPi * t);
            }

            const float pathDistance = m_pathTotalDistance * t;
            const int maxIndex = m_pathPointCount - 1;
            CFlatPathPoint* point = m_pathPoints;
            for (int i = 0; i < maxIndex; i++, point++) {
                if (point->m_distance <= pathDistance && pathDistance <= point[1].m_distance) {
                    const int i0 = (i - 1) < 0 ? 0 : (i - 1);
                    CFlatPathPoint* p0 = &m_pathPoints[i0];
                    CFlatPathPoint* p1 = &m_pathPoints[i];
                    const int i2 = (i + 1) < maxIndex ? (i + 1) : maxIndex;
                    CFlatPathPoint* p2 = &m_pathPoints[i2];
                    const int i3 = (i + 2) < maxIndex ? (i + 2) : maxIndex;
                    CFlatPathPoint* p3 = &m_pathPoints[i3];
                    const float scaleA = p1->m_distance - p0->m_distance;
                    const float scaleB = p2->m_distance - p1->m_distance;
                    const float scaleC = p3->m_distance - p2->m_distance;
                    float segmentT = kCFlatPadStickZero;
                    if (kCFlatPadStickZero != scaleB) {
                        segmentT = (pathDistance - p1->m_distance) / scaleB;
                    }

                    Vec result;
                    CrossCheckEllipseCapsule__5CMathFP3VecPfP3VecP3VecfP3Vecff(
                        scaleA, scaleB, scaleC, segmentT, kCFlatOneF, &Math, reinterpret_cast<float*>(&result),
                        &p0->m_position, &p1->m_position, &p2->m_position, &p3->m_position);
                    *reinterpret_cast<float*>(object->m_localBase[3]) = result.x;
                    *reinterpret_cast<float*>(object->m_localBase[4]) = result.y;
                    *reinterpret_cast<float*>(object->m_localBase[5]) = result.z;
                    break;
                }
            }
        }

        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x1C:
        m_debugFlags = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x1D:
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x1E: {
        unsigned int slot = *object->m_localBase;
        if (slot < 0x10) {
            int mask = object->m_localBase[1];
            m_debugLines[slot].pointCount = 0;
            m_debugLines[slot].m_mask = mask;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x1F: {
        unsigned int slot = *object->m_localBase;
        if (slot < 0x10) {
            if (m_debugLines[slot].pointCount < 0x40) {
                unsigned long index = m_debugLines[slot].pointCount;
                m_debugLines[slot].pointCount = index + 1;
                m_debugLines[slot].points[index].x = reinterpret_cast<float*>(object->m_localBase)[1];
                m_debugLines[slot].points[index].y = reinterpret_cast<float*>(object->m_localBase)[2];
                m_debugLines[slot].points[index].z = reinterpret_cast<float*>(object->m_localBase)[3];
                m_debugLines[slot].CalcBound();
            }
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x20: {
        CColor color(
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF);
        CharaPcs.SetAmbient(*object->m_localBase, color);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x21: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float yaw = localFloats[5];
        const float pitch = localFloats[6];
        const float sinYaw = std::sinf(yaw);
        const float cosYaw = std::cosf(yaw);
        const float x = sinYaw * std::cosf(pitch);
        const float y = std::sinf(pitch);
        const float z = cosYaw * std::cosf(pitch);
        unsigned int* diffuseBase = object->m_localBase;
        CVector direction(-x, -y, -z);
        Vec* directionPtr = direction;
        CColor color(
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            0xFF);

        CharaPcs.SetDiffuse(*diffuseBase, diffuseBase[1], color, directionPtr);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x22: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const unsigned int mask = *object->m_localBase;
        Vec target;
        target.x = localFloats[1];
        target.y = localFloats[2];
        target.z = localFloats[3];
        const float margin = localFloats[4];
        int found = 0;
        unsigned int bestLine = 0;
        float bestDistance = kLineBoundsInitMin;
        float bestLineDistance = 0.0f;

        CLine<64>* lines = m_debugLines;
        for (unsigned int i = 0; i < 0x10; i++) {
            CLine<64>& line = lines[i];
            if (line.pointCount == 0 || (line.m_mask & mask) == 0 || line.IsInner(&target, margin) == 0) {
                continue;
            }

            unsigned long segment;
            float segmentRatio;
            float nearestDistance;
            if (line.Calc((Vec*)0, &nearestDistance, &segment, &segmentRatio, &target, margin) != 0 &&
                nearestDistance < bestDistance) {
                found = 1;
                bestLine = i;
                bestDistance = nearestDistance;
                bestLineDistance = line.segments[segment].length * segmentRatio + line.segments[segment].startLength;
            }
        }

        if (found != 0) {
            *reinterpret_cast<unsigned int*>(object->m_localBase[5]) = bestLine;
            *reinterpret_cast<float*>(object->m_localBase[6]) = bestLineDistance;
            *reinterpret_cast<float*>(object->m_localBase[7]) = m_debugLines[bestLine].totalLength;
        }

        this->push(object, found);
        outResult = 0;
        break;
    }
    case -0x23: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float distance = localFloats[1];
        CLine<64>* line = &m_debugLines[*object->m_localBase];
        Vec position;

        if (distance < kCFlatPadStickZero) {
            position = line->points[0];
        } else if (line->totalLength <= distance) {
            position = line->points[line->pointCount - 1];
        } else {
            for (unsigned int i = 0; i < line->pointCount - 1; i++) {
                if (line->segments[i].startLength <= distance &&
                    distance < line->segments[i].startLength + line->segments[i].length) {
                    const float t = (distance - line->segments[i].startLength) / line->segments[i].length;
                    VECLerp(&line->points[i], &line->points[i + 1], &position, t);
                    break;
                }
            }
        }

        *reinterpret_cast<float*>(object->m_localBase[2]) = position.x;
        *reinterpret_cast<float*>(object->m_localBase[3]) = position.y;
        *reinterpret_cast<float*>(object->m_localBase[4]) = position.z;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x24: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float distance = localFloats[1];
        CLine<64>* line = &m_debugLines[*object->m_localBase];
        Vec direction;

        if (distance < kCFlatPadStickZero) {
            direction = line->segments[0].normal;
        } else if (line->totalLength <= distance) {
            direction = line->segments[line->pointCount - 1].normal;
        } else {
            for (unsigned int i = 0; i < line->pointCount - 1; i++) {
                if (line->segments[i].startLength <= distance &&
                    distance < line->segments[i].startLength + line->segments[i].length) {
                    direction = line->segments[i].normal;
                    break;
                }
            }
        }

        if (static_cast<int>(object->m_localBase[2]) == 0) {
            direction.x = -direction.x;
            direction.y = -direction.y;
            direction.z = -direction.z;
        }

        *reinterpret_cast<float*>(object->m_localBase[3]) = direction.x;
        *reinterpret_cast<float*>(object->m_localBase[4]) = direction.y;
        *reinterpret_cast<float*>(object->m_localBase[5]) = direction.z;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x25: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CLine<64>* line = &m_debugLines[*object->m_localBase];
        Vec target;
        target.x = localFloats[1];
        target.y = localFloats[2];
        target.z = localFloats[3];
        unsigned long segment;
        float segmentRatio;
        float distance;

        if (line->Calc((Vec*)0, (float*)0, &segment, &segmentRatio, &target, kCFlatPadStickZero) != 0) {
            distance = line->segments[segment].length * segmentRatio + line->segments[segment].startLength;
        }

        *reinterpret_cast<float*>(object->m_localBase[4]) = distance;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x26:
        this->push(object, *reinterpret_cast<int*>(&m_debugLines[*object->m_localBase].totalLength));
        outResult = 0;
        break;
    case -0x27: {
        if ((this->m_debugFlags & CFlatRuntimeDebugFlag_ClassCollision) != 0) {
            Mtx drawMtx;
            Mtx viewMtx;
            CameraPcs.GetViewMatrix(viewMtx);

            _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
            GXSetZCompLoc(GX_FALSE);
            _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXSetCullMode(GX_CULL_FRONT);
            GXSetNumTevStages(1);
            _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetNumChans(1);
            GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

            const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
            const float radius = localFloats[3];
            PSMTXScale(drawMtx, radius, radius, radius);
            const float* trans = reinterpret_cast<float*>(object->m_localBase);
            const float y = trans[1];
            const float z = trans[2];
            drawMtx[0][3] = trans[0];
            drawMtx[1][3] = y;
            drawMtx[2][3] = z;
            PSMTXConcat(viewMtx, drawMtx, drawMtx);
            GXLoadPosMtxImm(drawMtx, GX_PNMTX0);

            GXColor color;
            color.a = 0xFF;
            color.r = static_cast<u8>(object->m_localBase[4]);
            color.g = static_cast<u8>(object->m_localBase[5]);
            color.b = static_cast<u8>(object->m_localBase[6]);
            GXSetChanMatColor(GX_COLOR0A0, color);
            Graphic.DrawSphere();
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x28:
        m_debugLines[*object->m_localBase].m_mask = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x29: {
        _GXColor color;
        color.r = static_cast<u8>(object->m_localBase[0]);
        color.g = static_cast<u8>(object->m_localBase[1]);
        color.b = static_cast<u8>(object->m_localBase[2]);
        color.a = 0xFF;
        Graphic.SetCopyClear(color, 0xFFFFFF);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x2A: {
        _GXColor color;
        color.a = 0xFF;
        color.r = static_cast<u8>(object->m_localBase[0]);
        color.g = static_cast<u8>(object->m_localBase[1]);
        color.b = static_cast<u8>(object->m_localBase[2]);
        Graphic.SetFogColor(color);
        Graphic.SetFogParam(reinterpret_cast<float*>(object->m_localBase)[3],
                            reinterpret_cast<float*>(object->m_localBase)[4]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x2B:
        CameraPcs.SetFullScreenShadowEnable(static_cast<unsigned char>(*object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x2C: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position;
        position.x = localFloats[0];
        position.y = localFloats[1];
        position.z = localFloats[2];
        CameraPcs.SetFullScreenShadowPos(&position, localFloats[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x2D: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CameraPcs.SetFullScreenShadowRot(localFloats[0], localFloats[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x2E:
        MapPcs.IsHitDrawMode(static_cast<char>(*object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x2F:
        MapMng.SetIdGrpMask(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x32: {
        CGraphicPcs::ScreenFadeSlot& fade = GraphicPcs.m_screenFade[3];
        fade.m_invert = *object->m_localBase;
        fade.m_timer = object->m_localBase[1];
        fade.m_duration = fade.m_timer;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x33: {
        CGraphicPcs::ScreenFadeSlot& fade = GraphicPcs.m_screenFade[2];
        fade.m_invert = *object->m_localBase;
        fade.m_mode = 0;
        fade.m_colorA.r = static_cast<u8>(object->m_localBase[1]);
        fade.m_colorA.g = static_cast<u8>(object->m_localBase[2]);
        fade.m_colorA.b = static_cast<u8>(object->m_localBase[3]);
        fade.m_colorA.a = 0xFF;
        fade.m_timer = object->m_localBase[4];
        fade.m_duration = fade.m_timer;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x34: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float angle1 = localFloats[1];
        const float angle2 = localFloats[2];
        Vec axis;
        axis.x = std::cosf(angle1);
        axis.y = 0.0f;
        axis.z = std::sinf(angle1);
        Mtx matrix;
        Mtx rotation;

        CameraPcs.GetWorldMapMatrix(matrix);
        if (static_cast<int>(*object->m_localBase) != 0) {
            PSMTXIdentity(matrix);
        }

        PSMTXRotAxisRad(rotation, &axis, angle2);
        PSMTXConcat(rotation, matrix, matrix);

        axis.x = 0.0f;
        axis.y = 1.0f;
        axis.z = 0.0f;
        PSMTXRotAxisRad(rotation, &axis, localFloats[3]);
        PSMTXConcat(rotation, matrix, matrix);
        CameraPcs.SetWorldMapMatrix(matrix);

        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x1B: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[2],
            localFloats[3],
            localFloats[4]);
        this->PutParticle((*object->m_localBase << 8) | object->m_localBase[1], position, localFloats[5]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x3D:
        this->PutParticleWork();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x37:
        this->ResetParticleWork((*object->m_localBase << 8) | object->m_localBase[2], object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x38: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        this->SetParticleWorkPos(
            CVector(localFloats[0], localFloats[1], localFloats[2]), localFloats[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x39: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector target(
            localFloats[0],
            localFloats[1],
            localFloats[2]);
        this->SetParticleWorkTarget(target);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x3A:
        this->SetParticleWorkVector(
            reinterpret_cast<float*>(object->m_localBase)[0],
            reinterpret_cast<float*>(object->m_localBase)[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x3B:
        this->SetParticleWorkScale(reinterpret_cast<float*>(object->m_localBase)[0]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x3C:
        this->SetParticleWorkCol(
            *object->m_localBase, object->m_localBase[1],
            static_cast<float>(static_cast<int>(object->m_localBase[2])));
        this->push(object, 0);
        outResult = 0;
        break;
    case -99: {
        CFlatRuntime::CObject* targetObject = static_cast<CFlatRuntime::CObject*>(this->intToClass(*object->m_localBase));
        this->SetParticleWorkTrace(targetObject);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x49:
        this->SetParticleWorkSpeed(reinterpret_cast<float*>(object->m_localBase)[0]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x4E: {
        CFlatRuntime::CObject* targetObject = static_cast<CFlatRuntime::CObject*>(this->intToClass(*object->m_localBase));
        this->SetParticleWorkBind(targetObject);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x5B: {
        CFlatRuntime::CObject* targetObject = static_cast<CFlatRuntime::CObject*>(this->intToClass(object->m_localBase[1]));
        this->SetParticleWorkParam(*object->m_localBase, targetObject);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x80:
        this->SetParticleWorkSe(*object->m_localBase, object->m_localBase[1], object->m_localBase[2]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x35:
        this->push(object, this->GetFreeParticleSlot());
        outResult = 0;
        break;
    case -0x36:
        this->EndParticleSlot(*object->m_localBase, 0);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x3E:
        PartMng.pppEndPart(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x4B:
        PartMng.pppFieldShowFpNo(static_cast<short>(*object->m_localBase), static_cast<unsigned char>(object->m_localBase[1]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x5C: {
        CFlatRuntime::CObject* targetObject = static_cast<CFlatRuntime::CObject*>(this->intToClass(object->m_localBase[1]));
        this->IgnoreParticle(*object->m_localBase, targetObject);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x43:
        PartMng.pppShowIdx(static_cast<short>(*object->m_localBase), static_cast<unsigned char>(object->m_localBase[1]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x44:
        PartMng.pppShowSlot(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x7D:
        PartMng.pppDeletePart(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x7E:
        PartMng.pppDeleteSlot(*object->m_localBase, 0);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x91:
        this->push(object, PartMng.pppGetNumFreePppMngSt());
        outResult = 0;
        break;
    case -0x94: {
        float* bounds = reinterpret_cast<float*>(object->m_localBase);
        PartMng.m_pppEnvSt.m_boxMinX = bounds[0];
        PartMng.m_pppEnvSt.m_boxMaxX = bounds[1];
        PartMng.m_pppEnvSt.m_boxMinY = bounds[2];
        PartMng.m_pppEnvSt.m_boxMaxY = bounds[3];
        PartMng.m_pppEnvSt.m_boxMinZ = bounds[4];
        PartMng.m_pppEnvSt.m_boxMaxZ = bounds[5];
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xB4:
        PartMng.pppSetDeltaSlot(
            *object->m_localBase, static_cast<long>(0.25f * *reinterpret_cast<float*>(object->m_localBase + 1)));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xB5:
        PartMng.pppSetDeltaIdx(
            static_cast<short>(*object->m_localBase),
            static_cast<long>(0.25f * *reinterpret_cast<float*>(object->m_localBase + 1)));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xBB: {
        PPPCREATEPARAM createParam;
        PartMng.pppCreate(0, *object->m_localBase, &createParam, 1);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xBC:
        PartMng.pppFieldEndFpNo(static_cast<short>(*object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xBD:
        PartMng.pppFieldEndFpNo(static_cast<short>(*object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x3F: {
        Mtx matrix;
        Quaternion rotation;
        CameraPcs.GetWorldMapMatrix(matrix);
        C_QUATMtx(&rotation, matrix);
        *reinterpret_cast<float*>(object->m_localBase[0]) = rotation.x;
        *reinterpret_cast<float*>(object->m_localBase[1]) = rotation.y;
        *reinterpret_cast<float*>(object->m_localBase[2]) = rotation.z;
        *reinterpret_cast<float*>(object->m_localBase[3]) = rotation.w;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x40: {
        float* values = reinterpret_cast<float*>(object->m_localBase);
        Quaternion rotation;
        Mtx matrix;
        rotation.x = values[0];
        rotation.y = values[1];
        rotation.z = values[2];
        rotation.w = values[3];
        PSMTXQuat(matrix, &rotation);
        CameraPcs.SetWorldMapMatrix(matrix);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x41: {
        const unsigned int* localBase = object->m_localBase;
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        int mode = *localBase & 3;
        float alpha = static_cast<float>(static_cast<int>(localBase[1])) /
                      static_cast<float>(static_cast<int>(localBase[2]));
        Quaternion start;
        Quaternion end;
        Quaternion rotation;
        start.x = localFloats[3];
        start.y = localFloats[4];
        start.z = localFloats[5];
        start.w = localFloats[6];
        end.x = localFloats[7];
        end.y = localFloats[8];
        end.z = localFloats[9];
        end.w = localFloats[10];

        if (mode == 3) {
            float s = std::sinf(kCFlatPi * alpha + kCFlatHalfPi);
            alpha = kCFlatOneF - kCFlatHalfF * (kCFlatOneF + s);
        } else if (mode == 1) {
            alpha = kCFlatOneF + std::sinf(kCFlatHalfPi * alpha + kCFlatThreeHalfPi);
        } else if (mode == 2) {
            alpha = std::sinf(kCFlatHalfPi * alpha);
        }

        C_QUATSlerp(&start, &end, &rotation, alpha);
        *reinterpret_cast<float*>(object->m_localBase[11]) = rotation.x;
        *reinterpret_cast<float*>(object->m_localBase[12]) = rotation.y;
        *reinterpret_cast<float*>(object->m_localBase[13]) = rotation.z;
        *reinterpret_cast<float*>(object->m_localBase[14]) = rotation.w;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x42: {
        const int padType = Joybus.GetPadType(*object->m_localBase);
        this->push(object, (0x40U - padType | padType - 0x40U) >> 31);
        outResult = 0;
        break;
    }
    case -0x45: {
        unsigned int* localBase = object->m_localBase;
        int a0 = localBase[0];
        int a1 = localBase[1];
        int a2 = localBase[2];
        int a3 = localBase[3];
        int a4 = localBase[4];
        int a5 = localBase[5];
        int a6 = localBase[6];
        int a7 = localBase[7];
        if (MenuPcs.GetMesMenu(a0) != 0) {
            char* message;
            if ((a3 & 0x80) != 0) {
                message = GetNumSysMes__5CGameFv(&Game, a7);
            } else {
                message = reinterpret_cast<char*>(GetSysMes__5CGameFi(&m_flatData, a7));
            }
            if ((a3 & 0x80) != 0) {
                message = GetNumSysMes__5CGameFv(&Game, a7);
            } else {
                message = reinterpret_cast<char*>(GetSysMes__5CGameFi(&m_flatData, a7));
            }
            MenuPcs.GetMesMenu(a0)->Open(message, a1, a2, a3, a4, a5, a6);
        } else {
            if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
                System.Printf(const_cast<char*>("\203\201\203b\203Z\201[\203W\203\201\203j\203\205\201[%d\202\315\202\240\202\350\202\334\202\271\202\361\201B\n"), a0);
            }
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x46: {
        const int a0 = *object->m_localBase;
        if (MenuPcs.GetMesMenu(a0) != 0) {
            MenuPcs.GetMesMenu(a0)->CloseRequest(1);
        } else {
            if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
                System.Printf(const_cast<char*>("\203\201\203b\203Z\201[\203W\203\201\203j\203\205\201[%d\202\315\202\240\202\350\202\334\202\271\202\361\201B\n"), a0);
            }
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x47: {
        const int a0 = *object->m_localBase;
        const int a1 = object->m_localBase[1];
        const int a2 = object->m_localBase[2];
        if (MenuPcs.GetMesMenu(a0) != 0) {
            GetMes__9CFlatDataFi(MenuPcs.GetMesMenu(a0), a1, a2);
        } else {
            if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
                System.Printf(const_cast<char*>("\203\201\203b\203Z\201[\203W\203\201\203j\203\205\201[%d\202\315\202\240\202\350\202\334\202\271\202\361\201B\n"), a0);
            }
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x48: {
        int a0 = *object->m_localBase;
        int a1 = object->m_localBase[1];
        if (MenuPcs.GetMesMenu(a0) != 0) {
            this->push(object, GetErrorLevel__7CSystemFv(MenuPcs.GetMesMenu(a0), a1));
            outResult = 0;
            break;
        } else {
            if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
                System.Printf(const_cast<char*>("\203\201\203b\203Z\201[\203W\203\201\203j\203\205\201[%d\202\315\202\240\202\350\202\334\202\271\202\361\201B\n"), a0);
            }
            this->push(object, 0);
        }
        outResult = 0;
        break;
    }
    case -0x4C: {
        _GXColor color;
        color.a = 0x80;
        color.r = static_cast<u8>(object->m_localBase[2]);
        color.g = static_cast<u8>(object->m_localBase[3]);
        color.b = static_cast<u8>(object->m_localBase[4]);
        MapMng.SetIdGrpColor(*object->m_localBase, object->m_localBase[1], color);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x4D: {
        const int a0 = *object->m_localBase;
        if (MenuPcs.GetMesMenu(a0) == 0) {
            if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
                System.Printf(const_cast<char*>("\203\201\203b\203Z\201[\203W\203\201\203j\203\205\201[%d\202\315\202\240\202\350\202\334\202\271\202\361\201B\n"), a0);
            }
            this->push(object, 0);
            outResult = 0;
        } else {
            if (MenuPcs.GetMesMenu(a0)->IsUse() == 0) {
                this->push(object, 0);
                outResult = 0;
            }
        }
        break;
    }
    case -0x4F:
        MapMng.SetMeshCameraSemiTransRange(
            static_cast<unsigned short>(*object->m_localBase),
            *reinterpret_cast<float*>(object->m_localBase + 1),
            *reinterpret_cast<float*>(object->m_localBase + 2),
            *reinterpret_cast<float*>(object->m_localBase + 3),
            *reinterpret_cast<float*>(object->m_localBase + 4),
            (kCFlatDegrees180 * (2.0f * *reinterpret_cast<float*>(object->m_localBase + 5))) /
                kCFlatPi);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x50: {
        CGraphicPcs::ScreenFadeSlot* screenFade = &GraphicPcs.m_screenFade[0];
        screenFade->m_mode = 2;
        screenFade->m_colorA.r = 0xFF;
        screenFade->m_colorA.g = 0xFF;
        screenFade->m_colorA.b = 0xFF;
        screenFade->m_colorA.a = 0xFF;
        screenFade->m_invert = 0;
        screenFade->m_timer = object->m_localBase[0];
        screenFade->m_duration = screenFade->m_timer;
        screenFade->m_amplitude = reinterpret_cast<float*>(object->m_localBase)[1];
        screenFade->m_phase = reinterpret_cast<float*>(object->m_localBase)[2];
        screenFade->m_stretch = reinterpret_cast<float*>(object->m_localBase)[3];
        GraphicPcs.ReqScreenCapture();
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x51: {
        char path[0x100];
        sprintf(path, "dvd/%scft/%s.cfd", Game.GetLangString(), this->m_strBlob + this->m_strOffsets[*object->m_localBase]);
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            fileHandle->Read();
            fileHandle->SyncCompleted();
            m_flatData.Create(File.GetBuffer());
            fileHandle->Close();
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x52: {
        GraphicPcs.SetUseDOF(*object->m_localBase != 0);
        GraphicPcs.SetDOFParameter(
            static_cast<signed char>(*object->m_localBase - 1),
            static_cast<signed char>(object->m_localBase[1]),
            *reinterpret_cast<float*>(object->m_localBase + 2),
            *reinterpret_cast<float*>(object->m_localBase + 3),
            *reinterpret_cast<float*>(object->m_localBase + 4),
            *reinterpret_cast<float*>(object->m_localBase + 5),
            *reinterpret_cast<float*>(object->m_localBase + 6),
            object->m_localBase[7]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x53:
        CharaPcs.SetCharaAllocStage(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x54: {
        int index = m_debugDataIndex;
        m_debugDataIndex = index + 1;
        this->push(object, m_debugDataBuffer[index]);
        outResult = 0;
        break;
    }
    case -0x55: {
        int index = m_debugDataIndex;
        m_debugDataIndex = index + 1;
        this->push(object, m_debugDataBuffer[index]);
        outResult = 0;
        break;
    }
    case -0x56: {
        int index = m_debugDataIndex;
        const unsigned int value = *object->m_localBase;
        m_debugDataIndex = index + 1;
        m_debugDataBuffer[index] = value;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x57: {
        int index = m_debugDataIndex;
        const float value = *reinterpret_cast<float*>(object->m_localBase);
        m_debugDataIndex = index + 1;
        m_debugDataBuffer[index] = *reinterpret_cast<const int*>(&value);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x58: {
        char filename[0x80];
        sprintf(filename, "cflat_d%d.bin", *object->m_localBase);
        MemoryCardMan.DebugReadWrite(1, filename, reinterpret_cast<u8*>(m_debugDataBuffer), sizeof(m_debugDataBuffer));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x59: {
        char filename[0x80];
        sprintf(filename, "cflat_d%d.bin", *object->m_localBase);
        MemoryCardMan.DebugReadWrite(0, filename, reinterpret_cast<u8*>(m_debugDataBuffer), sizeof(m_debugDataBuffer));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x5A:
        m_debugDataIndex = 0;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x5D:
        this->push(object, System.IsGdev());
        outResult = 0;
        break;
    case -0x5E:
        if (GetNumMes__9CFlatDataFv(&System) >= 1U) {
            System.Printf(const_cast<char*>("\203f\203o\203b\203O\227p\212\326\220\224setForceAnimInterp\202\315\224p\216~\202\263\202\352\202\334\202\265\202\275\201B\n"));
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x5F: {
        float dstRot = Math.DstRot(
            *reinterpret_cast<float*>(object->m_localBase),
            *reinterpret_cast<float*>(object->m_localBase + 1));
        this->push(object, *reinterpret_cast<int*>(&dstRot));
        outResult = 0;
        break;
    }
    case -0x60: {
        const unsigned int blurA = static_cast<unsigned int>(__cntlzw(object->m_localBase[4]));
        const unsigned int blurB = static_cast<unsigned int>(__cntlzw(object->m_localBase[5]));
        const int alpha = static_cast<int>(kCFlatAlphaMax * *reinterpret_cast<float*>(object->m_localBase + 3)) & 0xFF;
        GraphicPcs.SetBlurParameter(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]),
            static_cast<unsigned char>(object->m_localBase[2]), static_cast<unsigned char>(alpha),
            static_cast<unsigned char>((blurA >> 5) & 0xFF), static_cast<unsigned char>((blurB >> 5) & 0xFF),
            static_cast<short>(object->m_localBase[6]));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x61: {
        const int x = static_cast<int>(object->m_localBase[1]);
        const int group = (~(x - 1 | 1 - x) >> 31) & 3;
        Memory.SetDefaultGroup(group);
        CharaPcs.LoadMergeFile(*object->m_localBase, x, 0);
        Memory.ResetDefaultGroup();
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x62:
        CharaPcs.SetNoFreeMergeMask(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x4A:
        m_eventFlags = static_cast<unsigned int>(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -100:
        this->initAllFinished();
        m_initAllFinishedFlag = 1;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x65: {
        CharaPcs.SetMapShadeColor(
            *object->m_localBase,
            CColor(
                static_cast<u8>(object->m_localBase[1]),
                static_cast<u8>(object->m_localBase[2]),
                static_cast<u8>(object->m_localBase[3]),
                0xFF));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x66:
        this->push(object, 2);
        outResult = 0;
        break;
    case -0x67:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadWaveAsync\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.LoadWaveASync(*object->m_localBase, -1, 0);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x68: {
        const int completed = Sound.IsLoadWaveASyncCompleted();
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347isLoadWaveAsyncCompleted\202\265\202\334\202\265\202\275\201B\223\307\202\335\215\236\202\335\202\315%s\n"),
                completed != 0 ? "\212\256\227\271" : "\226\242\212\256\227\271");
        }
        this->push(object, completed);
        outResult = 0;
        break;
    }
    case -0x69:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadBgm\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.LoadBgm(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x6A:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playBgm\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.PlayBgm(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x6B:
        Sound.LoadSe(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x6C: {
        int result = Sound.PlaySe(*object->m_localBase, 0x40, 0x7F, 0);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x6D: {
        unsigned int c = object->m_localBase[2];
        unsigned int d = object->m_localBase[3];
        unsigned int a = object->m_localBase[0];
        unsigned int b = object->m_localBase[1];
        unsigned char value = static_cast<unsigned char>(object->m_localBase[4]);
        Game.m_gameWork.m_linkTable[c][d][a][b] = value;
        Game.m_gameWork.m_linkTable[a][b][c][d] = value;
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x6E:
        this->push(
            object, Game.m_gameWork.m_linkTable[object->m_localBase[0]][object->m_localBase[1]][object->m_localBase[2]]
                                          [object->m_localBase[3]]);
        outResult = 0;
        break;
    case -0x6F:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&Game.m_gameWork) + 8) = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x70:
        Game.m_gameWork.m_timerA = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x71:
        Game.m_gameWork.m_scriptGlobalTime = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x72:
        Game.m_gameWork.m_bossArtifactStageTable[*object->m_localBase] = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x73:
        Game.m_gameWork.m_unkStageTable[*object->m_localBase] = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x74: {
        short buttonDown = Pad.GetGbaButtonDown(*object->m_localBase);
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttonDown &= ~0xC00;
        }
        this->push(object, buttonDown);
        outResult = 0;
        break;
    }
    case -0x75:
        CMes::SetTempValue(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x76:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1298) = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x77:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadWave\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.LoadWave(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x78:
        Sound.Clear3DLine(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x79: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Sound.Add3DLine(
            *object->m_localBase, CVector(localFloats[1], localFloats[2], localFloats[3]));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x7B: {
        int result = Sound.PlaySe3DLine(*object->m_localBase, object->m_localBase[1],
                         *reinterpret_cast<float*>(object->m_localBase + 2),
                         *reinterpret_cast<float*>(object->m_localBase + 3), 0);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x7A: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        int result = Sound.PlaySe3D(
            *object->m_localBase, CVector(localFloats[1], localFloats[2], localFloats[3]),
            localFloats[4], localFloats[5], 0);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x7C:
        Sound.StopSe3D(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x7F:
        Sound.SetReverb(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x81: {
        Mtx& reflectMtx = m_centerMatrix;
        PSMTXReflect(
            reflectMtx,
            CVector(reinterpret_cast<float*>(object->m_localBase)[0], kCFlatPadStickZero,
                reinterpret_cast<float*>(object->m_localBase)[1]),
            CVector(std::sinf(reinterpret_cast<float*>(object->m_localBase)[2]), kCFlatPadStickZero,
                std::cosf(reinterpret_cast<float*>(object->m_localBase)[2])));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x82:
        this->m_letterEventEnabled = static_cast<unsigned int>(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x83:
        this->push(object, Graphic.GetProgressive());
        outResult = 0;
        break;
    case -0x84:
        Graphic.ChangeProgressive(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x85: {
        int result = Wind.AddAmbient(reinterpret_cast<float*>(object->m_localBase)[0],
                                     reinterpret_cast<float*>(object->m_localBase)[1]);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x86: {
        const float* f = reinterpret_cast<float*>(object->m_localBase);
        int result = Wind.AddDiffuse(CVector(f[0], f[1], f[2]), f[3], f[4], f[5]);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x87: {
        const float* f = reinterpret_cast<float*>(object->m_localBase);
        int result = Wind.AddSphere(CVector(f[0], f[1], f[2]), f[3], f[4], object->m_localBase[5]);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x88:
        Wind.ChangePower(*object->m_localBase, reinterpret_cast<float*>(object->m_localBase)[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x89:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadStream\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.LoadStream(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8A:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playStream\202\265\202\334\202\265\202\275\201B\n"));
        }
        Sound.PlayStreamASync();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8B:
        Sound.StopStream();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA0:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347streamVolume\202\265\202\334\202\265\202\275\201B\n"));
        }
        Sound.SetStreamVolume(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8C:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347freeWave\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.FreeWave(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8D:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347stopBgm\202\265\202\334\202\265\202\275\201B\n"));
        }
        Sound.StopBgm();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8E:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347fadeOutBgm\202\265\202\334\202\265\202\275\201B\n"));
        }
        Sound.FadeOutBgm(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x8F:
        Sound.FadeOutSe3D(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x90:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playNextBgm\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.PlayNextBgm(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x92:
        MapMng.SetMapTexAnim(
            *object->m_localBase, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x95: {
        unsigned int result = 1;
        switch (*object->m_localBase) {
        case 0:
            Sound.Realloc(1);
            break;
        case 1:
            Game.ChangeMap(object->m_localBase[1], object->m_localBase[2], 1, 0);
            break;
        case 2:
            PartMng.pppDestroyAll();
            Game.ChangeMap(object->m_localBase[1], object->m_localBase[2], 1, 1);
            break;
        case 3:
            Sound.Realloc(0);
            break;
        case 4:
            Game.ChangeMap(object->m_localBase[1], object->m_localBase[2], 2, 0);
            break;
        case 5:
            PartMng.pppDestroyAll();
            Game.ChangeMap(object->m_localBase[1], object->m_localBase[2], 2, 1);
            break;
        case 6:
            result = static_cast<unsigned int>(MapPcs.IsLoadMapCompleted()) & PartPcs.IsLoadPartCompleted();
            break;
        }
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0x96:
        m_centerState = *object->m_localBase;
        m_centerDistanceScale = *reinterpret_cast<float*>(&object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x97: {
        unsigned int slot = static_cast<unsigned int>(*object->m_localBase);
        m_mapObjectInfo[slot].m_type = static_cast<char>(object->m_localBase[1]);
        m_mapObjectInfo[slot].m_x = *reinterpret_cast<float*>(object->m_localBase + 2);
        m_mapObjectInfo[slot].m_y = *reinterpret_cast<float*>(object->m_localBase + 3);
        m_mapObjectInfo[slot].m_z = *reinterpret_cast<float*>(object->m_localBase + 4);
        m_mapObjectInfo[slot].m_radius = *reinterpret_cast<float*>(object->m_localBase + 5);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x98:
        m_mapObjectInfo[*object->m_localBase].m_drawFlag = static_cast<char>(object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x99: {
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjAnim(
            mapObjIndex, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xF2:
        MapMng.SetMapAnimID(object->m_localBase[0], object->m_localBase[1],
            object->m_localBase[2], object->m_localBase[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x9A: {
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjMime(mapObjIndex, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0x9B:
        CharaPcs.LoadCam(*object->m_localBase, this->m_strBlob + this->m_strOffsets[object->m_localBase[1]]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x9C: {
        int cameraFrame = object->m_localBase[1];
        CCharaPcs::CCameraFrame*& cameraSlotRef = CharaPcs.m_cameraData[*object->m_localBase];
        if ((cameraSlotRef == 0) || (cameraFrame < 0) ||
            (CharaPcs.m_cameraFrameCount[*object->m_localBase] <= cameraFrame)) {
            this->push(object, 0);
            outResult = 0;
        }

        *reinterpret_cast<float*>(object->m_localBase[2]) = cameraSlotRef[cameraFrame].m_values[0].m_float;
        *reinterpret_cast<float*>(object->m_localBase[3]) = -cameraSlotRef[cameraFrame].m_values[1].m_float;
        *reinterpret_cast<float*>(object->m_localBase[4]) = -cameraSlotRef[cameraFrame].m_values[2].m_float;
        *reinterpret_cast<float*>(object->m_localBase[5]) = cameraSlotRef[cameraFrame].m_values[3].m_float;
        *reinterpret_cast<float*>(object->m_localBase[6]) = -cameraSlotRef[cameraFrame].m_values[4].m_float;
        *reinterpret_cast<float*>(object->m_localBase[7]) = -cameraSlotRef[cameraFrame].m_values[5].m_float;
        *reinterpret_cast<float*>(object->m_localBase[8]) = cameraSlotRef[cameraFrame].m_values[6].m_float;
        *reinterpret_cast<float*>(object->m_localBase[9]) =
            -((kCFlatPi * cameraSlotRef[cameraFrame].m_values[7].m_float) / kCFlatDegrees180);
        this->push(object, 1);
        outResult = 0;
        break;
    }
    case -0x9D: {
        int result = MemoryCardMan.DummyLoad();
        this->push(object, (static_cast<unsigned int>(__cntlzw(result)) >> 5) & 0xFF);
        outResult = 0;
        break;
    }
    case -0x9E: {
        int result = MemoryCardMan.DummySave();
        this->push(object, (static_cast<unsigned int>(__cntlzw(result)) >> 5) & 0xFF);
        outResult = 0;
        break;
    }
    case -0x9F:
        if (static_cast<int>(object->m_localBase[1]) >= 0) {
            Game.m_caravanWorkArr[*object->m_localBase].Init(
                object->m_localBase[1],
                reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + object->m_localBase[1] * 0x1D0),
                object->m_localBase[2]);
        } else {
            Game.m_caravanWorkArr[*object->m_localBase].m_shopState = 0;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA4:
        this->push(
            object, Game.m_caravanWorkArr[*object->m_localBase].GetEvtFlag(object->m_localBase[1]));
        outResult = 0;
        break;
    case -0xA5:
        Game.m_caravanWorkArr[*object->m_localBase].SetEvtFlag(object->m_localBase[1], object->m_localBase[2]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA6:
        this->push(
            object, static_cast<short>(Game.m_caravanWorkArr[*object->m_localBase].GetEvtWord(object->m_localBase[1])));
        outResult = 0;
        break;
    case -0xA7:
        Game.m_caravanWorkArr[*object->m_localBase].SetEvtWord(object->m_localBase[1],
            static_cast<short>(object->m_localBase[2]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA9:
        MenuPcs.SetWorldParam(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA8:
        this->push(object, MenuPcs.GetWorldParam(*object->m_localBase));
        outResult = 0;
        break;
    case -0xAB:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_letterMeta[object->m_localBase[1]]);
        outResult = 0;
        break;
    case -0xAA:
        Game.m_caravanWorkArr[*object->m_localBase].m_letterMeta[object->m_localBase[1]] =
            static_cast<unsigned short>(object->m_localBase[2]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xAD:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8);
        outResult = 0;
        break;
    case -0xAC:
        Game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8 = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xAF:
        this->push(
            object,
            static_cast<int>(
                static_cast<signed char>(Game.m_caravanWorkArr[*object->m_localBase].m_name[object->m_localBase[1]])));
        outResult = 0;
        break;
    case -0xAE:
        strcpy(
            reinterpret_cast<char*>(Game.m_caravanWorkArr[*object->m_localBase].m_name),
            this->m_strBlob + this->m_strOffsets[object->m_localBase[1]]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xB1:
        this->push(object, static_cast<int>(Game.m_gameWork.m_townName[*object->m_localBase]));
        outResult = 0;
        break;
    case -0xB0:
        strcpy(Game.m_gameWork.m_townName, this->m_strBlob + this->m_strOffsets[*object->m_localBase]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xB2: {
        CGraphicPcs::ScreenFadeSlot& fade = GraphicPcs.m_screenFade[1];
        fade.m_invert = 0;
        fade.m_timer = 1;
        fade.m_duration = 1;
        fade.m_mode = *object->m_localBase;
        fade.m_colorA.r = static_cast<u8>(object->m_localBase[1]);
        fade.m_colorA.g = static_cast<u8>(object->m_localBase[2]);
        fade.m_colorA.b = static_cast<u8>(object->m_localBase[3]);
        fade.m_colorA.a = static_cast<u8>(object->m_localBase[4]);
        fade.m_colorB.r = static_cast<u8>(object->m_localBase[5]);
        fade.m_colorB.g = static_cast<u8>(object->m_localBase[6]);
        fade.m_colorB.b = static_cast<u8>(object->m_localBase[7]);
        fade.m_colorB.a = static_cast<u8>(object->m_localBase[8]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xB3: {
        int result = CGItemObj::DeleteOld(*object->m_localBase, object->m_localBase[1], object,
                                          reinterpret_cast<CFlatRuntime::CObject*>(object->m_engineObject));
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0xB7:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac);
        outResult = 0;
        break;
    case -0xB6:
        Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xB8: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Sound.ChangeSe3DPos(
            *object->m_localBase, CVector(localFloats[1], localFloats[2], localFloats[3]));
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xB9:
        CharaPcs.m_overlapEnabled = *object->m_localBase;
        CharaPcs.m_overlapAlpha = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xBA:
        m_cameraScriptTargetMode = *object->m_localBase;
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xBE: {
        CRomLetterWork* romLetterWork[8];
        Game.m_caravanWorkArr[*object->m_localBase].SearchRomLetterWork(romLetterWork, 8);

        for (int i = 0; i < 8; i++) {
            int dstOffs = i * 4;
            for (int j = 0; j < 12; j++) {
                if (romLetterWork[i] != 0) {
                    *reinterpret_cast<int*>(object->m_localBase[1 + j] + dstOffs) =
                        reinterpret_cast<const unsigned short*>(romLetterWork[i])[j];
                } else {
                    *reinterpret_cast<int*>(object->m_localBase[1 + j] + dstOffs) = -1;
                }
            }
            if (romLetterWork[i] != 0) {
                int letterIndex = (reinterpret_cast<int>(romLetterWork[i]) - static_cast<int>(Game.m_romLetterWorkBase)) /
                                  static_cast<int>(sizeof(CRomLetterWork));
                *reinterpret_cast<int*>(object->m_localBase[13] + dstOffs) = letterIndex;
            } else {
                *reinterpret_cast<int*>(object->m_localBase[13] + dstOffs) = -1;
            }
        }

        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xBF:
        if (*reinterpret_cast<int*>(object->m_localBase + 2) != 0) {
            MapMng.ShowMapObjChildID(*object->m_localBase, object->m_localBase[1]);
        } else {
            MapMng.ShowMapObjID(*object->m_localBase, object->m_localBase[1]);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC0: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CharaPcs.SetTexShadowPos(CVector(localFloats[0], localFloats[1], localFloats[2]));
        CharaPcs.SetTexShadowColor(CColor(
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            static_cast<u8>(object->m_localBase[5]),
            static_cast<u8>(object->m_localBase[6])));
        CharaPcs.SetTexShadowRadius(reinterpret_cast<float*>(object->m_localBase)[7]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xC1:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].GetFoodRank(object->m_localBase[1]));
        outResult = 0;
        break;
    case -0xC2:
        Game.m_caravanWorkArr[*object->m_localBase].m_progressValue =
            static_cast<unsigned short>(object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC3:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_progressValue);
        outResult = 0;
        break;
    case -0xC4:
        GXSetDispCopyGamma(static_cast<_GXGamma>(object->m_localBase[0]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC5: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[4],
            localFloats[5],
            localFloats[6]);
        MapMng.SetMapObjWorldMapLightID(
            *object->m_localBase,
            CColor(
                static_cast<u8>(object->m_localBase[1]),
                static_cast<u8>(object->m_localBase[2]),
                static_cast<u8>(object->m_localBase[3]),
                0xFF),
            position);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xC6:
        MenuPcs.m_battleHud.m_visible = *object->m_localBase;
        MenuPcs.m_battleHud.m_fadeCounter = 0x40;
        MenuPcs.m_battleHud.m_width = object->m_localBase[1];
        MenuPcs.m_battleHud.m_gaugeMax = MenuPcs.m_battleHud.m_gaugeTarget =
            MenuPcs.m_battleHud.m_gaugeValue = object->m_localBase[2];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC7:
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        MenuPcs.m_battleHud.m_worldPos[0] = localFloats[0];
        MenuPcs.m_battleHud.m_worldPos[1] = localFloats[1];
        MenuPcs.m_battleHud.m_worldPos[2] = localFloats[2];
        if (static_cast<int>(object->m_localBase[3]) < MenuPcs.m_battleHud.m_gaugeTarget) {
            MenuPcs.m_battleHud.m_gaugeCounter = 0x10;
        }
        MenuPcs.m_battleHud.m_gaugeTarget = object->m_localBase[3];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC8:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347cancelWaveAsync\202\265\202\334\202\265\202\275\201B\n"));
        }
        Sound.CancelLoadWaveASync();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xC9: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjTransRate(
            mapObjIndex, localFloats[1], localFloats[2], localFloats[3]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xCA: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        int result = Sound.PlaySe3D(
            *object->m_localBase, CVector(localFloats[1], localFloats[2], localFloats[3]),
            localFloats[4], localFloats[5], object->m_localBase[6]);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0xCB:
        CameraPcs.SetShadowAuto(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xCC:
        MenuPcs.LoadExtraFont(*object->m_localBase, this->m_strBlob + this->m_strOffsets[object->m_localBase[1]]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xCD:
        reinterpret_cast<CFlatRuntime&>(CFlat).ClearParmanent();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xCE:
        Game.m_gameWork.ClearEvtWork();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xCF:
        Game.m_caravanWorkArr[*object->m_localBase].ClearEvtWork();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD0: {
        enum
        {
            kMaxCcClass2DResults = 64,
        };

        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector center(
            localFloats[2],
            localFloats[3],
            localFloats[4]);
        CGObject* foundObjects[kMaxCcClass2DResults];
        int maxCount = object->m_localBase[7];

        int foundCount = this->CcClass2D(
            *object->m_localBase, object->m_localBase[1], center, localFloats[5],
            localFloats[6], maxCount, foundObjects);
        for (int i = 0; i < foundCount; i++) {
            reinterpret_cast<int*>(object->m_localBase[8])[i] =
                reinterpret_cast<CFlatRuntime::CObject*>(foundObjects[i])->m_particleId;
        }

        this->push(object, foundCount);
        outResult = 0;
        break;
    }
    case -0xD1:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347crossPlayBgm\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.CrossPlayBgm(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD2: {
        if (*reinterpret_cast<int*>(object->m_localBase) != 0) {
            memcpy(m_savedNextScript, Game.m_currentScriptName, sizeof(m_savedNextScript));
        } else {
            CGame::CNextScript nextScript;
            strcpy(nextScript.m_name, m_savedNextScript);
            Game.SetNextScript(&nextScript);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xD3:
        if (*reinterpret_cast<int*>(object->m_localBase + 1) != 0) {
            MapMng.SetMeshCameraSemiTransAlpha(static_cast<unsigned short>(*object->m_localBase), 0x80, 0x3C);
        } else {
            MapMng.SetMeshCameraSemiTransAlpha(static_cast<unsigned short>(*object->m_localBase), 0, 0x3C);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD4:
        if (*reinterpret_cast<int*>(object->m_localBase) != 0) {
            MapMng.SetDrawRangeOctTree(*reinterpret_cast<float*>(object->m_localBase + 1));
        } else {
            MapMng.SetDrawRangeMapObj(*reinterpret_cast<float*>(object->m_localBase + 1));
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD5:
        this->loadLayer(*object->m_localBase, this->m_strBlob + this->m_strOffsets[object->m_localBase[1]]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD6: {
        const unsigned int* localBase = object->m_localBase;
        const float* localFloats = reinterpret_cast<const float*>(localBase);
        unsigned char value = static_cast<u8>(kCFlatAlphaMax * localFloats[10]);
        unsigned char alpha = static_cast<u8>(kCFlatAlphaMax * localFloats[11]);
        char* layerName = this->m_strBlob + this->m_strOffsets[localBase[1]];
        _GXColor color;
        color.r = value;
        color.g = value;
        color.b = value;
        color.a = alpha;
        this->drawLayer(
            *object->m_localBase, layerName, localBase[2],
            localBase[3], localBase[4], localBase[5], localBase[6], localBase[7],
            localFloats[8], localFloats[9], &color,
            localBase[12]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xD7:
        this->loadLayerASync(*object->m_localBase, this->m_strBlob + this->m_strOffsets[object->m_localBase[1]]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xD8:
        this->push(object, this->isLoadLayerASyncCompleted(*object->m_localBase));
        outResult = 0;
        break;
    case -0xD9:
        this->push(object, 1);
        outResult = 0;
        break;
    case -0xDA:
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xDB:
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xDC: {
        CRomLetterWork* letters = reinterpret_cast<CRomLetterWork*>(Game.m_romLetterWorkBase);
        this->push(object, reinterpret_cast<const unsigned short*>(&letters[*object->m_localBase])[object->m_localBase[1]]);
        outResult = 0;
        break;
    }
    case -0xDD:
        Sound.FadeOutSe(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xDE:
        this->SysControl(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xDF:
        switch (*reinterpret_cast<int*>(object->m_localBase)) {
        case 0:
            if (*reinterpret_cast<int*>(object->m_localBase + 1) != 0) {
                PartPcs.StartLocationTitle();
            } else {
                PartPcs.EndLocationTitle();
            }
            break;
        case 1:
            if (*reinterpret_cast<int*>(object->m_localBase + 1) != 0) {
                PartPcs.StartMiruraEvent();
            } else {
                PartPcs.EndMiruraEvent();
            }
            break;
        }
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xE0:
        MapMng.SetMapObjPrioID(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xE2:
        MiniGamePcs.SetMiniGameParam(*object->m_localBase, object->m_localBase[1]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xE1:
        this->push(object, MiniGamePcs.GetMiniGameParam(*object->m_localBase));
        outResult = 0;
        break;
    case -0xE3: {
        CCaravanWork* work = &Game.m_caravanWorkArr[object->m_localBase[0]];
        const int item = object->m_localBase[2];
        unsigned int flags = 0;
        if ((object->m_localBase[1] & 2) != 0) {
            const int itemIndex = work->FindItem(item);
            flags = ((static_cast<unsigned int>(itemIndex) >> 31) - 1) & 2;
        }
        this->push(object, flags);
        outResult = 0;
        break;
    }
    case -0xE4: {
        CCaravanWork* work = &Game.m_caravanWorkArr[object->m_localBase[0]];
        if (static_cast<int>(object->m_localBase[1]) == 1) {
            work->DeleteItem(object->m_localBase[2], 1);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xE5:
        this->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_gil);
        outResult = 0;
        break;
    case -0xE6:
        this->push(object, static_cast<unsigned int>(Game.m_caravanWorkArr[*object->m_localBase].m_inventoryItemCount));
        outResult = 0;
        break;
    case -0xE7:
        CharaPcs.m_texShadowSize = *object->m_localBase;
        CharaPcs.m_texShadowDistance =
            static_cast<int>(*reinterpret_cast<float*>(object->m_localBase + 1));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xE8: {
        CColor color(
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF);
        MenuPcs.SetExtraFontTlut(*object->m_localBase, color);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xE9: {
        _GXTexObj backTexObj;
        if (*reinterpret_cast<int*>(object->m_localBase) != 0) {
            Graphic.GetBackBufferRect2(
                Graphic.GetTmpFrameBuffer(), 0, 0, 0, 0x280, 0x1C0, 0, GX_NEAR, GX_TF_RGB565, 0);
        } else {
            GXInitTexObj(
                &backTexObj, Graphic.GetTmpFrameBuffer(), 0x280, 0x1C0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP,
                GX_FALSE);
            GXInitTexObjLOD(&backTexObj, GX_NEAR, GX_NEAR, kCFlatPadStickZero, kCFlatPadStickZero,
                kCFlatPadStickZero, GX_FALSE, GX_FALSE, GX_ANISO_1);
            gUtil.RenderTextureQuad(
                kCFlatPadStickZero, kCFlatPadStickZero, FLOAT_80330B88, FLOAT_80330B8C, &backTexObj, 0, 0,
                CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(object->m_localBase[1])),
                GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        }
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xEA:
        CharaPcs.SetSpecularAlpha(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xEB:
        CGPartyObj::SetBonusCondition(
            *object->m_localBase, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3],
            object->m_localBase[4]);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA3:
        GbaPcs.SetFirstZone();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xEC: {
        const int padType = Joybus.GetPadType(*object->m_localBase);
        this->push(object, (static_cast<unsigned int>(__cntlzw(0x40000 - padType)) >> 5) & 0xFF);
        outResult = 0;
        break;
    }
    case -0xED: {
        CVector hitPosition;
        hitPosition.x = reinterpret_cast<float*>(object->m_localBase)[0];
        hitPosition.y = reinterpret_cast<float*>(object->m_localBase)[1];
        hitPosition.z = reinterpret_cast<float*>(object->m_localBase)[2];
        if (MapPcs.CheckHitCylinderNear(hitPosition, CVector(kCFlatPadStickZero, FLOAT_80330B90, kCFlatPadStickZero), kCFlatPadStickZero, object->m_localBase[3]) != 0) {
            MapPcs.CalcHitPosition(hitPosition);
            *reinterpret_cast<float*>(object->m_localBase[4]) = hitPosition.y;
            this->push(object, 1);
            outResult = 0;
            break;
        } else {
            this->push(object, 0);
        }
        outResult = 0;
        break;
    }
    case -0xEE: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        AStar.addAstar(
            localFloats[0],
            localFloats[1],
            localFloats[2],
            object->m_localBase[3],
            object->m_localBase[4]);
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xEF:
        AStar.calcAStar();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF0: {
        this->push(
            object,
            m_spawnBits[*object->m_localBase].m_hi & static_cast<unsigned int>(1ULL << object->m_localBase[1]));
        outResult = 0;
        break;
    }
    case -0xF1:
        this->resetSpawnBit(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF3: {
        int result = this->GetSysControl(*object->m_localBase);
        this->push(object, result);
        outResult = 0;
        break;
    }
    case -0xF4:
        PartPcs.pppSetDebugHide(static_cast<unsigned char>(*object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF5:
        Sound.SeMaxVolume(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF6:
        Game.m_caravanWorkArr[*object->m_localBase].m_gil = object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF7: {
        CColor color(
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            static_cast<u8>(object->m_localBase[5]));
        MenuPcs.GetFont22()->SetTlutColor(*object->m_localBase + 0xB, object->m_localBase[1], color);
        MenuPcs.GetFont22()->FlushTlutColor();
        this->push(object, 0);
        outResult = 0;
        break;
    }
    case -0xF8:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347addNoFreeSeGroup\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.AddNoFreeSeGroup(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x93:
        if (GetNumMes__9CFlatDataFv(&System) >= 3U) {
            System.Printf(const_cast<char*>("\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347addNoFreeWave\202\265\202\334\202\265\202\275\201B%d\n"), *object->m_localBase);
        }
        Sound.AddNoFreeWave(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xF9:
        CameraPcs.SetFullScreenShadowCamLen(*reinterpret_cast<float*>(object->m_localBase));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xFA:
        CGItemObj::ItemJump(*object->m_localBase, *reinterpret_cast<float*>(object->m_localBase + 1));
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xFB:
        Game.SetNextScriptNewGame();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xFC:
        *reinterpret_cast<int*>(reinterpret_cast<char*>(&DbgMenuPcs) + 0x10844) = *object->m_localBase;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&DbgMenuPcs) + 0x10848) =
            object->m_localBase[1];
        this->push(object, 0);
        outResult = 0;
        break;
    case -0x30:
        this->push(object, GraphicPcs.GetScreenFadeExecutingBit());
        outResult = 0;
        break;
    case -0x31:
        CGItemObj::DeleteAllFieldItem();
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA1:
        CGItemObj::DispAllFieldItem(*object->m_localBase);
        this->push(object, 0);
        outResult = 0;
        break;
    case -0xA2:
        this->push(object, static_cast<int>(OSTicksToMilliseconds(OSGetTick())));
        outResult = 0;
        break;
    default:
        return 0;
    }

    return 1;
}
#pragma pool_strings off

/*
 * --INFO--
 * PAL Address: 0x800B2F80
 * PAL Size: 912b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CVal* CFlatRuntime2::onSystemVal(CFlatRuntime::CObject*, int systemValue)
{
    CGame::CGameWork& gameWork = Game.m_gameWork;
    u8* game = reinterpret_cast<u8*>(&Game);

    if (systemValue <= -0x1000) {
        int valueIndex = -0x1000 - systemValue;
        unsigned int result = 0;
        const unsigned short* row =
            reinterpret_cast<const unsigned short*>(Game.unkCFlatData0[2]) +
            (0x5FF - valueIndex % 0x600) * 0x24;

        switch (valueIndex / 0x600) {
        case 0: result = row[0]; break;
        case 1: result = row[1]; break;
        case 2: result = row[2]; break;
        case 3: result = row[3]; break;
        case 4: result = row[4]; break;
        case 5: result = row[5]; break;
        case 6: result = row[6]; break;
        case 7: result = row[7]; break;
        case 8: result = row[8]; break;
        case 9: result = row[9]; break;
        case 10: result = row[10]; break;
        case 0xB: result = row[0xB]; break;
        case 0xC: result = row[0xC]; break;
        case 0xD: result = row[0xD]; break;
        case 0xE: result = row[0xE]; break;
        case 0xF: result = row[0xF]; break;
        case 0x10: result = row[0x10]; break;
        case 0x11: result = row[0x11]; break;
        case 0x12: result = row[0x12]; break;
        case 0x13: result = row[0x13]; break;
        case 0x14: result = row[0x14]; break;
        case 0x15: result = row[0x15]; break;
        case 0x16: result = row[0x16]; break;
        case 0x17: result = row[0x17]; break;
        case 0x18: result = row[0x18]; break;
        case 0x19: result = row[0x19]; break;
        case 0x1A: result = row[0x1A]; break;
        case 0x1B: result = row[0x1B]; break;
        case 0x1C: result = row[0x1C]; break;
        case 0x1D: result = row[0x1D]; break;
        case 0x1E: result = row[0x1E]; break;
        case 0x1F: result = row[0x1F]; break;
        case 0x20: result = row[0x20]; break;
        case 0x21: result = row[0x21]; break;
        case 0x22: result = row[0x22]; break;
        case 0x23: result = row[0x23]; break;
        default:
            break;
        }
        FlatLastResult(this) = result;
    } else if (systemValue <= -500) {
        int bitIndex = systemValue + 0x9F3;
        int byteIndex = bitIndex / 8;
        unsigned int mask = 1U << (bitIndex % 8);
        unsigned int flag = static_cast<unsigned int>(static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[byteIndex])) & mask;
        FlatLastResult(this) = (-flag | flag) >> 31;
    } else if (systemValue <= -200) {
        int workIndex = systemValue + 0x1C7;
        FlatLastResult(this) = static_cast<unsigned int>(static_cast<int>(gameWork.m_eventWork[workIndex]));
    } else {
        switch (systemValue) {
        case -0x40:
            FlatLastResult(this) = *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0);
            break;
        case -0x41:
            FlatLastResult(this) = gameWork.m_timerA;
            break;
        case -0x42:
            FlatLastResult(this) = gameWork.m_scriptGlobalTime;
            break;
        case -0x43:
            FlatLastResult(this) = gameWork.m_frameCounter;
            break;
        case -0x47:
        case -0x46:
        case -0x45:
        case -0x44:
            {
                int index = systemValue + 0x47;
                FlatLastResult(this) = gameWork.m_wmBackupParams[index];
            }
            break;
        case -0x56:
        case -0x55:
        case -0x54:
        case -0x53:
        case -0x52:
        case -0x51:
        case -0x50:
        case -0x4F:
        case -0x4E:
        case -0x4D:
        case -0x4C:
        case -0x4B:
        case -0x4A:
        case -0x49:
        case -0x48:
            {
                int index = systemValue + 0x56;
                FlatLastResult(this) = gameWork.m_bossArtifactStageTable[index];
            }
            break;
        case -0x65:
        case -100:
        case -99:
        case -0x62:
        case -0x61:
        case -0x60:
        case -0x5F:
        case -0x5E:
        case -0x5D:
        case -0x5C:
        case -0x5B:
        case -0x5A:
        case -0x59:
        case -0x58:
        case -0x57:
            {
                int index = systemValue + 0x65;
                FlatLastResult(this) = gameWork.m_unkStageTable[index];
            }
            break;
        case -0x66:
            FlatLastResult(this) = gameWork.m_chaliceElement;
            break;
        case -0x6B:
        case -0x6A:
        case -0x69:
        case -0x68:
        case -0x67:
            {
                int index = systemValue + 0x6B;
                FlatLastResult(this) = gameWork.m_eventHeader[index];
            }
            break;
        case -0x73:
        case -0x72:
        case -0x71:
        case -0x70:
        case -0x6F:
        case -0x6E:
        case -0x6D:
        case -0x6C: {
            u8* usbEdit = reinterpret_cast<u8*>(&Game) + (systemValue + 0x73) * 0xC30;
            unsigned int charaValue;
            if (*(int*)(usbEdit + 0x1794) != 0) {
                charaValue = *(unsigned short*)(usbEdit + 0x1404);
            } else {
                charaValue = 0;
            }
            FlatLastResult(this) = charaValue;
            break;
        }
        case -0x76:
            FlatLastResult(this) = gameWork.m_menuStageMode;
            break;
        case -0x78:
            FlatLastResult(this) = gameWork.m_gameOverFlag;
            break;
        case -0x7A: {
            unsigned int languageValue = 1;
            switch (Game.m_gameWork.m_languageId) {
            case 0:
                languageValue = 1;
                break;
            case 1:
                languageValue = 3;
                break;
            case 2:
                languageValue = 5;
                break;
            case 3:
                languageValue = 6;
                break;
            case 4:
                languageValue = 4;
                break;
            case 5:
                languageValue = 7;
                break;
            default:
                break;
            }
            FlatLastResult(this) = languageValue;
            break;
        }
        default:
            break;
        }
    }

    return reinterpret_cast<CFlatRuntime::CVal*>(&FlatLastResult(this));
}

/*
 * --INFO--
 * PAL Address: 0x800BBDDC
 * PAL Size: 1680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_dead_assignments off
void CFlatRuntime2::onSetSystemVal(int systemValue, CFlatRuntime::CStack* stack, int setMode)
{
    CGame::CGameWork* gameWork = &Game.m_gameWork;
    if (systemValue > -0x1000) {
        if (systemValue <= -500) {
            int bitIndex = systemValue + 0x9F3;
            int byteIndex = bitIndex / 8;
            unsigned char* flagByte = reinterpret_cast<unsigned char*>(Game.m_gameWork.m_eventFlags) + byteIndex;
            unsigned char flagBits = *flagByte;
            unsigned int mask = 1U << (bitIndex % 8);
            unsigned int flag = flagBits & mask;
            int value = (-flag | flag) >> 31;
            stack[-1].m_word = value;

            int result = value;
            switch (setMode) {
            case -1:
                result = value - stack->m_word;
                break;
            case 0:
                result = stack->m_word;
                break;
            case 1:
                result = value + stack->m_word;
                break;
            }

            if (result != 0) {
                *flagByte |= mask;
            } else {
                *flagByte &= ~mask;
            }
        } else if (systemValue <= -200) {
            int workIndex = systemValue + 0x1C7;
            stack[-1].m_word = gameWork->m_eventWork[workIndex];
            switch (setMode) {
            case -1:
                gameWork->m_eventWork[workIndex] =
                    static_cast<short>(gameWork->m_eventWork[workIndex] - stack->m_word);
                break;
            case 0:
                gameWork->m_eventWork[workIndex] = static_cast<short>(stack->m_word);
                break;
            case 1:
                gameWork->m_eventWork[workIndex] =
                    static_cast<short>(gameWork->m_eventWork[workIndex] + stack->m_word);
                break;
            }
        } else {
            switch (systemValue) {
            case -0x40:
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0);
                switch (setMode) {
                case -1:
                    *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) =
                        *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) - stack->m_word;
                    break;
                case 0:
                    *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) = stack->m_word;
                    break;
                case 1:
                    *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) =
                        *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) + stack->m_word;
                    break;
                }
                break;
            case -0x41:
                stack[-1].m_word = gameWork->m_timerA;
                switch (setMode) {
                case -1:
                    gameWork->m_timerA = gameWork->m_timerA - stack->m_word;
                    break;
                case 0:
                    gameWork->m_timerA = stack->m_word;
                    break;
                case 1:
                    gameWork->m_timerA = gameWork->m_timerA + stack->m_word;
                    break;
                }
                break;
            case -0x42:
                stack[-1].m_word = gameWork->m_scriptGlobalTime;
                switch (setMode) {
                case -1:
                    gameWork->m_scriptGlobalTime = gameWork->m_scriptGlobalTime - stack->m_word;
                    break;
                case 0:
                    gameWork->m_scriptGlobalTime = stack->m_word;
                    break;
                case 1:
                    gameWork->m_scriptGlobalTime = gameWork->m_scriptGlobalTime + stack->m_word;
                    break;
                }
                break;
            case -0x43:
                stack[-1].m_word = gameWork->m_frameCounter;
                switch (setMode) {
                case -1:
                    gameWork->m_frameCounter = gameWork->m_frameCounter - stack->m_word;
                    break;
                case 0:
                    gameWork->m_frameCounter = stack->m_word;
                    break;
                case 1:
                    gameWork->m_frameCounter = gameWork->m_frameCounter + stack->m_word;
                    break;
                }
                break;
            case -0x56:
            case -0x55:
            case -0x54:
            case -0x53:
            case -0x52:
            case -0x51:
            case -0x50:
            case -0x4F:
            case -0x4E:
            case -0x4D:
            case -0x4C:
            case -0x4B:
            case -0x4A:
            case -0x49:
            case -0x48: {
                int workIndex = systemValue + 0x56;
                stack[-1].m_word = gameWork->m_bossArtifactStageTable[workIndex];
                switch (setMode) {
                case -1:
                    gameWork->m_bossArtifactStageTable[workIndex] = gameWork->m_bossArtifactStageTable[workIndex] - stack->m_word;
                    break;
                case 0:
                    gameWork->m_bossArtifactStageTable[workIndex] = stack->m_word;
                    break;
                case 1:
                    gameWork->m_bossArtifactStageTable[workIndex] = gameWork->m_bossArtifactStageTable[workIndex] + stack->m_word;
                    break;
                }
                break;
            }
            case -0x65:
            case -100:
            case -99:
            case -0x62:
            case -0x61:
            case -0x60:
            case -0x5F:
            case -0x5E:
            case -0x5D:
            case -0x5C:
            case -0x5B:
            case -0x5A:
            case -0x59:
            case -0x58:
            case -0x57: {
                int workIndex = systemValue + 0x65;
                stack[-1].m_word = gameWork->m_unkStageTable[workIndex];
                switch (setMode) {
                case -1:
                    gameWork->m_unkStageTable[workIndex] = gameWork->m_unkStageTable[workIndex] - stack->m_word;
                    break;
                case 0:
                    gameWork->m_unkStageTable[workIndex] = stack->m_word;
                    break;
                case 1:
                    gameWork->m_unkStageTable[workIndex] = gameWork->m_unkStageTable[workIndex] + stack->m_word;
                    break;
                }
                break;
            }
            case -0x66:
                stack[-1].m_word = gameWork->m_chaliceElement;
                switch (setMode) {
                case -1:
                    gameWork->m_chaliceElement = gameWork->m_chaliceElement - stack->m_word;
                    break;
                case 0:
                    gameWork->m_chaliceElement = stack->m_word;
                    break;
                case 1:
                    gameWork->m_chaliceElement = gameWork->m_chaliceElement + stack->m_word;
                    break;
                }
                break;
            case -0x6B:
            case -0x6A:
            case -0x69:
            case -0x68:
            case -0x67: {
                int workIndex = systemValue + 0x6B;
                stack[-1].m_word = gameWork->m_eventHeader[workIndex];
                switch (setMode) {
                case -1:
                    gameWork->m_eventHeader[workIndex] = gameWork->m_eventHeader[workIndex] - stack->m_word;
                    break;
                case 0:
                    gameWork->m_eventHeader[workIndex] = stack->m_word;
                    break;
                case 1:
                    gameWork->m_eventHeader[workIndex] = gameWork->m_eventHeader[workIndex] + stack->m_word;
                    break;
                }
                break;
            }
            case -0x47:
            case -0x46:
            case -0x45:
            case -0x44: {
                int workIndex = systemValue + 0x47;
                stack[-1].m_word = gameWork->m_wmBackupParams[workIndex];
                switch (setMode) {
                case -1:
                    gameWork->m_wmBackupParams[workIndex] = gameWork->m_wmBackupParams[workIndex] - stack->m_word;
                    break;
                case 0:
                    gameWork->m_wmBackupParams[workIndex] = stack->m_word;
                    break;
                case 1:
                    gameWork->m_wmBackupParams[workIndex] = gameWork->m_wmBackupParams[workIndex] + stack->m_word;
                    break;
                }
                break;
            }
            case -0x75:
                stack[-1].m_word = static_cast<int>(Game.m_gameWork.m_bossArtifactStageIndex);
                switch (setMode) {
                case -1:
                    Game.m_gameWork.m_bossArtifactStageIndex =
                        static_cast<short>(Game.m_gameWork.m_bossArtifactStageIndex - stack->m_word);
                    break;
                case 0:
                    Game.m_gameWork.m_bossArtifactStageIndex = static_cast<short>(stack->m_word);
                    break;
                case 1:
                    Game.m_gameWork.m_bossArtifactStageIndex =
                        static_cast<short>(Game.m_gameWork.m_bossArtifactStageIndex + stack->m_word);
                    break;
                }
                break;
            case -0x76: {
                unsigned int value = static_cast<unsigned int>(gameWork->m_menuStageMode);
                stack[-1].m_word = value;
                switch (setMode) {
                case -1:
                    value = value - stack->m_word;
                    break;
                case 0:
                    value = stack->m_word;
                    break;
                case 1:
                    value = value + stack->m_word;
                    break;
                }
                MenuPcs.ChgPlayModeFromScript(static_cast<bool>((-value | value) >> 31));
                break;
            }
            case -0x77:
                stack[-1].m_word = static_cast<unsigned int>(Game.m_gameWork.m_soundOptionFlag);
                switch (setMode) {
                case -1:
                    Game.m_gameWork.m_soundOptionFlag =
                        static_cast<unsigned char>(Game.m_gameWork.m_soundOptionFlag - stack->m_word);
                    break;
                case 0:
                    Game.m_gameWork.m_soundOptionFlag = static_cast<unsigned char>(stack->m_word);
                    break;
                case 1:
                    Game.m_gameWork.m_soundOptionFlag =
                        static_cast<unsigned char>(Game.m_gameWork.m_soundOptionFlag + stack->m_word);
                    break;
                }
                break;
            case -0x79: {
                short* optionValue = reinterpret_cast<short*>(&Game.m_gameWork.m_optionValue);
                stack[-1].m_word = *optionValue;
                switch (setMode) {
                case -1:
                    *optionValue = static_cast<short>(*optionValue - stack->m_word);
                    break;
                case 0:
                    *optionValue = static_cast<short>(stack->m_word);
                    break;
                case 1:
                    *optionValue = static_cast<short>(*optionValue + stack->m_word);
                    break;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
#pragma pop
