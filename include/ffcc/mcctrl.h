#ifndef _FFCC_MCCTRL_H_
#define _FFCC_MCCTRL_H_

#include "global.h"

class McCtrl
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
    int SaveDataBuffer(char*);
    void ChkParty(char*);
    int EraseDat();
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
    u64 m_serial; // 0x20
};
STATIC_ASSERT(sizeof(McCtrl) == 0x28);
STATIC_ASSERT(offsetof(McCtrl, m_serial) == 0x20);

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline McCtrl::McCtrl()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline McCtrl::~McCtrl()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void McCtrl::Init()
{
    m_previousState = 0;
    m_state = 0;
    m_lastResult = 0;
    m_iteration = 0;
    m_userBuffer = 0;
    m_createFlag = 0;
    m_cardChannel = 0;
    m_saveIndex = 0;
}

#endif // _FFCC_MCCTRL_H_
