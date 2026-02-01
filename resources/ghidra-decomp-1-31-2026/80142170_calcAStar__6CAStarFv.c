// Function: calcAStar__6CAStarFv
// Entry: 80142170
// Size: 324 bytes

void calcAStar__6CAStarFv(CAStar *aStar)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  CAStar *pCVar7;
  CATemp CStack_a8;
  
  memset(aStar->m_routeTable,0,0x2000);
  uVar6 = 0;
  pCVar7 = aStar;
  do {
    uVar5 = 0;
    do {
      if (uVar5 != uVar6) {
        (aStar->m_bestPath).m_cost = FLOAT_803320ac;
        memset(&CStack_a8,0,0x88);
        check__6CAStarFiiRQ26CAStar6CATemp(aStar,uVar5,uVar6,&CStack_a8);
        if ((aStar->m_bestPath).m_cost < FLOAT_803320ac) {
          Printf__7CSystemFPce(&System,&DAT_801dd6e0,uVar5,uVar6);
          uVar4 = uVar5;
          for (iVar3 = 0; iVar3 < (aStar->m_bestPath).m_pathLength; iVar3 = iVar3 + 1) {
            bVar1 = (aStar->m_bestPath).m_path[iVar3];
            pCVar7->m_routeTable[uVar4][0][1] = bVar1;
            uVar2 = (uint)aStar->m_portals[bVar1].m_groupA;
            if (uVar2 == uVar4) {
              uVar2 = (uint)aStar->m_portals[bVar1].m_groupB;
            }
            pCVar7->m_routeTable[uVar4][0][0] = (uint8_t)uVar2;
            Printf__7CSystemFPce(&System,&DAT_803320b0);
            uVar4 = uVar2;
          }
          Printf__7CSystemFPce(&System,&DAT_803320b4);
        }
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x40);
    uVar6 = uVar6 + 1;
    pCVar7 = (CAStar *)&pCVar7->field_0x2;
  } while ((int)uVar6 < 0x40);
  return;
}

