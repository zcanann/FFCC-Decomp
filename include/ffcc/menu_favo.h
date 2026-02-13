#ifndef _FFCC_MENU_FAVO_H_
#define _FFCC_MENU_FAVO_H_

class FoodRank
{
public:
};

class CMenuPcs
{
public:
    void FavoInit();
    void FavoInit0();
    bool FavoOpen();
    void FavoCtrl();
    bool FavoClose();
    void FavoDraw();
    void FavoCtrlCur();

    // TODO: These are placeholder field names - actual struct layout unknown
    char pad[0x850];
    int field_0x850;
    char pad2[0x100];
};

#endif // _FFCC_MENU_FAVO_H_
