#ifndef _FFCC_MENU_FAVO_H_
#define _FFCC_MENU_FAVO_H_

class FoodRank
{
public:
    FoodRank& operator=(const FoodRank&);
};

class CMenuPcs
{
public:
    void FavoInit();
    void FavoInit0();
    void FavoOpen();
    void FavoCtrl();
    void FavoClose();
    void FavoDraw();
    void FavoCtrlCur();
};

#endif // _FFCC_MENU_FAVO_H_
