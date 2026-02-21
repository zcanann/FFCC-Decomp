#include "ffcc/gobjwork.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include "ffcc/system.h"
#include <string.h>

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
				(unsigned short*)(Game.game.unkCFlatData0[2] + (short)m_artifacts[artifactIndex] * 0x48);
			if (artifactData[0] == 0xDB) {
				totalSlots += artifactData[3];
			}
		}

		if ((artifactIndex + 1) < 96 && (short)m_artifacts[artifactIndex + 1] > 0) {
			unsigned short* artifactData = (unsigned short*)(Game.game.unkCFlatData0[2] +
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
 * Address:	TODO
 * Size:	TODO
 */
void CCaravanWork::CalcStatus()
{
	// TODO
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
