// Function: addAstar__6CAStarFfffii
// Entry: 80142ce8
// Size: 668 bytes

void addAstar__6CAStarFfffii
               (float param_1,float param_2,float param_3,CAStar *aStar,uint param_5,uint param_6)

{
  bool bVar1;
  float *pfVar2;
  CAStar *pCVar3;
  int iVar4;
  int iVar5;
  CAPos *pCVar6;
  uint uVar7;
  int iVar8;
  CVector aCStack_28 [2];
  
  pfVar2 = (float *)__ct__7CVectorFfff(param_1,param_2,param_3,aCStack_28);
  uVar7 = param_6;
  if ((int)param_6 < (int)param_5) {
    uVar7 = param_5;
    param_5 = param_6;
  }
  iVar4 = 0;
  iVar8 = 8;
  pCVar3 = aStar;
  do {
    if (((((((pCVar3->m_portals[0].m_groupA == param_5) &&
            (iVar5 = iVar4, pCVar3->m_portals[0].m_groupB == uVar7)) ||
           ((pCVar3->m_portals[1].m_groupA == param_5 &&
            (iVar5 = iVar4 + 1, pCVar3->m_portals[1].m_groupB == uVar7)))) ||
          ((pCVar3->m_portals[2].m_groupA == param_5 &&
           (iVar5 = iVar4 + 2, pCVar3->m_portals[2].m_groupB == uVar7)))) ||
         ((pCVar3->m_portals[3].m_groupA == param_5 &&
          (iVar5 = iVar4 + 3, pCVar3->m_portals[3].m_groupB == uVar7)))) ||
        ((((pCVar3->m_portals[4].m_groupA == param_5 &&
           (iVar5 = iVar4 + 4, pCVar3->m_portals[4].m_groupB == uVar7)) ||
          ((pCVar3->m_portals[5].m_groupA == param_5 &&
           (iVar5 = iVar4 + 5, pCVar3->m_portals[5].m_groupB == uVar7)))) ||
         ((pCVar3->m_portals[6].m_groupA == param_5 &&
          (iVar5 = iVar4 + 6, pCVar3->m_portals[6].m_groupB == uVar7)))))) ||
       ((pCVar3->m_portals[7].m_groupA == param_5 &&
        (iVar5 = iVar4 + 7, pCVar3->m_portals[7].m_groupB == uVar7)))) break;
    pCVar3 = (CAStar *)&pCVar3->m_portals[7].m_position.y;
    iVar4 = iVar4 + 8;
    iVar8 = iVar8 + -1;
    iVar5 = iVar4;
  } while (iVar8 != 0);
  if (iVar5 == 0x40) {
    iVar8 = 0x10;
    iVar4 = 0;
    pCVar3 = aStar;
    do {
      bVar1 = false;
      if ((pCVar3->m_portals[0].m_groupA != '\0') && (pCVar3->m_portals[0].m_groupB != '\0')) {
        bVar1 = true;
      }
      if (!bVar1) {
        aStar->m_portalCount = aStar->m_portalCount + 1;
        iVar5 = iVar4;
        break;
      }
      bVar1 = false;
      iVar5 = iVar4 + 1;
      if ((pCVar3->m_portals[1].m_groupA != '\0') && (pCVar3->m_portals[1].m_groupB != '\0')) {
        bVar1 = true;
      }
      if (!bVar1) {
        aStar->m_portalCount = aStar->m_portalCount + 1;
        break;
      }
      bVar1 = false;
      iVar5 = iVar4 + 2;
      if ((pCVar3->m_portals[2].m_groupA != '\0') && (pCVar3->m_portals[2].m_groupB != '\0')) {
        bVar1 = true;
      }
      if (!bVar1) {
        aStar->m_portalCount = aStar->m_portalCount + 1;
        break;
      }
      bVar1 = false;
      iVar5 = iVar4 + 3;
      if ((pCVar3->m_portals[3].m_groupA != '\0') && (pCVar3->m_portals[3].m_groupB != '\0')) {
        bVar1 = true;
      }
      if (!bVar1) {
        aStar->m_portalCount = aStar->m_portalCount + 1;
        break;
      }
      pCVar3 = (CAStar *)&pCVar3->m_portals[3].m_position.y;
      iVar5 = iVar4 + 4;
      iVar8 = iVar8 + -1;
      iVar4 = iVar5;
    } while (iVar8 != 0);
  }
  pCVar6 = aStar->m_portals + iVar5;
  (pCVar6->m_position).x = *pfVar2;
  (pCVar6->m_position).y = pfVar2[1];
  (pCVar6->m_position).z = pfVar2[2];
  aStar->m_portals[iVar5].m_groupA = (uint8_t)param_5;
  aStar->m_portals[iVar5].m_groupB = (uint8_t)uVar7;
  return;
}

