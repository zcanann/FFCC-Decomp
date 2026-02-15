#ifndef _GOOUT_H_
#define _GOOUT_H_

#include "ffcc/memorycard.h"
#include "ffcc/p_menu.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"

class CGoOutMenu;
class CCaravanWork;
class McCtrl;

extern CMenuPcs MenuPcs;

void getFreeCaravanIdx(Mc::SaveDat*);
void CalcGoOutMenu();
void DrawGoOutMenu();

class CGoOutMenu
{
public:
    void CharaSelClose();
    void SetMemCardSlot(int, int);
    void SetMemCardProc(unsigned char);
    void SetMemCardSaveBuff(void*);
    void GetMemCardResult();
    void CalcMemCardProc();
    int SetMemCardError();
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
    char field_0x1;
    char field_0x2;
    char field_0x3;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    char field_0x18;
    char field_0x19;
    char field_0x1a;
    char field_0x1b;
    char field_0x1c;
    char field_0x1d;
    char field_0x1e;
    char field_0x1f;
    int field_0x20;
    char field_0x24;
    char field_0x25;
    char field_0x26;
    char field_0x27;
    int field_0x28;
    char field_0x2c;
    char field_0x2d;
    int field_0x30;
    short field_0x34;
    short field_0x36;
    short field_0x38;
    int field_0x3c;
    int field_0x40;
    char field_0x44;
    char field_0x45;
    char field_0x46;
    char field_0x47;
    char field_0x48;
    char field_0x49;
    short field74_0x4a;
    short field75_0x4c;
};

#endif // _GOOUT_H_
