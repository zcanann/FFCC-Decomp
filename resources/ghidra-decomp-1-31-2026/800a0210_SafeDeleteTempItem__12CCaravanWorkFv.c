// Function: SafeDeleteTempItem__12CCaravanWorkFv
// Entry: 800a0210
// Size: 936 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SafeDeleteTempItem__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  uint16_t uVar1;
  short *psVar2;
  int iVar3;
  CCaravanWork *pCVar4;
  int iVar5;
  uint16_t *puVar6;
  int iVar7;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_801d9f64);
  }
  iVar5 = 0;
  iVar3 = 0;
  iVar7 = 0x32;
  pCVar4 = caravanWork;
  do {
    if (((iVar3 < 0x60) && (0 < (short)pCVar4->m_artifacts[0])) &&
       (psVar2 = (short *)(Game.game.unkCFlatData0[2] + (short)pCVar4->m_artifacts[0] * 0x48),
       *psVar2 == 0xdb)) {
      iVar5 = iVar5 + (uint)(ushort)psVar2[3];
    }
    if (((iVar3 + 1 < 0x60) && (0 < (short)pCVar4->m_artifacts[1])) &&
       (psVar2 = (short *)(Game.game.unkCFlatData0[2] + (short)pCVar4->m_artifacts[1] * 0x48),
       *psVar2 == 0xdb)) {
      iVar5 = iVar5 + (uint)(ushort)psVar2[3];
    }
    pCVar4 = (CCaravanWork *)&(pCVar4->gObjWork).m_objType;
    iVar3 = iVar3 + 2;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar5 = iVar5 + (short)caravanWork->m_baseCmdListSlots;
  puVar6 = (caravanWork->gObjWork).m_elementResistances + iVar5 + -0x14;
  for (; iVar5 < 8; iVar5 = iVar5 + 1) {
    if ((-1 < (short)puVar6[0x102]) && (puVar6[0x102] = 0xffff, 2 < (uint)System.m_execParam)) {
      Printf__7CSystemFPce(&System,&DAT_801d9f94,iVar5);
    }
    puVar6 = puVar6 + 1;
  }
  caravanWork->m_treasures[0] = 0xffff;
  iVar3 = 0;
  caravanWork->m_treasures[1] = 0xffff;
  caravanWork->m_treasures[2] = 0xffff;
  caravanWork->m_treasures[3] = 0xffff;
  iVar5 = 0x10;
  pCVar4 = caravanWork;
  do {
    uVar1 = pCVar4->m_inventoryItems[0];
    if (((0xff < (short)uVar1) && ((short)uVar1 < 0x125)) && (uVar1 != 0xffff)) {
      pCVar4->m_inventoryItems[0] = 0xffff;
      caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    }
    uVar1 = pCVar4->m_inventoryItems[1];
    if (((0xff < (short)uVar1) && ((short)uVar1 < 0x125)) && (uVar1 != 0xffff)) {
      pCVar4->m_inventoryItems[1] = 0xffff;
      caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    }
    uVar1 = pCVar4->m_inventoryItems[2];
    if (((0xff < (short)uVar1) && ((short)uVar1 < 0x125)) && (uVar1 != 0xffff)) {
      pCVar4->m_inventoryItems[2] = 0xffff;
      caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    }
    uVar1 = pCVar4->m_inventoryItems[3];
    if (((0xff < (short)uVar1) && ((short)uVar1 < 0x125)) && (uVar1 != 0xffff)) {
      pCVar4->m_inventoryItems[3] = 0xffff;
      caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    }
    pCVar4 = (CCaravanWork *)&(pCVar4->gObjWork).m_saveSlot;
    iVar3 = iVar3 + 3;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[2]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[2]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[2] = 0xffff;
  }
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[3]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[3]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[3] = 0xffff;
  }
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[4]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[4]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[4] = 0xffff;
  }
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[5]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[5]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[5] = 0xffff;
  }
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[6]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[6]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[6] = 0xffff;
  }
  if ((-1 < (short)caravanWork->m_commandListInventorySlotRef[7]) &&
     ((short)caravanWork->m_inventoryItems[(short)caravanWork->m_commandListInventorySlotRef[7]] < 0
     )) {
    caravanWork->m_commandListInventorySlotRef[7] = 0xffff;
  }
  caravanWork->m_currentCmdListIndex = 0;
  caravanWork->m_weaponIdx = 0;
  memset(caravanWork->m_commandListExtra,0,0x10,iVar3);
  return;
}

