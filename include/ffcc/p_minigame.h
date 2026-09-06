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
unsigned long CalcCrc(unsigned long);
void AdjustGbaImageRegistry(char*, char*);
void _OpenCallback(MgGbaThreadParam*, void*);
void getKoubutsuList(unsigned char*, int);
void GbaThreadAlarmHandler(OSAlarm*, OSContext*);
void GbaThreadSleep(long long);
void GbaThreadReadInitialCode(MgGbaThreadParam*);
void _GbaThreadMain(void*);
void _MngThreadMain(void*);

struct MgGbaContext
{
    u8 m_initialConnect;
    u8 m_channel;
    u8 m_portId;
    u8 m_initialized;
    unsigned int m_sessionId;
    unsigned int m_tick;
    int m_transferId;
    u8 m_managerMode;
    u8 m_playerMask;
    u8 m_pad12[2];
    u8 m_foodLevels[4][16];
    u8 m_pad54[12];
};

class MgGbaThreadParam
{
public:
    OSMessageQueue m_queue;
    OSMessage m_message;
    void (*m_openCallback)(MgGbaThreadParam*, void*);
    MgGbaContext m_context;
    unsigned int m_lastTick;
    unsigned char* m_image;
    unsigned int m_imageSize;
    unsigned int m_deviceType;
    unsigned int m_lastProbeResult;
    int m_imageType;
    unsigned int m_receivedPacket;
    unsigned int m_identity;
    unsigned int m_sendPackets[5];
    s8 m_channel;
    u8 m_busy;
    u8 m_stopRequested;
    u8 m_result;
    u8 m_status;
    u8 m_padC1;
    u8 m_transferComplete;
    u8 m_identityReceived;
    u8 m_connected;
    u8 m_connectionReady;
    u8 m_connectionReset;
    u8 m_bootRetries;
};

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
    OSThread m_managerThread; // 0x8
    OSMessageQueue m_managerQueue; // 0x320
    OSMessage m_managerMessage; // 0x340
    u8 m_managerStack[0x1000]; // 0x344
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
    unsigned long m_managerImageSize; // 0x1358
    unsigned char* m_managerSpImage; // 0x135C
    unsigned long m_managerSpImageSize; // 0x1360
    unsigned int m_sessionId; // 0x1364
    unsigned int m_receivedWords[4]; // 0x1368
    unsigned int m_broadcastWords[5]; // 0x1378
    MgGbaThreadParam m_gbaParams[4]; // 0x138C
    MgGbaContext m_gbaContexts[4]; // 0x16AC
    OSThread m_gbaThreads[4]; // 0x1830
    u8 m_work2490[0x6484 - 0x2490];

public:
    unsigned int m_flags; // 0x6484

private:
    u8 m_work6488[8];
    u8 m_playerMessageReady[4]; // 0x6490
    unsigned char m_miniGameReady; // 0x6494
    unsigned char m_miniGameFailed; // 0x6495
    u8 m_raceEnded; // 0x6496
    u8 m_continueRequested; // 0x6497
    signed char m_miniGameParams[4]; // 0x6498
    unsigned char m_managerThreadStop; // 0x649C
    u8 m_workerStoppedMask; // 0x649D
    u8 m_pad649E[2];
};

extern CMiniGamePcs MiniGamePcs;

#endif // _FFCC_P_MINIGAME_H_
