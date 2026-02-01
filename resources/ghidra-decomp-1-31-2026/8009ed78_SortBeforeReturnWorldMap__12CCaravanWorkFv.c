// Function: SortBeforeReturnWorldMap__12CCaravanWorkFv
// Entry: 8009ed78
// Size: 1024 bytes

void SortBeforeReturnWorldMap__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  uint16_t uVar1;
  int iVar2;
  uint16_t *puVar3;
  CCaravanWork *pCVar4;
  uint16_t uVar5;
  int iVar6;
  uint16_t uVar7;
  int iVar8;
  int32_t *piVar9;
  
  memset(caravanWork->m_commandListExtra,0,0x10);
  iVar8 = 0;
  pCVar4 = caravanWork;
  do {
    Printf__7CSystemFPce
              (&System,s_item_d____d_801d9f2c,iVar8,(int)(short)pCVar4->m_inventoryItems[0]);
    iVar8 = iVar8 + 1;
    pCVar4 = (CCaravanWork *)((int)&(pCVar4->gObjWork).vtable + 2);
  } while (iVar8 < 0x40);
  piVar9 = &(caravanWork->gObjWork).m_objType;
  iVar8 = 2;
  do {
    Printf__7CSystemFPce(&System,s_commandidx_d____d_801d9f3c,iVar8,(int)*(short *)(piVar9 + 0x81));
    iVar8 = iVar8 + 1;
    piVar9 = (int32_t *)((int)piVar9 + 2);
  } while (iVar8 < 8);
  iVar8 = 0;
  pCVar4 = caravanWork;
  do {
    Printf__7CSystemFPce(&System,s_equipidx_d____d_801d9f50,iVar8,(int)pCVar4->m_equipment[0]);
    iVar8 = iVar8 + 1;
    pCVar4 = (CCaravanWork *)((int)&(pCVar4->gObjWork).vtable + 2);
  } while (iVar8 < 4);
  iVar8 = 0;
  pCVar4 = caravanWork;
  do {
    iVar6 = iVar8 + 1;
    iVar2 = 0x40 - iVar6;
    puVar3 = (caravanWork->gObjWork).m_elementResistances + iVar8 + -0x13;
    if (iVar6 < 0x40) {
      do {
        uVar7 = pCVar4->m_inventoryItems[0];
        if ((short)uVar7 < 1) {
          if (0 < (short)puVar3[0x5b]) goto LAB_8009ee88;
        }
        else {
LAB_8009ee88:
          uVar5 = (uint16_t)iVar8;
          if ((short)uVar7 < 1) {
            pCVar4->m_inventoryItems[0] = puVar3[0x5b];
            puVar3[0x5b] = 0xffff;
            if ((short)caravanWork->m_commandListInventorySlotRef[2] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[2] = uVar5;
            }
            if ((short)caravanWork->m_commandListInventorySlotRef[3] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[3] = uVar5;
            }
            if ((short)caravanWork->m_commandListInventorySlotRef[4] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[4] = uVar5;
            }
            if ((short)caravanWork->m_commandListInventorySlotRef[5] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[5] = uVar5;
            }
            if ((short)caravanWork->m_commandListInventorySlotRef[6] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[6] = uVar5;
            }
            if ((short)caravanWork->m_commandListInventorySlotRef[7] == iVar6) {
              caravanWork->m_commandListInventorySlotRef[7] = uVar5;
            }
            if (caravanWork->m_equipment[0] == iVar6) {
              caravanWork->m_equipment[0] = uVar5;
            }
            if (caravanWork->m_equipment[1] == iVar6) {
              caravanWork->m_equipment[1] = uVar5;
            }
            if (caravanWork->m_equipment[2] == iVar6) {
              caravanWork->m_equipment[2] = uVar5;
            }
            if (caravanWork->m_equipment[3] == iVar6) {
              caravanWork->m_equipment[3] = uVar5;
            }
          }
          else {
            uVar1 = puVar3[0x5b];
            if ((0 < (short)uVar1) && ((short)uVar1 < (short)uVar7)) {
              pCVar4->m_inventoryItems[0] = uVar1;
              puVar3[0x5b] = uVar7;
              uVar7 = (uint16_t)iVar6;
              if ((short)caravanWork->m_commandListInventorySlotRef[2] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[2] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[2] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[2] = uVar5;
              }
              if ((short)caravanWork->m_commandListInventorySlotRef[3] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[3] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[3] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[3] = uVar5;
              }
              if ((short)caravanWork->m_commandListInventorySlotRef[4] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[4] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[4] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[4] = uVar5;
              }
              if ((short)caravanWork->m_commandListInventorySlotRef[5] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[5] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[5] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[5] = uVar5;
              }
              if ((short)caravanWork->m_commandListInventorySlotRef[6] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[6] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[6] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[6] = uVar5;
              }
              if ((short)caravanWork->m_commandListInventorySlotRef[7] == iVar8) {
                caravanWork->m_commandListInventorySlotRef[7] = uVar7;
              }
              else if ((short)caravanWork->m_commandListInventorySlotRef[7] == iVar6) {
                caravanWork->m_commandListInventorySlotRef[7] = uVar5;
              }
              if (caravanWork->m_equipment[0] == iVar8) {
                caravanWork->m_equipment[0] = uVar7;
              }
              else if (caravanWork->m_equipment[0] == iVar6) {
                caravanWork->m_equipment[0] = uVar5;
              }
              if (caravanWork->m_equipment[1] == iVar8) {
                caravanWork->m_equipment[1] = uVar7;
              }
              else if (caravanWork->m_equipment[1] == iVar6) {
                caravanWork->m_equipment[1] = uVar5;
              }
              if (caravanWork->m_equipment[2] == iVar8) {
                caravanWork->m_equipment[2] = uVar7;
              }
              else if (caravanWork->m_equipment[2] == iVar6) {
                caravanWork->m_equipment[2] = uVar5;
              }
              if (caravanWork->m_equipment[3] == iVar8) {
                caravanWork->m_equipment[3] = uVar7;
              }
              else if (caravanWork->m_equipment[3] == iVar6) {
                caravanWork->m_equipment[3] = uVar5;
              }
            }
          }
        }
        puVar3 = puVar3 + 1;
        iVar6 = iVar6 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar8 = iVar8 + 1;
    pCVar4 = (CCaravanWork *)((int)&(pCVar4->gObjWork).vtable + 2);
    if (0x3e < iVar8) {
      iVar8 = 0;
      pCVar4 = caravanWork;
      do {
        Printf__7CSystemFPce
                  (&System,s_item_d____d_801d9f2c,iVar8,(int)(short)pCVar4->m_inventoryItems[0]);
        iVar8 = iVar8 + 1;
        pCVar4 = (CCaravanWork *)((int)&(pCVar4->gObjWork).vtable + 2);
      } while (iVar8 < 0x40);
      piVar9 = &(caravanWork->gObjWork).m_objType;
      iVar8 = 2;
      do {
        Printf__7CSystemFPce
                  (&System,s_commandidx_d____d_801d9f3c,iVar8,(int)*(short *)(piVar9 + 0x81));
        iVar8 = iVar8 + 1;
        piVar9 = (int32_t *)((int)piVar9 + 2);
      } while (iVar8 < 8);
      iVar8 = 0;
      do {
        Printf__7CSystemFPce
                  (&System,s_equipidx_d____d_801d9f50,iVar8,(int)caravanWork->m_equipment[0]);
        iVar8 = iVar8 + 1;
        caravanWork = (CCaravanWork *)((int)&(caravanWork->gObjWork).vtable + 2);
      } while (iVar8 < 4);
      return;
    }
  } while( true );
}

