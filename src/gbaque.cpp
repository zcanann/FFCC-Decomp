#include "ffcc/gbaque.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include <string.h>
#include <Dolphin/os.h>
#include <Runtime.PPCEABI.H/NMWException.h>

extern void* ARRAY_802f49b0;
extern "C" void __dt__8GbaQueueFv(void*);
extern __declspec(section ".data") CFlatRuntime CFlat;
extern CMenuPcs MenuPcs;
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void Printf__7CSystemFPce(CSystem*, char*, ...);
extern "C" int memcmp(const void*, const void*, unsigned long);
extern "C" void MakeAgbString__4CMesFPcPcii(char*, char*, int, int);
extern "C" int IsOutOfShouki__12CCaravanWorkFv(void*);
extern "C" int CanPlayerUseItem__12CCaravanWorkFv(void*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);

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

static char s_gbaque_cpp[] = "gbaque.cpp";
static char s_mem_alloc_error[] = "%s[%d] Error! memory allocation.\n";
static char s_npc_max_over[] = "%s[%d] Error! NPC max over.\n";
static char s_subject_max_over[] = "%s[%d] Error! Subject max over.\n";
static char s_letter_data_error[] = "%s[%d] Error! Letter data error.\n";
static char s_cmake_name_crc_error[] = "%s[%d] Error! ChkCMakeName() crc.\n";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
GbaQueue::GbaQueue()
{
	// TODO
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
	memset(cmakeInfo, 0, 0x80);
	memset(obj + 0x2D40, 0xFF, 0x10);

	i = 0;
	osSemaphore = this;
	do {
		OSInitSemaphore(osSemaphore->accessSemaphores, 1);
		i = i + 1;
		osSemaphore = reinterpret_cast<GbaQueue*>(osSemaphore->accessSemaphores + 1);
	} while (i < 4);

	*reinterpret_cast<unsigned int*>(obj + 0x448) = 0xFF;
	*reinterpret_cast<unsigned int*>(obj + 0x444) = 0xFF;
	*reinterpret_cast<unsigned int*>(obj + 0x44C) = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x44E) = 0;
	*reinterpret_cast<unsigned short*>(obj + 0x450) = 0;

	obj[0x2C94] = 0;
	obj[0x2C88] = 0;
	obj[0x2C89] = 0;
	obj[0x2D38] = 0;
	obj[0x2D39] = 0;
	obj[0x2CCA] = 0;
	obj[0x2CCB] = 0;
	obj[0x2CCC] = 0;
	obj[0x2CCD] = 0;
	obj[0x2CDE] = 0;
	obj[0x2CE8] = 0;
	obj[0x2CE9] = 0;
	obj[0x2CFA] = 0;
	obj[0x2D04] = 0;
	obj[0x2D14] = 0;
	obj[0x2AF4] = 0;
	obj[0x2D42] = 0;
	obj[0x2D41] = 0xF;
	obj[0x2D43] = 0;
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
	obj[0x2D30] = 0;
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
	obj[0x2D56] = static_cast<unsigned char>(Game.game.m_gameWork.m_menuStageMode != 0);
	if (prevMenuStageMode != static_cast<unsigned char>(obj[0x2D56])) {
		obj[0x2C88] = 0xF;
	}

	spModeBits = static_cast<unsigned char>(Game.game.m_gameWork.m_spModeFlags[0] != 0);
	if (Game.game.m_gameWork.m_spModeFlags[1] != 0) {
		spModeBits |= 2;
	}
	if (Game.game.m_gameWork.m_spModeFlags[2] != 0) {
		spModeBits |= 4;
	}
	if (Game.game.m_gameWork.m_spModeFlags[3] != 0) {
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

	scriptFoodBase = reinterpret_cast<int*>(Game.game.m_scriptFoodBase);
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
		caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[i]);
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
	char* compatibilityStr = reinterpret_cast<char*>(accessSemaphores) + 0x28;

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
	memcpy(scriptFoodBase, Game.game.m_scriptFoodBase, sizeof(scriptFoodBase));

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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetSmithData(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetStageNo(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetStageNo(int, int*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetStageFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrStageFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetRadarType()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMBasePos(int, short*, short*)
{
	// TODO
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
		memcpy(localNames + (i * 0x10), Game.game.m_caravanWorkArr[i].unk_0x3ca_0x3dd, 0x10);
	}

	outOfShoukiMask = 0;
	if (reinterpret_cast<unsigned int*>(&CFlat)[0x1041] != 0) {
		unsigned char* entry = localPlayerStat;
		for (i = 0; i < 4; i++) {
			unsigned char menuStageMode = static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D56]);
			CGPartyObj* partyObj;
			CCaravanWork* caravanWork;

			if ((menuStageMode == 0) || (i != 1)) {
				partyObj = Game.game.m_partyObjArr[i];
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[i]);
			} else {
				partyObj = Game.game.m_partyObjArr[0];
				caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[0]);
			}

			if (caravanWork != 0) {
				if ((menuStageMode == 0) || ((menuStageMode != 0) && (i == 0))) {
					entry[3] = 1;
				} else if ((menuStageMode != 0) && (i == 1) && (Game.game.m_scriptFoodBase[0] != 0)) {
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
				memcpy(entry + 0xC, &Game.game.m_gameWork.m_linkTable[caravanWork->m_saveSlot][0][0][0], 8);

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
					const int itemDataBase = Game.game.unkCFlatData0[2];
					const int bossStageLimit = Game.game.m_gameWork.m_bossArtifactStageTable[Game.game.m_gameWork.m_bossArtifactStageIndex] + 2;
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetPlayerPos(int, unsigned int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetEnemyPos(int, unsigned int*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetTreasurePos(int, unsigned int*, int*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetPlayerStat(int, GbaPInfo*)
{
	// TODO
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
	int i;
	OSSemaphore* semaphoreIter;

	i = 0;
	semaphoreIter = (OSSemaphore*)this;
	do {
		OSWaitSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);

	memcpy(outName, reinterpret_cast<char*>(this) + 0x2A74, 0x80);

	i = 0;
	semaphoreIter = (OSSemaphore*)this;
	do {
		OSSignalSemaphore(semaphoreIter);
		i++;
		semaphoreIter++;
	} while (i < 4);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetItemAll(int, unsigned char*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetScrFlg()
{
	// TODO
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
	const unsigned int scriptFood = Game.game.m_scriptFoodBase[channel];
	const unsigned char channelMask = static_cast<unsigned char>(1U << channel);

	if (scriptFood == 0) {
		self[0x2C8A] = static_cast<unsigned char>(self[0x2C8A] | channelMask);
		Joybus.SetLetterSize(channel, 0);
		self[0x2C89] = static_cast<unsigned char>(self[0x2C89] & ~channelMask);
		return;
	}

	char* npcNameBuf = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
		0x800, Game.game.m_mainStage, s_gbaque_cpp, 0x7A7));
	if (npcNameBuf == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0x7A9);
		}
		return;
	}
	memset(npcNameBuf, 0, 0x800);

	char* subjectNameBuf = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
		0x1800, Game.game.m_mainStage, s_gbaque_cpp, 0x7B1));
	if (subjectNameBuf == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0x7B3);
		}
		__dla__FPv(npcNameBuf);
		return;
	}
	memset(subjectNameBuf, 0, 0x1800);

	unsigned int* letterEntryBuf = static_cast<unsigned int*>(__nwa__FUlPQ27CMemory6CStagePci(
		0x4000, Game.game.m_mainStage, s_gbaque_cpp, 0x7BB));
	if (letterEntryBuf == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0x7BD);
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

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.game.m_cFlatDataArr[1]);
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
				Printf__7CSystemFPce(&System, s_npc_max_over, s_gbaque_cpp, 0x7DC);
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
				Printf__7CSystemFPce(&System, s_subject_max_over, s_gbaque_cpp, 0x7F0);
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
					Printf__7CSystemFPce(&System, s_letter_data_error, s_gbaque_cpp, 0x810, channel, i);
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
void GbaQueue::MakeLetterData(int, char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetLetterLstFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrLetterLstFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetLetterDatFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrLetterDatFlg(int)
{
	// TODO
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
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMapObjDrawFlg(unsigned int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetAddLetter(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetFavoriteFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrFavoriteFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetFavorite(int, char*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMoneyFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrMoneyFlg(int)
{
	// TODO
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
	char* compatibilityStr = reinterpret_cast<char*>(accessSemaphores) + 0x28;

	OSWaitSemaphore(accessSemaphores + channel);
	int value = *reinterpret_cast<int*>(compatibilityStr + channel * 0xDC + 0x20);
	OSSignalSemaphore(accessSemaphores + channel);

	return value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrScrInitEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::InitCmakeInfo(int, int)
{
	// TODO
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

		GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.game.m_cFlatDataArr[1]);
		for (int i = 0; i < 0x100; i++) {
			if (strcmp(flatData->m_tabl[2].m_strings[i], reinterpret_cast<char*>(nameBuffer)) == 0) {
				Joybus.SendResult(channel, 1, resultCode, 0);
				return;
			}
		}

		for (int i = 0; i < 8; i++) {
			CCaravanWork* caravanWork = &Game.game.m_caravanWorkArr[i];
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
			Printf__7CSystemFPce(&System, s_cmake_name_crc_error, s_gbaque_cpp, 0xAD3);
		}
		Joybus.SendResult(channel, 1, resultCode, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChkCMakeCharaType(int, unsigned int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::CMakeFavorite(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetCompatibilityFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrCompatibilityFlg(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetCMakeInfo(int, GbaCMakeInfo*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetCmdData(int, unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetEquipData(int, unsigned char*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetShopFlg(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetSmithFlg(int)
{
	// TODO
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
		0x400, Game.game.m_mainStage, s_gbaque_cpp, 0xD79));
	if (itemNameScratch == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0xD7B);
		}
		return;
	}
	memset(itemNameScratch, 0, 0x400);

	char* agbStringScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
		0x400, Game.game.m_mainStage, s_gbaque_cpp, 0xD82));
	if (agbStringScratch == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0xD84);
		}
		__dla__FPv(itemNameScratch);
		return;
	}
	memset(agbStringScratch, 0, 0x400);

	const unsigned int scriptFood = Game.game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.game.unkCFlatData0[2];
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

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.game.m_cFlatDataArr[1]);
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
		0x400, Game.game.m_mainStage, s_gbaque_cpp, 0xDD5));
	if (itemNameScratch == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0xDD7);
		}
		return;
	}
	memset(itemNameScratch, 0, 0x400);

	char* agbStringScratch = static_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
		0x400, Game.game.m_mainStage, s_gbaque_cpp, 0xDDE));
	if (agbStringScratch == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0xDE0);
		}
		__dla__FPv(itemNameScratch);
		return;
	}
	memset(agbStringScratch, 0, 0x400);

	const unsigned int scriptFood = Game.game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.game.unkCFlatData0[2];
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

	GbaFlatDataView* flatData = reinterpret_cast<GbaFlatDataView*>(&Game.game.m_cFlatDataArr[1]);
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
		__nwa__FUlPQ27CMemory6CStagePci(0x40, Game.game.m_mainStage, s_gbaque_cpp, 0xE41));
	if (smithIndices == 0) {
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s_mem_alloc_error, s_gbaque_cpp, 0xE43);
		}
		return;
	}
	memset(smithIndices, 0xFF, 0x40);

	const unsigned int scriptFood = Game.game.m_scriptFoodBase[channel];
	const unsigned int flatBase = Game.game.unkCFlatData0[2];

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
	unsigned int flag;

	OSWaitSemaphore(accessSemaphores + channel);
	flag = static_cast<unsigned int>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D57])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>((-static_cast<int>(flag) | static_cast<int>(flag)) >> 31);
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
	reinterpret_cast<char*>(this)[0x2D57] =
		static_cast<char>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D57]) & ~(1 << channel));
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
	unsigned int flag;

	OSWaitSemaphore(accessSemaphores + channel);
	flag = static_cast<unsigned int>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D55])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>((-static_cast<int>(flag) | static_cast<int>(flag)) >> 31);
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
	reinterpret_cast<char*>(this)[0x2D55] =
		static_cast<char>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D55]) & ~(1 << channel));
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
	unsigned int flag;

	OSWaitSemaphore(accessSemaphores + channel);
	flag = static_cast<unsigned int>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D56])) & (1U << channel);
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned int>((-static_cast<int>(flag) | static_cast<int>(flag)) >> 31);
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
	reinterpret_cast<char*>(this)[0x2D56] =
		static_cast<char>(static_cast<unsigned char>(reinterpret_cast<char*>(this)[0x2D56]) & ~(1 << channel));
	OSSignalSemaphore(accessSemaphores + channel);
	Joybus.SetLetterSize(channel, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetResetFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetBonus(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetArtifactFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrArtifactFlg(int)
{
	// TODO
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
void GbaQueue::GetUseItemFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetChgUseItemFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgUseItemFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetChgUseItemFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetStrengthFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrStrengthFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetStrengthData(int, unsigned char*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetArtiDatFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrArtiDatFlg(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
unsigned char GbaQueue::GetRadarType(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrRadarTypeFlg()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetRadarMode(int)
{
	// TODO
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
void GbaQueue::GetChgRadarMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgRadarMode(int)
{
	// TODO
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
void GbaQueue::GetChgHitFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgHitFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetChgScouFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrChgScouFlg(int)
{
	// TODO
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
		enemyType = *reinterpret_cast<unsigned short*>(Game.game.m_scriptWork[2][0][enemyIdx] + 0x1C);
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
void GbaQueue::GetHitEInfo(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool GbaQueue::IsSingleMode(int)
{
	return false;
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
	GbaQueue* semaphoreIter;

	i = 0;
	semaphoreIter = this;
	do {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	} while (i < 4);

	reinterpret_cast<char*>(this)[0x2D57] = static_cast<char>(controllerMode & 1);

	i = 0;
	semaphoreIter = this;
	do {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		i++;
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
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
 * Address:	TODO
 * Size:	TODO
 */
char GbaQueue::GetControllerMode()
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::OpenMenu(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetPauseMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetPauseMode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char GbaQueue::GetItemUse(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetSPModeFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrSPModeFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GbaQueue::GetSPMode(int)
{
	return 0;
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
	OSWaitSemaphore(accessSemaphores + channel);
	char value = obj[0x2C8B];
	OSSignalSemaphore(accessSemaphores + channel);
	unsigned int mask = static_cast<unsigned int>(value) & (1U << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2C8B] = obj[0x2C8B] & ~(1 << channel);
	OSSignalSemaphore(accessSemaphores + channel);
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
unsigned char GbaQueue::GetMemorys(int channel)
{
	char* compatibilityStr = reinterpret_cast<char*>(accessSemaphores) + 0x28;
	OSWaitSemaphore(accessSemaphores + channel);
	unsigned short value = *reinterpret_cast<unsigned short*>(compatibilityStr + channel * 0xDC + 0x10);
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned char>(value);
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
	OSWaitSemaphore(accessSemaphores + channel);
	char value = obj[0x2C8A];
	OSSignalSemaphore(accessSemaphores + channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2C8A] = obj[0x2C8A] & ~(3 << (channel << 1));
	OSSignalSemaphore(accessSemaphores + channel);
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
unsigned char GbaQueue::GetCmdNum(int channel)
{
	char* obj = reinterpret_cast<char*>(this);
	OSWaitSemaphore(accessSemaphores + channel);
	char value = obj[channel * 0xDC + 0x527];
	OSSignalSemaphore(accessSemaphores + channel);
	return static_cast<unsigned char>(value);
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
	OSWaitSemaphore(accessSemaphores + channel);
	char value = obj[0x2C88];
	OSSignalSemaphore(accessSemaphores + channel);
	unsigned int mask = static_cast<unsigned int>(value) & (1U << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2C88] = obj[0x2C88] & ~(1 << channel);
	OSSignalSemaphore(accessSemaphores + channel);
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
	GbaQueue* semaphoreIter = this;
	for (int i = 0; i < 4; i++) {
		OSWaitSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
	}

	char* obj = reinterpret_cast<char*>(this);
	obj[0x2D14] = 0xF;

	semaphoreIter = this;
	for (int i = 0; i < 4; i++) {
		OSSignalSemaphore(semaphoreIter->accessSemaphores);
		semaphoreIter = reinterpret_cast<GbaQueue*>(semaphoreIter->accessSemaphores + 1);
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
	OSWaitSemaphore(accessSemaphores + channel);
	char value = obj[0x2D14];
	OSSignalSemaphore(accessSemaphores + channel);
	unsigned int mask = static_cast<unsigned int>(value) & (1U << channel);
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
	OSWaitSemaphore(accessSemaphores + channel);
	obj[0x2D14] = obj[0x2D14] & ~(1 << channel);
	OSSignalSemaphore(accessSemaphores + channel);
}

/*
 * --INFO--
 * PAL Address: 0x800d15c8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_gbaque_cpp(void)
{
	GbaQue.Init();
	__register_global_object(&GbaQue, __dt__8GbaQueueFv, ARRAY_802f49b0);
}
