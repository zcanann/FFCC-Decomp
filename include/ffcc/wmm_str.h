#ifndef _FFCC_PPP_WMM_STR_H_
#define _FFCC_PPP_WMM_STR_H_

class CMenuPcs
{
public:
    const char* GetMcStr(int);
    const char* const* GetMcWinMessBuff(int);
    const char* GetWinMess(int);
    void GetYesNoXPos(int);
    void GetSlotABXPos(int);
};

#endif // _FFCC_PPP_WMM_STR_H_
