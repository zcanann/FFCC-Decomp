#ifndef _FFCC_MENU_EQUIP_H_
#define _FFCC_MENU_EQUIP_H_

class CMenuPcs
{
public:
    void EquipInit();
    void EquipInit0();
    void EquipInit1();
    int EquipOpen();
    void EquipCtrl();
    void EquipClose();
    void EquipDraw();
    int EquipCtrlCur();
    int EquipOpen0();
    int EquipClose0();
    void GetEquipItem();
    int ChkEquipActive(int);
};

#endif // _FFCC_MENU_EQUIP_H_
