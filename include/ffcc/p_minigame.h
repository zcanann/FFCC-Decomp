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

extern unsigned int m_table_desc0__12CMiniGamePcs[];
extern unsigned int m_table_desc1__12CMiniGamePcs[];
extern unsigned int m_table_desc2__12CMiniGamePcs[];
extern unsigned char m_table__12CMiniGamePcs[];

class CMiniGamePcs : public CProcess
{
public:
    CMiniGamePcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(m_table__12CMiniGamePcs);
        table[1] = m_table_desc0__12CMiniGamePcs[0];
        table[2] = m_table_desc0__12CMiniGamePcs[1];
        table[3] = m_table_desc0__12CMiniGamePcs[2];
        table[4] = m_table_desc1__12CMiniGamePcs[0];
        table[5] = m_table_desc1__12CMiniGamePcs[1];
        table[6] = m_table_desc1__12CMiniGamePcs[2];
        table[7] = m_table_desc2__12CMiniGamePcs[0];
        table[8] = m_table_desc2__12CMiniGamePcs[1];
        table[9] = m_table_desc2__12CMiniGamePcs[2];
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
};

extern CMiniGamePcs MiniGamePcs;

#endif // _FFCC_P_MINIGAME_H_
