#ifndef JOYBUS_H
#define JOYBUS_H

#include <Dolphin/os.h>
#include <Dolphin/dvd.h>

typedef unsigned char uchar;
typedef unsigned int uint;

class JoyBus
{
public:
	struct ThreadParam
	{
		unsigned int    m_portIndex;         // 0x00
		unsigned int    m_unk1;              // 0x04
		unsigned int    m_recvWriteIdx;      // 0x08
		unsigned int    m_recvReadIdx;       // 0x0C

		unsigned char   m_deviceType;        // 0x10
		unsigned char   m_padding[3];        // 0x11

		unsigned int    m_gbaStatus;         // 0x14
		unsigned int    m_padType;           // 0x18
		unsigned char   m_unknown1C[4];      // 0x1C

		unsigned char   m_gbaBootFlag;       // 0x20
		unsigned char   m_bootRetryCount;    // 0x21
		unsigned char   m_unk2;              // 0x22
		unsigned char   m_timeChangedFlag;   // 0x23

		unsigned int    m_timestamp;         // 0x24

		unsigned char   m_state;             // 0x28
		unsigned char   m_subState;          // 0x29
		unsigned char   m_prevState;         // 0x2A
		unsigned char   m_altState;          // 0x2B

		unsigned char   m_pposCounter;       // 0x2C
		unsigned char   m_unk3;              // 0x2D
		unsigned char   m_errorRetry;        // 0x2E
		unsigned char   m_counter0x2B;       // 0x2F

		unsigned char   m_skipProcessingFlag; // 0x30
		unsigned char   m_sentStartFlag;      // 0x31
		unsigned char   m_flags[10];          // 0x32
	};
	
	struct JoyBusRecvBuffer
	{
		unsigned int   m_length;      // 0x00
		unsigned int   m_cmdFlags;    // 0x04
		unsigned char  m_payload[1024]; // 0x08
	};



    JoyBus();
    ~JoyBus();

    void Init();
    void CreateInit();
    void Destroy();
    void LoadBin();
    void LoadMap(int, int);

    void Crc16(int, unsigned char*, unsigned short*);

    void BlockSem(int);
    void ReleaseSem(int);

    void ThreadMain(void*);
    static void* _ThreadMain(void*);
    void ThreadInit();
    void ThreadSleep(long long);

    void ReadInitialCode(ThreadParam*);
    void WriteInitialCode(ThreadParam*);
    void ReadContext(ThreadParam*);
    void ReadHostId(ThreadParam*);
    void WriteHostId(ThreadParam*);
    void WriteContext(ThreadParam*);

    void SetPadData(ThreadParam*, unsigned char*);
    void GetPadData(int);

    void RecvGBA(ThreadParam*, unsigned int*);
    void SendGBA(ThreadParam*);
    void GBARecvSend(ThreadParam*, unsigned int*);

    void ResetQueue(ThreadParam*);
    void CleanQueue(ThreadParam*);
    void InitialCode(ThreadParam*);
    void SetSendQueue(ThreadParam*, unsigned int);
    void SendGBAStart(ThreadParam*, unsigned int*);
    void SendGBAStop(ThreadParam*);
    void SendChkCrc(ThreadParam*, int, unsigned short, unsigned int*);
    void SendCancel(ThreadParam*);

    void SendDataFile(ThreadParam*);
    void SendMBase(ThreadParam*);
    void SendMapNo(ThreadParam*);

    void InitPpos();
    void SendPpos(ThreadParam*);

    void MakeJoyData(char*, int, unsigned int*);

    void SendPlayerStat(ThreadParam*);
    void SendPlayerHP(ThreadParam*);
    void SendItemAll(ThreadParam*);
    void SendMapObj(ThreadParam*);
    void SendCompatibility(ThreadParam*);
    void SendCtrlMode(ThreadParam*, int);
    void SendMapObjDrawFlg(ThreadParam*);
    void SendFavorite(ThreadParam*);

    void RequestData(ThreadParam*, int, int);
    void SetRecvBuffer(ThreadParam*, unsigned int);
    void ClrRecvBuffer(int);
    void GetRecvBuffer(int, unsigned char*);

    void SendMType(ThreadParam*, int);
    void SendEquip(ThreadParam*);
    void SendCmd(ThreadParam*);
    void SendBonusStr(ThreadParam*);
    void SendArtifact(ThreadParam*);
    void SendTmpArtifact(ThreadParam*);
    void SendMapObjInfo(ThreadParam*);
    void SendStrength(ThreadParam*);
    void SendRaderType(ThreadParam*);
    void SendRaderMode(ThreadParam*);
    void SendScouInfo(ThreadParam*);
    void SendOpenMenu(ThreadParam*, char);
    void SendItemUse(ThreadParam*);
    void SendSPMode(ThreadParam*);
    void SendMemorys(ThreadParam*);
    void SendChgCmdNum(ThreadParam*);
    void SendStartBonus(ThreadParam*);

    void DecRecvQueue(int);
    void GetGBAStat(ThreadParam*);
    void ChgCtrlMode(int);
    void SetCtrlMode(int, int);
    void GetCtrlMode(int);
    void GetGBAConnect(int);
    void IsInitSend(int);
    void GetGBAStart(int);
    void GBAReady(int);
    void SendAllStat(int);

    void GetLetterBuffer(int);
    void SetLetterSize(int, int);
    void SendResult(int, int, int, int);
    void IsLetterMenu(int);
    void SendAddLetter(int);

    void SetItem(int, unsigned char, short);
    void DelItem(int, unsigned char);

    void SendMask(int, unsigned short);
    void SetMoney(int, unsigned int);

    void SetMType(int, int);
    void GetMType(int);
    void GetPadType(int);

    void ExitThread();
    void IsThreadRunning();
    void RestartThread();

    void SetCmdLst(int, int, short);
	int SetTmpArti(int portIndex, int param3, int param4);
    void SendUseItem(int, char);
    void SendHitEnemy(int, char, short);
    void SetOpenMenu(int, char);

    char m_pathBuf[128];

    JoyBusRecvBuffer m_recvBuffer[4];

    unsigned int m_gbaBootParamA;
    unsigned int m_gbaBootParamB;

    unsigned int m_diskId;
    unsigned char m_diskIdBytes[4];

    OSThread m_threads[4];

    unsigned char m_sendBuffer[4][0x1000];

    ThreadParam m_threadParams[4];

    OSSemaphore m_accessSemaphores[4];

    short m_stageFlags[4];

    unsigned int m_cmdQueueData[4][64];
    unsigned int m_recvQueueEntriesArr[4][64];

    unsigned int m_cmdCount[4];
    unsigned int m_secCmdCount[4];

    unsigned char m_ctrlModeArr[4];
    unsigned char m_nextModeTypeArr[4];
    unsigned char m_modeXArr[4];
    unsigned char m_stateCodeArr[4];
    unsigned char m_stateFlagArr[4];

    uchar m_threadInitFlag;
    bool m_binLoaded;
    bool m_exitThreadFlag;
    uchar m_threadRunningMask;

    unsigned int m_fileBaseA;
    unsigned int m_fileBaseB;

    unsigned int m_letterBuffer[4];

    unsigned int m_fileBaseA_dup;
    unsigned int m_fileBaseB_dup;

    unsigned int m_letterSizeArr[4];

    unsigned char m_perThreadTemp[4][24];

    unsigned char m_cmdBuffer[8];

    uchar m_stageId;
    uchar m_mapId;

    unsigned char m_padding[5174];
};

#endif // JOYBUS_H
