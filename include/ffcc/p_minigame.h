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
    CMiniGamePcs();

    void GetTable(unsigned long);

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
    void SetNumPlayer();
};

#endif // _FFCC_P_MINIGAME_H_
