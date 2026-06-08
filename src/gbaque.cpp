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

STATIC_ASSERT(sizeof(GbaCMakeInfo) == 0x20);

STATIC_ASSERT(sizeof(GbaQueueMapObjEntry) == 0xC);
STATIC_ASSERT(sizeof(GbaQueueMapObjWork) == 0x188);

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
STATIC_ASSERT(sizeof(GbaQueueMapObjWork) == kGbaQueueMapObjWorkBytes);
STATIC_ASSERT(sizeof(GbaQueue) == 0x2D64);

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
static const char sGbaQueueMemoryAllocationErrorFmt[] = "%s(%d): Error: memory allocation error\n";
static const char s_compatibility_data_error[] = "compatibility data error!!\n";
static const char s_cmake_favorite_crc_error[] = "%s(%d): Error:CMakeFavorite() crc error!!\n";
static const char s_cmake_name_crc_error[] = "%s(%d): Error:ChkCMakeName() crc error!!\n";
static const char s_unknown_mapobj_type_error[] = "Error:Unknown mapobj type(%d)\n";
static const char s_npc_max_over[] = "%s(%d): Error: NPC max over!!\n";
static const char s_subject_max_over[] = "%s(%d): Error: Subject max over!!\n";
static const char s_letter_data_error[] = "%s(%d): Error: Letter data error(chan:%d  idx:%d)\n";
extern const float kGbaQueueQuarter = 0.25f;
extern const float kGbaQueueMapCoordScale = 3.0f;

namespace GbaQueConst {
const unsigned int ITEM_USE = 1;
const unsigned int ITEM_PUT = 2;
const unsigned int MONEY_ATTACH = 4;
const unsigned int OPEN_LETTER = 0x20;
const unsigned int MOVE_ATTACH = 8;
const unsigned int REPLY_LETTER = 0x10;
const unsigned int CAN_REPLY = 1;
const unsigned int ITEM_ATTACH = 2;
}

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
	memset(&m_mapObjWork, 0, sizeof(GbaQueueMapObjWork));
	memset(&m_sendMask, 0, 8);
	memset(cmakeInfo, 0, sizeof(cmakeInfo));
	memset(m_hitInfo, 0xFF, sizeof(m_hitInfo));

	i = 0;
	do {
		OSInitSemaphore(&accessSemaphores[i], 1);
		i = i + 1;
	} while (i < 4);

	m_mapNo = 0xFF;
	m_stageNo = 0xFF;
	m_stageFlags = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x44E) = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x450) = 0;

	m_letterDatFlg = 0;
	m_makeMapObjFlg = 0;
	m_letterFlags = 0;
	m_shopFlags = 0;
	m_shopStatusFlags = 0;
	m_sellFlg = 0;
	m_buyFlg = 0;
	m_mkSmithFlg = 0;
	m_resetFlags = 0;
	m_chgUseItemFlags = 0;
	m_favoriteFlags = 0;
	m_moneyFlags = 0;
	m_artifactFlags = 0;
	m_strengthFlags = 0;
	m_artiDatFlags = 0;
	m_mapItemCount = 0;
	m_radarTypeFlags = 0;
	m_radarMode = 0xF;
	m_chgRadarMode = 0;
	m_chgHitFlags = 0;
	m_chgScouFlags = 0;
	m_singleMode = 0;
	m_controllerMode = 0;
	obj[0x2D58] = 0;
	m_prevOutOfShoukiFlags = 0;
	m_outOfShoukiFlags = 0;
	m_pauseMode = 0;
	m_spModeBits = 0;
	m_spModeFlags = 0xF;
	m_memorysFlags = 0;
	m_cmdNumFlags = 0;
	m_playModeFlags = 0xF;
	m_startBonusFlags = 0;
	m_maskSendState[0] = static_cast<signed char>(0xFF);
	m_pendingMoney[0] = 0;
	m_moneyState[0] = 0;
	m_compatibilityFlg[0] = 0;
	m_radarType[0] = 1;
	m_maskSendState[1] = static_cast<signed char>(0xFF);
	m_pendingMoney[1] = 0;
	m_moneyState[1] = 0;
	m_compatibilityFlg[1] = 0;
	m_radarType[1] = 1;
	m_maskSendState[2] = static_cast<signed char>(0xFF);
	m_pendingMoney[2] = 0;
	m_moneyState[2] = 0;
	m_compatibilityFlg[2] = 0;
	m_radarType[2] = 1;
	m_maskSendState[3] = static_cast<signed char>(0xFF);
	m_pendingMoney[3] = 0;
	m_moneyState[3] = 0;
	m_compatibilityFlg[3] = 0;
	m_radarType[3] = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void GbaQueue::BlockSem(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void GbaQueue::ReleaseSem(int channel)
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
	char* obj;
	char prevMenuStageMode;
	char spModeBits;
	char spModeChangeBits;
	int cflatFlag;
	int* scriptFoodBase;

	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(&accessSemaphores[i]);
	}

	obj = reinterpret_cast<char*>(this);
	prevMenuStageMode = m_singleMode;
	m_singleMode = static_cast<char>(Game.m_gameWork.m_menuStageMode != 0);
	if (prevMenuStageMode != m_singleMode) {
		m_makeMapObjFlg = 0xF;
	}

	spModeBits = 0;
	for (i = 0; i < 4; i++) {
		if (Game.m_gameWork.m_spModeFlags[i] != 0) {
			spModeBits = static_cast<char>(spModeBits | (1 << i));
		}
	}

	spModeChangeBits = static_cast<char>(spModeBits ^ m_spModeBits);
	for (i = 0; i < 4; i++) {
		if ((spModeChangeBits & (1 << i)) != 0) {
			m_spModeFlags = static_cast<unsigned char>(m_spModeFlags | (1 << i));
		}
	}
	m_spModeBits = spModeBits;

	for (i = 0; i < 4; i++) {
		OSSignalSemaphore(&accessSemaphores[i]);
	}

	cflatFlag = reinterpret_cast<int*>(&CFlat)[0x4101];

	LoadPlayerStat();
	LoadEnemyStat();
	LoadMapItemStat();

	if ((m_scrInitEnd == 0) && (cflatFlag != 0)) {
		SetRadarType();
	}
	if (cflatFlag == 0) {
		memset(obj + 0x2D44, 0xFF, 0x10);
		obj[0x2D54] = 0;
	}

	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(&accessSemaphores[i]);
	}
	m_scrInitEnd = cflatFlag;
	for (i = 0; i < 4; i++) {
		OSSignalSemaphore(&accessSemaphores[i]);
	}

	LoadMapObj();

	scriptFoodBase = reinterpret_cast<int*>(Game.m_scriptFoodBase);
	for (i = 0; i < 4; i++) {
		if (scriptFoodBase[i] == 0) {
			m_maskSendState[i] = static_cast<signed char>(0xFF);
		} else {
			OSWaitSemaphore(accessSemaphores + i);
			{
				unsigned short maskValue = *reinterpret_cast<unsigned short*>(scriptFoodBase[i] + 0x89C);
				if ((maskValue != m_sendMask) && (Joybus.SendMask(i, maskValue) == 0)) {
					m_sendMask = maskValue;
					m_maskSendState[i] = 6;
				}
			}
			OSSignalSemaphore(accessSemaphores + i);
		}
	}

	for (i = 0; i < 4; i++) {
		OSWaitSemaphore(&accessSemaphores[i]);
	}
	{
		unsigned char resetMask = static_cast<unsigned char>(obj[0x2D30]);
		obj[0x2D30] = 0;
		for (i = 0; i < 4; i++) {
			OSSignalSemaphore(&accessSemaphores[i]);
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
					m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~static_cast<unsigned char>(bit));
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~static_cast<unsigned char>(bit));
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
					m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~shopMask);
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~shopMask);
					OSSignalSemaphore(accessSemaphores + i);
					for (int retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(i, 0) == 0) {
							break;
						}
					}
					caravanWork->CallShop(1, 0, 0, 0, 0);
				}
			}

			if ((m_shopStatusFlags & bit) == 0) {
				unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
				if ((m_shopStatusFlags & shopMask) != 0) {
					OSWaitSemaphore(accessSemaphores + i);
					m_shopFlags = static_cast<unsigned char>(m_shopFlags | shopMask);
					OSSignalSemaphore(accessSemaphores + i);
					if (Joybus.SetMType(i, 3) == 0) {
						m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~shopMask);
					} else {
						m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags | shopMask);
					}
				}
			} else {
				unsigned char playerMask = static_cast<unsigned char>(1 << i);
				OSWaitSemaphore(accessSemaphores + i);
				m_shopFlags = static_cast<unsigned char>(m_shopFlags | playerMask);
				OSSignalSemaphore(accessSemaphores + i);
				if (Joybus.SetMType(i, 2) == 0) {
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~playerMask);
				} else {
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags | playerMask);
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
				m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~playerMask);
				m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~playerMask);
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
				m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~shopMask);
				m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~shopMask);
			}
			OSSignalSemaphore(accessSemaphores + i);

			for (int retry = 0; retry < 10; retry++) {
				if (Joybus.SetMType(i, 0) == 0) {
					break;
				}
			}
			caravanWork->CallShop(1, 0, 0, 0, 0);
		}

		if ((m_shopStatusFlags & (1 << i)) == 0) {
			const unsigned char shopMask = static_cast<unsigned char>(0x10 << i);
			if ((m_shopStatusFlags & shopMask) != 0) {
				OSWaitSemaphore(accessSemaphores + i);
				m_shopFlags = static_cast<unsigned char>(m_shopFlags | shopMask);
				OSSignalSemaphore(accessSemaphores + i);
				if (Joybus.SetMType(i, 3) == 0) {
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~shopMask);
				} else {
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags | shopMask);
				}
			}
		} else {
			const unsigned char playerMask = static_cast<unsigned char>(1 << i);
			OSWaitSemaphore(accessSemaphores + i);
			m_shopFlags = static_cast<unsigned char>(m_shopFlags | playerMask);
			OSSignalSemaphore(accessSemaphores + i);
			if (Joybus.SetMType(i, 2) == 0) {
				m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~playerMask);
			} else {
				m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags | playerMask);
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

	for (int i = 0; i < 4; i++) {
		if (scriptFoodBase[i] == 0) {
			m_maskSendState[i] = static_cast<signed char>(0xFF);
			continue;
		}

		OSWaitSemaphore(accessSemaphores + i);
		{
			unsigned short maskValue = *reinterpret_cast<unsigned short*>(scriptFoodBase[i] + 0x89C);
			if ((maskValue != m_sendMask) && (Joybus.SendMask(i, maskValue) == 0)) {
				m_sendMask = maskValue;
				m_maskSendState[i] = 6;
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

	int channel;

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

	for (channel = 0; channel < 4; channel++) {
		const unsigned int playerBit = (1U << channel);
		const unsigned int shopBit = (0x10U << channel);
		unsigned int* queueWords = localQueueData[channel];
		int queueCount = localQueueCount[channel];
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
		int i;

		if (queue->m_queueFull[channel] != 0) {
			continue;
		}

		for (i = 0; i < queueCount; i++) {
			unsigned int cmdWord = queueWords[i];
			const unsigned char* cmdBytes = reinterpret_cast<const unsigned char*>(&cmdWord);
			int cmd = static_cast<int>(cmdBytes[0] & 0x3F);

			if (cmd == 0x17) {
				if (caravanWork != 0) {
					const int action = cmdBytes[1];
					const int itemIdx = cmdBytes[2];
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

					if ((static_cast<int>(p0) >> 6) == 0) {
						m_moneyState[channel] = static_cast<unsigned char>(p1 | 0x80);
						m_pendingMoney[channel] = (static_cast<unsigned int>(p2) << 24) | (static_cast<unsigned int>(p3) << 16);
					} else if (m_moneyState[channel] == 0) {
						Joybus.SendResult(channel, 1, p0, p1);
					} else {
						m_pendingMoney[channel] |= (static_cast<unsigned int>(p1) << 8) | p2;
						Joybus.SendResult(channel, 0, p0, m_moneyState[channel] & 7);
						if ((m_moneyState[channel] & 7) == 1) {
							caravanWork->FGPutGil(m_pendingMoney[channel]);
						}
						m_pendingMoney[channel] = 0;
						m_moneyState[channel] = 0;
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
					unsigned int cmakeOffset = channel * sizeof(GbaCMakeInfo);
					obj[0x2CCB + cmakeOffset] = static_cast<char>(cmdWord >> 8);
					obj[0x2CCC + cmakeOffset] = static_cast<char>(cmdWord);
					OSSignalSemaphore(accessSemaphores + channel);
					Joybus.SendResult(channel, 0, static_cast<unsigned char>(cmdWord >> 16), 0);
				} else if (request == 7) {
					OSWaitSemaphore(accessSemaphores + channel);
					m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~static_cast<unsigned char>(playerBit));
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~static_cast<unsigned char>(playerBit));
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
					m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~static_cast<unsigned char>(shopBit));
					m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~static_cast<unsigned char>(shopBit));
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
				m_maskSendState[channel] = static_cast<signed char>(0xFF);
			} else if (cmd == 0x1C) {
				ChkCMakeName(channel, cmdWord);
			} else if (cmd == 0x1D) {
				CMakeFavorite(channel, cmdWord);
			}
		}

		if (m_maskSendState[channel] >= 0) {
			if ((m_maskSendState[channel] == 0) && (Joybus.SendMask(channel, m_sendMask) == 0)) {
				m_maskSendState[channel] = 6;
			}
			m_maskSendState[channel] = static_cast<signed char>(m_maskSendState[channel] - 1);
		}

		if ((m_letterFlags & playerBit) != 0) {
			if (!Joybus.IsLetterMenu(channel)) {
				m_letterFlags = static_cast<unsigned char>(m_letterFlags & ~static_cast<unsigned char>(playerBit));
			} else if (Joybus.SendAddLetter(channel) == 0) {
				m_letterFlags = static_cast<unsigned char>(m_letterFlags & ~static_cast<unsigned char>(playerBit));
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
			int foundSlot;

			for (foundSlot = 0; foundSlot < 0x40; foundSlot++) {
				if (static_cast<int>(currentWork->m_inventoryItems[foundSlot]) == static_cast<int>(materialId)) {
					break;
				}
			}

			currentWork->DeleteItemIdx(foundSlot, 1);
		}
	}

	if (reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->AddItem(smithItem, 0) == 0) {
		Joybus.SendResult(channel, 1, valueBytes[0], valueBytes[1]);
	}

	const float smithRate = static_cast<float>(static_cast<double>(reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->m_shopParam) / 100.0);
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
    int waitIndex = 0;

    do {
        OSWaitSemaphore(&accessSemaphores[waitIndex]);
        waitIndex++;
    } while (waitIndex < 4);

    m_shopFlags = 0;
    m_shopStatusFlags = 0;
    m_startBonusFlags = 0;
    m_scrInitEnd = 0;
    m_makeMapObjFlg = 0;
    memset(&m_mapObjWork, 0, sizeof(GbaQueueMapObjWork));

    if ((m_stageNo != stageId) || (m_mapNo != mapId)) {
        m_stageFlags = 0xF;
        m_chgUseItemFlags = 0xF;
    }

    m_stageNo = stageId;
    m_mapNo = mapId;
    m_chgScouFlags = 0xF;

    int signalIndex = 0;
    do {
        OSSignalSemaphore(&accessSemaphores[signalIndex]);
        signalIndex++;
    } while (signalIndex < 4);

    if (Joybus.LoadMap(stageId, mapId) == 0) {
        int loadWaitIndex = 0;
        do {
            OSWaitSemaphore(&accessSemaphores[loadWaitIndex]);
            loadWaitIndex++;
        } while (loadWaitIndex < 4);

        m_stageFlags = 0xF;
        m_chgUseItemFlags = 0xF;

        int loadSignalIndex = 0;
        do {
            OSSignalSemaphore(&accessSemaphores[loadSignalIndex]);
            loadSignalIndex++;
        } while (loadSignalIndex < 4);
    }

    memset(m_hitInfo, 0xFF, sizeof(m_hitInfo));
    m_chgHitFlags = 0;
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
	OSWaitSemaphore(accessSemaphores + channel);
	*stageNo = m_stageNo;
	*mapNo = m_mapNo;
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
	stageFlg = static_cast<char>(m_stageFlags);
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
	OSSemaphore* semaphore = accessSemaphores + channel;

	OSWaitSemaphore(semaphore);
	m_stageFlags = static_cast<unsigned char>(m_stageFlags & ~(1 << channel));
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

	if ((static_cast<signed char>(m_radarTypeFlags) != 0) || (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)) {
		return;
	}

	const int* wmParams = Game.m_gameWork.m_wmBackupParams;
	validMemberCount = 0;
	for (i = 0; i < 4; i++) {
		if (wmParams[i] >= 0) {
			validMemberCount++;
		}
	}

	activeMask = 0;
	for (i = 0; i < 4; i++) {
		m_radarType[i] = 1;
		if ((Game.m_scriptFoodBase[i] != 0) &&
		    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_shopState != 0)) {
			activeMask |= (1 << i);
		}
	}

	assignedCount = 0;
	prevAssignedType = 0;
	while (assignedCount < static_cast<int>(validMemberCount)) {
		const int slot = rand() & 3;
		if ((activeMask & (1 << slot)) != 0) {
			int assignedType = assignedCount;
			if (assignedCount >= 2) {
				if (assignedCount == 2) {
					assignedType = assignedCount + (rand() & 1);
				} else {
					assignedType = (prevAssignedType == 2) ? 3 : 2;
				}
			}

			OSWaitSemaphore(accessSemaphores + slot);
			m_radarType[slot] = static_cast<unsigned char>(assignedType);
			OSSignalSemaphore(accessSemaphores + slot);

			activeMask &= static_cast<unsigned int>(~(1 << slot));
			assignedCount++;
			prevAssignedType = assignedType;
		}
	}

	if (m_singleMode != 0) {
		m_radarType[0] = Game.m_gameWork.m_mogScoreRadarType;
		m_radarType[1] = Game.m_gameWork.m_mogScoreRadarType;
		m_radarType[2] = Game.m_gameWork.m_mogScoreRadarType;
		m_radarType[3] = Game.m_gameWork.m_mogScoreRadarType;
	}

	obj[0x2D40] = 1;
	if (Game.m_gameWork.m_bossArtifactStageIndex >= 0xF) {
		m_radarType[0] = 0;
		m_radarType[1] = 0;
		m_radarType[2] = 0;
		m_radarType[3] = 0;
	}

	for (i = 0; i < 4; i++) {
		const unsigned char mask = static_cast<unsigned char>(1 << i);
		const unsigned char oldMode = m_radarMode;

		OSWaitSemaphore(accessSemaphores + i);
		m_radarMode = static_cast<unsigned char>((oldMode & ~mask) | mask);
		if (oldMode != m_radarMode) {
			m_chgRadarMode = static_cast<unsigned char>(m_chgRadarMode | mask);
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
	unsigned int outOfShoukiMask;
	int i;
	char* obj;

	memset(localPlayerStat, 0, sizeof(localPlayerStat));
	memset(localNames, 0, sizeof(localNames));

	for (i = 0; i < 8; i++) {
		memcpy(localNames + (i * 0x10), Game.m_caravanWorkArr[i].m_name, 0x10);
	}

	if (reinterpret_cast<int*>(&CFlat)[0x4101] != 0) {
		unsigned char* entry = localPlayerStat;
		outOfShoukiMask = 0;
		for (i = 0; i < 4; i++) {
			char menuStageMode = m_singleMode;
			CGPartyObj* partyObj;
			CCaravanWork* caravanWork;

			if ((menuStageMode != 0) && (i == 1)) {
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
				partyObj = Game.m_partyObjArr[0];
			} else {
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
				partyObj = Game.m_partyObjArr[i];
			}

			if (caravanWork != 0) {
				if ((menuStageMode == 0) || ((menuStageMode != 0) && (i == 0))) {
					entry[3] = 1;
				} else if ((menuStageMode != 0) && (i == 1) && (Game.m_scriptFoodBase[0] != 0)) {
					entry[3] = 1;
				}

				entry[0x16] = static_cast<unsigned char>(caravanWork->m_maxHp);
				entry[0x17] = static_cast<unsigned char>(caravanWork->m_hp);
				{
					unsigned char tribeAppearance = static_cast<unsigned char>((caravanWork->m_tribeId & 3) |
					                                      ((caravanWork->m_appearanceVariant & 3) << 2));
					if (caravanWork->m_genderFlag != 0) {
						tribeAppearance |= 0x80;
					}
					entry[2] = tribeAppearance;
				}

				*reinterpret_cast<int*>(entry + 0x24) = caravanWork->m_gil;
				{
					unsigned short progress = 0xFF;
					if (caravanWork->m_progressValue <= 0xFF) {
						progress = caravanWork->m_progressValue;
					}
					*reinterpret_cast<unsigned short*>(entry + 0x14) = progress;
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

				entry[0x20] = static_cast<unsigned char>(caravanWork->m_strength > 99 ? 99 : caravanWork->m_strength);
				entry[0x21] = static_cast<unsigned char>(caravanWork->m_defense > 99 ? 99 : caravanWork->m_defense);
				entry[0x22] = static_cast<unsigned char>(caravanWork->m_magic > 99 ? 99 : caravanWork->m_magic);
				entry[0xD2] = caravanWork->m_bonusCondition;
				entry[0xD5] = static_cast<unsigned char>(caravanWork->unk_0x3ac);

				memcpy(entry + 0x3A, caravanWork->m_inventoryItems, 0x80);
				{
					int artifactIndex = 0;
					int artifactGroup;
					for (artifactGroup = 0; artifactGroup < 0x20; artifactGroup++) {
						if (static_cast<short>(caravanWork->m_artifacts[artifactIndex]) > 0) {
							reinterpret_cast<unsigned int*>(entry + 0x28)[artifactIndex / 32] |=
							    static_cast<unsigned int>(1U << (artifactIndex % 32));
						}
						artifactIndex++;
						if (static_cast<short>(caravanWork->m_artifacts[artifactIndex]) > 0) {
							reinterpret_cast<unsigned int*>(entry + 0x28)[artifactIndex / 32] |=
							    static_cast<unsigned int>(1U << (artifactIndex % 32));
						}
						artifactIndex++;
						if (static_cast<short>(caravanWork->m_artifacts[artifactIndex]) > 0) {
							reinterpret_cast<unsigned int*>(entry + 0x28)[artifactIndex / 32] |=
							    static_cast<unsigned int>(1U << (artifactIndex % 32));
						}
						artifactIndex++;
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
					entry[0xD4] = static_cast<unsigned char>(partyObj->IsDispRader() != 0);
				}

				if ((caravanWork->IsOutOfShouki() != 0) && (entry[0x17] != 0)) {
					outOfShoukiMask |= (1U << i);
				}

				if (caravanWork->CanPlayerUseItem() != 0) {
					entry[0xD6] |= GbaQueConst::CAN_REPLY;
				}
				if (caravanWork->CanPlayerPutItem() != 0) {
					entry[0xD6] |= GbaQueConst::ITEM_ATTACH;
				}
			}

			if (partyObj != 0) {
				short posX = static_cast<short>(partyObj->m_worldPosition.x / kGbaQueueMapCoordScale);
				short posZ = static_cast<short>(partyObj->m_worldPosition.z / kGbaQueueMapCoordScale);
				entry[1] = 1;
				*reinterpret_cast<short*>(entry + 0x36) = posX;
				*reinterpret_cast<short*>(entry + 0x38) = posZ;
			}

			entry += 0xDC;
		}
	}

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	obj = reinterpret_cast<char*>(this);
	memcpy(obj + 0x7C4, GetPlayerDataBlock(this), kGbaQueuePlayerDataBlockBytes);
	memcpy(GetPlayerDataBlock(this), localPlayerStat, kGbaQueuePlayerDataBlockBytes);
	memcpy(obj + 0x2A74, localNames, kGbaQueueCaravanNameBlockBytes);

	m_prevOutOfShoukiFlags = m_outOfShoukiFlags;
	m_outOfShoukiFlags = static_cast<unsigned char>(outOfShoukiMask);

	for (i = 0; i < 4; i++) {
		char* base = obj + (i * 0xDC);
		int j;

		if (memcmp(base + 0x7C4 + 0x18, base + 0x454 + 0x18, 8) != 0) {
			m_compatibilityFlg[0] = static_cast<unsigned char>(m_compatibilityFlg[0] | (1 << i));
		}
		if (*reinterpret_cast<unsigned int*>(base + 0x7C4 + 0x24) != *reinterpret_cast<unsigned int*>(base + 0x454 + 0x24)) {
			m_compatibilityFlg[1] = static_cast<unsigned char>(m_compatibilityFlg[1] | (1 << i));
		}

		for (j = 0; j < 8; j++) {
			if (memcmp(base + 0x7C4 + 4, base + 0x454 + 4, 8) != 0) {
				m_maskSendState[i] = static_cast<signed char>(m_maskSendState[i] | (1 << j));
			}
		}

		if (base[0x7C4 + 0x23] != base[0x454 + 0x23]) {
			m_moneyState[0] = static_cast<unsigned char>(m_moneyState[0] | (1 << i));
		}
		if (memcmp(base + 0x7C4 + 0x20, base + 0x454 + 0x20, 3) != 0) {
			m_moneyState[1] = static_cast<unsigned char>(m_moneyState[1] | (1 << i));
		}
		if (memcmp(base + 0x7C4 + 0x28, base + 0x454 + 0x28, 0xC) != 0) {
			m_moneyState[2] = static_cast<unsigned char>(m_moneyState[2] | (1 << i));
		}
		if (*reinterpret_cast<unsigned short*>(base + 0x7C4 + 0x14) !=
		    *reinterpret_cast<unsigned short*>(base + 0x454 + 0x14)) {
			m_compatibilityFlg[2] = static_cast<unsigned char>(m_compatibilityFlg[2] | (1 << i));
		}

		if (base[0x7C4 + 0xD3] != base[0x454 + 0xD3]) {
			const int shift = i << 1;
			m_radarMode = static_cast<unsigned char>(m_radarMode | (1 << shift));
			if ((static_cast<int>(base[0x454 + 0xD3]) - static_cast<int>(base[0x7C4 + 0xD3])) != 1) {
				m_radarMode = static_cast<unsigned char>(m_radarMode | (2 << shift));
			}
		}
	}

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
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
	int i;

	memset(localEnemyData, 0, sizeof(localEnemyData));

	if (reinterpret_cast<int*>(&CFlat)[0x4101] != 0) {
		unsigned char* enemyEntry = localEnemyData;
		enemyObjPtrs = &Game.m_scriptWork[0][0][0];
		enemyWorkPtrs = &Game.m_scriptWork[4][0][0];

		for (i = 0; i < 0x40; i++) {
			if (enemyObjPtrs[i] == 0) {
				enemyEntry[3] = 0;
			} else {
				const int enemyDataBase = Game.unkCFlatData0[1] +
				    reinterpret_cast<CMonWork*>(enemyWorkPtrs[i])->m_baseDataIndex * 0x1D0;
				const unsigned int enemyKind = *reinterpret_cast<unsigned short*>(enemyDataBase + 0x10C);

				if (enemyKind == 10) {
					enemyEntry[1] = 1;
				} else if (enemyKind == 0xB) {
					enemyEntry[1] = 3;
				} else {
					enemyEntry[1] = 2;
				}

				CMonWork* enemyWork = reinterpret_cast<CMonWork*>(enemyWorkPtrs[i]);
				CGObject* enemyObj = reinterpret_cast<CGObject*>(enemyObjPtrs[i]);
				enemyEntry[3] = static_cast<unsigned char>(enemyWork->m_baseDataIndex);
				*reinterpret_cast<unsigned short*>(enemyEntry + 4) = enemyWork->m_hp;
				*reinterpret_cast<unsigned short*>(enemyEntry + 6) = enemyWork->m_maxHp;
				int isDispRadar = static_cast<int>(enemyObj->IsDispRader());
				int isDispRadarMask = -isDispRadar | isDispRadar;
				enemyEntry[2] = static_cast<unsigned char>(isDispRadarMask >> 31);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0xC) =
				    *reinterpret_cast<short*>(reinterpret_cast<char*>(enemyObj) + 0x510);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0xE) =
				    *reinterpret_cast<short*>(reinterpret_cast<char*>(enemyObj) + 0x512);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0x10) =
				    *reinterpret_cast<short*>(reinterpret_cast<char*>(enemyObj) + 0x514);
				*reinterpret_cast<unsigned short*>(enemyEntry + 0x12) =
				    *reinterpret_cast<short*>(reinterpret_cast<char*>(enemyObj) + 0x516);
				long long posX = static_cast<int>(enemyObj->m_worldPosition.x / kGbaQueueMapCoordScale);
				long long posZ = static_cast<int>(enemyObj->m_worldPosition.z / kGbaQueueMapCoordScale);
				*reinterpret_cast<short*>(enemyEntry + 8) = static_cast<short>(posX);
				*reinterpret_cast<short*>(enemyEntry + 0xA) = static_cast<short>(posZ);
			}

			enemyEntry += 0x14;
		}
	}

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	memcpy(reinterpret_cast<char*>(this) + 0xB34, localEnemyData, sizeof(localEnemyData));

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
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
	int i;

	memset(localMapItems, 0, sizeof(localMapItems));
	numMapItems = 0;

	if (reinterpret_cast<int*>(&CFlat)[0x4101] != 0) {
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
					if (itemStage >= bossStageLimit) {
						mapItemEntry[1] = 5;
					} else {
						mapItemEntry[1] = 4;
					}
				}

				int isDispRader = object->IsDispRader();
				numMapItems++;
				mapItemEntry[2] = static_cast<unsigned char>((-isDispRader | isDispRader) >> 31);
				*reinterpret_cast<short*>(mapItemEntry + 8) = static_cast<short>(object->m_worldPosition.x / kGbaQueueMapCoordScale);
				*reinterpret_cast<short*>(mapItemEntry + 0xA) = static_cast<short>(object->m_worldPosition.z / kGbaQueueMapCoordScale);
				mapItemEntry += 0x14;
			}

			object = gCFlatRuntime2.FindGObjNext(object);
		}
	}

	m_mapItemCount = numMapItems;

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	memcpy(reinterpret_cast<char*>(this) + 0x2434, localMapItems, sizeof(localMapItems));

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
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

    baseX = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x48A);
    baseZ = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x48C);
    memcpy(localEnemyData, obj + 0xB34, kGbaQueueEnemyDataBytes);

    prevEntry = obj + channel * kGbaQueueEnemyDataBytes + 0x1034;
    radarMode = m_radarType[channel];
    localEntry = localEnemyData;
    for (i = 0; i < 0x40; i++) {
        *reinterpret_cast<short*>(localEntry + 8) = *reinterpret_cast<short*>(localEntry + 8) - baseX;
        *reinterpret_cast<short*>(localEntry + 10) = *reinterpret_cast<short*>(localEntry + 10) - baseZ;

        int enemyX = *reinterpret_cast<short*>(localEntry + 8);
        if ((enemyX < 0 ? -enemyX : enemyX) < 0x50) {
            int enemyZ = *reinterpret_cast<short*>(localEntry + 10);
            if ((enemyZ < 0 ? -enemyZ : enemyZ) >= 0x40) {
                *reinterpret_cast<short*>(localEntry + 8) = -1;
                *reinterpret_cast<short*>(localEntry + 10) = -1;
                localEntry[0] = 0;
            } else {
                localEntry[0] = 1;
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
	i = 0;
	while (i < m_mapItemCount) {
		*reinterpret_cast<short*>(localEntry + 8) =
			static_cast<short>(*reinterpret_cast<short*>(localEntry + 8) - baseX);
		*reinterpret_cast<short*>(localEntry + 10) =
			static_cast<short>(*reinterpret_cast<short*>(localEntry + 10) - baseZ);

		int localX = *reinterpret_cast<short*>(localEntry + 8);
		int localZ = *reinterpret_cast<short*>(localEntry + 10);

		if ((localX < 0 ? -localX : localX) >= 0x50 || (localZ < 0 ? -localZ : localZ) >= 0x40) {
			*reinterpret_cast<short*>(localEntry + 8) = -1;
			*reinterpret_cast<short*>(localEntry + 10) = -1;
			localEntry[0] = 0;
		} else {
			localEntry[0] = 1;
		}

		if (localEntry[2] == 0) {
			localEntry[0] = 0;
		}
		if (m_radarType[channel] != 3) {
			localEntry[0] = 0;
		}

		localEntry += 0x14;
		i++;
	}

	count = 0;
	localEntry = localMapItems;
	prevEntry = obj + channel * kGbaQueueMapItemDataBytes + 0x2574;
	outPtr = reinterpret_cast<unsigned char*>(outData);
	i = 0;
	while (i < m_mapItemCount) {
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
		i++;
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
		int k;
		for (k = 0; k < 0x10; k++) {
			out[k] = mapObj[k * 0x14];
		}
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
	localPlayerData = m_playerData[channel];
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

	flag = m_scrInitEnd;
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
	if ((m_outOfShoukiFlags & channelMask) != (m_prevOutOfShoukiFlags & channelMask)) {
		changed = 1;
	}

	outData[0] = 0x13;
	outData[1] = static_cast<unsigned char>(hpFlags);
	outData[2] = static_cast<unsigned char>(hp);
	outData[3] = ((m_outOfShoukiFlags & channelMask) != 0);

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

		m_letterDatFlg |= channelMask;
		Joybus.SetLetterSize(channel, 0);
		m_letterFlags &= ~channelMask;
		return 0;
	}

char* npcNameBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7A7) char[kGbaQueueLetterNpcNameBytes];
	if (npcNameBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0x7A9);
		}
		return -1;
	}
	memset(npcNameBuf, 0, kGbaQueueLetterNpcNameBytes);

char* subjectNameBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7B1) char[kGbaQueueLetterSubjectNameBytes];
	if (subjectNameBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0x7B3);
		}
		return -1;
	}
	memset(subjectNameBuf, 0, kGbaQueueLetterSubjectNameBytes);

unsigned int* letterEntryBuf =
	new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x7BB) unsigned int[kGbaQueueLetterEntryAllocWords];
	if (letterEntryBuf == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0x7BD);
		}
		return -1;
	}
	memset(letterEntryBuf, 0, kGbaQueueLetterEntryBytes);

	const CCaravanWork* caravanWork = reinterpret_cast<const CCaravanWork*>(scriptFood);
	const unsigned int letterCount = static_cast<unsigned int>(caravanWork->m_letterCount);

	int subjectCount = 0;
	int npcCount = 0;

	char* npcWrite = npcNameBuf;
	char* subjectWrite = subjectNameBuf;
	unsigned int* entryWrite = letterEntryBuf;

	char** npcTable = Game.m_cFlatDataArr[1].TableStrings(2);
	char** subjectTable = Game.m_cFlatDataArr[1].TableStrings(5);
	char tempName[kGbaQueueLetterTempNameBytes];

	for (int i = 0; i < static_cast<int>(letterCount); i++) {
		int matchedSubject = -1;
		int matchedNpc = -1;

		const CCaravanWork::CLetterWork* cur = &caravanWork->m_letters[i];

		for (int j = 0; j < i; j++) {
			const CCaravanWork::CLetterWork* prev = &caravanWork->m_letters[j];
			if (cur->SenderId() == prev->SenderId()) {
				matchedNpc = j;
			}
			if (cur->MessageType() == prev->MessageType()) {
				matchedSubject = j;
			}
			if (matchedSubject != -1 && matchedNpc != -1) {
				break;
			}
		}

		if (matchedNpc != -1) {
			(reinterpret_cast<unsigned char*>(entryWrite))[5] =
				(reinterpret_cast<unsigned char*>(letterEntryBuf + matchedNpc * 2))[5];
		} else {
			if (npcCount >= 0x80 && (unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_npc_max_over), const_cast<char*>(s_gbaque_cpp), 0x7DC);
			}

			memset(tempName, 0, sizeof(tempName));
			strcpy(tempName, npcTable[(cur->Word0() >> 9) & 0x1FF]);
			memcpy(npcWrite, tempName, kGbaQueueLetterNpcNameEntryBytes);
			npcWrite += kGbaQueueLetterNpcNameEntryBytes;
			(reinterpret_cast<unsigned char*>(entryWrite))[5] = static_cast<unsigned char>(npcCount++);
		}

		if (matchedSubject != -1) {
			(reinterpret_cast<unsigned char*>(entryWrite))[4] =
				(reinterpret_cast<unsigned char*>(letterEntryBuf + matchedSubject * 2))[4];
		} else {
			if (subjectCount >= 0x100 && (unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_subject_max_over), const_cast<char*>(s_gbaque_cpp), 0x7F0);
			}

			memset(tempName, 0, sizeof(tempName));
			strcpy(tempName, subjectTable[(cur->HeaderWord() >> 2) & 0x1FF]);
			memcpy(subjectWrite, tempName, kGbaQueueLetterSubjectNameEntryBytes);
			subjectWrite += kGbaQueueLetterSubjectNameEntryBytes;
			(reinterpret_cast<unsigned char*>(entryWrite))[4] = static_cast<unsigned char>(subjectCount++);
		}

		unsigned int flags = 0;
		const unsigned char curFlags = cur->Flags();
		if (((curFlags >> 7) & 1) != 0) {
			flags = GbaQueConst::ITEM_USE;
		}
		if (((curFlags >> 6) & 1) != 0) {
			flags |= GbaQueConst::ITEM_PUT;
		}
		if (((curFlags >> 5) & 1) != 0) {
			flags |= GbaQueConst::MONEY_ATTACH;
		}
		if (((curFlags >> 4) & 1) != 0) {
			flags |= GbaQueConst::OPEN_LETTER;
		}

		if (cur->AttachmentIsGil() == 0) {
			const int value = static_cast<int>(cur->AttachmentValue());
			if (value != 0) {
				if (value >= 0x100 && value <= 0x124) {
					if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(s_letter_data_error), const_cast<char*>(s_gbaque_cpp), 0x810, channel, i);
					}
				} else {
					flags |= GbaQueConst::MOVE_ATTACH;
					entryWrite[0] = SwapU32(value);
				}
			}
		} else {
			const unsigned int value = cur->AttachmentValue();
			if (value != 0) {
				flags |= GbaQueConst::REPLY_LETTER;
				entryWrite[0] = SwapU32(value * 100);
			}
		}

		(reinterpret_cast<unsigned char*>(entryWrite))[6] = static_cast<unsigned char>(flags);
		entryWrite += 2;
	}

	unsigned int header[4];
	memset(header, 0, sizeof(header));
	header[0] = SwapU32(letterCount);
	header[1] = SwapU32(subjectCount);
	header[2] = SwapU32(npcCount);
	header[3] = reinterpret_cast<unsigned int*>(&CFlat)[0x4102];

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

	m_letterDatFlg |= channelMask;
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
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0x85B);
        }
        return -1;
    }
    memset(srcText, 0, kGbaQueueScratchTextSize);

char* workText = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x862) char[kGbaQueueScratchTextSize];
    if (workText == 0) {
        if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0x864);
        }
        return -1;
    }
    memset(workText, 0, kGbaQueueScratchTextSize);

    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
    CMes::m_tempVar[0] = caravanWork->m_letters[letterIndex].TempVar(0);
    CMes::m_tempVar[1] = caravanWork->m_letters[letterIndex].TempVar(1);
    CMes::m_tempVar[2] = caravanWork->m_letters[letterIndex].TempVar(2);
    CMes::m_tempVar[3] = caravanWork->m_letters[letterIndex].TempVar(3);

    unsigned short msgIndex = caravanWork->m_letters[letterIndex].HeaderWord();
    int mesIndex = (msgIndex & 0x7FC) >> 1;

    strcpy(srcText, reinterpret_cast<char**>(Game.m_cFlatDataArr[1].Data(3).m_data)[mesIndex]);
    CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);
    int totalSize = static_cast<int>(strlen(workText) + 1);
    memcpy(outData, workText, totalSize);

    memset(srcText, 0, kGbaQueueScratchTextSize);
    memset(workText, 0, kGbaQueueScratchTextSize);
    strcpy(srcText, reinterpret_cast<char**>(Game.m_cFlatDataArr[1].Data(3).m_data)[mesIndex + 1]);
    CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);
    int line2Size = static_cast<int>(strlen(workText));
    memcpy(outData + totalSize, workText, line2Size + 1);
    totalSize += line2Size + 1;

	delete[] workText;
	delete[] srcText;

    m_letterDatFlg = static_cast<unsigned char>(m_letterDatFlg | static_cast<unsigned char>(0x10 << channel));
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
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_letterDatFlg)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_letterDatFlg = static_cast<unsigned char>(m_letterDatFlg & ~(1 << channel));
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
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_letterDatFlg)) & (0x10 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_letterDatFlg = static_cast<unsigned char>(m_letterDatFlg & ~(0x10 << channel));
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
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
	int letterIndex = valueBytes[2];
	int hasGil = caravanWork->m_letters[letterIndex].FlagsBits().m_attachmentIsGil;
	int result;

	if (hasGil == 0) {
		int item = caravanWork->m_letters[letterIndex].AttachmentValue();
		if (item != 0) {
			if ((item < 1) || (item > 0x9E)) {
				if (caravanWork->AddItem(item, 0) == 0) {
					result = 1;
				} else {
					result = 0;
				}
			}
		}
	} else {
		int item = caravanWork->m_letters[letterIndex].AttachmentValue();
		if (item != 0) {
			int gil = item * 100;
			if (caravanWork->CanAddGil(gil) == 0) {
				result = 1;
			} else {
				caravanWork->AddGil(gil);
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
		caravanWork->m_letters[letterIndex].SetAttachmentClaimed();
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

	unsigned char arg0 = recvBuffer[0];
	unsigned char arg1 = recvBuffer[1];
	unsigned int value =
		(static_cast<unsigned int>(recvBuffer[3]) << 24) |
		(static_cast<unsigned int>(recvBuffer[4]) << 16) |
		(static_cast<unsigned int>(recvBuffer[5]) << 8) |
		recvBuffer[6];
	int itemId = 0;
	unsigned int gil = value;

	if (recvBuffer[2] != 0) {
		gil = value;
	} else {
		itemId = value & 0xffff;
		gil = 0;
	}

	unsigned int* scriptFoodBase = Game.m_scriptFoodBase + channel;
	reinterpret_cast<CCaravanWork*>(*scriptFoodBase)->FGLetterReply(arg0, arg1, itemId, gil);
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
	int i;

	if (m_scrInitEnd == 0) {
		i = 0;
		do {
			OSWaitSemaphore(&accessSemaphores[i]);
			i++;
		} while (i < 4);

		if (m_mapObjWork.m_count != 0) {
			memset(&m_mapObjWork, 0, sizeof(GbaQueueMapObjWork));
		}

		i = 0;
		do {
			OSSignalSemaphore(&accessSemaphores[i]);
			i++;
		} while (i < 4);
	} else {
		GbaQueueMapObjWork mapObjWork;
		memset(&mapObjWork, 0, sizeof(mapObjWork));

		CFlatRuntime2::CMapObjectInfo* mapObj = CFlat.m_mapObjectInfo;
		i = 0;
		do {
			char objType = mapObj->m_type;
			if (objType != -1) {
				unsigned int count = mapObjWork.m_count;
				if (objType >= 0x19) {
					if (static_cast<unsigned int>(System.m_execParam) >= 2) {
						System.Printf(const_cast<char*>(s_unknown_mapobj_type_error), objType);
					}
				} else {
					float x = mapObj->m_x;
					const float scale = kGbaQueueMapCoordScale;
					unsigned int mask = 1U << count;
					unsigned int clearMask = ~mask;
					float y = mapObj->m_y;
					float z = mapObj->m_z;
					float r = mapObj->m_radius;
					int drawFlag = static_cast<int>(mapObj->m_drawFlag);
					GbaQueueMapObjEntry* entry = &mapObjWork.m_entries[count];

					entry->m_type = static_cast<unsigned char>(objType);
					entry->m_x = static_cast<short>((int)(x / scale));
					entry->m_y = static_cast<short>((int)(y / scale));
					entry->m_z = static_cast<short>((int)(z / scale));
					entry->m_radius = static_cast<short>((int)(r / scale));

					unsigned int drawMask = mapObjWork.m_drawFlags;
					drawMask = (drawMask & clearMask) | (mask & ((-drawFlag | drawFlag) >> 31));
					mapObjWork.m_drawFlags = drawMask;
					mapObjWork.m_count = static_cast<unsigned char>(count + 1);
				}
			}

			i++;
			mapObj++;
		} while (i < 0x20);

		i = 0;
		do {
			OSWaitSemaphore(&accessSemaphores[i]);
			i++;
		} while (i < 4);

		memcpy(&m_mapObjWork, &mapObjWork, sizeof(mapObjWork));

		i = 0;
		do {
			OSSignalSemaphore(&accessSemaphores[i]);
			i++;
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
	GbaQueueMapObjWork mapObjWork;
	GbaQueueMapObjEntry* workEntry;
	int i;
	int outSize;

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	memcpy(&mapObjWork, &m_mapObjWork, sizeof(mapObjWork));

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	workEntry = mapObjWork.m_entries;
	outSize = 5;
	outData[0] = mapObjWork.m_count;
	outData[1] = static_cast<unsigned char>(mapObjWork.m_drawFlags);
	outData[2] = static_cast<unsigned char>(mapObjWork.m_drawFlags >> 8);
	outData[3] = static_cast<unsigned char>(mapObjWork.m_drawFlags >> 16);
	outData[4] = static_cast<unsigned char>(mapObjWork.m_drawFlags >> 24);

	for (i = 0; i < mapObjWork.m_count; i++) {
		workEntry = &mapObjWork.m_entries[i];
		outData[outSize++] = workEntry->m_type;
		outData[outSize++] = static_cast<unsigned char>(workEntry->m_x);
		outData[outSize++] = static_cast<unsigned char>((workEntry->m_x >> 8) & 0xFF);
		outData[outSize++] = static_cast<unsigned char>(workEntry->m_y);
		outData[outSize++] = static_cast<unsigned char>((workEntry->m_y >> 8) & 0xFF);
		outData[outSize++] = static_cast<unsigned char>(workEntry->m_z);
		outData[outSize++] = static_cast<unsigned char>((workEntry->m_z >> 8) & 0xFF);
		outData[outSize++] = static_cast<unsigned char>(workEntry->m_radius);
		outData[outSize++] = static_cast<unsigned char>((workEntry->m_radius >> 8) & 0xFF);
	}

	m_makeMapObjFlg = 1;
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

	*drawFlags = m_mapObjWork.m_drawFlags;

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
	m_letterFlags = static_cast<unsigned char>(m_letterFlags | (1 << channel));
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
	int flag;
	char value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<char>(m_favoriteFlags);
	flag = static_cast<int>(value) & (1 << channel);
	flag = static_cast<unsigned int>(-flag | flag) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);

	return static_cast<unsigned int>(flag);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_favoriteFlags = static_cast<unsigned char>(m_favoriteFlags & ~(1 << channel));
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
	int flag;
	char value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<char>(m_moneyFlags);
	flag = static_cast<int>(value) & (1 << channel);
	flag = static_cast<unsigned int>(-flag | flag) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);

	return static_cast<unsigned int>(flag);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_moneyFlags = static_cast<unsigned char>(m_moneyFlags & ~(1 << channel));
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
	m_scrInitEnd = 0;
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
	unsigned short crc[2];
	unsigned int stackValue = value;
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&stackValue);
	char* obj = reinterpret_cast<char*>(this);

	if ((static_cast<int>(valueBytes[0]) >> 6) == 0) {
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CB3 + channel * 0x20] = static_cast<char>(valueBytes[0]);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + channel * 0x20) = 1;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + channel * 0x20) =
		    static_cast<unsigned short>((valueBytes[1] << 8) | valueBytes[2]);
		memset(obj + 0x2CB9 + channel * 0x20, 0, 0x11);
		obj[0x2CB9 + channel * 0x20] = static_cast<char>(valueBytes[3]);
		OSSignalSemaphore(accessSemaphores + channel);
		return;
	}

	GbaCMakeInfo localInfo;

	OSWaitSemaphore(accessSemaphores + channel);
	{
		char* cmakeBase = obj + channel * 0x20;
		short packetCount = *reinterpret_cast<short*>(cmakeBase + 0x2CB4);
		char* writeBase = cmakeBase + static_cast<int>(packetCount) * 3;
		*reinterpret_cast<short*>(cmakeBase + 0x2CB4) = static_cast<short>(packetCount + 1);
		writeBase[0x2CB7] = static_cast<char>(valueBytes[1]);
		writeBase[0x2CB8] = static_cast<char>(valueBytes[2]);
		writeBase[0x2CB9] = static_cast<char>(valueBytes[3]);

		if (*reinterpret_cast<short*>(cmakeBase + 0x2CB4) >= 6) {
			localInfo = cmakeInfo[channel];
		}
	}
	OSSignalSemaphore(accessSemaphores + channel);

	if (*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20) < 6) {
		return;
	}

	if (strlen(reinterpret_cast<char*>(obj + 0x2CB9 + channel * 0x20)) == 0) {
		obj[0x2CCA + channel * 0x20] = static_cast<char>(0xFF);
		obj[0x2CD1 + channel * 0x20] = static_cast<char>(0xFF);
		return;
	}

	crc[0] = 0xFFFF;
	if (Joybus.Crc16(0x10, reinterpret_cast<unsigned char*>(localInfo.m_name), crc) != localInfo.m_crc) {
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(s_cmake_name_crc_error), const_cast<char*>(s_gbaque_cpp), 0xAD3);
		}
		Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
	} else {
		for (int i = 0; i < 4; i++) {
			OSWaitSemaphore(accessSemaphores + i);
		}

		for (int i = 0; i < 4; i++) {
			const int otherOffset = i * 0x20;
			if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
			    (strcmp(obj + 0x2CB9 + otherOffset, localInfo.m_name) == 0)) {
				memset(obj + 0x2CB9 + channel * 0x20, 0, 0x11);
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

		char** nameTable = Game.m_cFlatDataArr[1].TableStrings(2);
		for (int i = 0; i < 0x100; i++) {
			if (strcmp(nameTable[i], localInfo.m_name) == 0) {
				Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 8; i++) {
			CCaravanWork* caravanWork = &Game.m_caravanWorkArr[i];
			if ((i != localInfo.m_playerSlot) && (caravanWork->m_shopState != 0) &&
			    (caravanWork->m_caravanLocalFlags == '\0') &&
			    (strcmp(reinterpret_cast<char*>(caravanWork->m_name), localInfo.m_name) == 0)) {
				Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
				return;
			}
		}

		Joybus.SendResult(channel, 0, localInfo.m_resultCode, 0);
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CB3 + channel * 0x20] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + channel * 0x20) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + channel * 0x20) = 0;
		OSSignalSemaphore(accessSemaphores + channel);
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
	unsigned int stackValue = value;
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&stackValue);
	char* obj = reinterpret_cast<char*>(this);
	unsigned char charaType = valueBytes[2];

	if (charaType == 0xFF) {
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CCA + channel * 0x20] = static_cast<char>(0xFF);
		obj[0x2CD1 + channel * 0x20] = static_cast<char>(0xFF);
		OSSignalSemaphore(accessSemaphores + channel);
		return;
	}

	bool foundDuplicate = false;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);
	}

	unsigned char playerSlot = static_cast<unsigned char>(obj[0x2CB8 + channel * 0x20]);
	for (int i = 0; i < 4; i++) {
		int otherOffset = i * 0x20;
		if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
		    (static_cast<unsigned char>(obj[0x2CCA + otherOffset]) == charaType)) {
			Joybus.SendResult(channel, 1, valueBytes[1], 0);
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
				Joybus.SendResult(channel, 1, valueBytes[1], 0);
				return;
			}
		}
	}

	Joybus.SendResult(channel, 0, valueBytes[1], 0);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2CCA + channel * 0x20] = static_cast<char>(charaType);
	OSSignalSemaphore(accessSemaphores + channel);
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
	unsigned int stackValue = value;
	unsigned char* valueBytes = reinterpret_cast<unsigned char*>(&stackValue);
	char* obj = reinterpret_cast<char*>(this);

	if (valueBytes[2] == 0xFF) {
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CD1 + channel * 0x20] = static_cast<char>(valueBytes[2]);
		OSSignalSemaphore(accessSemaphores + channel);
		return;
	}

	bool foundDuplicate = false;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(accessSemaphores + i);
	}

	unsigned char playerSlot = static_cast<unsigned char>(obj[0x2CB8 + channel * 0x20]);
	for (int i = 0; i < 4; i++) {
		int otherOffset = i * 0x20;
		if ((channel != i) && (cmakeInfo[i].m_active != 0) &&
		    (static_cast<unsigned char>(obj[0x2CD1 + otherOffset]) == valueBytes[2])) {
			Joybus.SendResult(channel, 1, valueBytes[1], 0);
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
		    (static_cast<unsigned char>(caravanWork->unk_0x3ac) == valueBytes[2])) {
			Joybus.SendResult(channel, 1, valueBytes[1], 0);
			return;
		}
	}

	Joybus.SendResult(channel, 0, valueBytes[1], 0);
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2CD1 + channel * 0x20] = static_cast<char>(valueBytes[2]);
	OSSignalSemaphore(accessSemaphores + channel);
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

	if ((static_cast<int>(valueBytes[0]) >> 6) == 0) {
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CB3 + channel * 0x20] = static_cast<char>(valueBytes[0]);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + channel * 0x20) = 1;
		*reinterpret_cast<short*>(obj + 0x2CB6 + channel * 0x20) = static_cast<short>((valueBytes[1] << 8) | valueBytes[2]);
		memset(obj + 0x2CCD + channel * 0x20, 0, 4);
		obj[0x2CCD + channel * 0x20] = static_cast<char>(valueBytes[3]);
		OSSignalSemaphore(accessSemaphores + channel);
		return;
	}

	GbaCMakeInfo localInfo;

	OSWaitSemaphore(accessSemaphores + channel);
	{
		int writeOffset = static_cast<int>(*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20)) * 3;
		*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20) =
			static_cast<short>(*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20) + 1);
		char* favBase = obj + 0x2CCD + channel * 0x20;
		favBase[writeOffset - 2] = static_cast<char>(valueBytes[1]);
		favBase[writeOffset - 1] = static_cast<char>(valueBytes[2]);
		favBase[writeOffset] = static_cast<char>(valueBytes[3]);

		if (*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20) >= 2) {
			localInfo = cmakeInfo[channel];
		}
	}
	OSSignalSemaphore(accessSemaphores + channel);

	if (*reinterpret_cast<short*>(obj + 0x2CB4 + channel * 0x20) < 2) {
		return;
	}

	unsigned short crc = 0xFFFF;
	if (Joybus.Crc16(4, localInfo.m_favorite, &crc) != localInfo.m_crc) {
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
System.Printf(const_cast<char*>(s_cmake_favorite_crc_error), const_cast<char*>(s_gbaque_cpp), 0xBDC);
		}
		Joybus.SendResult(channel, 1, localInfo.m_resultCode, 0);
	} else {
		Joybus.SendResult(channel, 0, localInfo.m_resultCode, 0);
		OSWaitSemaphore(accessSemaphores + channel);
		obj[0x2CB3 + channel * 0x20] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + channel * 0x20) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + channel * 0x20) = 0;
		OSSignalSemaphore(accessSemaphores + channel);
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
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<char>(m_compatibilityFlg[channel]);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_compatibilityFlg[channel] = 0;
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
	int count = 2;
	unsigned char* writePtr;
	int outSize = 2;
	int selectedCount = 0;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(compatibilityData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x458, sizeof(compatibilityData));
	OSSignalSemaphore(accessSemaphores + channel);

	outCompatibility[0] = reinterpret_cast<unsigned char*>(this)[channel * 0xDC + 0x529];
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

	if ((count > 4) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
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
			char* src = Game.m_cFlatDataArr[1].TableStrings(2)[slotValue];
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
		if (MenuPcs.GetItemType(itemId, 1) == 1) {
		const int iconMask = localPlayerData[2] & 3;
		if (MenuPcs.GetItemIcon(itemId) == iconMask) {
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
	}

	outData[0] = count;
	return size;
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

	OSWaitSemaphore(semaphore);
	int mask = 0x10;
	mask <<= channel;
	m_shopFlags = static_cast<u8>(m_shopFlags | mask);
	OSSignalSemaphore(semaphore);

	if (Joybus.SetMType(channel, 3) != 0) {
		m_shopStatusFlags = static_cast<u8>(m_shopStatusFlags | mask);
	} else {
		m_shopStatusFlags = static_cast<u8>(m_shopStatusFlags & ~mask);
	}
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

	OSWaitSemaphore(semaphore);
	int mask = 1;
	mask <<= channel;
	m_shopFlags = static_cast<u8>(m_shopFlags | mask);
	OSSignalSemaphore(semaphore);

	if (Joybus.SetMType(channel, 2) != 0) {
		m_shopStatusFlags = static_cast<u8>(m_shopStatusFlags | mask);
	} else {
		m_shopStatusFlags = static_cast<u8>(m_shopStatusFlags & ~mask);
	}
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
		if ((itemId >= 0) && (itemId <= 0x9E)) {
			*indexPtr = static_cast<unsigned char>(itemIndex);
			equipCount++;
			indexPtr++;
		}
		itemPtr += 2;
		itemIndex++;
		remaining--;
	} while (remaining != 0);

	int indexBytesS = equipCount + 1;
	if ((indexBytesS & 3) != 0) {
		indexBytesS = (((indexBytesS >> 2) + 1) * 4);
	}
	indexBytes = static_cast<unsigned int>(indexBytesS);

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
 * Address:	TODO
 * Size:	TODO
 */
inline void GbaQueue::ClrShopFlg(int channel)
{
	const unsigned char playerMask = static_cast<unsigned char>(1 << channel);

	OSWaitSemaphore(accessSemaphores + channel);
	m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~playerMask);
	m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~playerMask);
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
inline void GbaQueue::ClrSmithFlg(int channel)
{
	const unsigned char shopMask = static_cast<unsigned char>(0x10 << channel);

	OSWaitSemaphore(accessSemaphores + channel);
	m_shopFlags = static_cast<unsigned char>(m_shopFlags & ~shopMask);
	m_shopStatusFlags = static_cast<unsigned char>(m_shopStatusFlags & ~shopMask);
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
int GbaQueue::MakeBuyData(int channel, char* outData)
{
char* itemNameScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xD79) char[kGbaQueueScratchTextSize];
	if (itemNameScratch == 0) {
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0xD7B);
		}
		return -1;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xD82) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0xD84);
		}
		return -1;
	}
	memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
	const unsigned int itemCount = static_cast<unsigned short>(caravanWork->m_shopListCount);

	int totalSize = 4;
	outData[0] = static_cast<char>(itemCount);
	char* writePtr = outData + 4;

	for (unsigned int i = 0; i < itemCount; i++) {
		const unsigned short itemId = static_cast<unsigned short>(reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel])->m_shopList[i]);
		const unsigned short swapped = SwapU16(itemId);
		memcpy(writePtr, &swapped, 2);
		writePtr += 2;
		totalSize += 2;
	}

	if ((itemCount & 1) != 0) {
		writePtr += 2;
		totalSize += 2;
	}

	const float userRate = static_cast<float>(static_cast<double>(caravanWork->m_shopParam) / 100.0);

	for (unsigned int i = 0; i < itemCount; i++) {
		const int itemId = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel])->m_shopList[i];
		int itemPrice = static_cast<unsigned short>(
			*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20));
		itemPrice = static_cast<int>(static_cast<float>(itemPrice) * userRate);
		if (itemPrice < 1) {
			itemPrice = 1;
		}

		const unsigned int packedPrice = SwapU32(static_cast<unsigned int>(itemPrice));
		memcpy(writePtr, &packedPrice, 4);
		writePtr += 4;
		totalSize += 4;
	}

	char** itemNameTable = Game.m_cFlatDataArr[1].TableStrings(6);
	for (unsigned int i = 0; i < itemCount; i++) {
		memset(itemNameScratch, 0, kGbaQueueScratchTextSize);
		memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

		const int itemId = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel])->m_shopList[i];
		strcpy(itemNameScratch, itemNameTable[itemId]);
		CMes::MakeAgbString(agbStringScratch, itemNameScratch, 0, 0);

		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(writePtr, agbStringScratch, strSize);
		writePtr += strSize;
		totalSize += strSize;
	}

	delete[] agbStringScratch;
	delete[] itemNameScratch;

	OSWaitSemaphore(accessSemaphores + channel);
	m_buyFlg = static_cast<unsigned char>(m_buyFlg | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
	return totalSize;
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
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0xDD7);
		}
		return -1;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0xDDE) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if ((unsigned int)System.m_execParam >= 1) {
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0xDE0);
		}
		return -1;
	}
	memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

	unsigned int* foodBasePtr = &Game.m_scriptFoodBase[channel];
	int totalSize = 0;

	for (int i = 0; i < 0x40; i++) {
		const int itemId = reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_inventoryItems[i];
		unsigned short sellInfo[4];
		if ((itemId < 1) || (itemId > 0x9E)) {
			memset(sellInfo, 0, sizeof(sellInfo));
		} else {
			const int itemBase = Game.unkCFlatData0[2] + itemId * 0x48;
			sellInfo[0] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 4), 0);
			sellInfo[1] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 6), 0);
			sellInfo[2] = __lhbrx(reinterpret_cast<unsigned short*>(itemBase + 8), 0);
			sellInfo[3] = 0;
		}
		memcpy(outData, sellInfo, 8);
		outData += 8;
		totalSize += 8;
	}

	const float userRate = static_cast<float>(static_cast<double>(reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_shopParam) / 100.0) * kGbaQueueQuarter;
	for (int i = 0; i < 0x40; i++) {
		const int itemId = reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_inventoryItems[i];
		unsigned int packedPrice;
		if (itemId > 0) {
			int itemPrice = static_cast<unsigned short>(
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20));
			itemPrice = static_cast<int>(static_cast<float>(itemPrice) * userRate);
			if (itemPrice < 1) {
				itemPrice = 1;
			}
			packedPrice = SwapU32(static_cast<unsigned int>(itemPrice));
		} else {
			packedPrice = 0;
		}

		memcpy(outData, &packedPrice, 4);
		outData += 4;
		totalSize += 4;
	}

	char** itemNameTable = Game.m_cFlatDataArr[1].TableStrings(6);
	for (int i = 0; i < 0x40; i++) {
		memset(itemNameScratch, 0, kGbaQueueScratchTextSize);
		memset(agbStringScratch, 0, kGbaQueueScratchTextSize);

		const int itemId = reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_inventoryItems[i];
		if (itemId < 1) {
			outData[0] = 0;
			outData += 1;
			totalSize += 1;
			continue;
		}

		strcpy(itemNameScratch, itemNameTable[itemId]);
		CMes::MakeAgbString(agbStringScratch, itemNameScratch, 0, 0);
		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(outData, agbStringScratch, strSize);
		outData += strSize;
		totalSize += strSize;
	}

	delete[] agbStringScratch;
	delete[] itemNameScratch;

	OSWaitSemaphore(accessSemaphores + channel);
	m_sellFlg = static_cast<unsigned char>(m_sellFlg | (1 << channel));
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
System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp), 0xE43);
		}
		return -1;
	}
	memset(smithIndices, 0xFF, 0x40);

	unsigned int* foodBasePtr = &Game.m_scriptFoodBase[channel];

	char smithCount = 0;
	for (int i = 0; i < 0x40; i++) {
		if (reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_inventoryItems[i] >= 401) {
			smithIndices[smithCount++] = static_cast<unsigned char>(i);
		}
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
		const int itemId = reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_inventoryItems[i];
		if (itemId >= 401) {
			unsigned int itemBuf[0xE];
			memset(itemBuf, 0, sizeof(itemBuf));

			const int itemOffset = itemId * 0x48;
			unsigned short* itemBase = reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemOffset);
			int price = static_cast<int>(
				static_cast<float>(static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(reinterpret_cast<int>(itemBase) + 0x24))) *
				static_cast<float>(static_cast<double>(reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_shopParam) / 100.0));

			itemBuf[0] = SwapU32(static_cast<unsigned int>(price));

			for (int k = 3; k < 9; k++) {
				reinterpret_cast<unsigned short*>(itemBuf)[k - 1] = __lhbrx(itemBase, k * 2 + 0x20);
			}

			for (int j = 0; j < 2; j++) {
				const int recipeBase = Game.unkCFlatData0[2] + itemOffset + j * 4;

				reinterpret_cast<unsigned short*>(itemBuf)[8 + j * 2] = __lhbrx(reinterpret_cast<unsigned short*>(recipeBase + 0x38), 0);
				const int materialA = *reinterpret_cast<unsigned short*>(recipeBase + 0x38);
				if (materialA == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 8] = 0;
				} else {
					const int materialBase = Game.unkCFlatData0[2] + materialA * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 4), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 6), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 8), 0);
				}

				reinterpret_cast<unsigned short*>(itemBuf)[9 + j * 2] = __lhbrx(reinterpret_cast<unsigned short*>(recipeBase + 0x3A), 0);
				const int materialB = *reinterpret_cast<unsigned short*>(recipeBase + 0x3A);
				if (materialB == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 8] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 8] = 0;
				} else {
					const int materialBase = Game.unkCFlatData0[2] + materialB * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 4), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 6), 0);
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 8] = __lhbrx(reinterpret_cast<unsigned short*>(materialBase + 8), 0);
				}
			}

			memcpy(writePtr, itemBuf, 0x38);
			writePtr += 0x38;
			totalSize += 0x38;
		}
	}

	for (int i = 0; i < 4; i++) {
		unsigned int value = __lwbrx(reinterpret_cast<unsigned int*>(&reinterpret_cast<CCaravanWork*>(*foodBasePtr)->m_shopArgs[i]), 0);
		memcpy(writePtr, &value, 4);
		writePtr += 4;
		totalSize += 4;
	}

	delete[] smithIndices;

	OSWaitSemaphore(accessSemaphores + channel);
	m_mkSmithFlg = static_cast<unsigned char>(m_mkSmithFlg | (1 << channel));
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
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_sellFlg)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_sellFlg = static_cast<unsigned char>(m_sellFlg & ~(1 << channel));
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
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_buyFlg)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_buyFlg = static_cast<unsigned char>(m_buyFlg & ~(1 << channel));
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
	unsigned int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_mkSmithFlg)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_mkSmithFlg = static_cast<unsigned char>(m_mkSmithFlg & ~(1 << channel));
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
	OSSemaphore* semaphore = accessSemaphores + channel;

	OSWaitSemaphore(semaphore);
	m_resetFlags = static_cast<unsigned char>(m_resetFlags | (1 << channel));
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
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_artifactFlags)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_artifactFlags = static_cast<unsigned char>(m_artifactFlags & ~(1U << channel));
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
	localPlayerData = m_playerData[channel];
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
	int value;
	unsigned int result;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_chgUseItemFlags)) & (1 << channel);
	result = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	result = static_cast<unsigned int>(-result | result) >> 31;
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgUseItemFlg(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
	m_chgUseItemFlags = static_cast<unsigned char>(m_chgUseItemFlags & ~(1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetChgUseItemFlg(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
	m_chgUseItemFlags = static_cast<unsigned char>(m_chgUseItemFlags | (1U << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetStrengthFlg(int channel)
{
	int value;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_strengthFlags)) & (1 << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	m_strengthFlags = static_cast<unsigned char>(m_strengthFlags & ~(1U << channel));
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
	int value;
	unsigned int result;

	OSWaitSemaphore(accessSemaphores + channel);
	value = static_cast<int>(static_cast<char>(m_artiDatFlags)) & (1 << channel);
	result = static_cast<unsigned int>(-value | value) >> 31;
	OSSignalSemaphore(accessSemaphores + channel);
	result = static_cast<unsigned int>(-result | result) >> 31;
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrArtiDatFlg(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
	m_artiDatFlags = static_cast<unsigned char>(m_artiDatFlags & ~(1U << channel));
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
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp),
			              0x1011);
		}
		return -1;
	}
	memset(itemNameScratch, 0, kGbaQueueScratchTextSize);

	char* agbStringScratch = new (GbaPcs.m_stage, const_cast<char*>(s_gbaque_cpp), 0x1017) char[kGbaQueueScratchTextSize];
	if (agbStringScratch == 0) {
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(sGbaQueueMemoryAllocationErrorFmt), const_cast<char*>(s_gbaque_cpp),
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

	m_artiDatFlags = static_cast<unsigned char>(m_artiDatFlags | (1 << channel));
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
	localPlayerData = m_playerData[channel];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	int radarType;

	OSWaitSemaphore(semaphore);
	radarType = m_radarType[channel];
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
	m_radarTypeFlags = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetRadarMode(int channel)
{
	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = m_radarMode;
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
	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = m_radarMode;
	int mask = 1 << channel;
	int newRadarMode = radarMode & ~mask;
	newRadarMode |= (mode & 1) << channel;
	m_radarMode = static_cast<unsigned char>(newRadarMode);
	if (radarMode != m_radarMode) {
		m_chgRadarMode = static_cast<unsigned char>(m_chgRadarMode | mask);
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
	OSWaitSemaphore(accessSemaphores + channel);
	int radarMode = m_chgRadarMode;
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
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned char radarMode = m_chgRadarMode;
	m_chgRadarMode = static_cast<char>(radarMode & ~(1U << channel));
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
	unsigned int* enemyWorkPtrs = &Game.m_scriptWork[4][0][0];

	memset(localScouterInfo, 0xFF, sizeof(localScouterInfo));

	OSWaitSemaphore(accessSemaphores + channel);
	{
		unsigned char* scouterEntry = localScouterInfo;
		unsigned char* enemyEntry = reinterpret_cast<unsigned char*>(this);

		for (int i = 0; i < 0x40; i++) {
			scouterEntry[0] = enemyEntry[0xB37];
			if (scouterEntry[0] != 0) {
				CMonWork* enemyWork = reinterpret_cast<CMonWork*>(enemyWorkPtrs[i]);
				const int enemyDataBase = Game.unkCFlatData0[1] + static_cast<unsigned char>(enemyEntry[0xB37]) * 0x1D0;

				*reinterpret_cast<unsigned short*>(scouterEntry + 4) = SwapU16(enemyWork->m_maxHp);

				if (*reinterpret_cast<short*>(enemyEntry + 0xB42) > 0) {
					scouterEntry[6] = 0xFF;
					scouterEntry[7] = 0xFF;
				} else {
					const short scouterValue = *reinterpret_cast<short*>(enemyEntry + 0xB40);
					if ((scouterValue < 1) || ((scouterValue & 0xC000) == 0x4000)) {
						*reinterpret_cast<unsigned short*>(scouterEntry + 6) = 0;
					} else {
						*reinterpret_cast<unsigned short*>(scouterEntry + 6) = SwapU16(static_cast<unsigned short>(scouterValue));
					}
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
	char* obj = reinterpret_cast<char*>(this);
	signed char singleModeByte = m_singleMode;
	int singleMode = singleModeByte;
	unsigned int actualChannel = static_cast<unsigned int>(channel) &
	                             ~static_cast<unsigned int>((-singleMode | singleMode) >> 31);
	OSSemaphore* semaphore = accessSemaphores + actualChannel;
	OSWaitSemaphore(semaphore);
	int flag = obj[0x2D54];
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
	OSWaitSemaphore(semaphore);
	m_chgHitFlags = static_cast<unsigned char>(m_chgHitFlags & ~(1U << actualChannel));
	OSSignalSemaphore(semaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetChgScouFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int flag = obj[0x2D55];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_chgScouFlags = static_cast<unsigned char>(m_chgScouFlags & ~(1U << channel));
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
		enemyType = static_cast<short>(*reinterpret_cast<unsigned short*>(Game.m_scriptWork[4][0][enemyIdx] + 0x1C));
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
	int retries;
	int ret;

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	m_controllerMode = static_cast<char>(controllerMode & 1);

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
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
	char mode;
	unsigned int result;
	int i;

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	mode = m_controllerMode;
	result = static_cast<unsigned int>(-static_cast<int>(mode) | static_cast<int>(mode)) >> 31;

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

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

		m_controllerMode = 1;

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

	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	char menuStageMode = m_singleMode;
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
	menuStageMode = m_singleMode;
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
	char mode;
	unsigned int result;
	int i;

	i = 0;
	do {
		OSWaitSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

	mode = m_pauseMode;
	result = static_cast<unsigned int>(-static_cast<int>(mode) | static_cast<int>(mode)) >> 31;

	i = 0;
	do {
		OSSignalSemaphore(&accessSemaphores[i]);
		i++;
	} while (i < 4);

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
	OSSemaphore* semaphore = accessSemaphores + channel;
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D5D];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_spModeFlags = static_cast<unsigned char>(m_spModeFlags & ~(1 << channel));
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D5C];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D5E];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_memorysFlags = static_cast<unsigned char>(m_memorysFlags & ~(1 << channel));
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
	OSSemaphore* semaphore = accessSemaphores + channel;
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D5F];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_cmdNumFlags = static_cast<unsigned char>(m_cmdNumFlags & ~(3 << (channel << 1)));
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
	OSSemaphore* semaphore = accessSemaphores + channel;
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D60];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_playModeFlags = static_cast<unsigned char>(m_playModeFlags & ~(1 << channel));
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
	OSSemaphore* semaphoreIter = accessSemaphores;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter);
		semaphoreIter++;
	}

	m_startBonusFlags = 0xF;

	semaphoreIter = accessSemaphores;
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	int value = obj[0x2D61];
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
	OSSemaphore* semaphore = accessSemaphores + channel;
	OSWaitSemaphore(semaphore);
	m_startBonusFlags = static_cast<unsigned char>(m_startBonusFlags & ~(1 << channel));
	OSSignalSemaphore(semaphore);
}
