#ifndef _FFCC_PPP_WM_MENU_H_
#define _FFCC_PPP_WM_MENU_H_

#include "ffcc/memorycard.h"
#include "ffcc/p_menu.h"

class CFont;
class CGraphic;
class CCameraPcs;

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
    int ChkEmpty(int param_2);
    int ChkConnect(int chan);
    int ChkNowData();
    void SaveDataBuffer(char*);
    void ChkParty(char*);
    void EraseDat();
    void GetDno();
    void GetSerial();
    void SetDataBuff(char*);
    void GetSlot();
    void SetDno(int);
    void SetSlot(int);

    int m_previousState;
    int m_state;
    int m_cardChannel;
    int m_lastResult;
    int m_saveIndex;
    int m_iteration;
    int m_createFlag;
    void* m_userBuffer;
    unsigned int m_serialLo;
    unsigned int m_serialHi;	
};

#endif // _FFCC_PPP_WM_MENU_H_
