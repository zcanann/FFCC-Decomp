#ifndef _GOOUT_H_
#define _GOOUT_H_

#include "ffcc/memorycard.h"
#include "ffcc/p_menu.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"

class CGoOutMenu;
class CCaravanWork;
class McCtrl;

extern CMenuPcs MenuPcs;
extern CGoOutMenu g_GoOutMenu;
extern CGoOutMenu* g_pGoOutMenu;

int getFreeCaravanIdx(Mc::SaveDat*);
void CalcGoOutMenu();
void DrawGoOutMenu();

class CGoOutMenu
{
    friend void DrawGoOutMenu();

public:
    void CharaSelClose();
    void SetMemCardSlot(int, int);
    void SetMemCardProc(unsigned char);
    void SetMemCardSaveBuff(void*);
    void GetMemCardResult();
    void CalcMemCardProc();
    unsigned char SetMemCardError();
    void SetMenu(short, long);
    void SetMenuStr(long, int, ...);
    void CalcMenu();
    void DrawMenu();
    void SetMenuForceClose();
    void CalcLoadMenu();
    void SetMainMode(unsigned char);
    void SelectYesNo(int, int, int);
    void InitSelectYesNo();
    void HitAnyKey();
    void HitCanncel();
    void Init();
    void Destroy();
    void SetGoOutMode(unsigned char);
    void CalcGoOut();
    void DrawGoOut();
    void SetDelMode(unsigned char);
    void CalcDel();
    void DrawDel();
    void Calc();
    void DrawSelectYesNo();
    void Draw();
    void InitMemCardProc();
    void EndMemCardProc();

private:
    unsigned char m_lastMemCardProc;
    char m_memCardProc;
    char m_cardChannel;
    char m_saveIndex;
    int m_memCardResult;
    void* m_memCardBuffer;
    int m_accessCardChannel;
    int m_accessSaveIndex;
    char unk_0x14;
    char unk_0x15[3];
    char m_goOutMode;
    char m_returnGoOutMode;
    char m_odekakeCardChannel;
    char m_odekakeSaveIndex;
    unsigned char m_watchCardDisconnect;
    unsigned char m_saveLoadMenuOpen;
    unsigned char m_returnTransfer;
    char unk_0x1f;
    int m_selectedTransferChara;
    signed char m_deleteMode;
    signed char m_prevDeleteMode;
    unsigned char m_deleteInitSelChar;
    char unk_0x27;
    int m_selectedChara;
    char m_mainMode;
    char m_nextMainMode;
    unsigned int m_modeFrame;
    short m_pendingMessage;
    short m_currentMessage;
    short m_menuStringSlot;
    int m_pendingMessageTimer;
    int m_messageTimer;
    unsigned char m_messageState;
    unsigned char m_messageWindowOpen;
    unsigned char m_cursorChoice;
    unsigned char m_drawCursor;
    unsigned char m_messageCloseMode;
    unsigned char m_cursorMode;
    short m_cursorListY0;
    short m_cursorListY1;
};

#endif // _GOOUT_H_
