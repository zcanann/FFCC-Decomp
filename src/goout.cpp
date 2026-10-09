#include "ffcc/goout.h"
#include "ffcc/memory.h"
#include "ffcc/wm_menu.h"
#include <stdarg.h>
#include <string.h>

#ifdef VERSION_GCCJGC
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"
#endif

CGoOutMenu g_GoOutMenu;
CGoOutMenu* g_pGoOutMenu;
int g_freeCaravanIdx;

#ifdef VERSION_GCCJGC
static const int kTransferWindowBase = 50;
static const int kTransferMessageBase = 100;
static const int kTransferMessageGroup = 0;
static const int kConfirmationDefault = 0;
static const int kTransferSaveMessage = 44;
static const int kTransferCompleteMessage = 45;
static const int kTransferCheckMessage = 46;
static const int kTransferInitializedIds = 16;
static const int kTransferSaveAllocLine = 0x319;
static const int kTransferWorkAllocLine = 0x31B;
#else
static const int kTransferWindowBase = 34;
static const int kTransferMessageBase = 0;
static const int kTransferMessageGroup = 2;
static const int kConfirmationDefault = 1;
static const int kTransferSaveMessage = 31;
static const int kTransferCompleteMessage = 32;
static const int kTransferCheckMessage = 33;
static const int kTransferInitializedIds = 8;
static const int kTransferSaveAllocLine = 0x32B;
static const int kTransferWorkAllocLine = 0x32D;
#endif

#ifndef VERSION_GCCJGC
#ifdef VERSION_GCCE01
#include "src/goout_str_data_us.inc"
#else
#include "src/goout_str_data.inc"
#endif
#endif

struct GoOutMenuState
{
    unsigned char unk0[0x18];
    signed short m_waitFrames;
    signed short unk1A;
    signed short m_closeMode;
    signed short m_resultDir;
    signed short m_resultSelect;
    signed short m_animFrame;
};

struct CGoOutSaveCaravan
{
    int m_dataPresent;
    unsigned char unk4[0x308];
    unsigned char m_odekakeOutFlag;
    unsigned char m_odekakeReturnFlag;
    unsigned char unk30E[0x6B2];
};

struct CGoOutSaveDatLayout
{
    unsigned char unk0[0x1A84];
    CGoOutSaveCaravan m_caravan[8];
};


static inline GoOutMenuState& MenuGoOutState()
{
    return *MenuPcs.m_goOutState;
}

#ifndef VERSION_GCCJGC
static inline const char* GetGoOutMessageLine(int languageId, int line)
{
    return g_strGooutMes[(languageId * 0x6E) + line];
}

#endif

static const char s_gooutCpp[] = "goout.cpp";

static inline CGoOutSaveDatLayout& GoOutSaveDat(Mc::SaveDat* saveData)
{
    return *reinterpret_cast<CGoOutSaveDatLayout*>(saveData);
}

static inline int FindFreeCaravanIdx(Mc::SaveDat* saveData)
{
    for (int i = 0; i < 8; i++) {
        if (GoOutSaveDat(saveData).m_caravan[i].m_dataPresent == 0) {
            return i;
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int getFreeCaravanIdx(Mc::SaveDat* saveData)
{
    g_freeCaravanIdx = FindFreeCaravanIdx(saveData);
    return g_freeCaravanIdx;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CharaSelClose()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::SetMemCardSlot(int cardChannel, int saveIndex)
{
    m_cardChannel = cardChannel;
    m_saveIndex = saveIndex;
    MenuPcs.m_mcCtrl.m_cardChannel = cardChannel;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardProc(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardSaveBuff(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::GetMemCardResult()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcMemCardProc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8016C564
 * PAL Size: 1156b
 * EN Address: 0x8016B4EC
 * EN Size: 1156b
 * JP Address: 0x801668A8
 * JP Size: 1108b
 */
unsigned char CGoOutMenu::SetMemCardError()
{
    switch (m_memCardResult) {
    case 1:
        return 0;
    case -2:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 2;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -999:
        if (m_lastMemCardProc == 1) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 5,
                       "\203\130\203\215\203\142\203\147\202\140\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\202\315",
                       "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\202\240\202\350\202\334\202\271\202\361\201\102",
                       "",
                       "\203\130\203\215\203\142\203\147\202\140\202\311\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\223\374\202\301\202\275",
                       "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\202\263\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
#endif
            break;
        } else if (m_lastMemCardProc == 3) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = 0xd;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
            break;
        } else if (m_lastMemCardProc == 2) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = 0xf;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
            break;
        }
        // fall through
    case -1:
    case -3:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -4:
        if (m_lastMemCardProc == 1) {
            goto setLoadFailedMessage;
        }
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x13;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -5:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 3;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -13:
    case -6:
        SetGoOutMode(3);
        return 1;
    case -1000:
        if (m_lastMemCardProc == 1) {
        setLoadFailedMessage:
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 5,
                       "\203\130\203\215\203\142\203\147\202\140\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\202\315",
                       "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\202\240\202\350\202\334\202\271\202\361\201\102",
                       "",
                       "\203\130\203\215\203\142\203\147\202\140\202\311\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\223\374\202\301\202\275",
                       "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\202\263\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
#endif
        }
        break;
    }

    m_goOutMode = 2;
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenu(short message, long timer)
{
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageState = 1;
    m_messageWindowOpen = 0;
    m_pendingMessage = message;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = static_cast<int>(timer);
}

/*
 * --INFO--
 * PAL Address: 0x8016C40C
 * PAL Size: 344b
 * EN Address: 0x8016B394
 * EN Size: 344b
 * JP Address: 0x80166760
 * JP Size: 328b
 */
void CGoOutMenu::SetMenuStr(long timer, int lineCount, ...)
{
    va_list args;
    int i;
    int indexBase;
    WinMessEntry* winMessage;
    const char** winMessageBuffer;
    short messageIndex;

    m_menuStringSlot ^= 1;
#ifdef VERSION_GCCJGC
    winMessage = MenuPcs.GetWinMess(0);
    winMessage += m_menuStringSlot;
    winMessage[kTransferWindowBase].m_lineCount = lineCount;
#else
    winMessage = MenuPcs.GetWinMess(m_menuStringSlot + kTransferWindowBase);
    winMessage->m_lineCount = lineCount;
#endif

    if (m_menuStringSlot == 0) {
        indexBase = kTransferMessageBase;
    } else {
        indexBase = kTransferMessageBase + 10;
    }
    va_start(args, lineCount);
    winMessageBuffer = (const char**)MenuPcs.GetMcWinMessBuff(kTransferMessageGroup);
    for (i = 0; i < lineCount; i++) {
#ifdef VERSION_GCCJGC
        winMessageBuffer[indexBase++] = va_arg(args, const char*);
#else
        winMessageBuffer[indexBase + i] = va_arg(args, const char*);
#endif
    }
    va_end(args);

    messageIndex = m_menuStringSlot + kTransferWindowBase;
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageWindowOpen = 0;
    m_pendingMessage = messageIndex;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = timer;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::CalcMenu()
{
    if (MenuPcs.m_menuWindowInfo->state == 1) {
        m_messageState = 1;
        m_messageWindowOpen = 1;
    }

    if (m_messageState != 0 && MenuPcs.m_menuWindowInfo->state == 3) {
        short x;
        short y;

        m_currentMessage = m_pendingMessage;
        if (m_pendingMessage != -1) {
            MenuPcs.GetWinSize(static_cast<unsigned short>(m_currentMessage), &x, &y,
                               (m_currentMessage >= 0x1E) ? kTransferMessageGroup : 0);
            MenuPcs.SetMcWinInfo(x, y);
            MenuPcs.m_menuWindowInfo->state = 0;
            MenuGoOutState().m_animFrame = 0;
            m_messageTimer = m_pendingMessageTimer;
            m_messageState = 0;
        }
    }

    if (m_messageTimer != 0) {
        m_messageTimer--;
        if (m_messageTimer == 0) {
            SetMenuForceClose();
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::DrawMenu()
{
    if (m_currentMessage != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuPcs.m_menuWindowInfo->state == 1) {
            const unsigned int message = static_cast<unsigned int>(m_currentMessage);
#ifdef VERSION_GCCJGC
            MenuPcs.DrawMcWinMess(message, kTransferMessageGroup);
#else
            MenuPcs.DrawMcWinMess(message, (m_currentMessage < 0x1E) ? 0 : 2);
#endif
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuForceClose()
{
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageWindowOpen = 0;
    m_pendingMessage = -1;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::CalcLoadMenu()
{
    CalcMenu();
}

/*
 * --INFO--
 * PAL Address: 0x8016C1A4
 * PAL Size: 616b
 * EN Address: 0x8016B12C
 * EN Size: 616b
 * JP Address: 0x8016653C
 * JP Size: 548b
 */
void CGoOutMenu::SetMainMode(unsigned char mode)
{
    unsigned char prevMainMode;
    int i;

    {
        MenuPcs.m_goOutSaveLoadMode = 0;
        MenuPcs.m_goOutUnknown88A = 0;
        MenuPcs.m_goOutTransferWorkActive = 0;
    }
    if (m_mainMode == '\x02') {
        MemoryCardMan.McEnd();
    }
    prevMainMode = m_mainMode;
    m_mainMode = mode;
    m_modeFrame = 0;
    switch (mode) {
    case 1: {
        m_cursorChoice = kConfirmationDefault;
#ifdef VERSION_GCCJGC
        if (prevMainMode == 3U) {
            m_cursorChoice = 1;
        }
#else
        if (prevMainMode != 3U) {
            m_cursorChoice = 0;
        }
#endif
        MenuPcs.ChgAllModel();
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x1e;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        unk_0x14 = 0;
        break;
    }
    case 2:
        if (static_cast<signed char>(Game.m_gameWork.m_mcHasSerial) != 1) {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 4,
                       "\202\334\202\276\210\352\223\170\202\340\203\132\201\133\203\165\202\263\202\352\202\304\202\242\202\334\202\271\202\361\201\102",
                       "",
                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\311\202\315\203\132\201\133\203\165\203\146\201\133\203\136\202\252\225\113\227\166\202\310\202\314\202\305\201\101",
                       "\220\346\202\311\214\273\215\335\202\314\203\146\201\133\203\136\202\360\203\132\201\133\203\165\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 5),
                       GetGoOutMessageLine(languageId, 6),
                       GetGoOutMessageLine(languageId, 7),
                       GetGoOutMessageLine(languageId, 8));
#endif
            m_returnGoOutMode = (char)0xff;
            m_goOutMode = 0;
        }
        i = 0;
        do {
            if (Game.m_caravanWorkArr[i].m_shopState != 0 &&
                static_cast<signed char>(Game.m_caravanWorkArr[i].unk_0xc1e) != 1) {
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 5,
                           "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311\201\101",
                           "\202\334\202\276\203\132\201\133\203\165\202\263\202\352\202\304\202\242\202\310\202\242\203\114\203\203\203\211\203\116\203\136\201\133\202\252\202\242\202\334\202\267\201\102",
                           "",
                           "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\311\202\315\203\132\201\133\203\165\203\146\201\133\203\136\202\252\225\113\227\166\202\310\202\314\202\305\201\101",
                           "\220\346\202\311\214\273\215\335\202\314\203\146\201\133\203\136\202\360\203\132\201\133\203\165\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 9),
                           GetGoOutMessageLine(languageId, 10),
                           GetGoOutMessageLine(languageId, 11),
                           GetGoOutMessageLine(languageId, 12),
                           GetGoOutMessageLine(languageId, 13));
#endif
                m_returnGoOutMode = (char)0xff;
                m_goOutMode = 0;
            }
            i++;
        } while (i < 8);
        m_memCardProc = 0;
        m_lastMemCardProc = 0;
        m_cardChannel = 0;
        m_saveIndex = 0;
        m_memCardResult = -1;
        m_memCardBuffer = 0;
        SetGoOutMode(7);
        break;
    case 3: {
        MenuPcs.ChgAllModel();
        MenuPcs.m_goOutUnknown888 = 2;
        unk_0x14 = 0;
        m_deleteInitSelChar = 0;
        SetDelMode(2);
        break;
    }
    }
}

#ifdef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 232b
 * EN Address: UNUSED
 * EN Size: 272b
 * JP Address: UNUSED
 * JP Size: TODO
 */
void dumpOdekake(Mc::SaveDat* saveData)
{
    for (int i = 0; i < 8; i++) {
        const CGoOutSaveCaravan& caravan = GoOutSaveDat(saveData).m_caravan[i];
        System.Printf("pc=%d  use=%d:  odekake=%d  Guest=%d\n", i,
                      caravan.m_dataPresent, caravan.m_odekakeOutFlag,
                      caravan.m_odekakeReturnFlag);
    }
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 584b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned char CGoOutMenu::SelectYesNo(int cursorX, int cursorY, int cursorMode)
{
    m_drawCursor = 1;
    m_cursorX = cursorX;
    m_cursorY = cursorY;
    m_cursorMode = cursorMode;

#ifndef VERSION_GCCJGC
    if (MenuPcs.m_menuWindowInfo->state != 1) {
        return 0;
    }

#endif

    if ((Pad.GetButtonDown(0) & (cursorMode ? 0xC : 3)) != 0) {
        m_cursorChoice ^= 1;
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        if (cursorMode || m_cursorChoice == 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
        } else if (m_cursorChoice == 1) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
        }
        return m_cursorChoice + 1;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitSelectYesNo()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline bool CGoOutMenu::HitAnyKey()
{
    if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        Sound.PlaySe(2, 0x40, 0x7f, 0);
        return true;
    }

    return false;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline bool CGoOutMenu::HitCanncel()
{
    if ((Pad.GetButtonDown(0) & 0x200) != 0) {
        Sound.PlaySe(3, 0x40, 0x7f, 0);
        return true;
    }

    return false;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::Init()
{
    memset(this, 0, sizeof(*this));
    m_memCardResult = -1;
    m_returnGoOutMode = -1;
    m_pendingMessage = -1;
    m_currentMessage = -1;
    m_menuStringSlot = 0;
    m_messageState = 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::Destroy()
{
    if (MenuPcs.m_goOutTransferSaveData != 0) {
        delete reinterpret_cast<unsigned char*>(MenuPcs.m_goOutTransferSaveData);
        MenuPcs.m_goOutTransferSaveData = 0;
    }
    if (MenuPcs.m_goOutTransferWork != 0) {
        delete static_cast<unsigned char*>(MenuPcs.m_goOutTransferWork);
        MenuPcs.m_goOutTransferWork = 0;
    }

    MenuPcs.m_goOutTransferWorkActive = 0;
    MenuPcs.m_goOutUnknown888 = 0;
    MenuPcs.m_goOutSaveLoadMode = 0;
    MenuPcs.m_goOutUnknown88A = 0;

    if (m_mainMode == 2) {
        MemoryCardMan.McEnd();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8016B8D4
 * PAL Size: 2256b
 * EN Address: 0x8016A85C
 * EN Size: 2256b
 * JP Address: 0x80165D4C
 * JP Size: 2032b
 */
void CGoOutMenu::SetGoOutMode(unsigned char mode)
{

	m_goOutMode = mode;
	switch(m_goOutMode) {
    case 7:
        MenuPcs.m_goOutUnknown888 = 1;
        unk_0x14 = 0;
        m_goOutMode = 7;
        m_watchCardDisconnect = 0;
        m_saveLoadMenuOpen = 0;
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 7,
                       "\203\130\203\215\203\142\203\147\202\140\202\311\201\101\214\273\215\335\203\166\203\214\203\103\222\206\202\314",
                       "\203\146\201\133\203\136\202\252\202\240\202\351\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\201\101",
                       "\203\130\203\215\203\142\203\147\202\141\202\311\201\101\210\332\223\256\202\263\202\271\202\351\203\114\203\203\203\211\203\116\203\136\201\133\202\314",
                       "\203\146\201\133\203\136\202\252\202\240\202\351\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\202\263\202\265\202\304\202\255\202\276\202\263\202\242\201\102",
                       "",
                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\202\250\202\261\202\310\202\301\202\304\202\242\202\351\212\324\202\315",
                       "\202\307\202\277\202\347\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\340\224\262\202\251\202\310\202\242\202\305\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 7,
                       GetGoOutMessageLine(languageId, 14),
                       GetGoOutMessageLine(languageId, 15),
                       GetGoOutMessageLine(languageId, 16),
                       GetGoOutMessageLine(languageId, 17),
                       GetGoOutMessageLine(languageId, 18),
                       GetGoOutMessageLine(languageId, 19),
                       GetGoOutMessageLine(languageId, 20));
#endif
        }
        break;
	case 1:
		m_watchCardDisconnect = 0;
        MenuGoOutState().m_resultDir = -1;
        MenuGoOutState().m_waitFrames = 10;
		break;
    case 0xC:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = kTransferCheckMessage;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        MenuPcs.GetMcAccessPos(&m_accessCardChannel, &m_accessSaveIndex);
        m_accessCardChannel = 0;
        {
        const int cardChannel = m_accessCardChannel;
        MenuPcs.m_mcCtrl.m_cardChannel = cardChannel;
        const int saveIndex = m_accessSaveIndex;
        m_cardChannel = static_cast<char>(cardChannel);
        m_saveIndex = static_cast<char>(saveIndex);
        MenuPcs.m_mcCtrl.m_cardChannel = cardChannel;
        }
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 1;
        }
        break;
    case 0xE:
        MenuPcs.InitSaveLoadMenu();
        MenuPcs.CalcGoOutSelCharInit();
        MenuPcs.CopyNowCaravanDat(MenuPcs.m_goOutTransferSaveData);
        MenuPcs.m_goOutSaveLoadMode = 2;
        MenuPcs.m_goOutUnknown88A = 1;
        MenuPcs.m_goOutTransferWorkActive = MenuPcs.m_goOutTransferWork;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case 0xF:
        MenuPcs.ChgAllModel2();
        if (m_saveLoadMenuOpen == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        MenuPcs.CalcGoOutSelCharInit();
        m_saveLoadMenuOpen = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        MenuPcs.m_goOutSaveLoadMode = 2;
        MenuPcs.m_goOutUnknown88A = 1;
        MenuPcs.m_goOutTransferWorkActive = MenuPcs.m_goOutTransferWork;
        break;
    case 0x10:
        if (m_returnTransfer == 0) {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 5,
                       "\221\111\202\361\202\276\203\114\203\203\203\211\203\116\203\136\201\133\202\360\201\101",
                       "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311",
                       "\210\332\223\256\202\265\202\304\202\340\202\346\202\353\202\265\202\242\202\305\202\267\202\251\201\110",
                       "\201\151\214\263\202\311\226\337\202\267\202\334\202\305\216\147\227\160\202\305\202\253\202\334\202\271\202\361\201\152",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 21),
                       GetGoOutMessageLine(languageId, 22),
                       GetGoOutMessageLine(languageId, 23),
                       GetGoOutMessageLine(languageId, 24),
                       GetGoOutMessageLine(languageId, 25));
#endif
        } else {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 5,
                       "\221\111\202\361\202\276\203\114\203\203\203\211\203\116\203\136\201\133\202\360\201\101",
                       "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311",
                       "\226\337\202\265\202\304\202\340\202\346\202\353\202\265\202\242\202\305\202\267\202\251\201\110",
                       "\201\151\201\165\203\121\203\130\203\147\201\166\202\252\202\355\202\314\203\146\201\133\203\136\202\251\202\347\215\355\217\234\202\265\202\334\202\267\201\152",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 26),
                       GetGoOutMessageLine(languageId, 27),
                       GetGoOutMessageLine(languageId, 28),
                       GetGoOutMessageLine(languageId, 29),
                       GetGoOutMessageLine(languageId, 30));
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        break;
    case 0x11:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = kTransferSaveMessage;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        m_cursorChoice = kConfirmationDefault;
        break;
    case 0x12: {
        m_watchCardDisconnect = 0;
        const int selectedChara = m_selectedTransferChara;
        int freeCaravanIdx;

        if (GoOutSaveDat(static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)).m_caravan[selectedChara].m_odekakeReturnFlag == 0) {
            freeCaravanIdx = FindFreeCaravanIdx(MenuPcs.m_goOutTransferSaveData);
            MemoryCardMan.Odekake(1, *static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), selectedChara, *MenuPcs.m_goOutTransferSaveData, freeCaravanIdx);
        } else {
            freeCaravanIdx = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), selectedChara, 0);
            MemoryCardMan.Odekake(0, *static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), m_selectedTransferChara, *MenuPcs.m_goOutTransferSaveData, freeCaravanIdx);
        }

        SetMemCardSlot(m_accessCardChannel, m_accessSaveIndex);
        m_memCardBuffer = MenuPcs.m_goOutTransferSaveData;
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 2;
        }
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 4,
                       "\203\130\203\215\203\142\203\147\202\140\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311",
                       "\203\132\201\133\203\165\222\206\202\305\202\267\201\102",
                       "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\342\203\160\203\217\201\133\203\173\203\136\203\223\202\311",
                       "\202\263\202\355\202\347\202\310\202\242\202\305\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 31),
                       GetGoOutMessageLine(languageId, 32),
                       GetGoOutMessageLine(languageId, 33),
                       GetGoOutMessageLine(languageId, 34));
#endif
        }
        break;
    }
    case 0x13:
    {
        const char odekakeSaveIndex = m_odekakeSaveIndex;
        const unsigned char odekakeCardChannel = static_cast<unsigned char>(m_odekakeCardChannel);
        m_cardChannel = odekakeCardChannel;
        m_saveIndex = odekakeSaveIndex;
        MenuPcs.m_mcCtrl.m_cardChannel = odekakeCardChannel;
    }
        m_memCardBuffer = MenuPcs.m_goOutTransferWork;
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 2;
        }
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 4,
                       "\203\130\203\215\203\142\203\147\202\141\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311",
                       "\203\132\201\133\203\165\222\206\202\305\202\267\201\102",
                       "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\342\203\160\203\217\201\133\203\173\203\136\203\223\202\311",
                       "\202\263\202\355\202\347\202\310\202\242\202\305\202\255\202\276\202\263\202\242\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 35),
                       GetGoOutMessageLine(languageId, 36),
                       GetGoOutMessageLine(languageId, 37),
                       GetGoOutMessageLine(languageId, 38));
#endif
        }
        break;
    case 0x14:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = kTransferCompleteMessage;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
	case 3:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
		m_messageWindowOpen = 0;
		m_pendingMessage = 4;
		m_messageCloseMode = 0;
		m_pendingMessageTimer = 0;
		m_cursorChoice = kConfirmationDefault;
		break;
	case 4:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
		m_messageWindowOpen = 0;
		m_pendingMessage = 5;
		m_messageCloseMode = 0;
		m_pendingMessageTimer = 0;
		m_cursorChoice = kConfirmationDefault;
		break;
    case 5:
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 3;
        }
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 7;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case 6:
#ifndef VERSION_GCCJGC
        if (MenuPcs.m_menuWindowInfo->state == 1) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
        }
#endif
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0xc;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        m_cursorChoice = kConfirmationDefault;
        break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8016A06C
 * PAL Size: 6248b
 * EN Address: 0x80169014
 * EN Size: 6216b
 * JP Address: 0x80164700
 * JP Size: 5708b
 */
void CGoOutMenu::CalcGoOut()
{
    if (m_watchCardDisconnect != 0 && m_modeFrame >= 0x14 && (m_modeFrame & 0xF) == 0) {
        if ((m_modeFrame & 0x10) != 0) {
            if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == 1) {
                goto card_connected;
            }
        card_disconnected:
            m_watchCardDisconnect = 0;
            m_returnGoOutMode = -1;
            m_goOutMode = 0;
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            {
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 5,
                           "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\252\224\262\202\251\202\352\202\275\202\314\202\305\201\101",
                           "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\222\206\216\176\202\265\202\334\202\267\201\102",
                           "",
                           "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\202\265\202\304\202\242\202\351\212\324\202\315",
                           "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\224\262\202\251\202\310\202\242\202\305\202\255\202\276\202\263\202\242\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 39),
                           GetGoOutMessageLine(languageId, 40),
                           GetGoOutMessageLine(languageId, 41),
                           GetGoOutMessageLine(languageId, 42),
                           GetGoOutMessageLine(languageId, 43));
#endif
            }
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) != 1) {
            goto card_disconnected;
        }
    }
card_connected:;

    int selResult = -1;
    if (m_saveLoadMenuOpen != 0) {
        const unsigned char selInit = static_cast<unsigned char>(__cntlzw(0xF - static_cast<int>(m_goOutMode)) >> 5 & 0xFF);
        selResult = MenuPcs.CalcGoOutSelChar(selInit, 1);
    }

    switch (m_goOutMode) {
    case 0:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitAnyKey()) {
            if (m_returnGoOutMode == -1) {
                SetMainMode(1);
            } else {
                SetGoOutMode(m_returnGoOutMode);
            }
        }
        break;
    case 2:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitAnyKey()) {
            SetMainMode(1);
        }
        break;
    case 7:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitAnyKey()) {
            SetGoOutMode(8);
        }
        break;
    case 8:
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == -1) {
            return;
        }
        m_modeFrame = 0;
        SetGoOutMode(9);
        break;
    case 9:
        if (m_modeFrame < 0x14) {
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == -3) {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 2,
                       "\203\130\203\215\203\142\203\147\202\140\202\311\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\252",
                       "\202\263\202\263\202\301\202\304\202\242\202\334\202\271\202\361\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 44),
                       GetGoOutMessageLine(languageId, 45));
#endif
            m_returnGoOutMode = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xC);
        break;
    case 0xC:
        if (m_memCardResult != 0) {
            if (SetMemCardError() != 0) {
                return;
            }

            MenuPcs.GetMcAccessPos(&m_accessCardChannel, &m_accessSaveIndex);
            if (m_accessCardChannel == -1) {
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 5,
                           "\203\130\203\215\203\142\203\147\202\140\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\202\315",
                           "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\202\240\202\350\202\334\202\271\202\361\201\102",
                           "",
                           "\203\130\203\215\203\142\203\147\202\140\202\311\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\252\223\374\202\301\202\275",
                           "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\202\263\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 0),
                           GetGoOutMessageLine(languageId, 1),
                           GetGoOutMessageLine(languageId, 2),
                           GetGoOutMessageLine(languageId, 3),
                           GetGoOutMessageLine(languageId, 4));
#endif
                m_returnGoOutMode = -1;
                SetGoOutMode(0);
            } else {
                m_accessCardChannel = 0;
                SetMemCardSlot(m_accessCardChannel, m_accessSaveIndex);
                SetGoOutMode(10);
            }
        }
        break;
    case 10:
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) == -1) {
            return;
        }
        m_modeFrame = 0;
        SetGoOutMode(0xB);
        break;
    case 0xB:
        if (m_modeFrame < 0x14) {
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) == -3) {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 2,
                       "\203\130\203\215\203\142\203\147\202\141\202\311\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\252",
                       "\202\263\202\263\202\301\202\304\202\242\202\334\202\271\202\361\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 46),
                       GetGoOutMessageLine(languageId, 47));
#endif
            m_returnGoOutMode = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xE);
        break;
    case 0xE:
        if (static_cast<char>(MenuPcs.m_goOutLoadFinished) != 0) {
            if (MenuPcs.m_goOutLoadResult == 4) {
                MenuGoOutState().m_resultSelect = 0;
                MenuPcs.InitSaveLoadMenu();
                MenuPcs.CalcGoOutSelCharInit();
                if (MenuPcs.CheckSameMcFormatID(MenuPcs.m_goOutTransferSaveData,
                                                static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)) != 0) {
#ifdef VERSION_GCCJGC
                    SetMenuStr(0, 2,
                               "\202\261\202\314\203\146\201\133\203\136\202\315\201\101\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\251\202\347",
                               "\203\122\203\163\201\133\202\263\202\352\202\275\202\340\202\314\202\310\202\314\202\305\216\147\227\160\202\305\202\253\202\334\202\271\202\361\201\102");
#else
                    int languageId = Game.m_gameWork.GetLanguage() - 1;
                    SetMenuStr(0, 2,
                               GetGoOutMessageLine(languageId, 48),
                               GetGoOutMessageLine(languageId, 49));
#endif
                    m_returnGoOutMode = -1;
                    SetGoOutMode(0);
                    return;
                }

                int odekakeX;
                int odekakeY;
                MenuPcs.GetMcOdekakePos(&odekakeX, &odekakeY);
                m_odekakeCardChannel = static_cast<char>(odekakeX);
                m_odekakeSaveIndex = static_cast<char>(odekakeY);
                SetGoOutMode(0xF);
                m_watchCardDisconnect = 1;
            } else if (MenuPcs.m_goOutLoadResult == 1) {
                SetMainMode(1);
            } else {
                MenuGoOutState().m_resultSelect = 0;
                MenuPcs.InitSaveLoadMenu();
                MenuPcs.CalcGoOutSelCharInit();
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 7,
                           "\203\130\203\215\203\142\203\147\202\141\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\202\315",
                           "\203\164\203\100\203\103\203\151\203\213\203\164\203\100\203\223\203\136\203\127\201\133\201\105\203\116\203\212\203\130\203\136\203\213\203\116\203\215\203\152\203\116\203\213\202\314",
                           "\203\132\201\133\203\165\203\146\201\133\203\136\202\252\202\240\202\350\202\334\202\271\202\361\201\102",
                           "",
                           "\203\130\203\215\203\142\203\147\202\141\202\311",
                           "\203\164\203\100\203\103\203\151\203\213\203\164\203\100\203\223\203\136\203\127\201\133\201\105\203\116\203\212\203\130\203\136\203\213\203\116\203\215\203\152\203\116\203\213\202\314",
                           "\203\132\201\133\203\165\203\146\201\133\203\136\202\314\202\240\202\351\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\360\202\263\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 7,
                           GetGoOutMessageLine(languageId, 50),
                           GetGoOutMessageLine(languageId, 51),
                           GetGoOutMessageLine(languageId, 52),
                           GetGoOutMessageLine(languageId, 53),
                           GetGoOutMessageLine(languageId, 54),
                           GetGoOutMessageLine(languageId, 55),
                           GetGoOutMessageLine(languageId, 56));
#endif
                m_returnGoOutMode = -1;
                SetGoOutMode(0);
            }
        }
        if (m_currentMessage == -1) {
            MenuPcs.CalcLoadMenu();
        }
        break;
    case 0xF:
        m_selectedTransferChara = selResult;
        if (m_selectedTransferChara == -2) {
            SetGoOutMode(1);
            return;
        }
        if (m_selectedTransferChara != -1) {
            if (GoOutSaveDat(static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)).m_caravan[m_selectedTransferChara].m_odekakeOutFlag != 0) {
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 2,
                           "\201\165\202\250\202\305\202\251\202\257\222\206\201\166\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\315",
                           "\210\332\223\256\202\267\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\271\202\361\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 2,
                           GetGoOutMessageLine(languageId, 57),
                           GetGoOutMessageLine(languageId, 58));
#endif
                m_returnGoOutMode = 0xF;
                SetGoOutMode(0);
            } else {
                m_returnTransfer = 0;
                Mc::SaveDat* transferWork = static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork);
                if (GoOutSaveDat(transferWork).m_caravan[m_selectedTransferChara].m_odekakeReturnFlag == 0) {
                    int sameChara = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, transferWork, m_selectedTransferChara, 1);
                    if (sameChara == -3) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
#ifdef VERSION_GCCJGC
                        SetMenuStr(0, 3,
                                   "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311\202\315",
                                   "\202\267\202\305\202\311\223\257\202\266\203\114\203\203\203\211\203\116\203\136\201\133\202\252\202\242\202\351\202\275\202\337\201\101",
                                   "\202\261\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\315\210\332\223\256\202\305\202\253\202\334\202\271\202\361\201\102");
#else
                        int languageId = Game.m_gameWork.GetLanguage() - 1;
                        SetMenuStr(0, 3,
                                   GetGoOutMessageLine(languageId, 59),
                                   GetGoOutMessageLine(languageId, 60),
                                   GetGoOutMessageLine(languageId, 61));
#endif
                        break;
                    }

                    g_freeCaravanIdx = FindFreeCaravanIdx(MenuPcs.m_goOutTransferSaveData);
                    if (g_freeCaravanIdx < 0) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
#ifdef VERSION_GCCJGC
                        SetMenuStr(0, 6,
                                   "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311\202\315",
                                   "\202\267\202\305\202\311\203\114\203\203\203\211\203\116\203\136\201\133\202\252\202\127\220\154\202\242\202\351\202\275\202\337\201\101",
                                   "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\210\332\223\256\202\263\202\271\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\271\202\361\201\102",
                                   "",
                                   "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\202\250\202\261\202\310\202\244\217\352\215\207\202\315\201\101",
                                   "\202\120\220\154\225\252\210\310\217\343\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\314\213\363\202\253\202\252\225\113\227\166\202\305\202\267\201\102");
#else
                        int languageId = Game.m_gameWork.GetLanguage() - 1;
                        SetMenuStr(0, 6,
                                   GetGoOutMessageLine(languageId, 62),
                                   GetGoOutMessageLine(languageId, 63),
                                   GetGoOutMessageLine(languageId, 64),
                                   GetGoOutMessageLine(languageId, 65),
                                   GetGoOutMessageLine(languageId, 66),
                                   GetGoOutMessageLine(languageId, 67));
#endif
                        break;
                    }
                } else {
                    if ((g_freeCaravanIdx = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, transferWork, m_selectedTransferChara, 0)) < 0) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
#ifdef VERSION_GCCJGC
                        SetMenuStr(0, 2,
                                   "\201\165\203\121\203\130\203\147\201\166\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\315",
                                   "\214\263\202\314\203\146\201\133\203\136\210\310\212\117\202\311\202\315\210\332\223\256\202\305\202\253\202\334\202\271\202\361\201\102");
#else
                        int languageId = Game.m_gameWork.GetLanguage() - 1;
                        SetMenuStr(0, 2,
                                   GetGoOutMessageLine(languageId, 68),
                                   GetGoOutMessageLine(languageId, 69));
#endif
                        break;
                    }
                    m_returnTransfer = 1;
                }
                SetGoOutMode(0x10);
            }
        }
        break;
    case 0x10:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitCanncel()) {
            SetGoOutMode(0xf);
            break;
        }

        unsigned char sel;
        if (m_returnTransfer == 0) {
            sel = SelectYesNo(0xb1, 0xdc, 0);
        } else {
            sel = SelectYesNo(0x8b, 0xdc, 0);
        }
        switch (sel) {
        case 1:
            SetGoOutMode(0x11);
            break;
        case 2:
            SetGoOutMode(0xf);
            break;
        }
        break;
    case 0x11:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitCanncel()) {
            SetGoOutMode(0xf);
            break;
        }

        switch (SelectYesNo(0xd3, 0xe9, 0)) {
        case 1:
            SetGoOutMode(0x12);
            break;
        case 2:
            SetGoOutMode(0xf);
            break;
        }
        break;
    case 0x12:
#ifdef VERSION_GCCJGC
        if (m_memCardResult != 0) {
#else
        if (m_messageWindowOpen != 0 && m_memCardResult != 0) {
#endif
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x13);
        }
        break;
    case 0x13:
#ifdef VERSION_GCCJGC
        if (m_memCardResult != 0) {
#else
        if (m_messageWindowOpen != 0 && m_memCardResult != 0) {
#endif
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x14);
        }
        break;
    case 0x14:
        if (m_messageWindowOpen != 0) {
            if (HitAnyKey()) {
                MenuPcs.SetCaravanWork(MenuPcs.m_goOutTransferSaveData);
                MenuPcs.ChgAllModel();
                SetGoOutMode(1);
            }
        }
        break;
    case 3:
        if (m_messageWindowOpen == 0) {
            break;
        }

        switch (SelectYesNo(0xcf, 0xe7, 0)) {
        case 1:
            SetGoOutMode(4);
            break;
        case 2:
            SetMainMode(1);
            break;
        }
        break;
    case 4:
        if (m_messageWindowOpen == 0) {
            break;
        }

        switch (SelectYesNo(0xce, 0xde, 0)) {
        case 1:
            SetGoOutMode(5);
            break;
        case 2:
            SetMainMode(1);
            break;
        }
        break;
    case 5:
#ifdef VERSION_GCCJGC
        if (m_memCardResult == 0) {
#else
        if (m_messageWindowOpen == 0 || m_memCardResult == 0) {
#endif
            break;
        }

        if (SetMemCardError() != 0) {
            return;
        }
        SetGoOutMode(6);
        break;
    case 6:
        if (m_messageWindowOpen == 0) {
            break;
        }

        if (HitAnyKey()) {
            SetMainMode(1);
        }
        break;
    default:
        break;
    }

    switch (static_cast<unsigned char>(m_memCardProc)) {
    case 1:
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkNowData();
        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    case 2:
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->SaveDataBuffer(static_cast<char*>(m_memCardBuffer));
        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    case 3: {
        int formatResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->Format(1);
#if defined(VERSION_GCCP01)
        if (formatResult < 0) {
            MemoryCardMan.m_opDoneFlag = 1;
            MemoryCardMan.m_currentSlot = static_cast<char>(0xff);
        }
#endif

        int result;
        if (formatResult == 0) {
            result = 0;
        } else if (formatResult == 1) {
            result = 1;
        } else if (formatResult == -2) {
            result = -5;
        } else {
            result = -999;
        }
        m_memCardResult = result;

        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::DrawGoOut()
{
    if (m_saveLoadMenuOpen != 0) {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
    }

    switch (m_goOutMode) {
    case 0xE:
        MenuPcs.DrawLoadMenu();
        break;
    case 0xF:
        break;
    }

    if (m_goOutMode == 1 && MenuGoOutState().m_resultSelect != 0) {
        MenuGoOutState().m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState().m_resultSelect = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80169C18
 * PAL Size: 1108b
 * EN Address: 0x80168BC0
 * EN Size: 1108b
 * JP Address: 0x8016438C
 * JP Size: 884b
 */
void CGoOutMenu::SetDelMode(unsigned char mode)
{

    m_deleteMode = mode;
    switch (m_deleteMode) {
    case 2:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        if (m_deleteInitSelChar == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        MenuPcs.CalcGoOutSelCharInit();
        m_deleteInitSelChar = 1;
        break;
    case 1:
        MenuGoOutState().m_resultDir = -1;
        MenuGoOutState().m_waitFrames = 10;
        break;
    case 3: {
        if (Game.m_caravanWorkArr[m_selectedChara].m_caravanLocalFlags == 0) {
            int activeMainCharacterCount = 0;
            for (int i = 0; i < 8; i++) {
                if (Game.m_caravanWorkArr[i].m_shopState != 0 && Game.m_caravanWorkArr[i].m_caravanLocalFlags == 0) {
                    activeMainCharacterCount++;
                }
            }

            if (activeMainCharacterCount <= 1) {
#ifdef VERSION_GCCJGC
                SetMenuStr(0, 4,
                           "\202\261\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\315\215\355\217\234\202\305\202\253\202\334\202\271\202\361\201\102",
                           "",
                           "\203\146\201\133\203\136\202\311\202\315\201\101\203\121\203\130\203\147\202\305\202\315\202\310\202\242\203\114\203\203\203\211\203\116\203\136\201\133\202\252",
                           "\217\355\202\311\202\120\220\154\210\310\217\343\202\242\202\310\202\257\202\352\202\316\202\310\202\350\202\334\202\271\202\361\201\102");
#else
                int languageId = Game.m_gameWork.GetLanguage() - 1;
                SetMenuStr(0, 4,
                           GetGoOutMessageLine(languageId, 70),
                           GetGoOutMessageLine(languageId, 71),
                           GetGoOutMessageLine(languageId, 72),
                           GetGoOutMessageLine(languageId, 73));
#endif
                m_prevDeleteMode = 2;
                SetDelMode(0);
                return;
            }
        }

        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 2,
                       "\202\261\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\265\202\334\202\267\202\251\201\110",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 74),
                       GetGoOutMessageLine(languageId, 75));
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        break;
    }
    case 4:
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 4,
                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\267\202\351\202\306",
                       "\214\263\202\311\226\337\202\267\202\261\202\306\202\315\202\305\202\253\202\334\202\271\202\361\201\102",
                       "\226\173\223\226\202\311\202\346\202\353\202\265\202\242\202\305\202\267\202\251\201\110",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 76),
                       GetGoOutMessageLine(languageId, 77),
                       GetGoOutMessageLine(languageId, 78),
                       GetGoOutMessageLine(languageId, 79));
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        break;
    case 5:
        if (Game.m_caravanWorkArr[m_selectedChara].m_caravanLocalFlags != 0) {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 8,
                       "\201\165\203\121\203\130\203\147\201\166\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\265\202\334\202\265\202\275\201\102",
                       "",
                       "\214\263\202\314\203\146\201\133\203\136\202\314\201\165\202\250\202\305\202\251\202\257\222\206\201\166\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\314",
                       "\203\146\201\133\203\136\202\360\225\234\212\210\202\263\202\271\202\304\202\250\202\242\202\304\202\255\202\276\202\263\202\242\201\102",
                       "",
                       "\201\165\202\250\202\305\202\251\202\257\222\206\201\166\203\114\203\203\203\211\203\116\203\136\201\133\202\314\203\146\201\133\203\136\202\314\225\234\212\210\202\315\201\101",
                       "\201\165\203\114\203\203\203\211\203\116\203\136\201\133\202\314\215\355\217\234\201\166\202\305\201\101\201\165\202\250\202\305\202\251\202\257\222\206\201\166\202\314",
                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\221\111\202\324\202\306\225\234\212\210\202\267\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\267\201\102");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 8,
                       GetGoOutMessageLine(languageId, 80),
                       GetGoOutMessageLine(languageId, 81),
                       GetGoOutMessageLine(languageId, 82),
                       GetGoOutMessageLine(languageId, 83),
                       GetGoOutMessageLine(languageId, 84),
                       GetGoOutMessageLine(languageId, 85),
                       GetGoOutMessageLine(languageId, 86),
                       GetGoOutMessageLine(languageId, 87));
#endif
        } else {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 1, "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\265\202\334\202\265\202\275\201\102");
#else
            const char** mes = &g_strGooutMes[(Game.m_gameWork.GetLanguage() - 1) * 0x6E];
            SetMenuStr(0, 1, mes[88]);
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        MenuPcs.SetMenuCharaAnim(m_selectedChara, 5);
        break;
    case 6:
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 6,
                       "\202\261\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\315",
                       "\201\165\202\250\202\305\202\251\202\257\222\206\201\166\202\314\202\275\202\337\215\355\217\234\202\305\202\253\202\334\202\271\202\361\201\102",
                       "\202\261\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\267\202\351\202\311\202\315\201\101",
                       "\203\146\201\133\203\136\202\360\225\234\212\210\202\263\202\271\202\351\225\113\227\166\202\252\202\240\202\350\202\334\202\267\201\102",
                       "\225\234\212\210\202\263\202\271\202\304\202\346\202\353\202\265\202\242\202\305\202\267\202\251\201\110",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 6,
                       GetGoOutMessageLine(languageId, 89),
                       GetGoOutMessageLine(languageId, 90),
                       GetGoOutMessageLine(languageId, 91),
                       GetGoOutMessageLine(languageId, 92),
                       GetGoOutMessageLine(languageId, 93),
                       GetGoOutMessageLine(languageId, 94));
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        break;
    case 7:
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 5,
                       "\203\146\201\133\203\136\202\360\225\234\212\210\202\263\202\271\202\351\202\306\201\101",
                       "\210\332\223\256\220\346\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\314\203\146\201\133\203\136\202\360",
                       "\202\261\202\261\202\311\226\337\202\267\202\261\202\306\202\252\202\305\202\253\202\310\202\255\202\310\202\350\202\334\202\267\201\102",
                       "\226\173\223\226\202\311\202\346\202\353\202\265\202\242\202\305\202\267\202\251\201\110",
                       "\201\100\202\315\202\242\201\100\201\100\202\242\202\242\202\246");
#else
            int languageId = Game.m_gameWork.GetLanguage() - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 95),
                       GetGoOutMessageLine(languageId, 96),
                       GetGoOutMessageLine(languageId, 97),
                       GetGoOutMessageLine(languageId, 98),
                       GetGoOutMessageLine(languageId, 99));
#endif
        }
        m_cursorChoice = kConfirmationDefault;
        break;
    case 8:
        MenuPcs.SetMenuCharaAnim(m_selectedChara, 3);
        {
#ifdef VERSION_GCCJGC
            SetMenuStr(0, 1, "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\225\234\212\210\202\263\202\271\202\334\202\265\202\275\201\102");
#else
            const char** mes = &g_strGooutMes[(Game.m_gameWork.GetLanguage() - 1) * 0x6E];
            SetMenuStr(0, 1, mes[100]);
#endif
        }
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80168E3C
 * PAL Size: 3548b
 * EN Address: 0x80167DE4
 * EN Size: 3548b
 * JP Address: 0x80163620
 * JP Size: 3436b
 */
void CGoOutMenu::CalcDel()
{
    const unsigned char selInit = static_cast<unsigned char>(__cntlzw(2 - static_cast<int>(m_deleteMode)) >> 5 & 0xFF);
    const int selResult = MenuPcs.CalcGoOutSelChar(selInit, 0);

    switch (m_deleteMode) {
    case 0:
        if (m_messageWindowOpen != 0) {
            if (HitAnyKey()) {
                if (m_prevDeleteMode == -1) {
                    SetMainMode(1);
                } else {
                    SetDelMode(m_prevDeleteMode);
                }
            }
        }
        break;
    case 2:
        m_selectedChara = selResult;
        if (m_selectedChara == -2) {
            SetDelMode(1);
        } else if (m_selectedChara != -1) {
            if (Game.m_caravanWorkArr[m_selectedChara].m_shopBusyFlag != 0) {
                SetDelMode(6);
            } else {
                SetDelMode(3);
            }
        }
        break;
    case 3:
        if (m_messageWindowOpen == 0) {
            return;
        }

        if (HitCanncel()) {
            SetDelMode(2);
        }

        switch (SelectYesNo(0xad, 0xbc, 0)) {
        case 1:
            SetDelMode(4);
            break;
        case 2:
            SetDelMode(2);
            break;
        }
        break;
    case 4:
        if (m_messageWindowOpen == 0) {
            return;
        }

        if (HitCanncel()) {
            SetDelMode(2);
        }

        switch (SelectYesNo(0xc2, 0xd1, 0)) {
        case 1:
            SetDelMode(5);
            break;
        case 2:
            SetDelMode(2);
            break;
        }
        break;
    case 5:
        if (m_messageWindowOpen != 0 && static_cast<int>(MenuPcs.IsMenuCharaAnimIdle(m_selectedChara)) != 0) {
            if (HitAnyKey()) {
                CCaravanWork& caravanWork = Game.m_caravanWorkArr[m_selectedChara];
                caravanWork.m_shopState = 0;
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0x8A4, 0, 0x100);
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0x9A4, 0, 0x200);
                SetDelMode(1);
            }
        }
        break;
    case 6:
        if (m_messageWindowOpen == 0) {
            return;
        }

        if (HitCanncel()) {
            SetDelMode(2);
        }

        switch (SelectYesNo(0x97, 0xe9, 0)) {
        case 1:
            SetDelMode(7);
            break;
        case 2:
            SetDelMode(2);
            break;
        }
        break;
    case 7:
        if (m_messageWindowOpen == 0) {
            return;
        }

        if (HitCanncel()) {
            SetDelMode(2);
        }

        switch (SelectYesNo(0x9f, 0xdb, 0)) {
        case 1:
            Game.m_caravanWorkArr[m_selectedChara].m_shopBusyFlag = 0;
            SetDelMode(8);
            break;
        case 2:
            SetDelMode(2);
            break;
        }
        break;
    case 8:
        if (m_messageWindowOpen != 0 && static_cast<int>(MenuPcs.IsMenuCharaAnimIdle(m_selectedChara)) != 0) {
            if (HitAnyKey()) {
                SetDelMode(1);
            }
        }
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::DrawDel()
{
    MenuPcs.DrawInit();
    MenuPcs.DrawCMakeMenu();
    if (m_deleteMode == 1 && MenuGoOutState().m_resultSelect != 0) {
        MenuGoOutState().m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState().m_resultSelect = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80168400
 * PAL Size: 2620b
 * EN Address: 0x801673A8
 * EN Size: 2620b
 * JP Address: 0x80162C28
 * JP Size: 2552b
 */
void CGoOutMenu::Calc()
{
    unsigned short input;
    unsigned char nextMode;
    char mode;

    m_drawCursor = 0;

    if (MenuPcs.m_goOutReset.m_resetFlag != 0) {
        MenuPcs.m_goOutReset.m_resetFlag = 0;
        MenuPcs.m_menuWindowInfo->state = 3;
        m_currentMessage = -1;
        m_pendingMessage = -1;
        m_menuStringSlot = 0;
        SetMainMode(1);
        MenuPcs.m_goOutTransferSaveData =
            static_cast<Mc::SaveDat*>(operator new(0x8BD0, MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), kTransferSaveAllocLine));
        MenuPcs.m_goOutTransferWork = operator new(0x8BD0, MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), kTransferWorkAllocLine);
        MenuPcs.m_goOutTransferWorkActive = 0;
        MenuPcs.m_goOutUnknown888 = 0;
        MenuPcs.m_goOutSaveLoadMode = 0;
        MenuPcs.m_goOutUnknown88A = 0;
        WinMessEntry* winMessage = MenuPcs.GetWinMess(kTransferWindowBase);
        winMessage->m_lineCount = 0;
        // Japanese retail initializes 16 IDs across adjacent 20-byte descriptors.
        for (int i = 0; i < kTransferInitializedIds; i++) {
            winMessage->m_messageIds[i] = i + kTransferMessageBase;
        }
        winMessage = MenuPcs.GetWinMess(kTransferWindowBase + 1);
        winMessage->m_lineCount = 0;
        for (int i = 0; i < kTransferInitializedIds; i++) {
            winMessage->m_messageIds[i] = i + kTransferMessageBase + 10;
        }
        MenuPcs.m_menuWindowInfo->state = 3;
        m_messageState = 1;
    }

    if (m_messageCloseMode == 0) {
        mode = m_mainMode;
        switch (mode) {
        case 0:
            if (m_messageWindowOpen != 0) {
                if (HitAnyKey()) {
                    SetMainMode(m_nextMainMode);
                }
            }
            break;
        case 1:
            if (m_messageWindowOpen != 0) {
                input = Pad.GetButtonDown(0);
                if ((input & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7f, 0);
                    MenuPcs.InitSaveLoadMenu();
                    MenuPcs.CalcGoOutSelCharInit();
                    MenuGoOutState().m_resultSelect = -1;

                    if (MenuPcs.m_goOutTransferSaveData != 0) {
                        delete reinterpret_cast<unsigned char*>(MenuPcs.m_goOutTransferSaveData);
                        MenuPcs.m_goOutTransferSaveData = 0;
                    }
                    if (MenuPcs.m_goOutTransferWork != 0) {
                        delete static_cast<unsigned char*>(MenuPcs.m_goOutTransferWork);
                        MenuPcs.m_goOutTransferWork = 0;
                    }

                    MenuPcs.m_goOutTransferWorkActive = 0;
                    MenuPcs.m_goOutUnknown888 = 0;
                    MenuPcs.m_goOutSaveLoadMode = 0;
                    MenuPcs.m_goOutUnknown88A = 0;
                    MenuPcs.m_goOutReset.m_resetFlag = 1;
                    MenuPcs.ChgAllModel();
                    return;
                }
                nextMode = SelectYesNo(200, 0xB0, 1);
                switch (nextMode) {
                case 1: {
                    int characterCount = 0;
                    for (int i = 0; i < 8; i++) {
                        if (Game.m_caravanWorkArr[i].m_shopState != 0) {
                            characterCount++;
                        }
                    }

                    if (characterCount <= 0) {
#ifdef VERSION_GCCJGC
                        SetMenuStr(0, 7,
                                   "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\315",
                                   "\202\334\202\276\203\114\203\203\203\211\203\116\203\136\201\133\202\252\215\354\220\254\202\263\202\352\202\304\202\242\202\310\202\242\202\275\202\337\201\101",
                                   "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\210\332\223\256\202\263\202\271\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\271\202\361\201\102",
                                   "",
                                   "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\202\250\202\261\202\310\202\244\221\117\202\311\201\101",
                                   "\202\120\220\154\210\310\217\343\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\354\220\254\202\265\201\101",
                                   "\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\203\132\201\133\203\165\202\265\202\304\202\255\202\276\202\263\202\242\201\102");
#else
                        int languageId = Game.m_gameWork.GetLanguage() - 1;
                        SetMenuStr(0, 7,
                                   GetGoOutMessageLine(languageId, 101),
                                   GetGoOutMessageLine(languageId, 102),
                                   GetGoOutMessageLine(languageId, 103),
                                   GetGoOutMessageLine(languageId, 104),
                                   GetGoOutMessageLine(languageId, 105),
                                   GetGoOutMessageLine(languageId, 106),
                                   GetGoOutMessageLine(languageId, 107));
#endif
                        m_nextMainMode = 1;
                        SetMainMode(0);
                    } else {
                        int transferableCount = 0;
                        for (int i = 0; i < 8; i++) {
                            if (Game.m_caravanWorkArr[i].m_shopState != 0 && Game.m_caravanWorkArr[i].m_shopBusyFlag == 0) {
                                transferableCount++;
                            }
                        }

                        if (transferableCount >= 8) {
#ifdef VERSION_GCCJGC
                            SetMenuStr(0, 6,
                                       "\214\273\215\335\203\166\203\214\203\103\222\206\202\314\203\146\201\133\203\136\202\311\202\315",
                                       "\202\267\202\305\202\311\203\114\203\203\203\211\203\116\203\136\201\133\202\252\202\127\220\154\202\242\202\351\202\275\202\337\201\101",
                                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\210\332\223\256\202\263\202\271\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\271\202\361\201\102",
                                       "",
                                       "\203\114\203\203\203\211\203\116\203\136\201\133\202\314\210\332\223\256\202\360\202\250\202\261\202\310\202\244\217\352\215\207\202\315\201\101",
                                       "\202\120\220\154\225\252\210\310\217\343\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\314\213\363\202\253\202\252\225\113\227\166\202\305\202\267\201\102");
#else
                            int languageId = Game.m_gameWork.GetLanguage() - 1;
                            SetMenuStr(0, 6,
                                       GetGoOutMessageLine(languageId, 62),
                                       GetGoOutMessageLine(languageId, 63),
                                       GetGoOutMessageLine(languageId, 64),
                                       GetGoOutMessageLine(languageId, 65),
                                       GetGoOutMessageLine(languageId, 66),
                                       GetGoOutMessageLine(languageId, 67));
#endif
                            m_nextMainMode = 1;
                            SetMainMode(0);
                        } else {
                            SetMainMode(2);
                        }
                    }
                    break;
                }
                case 2: {
                    int activeCount = 0;
                    for (int i = 0; i < 8; i++) {
                        if (Game.m_caravanWorkArr[i].m_shopState != 0) {
                            activeCount++;
                            if (Game.m_caravanWorkArr[i].m_shopBusyFlag != 0) {
                                activeCount++;
                            }
                        }
                    }

                    if (activeCount >= 2) {
                        SetMainMode(3);
                        if (m_currentMessage >= 0) {
                            MenuPcs.m_menuWindowInfo->state = 2;
                            MenuGoOutState().m_animFrame = 0;
                        }
                        m_messageWindowOpen = 0;
                        m_pendingMessage = -1;
                        m_messageCloseMode = 0;
                        m_pendingMessageTimer = 0;
                    } else {
#ifdef VERSION_GCCJGC
                        SetMenuStr(0, 2,
                                   "\214\273\215\335\202\314\203\146\201\133\203\136\202\251\202\347\202\315",
                                   "\203\114\203\203\203\211\203\116\203\136\201\133\202\360\215\355\217\234\202\305\202\253\202\334\202\271\202\361\201\102");
#else
                        int languageId = Game.m_gameWork.GetLanguage() - 1;
                        SetMenuStr(0, 2,
                                   GetGoOutMessageLine(languageId, 108),
                                   GetGoOutMessageLine(languageId, 109));
#endif
                        m_nextMainMode = 1;
                        SetMainMode(0);
                    }
                    break;
                }
                }
            }
            break;
        case 2:
            CalcGoOut();
            break;
        case 3:
            CalcDel();
            break;
        }

        m_modeFrame = m_modeFrame + 1;
        if (10000 < m_modeFrame) {
            m_modeFrame = 10000;
        }
    }

    if (MenuPcs.m_menuWindowInfo->state == 1) {
        m_messageState = 1;
        m_messageWindowOpen = 1;
    }

    if (m_messageState != 0 && MenuPcs.m_menuWindowInfo->state == 3) {
        short y;
        short x;

        m_currentMessage = m_pendingMessage;
        if (m_pendingMessage != -1) {
            MenuPcs.GetWinSize(static_cast<short>(m_currentMessage), &x, &y,
#ifdef VERSION_GCCJGC
                               kTransferMessageGroup);
#else
                               (m_currentMessage < 0x1E) ? 0 : 2);
#endif
            MenuPcs.SetMcWinInfo(x, y);
            MenuPcs.m_menuWindowInfo->state = 0;
            MenuGoOutState().m_animFrame = 0;
            m_messageTimer = m_pendingMessageTimer;
            m_messageState = 0;
        } else {
            m_messageState = 1;
        }
    }

    if (m_messageTimer != 0) {
        int remaining = m_messageTimer - 1;
        m_messageTimer = remaining;
        if (remaining == 0) {
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = -1;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801683D4
 * PAL Size: 44b
 * EN Address: 0x8016737C
 * EN Size: 44b
 * JP Address: 0x80162BF8
 * JP Size: 48b
 */
void CalcGoOutMenu()
{
    g_pGoOutMenu = &g_GoOutMenu;
    g_pGoOutMenu->Calc();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::DrawSelectYesNo()
{
#ifdef VERSION_GCCJGC
    if (m_drawCursor != 0) {
        if (m_cursorMode != 0) {
            MenuPcs.DrawCursor(m_cursorX, m_cursorY + m_cursorChoice * 24, 1.0f);
        } else {
            MenuPcs.DrawCursor(m_cursorX + m_cursorChoice * 82, m_cursorY, 1.0f);
        }
    }
#elif defined(VERSION_GCCE01)
    if (MenuPcs.m_menuWindowInfo->state == 1 && m_drawCursor != 0) {
        const float cursorY = (float)(MenuPcs.m_menuWindowInfo->y +
            MenuPcs.m_menuWindowInfo->height - 0x3E);

        if (m_cursorMode != 0) {
            MenuPcs.DrawCursor(m_cursorX, m_cursorY + m_cursorChoice * 0x1E, 1.0f);
        } else {
            const int cursorX = MenuPcs.GetYesNoXPos(m_cursorChoice);
            MenuPcs.DrawCursor(cursorX, (int)cursorY, 1.0f);
        }
    }
#else
    if (MenuPcs.m_menuWindowInfo->state == 1 && m_drawCursor != 0) {
        const float cursorY = (float)(MenuPcs.m_menuWindowInfo->y +
            MenuPcs.m_menuWindowInfo->height - 0x3E);
        float cursorX = (float)(MenuPcs.m_menuWindowInfo->x + 0x20);

        if (m_cursorMode != 0) {
            const int localY = m_cursorY + m_cursorChoice * 0x1E;
            MenuPcs.DrawCursor((int)cursorX, localY, 1.0f);
        } else {
            cursorX = (float)MenuPcs.GetYesNoXPos(m_cursorChoice);
            MenuPcs.DrawCursor((int)cursorX, (int)cursorY, 1.0f);
        }
    }
#endif
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::Draw()
{
    switch (m_mainMode) {
    case 2:
        DrawGoOut();
        break;
    case 3:
        DrawDel();
        break;
    }

    DrawMenu();
    DrawSelectYesNo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitMemCardProc()
{
    McCtrl& mcCtrl = *MenuPcs.GetMcCtrl();

    mcCtrl.m_saveIndex = static_cast<unsigned char>(m_saveIndex);
    mcCtrl.m_cardChannel = static_cast<unsigned char>(m_cardChannel);
    mcCtrl.m_previousState = 0;
    mcCtrl.m_state = 0;
    mcCtrl.m_lastResult = 0;
    mcCtrl.m_iteration = 0;
    mcCtrl.m_userBuffer = m_memCardBuffer;
    mcCtrl.m_createFlag = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8018FBE0
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGoOutMenu::EndMemCardProc()
{
    m_memCardProc = 0;
    m_memCardResult = -1;
    MemoryCardMan.McEnd();
}
/*
 * --INFO--
 * PAL Address: 0x80168130
 * PAL Size: 676b
 * EN Address: 0x8016711C
 * EN Size: 608b
 * JP Address: 0x80162A00
 * JP Size: 504b
 */
void DrawGoOutMenu()
{
    g_pGoOutMenu = &g_GoOutMenu;
    g_pGoOutMenu->Draw();
}
