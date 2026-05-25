#include "ffcc/gbaque.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/mes.h"
#include "ffcc/game.h"
#include "ffcc/p_gba.h"
#include "ffcc/p_menu.h"
#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include <string.h>
#include <Dolphin/os.h>
#include <Runtime.PPCEABI.H/NMWException.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

GbaQueue GbaQue;

struct GbaFlatDataTableEntryView
{
	int m_numEntries;
	char** m_strings;
	char* m_stringBuf;
};

struct GbaFlatDataView
{
	int m_dataCount;
	unsigned char _pad[0x68 - 4];
	int m_tableCount;
	GbaFlatDataTableEntryView m_tabl[8];
};

struct GbaQueueFlagView
{
	unsigned char _pad0[0x2AFC];
	unsigned char m_letterDatFlg;
	unsigned char _pad2AFD[0x18D];
	unsigned char m_compatibilityFlg[4];
	unsigned char _pad2C8E[0xAC];
	unsigned char m_sellFlg;
	unsigned char m_buyFlg;
	unsigned char m_mkSmithFlg;
};

struct GbaQueuePlayerDataView
{
	unsigned char _pad00;
	unsigned char _pad01;
	unsigned char _pad02;
	unsigned char _pad03;
	unsigned int _pad04[4];
	unsigned short _pad14;
	unsigned char _pad16;
	unsigned char _pad17;
	unsigned int _pad18[2];
	unsigned char m_strength[3];
	unsigned char _pad23;
	unsigned int m_artifacts[3];
	unsigned short _pad30;
	unsigned char _pad32[8];
	unsigned short m_items[0x40];
	unsigned short m_tmpArtifacts[4];
	unsigned short m_artifactList[8];
	unsigned char _padD2;
	unsigned char m_artifactCount;
	unsigned char _padD4;
	unsigned char _padD5;
	unsigned char _padD6;
	unsigned char m_commandData[4];
	unsigned char _padDB;
};
STATIC_ASSERT(sizeof(GbaQueuePlayerDataView) == 0xDC);

struct GbaQueuePlayerPosView
{
	unsigned char _pad00[3];
	char m_active;
	unsigned char _pad04[0x32];
	short m_posX;
	short m_posZ;
	unsigned char _pad3A[0xA2];
};
STATIC_ASSERT(sizeof(GbaQueuePlayerPosView) == 0xDC);

struct GbaQueueCMakeInfoView
{
	unsigned char m_active;
	unsigned char m_resultCode;
	short m_packetCount;
	unsigned short m_crc;
	unsigned char m_playerSlot;
	char m_name[0x11];
	unsigned char m_charaType;
	unsigned char m_favoriteLead[2];
	unsigned char m_favorite[4];
	unsigned char m_jobType;
};
STATIC_ASSERT(sizeof(GbaQueueCMakeInfoView) == 0x20);
STATIC_ASSERT(sizeof(GbaCMakeInfo) == 0x20);

struct GbaQueueSetQueueView
{
	unsigned char _pad00[0x30];
	unsigned int m_queue[4][0x40];
	int m_queueCount[4];
	char m_queueFull[4];
};
STATIC_ASSERT(sizeof(GbaQueueSetQueueView) == 0x444);

enum {
	kGbaQueueScratchTextSize = 0x400,
	kGbaQueuePlayerDataChannelCount = 4,
	kGbaQueuePlayerDataBlockBytes = sizeof(GbaQueuePlayerDataView) * kGbaQueuePlayerDataChannelCount,
	kGbaQueueCaravanNameBlockBytes = 0x80,
	kGbaQueueEnemyDataBytes = 0x500,
	kGbaQueueEnemyHistoryBlockBytes = kGbaQueueEnemyDataBytes * kGbaQueuePlayerDataChannelCount,
	kGbaQueueMapItemDataBytes = 0x140,
	kGbaQueueMapItemHistoryBlockBytes = kGbaQueueMapItemDataBytes * kGbaQueuePlayerDataChannelCount,
	kGbaQueueMapObjWorkBytes = 0x188,
	kGbaQueueLetterNpcNameBytes = 0x800,
	kGbaQueueLetterSubjectNameBytes = 0x1800,
	kGbaQueueLetterEntryAllocWords = 0x1000,
	kGbaQueueLetterEntryBytes = 0x800,
	kGbaQueueLetterTempNameBytes = 0x20,
	kGbaQueueLetterHeaderBytes = 0x10,
	kGbaQueueLetterNpcNameEntryBytes = 0x10,
	kGbaQueueLetterSubjectNameEntryBytes = 0x18,
};

STATIC_ASSERT(kGbaQueuePlayerDataBlockBytes == 0x370);
STATIC_ASSERT(sizeof(GbaPInfo) == kGbaQueuePlayerDataBlockBytes);
STATIC_ASSERT(kGbaQueueEnemyHistoryBlockBytes == 0x1400);
STATIC_ASSERT(kGbaQueueMapItemHistoryBlockBytes == 0x500);

static inline GbaQueueFlagView* GetFlagView(GbaQueue* gbaQueue)
{
	return reinterpret_cast<GbaQueueFlagView*>(gbaQueue);
}

static inline GbaQueuePlayerDataView* GetPlayerDataView(GbaQueue* gbaQueue, int channel)
{
	return reinterpret_cast<GbaQueuePlayerDataView*>(reinterpret_cast<unsigned char*>(gbaQueue) + channel * 0xDC + 0x454);
}

static inline GbaQueuePlayerDataView* GetPlayerDataBlock(GbaQueue* gbaQueue)
{
	return GetPlayerDataView(gbaQueue, 0);
}

static inline GbaQueueSetQueueView* GetSetQueueView(GbaQueue* gbaQueue)
{
	return reinterpret_cast<GbaQueueSetQueueView*>(gbaQueue);
}

static inline unsigned short SwapU16(unsigned short value)
{
	return __lhbrx(&value, 0);
}

static inline unsigned int SwapU32(unsigned int value)
{
	return __lwbrx(&value, 0);
}

static inline unsigned short SwapU16Value(unsigned short value)
{
	return static_cast<unsigned short>((value << 8) | (value >> 8));
}

static inline unsigned int SwapU32Value(unsigned int value)
{
	return (value << 24) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | (value >> 24);
}

extern "C" const char s_gbaque_cpp[] = "gbaque.cpp";
static const char s_pcts_pctd_Error_memory_allocation_error_801DB37C[] = "%s(%d): Error: memory allocation error\n";
static const char s_compatibility_data_error[] = "compatibility data error!!\n";
static const char s_cmake_favorite_crc_error[] = "%s(%d): Error:CMakeFavorite() crc error!!\n";
static const char s_cmake_name_crc_error[] = "%s(%d): Error:ChkCMakeName() crc error!!\n";
static const char s_unknown_mapobj_type_error[] = "Error:Unknown mapobj type(%d)\n";
static const char s_npc_max_over[] = "%s(%d): Error: NPC max over!!\n";
static const char s_subject_max_over[] = "%s(%d): Error: Subject max over!!\n";
static const char s_letter_data_error[] = "%s(%d): Error: Letter data error(chan:%d  idx:%d)\n";
extern float kGbaQueueMapCoordScale;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
GbaQueue::GbaQueue()
{
	Init();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
GbaQueue::~GbaQueue()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800D1354
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::Init()
{
	GbaQueue* osSemaphore;
	int i;
	char* obj = reinterpret_cast<char*>(this);
	GbaQueueSetQueueView* queue = GetSetQueueView(this);

	memset(queue->m_queue, 0, sizeof(queue->m_queue));
	memset(queue->m_queueCount, 0, sizeof(queue->m_queueCount));
	memset(queue->m_queueFull, 0, sizeof(queue->m_queueFull));
	memset(GetPlayerDataBlock(this), 0, kGbaQueuePlayerDataBlockBytes);
	memset(obj + 0x7C4, 0, kGbaQueuePlayerDataBlockBytes);
	memset(obj + 0xB34, 0, kGbaQueueEnemyDataBytes);
	memset(obj + 0x1034, 0, kGbaQueueEnemyHistoryBlockBytes);
	memset(obj + 0x2434, 0, kGbaQueueMapItemDataBytes);
	memset(obj + 0x2574, 0, kGbaQueueMapItemHistoryBlockBytes);
	memset(obj + 0x2A74, 0, kGbaQueueCaravanNameBlockBytes);
	memset(obj + 0x2B00, 0, kGbaQueueMapObjWorkBytes);
	memset(obj + 0x2C8E, 0, 8);
	memset(cmakeInfo, 0, sizeof(cmakeInfo));
	memset(m_hitInfo, 0xFF, sizeof(m_hitInfo));

	i = 0;
	osSemaphore = this;
	do {
		OSInitSemaphore(osSemaphore->accessSemaphores, 1);
		i = i + 1;
		osSemaphore = reinterpret_cast<GbaQueue*>(osSemaphore->accessSemaphores + 1);
	} while (i < 4);

	*reinterpret_cast<unsigned int*>(obj + 0x448) = 0xFF;
	*reinterpret_cast<unsigned int*>(obj + 0x444) = 0xFF;
	obj[0x44C] = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x44E) = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x450) = 0;

	obj[0x2AFC] = 0;
	obj[0x2C88] = 0;
	obj[0x2C89] = 0;
	obj[0x2D38] = 0;
	obj[0x2D39] = 0;
	obj[0x2D3A] = 0;
	obj[0x2D3B] = 0;
	obj[0x2D3C] = 0;
	obj[0x2D3D] = 0;
	obj[0x2D37] = 0;
	obj[0x2CB1] = 0;
	obj[0x2CB0] = 0;
	obj[0x2D36] = 0;
	obj[0x2D3E] = 0;
	obj[0x2D3F] = 0;
	obj[0x2AF4] = 0;
	obj[0x2D40] = 0;
	obj[0x2D41] = 0xF;
	obj[0x2D42] = 0;
	obj[0x2D54] = 0;
	obj[0x2D55] = 0;
	m_singleMode = 0;
	obj[0x2D57] = 0;
	obj[0x2D58] = 0;
	obj[0x2D59] = 0;
	obj[0x2D5A] = 0;
	obj[0x2D5B] = 0;
	obj[0x2D5C] = 0;
	obj[0x2D5D] = 0xF;
	obj[0x2D5E] = 0;
	obj[0x2D5F] = 0;
	obj[0x2D60] = 0xF;
	obj[0x2D61] = 0;
	obj[0x2C96] = static_cast<char>(0xFF);
	*reinterpret_cast<unsigned int*>(obj + 0x2C9C) = 0;
	obj[0x2CAC] = 0;
	obj[0x2C8A] = 0;
	obj[0x2D32] = 1;
	obj[0x2C97] = static_cast<char>(0xFF);
	*reinterpret_cast<unsigned int*>(obj + 0x2CA0) = 0;
	obj[0x2CAD] = 0;
	obj[0x2C8B] = 0;
	obj[0x2D33] = 1;
	obj[0x2C98] = static_cast<char>(0xFF);
	*reinterpret_cast<unsigned int*>(obj + 0x2CA4) = 0;
	obj[0x2CAE] = 0;
	obj[0x2C8C] = 0;
	obj[0x2D34] = 1;
	obj[0x2C99] = static_cast<char>(0xFF);
	*reinterpret_cast<unsigned int*>(obj + 0x2CA8) = 0;
	obj[0x2CAF] = 0;
	obj[0x2C8D] = 0;
	obj[0x2D35] = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::BlockSem(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ReleaseSem(int channel)
{
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadAll()
{
	int i;
	GbaQueue* semaphoreIter;
	char* obj;
	unsigned char prevMenuStageMode;
	unsigned char spModeBits;
	unsigned char spModeChangeBits;
	unsigned int cflatFlag;
	int* scriptFoodBase;

	semaphoreIter = this;
	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}

	obj = reinterpret_cast<char*>(this);
	prevMenuStageMode = static_cast<unsigned char>(m_singleMode);
	m_singleMode = static_cast<char>(Game.m_gameWork.m_menuStageMode != 0);
	if (prevMenuStageMode != static_cast<unsigned char>(m_singleMode)) {
		obj[0x2C88] = 0xF;
	}

	spModeBits = static_cast<unsigned char>(Game.m_gameWork.m_spModeFlags[0] != 0);
	if (Game.m_gameWork.m_spModeFlags[1] != 0) {
		spModeBits |= 2;
	}
	if (Game.m_gameWork.m_spModeFlags[2] != 0) {
		spModeBits |= 4;
	}
	if (Game.m_gameWork.m_spModeFlags[3] != 0) {
		spModeBits |= 8;
	}

	spModeChangeBits = static_cast<unsigned char>(spModeBits ^ static_cast<unsigned char>(obj[0x2D5C]));
	if ((spModeChangeBits & 1) != 0) {
		obj[0x2D5D] = static_cast<char>(obj[0x2D5D] | 1);
	}
	if ((spModeChangeBits & 2) != 0) {
		obj[0x2D5D] = static_cast<char>(obj[0x2D5D] | 2);
	}
	if ((spModeChangeBits & 4) != 0) {
		obj[0x2D5D] = static_cast<char>(obj[0x2D5D] | 4);
	}
	if ((spModeChangeBits & 8) != 0) {
		obj[0x2D5D] = static_cast<char>(obj[0x2D5D] | 8);
	}
	obj[0x2D5C] = static_cast<char>(spModeBits);

	semaphoreIter = this;
	for (i = 0; i < 4; i++) {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}

	LoadPlayerStat();
	LoadEnemyStat();
	LoadMapItemStat();

	cflatFlag = reinterpret_cast<unsigned int*>(&CFlat)[0x1041];
	if ((obj[0x2CE8] == 0) && (cflatFlag != 0)) {
		SetRadarType();
	}
	if (cflatFlag == 0) {
		memset(obj + 0x2CB8, 0xFF, 0x10);
		obj[0x2CD8] = 0;
	}

	semaphoreIter = this;
	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}
	obj[0x2CE8] = static_cast<char>(cflatFlag);
	semaphoreIter = this;
	for (i = 0; i < 4; i++) {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}

	LoadMapObj();

	scriptFoodBase = reinterpret_cast<int*>(Game.m_scriptFoodBase);
	for (i = 0; i < 4; i++) {
		if (scriptFoodBase[i] == 0) {
			obj[0x2C96 + i] = static_cast<char>(0xFF);
		} else {
			OSWaitSemaphore(accessSemaphores + i);
			{
				unsigned short maskValue = *reinterpret_cast<unsigned short*>(scriptFoodBase[i] + 0x89C);
				if ((maskValue != *reinterpret_cast<unsigned short*>(obj + 0x2C8E)) && (Joybus.SendMask(i, maskValue) == 0)) {
					*reinterpret_cast<unsigned short*>(obj + 0x2C8E) = maskValue;
					obj[0x2C96 + i] = 6;
				}
			}
			OSSignalSemaphore(accessSemaphores + i);
		}
	}

	semaphoreIter = this;
	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}
	{
		unsigned char resetMask = static_cast<unsigned char>(obj[0x2D30]);
		obj[0x2D30] = 0;
		semaphoreIter = this;
		for (i = 0; i < 4; i++) {
			OSSignalSemaphore(semaphoreIter->accessSemaphores);
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		}

		for (i = 0; i < 4; i++) {
			if (scriptFoodBase[i] == 0) {
				continue;
			}

			unsigned int bit = static_cast<unsigned int>(1U << i);
			if ((resetMask & bit) != 0) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(scriptFoodBase[i]);
				if (caravanWork->m_shopBusyFlag == 1) {
					OSWaitSemaphore(accessSemaphores + i);
					obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~static_cast<char>(bit));
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~static_cast<char>(bit));
					OSSignalSemaphore(accessSemaphores + i);
					for (int retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(i, 0) == 0) {
							break;
						}
					}
					caravanWork->CallShop(0, 0, 0, 0, 0);
				}
				if (caravanWork->m_shopBusyFlag == 2) {
					unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
					OSWaitSemaphore(accessSemaphores + i);
					obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~shopMask);
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~shopMask);
					OSSignalSemaphore(accessSemaphores + i);
					for (int retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(i, 0) == 0) {
							break;
						}
					}
					caravanWork->CallShop(1, 0, 0, 0, 0);
				}
			}

			if ((static_cast<unsigned char>(obj[0x2D39]) & bit) == 0) {
				unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
				if ((static_cast<unsigned char>(obj[0x2D39]) & shopMask) != 0) {
					OSWaitSemaphore(accessSemaphores + i);
					obj[0x2D38] = static_cast<char>(obj[0x2D38] | shopMask);
					OSSignalSemaphore(accessSemaphores + i);
					if (Joybus.SetMType(i, 3) == 0) {
						obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~shopMask);
					} else {
						obj[0x2D39] = static_cast<char>(obj[0x2D39] | shopMask);
					}
				}
			} else {
				unsigned char playerMask = static_cast<unsigned char>(1 << i);
				OSWaitSemaphore(accessSemaphores + i);
				obj[0x2D38] = static_cast<char>(obj[0x2D38] | playerMask);
				OSSignalSemaphore(accessSemaphores + i);
				if (Joybus.SetMType(i, 2) == 0) {
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~playerMask);
				} else {
					obj[0x2D39] = static_cast<char>(obj[0x2D39] | playerMask);
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800D0B98
 * PAL Size: 596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrShopMode()
{
	int i;
	char* obj;
	CCaravanWork* caravanWork;

	obj = reinterpret_cast<char*>(this);
	for (i = 0; i < 4; i++) {
		caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
		if (caravanWork == 0) {
			continue;
		}

		if (caravanWork->m_shopBusyFlag == 1) {
			OSWaitSemaphore(accessSemaphores + i);
			{
				const unsigned char playerMask = static_cast<unsigned char>(1 << i);
				obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~playerMask);
				obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~playerMask);
			}
			OSSignalSemaphore(accessSemaphores + i);

			for (int retry = 0; retry < 10; retry++) {
				if (Joybus.SetMType(i, 0) == 0) {
					break;
				}
			}
			caravanWork->CallShop(0, 0, 0, 0, 0);
		}

		if (caravanWork->m_shopBusyFlag == 2) {
			OSWaitSemaphore(accessSemaphores + i);
			{
				const unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
				obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~shopMask);
				obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~shopMask);
			}
			OSSignalSemaphore(accessSemaphores + i);

			for (int retry = 0; retry < 10; retry++) {
				if (Joybus.SetMType(i, 0) == 0) {
					break;
				}
			}
			caravanWork->CallShop(1, 0, 0, 0, 0);
		}

		if ((static_cast<unsigned char>(obj[0x2D39]) & (1 << i)) == 0) {
			const unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
			if ((static_cast<unsigned char>(obj[0x2D39]) & shopMask) != 0) {
				OSWaitSemaphore(accessSemaphores + i);
				obj[0x2D38] = static_cast<char>(obj[0x2D38] | shopMask);
				OSSignalSemaphore(accessSemaphores + i);
				if (Joybus.SetMType(i, 3) == 0) {
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~shopMask);
				} else {
					obj[0x2D39] = static_cast<char>(obj[0x2D39] | shopMask);
				}
			}
		} else {
			const unsigned char playerMask = static_cast<unsigned char>(1 << i);
			OSWaitSemaphore(accessSemaphores + i);
			obj[0x2D38] = static_cast<char>(obj[0x2D38] | playerMask);
			OSSignalSemaphore(accessSemaphores + i);
			if (Joybus.SetMType(i, 2) == 0) {
				obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~playerMask);
			} else {
				obj[0x2D39] = static_cast<char>(obj[0x2D39] | playerMask);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadMask()
{
	int* scriptFoodBase = reinterpret_cast<int*>(Game.m_scriptFoodBase);
	char* obj = reinterpret_cast<char*>(this);

	for (int i = 0; i < 4; i++) {
		if (scriptFoodBase[i] == 0) {
			obj[0x2C96 + i] = static_cast<char>(0xFF);
			continue;
		}

		OSWaitSemaphore(accessSemaphores + i);
		{
			unsigned short maskValue = *reinterpret_cast<unsigned short*>(scriptFoodBase[i] + 0x89C);
			if ((maskValue != *reinterpret_cast<unsigned short*>(obj + 0x2C8E)) && (Joybus.SendMask(i, maskValue) == 0)) {
				*reinterpret_cast<unsigned short*>(obj + 0x2C8E) = maskValue;
				obj[0x2C96 + i] = 6;
			}
		}
		OSSignalSemaphore(accessSemaphores + i);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800D0AD4
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::SetQueue(int channel, unsigned int value)
{
	GbaQueueSetQueueView* queue = reinterpret_cast<GbaQueueSetQueueView*>(this);
	OSSemaphore* semaphore = accessSemaphores + channel;
	int ret;

	OSWaitSemaphore(semaphore);
	if (queue->m_queueFull[channel] != 0) {
		ret = -1;
	} else {
		if (queue->m_queueCount[channel] >= 0x40) {
			ret = -1;
			queue->m_queueFull[channel] = 1;
		} else {
			ret = 0;
			queue->m_queue[channel][queue->m_queueCount[channel]] = value;
			queue->m_queueCount[channel] = queue->m_queueCount[channel] + 1;
		}
	}
	OSSignalSemaphore(semaphore);
	return ret;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ResetQueue()
{
	GbaQueueSetQueueView* queue = GetSetQueueView(this);

	for (int channel = 0; channel < 4; channel++) {
		OSWaitSemaphore(accessSemaphores + channel);
		memset(queue->m_queue[channel], 0, sizeof(queue->m_queue[channel]));
		queue->m_queueCount[channel] = 0;
		queue->m_queueFull[channel] = 0;
		OSSignalSemaphore(accessSemaphores + channel);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CFF38
 * PAL Size: 2972b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ExecutQueue()
{
	unsigned int localQueueData[4][64];
	int localQueueCount[4];
	GbaQueueSetQueueView* queue = GetSetQueueView(this);
	char* obj;
	int scriptFoodBase[4];
	unsigned int channel;

	for (channel = 0; channel < 4; channel++) {
		OSWaitSemaphore(accessSemaphores + channel);
	}

	memcpy(localQueueData, queue->m_queue, sizeof(localQueueData));
	memcpy(localQueueCount, queue->m_queueCount, sizeof(localQueueCount));
	memset(queue->m_queue, 0, sizeof(localQueueData));
	memset(queue->m_queueCount, 0, sizeof(localQueueCount));

	for (channel = 0; channel < 4; channel++) {
		OSSignalSemaphore(accessSemaphores + channel);
	}

	obj = reinterpret_cast<char*>(this);
	memcpy(scriptFoodBase, Game.m_scriptFoodBase, sizeof(scriptFoodBase));

	for (channel = 0; channel < 4; channel++) {
		const unsigned int playerBit = (1U << channel);
		const unsigned int shopBit = (0x10U << channel);
		unsigned int* queueWords = localQueueData[channel];
		int queueCount = localQueueCount[channel];
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(scriptFoodBase[channel]);
		int i;

		if (queue->m_queueFull[channel] != 0) {
			continue;
		}

		for (i = 0; i < queueCount; i++) {
			unsigned int cmdWord = queueWords[i];
			unsigned char cmd = static_cast<unsigned char>(cmdWord & 0x3F);

			if (cmd == 0x17) {
				if (caravanWork != 0) {
					const int action = static_cast<unsigned char>(cmdWord >> 16);
					const int itemIdx = static_cast<unsigned char>(cmdWord >> 8);
					if (action == 1) {
						caravanWork->FGUseItem(itemIdx, 1);
					} else if (action == 2) {
						caravanWork->FGPutItem(itemIdx, 1);
					} else if (action == 3) {
						caravanWork->DeleteItemIdx(itemIdx, 1);
					}
				}
			} else if (cmd == 0x1A) {
				if (caravanWork != 0) {
					const unsigned char p0 = static_cast<unsigned char>(cmdWord >> 24);
					const unsigned char p1 = static_cast<unsigned char>(cmdWord >> 16);
					const unsigned char p2 = static_cast<unsigned char>(cmdWord >> 8);
					const unsigned char p3 = static_cast<unsigned char>(cmdWord);
					unsigned int* pendingMoney = reinterpret_cast<unsigned int*>(obj + 0x2C9C + channel * 4);
					unsigned char* moneyState = reinterpret_cast<unsigned char*>(obj + 0x2CAC + channel);

					if ((static_cast<int>(p0) >> 6) == 0) {
						*moneyState = static_cast<unsigned char>(p1 | 0x80);
						*pendingMoney = (static_cast<unsigned int>(p2) << 24) | (static_cast<unsigned int>(p3) << 16);
					} else if (*moneyState == 0) {
						Joybus.SendResult(channel, 1, p0, p1);
					} else {
						*pendingMoney |= (static_cast<unsigned int>(p1) << 8) | p2;
						Joybus.SendResult(channel, 0, p0, *moneyState & 7);
						if ((*moneyState & 7) == 1) {
							caravanWork->FGPutGil(*pendingMoney);
						}
						*pendingMoney = 0;
						*moneyState = 0;
					}
				}
			} else if (cmd == 0x1E) {
				if (caravanWork != 0) {
					const int equipType = static_cast<signed char>(cmdWord >> 16);
					const int equipItem = static_cast<signed char>(cmdWord >> 8);
					caravanWork->ChgEquipPos(equipType, equipItem);
				}
			} else if (cmd == 0x1F) {
				if (caravanWork != 0) {
					unsigned short cmdListData = static_cast<unsigned short>((cmdWord << 8) | ((cmdWord >> 8) & 0xFF));
					caravanWork->ChgCmdLst(static_cast<unsigned char>(cmdWord >> 16), static_cast<short>(cmdListData));
				}
			} else if (cmd == 0x0C) {
				const unsigned char request = static_cast<unsigned char>(cmdWord >> 8);
				if (caravanWork != 0) {
					if (request == 3) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeLetterList(channel, letterBuf);
					} else if (request == 2) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						caravanWork->FGLetterOpen(static_cast<unsigned char>(cmdWord));
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeLetterData(channel, letterBuf, static_cast<unsigned char>(cmdWord));
					} else if (request == 6) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeSellData(channel, letterBuf);
					} else if (request == 7) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeBuyData(channel, letterBuf);
					} else if (request == 8) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeSmithData(channel, letterBuf);
					} else if (request == 9) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);
						char* letterBuf = Joybus.GetLetterBuffer(channel);
						MakeArtiData(channel, letterBuf);
					}
				}
			} else if (cmd == 0x14) {
				const unsigned char request = static_cast<unsigned char>(cmdWord >> 8);
				if (request == 0 || request == 1) {
					if (caravanWork != 0) {
						MoveLetterItem(channel, cmdWord);
					}
				} else if (request == 2) {
					ChkCMakeCharaType(channel, cmdWord);
				} else if (request == 3) {
					ChkCMakeJob(channel, cmdWord);
				} else if (request == 4 || request == 5) {
					unsigned char status = static_cast<unsigned char>(cmdWord >> 16);
					int retry;
					for (retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(channel, 4) == 0) {
							break;
						}
					}
					if (retry >= 10) {
						status = 4;
					}
					if (status == 4) {
						MenuPcs.ClrCMakeFlg(channel);
					} else if (status == 5) {
						MenuPcs.SetCMakeEnd(channel);
					}
				} else if (request == 6) {
					OSWaitSemaphore(accessSemaphores + channel);
					obj[0x2CCB] = static_cast<char>(cmdWord >> 8);
					obj[0x2CCC] = static_cast<char>(cmdWord);
					OSSignalSemaphore(accessSemaphores + channel);
					Joybus.SendResult(channel, 0, static_cast<unsigned char>(cmdWord >> 16), 0);
				} else if (request == 7) {
					OSWaitSemaphore(accessSemaphores + channel);
					obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~static_cast<unsigned char>(playerBit));
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~static_cast<unsigned char>(playerBit));
					OSSignalSemaphore(accessSemaphores + channel);
					for (int retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(channel, 0) == 0) {
							break;
						}
					}
					if (caravanWork != 0) {
						caravanWork->CallShop(0, 0, 0, 0, 0);
					}
				} else if (request == 8) {
					if (caravanWork != 0) {
						const int itemIdx = static_cast<unsigned char>(cmdWord >> 8);
						const short itemId = caravanWork->m_inventoryItems[itemIdx];
						caravanWork->DeleteItemIdx(itemIdx, 1);
						const unsigned short baseGil =
							*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + static_cast<int>(itemId) * 0x48 + 0x20);
						int gil = static_cast<int>(
							static_cast<float>(caravanWork->m_shopParam) / 100.0f * 0.25f * static_cast<float>(baseGil));
						if (gil < 1) {
							gil = 1;
						}
						caravanWork->AddGil(gil);
						Joybus.SendResult(channel, 0, static_cast<unsigned char>(cmdWord >> 24), static_cast<unsigned char>(cmdWord >> 16));
					}
				} else if (request == 9) {
					if (caravanWork != 0) {
						const unsigned int quantity = static_cast<unsigned char>(cmdWord);
						const int shopIndex = static_cast<unsigned char>(cmdWord >> 8);
						int shopItem = caravanWork->m_shopList[shopIndex];
						for (unsigned int n = 0; n < quantity; n++) {
							if (caravanWork->AddItem(shopItem, 0) == 0) {
								Joybus.SendResult(channel, 1, static_cast<unsigned char>(cmdWord >> 24),
									static_cast<unsigned char>(cmdWord >> 16));
							}
						}
						const unsigned short baseGil =
							*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + static_cast<short>(shopItem) * 0x48 + 0x20);
						const int gil =
							static_cast<int>(static_cast<float>(caravanWork->m_shopParam) / 100.0f * static_cast<float>(baseGil));
						caravanWork->AddGil(-static_cast<int>(gil * quantity));
						Joybus.SendResult(channel, 0, static_cast<unsigned char>(cmdWord >> 24), static_cast<unsigned char>(cmdWord >> 16));
					}
				} else if (request == 10) {
					if (caravanWork != 0) {
						SetSmithData(channel, cmdWord);
					}
				} else if (request == 0x0B) {
					OSWaitSemaphore(accessSemaphores + channel);
					obj[0x2D38] = static_cast<char>(obj[0x2D38] & ~static_cast<unsigned char>(shopBit));
					obj[0x2D39] = static_cast<char>(obj[0x2D39] & ~static_cast<unsigned char>(shopBit));
					OSSignalSemaphore(accessSemaphores + channel);
					for (int retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(channel, 0) == 0) {
							break;
						}
					}
					if (caravanWork != 0) {
						caravanWork->CallShop(1, 0, 0, 0, 0);
					}
				} else if (request == 0x15) {
					for (int s = 0; s < 4; s++) {
						OSWaitSemaphore(accessSemaphores + s);
					}
					obj[0x2D14] = static_cast<char>(obj[0x2D14] | static_cast<unsigned char>(playerBit));
					for (int s = 0; s < 4; s++) {
						OSSignalSemaphore(accessSemaphores + s);
					}
				}
			} else if (cmd == 0x15) {
				if (caravanWork != 0) {
					ReplyLetter(channel);
				}
			} else if ((cmd == 6) && (static_cast<unsigned char>(cmdWord >> 8) == 0x18)) {
				if (caravanWork != 0) {
					caravanWork->m_evtState1 = 1;
				}
				obj[0x2C96 + channel] = static_cast<char>(0xFF);
			} else if (cmd == 0x1C) {
				ChkCMakeName(channel, cmdWord);
			} else if (cmd == 0x1D) {
				CMakeFavorite(channel, cmdWord);
			}
		}

		if (obj[0x2C96 + channel] >= 0) {
			if ((obj[0x2C96 + channel] == 0) && (Joybus.SendMask(channel, *reinterpret_cast<unsigned short*>(obj + 0x2C8E)) == 0)) {
				obj[0x2C96 + channel] = 6;
			}
			obj[0x2C96 + channel] = static_cast<char>(obj[0x2C96 + channel] - 1);
		}

		if ((obj[0x2C89] & playerBit) != 0) {
			if (!Joybus.IsLetterMenu(channel)) {
				obj[0x2C89] = static_cast<char>(obj[0x2C89] & ~static_cast<unsigned char>(playerBit));
			} else if (Joybus.SendAddLetter(channel) == 0) {
				obj[0x2C89] = static_cast<char>(obj[0x2C89] & ~static_cast<unsigned char>(playerBit));
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChgItemData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChgMoneyData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChgEquipPosData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChgCmdLstData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetSellData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetBuyData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800CFCB8
 * PAL Size: 640b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetSmithData(int channel, unsigned int value)
{
	unsigned int* scriptFoodBase = Game.m_scriptFoodBase + channel;
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(*scriptFoodBase);
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&value);
	const unsigned int itemSlot = valueBytes[2];
	const unsigned char recipeIndex = valueBytes[3];
	const short baseItem = caravanWork->m_inventoryItems[itemSlot];

	caravanWork->DeleteItemIdx(itemSlot, 1);

	const unsigned int itemTableBase = Game.unkCFlatData0[2] + static_cast<int>(baseItem) * 0x48;
	const unsigned short smithItem = *reinterpret_cast<unsigned short*>(itemTableBase + recipeIndex * 2 + 0x38);

	unsigned int materialTable = itemTableBase;
	for (int i = 0; i < 3; i++, materialTable += 2) {
		const int materialId = *reinterpret_cast<unsigned short*>(materialTable + 0x26);
		if (materialId <= 0) {
			break;
		}

		const int materialCount = *reinterpret_cast<unsigned short*>(materialTable + 0x2C);
		if (materialCount == 0) {
			break;
		}

		for (int materialIdx = 0; materialIdx < static_cast<int>(materialCount); materialIdx++) {
			CCaravanWork* currentWork = reinterpret_cast<CCaravanWork*>(*scriptFoodBase);
			int foundSlot = 0;
			int rowBase = 0;
			int row = 0;
			int remainingRows = 8;

			do {
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 0]) == static_cast<int>(materialId)) {
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 1]) == static_cast<int>(materialId)) {
					foundSlot += 1;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 2]) == static_cast<int>(materialId)) {
					foundSlot += 2;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 3]) == static_cast<int>(materialId)) {
					foundSlot += 3;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 4]) == static_cast<int>(materialId)) {
					foundSlot += 4;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 5]) == static_cast<int>(materialId)) {
					foundSlot += 5;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 6]) == static_cast<int>(materialId)) {
					foundSlot += 6;
					break;
				}
				if (static_cast<int>(currentWork->m_inventoryItems[rowBase + 7]) == static_cast<int>(materialId)) {
					foundSlot += 7;
					break;
				}

				row++;
				rowBase += 8;
				foundSlot = row * 8;
				remainingRows--;
			} while (remainingRows != 0);

			currentWork->DeleteItemIdx(foundSlot, 1);
		}
	}

	if (reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->AddItem(smithItem, 0) == 0) {
		Joybus.SendResult(channel, 1, valueBytes[0], valueBytes[1]);
	}

	const float smithRate = static_cast<float>(reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->m_shopParam) / 100.0f;
	const int gilCost = -static_cast<int>(static_cast<float>(*reinterpret_cast<unsigned short*>(itemTableBase + 0x24)) * smithRate);
	if (reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->AddGil(gilCost) == 0) {
		Joybus.SendResult(channel, 1, valueBytes[0], valueBytes[1]);
	}

	Joybus.SendResult(channel, 0, valueBytes[0], valueBytes[1]);
}

/*
 * --INFO--
 * PAL Address: 0x800CFB6C
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetStageNo(int stageId, int mapId)
{
    char* obj = reinterpret_cast<char*>(this);
    GbaQueue* waitSemaphore = this;
    int waitIndex = 0;

    do {
        OSWaitSemaphore(waitSemaphore->accessSemaphores);
        waitIndex++;
        waitSemaphore = reinterpret_cast<GbaQueue*>(waitSemaphore->accessSemaphores + 1);
    } while (waitIndex < 4);

    obj[0x2D38] = 0;
    obj[0x2D39] = 0;
    obj[0x2D61] = 0;
    *reinterpret_cast<int*>(obj + 0x2AF8) = 0;
    obj[0x2C88] = 0;
    memset(obj + 0x2B00, 0, kGbaQueueMapObjWorkBytes);

    if ((*reinterpret_cast<int*>(obj + 0x444) != stageId) || (*reinterpret_cast<int*>(obj + 0x448) != mapId)) {
        obj[0x44C] = 0xF;
        obj[0x2D37] = 0xF;
    }

    *reinterpret_cast<int*>(obj + 0x444) = stageId;
    *reinterpret_cast<int*>(obj + 0x448) = mapId;
    obj[0x2D55] = 0xF;

    int signalIndex = 0;
    GbaQueue* signalSemaphore = this;
    do {
        OSSignalSemaphore(signalSemaphore->accessSemaphores);
        signalIndex++;
        signalSemaphore = reinterpret_cast<GbaQueue*>(signalSemaphore->accessSemaphores + 1);
    } while (signalIndex < 4);

    if (Joybus.LoadMap(stageId, mapId) == 0) {
        int loadWaitIndex = 0;
        GbaQueue* loadWaitSemaphore = this;
        do {
            OSWaitSemaphore(loadWaitSemaphore->accessSemaphores);
            loadWaitIndex++;
            loadWaitSemaphore = reinterpret_cast<GbaQueue*>(loadWaitSemaphore->accessSemaphores + 1);
        } while (loadWaitIndex < 4);

        obj[0x44C] = 0xF;
        obj[0x2D37] = 0xF;

        int loadSignalIndex = 0;
        GbaQueue* loadSignalSemaphore = this;
        do {
            OSSignalSemaphore(loadSignalSemaphore->accessSemaphores);
            loadSignalIndex++;
            loadSignalSemaphore = reinterpret_cast<GbaQueue*>(loadSignalSemaphore->accessSemaphores + 1);
        } while (loadSignalIndex < 4);
    }

    memset(m_hitInfo, 0xFF, sizeof(m_hitInfo));
    obj[0x2D54] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800CFAFC
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetStageNo(int channel, int* stageNo, int* mapNo)
{
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	*stageNo = *reinterpret_cast<int*>(obj + 0x444);
	*mapNo = *reinterpret_cast<int*>(obj + 0x448);
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800CFA84
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetStageFlg(int channel)
{
	int flag;
	char stageFlg;

	OSWaitSemaphore(accessSemaphores + channel);
	stageFlg = *(reinterpret_cast<char*>(this) + 0x44C);
	flag = static_cast<int>(stageFlg) & (1 << channel);
	flag = static_cast<unsigned int>(-flag | flag) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);

	return static_cast<unsigned int>(flag);
}

/*
 * --INFO--
 * PAL Address: 0x800CFA10
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrStageFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(obj + channel * sizeof(OSSemaphore));

	OSWaitSemaphore(semaphore);
	obj[0x44C] = obj[0x44C] & ~(1 << channel);
	m_chgScouFlags = m_chgScouFlags | (1 << channel);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800CF764
 * PAL Size: 684b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetRadarType()
{
	char* obj = reinterpret_cast<char*>(this);
	unsigned int validMemberCount;
	unsigned int activeMask;
	int assignedCount;
	int prevAssignedType;
	int i;

	if ((obj[0x2D30] != 0) || (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)) {
		return;
	}

	validMemberCount = static_cast<unsigned int>(Game.m_gameWork.m_wmBackupParams[0] >= 0);
	if (Game.m_gameWork.m_wmBackupParams[1] >= 0) {
		validMemberCount++;
	}
	if (Game.m_gameWork.m_wmBackupParams[2] >= 0) {
		validMemberCount++;
	}
	if (Game.m_gameWork.m_wmBackupParams[3] >= 0) {
		validMemberCount++;
	}

	obj[0x2D32] = 1;
	activeMask = 0;
	if ((Game.m_scriptFoodBase[0] != 0) &&
	    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->m_shopState != 0)) {
		activeMask = 1;
	}

	obj[0x2D33] = 1;
	if ((Game.m_scriptFoodBase[1] != 0) &&
	    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[1])->m_shopState != 0)) {
		activeMask |= 2;
	}

	obj[0x2D34] = 1;
	if ((Game.m_scriptFoodBase[2] != 0) &&
	    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[2])->m_shopState != 0)) {
		activeMask |= 4;
	}

	obj[0x2D35] = 1;
	if ((Game.m_scriptFoodBase[3] != 0) &&
	    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[3])->m_shopState != 0)) {
		activeMask |= 8;
	}

	assignedCount = 0;
	prevAssignedType = 0;
	while (assignedCount < static_cast<int>(validMemberCount)) {
		const int slot = rand() & 3;
		if ((activeMask & (1 << slot)) != 0) {
			int assignedType = assignedCount;
			if (assignedCount > 1) {
				if (assignedCount == 2) {
					assignedType = (rand() & 1) + 2;
				} else {
					assignedType = (prevAssignedType == 2) ? 3 : 2;
				}
			}

			OSWaitSemaphore(accessSemaphores + slot);
			obj[0x2D32 + slot] = static_cast<char>(assignedType);
			OSSignalSemaphore(accessSemaphores + slot);

			activeMask &= static_cast<unsigned int>(~(1 << slot));
			assignedCount++;
			prevAssignedType = assignedType;
		}
	}

	if (m_singleMode != 0) {
		const unsigned char radarType = Game.m_gameWork.m_mogScoreRadarType;
		obj[0x2D32] = static_cast<char>(radarType);
		obj[0x2D33] = static_cast<char>(radarType);
		obj[0x2D34] = static_cast<char>(radarType);
		obj[0x2D35] = static_cast<char>(radarType);
	}

	obj[0x2D30] = 1;
	if (Game.m_gameWork.m_bossArtifactStageIndex > 0xE) {
		obj[0x2D32] = 0;
		obj[0x2D33] = 0;
		obj[0x2D34] = 0;
		obj[0x2D35] = 0;
	}

	for (i = 0; i < 4; i++) {
		const unsigned char mask = static_cast<unsigned char>(1 << i);
		const unsigned char oldMode = static_cast<unsigned char>(obj[0x2D41]);

		OSWaitSemaphore(accessSemaphores + i);
		obj[0x2D41] = static_cast<char>((oldMode & ~mask) | mask);
		if (oldMode != static_cast<unsigned char>(obj[0x2D41])) {
			obj[0x2D42] = static_cast<char>(static_cast<unsigned char>(obj[0x2D42]) | mask);
		}
		OSSignalSemaphore(accessSemaphores + i);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CF6EC
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetMBasePos(int channel, short* outX, short* outY)
{
	int actualChannel;
	OSSemaphore* semaphore;
	char* obj = reinterpret_cast<char*>(this);
	signed char connectedFlag = m_singleMode;

	actualChannel = channel & ~((-connectedFlag | connectedFlag) >> 31);
	semaphore = accessSemaphores + actualChannel;

	OSWaitSemaphore(semaphore);
	*outX = *reinterpret_cast<short*>(obj + 0x454 + actualChannel * 0xDC + 0x36);
	*outY = *reinterpret_cast<short*>(obj + 0x454 + actualChannel * 0xDC + 0x38);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadAllStat()
{
	LoadPlayerStat();
	LoadEnemyStat();
	LoadMapItemStat();
}

/*
 * --INFO--
 * PAL Address: 0x800CEF70
 * PAL Size: 1916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::LoadPlayerStat()
{
	unsigned char localNames[kGbaQueueCaravanNameBlockBytes];
	unsigned char localPlayerStat[kGbaQueuePlayerDataBlockBytes];
	GbaQueue* semaphoreIter;
	unsigned int outOfShoukiMask;
	int i;
	char* obj;

	memset(localPlayerStat, 0, sizeof(localPlayerStat));
	memset(localNames, 0, sizeof(localNames));

	for (i = 0; i < 8; i++) {
		memcpy(localNames + (i * 0x10), Game.m_caravanWorkArr[i].unk_0x3ca_0x3dd, 0x10);
	}

	outOfShoukiMask = 0;
	if (reinterpret_cast<unsigned int*>(&CFlat)[0x1041] != 0) {
		unsigned char* entry = localPlayerStat;
		for (i = 0; i < 4; i++) {
			unsigned char menuStageMode = static_cast<unsigned char>(m_singleMode);
			CGPartyObj* partyObj;
			CCaravanWork* caravanWork;

			if ((menuStageMode == 0) || (i != 1)) {
				partyObj = Game.m_partyObjArr[i];
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
			} else {
				partyObj = Game.m_partyObjArr[0];
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
			}

			if (caravanWork != 0) {
				if ((menuStageMode == 0) || ((menuStageMode != 0) && (i == 0))) {
					entry[3] = 1;
				} else if ((menuStageMode != 0) && (i == 1) && (Game.m_scriptFoodBase[0] != 0)) {
					entry[3] = 1;
				}

				entry[0x16] = static_cast<unsigned char>(caravanWork->m_maxHp);
				entry[0x17] = static_cast<unsigned char>(caravanWork->m_hp);
				entry[2] = static_cast<unsigned char>((caravanWork->m_tribeId & 3) |
				                                      ((caravanWork->m_appearanceVariant & 3) << 2));
				if (caravanWork->m_genderFlag != 0) {
					entry[2] |= 0x80;
				}

				*reinterpret_cast<int*>(entry + 0x24) = caravanWork->m_gil;
				if (caravanWork->m_progressValue < 0x100) {
					*reinterpret_cast<unsigned short*>(entry + 0x14) = caravanWork->m_progressValue;
				} else {
					*reinterpret_cast<unsigned short*>(entry + 0x14) = 0xFF;
				}

				entry[0x18] = static_cast<unsigned char>(caravanWork->m_letterMeta[0]);
				entry[0x19] = static_cast<unsigned char>(caravanWork->m_letterMeta[1]);
				entry[0x1A] = static_cast<unsigned char>(caravanWork->m_letterMeta[2]);
				entry[0x1B] = static_cast<unsigned char>(caravanWork->m_letterMeta[3]);
				entry[0x1C] = static_cast<unsigned char>(caravanWork->m_letterMeta[4]);
				entry[0x1D] = static_cast<unsigned char>(caravanWork->m_letterMeta[5]);
				entry[0x1E] = static_cast<unsigned char>(caravanWork->m_letterMeta[6]);
				entry[0x1F] = static_cast<unsigned char>(caravanWork->m_letterMeta[7]);

				entry[0] = static_cast<unsigned char>(caravanWork->m_saveSlot);
				entry[4] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x12]);
				entry[5] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x13]);
				entry[6] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x14]);
				entry[7] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x15]);
				entry[8] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x16]);
				entry[9] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x17]);
				entry[0xA] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x18]);
				entry[0xB] = static_cast<unsigned char>(caravanWork->m_evtWordArr[0x19]);
				memcpy(entry + 0xC, &Game.m_gameWork.m_linkTable[caravanWork->m_saveSlot][0][0][0], 8);

				entry[0x20] = static_cast<unsigned char>(caravanWork->m_strength >= 100 ? 99 : caravanWork->m_strength);
				entry[0x21] = static_cast<unsigned char>(caravanWork->m_defense >= 100 ? 99 : caravanWork->m_defense);
				entry[0x22] = static_cast<unsigned char>(caravanWork->m_magic >= 100 ? 99 : caravanWork->m_magic);
				entry[0xD2] = caravanWork->m_bonusCondition;
				entry[0xD5] = static_cast<unsigned char>(caravanWork->unk_0x3ac);

				memcpy(entry + 0x3A, caravanWork->m_inventoryItems, 0x80);
				for (int artifactIndex = 0; artifactIndex < 96; artifactIndex++) {
					if (static_cast<short>(caravanWork->m_artifacts[artifactIndex]) > 0) {
						reinterpret_cast<unsigned int*>(entry + 0x28)[artifactIndex >> 5] |=
						    static_cast<unsigned int>(1U << (artifactIndex & 0x1F));
					}
				}

				*reinterpret_cast<unsigned short*>(entry + 0xBA) = caravanWork->m_treasures[0];
				*reinterpret_cast<unsigned short*>(entry + 0xBC) = caravanWork->m_treasures[1];
				*reinterpret_cast<unsigned short*>(entry + 0xBE) = caravanWork->m_treasures[2];
				*reinterpret_cast<unsigned short*>(entry + 0xC0) = caravanWork->m_treasures[3];

				entry[0xD3] = static_cast<unsigned char>(caravanWork->m_numCmdListSlots);
				*reinterpret_cast<unsigned short*>(entry + 0xC2) = caravanWork->m_commandListInventorySlotRef[0];
				*reinterpret_cast<unsigned short*>(entry + 0xC4) = caravanWork->m_commandListInventorySlotRef[1];
				*reinterpret_cast<unsigned short*>(entry + 0xC6) = caravanWork->m_commandListInventorySlotRef[2];
				*reinterpret_cast<unsigned short*>(entry + 0xC8) = caravanWork->m_commandListInventorySlotRef[3];
				*reinterpret_cast<unsigned short*>(entry + 0xCA) = caravanWork->m_commandListInventorySlotRef[4];
				*reinterpret_cast<unsigned short*>(entry + 0xCC) = caravanWork->m_commandListInventorySlotRef[5];
				*reinterpret_cast<unsigned short*>(entry + 0xCE) = caravanWork->m_commandListInventorySlotRef[6];
				*reinterpret_cast<unsigned short*>(entry + 0xD0) = caravanWork->m_commandListInventorySlotRef[7];

				entry[0xD7] = static_cast<unsigned char>(caravanWork->m_equipment[0]);
				entry[0xD8] = static_cast<unsigned char>(caravanWork->m_equipment[1]);
				entry[0xD9] = static_cast<unsigned char>(caravanWork->m_equipment[2]);
				entry[0xDA] = static_cast<unsigned char>(caravanWork->m_equipment[3]);

				entry[0x23] = 1;
				entry[0xD4] = 0;
				if (partyObj != 0) {
					entry[0xD4] = static_cast<unsigned char>((reinterpret_cast<int (*)(CGPartyObj*)>(
					                                             (*reinterpret_cast<void***>(partyObj))[0xB])(partyObj) != 0));
				}

				if ((caravanWork->IsOutOfShouki() != 0) && (entry[0x17] != 0)) {
					outOfShoukiMask |= (1U << i);
				}

				if (caravanWork->CanPlayerUseItem() != 0) {
					entry[0xD6] |= 1;
				}
				if (caravanWork->CanPlayerPutItem() != 0) {
					entry[0xD6] |= 2;
				}
			}

			if (partyObj != 0) {
				entry[1] = 1;
				*reinterpret_cast<short*>(entry + 0x36) = static_cast<short>(partyObj->m_worldPosition.x / 100.0f);
				*reinterpret_cast<short*>(entry + 0x38) = static_cast<short>(partyObj->m_worldPosition.z / 100.0f);
			}

			entry += 0xDC;
		}
	}

	i = 0;
	semaphoreIter = this;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	obj = reinterpret_cast<char*>(this);
	memcpy(obj + 0x7C4, GetPlayerDataBlock(this), kGbaQueuePlayerDataBlockBytes);
	memcpy(GetPlayerDataBlock(this), localPlayerStat, kGbaQueuePlayerDataBlockBytes);
	memcpy(obj + 0x2A74, localNames, kGbaQueueCaravanNameBlockBytes);

	obj[0x2D59] = obj[0x2D5A];
	obj[0x2D5A] = static_cast<char>(outOfShoukiMask);

	for (i = 0; i < 4; i++) {
		const int oldBase = 0x7C4 + (i * 0xDC);
		const int newBase = 0x454 + (i * 0xDC);
		int j;

		if (memcmp(obj + oldBase + 0x18, obj + newBase + 0x18, 8) != 0) {
			obj[0x2C8A] = static_cast<char>(obj[0x2C8A] | (1 << i));
		}
		if (*reinterpret_cast<int*>(obj + oldBase + 0x24) != *reinterpret_cast<int*>(obj + newBase + 0x24)) {
			obj[0x2C8B] = static_cast<char>(obj[0x2C8B] | (1 << i));
		}

		for (j = 0; j < 8; j++) {
			if (memcmp(obj + oldBase + 4, obj + newBase + 4, 8) != 0) {
				obj[0x2C96 + i] = static_cast<char>(obj[0x2C96 + i] | (1 << j));
			}
		}

		if (obj[oldBase + 0x23] != obj[newBase + 0x23]) {
			obj[0x2CAC] = static_cast<char>(obj[0x2CAC] | (1 << i));
		}
		if (memcmp(obj + oldBase + 0x20, obj + newBase + 0x20, 3) != 0) {
			obj[0x2CAD] = static_cast<char>(obj[0x2CAD] | (1 << i));
		}
		if (memcmp(obj + oldBase + 0x28, obj + newBase + 0x28, 0xC) != 0) {
			obj[0x2CAE] = static_cast<char>(obj[0x2CAE] | (1 << i));
		}
		if (*reinterpret_cast<unsigned short*>(obj + oldBase + 0x14) !=
		    *reinterpret_cast<unsigned short*>(obj + newBase + 0x14)) {
			obj[0x2C8C] = static_cast<char>(obj[0x2C8C] | (1 << i));
		}

		if (obj[oldBase + 0xD3] != obj[newBase + 0xD3]) {
			const int shift = i << 1;
			obj[0x2D41] = static_cast<char>(obj[0x2D41] | (1 << shift));
			if ((static_cast<int>(obj[newBase + 0xD3]) - static_cast<int>(obj[oldBase + 0xD3])) != 1) {
				obj[0x2D41] = static_cast<char>(obj[0x2D41] | (2 << shift));
			}
		}
	}

	i = 0;
	semaphoreIter = this;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);
}

/*
 * --INFO--
 * PAL Address: 0x800CED98
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::LoadEnemyStat()
{
	unsigned char localEnemyData[kGbaQueueEnemyDataBytes];
	unsigned int* enemyObjPtrs;
	unsigned int* enemyWorkPtrs;
	GbaQueue* semaphoreIter;
	int i;

	memset(localEnemyData, 0, sizeof(localEnemyData));

	if (reinterpret_cast<unsigned int*>(&CFlat)[0x1041] != 0) {
		unsigned char* enemyEntry = localEnemyData;
		enemyObjPtrs = &Game.m_scriptWork[0][0][0];
		enemyWorkPtrs = &Game.m_scriptWork[2][0][0];

		for (i = 0; i < 0x40; i++) {
			if (enemyObjPtrs[i] == 0) {
				enemyEntry[3] = 0;
			} else {
				CGObject* enemyObj = reinterpret_cast<CGObject*>(enemyObjPtrs[i]);
				CMonWork* enemyWork = reinterpret_cast<CMonWork*>(enemyWorkPtrs[i]);
				const int enemyDataBase = Game.unkCFlatData0[1] + enemyWork->m_baseDataIndex * 0x1D0;
				const int enemyKind = *reinterpret_cast<short*>(enemyDataBase + 0x10C);

				if (enemyKind == 10) {
					enemyEntry[1] = 1;
				} else if (enemyKind == 0xB) {
					enemyEntry[1] = 3;
				} else {
					enemyEntry[1] = 2;
				}

				enemyEntry[3] = static_cast<unsigned char>(enemyWork->m_baseDataIndex);
				*reinterpret_cast<unsigned short*>(enemyEntry + 4) = enemyWork->m_hp;
				*reinterpret_cast<unsigned short*>(enemyEntry + 6) = enemyWork->m_maxHp;
				int isDispRadar = static_cast<int>(enemyObj->IsDispRader());
				int isDispRadarMask = -isDispRadar | isDispRadar;
				enemyEntry[2] = static_cast<unsigned char>(isDispRadarMask >> 31);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0xC) =
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(enemyObj) + 0x510);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0xE) =
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(enemyObj) + 0x512);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0x10) =
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(enemyObj) + 0x514);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0x12) =
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(enemyObj) + 0x516);
				long long posX = static_cast<int>(enemyObj->m_worldPosition.x / kGbaQueueMapCoordScale);
				*reinterpret_cast<short*>(enemyEntry + 8) = static_cast<short>(posX);
				long long posZ = static_cast<int>(enemyObj->m_worldPosition.z / kGbaQueueMapCoordScale);
				*reinterpret_cast<short*>(enemyEntry + 0xA) = static_cast<short>(posZ);
			}

			enemyEntry += 0x14;
		}
	}

	i = 0;
	semaphoreIter = this;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	memcpy(reinterpret_cast<char*>(this) + 0xB34, localEnemyData, sizeof(localEnemyData));

	i = 0;
	semaphoreIter = this;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);
}

/*
 * --INFO--
 * PAL Address: 0x800cebe4
 * PAL Size: 436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::LoadMapItemStat()
{
	unsigned char localMapItems[kGbaQueueMapItemDataBytes];
	char numMapItems;
	CGObject* object;
	GbaQueue* semaphoreIter;
	int i;

	memset(localMapItems, 0, sizeof(localMapItems));
	numMapItems = 0;

	if (reinterpret_cast<unsigned int*>(&CFlat)[0x1041] != 0) {
		unsigned char* mapItemEntry = localMapItems;
		object = gCFlatRuntime2.FindGObjFirst();

		while (object != 0) {
			if ((object->m_objectFlags & 0x100) != 0) {
				if ((object->m_dropItemCodes[0] & 0xC000) == 0x4000) {
					mapItemEntry[1] = 4;
				} else {
					const int itemDataBase = Game.unkCFlatData0[2];
					const int bossStageLimit = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex] + 2;
					const int itemStage = *reinterpret_cast<unsigned short*>(itemDataBase + object->m_dropItemCodes[0] * 0x48 + 0xC);
					mapItemEntry[1] = (itemStage < bossStageLimit) ? 4 : 5;
				}

				int isDispRader = object->IsDispRader();
				numMapItems++;
				mapItemEntry[2] = static_cast<unsigned char>((-isDispRader | isDispRader) >> 31);
				*reinterpret_cast<short*>(mapItemEntry + 8) = static_cast<short>(object->m_worldPosition.x / 100.0f);
				*reinterpret_cast<short*>(mapItemEntry + 0xA) = static_cast<short>(object->m_worldPosition.z / 100.0f);
				mapItemEntry += 0x14;
			}

			object = gCFlatRuntime2.FindGObjNext(object);
		}
	}

	reinterpret_cast<char*>(this)[0x2AF4] = numMapItems;

	i = 0;
	semaphoreIter = this;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	memcpy(reinterpret_cast<char*>(this) + 0x2434, localMapItems, sizeof(localMapItems));

	i = 0;
	semaphoreIter = this;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);
}

/*
 * --INFO--
 * PAL Address: 0x800CE9AC
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetPlayerPos(int channel, unsigned int* outData)
{
	GbaQueuePlayerPosView localPlayerData[4];
	unsigned char packet[0xC];
	int i;
	unsigned int nearbyMask;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + 0x454, sizeof(localPlayerData));
	OSSignalSemaphore(accessSemaphores + channel);

	memset(packet, 0, sizeof(packet));

	if (m_singleMode != 0) {
		channel = 0;
	}

	packet[0] = 0x11;
	packet[4] = 0x51;
	packet[8] = 0x91;

	const GbaQueuePlayerPosView* basePlayer = &localPlayerData[channel];

	nearbyMask = 0;
	const GbaQueuePlayerPosView* player = localPlayerData;
	for (i = 0; i < 4;) {
		if (i == channel) {
			nearbyMask = (nearbyMask | (1 << i)) & 0xFF;
		} else if (player[0].m_active != 0) {
			int px = player[0].m_posX;
			const int dx = px - basePlayer->m_posX;

			if (dx >= -0x50 && dx <= 0x50) {
				int pz = player[0].m_posZ;
				const int dz = pz - basePlayer->m_posZ;

				if (dz >= -0x40 && dz <= 0x40) {
					nearbyMask = (nearbyMask | (1 << i)) & 0xFF;
				}
			}
		}

		i++;

		if (i == channel) {
			nearbyMask = (nearbyMask | (1 << i)) & 0xFF;
		} else if (player[1].m_active != 0) {
			int px = player[1].m_posX;
			const int dx = px - basePlayer->m_posX;

			if (dx >= -0x50 && dx <= 0x50) {
				int pz = player[1].m_posZ;
				const int dz = pz - basePlayer->m_posZ;

				if (dz >= -0x40 && dz <= 0x40) {
					nearbyMask = (nearbyMask | (1 << i)) & 0xFF;
				}
			}
		}

		player += 2;
		i++;
	}

	packet[1] = static_cast<unsigned char>(nearbyMask);
	packet[2] = static_cast<unsigned char>(localPlayerData[0].m_posX - basePlayer->m_posX);
	packet[3] = static_cast<unsigned char>(localPlayerData[0].m_posZ - basePlayer->m_posZ);
	packet[5] = static_cast<unsigned char>(localPlayerData[1].m_posX - basePlayer->m_posX);
	packet[6] = static_cast<unsigned char>(localPlayerData[1].m_posZ - basePlayer->m_posZ);
	packet[7] = static_cast<unsigned char>(localPlayerData[2].m_posX - basePlayer->m_posX);
	packet[9] = static_cast<unsigned char>(localPlayerData[2].m_posZ - basePlayer->m_posZ);
	packet[10] = static_cast<unsigned char>(localPlayerData[3].m_posX - basePlayer->m_posX);
	packet[11] = static_cast<unsigned char>(localPlayerData[3].m_posZ - basePlayer->m_posZ);

	memcpy(outData, packet, sizeof(packet));
}

/*
 * --INFO--
 * PAL Address: 0x800CE76C
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetEnemyPos(int channel, unsigned int* outData, int* outCount)
{
    char localEnemyData[0x508];
    char* obj;
    char radarMode;
    short baseX;
    short baseZ;
    int count;
    int i;
    char* localEntry;
    char* prevEntry;
    unsigned char* outPtr;

    obj = reinterpret_cast<char*>(this);

    OSWaitSemaphore(accessSemaphores + channel);
    unsigned int singleMode = (unsigned int)__cntlzw(1 - static_cast<int>(m_singleMode)) >> 5;
    OSSignalSemaphore(accessSemaphores + channel);
    if ((singleMode & 0xFFU) != 0U) {
        channel = 0;
    }

    OSWaitSemaphore(accessSemaphores + channel);

    baseX = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x32);
    baseZ = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x34);
    memcpy(localEnemyData, obj + 0xB34, kGbaQueueEnemyDataBytes);

    prevEntry = obj + channel * kGbaQueueEnemyDataBytes + 0x1034;
    radarMode = obj[channel + 0x2D32];
    localEntry = localEnemyData;
    for (i = 0; i < 0x40; i++) {
        *reinterpret_cast<short*>(localEntry + 8) = *reinterpret_cast<short*>(localEntry + 8) - baseX;
        *reinterpret_cast<short*>(localEntry + 10) = *reinterpret_cast<short*>(localEntry + 10) - baseZ;

        int enemyX = *reinterpret_cast<short*>(localEntry + 8);
        if ((enemyX < 0 ? -enemyX : enemyX) < 0x50) {
            int enemyZ = *reinterpret_cast<short*>(localEntry + 10);
            if ((enemyZ < 0 ? -enemyZ : enemyZ) < 0x40) {
                localEntry[0] = 1;
            } else {
                *reinterpret_cast<short*>(localEntry + 8) = -1;
                *reinterpret_cast<short*>(localEntry + 10) = -1;
                localEntry[0] = 0;
            }
        } else {
            *reinterpret_cast<short*>(localEntry + 8) = -1;
            *reinterpret_cast<short*>(localEntry + 10) = -1;
            localEntry[0] = 0;
        }

        if (*reinterpret_cast<unsigned short*>(localEntry + 4) == 0 || localEntry[2] == 0) {
            localEntry[0] = 0;
        }

        if (radarMode == 2 || radarMode == 0) {
            localEntry[0] = 0;
        } else if (radarMode == 3 && localEntry[1] == 1) {
            localEntry[0] = 0;
        }

        localEntry += 0x14;
    }

    count = 0;
    localEntry = localEnemyData;
    outPtr = reinterpret_cast<unsigned char*>(outData);
    for (i = 0; i < 0x40; i++) {
        if ((localEntry[0] != 0 || prevEntry[0] != 0) && memcmp(localEntry, prevEntry, 0x14) != 0) {
            count++;
            outPtr[0] = 0x12;
            outPtr[1] = static_cast<unsigned char>(i) | (static_cast<unsigned char>(localEntry[0]) << 7);
            outPtr[2] = static_cast<unsigned char>(*reinterpret_cast<short*>(localEntry + 8));
            outPtr[3] = static_cast<unsigned char>(*reinterpret_cast<short*>(localEntry + 10));
            outPtr += 4;
        }

        localEntry += 0x14;
        prevEntry += 0x14;
    }

    *outCount = count;
    memcpy(obj + channel * kGbaQueueEnemyDataBytes + 0x1034, localEnemyData, kGbaQueueEnemyDataBytes);
    OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800CE56C
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetTreasurePos(int channel, unsigned int* outData, int* outCount)
{
	char localMapItems[kGbaQueueMapItemDataBytes];
	char* obj;
	char* localEntry;
	char* prevEntry;
	unsigned char* outPtr;
	short baseX;
	short baseZ;
	int count;
	int i;

	obj = reinterpret_cast<char*>(this);

	if (m_singleMode != 0) {
		channel = 0;
	}

	OSWaitSemaphore(accessSemaphores + channel);

	baseX = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x48A);
	baseZ = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x48C);
	memcpy(localMapItems, obj + 0x2434, sizeof(localMapItems));

	localEntry = localMapItems;
	for (i = 0; i < static_cast<unsigned char>(obj[0x2AF4]); i++) {
		int localX = static_cast<int>(*reinterpret_cast<short*>(localEntry + 8)) - static_cast<int>(baseX);
		int localZ = static_cast<int>(*reinterpret_cast<short*>(localEntry + 10)) - static_cast<int>(baseZ);

		*reinterpret_cast<short*>(localEntry + 8) = static_cast<short>(localX);
		*reinterpret_cast<short*>(localEntry + 10) = static_cast<short>(localZ);

		if ((localX < 0 ? -localX : localX) < 0x50 && (localZ < 0 ? -localZ : localZ) < 0x40) {
			localEntry[0] = 1;
		} else {
			localEntry[8] = -1;
			localEntry[9] = -1;
			localEntry[10] = -1;
			localEntry[11] = -1;
			localEntry[0] = 0;
		}

		if (localEntry[2] == 0 || obj[channel + 0x2D32] != 3) {
			localEntry[0] = 0;
		}

		localEntry += 0x14;
	}

	count = 0;
	localEntry = localMapItems;
	prevEntry = obj + channel * kGbaQueueMapItemDataBytes + 0x2574;
	outPtr = reinterpret_cast<unsigned char*>(outData);
	for (i = 0; i < static_cast<unsigned char>(obj[0x2AF4]); i++) {
		if ((localEntry[0] != 0 || prevEntry[0] != 0) && memcmp(localEntry, prevEntry, 0x14) != 0) {
			count++;
			outPtr[0] = 0x21;
			outPtr[1] = static_cast<unsigned char>(i + 0x40) | (static_cast<unsigned char>(localEntry[0]) << 7);
			outPtr[2] = static_cast<unsigned char>(*reinterpret_cast<short*>(localEntry + 8));
			outPtr[3] = static_cast<unsigned char>(*reinterpret_cast<short*>(localEntry + 10));
			outPtr += 4;
		}

		localEntry += 0x14;
		prevEntry += 0x14;
	}

	*outCount = count;
	memcpy(obj + channel * kGbaQueueMapItemDataBytes + 0x2574, localMapItems, sizeof(localMapItems));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800CE3F8
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetMapObjInfo(int channel, unsigned char* outData)
{
	unsigned char* obj = reinterpret_cast<unsigned char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);

	unsigned char* mapObj = obj + 0xB35;
	int count = 4;
	do {
		unsigned char* out = outData;
		out[0] = mapObj[0x000];
		out[1] = mapObj[0x014];
		out[2] = mapObj[0x028];
		out[3] = mapObj[0x03C];
		out[4] = mapObj[0x050];
		out[5] = mapObj[0x064];
		out[6] = mapObj[0x078];
		out[7] = mapObj[0x08C];
		out[8] = mapObj[0x0A0];
		out[9] = mapObj[0x0B4];
		out[10] = mapObj[0x0C8];
		out[11] = mapObj[0x0DC];
		out[12] = mapObj[0x0F0];
		out[13] = mapObj[0x104];
		out[14] = mapObj[0x118];
		out[15] = mapObj[0x12C];
		mapObj += 0x140;
		count--;
		outData += 0x10;
	} while (count != 0);

	for (int i = 0; i < 0x10; i++) {
		outData[i] = obj[0x2435 + i * 0x14];
	}

	OSSignalSemaphore(accessSemaphores + channel);
	return 0x50;
}

/*
 * --INFO--
 * PAL Address: 0x800CE394
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetPlayerStat(int channel, GbaPInfo* outInfo)
{
	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(outInfo, GetPlayerDataBlock(this), sizeof(*outInfo));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800CE300
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetCaravanName(char* outName)
{
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);
	}

	memcpy(outName, reinterpret_cast<char*>(this) + 0x2A74, kGbaQueueCaravanNameBlockBytes);

	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(accessSemaphores + i);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CDFC0
 * PAL Size: 832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetItemAll(int channel, unsigned char* outData)
{
	GbaQueuePlayerDataView localPlayerData;
	unsigned short itemList[0x40];
	unsigned int artifacts[3];
	unsigned short tmpArtifacts[4];
	unsigned short artifactList[8];
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	localPlayerData = *GetPlayerDataView(this, channel);
	OSSignalSemaphore(accessSemaphores + channel);

	for (i = 0; i < 0x40; i++) {
		itemList[i] = __lhbrx(&localPlayerData.m_items[i], 0);
	}
	memcpy(outData, itemList, sizeof(itemList));

	artifacts[0] = __lwbrx(&localPlayerData.m_artifacts[0], 0);
	artifacts[1] = __lwbrx(&localPlayerData.m_artifacts[1], 0);
	artifacts[2] = __lwbrx(&localPlayerData.m_artifacts[2], 0);
	memcpy(outData + 0x80, artifacts, sizeof(artifacts));

	for (i = 0; i < 4; i++) {
		tmpArtifacts[i] = __lhbrx(&localPlayerData.m_tmpArtifacts[i], 0);
	}
	memcpy(outData + 0x8C, tmpArtifacts, sizeof(tmpArtifacts));

	outData[0x94] = localPlayerData.m_commandData[0];
	outData[0x95] = localPlayerData.m_commandData[1];
	outData[0x96] = localPlayerData.m_commandData[2];
	outData[0x97] = localPlayerData.m_commandData[3];

	for (i = 0; i < 8; i++) {
		artifactList[i] = __lhbrx(&localPlayerData.m_artifactList[i], 0);
	}
	memcpy(outData + 0x98, artifactList, sizeof(artifactList));

	outData[0xA8] = localPlayerData.m_artifactCount;
	return 0xA9;
}

/*
 * --INFO--
 * PAL Address: 0x800CDF38
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetScrFlg()
{
	int i;
	OSSemaphore* semaphoreIter;
	unsigned int flag;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	flag = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x2AF8);
	flag = (-flag | flag) >> 31;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSSignalSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	return flag;
}

/*
 * --INFO--
 * PAL Address: 0x800CDDEC
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetPlayerHP(int channel, unsigned char* outData)
{
	char* obj = reinterpret_cast<char*>(this);
	char hpFlags = 0;
	char prevHpFlags = 0;
	char hp;
	char prevHp;

	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);

		char* playerData = obj + i * 0xDC;
		if (i == channel) {
			hp = playerData[0x46B];
			prevHp = playerData[0x7DB];
		}
		if (playerData[0x46B] != 0) {
			hpFlags = static_cast<char>(hpFlags | (1 << i));
		}
		if (playerData[0x7DB] != 0) {
			prevHpFlags = static_cast<char>(prevHpFlags | (1 << i));
		}

		OSSignalSemaphore(accessSemaphores + i);
	}

	int hpChanged = hp != prevHp;
	unsigned int changed = static_cast<unsigned int>(
	    (static_cast<int>(prevHpFlags) - static_cast<int>(hpFlags)) |
	    (static_cast<int>(hpFlags) - static_cast<int>(prevHpFlags))) >> 31;
	if (hpChanged) {
		changed = 1;
	}

	int channelMask = 1 << channel;
	if (hp != prevHp) {
		changed = 1;
	}
	if ((obj[0x2D5A] & channelMask) != (obj[0x2D59] & channelMask)) {
		changed = 1;
	}

	outData[0] = 0x13;
	outData[1] = static_cast<unsigned char>(hpFlags);
	outData[2] = static_cast<unsigned char>(hp);
	outData[3] = ((obj[0x2D5A] & channelMask) != 0);

	return changed;
}

/*
 * --INFO--
 * PAL Address: 0x800cd850
 * PAL Size: 1436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::MakeLetterList(int channel, char* outData)
{
	const unsigned int scriptFood = Game.m_scriptFoodBase[channel];

	if (scriptFood == 0) {
		const unsigned int channelMask = 1U << channel;

		GetFlagView(this)->m_letterDatFlg |= channelMask;
		Joybus.SetLetterSize(channel, 0);
		m_letterFlags &= ~channelMask;
		return 0;
	}

char* npcNameBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7A7) char[kGbaQueueLetterNpcNameBytes];
	if (npcNameBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0x7A9);
		}
		return -1;
	}
	memset(npcNameBuf, 0, kGbaQueueLetterNpcNameBytes);

char* subjectNameBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7B1) char[kGbaQueueLetterSubjectNameBytes];
	if (subjectNameBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0x7B3);
		}
		return -1;
	}
	memset(subjectNameBuf, 0, kGbaQueueLetterSubjectNameBytes);

unsigned int* letterEntryBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7BB) unsigned int[kGbaQueueLetterEntryAllocWords];
	if (letterEntryBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0x7BD);
		}
		return -1;
	}
	memset(letterEntryBuf, 0, kGbaQueueLetterEntryBytes);

	const CCaravanWork* caravanWork = reinterpret_cast<const CCaravanWork*>(scriptFood);
	const unsigned int letterCount = static_cast<unsigned int>(caravanWork->m_letterCount);

	unsigned int subjectCount = 0;
	unsigned int npcCount = 0;

	char* npcWrite = npcNameBuf;
	char* subjectWrite = subjectNameBuf;
	unsigned int* entryWrite = letterEntryBuf;

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
	char tempName[kGbaQueueLetterTempNameBytes];

	for (int i = 0; i < static_cast<int>(letterCount); i++) {
		int matchedSubject = -1;
		int matchedNpc = -1;

		const unsigned int* cur = reinterpret_cast<const unsigned int*>(scriptFood + 0x3EC + i * 0xC);
		const unsigned int curWord = cur[0];
		const unsigned short curHalf = *reinterpret_cast<const unsigned short*>(cur);

		for (int j = 0; j < i; j++) {
			const unsigned int* prev = reinterpret_cast<const unsigned int*>(scriptFood + 0x3EC + j * 0xC);
			if (((curWord >> 9) & 0x1FF) == ((prev[0] >> 9) & 0x1FF)) {
				matchedNpc = j;
			}
			if (((curHalf >> 2) & 0x1FF) == ((*reinterpret_cast<const unsigned short*>(prev) >> 2) & 0x1FF)) {
				matchedSubject = j;
			}
			if (matchedSubject != -1 && matchedNpc != -1) {
				break;
			}
		}

		if (matchedNpc == -1) {
			if (npcCount > 0x7F && (unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_npc_max_over), const_cast<char*>(s_gbaque_cpp), 0x7DC);
			}

			memset(tempName, 0, sizeof(tempName));
			strcpy(tempName, flatData->m_tabl[2].m_strings[(curWord >> 9) & 0x1FF]);
			memcpy(npcWrite, tempName, kGbaQueueLetterNpcNameEntryBytes);
			npcWrite += kGbaQueueLetterNpcNameEntryBytes;
			(reinterpret_cast<unsigned char*>(entryWrite))[5] = static_cast<unsigned char>(npcCount);
			npcCount++;
		} else {
			(reinterpret_cast<unsigned char*>(entryWrite))[5] =
				(reinterpret_cast<unsigned char*>(letterEntryBuf + matchedNpc * 2))[5];
		}

		if (matchedSubject == -1) {
			if (subjectCount > 0xFF && (unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_subject_max_over), const_cast<char*>(s_gbaque_cpp), 0x7F0);
			}

			memset(tempName, 0, sizeof(tempName));
			strcpy(tempName, flatData->m_tabl[5].m_strings[(curHalf >> 2) & 0x1FF]);
			memcpy(subjectWrite, tempName, kGbaQueueLetterSubjectNameEntryBytes);
			subjectWrite += kGbaQueueLetterSubjectNameEntryBytes;
			(reinterpret_cast<unsigned char*>(entryWrite))[4] = static_cast<unsigned char>(subjectCount);
			subjectCount++;
		} else {
			(reinterpret_cast<unsigned char*>(entryWrite))[4] =
				(reinterpret_cast<unsigned char*>(letterEntryBuf + matchedSubject * 2))[4];
		}

		unsigned char flags = 0;
		if ((curWord & 0x80000000U) != 0) {
			flags |= 1;
		}
		if ((curWord & 0x40) != 0) {
			flags |= 2;
		}
		if ((curWord & 0x20) != 0) {
			flags |= 4;
		}
		if ((curWord & 0x10) != 0) {
			flags |= 8;
		}

		const unsigned int value = *reinterpret_cast<const unsigned short*>(scriptFood + 0x3EE + i * 0xC) & 0x1FF;
		if ((curWord & 8) == 0) {
			if (value != 0) {
				if (value < 0x100 || value > 0x124) {
					flags |= 0x10;
					entryWrite[0] = SwapU32(value);
				} else if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_letter_data_error), const_cast<char*>(s_gbaque_cpp), 0x810, channel, i);
				}
			}
		} else if (value != 0) {
			flags |= 0x20;
			entryWrite[0] = SwapU32(value * 100);
		}

		(reinterpret_cast<unsigned char*>(entryWrite))[6] = flags;
		entryWrite += 2;
	}

	unsigned int header[4];
	memset(header, 0, sizeof(header));
	header[0] = SwapU32(letterCount);
	header[1] = SwapU32(subjectCount);
	header[2] = SwapU32(npcCount);
	header[3] = reinterpret_cast<unsigned int*>(&CFlat)[0x1042];

	memcpy(outData, header, sizeof(header));

	const int entriesSize = static_cast<int>(letterCount * 8);
	memcpy(outData + kGbaQueueLetterHeaderBytes, letterEntryBuf, entriesSize);

	char* dst = outData + kGbaQueueLetterHeaderBytes + entriesSize;
	const int subjectSize = static_cast<int>(subjectCount * kGbaQueueLetterSubjectNameEntryBytes);
	memcpy(dst, subjectNameBuf, subjectSize);
	memcpy(dst + subjectSize, npcNameBuf, static_cast<int>(npcCount * kGbaQueueLetterNpcNameEntryBytes));

	const int totalSize = entriesSize + kGbaQueueLetterHeaderBytes + subjectSize +
	                      static_cast<int>(npcCount * kGbaQueueLetterNpcNameEntryBytes);

	delete[] letterEntryBuf;
	delete[] subjectNameBuf;
	delete[] npcNameBuf;

	const unsigned int channelMask = 1U << channel;

	GetFlagView(this)->m_letterDatFlg |= channelMask;
	Joybus.SetLetterSize(channel, totalSize);
	m_letterFlags &= ~channelMask;
	return totalSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::MakeLetterData(int channel, char* outData, int letterIndex)
{
char* srcText = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x859) char[kGbaQueueScratchTextSize];
    if (srcText == 0) {
        if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0x85B);
        }
        return -1;
    }
    memset(srcText, 0, kGbaQueueScratchTextSize);

char* workText = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x862) char[kGbaQueueScratchTextSize];
    if (workText == 0) {
        if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0x864);
        }
        return -1;
    }
    memset(workText, 0, kGbaQueueScratchTextSize);

    unsigned int scriptFood = Game.m_scriptFoodBase[channel];
    int entry = scriptFood + letterIndex * 0xC;
    CMes::m_tempVar[0] = *reinterpret_cast<unsigned short*>(entry + 0x3F0);
    CMes::m_tempVar[1] = *reinterpret_cast<unsigned short*>(entry + 0x3F2);
    CMes::m_tempVar[2] = *reinterpret_cast<unsigned short*>(entry + 0x3F4);
    CMes::m_tempVar[3] = *reinterpret_cast<unsigned short*>(entry + 0x3F6);

    unsigned short msgIndex = *reinterpret_cast<unsigned short*>(entry + 0x3EC);
    int mesIndex = (msgIndex & 0x7FC) >> 1;
    char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<char*>(&Game.m_cFlatDataArr[1]) + 0x44);

    strcpy(srcText, mesPtr[mesIndex]);
    CMes::MakeAgbString(workText, srcText, *reinterpret_cast<unsigned short*>(scriptFood + 0x3E2), 0);
    int totalSize = static_cast<int>(strlen(workText) + 1);
    memcpy(outData, workText, totalSize);

    memset(srcText, 0, kGbaQueueScratchTextSize);
    memset(workText, 0, kGbaQueueScratchTextSize);
    strcpy(srcText, mesPtr[mesIndex + 1]);
    CMes::MakeAgbString(workText, srcText, *reinterpret_cast<unsigned short*>(scriptFood + 0x3E2), 0);
    int line2Size = static_cast<int>(strlen(workText));
    memcpy(outData + totalSize, workText, line2Size + 1);
    totalSize += line2Size + 1;

	delete[] workText;
	delete[] srcText;

    GetFlagView(this)->m_letterDatFlg =
        static_cast<unsigned char>(GetFlagView(this)->m_letterDatFlg | static_cast<unsigned char>(0x10 << channel));
    Joybus.SetLetterSize(channel, totalSize);
    return totalSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetLetterLstFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(flags->m_letterDatFlg)) & (1 << channel);
	value = (-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800cd50c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrLetterLstFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_letterDatFlg = static_cast<unsigned char>(flags->m_letterDatFlg & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetLetterDatFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(flags->m_letterDatFlg)) & (0x10 << channel);
	value = (-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800cd418
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrLetterDatFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_letterDatFlg = static_cast<unsigned char>(flags->m_letterDatFlg & ~(0x10 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800CD2DC
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::MoveLetterItem(int channel, unsigned int value)
{
	unsigned int stackValue = value;
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&stackValue);
	unsigned int* scriptFoodBase = Game.m_scriptFoodBase + channel;
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(*scriptFoodBase);
	int letterIndex = valueBytes[2];
	int letterOffset = letterIndex * 0xC;
	unsigned char* letter = reinterpret_cast<unsigned char*>(caravanWork) + letterOffset;
	int hasGil = (letter[0x3EC] >> 3) & 1;
	int result;

	if (hasGil == 0) {
		int item = *reinterpret_cast<unsigned short*>(letter + 0x3EE) & 0x1FF;
		if (item != 0) {
			if ((item < 1) || (item > 0x9E)) {
				if (caravanWork->AddItem(item, 0) == 0) {
					result = 1;
				} else {
					result = 0;
				}
			}
		}
	}
	if (hasGil != 0) {
		int item = *reinterpret_cast<unsigned short*>(letter + 0x3EE) & 0x1FF;
		if (item != 0) {
			int gil = item * 100;
			if (caravanWork->CanAddGil(gil) == 0) {
				result = 1;
			} else {
				reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->AddGil(gil);
				result = 0;
			}
		}
	}

	int i = 0;
	do {
		if (Joybus.SendResult(channel, result, valueBytes[0], valueBytes[1]) == 0) {
			break;
		}
		i++;
	} while (i < 10);

	if ((result == 0) && (i < 10)) {
		unsigned char* letterBase = reinterpret_cast<unsigned char*>(*scriptFoodBase);
		int readFlag = 1;
		letterBase[letterOffset + 0x3EC] =
			static_cast<unsigned char>((letterBase[letterOffset + 0x3EC] & 0xBF) | ((readFlag << 6) & 0x40));
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CD1CC
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ReplyLetter(int channel)
{
	unsigned char recvBuffer[0x400];

	Joybus.GetRecvBuffer(channel, recvBuffer);

	unsigned int value =
		(static_cast<unsigned int>(recvBuffer[3]) << 24) |
		(static_cast<unsigned int>(recvBuffer[4]) << 16) |
		(static_cast<unsigned int>(recvBuffer[5]) << 8) |
		recvBuffer[6];
	unsigned int itemId = 0;
	unsigned int gil = value;

	if (recvBuffer[2] == 0) {
		itemId = (static_cast<unsigned int>(recvBuffer[5]) << 8) | recvBuffer[6];
		gil = 0;
	}

	unsigned int* scriptFoodBase = Game.m_scriptFoodBase + channel;
	reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->FGLetterReply(recvBuffer[0], recvBuffer[1], itemId, gil);
	Joybus.ClrRecvBuffer(channel);
	Joybus.SendResult(channel, 0, 0x15, 0);

	if (recvBuffer[2] != 0) {
		reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->AddGil(-static_cast<int>(gil));
	} else if (itemId != 0) {
		reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->DeleteItemIdx(static_cast<int>(value) >> 16, 1);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadMapObj()
{
	unsigned char* obj = reinterpret_cast<unsigned char*>(this);
	GbaQueue* semaphoreIter;
	int i;

	if (*reinterpret_cast<unsigned int*>(obj + 0x2AF8) == 0) {
		i = 0;
		semaphoreIter = this;
		do {
			OSWaitSemaphore(semaphoreIter->accessSemaphores);
			i++;
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		} while (i < 4);

		if (obj[0x2B00] != 0) {
			memset(obj + 0x2B00, 0, kGbaQueueMapObjWorkBytes);
		}

		i = 0;
		semaphoreIter = this;
		do {
			OSSignalSemaphore(semaphoreIter->accessSemaphores);
			i++;
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		} while (i < 4);
	} else {
		unsigned char mapObjWork[kGbaQueueMapObjWorkBytes];
		memset(mapObjWork, 0, sizeof(mapObjWork));

		char* mapObjBase = reinterpret_cast<char*>(&CFlat) + 0x134C;
		for (i = 0; i < 0x20; i++) {
			char objType = mapObjBase[0];
			if (objType != -1) {
				unsigned int count = mapObjWork[0];
				if (objType < 0x19) {
					float x = *reinterpret_cast<float*>(mapObjBase + 4);
					float y = *reinterpret_cast<float*>(mapObjBase + 8);
					float z = *reinterpret_cast<float*>(mapObjBase + 0xC);
					float r = *reinterpret_cast<float*>(mapObjBase + 0x10);
					unsigned int entryBase = count * 0xC;

					mapObjWork[8 + entryBase] = static_cast<unsigned char>(objType);
					*reinterpret_cast<short*>(mapObjWork + 0xC + entryBase) =
						static_cast<short>((int)(x / kGbaQueueMapCoordScale));
					*reinterpret_cast<short*>(mapObjWork + 0xE + entryBase) =
						static_cast<short>((int)(y / kGbaQueueMapCoordScale));
					*reinterpret_cast<short*>(mapObjWork + 0x10 + entryBase) =
						static_cast<short>((int)(z / kGbaQueueMapCoordScale));
					*reinterpret_cast<short*>(mapObjWork + 0x12 + entryBase) =
						static_cast<short>((int)(r / kGbaQueueMapCoordScale));

					unsigned int mask = 1U << count;
					unsigned int drawMask = *reinterpret_cast<unsigned int*>(mapObjWork + 4);
					if (mapObjBase[1] != 0) {
						drawMask |= mask;
					} else {
						drawMask &= ~mask;
					}
					*reinterpret_cast<unsigned int*>(mapObjWork + 4) = drawMask;
					mapObjWork[0] = static_cast<unsigned char>(count + 1);
				} else if (System.m_execParam > 1) {
System.Printf(const_cast<char*>(s_unknown_mapobj_type_error), objType);
				}
			}

			mapObjBase += 0x14;
		}

		i = 0;
		semaphoreIter = this;
		do {
			OSWaitSemaphore(semaphoreIter->accessSemaphores);
			i++;
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		} while (i < 4);

		memcpy(obj + 0x2B00, mapObjWork, sizeof(mapObjWork));

		i = 0;
		semaphoreIter = this;
		do {
			OSSignalSemaphore(semaphoreIter->accessSemaphores);
			i++;
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		} while (i < 4);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CCE38
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetMapObj(unsigned char* outData)
{
	unsigned char mapObjWork[kGbaQueueMapObjWorkBytes];
	unsigned char* workEntry;
	GbaQueue* semaphoreIter;
	int i;
	int outSize;
	unsigned int drawFlags;

	i = 0;
	semaphoreIter = this;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	memcpy(mapObjWork, reinterpret_cast<char*>(this) + 0x2B00, sizeof(mapObjWork));

	i = 0;
	semaphoreIter = this;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	workEntry = mapObjWork;
	outSize = 5;
	outData[0] = mapObjWork[0];
	drawFlags = *reinterpret_cast<unsigned int*>(mapObjWork + 4);
	outData[1] = static_cast<unsigned char>(drawFlags);
	outData[2] = static_cast<unsigned char>(drawFlags >> 8);
	outData[3] = static_cast<unsigned char>(drawFlags >> 16);
	outData[4] = static_cast<unsigned char>(drawFlags >> 24);

	for (i = 0; i < mapObjWork[0]; i++) {
		outData[outSize] = workEntry[8];
		outSize++;
		outData[outSize] = static_cast<unsigned char>(*reinterpret_cast<short*>(workEntry + 0xC));
		outSize++;
		outData[outSize] =
			static_cast<unsigned char>(static_cast<unsigned short>(*reinterpret_cast<short*>(workEntry + 0xC)) >> 8);
		outSize++;
		outData[outSize] = static_cast<unsigned char>(*reinterpret_cast<short*>(workEntry + 0xE));
		outSize++;
		outData[outSize] =
			static_cast<unsigned char>(static_cast<unsigned short>(*reinterpret_cast<short*>(workEntry + 0xE)) >> 8);
		outSize++;
		outData[outSize] = static_cast<unsigned char>(*reinterpret_cast<short*>(workEntry + 0x10));
		outSize++;
		outData[outSize] =
			static_cast<unsigned char>(static_cast<unsigned short>(*reinterpret_cast<short*>(workEntry + 0x10)) >> 8);
		outSize++;
		outData[outSize] = static_cast<unsigned char>(*reinterpret_cast<short*>(workEntry + 0x12));
		outSize++;
		outData[outSize] =
			static_cast<unsigned char>(static_cast<unsigned short>(*reinterpret_cast<short*>(workEntry + 0x12)) >> 8);
		outSize++;

		workEntry += 0xC;
	}

	reinterpret_cast<char*>(this)[0x2C88] = 1;
	return outSize;
}

/*
 * --INFO--
 * PAL Address: 0x800ccdac
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetMapObjDrawFlg(unsigned int* drawFlags)
{
	OSSemaphore* semaphoreQueue = reinterpret_cast<OSSemaphore*>(this);

	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreQueue);
		semaphoreQueue++;
	}

	*drawFlags = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x2B04);

	semaphoreQueue = reinterpret_cast<OSSemaphore*>(this);
	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(semaphoreQueue);
		semaphoreQueue++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ccd94
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetAddLetter(int channel)
{
	reinterpret_cast<unsigned char*>(this)[0x2C89] |= 1 << channel;
}

/*
 * --INFO--
 * PAL Address: 0x800ccd1c
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetFavoriteFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int mask = static_cast<unsigned int>(obj[0x2CB1]) & (1U << channel);
	mask = (-mask | mask) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return mask;
}

/*
 * --INFO--
 * PAL Address: 0x800cccb4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrFavoriteFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2CB1] = static_cast<char>(obj[0x2CB1] & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800ccc38
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetFavorite(int channel, char* favorite)
{
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(favorite, obj + channel * 0xDC + 0x46C, 8);
	OSSignalSemaphore(accessSemaphores + channel);

	return 8;
}

/*
 * --INFO--
 * PAL Address: 0x800ccbc0
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetMoneyFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int mask = static_cast<unsigned int>(obj[0x2CB0]) & (1U << channel);
	mask = (-mask | mask) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return mask;
}

/*
 * --INFO--
 * PAL Address: 0x800ccb58
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrMoneyFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2CB0] = static_cast<char>(obj[0x2CB0] & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800ccaf4
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetMoney(int channel)
{
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;

	OSWaitSemaphore(accessSemaphores + channel);
	int value = *reinterpret_cast<int*>(compatibilityStr + channel * 0xDC + 0x20);
	OSSignalSemaphore(accessSemaphores + channel);

	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800ccae8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrScrInitEnd()
{
	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2AF8) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800cca58
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::InitCmakeInfo(int channel, int value)
{
	unsigned char* obj = reinterpret_cast<unsigned char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	memset(&cmakeInfo[channel], 0, sizeof(cmakeInfo[channel]));
	cmakeInfo[channel].m_active = 1;
	obj[channel * 0x20 + 0x2CCA] = 0xFF;
	obj[channel * 0x20 + 0x2CD1] = 0xFF;
	obj[channel * 0x20 + 0x2CB8] = static_cast<unsigned char>(value);
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetMType(channel, 1);
}

/*
 * --INFO--
 * PAL Address: 0x800cc9dc
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrCmakeInfo(int param_2)
{
	BlockSem(param_2);
	if (cmakeInfo[param_2].m_active != 0) {
		memset(&cmakeInfo[param_2], 0, sizeof(cmakeInfo[param_2]));
	}
	ReleaseSem(param_2);
}

/*
 * --INFO--
 * PAL Address: 0x800cc5c4
 * PAL Size: 1048b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ChkCMakeName(int channel, unsigned int value)
{
	char* obj = reinterpret_cast<char*>(this);
	unsigned char cmdType = value >> 24;
	unsigned char byte0 = value;
	unsigned char byte1 = value >> 8;
	unsigned char byte2 = value >> 16;
	unsigned short nameCrc = value >> 8;
	const int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if ((static_cast<int>(cmdType) >> 6) == 0) {
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = static_cast<char>(cmdType);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 1;
		*reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset) = static_cast<short>(nameCrc);
		memset(obj + 0x2CB9 + cmakeOffset, 0, 0x11);
		obj[0x2CB9 + cmakeOffset] = static_cast<char>(byte0);
		OSSignalSemaphore(semaphore);
		return;
	}

	GbaQueueCMakeInfoView localInfo;

	OSWaitSemaphore(semaphore);
	{
		char* cmakeBase = obj + cmakeOffset;
		short packetCount = *reinterpret_cast<short*>(cmakeBase + 0x2CB4);
		char* writeBase = cmakeBase + static_cast<int>(packetCount) * 3;
		*reinterpret_cast<short*>(cmakeBase + 0x2CB4) = static_cast<short>(packetCount + 1);
		writeBase[0x2CB7] = static_cast<char>(byte2);
		writeBase[0x2CB8] = static_cast<char>(byte1);
		writeBase[0x2CB9] = static_cast<char>(byte0);

		if (5 < *reinterpret_cast<short*>(cmakeBase + 0x2CB4)) {
			localInfo = *reinterpret_cast<GbaQueueCMakeInfoView*>(obj + 0x2CB2 + cmakeOffset);
		}
	}
	OSSignalSemaphore(semaphore);

	if (5 >= *reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset)) {
		return;
	}

	if (strlen(reinterpret_cast<char*>(obj + 0x2CB9 + cmakeOffset)) == 0) {
		obj[0x2CCA + cmakeOffset] = static_cast<char>(0xFF);
		obj[0x2CD1 + cmakeOffset] = static_cast<char>(0xFF);
		return;
	}

	unsigned short crc = 0xFFFF;
	if (Joybus.Crc16(0x10, reinterpret_cast<unsigned char*>(localInfo.m_name), &crc) == localInfo.m_crc) {
		for (int i = 0; i < 4; i++) {
			OSWaitSemaphore(accessSemaphores + i);
		}

		for (int i = 0; i < 4; i++) {
			const int otherOffset = i * 0x20;
			if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
			    (strcmp(obj + 0x2CB9 + otherOffset, localInfo.m_name) == 0)) {
				memset(obj + 0x2CB9 + cmakeOffset, 0, 0x11);
				for (int j = 0; j < 4; j++) {
					OSSignalSemaphore(accessSemaphores + j);
				}
				Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 4; i++) {
			OSSignalSemaphore(accessSemaphores + i);
		}

		GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
		for (int i = 0; i < 0x100; i++) {
			if (strcmp(flatData->m_tabl[2].m_strings[i], localInfo.m_name) == 0) {
				Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 8; i++) {
			CCaravanWork* caravanWork = &Game.m_caravanWorkArr[i];
			char* caravanObj = reinterpret_cast<char*>(caravanWork);
			if ((i != localInfo.m_playerSlot) && (*reinterpret_cast<int*>(caravanObj + 0x3A4) != 0) &&
			    (caravanObj[0xBA6] == '\0') &&
			    (strcmp(caravanObj + 0x3CA, localInfo.m_name) == 0)) {
				Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
				return;
			}
		}

		Joybus.SendResult(channel, 0, localInfo.m_resultCode, 0);
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + cmakeOffset) = 0;
		OSSignalSemaphore(semaphore);
	} else {
		if (System.m_execParam != 0) {
System.Printf(const_cast<char*>(s_cmake_name_crc_error), const_cast<char*>(s_gbaque_cpp), 0xAD3);
		}
		Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800CC394
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ChkCMakeCharaType(int channel, unsigned int value)
{
	char* obj = reinterpret_cast<char*>(this);
	unsigned char charaType = static_cast<unsigned char>(value >> 8);
	unsigned char resultCode = static_cast<unsigned char>(value >> 16);
	int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if (charaType == 0xFF) {
		OSWaitSemaphore(semaphore);
		obj[0x2CCA + cmakeOffset] = static_cast<char>(0xFF);
		obj[0x2CD1 + cmakeOffset] = static_cast<char>(0xFF);
		OSSignalSemaphore(semaphore);
		return;
	}

	bool foundDuplicate = false;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);
	}

	unsigned char playerSlot = static_cast<unsigned char>(obj[0x2CB8 + cmakeOffset]);
	for (int i = 0; i < 4; i++) {
		int otherOffset = i * 0x20;
		if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
		    (static_cast<unsigned char>(obj[0x2CCA + otherOffset]) == charaType)) {
			Joybus.SendResult(channel, 1, resultCode, 0);
			foundDuplicate = true;
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(accessSemaphores + i);
	}

	if (foundDuplicate) {
		return;
	}

	for (int i = 0; i < 8; i++) {
		CCaravanWork* caravanWork = &Game.m_caravanWorkArr[i];
		char* caravanObj = reinterpret_cast<char*>(caravanWork);
		if ((i != playerSlot) && (*reinterpret_cast<int*>(caravanObj + 0x3A4) != 0) &&
		    (caravanObj[0xBA6] == '\0')) {
			unsigned short existingCharaType = *reinterpret_cast<unsigned short*>(caravanObj + 0x3E0) & 0xFF;
			existingCharaType |= static_cast<unsigned short>(
			    static_cast<unsigned char>(static_cast<char>(*reinterpret_cast<unsigned short*>(caravanObj + 0x3E4)) << 2));
			if (*reinterpret_cast<short*>(caravanObj + 0x3E2) != 0) {
				existingCharaType = static_cast<unsigned short>(existingCharaType | 0x80);
			}

			if (existingCharaType == charaType) {
				Joybus.SendResult(channel, 1, resultCode, 0);
				return;
			}
		}
	}

	Joybus.SendResult(channel, 0, resultCode, 0);
	OSWaitSemaphore(semaphore);
	obj[0x2CCA + cmakeOffset] = static_cast<char>(charaType);
	OSSignalSemaphore(semaphore);
	MenuPcs.ChgModel(static_cast<int>(playerSlot), charaType & 3, (charaType >> 2) & 3, static_cast<int>(charaType >> 7));
}

/*
 * --INFO--
 * PAL Address: 0x800CC1B8
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ChkCMakeJob(int channel, unsigned int value)
{
	char* obj = reinterpret_cast<char*>(this);
	unsigned char jobType = static_cast<unsigned char>(value >> 8);
	unsigned char resultCode = static_cast<unsigned char>(value >> 16);
	int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if (jobType == 0xFF) {
		OSWaitSemaphore(semaphore);
		obj[0x2CD1 + cmakeOffset] = static_cast<char>(0xFF);
		OSSignalSemaphore(semaphore);
		return;
	}

	bool foundDuplicate = false;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);
	}

	unsigned char playerSlot = static_cast<unsigned char>(obj[0x2CB8 + cmakeOffset]);
	for (int i = 0; i < 4; i++) {
		int otherOffset = i * 0x20;
		if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
		    (static_cast<unsigned char>(obj[0x2CD1 + otherOffset]) == jobType)) {
			Joybus.SendResult(channel, 1, resultCode, 0);
			foundDuplicate = true;
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(accessSemaphores + i);
	}

	if (foundDuplicate) {
		return;
	}

	for (int i = 0; i < 8; i++) {
		CCaravanWork* caravanWork = &Game.m_caravanWorkArr[i];
		if ((i != playerSlot) && (caravanWork->m_shopState != 0) && (caravanWork->m_caravanLocalFlags == 0) &&
		    (static_cast<unsigned char>(caravanWork->unk_0x3ac) == jobType)) {
			Joybus.SendResult(channel, 1, resultCode, 0);
			return;
		}
	}

	Joybus.SendResult(channel, 0, resultCode, 0);
	OSWaitSemaphore(semaphore);
	obj[0x2CD1 + cmakeOffset] = static_cast<char>(jobType);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::CMakeEnd(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::CMakeBarthday(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800CBF74
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::CMakeFavorite(int channel, unsigned int value)
{
	char* obj = reinterpret_cast<char*>(this);
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&value);
	int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if ((static_cast<int>(valueBytes[0]) >> 6) == 0) {
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = static_cast<char>(valueBytes[0]);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 1;
		*reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset) = static_cast<short>((valueBytes[1] << 8) | valueBytes[2]);
		memset(obj + 0x2CCD + cmakeOffset, 0, 4);
		obj[0x2CCD + cmakeOffset] = static_cast<char>(valueBytes[3]);
		OSSignalSemaphore(semaphore);
		return;
	}

	GbaQueueCMakeInfoView localInfo;

	OSWaitSemaphore(semaphore);
	{
		int writeOffset = static_cast<int>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset)) * 3;
		*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) =
			static_cast<short>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) + 1);
		obj[0x2CCB + cmakeOffset + writeOffset] = static_cast<char>(valueBytes[1]);
		obj[0x2CCC + cmakeOffset + writeOffset] = static_cast<char>(valueBytes[2]);
		obj[0x2CCD + cmakeOffset + writeOffset] = static_cast<char>(valueBytes[3]);

		if (*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) >= 2) {
			localInfo = *reinterpret_cast<GbaQueueCMakeInfoView*>(obj + 0x2CB2 + cmakeOffset);
		}
	}
	OSSignalSemaphore(semaphore);

	if (*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) < 2) {
		return;
	}

	unsigned short crc = 0xFFFF;
	if (Joybus.Crc16(4, localInfo.m_favorite, &crc) != localInfo.m_crc) {
		if (System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_cmake_favorite_crc_error), const_cast<char*>(s_gbaque_cpp), 0xBDC);
		}
		Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
	} else {
		Joybus.SendResult(channel, 0, localInfo.m_resultCode, 0);
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + cmakeOffset) = 0;
		OSSignalSemaphore(semaphore);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800cbf04
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetCompatibilityFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<char>(flags->m_compatibilityFlg[channel]);
	value = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>(value);
}

/*
 * --INFO--
 * PAL Address: 0x800cbea4
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrCompatibilityFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_compatibilityFlg[channel] = 0;
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetCompatibility(int channel, unsigned char* outCompatibility)
{
	unsigned char compatibilityData[0x10];
	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
	unsigned char count = 2;
	unsigned char* writePtr;
	int outSize = 2;
	int selectedCount = 0;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(compatibilityData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x524, sizeof(compatibilityData));
	OSSignalSemaphore(accessSemaphores + channel);

	outCompatibility[0] = compatibilityData[5];
	if (compatibilityData[3] != 0) {
		count++;
	}
	if (compatibilityData[4] != 0) {
		count++;
	}
	if (compatibilityData[5] != 0) {
		count++;
	}
	if (compatibilityData[6] != 0) {
		count++;
	}
	if (compatibilityData[7] != 0) {
		count++;
	}

	if ((count > 4) && (System.m_execParam != 0)) {
		System.Printf(const_cast<char*>(s_compatibility_data_error));
	}

	outCompatibility[1] = count;
	writePtr = outCompatibility + 2;
	for (int slot = 1; (selectedCount < count) && (slot < 8); slot++) {
		unsigned char slotValue = compatibilityData[slot];
		if ((selectedCount < 2) || (slotValue != 0)) {
			writePtr[0] = static_cast<unsigned char>(slot);
			writePtr[1] = compatibilityData[slot + 8];
			writePtr += 2;
			outSize += 2;
			selectedCount++;
		}
	}

	selectedCount = 0;
	for (int slot = 1; (selectedCount < count) && (slot < 8); slot++) {
		unsigned char slotValue = compatibilityData[slot];
		if ((selectedCount < 2) || (slotValue != 0)) {
			char* src = flatData->m_tabl[2].m_strings[slotValue];
			int len = strlen(src);
			memcpy(writePtr, src, len + 1);
			writePtr += len + 1;
			outSize += len + 1;
			selectedCount++;
		}
	}

	return outSize;
}

/*
 * --INFO--
 * PAL Address: 0x800cbc4c
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetCMakeInfo(int channel, GbaCMakeInfo* outInfo)
{
	OSSemaphore* sem = accessSemaphores + channel;

	OSWaitSemaphore(sem);
	memcpy(outInfo, &cmakeInfo[channel], sizeof(*outInfo));
	OSSignalSemaphore(sem);
}

/*
 * --INFO--
 * PAL Address: 0x800CBB04
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetCmdData(int channel, unsigned char* outData)
{
	unsigned char localPlayerData[0xDC];
	unsigned char count;
	unsigned char* writePtr;
	unsigned char* itemPtr;
	unsigned short cmdData[4];
	int size;
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x454, sizeof(localPlayerData));
	OSSignalSemaphore(accessSemaphores + channel);

	count = 0;
	writePtr = outData + 4;
	size = 4;

	outData[0] = 0;
	outData[1] = 0;
	outData[2] = 0;
	outData[3] = 0;
	itemPtr = localPlayerData;

	for (i = 0; i < 0x40; i++, itemPtr += 2) {
		int itemId = *reinterpret_cast<short*>(itemPtr + 0x3A);
		if ((MenuPcs.GetItemType(itemId, 1) == 1) &&
		    (MenuPcs.GetItemIcon(itemId) == (localPlayerData[2] & 3))) {
			int itemBase = Game.unkCFlatData0[2] + itemId * 0x48;

			cmdData[0] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 4), 0);
			cmdData[1] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 6), 0);
			cmdData[2] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 8), 0);
			cmdData[3] = 0;
			memcpy(writePtr, cmdData, sizeof(cmdData));

			writePtr += 8;
			size += 8;
			count++;
		}
	}

	outData[0] = count;
	return size;
}

/*
 * --INFO--
 * PAL Address: 0x800CB968
 * PAL Size: 412b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetEquipData(int channel, unsigned char* outData)
{
	unsigned char localPlayerData[0xDC];
	unsigned char equipIndices[0x40];
	unsigned int indexBytes;
	int equipCount;
	unsigned char* writePtr;
	unsigned short equipData[4];
	int dataSize;
	unsigned char* itemPtr;
	unsigned char* indexPtr;
	char itemIndex;
	int remaining;
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x454, sizeof(localPlayerData));
	memcpy(outData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x52B, 4);
	OSSignalSemaphore(accessSemaphores + channel);

	memset(equipIndices, 0xFF, sizeof(equipIndices));
	equipCount = 0;
	itemPtr = localPlayerData;
	indexPtr = equipIndices;
	itemIndex = 0;
	remaining = 0x40;
	do {
		int itemId = *reinterpret_cast<short*>(itemPtr + 0x3A);
		if (itemId >= 0 && itemId < 0x9F) {
			*indexPtr = static_cast<unsigned char>(itemIndex);
			equipCount++;
			indexPtr++;
		}
		itemPtr += 2;
		itemIndex++;
		remaining--;
	} while (remaining != 0);

	indexBytes = static_cast<unsigned int>(equipCount) + 1;
	if ((indexBytes & 3) != 0) {
		indexBytes = (((indexBytes >> 2) + 1) * 4);
	}

	outData[4] = equipCount;
	memcpy(outData + 5, equipIndices, indexBytes - 1);

	dataSize = indexBytes + 4;
	writePtr = outData + 4 + indexBytes;
	for (i = 0; i < equipCount; i++) {
		int itemId = *reinterpret_cast<short*>(localPlayerData + 0x3A + equipIndices[i] * 2);
		int itemBase = Game.unkCFlatData0[2] + itemId * 0x48;

		equipData[0] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 4), 0);
		equipData[1] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 6), 0);
		equipData[2] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 8), 0);
		equipData[3] = 0;
		memcpy(writePtr, equipData, sizeof(equipData));
		writePtr += 8;
		dataSize += 8;
	}

	return dataSize;
}

/*
 * --INFO--
 * PAL Address: 0x800cb8c0
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetShopFlg(int channel)
{
	OSSemaphore* semaphore = accessSemaphores + channel;
	u8* flags = reinterpret_cast<u8*>(this) + 0x2D38;

	OSWaitSemaphore(semaphore);
	int mask = 1 << channel;
	*flags = static_cast<u8>(*flags | mask);
	OSSignalSemaphore(semaphore);

	if (Joybus.SetMType(channel, 2) != 0) {
		flags[1] = static_cast<u8>(flags[1] | mask);
	} else {
		flags[1] = static_cast<u8>(flags[1] & ~mask);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrShopFlg(int channel)
{
	const unsigned char playerMask = static_cast<unsigned char>(1 << channel);
	unsigned char* flags = reinterpret_cast<unsigned char*>(this) + 0x2D38;

	OSWaitSemaphore(accessSemaphores + channel);
	flags[0] = static_cast<unsigned char>(flags[0] & ~playerMask);
	flags[1] = static_cast<unsigned char>(flags[1] & ~playerMask);
	OSSignalSemaphore(accessSemaphores + channel);

	for (int retry = 0; retry < 10; retry++) {
		if (Joybus.SetMType(channel, 0) == 0) {
			break;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800cb818
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetSmithFlg(int channel)
{
	OSSemaphore* semaphore = accessSemaphores + channel;
	u8* flags = reinterpret_cast<u8*>(this) + 0x2D38;

	OSWaitSemaphore(semaphore);
	int mask = 0x10 << channel;
	*flags = static_cast<u8>(*flags | mask);
	OSSignalSemaphore(semaphore);

	if (Joybus.SetMType(channel, 3) != 0) {
		flags[1] = static_cast<u8>(flags[1] | mask);
	} else {
		flags[1] = static_cast<u8>(flags[1] & ~mask);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrSmithFlg(int channel)
{
	const unsigned char shopMask = static_cast<unsigned char>(0x10 << channel);
	unsigned char* flags = reinterpret_cast<unsigned char*>(this) + 0x2D38;

	OSWaitSemaphore(accessSemaphores + channel);
	flags[0] = static_cast<unsigned char>(flags[0] & ~shopMask);
	flags[1] = static_cast<unsigned char>(flags[1] & ~shopMask);
	OSSignalSemaphore(accessSemaphores + channel);

	for (int retry = 0; retry < 10; retry++) {
		if (Joybus.SetMType(channel, 0) == 0) {
			break;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ShopEnd(int channel)
{
	ClrShopFlg(channel);

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
	if (caravanWork != 0) {
		caravanWork->CallShop(0, 0, 0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SmithEnd(int channel)
{
	ClrSmithFlg(channel);

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
	if (caravanWork != 0) {
		caravanWork->CallShop(1, 0, 0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800cb49c
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::MakeBuyData(int channel, char* outData)
{
char* itemNameScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xD79) char[kGbaQueueScratchTextSize];
	if (itemNameScratch == 0) {
		if (System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0xD7B);
		}
		return;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xD82) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if (System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0xD84);
		}
		return;
	}
	memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

	const unsigned int scriptFood = Game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.unkCFlatData0[2];
	const unsigned int itemCount =
		static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(scriptFood + 0xBE4));

	int totalSize = 4;
	outData[0] = static_cast<char>(itemCount);
	char* writePtr = outData + 4;

	for (unsigned int i = 0; i < itemCount; i++) {
		const unsigned short itemId =
			static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(scriptFood + i * 2 + 0xBE6));
		const unsigned short swapped = static_cast<unsigned short>((itemId << 8) | (itemId >> 8));
		memcpy(writePtr, &swapped, 2);
		writePtr += 2;
		totalSize += 2;
	}

	if ((itemCount & 1) != 0) {
		writePtr += 2;
		totalSize += 2;
	}

	const double userRate = static_cast<double>(
		static_cast<float>(static_cast<float>(*reinterpret_cast<short*>(scriptFood + 0xBE2)) / 100.0f));

	for (unsigned int i = 0; i < itemCount; i++) {
		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xBE6);
		unsigned int itemPrice = static_cast<unsigned short>(
			*reinterpret_cast<unsigned short*>(flatBase + itemId * 0x48 + 0x20));
		itemPrice = static_cast<unsigned int>(static_cast<double>(static_cast<float>(itemPrice)) * userRate);
		if (static_cast<int>(itemPrice) < 1) {
			itemPrice = 1;
		}

		const unsigned int packedPrice =
			(itemPrice << 24) |
			(((itemPrice >> 8) & 0xFF) << 16) |
			(((itemPrice >> 16) & 0xFF) << 8) |
			(itemPrice >> 24);
		memcpy(writePtr, &packedPrice, 4);
		writePtr += 4;
		totalSize += 4;
	}

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
	for (unsigned int i = 0; i < itemCount; i++) {
		memset(itemNameScratch, 0, kGbaQueueScratchTextSize);
		memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xBE6);
		strcpy(itemNameScratch, flatData->m_tabl[6].m_strings[itemId]);
		CMes::MakeAgbString(agbStringScratch, itemNameScratch, 0, 0);

		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(writePtr, agbStringScratch, strSize);
		writePtr += strSize;
		totalSize += strSize;
	}

	delete[] agbStringScratch;
	delete[] itemNameScratch;

	OSWaitSemaphore(accessSemaphores + channel);
	GbaQueueFlagView* flags = GetFlagView(this);
	flags->m_buyFlg = static_cast<unsigned char>(flags->m_buyFlg | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
}

/*
 * --INFO--
 * PAL Address: 0x800cb0d0
 * PAL Size: 972b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::MakeSellData(int channel, char* outData)
{
char* itemNameScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xDD5) char[kGbaQueueScratchTextSize];
	if (itemNameScratch == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0xDD7);
		}
		return -1;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xDDE) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0xDE0);
		}
		return -1;
	}
	memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

	const unsigned int scriptFood = Game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.unkCFlatData0[2];
	int totalSize = 0;

	for (int i = 0; i < 0x40; i++) {
		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xB6);
		unsigned int sellInfo[2];
		if ((itemId < 1) || (itemId > 0x9E)) {
			sellInfo[0] = 0;
			sellInfo[1] = 0;
		} else {
			const int itemBase = flatBase + itemId * 0x48;
			sellInfo[0] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 4));
			sellInfo[1] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 6)) |
				(static_cast<unsigned int>(static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 8))) << 16);
		}
		memcpy(outData, sellInfo, 8);
		outData += 8;
		totalSize += 8;
	}

	const double userRate = static_cast<double>(static_cast<float>(
		static_cast<float>(*reinterpret_cast<short*>(scriptFood + 0xBE2)) / 100.0f * 0.3f));
	for (int i = 0; i < 0x40; i++) {
		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xB6);
		unsigned int packedPrice = 0;
		if (itemId > 0) {
			unsigned int itemPrice = static_cast<unsigned short>(
				*reinterpret_cast<unsigned short*>(flatBase + itemId * 0x48 + 0x20));
			itemPrice = static_cast<unsigned int>(static_cast<double>(static_cast<float>(itemPrice)) * userRate);
			if (static_cast<int>(itemPrice) < 1) {
				itemPrice = 1;
			}
			packedPrice =
				(itemPrice << 24) |
				((itemPrice >> 8) & 0xFF) << 16 |
				((itemPrice >> 16) & 0xFF) << 8 |
				(itemPrice >> 24);
		}

		memcpy(outData, &packedPrice, 4);
		outData += 4;
		totalSize += 4;
	}

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
	for (int i = 0; i < 0x40; i++) {
		memset(itemNameScratch, 0, kGbaQueueScratchTextSize);
		memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xB6);
		if (itemId < 1) {
			outData[0] = 0;
			outData += 1;
			totalSize += 1;
			continue;
		}

		strcpy(itemNameScratch, flatData->m_tabl[6].m_strings[itemId]);
		CMes::MakeAgbString(agbStringScratch, itemNameScratch, 0, 0);
		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(outData, agbStringScratch, strSize);
		outData += strSize;
		totalSize += strSize;
	}

	delete[] agbStringScratch;
	delete[] itemNameScratch;

	GbaQueueFlagView* flags = GetFlagView(this);
	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_sellFlg = static_cast<unsigned char>(flags->m_sellFlg | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
	return totalSize;
}

/*
 * --INFO--
 * PAL Address: 0x800cac30
 * PAL Size: 1184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::MakeSmithData(int channel, char* outData)
{
	unsigned char* smithIndices = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xE41)
		unsigned char[0x40];
	if (smithIndices == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp), 0xE43);
		}
		return -1;
	}
	memset(smithIndices, 0xFF, 0x40);

	unsigned int* scriptFood = Game.m_scriptFoodBase + channel;
	const unsigned int flatBase = Game.unkCFlatData0[2];

	char smithCount = 0;
	char baseIndex = 0;
	int itemOffset = 0;
	for (int i = 0; i < 0x10; i++, itemOffset += 8) {
		if (*reinterpret_cast<short*>(*scriptFood + itemOffset + 0xB6) >= 401) {
			smithIndices[smithCount++] = baseIndex;
		}
		baseIndex++;
		if (*reinterpret_cast<short*>(*scriptFood + itemOffset + 0xB8) >= 401) {
			smithIndices[smithCount++] = baseIndex;
		}
		baseIndex++;
		if (*reinterpret_cast<short*>(*scriptFood + itemOffset + 0xBA) >= 401) {
			smithIndices[smithCount++] = baseIndex;
		}
		baseIndex++;
		if (*reinterpret_cast<short*>(*scriptFood + itemOffset + 0xBC) >= 401) {
			smithIndices[smithCount++] = baseIndex;
		}
		baseIndex++;
	}

	*outData = smithCount;
	memcpy(outData + 1, smithIndices, smithCount);

	int totalSize = static_cast<int>(smithCount);
	if (((totalSize + 1) % 4) != 0) {
		totalSize = (((totalSize + 1) >> 2) + 1) * 4 - 1;
	}
	char* writePtr = outData + 1 + totalSize;
	totalSize += 1;

	for (int i = 0; i < 0x40; i++) {
		const int itemId = *reinterpret_cast<short*>(*scriptFood + i * 2 + 0xB6);
		if (itemId >= 401) {
			unsigned int itemBuf[0xE];
			memset(itemBuf, 0, sizeof(itemBuf));

			const int itemBase = flatBase + itemId * 0x48;
			int price = static_cast<int>(
				static_cast<float>(static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x24))) *
				static_cast<float>(static_cast<float>(*reinterpret_cast<short*>(*scriptFood + 0xBE2)) / 100.0f));

			itemBuf[0] = SwapU32(static_cast<unsigned int>(price));

			reinterpret_cast<unsigned short*>(itemBuf)[2] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x26), 0);
			reinterpret_cast<unsigned short*>(itemBuf)[3] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x28), 0);
			reinterpret_cast<unsigned short*>(itemBuf)[4] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x2A), 0);
			reinterpret_cast<unsigned short*>(itemBuf)[5] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x2C), 0);
			reinterpret_cast<unsigned short*>(itemBuf)[6] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x2E), 0);
			reinterpret_cast<unsigned short*>(itemBuf)[7] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 0x30), 0);

			for (int j = 0; j < 2; j++) {
				const int recipeBase = itemBase + j * 4;

				const unsigned short materialA = *reinterpret_cast<unsigned short*>(recipeBase + 0x38);
				reinterpret_cast<unsigned short*>(itemBuf)[8 + j * 2] =
					__lhbrx(reinterpret_cast<unsigned short*>(recipeBase + 0x38), 0);
				if (materialA == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 8] = 0;
				} else {
					const int materialBase = flatBase + materialA * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 4), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 6), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 8), 0);
				}

				const unsigned short materialB = *reinterpret_cast<unsigned short*>(recipeBase + 0x3A);
				reinterpret_cast<unsigned short*>(itemBuf)[9 + j * 2] =
					__lhbrx(reinterpret_cast<unsigned short*>(recipeBase + 0x3A), 0);
				if (materialB == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 8] = 0;
				} else {
					const int materialBase = flatBase + materialB * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 4), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 6), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 8] =
						__lhbrx(reinterpret_cast<unsigned short*>(materialBase + 8), 0);
				}
			}

			memcpy(writePtr, itemBuf, 0x38);
			writePtr += 0x38;
			totalSize += 0x38;
		}
	}

	for (int i = 0; i < 4; i++) {
		unsigned int value = __lwbrx(reinterpret_cast<unsigned int*>(*scriptFood + i * 4 + 0xC08), 0);
		memcpy(writePtr, &value, 4);
		writePtr += 4;
		totalSize += 4;
	}

	delete[] smithIndices;

	GbaQueueFlagView* flags = GetFlagView(this);
	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_mkSmithFlg = static_cast<unsigned char>(flags->m_mkSmithFlg | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
	return totalSize;
}

/*
 * --INFO--
 * PAL Address: 0x800cabb8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetSellFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(flags->m_sellFlg)) & (1 << channel);
	value = (-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800cab3c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrSellFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_sellFlg = static_cast<unsigned char>(flags->m_sellFlg & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800caac4
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetBuyFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(flags->m_buyFlg)) & (1 << channel);
	value = (-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800caa48
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrBuyFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_buyFlg = static_cast<unsigned char>(flags->m_buyFlg & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ca9d0
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetMkSmithFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(flags->m_mkSmithFlg)) & (1 << channel);
	value = (-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800ca954
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrMkSmithFlg(int channel)
{
	GbaQueueFlagView* flags = GetFlagView(this);

	OSWaitSemaphore(accessSemaphores + channel);
	flags->m_mkSmithFlg = static_cast<unsigned char>(flags->m_mkSmithFlg & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ca8ec
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetResetFlg(int channel)
{
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(reinterpret_cast<char*>(this) + channel * 0xC);

	OSWaitSemaphore(semaphore);
	reinterpret_cast<unsigned char*>(this)[0x2D3D] =
		static_cast<unsigned char>(reinterpret_cast<unsigned char*>(this)[0x2D3D] | (1 << channel));
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800ca888
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char GbaQueue::GetBonus(int channel)
{
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned char value = static_cast<unsigned char>(compatibilityStr[channel * 0xDC + 0xCE]);
	OSSignalSemaphore(accessSemaphores + channel);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800ca810
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetArtifactFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(obj[0x2D36])) & (1 << channel);
	value = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>(value);
}

/*
 * --INFO--
 * PAL Address: 0x800ca7a8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrArtifactFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D36] = static_cast<char>(static_cast<unsigned char>(obj[0x2D36]) & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800CA5D4
 * PAL Size: 468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetArtifactData(int channel, unsigned char* outData)
{
	GbaQueuePlayerDataView localPlayerData;
	unsigned int artifactData[3];

	OSWaitSemaphore(accessSemaphores + channel);
	localPlayerData = *GetPlayerDataView(this, channel);
	OSSignalSemaphore(accessSemaphores + channel);

	artifactData[0] = SwapU32Value(localPlayerData.m_artifacts[0]);
	artifactData[1] = SwapU32Value(localPlayerData.m_artifacts[1]);
	artifactData[2] = SwapU32Value(localPlayerData.m_artifacts[2]);
	memcpy(outData, artifactData, sizeof(artifactData));
	return 0xC;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetUseItemFlg(int channel)
{
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;
	int result;
	OSWaitSemaphore(accessSemaphores + channel);
	char value = compatibilityStr[channel * 0xDC + 0x1F];
	result = static_cast<int>(value);
	OSSignalSemaphore(accessSemaphores + channel);
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetChgUseItemFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	int value;
	unsigned int result;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(obj[0x2D37])) & (1 << channel);
	result = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return result != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgUseItemFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D37] = static_cast<char>(static_cast<unsigned char>(obj[0x2D37]) & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetChgUseItemFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D37] = static_cast<char>(static_cast<unsigned char>(obj[0x2D37]) | (1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetStrengthFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(obj[0x2D3E])) & (1 << channel);
	value = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>(value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrStrengthFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D3E] = static_cast<char>(static_cast<unsigned char>(obj[0x2D3E]) & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800ca2bc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::GetStrengthData(int channel, unsigned char* strengthData)
{
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	strengthData[0] = static_cast<unsigned char>(obj[channel * 0xDC + 0x474]);
	strengthData[1] = static_cast<unsigned char>(obj[channel * 0xDC + 0x475]);
	strengthData[2] = static_cast<unsigned char>(obj[channel * 0xDC + 0x476]);
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetArtiDatFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	int value;
	unsigned int result;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(obj[0x2D3F])) & (1 << channel);
	result = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	return result != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrArtiDatFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D3F] = static_cast<char>(static_cast<unsigned char>(obj[0x2D3F]) & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800CA030
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::MakeArtiData(int channel, char* outData)
{
	char* itemNameScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x100F) char[kGbaQueueScratchTextSize];
	if (itemNameScratch == 0) {
		if (System.m_execParam != 0) {
			System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp),
			              0x1011);
		}
		return -1;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

	char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x1017) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if (System.m_execParam != 0) {
			System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DB37C), const_cast<char*>(s_gbaque_cpp),
			              0x1019);
		}
		return -1;
	}
	memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;
	unsigned int artifactData[3];

	OSWaitSemaphore(accessSemaphores + channel);
	artifactData[0] = SwapU32Value(*reinterpret_cast<unsigned int*>(compatibilityStr + channel * 0xDC + 0x24));
	artifactData[1] = SwapU32Value(*reinterpret_cast<unsigned int*>(compatibilityStr + channel * 0xDC + 0x28));
	artifactData[2] = SwapU32Value(*reinterpret_cast<unsigned int*>(compatibilityStr + channel * 0xDC + 0x2C));
	OSSignalSemaphore(accessSemaphores + channel);

	memcpy(outData, artifactData, sizeof(artifactData));
	delete[] agbStringScratch;
	delete[] itemNameScratch;

	reinterpret_cast<char*>(this)[0x2D3F] =
		static_cast<char>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D3F]) | (1 << channel));
	Joybus.SetLetterSize(channel, 0xC);
	return 0xC;
}

/*
 * --INFO--
 * PAL Address: 0x800C9E50
 * PAL Size: 480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetTmpArtifactData(int channel, unsigned char* outData)
{
	GbaQueuePlayerDataView localPlayerData;
	unsigned short tmpArtifacts[4];

	OSWaitSemaphore(accessSemaphores + channel);
	localPlayerData = *GetPlayerDataView(this, channel);
	OSSignalSemaphore(accessSemaphores + channel);

	for (int i = 0; i < 4; i++) {
		tmpArtifacts[i] = SwapU16(localPlayerData.m_tmpArtifacts[i]);
	}
	memcpy(outData, tmpArtifacts, sizeof(tmpArtifacts));

	return 8;
}

/*
 * --INFO--
 * PAL Address: 0x800c9dec
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char GbaQueue::GetRadarType(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(obj + channel * 0xC);
	int radarType;

	OSWaitSemaphore(semaphore);
	radarType = obj[channel + 0x2D32];
	OSSignalSemaphore(semaphore);

	return static_cast<signed char>(radarType);
}

/*
 * --INFO--
 * PAL Address: 0x800c9de0
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrRadarTypeFlg()
{
	*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x2D40) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetRadarMode(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = obj[0x2D41];
	OSSignalSemaphore(accessSemaphores + channel);
	unsigned int value = radarMode & (1 << channel);
	return (-value | value) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800C9CCC
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetRadarMode(int channel, int mode)
{
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = obj[0x2D41];
	int mask = 1 << channel;
	int newRadarMode = radarMode & ~mask;
	newRadarMode |= (mode & 1) << channel;
	obj[0x2D41] = newRadarMode;
	if (radarMode != obj[0x2D41]) {
		obj[0x2D42] = obj[0x2D42] | mask;
	}
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetChgRadarMode(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = obj[0x2D42];
	OSSignalSemaphore(accessSemaphores + channel);
	unsigned int value = radarMode & (1 << channel);
	return (-value | value) >> 31;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgRadarMode(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D42] = static_cast<char>(static_cast<unsigned char>(obj[0x2D42]) & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800C98C0
 * PAL Size: 816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetScouterInfo(int channel, unsigned char* outData)
{
	unsigned char localScouterInfo[0x200];
	unsigned int* enemyWorkPtrs = &Game.m_scriptWork[2][0][0];

	memset(localScouterInfo, 0xFF, sizeof(localScouterInfo));

	OSWaitSemaphore(accessSemaphores + channel);
	{
		unsigned char* scouterEntry = localScouterInfo;
		unsigned char* enemyEntry = reinterpret_cast<unsigned char*>(this) + 0xB34;

		for (int i = 0; i < 0x40; i++) {
			scouterEntry[0] = enemyEntry[3];
			if (scouterEntry[0] != 0) {
				CMonWork* enemyWork = reinterpret_cast<CMonWork*>(enemyWorkPtrs[i]);
				const int enemyDataBase = Game.unkCFlatData0[1] + static_cast<unsigned char>(enemyEntry[3]) * 0x1D0;

				*reinterpret_cast<unsigned short*>(scouterEntry + 4) = SwapU16(enemyWork->m_maxHp);

				if (*reinterpret_cast<short*>(enemyEntry + 0xE) < 1) {
					const unsigned short scouterValue = *reinterpret_cast<unsigned short*>(enemyEntry + 0xC);
					if ((static_cast<short>(scouterValue) < 1) || ((scouterValue & 0xC000) == 0x4000)) {
						scouterEntry[6] = 0;
						scouterEntry[7] = 0;
					} else {
						*reinterpret_cast<unsigned short*>(scouterEntry + 6) = SwapU16(scouterValue);
					}
				} else {
					scouterEntry[6] = 0xFF;
					scouterEntry[7] = 0xFF;
				}

				const unsigned short enemyFlags = *reinterpret_cast<unsigned short*>(enemyDataBase + 0x10E);
				if ((enemyFlags & 5) == 5) {
					scouterEntry[1] = 0;
				} else if ((enemyFlags & 4) == 0) {
					if ((enemyFlags & 1) == 0) {
						const unsigned short form0 = *reinterpret_cast<unsigned short*>(enemyDataBase + 0xF0);
						if ((form0 == 0) && (*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF2) == 0) &&
						    (*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF4) == 0)) {
							scouterEntry[1] = 3;
						} else if ((form0 == 3) && (*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF2) == 3) &&
						           (*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF4) == 3)) {
							if (*reinterpret_cast<unsigned short*>(enemyDataBase + 0xC) == 0x10) {
								scouterEntry[1] = 0xE;
							} else {
								scouterEntry[1] = 4;
							}
						} else {
							int statusCount = 0;

							if (form0 == 0) {
								scouterEntry[1] = 5;
								statusCount = 1;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF0) == 3) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 6;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF2) == 0) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 7;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF2) == 3) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 8;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF4) == 0) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 9;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF4) == 3) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 10;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF6) == 0) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 11;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xF8) == 0) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 12;
								statusCount++;
							}
							if ((*reinterpret_cast<unsigned short*>(enemyDataBase + 0xFA) == 3) && (statusCount < 3)) {
								scouterEntry[statusCount + 1] = 13;
							}
						}
					} else {
						scouterEntry[1] = 2;
					}
				} else {
					scouterEntry[1] = 1;
				}
			}

			enemyEntry += 0x14;
			scouterEntry += 8;
		}
	}
	OSSignalSemaphore(accessSemaphores + channel);

	memcpy(outData, localScouterInfo, sizeof(localScouterInfo));
	return sizeof(localScouterInfo);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
namespace {
static inline OSSemaphore* AccessSemaphoreAt(GbaQueue* self, unsigned int channel)
{
	return reinterpret_cast<OSSemaphore*>(reinterpret_cast<char*>(self) + channel * sizeof(OSSemaphore));
}
}

/*
 * --INFO--
 * PAL Address: 0x800C9838
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetChgHitFlg(int channel)
{
	signed char singleModeByte = m_singleMode;
	int singleMode = singleModeByte;
	unsigned int actualChannel = static_cast<unsigned int>(channel) &
	                             ~static_cast<unsigned int>((-singleMode | singleMode) >> 31);
	OSSemaphore* semaphore = accessSemaphores + actualChannel;
	OSWaitSemaphore(semaphore);
	int flag = reinterpret_cast<signed char*>(this)[0x2D54];
	OSSignalSemaphore(semaphore);
	unsigned int value = flag & (1U << actualChannel);
	return (-value | value) >> 31U;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgHitFlg(int channel)
{
	unsigned char flag = static_cast<unsigned char>(m_singleMode);
	unsigned int actualChannel =
	    static_cast<unsigned int>(channel) &
	    ~static_cast<unsigned int>((-static_cast<signed char>(flag) | static_cast<signed char>(flag)) >> 31);
	OSSemaphore* semaphore = accessSemaphores + actualChannel;
	unsigned char* obj = reinterpret_cast<unsigned char*>(this);
	OSWaitSemaphore(semaphore);
	obj[0x2D54] = obj[0x2D54] & ~(1U << actualChannel);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetChgScouFlg(int channel)
{
	OSSemaphore* semaphore = AccessSemaphoreAt(this, channel);
	OSWaitSemaphore(semaphore);
	int flag = reinterpret_cast<signed char*>(this)[0x2D55];
	OSSignalSemaphore(semaphore);
	unsigned int value = flag & (1U << channel);
	return (-value | value) >> 31U;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgScouFlg(int channel)
{
	OSSemaphore* semaphore = AccessSemaphoreAt(this, channel);
	unsigned char* obj = reinterpret_cast<unsigned char*>(this);
	OSWaitSemaphore(semaphore);
	obj[0x2D55] = static_cast<unsigned char>(obj[0x2D55] & ~(1U << channel));
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800C9640
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetHitEnemy(int channel, int enemyIdx)
{
	short enemyId;
	short enemyType;

	if (enemyIdx >= 0) {
		enemyId = static_cast<short>(enemyIdx);
		enemyType = static_cast<short>(*reinterpret_cast<unsigned short*>(Game.m_scriptWork[2][0][enemyIdx] + 0x1C));
	} else {
		enemyType = enemyId = -1;
	}

	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_hitInfo[channel].m_enemyId = enemyId;
	m_hitInfo[channel].m_enemyType = enemyType;
	m_chgHitFlags = static_cast<unsigned char>(m_chgHitFlags | (1 << channel));
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800C95BC
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetHitEInfo(int channel)
{
	signed char singleModeByte = m_singleMode;
	int singleMode = singleModeByte;
	unsigned int actualChannel = static_cast<unsigned int>(channel) &
	                             ~static_cast<unsigned int>((-singleMode | singleMode) >> 31);
	OSSemaphore* semaphore = accessSemaphores + actualChannel;
	OSWaitSemaphore(semaphore);
	int hitInfo;
	*reinterpret_cast<short*>(&hitInfo) = m_hitInfo[actualChannel].m_enemyId;
	*reinterpret_cast<short*>(reinterpret_cast<char*>(&hitInfo) + 2) = m_hitInfo[actualChannel].m_enemyType;
	OSSignalSemaphore(semaphore);
	return hitInfo;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool GbaQueue::IsSingleMode(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
	bool isSingle = m_singleMode == 1;
	OSSignalSemaphore(accessSemaphores + channel);
	return isSingle;
}

/*
 * --INFO--
 * PAL Address: 0x800C9474
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetControllerMode(int controllerMode)
{
	int i;
	GbaQueue* semaphoreIter;
	GbaQueue* queue;
	int retries;
	int ret;

	queue = this;
	i = 0;
	semaphoreIter = queue;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	queue->m_controllerMode = static_cast<char>(controllerMode & 1);

	i = 0;
	semaphoreIter = queue;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	for (i = 0; i < 4; i++) {
		retries = 0;
		do {
			if (controllerMode != 0) {
				ret = Joybus.SetMType(i, 4);
			} else {
				ret = Joybus.SetMType(i, 0);
			}
			if (ret == 0) {
				break;
			}
			retries++;
		} while (retries < 10);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C93E8
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetControllerMode()
{
	GbaQueue* queue;
	char mode;
	int waitIndex;
	GbaQueue* waitSemaphore;
	unsigned int result;
	int signalIndex;
	GbaQueue* signalSemaphore;

	queue = this;
	waitIndex = 0;
	waitSemaphore = queue;
	do {
		OSWaitSemaphore(waitSemaphore->accessSemaphores);
		waitIndex++;
		waitSemaphore = reinterpret_cast<GbaQueue*>(waitSemaphore->accessSemaphores + 1);
	} while (waitIndex < 4);

	mode = queue->m_controllerMode;
	result = static_cast<unsigned int>(-static_cast<int>(mode) | static_cast<int>(mode)) >> 31;

	signalSemaphore = queue;
	signalIndex = 0;
	do {
		OSSignalSemaphore(signalSemaphore->accessSemaphores);
		signalIndex++;
		signalSemaphore = reinterpret_cast<GbaQueue*>(signalSemaphore->accessSemaphores + 1);
	} while (signalIndex < 4);

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800D4E50
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::OpenMenu(int channel, int menuId, int controlMode)
{
	char* obj = reinterpret_cast<char*>(this);
	GbaQueue* queue = &GbaQue;
	char* queueObj = reinterpret_cast<char*>(queue);
	int i;
	int retries;
	unsigned int isSingleMode;
	OSSemaphore* semaphoreIter;

	if (menuId == 999) {
		i = 0;
		semaphoreIter = accessSemaphores;
		do {
			OSWaitSemaphore(semaphoreIter);
			i++;
			semaphoreIter++;
		} while (i < 4);

		obj[0x2D57] = 1;

		i = 0;
		semaphoreIter = accessSemaphores;
		do {
			OSSignalSemaphore(semaphoreIter);
			i++;
			semaphoreIter++;
		} while (i < 4);

		for (i = 0; i < 4; i++) {
			retries = 0;
			do {
				if (Joybus.SetMType(i, 4) == 0) {
					break;
				}
				retries++;
			} while (retries < 10);
		}
		return;
	}

	retries = 0;
	do {
		if (Joybus.SetOpenMenu(channel, static_cast<char>(menuId)) == 0) {
			break;
		}
		retries++;
	} while (retries < 10);

	OSSemaphore* semaphore = queue->accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	char menuStageMode = queueObj[0x2D56];
	isSingleMode =
		(static_cast<unsigned int>(__cntlzw(1 - static_cast<int>(menuStageMode))) >>
		 5) &
		0xFFU;
	OSSignalSemaphore(semaphore);

	if (isSingleMode == 0) {
		retries = 0;
		do {
			if (Joybus.SetCtrlMode(channel, controlMode) == 0) {
				return;
			}
			retries++;
		} while (retries < 10);
		return;
	}

	OSWaitSemaphore(semaphore);
	menuStageMode = queueObj[0x2D56];
	isSingleMode =
		(static_cast<unsigned int>(__cntlzw(1 - static_cast<int>(menuStageMode))) >>
		 5) &
		0xFFU;
	OSSignalSemaphore(semaphore);
	if (isSingleMode == 0 && channel == 1 && menuId == 0) {
		retries = 0;
		do {
			if (Joybus.SetCtrlMode(channel, 0) == 0) {
				return;
			}
			retries++;
		} while (retries < 10);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C9184
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetPauseMode(int mode)
{
	{
		OSSemaphore* waitSemaphore = accessSemaphores;
		int waitIndex = 0;
		do {
			OSWaitSemaphore(waitSemaphore);
			waitIndex++;
			waitSemaphore++;
		} while (waitIndex < 4);
	}

	m_pauseMode = static_cast<char>(mode);

	{
		int signalIndex = 0;
		OSSemaphore* signalSemaphore = accessSemaphores;
		do {
			OSSignalSemaphore(signalSemaphore);
			signalIndex++;
			signalSemaphore++;
		} while (signalIndex < 4);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C90F8
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetPauseMode()
{
	GbaQueue* queue;
	char mode;
	int waitIndex;
	GbaQueue* waitSemaphore;
	unsigned int result;
	int signalIndex;
	GbaQueue* signalSemaphore;

	queue = this;
	waitIndex = 0;
	waitSemaphore = queue;
	do {
		OSWaitSemaphore(waitSemaphore->accessSemaphores);
		waitIndex++;
		waitSemaphore = reinterpret_cast<GbaQueue*>(waitSemaphore->accessSemaphores + 1);
	} while (waitIndex < 4);

	mode = queue->m_pauseMode;
	result = static_cast<unsigned int>(-static_cast<int>(mode) | static_cast<int>(mode)) >> 31;

	signalSemaphore = queue;
	signalIndex = 0;
	do {
		OSSignalSemaphore(signalSemaphore->accessSemaphores);
		signalIndex++;
		signalSemaphore = reinterpret_cast<GbaQueue*>(signalSemaphore->accessSemaphores + 1);
	} while (signalIndex < 4);

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800c9090
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetItemUse(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	char value = obj[channel * 0xDC + 0x52A];
	int result = (int)value;
	OSSignalSemaphore(semaphore);
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800c901c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetSPModeFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D5D);
	OSSignalSemaphore(semaphore);
	unsigned int mask = value & (1U << channel);
	return (-mask | mask) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800c8fb4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrSPModeFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(obj + channel * sizeof(OSSemaphore));
	OSWaitSemaphore(semaphore);
	obj[0x2D5D] = obj[0x2D5D] & ~(1 << channel);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800c8f40
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetSPMode(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D5C);
	OSSignalSemaphore(semaphore);
	unsigned int mask = value & (1U << channel);
	return (-mask | mask) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800c8ecc
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetMemorysFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D5E);
	OSSignalSemaphore(semaphore);
	unsigned int mask = value & (1U << channel);
	return (-mask | mask) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800c8e64
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrMemorysFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	obj[0x2D5E] = obj[0x2D5E] & ~(1 << channel);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800c8e00
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetMemorys(int channel)
{
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	unsigned short value =
		*reinterpret_cast<unsigned short*>(compatibilityStr + channel * 0xDC + 0x10);
	OSSignalSemaphore(semaphore);
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x800c8d98
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetCmdNumFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D5F);
	OSSignalSemaphore(semaphore);
	return (value >> (channel << 1)) & 3;
}

/*
 * --INFO--
 * PAL Address: 0x800c8d2c
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrCmdNumFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	obj[0x2D5F] = obj[0x2D5F] & ~(3 << (channel << 1));
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800c8cc4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GbaQueue::GetCmdNum(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	char value = obj[channel * 0xDC + 0x527];
	int result = (int)value;
	OSSignalSemaphore(semaphore);
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800c8c50
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetPlayModeFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D60);
	OSSignalSemaphore(semaphore);
	unsigned int mask = value & (1U << channel);
	return (-mask | mask) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800c8be8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrPlayModeFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(obj + channel * sizeof(OSSemaphore));
	OSWaitSemaphore(semaphore);
	obj[0x2D60] = obj[0x2D60] & ~(1 << channel);
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * PAL Address: 0x800c8b68
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::SetStartBonusFlg()
{
	OSSemaphore* semaphoreIter = reinterpret_cast<OSSemaphore*>(this);
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter);
		semaphoreIter++;
	}

	char* obj = reinterpret_cast<char*>(this);
	obj[0x2D61] = 0xF;

	semaphoreIter = reinterpret_cast<OSSemaphore*>(this);
	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(semaphoreIter);
		semaphoreIter++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800c8af4
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GbaQueue::GetStartBonusFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(this) + channel;
	OSWaitSemaphore(semaphore);
	int value = *reinterpret_cast<signed char*>(obj + 0x2D61);
	OSSignalSemaphore(semaphore);
	unsigned int mask = value & (1U << channel);
	return (-mask | mask) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x800c8a8c
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaQueue::ClrStartBonusFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(obj + channel * sizeof(OSSemaphore));
	OSWaitSemaphore(semaphore);
	obj[0x2D61] = obj[0x2D61] & ~(1 << channel);
	OSSignalSemaphore(semaphore);
}
