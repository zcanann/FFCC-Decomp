#include "ffcc/gobjwork.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include <string.h>

namespace {
static inline unsigned short* GetItemDataPtr(int itemIdx)
{
	return (unsigned short*)(Game.game.unkCFlatData0[2] + (itemIdx * 0x48));
}

static inline float GetStatusMultiplier(int offset)
{
	return ((float)(*(unsigned short*)(Game.game.unk_flat3_field_8_0xc7dc + offset)) * 0.01f) + 1.0f;
}
}

extern "C" void __dl__FPv(void*);
extern "C" void* __vt__8CMonWork[];
extern "C" void* __vt__12CCaravanWork[];
extern "C" void* __vt__9CGObjWork[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGObjWork::CGObjWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGObjWork::~CGObjWork()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGObjWork::Init(int, CRomWork*, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CCaravanWork::CCaravanWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCaravanWork::~CCaravanWork()
{
	// TODO
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
	unk_0x3c8 = 0;
	unk_0x3c9 = 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::LoadInit()
{
	// TODO
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

	m_baseDataIndex = (m_id / 100) - 1;
	m_romWorkPtr = reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[0] + (m_baseDataIndex * 0x1D0) + 0x10);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::Init(int, CRomWork*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::SetBonusCondition(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::IsOutOfShouki()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::AddLetter(int, int, int, int, int, int, int, int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGLetterOpen(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGLetterReply(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGUseItem(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGPutItem(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FGPutGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::ChgCmdLst(int, int)
{
	// TODO
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
	int slotCount = m_numCmdListSlots;
	unsigned short* slot = m_commandListInventorySlotRef;

	if (slotCount > 2) {
		for (int i = slotCount - 2; i != 0; i--) {
			if ((*slot == 0xFFFF) && (--count == 0)) {
				break;
			}
			slot++;
		}
	}

	return count == 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::AddComList(int, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::DeleteCmdList(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::AddItem(int, int*)
{
	// TODO
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
	unsigned short artifact = 0xFFFF;
	if (enabled != 0) {
		artifact = (short)artifactIndex + 0x9F;
	}
	m_artifacts[artifactIndex] = artifact;
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
void CCaravanWork::ChkNumItem(char*, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::FindItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::DeleteItemIdx(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::DeleteItem(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::AddTmpArtifact(int, int*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::AddGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetFoodRank(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::SearchRomLetterWork(CRomLetterWork **, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::ShopRequest(int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CallShop(int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::SafeDeleteTempItem()
{
	// TODO
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
	unsigned short* baseData = (unsigned short*)(Game.game.unkCFlatData0[0] + (m_baseDataIndex * 0x1D0));

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
			m_strength += *(short*)(Game.game.unk_flat3_field_8_0xc7dc + 0x6A);
		} else if (m_tempStatBuffId >= 0x180) {
			m_defense += *(short*)(Game.game.unk_flat3_field_8_0xc7dc + 0x6C);
		} else if (m_tempStatBuffId > 0x17C) {
			m_magic += *(short*)(Game.game.unk_flat3_field_8_0xc7dc + 0x6E);
		}
		m_tempStatBuffTimer--;
	}

	if (Game.game.m_gameWork.m_chaliceElement == 4) {
		m_elementResistances[3]++;
	} else if (Game.game.m_gameWork.m_chaliceElement < 4) {
		if (Game.game.m_gameWork.m_chaliceElement == 2) {
			m_elementResistances[2]++;
		} else if ((Game.game.m_gameWork.m_chaliceElement < 2) && (Game.game.m_gameWork.m_chaliceElement > 0)) {
			m_elementResistances[1]++;
		}
	} else if (Game.game.m_gameWork.m_chaliceElement == 8) {
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
void CCaravanWork::CanPlayerUseItem()
{
	((CGPartyObj*)m_ownerObj)->canPlayerUseItem();
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetIdxCmdList()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::IsUseCmdList(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::IsSelectedCmdList(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetMagicCharge(int, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetCmdListItemName(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetWeaponAttrib(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetCmdListItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::DelCmdListAndItem(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetNumCombi(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetNextCmdListIdx(int, int)
{
	// TODO
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
void CCaravanWork::CanPlayerPutItem()
{
	((CGPartyObj*)m_ownerObj)->canPlayerPutItem();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::GetCurrentWeaponItem(int&, int&)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CheckAndResetCurrentWeaponIdx(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::BackupTutorialItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::UniteComList(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::UnuniteComList(int, int)
{
	// TODO
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
	int totalHpBonus = 0;
	int artifactIndex = 0;
	
	// Iterate through artifacts in pairs (50 iterations, 2 artifacts each = 100 artifacts total)
	for (int i = 0; i < 50; i++)
	{
		// Check first artifact in pair
		if (artifactIndex < 96 && m_artifacts[artifactIndex] > 0)
		{
			unsigned short* artifactData = (unsigned short*)(Game.game.unkCFlatData0[2] + m_artifacts[artifactIndex] * 0x48);
			unsigned short artifactType = artifactData[0];
			
			// Check if this is an HP-boosting artifact (type 0xe4, excluding 0xdb)
			if (artifactType != 0xdb && artifactType > 0xda && artifactType == 0xe4)
			{
				totalHpBonus += artifactData[3]; // Add HP bonus value
			}
		}
		
		// Check second artifact in pair
		if ((artifactIndex + 1) < 96 && m_artifacts[artifactIndex + 1] > 0)
		{
			unsigned short* artifactData = (unsigned short*)(Game.game.unkCFlatData0[2] + m_artifacts[artifactIndex + 1] * 0x48);
			unsigned short artifactType = artifactData[0];
			
			// Check if this is an HP-boosting artifact (type 0xe4, excluding 0xdb)
			if (artifactType != 0xdb && artifactType > 0xda && artifactType == 0xe4)
			{
				totalHpBonus += artifactData[3]; // Add HP bonus value
			}
		}
		
		artifactIndex += 2;
	}
	
	// Add base HP value from character data
	totalHpBonus += *(unsigned short*)(Game.game.unkCFlatData0[0] + m_baseDataIndex * 0x1d0 + 6);
	
	// Cap at 16 (0x10)
	if (totalHpBonus > 15)
	{
		return 16;
	}
	
	return totalHpBonus;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMonWork::CMonWork()
{ 
	m_objType = -1;
	m_saveSlot = 0xff;
	m_partyIndex = 0xff;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMonWork::Init(int, CRomWork*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMonWork::CalcStatus()
{
	// TODO
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
