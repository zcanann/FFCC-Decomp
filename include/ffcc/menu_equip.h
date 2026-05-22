#ifndef _FFCC_MENU_EQUIP_H_
#define _FFCC_MENU_EQUIP_H_

class CMenuPcs
{
public:
    void EquipInit1();
    int EquipOpen();
    void EquipCtrl();
    int EquipClose();
    void EquipDraw();
    int EquipCtrlCur();
    bool EquipOpen0();
    bool EquipClose0();
    int ChkEquipActive(int);
    int GetItemType(int, int);
    int ChkEquipPossible(int);
    int GetEquipType(int);
    int EquipChk(int);
    void CmdInit1();
    void CmdInit2();
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_MENU_EQUIP_H_
