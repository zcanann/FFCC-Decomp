// Function: SearchRomLetterWork__12CCaravanWorkFPP14CRomLetterWorki
// Entry: 800a077c
// Size: 4916 bytes

/* WARNING: Removing unreachable block (ram,0x800a16a0) */
/* WARNING: Removing unreachable block (ram,0x800a16c8) */
/* WARNING: Removing unreachable block (ram,0x800a1744) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SearchRomLetterWork__12CCaravanWorkFPP14CRomLetterWorki
               (CCaravanWork *caravanWork,CRomLetterWork *romLetterWork,int param_3)

{
  byte bVar1;
  uint in_r0;
  int iVar2;
  int iVar3;
  CRomLetterWork CVar4;
  int iVar5;
  uint in_r10;
  uint in_r11;
  uint in_r12;
  CRomLetterWork *pCVar6;
  int iVar7;
  uint uVar8;
  CRomLetterWork CVar9;
  ushort uVar10;
  int iVar11;
  CCaravanWork *pCVar12;
  ushort uVar13;
  uint uVar14;
  int iVar15;
  
  iVar3 = 0;
  iVar5 = 0;
  iVar7 = 0;
  if (0 < param_3) {
    if ((8 < param_3) && (uVar14 = param_3 - 1U >> 3, pCVar6 = romLetterWork, 0 < param_3 + -8)) {
      do {
        *pCVar6 = (CRomLetterWork)0x0;
        iVar7 = iVar7 + 8;
        pCVar6[1] = (CRomLetterWork)0x0;
        pCVar6[2] = (CRomLetterWork)0x0;
        pCVar6[3] = (CRomLetterWork)0x0;
        pCVar6[4] = (CRomLetterWork)0x0;
        pCVar6[5] = (CRomLetterWork)0x0;
        pCVar6[6] = (CRomLetterWork)0x0;
        pCVar6[7] = (CRomLetterWork)0x0;
        pCVar6 = pCVar6 + 8;
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
    iVar2 = param_3 - iVar7;
    pCVar6 = romLetterWork + iVar7;
    if (iVar7 < param_3) {
      do {
        *pCVar6 = (CRomLetterWork)0x0;
        pCVar6 = pCVar6 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  iVar7 = 0;
  CVar4 = (CRomLetterWork)Game.game.unkCFlatData0[3];
  do {
    uVar10 = *(ushort *)((int)CVar4 + 0x18);
    if ((uVar10 & 0x7fff) == 0) {
LAB_800a0f20:
      uVar10 = *(ushort *)((int)CVar4 + 0x1a);
      if ((uVar10 & 0x7fff) != 0) {
        if ((uVar10 & 1) != 0) {
          if (caravanWork->unk_0x3ac == 0) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 2) != 0) {
          if (caravanWork->unk_0x3ac == 1) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 4) != 0) {
          if (caravanWork->unk_0x3ac == 2) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 8) != 0) {
          if (caravanWork->unk_0x3ac == 3) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 0x10) != 0) {
          if (caravanWork->unk_0x3ac == 4) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 0x20) != 0) {
          if (caravanWork->unk_0x3ac == 5) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 0x40) != 0) {
          if (caravanWork->unk_0x3ac == 6) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 0x80) != 0) {
          if (caravanWork->unk_0x3ac == 7) {
            if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
          }
          else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
        }
        if ((uVar10 & 0x100) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 1) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x200) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 2) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x400) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 3) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x800) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 4) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x1000) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 5) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x2000) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 6) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x4000) != 0) {
          if (*(char *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 7) == '\0') {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a1254;
        }
        if ((uVar10 & 0x8000) == 0) goto LAB_800a1a94;
      }
LAB_800a1254:
      uVar10 = *(ushort *)((int)CVar4 + 0x1c);
      if ((uVar10 & 0x7fff) != 0) {
        if ((uVar10 & 1) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 1) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 2) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 2) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 4) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 3) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 8) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 4) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x10) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 5) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x20) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 6) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x40) != 0) {
          if (*(byte *)((int)Game.game.m_gameWork.m_linkTable +
                       *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 7) < 0x3d) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x100) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 1);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x200) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 2);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x400) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 3);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x800) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 4);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x1000) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 5);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x2000) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 6);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x4000) != 0) {
          bVar1 = *(byte *)((int)Game.game.m_gameWork.m_linkTable +
                           *(int *)&(caravanWork->gObjWork).m_saveSlot * 0x208 + 7);
          if ((bVar1 == 0) || (0x28 < bVar1)) {
            if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
          }
          else if ((uVar10 & 0x8000) == 0) goto LAB_800a165c;
        }
        if ((uVar10 & 0x8000) == 0) goto LAB_800a1a94;
      }
LAB_800a165c:
      iVar2 = 4;
      uVar14 = in_r0;
      CVar9 = CVar4;
      do {
        uVar10 = *(ushort *)((int)CVar9 + 0x1e);
        uVar13 = uVar10 >> 0xb & 3;
        in_r0 = uVar14;
        if (uVar13 != 3) {
          uVar8 = uVar10 & 0x7ff;
          if (uVar13 == 1) {
            in_r0 = (uint)Game.game.m_gameWork.m_eventWork[uVar8 + 4];
          }
          else if (uVar13 == 0) {
            in_r0 = Game.game.m_gameWork.m_scriptGlobalTime;
            if (uVar8 != 2) {
              if (uVar8 < 2) {
                in_r0 = Game.game.m_gameWork._8_4_;
                if ((uVar10 & 0x7ff) != 0) {
                  in_r0 = Game.game.m_gameWork.m_timerA;
                }
              }
              else {
                in_r0 = uVar14;
                if (uVar8 < 4) {
                  in_r0 = Game.game.m_gameWork.m_frameCounter;
                }
              }
            }
          }
          else if (uVar13 < 3) {
            in_r0 = (uint)caravanWork->m_evtWordArr[uVar8];
          }
          uVar14 = (int)(uint)uVar10 >> 0xd;
          uVar8 = (uint)*(ushort *)((int)CVar9 + 0x20);
          if (uVar14 == 3) {
            if ((int)uVar8 < (int)in_r0) goto LAB_800a1a94;
          }
          else if (uVar14 < 3) {
            if (uVar14 == 1) {
              if (in_r0 == uVar8) goto LAB_800a1a94;
            }
            else if (uVar14 == 0) {
              if (in_r0 != uVar8) goto LAB_800a1a94;
            }
            else if ((int)in_r0 < (int)uVar8) goto LAB_800a1a94;
          }
          else if (uVar14 == 5) {
            if ((int)uVar8 <= (int)in_r0) goto LAB_800a1a94;
          }
          else if ((uVar14 < 5) && ((int)in_r0 <= (int)uVar8)) goto LAB_800a1a94;
        }
        CVar9 = (CRomLetterWork)((int)CVar9 + 4);
        iVar2 = iVar2 + -1;
        uVar14 = in_r0;
      } while (iVar2 != 0);
      iVar2 = 0;
      CVar9 = CVar4;
      do {
        uVar10 = *(ushort *)((int)CVar9 + 0x2e);
        uVar13 = uVar10 >> 0xb & 3;
        if (uVar13 == 3) goto switchD_800a196c_caseD_8;
        uVar14 = (uint)uVar10;
        uVar8 = uVar14 & 0x7ff;
        if (uVar13 == 2) {
          in_r10 = -((uint)*(byte *)((int)caravanWork->m_evtWorkArr + ((int)uVar8 >> 3)) &
                    1 << (uVar14 & 7)) >> 0x1f;
          in_r11 = -((uint)*(byte *)((int)caravanWork->m_evtWorkArr + ((int)(uVar8 + 1) >> 3)) &
                    1 << (uVar8 + 1 & 7)) >> 0x1f;
          in_r12 = -((uint)*(byte *)((int)caravanWork->m_evtWorkArr + ((int)(uVar8 + 2) >> 3)) &
                    1 << (uVar8 + 2 & 7)) >> 0x1f;
        }
        else if ((uVar13 < 2) && (uVar13 != 0)) {
          in_r10 = -((uint)(byte)Game.game.m_gameWork.m_eventFlags[((int)uVar8 >> 3) + 8] &
                    1 << (uVar14 & 7)) >> 0x1f;
          in_r11 = -((uint)(byte)Game.game.m_gameWork.m_eventFlags[((int)(uVar8 + 1) >> 3) + 8] &
                    1 << (uVar8 + 1 & 7)) >> 0x1f;
          in_r12 = -((uint)(byte)Game.game.m_gameWork.m_eventFlags[((int)(uVar8 + 2) >> 3) + 8] &
                    1 << (uVar8 + 2 & 7)) >> 0x1f;
        }
        uVar14 = in_r10;
        switch(uVar10 >> 0xd) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          if (in_r10 == 0) goto joined_r0x800a19d8;
          goto LAB_800a1a94;
        case 3:
          if ((in_r10 == 0) && (uVar14 = in_r12, in_r11 == 0)) break;
          goto switchD_800a196c_caseD_8;
        case 4:
          goto joined_r0x800a19d8;
        case 5:
joined_r0x800a19d8:
          uVar14 = in_r12;
          if (in_r11 != 0) goto LAB_800a1a94;
          break;
        case 6:
          goto joined_r0x800a1a00;
        case 7:
joined_r0x800a1a00:
          uVar14 = in_r12;
          if (in_r11 == 0) goto LAB_800a1a94;
          break;
        default:
          goto switchD_800a196c_caseD_8;
        }
        if (uVar14 == 0) goto LAB_800a1a94;
switchD_800a196c_caseD_8:
        iVar2 = iVar2 + 1;
        CVar9 = (CRomLetterWork)((int)CVar9 + 2);
      } while (iVar2 < 8);
      if (iVar3 == param_3) {
        uVar10 = 0xffff;
        iVar2 = 0;
        iVar15 = 0;
        pCVar6 = romLetterWork;
        iVar11 = param_3;
        if (0 < param_3) {
          do {
            uVar13 = *(ushort *)((int)*pCVar6 + 6) & 0xf00;
            if (uVar13 < uVar10) {
              iVar2 = iVar15;
              uVar10 = uVar13;
            }
            pCVar6 = pCVar6 + 1;
            iVar15 = iVar15 + 1;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
        }
        if (uVar10 < (*(ushort *)((int)CVar4 + 6) & 0xf00)) {
          romLetterWork[iVar2] = CVar4;
        }
      }
      else {
        *(CRomLetterWork *)(&romLetterWork->field_0x0 + iVar5) = CVar4;
        iVar3 = iVar3 + 1;
        iVar5 = iVar5 + 4;
      }
    }
    else if ((uVar10 & 1) == 0) {
LAB_800a085c:
      if ((uVar10 & 2) != 0) {
        if (caravanWork->m_tribeId == 1) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 4) != 0) {
        if (caravanWork->m_tribeId == 2) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 8) != 0) {
        if (caravanWork->m_tribeId == 3) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x10) != 0) {
        if (caravanWork->m_genderFlag == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x20) != 0) {
        if (caravanWork->m_genderFlag == 1) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x40) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 0) && (caravanWork->m_letterMeta[0] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -1) && (caravanWork->m_letterMeta[0] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -2) && (caravanWork->m_letterMeta[0] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -3) && (caravanWork->m_letterMeta[0] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x80) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 1) && (caravanWork->m_letterMeta[1] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 0) && (caravanWork->m_letterMeta[1] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -1) && (caravanWork->m_letterMeta[1] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -2) && (caravanWork->m_letterMeta[1] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x100) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 2) && (caravanWork->m_letterMeta[2] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 1) && (caravanWork->m_letterMeta[2] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 0) && (caravanWork->m_letterMeta[2] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != -1) && (caravanWork->m_letterMeta[2] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x200) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 3) && (caravanWork->m_letterMeta[3] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 2) && (caravanWork->m_letterMeta[3] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 1) && (caravanWork->m_letterMeta[3] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 0) && (caravanWork->m_letterMeta[3] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x400) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 4) && (caravanWork->m_letterMeta[4] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 3) && (caravanWork->m_letterMeta[4] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 2) && (caravanWork->m_letterMeta[4] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 1) && (caravanWork->m_letterMeta[4] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x800) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 5) && (caravanWork->m_letterMeta[5] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 4) && (caravanWork->m_letterMeta[5] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 3) && (caravanWork->m_letterMeta[5] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 2) && (caravanWork->m_letterMeta[5] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x1000) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 6) && (caravanWork->m_letterMeta[6] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 5) && (caravanWork->m_letterMeta[6] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 4) && (caravanWork->m_letterMeta[6] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 3) && (caravanWork->m_letterMeta[6] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x2000) != 0) {
        iVar11 = 0;
        iVar2 = 0;
        iVar15 = 2;
        pCVar12 = caravanWork;
        do {
          if ((iVar2 != 7) && (caravanWork->m_letterMeta[7] < pCVar12->m_letterMeta[0])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 6) && (caravanWork->m_letterMeta[7] < pCVar12->m_letterMeta[1])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 5) && (caravanWork->m_letterMeta[7] < pCVar12->m_letterMeta[2])) {
            iVar11 = iVar11 + 1;
          }
          if ((iVar2 != 4) && (caravanWork->m_letterMeta[7] < pCVar12->m_letterMeta[3])) {
            iVar11 = iVar11 + 1;
          }
          pCVar12 = (CCaravanWork *)&(pCVar12->gObjWork).m_saveSlot;
          iVar2 = iVar2 + 4;
          iVar15 = iVar15 + -1;
        } while (iVar15 != 0);
        if (iVar11 == 0) {
          if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        }
        else if ((uVar10 & 0x8000) != 0) goto LAB_800a1a94;
      }
      if ((uVar10 & 0x8000) != 0) goto LAB_800a0f20;
    }
    else {
      if (caravanWork->m_tribeId == 0) {
        if ((uVar10 & 0x8000) == 0) goto LAB_800a0f20;
        goto LAB_800a085c;
      }
      if ((uVar10 & 0x8000) == 0) goto LAB_800a085c;
    }
LAB_800a1a94:
    iVar7 = iVar7 + 1;
    CVar4 = (CRomLetterWork)((int)CVar4 + 0x3e);
    if (0x1ff < iVar7) {
      return;
    }
  } while( true );
}

