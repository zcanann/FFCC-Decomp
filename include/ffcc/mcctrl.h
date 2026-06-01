#ifndef _FFCC_MCCTRL_H_
#define _FFCC_MCCTRL_H_

struct McCtrlData
{
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
typedef int McCtrlData_size_mismatch[(sizeof(McCtrlData) == 0x28) ? 1 : -1];

class McCtrl : public McCtrlData
{
public:
    McCtrl();
    ~McCtrl();

    void Init();
    int LoadMcList();
    void SetListDat(int, int);
    void SetBrokenFile(int);
    int SaveDat();
    int LoadDat();
    int Format(int);
    int ChkEmpty(int param_2);
    int ChkConnect(int chan);
    int ChkNowData();
    void SaveDataBuffer(char*);
    void ChkParty(char*);
    int EraseDat();
    void GetDno();
    void GetSerial();
    void SetDataBuff(char*);
    void GetSlot();
    void SetDno(int);
    void SetSlot(int);
};
typedef int McCtrl_size_mismatch[(sizeof(McCtrl) == 0x28) ? 1 : -1];

#endif // _FFCC_MCCTRL_H_
