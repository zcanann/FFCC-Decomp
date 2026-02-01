// Function: CalcCharaSelect__8CMenuPcsFv
// Entry: 800f0a70
// Size: 5544 bytes

/* WARNING: Removing unreachable block (ram,0x800f0cf0) */
/* WARNING: Removing unreachable block (ram,0x800f0d38) */
/* WARNING: Removing unreachable block (ram,0x800f1538) */
/* WARNING: Removing unreachable block (ram,0x800f15a0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcCharaSelect__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  uint uVar6;
  undefined uVar13;
  ushort uVar11;
  int iVar7;
  int iVar8;
  int *piVar9;
  short sVar12;
  CCaravanWork *pCVar10;
  char *pcVar14;
  ushort *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  short sVar19;
  int iVar20;
  CCaravanWork *caravanWork;
  CFont *font;
  ushort *puVar21;
  int iVar22;
  CMenuPcs *pCVar23;
  int iVar24;
  int *piVar25;
  uint uVar26;
  int iVar27;
  int iVar28;
  double dVar29;
  ushort local_a8 [8];
  undefined4 local_98;
  int local_94;
  undefined4 local_90;
  undefined auStack_8c [6];
  char local_86;
  undefined auStack_85 [17];
  byte local_74;
  undefined local_73;
  undefined local_72;
  byte abStack_71 [4];
  byte local_6d;
  double local_68;
  longlong local_50;
  
  *(short *)&menuPcs->field_0x74 = *(short *)&menuPcs->field_0x74 + 1;
  uVar6 = countLeadingZeros((uint)Game.game.m_gameWork.m_menuStageMode);
  if ((int)(((uVar6 >> 5) + 2) * 0x4b) <= (int)*(short *)&menuPcs->field_0x74) {
    *(undefined2 *)&menuPcs->field_0x74 = 0;
  }
  puVar15 = local_a8 + 4;
  puVar21 = local_a8;
  bVar3 = false;
  bVar4 = false;
  uVar6 = 0;
  iVar20 = 0;
  do {
    piVar25 = (int *)(*(int *)&menuPcs->field_0x828 + iVar20);
    if ((uVar6 == 0) || (Game.game.m_gameWork.m_menuStageMode == '\0')) {
      iVar22 = GetPadType__6JoyBusFi(&Joybus,uVar6);
      *piVar25 = iVar22;
      iVar22 = *piVar25;
      if ((iVar22 == 0x9000000) || ((iVar22 == -0x74f00000 || (iVar22 == -0x78000000)))) {
        if (Game.game.m_gameWork.m_menuStageMode == '\0') {
          *(undefined *)((int)piVar25 + 0xd) = 0;
        }
        else {
          *(undefined *)((int)piVar25 + 0xd) = 1;
        }
      }
      else {
        uVar13 = GetGBAConnect__6JoyBusFi(&Joybus,uVar6);
        *(undefined *)((int)piVar25 + 0xd) = uVar13;
      }
      if ((*(char *)((int)piVar25 + 0xd) == '\x01') && (*(char *)((int)piVar25 + 0xb) == '\0')) {
        bVar5 = false;
        if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
          bVar5 = true;
        }
        if (bVar5) {
          uVar11 = 0;
        }
        else {
          uVar11 = *(ushort *)
                    (&Pad.field_0x14 +
                    (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        *puVar15 = uVar11;
        bVar5 = false;
        if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
          bVar5 = true;
        }
        if (bVar5) {
          uVar11 = 0;
        }
        else {
          uVar11 = *(ushort *)
                    (&Pad.field_0x8 +
                    (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        *puVar21 = uVar11;
      }
      else {
        *puVar15 = 0;
        *puVar21 = 0;
      }
    }
    else {
      *puVar15 = 0;
      *puVar21 = 0;
      *(undefined *)((int)piVar25 + 0xd) = 0;
    }
    uVar6 = uVar6 + 1;
    puVar15 = puVar15 + 1;
    puVar21 = puVar21 + 1;
    iVar20 = iVar20 + 0x10;
  } while ((int)uVar6 < 4);
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) == 0)) {
    sVar12 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
    if (sVar12 == 3) {
      uVar6 = 0;
      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0xb) != '\0') {
          uVar6 = 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
        }
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1b) != '\0') {
          uVar6 = uVar6 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
        }
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2b) != '\0') {
          uVar6 = uVar6 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
        }
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3b) != '\0') {
          uVar6 = uVar6 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
        }
      }
      iVar22 = 0;
      iVar20 = 0;
      do {
        if (Game.game.m_gameWork.m_menuStageMode != '\0') break;
        iVar24 = *(int *)&menuPcs->field_0x828 + iVar20;
        if (*(char *)(iVar24 + 0xd) == '\0') {
          ClrCmakeInfo__8GbaQueueFi(&GbaQue,iVar22);
          if (*(char *)(iVar24 + 0xc) == '\x01') {
            *(undefined *)(iVar24 + 0xc) = 0;
          }
          else if ((uVar6 & 1 << (int)*(short *)(iVar24 + 4)) != 0) goto LAB_800f1050;
          if (Game.game.m_caravanWorkArr[*(short *)(iVar24 + 4)].m_shopState == 0) {
            iVar8 = *(short *)(iVar24 + 4) * 4;
            iVar7 = IsModelLoaded__Q29CCharaPcs7CHandleFi
                              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar8),1);
            if (((iVar7 != 0) && (**(int **)(&menuPcs->field_0x7f4 + iVar8) != 3)) &&
               (*(char *)(iVar24 + 0xc) != '\x01')) {
              if (2 < (uint)System.m_execParam) {
                Printf__7CSystemFPce
                          (&System,s_chan____d_cur____d_801dc3d8,iVar22,(int)*(short *)(iVar24 + 4))
                ;
              }
              sVar12 = *(short *)(iVar24 + 4);
              *(undefined *)(*(int *)&menuPcs->field_0x824 + sVar12 * 0x34 + 0xc) = 0;
              LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
                        (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + sVar12 * 4),3,0x43,0);
            }
          }
        }
        else if ((*(char *)(iVar24 + 0xb) == '\0') &&
                (iVar24 = GetMType__6JoyBusFi(&Joybus,iVar22), iVar24 == 1)) {
          SetMType__6JoyBusFii(&Joybus,iVar22,4);
        }
LAB_800f1050:
        iVar22 = iVar22 + 1;
        iVar20 = iVar20 + 0x10;
      } while (iVar22 < 4);
      uVar26 = 0;
      if (*(char *)(*(int *)&menuPcs->field_0x828 + 10) != '\0') {
        uVar26 = 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
      }
      if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1a) != '\0') {
        uVar26 = uVar26 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
      }
      if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2a) != '\0') {
        uVar26 = uVar26 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
      }
      if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3a) != '\0') {
        uVar26 = uVar26 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
      }
      iVar24 = 0;
      iVar20 = -0x7fde1140;
      iVar22 = 0;
      pCVar23 = menuPcs;
      do {
        if ((((uVar26 & 1 << iVar24) == 0) && ((uVar6 & 1 << iVar24) == 0)) &&
           (*(int *)(iVar20 + 0x1794) == 0)) {
          iVar8 = IsModelLoaded__Q29CCharaPcs7CHandleFi
                            (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar24 * 4),1);
          if ((iVar8 != 0) && (**(int **)(&menuPcs->field_0x7f4 + iVar24 * 4) != 3)) {
            *(undefined *)(*(int *)&menuPcs->field_0x824 + iVar22 + 0xc) = 0;
            LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
                      (*(CCharaPcsCHandle **)&pCVar23->field_0x7f4,3,0x43,0);
          }
        }
        iVar24 = iVar24 + 1;
        iVar22 = iVar22 + 0x34;
        pCVar23 = (CMenuPcs *)&pCVar23->field_0x4;
        iVar20 = iVar20 + 0xc30;
      } while (iVar24 < 8);
      iVar24 = 0;
      uVar6 = 0;
      iVar22 = 4;
      iVar7 = 0;
      iVar20 = 0;
      iVar8 = 0;
      do {
        iVar18 = *(int *)&menuPcs->field_0x828 + iVar20;
        if (*(char *)(iVar18 + 0xd) != '\0') {
          uVar6 = uVar6 | 1 << iVar24;
          iVar8 = iVar8 + 1;
          if ((*(char *)(iVar18 + 10) != '\0') &&
             (Game.game.m_caravanWorkArr[*(short *)(iVar18 + 4)].m_caravanLocalFlags != '\0')) {
            iVar7 = iVar7 + 1;
          }
        }
        iVar20 = iVar20 + 0x10;
        iVar24 = iVar24 + 1;
        iVar22 = iVar22 + -1;
      } while (iVar22 != 0);
      if ((iVar8 == 0) || (iVar8 != iVar7)) {
        puVar21 = local_a8 + 7;
        puVar15 = local_a8 + 3;
        iVar22 = 3;
        iVar20 = 0x30;
        do {
          piVar25 = (int *)(*(int *)&menuPcs->field_0x828 + iVar20);
          if (*(char *)(piVar25 + 3) == '\x01') {
            *(undefined *)((int)piVar25 + 10) = 1;
            *(undefined *)((int)piVar25 + 0xb) = 0;
            *(undefined *)(piVar25 + 3) = 0;
            GetCMakeInfo__8GbaQueueFiP12GbaCMakeInfo(&GbaQue,iVar22,auStack_8c);
            iVar27 = (int)local_86;
            iVar24 = (local_74 & 3) * 200;
            iVar18 = iVar24 + 100;
            if ((int)(uint)local_74 >> 7 != 0) {
              iVar18 = iVar24 + 200;
            }
            *(uint *)(*(int *)&menuPcs->field_0x824 + iVar27 * 0x34 + 8) =
                 iVar18 + (local_74 >> 2 & 3);
            caravanWork = Game.game.m_caravanWorkArr + iVar27;
            LoadInit__12CCaravanWorkFv(caravanWork);
            Game.game.m_caravanWorkArr[iVar27].m_shopState = 1;
            Game.game.m_caravanWorkArr[iVar27].unk_0x3a8 = (uint)CONCAT11(local_73,local_72);
            Game.game.m_caravanWorkArr[iVar27].unk_0x3ac = (uint)local_6d;
            memset(iVar27 * 0xc30 + -0x7fddf986,0,0x11);
            strcpy(iVar27 * 0xc30 + -0x7fddf986,auStack_85);
            Game.game.m_caravanWorkArr[iVar27].m_tribeId = local_74 & 3;
            uVar11 = local_74 >> 2 & 3;
            Game.game.m_caravanWorkArr[iVar27].m_appearanceVariant = uVar11;
            sVar12 = (local_74 & 3) * 200;
            Game.game.m_caravanWorkArr[iVar27].m_genderFlag =
                 (ushort)((uint)-((int)(uint)local_74 >> 7) >> 0x1f);
            sVar19 = sVar12 + 100;
            if ((int)(uint)local_74 >> 7 != 0) {
              sVar19 = sVar12 + 200;
            }
            Game.game.m_caravanWorkArr[iVar27].gObjWork.m_id = sVar19 + uVar11;
            iVar24 = 0;
            iVar18 = 2;
            pCVar10 = caravanWork;
            do {
              pCVar10->m_letterMeta[0] = (10 - (abStack_71[iVar24 >> 1] & 0xf)) * 10 - 5;
              bVar1 = abStack_71[(int)(iVar24 + 1U) >> 1];
              if ((iVar24 + 1U & 1) != 0) {
                bVar1 = bVar1 >> 4;
              }
              pCVar10->m_letterMeta[1] = (10 - (bVar1 & 0xf)) * 10 - 5;
              pCVar10->m_letterMeta[2] = (10 - (abStack_71[iVar24 + 2 >> 1] & 0xf)) * 10 - 5;
              bVar1 = abStack_71[(int)(iVar24 + 3U) >> 1];
              if ((iVar24 + 3U & 1) != 0) {
                bVar1 = bVar1 >> 4;
              }
              iVar24 = iVar24 + 4;
              pCVar10->m_letterMeta[3] = (10 - (bVar1 & 0xf)) * 10 - 5;
              pCVar10 = (CCaravanWork *)&(pCVar10->gObjWork).m_saveSlot;
              iVar18 = iVar18 + -1;
            } while (iVar18 != 0);
            iVar24 = (uint)Game.game.m_caravanWorkArr[iVar27].m_genderFlag +
                     (uint)Game.game.m_caravanWorkArr[iVar27].m_tribeId * 2;
            (**(code **)((int)(caravanWork->gObjWork).vtable + 0xc))
                      (caravanWork,iVar24,Game.game.unkCFlatData0[0] + iVar24 * 0x1d0,
                       Game.game.m_caravanWorkArr[iVar27].m_appearanceVariant);
            LoadFinished__12CCaravanWorkFv(caravanWork);
            local_98 = 0;
            local_90 = 0;
            local_94 = iVar27;
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                      (&CFlat,0,1,4,3,&local_98,(CStack *)0x0);
            PlaySe__6CSoundFiiii(&Sound,0x33,0x40,0x7f,0);
            *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(piVar25 + 1) * 0x14 + 4) = 3;
          }
          if (*(char *)((int)piVar25 + 0xd) == '\0') {
            if (*(char *)((int)piVar25 + 10) != '\0') {
              *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(piVar25 + 1) * 0x14 + 4) =
                   0;
            }
            *(undefined *)((int)piVar25 + 10) = 0;
            *(undefined *)((int)piVar25 + 0xb) = 0;
            *(undefined *)(piVar25 + 3) = 0;
            if (*(ushort *)(piVar25 + 2) < 0x3c) {
              *(ushort *)(piVar25 + 2) = *(ushort *)(piVar25 + 2) + 1;
            }
            *puVar21 = 0;
            *puVar15 = 0;
          }
          else {
            uVar11 = *puVar21;
            *(undefined2 *)(piVar25 + 2) = 0;
            iVar24 = (int)*(short *)(piVar25 + 1);
            if ((uVar11 & 0xc) != 0) {
              if (*(char *)((int)piVar25 + 10) == '\0') {
                if (iVar24 < 4) {
                  iVar24 = iVar24 + 4;
                }
                else {
                  iVar24 = iVar24 + -4;
                }
                PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
              }
              else {
                PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
              }
            }
            uVar26 = iVar24 >> 2;
            if ((*puVar21 & 1) == 0) {
              if ((*puVar21 & 2) != 0) {
                if (*(char *)((int)piVar25 + 10) == '\0') {
                  iVar18 = 3;
                  if (uVar26 != 0) {
                    iVar18 = 7;
                  }
                  if (iVar24 < iVar18) {
                    iVar24 = iVar24 + 1;
                  }
                  else {
                    iVar24 = iVar24 + -3;
                  }
                  PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
                }
                else {
                  PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                }
              }
            }
            else if (*(char *)((int)piVar25 + 10) == '\0') {
              if ((int)((int)(-uVar26 | uVar26) >> 0x1f & 4U) < iVar24) {
                iVar24 = iVar24 + -1;
              }
              else {
                iVar24 = iVar24 + 3;
              }
              PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
            }
            else {
              PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
            }
            uVar11 = *puVar21;
            *(short *)(piVar25 + 1) = (short)iVar24;
            if ((uVar11 & 0x6f) == 0) {
              iVar18 = (int)*(short *)(piVar25 + 1);
              uVar11 = *puVar15;
              if (((uVar11 & 0x100) == 0) ||
                 (Game.game.m_caravanWorkArr[iVar18].m_shopBusyFlag == '\0')) {
                if (((uVar11 & 0x100) == 0) || (*(char *)((int)piVar25 + 10) != '\0')) {
                  if (((uVar11 & 0x100) == 0) || (*(char *)((int)piVar25 + 10) == '\0')) {
                    if ((uVar11 & 0x200) == 0) {
                      if ((uVar11 & 0x1000) != 0) {
                        bVar4 = true;
                      }
                    }
                    else if (*(char *)((int)piVar25 + 10) == '\0') {
                      bVar3 = true;
                    }
                    else {
                      *(undefined *)((int)piVar25 + 10) = 0;
                      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar24 * 0x14 + 4) = 0;
                      PlaySe__6CSoundFiiii(&Sound,0x34,0x40,0x7f,0);
                    }
                  }
                  else {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  }
                }
                else if (*(int *)(*(int *)&menuPcs->field_0x824 + iVar24 * 0x34 + 8) < 0) {
                  if ((Game.game.m_gameWork.m_menuStageMode == '\0') &&
                     ((*piVar25 == 0x9000000 || (*piVar25 == -0x74f00000)))) {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  }
                  else {
                    iVar27 = 0;
                    iVar24 = 0;
                    iVar28 = 4;
                    do {
                      if (((iVar22 != iVar27) &&
                          (iVar16 = *(int *)&menuPcs->field_0x828 + iVar24,
                          *(char *)(iVar16 + 0xb) != '\0')) && (iVar18 == *(short *)(iVar16 + 4))) {
                        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                        break;
                      }
                      iVar24 = iVar24 + 0x10;
                      iVar27 = iVar27 + 1;
                      iVar28 = iVar28 + -1;
                    } while (iVar28 != 0);
                    if (3 < iVar27) {
                      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
                        InitCmakeInfo__8GbaQueueFii
                                  (&GbaQue,iVar22,(char)*(undefined2 *)(piVar25 + 1));
                        *(undefined *)((int)piVar25 + 0xb) = 1;
                      }
                      else {
                        *(undefined2 *)&menuPcs->field_0x86a = *(undefined2 *)(piVar25 + 1);
                      }
                      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                    }
                  }
                }
                else {
                  iVar28 = 0;
                  iVar27 = 0;
                  iVar16 = 4;
                  do {
                    if (((iVar22 != iVar28) &&
                        (iVar17 = *(int *)&menuPcs->field_0x828 + iVar27,
                        *(char *)(iVar17 + 10) != '\0')) && (iVar18 == *(short *)(iVar17 + 4))) {
                      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                      break;
                    }
                    iVar27 = iVar27 + 0x10;
                    iVar28 = iVar28 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                  if (3 < iVar28) {
                    if (Game.game.m_caravanWorkArr[iVar18].m_caravanLocalFlags == '\0') {
                      *(undefined *)((int)piVar25 + 10) = 1;
                      PlaySe__6CSoundFiiii(&Sound,0x33,0x40,0x7f,0);
                      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar24 * 0x14 + 4) = 3;
                    }
                    else if (Game.game.m_gameWork.m_menuStageMode == '\0') {
                      if (iVar8 == iVar7 + 1) {
                        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                      }
                      else {
                        *(undefined *)((int)piVar25 + 10) = 1;
                        iVar7 = iVar7 + 1;
                        PlaySe__6CSoundFiiii(&Sound,0x33,0x40,0x7f,0);
                        *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar24 * 0x14 + 4) = 3;
                      }
                    }
                    else {
                      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                    }
                  }
                }
              }
              else {
                PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
              }
            }
          }
          iVar22 = iVar22 + -1;
          puVar21 = puVar21 + -1;
          puVar15 = puVar15 + -1;
          iVar20 = iVar20 + -0x10;
        } while (-1 < iVar22);
        if (bVar3) {
          iVar20 = *(int *)&menuPcs->field_0x828;
          bVar3 = false;
          if ((*(char *)(iVar20 + 10) == '\0') && (*(char *)(iVar20 + 0xb) == '\0')) {
            if ((*(char *)(iVar20 + 0x1a) == '\0') && (*(char *)(iVar20 + 0x1b) == '\0')) {
              if ((*(char *)(iVar20 + 0x2a) == '\0') && (*(char *)(iVar20 + 0x2b) == '\0')) {
                if ((*(char *)(iVar20 + 0x3a) != '\0') || (*(char *)(iVar20 + 0x3b) != '\0')) {
                  bVar3 = true;
                }
              }
              else {
                bVar3 = true;
              }
            }
            else {
              bVar3 = true;
            }
          }
          else {
            bVar3 = true;
          }
          if (bVar3) {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
          else {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 10;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
        if (bVar4) {
          uVar26 = (uint)(*(char *)(*(int *)&menuPcs->field_0x828 + 10) != '\0');
          if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1a) != '\0') {
            uVar26 = uVar26 + 1;
          }
          if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2a) != '\0') {
            uVar26 = uVar26 + 1;
          }
          if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3a) != '\0') {
            uVar26 = uVar26 + 1;
          }
          iVar20 = *(int *)&menuPcs->field_0x828;
          if (*(char *)(iVar20 + 0xb) == '\0') {
            if (*(char *)(iVar20 + 0x1b) == '\0') {
              if (*(char *)(iVar20 + 0x2b) == '\0') {
                if (*(char *)(iVar20 + 0x3b) != '\0') {
                  uVar26 = 0;
                }
              }
              else {
                uVar26 = 0;
              }
            }
            else {
              uVar26 = 0;
            }
          }
          else {
            uVar26 = 0;
          }
          if ((int)uVar26 <= iVar7) {
            uVar26 = 0;
          }
          if (uVar26 == 0) {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
          else {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 10;
          }
        }
        uVar26 = (uint)(*(char *)(*(int *)&menuPcs->field_0x828 + 10) != '\0');
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1a) != '\0') {
          uVar26 = uVar26 | 2;
        }
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2a) != '\0') {
          uVar26 = uVar26 | 4;
        }
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3a) != '\0') {
          uVar26 = uVar26 | 8;
        }
        if ((Game.game.m_gameWork.m_menuStageMode == '\0') || (*(short *)&menuPcs->field_0x86a < 0))
        {
          if ((*(char *)(*(int *)&menuPcs->field_0x828 + 0xd) == '\0') &&
             (*(ushort *)(*(int *)&menuPcs->field_0x828 + 8) < 0x1e)) {
            uVar6 = uVar6 | 1;
          }
          if ((*(char *)(*(int *)&menuPcs->field_0x828 + 0x1d) == '\0') &&
             (*(ushort *)(*(int *)&menuPcs->field_0x828 + 0x18) < 0x1e)) {
            uVar6 = uVar6 | 2;
          }
          if ((*(char *)(*(int *)&menuPcs->field_0x828 + 0x2d) == '\0') &&
             (*(ushort *)(*(int *)&menuPcs->field_0x828 + 0x28) < 0x1e)) {
            uVar6 = uVar6 | 4;
          }
          if ((*(char *)(*(int *)&menuPcs->field_0x828 + 0x3d) == '\0') &&
             (*(ushort *)(*(int *)&menuPcs->field_0x828 + 0x38) < 0x1e)) {
            uVar6 = uVar6 | 8;
          }
          if ((uVar26 != 0) && (uVar26 == uVar6)) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            local_50 = (longlong)(int)FLOAT_8032ee18;
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x18) = (short)(int)FLOAT_8032ee18;
          }
        }
        else {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 10;
        }
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) != 0) {
          SetControllerMode__8GbaQueueFi(&GbaQue,1);
          iVar20 = *(int *)&menuPcs->field_0x828;
          if (*(char *)(iVar20 + 0xb) != '\0') {
            *(undefined *)(iVar20 + 10) = 0;
            *(undefined *)(iVar20 + 0xb) = 0;
            *(undefined *)(iVar20 + 0xc) = 0;
          }
          iVar20 = *(int *)&menuPcs->field_0x828;
          if (*(char *)(iVar20 + 0x1b) != '\0') {
            *(undefined *)(iVar20 + 0x1a) = 0;
            *(undefined *)(iVar20 + 0x1b) = 0;
            *(undefined *)(iVar20 + 0x1c) = 0;
          }
          iVar20 = *(int *)&menuPcs->field_0x828;
          if (*(char *)(iVar20 + 0x2b) != '\0') {
            *(undefined *)(iVar20 + 0x2a) = 0;
            *(undefined *)(iVar20 + 0x2b) = 0;
            *(undefined *)(iVar20 + 0x2c) = 0;
          }
          iVar20 = *(int *)&menuPcs->field_0x828;
          if (*(char *)(iVar20 + 0x3b) != '\0') {
            *(undefined *)(iVar20 + 0x3a) = 0;
            *(undefined *)(iVar20 + 0x3b) = 0;
            *(undefined *)(iVar20 + 0x3c) = 0;
          }
        }
      }
      else {
        font = *(CFont **)&menuPcs->field_0xf8;
        SetMargin__5CFontFf(FLOAT_803313e8,font);
        SetShadow__5CFontFi(font,0);
        SetScale__5CFontFf(FLOAT_803313e8,font);
        iVar22 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,1);
        iVar20 = 0;
        piVar9 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,0x17);
        piVar25 = piVar9;
        for (iVar24 = 0; iVar24 < *piVar9; iVar24 = iVar24 + 1) {
          pcVar14 = *(char **)(iVar22 + *(short *)(piVar25 + 1) * 4);
          if (pcVar14 != (char *)0x0) {
            if (*pcVar14 == '$') {
              pcVar14 = pcVar14 + 1;
            }
            dVar29 = (double)GetWidth__5CFontFPc(font,pcVar14);
            iVar8 = (int)dVar29;
            local_68 = (double)(longlong)iVar8;
            if (iVar20 < iVar8) {
              iVar20 = iVar8;
            }
          }
          piVar25 = (int *)((int)piVar25 + 2);
        }
        iVar22 = iVar20 / 0x16 + (iVar20 >> 0x1f);
        sVar12 = (short)iVar22 - (short)(iVar22 >> 0x1f);
        if (iVar20 != (iVar22 - (iVar22 >> 0x1f)) * 0x16) {
          sVar12 = sVar12 + 1;
        }
        sVar12 = (sVar12 + 2) * 0x16 + 0x40;
        sVar19 = (short)*piVar9 * 0x1e + 0x40;
        local_68 = (double)(CONCAT44(0x43300000,0x280 - sVar12) ^ 0x80000000);
        dVar29 = (double)(FLOAT_80331430 -
                         (float)((double)CONCAT44(0x43300000,(int)sVar19 ^ 0x80000000) -
                                DOUBLE_80331408)) * DOUBLE_803313f8;
        **(undefined2 **)&menuPcs->field_0x848 =
             (short)(int)((double)(float)(local_68 - DOUBLE_80331408) * DOUBLE_803313f8);
        *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar29;
        *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar12;
        *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar19;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      }
    }
    else {
      puVar15 = local_a8;
      uVar11 = 0;
      iVar20 = 4;
      do {
        uVar2 = *puVar15;
        puVar15 = puVar15 + 1;
        uVar11 = uVar11 | uVar2;
        iVar20 = iVar20 + -1;
      } while (iVar20 != 0);
      if ((sVar12 == 1) && ((uVar11 & 0x300) != 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
        iVar20 = *(int *)&menuPcs->field_0x828;
        if (*(char *)(iVar20 + 10) != '\0') {
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(iVar20 + 4) * 0x14 + 4) = 0;
        }
        *(undefined *)(iVar20 + 10) = 0;
        *(undefined *)(iVar20 + 0xb) = 0;
        *(undefined *)(iVar20 + 0xc) = 0;
        iVar20 = *(int *)&menuPcs->field_0x828;
        if (*(char *)(iVar20 + 0x1a) != '\0') {
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(iVar20 + 0x14) * 0x14 + 4) = 0;
        }
        *(undefined *)(iVar20 + 0x1a) = 0;
        *(undefined *)(iVar20 + 0x1b) = 0;
        *(undefined *)(iVar20 + 0x1c) = 0;
        iVar20 = *(int *)&menuPcs->field_0x828;
        if (*(char *)(iVar20 + 0x2a) != '\0') {
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(iVar20 + 0x24) * 0x14 + 4) = 0;
        }
        *(undefined *)(iVar20 + 0x2a) = 0;
        *(undefined *)(iVar20 + 0x2b) = 0;
        *(undefined *)(iVar20 + 0x2c) = 0;
        iVar20 = *(int *)&menuPcs->field_0x828;
        if (*(char *)(iVar20 + 0x3a) != '\0') {
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + *(short *)(iVar20 + 0x34) * 0x14 + 4) = 0;
        }
        *(undefined *)(iVar20 + 0x3a) = 0;
        *(undefined *)(iVar20 + 0x3b) = 0;
        *(undefined *)(iVar20 + 0x3c) = 0;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
  }
  return;
}

