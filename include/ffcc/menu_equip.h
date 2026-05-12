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
};

#endif // _FFCC_MENU_EQUIP_H_
