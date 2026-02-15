#ifndef _FFCC_MENU_ITEM_H_
#define _FFCC_MENU_ITEM_H_

class CMenuPcs
{
public:
    void ItemInit();
    void ItemInit1();
    bool ItemOpen();
    int ItemCtrl();
    void ItemClose();
    void ItemDraw();
    int ItemCtrlCur();
    void SingLifeInit(int);
};

#endif // _FFCC_MENU_ITEM_H_
