#ifndef _FFCC_MENU_CMD_H_
#define _FFCC_MENU_CMD_H_

#include <dolphin/gx.h>

bool IsMagicArti(int);

class CFont;

class CMenuPcs
{
public:
    enum FMT
    {
        TODO_FMT
    };

    enum TEX
    {
        TODO_TEX
    };

    void DrawInit();
    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
    void DrawSingleIcon(int, int, int, float, int, float);
    float CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    void DrawCursor(int, int, float);
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);

    void CmdInit();
    void CmdInit0();
    void CmdInit1();
    void CmdInit2();
    void CmdOpen();
    void CmdCtrl();
    int CmdClose();
    void CmdDraw();
    unsigned int CmdCtrlCur();
    unsigned int CmdOpen0();
    unsigned int CmdClose0();
    void GetCmdItem();
    void ChkCmdActive(int);
    int ChkUnite(int, int (*)[2]);
    void CmdUnite(int, int);
    void CmdDismantle(int);
    void DrawUniteList();
    int UniteOpenAnim(int);
    int UniteCloseAnim(int);
    unsigned int CmdOpen1();
    unsigned int CmdClose1();
    void CmdOpen2();
    unsigned int CmdClose2();
    const char* GetSkillStr(int);
    void GetFontItem();
    int GetItemType(int, int);
    unsigned char GetItemIcon(int);
    int EquipChk(int);
    char* GetMenuStr(int);
};

#endif // _FFCC_MENU_CMD_H_
