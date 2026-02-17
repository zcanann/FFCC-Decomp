#include "ffcc/gbaque.h"
#include <string.h>
#include <Dolphin/os.h>
#include <Runtime.PPCEABI.H/NMWException.h>

extern void* ARRAY_802f49b0;
extern "C" void __dt__8GbaQueueFv(void*);

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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::BlockSem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ReleaseSem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::LoadAll()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetMemorysFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrMemorysFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char GbaQueue::GetMemorys(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetCmdNumFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrCmdNumFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char GbaQueue::GetCmdNum(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetPlayModeFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrPlayModeFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::SetStartBonusFlg()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::GetStartBonusFlg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaQueue::ClrStartBonusFlg(int)
{
	// TODO
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
