#ifndef _FFCC_PPP_WM_MENU_H_
#define _FFCC_PPP_WM_MENU_H_

#include "ffcc/memorycard.h"
#include "ffcc/p_menu.h"

class CFont;
class CGraphic;
class CCameraPcs;

struct McListInfo
{
    void operator=(const McListInfo&);
};

class McCtrl
{
public:
    McCtrl();
    ~McCtrl();

    void Init();
    void LoadMcList();
    void SetListDat(int, int);
    void SetBrokenFile(int);
    void SaveDat();
    void LoadDat();
    void Format(int);
    void ChkEmpty(int);
    void ChkConnect(int);
    void ChkNowData();
    void SaveDataBuffer(char*);
    void ChkParty(char*);
    void EraseDat();
    void GetDno();
    void GetSerial();
    void SetDataBuff(char*);
    void GetSlot();
    void SetDno(int);
    void SetSlot(int);
};

#endif // _FFCC_PPP_WM_MENU_H_
