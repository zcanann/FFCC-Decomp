#ifndef _FFCC_PPP_WMM_STR_H_
#define _FFCC_PPP_WMM_STR_H_

class CFont;

class CMenuPcs
{
public:
    const char* GetMcStr(int);
    const char* const* GetMcWinMessBuff(int);
    const char* GetWinMess(int);
    int GetYesNoXPos(int);
    int GetSlotABXPos(int);

    char pad_00[0xF8];
    CFont* menuFont;
    char pad_fc[0x74C];
    short* singWindowInfo;
};

#endif // _FFCC_PPP_WMM_STR_H_
