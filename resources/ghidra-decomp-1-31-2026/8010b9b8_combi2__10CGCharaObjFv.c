// Function: combi2__10CGCharaObjFv
// Entry: 8010b9b8
// Size: 1804 bytes

/* WARNING: Removing unreachable block (ram,0x8010c0a8) */
/* WARNING: Removing unreachable block (ram,0x8010b9c8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void combi2__10CGCharaObjFv(void)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  CGPrgObj **ppCVar6;
  CGPrgObj *pCVar7;
  CGPrgObj **ppCVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  short *psVar12;
  int iVar13;
  CGPrgObj *pCVar14;
  CGPrgObj *pCVar15;
  uint uVar16;
  uint uVar17;
  double dVar18;
  double dVar19;
  int local_78;
  CVector CStack_74;
  CVector local_68;
  CGPrgObj *local_5c [5];
  undefined4 local_48;
  uint uStack_44;
  
  iVar13 = 0;
  iVar10 = 0;
  __ct__7CVectorFv(&local_68);
  if ((Game.game.m_partyObjArr[0] != (CGPartyObj *)0x0) &&
     (((iVar4 = (Game.game.m_partyObjArr[0]->gCharaObj).gPrgObj.m_lastStateId, iVar4 == 6 ||
       (iVar4 == 2)) && ((Game.game.m_partyObjArr[0]->gCharaObj).gPrgObj.m_subState == 1)))) {
    local_5c[0] = (CGPrgObj *)Game.game.m_partyObjArr[0];
    iVar13 = 1;
    iVar10 = 4;
  }
  if (((Game.game.m_partyObjArr[1] != (CGPartyObj *)0x0) &&
      ((iVar4 = (Game.game.m_partyObjArr[1]->gCharaObj).gPrgObj.m_lastStateId, iVar4 == 6 ||
       (iVar4 == 2)))) && ((Game.game.m_partyObjArr[1]->gCharaObj).gPrgObj.m_subState == 1)) {
    *(CGPartyObj **)((int)local_5c + iVar10) = Game.game.m_partyObjArr[1];
    iVar13 = iVar13 + 1;
    iVar10 = iVar10 + 4;
  }
  if (((Game.game.m_partyObjArr[2] != (CGPartyObj *)0x0) &&
      ((iVar4 = (Game.game.m_partyObjArr[2]->gCharaObj).gPrgObj.m_lastStateId, iVar4 == 6 ||
       (iVar4 == 2)))) && ((Game.game.m_partyObjArr[2]->gCharaObj).gPrgObj.m_subState == 1)) {
    *(CGPartyObj **)((int)local_5c + iVar10) = Game.game.m_partyObjArr[2];
    iVar13 = iVar13 + 1;
    iVar10 = iVar10 + 4;
  }
  if ((Game.game.m_partyObjArr[3] != (CGPartyObj *)0x0) &&
     (((iVar4 = (Game.game.m_partyObjArr[3]->gCharaObj).gPrgObj.m_lastStateId, iVar4 == 6 ||
       (iVar4 == 2)) && ((Game.game.m_partyObjArr[3]->gCharaObj).gPrgObj.m_subState == 1)))) {
    *(CGPartyObj **)((int)local_5c + iVar10) = Game.game.m_partyObjArr[3];
    iVar13 = iVar13 + 1;
  }
  if (iVar13 != 0) {
    ppCVar8 = local_5c;
    for (iVar10 = 0; iVar10 < iVar13; iVar10 = iVar10 + 1) {
      pCVar14 = *ppCVar8;
      if ((pCVar14 != (CGPrgObj *)0x0) && (pCVar14[1].object.m_bodyOffset.z != 0.0)) {
        dVar19 = (double)FLOAT_80331960;
        uVar16 = 0;
        ppCVar6 = local_5c;
        for (iVar4 = 0; iVar4 < iVar13; iVar4 = iVar4 + 1) {
          if (((iVar10 != iVar4) && (pCVar15 = *ppCVar6, pCVar15 != (CGPrgObj *)0x0)) &&
             ((pCVar15[1].object.m_bodyOffset.z != 0.0 &&
              (dVar18 = (double)PSVECDistance(&pCVar14[1].object.m_jumpOffset,
                                              &pCVar15[1].object.m_jumpOffset), dVar18 < dVar19))))
          {
            uVar16 = 1;
            break;
          }
          ppCVar6 = ppCVar6 + 1;
        }
        if (((uVar16 != 0) &&
            (bVar1 = *(byte *)&pCVar14[1].object.unk_0x168,
            -1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) ||
           ((uVar16 == 0 &&
            (bVar1 = *(byte *)&pCVar14[1].object.unk_0x168,
            (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0)))) {
          *(byte *)&pCVar14[1].object.unk_0x168 =
               (byte)((int)(char)uVar16 << 6) | *(byte *)&pCVar14[1].object.unk_0x168 & 0xbf;
          *(byte *)&pCVar14[1].object.unk_0x168 =
               *(byte *)&pCVar14[1].object.unk_0x168 & 0xef | 0x10;
          playSe3D__8CGPrgObjFiiiiP3Vec
                    (pCVar14,((int)(-uVar16 | uVar16) >> 0x1f) + 0x3d,0x32,0x96,0,0);
        }
      }
      ppCVar8 = ppCVar8 + 1;
    }
    ppCVar8 = local_5c;
    for (iVar10 = 0; iVar10 < iVar13 + -1; iVar10 = iVar10 + 1) {
      iVar9 = iVar10 + 1;
      iVar4 = iVar13 - iVar9;
      ppCVar6 = local_5c + iVar9;
      if (iVar9 < iVar13) {
        do {
          pCVar14 = *ppCVar8;
          if ((int)pCVar14[1].object.m_bodyOffset.x < (int)(*ppCVar6)[1].object.m_bodyOffset.x) {
            *ppCVar8 = *ppCVar6;
            *ppCVar6 = pCVar14;
          }
          ppCVar6 = ppCVar6 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      ppCVar8 = ppCVar8 + 1;
    }
    dVar19 = (double)FLOAT_80331960;
    for (iVar10 = 1; iVar10 < iVar13; iVar10 = iVar10 + 1) {
      ppCVar8 = local_5c + iVar10;
      dVar18 = (double)PSVECDistance(&local_5c[0][1].object.m_jumpOffset,
                                     &(*ppCVar8)[1].object.m_jumpOffset);
      if (dVar19 < dVar18) {
        uVar16 = (iVar13 + -1) - iVar10;
        if (iVar10 < iVar13 + -1) {
          uVar5 = uVar16 >> 3;
          if (uVar5 != 0) {
            do {
              *ppCVar8 = ppCVar8[1];
              ppCVar8[1] = ppCVar8[2];
              ppCVar8[2] = ppCVar8[3];
              ppCVar8[3] = ppCVar8[4];
              ppCVar8[4] = ppCVar8[5];
              ppCVar8[5] = ppCVar8[6];
              ppCVar8[6] = ppCVar8[7];
              ppCVar8[7] = ppCVar8[8];
              ppCVar8 = ppCVar8 + 8;
              uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
            uVar16 = uVar16 & 7;
            if (uVar16 == 0) goto LAB_8010bd24;
          }
          do {
            *ppCVar8 = ppCVar8[1];
            ppCVar8 = ppCVar8 + 1;
            uVar16 = uVar16 - 1;
          } while (uVar16 != 0);
        }
LAB_8010bd24:
        iVar13 = iVar13 + -1;
        iVar10 = iVar10 + -1;
      }
    }
    if (local_5c[0][1].object.m_bodyOffset.x != 0.0) {
      iVar10 = searchCombi__10CGCharaObjFiPP10CGPartyObjRi(iVar13,local_5c,&local_78);
      if (iVar10 < 0) {
        if ((local_78 == 0) || (0x41 < (int)local_5c[0][1].object.m_bodyOffset.x)) {
          local_5c[0][1].object.m_bodyOffset.z = 0.0;
          local_5c[0][1].object.m_bodyOffset.x = 0.0;
          addSubStat__8CGPrgObjFv(local_5c[0]);
          combi2__10CGCharaObjFv();
        }
      }
      else if ((local_78 == 0) || (0x41 < (int)local_5c[0][1].object.m_bodyOffset.x)) {
        uVar16 = 0;
        psVar12 = (short *)(Game.game.unk_flat3_field_1C_0xc7d8 + iVar10 * 0x1a);
        if ((*psVar12 != 0) &&
           (((uVar16 = 1, psVar12[3] != 0 && (uVar16 = 2, psVar12[6] != 0)) &&
            (uVar16 = 3, psVar12[9] != 0)))) {
          uVar16 = 4;
        }
        uVar5 = countLeadingZeros(0x1f8 - (uint)(ushort)psVar12[uVar16 * 3 + -3]);
        uVar5 = uVar5 >> 5 & 0xff;
        if (uVar5 == 0) {
          Identity__7CVectorFv(&local_68);
          ppCVar8 = local_5c;
          for (iVar10 = 0; iVar10 < (int)uVar16; iVar10 = iVar10 + 1) {
            __ct__7CVectorFRC3Vec(&CStack_74,&(*ppCVar8)[1].object.m_jumpOffset);
            PSVECAdd((Vec *)&local_68,(Vec *)&CStack_74,(Vec *)&local_68);
            ppCVar8 = ppCVar8 + 1;
          }
          uStack_44 = uVar16 ^ 0x80000000;
          local_48 = 0x43300000;
          PSVECScale(FLOAT_80331964 /
                     (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331968),
                     (Vec *)&local_68,(Vec *)&local_68);
        }
        Printf__7CSystemFPce(&System,&DAT_801dc590,System.m_frameCounter,psVar12[0xc]);
        pCVar14 = local_5c[uVar16 - 1];
        bVar3 = false;
        ppCVar8 = local_5c;
        for (iVar10 = 0; iVar10 < (int)uVar16; iVar10 = iVar10 + 1) {
          pCVar15 = *ppCVar8;
          fVar11 = -NAN;
          if (uVar5 == 0) {
            pCVar15[1].object.m_jumpOffset.x = local_68.x;
            pCVar15[1].object.m_jumpOffset.y = local_68.y;
            pCVar15[1].object.m_jumpOffset.z = local_68.z;
            if ((bVar3) ||
               (((Game.game.m_gameWork.m_menuStageMode != '\0' &&
                 (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
                ((uVar17 = (**(code **)((int)(pCVar15->object).base_object.object.m_vtable + 0xc))
                                     (pCVar15), (uVar17 & 0x6d) == 0x6d &&
                 ((pCVar15->object).m_scriptHandle[0xed] != (void *)0x0)))))) {
              pCVar15[1].object.base_object.object.m_thisBase = (uint32_t *)0x0;
            }
            else {
              pCVar15[1].object.base_object.object.m_thisBase =
                   (uint32_t *)(uint)(ushort)psVar12[0xc];
              playSe3D__8CGPrgObjFiiiiP3Vec(pCVar15,0x3f,0x32,0x96,0,0);
              bVar3 = true;
            }
          }
          else {
            uVar2 = psVar12[0xc];
            if (uVar2 == 0x20b) {
              fVar11 = 1.4013e-45;
            }
            else if (uVar2 < 0x20b) {
              if (uVar2 == 0x207) {
                fVar11 = 0.0;
              }
            }
            else if (uVar2 == 0x20f) {
              fVar11 = 2.8026e-45;
            }
            if (pCVar15 == pCVar14) {
              pCVar14[1].object.m_capsuleHalfHeight = fVar11;
              playSe3D__8CGPrgObjFiiiiP3Vec(pCVar14,0x3f,0x32,0x96,0,0);
            }
            else {
              pCVar15[1].object.m_jumpOffset.x = (pCVar14->object).m_worldPosition.x;
              pCVar15[1].object.m_jumpOffset.y = (pCVar14->object).m_worldPosition.y;
              pCVar15[1].object.m_jumpOffset.z = (pCVar14->object).m_worldPosition.z;
              pCVar15[1].object.base_object.object.m_thisBase = (uint32_t *)0x0;
            }
          }
          pCVar15[1].object.m_bodyOffset.z = 0.0;
          pCVar15[1].object.m_bodyOffset.x = 0.0;
          addSubStat__8CGPrgObjFv(pCVar15);
          putComboParticle__10CGPartyObjFv(pCVar15);
          pCVar15[1].object.m_bodyEllipsoidOffset = (float)(uint)(ushort)psVar12[0xc];
          pCVar15[1].object.m_bodyEllipsoidAspect = fVar11;
          pCVar15[1].object.m_nearColRadius = 0.0;
          ppCVar6 = local_5c;
          for (uVar17 = uVar16; uVar17 != 0; uVar17 = uVar17 - 1) {
            pCVar7 = *ppCVar6;
            if (pCVar15 != pCVar7) {
              fVar11 = pCVar15[1].object.m_nearColRadius;
              pCVar15[1].object.m_nearColRadius = (float)((int)fVar11 + 1);
              *(CGPrgObj **)(pCVar15[1].object.m_animQueue + (int)fVar11 * 4 + 0x7e) = pCVar7;
            }
            ppCVar6 = ppCVar6 + 1;
          }
          ppCVar8 = ppCVar8 + 1;
        }
        combi2__10CGCharaObjFv();
      }
    }
  }
  return;
}

