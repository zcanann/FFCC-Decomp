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
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/memorycard.h"
#include "ffcc/mes.h"
#include "ffcc/mesmenu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_gba.h"
#include "ffcc/p_game.h"
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

static inline CUSBStreamData* UsbStream(CPartPcs* self)
{
    return &self->m_usbStreamData;
}

struct CMapCylinderRaw
{
    Vec m_bottom;
    u8 m_pad0C[0x0C];
    Vec m_top;
    float m_radius;
    Vec m_direction;
    Vec m_direction2;
};

extern float FLOAT_80330B30;
extern float FLOAT_80330b74;
extern float FLOAT_80330b54;
extern float FLOAT_80330b64;
extern const float FLOAT_80330B34;
extern float FLOAT_80330B3C;
extern float FLOAT_80330B50;
extern float FLOAT_80330B54;
extern float FLOAT_80330B58;

static const char s_setMiniGameParamFmt[] = "SetMiniGameParam no 0x%04x data[%d]\n";
static const char s_cflatDebugFileFmt[] = "cflat_d%d.bin";
static const char s_cflatCfdPathFmt[] = "dvd/%scft/%s.cfd";
static const char s_cflatForceAnimInterpDeprecatedFmt[] =
    "\203f\203o\203b\203O\227p\212\326\220\224setForceAnimInterp\202\315\224p\216~"
    "\202\263\202\352\202\334\202\265\202\275\201B\n";
static const char s_cflatLoadWaveAsyncFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadWaveAsync"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatIsLoadWaveAsyncCompletedFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347isLoadWaveAsyncCompleted"
    "\202\265\202\334\202\265\202\275\201B\223\307\202\335\215\236\202\335\202\315%s\n";
static const char s_cflatLoadBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadBgm"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatPlayBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playBgm"
    "\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatLoadWaveFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadWave"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatLoadStreamFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347loadStream"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatPlayStreamFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playStream"
    "\202\265\202\334\202\265\202\275\201B\n";
static const char s_cflatStreamVolumeFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347streamVolume"
    "\202\265\202\334\202\265\202\275\201B\n";
static const char s_cflatFreeWaveFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347freeWave"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatStopBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347stopBgm"
    "\202\265\202\334\202\265\202\275\201B\n";
static const char s_cflatFadeOutBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347fadeOutBgm"
    "\202\265\202\334\202\265\202\275\201B\n";
static const char s_cflatPlayNextBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347playNextBgm"
    "\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatCancelWaveAsyncFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347cancelWaveAsync"
    "\202\265\202\334\202\265\202\275\201B\n";
static const char s_cflatCrossPlayBgmFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347crossPlayBgm"
    "\202\360\215\304\220\266\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatAddNoFreeSeGroupFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347addNoFreeSeGroup"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatAddNoFreeWaveFmt[] =
    "\201\254\201\254\203X\203N\203\212\203v\203g\202\251\202\347addNoFreeWave"
    "\202\265\202\334\202\265\202\275\201B%d\n";
static const char s_cflatLoadCompleted[] = "\212\256\227\271";
static const char s_cflatLoadNotCompleted[] = "\226\242\212\256\227\271";

static inline int RemapPadSlot(CPad* pad, unsigned int padIndex)
{
    int activePad = pad->_448_4_;
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

static inline void CatmullRomVec(Vec& out, const Vec& p0, const Vec& p1, const Vec& p2, const Vec& p3, float t)
{
    const float t2 = t * t;
    const float t3 = t2 * t;

    out.x = 0.5f * ((2.0f * p1.x) + (-p0.x + p2.x) * t +
                    (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
                    (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);
    out.y = 0.5f * ((2.0f * p1.y) + (-p0.y + p2.y) * t +
                    (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
                    (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);
    out.z = 0.5f * ((2.0f * p1.z) + (-p0.z + p2.z) * t +
                    (2.0f * p0.z - 5.0f * p1.z + 4.0f * p2.z - p3.z) * t2 +
                    (-p0.z + 3.0f * p1.z - 3.0f * p2.z + p3.z) * t3);
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

static inline unsigned int& RuntimeDebugFlags(CFlatRuntime2* self)
{
    return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(self) + 0x129C);
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
    CMapCylinderRaw cylinder;

    cylinder.m_direction.z = 0.0f;
    cylinder.m_direction.y = 0.0f;
    cylinder.m_direction.x = 0.0f;
    cylinder.m_direction2.z = 1.0f;
    cylinder.m_direction2.y = 1.0f;
    cylinder.m_direction2.x = 1.0f;

    cylinder.m_bottom = *cylinderBottom;
    cylinder.m_top = *direction;
    cylinder.m_radius = radius;

    return MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cylinder), direction, hitMask);
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
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_setMiniGameParamFmt), id, value);
    }

    if (id != 0x1202) {
        if (id < 0x1202) {
            if (id != 0x1102) {
                if (id < 0x1102 && id >= 0x1101) {
                    *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x1350) =
                        static_cast<char>(value);
                }
            } else {
                *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x1348) = 1;
            }
        } else if (id < 0x1204) {
            *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x134B) &= ~(1 << value);
        }
    } else {
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x134B) |= 1 << value;
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
    *(int*)((char*)this + 0x434) = enable;
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return FLOAT_80330B30;
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return FLOAT_80330B30;
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return FLOAT_80330B30;
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
            goto done_check;
        }
    }
    isInvalidPad = true;

done_check:
    if (isInvalidPad) {
        return FLOAT_80330B30;
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
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

    if (_452_4_ == 0) {
        if (padIndex != 0) {
            goto done_check;
        }
        if (_448_4_ == -1) {
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
    m_viewerChoiceColor[shadeIndex].color.r = color.color.r;
    m_viewerChoiceColor[shadeIndex].color.g = color.color.g;
    m_viewerChoiceColor[shadeIndex].color.b = color.color.b;
    m_viewerChoiceColor[shadeIndex].color.a = color.color.a;
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
extern "C" int IsUse__8CMesMenuFv(void* mesMenu)
{
    unsigned char result = 0;
    if (*(int*)((char*)mesMenu + 8) != 0 && *(int*)((char*)mesMenu + 0xC) <= 1 &&
        reinterpret_cast<CMes*>(reinterpret_cast<char*>(mesMenu) + 0x1C)->GetWait() != 4) {
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
 * PAL Address: 0x800B9538
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
PPPCREATEPARAM::PPPCREATEPARAM()
{
    m_soundEffectParams.m_soundEffectHandle = -1;
    m_soundEffectParams.m_soundEffectSlot = -1;
    m_soundEffectParams.m_soundEffectStopFlag = 0;
    m_soundEffectParams.m_soundEffectKind = 1;
    m_soundEffectParams.m_soundEffectStartFrame = 0;
    m_soundEffectParams.m_soundEffectStartedOnce = 0;
    m_soundEffectParams.m_soundEffectFadeFrames = 30;
    m_hitParamA = 0;
    m_hitParamB = 0;
    m_hitObjectCount = 0;
    m_hitFlags = 0;
    m_positionOffsetPtr = 0;
    m_rotationPtr = 0;
    m_scalePtr = 0;
    m_extraPositionPtr = 0;
    m_paramA = 0;
    m_paramB = 0;
    m_lookTargetPtr = 0;
    m_objectHitMask = 0;
    m_cylinderAttribute = 0;
    m_paramC = FLOAT_80330B34;
    m_paramD = FLOAT_80330B34;
    *reinterpret_cast<unsigned char*>(&m_owner) = 0;
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
CVector::operator Vec&()
{
    return *reinterpret_cast<Vec*>(this);
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
    gMapHitDrawMode.m_byte = drawMode;
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

    PSVECScale(a, &scaledA, FLOAT_80330B34 - t);
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
CVector::operator Vec*()
{
    return reinterpret_cast<Vec*>(this);
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
    float x = other.x;
    float y = other.y;
    this->x = x;
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
void CCameraPcs::SetFov(float fov)
{
    *(float*)((char*)this + 0xFC) = fov;
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
    unsigned int* dst = (unsigned int*)((char*)&m_nextScript - 4);
    unsigned int* src = (unsigned int*)((char*)nextScript - 4);

    for (int i = 0; i < 0x20; i++) {
        unsigned int a = src[1];
        src += 2;
        unsigned int b = src[0];
        dst[1] = a;
        dst += 2;
        dst[0] = b;
    }

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
void CCameraPcs::SetFromScript()
{
    *(int*)((char*)this + 0x438) = 1;
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
int CCameraPcs::IsAbsolute()
{
    return *(int*)((char*)this + 0x444);
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
    const bool infiniteRange = (kLineSegmentMinT == maxDistance);
    float bestDistance = infiniteRange ? kLineBoundsInitMin : maxDistance;
    const float maxDistanceSq = maxDistance * maxDistance;
    int found = 0;
    unsigned int bestIndex = 0;
    float bestT = kLineSegmentMinT;
    Vec bestPosition;

    for (unsigned int i = 0; i + 1 < m_numPoints; i++) {
        Vec* candidate = &m_points[i];
        float distanceSq = PSVECSquareDistance(candidate, targetPosition);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            Vec candidatePosition = *candidate;
            float distance = sqrtf(distanceSq);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosition = candidatePosition;
                bestIndex = i;
                bestT = kLineSegmentMinT;
                found = 1;
            }
        }

        if (i + 1 == m_numPoints - 1) {
            candidate = &m_points[i + 1];
            distanceSq = PSVECSquareDistance(candidate, targetPosition);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                Vec candidatePosition = *candidate;
                float distance = sqrtf(distanceSq);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPosition = candidatePosition;
                    bestIndex = i;
                    bestT = kLineSegmentMaxT;
                    found = 1;
                }
            }
        }

        CLineSegment64& segment = m_segments[i];
        float dotTarget = PSVECDotProduct(targetPosition, &segment.delta);
        float dotPoint = PSVECDotProduct(&m_points[i], &segment.delta);
        float segmentT = (dotTarget - dotPoint) / (segment.length * segment.length);
        if (((kLineSegmentMinT <= segmentT) && (segmentT <= kLineSegmentMaxT)) || infiniteRange) {
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
    if (m_numPoints == 0) {
        return 0;
    }

    if ((m_min.x - margin) <= position->x && (m_min.y - margin) <= position->y &&
        (m_min.z - margin) <= position->z && (m_max.x + margin) >= position->x &&
        (m_max.y + margin) >= position->y && (m_max.z + margin) >= position->z) {
        return 1;
    }

    return 0;
}

extern "C" void CalcBound__9CLine(CLine<64>* line)
{
    line->m_min.x = kLineBoundsInitMin;
    line->m_min.y = kLineBoundsInitMin;
    line->m_min.z = kLineBoundsInitMin;
    line->m_max.x = kLineBoundsInitMax;
    line->m_max.y = kLineBoundsInitMax;
    line->m_max.z = kLineBoundsInitMax;
    line->m_totalLength = kLineSegmentMinT;

    Vec* point = line->m_points;
    CLineSegment64* segment = line->m_segments;
    for (unsigned int i = 0; i < line->m_numPoints; i++, point++, segment++) {

        if (point->x < line->m_min.x) {
            line->m_min.x = point->x;
        }
        if (point->y < line->m_min.y) {
            line->m_min.y = point->y;
        }
        if (point->z < line->m_min.z) {
            line->m_min.z = point->z;
        }

        if (point->x > line->m_max.x) {
            line->m_max.x = point->x;
        }
        if (point->y > line->m_max.y) {
            line->m_max.y = point->y;
        }
        if (point->z > line->m_max.z) {
            line->m_max.z = point->z;
        }

        if (i != 0) {
            CLineSegment64* prevSegment = segment - 1;
            PSVECSubtract(point, point - 1, &prevSegment->delta);
            prevSegment->length = PSVECMag(&prevSegment->delta);
            prevSegment->startLength = line->m_totalLength;
            line->m_totalLength += prevSegment->length;
            if (prevSegment->length != kLineSegmentMinT) {
                PSVECNormalize(&prevSegment->delta, &prevSegment->normal);
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
void CFlatRuntime2::onSystemFunc(CFlatRuntime::CObject* object, int, int systemFunc, int& outResult)
{
    CFlatRuntime* runtime = reinterpret_cast<CFlatRuntime*>(this);
    CGame::CGameWork& gameWork = Game.m_gameWork;
    u16* strOffs = *reinterpret_cast<u16**>(reinterpret_cast<u8*>(runtime) + 0x34);
    char* strBlob = *reinterpret_cast<char**>(reinterpret_cast<u8*>(runtime) + 0x38);

    switch (systemFunc) {
    case -3:
        runtime->push(object, getNumFreeObject(5));
        outResult = 0;
        return;
    case -4:
        if (CameraPcs.IsAbsolute() != 0) {
            const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
            CVector refPosition(localFloats[0], localFloats[1], localFloats[2]);
            if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10414) == 0) {
                CameraPcs.SetRefPosition(refPosition);
            } else {
                *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(&CharaPcs) + 0x38) = refPosition;
            }

            CVector position(localFloats[3], localFloats[4], localFloats[5]);
            if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10414) == 0) {
                CameraPcs.SetPosition(position);
            } else {
                *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(&CharaPcs) + 0x2C) = position;
            }
            CameraPcs.SetFromScript();
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -5: {
        unsigned short buttons = 0;
        if (((1 << *object->m_localBase) & *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x12A8)) == 0) {
            buttons = Pad.GetButton(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= 0xF3FF;
        }
        runtime->push(object, static_cast<short>(buttons));
        outResult = 0;
        return;
    }
    case -6: {
        float value = sinf(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -7: {
        float value = cosf(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -8: {
        const unsigned int x = object->m_localBase[0];
        const unsigned int y = object->m_localBase[1];
        char* format = strBlob + strOffs[object->m_localBase[2]];

        if (object->m_argCount == 3) {
            Graphic.Printf(x, y, format);
        } else {
            char spec[256];
            char rendered[256];
            char line[264];
            line[0] = '\0';

            for (int i = 0; i < object->m_argCount - 3; i++) {
                while (true) {
                    int specLen = 0;
                    while ((format[specLen] != '\0') && ((specLen == 0) || (format[specLen] != '%'))) {
                        spec[specLen] = format[specLen];
                        specLen++;
                    }
                    spec[specLen] = '\0';
                    format += specLen;

                    if (spec[0] == '%') {
                        break;
                    }
                    strcat(line, spec, sizeof(line));
                }

                rendered[0] = '\0';
                const int argIndex = i + 3;
                char* scan = spec + 1;
                if (spec[0] == '%') {
                    int fmtIndex = 1;
                    int width = 0;
                    int started = spec[1] == '0';
                    for (; (*scan >= '0') && (*scan <= '9'); scan++) {
                        fmtIndex++;
                        width = width * 10 + (*scan - '0');
                    }

                    if (spec[fmtIndex] == 'b') {
                        char* out = rendered;
                        unsigned int value = object->m_localBase[argIndex];
                        int outLen = 0;
                        for (int bit = 0; bit < width; bit++) {
                            const unsigned int cur = (value >> ((width - bit) - 1U)) & 1U;
                            if (started == 0 && cur != 0) {
                                started = 1;
                            }
                            if (started != 0) {
                                *out++ = static_cast<char>(cur + '0');
                                outLen++;
                            }
                        }
                        rendered[outLen] = '\0';
                        strcat(rendered, spec + fmtIndex + 1, sizeof(rendered));
                    } else {
                        while (*scan != '\0') {
                            switch (*scan) {
                            case 'd':
                            case 'x':
                                sprintf(rendered, spec, object->m_localBase[argIndex]);
                                scan = const_cast<char*>("");
                                break;
                            case 'f': {
                                union {
                                    unsigned int word;
                                    float value;
                                } arg;
                                arg.word = object->m_localBase[argIndex];
                                sprintf(rendered, spec, static_cast<double>(arg.value));
                                scan = const_cast<char*>("");
                                break;
                            }
                            case 's':
                                sprintf(rendered, spec, strBlob + strOffs[object->m_localBase[argIndex]]);
                                scan = const_cast<char*>("");
                                break;
                            default:
                                scan++;
                                break;
                            }
                        }
                    }
                }

                strcat(line, rendered, sizeof(line));
            }

            Graphic.Printf(x, y, line);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -9:
        Game.ChangeMap(*object->m_localBase, object->m_localBase[1], 0, 1);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -10: {
        float value = atan2__3stdFff(
            *reinterpret_cast<float*>(object->m_localBase),
            *reinterpret_cast<float*>(object->m_localBase + 1));
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -0x0B: {
        unsigned short buttons = 0;
        if (((1 << *object->m_localBase) & *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x12A8)) == 0) {
            buttons = Pad.GetButtonDown(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= 0xF3FF;
        }
        runtime->push(object, static_cast<short>(buttons));
        outResult = 0;
        return;
    }
    case -0x0C: {
        unsigned short buttons = 0;
        if (((1 << *object->m_localBase) & *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x12A8)) == 0) {
            buttons = Pad.GetButtonRepeat(*object->m_localBase);
        }
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttons &= 0xF3FF;
        }
        runtime->push(object, static_cast<short>(buttons));
        outResult = 0;
        return;
    }
    case -0x0D: {
        float* values = reinterpret_cast<float*>(object->m_localBase);
        Vec a = {values[0], values[1], values[2]};
        Vec b = {values[3], values[4], values[5]};
        float value = PSVECDistance(&a, &b);
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -0x0E:
        runtime->push(object, Math.Rand(*object->m_localBase));
        outResult = 0;
        return;
    case -0x0F: {
        float value = Math.RandF(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -0x10:
        runtime->push(object, Math.RandPM(*object->m_localBase));
        outResult = 0;
        return;
    case -0x11: {
        float value = Math.RandFPM(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -0x12:
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) == 0) {
            *reinterpret_cast<float*>(object->m_localBase[1]) =
                static_cast<float>(Pad.GetLeftStickX(*object->m_localBase));
            *reinterpret_cast<float*>(object->m_localBase[2]) =
                static_cast<float>(Pad.GetLeftStickY(*object->m_localBase));
        } else {
            *reinterpret_cast<float*>(object->m_localBase[1]) = 0.0f;
            *reinterpret_cast<float*>(object->m_localBase[2]) = 0.0f;
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x13:
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) == 0) {
            *reinterpret_cast<float*>(object->m_localBase[1]) =
                static_cast<float>(Pad.GetRightStickX(*object->m_localBase));
            *reinterpret_cast<float*>(object->m_localBase[2]) =
                static_cast<float>(Pad.GetRightStickY(*object->m_localBase));
        } else {
            *reinterpret_cast<float*>(object->m_localBase[1]) = 0.0f;
            *reinterpret_cast<float*>(object->m_localBase[2]) = 0.0f;
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x14: {
        const int value = *object->m_localBase;
        runtime->push(object, value < 0 ? -value : value);
        outResult = 0;
        return;
    }
    case -0x15: {
        float value = *reinterpret_cast<float*>(object->m_localBase);
        if (value < 0.0f) {
            value = -value;
        }
        runtime->push(object, *reinterpret_cast<int*>(&value));
        outResult = 0;
        return;
    }
    case -0x16: {
        CGame::CNextScript nextScript;
        nextScript.m_flags = 0;
        strcpy(nextScript.m_name, strBlob + strOffs[*object->m_localBase]);
        Game.SetNextScript(&nextScript);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x17:
        CameraPcs.SetZRotate(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x18:
        CameraPcs.SetFov(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x19: {
        int* pointCount = reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x17D4);
        float* totalDistance = reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x17D8);
        if (*pointCount < 0x40) {
            if (*object->m_localBase != 0) {
                *pointCount = 0;
                *totalDistance = 0.0f;
            }

            Vec* point = reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + *pointCount * 0x10);
            *reinterpret_cast<unsigned int*>(&point->x) = object->m_localBase[1];
            *reinterpret_cast<unsigned int*>(&point->y) = object->m_localBase[2];
            *reinterpret_cast<unsigned int*>(&point->z) = object->m_localBase[3];

            if (*pointCount != 0) {
                Vec* previous = reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + (*pointCount - 1) * 0x10);
                *totalDistance += PSVECDistance(point, previous);
            }

            *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x17DC + *pointCount * 0x10) = *totalDistance;
            *pointCount = *pointCount + 1;
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x1A: {
        const unsigned int mode = *object->m_localBase;
        const int pointCount = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x17D4);
        Vec result = {0.0f, 0.0f, 0.0f};

        if (pointCount > 0 && object->m_localBase[2] != 0) {
            float t = static_cast<float>(static_cast<int>(object->m_localBase[1])) /
                      static_cast<float>(static_cast<int>(object->m_localBase[2]));

            switch (mode & 3) {
            case 3:
                t = -((FLOAT_80330B3C * (FLOAT_80330B34 + sinf(FLOAT_80330B54 * t + FLOAT_80330B50))) -
                      FLOAT_80330B34);
                break;
            case 1:
                t = FLOAT_80330B34 + sinf(FLOAT_80330B50 * t + FLOAT_80330B58);
                break;
            case 2:
                t = sinf(FLOAT_80330B50 * t);
                break;
            default:
                break;
            }

            if ((mode & 4) == 0) {
                const float totalDistance = *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x17D8);
                const float pathDistance = totalDistance * t;

                result = *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0);
                for (int i = 0; i + 1 < pointCount; i++) {
                    const float startDistance =
                        *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x17DC + i * 0x10);
                    const float endDistance =
                        *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x17DC + (i + 1) * 0x10);
                    if (startDistance <= pathDistance && pathDistance <= endDistance) {
                        float segmentT = 0.0f;
                        if (endDistance != startDistance) {
                            segmentT = (pathDistance - startDistance) / (endDistance - startDistance);
                        }
                        const Vec& startPoint = *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + i * 0x10);
                        const Vec& endPoint =
                            *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + (i + 1) * 0x10);
                        VECLerp(const_cast<Vec*>(&startPoint), const_cast<Vec*>(&endPoint), &result, segmentT);
                        break;
                    }
                }
            } else {
                const int maxIndex = pointCount - 1;
                float scaled = t * static_cast<float>(pointCount - 1);
                int baseIndex = static_cast<int>(scaled);
                float segmentT = scaled - static_cast<float>(baseIndex);

                if (baseIndex >= maxIndex) {
                    baseIndex = maxIndex;
                    segmentT = 0.0f;
                }

                const Vec& p0 =
                    *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + ClampIndex(baseIndex - 1, maxIndex) * 0x10);
                const Vec& p1 =
                    *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + ClampIndex(baseIndex, maxIndex) * 0x10);
                const Vec& p2 =
                    *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + ClampIndex(baseIndex + 1, maxIndex) * 0x10);
                const Vec& p3 =
                    *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(this) + 0x17E0 + ClampIndex(baseIndex + 2, maxIndex) * 0x10);
                CatmullRomVec(result, p0, p1, p2, p3, segmentT);
            }
        }

        *reinterpret_cast<float*>(object->m_localBase[3]) = result.x;
        *reinterpret_cast<float*>(object->m_localBase[4]) = result.y;
        *reinterpret_cast<float*>(object->m_localBase[5]) = result.z;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x1B: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[2],
            localFloats[3],
            localFloats[4]);
        this->PutParticle((*object->m_localBase << 8) | object->m_localBase[1], position, localFloats[5]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x1C:
        RuntimeDebugFlags(this) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x1D:
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x1E:
        if (*object->m_localBase < 0x10) {
            const int lineOffset = *object->m_localBase * 0xB14;
            *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1BF4 + lineOffset) = 0;
            *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1C08 + lineOffset) = object->m_localBase[1];
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x1F:
        if (*object->m_localBase < 0x10) {
            const int lineOffset = *object->m_localBase * 0xB14;
            unsigned int* pointCount = reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1BF4 + lineOffset);
            if (*pointCount < 0x40) {
                const unsigned int pointOffset = *pointCount * 0xC + lineOffset;
                *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1C0C + pointOffset) =
                    object->m_localBase[1];
                *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1C10 + pointOffset) =
                    object->m_localBase[2];
                *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1C14 + pointOffset) =
                    object->m_localBase[3];
                *pointCount = *pointCount + 1;
                CalcBound__9CLine(reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(this) + 0x1BDC + lineOffset));
            }
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x20: {
        CColor color(
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF);
        SetAmbient__9CCharaPcsFiP8_GXColor(&CharaPcs, *object->m_localBase, color);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x21: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float yaw = localFloats[5];
        const float pitch = localFloats[6];
        const float sinYaw = sinf(yaw);
        const float cosYaw = cosf(yaw);
        const float sinPitch = sinf(pitch);
        const float cosPitch = cosf(pitch);
        Vec direction = {-sinYaw * cosPitch, -sinPitch, -cosYaw * cosPitch};
        CColor color(
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            0xFF);

        SetDiffuse__9CCharaPcsFiUlP8_GXColorP3Vec(
            &CharaPcs, *object->m_localBase, object->m_localBase[1], color, &direction);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x22: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const unsigned int mask = *object->m_localBase;
        Vec target = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        const float margin = localFloats[4];
        int found = 0;
        unsigned int bestLine = 0;
        float bestDistance = kLineBoundsInitMin;
        float bestLineDistance = 0.0f;

        for (unsigned int i = 0; i < 0x10; i++) {
            CLine<64>* line = reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(this) + 0x1BDC + i * 0xB14);
            const unsigned int lineMask = *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(line) + 0x2C);
            if (line->m_numPoints == 0 || (lineMask & mask) == 0 || line->IsInner(&target, margin) == 0) {
                continue;
            }

            unsigned long segment = 0;
            float segmentRatio = 0.0f;
            float nearestDistance = 0.0f;
            if (line->Calc((Vec*)0, &nearestDistance, &segment, &segmentRatio, &target, margin) != 0 &&
                nearestDistance < bestDistance) {
                found = 1;
                bestLine = i;
                bestDistance = nearestDistance;
                bestLineDistance = line->m_segments[segment].length * segmentRatio + line->m_segments[segment].startLength;
            }
        }

        if (found != 0) {
            *reinterpret_cast<unsigned int*>(object->m_localBase[5]) = bestLine;
            *reinterpret_cast<float*>(object->m_localBase[6]) = bestLineDistance;
            *reinterpret_cast<unsigned int*>(object->m_localBase[7]) =
                *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x26EC + bestLine * 0xB14);
        }

        runtime->push(object, found);
        outResult = 0;
        return;
    }
    case -0x23: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float distance = localFloats[1];
        CLine<64>* line = reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(this) + 0x1BDC + *object->m_localBase * 0xB14);
        Vec position = {0.0f, 0.0f, 0.0f};

        if (line->m_numPoints > 0) {
            if (distance < 0.0f || line->m_numPoints == 1) {
                position = line->m_points[0];
            } else if (distance >= line->m_totalLength) {
                position = line->m_points[line->m_numPoints - 1];
            } else {
                for (unsigned int i = 0; i + 1 < line->m_numPoints; i++) {
                    CLineSegment64& segment = line->m_segments[i];
                    if (segment.startLength <= distance && distance < segment.startLength + segment.length) {
                        const float t = (distance - segment.startLength) / segment.length;
                        VECLerp(&line->m_points[i], &line->m_points[i + 1], &position, t);
                        break;
                    }
                }
            }
        }

        *reinterpret_cast<float*>(object->m_localBase[2]) = position.x;
        *reinterpret_cast<float*>(object->m_localBase[3]) = position.y;
        *reinterpret_cast<float*>(object->m_localBase[4]) = position.z;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x24: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        const float distance = localFloats[1];
        CLine<64>* line = reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(this) + 0x1BDC + *object->m_localBase * 0xB14);
        Vec direction = {0.0f, 0.0f, 0.0f};

        if (line->m_numPoints > 1) {
            if (distance < 0.0f) {
                direction = line->m_segments[0].normal;
            } else if (distance >= line->m_totalLength) {
                direction = line->m_segments[line->m_numPoints - 2].normal;
            } else {
                for (unsigned int i = 0; i + 1 < line->m_numPoints; i++) {
                    CLineSegment64& segment = line->m_segments[i];
                    if (segment.startLength <= distance && distance < segment.startLength + segment.length) {
                        direction = segment.normal;
                        break;
                    }
                }
            }
        }

        if (object->m_localBase[2] == 0) {
            direction.x = -direction.x;
            direction.y = -direction.y;
            direction.z = -direction.z;
        }

        *reinterpret_cast<float*>(object->m_localBase[3]) = direction.x;
        *reinterpret_cast<float*>(object->m_localBase[4]) = direction.y;
        *reinterpret_cast<float*>(object->m_localBase[5]) = direction.z;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x25: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec target = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        CLine<64>* line = reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(this) + 0x1BDC + *object->m_localBase * 0xB14);
        unsigned long segment = 0;
        float segmentRatio = 0.0f;
        float distance = 0.0f;

        if (line->Calc((Vec*)0, (float*)0, &segment, &segmentRatio, &target, 0.0f) != 0) {
            distance = line->m_segments[segment].length * segmentRatio + line->m_segments[segment].startLength;
        }

        *reinterpret_cast<float*>(object->m_localBase[4]) = distance;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x26:
        runtime->push(
            object, *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x26EC + *object->m_localBase * 0xB14));
        outResult = 0;
        return;
    case -0x27: {
        if ((RuntimeDebugFlags(this) & CFlatRuntimeDebugFlag_ClassCollision) != 0) {
            Mtx viewMtx;
            Mtx drawMtx;
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
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

            const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
            const float radius = localFloats[3];
            PSMTXScale(drawMtx, radius, radius, radius);
            drawMtx[0][3] = localFloats[0];
            drawMtx[1][3] = localFloats[1];
            drawMtx[2][3] = localFloats[2];
            PSMTXConcat(viewMtx, drawMtx, drawMtx);
            GXLoadPosMtxImm(drawMtx, GX_PNMTX0);

            GXColor color = {
                static_cast<u8>(object->m_localBase[4]),
                static_cast<u8>(object->m_localBase[5]),
                static_cast<u8>(object->m_localBase[6]),
                0xFF,
            };
            GXSetChanMatColor(GX_COLOR0A0, color);
            Graphic.DrawSphere();
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x28:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1C08 + *object->m_localBase * 0xB14) =
            *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x29: {
        _GXColor color = {
            static_cast<u8>(object->m_localBase[0]),
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            0xFF,
        };
        Graphic.SetCopyClear(color, 0);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x2A: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        _GXColor color = {
            static_cast<u8>(object->m_localBase[0]),
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            0xFF,
        };
        Graphic.SetFogColor(color);
        Graphic.SetFogParam(localFloats[3], localFloats[4]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x2B:
        CameraPcs.SetFullScreenShadowEnable(static_cast<unsigned char>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x2C: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position = {
            localFloats[0],
            localFloats[1],
            localFloats[2],
        };
        CameraPcs.SetFullScreenShadowPos(&position, localFloats[3]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x2D: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CameraPcs.SetFullScreenShadowRot(localFloats[0], localFloats[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x2E:
        MapPcs.IsHitDrawMode(static_cast<char>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x2F:
        MapMng.SetIdGrpMask(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x30:
        runtime->push(object, GraphicPcs.GetScreenFadeExecutingBit());
        outResult = 0;
        return;
    case -0x31:
        CGItemObj::DeleteAllFieldItem();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x32: {
        u8* graphicsPcs = reinterpret_cast<u8*>(&GraphicPcs);
        *reinterpret_cast<int*>(graphicsPcs + 0x98) = *object->m_localBase;
        *reinterpret_cast<int*>(graphicsPcs + 0x88) = object->m_localBase[1];
        *reinterpret_cast<int*>(graphicsPcs + 0x8C) = *reinterpret_cast<int*>(graphicsPcs + 0x88);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x33: {
        u8* graphicsPcs = reinterpret_cast<u8*>(&GraphicPcs);
        *reinterpret_cast<int*>(graphicsPcs + 0x6C) = *object->m_localBase;
        *reinterpret_cast<int*>(graphicsPcs + 0x70) = 0;
        graphicsPcs[0x64] = static_cast<u8>(object->m_localBase[1]);
        graphicsPcs[0x65] = static_cast<u8>(object->m_localBase[2]);
        graphicsPcs[0x66] = static_cast<u8>(object->m_localBase[3]);
        graphicsPcs[0x67] = 0xFF;
        *reinterpret_cast<int*>(graphicsPcs + 0x5C) = object->m_localBase[4];
        *reinterpret_cast<int*>(graphicsPcs + 0x60) = *reinterpret_cast<int*>(graphicsPcs + 0x5C);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x34: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec axis = {cosf(localFloats[1]), 0.0f, sinf(localFloats[1])};
        Mtx matrix;
        Mtx rotation;

        CameraPcs.GetWorldMapMatrix(matrix);
        if (*object->m_localBase != 0) {
            PSMTXIdentity(matrix);
        }

        PSMTXRotAxisRad(rotation, &axis, localFloats[2]);
        PSMTXConcat(rotation, matrix, matrix);

        axis.x = 0.0f;
        axis.y = 1.0f;
        axis.z = 0.0f;
        PSMTXRotAxisRad(rotation, &axis, localFloats[3]);
        PSMTXConcat(rotation, matrix, matrix);
        CameraPcs.SetWorldMapMatrix(matrix);

        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x35:
        runtime->push(object, this->GetFreeParticleSlot());
        outResult = 0;
        return;
    case -0x36:
        this->EndParticleSlot(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x37:
        this->ResetParticleWork((*object->m_localBase << 8) | object->m_localBase[2], object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x38: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[0],
            localFloats[1],
            localFloats[2]);
        this->SetParticleWorkPos(position, localFloats[3]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x39: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector target(
            localFloats[0],
            localFloats[1],
            localFloats[2]);
        this->SetParticleWorkTarget(target);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x3A:
        this->SetParticleWorkVector(
            static_cast<float>(*object->m_localBase), static_cast<float>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x3B:
        this->SetParticleWorkScale(static_cast<float>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x3C:
        this->SetParticleWorkCol(
            *object->m_localBase, object->m_localBase[1], static_cast<float>(object->m_localBase[2]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x3D:
        this->PutParticleWork();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x3E:
        PartMng.pppEndPart(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x3F: {
        Mtx matrix;
        Quaternion rotation;
        CameraPcs.GetWorldMapMatrix(matrix);
        C_QUATMtx(&rotation, matrix);
        *reinterpret_cast<float*>(object->m_localBase[0]) = rotation.x;
        *reinterpret_cast<float*>(object->m_localBase[1]) = rotation.y;
        *reinterpret_cast<float*>(object->m_localBase[2]) = rotation.z;
        *reinterpret_cast<float*>(object->m_localBase[3]) = rotation.w;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x40: {
        float* values = reinterpret_cast<float*>(object->m_localBase);
        Quaternion rotation = {values[0], values[1], values[2], values[3]};
        Mtx matrix;
        PSMTXQuat(matrix, &rotation);
        CameraPcs.SetWorldMapMatrix(matrix);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x41: {
        const unsigned int* localBase = object->m_localBase;
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        float alpha = static_cast<float>(static_cast<int>(localBase[1])) /
                      static_cast<float>(static_cast<int>(localBase[2]));
        Quaternion start = {localFloats[3], localFloats[4], localFloats[5], localFloats[6]};
        Quaternion end = {localFloats[7], localFloats[8], localFloats[9], localFloats[10]};
        Quaternion rotation;

        switch (*localBase & 3) {
        case 3:
            alpha = -((FLOAT_80330B3C * (FLOAT_80330B34 + sinf(FLOAT_80330B54 * alpha + FLOAT_80330B50))) -
                      FLOAT_80330B34);
            break;
        case 1:
            alpha = FLOAT_80330B34 + sinf(FLOAT_80330B50 * alpha + FLOAT_80330B58);
            break;
        case 2:
            alpha = sinf(FLOAT_80330B50 * alpha);
            break;
        default:
            break;
        }

        C_QUATSlerp(&start, &end, &rotation, alpha);
        *reinterpret_cast<float*>(localBase[11]) = rotation.x;
        *reinterpret_cast<float*>(localBase[12]) = rotation.y;
        *reinterpret_cast<float*>(localBase[13]) = rotation.z;
        *reinterpret_cast<float*>(localBase[14]) = rotation.w;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x42: {
        const int padType = Joybus.GetPadType(*object->m_localBase);
        runtime->push(object, (0x40U - padType | padType - 0x40U) >> 31);
        outResult = 0;
        return;
    }
    case -0x43:
        PartMng.pppShowIdx(static_cast<short>(*object->m_localBase), static_cast<unsigned char>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x44:
        PartMng.pppShowSlot(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x45: {
        unsigned int* localBase = object->m_localBase;
        CMesMenu* mesMenu = MenuPcs.GetMesMenu(localBase[0]);
        if (mesMenu == 0) {
            if (GetNumMes__9CFlatDataFv(&System) != 0) {
                System.Printf(const_cast<char*>("MesMenu no %d is null\n"), localBase[0]);
            }
        } else {
            char* message;
            if ((localBase[3] & 0x80) == 0) {
                message = reinterpret_cast<char*>(GetSysMes__5CGameFi(reinterpret_cast<u8*>(this) + 0xCF20, localBase[7]));
            } else {
                message = GetNumSysMes__5CGameFv(&Game, localBase[7]);
            }
            reinterpret_cast<CMesMenu*>(mesMenu)->Open(
                message, localBase[1], localBase[2], localBase[3], localBase[4], localBase[5], localBase[6]);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x46: {
        CMesMenu* mesMenu = MenuPcs.GetMesMenu(*object->m_localBase);
        if (mesMenu == 0) {
            if (GetNumMes__9CFlatDataFv(&System) != 0) {
                System.Printf(const_cast<char*>("MesMenu no %d is null\n"), *object->m_localBase);
            }
        } else {
            reinterpret_cast<CMesMenu*>(mesMenu)->CloseRequest(1);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x47: {
        CMesMenu* mesMenu = MenuPcs.GetMesMenu(*object->m_localBase);
        if (mesMenu == 0) {
            if (GetNumMes__9CFlatDataFv(&System) != 0) {
                System.Printf(const_cast<char*>("MesMenu no %d is null\n"), *object->m_localBase);
            }
        } else {
            GetMes__9CFlatDataFi(mesMenu, object->m_localBase[1], object->m_localBase[2]);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x48: {
        CMesMenu* mesMenu = MenuPcs.GetMesMenu(*object->m_localBase);
        if (mesMenu == 0) {
            if (GetNumMes__9CFlatDataFv(&System) != 0) {
                System.Printf(const_cast<char*>("MesMenu no %d is null\n"), *object->m_localBase);
            }
            runtime->push(object, 0);
        } else {
            runtime->push(object, GetErrorLevel__7CSystemFv(mesMenu, object->m_localBase[1]));
        }
        outResult = 0;
        return;
    }
    case -0x49:
        this->SetParticleWorkSpeed(static_cast<float>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x4A:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x12A0) =
            static_cast<unsigned int>(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x4B:
        PartMng.pppFieldShowFpNo(static_cast<short>(*object->m_localBase), static_cast<unsigned char>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x4C: {
        _GXColor color = {
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            0x80,
        };
        MapMng.SetIdGrpColor(*object->m_localBase, object->m_localBase[1], color);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x4D: {
        CMesMenu* mesMenu = MenuPcs.GetMesMenu(*object->m_localBase);
        if (mesMenu == 0) {
            if (GetNumMes__9CFlatDataFv(&System) != 0) {
                System.Printf(const_cast<char*>("MesMenu no %d is null\n"), *object->m_localBase);
            }
            runtime->push(object, 0);
            outResult = 0;
            return;
        }
        if (IsUse__8CMesMenuFv(mesMenu) == 0) {
            runtime->push(object, 0);
            outResult = 0;
            return;
        }
        return;
    }
    case -0x4E: {
        CFlatRuntime::CObject* targetObject = ResolveRuntimeObjectById(this, *object->m_localBase);
        this->SetParticleWorkBind(targetObject);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x4F:
        MapMng.SetMeshCameraSemiTransRange(
            static_cast<unsigned short>(*object->m_localBase),
            *reinterpret_cast<float*>(object->m_localBase + 1),
            *reinterpret_cast<float*>(object->m_localBase + 2),
            *reinterpret_cast<float*>(object->m_localBase + 3),
            *reinterpret_cast<float*>(object->m_localBase + 4),
            (60.0f * 1000.0f * *reinterpret_cast<float*>(object->m_localBase + 5)) / 180.0f);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x50: {
        u8* graphicsPcs = reinterpret_cast<u8*>(&GraphicPcs);
        *reinterpret_cast<int*>(graphicsPcs + 0x24) = 2;
        graphicsPcs[0x12] = 0xFF;
        graphicsPcs[0x13] = 0xFF;
        graphicsPcs[0x14] = 0xFF;
        graphicsPcs[0x15] = 0xFF;
        *reinterpret_cast<int*>(graphicsPcs + 0x20) = 0;
        *reinterpret_cast<int*>(graphicsPcs + 0x4) = object->m_localBase[0];
        *reinterpret_cast<int*>(graphicsPcs + 0x44) = object->m_localBase[1];
        *reinterpret_cast<int*>(graphicsPcs + 0x36) = object->m_localBase[2];
        *reinterpret_cast<int*>(graphicsPcs + 0x40) = object->m_localBase[3];
        *reinterpret_cast<int*>(graphicsPcs + 0x8) = *reinterpret_cast<int*>(graphicsPcs + 0x4);
        GraphicPcs.ReqScreenCapture();
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x51: {
        char path[0x100];
        sprintf(path, s_cflatCfdPathFmt, Game.GetLangString(), strBlob + strOffs[*object->m_localBase]);
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            fileHandle->Read();
            fileHandle->SyncCompleted();
            reinterpret_cast<CFlatData*>(reinterpret_cast<u8*>(this) + 0xCF20)->Create(File.GetBuffer());
            fileHandle->Close();
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x52: {
        const int enabled = (((-*object->m_localBase) | *object->m_localBase) >> 31);
        GraphicPcs.m_dofFlag = enabled;
        GraphicPcs.SetDOFParameter(
            static_cast<signed char>(static_cast<char>(*object->m_localBase) - 1),
            static_cast<signed char>(object->m_localBase[1]),
            *reinterpret_cast<float*>(object->m_localBase + 2),
            *reinterpret_cast<float*>(object->m_localBase + 3),
            *reinterpret_cast<float*>(object->m_localBase + 4),
            *reinterpret_cast<float*>(object->m_localBase + 5),
            *reinterpret_cast<float*>(object->m_localBase + 6),
            object->m_localBase[7]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x53:
        CharaPcs.SetCharaAllocStage(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x54: {
        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400) = index + 1;
        runtime->push(object, *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0xE400 + index * 4));
        outResult = 0;
        return;
    }
    case -0x55: {
        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400) = index + 1;
        runtime->push(object, *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0xE400 + index * 4));
        outResult = 0;
        return;
    }
    case -0x56: {
        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400) = index + 1;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0xE400 + index * 4) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x57: {
        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400) = index + 1;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0xE400 + index * 4) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x58: {
        char filename[0x80];
        sprintf(filename, s_cflatDebugFileFmt, *object->m_localBase);
        MemoryCardMan.DebugReadWrite(1, filename, reinterpret_cast<u8*>(this) + 0xE400, 0x2000);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x59: {
        char filename[0x80];
        sprintf(filename, s_cflatDebugFileFmt, *object->m_localBase);
        MemoryCardMan.DebugReadWrite(0, filename, reinterpret_cast<u8*>(this) + 0xE400, 0x2000);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x5A:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10400) = 0;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x5B: {
        CFlatRuntime::CObject* targetObject = ResolveRuntimeObjectById(this, object->m_localBase[1]);
        this->SetParticleWorkParam(*object->m_localBase, targetObject);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x5C: {
        CFlatRuntime::CObject* targetObject = ResolveRuntimeObjectById(this, object->m_localBase[1]);
        this->IgnoreParticle(static_cast<short>(*object->m_localBase), targetObject);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x5D:
        runtime->push(object, System.IsGdev());
        outResult = 0;
        return;
    case -0x5E:
        if (GetNumMes__9CFlatDataFv(&System) != 0) {
            System.Printf(const_cast<char*>(s_cflatForceAnimInterpDeprecatedFmt));
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x5F:
        runtime->push(object, static_cast<int>(Math.DstRot(
                                  *reinterpret_cast<float*>(object->m_localBase),
                                  *reinterpret_cast<float*>(object->m_localBase + 1))));
        outResult = 0;
        return;
    case -0x60: {
        const int alpha = static_cast<int>(FLOAT_80330b74 * *reinterpret_cast<float*>(object->m_localBase + 3)) & 0xFF;
        const unsigned int blurA = (static_cast<unsigned int>(__cntlzw(object->m_localBase[4])) >> 5) & 0xFF;
        const unsigned int blurB = (static_cast<unsigned int>(__cntlzw(object->m_localBase[5])) >> 5) & 0xFF;
        GraphicPcs.SetBlurParameter(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]),
            static_cast<unsigned char>(object->m_localBase[2]), static_cast<unsigned char>(alpha),
            static_cast<unsigned char>(blurA), static_cast<unsigned char>(blurB),
            static_cast<short>(object->m_localBase[6]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x61: {
        const int group = (~(object->m_localBase[1] - 1 | 1 - object->m_localBase[1]) >> 31) & 3;
        Memory.SetDefaultGroup(group);
        CharaPcs.LoadMergeFile(*object->m_localBase, object->m_localBase[1], 0);
        Memory.ResetDefaultGroup();
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x62:
        CharaPcs.SetNoFreeMergeMask(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -99: {
        CFlatRuntime::CObject* targetObject = ResolveRuntimeObjectById(this, *object->m_localBase);
        this->SetParticleWorkTrace(targetObject);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -100:
        this->initAllFinished();
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(this) + 0x10404) = 1;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x65: {
        _GXColor color = {
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF,
        };
        CColor shadeColor(color);
        CharaPcs.SetMapShadeColor(*object->m_localBase, shadeColor);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x66:
        runtime->push(object, 2);
        outResult = 0;
        return;
    case -0x67:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatLoadWaveAsyncFmt), *object->m_localBase);
        }
        Sound.LoadWaveASync(*object->m_localBase, -1, 0);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x68: {
        const int completed = Sound.IsLoadWaveASyncCompleted();
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatIsLoadWaveAsyncCompletedFmt),
                completed != 0 ? s_cflatLoadCompleted : s_cflatLoadNotCompleted);
        }
        runtime->push(object, completed);
        outResult = 0;
        return;
    }
    case -0x69:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatLoadBgmFmt), *object->m_localBase);
        }
        Sound.LoadBgm(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x6A:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatPlayBgmFmt), *object->m_localBase);
        }
        Sound.PlayBgm(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x6B:
        Sound.LoadSe(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x6C:
        runtime->push(object, Sound.PlaySe(*object->m_localBase, 0x40, 0x7F, 0));
        outResult = 0;
        return;
    case -0x6D:
        gameWork.m_linkTable[object->m_localBase[2]][object->m_localBase[3]][object->m_localBase[0]]
                                   [object->m_localBase[1]] = static_cast<unsigned char>(object->m_localBase[4]);
        gameWork.m_linkTable[object->m_localBase[0]][object->m_localBase[1]][object->m_localBase[2]]
                                   [object->m_localBase[3]] = static_cast<unsigned char>(object->m_localBase[4]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x6E:
        runtime->push(
            object, gameWork.m_linkTable[object->m_localBase[0]][object->m_localBase[1]][object->m_localBase[2]]
                                          [object->m_localBase[3]]);
        outResult = 0;
        return;
    case -0x6F:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&Game.m_gameWork) + 8) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x70:
        gameWork.m_timerA = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x71:
        gameWork.m_scriptGlobalTime = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x72:
        gameWork.m_bossArtifactStageTable[*object->m_localBase] = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x73:
        gameWork.m_unkStageTable[*object->m_localBase] = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x74: {
        unsigned short buttonDown = Pad.GetGbaButtonDown(*object->m_localBase);
        if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
            buttonDown &= 0xF3FF;
        }
        runtime->push(object, static_cast<int>(static_cast<short>(buttonDown)));
        outResult = 0;
        return;
    }
    case -0x75:
        CMes::SetTempValue(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x76:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1298) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x77:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatLoadWaveFmt), *object->m_localBase);
        }
        Sound.LoadWave(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x78:
        Sound.Clear3DLine(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x79: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        Sound.Add3DLine(*object->m_localBase, &position);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x7A: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        runtime->push(
            object,
            Sound.PlaySe3D(
                *object->m_localBase, &position, localFloats[4], localFloats[5], 0));
        outResult = 0;
        return;
    }
    case -0x7B:
        runtime->push(
            object, Sound.PlaySe3DLine(*object->m_localBase, static_cast<char>(object->m_localBase[1]),
                        *reinterpret_cast<float*>(object->m_localBase + 2),
                        *reinterpret_cast<float*>(object->m_localBase + 3), 0));
        outResult = 0;
        return;
    case -0x7C:
        Sound.StopSe3D(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x7D:
        PartMng.pppDeletePart(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x7E:
        PartMng.pppDeleteSlot(*object->m_localBase, 0);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x7F:
        Sound.SetReverb(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x80:
        this->SetParticleWorkSe(*object->m_localBase, static_cast<char>(object->m_localBase[1]), object->m_localBase[2]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x81: {
        float angle = static_cast<float>(object->m_localBase[2]);
        Vec normal = {sinf(angle), 0.0f, cosf(angle)};
        Vec point = {static_cast<float>(*object->m_localBase), 0.0f, static_cast<float>(object->m_localBase[1])};
        Mtx& reflectMtx = *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(this) + 0x12b4);
        PSMTXReflect(reflectMtx, &point, &normal);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x82:
        CFlatLetterEventEnabled() = static_cast<unsigned int>(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x83:
        runtime->push(object, Graphic.GetProgressive());
        outResult = 0;
        return;
    case -0x84:
        Graphic.ChangeProgressive(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x85:
        runtime->push(
            object, Wind.AddAmbient(static_cast<float>(*object->m_localBase), static_cast<float>(object->m_localBase[1])));
        outResult = 0;
        return;
    case -0x86: {
        Vec position = {
            static_cast<float>(object->m_localBase[0]),
            static_cast<float>(object->m_localBase[1]),
            static_cast<float>(object->m_localBase[2]),
        };
        runtime->push(
            object,
            Wind.AddDiffuse(&position, static_cast<float>(object->m_localBase[3]),
                static_cast<float>(object->m_localBase[4]), static_cast<float>(object->m_localBase[5])));
        outResult = 0;
        return;
    }
    case -0x87: {
        Vec position = {
            static_cast<float>(object->m_localBase[0]),
            static_cast<float>(object->m_localBase[1]),
            static_cast<float>(object->m_localBase[2]),
        };
        runtime->push(
            object,
            Wind.AddSphere(&position, static_cast<float>(object->m_localBase[3]),
                static_cast<float>(object->m_localBase[4]), object->m_localBase[5]));
        outResult = 0;
        return;
    }
    case -0x88:
        Wind.ChangePower(*object->m_localBase, static_cast<float>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x89:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatLoadStreamFmt), *object->m_localBase);
        }
        Sound.LoadStream(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8A:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatPlayStreamFmt));
        }
        Sound.PlayStreamASync();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8B:
        Sound.StopStream();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8C:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatFreeWaveFmt), *object->m_localBase);
        }
        Sound.FreeWave(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8D:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatStopBgmFmt));
        }
        Sound.StopBgm();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8E:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatFadeOutBgmFmt));
        }
        Sound.FadeOutBgm(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x8F:
        Sound.FadeOutSe3D(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x90:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatPlayNextBgmFmt), *object->m_localBase);
        }
        Sound.PlayNextBgm(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x91:
        runtime->push(object, PartMng.pppGetNumFreePppMngSt());
        outResult = 0;
        return;
    case -0x92:
        MapMng.SetMapTexAnim(
            *object->m_localBase, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x93:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatAddNoFreeWaveFmt), *object->m_localBase);
        }
        Sound.AddNoFreeWave(static_cast<short>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x94: {
        float* bounds = reinterpret_cast<float*>(object->m_localBase);
        ppvEnv->m_boxMinX = bounds[0];
        ppvEnv->m_boxMaxX = bounds[1];
        ppvEnv->m_boxMinY = bounds[2];
        ppvEnv->m_boxMaxY = bounds[3];
        ppvEnv->m_boxMinZ = bounds[4];
        ppvEnv->m_boxMaxZ = bounds[5];
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
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
        runtime->push(object, result);
        outResult = 0;
        return;
    }
    case -0x96:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x12AC) = *object->m_localBase;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x12B0) = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x97: {
        unsigned int slot = static_cast<unsigned int>(*object->m_localBase);
        *reinterpret_cast<char*>(reinterpret_cast<u8*>(this) + 0x134C + (slot * 0x14)) =
            static_cast<char>(object->m_localBase[1]);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1350 + (slot * 0x14)) = object->m_localBase[2];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1354 + (slot * 0x14)) = object->m_localBase[3];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1358 + (slot * 0x14)) = object->m_localBase[4];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x135C + (slot * 0x14)) = object->m_localBase[5];
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x98:
        *reinterpret_cast<char*>(reinterpret_cast<u8*>(this) + 0x134D + (*object->m_localBase * 0x14)) =
            static_cast<char>(object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x99: {
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjAnim(
            mapObjIndex, object->m_localBase[1], object->m_localBase[2], static_cast<char>(object->m_localBase[3]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x9A: {
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjMime(mapObjIndex, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0x9B:
        CharaPcs.LoadCam(*object->m_localBase, strBlob + strOffs[object->m_localBase[1]]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0x9C: {
        int cameraSlot = *object->m_localBase;
        int cameraFrame = object->m_localBase[1];
        int* cameraFrameCount = reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 4 + cameraSlot * 4);
        int* cameraTablePtr = reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0x14 + cameraSlot * 4);
        if ((*cameraTablePtr == 0) || (cameraFrame < 0) || (*cameraFrameCount <= cameraFrame)) {
            runtime->push(object, 0);
            outResult = 0;
            return;
        }

        int cameraData = *cameraTablePtr + cameraFrame * 0x20;
        *reinterpret_cast<int*>(object->m_localBase[2]) = *reinterpret_cast<int*>(cameraData + 0x0);
        *reinterpret_cast<float*>(object->m_localBase[3]) = -*reinterpret_cast<float*>(cameraData + 0x4);
        *reinterpret_cast<float*>(object->m_localBase[4]) = -*reinterpret_cast<float*>(cameraData + 0x8);
        *reinterpret_cast<int*>(object->m_localBase[5]) = *reinterpret_cast<int*>(cameraData + 0xC);
        *reinterpret_cast<float*>(object->m_localBase[6]) = -*reinterpret_cast<float*>(cameraData + 0x10);
        *reinterpret_cast<float*>(object->m_localBase[7]) = -*reinterpret_cast<float*>(cameraData + 0x14);
        *reinterpret_cast<int*>(object->m_localBase[8]) = *reinterpret_cast<int*>(cameraData + 0x18);
        *reinterpret_cast<float*>(object->m_localBase[9]) =
            -(FLOAT_80330b54 * *reinterpret_cast<float*>(cameraData + 0x1C)) / FLOAT_80330b64;
        runtime->push(object, 1);
        outResult = 0;
        return;
    }
    case -0x9D:
        runtime->push(object, (static_cast<unsigned int>(__cntlzw(MemoryCardMan.DummyLoad())) >> 5) & 0xFF);
        outResult = 0;
        return;
    case -0x9E:
        runtime->push(object, (static_cast<unsigned int>(__cntlzw(MemoryCardMan.DummySave())) >> 5) & 0xFF);
        outResult = 0;
        return;
    case -0x9F:
        if (object->m_localBase[1] < 0) {
            Game.m_caravanWorkArr[*object->m_localBase].m_shopState = 0;
        } else {
            Game.m_caravanWorkArr[*object->m_localBase].Init(
                object->m_localBase[1],
                reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + object->m_localBase[1] * 0x1D0),
                object->m_localBase[2]);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA0:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatStreamVolumeFmt));
        }
        Sound.SetStreamVolume(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA1:
        CGItemObj::DispAllFieldItem(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA2:
        runtime->push(object, static_cast<int>(OSTicksToMilliseconds(OSGetTick())));
        outResult = 0;
        return;
    case -0xA3:
        GbaPcs.SetFirstZone();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA4:
        runtime->push(
            object, Game.m_caravanWorkArr[*object->m_localBase].GetEvtFlag(object->m_localBase[1]));
        outResult = 0;
        return;
    case -0xA5:
        Game.m_caravanWorkArr[*object->m_localBase].SetEvtFlag(object->m_localBase[1], object->m_localBase[2]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA6:
        runtime->push(
            object, Game.m_caravanWorkArr[*object->m_localBase].GetEvtWord(object->m_localBase[1]));
        outResult = 0;
        return;
    case -0xA7:
        Game.m_caravanWorkArr[*object->m_localBase].SetEvtWord(object->m_localBase[1],
            static_cast<short>(object->m_localBase[2]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xA8:
        runtime->push(object, MenuPcs.GetWorldParam(*object->m_localBase));
        outResult = 0;
        return;
    case -0xA9:
        MenuPcs.SetWorldParam(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xAA:
        Game.m_caravanWorkArr[*object->m_localBase].m_letterMeta[object->m_localBase[1]] =
            static_cast<unsigned short>(object->m_localBase[2]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xAB:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_letterMeta[object->m_localBase[1]]);
        outResult = 0;
        return;
    case -0xAC:
        Game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8 = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xAD:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8);
        outResult = 0;
        return;
    case -0xAE:
        strcpy(
            reinterpret_cast<char*>(Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ca_0x3dd),
            strBlob + strOffs[object->m_localBase[1]]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xAF:
        runtime->push(
            object, static_cast<int>(Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ca_0x3dd[object->m_localBase[1]]));
        outResult = 0;
        return;
    case -0xB0:
        strcpy(Game.m_startScriptName, strBlob + strOffs[*object->m_localBase]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xB1:
        runtime->push(object, static_cast<int>(gameWork.m_townName[*object->m_localBase]));
        outResult = 0;
        return;
    case -0xB2:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&GraphicPcs) + 64) = 0;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&GraphicPcs) + 48) = 1;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&GraphicPcs) + 52) = 1;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&GraphicPcs) + 68) = *object->m_localBase;
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 56) = static_cast<u8>(object->m_localBase[1]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 57) = static_cast<u8>(object->m_localBase[2]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 58) = static_cast<u8>(object->m_localBase[3]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 59) = static_cast<u8>(object->m_localBase[4]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 60) = static_cast<u8>(object->m_localBase[5]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 61) = static_cast<u8>(object->m_localBase[6]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 62) = static_cast<u8>(object->m_localBase[7]);
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(&GraphicPcs) + 63) = static_cast<u8>(object->m_localBase[8]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xB3:
        runtime->push(
            object,
            CGItemObj::DeleteOld(*object->m_localBase, object->m_localBase[1], object,
                                 reinterpret_cast<CFlatRuntime::CObject*>(object->m_engineObject)));
        outResult = 0;
        return;
    case -0xB4:
        PartMng.pppSetDeltaSlot(
            *object->m_localBase, static_cast<long>(0.25f * *reinterpret_cast<float*>(object->m_localBase + 1)));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xB5:
        PartMng.pppSetDeltaIdx(
            static_cast<short>(*object->m_localBase),
            static_cast<long>(0.25f * *reinterpret_cast<float*>(object->m_localBase + 1)));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xB6:
        Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xB7:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac);
        outResult = 0;
        return;
    case -0xB8: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        Sound.ChangeSe3DPos(*object->m_localBase, &position);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xB9:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 36) = *object->m_localBase;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 40) = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xBA:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x10414) = *object->m_localBase;
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xBB: {
        PPPCREATEPARAM createParam;
        PartMng.pppCreate(0, *object->m_localBase, &createParam, 1);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xBC:
        PartMng.pppFieldEndFpNo(static_cast<short>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xBD:
    case -0xBE: {
        CRomLetterWork* romLetterWork[8];
        Game.m_caravanWorkArr[*object->m_localBase].SearchRomLetterWork(romLetterWork, 8);

        for (int i = 0; i < 8; i++) {
            u16* letter = reinterpret_cast<u16*>(romLetterWork[i]);
            int dstOffs = i * 4;
            *reinterpret_cast<int*>(object->m_localBase[1] + dstOffs) = letter != 0 ? letter[0] : -1;
            *reinterpret_cast<int*>(object->m_localBase[2] + dstOffs) = letter != 0 ? letter[1] : -1;
            *reinterpret_cast<int*>(object->m_localBase[3] + dstOffs) = letter != 0 ? letter[2] : -1;
            *reinterpret_cast<int*>(object->m_localBase[4] + dstOffs) = letter != 0 ? letter[3] : -1;
            if (letter == 0) {
                *reinterpret_cast<int*>(object->m_localBase[13] + dstOffs) = -1;
            } else {
                int letterIndex =
                    (reinterpret_cast<int>(letter) - static_cast<int>(Game.unkCFlatData0[3])) / 0x3E;
                *reinterpret_cast<int*>(object->m_localBase[13] + dstOffs) = letterIndex;
            }
        }

        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xBF:
        if (object->m_localBase[2] == 0) {
            MapMng.ShowMapObjID(*object->m_localBase, object->m_localBase[1]);
        } else {
            MapMng.ShowMapObjChildID(*object->m_localBase, object->m_localBase[1]);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC0: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[0],
            localFloats[1],
            localFloats[2]);
        _GXColor color = {
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            static_cast<u8>(object->m_localBase[5]),
            static_cast<u8>(object->m_localBase[6]),
        };
        CharaPcs.SetTexShadowPos(position);
        CharaPcs.SetTexShadowColor(color);
        CharaPcs.SetTexShadowRadius(localFloats[7]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xC1:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].GetFoodRank(object->m_localBase[1]));
        outResult = 0;
        return;
    case -0xC2:
        Game.m_caravanWorkArr[*object->m_localBase].m_progressValue =
            static_cast<unsigned short>(object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC3:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_progressValue);
        outResult = 0;
        return;
    case -0xC4:
        GXSetDispCopyGamma(static_cast<_GXGamma>(object->m_localBase[0]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC5: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector position(
            localFloats[4],
            localFloats[5],
            localFloats[6]);
        _GXColor color = {
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF,
        };
        MapMng.SetMapObjWorldMapLightID(*object->m_localBase, color, position);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xC6:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 72) = *object->m_localBase;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 88) = 0x40;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 96) = object->m_localBase[1];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 100) = object->m_localBase[2];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 104) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 100);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 108) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 100);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC7:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 76) = *object->m_localBase;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 80) = object->m_localBase[1];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 84) = object->m_localBase[2];
        if (object->m_localBase[3] < *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 104)) {
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 92) = 0x10;
        }
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&MenuPcs) + 104) = object->m_localBase[3];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC8:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatCancelWaveAsyncFmt));
        }
        Sound.CancelLoadWaveASync();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xC9: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        int mapObjIndex = MapMng.GetMapObjIdx(static_cast<unsigned short>(*object->m_localBase));
        MapMng.SetMapObjTransRate(
            mapObjIndex, localFloats[1], localFloats[2], localFloats[3]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xCA: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        Vec position = {
            localFloats[1],
            localFloats[2],
            localFloats[3],
        };
        runtime->push(
            object,
            Sound.PlaySe3D(
                *object->m_localBase, &position, localFloats[4], localFloats[5], object->m_localBase[6]));
        outResult = 0;
        return;
    }
    case -0xCB:
        CameraPcs.SetShadowAuto(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xCC:
        MenuPcs.LoadExtraFont(*object->m_localBase, strBlob + strOffs[object->m_localBase[1]]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xCD:
        gCFlatRuntime().ClearParmanent();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xCE:
        gameWork.ClearEvtWork();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xCF:
        Game.m_caravanWorkArr[*object->m_localBase].ClearEvtWork();
        runtime->push(object, 0);
        outResult = 0;
        return;
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
        int* outIds = reinterpret_cast<int*>(object->m_localBase[8]);
        for (int i = 0; i < foundCount; i++) {
            outIds[i] = reinterpret_cast<CFlatRuntime::CObject*>(foundObjects[i])->m_particleId;
        }

        runtime->push(object, foundCount);
        outResult = 0;
        return;
    }
    case -0xD1:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatCrossPlayBgmFmt), *object->m_localBase);
        }
        Sound.CrossPlayBgm(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xD2: {
        char* savedNextScript = reinterpret_cast<char*>(reinterpret_cast<u8*>(this) + 0x15CC);
        if (*object->m_localBase == 0) {
            CGame::CNextScript nextScript;
            nextScript.m_flags = 0;
            strcpy(nextScript.m_name, savedNextScript);
            Game.SetNextScript(&nextScript);
        } else {
            memset(savedNextScript, 0, 0x100);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xD3:
        if (object->m_localBase[1] == 0) {
            MapMng.SetMeshCameraSemiTransAlpha(static_cast<unsigned short>(*object->m_localBase), 0, 0x3C);
        } else {
            MapMng.SetMeshCameraSemiTransAlpha(static_cast<unsigned short>(*object->m_localBase), 0x80, 0x3C);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xD4:
        if (*object->m_localBase == 0) {
            MapMng.SetDrawRangeMapObj(*reinterpret_cast<float*>(object->m_localBase + 1));
        } else {
            MapMng.SetDrawRangeOctTree(*reinterpret_cast<float*>(object->m_localBase + 1));
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xD5:
        this->loadLayer(*object->m_localBase, strBlob + strOffs[object->m_localBase[1]]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xD6: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        _GXColor color = {
            static_cast<u8>(255.0f * localFloats[10]),
            static_cast<u8>(255.0f * localFloats[10]),
            static_cast<u8>(255.0f * localFloats[10]),
            static_cast<u8>(255.0f * localFloats[11]),
        };
        this->drawLayer(
            *object->m_localBase, strBlob + strOffs[object->m_localBase[1]], object->m_localBase[2],
            object->m_localBase[3], object->m_localBase[4], object->m_localBase[5],
            static_cast<short>(object->m_localBase[6]), static_cast<short>(object->m_localBase[7]),
            localFloats[8], localFloats[9], &color,
            object->m_localBase[12]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xD7:
        this->loadLayerASync(*object->m_localBase, strBlob + strOffs[object->m_localBase[1]]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xD8:
        runtime->push(object, this->isLoadLayerASyncCompleted(*object->m_localBase));
        outResult = 0;
        return;
    case -0xD9:
        runtime->push(object, 1);
        outResult = 0;
        return;
    case -0xDA:
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xDB:
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xDC: {
        u8* base = reinterpret_cast<u8*>(Game.unkCFlatData0[3]);
        runtime->push(
            object, *reinterpret_cast<u16*>(base + *object->m_localBase * 0x3E + object->m_localBase[1] * 2));
        outResult = 0;
        return;
    }
    case -0xDD:
        Sound.FadeOutSe(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xDE:
        this->SysControl(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xDF:
        if (*object->m_localBase == 1) {
            if (object->m_localBase[1] == 0) {
                PartPcs.EndMiruraEvent();
            } else {
                PartPcs.StartMiruraEvent();
            }
        } else if (*object->m_localBase == 0) {
            if (object->m_localBase[1] == 0) {
                PartPcs.EndLocationTitle();
            } else {
                PartPcs.StartLocationTitle();
            }
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xE0:
        MapMng.SetMapObjPrioID(*object->m_localBase, static_cast<unsigned char>(object->m_localBase[1]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xE1:
        runtime->push(object, MiniGamePcs.GetMiniGameParam(*object->m_localBase));
        outResult = 0;
        return;
    case -0xE2:
        MiniGamePcs.SetMiniGameParam(*object->m_localBase, object->m_localBase[1]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xE3: {
        unsigned int flags = 0;
        if ((object->m_localBase[1] & 2) != 0) {
            const int itemIndex = Game.m_caravanWorkArr[object->m_localBase[0]].FindItem(object->m_localBase[2]);
            flags = (0xffffffffU - (itemIndex >> 31)) & 2;
        }
        runtime->push(object, flags);
        outResult = 0;
        return;
    }
    case -0xE4:
        if (object->m_localBase[1] == 1) {
            Game.m_caravanWorkArr[object->m_localBase[0]].DeleteItem(object->m_localBase[2], 1);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xE5:
        runtime->push(object, Game.m_caravanWorkArr[*object->m_localBase].m_gil);
        outResult = 0;
        return;
    case -0xE6:
        runtime->push(object, static_cast<unsigned int>(Game.m_caravanWorkArr[*object->m_localBase].m_inventoryItemCount));
        outResult = 0;
        return;
    case -0xE7:
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0x68) = *object->m_localBase;
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CharaPcs) + 0x72) =
            *reinterpret_cast<float*>(object->m_localBase + 1);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xE8: {
        _GXColor color = {
            static_cast<u8>(object->m_localBase[1]),
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            0xFF,
        };
        MenuPcs.SetExtraFontTlut(*object->m_localBase, color);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xE9:
        if (*object->m_localBase == 0) {
            _GXTexObj backTexObj;
            _GXColor color = { 0xFF, 0xFF, 0xFF, static_cast<u8>(object->m_localBase[1]) };

            GXInitTexObj(
                &backTexObj, static_cast<unsigned char*>(Graphic.m_scratchTextureBuffer), 0x280, 0x1C0, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP,
                GX_FALSE);
            GXInitTexObjLOD(&backTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            gUtil.RenderTextureQuad(
                0.0f, 0.0f, 640.0f, 448.0f, &backTexObj, 0, 0, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        } else {
            _GXTexObj backTexObj;
            Graphic.GetBackBufferRect2(
                Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 0x280, 0x1C0, 0, GX_NEAR, GX_TF_RGBA8, 0);
        }
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xEA:
        CharaPcs.SetSpecularAlpha(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xEB:
        CGPartyObj::SetBonusCondition(
            *object->m_localBase, object->m_localBase[1], object->m_localBase[2], object->m_localBase[3],
            object->m_localBase[4]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xEC: {
        const int padType = Joybus.GetPadType(*object->m_localBase);
        runtime->push(object, (static_cast<unsigned int>(__cntlzw(0x40000 - padType)) >> 5) & 0xFF);
        outResult = 0;
        return;
    }
    case -0xED: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        CVector hitPosition(
            localFloats[0],
            localFloats[1],
            localFloats[2]);
        Vec cylinderTop = { 0.0f, 1.0f, 0.0f };
        if (MapPcs.CheckHitCylinderNear(hitPosition, &cylinderTop, static_cast<float>(0.0f), object->m_localBase[3]) == 0) {
            runtime->push(object, 0);
        } else {
            MapPcs.CalcHitPosition(hitPosition);
            *reinterpret_cast<float*>(object->m_localBase[4]) = hitPosition.y;
            runtime->push(object, 1);
        }
        outResult = 0;
        return;
    }
    case -0xEE: {
        const float* localFloats = reinterpret_cast<float*>(object->m_localBase);
        AStar.addAstar(
            localFloats[0],
            localFloats[1],
            localFloats[2],
            object->m_localBase[3],
            object->m_localBase[4]);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xEF:
        AStar.calcAStar();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF0: {
        runtime->push(
            object,
            *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x12F4 + *object->m_localBase * 8) &
                static_cast<unsigned int>(1ULL << object->m_localBase[1]));
        outResult = 0;
        return;
    }
    case -0xF1:
        this->resetSpawnBit(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF2:
        MapMng.SetMapAnimID(static_cast<char>(object->m_localBase[0]), object->m_localBase[1],
            object->m_localBase[2], static_cast<char>(object->m_localBase[3]));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF3:
        runtime->push(object, this->GetSysControl(*object->m_localBase));
        outResult = 0;
        return;
    case -0xF4:
        PartPcs.pppSetDebugHide(static_cast<unsigned char>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF5:
        Sound.SeMaxVolume(*object->m_localBase);
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF6:
        Game.m_caravanWorkArr[*object->m_localBase].m_gil = object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF7: {
        _GXColor color = {
            static_cast<u8>(object->m_localBase[2]),
            static_cast<u8>(object->m_localBase[3]),
            static_cast<u8>(object->m_localBase[4]),
            static_cast<u8>(object->m_localBase[5]),
        };
        MenuPcs.GetFont22()->SetTlutColor(*object->m_localBase, 0xB, color);
        MenuPcs.GetFont22()->FlushTlutColor();
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    case -0xF8:
        if (GetNumMes__9CFlatDataFv(&System) > 2) {
            System.Printf(const_cast<char*>(s_cflatAddNoFreeSeGroupFmt), *object->m_localBase);
        }
        Sound.AddNoFreeSeGroup(static_cast<short>(*object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xF9:
        CameraPcs.SetFullScreenShadowCamLen(*reinterpret_cast<float*>(object->m_localBase));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xFA:
        CGItemObj::ItemJump(*object->m_localBase, *reinterpret_cast<float*>(object->m_localBase + 1));
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xFB:
        Game.SetNextScriptNewGame();
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xFC:
        *reinterpret_cast<int*>(reinterpret_cast<char*>(&DbgMenuPcs) + 0x10844) = *object->m_localBase;
        *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&DbgMenuPcs) + 0x10848) =
            object->m_localBase[1];
        runtime->push(object, 0);
        outResult = 0;
        return;
    case -0xFD: {
        const double stickX = Pad.GetLeftStickX(*object->m_localBase);
        const double stickY = Pad.GetLeftStickY(*object->m_localBase);
        *reinterpret_cast<float*>(object->m_localBase[1]) = static_cast<float>(stickX);
        *reinterpret_cast<float*>(object->m_localBase[2]) = static_cast<float>(stickY);
        runtime->push(object, 0);
        outResult = 0;
        return;
    }
    default:
        return;
    }
}

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
    u8* game = reinterpret_cast<u8*>(&Game);
    CGame::CGameWork& gameWork = Game.m_gameWork;

    if (systemValue <= -0x1000) {
        int valueIndex = -0x1000 - systemValue;
        unsigned int result = 0;
        int valueGroup = valueIndex / 0x600;
        const unsigned short* row =
            reinterpret_cast<const unsigned short*>(Game.unkCFlatData0[2]) +
            (0x5FF - (valueIndex - valueGroup * 0x600)) * 0x24;

        switch (valueGroup) {
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
        int byteIndex = bitIndex / 8 + 8;
        unsigned int mask = 1U << (bitIndex % 8);
        unsigned int flag = static_cast<unsigned int>(static_cast<unsigned char>(gameWork.m_eventFlags[byteIndex])) & mask;
        FlatLastResult(this) = (flag | -flag) >> 31;
    } else if (systemValue <= -200) {
        short* artifact = gameWork.m_eventWork + systemValue + 0x1C7;
        FlatLastResult(this) = static_cast<unsigned int>(static_cast<int>(*artifact));
    } else {
        switch (systemValue) {
        case -0x40:
            FlatLastResult(this) = gameWork.m_scriptSysVal0;
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
            FlatLastResult(this) = *reinterpret_cast<unsigned int*>(gameWork.m_linkTable[0][2][2] + systemValue * 4 + 4);
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
            FlatLastResult(this) = *reinterpret_cast<unsigned int*>(gameWork.m_linkTable[0][3][4] + systemValue * 4);
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
            FlatLastResult(this) = *reinterpret_cast<unsigned int*>(gameWork.m_linkTable[0][5][3] + systemValue * 4);
            break;
        case -0x66:
            FlatLastResult(this) = gameWork.m_chaliceElement;
            break;
        case -0x6B:
        case -0x6A:
        case -0x69:
        case -0x68:
        case -0x67:
            FlatLastResult(this) = *reinterpret_cast<unsigned int*>(gameWork.m_eventWork + systemValue * 2 + 0x50);
            break;
        case -0x73:
        case -0x72:
        case -0x71:
        case -0x70:
        case -0x6F:
        case -0x6E:
        case -0x6D:
        case -0x6C: {
            u8* usbEdit = game + (systemValue + 0x73) * 0xC30;
            if (*(int*)(usbEdit + 0x1794) == 0) {
                FlatLastResult(this) = 0;
            } else {
                FlatLastResult(this) = *(unsigned short*)(usbEdit + 0x1404);
            }
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
            if (gameWork.m_languageId == 3) {
                languageValue = 6;
            } else if (gameWork.m_languageId < 3) {
                if (gameWork.m_languageId == 1) {
                    languageValue = 3;
                } else if (gameWork.m_languageId == 0) {
                    languageValue = 1;
                } else {
                    languageValue = 5;
                }
            } else if (gameWork.m_languageId == 5) {
                languageValue = 7;
            } else if (gameWork.m_languageId < 5) {
                languageValue = 4;
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
void CFlatRuntime2::onSetSystemVal(int systemValue, CFlatRuntime::CStack* stack, int setMode)
{
    CGame::CGameWork& gameWork = Game.m_gameWork;
    if (systemValue > -0x1000) {
        if (systemValue <= -500) {
            int bitIndex = systemValue + 0x9F3;
            unsigned char* flagByte = reinterpret_cast<unsigned char*>(gameWork.m_eventFlags) + bitIndex / 8;
            unsigned int mask = 1U << (bitIndex % 8);
            unsigned int flag = *flagByte & mask;
            unsigned int value = (flag | -flag) >> 31;
            stack[-1].m_word = value;

            if (setMode == 0) {
                value = stack->m_word;
            } else if (setMode < 0) {
                if (setMode >= -1) {
                    value = value - stack->m_word;
                }
            } else if (setMode < 2) {
                value = value + stack->m_word;
            }

            if (value != 0) {
                *flagByte |= mask;
            } else {
                *flagByte &= ~mask;
            }
        } else if (systemValue <= -200) {
            short* artifact = gameWork.m_eventWork + systemValue + 0x1C7;
            stack[-1].m_word = *artifact;
            if (setMode == 0) {
                *artifact = static_cast<short>(stack->m_word);
            } else if (setMode < 0) {
                if (setMode >= -1) {
                    *artifact = static_cast<short>(*artifact - static_cast<short>(stack->m_word));
                }
            } else if (setMode < 2) {
                *artifact = static_cast<short>(*artifact + static_cast<short>(stack->m_word));
            }
        } else {
            switch (systemValue) {
            case -0x40:
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0);
                if (setMode == 0) {
                    *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0) = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0) =
                            *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0) - stack->m_word;
                    }
                } else if (setMode < 2) {
                    *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0) =
                        *reinterpret_cast<unsigned int*>(&gameWork.m_scriptSysVal0) + stack->m_word;
                }
                break;
            case -0x41:
                stack[-1].m_word = gameWork.m_timerA;
                if (setMode == 0) {
                    gameWork.m_timerA = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_timerA = gameWork.m_timerA - stack->m_word;
                    }
                } else if (setMode < 2) {
                    gameWork.m_timerA = gameWork.m_timerA + stack->m_word;
                }
                break;
            case -0x42:
                stack[-1].m_word = gameWork.m_scriptGlobalTime;
                if (setMode == 0) {
                    gameWork.m_scriptGlobalTime = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_scriptGlobalTime = gameWork.m_scriptGlobalTime - stack->m_word;
                    }
                } else if (setMode < 2) {
                    gameWork.m_scriptGlobalTime = gameWork.m_scriptGlobalTime + stack->m_word;
                }
                break;
            case -0x43:
                stack[-1].m_word = gameWork.m_frameCounter;
                if (setMode == 0) {
                    gameWork.m_frameCounter = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_frameCounter = gameWork.m_frameCounter - stack->m_word;
                    }
                } else if (setMode < 2) {
                    gameWork.m_frameCounter = gameWork.m_frameCounter + stack->m_word;
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
                unsigned char* value = gameWork.m_linkTable[0][3][4] + systemValue * 4;
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(value);
                if (setMode == 0) {
                    *reinterpret_cast<unsigned int*>(value) = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        *reinterpret_cast<unsigned int*>(value) = *value - stack->m_word;
                    }
                } else if (setMode < 2) {
                    *reinterpret_cast<unsigned int*>(value) = *value + stack->m_word;
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
                unsigned char* value = gameWork.m_linkTable[0][5][3] + systemValue * 4;
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(value);
                if (setMode == 0) {
                    *reinterpret_cast<unsigned int*>(value) = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        *reinterpret_cast<unsigned int*>(value) =
                            *reinterpret_cast<int*>(value) - stack->m_word;
                    }
                } else if (setMode < 2) {
                    *reinterpret_cast<unsigned int*>(value) =
                        *reinterpret_cast<int*>(value) + stack->m_word;
                }
                break;
            }
            case -0x66:
                stack[-1].m_word = gameWork.m_chaliceElement;
                if (setMode == 0) {
                    gameWork.m_chaliceElement = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_chaliceElement = gameWork.m_chaliceElement - stack->m_word;
                    }
                } else if (setMode < 2) {
                    gameWork.m_chaliceElement = gameWork.m_chaliceElement + stack->m_word;
                }
                break;
            case -0x6B:
            case -0x6A:
            case -0x69:
            case -0x68:
            case -0x67: {
                int* value = reinterpret_cast<int*>(gameWork.m_eventWork + systemValue * 2 + 0x50);
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(value);
                if (setMode == 0) {
                    *reinterpret_cast<unsigned int*>(value) = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        *reinterpret_cast<unsigned int*>(value) =
                            *reinterpret_cast<int*>(value) - stack->m_word;
                    }
                } else if (setMode < 2) {
                    *reinterpret_cast<unsigned int*>(value) =
                        *reinterpret_cast<int*>(value) + stack->m_word;
                }
                break;
            }
            case -0x47:
            case -0x46:
            case -0x45:
            case -0x44: {
                unsigned char* value = gameWork.m_linkTable[0][2][2] + systemValue * 4 + 4;
                stack[-1].m_word = *reinterpret_cast<unsigned int*>(value);
                if (setMode == 0) {
                    *reinterpret_cast<unsigned int*>(value) = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        *reinterpret_cast<unsigned int*>(value) =
                            *reinterpret_cast<int*>(value) - stack->m_word;
                    }
                } else if (setMode < 2) {
                    *reinterpret_cast<unsigned int*>(value) =
                        *reinterpret_cast<int*>(value) + stack->m_word;
                }
                break;
            }
            case -0x75:
                stack[-1].m_word = static_cast<int>(gameWork.m_bossArtifactStageIndex);
                if (setMode == 0) {
                    gameWork.m_bossArtifactStageIndex = static_cast<short>(stack->m_word);
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_bossArtifactStageIndex =
                            static_cast<short>(gameWork.m_bossArtifactStageIndex - static_cast<short>(stack->m_word));
                    }
                } else if (setMode < 2) {
                    gameWork.m_bossArtifactStageIndex =
                        static_cast<short>(gameWork.m_bossArtifactStageIndex + static_cast<short>(stack->m_word));
                }
                break;
            case -0x76: {
                unsigned int value = static_cast<unsigned int>(gameWork.m_menuStageMode);
                stack[-1].m_word = value;
                if (setMode == 0) {
                    value = stack->m_word;
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        value = value - stack->m_word;
                    }
                } else if (setMode < 2) {
                    value = value + stack->m_word;
                }
                MenuPcs.ChgPlayModeFromScript(static_cast<bool>((value | -value) >> 31));
                break;
            }
            case -0x77:
                stack[-1].m_word = static_cast<unsigned int>(gameWork.m_soundOptionFlag);
                if (setMode == 0) {
                    gameWork.m_soundOptionFlag = static_cast<unsigned char>(stack->m_word);
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_soundOptionFlag =
                            static_cast<unsigned char>(gameWork.m_soundOptionFlag - static_cast<char>(stack->m_word));
                    }
                } else if (setMode < 2) {
                    gameWork.m_soundOptionFlag =
                        static_cast<unsigned char>(gameWork.m_soundOptionFlag + static_cast<char>(stack->m_word));
                }
                break;
            case -0x79:
                stack[-1].m_word = static_cast<int>(static_cast<short>(gameWork.m_optionValue));
                if (setMode == 0) {
                    gameWork.m_optionValue = static_cast<unsigned short>(stack->m_word);
                } else if (setMode < 0) {
                    if (setMode >= -1) {
                        gameWork.m_optionValue =
                            static_cast<unsigned short>(gameWork.m_optionValue - static_cast<short>(stack->m_word));
                    }
                } else if (setMode < 2) {
                    gameWork.m_optionValue =
                        static_cast<unsigned short>(gameWork.m_optionValue + static_cast<short>(stack->m_word));
                }
                break;
            default:
                break;
            }
        }
    }
}
