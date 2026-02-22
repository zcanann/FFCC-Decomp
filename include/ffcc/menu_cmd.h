#ifndef _FFCC_MENU_CMD_H_
#define _FFCC_MENU_CMD_H_

bool IsMagicArti(int);

class CMenuPcs
{
public:
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
    void UniteOpenAnim(int);
    int UniteCloseAnim(int);
    void CmdOpen1();
    unsigned int CmdClose1();
    void CmdOpen2();
    void CmdClose2();
    const char* GetSkillStr(int);
    void GetFontItem();
};

#endif // _FFCC_MENU_CMD_H_
