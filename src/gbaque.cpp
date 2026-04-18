#include "ffcc/gbaque.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/mes.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include <string.h>
#include <Dolphin/os.h>
#include <Runtime.PPCEABI.H/NMWException.h>

GbaQueue GbaQue;

extern "C" int rand(void);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void Printf__7CSystemFPce(CSystem*, char*, ...);
extern "C" int memcmp(const void*, const void*, unsigned long);
extern "C" void MakeAgbString__4CMesFPcPcii(char*, char*, int, int);
extern "C" int AddItem__12CCaravanWorkFiPi(void*, int, int*);
extern "C" int AddGil__12CCaravanWorkFi(void*, int);
extern "C" int IsOutOfShouki__12CCaravanWorkFv(void*);
extern "C" int CanPlayerUseItem__12CCaravanWorkFv(void*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);
extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetItemIcon__8CMenuPcsFi(CMenuPcs*, int);

extern CMenuPcs MenuPcs;

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

static inline GbaQueueFlagView* GetFlagView(GbaQueue* gbaQueue)
{
	return reinterpret_cast<GbaQueueFlagView*>(gbaQueue);
}

static inline unsigned short SwapU16(unsigned short value)
{
	return static_cast<unsigned short>((value << 8) | (value >> 8));
}

static inline unsigned int SwapU32(unsigned int value)
{
	return (value << 24) | ((value >> 8 & 0xFF) << 16) | ((value >> 16 & 0xFF) << 8) | (value >> 24);
}

static const char s_gbaque_cpp[] = "gbaque.cpp";
static const char s_mem_alloc_error[] = "%s[%d] Error! memory allocation.\n";
static const char s_npc_max_over[] = "%s[%d] Error! NPC max over.\n";
static const char s_subject_max_over[] = "%s[%d] Error! Subject max over.\n";
static const char s_letter_data_error[] = "%s[%d] Error! Letter data error.\n";
static const char s_cmake_name_crc_error[] = "%s[%d] Error! ChkCMakeName() crc.\n";
static const char s_cmake_favorite_crc_error[] = "%s[%d] Error! CMakeFavorite() crc.\n";
static const char s_unknown_mapobj_type_error[] = "Error! Unknown mapobj type = %d.\n";
extern float FLOAT_80330D54;

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

	memset(obj + 0x30, 0, 0x400);
	memset(obj + 0x430, 0, 0x10);
	memset(obj + 0x440, 0, 4);
	memset(obj + 0x454, 0, 0x370);
	memset(obj + 0x7C4, 0, 0x370);
	memset(obj + 0xB34, 0, 0x500);
	memset(obj + 0x1034, 0, 0x1400);
	memset(obj + 0x2434, 0, 0x140);
	memset(obj + 0x2574, 0, 0x500);
	memset(obj + 0x2A74, 0, 0x80);
	memset(obj + 0x2B00, 0, 0x188);
	memset(obj + 0x2C8E, 0, 8);
	memset(obj + 0x2CB2, 0, 0x80);
	memset(obj + 0x2D44, 0xFF, 0x10);

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
	obj[0x2D56] = 0;
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
	prevMenuStageMode = static_cast<unsigned char>(obj[0x2D56]);
	obj[0x2D56] = static_cast<unsigned char>(Game.m_gameWork.m_menuStageMode != 0);
	if (prevMenuStageMode != static_cast<unsigned char>(obj[0x2D56])) {
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
	// TODO
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
	int ret;
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;

	OSWaitSemaphore(accessSemaphores + channel);
	if (compatibilityStr[channel - 0x18] == 0) {
		if (*(int*)(compatibilityStr + channel * 4 - 0x28) < 0x40) {
			ret = 0;
			*(unsigned int*)(reinterpret_cast<char*>(accessSemaphores) + *(int*)(compatibilityStr + channel * 4 - 0x28) * 4 + channel * 0x100 + 0x30) = value;
			*(int*)(compatibilityStr + channel * 4 - 0x28) = *(int*)(compatibilityStr + channel * 4 - 0x28) + 1;
		} else {
			ret = -1;
			compatibilityStr[channel - 0x18] = 1;
		}
	} else {
		ret = -1;
	}
	OSSignalSemaphore(accessSemaphores + channel);
	return ret;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ResetQueue()
{
	// TODO
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
	char* obj;
	int scriptFoodBase[4];
	unsigned int channel;

	for (channel = 0; channel < 4; channel++) {
		OSWaitSemaphore(accessSemaphores + channel);
	}

	memcpy(localQueueData, reinterpret_cast<char*>(this) + 0x30, sizeof(localQueueData));
	memcpy(localQueueCount, reinterpret_cast<char*>(this) + 0x430, sizeof(localQueueCount));
	memset(reinterpret_cast<char*>(this) + 0x30, 0, sizeof(localQueueData));
	memset(reinterpret_cast<char*>(this) + 0x430, 0, sizeof(localQueueCount));

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

		if (obj[0x430 + channel] != 0) {
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
					caravanWork->ChgCmdLst(static_cast<unsigned char>(cmdWord >> 16), static_cast<short>(cmdWord));
				}
			} else if (cmd == 0x0C) {
				const unsigned char request = static_cast<unsigned char>(cmdWord >> 8);
				if (caravanWork != 0) {
					if ((request == 2) || (request == 3) || (request == 6) || (request == 7) || (request == 8) || (request == 9)) {
						OSWaitSemaphore(accessSemaphores + channel);
						obj[0x2CCA] = static_cast<char>(obj[0x2CCA] & ~static_cast<unsigned char>(playerBit));
						OSSignalSemaphore(accessSemaphores + channel);
						Joybus.SetLetterSize(channel, 0);

						char* letterBuf = Joybus.GetLetterBuffer(channel);
						if (request == 3) {
							MakeLetterList(channel, letterBuf);
						} else if (request == 2) {
							caravanWork->FGLetterOpen(static_cast<unsigned char>(cmdWord));
							MakeLetterData(channel, letterBuf, static_cast<unsigned char>(cmdWord));
						} else if (request == 6) {
							MakeSellData(channel, letterBuf);
						} else if (request == 7) {
							MakeBuyData(channel, letterBuf);
						} else if (request == 8) {
							MakeSmithData(channel, letterBuf);
						} else if (request == 9) {
							MakeArtiData(channel, letterBuf);
						}
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
						caravanWork->DeleteItemIdx(itemIdx, 1);
						Joybus.SendResult(channel, 0, static_cast<unsigned char>(cmdWord >> 24), static_cast<unsigned char>(cmdWord >> 16));
					}
				} else if (request == 9) {
					if (caravanWork != 0) {
						const unsigned int quantity = static_cast<unsigned char>(cmdWord);
						const int shopIndex = static_cast<unsigned char>(cmdWord >> 8);
						int shopItem = caravanWork->m_shopList[shopIndex];
						for (unsigned int n = 0; n < quantity; n++) {
							caravanWork->AddItem(shopItem, 0);
						}
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
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[channel]);
	const unsigned int itemSlot = (value >> 8) & 0xFF;
	const unsigned short baseItem = caravanWork->m_inventoryItems[itemSlot];

	caravanWork->DeleteItemIdx(itemSlot, 1);

	const unsigned int itemTableBase = Game.unkCFlatData0[2] + static_cast<int>(baseItem) * 0x48;
	const unsigned short smithItem = *reinterpret_cast<unsigned short*>(itemTableBase + (value & 0xFF) * 2 + 0x38);

	for (int i = 0; i < 3; i++) {
		const unsigned short materialId = *reinterpret_cast<unsigned short*>(itemTableBase + i * 2 + 0x26);
		if (materialId == 0) {
			break;
		}

		const unsigned short materialCount = *reinterpret_cast<unsigned short*>(itemTableBase + i * 2 + 0x2C);
		if (materialCount == 0) {
			break;
		}

		for (int materialIdx = 0; materialIdx < materialCount; materialIdx++) {
			int foundSlot = 0;
			int rowBase = 0;
			int row = 0;
			int remainingRows = 8;

			do {
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 0]) == static_cast<int>(materialId)) {
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 1]) == static_cast<int>(materialId)) {
					foundSlot += 1;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 2]) == static_cast<int>(materialId)) {
					foundSlot += 2;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 3]) == static_cast<int>(materialId)) {
					foundSlot += 3;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 4]) == static_cast<int>(materialId)) {
					foundSlot += 4;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 5]) == static_cast<int>(materialId)) {
					foundSlot += 5;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 6]) == static_cast<int>(materialId)) {
					foundSlot += 6;
					break;
				}
				if (static_cast<int>(caravanWork->m_inventoryItems[rowBase + 7]) == static_cast<int>(materialId)) {
					foundSlot += 7;
					break;
				}

				row++;
				rowBase += 8;
				foundSlot = row * 8;
				remainingRows--;
			} while (remainingRows != 0);

			caravanWork->DeleteItemIdx(foundSlot, 1);
		}
	}

	if (AddItem__12CCaravanWorkFiPi(reinterpret_cast<void*>(caravanWork), smithItem, 0) != 0) {
		Joybus.SendResult(channel, 1, static_cast<unsigned char>(value >> 24), static_cast<unsigned char>(value >> 16));
	}

	const float smithRate = static_cast<float>(caravanWork->m_shopParam) / 100.0f;
	const int gilCost = -static_cast<int>(static_cast<float>(*reinterpret_cast<unsigned short*>(itemTableBase + 0x24)) * smithRate);
	if (AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravanWork), gilCost) != 0) {
		Joybus.SendResult(channel, 1, static_cast<unsigned char>(value >> 24), static_cast<unsigned char>(value >> 16));
	}

	Joybus.SendResult(channel, 0, static_cast<unsigned char>(value >> 24), static_cast<unsigned char>(value >> 16));
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
    int i = 0;
    GbaQueue* semaphoreIter = this;
    char* obj = reinterpret_cast<char*>(this);

    do {
        OSWaitSemaphore(semaphoreIter->accessSemaphores);
        i++;
        semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
    } while (i < 4);

    obj[0x2D38] = 0;
    obj[0x2D39] = 0;
    obj[0x2C89] = 0;
    obj[0x2C88] = 0;
    obj[0x2C8A] = 0;
    memset(obj + 0x2B00, 0, 0x188);

    if ((*reinterpret_cast<int*>(obj + 0x444) != stageId) || (*reinterpret_cast<int*>(obj + 0x448) != mapId)) {
        *reinterpret_cast<int*>(obj + 0x44C) = 0xF;
        obj[0x2C89] = 0xF;
    }

    *reinterpret_cast<int*>(obj + 0x444) = stageId;
    *reinterpret_cast<int*>(obj + 0x448) = mapId;
    obj[0x2C8B] = 0xF;

    i = 0;
    semaphoreIter = this;
    do {
        OSSignalSemaphore(semaphoreIter->accessSemaphores);
        i++;
        semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
    } while (i < 4);

    if (Joybus.LoadMap(stageId, mapId) == 0) {
        i = 0;
        semaphoreIter = this;
        do {
            OSWaitSemaphore(semaphoreIter->accessSemaphores);
            i++;
            semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
        } while (i < 4);

        *reinterpret_cast<int*>(obj + 0x44C) = 0xF;
        obj[0x2C89] = 0xF;

        i = 0;
        semaphoreIter = this;
        do {
            OSSignalSemaphore(semaphoreIter->accessSemaphores);
            i++;
            semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
        } while (i < 4);
    }

    memset(obj + 0x2D40, 0xFF, 0x10);
    obj[0x2C8A] = 0;
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
	unsigned int flag;
	char stageFlg;

	OSWaitSemaphore(accessSemaphores + channel);
	stageFlg = *(reinterpret_cast<char*>(this) + 0x44C);
	flag = static_cast<unsigned int>(stageFlg) & static_cast<unsigned int>(1 << channel);
	OSSignalSemaphore(accessSemaphores + channel);

	return static_cast<unsigned int>((-static_cast<int>(flag) | static_cast<int>(flag)) >> 31);
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
	unsigned char bitMask;
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	bitMask = static_cast<unsigned char>(1 << channel);
	obj[0x44C] = static_cast<char>(obj[0x44C] & ~bitMask);
	obj[0x2C89] = static_cast<char>(obj[0x2C89] | bitMask);
	OSSignalSemaphore(accessSemaphores + channel);
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

	if (obj[0x2D56] != 0) {
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
	signed char connectedFlag = obj[0x2D56];

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
	// TODO
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
	unsigned char localNames[0x80];
	unsigned char localPlayerStat[0x370];
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
			unsigned char menuStageMode = static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D56]);
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

				if ((IsOutOfShouki__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork)) != 0) && (entry[0x17] != 0)) {
					outOfShoukiMask |= (1U << i);
				}

				if (CanPlayerUseItem__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork)) != 0) {
					entry[0xD6] |= 1;
				}
				if (CanPlayerPutItem__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork)) != 0) {
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
	memcpy(obj + 0x7C4, obj + 0x454, 0x370);
	memcpy(obj + 0x454, localPlayerStat, 0x370);
	memcpy(obj + 0x2A74, localNames, 0x80);

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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadEnemyStat()
{
	// TODO
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
	unsigned char localMapItems[0x140];
	char numMapItems;
	CGObject* object;
	GbaQueue* semaphoreIter;
	int i;

	memset(localMapItems, 0, sizeof(localMapItems));
	numMapItems = 0;

	if (reinterpret_cast<unsigned int*>(&CFlat)[0x1041] != 0) {
		unsigned char* mapItemEntry = localMapItems;
		object = FindGObjFirst__13CFlatRuntime2Fv(&CFlat);

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

				typedef int (*IsDispRadarFn)(CGObject*);
				int isDispRader = reinterpret_cast<IsDispRadarFn>((*reinterpret_cast<void***>(object))[0xB])(object);
				numMapItems++;
				mapItemEntry[2] = static_cast<unsigned char>((-isDispRader | isDispRader) >> 31);
				*reinterpret_cast<short*>(mapItemEntry + 8) = static_cast<short>(object->m_worldPosition.x / 100.0f);
				*reinterpret_cast<short*>(mapItemEntry + 0xA) = static_cast<short>(object->m_worldPosition.z / 100.0f);
				mapItemEntry += 0x14;
			}

			object = FindGObjNext__13CFlatRuntime2FP8CGObject(&CFlat, object);
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
	unsigned char localPlayerData[0x370];
	unsigned char packet[0xC];
	short xPos[4];
	short zPos[4];
	int i;
	short baseX;
	short baseZ;
	unsigned char nearbyMask;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + 0x454, sizeof(localPlayerData));
	OSSignalSemaphore(accessSemaphores + channel);

	memset(packet, 0, sizeof(packet));

	if (reinterpret_cast<unsigned char*>(this)[0x2D56] != 0) {
		channel = 0;
	}

	packet[0] = 0x11;
	packet[4] = 0x51;
	packet[8] = 0x91;

	baseX = *reinterpret_cast<short*>(localPlayerData + (channel * 0xDC) + 0x36);
	baseZ = *reinterpret_cast<short*>(localPlayerData + (channel * 0xDC) + 0x38);

	nearbyMask = 0;
	for (i = 0; i < 4; i++) {
		const unsigned char* player = localPlayerData + (i * 0xDC);
		const short px = *reinterpret_cast<const short*>(player + 0x36);
		const short pz = *reinterpret_cast<const short*>(player + 0x38);

		xPos[i] = px;
		zPos[i] = pz;

		if (i == channel) {
			nearbyMask |= static_cast<unsigned char>(1 << i);
		} else if (player[3] != 0) {
			const int dx = static_cast<int>(px) - static_cast<int>(baseX);
			const int dz = static_cast<int>(pz) - static_cast<int>(baseZ);

			if ((dx > -0x51 && dx < 0x51) && (dz > -0x41 && dz < 0x41)) {
				nearbyMask |= static_cast<unsigned char>(1 << i);
			}
		}
	}

	packet[1] = nearbyMask;
	packet[2] = static_cast<unsigned char>(static_cast<char>(xPos[0]) - static_cast<char>(baseX));
	packet[3] = static_cast<unsigned char>(static_cast<char>(zPos[0]) - static_cast<char>(baseZ));
	packet[5] = static_cast<unsigned char>(static_cast<char>(xPos[1]) - static_cast<char>(baseX));
	packet[6] = static_cast<unsigned char>(static_cast<char>(zPos[1]) - static_cast<char>(baseZ));
	packet[7] = static_cast<unsigned char>(static_cast<char>(xPos[2]) - static_cast<char>(baseX));
	packet[9] = static_cast<unsigned char>(static_cast<char>(zPos[2]) - static_cast<char>(baseZ));
	packet[10] = static_cast<unsigned char>(static_cast<char>(xPos[3]) - static_cast<char>(baseX));
	packet[11] = static_cast<unsigned char>(static_cast<char>(zPos[3]) - static_cast<char>(baseZ));

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
    if (((unsigned int)__cntlzw(1 - static_cast<int>(obj[0x2D56])) >> 5 & 0xFFU) != 0U) {
        channel = 0;
    }
    OSSignalSemaphore(accessSemaphores + channel);

    OSWaitSemaphore(accessSemaphores + channel);

    baseX = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x32);
    baseZ = *reinterpret_cast<short*>(obj + channel * 0xDC + 0x34);
    memcpy(localEnemyData, obj + 0xB34, 0x500);

    radarMode = obj[channel + 0x2D32];
    localEntry = localEnemyData;
    for (i = 0; i < 0x40; i++) {
        int enemyX = *reinterpret_cast<short*>(localEntry + 8) - baseX;
        int enemyZ = *reinterpret_cast<short*>(localEntry + 10) - baseZ;

        *reinterpret_cast<short*>(localEntry + 8) = static_cast<short>(enemyX);
        *reinterpret_cast<short*>(localEntry + 10) = static_cast<short>(enemyZ);

        if ((enemyX < 0 ? -enemyX : enemyX) < 0x50 && (enemyZ < 0 ? -enemyZ : enemyZ) < 0x40) {
            localEntry[0] = 1;
        } else {
            localEntry[8] = -1;
            localEntry[9] = -1;
            localEntry[10] = -1;
            localEntry[11] = -1;
            localEntry[0] = 0;
        }

        if (*reinterpret_cast<short*>(localEntry + 4) == 0 || localEntry[2] == 0) {
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
    prevEntry = obj + channel * 0x500 + 0x1034;
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
    memcpy(obj + channel * 0x500 + 0x1034, localEnemyData, 0x500);
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
	char localMapItems[0x140];
	char* obj;
	char* localEntry;
	char* prevEntry;
	unsigned char* outPtr;
	short baseX;
	short baseZ;
	int count;
	int i;

	obj = reinterpret_cast<char*>(this);

	if (obj[0x2D56] != 0) {
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
	prevEntry = obj + channel * 0x140 + 0x2574;
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
	memcpy(obj + channel * 0x140 + 0x2574, localMapItems, sizeof(localMapItems));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetMapObjInfo(int, unsigned char*)
{
	return 0;
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
	memcpy(outInfo, reinterpret_cast<char*>(this) + 0x454, 0x370);
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

	memcpy(outName, reinterpret_cast<char*>(this) + 0x2A74, 0x80);

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
	unsigned char localPlayerData[0xDC];
	unsigned short itemList[0x40];
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x454, sizeof(localPlayerData));
	OSSignalSemaphore(accessSemaphores + channel);

	for (i = 0; i < 0x40; i++) {
		itemList[i] = SwapU16(*reinterpret_cast<unsigned short*>(localPlayerData + 0x3A + i * 2));
	}
	memcpy(outData, itemList, sizeof(itemList));

	*reinterpret_cast<unsigned int*>(outData + 0x80) = SwapU32(*reinterpret_cast<unsigned int*>(localPlayerData + 0x24));
	*reinterpret_cast<unsigned int*>(outData + 0x84) = SwapU32(*reinterpret_cast<unsigned int*>(localPlayerData + 0x28));
	*reinterpret_cast<unsigned int*>(outData + 0x88) = SwapU32(*reinterpret_cast<unsigned int*>(localPlayerData + 0x2C));

	for (i = 0; i < 4; i++) {
		*reinterpret_cast<unsigned short*>(outData + 0x8C + i * 2) =
			SwapU16(*reinterpret_cast<unsigned short*>(localPlayerData + 0xBA + i * 2));
	}

	outData[0x94] = localPlayerData[0xD7];
	outData[0x95] = localPlayerData[0xD8];
	outData[0x96] = localPlayerData[0xD9];
	outData[0x97] = localPlayerData[0xDA];

	for (i = 0; i < 8; i++) {
		*reinterpret_cast<unsigned short*>(outData + 0x98 + i * 2) =
			SwapU16(*reinterpret_cast<unsigned short*>(localPlayerData + 0xC2 + i * 2));
	}

	outData[0xA8] = localPlayerData[0xD3];
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
	semaphoreIter = reinterpret_cast<OSSemaphore*>(this);
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	flag = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x2AF8);

	i = 0;
	semaphoreIter = reinterpret_cast<OSSemaphore*>(this);
	do {
		OSSignalSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	return (-flag | flag) >> 31;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetPlayerHP(int, unsigned char*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MakeLetterList(int channel, char* outData)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	const unsigned int scriptFood = Game.m_scriptFoodBase[channel];
	const unsigned char channelMask = static_cast<unsigned char>(1U << channel);

	if (scriptFood == 0) {
		self[0x2C8A] = static_cast<unsigned char>(self[0x2C8A] | channelMask);
		Joybus.SetLetterSize(channel, 0);
		self[0x2C89] = static_cast<unsigned char>(self[0x2C89] & ~channelMask);
		return;
	}

char* npcNameBuf = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x800, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0x7A7));
	if (npcNameBuf == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0x7A9);
		}
		return;
	}
	memset(npcNameBuf, 0, 0x800);

char* subjectNameBuf = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x1800, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0x7B1));
	if (subjectNameBuf == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0x7B3);
		}
		__dla__FPv(npcNameBuf);
		return;
	}
	memset(subjectNameBuf, 0, 0x1800);

unsigned int* letterEntryBuf = static_cast<unsigned int*>(__nwa__FUlPQ27CMemory6CStagePci(
0x4000, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0x7BB));
	if (letterEntryBuf == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0x7BD);
		}
		__dla__FPv(subjectNameBuf);
		__dla__FPv(npcNameBuf);
		return;
	}
	memset(letterEntryBuf, 0, 0x800);

	const CCaravanWork* caravanWork = reinterpret_cast<const CCaravanWork*>(scriptFood);
	const unsigned int letterCount = static_cast<unsigned int>(caravanWork->m_letterCount);

	unsigned int subjectCount = 0;
	unsigned int npcCount = 0;

	char* npcWrite = npcNameBuf;
	char* subjectWrite = subjectNameBuf;
	unsigned int* entryWrite = letterEntryBuf;

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
	char** npcTable = flatData->m_tabl[2].m_strings;
	char** subjectTable = flatData->m_tabl[5].m_strings;

	for (int i = 0; i < static_cast<int>(letterCount); i++) {
		int matchedSubject = -1;
		int matchedNpc = -1;

		const unsigned int* cur = reinterpret_cast<const unsigned int*>(scriptFood + 0x3EC + i * 0xC);
		const unsigned int curWord = cur[0];

		for (int j = 0; j < i; j++) {
			const unsigned int* prev = reinterpret_cast<const unsigned int*>(scriptFood + 0x3EC + j * 0xC);
			if (((curWord >> 9) & 0x1FF) == ((prev[0] >> 9) & 0x1FF)) {
				matchedNpc = j;
			}
			if (((curWord >> 2) & 0x1FF) == ((prev[0] >> 2) & 0x1FF)) {
				matchedSubject = j;
			}
			if (matchedSubject != -1 && matchedNpc != -1) {
				break;
			}
		}

		if (matchedNpc == -1) {
			if (npcCount > 0x7F && System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_npc_max_over), const_cast<char*>(s_gbaque_cpp), 0x7DC);
			}

			char tempName[0x20];
			memset(tempName, 0, sizeof(tempName));
			strcpy(tempName, npcTable[(curWord >> 9) & 0x1FF]);
			memcpy(npcWrite, tempName, 0x10);
			npcWrite += 0x10;
			(reinterpret_cast<unsigned char*>(entryWrite))[5] = static_cast<unsigned char>(npcCount);
			npcCount++;
		} else {
			(reinterpret_cast<unsigned char*>(entryWrite))[5] =
				(reinterpret_cast<unsigned char*>(letterEntryBuf + matchedNpc * 2))[5];
		}

		if (matchedSubject == -1) {
			if (subjectCount > 0xFF && System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_subject_max_over), const_cast<char*>(s_gbaque_cpp), 0x7F0);
			}

			char tempSubject[0x20];
			memset(tempSubject, 0, sizeof(tempSubject));
			strcpy(tempSubject, subjectTable[(curWord >> 2) & 0x1FF]);
			memcpy(subjectWrite, tempSubject, 0x18);
			subjectWrite += 0x18;
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

		const unsigned int value = cur[0] >> 16 & 0x1FF;
		if ((curWord & 8) == 0) {
			if (value != 0) {
				if (value < 0x100 || value > 0x124) {
					flags |= 0x10;
					entryWrite[0] = (value << 24) | ((value >> 8) << 16);
				} else if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_letter_data_error), const_cast<char*>(s_gbaque_cpp), 0x810, channel, i);
				}
			}
		} else if (value != 0) {
			flags |= 0x20;
			entryWrite[0] = value * 0x64000000 | ((value * 100 >> 8) << 16);
		}

		(reinterpret_cast<unsigned char*>(entryWrite))[6] = flags;
		entryWrite += 2;
	}

	unsigned int header[4];
	header[0] = (letterCount << 24) | ((letterCount >> 8) & 0xFF) << 16 |
		((letterCount >> 16) & 0xFF) << 8 | (letterCount >> 24);
	header[1] = (subjectCount << 24) | ((subjectCount >> 8) & 0xFF) << 16 |
		((subjectCount >> 16) & 0xFF) << 8 | (subjectCount >> 24);
	header[2] = (npcCount << 24) | ((npcCount >> 8) & 0xFF) << 16 |
		((npcCount >> 16) & 0xFF) << 8 | (npcCount >> 24);
	header[3] = reinterpret_cast<unsigned int*>(&CFlat)[0x1042];

	memcpy(outData, header, 0x10);

	const int entriesSize = static_cast<int>(letterCount * 8);
	memcpy(outData + 0x10, letterEntryBuf, entriesSize);

	char* dst = outData + 0x10 + entriesSize;
	const int subjectSize = static_cast<int>(subjectCount * 0x18);
	memcpy(dst, subjectNameBuf, subjectSize);
	memcpy(dst + subjectSize, npcNameBuf, static_cast<int>(npcCount * 0x10));

	const int totalSize = entriesSize + 0x10 + subjectSize + static_cast<int>(npcCount * 0x10);

	__dla__FPv(letterEntryBuf);
	__dla__FPv(subjectNameBuf);
	__dla__FPv(npcNameBuf);

	self[0x2C8A] = static_cast<unsigned char>(self[0x2C8A] | channelMask);
	Joybus.SetLetterSize(channel, totalSize);
	self[0x2C89] = static_cast<unsigned char>(self[0x2C89] & ~channelMask);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::MakeLetterData(int channel, char* outData, int letterIndex)
{
char* srcText = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0x859));
    if (srcText == 0) {
        if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0x85B);
        }
        return -1;
    }
    memset(srcText, 0, 0x400);

char* workText = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0x862));
    if (workText == 0) {
        if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0x864);
        }
        __dla__FPv(srcText);
        return -1;
    }
    memset(workText, 0, 0x400);

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
    MakeAgbString__4CMesFPcPcii(workText, srcText, *reinterpret_cast<unsigned short*>(scriptFood + 0x3E2), 0);
    int totalSize = static_cast<int>(strlen(workText) + 1);
    memcpy(outData, workText, totalSize);

    memset(srcText, 0, 0x400);
    memset(workText, 0, 0x400);
    strcpy(srcText, mesPtr[mesIndex + 1]);
    MakeAgbString__4CMesFPcPcii(workText, srcText, *reinterpret_cast<unsigned short*>(scriptFood + 0x3E2), 0);
    int line2Size = static_cast<int>(strlen(workText));
    memcpy(outData + totalSize, workText, line2Size + 1);
    totalSize += line2Size + 1;

    __dla__FPv(workText);
    __dla__FPv(srcText);

    reinterpret_cast<unsigned char*>(this)[0x2C89] |= static_cast<unsigned char>(0x10 << channel);
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
	value = static_cast<unsigned int>(flags->m_letterDatFlg) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
	value = static_cast<unsigned int>(flags->m_letterDatFlg) & (0x10U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MoveLetterItem(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ReplyLetter(int)
{
	// TODO
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
			memset(obj + 0x2B00, 0, 0x188);
		}

		i = 0;
		semaphoreIter = this;
		do {
			OSSignalSemaphore(semaphoreIter->accessSemaphores);
			i++;
			semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
		} while (i < 4);
	} else {
		unsigned char mapObjWork[0x188];
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
					*reinterpret_cast<short*>(mapObjWork + 0xC + entryBase) = static_cast<short>((int)(x / FLOAT_80330D54));
					*reinterpret_cast<short*>(mapObjWork + 0xE + entryBase) = static_cast<short>((int)(y / FLOAT_80330D54));
					*reinterpret_cast<short*>(mapObjWork + 0x10 + entryBase) = static_cast<short>((int)(z / FLOAT_80330D54));
					*reinterpret_cast<short*>(mapObjWork + 0x12 + entryBase) = static_cast<short>((int)(r / FLOAT_80330D54));

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
Printf__7CSystemFPce(&System, const_cast<char*>(s_unknown_mapobj_type_error), objType);
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
	unsigned char mapObjWork[0x188];
	unsigned char* workEntry;
	unsigned char* writePtr;
	GbaQueue* semaphoreIter;
	int i;
	int outSize;

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
	outData[0] = mapObjWork[0];
	outData[1] = mapObjWork[4];
	outData[2] = mapObjWork[5];
	outData[3] = mapObjWork[6];
	outData[4] = mapObjWork[7];

	writePtr = outData + 5;
	for (i = 0; i < mapObjWork[0]; i++) {
		writePtr[0] = workEntry[8];
		writePtr[1] = workEntry[0xC];
		writePtr[2] = workEntry[0xD];
		writePtr[3] = workEntry[0xE];
		writePtr[4] = workEntry[0xF];
		writePtr[5] = workEntry[0x10];
		writePtr[6] = workEntry[0x11];
		writePtr[7] = workEntry[0x12];
		writePtr[8] = workEntry[0x13];

		workEntry += 0xC;
		writePtr += 9;
	}

	reinterpret_cast<char*>(this)[0x2C88] = 1;
	outSize = static_cast<int>(writePtr - outData);
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
	OSSignalSemaphore(accessSemaphores + channel);
	return (-mask | mask) >> 31;
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
	OSSignalSemaphore(accessSemaphores + channel);
	return (-mask | mask) >> 31;
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
	char* obj = reinterpret_cast<char*>(this);

	OSWaitSemaphore(accessSemaphores + channel);
	memset(&cmakeInfo[channel], 0, 0x20);
	cmakeInfo[channel][0] = 1;
	obj[channel + 0x2CCA] = static_cast<char>(0xFF);
	obj[channel + 0x2CD1] = static_cast<char>(0xFF);
	obj[channel + 0x2CB8] = static_cast<char>(value);
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
	if (cmakeInfo[param_2 * 0x20] != '\0') {
		memset(&cmakeInfo[param_2 * 0x20], 0, 0x20);
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
	const unsigned char byte0 = static_cast<unsigned char>(value);
	const unsigned char byte1 = static_cast<unsigned char>(value >> 8);
	const unsigned char byte2 = static_cast<unsigned char>(value >> 16);
	const unsigned char cmdType = static_cast<unsigned char>(value >> 24);
	const int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if ((static_cast<int>(value >> 24) >> 6) == 0) {
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = static_cast<char>(cmdType);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 1;
		*reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset) = static_cast<short>(value >> 8);
		memset(obj + 0x2CB9 + cmakeOffset, 0, 0x11);
		obj[0x2CB9 + cmakeOffset] = static_cast<char>(byte0);
		OSSignalSemaphore(semaphore);
		return;
	}

	unsigned char resultCode;
	unsigned char compareSlot;
	short expectedCrc;
	unsigned char nameBuffer[0x11];
	bool hasFullName = false;

	OSWaitSemaphore(semaphore);
	{
		const int writeOffset = static_cast<int>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset)) * 3;
		*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) =
			static_cast<short>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) + 1);
		obj[0x2CB7 + cmakeOffset + writeOffset] = static_cast<char>(byte2);
		obj[0x2CB8 + cmakeOffset + writeOffset] = static_cast<char>(byte1);
		obj[0x2CB9 + cmakeOffset + writeOffset] = static_cast<char>(byte0);

		hasFullName = (*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) > 5);
		resultCode = static_cast<unsigned char>(obj[0x2CB3 + cmakeOffset]);
		expectedCrc = *reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset);
		compareSlot = static_cast<unsigned char>(obj[0x2CB8 + cmakeOffset]);
		memcpy(nameBuffer, obj + 0x2CB9 + cmakeOffset, sizeof(nameBuffer));
	}
	OSSignalSemaphore(semaphore);

	if (!hasFullName) {
		return;
	}

	if (strlen(reinterpret_cast<char*>(obj + 0x2CB9 + cmakeOffset)) == 0) {
		obj[0x2CCA + cmakeOffset] = static_cast<char>(0xFF);
		obj[0x2CD1 + cmakeOffset] = static_cast<char>(0xFF);
		return;
	}

	unsigned short crc = 0xFFFF;
	if (Joybus.Crc16(0x10, nameBuffer, &crc) == expectedCrc) {
		for (int i = 0; i < 4; i++) {
			OSWaitSemaphore(accessSemaphores + i);
		}

		for (int i = 0; i < 4; i++) {
			const int otherOffset = i * 0x20;
			if ((channel != i) && (cmakeInfo[i][0] != '\0') &&
			    (strcmp(obj + 0x2CB9 + otherOffset, reinterpret_cast<char*>(nameBuffer)) == 0)) {
				memset(obj + 0x2CB9 + cmakeOffset, 0, 0x11);
				for (int j = 0; j < 4; j++) {
					OSSignalSemaphore(accessSemaphores + j);
				}
				Joybus.SendResult(channel, 1, resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 4; i++) {
			OSSignalSemaphore(accessSemaphores + i);
		}

		GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.m_cFlatDataArr[1]);
		for (int i = 0; i < 0x100; i++) {
			if (strcmp(flatData->m_tabl[2].m_strings[i], reinterpret_cast<char*>(nameBuffer)) == 0) {
				Joybus.SendResult(channel, 1, resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 8; i++) {
			CCaravanWork* caravanWork = &Game.m_caravanWorkArr[i];
			char* caravanObj = reinterpret_cast<char*>(caravanWork);
			if ((i != compareSlot) && (*reinterpret_cast<int*>(caravanObj + 0x3A4) != 0) &&
			    (caravanObj[0xBA6] == '\0') &&
			    (strcmp(caravanObj + 0x3CA, reinterpret_cast<char*>(nameBuffer)) == 0)) {
				Joybus.SendResult(channel, 1, resultCode, 0);
				return;
			}
		}

		Joybus.SendResult(channel, 0, resultCode, 0);
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + cmakeOffset) = 0;
		OSSignalSemaphore(semaphore);
	} else {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_cmake_name_crc_error), const_cast<char*>(s_gbaque_cpp), 0xAD3);
		}
		Joybus.SendResult(channel, 1, resultCode, 0);
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
		if ((channel != i) && (cmakeInfo[i][0] != '\0') &&
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChkCMakeJob(int, unsigned int)
{
	// TODO
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
	unsigned char byte0 = static_cast<unsigned char>(value);
	unsigned char byte1 = static_cast<unsigned char>(value >> 8);
	unsigned char byte2 = static_cast<unsigned char>(value >> 16);
	unsigned char cmdType = static_cast<unsigned char>(value >> 24);
	int cmakeOffset = channel * 0x20;
	OSSemaphore* semaphore = accessSemaphores + channel;

	if ((static_cast<int>(value >> 24) >> 6) == 0) {
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = static_cast<char>(cmdType);
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 1;
		*reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset) = static_cast<short>(value >> 8);
		memset(obj + 0x2CCD + cmakeOffset, 0, 4);
		obj[0x2CCD + cmakeOffset] = static_cast<char>(byte0);
		OSSignalSemaphore(semaphore);
		return;
	}

	unsigned char resultCode = 0;
	short expectedCrc = 0;
	unsigned char crcData[4];
	bool hasData = false;

	OSWaitSemaphore(semaphore);
	{
		int writeOffset = static_cast<int>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset)) * 3;
		*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) =
			static_cast<short>(*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) + 1);
		obj[0x2CCB + cmakeOffset + writeOffset] = static_cast<char>(byte2);
		obj[0x2CCC + cmakeOffset + writeOffset] = static_cast<char>(byte1);
		obj[0x2CCD + cmakeOffset + writeOffset] = static_cast<char>(byte0);

		if (*reinterpret_cast<short*>(obj + 0x2CB4 + cmakeOffset) > 1) {
			resultCode = static_cast<unsigned char>(obj[0x2CB3 + cmakeOffset]);
			expectedCrc = *reinterpret_cast<short*>(obj + 0x2CB6 + cmakeOffset);
			memcpy(crcData, obj + 0x2CCD + cmakeOffset, sizeof(crcData));
			hasData = true;
		}
	}
	OSSignalSemaphore(semaphore);

	if (!hasData) {
		return;
	}

	unsigned short crc = 0xFFFF;
	if (Joybus.Crc16(4, crcData, &crc) == expectedCrc) {
		Joybus.SendResult(channel, 0, resultCode, 0);
		OSWaitSemaphore(semaphore);
		obj[0x2CB3 + cmakeOffset] = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB4 + cmakeOffset) = 0;
		*reinterpret_cast<unsigned short*>(obj + 0x2CB6 + cmakeOffset) = 0;
		OSSignalSemaphore(semaphore);
	} else {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_cmake_favorite_crc_error), const_cast<char*>(s_gbaque_cpp), 0xBDC);
		}
		Joybus.SendResult(channel, 1, resultCode, 0);
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
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>((-value | value) >> 31);
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
int GbaQueue::GetCompatibility(int, unsigned char*)
{
	return 0;
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
	void* src = reinterpret_cast<char*>(this) + channel * 0x20 + 0x2CB2;

	OSWaitSemaphore(sem);
	memcpy(outInfo, src, 0x20);
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
void GbaQueue::GetCmdData(int channel, unsigned char* outData)
{
	unsigned char localPlayerData[0xDC];
	unsigned char count;
	unsigned char* writePtr;
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x454, sizeof(localPlayerData));
	OSSignalSemaphore(accessSemaphores + channel);

	count = 0;
	writePtr = outData + 4;

	outData[0] = 0;
	outData[1] = 0;
	outData[2] = 0;
	outData[3] = 0;

	for (i = 0; i < 0x40; i++) {
		int itemId = *reinterpret_cast<short*>(localPlayerData + 0x3A + i * 2);
		if ((GetItemType__8CMenuPcsFii(&MenuPcs, itemId, 1) == 1) &&
		    (GetItemIcon__8CMenuPcsFi(&MenuPcs, itemId) == (localPlayerData[0xDA] & 3))) {
			int itemBase = Game.unkCFlatData0[2] + itemId * 0x48;

			*reinterpret_cast<unsigned short*>(writePtr + 0) =
				SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 4));
			*reinterpret_cast<unsigned short*>(writePtr + 2) =
				SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 6));
			*reinterpret_cast<unsigned short*>(writePtr + 4) =
				SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 8));
			*reinterpret_cast<unsigned short*>(writePtr + 6) = 0;

			writePtr += 8;
			count++;
		}
	}

	outData[0] = count;
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
	unsigned char equipCount;
	unsigned char* writePtr;
	int i;

	OSWaitSemaphore(accessSemaphores + channel);
	memcpy(localPlayerData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x454, sizeof(localPlayerData));
	memcpy(outData, reinterpret_cast<unsigned char*>(this) + channel * 0xDC + 0x52B, 4);
	OSSignalSemaphore(accessSemaphores + channel);

	memset(equipIndices, 0xFF, sizeof(equipIndices));
	equipCount = 0;
	for (i = 0; i < 0x40; i++) {
		int itemId = *reinterpret_cast<short*>(localPlayerData + 0x3A + i * 2);
		if (itemId >= 0 && itemId < 0x9F) {
			equipIndices[equipCount] = static_cast<unsigned char>(i);
			equipCount++;
		}
	}

	indexBytes = static_cast<unsigned int>(equipCount) + 1;
	if ((indexBytes & 3) != 0) {
		indexBytes = (((indexBytes >> 2) + 1) * 4);
	}

	outData[4] = equipCount;
	memcpy(outData + 5, equipIndices, indexBytes - 1);

	writePtr = outData + 4 + indexBytes;
	for (i = 0; i < equipCount; i++) {
		int itemId = *reinterpret_cast<short*>(localPlayerData + 0x3A + equipIndices[i] * 2);
		int itemBase = Game.unkCFlatData0[2] + itemId * 0x48;

		*reinterpret_cast<unsigned short*>(writePtr + 0) =
			SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 4));
		*reinterpret_cast<unsigned short*>(writePtr + 2) =
			SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 6));
		*reinterpret_cast<unsigned short*>(writePtr + 4) =
			SwapU16(*reinterpret_cast<unsigned short*>(itemBase + 8));
		*reinterpret_cast<unsigned short*>(writePtr + 6) = 0;
		writePtr += 8;
	}

	return static_cast<int>((writePtr - outData));
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
	u8 mask = static_cast<u8>(1 << channel);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(reinterpret_cast<char*>(this) + channel * 0xC + 0x80);
	u8* flags = reinterpret_cast<u8*>(this) + 0x2D38;

	OSWaitSemaphore(semaphore);
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
void GbaQueue::ClrShopFlg(int)
{
	// TODO
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
	u8 mask = static_cast<u8>(0x10 << channel);
	OSSemaphore* semaphore = reinterpret_cast<OSSemaphore*>(reinterpret_cast<char*>(this) + channel * 0xC + 0x80);
	u8* flags = reinterpret_cast<u8*>(this) + 0x2D38;

	OSWaitSemaphore(semaphore);
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
void GbaQueue::ClrSmithFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ShopEnd(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SmithEnd(int)
{
	// TODO
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
char* itemNameScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0xD79));
	if (itemNameScratch == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0xD7B);
		}
		return;
	}
	memset(itemNameScratch, 0, 0x400);

char* agbStringScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0xD82));
	if (agbStringScratch == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0xD84);
		}
		__dla__FPv(itemNameScratch);
		return;
	}
	memset(agbStringScratch, 0, 0x400);

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
		memset(itemNameScratch, 0, 0x400);
		memset(agbStringScratch, 0, 0x400);

		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xBE6);
		strcpy(itemNameScratch, flatData->m_tabl[6].m_strings[itemId]);
		MakeAgbString__4CMesFPcPcii(agbStringScratch, itemNameScratch, 0, 0);

		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(writePtr, agbStringScratch, strSize);
		writePtr += strSize;
		totalSize += strSize;
	}

	__dla__FPv(agbStringScratch);
	__dla__FPv(itemNameScratch);

	OSWaitSemaphore(accessSemaphores + channel);
	reinterpret_cast<unsigned char*>(this)[0x2D55] =
		static_cast<unsigned char>(reinterpret_cast<unsigned char*>(this)[0x2D55] | (1 << channel));
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
void GbaQueue::MakeSellData(int channel, char* outData)
{
char* itemNameScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0xDD5));
	if (itemNameScratch == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0xDD7);
		}
		return;
	}
	memset(itemNameScratch, 0, 0x400);

char* agbStringScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
0x400, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0xDDE));
	if (agbStringScratch == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0xDE0);
		}
		__dla__FPv(itemNameScratch);
		return;
	}
	memset(agbStringScratch, 0, 0x400);

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
		memset(itemNameScratch, 0, 0x400);
		memset(agbStringScratch, 0, 0x400);

		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xB6);
		if (itemId < 1) {
			outData[0] = 0;
			outData += 1;
			totalSize += 1;
			continue;
		}

		strcpy(itemNameScratch, flatData->m_tabl[6].m_strings[itemId]);
		MakeAgbString__4CMesFPcPcii(agbStringScratch, itemNameScratch, 0, 0);
		const int strSize = static_cast<int>(strlen(agbStringScratch) + 1);
		memcpy(outData, agbStringScratch, strSize);
		outData += strSize;
		totalSize += strSize;
	}

	__dla__FPv(agbStringScratch);
	__dla__FPv(itemNameScratch);

	OSWaitSemaphore(accessSemaphores + channel);
	reinterpret_cast<unsigned char*>(this)[0x2C98] =
		static_cast<unsigned char>(reinterpret_cast<unsigned char*>(this)[0x2C98] | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
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
void GbaQueue::MakeSmithData(int channel, char* outData)
{
	unsigned char* smithIndices = static_cast<unsigned char*>(
__nwa__FUlPQ27CMemory6CStagePci(0x40, Game.m_mainStage, const_cast<char*>(s_gbaque_cpp), 0xE41));
	if (smithIndices == 0) {
		if (System.m_execParam != 0) {
Printf__7CSystemFPce(&System, const_cast<char*>(s_mem_alloc_error), const_cast<char*>(s_gbaque_cpp), 0xE43);
		}
		return;
	}
	memset(smithIndices, 0xFF, 0x40);

	const unsigned int scriptFood = Game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.unkCFlatData0[2];

	unsigned char smithCount = 0;
	unsigned char baseIndex = 0;
	for (int i = 0; i < 0x10; i++) {
		if (*reinterpret_cast<short*>(scriptFood + i * 8 + 0xB6) > 400) {
			smithIndices[smithCount++] = baseIndex;
		}
		if (*reinterpret_cast<short*>(scriptFood + i * 8 + 0xB8) > 400) {
			smithIndices[smithCount++] = baseIndex + 1;
		}
		if (*reinterpret_cast<short*>(scriptFood + i * 8 + 0xBA) > 400) {
			smithIndices[smithCount++] = baseIndex + 2;
		}
		if (*reinterpret_cast<short*>(scriptFood + i * 8 + 0xBC) > 400) {
			smithIndices[smithCount++] = baseIndex + 3;
		}
		baseIndex += 4;
	}

	*outData = static_cast<char>(smithCount);
	memcpy(outData + 1, smithIndices, smithCount);

	int totalSize = static_cast<int>(smithCount) + 1;
	if ((totalSize & 3) != 0) {
		totalSize = ((totalSize >> 2) + 1) * 4;
	}
	char* writePtr = outData + totalSize;

	const double userRate =
		static_cast<double>(static_cast<float>(static_cast<float>(*reinterpret_cast<short*>(scriptFood + 0xBE2)) / 100.0f));

	for (int i = 0; i < 0x40; i++) {
		const int itemId = *reinterpret_cast<short*>(scriptFood + i * 2 + 0xB6);
		if (itemId > 400) {
			unsigned int itemBuf[0xE];
			memset(itemBuf, 0, sizeof(itemBuf));

			const int itemBase = flatBase + itemId * 0x48;
			unsigned int price = static_cast<unsigned int>(static_cast<float>(static_cast<unsigned short>(
				*reinterpret_cast<unsigned short*>(itemBase + 0x24))) * userRate);

			itemBuf[0] =
				(price << 24) |
				(((price >> 8) & 0xFF) << 16) |
				(((price >> 16) & 0xFF) << 8) |
				(price >> 24);

			reinterpret_cast<unsigned short*>(itemBuf)[2] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x26));
			reinterpret_cast<unsigned short*>(itemBuf)[3] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x28));
			reinterpret_cast<unsigned short*>(itemBuf)[4] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x2A));
			reinterpret_cast<unsigned short*>(itemBuf)[5] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x2C));
			reinterpret_cast<unsigned short*>(itemBuf)[6] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x2E));
			reinterpret_cast<unsigned short*>(itemBuf)[7] = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(itemBase + 0x30));

			for (int j = 0; j < 2; j++) {
				const int recipeBase = itemBase + j * 4;

				const unsigned short materialA = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(recipeBase + 0x38));
				reinterpret_cast<unsigned short*>(itemBuf)[8 + j] = materialA;
				if (materialA == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 2] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 2] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 2] = 0;
				} else {
					const int materialBase = flatBase + materialA * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[12 + j * 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 4));
					reinterpret_cast<unsigned short*>(itemBuf)[13 + j * 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 6));
					reinterpret_cast<unsigned short*>(itemBuf)[14 + j * 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 8));
				}

				const unsigned short materialB = static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(recipeBase + 0x3A));
				reinterpret_cast<unsigned short*>(itemBuf)[17 + j] = materialB;
				if (materialB == 0) {
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 2] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 2 + 2] = 0;
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 2 + 2] = 0;
				} else {
					const int materialBase = flatBase + materialB * 0x48;
					reinterpret_cast<unsigned short*>(itemBuf)[16 + j * 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 4));
					reinterpret_cast<unsigned short*>(itemBuf)[17 + j * 2 + 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 6));
					reinterpret_cast<unsigned short*>(itemBuf)[18 + j * 2 + 2] =
						static_cast<unsigned short>(*reinterpret_cast<unsigned short*>(materialBase + 8));
				}
			}

			memcpy(writePtr, itemBuf, 0x38);
			writePtr += 0x38;
			totalSize += 0x38;
		}
	}

	for (int i = 0; i < 4; i++) {
		const unsigned char* src = reinterpret_cast<unsigned char*>(scriptFood + i * 4 + 0xC08);
		unsigned int value =
			(static_cast<unsigned int>(src[3]) << 24) |
			(static_cast<unsigned int>(src[2]) << 16) |
			(static_cast<unsigned int>(src[1]) << 8) |
			static_cast<unsigned int>(src[0]);
		memcpy(writePtr, &value, 4);
		writePtr += 4;
		totalSize += 4;
	}

	__dla__FPv(smithIndices);

	OSWaitSemaphore(accessSemaphores + channel);
	reinterpret_cast<unsigned char*>(this)[0x2D56] =
		static_cast<unsigned char>(reinterpret_cast<unsigned char*>(this)[0x2D56] | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);

	Joybus.SetLetterSize(channel, totalSize);
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
	value = static_cast<unsigned int>(flags->m_sellFlg) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
	value = static_cast<unsigned int>(flags->m_buyFlg) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
	value = static_cast<unsigned int>(flags->m_mkSmithFlg) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D36])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31;
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
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetArtifactData(int, unsigned char*)
{
	return 0;
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
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D37])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return ((-static_cast<int>(value) | static_cast<int>(value)) >> 31U);
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
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D3E])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31U;
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
int GbaQueue::GetStrengthData(int channel, unsigned char* strengthData)
{
	char* compatibilityStr = reinterpret_cast<char*>(this) + 0x458;

	OSWaitSemaphore(accessSemaphores + channel);
	strengthData[0] = static_cast<unsigned char>(compatibilityStr[channel * 0xDC + 0x1C]);
	strengthData[1] = static_cast<unsigned char>(compatibilityStr[channel * 0xDC + 0x1D]);
	strengthData[2] = static_cast<unsigned char>(compatibilityStr[channel * 0xDC + 0x1E]);
	OSSignalSemaphore(accessSemaphores + channel);

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetArtiDatFlg(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D3F])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31U;
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MakeArtiData(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetTmpArtifactData(int, unsigned char*)
{
	return 0;
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
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D41])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31U;
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
	unsigned char mask = static_cast<unsigned char>(1 << channel);
	unsigned char radarMode;

	OSWaitSemaphore(accessSemaphores + channel);
	radarMode = static_cast<unsigned char>(obj[0x2D41]);
	obj[0x2D41] = static_cast<char>((radarMode & ~mask) | ((mode & 1) << channel));
	if (radarMode != static_cast<unsigned char>(obj[0x2D41])) {
		obj[0x2D42] = static_cast<char>(obj[0x2D42] | mask);
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
	unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(obj[0x2D42])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return (-value | value) >> 31U;
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
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetScouterInfo(int, unsigned char*)
{
	return 0;
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

unsigned int GbaQueue::GetChgHitFlg(int channel)
{
	unsigned int actualChannel = static_cast<unsigned int>(channel) &
	                             ~static_cast<unsigned int>((-reinterpret_cast<signed char*>(this)[0x2D56] |
	                                                        reinterpret_cast<signed char*>(this)[0x2D56]) >>
	                                                       31);
	OSSemaphore* semaphore = AccessSemaphoreAt(this, actualChannel);
	OSWaitSemaphore(semaphore);
	signed char flag = reinterpret_cast<signed char*>(this)[0x2D54];
	OSSignalSemaphore(semaphore);
	unsigned int value = static_cast<unsigned int>(flag) & (1U << actualChannel);
	return (-value | value) >> 31U;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgHitFlg(int channel)
{
	unsigned char flag = reinterpret_cast<unsigned char*>(this)[0x2D56];
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
	signed char flag = reinterpret_cast<signed char*>(this)[0x2D55];
	OSSignalSemaphore(semaphore);
	unsigned int value = static_cast<unsigned int>(flag) & (1U << channel);
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
	unsigned short enemyId;
	unsigned short enemyType;
	unsigned short* hitInfo = reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(this) + 0x2CDE);
	char* obj = reinterpret_cast<char*>(this);

	if (enemyIdx < 0) {
		enemyId = 0xFFFF;
		enemyType = 0xFFFF;
	} else {
		enemyId = static_cast<unsigned short>(enemyIdx);
		enemyType = *reinterpret_cast<unsigned short*>(Game.m_scriptWork[2][0][enemyIdx] + 0x1C);
	}

	OSWaitSemaphore(accessSemaphores + channel);
	hitInfo[channel * 2] = enemyId;
	hitInfo[channel * 2 + 1] = enemyType;
	obj[0x2CE8] = static_cast<char>(obj[0x2CE8] | (1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetHitEInfo(int channel)
{
	unsigned int actualChannel = static_cast<unsigned int>(channel) &
	                             ~static_cast<unsigned int>((-reinterpret_cast<char*>(this)[0x2D56] |
	                                                        reinterpret_cast<char*>(this)[0x2D56]) >>
	                                                       31);
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + actualChannel);
	int hitInfo = *reinterpret_cast<int*>(obj + 0x2CDE + (actualChannel * 4));
	OSSignalSemaphore(accessSemaphores + actualChannel);
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
	bool isSingle = reinterpret_cast<signed char*>(this)[0x2D56] == 1;
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
	OSSemaphore* semaphoreIter;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	m_controllerMode = static_cast<char>(controllerMode & 1);

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
			if (controllerMode == 0) {
				ret = Joybus.SetMType(i, 0);
			} else {
				ret = Joybus.SetMType(i, 4);
			}
			retries++;
		} while ((ret != 0) && (retries < 10));
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
	int i;
	OSSemaphore* semaphoreIter;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	mode = m_controllerMode;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSSignalSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	return static_cast<unsigned int>((-static_cast<int>(mode) | static_cast<int>(mode)) >> 31);
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
	char mode;
	int i;
	OSSemaphore* semaphoreIter;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	mode = m_pauseMode;

	i = 0;
	semaphoreIter = accessSemaphores;
	do {
		OSSignalSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	return static_cast<unsigned int>((-static_cast<int>(mode) | static_cast<int>(mode)) >> 31);
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
	return (static_cast<unsigned int>(value) >> ((channel & 0x1F) << 1)) & 3;
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
