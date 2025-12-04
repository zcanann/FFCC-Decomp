#ifndef _GOOUT_H_
#define _GOOUT_H_

#include "ffcc/memorycard.h"

class CGoOutMenu;
class CCaravanWork;
class McCtrl;
class CMenuPcs;

void getFreeCaravanIdx(CMemoryCardMan::Mc::SaveDat *);
void CalcGoOutMenu();
void DrawGoOutMenu();

class CGoOutMenu
{
public:
    void CharaSelClose();
    void SetMemCardSlot(int, int);
    void SetMemCardProc(unsigned char);
    void SetMemCardSaveBuff(void *);
    void GetMemCardResult();
    void CalcMemCardProc();
    void SetMemCardError();
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
};

#endif // _GOOUT_H_
