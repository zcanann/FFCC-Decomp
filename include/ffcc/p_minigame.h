#ifndef _FFCC_P_MINIGAME_H_
#define _FFCC_P_MINIGAME_H_

#include "ffcc/system.h"

#include <dolphin/os.h>

class MgGbaThreadParam;
class OSAlarm;
class OSContext;
class OSThread;

void ChgHL16(unsigned short);
void MiniGameFileRead(char*, void*, unsigned long&);
void CalcCrc(unsigned long);
void AdjustGbaImageRegistry(char*, char*);
void _OpenCallback(MgGbaThreadParam*, void*);
void getKoubutsuList(unsigned char*, int);
void GbaThreadAlarmHandler(OSAlarm*, OSContext*);
void GbaThreadSleep(long long);
void GbaThreadReadInitialCode(MgGbaThreadParam*);
void _GbaThreadMain(void*);
void _MngThreadMain(void*);

class CMiniGamePcs : public CProcess
{
public:
    static unsigned int m_table_desc0[3];
    static unsigned int m_table_desc1[3];
    static unsigned int m_table_desc2[3];
    static CProcessTable m_table;

    CMiniGamePcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(&m_table);
        table[1] = m_table_desc0[0];
        table[2] = m_table_desc0[1];
        table[3] = m_table_desc0[2];
        table[4] = m_table_desc1[0];
        table[5] = m_table_desc1[1];
        table[6] = m_table_desc1[2];
        table[7] = m_table_desc2[0];
        table[8] = m_table_desc2[1];
        table[9] = m_table_desc2[2];
    }

    int GetTable(unsigned long);

    void Init();
    void Quit();

    void create();
    void destroy();

    void MiniGameGo(char*, char*);

    void GbaThreadInitGbaContext(MgGbaThreadParam*, int);
    void GbaThreadWriteInitialCode(MgGbaThreadParam*);
    void GbaThreadReadContext(MgGbaThreadParam*);
    void GbaThreadMain(void*);
    void GbaThreadInit(long, MgGbaThreadParam*, OSThread*, unsigned char*, unsigned long,
                       long, void (*)(MgGbaThreadParam*, void*), unsigned char*, long);

    void OpenCallback(MgGbaThreadParam*, void*);

    void calc();
    void PadCodeProc(int, unsigned short);
    void EndThread();

    void MngThreadMain(void*);
    void MiniGameEnd();

    void CallMiniGameParam(int, int, int);
    int GetMiniGameParam(int);
    void SetMiniGameParam(int, int);
    void SetNumPlayer();

private:
    u8 m_work[0x6480];

public:
    unsigned int m_flags; // 0x6484

private:
    u8 m_work6488[0x649C - 0x6484];
};

extern "C" void create__12CMiniGamePcsFv(CMiniGamePcs*);
extern "C" void destroy__12CMiniGamePcsFv(CMiniGamePcs*);
extern "C" void calc__12CMiniGamePcsFv(CMiniGamePcs*);

extern CMiniGamePcs MiniGamePcs;

#endif // _FFCC_P_MINIGAME_H_
