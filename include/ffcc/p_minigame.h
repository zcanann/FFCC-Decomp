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
    static CProcessTable m_table;

    CMiniGamePcs();

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
    u8 m_work[0x1340];
    char m_managerTag[4]; // 0x1344
    unsigned char m_managerState; // 0x1348
    u8 m_work1349;
    unsigned char m_managerMode; // 0x134A
    unsigned char m_playerMask; // 0x134B
    unsigned char m_playerCount; // 0x134C
    u8 m_work134D;
    unsigned short m_statusCode; // 0x134E
    unsigned char m_managerIndex; // 0x1350
    u8 m_work1351[3];
    unsigned char* m_managerImage; // 0x1354
    unsigned int m_managerImageSize; // 0x1358
    unsigned char* m_managerSpImage; // 0x135C
    unsigned int m_managerSpImageSize; // 0x1360
    u8 m_work1364[0x6484 - 0x1364];

public:
    unsigned int m_flags; // 0x6484

private:
    u8 m_work6488[0x6494 - 0x6488];
    unsigned char m_miniGameReady; // 0x6494
    unsigned char m_miniGameFailed; // 0x6495
    u8 m_work6496[2];
    signed char m_miniGameParams[4]; // 0x6498
    unsigned char m_managerThreadStop; // 0x649C
    u8 m_work649D[3];
};

extern CMiniGamePcs MiniGamePcs;

#endif // _FFCC_P_MINIGAME_H_
