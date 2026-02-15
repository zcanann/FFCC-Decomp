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
    void EquipCtrlCur();
    void EquipOpen0();
    void EquipClose0();
    void GetEquipItem();
    void ChkEquipActive(int);
};

#endif // _FFCC_MENU_EQUIP_H_
