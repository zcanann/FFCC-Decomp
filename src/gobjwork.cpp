#include "ffcc/gobjwork.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/gbaque.h"
#include "ffcc/joybus.h"
#include "ffcc/partyobj.h"
#include "ffcc/mes.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/system.h"
#include <string.h>

namespace {
static inline unsigned short* GetItemDataPtr(int itemIdx)
{
	return (unsigned short*)(Game.unkCFlatData0[2] + (itemIdx * 0x48));
}

struct GobjworkFlatTableEntry {
	int count;
	const char** index;
	char* buffer;
};

struct GobjworkFlatData {
	char pad[0x6C];
	GobjworkFlatTableEntry table[8];
};

static inline float GetStatusMultiplier(int offset)
{
	return ((float)(*(unsigned short*)(Game.unk_flat3_field_8_0xc7dc + offset)) * 0.01f) + 1.0f;
}
}

extern "C" void __dl__FPv(void*);
extern "C" int __cntlzw(unsigned int);
extern "C" int sprintf(char*, const char*, ...);
extern "C" int useItem__10CGPartyObjFi(CGPartyObj*, int);
extern "C" int putItem__10CGPartyObjFi(CGPartyObj*, int);
extern "C" int putGil__10CGPartyObjFi(CGPartyObj*, int);
extern "C" int DelItem__6JoyBusFiUc(JoyBus*, int, unsigned char);
extern "C" int GetSkillStr__8CMenuPcsFi(void*, int);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	void*, void*, int, int, int, void*, void*);
extern "C" void* __vt__8CMonWork[];
extern "C" void* __vt__12CCaravanWork[];
extern "C" void* __vt__9CGObjWork[];
extern float FLOAT_803309a8;
extern char DAT_801d9ff0[];

/*
 * --INFO--
 * PAL Address: 0x800a2dd4
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObjWork::CGObjWork()
{
	m_objType = -1;
	*reinterpret_cast<unsigned int*>(&m_saveSlot) = 0xFFFFFFFF;
	m_ownerObj = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a2db8
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObjWork::~CGObjWork()
{
}

/*
 * --INFO--
 * PAL Address: 0x800a2d8c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CGObjWork* dtor_800A2D8C(CGObjWork* gObjWork, short shouldDelete)
{
	if (gObjWork != 0) {
		*(void**)gObjWork = __vt__9CGObjWork;
		if (0 < shouldDelete) {
			__dl__FPv(gObjWork);
		}
	}

	return gObjWork;
}

/*
 * --INFO--
 * PAL Address: 0x800a2ca8
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObjWork::Init(int baseDataIndex, CRomWork* romWork, int idOffset)
{
	short* romData = reinterpret_cast<short*>(romWork);

	m_baseDataIndex = baseDataIndex;
	m_id = romData[0] + idOffset;
	m_param1 = romData[1];
	m_param2 = romData[2];
	m_maxHp = romData[3];
	m_strength = romData[4];
	m_magic = romData[5];
	m_defense = romData[6];
	m_romWorkPtr = reinterpret_cast<unsigned short*>(romData + 8);

	memcpy(m_elementResistances, m_romWorkPtr + 0x6F, 0x16);
	memset(m_statusTimers + 3, 0, 0x4E);
	memset(m_statusValues, 0xFF, sizeof(m_statusValues));
	m_hp = m_maxHp;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGObjWork::CalcStatus()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800a2bf8
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCaravanWork::CCaravanWork()
{
	m_shopState = 0;
	unk_0x3a8 = 0;
	unk_0x3ac = 0;
	m_objType = 0;
	m_joybusCaravanId = -1;
	sprintf((char*)unk_0x3ca_0x3dd, DAT_801d9ff0);
	m_letterMeta[0] = 0xFFFF;
	m_letterMeta[1] = 0xFFFF;
	m_letterMeta[2] = 0xFFFF;
	m_letterMeta[3] = 0xFFFF;
	m_letterMeta[4] = 0xFFFF;
	m_letterMeta[5] = 0xFFFF;
	m_letterMeta[6] = 0xFFFF;
	m_letterMeta[7] = 0xFFFF;
	clearCaravanWork();
}

/*
 * --INFO--
 * PAL Address: 0x800a2bf0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCaravanWork::~CCaravanWork()
{
}

/*
 * --INFO--
 * PAL Address: 0x800a2b9c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CCaravanWork* dtor_800A2B9C(CCaravanWork* caravanWork, short shouldDelete)
{
	if (caravanWork != 0) {
		*(void**)caravanWork = __vt__12CCaravanWork;
		if (caravanWork != 0) {
			*(void**)caravanWork = __vt__9CGObjWork;
		}
		if (0 < shouldDelete) {
			__dl__FPv(caravanWork);
		}
	}

	return caravanWork;
}

/*
 * --INFO--
 * PAL Address: 0x800a2a64
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::clearCaravanWork()
{
	m_letterCount = 0;
	m_gil = 0;
	*reinterpret_cast<unsigned short*>(&unk_0x3c8) = 0;
	m_equipment[0] = -1;
	m_equipment[1] = -1;
	m_equipment[2] = -1;
	m_equipment[3] = -1;
	m_inventoryItemCount = 0;
	memset(m_inventoryItems, 0xFF, 0x148);
	memset(m_evtWorkArr, 0, 0x100);
	memset(m_evtWordArr, 0, 0x200);
	m_tempStatBuffTimer = 0;
	m_tempStatBuffId = 0;
	unk_0x3e6 = 0;
	m_evtState0 = 0;
	m_evtState1 = 0;
	memset(m_commandListInventorySlotRef, 0xFF, 0x10);
	memset(m_commandListExtra, 0, 0x10);
	memset(&m_bonusCondition, 0, 1);
	memset(m_equipEffectParams, 0, 7);
	memset(&m_shopBusyFlag, 0, 1);
	memset(&m_caravanLocalFlags, 0, 1);
	m_inventoryItemCount = 0;
	memset(m_inventoryItems, 0xFF, 0x148);
	m_progressValue = 0;
	m_numCmdListSlots = 4;
	m_baseCmdListSlots = 4;
	m_currentCmdListIndex = 0;
	m_weaponIdx = 0;
	m_equipEffectFlags = 0;
	unk_0xc1e = 0;
	m_shopRandSeed = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a29dc
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::LoadInit()
{
	m_shopState = 0;
	unk_0x3a8 = 0;
	unk_0x3ac = 0;
	m_objType = 0;
	m_joybusCaravanId = -1;
	sprintf((char*)unk_0x3ca_0x3dd, DAT_801d9ff0);
	m_letterMeta[0] = 0xFFFF;
	m_letterMeta[1] = 0xFFFF;
	m_letterMeta[2] = 0xFFFF;
	m_letterMeta[3] = 0xFFFF;
	m_letterMeta[4] = 0xFFFF;
	m_letterMeta[5] = 0xFFFF;
	m_letterMeta[6] = 0xFFFF;
	m_letterMeta[7] = 0xFFFF;
	clearCaravanWork();
}

/*
 * --INFO--
 * PAL Address: 0x800a2994
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::ClearEvtWork()
{
	memset(m_evtWorkArr, 0, sizeof(m_evtWorkArr));
	memset(m_evtWordArr, 0, sizeof(m_evtWordArr));
}

/*
 * --INFO--
 * PAL Address: 0x800a293c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::LoadFinished()
{
	if (m_shopState == 0) {
		return;
	}

	CGame* game = &Game;
	m_baseDataIndex = (m_id / 100) - 1;
	m_romWorkPtr = reinterpret_cast<unsigned short*>(game->unkCFlatData0[0] + (m_baseDataIndex * 0x1D0) + 0x10);
}

/*
 * --INFO--
 * PAL Address: 0x800a27b0
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::Init(int baseDataIndex, CRomWork* romWork, int idOffset)
{
	short* romData = reinterpret_cast<short*>(romWork);
	int value = 0;

	m_baseDataIndex = baseDataIndex;
	m_id = romData[0] + idOffset;
	m_param1 = romData[1];
	m_param2 = romData[2];
	m_maxHp = romData[3];
	m_strength = romData[4];
	m_magic = romData[5];
	m_defense = romData[6];
	m_romWorkPtr = reinterpret_cast<unsigned short*>(romData + 8);
	memcpy(m_elementResistances, m_romWorkPtr + 0x6F, 0x16);
	memset(m_statusTimers + 3, 0, 0x4E);
	memset(m_statusValues, 0xFF, sizeof(m_statusValues));
	m_hp = m_maxHp;
	m_shopState = 1;

	value = (int)m_id - 100;
	value = (value / 200) + (value >> 31);
	m_tribeId = (short)value - (short)(value >> 31);

	value = (int)m_id - 100;
	value = (value / 100) + (value >> 31);
	m_genderFlag = ((short)value - (short)(value >> 31)) & 1;

	clearCaravanWork();
	m_bonusCondition = 0;
	memset(m_artifactRelated, 0, sizeof(m_artifactRelated));
	m_artifactRelated[3] = *(unsigned short*)(Game.m_bossArtifactBase +
											  (Game.m_gameWork.m_bossArtifactStageIndex * 0x168) + 0x62);
	m_artifactRelated[4] = *(unsigned short*)(Game.m_bossArtifactBase +
											  (Game.m_gameWork.m_bossArtifactStageIndex * 0x168) + 100);
}

/*
 * --INFO--
 * PAL Address: 0x800a2720
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SetBonusCondition(int bonusCondition)
{
	m_bonusCondition = static_cast<unsigned char>(bonusCondition);
	memset(m_artifactRelated, 0, sizeof(m_artifactRelated));
	m_artifactRelated[3] =
		*(unsigned short*)(Game.m_bossArtifactBase +
						   (Game.m_gameWork.m_bossArtifactStageIndex * 0x168) +
						   (bonusCondition * 8) + 0x62);
	m_artifactRelated[4] =
		*(unsigned short*)(Game.m_bossArtifactBase +
						   (Game.m_gameWork.m_bossArtifactStageIndex * 0x168) +
						   (bonusCondition * 8) + 100);
}

/*
 * --INFO--
 * PAL Address: 0x800A269C
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::IsOutOfShouki()
{
	int result = 0;

	if (FLOAT_803309a8 * Game.unkFloat_0xca10 <
		*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x5BC)) {
		if (m_hp != 0) {
			if ((((int)((unsigned int)(unsigned char)CFlat[4836] << 24) < 0) ||
				 ((int)(((unsigned int)(unsigned char)CFlat[4836] << 27) |
					   ((unsigned int)(unsigned char)CFlat[4836] >> 5)) < 0)) &&
				((int)((unsigned int) * (unsigned char*)(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x9B)
					  << 24) < 0)) {
				result = 1;
			}
		}
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800a2514
 * PAL Size: 392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::AddLetter(int letterType, int senderId, int placeId, int moneyValue, int hasMoneyFlag,
							 int hasReplyFlag, int itemA, int itemB, int itemC)
{
	struct LetterSlot
	{
		unsigned int words[3];
	};

	LetterSlot* slots = reinterpret_cast<LetterSlot*>(m_letter0);
	for (int i = 98; i >= 0; i--) {
		slots[i + 1] = slots[i];
	}

	memset(m_letter0, 0, sizeof(m_letter0));

	unsigned short* letterWords16 = reinterpret_cast<unsigned short*>(m_letter0);
	unsigned int* letterWords32 = reinterpret_cast<unsigned int*>(m_letter0);
	letterWords16[0] = (unsigned short)((letterWords16[0] & 0xF803) | ((letterType << 2) & 0x7FC));
	letterWords32[0] = (letterWords32[0] & 0xFFFC01FF) | ((senderId & 0x1FF) << 9);
	m_letter0[0] = (unsigned char)((m_letter0[0] & 0xF7) | ((hasMoneyFlag << 3) & 8));
	if (((m_letter0[0] >> 3) & 1) != 0) {
		int divValue = (moneyValue / 100) + (moneyValue >> 31);
		moneyValue = divValue - (divValue >> 31);
	}
	letterWords16[1] = (unsigned short)((letterWords16[1] & 0xFE00) | (moneyValue & 0x1FF));
	m_letter0[0] = (unsigned char)(m_letter0[0] & 0x7F);
	m_letter0[0] = (unsigned char)(m_letter0[0] & 0xBF);
	m_letter0[0] = (unsigned char)(m_letter0[0] & 0xDF);
	m_letter0[0] = (unsigned char)((m_letter0[0] & 0xEF) | ((hasReplyFlag << 4) & 0x10));
	letterWords16[2] = (unsigned short)itemA;
	letterWords16[3] = (unsigned short)itemB;
	letterWords16[4] = (unsigned short)itemC;
	letterWords16[5] = 0;

	int nextCount = m_letterCount + 1;
	if (nextCount > 100) {
		nextCount = 100;
	}
	m_letterCount = nextCount;

	GbaQue.SetAddLetter(m_joybusCaravanId);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CLetterWork::operator= (const CCaravanWork::CLetterWork&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800a23d8
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::FGLetterOpen(int letterIdx)
{
	unsigned int stack[2];
	unsigned char* letter = m_letter0 + letterIdx * 0xC;
	unsigned short* words16 = reinterpret_cast<unsigned short*>(letter);

	stack[0] = (words16[0] >> 2) & 0x1FF;
	stack[1] = (*(unsigned int*)letter >> 9) & 0x1FF;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
		CFlat, Game.m_partyObjArr[m_joybusCaravanId], 2, 0xF, 2, stack, 0);

	CMes::m_tempVar[0] = words16[2];
	CMes::m_tempVar[1] = words16[3];
	CMes::m_tempVar[2] = words16[4];
	CMes::m_tempVar[3] = words16[5];
	CMes::m_tempVar[4] = (words16[0] >> 2) & 0x1FF;
	CMes::m_tempVar[5] = (*(unsigned int*)letter >> 9) & 0x1FF;

	if (((letter[0] >> 3) & 1) == 0) {
		CMes::m_tempVar[6] = words16[1] & 0x1FF;
	} else {
		CMes::m_tempVar[6] = 0;
	}

	if (((letter[0] >> 3) & 1) == 0) {
		CMes::m_tempVar[7] = 0;
	} else {
		CMes::m_tempVar[7] = (words16[1] & 0x1FF) * 100;
	}

	CMes::m_tempVar[0x20] = m_saveSlot;
	CMes::m_tempVar[0x21] = m_partyIndex;
	CMes::m_tempVar[0x22] = m_isLoadingFlag;
	CMes::m_tempVar[0x23] = m_miscFlags;
	letter[0] = (letter[0] & 0x7F) | 0x80;
}

/*
 * --INFO--
 * PAL Address: 0x800a2330
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::FGLetterReply(int letterIdx, int param3, int param4, int param5)
{
	int stack[5];
	unsigned char* letter = m_letter0 + (letterIdx * 0xC);
	unsigned short* words16 = reinterpret_cast<unsigned short*>(letter);
	unsigned int* words32 = reinterpret_cast<unsigned int*>(letter);

	stack[0] = (words16[0] >> 2) & 0x1FF;
	stack[1] = (words32[0] >> 9) & 0x1FF;
	stack[2] = param3;
	stack[3] = param4;
	stack[4] = param5;

	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
		CFlat, Game.m_partyObjArr[m_joybusCaravanId], 2, 0x10, 5, stack, 0);

	letter[0] = (letter[0] & 0xDF) | 0x20;
}

/*
 * --INFO--
 * PAL Address: 0x800a2290
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::FGUseItem(int itemIdx, int updateJoybus)
{
	int used = useItem__10CGPartyObjFi((CGPartyObj*)m_ownerObj, (int)(short)m_inventoryItems[itemIdx]);
	if ((used != 0) && ((short)m_inventoryItems[itemIdx] != -1)) {
		m_inventoryItems[itemIdx] = 0xFFFF;
		m_inventoryItemCount--;
		if (updateJoybus != 0) {
			DelItem__6JoyBusFiUc(&Joybus, m_joybusCaravanId, (char)itemIdx);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a21f0
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::FGPutItem(int itemIdx, int updateJoybus)
{
	int put = putItem__10CGPartyObjFi((CGPartyObj*)m_ownerObj, (int)(short)m_inventoryItems[itemIdx]);
	if ((put != 0) && ((short)m_inventoryItems[itemIdx] != -1)) {
		m_inventoryItems[itemIdx] = 0xFFFF;
		m_inventoryItemCount--;
		if (updateJoybus != 0) {
			DelItem__6JoyBusFiUc(&Joybus, m_joybusCaravanId, (char)itemIdx);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a2164
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::FGPutGil(int gilToRemove)
{
	int put = putGil__10CGPartyObjFi((CGPartyObj*)m_ownerObj, gilToRemove);
	if (put != 0) {
		int gil = m_gil;
		gil += -gilToRemove;
		m_gil = gil;
		if (gil <= 99999999) {
			if (gil < 0) {
				m_gil = 0;
			}
		} else {
			m_gil -= m_gil - 99999999;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a2100
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::ChgCmdLst(int commandListIndex, int itemSlot)
{
	m_commandListInventorySlotRef[commandListIndex] = itemSlot;
	if ((itemSlot < 0) && (m_currentCmdListIndex == commandListIndex)) {
		m_currentCmdListIndex = GetNextCmdListIdx(m_currentCmdListIndex, -1);
	}
	CheckAndResetCurrentWeaponIdx(0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::ChgEquipPos(int idx, int equip)
{
	m_equipment[idx] = equip;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCaravanWork::CanAddComList(int count)
{
	short* slot = m_commandListInventorySlotRef;
	int remaining = (short)m_numCmdListSlots;

	if (2 < remaining) {
		remaining = remaining - 2;
		while (remaining != 0) {
			if ((*slot == -1) && (--count == 0)) {
				break;
			}
			slot++;
			remaining--;
		}
	}

	return (((unsigned int)__cntlzw(count)) >> 5) & 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x800a200c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::AddComList(int itemSlot, int* cmdListSlotOut)
{
	if (m_numCmdListSlots > 2) {
		for (int i = 2; i < m_numCmdListSlots; i++) {
			if (m_commandListInventorySlotRef[i] == -1) {
				m_commandListInventorySlotRef[i] = itemSlot;
				Joybus.SetCmdLst(m_joybusCaravanId, i, itemSlot);
				if (cmdListSlotOut != 0) {
					*cmdListSlotOut = i;
				}
				return 1;
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a1fbc
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::DeleteCmdList(int commandListIndex, int updateJoybus)
{
	short* slot = (short*)m_commandListInventorySlotRef + commandListIndex;
	*slot = -1;
	if (updateJoybus != 0) {
		Joybus.SetCmdLst(m_joybusCaravanId, commandListIndex, -1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a1f08
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::AddItem(int itemId, int* inventorySlotOut)
{
	if ((unsigned short)m_inventoryItemCount >= 0x40) {
		return 0;
	}

	for (unsigned int i = 0; i < 0x40; i++) {
		if (m_inventoryItems[i] == 0xFFFF) {
			m_inventoryItems[i] = (unsigned short)itemId;
			m_inventoryItemCount = (short)(m_inventoryItemCount + 1);
			Joybus.SetItem(m_joybusCaravanId, (unsigned char)i, (short)itemId);
			if (inventorySlotOut != 0) {
				*inventorySlotOut = i;
			}
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a1ee8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SetArtifact(int artifactIndex, int enabled)
{
	int artifact = -1;
	if (enabled != 0) {
		artifact = artifactIndex + 0x9F;
	}
	m_artifacts[artifactIndex] = (unsigned short)artifact;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGAddItemIdx(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCaravanWork::ChkNumItem(char*, int numItems)
{
	int emptySlots = 0;

	if (m_treasures[0] == 0xFFFF) {
		emptySlots++;
	}
	if (m_treasures[1] == 0xFFFF) {
		emptySlots++;
	}
	if (m_treasures[2] == 0xFFFF) {
		emptySlots++;
	}
	if (m_treasures[3] == 0xFFFF) {
		emptySlots++;
	}

	return (numItems <= emptySlots);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CanAddTmpArtifact(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800a1d70
 * PAL Size: 284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::FindItem(int itemId)
{
	int baseIdx = 0;
	int rowCount = 8;
	CCaravanWork* cur = this;

	while (true) {
		if ((short)cur->m_inventoryItems[0] != -1 && (short)cur->m_inventoryItems[0] == itemId) {
			return baseIdx;
		}
		if ((short)cur->m_inventoryItems[1] != -1 && (short)cur->m_inventoryItems[1] == itemId) {
			return baseIdx + 1;
		}
		if ((short)cur->m_inventoryItems[2] != -1 && (short)cur->m_inventoryItems[2] == itemId) {
			return baseIdx + 2;
		}
		if ((short)cur->m_inventoryItems[3] != -1 && (short)cur->m_inventoryItems[3] == itemId) {
			return baseIdx + 3;
		}
		if ((short)cur->m_inventoryItems[4] != -1 && (short)cur->m_inventoryItems[4] == itemId) {
			return baseIdx + 4;
		}
		if ((short)cur->m_inventoryItems[5] != -1 && (short)cur->m_inventoryItems[5] == itemId) {
			return baseIdx + 5;
		}
		if ((short)cur->m_inventoryItems[6] != -1 && (short)cur->m_inventoryItems[6] == itemId) {
			return baseIdx + 6;
		}
		if ((short)cur->m_inventoryItems[7] != -1 && (short)cur->m_inventoryItems[7] == itemId) {
			return baseIdx + 7;
		}

		cur = (CCaravanWork*)&cur->m_baseDataIndex;
		baseIdx += 8;
		rowCount--;
		if (rowCount == 0) {
			return -1;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::DeleteItemIdx(int itemSlot, int updateJoybus)
{
	unsigned short item = m_inventoryItems[itemSlot];

	if (item != 0xFFFF) {
		short itemCount = m_inventoryItemCount;
		m_inventoryItems[itemSlot] = 0xFFFF;
		m_inventoryItemCount = itemCount - 1;
		if (updateJoybus != 0) {
			DelItem__6JoyBusFiUc(&Joybus, m_joybusCaravanId, static_cast<signed char>(itemSlot));
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a1c7c
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::DeleteItem(int itemIndex, int updateJoybus)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if ((short)m_inventoryItems[i] != -1 && (short)m_inventoryItems[i] == itemIndex) {
            m_inventoryItems[i] = 0xFFFF;
            m_inventoryItemCount = m_inventoryItemCount - 1;
            if (updateJoybus != 0) {
                DelItem__6JoyBusFiUc(&Joybus, m_joybusCaravanId, (char)i);
            }
            return 1;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a1be8
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::AddTmpArtifact(int itemId, int* outIndex)
{
    int i;

    for (i = 0; i < 4; i++) {
        unsigned short treasure = m_treasures[i];
        if ((short)treasure == -1) {
            m_treasures[i] = (unsigned short)itemId;
            Joybus.SetTmpArti(m_joybusCaravanId, i, itemId);
            if (outIndex != 0) {
                *outIndex = i;
            }
            return 1;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a1bb0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::CanAddGil(int gilAmount)
{
	int totalGil = m_gil + gilAmount;
	return (totalGil >= 0 && totalGil < 100000000);
}

/*
 * --INFO--
 * PAL Address: 0x800a1b5c
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::AddGil(int gilToAdd)
{
	int totalGil;

	m_gil = m_gil + gilToAdd;
	totalGil = m_gil;
	if (totalGil <= 99999999) {
		if (totalGil < 0) {
			gilToAdd = gilToAdd - totalGil;
			m_gil = 0;
		}
	} else {
		int overflow = totalGil - 99999999;
		m_gil = totalGil - overflow;
		gilToAdd = gilToAdd - overflow;
	}
	return gilToAdd;
}

/*
 * --INFO--
 * PAL Address: 0x800a1ab0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetFoodRank(int playerIdx)
{
	int rank = 0;
	int baseIdx = 0;
	int loops = 2;
	CCaravanWork* cur = this;

	do {
		if ((playerIdx != baseIdx) && (m_letterMeta[playerIdx] < cur->m_letterMeta[0])) {
			rank++;
		}
		if ((playerIdx != (baseIdx + 1)) && (m_letterMeta[playerIdx] < cur->m_letterMeta[1])) {
			rank++;
		}
		if ((playerIdx != (baseIdx + 2)) && (m_letterMeta[playerIdx] < cur->m_letterMeta[2])) {
			rank++;
		}
		if ((playerIdx != (baseIdx + 3)) && (m_letterMeta[playerIdx] < cur->m_letterMeta[3])) {
			rank++;
		}

		cur = (CCaravanWork*)&cur->m_saveSlot;
		baseIdx += 4;
		loops--;
	} while (loops != 0);

	return rank;
}

/*
 * --INFO--
 * PAL Address: 0x800a077c
 * PAL Size: 4916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SearchRomLetterWork(CRomLetterWork **romLetterWork, int maxResults)
{
	int foundCount = 0;
	unsigned char* curLetter = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[3]);
	unsigned char* linkBase = &Game.m_gameWork.m_linkTable[m_saveSlot][0][0][0];

	if (maxResults > 0) {
		for (int i = 0; i < maxResults; i++) {
			romLetterWork[i] = 0;
		}
	}

	for (int letterIdx = 0; letterIdx < 0x200; letterIdx++, curLetter += 0x3E) {
		unsigned short condBits = *reinterpret_cast<unsigned short*>(curLetter + 0x18);

		if ((condBits & 0x7FFF) != 0) {
			const bool invert = (condBits & 0x8000) != 0;
			bool matched = false;

			if ((condBits & 0x0001) != 0 && m_tribeId == 0) {
				matched = true;
			}
			if ((condBits & 0x0002) != 0 && m_tribeId == 1) {
				matched = true;
			}
			if ((condBits & 0x0004) != 0 && m_tribeId == 2) {
				matched = true;
			}
			if ((condBits & 0x0008) != 0 && m_tribeId == 3) {
				matched = true;
			}
			if ((condBits & 0x0010) != 0 && m_genderFlag == 0) {
				matched = true;
			}
			if ((condBits & 0x0020) != 0 && m_genderFlag == 1) {
				matched = true;
			}
			if ((condBits & 0x0040) != 0 && GetFoodRank(0) == 0) {
				matched = true;
			}
			if ((condBits & 0x0080) != 0 && GetFoodRank(1) == 0) {
				matched = true;
			}
			if ((condBits & 0x0100) != 0 && GetFoodRank(2) == 0) {
				matched = true;
			}
			if ((condBits & 0x0200) != 0 && GetFoodRank(3) == 0) {
				matched = true;
			}
			if ((condBits & 0x0400) != 0 && GetFoodRank(4) == 0) {
				matched = true;
			}
			if ((condBits & 0x0800) != 0 && GetFoodRank(5) == 0) {
				matched = true;
			}
			if ((condBits & 0x1000) != 0 && GetFoodRank(6) == 0) {
				matched = true;
			}
			if ((condBits & 0x2000) != 0 && GetFoodRank(7) == 0) {
				matched = true;
			}

			if ((!invert && !matched) || (invert && matched)) {
				continue;
			}
		}

		condBits = *reinterpret_cast<unsigned short*>(curLetter + 0x1A);
		if ((condBits & 0x7FFF) != 0) {
			const bool invert = (condBits & 0x8000) != 0;
			bool matched = false;

			if ((condBits & 0x0001) != 0 && unk_0x3ac == 0) {
				matched = true;
			}
			if ((condBits & 0x0002) != 0 && unk_0x3ac == 1) {
				matched = true;
			}
			if ((condBits & 0x0004) != 0 && unk_0x3ac == 2) {
				matched = true;
			}
			if ((condBits & 0x0008) != 0 && unk_0x3ac == 3) {
				matched = true;
			}
			if ((condBits & 0x0010) != 0 && unk_0x3ac == 4) {
				matched = true;
			}
			if ((condBits & 0x0020) != 0 && unk_0x3ac == 5) {
				matched = true;
			}
			if ((condBits & 0x0040) != 0 && unk_0x3ac == 6) {
				matched = true;
			}
			if ((condBits & 0x0080) != 0 && unk_0x3ac == 7) {
				matched = true;
			}
			if ((condBits & 0x0100) != 0 && linkBase[1] != 0) {
				matched = true;
			}
			if ((condBits & 0x0200) != 0 && linkBase[2] != 0) {
				matched = true;
			}
			if ((condBits & 0x0400) != 0 && linkBase[3] != 0) {
				matched = true;
			}
			if ((condBits & 0x0800) != 0 && linkBase[4] != 0) {
				matched = true;
			}
			if ((condBits & 0x1000) != 0 && linkBase[5] != 0) {
				matched = true;
			}
			if ((condBits & 0x2000) != 0 && linkBase[6] != 0) {
				matched = true;
			}
			if ((condBits & 0x4000) != 0 && linkBase[7] != 0) {
				matched = true;
			}

			if ((!invert && !matched) || (invert && matched)) {
				continue;
			}
		}

		condBits = *reinterpret_cast<unsigned short*>(curLetter + 0x1C);
		if ((condBits & 0x7FFF) != 0) {
			const bool invert = (condBits & 0x8000) != 0;
			bool matched = false;

			if ((condBits & 0x0001) != 0 && linkBase[1] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0002) != 0 && linkBase[2] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0004) != 0 && linkBase[3] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0008) != 0 && linkBase[4] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0010) != 0 && linkBase[5] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0020) != 0 && linkBase[6] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0040) != 0 && linkBase[7] >= 0x3D) {
				matched = true;
			}
			if ((condBits & 0x0100) != 0 && linkBase[1] > 0 && linkBase[1] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x0200) != 0 && linkBase[2] > 0 && linkBase[2] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x0400) != 0 && linkBase[3] > 0 && linkBase[3] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x0800) != 0 && linkBase[4] > 0 && linkBase[4] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x1000) != 0 && linkBase[5] > 0 && linkBase[5] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x2000) != 0 && linkBase[6] > 0 && linkBase[6] <= 0x28) {
				matched = true;
			}
			if ((condBits & 0x4000) != 0 && linkBase[7] > 0 && linkBase[7] <= 0x28) {
				matched = true;
			}

			if ((!invert && !matched) || (invert && matched)) {
				continue;
			}
		}

		unsigned int cmpValue = 0;
		for (int i = 0; i < 4; i++) {
			const unsigned short cmpType = *reinterpret_cast<unsigned short*>(curLetter + 0x1E + i * 4);
			const unsigned short sourceType = (cmpType >> 11) & 3;
			const unsigned short sourceIdx = cmpType & 0x7FF;

			if (sourceType != 3) {
				if (sourceType == 1) {
					cmpValue = static_cast<unsigned int>(Game.m_gameWork.m_eventWork[sourceIdx + 4]);
				} else if (sourceType == 0) {
					if (sourceIdx == 0) {
						cmpValue = static_cast<unsigned int>(Game.m_gameWork.m_scriptSysVal0);
					} else if (sourceIdx == 1) {
						cmpValue = static_cast<unsigned int>(Game.m_gameWork.m_timerA);
					} else if (sourceIdx == 2) {
						cmpValue = static_cast<unsigned int>(Game.m_gameWork.m_scriptGlobalTime);
					} else if (sourceIdx == 3) {
						cmpValue = static_cast<unsigned int>(Game.m_gameWork.m_frameCounter);
					}
				} else if (sourceType == 2) {
					cmpValue = static_cast<unsigned int>(m_evtWordArr[sourceIdx]);
				}

				const unsigned short op = cmpType >> 13;
				const unsigned int compareValue = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(curLetter + 0x20 + i * 4));
				if (op == 0) {
					if (cmpValue != compareValue) {
						goto NextLetter;
					}
				} else if (op == 1) {
					if (cmpValue == compareValue) {
						goto NextLetter;
					}
				} else if (op == 2) {
					if (cmpValue < compareValue) {
						goto NextLetter;
					}
				} else if (op == 3) {
					if (compareValue < cmpValue) {
						goto NextLetter;
					}
				} else if (op == 4) {
					if (cmpValue <= compareValue) {
						goto NextLetter;
					}
				} else if (op == 5) {
					if (compareValue <= cmpValue) {
						goto NextLetter;
					}
				}
			}
		}

		{
			unsigned int bit0 = 0;
			unsigned int bit1 = 0;
			unsigned int bit2 = 0;
			unsigned char* evtWorkBytes = reinterpret_cast<unsigned char*>(m_evtWorkArr);

			for (int i = 0; i < 8; i++) {
				const unsigned short evtRule = *reinterpret_cast<unsigned short*>(curLetter + 0x2E + i * 2);
				const unsigned short sourceType = (evtRule >> 11) & 3;
				const unsigned short sourceIdx = evtRule & 0x7FF;
				unsigned int checkValue = bit0;

				if (sourceType == 3) {
					continue;
				}

				if (sourceType == 2) {
					bit0 = ((evtWorkBytes[sourceIdx >> 3] & (1 << (sourceIdx & 7))) != 0);
					bit1 = ((evtWorkBytes[(sourceIdx + 1) >> 3] & (1 << ((sourceIdx + 1) & 7))) != 0);
					bit2 = ((evtWorkBytes[(sourceIdx + 2) >> 3] & (1 << ((sourceIdx + 2) & 7))) != 0);
				} else if (sourceType == 1) {
					bit0 = ((static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[(sourceIdx >> 3) + 8]) &
							 (1 << (sourceIdx & 7))) != 0);
					bit1 = ((static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[((sourceIdx + 1) >> 3) + 8]) &
							 (1 << ((sourceIdx + 1) & 7))) != 0);
					bit2 = ((static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[((sourceIdx + 2) >> 3) + 8]) &
							 (1 << ((sourceIdx + 2) & 7))) != 0);
				}

				checkValue = bit0;

				switch (evtRule >> 13) {
				case 0:
				case 1:
					break;
				case 2:
					if (bit0 != 0) {
						goto NextLetter;
					}
					checkValue = bit2;
					if (bit1 != 0) {
						goto NextLetter;
					}
					break;
				case 3:
					if ((bit0 != 0) || (bit1 != 0)) {
						continue;
					}
					checkValue = bit2;
					break;
				case 4:
				case 5:
					checkValue = bit2;
					if (bit1 != 0) {
						goto NextLetter;
					}
					break;
				case 6:
				case 7:
					checkValue = bit2;
					if (bit1 == 0) {
						goto NextLetter;
					}
					break;
				default:
					continue;
				}

				if (checkValue == 0) {
					goto NextLetter;
				}
			}
		}

		if (foundCount == maxResults) {
			unsigned short minPriority = 0xFFFF;
			int replaceIndex = 0;
			for (int i = 0; i < maxResults; i++) {
				unsigned char* existing = reinterpret_cast<unsigned char*>(romLetterWork[i]);
				unsigned short priority = *reinterpret_cast<unsigned short*>(existing + 6) & 0xF00;
				if (priority < minPriority) {
					minPriority = priority;
					replaceIndex = i;
				}
			}

			const unsigned short curPriority = *reinterpret_cast<unsigned short*>(curLetter + 6) & 0xF00;
			if (minPriority < curPriority) {
				romLetterWork[replaceIndex] = reinterpret_cast<CRomLetterWork*>(curLetter);
			}
		} else {
			romLetterWork[foundCount] = reinterpret_cast<CRomLetterWork*>(curLetter);
			foundCount++;
		}

	NextLetter:;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a0628
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::ShopRequest(int requestType, int param3, int param4, int param5, int param6, int, int flags)
{
	switch (requestType) {
	case 0:
		m_shopListCount = 0;
		m_shopRequestState = 0;
		m_shopList[0] = 0;
		m_shopList[1] = 0;
		m_shopList[2] = 0;
		m_shopList[3] = 0;
		m_shopList[4] = 0;
		m_shopList[5] = 0;
		m_shopList[6] = 0;
		m_shopList[7] = 0;
		m_shopList[8] = 0;
		m_shopList[9] = 0;
		m_shopList[10] = 0;
		m_shopList[11] = 0;
		m_shopList[12] = 0;
		m_shopList[13] = 0;
		m_shopList[14] = 0;
		m_shopList[15] = 0;
		break;
	case 1: {
		short idx = m_shopListCount;
		m_shopListCount = idx + 1;
		m_shopList[idx] = (short)param3;
		break;
	}
	case 2:
		m_shopArg0 = param3;
		m_shopArg1 = param4;
		m_shopArg2 = param5;
		m_shopArg3 = param6;
		m_shopRequestFlags = (unsigned char)(flags & 1);
		break;
	case 3:
		m_shopParam = (short)param3;
		break;
	case 4:
		m_shopRequestState = 1;
		if (Game.m_gameWork.m_menuStageMode == 0) {
			GbaQue.SetShopFlg(m_joybusCaravanId);
		} else {
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		}
		break;
	case 5:
		m_shopRequestState = 2;
		if (Game.m_gameWork.m_menuStageMode == 0) {
			GbaQue.SetSmithFlg(m_joybusCaravanId);
		} else {
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		}
		break;
	default:
		break;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CallShop(int requestType, int arg0, int arg1, int arg2, int arg3)
{
	int local18;
	int local14;
	int local10;
	int localC;
	int local8;

	if ((requestType == 0) || (requestType == 1)) {
		m_shopRequestState = 0;
	}
	local18 = requestType;
	local14 = arg0;
	local10 = arg1;
	localC = arg2;
	local8 = arg3;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
		&CFlat, m_ownerObj, 2, 0x12, 5, &local18, (void*)0);
}

/*
 * --INFO--
 * PAL Address: 0x800a0210
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SafeDeleteTempItem()
{
	int totalSlots = 0;
	int artifactIndex = 0;

	if ((unsigned int)System.m_execParam > 2U) {
		System.Printf("");
	}

	for (int i = 0; i < 50; i++) {
		if (artifactIndex < 96 && (short)m_artifacts[artifactIndex] > 0) {
			unsigned short* artifactData =
				(unsigned short*)(Game.unkCFlatData0[2] + (short)m_artifacts[artifactIndex] * 0x48);
			if (artifactData[0] == 0xDB) {
				totalSlots += artifactData[3];
			}
		}

		if ((artifactIndex + 1) < 96 && (short)m_artifacts[artifactIndex + 1] > 0) {
			unsigned short* artifactData = (unsigned short*)(Game.unkCFlatData0[2] +
															 (short)m_artifacts[artifactIndex + 1] * 0x48);
			if (artifactData[0] == 0xDB) {
				totalSlots += artifactData[3];
			}
		}

		artifactIndex += 2;
	}

	totalSlots += (short)m_baseCmdListSlots;
	for (; totalSlots < 8; totalSlots++) {
		if ((short)m_commandListInventorySlotRef[totalSlots] >= 0) {
			m_commandListInventorySlotRef[totalSlots] = 0xFFFF;
			if ((unsigned int)System.m_execParam > 2U) {
				System.Printf("", totalSlots);
			}
		}
	}

	m_treasures[0] = 0xFFFF;
	m_treasures[1] = 0xFFFF;
	m_treasures[2] = 0xFFFF;
	m_treasures[3] = 0xFFFF;

	for (int i = 0; i < 64; i++) {
		unsigned short item = m_inventoryItems[i];
		if (((short)item > 0xFF) && ((short)item < 0x125) && item != 0xFFFF) {
			m_inventoryItems[i] = 0xFFFF;
			m_inventoryItemCount--;
		}
	}

	if ((short)m_commandListInventorySlotRef[2] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[2]] < 0) {
		m_commandListInventorySlotRef[2] = 0xFFFF;
	}
	if ((short)m_commandListInventorySlotRef[3] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[3]] < 0) {
		m_commandListInventorySlotRef[3] = 0xFFFF;
	}
	if ((short)m_commandListInventorySlotRef[4] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[4]] < 0) {
		m_commandListInventorySlotRef[4] = 0xFFFF;
	}
	if ((short)m_commandListInventorySlotRef[5] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[5]] < 0) {
		m_commandListInventorySlotRef[5] = 0xFFFF;
	}
	if ((short)m_commandListInventorySlotRef[6] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[6]] < 0) {
		m_commandListInventorySlotRef[6] = 0xFFFF;
	}
	if ((short)m_commandListInventorySlotRef[7] >= 0 &&
		(short)m_inventoryItems[(short)m_commandListInventorySlotRef[7]] < 0) {
		m_commandListInventorySlotRef[7] = 0xFFFF;
	}

	m_currentCmdListIndex = 0;
	m_weaponIdx = 0;
	memset(m_commandListExtra, 0, sizeof(m_commandListExtra));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::ClampStatus(short&, unsigned short&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CalcArtifactStatus(int, int, int&, int&, int&, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009fa44
 * PAL Size: 1996b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::CalcStatus()
{
	unsigned short* baseData = (unsigned short*)(Game.unkCFlatData0[0] + (m_baseDataIndex * 0x1D0));

	memcpy(m_elementResistances, m_romWorkPtr + 0x6F, 0x16);

	m_strength = baseData[4];
	m_baseStrength = m_strength;
	m_magic = baseData[5];
	m_baseMagic = m_magic;
	m_defense = baseData[6];
	m_baseDefense = m_defense;
	m_maxHp = baseData[3];

	m_equipEffectFlags = 0;
	m_numCmdListSlots = m_baseCmdListSlots;
	memset(m_equipEffectParams, 0, 7);

	if (m_tempStatBuffTimer != 0) {
		if (m_tempStatBuffId >= 0x185) {
			m_strength += *(short*)(Game.unk_flat3_field_8_0xc7dc + 0x6A);
		} else if (m_tempStatBuffId >= 0x180) {
			m_defense += *(short*)(Game.unk_flat3_field_8_0xc7dc + 0x6C);
		} else if (m_tempStatBuffId > 0x17C) {
			m_magic += *(short*)(Game.unk_flat3_field_8_0xc7dc + 0x6E);
		}
		m_tempStatBuffTimer--;
	}

	if (Game.m_gameWork.m_chaliceElement == 4) {
		m_elementResistances[3]++;
	} else if (Game.m_gameWork.m_chaliceElement < 4) {
		if (Game.m_gameWork.m_chaliceElement == 2) {
			m_elementResistances[2]++;
		} else if ((Game.m_gameWork.m_chaliceElement < 2) && (Game.m_gameWork.m_chaliceElement > 0)) {
			m_elementResistances[1]++;
		}
	} else if (Game.m_gameWork.m_chaliceElement == 8) {
		m_statusTimers[0]++;
		m_statusTimers[2]++;
	}

	short hpBonus = 0;
	short cmdBonus = 0;
	short strBonus = 0;
	short magBonus = 0;
	short defBonus = 0;
	unsigned short* artifact = &m_artifacts[0];
	for (int i = 0; i < 100; i++, artifact++) {
		if (*(short*)artifact > 0) {
			unsigned short* artifactData = GetItemDataPtr(*(short*)artifact);
			unsigned short artifactEffect = artifactData[0];
			short value = artifactData[3];

			if (artifactEffect == 0xDB) {
				cmdBonus += value;
			} else if (artifactEffect < 0xDB) {
				if (artifactEffect == 0xB6) {
					magBonus += value;
				} else if (artifactEffect < 0xB6) {
					if (artifactEffect == 0x9F) {
						strBonus += value;
					}
				} else if (artifactEffect == 0xCC) {
					defBonus += value;
				}
			} else if (artifactEffect == 0xE4) {
				hpBonus += value;
			} else if ((artifactEffect < 0xE4) && (artifactEffect == 0xDF)) {
				magBonus += value;
			}
		}
	}

	m_strength += strBonus;
	m_baseStrength += strBonus;
	m_magic += magBonus;
	m_baseMagic += magBonus;
	m_defense += defBonus;
	m_baseDefense += defBonus;
	m_numCmdListSlots += cmdBonus;
	m_maxHp += hpBonus;

	if ((short)m_numCmdListSlots > 8) {
		m_numCmdListSlots = 8;
	}
	if (m_maxHp > 0x10) {
		m_maxHp = 0x10;
	}

	for (int equipIdx = 0; equipIdx < 4; equipIdx++) {
		if (m_equipment[equipIdx] >= 0) {
			int itemIdx = (short)m_inventoryItems[m_equipment[equipIdx]];
			unsigned short* itemData = GetItemDataPtr(itemIdx);
			unsigned short itemType = itemData[0];

			if (itemType == 1) {
				int weaponItem = 0;
				int weaponRef = 0;
				GetCurrentWeaponItem(weaponItem, weaponRef);
				if (weaponItem > 0) {
					itemIdx = weaponItem;
					itemData = GetItemDataPtr(itemIdx);
				}
			}

			short itemValue = (short)itemData[3];
			if (itemType == 0x45) {
				m_defense += itemValue;
				m_baseDefense += itemValue;
			apply_effect:
				switch (itemData[4]) {
				case 1:
					m_elementResistances[1]++;
					break;
				case 2:
					m_elementResistances[2]++;
					break;
				case 3:
					m_elementResistances[3]++;
					break;
				case 4:
					m_elementResistances[4]++;
					break;
				case 5:
					m_elementResistances[5]++;
					break;
				case 6:
					m_statusTimers[0]++;
					break;
				case 7:
					m_statusTimers[1]++;
					break;
				case 8:
					m_statusTimers[2]++;
					break;
				case 9:
					m_equipEffectParams[0] += (char)itemValue;
					break;
				case 10:
					m_equipEffectParams[1] += (char)itemValue;
					break;
				case 0xB:
					m_equipEffectParams[2] += (char)itemValue;
					break;
				case 0xC:
					m_equipEffectParams[3] += (char)itemValue;
					break;
				case 0x10:
					m_equipEffectParams[4] += (char)itemValue;
					break;
				case 0x11:
					m_equipEffectParams[5] += (char)itemValue;
					break;
				case 0x12:
					m_equipEffectParams[6] += (char)itemValue;
					break;
				case 0x13:
					m_elementResistances[0]++;
					break;
				}
				m_equipEffectFlags |= 1 << itemData[4];
			} else if (itemType < 0x45) {
				if (itemType == 1) {
					m_strength += itemValue;
					m_baseStrength += itemValue;
				}
			} else if (itemType == 0x7F) {
				m_defense += itemValue;
				m_baseDefense += itemValue;
				goto apply_effect;
			}
		}
	}

	for (int i = 0; i < 11; i++) {
		if (m_elementResistances[i] > 2) {
			m_elementResistances[i] = 2;
		}
	}

	if (m_maxHp < m_hp) {
		m_hp = m_maxHp;
	}

	if (m_statusTimers[9] != 0) {
		float mul = GetStatusMultiplier(0x38);
		m_strength = (unsigned short)((float)m_strength * mul);
		m_magic = (unsigned short)((float)m_magic * mul);
		m_defense = (unsigned short)((float)m_defense * mul);
	}
	if (m_statusTimers[4] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x3E));
	}
	if (m_statusTimers[6] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x44));
	}

	if (m_strength > 99) {
		m_strength = 99;
	}
	if (m_defense > 99) {
		m_defense = 99;
	}
	if (m_magic > 99) {
		m_magic = 99;
	}
	if (m_baseStrength > 99) {
		m_baseStrength = 99;
	}
	if (m_baseDefense > 99) {
		m_baseDefense = 99;
	}
	if (m_baseMagic > 99) {
		m_baseMagic = 99;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009fa20
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::CanPlayerUseItem()
{
	return ((CGPartyObj*)m_ownerObj)->canPlayerUseItem();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::ValidCmdList(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009fa18
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetIdxCmdList()
{
	return m_currentCmdListIndex;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::SetIdxCmdList(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009fa10
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::IsUseCmdList(int cmdListIdx)
{
	m_currentCmdListIndex = cmdListIdx;
}

/*
 * --INFO--
 * PAL Address: 0x8009f9dc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::IsSelectedCmdList(int cmdListIdx)
{
	unsigned int isInvalid = 0;
	short slotRef = m_commandListInventorySlotRef[cmdListIdx];

	if ((cmdListIdx >= 2) && (slotRef == -1)) {
		isInvalid = 1;
	}
	return ((unsigned int)__cntlzw((unsigned char)isInvalid)) >> 5;
}

/*
 * --INFO--
 * PAL Address: 0x8009f890
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::GetMagicCharge(int cmdListIdx, int& groupedCount, int& isSelected)
{
	unsigned int isInvalid = 0;
	if ((cmdListIdx >= 2) && (m_commandListInventorySlotRef[cmdListIdx] == -1)) {
		isInvalid = 1;
	}

	if ((((unsigned int)__cntlzw((unsigned char)isInvalid)) >> 5) == 0) {
		groupedCount = 0;
		isSelected = 0;
		return;
	}

	groupedCount = 1;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		short* slotRef = m_commandListExtra + cmdListIdx;
		if (slotRef[0] != 0) {
			int scanCount = cmdListIdx + 1;
			int topIdx = cmdListIdx;
			if (cmdListIdx >= 0) {
				do {
					if (slotRef[0] != -1) {
						break;
					}
					slotRef--;
					topIdx--;
					scanCount--;
				} while (scanCount != 0);
			}

			groupedCount = 1;
			scanCount = m_numCmdListSlots - (topIdx + 1);
			slotRef = m_commandListExtra + topIdx + 1;
			if ((topIdx + 1) < m_numCmdListSlots) {
				do {
					if (slotRef[0] != -1) {
						break;
					}
					groupedCount++;
					slotRef++;
					scanCount--;
				} while (scanCount != 0);
			}
		}
	}

	if (groupedCount == 1) {
		isSelected = (((unsigned int)__cntlzw(cmdListIdx - m_currentCmdListIndex)) >> 5) & 0xFF;
		return;
	}

	int scanCount = cmdListIdx + 1;
	short* slotRef = m_commandListExtra + cmdListIdx;
	if (cmdListIdx >= 0) {
		do {
			if (slotRef[0] != -1) {
				break;
			}
			slotRef--;
			cmdListIdx--;
			scanCount--;
		} while (scanCount != 0);
	}

	unsigned int selected = 0;
	if ((cmdListIdx <= m_currentCmdListIndex) &&
		(m_currentCmdListIndex <= (cmdListIdx + groupedCount - 1))) {
		selected = 1;
	}
	isSelected = selected;
}

extern "C" int GetCmdListItemName__12CCaravanWorkFi(CCaravanWork* caravanWork, int cmdListIdx, int* firstCmdIdx, int* itemCmdListIdx)
{
	int groupedCount = 1;

	if (Game.m_gameWork.m_menuStageMode != 0) {
		short* slotRef = caravanWork->m_commandListInventorySlotRef + cmdListIdx;
		if (slotRef[0] != 0) {
			int scanCount = cmdListIdx + 1;
			int topIdx = cmdListIdx;
			if (cmdListIdx >= 0) {
				do {
					if (slotRef[0] != 0xFFFF) {
						break;
					}
					slotRef--;
					topIdx--;
					scanCount--;
				} while (scanCount != 0);
			}

			groupedCount = 1;
			scanCount = caravanWork->m_numCmdListSlots - (topIdx + 1);
			slotRef = caravanWork->m_commandListInventorySlotRef + topIdx + 1;
			if ((topIdx + 1) < caravanWork->m_numCmdListSlots) {
				do {
					if (slotRef[0] != 0xFFFF) {
						break;
					}
					groupedCount++;
					slotRef++;
					scanCount--;
				} while (scanCount != 0);
			}
		}
	}

	if (groupedCount > 1) {
		int scanCount = cmdListIdx + 1;
		short* slotRef = caravanWork->m_commandListInventorySlotRef + cmdListIdx;
		if (cmdListIdx >= 0) {
			do {
				if (slotRef[0] != 0xFFFF) {
					break;
				}
				slotRef--;
				cmdListIdx--;
				scanCount--;
			} while (scanCount != 0);
		}

		short cmdId = caravanWork->m_commandListExtra[cmdListIdx];
		if (cmdId == 0x207 || cmdId == 0x20B || cmdId == 0x20F) {
			*firstCmdIdx = cmdListIdx;
			for (int i = 0; i < groupedCount; i++) {
				short invSlot = (short)caravanWork->m_commandListInventorySlotRef[cmdListIdx + i];
				short itemId = (short)caravanWork->m_inventoryItems[invSlot];
				if (*(short*)(Game.unkCFlatData0[2] + itemId * 0x48) == 1) {
					*itemCmdListIdx = cmdListIdx + i;
					return 1;
				}
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8009f6ac
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetWeaponAttrib(int cmdListIdx)
{
	int weaponType = GetCmdListItem(cmdListIdx);
	if (weaponType < 0 || weaponType > 2) {
		int itemId = DelCmdListAndItem(cmdListIdx, 0);
		const GobjworkFlatData* flatData = reinterpret_cast<const GobjworkFlatData*>(&Game.m_cFlatDataArr[1]);
		return reinterpret_cast<int>(flatData->table[0].index[itemId * 5 + 4]);
	}

	return GetSkillStr__8CMenuPcsFi(&MenuPcs, weaponType);
}

/*
 * --INFO--
 * PAL Address: 0x8009f618
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetCmdListItem(int cmdListIdx)
{
	int cmdTopIdx;
	int itemCmdListIdx;

	if (GetCmdListItemName__12CCaravanWorkFi(this, cmdListIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
		short cmdId = m_commandListExtra[cmdTopIdx];
		if (cmdId == 0x207) {
			return 0;
		}
		if (cmdId == 0x20B) {
			return 1;
		}
		if (cmdId == 0x20F) {
			return 2;
		}
	}
	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8009f458
 * PAL Size: 448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::DelCmdListAndItem(int cmdListIdx, int)
{
	int result;
	short* cmdListSlot = reinterpret_cast<short*>(m_commandListInventorySlotRef) + cmdListIdx;

	if (cmdListIdx == 0) {
		if (m_equipment[0] < 0) {
			result = 0;
		} else {
			result = (short)m_inventoryItems[m_equipment[0]];
		}
	} else if (cmdListIdx == 1) {
		if (m_equipment[2] < 0) {
			result = 0;
		} else {
			result = (short)m_inventoryItems[m_equipment[2]];
		}
	} else {
		int numGrouped;
		if (Game.m_gameWork.m_menuStageMode == 0 || cmdListSlot[0] == 0) {
			numGrouped = 1;
		} else {
			int scanCount = cmdListIdx + 1;
			int topIdx = cmdListIdx;
			if (cmdListIdx >= 0) {
				do {
					if (cmdListSlot[0] != -1) {
						break;
					}
					cmdListSlot--;
					topIdx--;
					scanCount--;
				} while (scanCount != 0);
			}

			numGrouped = 1;
			scanCount = (short)m_numCmdListSlots - (topIdx + 1);
			cmdListSlot = reinterpret_cast<short*>(m_commandListInventorySlotRef) + topIdx + 1;
			if ((topIdx + 1) < (short)m_numCmdListSlots) {
				do {
					if (cmdListSlot[0] != -1) {
						break;
					}
					numGrouped++;
					cmdListSlot++;
					scanCount--;
				} while (scanCount != 0);
			}
		}

		if (numGrouped < 2) {
			if (*cmdListSlot < 0) {
				result = 0;
			} else {
				result = (short)m_inventoryItems[*cmdListSlot];
			}
		} else {
			int scanCount = cmdListIdx + 1;
			cmdListSlot = reinterpret_cast<short*>(m_commandListInventorySlotRef) + cmdListIdx;
			if (cmdListIdx >= 0) {
				do {
					if (cmdListSlot[0] != -1) {
						break;
					}
					cmdListSlot--;
					cmdListIdx--;
					scanCount--;
				} while (scanCount != 0);
			}

			short cmdResult = m_commandListExtra[cmdListIdx];
			int cmdTopIdx;
			int itemCmdListIdx;
			if (GetCmdListItemName__12CCaravanWorkFi(this, cmdListIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
				cmdResult = (short)m_inventoryItems[(short)m_commandListInventorySlotRef[itemCmdListIdx]];
			}
			result = cmdResult;
		}
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::SearchCombiTop(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009f384
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::GetNumCombi(int cmdListIdx, int updateJoybus)
{
	short nextCmdIdx = 0;
	if (m_currentCmdListIndex == cmdListIdx) {
		nextCmdIdx = GetNextCmdListIdx(cmdListIdx, 1);
	}

	short inventorySlot = m_commandListInventorySlotRef[cmdListIdx];
	if (m_inventoryItems[inventorySlot] != 0xFFFF) {
		m_inventoryItems[inventorySlot] = 0xFFFF;
		m_inventoryItemCount = static_cast<short>(m_inventoryItemCount - 1);
		if (updateJoybus != 0) {
			DelItem__6JoyBusFiUc(&Joybus, m_joybusCaravanId, static_cast<char>(inventorySlot));
		}
	}

	m_commandListInventorySlotRef[cmdListIdx] = 0xFFFF;
	if (updateJoybus != 0) {
		Joybus.SetCmdLst(m_joybusCaravanId, cmdListIdx, -1);
	}

	if (m_currentCmdListIndex == cmdListIdx) {
		m_currentCmdListIndex = nextCmdIdx;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009f2a4
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetNextCmdListIdx(int cmdListIdx, int dir)
{
	while (true) {
		int prev = cmdListIdx;
		cmdListIdx = prev + dir;

		if (cmdListIdx < 0) {
			cmdListIdx += m_numCmdListSlots;
		} else if (cmdListIdx > m_numCmdListSlots - 1) {
			cmdListIdx -= m_numCmdListSlots;
		}

		if (Game.m_gameWork.m_menuStageMode != 0) {
			if (m_commandListExtra[cmdListIdx] == -1) {
				continue;
			}
			if (dir == -1 && m_commandListExtra[cmdListIdx] == -1) {
				if (0 < m_commandListExtra[prev]) {
					continue;
				}
			}
		}

		int item = DelCmdListAndItem(cmdListIdx, 0);
		if (cmdListIdx < 2 || item > 0) {
			return cmdListIdx;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009f280
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::CanPlayerPutItem()
{
	return ((CGPartyObj*)m_ownerObj)->canPlayerPutItem();
}

/*
 * --INFO--
 * PAL Address: 0x8009F1FC
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::GetCurrentWeaponItem(int& weaponItem, int& weaponRef)
{
	short weaponIdx = m_weaponIdx;
	if (weaponIdx == 0) {
		int activeWeapon = 0;
		weaponItem = 0;
		int ownerWorkAddr = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x58);
		int equippedSlot = *reinterpret_cast<short*>(ownerWorkAddr + 0xAC);
		if (equippedSlot >= 0) {
			activeWeapon = *reinterpret_cast<short*>(ownerWorkAddr + equippedSlot * 2 + 0xB6);
		}
		weaponRef = activeWeapon;
		return;
	}

	if (weaponIdx != 1) {
		weaponItem = weaponIdx;
		CCaravanWork* ownerWork = *reinterpret_cast<CCaravanWork**>(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x58);
		weaponRef = ownerWork->DelCmdListAndItem(weaponIdx, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009f1d8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SetCurrentWeaponIdx(int weaponIdx)
{
	m_weaponIdx = (short)weaponIdx;
	CheckAndResetCurrentWeaponIdx(weaponIdx);
}

/*
 * --INFO--
 * PAL Address: 0x8009f178
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::CheckAndResetCurrentWeaponIdx(int)
{
	short weaponIdx = m_weaponIdx;
	int reset = 0;
	int weaponItem = DelCmdListAndItem(weaponIdx, reset);
	if ((0 < weaponItem) && (*GetItemDataPtr(weaponItem) == 1)) {
		return;
	}

	m_currentCmdListIndex = 0;
	m_weaponIdx = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8009ED78
 * PAL Size: 1024b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::SortBeforeReturnWorldMap()
{
	memset(m_commandListExtra, 0, sizeof(m_commandListExtra));

	for (int i = 0; i < 0x3F; i++) {
		for (int j = i + 1; j < 0x40; j++) {
			unsigned short lhs = m_inventoryItems[i];
			unsigned short rhs = m_inventoryItems[j];

			if (static_cast<short>(lhs) < 1) {
				if (static_cast<short>(rhs) > 0) {
					m_inventoryItems[i] = rhs;
					m_inventoryItems[j] = 0xFFFF;

					for (int slot = 2; slot < 8; slot++) {
						if (static_cast<short>(m_commandListInventorySlotRef[slot]) == j) {
							m_commandListInventorySlotRef[slot] = static_cast<unsigned short>(i);
						}
					}

					for (int equip = 0; equip < 4; equip++) {
						if (m_equipment[equip] == j) {
							m_equipment[equip] = static_cast<short>(i);
						}
					}
				}
			} else if ((static_cast<short>(rhs) > 0) && (static_cast<short>(rhs) < static_cast<short>(lhs))) {
				m_inventoryItems[i] = rhs;
				m_inventoryItems[j] = lhs;

				for (int slot = 2; slot < 8; slot++) {
					short cur = static_cast<short>(m_commandListInventorySlotRef[slot]);
					if (cur == i) {
						m_commandListInventorySlotRef[slot] = static_cast<unsigned short>(j);
					} else if (cur == j) {
						m_commandListInventorySlotRef[slot] = static_cast<unsigned short>(i);
					}
				}

				for (int equip = 0; equip < 4; equip++) {
					if (m_equipment[equip] == i) {
						m_equipment[equip] = static_cast<short>(j);
					} else if (m_equipment[equip] == j) {
						m_equipment[equip] = static_cast<short>(i);
					}
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009ec2c
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::BackupTutorialItem(int mode)
{
	if (mode == 0) {
		memcpy(m_inventoryItems, m_backupInventoryBlock, 0x148);
		m_inventoryItemCount = m_backupInventoryItemCount;
		memcpy(m_commandListInventorySlotRef, m_backupCommandListInventorySlotRef, 0x10);
		memcpy(m_commandListExtra, m_backupCmdlistExtra, 0x10);
		memcpy(m_equipment, m_backupEquipment, 8);
		m_gil = m_backupGil;
		m_currentCmdListIndex = m_backupCurrentCmdListIndex;
		m_weaponIdx = m_backupWeaponIdx;
	} else {
		memcpy(m_backupInventoryBlock, m_inventoryItems, 0x148);
		memset(m_inventoryItems, 0xFF, 0x148);
		m_backupInventoryItemCount = m_inventoryItemCount;
		m_inventoryItemCount = 0;
		memcpy(m_backupCommandListInventorySlotRef, m_commandListInventorySlotRef, 0x10);
		memset(m_commandListInventorySlotRef, 0xFF, 0x10);
		memcpy(m_backupCmdlistExtra, m_commandListExtra, 0x10);
		memset(m_commandListExtra, 0, 0x10);
		memcpy(m_backupEquipment, m_equipment, 8);
		memset(m_equipment, 0xFF, 8);
		m_backupGil = m_gil;
		m_gil = 0;
		m_backupCurrentCmdListIndex = m_currentCmdListIndex;
		m_currentCmdListIndex = 0;
		m_backupWeaponIdx = m_weaponIdx;
		m_weaponIdx = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009eb94
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::UniteComList(int startIdx, int count, int cmdId)
{
	for (int i = 0; i < count; i++) {
		short value = -1;
		if (i == 0) {
			value = (short)cmdId;
		}
		m_commandListExtra[startIdx + i] = value;
	}

	if ((startIdx <= m_weaponIdx) && (m_weaponIdx < (startIdx + count))) {
		int cmdTopIdx;
		int itemCmdListIdx;
		if (GetCmdListItemName__12CCaravanWorkFi(this, startIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
			m_weaponIdx = (short)itemCmdListIdx;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009ea48
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::UnuniteComList(int startIdx, int count)
{
	if (m_weaponIdx == startIdx) {
		int cmdTopIdx;
		int itemCmdListIdx;
		if (GetCmdListItemName__12CCaravanWorkFi(this, startIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
			m_weaponIdx = (short)itemCmdListIdx;
		}
	}

	for (int i = 0; i < count; i++) {
		m_commandListExtra[startIdx + i] = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009e1c0
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::GetArtifactIncludeHpMax()
{
	CGObjWork* gObjWork = this;
	CCaravanWork* artifactWork = this;
	int hpMax = 0;
	int artifactIndex = 0;
	int count = 0x32;

	do {
		if ((artifactIndex < 0x60) && ((short)artifactWork->m_artifacts[0] > 0)) {
			unsigned short* artifactData = GetItemDataPtr((short)artifactWork->m_artifacts[0]);
			unsigned short artifactType = artifactData[0];

			if (artifactType == 0xDB) {
			} else if (artifactType < 0xDB) {
				if (artifactType == 0xB6) {
				} else if (artifactType < 0xB6) {
					if (artifactType == 0x9F) {
					}
				} else if (artifactType == 0xCC) {
				}
			} else if (artifactType == 0xE4) {
				hpMax += artifactData[3];
			} else if ((artifactType < 0xE4) && (artifactType == 0xDF)) {
			}
		}

		artifactIndex++;
		if ((artifactIndex < 0x60) && ((short)artifactWork->m_artifacts[1] > 0)) {
			unsigned short* artifactData = GetItemDataPtr((short)artifactWork->m_artifacts[1]);
			unsigned short artifactType = artifactData[0];

			if (artifactType == 0xDB) {
			} else if (artifactType < 0xDB) {
				if (artifactType == 0xB6) {
				} else if (artifactType < 0xB6) {
					if (artifactType == 0x9F) {
					}
				} else if (artifactType == 0xCC) {
				}
			} else if (artifactType == 0xE4) {
				hpMax += artifactData[3];
			} else if ((artifactType < 0xE4) && (artifactType == 0xDF)) {
			}
		}

		artifactWork = (CCaravanWork*)&artifactWork->m_objType;
		artifactIndex++;
		count--;
	} while (count != 0);

	hpMax += *(unsigned short*)(Game.unkCFlatData0[0] + gObjWork->m_baseDataIndex * 0x1D0 + 6);
	if (hpMax > 0xF) {
		return 0x10;
	}
	return hpMax;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMonWork::CMonWork()
{ 
	m_objType = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8009e9b4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMonWork* dtor_8009E9B4(CMonWork* monWork, short shouldDelete)
{
	if (monWork != 0) {
		*(void**)monWork = __vt__8CMonWork;
		if (monWork != 0) {
			*(void**)monWork = __vt__9CGObjWork;
		}
		if (0 < shouldDelete) {
			__dl__FPv(monWork);
		}
	}

	return monWork;
}

/*
 * --INFO--
 * PAL Address: 0x8009e678
 * PAL Size: 828b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMonWork::Init(int baseDataIndex, CRomWork* romWork, int)
{
	unsigned short* romData = reinterpret_cast<unsigned short*>(romWork);
	int stageRank;
	unsigned int memberCount;

	m_baseDataIndex = baseDataIndex;
	m_id = romData[0];
	m_param1 = romData[1];
	m_param2 = romData[2];
	m_maxHp = romData[3];
	m_strength = romData[4];
	m_magic = romData[5];
	m_defense = romData[6];
	m_romWorkPtr = romData + 8;

	memcpy(m_elementResistances, m_romWorkPtr + 0x6F, 0x16);
	memset(m_statusTimers + 3, 0, 0x4E);
	memset(m_statusValues, 0xFF, sizeof(m_statusValues));
	m_hp = m_maxHp;

	memcpy(unk_0xac, romData + 0x56, 8);
	memcpy(unk_0xb4, romData + 0x5A, 0x1C);
	memset(unk_0xd0, 0, 0x20);
	memset(unk_0xf0, 0, 0x20);

	if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		stageRank = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
		if (stageRank > 2) {
			stageRank = 2;
		}
	} else {
		stageRank = 0;
	}

	if (stageRank > 0) {
		m_maxHp = (unsigned short)((float)m_maxHp * GetStatusMultiplier(stageRank * 2 + 0x44));
	}

	memberCount = (unsigned int)(Game.m_gameWork.m_wmBackupParams[0] >= 0);
	if (Game.m_gameWork.m_wmBackupParams[1] >= 0) {
		memberCount++;
	}
	if (Game.m_gameWork.m_wmBackupParams[2] >= 0) {
		memberCount++;
	}
	if (Game.m_gameWork.m_wmBackupParams[3] >= 0) {
		memberCount++;
	}

	if (Game.m_gameWork.m_menuStageMode != 0) {
		memberCount = 1;
	}

	if (memberCount > 1) {
		m_maxHp = (unsigned short)((float)m_maxHp * GetStatusMultiplier((int)(memberCount * 2 + 0x5E)));
	}

	if ((Game.m_gameWork.m_scriptSysVal0 == 1) && (Game.m_gameWork.m_bossArtifactStageIndex < 0xF)) {
		m_maxHp = (unsigned short)((float)m_maxHp * ((((float)(*(unsigned short*)(Game.m_bossArtifactBase +
			Game.m_gameWork.m_bossArtifactStageIndex * 0x168 + 0x60))) * 0.01f) + 1.0f));
	}

	m_hp = m_maxHp;
}

/*
 * --INFO--
 * PAL Address: 0x8009e2fc
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMonWork::CalcStatus()
{
	unsigned short* baseData = reinterpret_cast<unsigned short*>(Game.unkCFlatData0[1] + (m_baseDataIndex * 0x1D0));

	memcpy(m_elementResistances, m_romWorkPtr + 0x6F, 0x16);

	m_strength = baseData[4];
	m_magic = baseData[5];
	m_defense = baseData[6];

	int stageRank = 0;
	if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		stageRank = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
		if (stageRank > 2) {
			stageRank = 2;
		}
	}

	if (stageRank > 0) {
		const int stageOffset = stageRank * 2;
		m_strength = (unsigned short)((float)m_strength * GetStatusMultiplier(stageOffset + 0x48));
		m_magic = (unsigned short)((float)m_magic * GetStatusMultiplier(stageOffset + 0x4C));
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(stageOffset + 0x50));
	}

	if (m_statusTimers[9] != 0) {
		const float mul = GetStatusMultiplier(0x38);
		m_strength = (unsigned short)((float)m_strength * mul);
		m_magic = (unsigned short)((float)m_magic * mul);
		m_defense = (unsigned short)((float)m_defense * mul);
	}

	if (m_statusTimers[4] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x3E));
	}

	if (m_statusTimers[6] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x44));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetEvtFlag(int)
{
	// TODO
}
