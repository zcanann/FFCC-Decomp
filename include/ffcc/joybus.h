#ifndef JOYBUS_H
#define JOYBUS_H

#include <Dolphin/os.h>
#include <Dolphin/dvd.h>

typedef unsigned char uchar;
typedef unsigned int uint;

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

class JoyBus
{
public:
	
	struct JoyBusRecvBuffer
	{
		unsigned int   m_length;         // 0x00
		unsigned short m_cmdFlags;       // 0x04
		unsigned short m_crc;            // 0x06
		unsigned char  m_payload[0x400]; // 0x08
	};



    JoyBus();
    ~JoyBus();

    void Init();
    void CreateInit();
    void Destroy();
    int LoadBin();
    int LoadMap(int, int);

	unsigned short Crc16(int len, unsigned char* data, unsigned short* crc);

    void BlockSem(int portIndex);
    void ReleaseSem(int portIndex);

    void ThreadMain(void* arg);
    static void* _ThreadMain(void* arg);
    void ThreadInit();
    void ThreadSleep(long long);

    void ReadInitialCode(ThreadParam* threadParam);
    void WriteInitialCode(ThreadParam* threadParam);
    void ReadContext(ThreadParam* threadParam);
    void ReadHostId(ThreadParam* threadParam);
    void WriteHostId(ThreadParam* threadParam);
    void WriteContext(ThreadParam* threadParam);

    void SetPadData(ThreadParam* threadParam, unsigned char* data);
    short GetPadData(int portIndex);

    int RecvGBA(ThreadParam* threadParam, unsigned int* recvBuffer);
    int SendGBA(ThreadParam* threadParam);
    int GBARecvSend(ThreadParam* threadParam, unsigned int* outCmd);

    void ResetQueue(ThreadParam* threadParam);
    void CleanQueue(ThreadParam* threadParam);
    int InitialCode(ThreadParam* threadParam);
    int SetSendQueue(ThreadParam* threadParam, unsigned int command);
    int SendGBAStart(ThreadParam* threadParam, unsigned int* outCmd);
    int SendGBAStop(ThreadParam* threadParam);
    int SendChkCrc(ThreadParam* threadParam, int, unsigned short, unsigned int*);
    int SendCancel(ThreadParam* threadParam);

    int SendDataFile(ThreadParam* threadParam);
    int SendMBase(ThreadParam* threadParam);
    int SendMapNo(ThreadParam* threadParam);

    void InitPpos();
    int SendPpos(ThreadParam* threadParam);

	int MakeJoyData(char* src, int length, unsigned int* outBuffer);

    int SendPlayerStat(ThreadParam* threadParam);
    int SendPlayerHP(ThreadParam* threadParam);
    int SendItemAll(ThreadParam* threadParam);
    int SendMapObj(ThreadParam* threadParam);
    int SendCompatibility(ThreadParam* threadParam);
    int SendCtrlMode(ThreadParam*, int);
    int SendMapObjDrawFlg(ThreadParam* threadParam);
    int SendFavorite(ThreadParam* threadParam);

    unsigned int RequestData(ThreadParam*, int a, int b);
    void SetRecvBuffer(ThreadParam*, unsigned int);
    void ClrRecvBuffer(int portIndex);
	void GetRecvBuffer(int playerIndex, unsigned char* outBuffer);

    int SendMType(ThreadParam* threadParam, int modeType);
    int SendEquip(ThreadParam* threadParam);
    int SendCmd(ThreadParam* threadParam);
    int SendBonusStr(ThreadParam* threadParam);
    int SendArtifact(ThreadParam* threadParam);
    int SendTmpArtifact(ThreadParam* threadParam);
    int SendMapObjInfo(ThreadParam* threadParam);
    int SendStrength(ThreadParam* threadParam);
    int SendRaderType(ThreadParam* threadParam);
    int SendRaderMode(ThreadParam* threadParam);
    int SendScouInfo(ThreadParam* threadParam);
    int SendOpenMenu(ThreadParam* threadParam, char menuId);
    int SendItemUse(ThreadParam* threadParam);
    void SendSPMode(ThreadParam* threadParam);
    int SendMemorys(ThreadParam* threadParam);
    int SendChgCmdNum(ThreadParam* threadParam);
    int SendStartBonus(ThreadParam* threadParam);

    void DecRecvQueue(int portIndex);
    int GetGBAStat(ThreadParam* threadParam);
    int ChgCtrlMode(int portIndex);
    int SetCtrlMode(int portIndex, int controlMode);
	unsigned char GetCtrlMode(int portIndex);
    int GetGBAConnect(int portIndex);
    int IsInitSend(int portIndex);
    bool GetGBAStart(int portIndex);
    int GBAReady(int portIndex);
    int SendAllStat(int portIndex);

    char* GetLetterBuffer(int portIndex);
    void SetLetterSize(int portIndex, int letterSize);
    int SendResult(int portIndex, int, int, int);
    bool IsLetterMenu(int portIndex);
    int SendAddLetter(int portIndex);

	int SetItem(int portIndex, unsigned char itemId, short amount);
    int DelItem(int portIndex, unsigned char itemId);

    int SendMask(int portIndex, unsigned short);
	int SetMoney(int portIndex, unsigned int money);

	int SetMType(int portIndex, int mtype);
    char GetMType(int portIndex);
    unsigned int GetPadType(int portIndex);

    void ExitThread();
    bool IsThreadRunning();
    void RestartThread();

    int SetCmdLst(int portIndex, int, short);
	int SetTmpArti(int portIndex, int param3, int param4);
    int SendUseItem(int portIndex, char itemId);
    int SendHitEnemy(int portIndex, char enemyId, short hitValue);
    int SetOpenMenu(int playerIndex, char menuId);

    char m_pathBuf[128];

    JoyBusRecvBuffer m_recvBuffer[4];

    char* m_gbaBootImage;
    unsigned int m_gbaBootImageSize;

    char* m_diskId;
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

    unsigned int* m_fileBaseA;
    unsigned int* m_fileBaseB;

    char* m_letterBuffer[4];

    unsigned int m_fileBaseA_dup;
    unsigned int m_fileBaseB_dup;

    unsigned int m_letterSizeArr[4];

    unsigned char m_perThreadTemp[4][24];

    unsigned char m_cmdBuffer[8];

    uchar m_stageId;
    uchar m_mapId;

	unsigned char m_joyDataPacketBuffer[4][1024];
	// unsigned char padding[2];
	unsigned char m_playerPosPacketBuffer[4][256];
	int m_txWordIndex[4];
	int m_pposWordIndex[4];
	int m_txWordCount[4];
	// unsigned char padding[4];
};

extern JoyBus Joybus;
extern const unsigned short JoyBusCrcTable[256];

#endif // JOYBUS_H
