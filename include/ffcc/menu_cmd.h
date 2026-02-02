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
    void CmdCtrlCur();
    void CmdOpen0();
    void CmdClose0();
    void GetCmdItem();
    void ChkCmdActive(int);
    void ChkUnite(int, int (*)[2]);
    void CmdUnite(int, int);
    void CmdDismantle(int);
    void DrawUniteList();
    void UniteOpenAnim(int);
    void UniteCloseAnim(int);
    void CmdOpen1();
    void CmdClose1();
    void CmdOpen2();
    void CmdClose2();
    void GetSkillStr(int);
    void GetFontItem();
};

#endif // _FFCC_MENU_CMD_H_
