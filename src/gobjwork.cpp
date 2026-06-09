#include "ffcc/gobjwork.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/gbaque.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/partyobj.h"
#include "ffcc/mes.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/system.h"
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern const float kGObjWorkStatusScaleBase;
extern const float kGObjWorkStatusScaleStep;
extern const float kCaravanShoukiLimitScale[2] = {0.95f, 0.0f};

namespace {
static inline unsigned short* GetItemDataPtr(int itemIdx)
{
	return (unsigned short*)(Game.unkCFlatData0[2] + (itemIdx * 0x48));
}

struct ShoukiByteFlags {
	int upper : 1;
	unsigned int pad0 : 2;
	int middle : 1;
};

static inline float GetStatusMultiplier(int offset)
{
	return ((float)(*(unsigned short*)(Game.unk_flat3_field_8_0xc7dc + offset)) * kGObjWorkStatusScaleStep) +
		   kGObjWorkStatusScaleBase;
}
}

STATIC_ASSERT(offsetof(CRomLetterWork, m_priorityFlags) == 0x06);
STATIC_ASSERT(offsetof(CRomLetterWork, m_personalConditions) == 0x18);
STATIC_ASSERT(offsetof(CRomLetterWork, m_linkConditions) == 0x1A);
STATIC_ASSERT(offsetof(CRomLetterWork, m_linkValueConditions) == 0x1C);
STATIC_ASSERT(offsetof(CRomLetterWork, m_compareRules) == 0x1E);
STATIC_ASSERT(offsetof(CRomLetterWork, m_eventRules) == 0x2E);

extern char sWorldMapSortFormatBlock[];
static const char sNoWorldReturnItemWarning[] = {
	(char)0x83, (char)0x8F, (char)0x81, (char)0x5B, (char)0x83, (char)0x8B, (char)0x83, (char)0x68,
	(char)0x82, (char)0xC9, (char)0x8C, (char)0x4A, (char)0x82, (char)0xE8, (char)0x89, (char)0x7A,
	(char)0x82, (char)0xB9, (char)0x82, (char)0xC8, (char)0x82, (char)0xA2, (char)0x83, (char)0x41,
	(char)0x83, (char)0x43, (char)0x83, (char)0x65, (char)0x83, (char)0x80, (char)0x82, (char)0xF0,
	(char)0x8D, (char)0xED, (char)0x8F, (char)0x9C, (char)0x82, (char)0xB5, (char)0x82, (char)0xDC,
	(char)0x82, (char)0xB7, (char)0x81, (char)0x42, (char)0x0A, 0x00, 0x00, 0x00
};
static const char sTempArtifactIndexWarning[] = {
	(char)0x83, (char)0x65, (char)0x83, (char)0x93, (char)0x83, (char)0x7C, (char)0x83, (char)0x89,
	(char)0x83, (char)0x8A, (char)0x83, (char)0x41, (char)0x81, (char)0x5B, (char)0x83, (char)0x65,
	(char)0x83, (char)0x42, (char)0x83, (char)0x74, (char)0x83, (char)0x40, (char)0x83, (char)0x4E,
	(char)0x83, (char)0x67, (char)0x82, (char)0xC9, (char)0x82, (char)0xE6, (char)0x82, (char)0xC1,
	(char)0x82, (char)0xC4, (char)0x91, (char)0x9D, (char)0x89, (char)0xC1, (char)0x82, (char)0xB5,
	(char)0x82, (char)0xC4, (char)0x82, (char)0xA2, (char)0x82, (char)0xBD, (char)0x63, (char)0x6F,
	(char)0x6D, (char)0x6C, (char)0x69, (char)0x73, (char)0x74, (char)0x3D, (char)0x25, (char)0x64,
	(char)0x82, (char)0xCC, (char)0x83, (char)0x43, (char)0x83, (char)0x93, (char)0x83, (char)0x66,
	(char)0x83, (char)0x62, (char)0x83, (char)0x4E, (char)0x83, (char)0x58, (char)0x82, (char)0xCC,
	(char)0x82, (char)0xDD, (char)0x82, (char)0xF0, (char)0x8D, (char)0xED, (char)0x8F, (char)0x9C,
	(char)0x82, (char)0xB5, (char)0x82, (char)0xDC, (char)0x82, (char)0xB5, (char)0x82, (char)0xBD,
	(char)0x81, (char)0x42, (char)0x0A, 0x00
};
static const char sUnnamedItemName[] = {
	(char)0x81, (char)0x69, (char)0x82, (char)0xC8, (char)0x82, (char)0xDC, (char)0x82, (char)0xA6,
	(char)0x82, (char)0xC8, (char)0x82, (char)0xB5, (char)0x81, (char)0x6A, 0x00, 0x00
};

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
	m_baseDataIndex = baseDataIndex;
	m_id = romWork->m_id + idOffset;
	m_param1 = romWork->m_param1;
	m_param2 = romWork->m_param2;
	m_maxHp = romWork->m_maxHp;
	m_strength = romWork->m_strength;
	m_magic = romWork->m_magic;
	m_defense = romWork->m_defense;
	m_romWork = romWork->Data();

	memcpy(RomStatusBlock(), (m_romWork + CRomWork::ElementResistanceOffset), RomStatusBlockHalfwordCount * sizeof(unsigned short));
	memset(m_statusTimers + 3, 0, sizeof(m_statusTimers) - 3 * sizeof(m_statusTimers[0]));
	m_statusValues[0] = 0xFFFF;
	m_statusValues[1] = 0xFFFF;
	m_statusValues[2] = 0xFFFF;
	m_statusValues[3] = 0xFFFF;
	m_statusValues[4] = 0xFFFF;
	m_statusValues[5] = 0xFFFF;
	m_statusValues[6] = 0xFFFF;
	m_statusValues[7] = 0xFFFF;
	m_statusValues[8] = 0xFFFF;
	m_statusValues[9] = 0xFFFF;
	m_statusValues[10] = 0xFFFF;
	m_statusValues[11] = 0xFFFF;
	m_statusValues[12] = 0xFFFF;
	m_statusValues[13] = 0xFFFF;
	m_statusValues[14] = 0xFFFF;
	m_statusValues[15] = 0xFFFF;
	m_hp = m_maxHp;
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
CGObjWork::~CGObjWork()
{
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
	sprintf((char*)m_name, const_cast<char*>(sUnnamedItemName));
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
 * PAL Address: 0x800a2b9c
 * PAL Size: 92b
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
	unk_0x3c8 = 0;
	m_equipment[0] = -1;
	m_equipment[1] = -1;
	m_equipment[2] = -1;
	m_equipment[3] = -1;
	m_inventoryItemCount = 0;
	memset(m_inventoryItems, 0xFF, sizeof(m_backupInventoryBlock));
	memset(m_evtWorkArr, 0, sizeof(m_evtWorkArr));
	memset(m_evtWordArr, 0, sizeof(m_evtWordArr));
	m_tempStatBuffTimer = 0;
	m_tempStatBuffId = 0;
	unk_0x3e6 = 0;
	m_evtState0 = 0;
	m_evtState1 = 0;
	memset(m_commandListInventorySlotRef, 0xFF, sizeof(m_commandListInventorySlotRef));
	memset(m_commandListExtra, 0, sizeof(m_commandListExtra));
	memset(&m_bonusCondition, 0, 1);
	memset(m_equipEffectParams, 0, sizeof(m_equipEffectParams) - sizeof(m_equipEffectParams[0]));
	memset(&m_shopBusyFlag, 0, 1);
	memset(&m_caravanLocalFlags, 0, 1);
	m_inventoryItemCount = 0;
	memset(m_inventoryItems, 0xFF, sizeof(m_backupInventoryBlock));
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
	sprintf((char*)m_name, const_cast<char*>(sUnnamedItemName));
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
	m_romWork = reinterpret_cast<unsigned short*>(game->unkCFlatData0[0] + (m_baseDataIndex * 0x1D0) + 0x10);
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
	int value = 0;

	m_baseDataIndex = baseDataIndex;
	m_id = romWork->m_id + idOffset;
	m_param1 = romWork->m_param1;
	m_param2 = romWork->m_param2;
	m_maxHp = romWork->m_maxHp;
	m_strength = romWork->m_strength;
	m_magic = romWork->m_magic;
	m_defense = romWork->m_defense;
	m_romWork = romWork->Data();
	memcpy(RomStatusBlock(), (m_romWork + CRomWork::ElementResistanceOffset), RomStatusBlockHalfwordCount * sizeof(unsigned short));
	memset(m_statusTimers + 3, 0, sizeof(m_statusTimers) - 3 * sizeof(m_statusTimers[0]));
	m_statusValues[0] = 0xFFFF;
	m_statusValues[1] = 0xFFFF;
	m_statusValues[2] = 0xFFFF;
	m_statusValues[3] = 0xFFFF;
	m_statusValues[4] = 0xFFFF;
	m_statusValues[5] = 0xFFFF;
	m_statusValues[6] = 0xFFFF;
	m_statusValues[7] = 0xFFFF;
	m_statusValues[8] = 0xFFFF;
	m_statusValues[9] = 0xFFFF;
	m_statusValues[10] = 0xFFFF;
	m_statusValues[11] = 0xFFFF;
	m_statusValues[12] = 0xFFFF;
	m_statusValues[13] = 0xFFFF;
	m_statusValues[14] = 0xFFFF;
	m_statusValues[15] = 0xFFFF;
	m_hp = m_maxHp;
	m_shopState = 1;

	value = (int)m_id - 100;
	m_tribeId = value / 200;

	value = (int)m_id - 100;
	m_genderFlag = (value / 100) & 1;

	clearCaravanWork();
	m_bonusCondition = 0;
	memset(m_artifactRelated, 0, sizeof(m_artifactRelated));
	m_artifactRelated[3] = Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex]
								.m_entries[8]
								.m_values[1];
	m_artifactRelated[4] = Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex]
								.m_entries[8]
								.m_values[2];
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
		Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex].m_entries[bonusCondition + 8]
			.m_values[1];
	m_artifactRelated[4] =
		Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex].m_entries[bonusCondition + 8]
			.m_values[2];
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
	unsigned char result = 0;
	void* ownerObj = m_ownerObj;

	if (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(ownerObj) + 0x5BC) >
		kCaravanShoukiLimitScale[0] * Game.unkFloat_0xca10) {
		if (m_hp != 0) {
			unsigned char cflatFlag = CFlatGameFlags();
			if (((char)(((int)(((unsigned int)cflatFlag << 24) & 0xC0000000)) >> 31) != 0 ||
				 (char)(((int)(((unsigned int)cflatFlag << 27) & 0xC0000000)) >> 31) != 0) &&
				(char)(((int)((((unsigned int) * (unsigned char*)(reinterpret_cast<unsigned char*>(ownerObj) + 0x9B))
							   << 24) &
							  0xC0000000)) >>
					   31) != 0) {
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
void CCaravanWork::AddLetter(int letterType, int senderId, int moneyValue, int hasMoneyFlag, int hasReplyFlag,
							 int itemA, int itemB, int itemC, int itemD)
{
	for (int i = 99; i > 0; i--) {
		m_letters[i] = m_letters[i - 1];
	}

	memset(&m_letters[0], 0, sizeof(m_letters[0]));
	m_letters[0].SetMessageType(letterType);
	m_letters[0].m_words.m_word0 = (m_letters[0].m_words.m_word0 & 0xFFFC01FF) | ((senderId & 0x1FF) << 9);
	m_letters[0].SetFlags((m_letters[0].Flags() & ~8) | ((hasMoneyFlag << 3) & 8));
	int attachmentValue;
	if (m_letters[0].AttachmentIsGil()) {
		attachmentValue = moneyValue / 100;
	} else {
		attachmentValue = moneyValue;
	}
	m_letters[0].SetAttachmentValue(attachmentValue);
	m_letters[0].FlagsBits().m_opened = 0;
	m_letters[0].FlagsBits().m_attachmentClaimed = 0;
	m_letters[0].FlagsBits().m_replySent = 0;
	m_letters[0].FlagsBits().m_hasReply = hasReplyFlag;
	m_letters[0].m_half.m_tempVars[0] = static_cast<unsigned short>(itemA);
	m_letters[0].m_half.m_tempVars[1] = static_cast<unsigned short>(itemB);
	m_letters[0].m_half.m_tempVars[2] = static_cast<unsigned short>(itemC);
	m_letters[0].m_half.m_tempVars[3] = static_cast<unsigned short>(itemD);

	int nextCount = m_letterCount + 1;
	int letterCount = 100;
	if (nextCount < 100) {
		letterCount = nextCount;
	}
	m_letterCount = letterCount;

	GbaQue.SetAddLetter(m_joybusCaravanId);
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
	CLetterWork* letter = &m_letters[letterIdx];
	CFlatRuntime::CStack stack[2];

	stack[0].m_word = letter->MessageType();
	stack[1].m_word = letter->SenderId();
	gCFlatRuntime().SystemCall(
		Game.m_partyObjArr[m_joybusCaravanId], 2, 0xF, 2, stack, 0);

	CMes::m_tempVar[0] = letter->TempVar(0);
	CMes::m_tempVar[1] = letter->TempVar(1);
	CMes::m_tempVar[2] = letter->TempVar(2);
	CMes::m_tempVar[3] = letter->TempVar(3);
	CMes::m_tempVar[4] = letter->MessageType();
	CMes::m_tempVar[5] = letter->SenderId();

	int money;
	if (letter->AttachmentIsGil()) {
		money = 0;
	} else {
		money = letter->AttachmentValue();
	}
	CMes::m_tempVar[6] = money;

	int gil;
	if (letter->AttachmentIsGil()) {
		gil = letter->AttachmentValue() * 100;
	} else {
		gil = 0;
	}
	CMes::m_tempVar[7] = gil;

	CMes::m_tempVar[8] = m_saveSlot;

	letter->SetOpened();
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
	CFlatRuntime::CStack stack[5];
	CLetterWork* letter = &m_letters[letterIdx];

	stack[0].m_word = letter->MessageType();
	stack[1].m_word = letter->SenderId();
	stack[2].m_word = param3;
	stack[3].m_word = param4;
	stack[4].m_word = param5;

	gCFlatRuntime().SystemCall(
		Game.m_partyObjArr[m_joybusCaravanId], 2, 0x10, 5, stack, 0);

	letter->SetReplySent();
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
	int used = static_cast<CGPartyObj*>(m_ownerObj)->useItem(static_cast<short>(m_inventoryItems[itemIdx]));
	if ((used != 0) && ((short)m_inventoryItems[itemIdx] != -1)) {
		m_inventoryItems[itemIdx] = 0xFFFF;
		m_inventoryItemCount--;
		if (updateJoybus != 0) {
			Joybus.DelItem(m_joybusCaravanId, static_cast<unsigned char>(itemIdx));
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
	int put = static_cast<CGPartyObj*>(m_ownerObj)->putItem(static_cast<short>(m_inventoryItems[itemIdx]));
	if ((put != 0) && ((short)m_inventoryItems[itemIdx] != -1)) {
		m_inventoryItems[itemIdx] = 0xFFFF;
		m_inventoryItemCount--;
		if (updateJoybus != 0) {
			Joybus.DelItem(m_joybusCaravanId, static_cast<unsigned char>(itemIdx));
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
	int put = static_cast<CGPartyObj*>(m_ownerObj)->putGil(gilToRemove);
	if (put != 0) {
		gilToRemove = -gilToRemove;
		m_gil += gilToRemove;
		if (m_gil > 99999999) {
			m_gil -= m_gil - 99999999;
		} else if (m_gil < 0) {
			m_gil = 0;
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
	CheckAndResetCurrentWeaponIdx(m_weaponIdx);
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
 * PAL Address: 0x800a20b0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::CanAddComList(int count)
{
	for (int i = 2; i < (short)m_numCmdListSlots; i++) {
		if ((m_commandListInventorySlotRef[i] == -1) && (--count == 0)) {
			break;
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
	int i = 2;

	for (; i < m_numCmdListSlots; i++) {
		if (m_commandListInventorySlotRef[i] == -1) {
			m_commandListInventorySlotRef[i] = itemSlot;
			Joybus.SetCmdLst(m_joybusCaravanId, i, itemSlot);
			if (cmdListSlotOut != 0) {
				*cmdListSlotOut = i;
			}
			return 1;
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
		short item = m_inventoryItems[i];
		if (item == -1) {
			m_inventoryItems[i] = static_cast<short>(itemId);
			m_inventoryItemCount = m_inventoryItemCount + 1;
			Joybus.SetItem(m_joybusCaravanId, static_cast<unsigned char>(i), static_cast<short>(itemId));
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
 * PAL Address: 0x800a1e8c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCaravanWork::CanAddTmpArtifact(int numItems)
{
	int emptySlots = 0;

	if (m_treasures[0] == -1) {
		emptySlots++;
	}
	if (m_treasures[1] == -1) {
		emptySlots++;
	}
	if (m_treasures[2] == -1) {
		emptySlots++;
	}
	if (m_treasures[3] == -1) {
		emptySlots++;
	}

	return (numItems <= emptySlots);
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
#pragma push
#pragma opt_propagation off
int CCaravanWork::FindItem(int itemId)
{
	CCaravanWork* cur = this;
	int itemIdx = 0;

	for (int row = 0; row < 8; row++) {
		short item = cur->m_inventoryItems[0];
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[1];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[2];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[3];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[4];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[5];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[6];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}
		item = cur->m_inventoryItems[7];
		itemIdx++;
		if (item != -1 && item == itemId) {
			return itemIdx;
		}

		cur = (CCaravanWork*)&cur->m_baseDataIndex;
		itemIdx++;
	}

	return -1;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800a1d0c
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCaravanWork::DeleteItemIdx(int itemSlot, int updateJoybus)
{
	if (m_inventoryItems[itemSlot] != -1) {
		m_inventoryItems[itemSlot] = -1;
		m_inventoryItemCount = m_inventoryItemCount - 1;
		if (updateJoybus != 0) {
			Joybus.DelItem(m_joybusCaravanId, static_cast<unsigned char>(itemSlot));
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
        if (m_inventoryItems[i] != -1 && m_inventoryItems[i] == itemIndex) {
            m_inventoryItems[i] = 0xFFFF;
            m_inventoryItemCount = m_inventoryItemCount - 1;
            if (updateJoybus != 0) {
                Joybus.DelItem(m_joybusCaravanId, static_cast<unsigned char>(i));
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
    for (int i = 0; i < 4; i++) {
        if (m_treasures[i] == -1) {
            m_treasures[i] = (short)itemId;
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
	unsigned char canAdd = 0;
	int totalGil = m_gil + gilAmount;
	if ((totalGil >= 0) && (totalGil <= 99999999)) {
		canAdd = 1;
	}
	return canAdd != 0;
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
	if (totalGil > 99999999) {
		int overflow = totalGil - 99999999;
		m_gil = totalGil - overflow;
		gilToAdd = gilToAdd - overflow;
	} else if (totalGil < 0) {
		gilToAdd = gilToAdd - totalGil;
		m_gil = 0;
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
	CCaravanWork* cur = this;
	unsigned short* target = &m_letterMeta[playerIdx];
	int rank = 0;
	int baseIdx = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if ((playerIdx != baseIdx) && (cur->m_letterMeta[j] > *target)) {
				rank++;
			}
			baseIdx++;
		}

		if ((playerIdx != baseIdx) && (cur->m_letterMeta[3] > *target)) {
			rank++;
		}
		cur = (CCaravanWork*)&cur->m_saveSlot;
		baseIdx++;
	}

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

	for (int i = 0; i < maxResults; i++) {
		romLetterWork[i] = 0;
	}

	CRomLetterWork* curLetter = reinterpret_cast<CRomLetterWork*>(Game.m_romLetterWorkBase);
	for (int letterIdx = 0; letterIdx < 0x200; letterIdx++, curLetter++) {
		unsigned short condBits = curLetter->m_personalConditions;

		if ((condBits & 0x7FFF) != 0) {
			int excludeFlag = condBits & 0x8000;
			if ((condBits & 0x0001) != 0) {
				if (m_tribeId == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0002) != 0) {
				if (m_tribeId == 1) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0004) != 0) {
				if (m_tribeId == 2) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0008) != 0) {
				if (m_tribeId == 3) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0010) != 0) {
				if (m_genderFlag == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0020) != 0) {
				if (m_genderFlag == 1) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0040) != 0) {
				if (GetFoodRank(0) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0080) != 0) {
				if (GetFoodRank(1) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0100) != 0) {
				if (GetFoodRank(2) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0200) != 0) {
				if (GetFoodRank(3) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0400) != 0) {
				if (GetFoodRank(4) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0800) != 0) {
				if (GetFoodRank(5) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x1000) != 0) {
				if (GetFoodRank(6) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x2000) != 0) {
				if (GetFoodRank(7) == 0) {
					if (excludeFlag == 0) {
						goto PassedPersonalConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}

			if (excludeFlag == 0) {
				goto NextLetter;
			}
		}
	PassedPersonalConditions:

		condBits = curLetter->m_linkConditions;
		if ((condBits & 0x7FFF) != 0) {
			int excludeFlag = condBits & 0x8000;
			if ((condBits & 0x0001) != 0) {
				if (unk_0x3ac == 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0002) != 0) {
				if (unk_0x3ac == 1) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0004) != 0) {
				if (unk_0x3ac == 2) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0008) != 0) {
				if (unk_0x3ac == 3) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0010) != 0) {
				if (unk_0x3ac == 4) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0020) != 0) {
				if (unk_0x3ac == 5) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0040) != 0) {
				if (unk_0x3ac == 6) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0080) != 0) {
				if (unk_0x3ac == 7) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0100) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][1] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0200) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][2] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0400) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][3] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0800) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][4] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x1000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][5] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x2000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][6] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x4000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][7] != 0) {
					if (excludeFlag == 0) {
						goto PassedLinkConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}

			if (excludeFlag == 0) {
				goto NextLetter;
			}
		}
	PassedLinkConditions:

		condBits = curLetter->m_linkValueConditions;
		if ((condBits & 0x7FFF) != 0) {
			int excludeFlag = condBits & 0x8000;
			if ((condBits & 0x0001) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][1] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0002) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][2] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0004) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][3] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0008) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][4] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0010) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][5] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0020) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][6] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0040) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][7] >= 0x3D) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0100) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][1] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][1] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0200) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][2] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][2] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0400) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][3] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][3] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x0800) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][4] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][4] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x1000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][5] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][5] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x2000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][6] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][6] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}
			if ((condBits & 0x4000) != 0) {
				if (Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][7] > 0 && Game.m_gameWork.m_linkTable[m_saveSlot][0][m_saveSlot][7] <= 0x28) {
					if (excludeFlag == 0) {
						goto PassedLinkValueConditions;
					}
				} else if (excludeFlag != 0) {
					goto NextLetter;
				}
			}

			if (excludeFlag == 0) {
				goto NextLetter;
			}
		}
	PassedLinkValueConditions:

		int cmpValue = 0;
		int sysVal0 = *reinterpret_cast<int*>(&Game.m_gameWork.m_scriptSysVal0);
		int sysVal1 = Game.m_gameWork.m_timerA;
		int sysVal2 = Game.m_gameWork.m_scriptGlobalTime;
		int sysVal3 = Game.m_gameWork.m_frameCounter;
		for (int i = 0; i < 4; i++) {
			const unsigned short cmpType = curLetter->m_compareRules[i].m_rule;
			const int sourceType = (cmpType >> 11) & 3;
			const int sourceIdx = cmpType & 0x7FF;

			if (sourceType != 3) {
				switch (sourceType) {
				case 0:
					switch (sourceIdx) {
					case 0:
						cmpValue = sysVal0;
						break;
					case 1:
						cmpValue = sysVal1;
						break;
					case 2:
						cmpValue = sysVal2;
						break;
					case 3:
						cmpValue = sysVal3;
						break;
					}
					break;
				case 1:
					cmpValue = Game.m_gameWork.m_eventWork[sourceIdx];
					break;
				case 2:
					cmpValue = m_evtWordArr[sourceIdx];
					break;
				}

				const int op = cmpType >> 13;
				const int compareValue = curLetter->m_compareRules[i].m_value;
				switch (op) {
				case 0:
					if (cmpValue != compareValue) {
						goto NextLetter;
					}
					break;
				case 1:
					if (cmpValue == compareValue) {
						goto NextLetter;
					}
					break;
				case 2:
					if (cmpValue < compareValue) {
						goto NextLetter;
					}
					break;
				case 3:
					if (cmpValue > compareValue) {
						goto NextLetter;
					}
					break;
				case 4:
					if (cmpValue <= compareValue) {
						goto NextLetter;
					}
					break;
				case 5:
					if (cmpValue >= compareValue) {
						goto NextLetter;
					}
					break;
				}
			}
		}

		{
			int bit0 = 0;
			int bit1 = 0;
			int bit2 = 0;
			unsigned char* evtWorkBytes = reinterpret_cast<unsigned char*>(m_evtWorkArr);

			for (int i = 0; i < 8; i++) {
				const unsigned short evtRule = curLetter->m_eventRules[i];
				const int sourceType = (evtRule >> 11) & 3;
				const int sourceIdx = evtRule & 0x7FF;
				int checkValue = bit0;

				if (sourceType == 3) {
					continue;
				}

				switch (sourceType) {
				case 2:
					bit0 = ((evtWorkBytes[sourceIdx / 8] & (1 << (sourceIdx % 8))) != 0);
					bit1 = ((evtWorkBytes[(sourceIdx + 1) / 8] & (1 << ((sourceIdx + 1) % 8))) != 0);
					bit2 = ((evtWorkBytes[(sourceIdx + 2) / 8] & (1 << ((sourceIdx + 2) % 8))) != 0);
					break;
				case 1:
					bit0 = ((static_cast<signed char>(Game.m_gameWork.m_eventFlags[sourceIdx / 8]) &
							 (1 << (sourceIdx % 8))) != 0);
					bit1 = ((static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[(sourceIdx + 1) / 8]) &
							 (1 << ((sourceIdx + 1) % 8))) != 0);
					bit2 = ((static_cast<unsigned char>(Game.m_gameWork.m_eventFlags[(sourceIdx + 2) / 8]) &
							 (1 << ((sourceIdx + 2) % 8))) != 0);
					break;
				}

				checkValue = bit0;

				switch ((evtRule >> 13) & 7) {
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
				short priority = romLetterWork[i]->m_priorityFlags & 0xF00;
				if (priority < minPriority) {
					minPriority = priority;
					replaceIndex = i;
				}
			}

			const short curPriority = curLetter->m_priorityFlags & 0xF00;
			if (minPriority < curPriority) {
				romLetterWork[replaceIndex] = curLetter;
			}
		} else {
			romLetterWork[foundCount] = curLetter;
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
int CCaravanWork::ShopRequest(int requestType, int param3, int param4, int param5, int param6, int flags, int)
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
			m_shopArgs[0] = param3;
			m_shopArgs[1] = param4;
			m_shopArgs[2] = param5;
			m_shopArgs[3] = param6;
			m_shopRequestFlags = (unsigned char)(flags & 1);
			break;
	case 3:
		m_shopParam = (short)param3;
		break;
	case 4:
		m_shopRequestState = 1;
		if (Game.m_gameWork.m_menuStageMode != 0) {
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		} else {
			GbaQue.SetShopFlg(m_joybusCaravanId);
		}
		break;
	case 5:
		m_shopRequestState = 2;
		if (Game.m_gameWork.m_menuStageMode != 0) {
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		} else {
			GbaQue.SetSmithFlg(m_joybusCaravanId);
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
	CFlatRuntime::CStack args[5];

	if ((requestType == 0) || (requestType == 1)) {
		m_shopRequestState = 0;
	}
	args[0].m_word = requestType;
	args[1].m_word = arg0;
	args[2].m_word = arg1;
	args[3].m_word = arg2;
	args[4].m_word = arg3;
	gCFlatRuntime().SystemCall(
		reinterpret_cast<CFlatRuntime::CObject*>(m_ownerObj), 2, 0x12, 5, args, 0);
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
#pragma push
#pragma opt_propagation off
void CCaravanWork::SafeDeleteTempItem()
{
	if ((unsigned int)System.m_execParam >= 3U) {
		System.Printf(const_cast<char*>(sNoWorldReturnItemWarning));
	}

	int totalSlots = 0;
	int artifactIndex = 0;
	CCaravanWork* artifactCur = this;
	for (int i = 50; i != 0; i--) {
		if (artifactIndex < 96) {
			int artifactId = artifactCur->m_artifacts[0];
			if (artifactId > 0) {
				unsigned short* artifactData =
					(unsigned short*)(Game.unkCFlatData0[2] + artifactId * 0x48);
				unsigned short slots = artifactData[3];
				switch (artifactData[0]) {
				case 0xDB:
					totalSlots += slots;
					break;
				case 0x9F:
				case 0xB6:
				case 0xCC:
				case 0xDF:
				case 0xE4:
				default:
					break;
				}
			}
		}

		artifactIndex++;
		if (artifactIndex < 96) {
			int artifactId = artifactCur->m_artifacts[1];
			if (artifactId > 0) {
				unsigned short* artifactData =
					(unsigned short*)(Game.unkCFlatData0[2] + artifactId * 0x48);
				unsigned short slots = artifactData[3];
				switch (artifactData[0]) {
				case 0xDB:
					totalSlots += slots;
					break;
				case 0x9F:
				case 0xB6:
				case 0xCC:
				case 0xDF:
				case 0xE4:
				default:
					break;
				}
			}
		}

		artifactCur = (CCaravanWork*)&artifactCur->m_objType;
		artifactIndex++;
	}

	totalSlots += (short)m_baseCmdListSlots;
	for (int slotIndex = totalSlots; slotIndex < 8; slotIndex++) {
		if (m_commandListInventorySlotRef[slotIndex] >= 0) {
			m_commandListInventorySlotRef[slotIndex] = -1;
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(const_cast<char*>(sTempArtifactIndexWarning), slotIndex);
			}
		}
	}

	short invalidItem = -1;
	m_treasures[0] = invalidItem;
	m_treasures[1] = invalidItem;
	m_treasures[2] = invalidItem;
	m_treasures[3] = invalidItem;

	for (int i = 0; i < 64; i++) {
		short item = m_inventoryItems[i];
		if ((item >= 0x100) && (item <= 0x124) && (item != -1)) {
			m_inventoryItems[i] = invalidItem;
			m_inventoryItemCount--;
		}
	}

	short invalidSlot = -1;
	int slot = m_commandListInventorySlotRef[2];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[2] = invalidSlot;
	}
	slot = m_commandListInventorySlotRef[3];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[3] = invalidSlot;
	}
	slot = m_commandListInventorySlotRef[4];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[4] = invalidSlot;
	}
	slot = m_commandListInventorySlotRef[5];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[5] = invalidSlot;
	}
	slot = m_commandListInventorySlotRef[6];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[6] = invalidSlot;
	}
	slot = m_commandListInventorySlotRef[7];
	if (slot >= 0 && m_inventoryItems[slot] < 0) {
		m_commandListInventorySlotRef[7] = invalidSlot;
	}

	m_currentCmdListIndex = 0;
	m_weaponIdx = 0;
	memset(m_commandListExtra, 0, sizeof(m_commandListExtra));
}
#pragma pop

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
	CRomWork* baseData = reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + (m_baseDataIndex * 0x1D0));

	memcpy(RomStatusBlock(), (m_romWork + CRomWork::ElementResistanceOffset), RomStatusBlockHalfwordCount * sizeof(unsigned short));

	unsigned short stat = baseData->m_strength;
	m_strength = stat;
	m_baseStrength = stat;
	stat = baseData->m_magic;
	m_magic = stat;
	m_baseMagic = stat;
	stat = baseData->m_defense;
	m_defense = stat;
	m_baseDefense = stat;
	m_maxHp = baseData->m_maxHp;

	m_equipEffectFlags = 0;
	m_numCmdListSlots = m_baseCmdListSlots;
	memset(m_equipEffectParams, 0, sizeof(m_equipEffectParams) - sizeof(m_equipEffectParams[0]));

	if (m_tempStatBuffTimer != 0) {
		int tempStatBuffId = m_tempStatBuffId;
		if (tempStatBuffId >= 0x183) {
			goto TempStatStr;
		}
		if (tempStatBuffId >= 0x180) {
			goto TempStatDef;
		}
		if (tempStatBuffId >= 0x17D) {
			goto TempStatMag;
		}
		goto TempStatDone;
	TempStatStr:
		if (tempStatBuffId >= 0x185) {
			goto TempStatDone;
		}
		m_strength += *(unsigned short*)(Game.unk_flat3_field_8_0xc7dc + 0x6A);
		goto TempStatDone;
	TempStatDef:
		m_defense += *(unsigned short*)(Game.unk_flat3_field_8_0xc7dc + 0x6C);
		goto TempStatDone;
	TempStatMag:
		m_magic += *(unsigned short*)(Game.unk_flat3_field_8_0xc7dc + 0x6E);
	TempStatDone:;
		m_tempStatBuffTimer--;
	}

	int chaliceElement = Game.m_gameWork.m_chaliceElement;
	switch (chaliceElement) {
	case 1:
		m_elementResistances[1]++;
		break;
	case 2:
		m_elementResistances[2]++;
		break;
	case 4:
		m_elementResistances[3]++;
		break;
	case 8:
		m_statusTimers[0]++;
		m_statusTimers[2]++;
		break;
	}

	int hpBonus = 0;
	int cmdBonus = 0;
	int strBonus = 0;
	int magBonus = 0;
	int defBonus = 0;
	for (int i = 0; i < 100; i++) {
		int artifactId = m_artifacts[i];
		if (artifactId > 0) {
			unsigned short* artifactData = GetItemDataPtr(artifactId);
			int artifactEffect = artifactData[0];
			int value = artifactData[3];

			switch (artifactEffect) {
			case 0x9F:
				strBonus += value;
				break;
			case 0xB6:
				magBonus += value;
				break;
			case 0xCC:
				defBonus += value;
				break;
			case 0xDB:
				cmdBonus += value;
				break;
			case 0xE4:
				hpBonus += value;
				break;
			case 0xDF:
				magBonus += value;
				break;
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

	short cmdSlotCap = 8;
	if ((short)m_numCmdListSlots < 8) {
		cmdSlotCap = m_numCmdListSlots;
	}
	m_numCmdListSlots = cmdSlotCap;

	unsigned short cappedValue = 0x10;
	if (m_maxHp < 0x10) {
		cappedValue = m_maxHp;
	}
	m_maxHp = cappedValue;

	for (int equipIdx = 0; equipIdx < 4; equipIdx++) {
		int equipSlot = m_equipment[equipIdx];
		if (equipSlot >= 0) {
			int itemIdx = m_inventoryItems[equipSlot];
			int itemType = GetItemDataPtr(itemIdx)[0];

			if (itemType == 1) {
				int weaponItem;
				int weaponRef;
				GetCurrentWeaponItem(weaponItem, weaponRef);
				if (weaponItem > 0) {
					itemIdx = weaponItem;
				}
			}

			unsigned short itemValue = (short)GetItemDataPtr(itemIdx)[3];
			if (itemType != 0x45) {
				if (itemType >= 0x45) {
					if (itemType == 0x7F) {
						goto apply_effect;
					}
					goto no_effect;
				}
				if (itemType == 1) {
					m_strength += itemValue;
					m_baseStrength += itemValue;
				}
				goto no_effect;
			}

			m_defense += itemValue;
			m_baseDefense += itemValue;
		apply_effect:
			int itemEffect = GetItemDataPtr(itemIdx)[4];
			unsigned short effectValue = itemValue;
			switch (itemEffect) {
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
			case 0x13:
				m_elementResistances[0]++;
				break;
			case 9:
				m_equipEffectParams[0] += effectValue;
				break;
			case 10:
				m_equipEffectParams[1] += effectValue;
				break;
			case 0xB:
				m_equipEffectParams[2] += effectValue;
				break;
			case 0xC:
				m_equipEffectParams[3] += effectValue;
				break;
			case 0x10:
				m_equipEffectParams[4] += effectValue;
				break;
			case 0x11:
				m_equipEffectParams[5] += effectValue;
				break;
			case 0x12:
				m_equipEffectParams[6] += effectValue;
				break;
			}
			m_equipEffectFlags |= 1 << itemEffect;
		no_effect:
			;
		}
	}

	for (int i = 0; i < 11; i++) {
		unsigned short resistance = 2;
		if (m_elementResistances[i] < 2) {
			resistance = m_elementResistances[i];
		}
		m_elementResistances[i] = resistance;
	}

	if (m_hp > m_maxHp) {
		m_hp = m_maxHp;
	}

	if (m_statusTimers[9] != 0) {
		m_strength = (unsigned short)((float)m_strength * GetStatusMultiplier(0x38));
		m_magic = (unsigned short)((float)m_magic * GetStatusMultiplier(0x38));
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x38));
	}
	if (m_statusTimers[4] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x3E));
	}
	if (m_statusTimers[6] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x44));
	}

	cappedValue = 99;
	if (m_strength <= 99) {
		cappedValue = m_strength;
	}
	m_strength = cappedValue;

	cappedValue = 99;
	if (m_defense <= 99) {
		cappedValue = m_defense;
	}
	m_defense = cappedValue;

	cappedValue = 99;
	if (m_magic <= 99) {
		cappedValue = m_magic;
	}
	m_magic = cappedValue;

	cappedValue = 99;
	if (m_baseStrength <= 99) {
		cappedValue = m_baseStrength;
	}
	m_baseStrength = cappedValue;

	cappedValue = 99;
	if (m_baseDefense <= 99) {
		cappedValue = m_baseDefense;
	}
	m_baseDefense = cappedValue;

	cappedValue = 99;
	if (m_baseMagic <= 99) {
		cappedValue = m_baseMagic;
	}
	m_baseMagic = cappedValue;
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
unsigned int CCaravanWork::GetMagicCharge(int cmdListIdx, int&, int&)
{
	unsigned int isInvalid = 0;
	short slotRef = m_commandListInventorySlotRef[cmdListIdx];
	if ((cmdListIdx >= 2) && (slotRef == -1)) {
		isInvalid = 1;
	}

	if ((((unsigned int)__cntlzw((unsigned char)isInvalid)) >> 5) == 0) {
		return 0;
	}

	int groupedCountLocal = 1;
	if (Game.m_gameWork.m_menuStageMode == 0) {
		groupedCountLocal = 1;
	} else {
		if (m_commandListExtra[cmdListIdx] == 0) {
			groupedCountLocal = 1;
		} else {
			int topIdx = cmdListIdx;
			for (int n = cmdListIdx; n >= 0; n--) {
				if (m_commandListExtra[topIdx] != -1) {
					break;
				}
				topIdx--;
			}

			groupedCountLocal = 1;
			int nextIdx = topIdx + 1;
			int numSlots = static_cast<short>(m_numCmdListSlots);
			for (int n = topIdx + 1; n < numSlots; n++) {
				if (m_commandListExtra[nextIdx] != -1) {
					break;
				}
				groupedCountLocal++;
				nextIdx++;
			}
		}
	}

	if (groupedCountLocal == 1) {
		return (((unsigned int)__cntlzw(cmdListIdx - static_cast<short>(m_currentCmdListIndex))) >> 5) & 0xFF;
	} else {
		for (int n = cmdListIdx; n >= 0; n--) {
			if (m_commandListExtra[cmdListIdx] != -1) {
				break;
			}
			cmdListIdx--;
		}

		unsigned int selected = 0;
		short currentCmdListIndex = m_currentCmdListIndex;
		if ((currentCmdListIndex >= cmdListIdx) && (currentCmdListIndex <= (cmdListIdx + groupedCountLocal - 1))) {
			selected = 1;
		}
		return selected & 0xFF;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a7e18
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
int CCaravanWork::GetCmdListItemName(int cmdListIdx, int* firstCmdIdx, int* itemCmdListIdx)
{
	int groupedCount;

	if (Game.m_gameWork.m_menuStageMode == 0) {
		groupedCount = 1;
	} else {
		if (m_commandListExtra[cmdListIdx] == 0) {
			groupedCount = 1;
		} else {
			int topIdx;
			for (topIdx = cmdListIdx; topIdx >= 0; topIdx--) {
				if (m_commandListExtra[topIdx] != -1) {
					break;
				}
			}

			groupedCount = 1;
			int nextIdx = topIdx + 1;
			for (int n = topIdx + 1; n < static_cast<short>(m_numCmdListSlots); n++) {
				if (m_commandListExtra[nextIdx] != -1) {
					break;
				}
				groupedCount++;
				nextIdx++;
			}
		}
	}

	if (groupedCount > 1) {
		for (int n = cmdListIdx; n >= 0; n--) {
			if (m_commandListExtra[cmdListIdx] != -1) {
				break;
			}
			cmdListIdx--;
		}

		short cmdId = m_commandListExtra[cmdListIdx];
		if (cmdId == 0x207 || cmdId == 0x20B || cmdId == 0x20F) {
			*firstCmdIdx = cmdListIdx;
			int i = 0;
			for (; groupedCount > 0; groupedCount--) {
				short invSlot = (short)m_commandListInventorySlotRef[cmdListIdx + i];
				short itemId = (short)m_inventoryItems[invSlot];
				int itemType = GetItemDataPtr(itemId)[0];
				if (itemType == 1) {
					*itemCmdListIdx = cmdListIdx + i;
					return 1;
				}
				i++;
			}
		}
	}

	return 0;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8009f6ac
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CCaravanWork::GetWeaponAttrib(int cmdListIdx)
{
	int weaponType = GetCmdListItem(cmdListIdx);
	if (weaponType >= 0 && weaponType < 3) {
		return MenuPcs.GetSkillStr(weaponType);
	}

	int itemId = DelCmdListAndItem(cmdListIdx);
	return Game.m_cFlatDataArr[1].TableStrings(0)[itemId * 5 + 4];
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
	int result = -1;

	if (GetCmdListItemName(cmdListIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
		short cmdId = m_commandListExtra[cmdTopIdx];
		switch (cmdId) {
		case 0x207:
			result = 0;
			break;
		case 0x20B:
			result = 1;
			break;
		case 0x20F:
			result = 2;
			break;
		}
	}

	return result;
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
int CCaravanWork::DelCmdListAndItem(int cmdListIdx)
{
	int result;
	int inventorySlot = m_commandListInventorySlotRef[cmdListIdx];

	if (cmdListIdx == 0) {
		int equipmentSlot = m_equipment[0];
		if (equipmentSlot < 0) {
			result = 0;
		} else {
			result = (short)m_inventoryItems[equipmentSlot];
		}
	} else if (cmdListIdx == 1) {
		int equipmentSlot = m_equipment[2];
		if (equipmentSlot < 0) {
			result = 0;
		} else {
			result = (short)m_inventoryItems[equipmentSlot];
		}
	} else {
		int numGrouped;
		if (Game.m_gameWork.m_menuStageMode == 0) {
			numGrouped = 1;
		} else if (m_commandListExtra[cmdListIdx] == 0) {
			numGrouped = 1;
		} else {
			int topIdx;
			for (topIdx = cmdListIdx; topIdx >= 0; topIdx--) {
				if (m_commandListExtra[topIdx] != -1) {
					break;
				}
			}

			numGrouped = 1;
			int nextIdx = topIdx + 1;
			for (int n = topIdx + 1; n < (short)m_numCmdListSlots; n++) {
				if (m_commandListExtra[nextIdx] != -1) {
					break;
				}
				numGrouped++;
				nextIdx++;
			}
		}

		if (numGrouped > 1) {
			for (int n = cmdListIdx; n >= 0; n--) {
				if (m_commandListExtra[cmdListIdx] != -1) {
					break;
				}
				cmdListIdx--;
			}

			int cmdResult = m_commandListExtra[cmdListIdx];
			int cmdTopIdx;
			int itemCmdListIdx;
			if (GetCmdListItemName(cmdListIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
				cmdResult = (short)m_inventoryItems[(short)m_commandListInventorySlotRef[itemCmdListIdx]];
			}
			result = cmdResult;
		} else {
			if (inventorySlot < 0) {
				result = 0;
			} else {
				result = (short)m_inventoryItems[inventorySlot];
			}
		}
	}

	return result;
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
	int nextCmdIdx = 0;
	short* slotRefPtr = &m_commandListInventorySlotRef[cmdListIdx];
	if (m_currentCmdListIndex == cmdListIdx) {
		nextCmdIdx = GetNextCmdListIdx(cmdListIdx, 1);
	}

	short inventorySlot = *slotRefPtr;
	if (m_inventoryItems[inventorySlot] != -1) {
		m_inventoryItems[inventorySlot] = 0xFFFF;
		m_inventoryItemCount = static_cast<short>(m_inventoryItemCount - 1);
		if (updateJoybus != 0) {
			Joybus.DelItem(m_joybusCaravanId, static_cast<unsigned char>(inventorySlot));
		}
	}

	*slotRefPtr = 0xFFFF;
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

		int item = DelCmdListAndItem(cmdListIdx);
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
		weaponItem = 0;
		CCaravanWork* ownerWork = *reinterpret_cast<CCaravanWork**>(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x58);
		int equippedSlot = ownerWork->m_equipment[0];
		if (equippedSlot >= 0) {
			weaponRef = ownerWork->m_inventoryItems[equippedSlot];
		}
	} else if (weaponIdx != 1) {
		weaponItem = weaponIdx;
		CCaravanWork* ownerWork = *reinterpret_cast<CCaravanWork**>(reinterpret_cast<unsigned char*>(m_ownerObj) + 0x58);
		weaponRef = ownerWork->DelCmdListAndItem(m_weaponIdx);
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
void CCaravanWork::CheckAndResetCurrentWeaponIdx(int weaponIdx)
{
	int reset = 0;
	int weaponItem = DelCmdListAndItem(weaponIdx);
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
	char* fmtBase = sWorldMapSortFormatBlock;

	memset(m_commandListExtra, 0, sizeof(m_commandListExtra));

	for (int i = 0; i < 0x40; i++) {
		System.Printf(fmtBase + 0x64, i, m_inventoryItems[i]);
	}

	for (int i = 2; i < 8; i++) {
		System.Printf(fmtBase + 0x74, i, m_commandListInventorySlotRef[i]);
	}

	for (int i = 0; i < 4; i++) {
		System.Printf(fmtBase + 0x88, i, m_equipment[i]);
	}

	for (int i = 0; i < 0x3F; i++) {
		for (int j = i + 1; j < 0x40; j++) {
			short lhs = m_inventoryItems[i];
			short rhs = m_inventoryItems[j];

			if (lhs < 1) {
				if (rhs > 0) {
					m_inventoryItems[i] = rhs;
					m_inventoryItems[j] = 0xFFFF;

					for (int slot = 2; slot < 8; slot++) {
						if (static_cast<short>(m_commandListInventorySlotRef[slot]) == j) {
							m_commandListInventorySlotRef[slot] = static_cast<short>(i);
						}
					}

					for (int equip = 0; equip < 4; equip++) {
						if (m_equipment[equip] == j) {
							m_equipment[equip] = static_cast<short>(i);
						}
					}
				}
			} else if ((rhs > 0) && (rhs < lhs)) {
				m_inventoryItems[i] = rhs;
				m_inventoryItems[j] = lhs;

				for (int slot = 2; slot < 8; slot++) {
					short cur = static_cast<short>(m_commandListInventorySlotRef[slot]);
					if (cur == i) {
						m_commandListInventorySlotRef[slot] = static_cast<short>(j);
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

	for (int i = 0; i < 0x40; i++) {
		System.Printf(fmtBase + 0x64, i, m_inventoryItems[i]);
	}

	for (int i = 2; i < 8; i++) {
		System.Printf(fmtBase + 0x74, i, m_commandListInventorySlotRef[i]);
	}

	for (int i = 0; i < 4; i++) {
		System.Printf(fmtBase + 0x88, i, m_equipment[i]);
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
	if (mode != 0) {
		memcpy(m_backupInventoryBlock, m_inventoryItems, sizeof(m_backupInventoryBlock));
		memset(m_inventoryItems, 0xFF, sizeof(m_backupInventoryBlock));
		m_backupInventoryItemCount = m_inventoryItemCount;
		m_inventoryItemCount = 0;
		memcpy(m_backupCommandListInventorySlotRef, m_commandListInventorySlotRef, sizeof(m_backupCommandListInventorySlotRef));
		memset(m_commandListInventorySlotRef, 0xFF, sizeof(m_commandListInventorySlotRef));
		memcpy(m_backupCmdlistExtra, m_commandListExtra, sizeof(m_backupCmdlistExtra));
		memset(m_commandListExtra, 0, sizeof(m_commandListExtra));
		memcpy(m_backupEquipment, m_equipment, sizeof(m_backupEquipment));
		memset(m_equipment, 0xFF, sizeof(m_equipment));
		m_backupGil = m_gil;
		m_gil = 0;
		m_backupCurrentCmdListIndex = m_currentCmdListIndex;
		m_currentCmdListIndex = 0;
		m_backupWeaponIdx = m_weaponIdx;
		m_weaponIdx = 0;
	} else {
		memcpy(m_inventoryItems, m_backupInventoryBlock, sizeof(m_backupInventoryBlock));
		m_inventoryItemCount = m_backupInventoryItemCount;
		memcpy(m_commandListInventorySlotRef, m_backupCommandListInventorySlotRef, sizeof(m_backupCommandListInventorySlotRef));
		memcpy(m_commandListExtra, m_backupCmdlistExtra, sizeof(m_backupCmdlistExtra));
		memcpy(m_equipment, m_backupEquipment, sizeof(m_backupEquipment));
		m_gil = m_backupGil;
		m_currentCmdListIndex = m_backupCurrentCmdListIndex;
		m_weaponIdx = m_backupWeaponIdx;
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
		m_commandListExtra[startIdx + i] = (i == 0) ? cmdId : -1;
	}

	if ((m_weaponIdx >= startIdx) && (m_weaponIdx < (startIdx + count))) {
		int cmdTopIdx;
		int itemCmdListIdx;
		if (GetCmdListItemName(startIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
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
		if (GetCmdListItemName(startIdx, &cmdTopIdx, &itemCmdListIdx) != 0) {
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
	unsigned short* artifactDataBase = reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2]);
	CRomWork* baseData = reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + (m_baseDataIndex * 0x1D0));
	int hpMax = 0;
	int artifactIndex = 0;
	int count = 0x32;

	while (count != 0) {
		if (artifactIndex < 0x60) {
			int artifactId = m_artifacts[artifactIndex];
			if (artifactId > 0) {
				unsigned short* artifactData = artifactDataBase + (artifactId * 0x24);
				unsigned short artifactType = artifactData[0];
				unsigned short artifactValue = artifactData[3];

				switch (artifactType) {
				case 0x9F:
				case 0xB6:
				case 0xCC:
				case 0xDB:
				case 0xDF:
					break;
				case 0xE4:
					hpMax += artifactValue;
					break;
				}
			}
		}

		if ((artifactIndex + 1) < 0x60) {
			int artifactId = m_artifacts[artifactIndex + 1];
			if (artifactId > 0) {
				unsigned short* artifactData = artifactDataBase + (artifactId * 0x24);
				unsigned short artifactType = artifactData[0];
				unsigned short artifactValue = artifactData[3];

				switch (artifactType) {
				case 0x9F:
				case 0xB6:
				case 0xCC:
				case 0xDB:
				case 0xDF:
					break;
				case 0xE4:
					hpMax += artifactValue;
					break;
				}
			}
		}

		artifactIndex += 2;
		count--;
	}

	hpMax += baseData->m_maxHp;
	if (hpMax >= 0x10) {
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
CMonWork::~CMonWork()
{
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
	int stageRank;
	int memberCount;

	m_baseDataIndex = baseDataIndex;
	m_id = romWork->m_id;
	m_param1 = romWork->m_param1;
	m_param2 = romWork->m_param2;
	m_maxHp = romWork->m_maxHp;
	m_strength = romWork->m_strength;
	m_magic = romWork->m_magic;
	m_defense = romWork->m_defense;
	m_romWork = romWork->Data();

	memcpy(RomStatusBlock(), (m_romWork + CRomWork::ElementResistanceOffset), RomStatusBlockHalfwordCount * sizeof(unsigned short));
	memset(m_statusTimers + 3, 0, sizeof(m_statusTimers) - 3 * sizeof(m_statusTimers[0]));
	m_statusValues[0] = 0xFFFF;
	m_statusValues[1] = 0xFFFF;
	m_statusValues[2] = 0xFFFF;
	m_statusValues[3] = 0xFFFF;
	m_statusValues[4] = 0xFFFF;
	m_statusValues[5] = 0xFFFF;
	m_statusValues[6] = 0xFFFF;
	m_statusValues[7] = 0xFFFF;
	m_statusValues[8] = 0xFFFF;
	m_statusValues[9] = 0xFFFF;
	m_statusValues[10] = 0xFFFF;
	m_statusValues[11] = 0xFFFF;
	m_statusValues[12] = 0xFFFF;
	m_statusValues[13] = 0xFFFF;
	m_statusValues[14] = 0xFFFF;
	m_statusValues[15] = 0xFFFF;
	m_hp = m_maxHp;

	memcpy(unk_0xac, romWork->MonsterParams0(), 8);
	memcpy(unk_0xb4, romWork->MonsterParams1(), 0x1C);
	memset(unk_0xd0, 0, sizeof(unk_0xd0));
	memset(unk_0xf0, 0, sizeof(unk_0xf0));

	if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		int rank = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
		stageRank = 2;
		if (rank < stageRank) {
			stageRank = rank;
		}
	} else {
		stageRank = 0;
	}

	if (stageRank > 0) {
		m_maxHp = (unsigned short)((float)m_maxHp * GetStatusMultiplier(stageRank * 2 + 0x44));
	}

	int* backupParam = Game.m_gameWork.m_wmBackupParams;
	memberCount = 0;
	if (*backupParam >= 0) {
		memberCount = 1;
	}
	backupParam++;
	if (*backupParam >= 0) {
		memberCount++;
	}
	backupParam++;
	if (*backupParam >= 0) {
		memberCount++;
	}
	backupParam++;
	if (*backupParam >= 0) {
		memberCount++;
	}

	int scaledMemberCount = memberCount;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		scaledMemberCount = 1;
	}

	if (scaledMemberCount > 1) {
		m_maxHp = (unsigned short)((float)m_maxHp * GetStatusMultiplier((int)(scaledMemberCount * 2 + 0x5E)));
	}

	if ((*reinterpret_cast<int*>(&Game.m_gameWork.m_scriptSysVal0) == 1) &&
		(Game.m_gameWork.m_bossArtifactStageIndex < 0xF)) {
		CGame::CBossArtifactStage* bossArtifacts =
			&Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex];
		short artifactScale = bossArtifacts->m_entries[8].m_values[0];
		m_maxHp = (unsigned short)((float)m_maxHp *
								   ((((float)artifactScale) * kGObjWorkStatusScaleStep) + kGObjWorkStatusScaleBase));
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
	CRomWork* baseData = reinterpret_cast<CRomWork*>(Game.unkCFlatData0[1] + (m_baseDataIndex * 0x1D0));

	memcpy(RomStatusBlock(), (m_romWork + CRomWork::ElementResistanceOffset), RomStatusBlockHalfwordCount * sizeof(unsigned short));

	m_strength = baseData->m_strength;
	m_magic = baseData->m_magic;
	m_defense = baseData->m_defense;

	int stageRank;
	if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		int rank = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
		stageRank = 2;
		if (rank < stageRank) {
			stageRank = rank;
		}
	} else {
		stageRank = 0;
	}

	if (stageRank > 0) {
		m_strength = (unsigned short)((float)m_strength * GetStatusMultiplier(stageRank * 2 + 0x48));
		m_magic = (unsigned short)((float)m_magic * GetStatusMultiplier(stageRank * 2 + 0x4C));
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(stageRank * 2 + 0x50));
	}

	if (m_statusTimers[9] != 0) {
		m_strength = (unsigned short)((float)m_strength * GetStatusMultiplier(0x38));
		m_magic = (unsigned short)((float)m_magic * GetStatusMultiplier(0x38));
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x38));
	}

	if (m_statusTimers[4] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x3E));
	}

	if (m_statusTimers[6] != 0) {
		m_defense = (unsigned short)((float)m_defense * GetStatusMultiplier(0x44));
	}
}

unsigned char sRingMenuBlinkAlphaTable[16] = {
	0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0,
	0xFF, 0xE0, 0xC0, 0xA0, 0x80, 0x60, 0x40, 0x20,
};
