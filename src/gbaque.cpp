#include "ffcc/gbaque.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/p_game.h"
#include <string.h>
#include <Dolphin/os.h>
#include <Runtime.PPCEABI.H/NMWException.h>

extern void* ARRAY_802f49b0;
extern "C" void __dt__8GbaQueueFv(void*);
extern __declspec(section ".data") CFlatRuntime CFlat;

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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrShopMode()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ExecutQueue()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadPlayerStat()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadMapItemStat()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetCaravanName(char*)
{
	// TODO
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
void GbaQueue::MakeLetterList(int, char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
int GbaQueue::GetMapObj(unsigned char*)
{
	return 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMoney(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ChkCMakeName(int, unsigned int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MakeBuyData(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MakeSellData(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::MakeSmithData(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetSellFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrSellFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetBuyFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrBuyFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMkSmithFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrMkSmithFlg(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetRadarMode(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetHitEnemy(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetControllerMode(int)
{
	// TODO
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
