// Function: addRealTime__6CAStarFP10CGPartyObj
// Entry: 80141a68
// Size: 1100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void addRealTime__6CAStarFP10CGPartyObj(CAStar *aStar,CGPartyObj *gPartyObj)

{
  byte bVar1;
  bool bVar2;
  ushort uVar3;
  CAStar *pCVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  byte bVar8;
  CAPos *pCVar9;
  int iVar10;
  
  if ((ushort)aStar->m_lastSeenGroup != (gPartyObj->gCharaObj).m_aStarGroupId) {
    (aStar->m_lastGroupPos).x = (gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition.x;
    (aStar->m_lastGroupPos).y = (gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition.y;
    (aStar->m_lastGroupPos).z = (gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition.z;
    aStar->m_currentGroup = (uint8_t)(gPartyObj->gCharaObj).m_aStarGroupId;
    aStar->m_prevGroup = aStar->m_lastSeenGroup;
    aStar->m_lastSeenGroup = (uint8_t)(gPartyObj->gCharaObj).m_aStarGroupId;
  }
  Printf__8CGraphicFUlUlPce
            (&Graphic,10,10,s_A__GROUP__d_801dd6a8,(int)(gPartyObj->gCharaObj).m_aStarGroupId);
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._8_2_;
  }
  if ((uVar3 & 0x20) == 0) {
    return;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._4_2_;
  }
  if ((uVar3 & 0x40) != 0) {
    bVar1 = aStar->m_prevGroup;
    bVar7 = aStar->m_currentGroup;
    bVar8 = bVar1;
    if (bVar1 < bVar7) {
      bVar8 = bVar7;
      bVar7 = bVar1;
    }
    iVar5 = 0;
    iVar10 = 8;
    pCVar4 = aStar;
    do {
      if (((((((pCVar4->m_portals[0].m_groupA == bVar7) &&
              (iVar6 = iVar5, pCVar4->m_portals[0].m_groupB == bVar8)) ||
             ((pCVar4->m_portals[1].m_groupA == bVar7 &&
              (iVar6 = iVar5 + 1, pCVar4->m_portals[1].m_groupB == bVar8)))) ||
            ((pCVar4->m_portals[2].m_groupA == bVar7 &&
             (iVar6 = iVar5 + 2, pCVar4->m_portals[2].m_groupB == bVar8)))) ||
           ((pCVar4->m_portals[3].m_groupA == bVar7 &&
            (iVar6 = iVar5 + 3, pCVar4->m_portals[3].m_groupB == bVar8)))) ||
          ((((pCVar4->m_portals[4].m_groupA == bVar7 &&
             (iVar6 = iVar5 + 4, pCVar4->m_portals[4].m_groupB == bVar8)) ||
            ((pCVar4->m_portals[5].m_groupA == bVar7 &&
             (iVar6 = iVar5 + 5, pCVar4->m_portals[5].m_groupB == bVar8)))) ||
           ((pCVar4->m_portals[6].m_groupA == bVar7 &&
            (iVar6 = iVar5 + 6, pCVar4->m_portals[6].m_groupB == bVar8)))))) ||
         ((pCVar4->m_portals[7].m_groupA == bVar7 &&
          (iVar6 = iVar5 + 7, pCVar4->m_portals[7].m_groupB == bVar8)))) break;
      pCVar4 = (CAStar *)&pCVar4->m_portals[7].m_position.y;
      iVar5 = iVar5 + 8;
      iVar10 = iVar10 + -1;
      iVar6 = iVar5;
    } while (iVar10 != 0);
    if (iVar6 == 0x40) {
      iVar10 = 0x10;
      iVar5 = 0;
      pCVar4 = aStar;
      do {
        bVar2 = false;
        if ((pCVar4->m_portals[0].m_groupA != '\0') && (pCVar4->m_portals[0].m_groupB != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          aStar->m_portalCount = aStar->m_portalCount + 1;
          iVar6 = iVar5;
          break;
        }
        bVar2 = false;
        iVar6 = iVar5 + 1;
        if ((pCVar4->m_portals[1].m_groupA != '\0') && (pCVar4->m_portals[1].m_groupB != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          aStar->m_portalCount = aStar->m_portalCount + 1;
          break;
        }
        bVar2 = false;
        iVar6 = iVar5 + 2;
        if ((pCVar4->m_portals[2].m_groupA != '\0') && (pCVar4->m_portals[2].m_groupB != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          aStar->m_portalCount = aStar->m_portalCount + 1;
          break;
        }
        bVar2 = false;
        iVar6 = iVar5 + 3;
        if ((pCVar4->m_portals[3].m_groupA != '\0') && (pCVar4->m_portals[3].m_groupB != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          aStar->m_portalCount = aStar->m_portalCount + 1;
          break;
        }
        pCVar4 = (CAStar *)&pCVar4->m_portals[3].m_position.y;
        iVar6 = iVar5 + 4;
        iVar10 = iVar10 + -1;
        iVar5 = iVar6;
      } while (iVar10 != 0);
    }
    pCVar9 = aStar->m_portals + iVar6;
    (pCVar9->m_position).x = (aStar->m_lastGroupPos).x;
    (pCVar9->m_position).y = (aStar->m_lastGroupPos).y;
    (pCVar9->m_position).z = (aStar->m_lastGroupPos).z;
    aStar->m_portals[iVar6].m_groupA = bVar7;
    aStar->m_portals[iVar6].m_groupB = bVar8;
    Printf__7CSystemFPce(&System,&DAT_803320a0);
    iVar5 = 0;
    pCVar4 = aStar;
    do {
      bVar2 = false;
      if ((pCVar4->m_portals[0].m_groupA != '\0') && (pCVar4->m_portals[0].m_groupB != '\0')) {
        bVar2 = true;
      }
      if (bVar2) {
        Printf__7CSystemFPce
                  ((double)pCVar4->m_portals[0].m_position.x,
                   (double)pCVar4->m_portals[0].m_position.y,
                   (double)pCVar4->m_portals[0].m_position.z,&System,
                   s_addAStar___5f____5f____5f___d____801dd6b4,pCVar4->m_portals[0].m_groupA,
                   pCVar4->m_portals[0].m_groupB);
      }
      iVar5 = iVar5 + 1;
      pCVar4 = (CAStar *)&pCVar4->m_portals[0].m_position.y;
    } while (iVar5 < 0x40);
    calcAStar__6CAStarFv(aStar);
  }
  return;
}

