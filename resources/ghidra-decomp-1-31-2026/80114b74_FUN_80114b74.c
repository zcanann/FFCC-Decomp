// Function: FUN_80114b74
// Entry: 80114b74
// Size: 2328 bytes

/* WARNING: Removing unreachable block (ram,0x80115470) */
/* WARNING: Removing unreachable block (ram,0x80114b84) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FUN_80114b74(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  CGPartyObj *pCVar14;
  double dVar15;
  double dVar16;
  
  if (*(int *)(param_1 + 0x520) == 0) {
    *(undefined *)(param_1 + 0x6bd) = 0;
    dVar16 = (double)(float)((double)CONCAT44(0x43300000,
                                              (uint)*(ushort *)
                                                     (*(int *)(*(int *)(param_1 + 0x58) + 0x24) +
                                                     0xcc)) - DOUBLE_803319e0);
    dVar15 = (double)PSVECDistance((Vec *)(param_1 + 0x6f8),(Vec *)(param_1 + 0x15c));
    if (dVar15 < dVar16) {
      if (*(short *)(param_1 + 0x6e4) == 0) {
        iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
      }
      else {
        iVar6 = Game.game.unkCFlatData0[1] +
                ((int)*(short *)(param_1 + 0x6e4) +
                (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0 + 0x10
        ;
      }
      uVar2 = *(ushort *)(iVar6 + 0x106);
      if (uVar2 == 0xffff) {
        *(undefined4 *)(param_1 + 0x6d8) = 0;
        *(undefined4 *)(param_1 + 0x6dc) = 0;
        *(undefined *)(param_1 + 0x6bb) = 1;
      }
      else {
        if (uVar2 < 10) {
          iVar5 = 0;
          iVar10 = 0;
          iVar6 = param_1;
          do {
            pCVar14 = Game.game.m_partyObjArr[*(int *)(iVar6 + 0x620)];
            if (((((pCVar14 != (CGPartyObj *)0x0) &&
                  (*(short *)((pCVar14->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)) &&
                 (iVar3 = (pCVar14->gCharaObj).gPrgObj.m_lastStateId, iVar3 != 9)) &&
                (iVar3 != 0x22)) &&
               (((Game.game.m_gameWork.m_menuStageMode == '\0' ||
                 (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
                ((uVar8 = (**(code **)((int)*(void **)((int)&(pCVar14->gCharaObj).gPrgObj.object.
                                                             base_object + 0x48) + 0xc))(pCVar14),
                 (uVar8 & 0x6d) != 0x6d ||
                 ((pCVar14->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)))))) {
              iVar5 = iVar5 + 1;
            }
            iVar10 = iVar10 + 1;
            iVar6 = iVar6 + 4;
          } while (iVar10 < 4);
          iVar3 = Rand__5CMathFUl(&Math,iVar5);
          uVar8 = 10000000;
          iVar11 = 0;
          iVar13 = 0;
          dVar15 = (double)(float)((double)CONCAT44(0x43300000,
                                                    (uint)*(ushort *)
                                                           (*(int *)(*(int *)(param_1 + 0x58) + 0x24
                                                                    ) + 0xcc)) - DOUBLE_803319e0);
          iVar6 = -1;
          iVar10 = -1;
          iVar5 = param_1;
          do {
            iVar7 = *(int *)(iVar5 + 0x620);
            pCVar14 = Game.game.m_partyObjArr[iVar7];
            iVar12 = iVar6;
            if ((((pCVar14 != (CGPartyObj *)0x0) &&
                 (*(short *)((pCVar14->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)) &&
                ((iVar4 = (pCVar14->gCharaObj).gPrgObj.m_lastStateId, iVar4 != 9 && (iVar4 != 0x22))
                )) && ((((Game.game.m_gameWork.m_menuStageMode == '\0' ||
                         (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
                        (uVar9 = (**(code **)((int)*(void **)((int)&(pCVar14->gCharaObj).gPrgObj.
                                                                    object.base_object + 0x48) + 0xc
                                             ))(pCVar14), (uVar9 & 0x6d) != 0x6d)) ||
                       ((pCVar14->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0))))
            {
              if (((double)*(float *)(param_1 + iVar7 * 4 + 0x5d0) < dVar15) &&
                 (iVar10 = iVar7, uVar2 == 0)) break;
              iVar12 = iVar7;
              if ((uVar2 != 3) ||
                 ((iVar4 = (pCVar14->gCharaObj).gPrgObj.m_lastStateId, iVar4 != 6 && (iVar4 != 2))))
              {
                if (uVar2 == 2) {
                  uVar9 = (uint)*(ushort *)((pCVar14->gCharaObj).gPrgObj.object.m_scriptHandle + 7);
                  iVar12 = iVar6;
                  if (uVar9 < uVar8) {
                    uVar8 = uVar9;
                    iVar12 = iVar7;
                  }
                }
                else {
                  iVar12 = iVar6;
                  if ((uVar2 == 4) && (iVar11 == iVar3)) {
                    iVar12 = iVar7;
                  }
                }
              }
              iVar11 = iVar11 + 1;
            }
            iVar7 = iVar10;
            iVar13 = iVar13 + 1;
            iVar5 = iVar5 + 4;
            iVar6 = iVar12;
            iVar10 = iVar7;
          } while (iVar13 < 4);
          if (uVar2 == 1) {
            iVar7 = *(int *)(param_1 + 0x6c4);
          }
          else if (((uVar2 != 0) && (uVar2 < 5)) && (-1 < iVar12)) {
            iVar7 = iVar12;
          }
        }
        else {
          iVar7 = __ptmf_scall(param_1,uVar2,*(undefined4 *)(param_1 + 0x708));
        }
        if (iVar7 < 0) {
          SoundBuffer._1252_4_ = 0;
          memset(param_1 + 0x70c,0,0x34);
          *(undefined4 *)(param_1 + 0x6d8) = 3;
          *(undefined4 *)(param_1 + 0x6dc) = 0;
          *(undefined *)(param_1 + 0x6bb) = 1;
        }
        else {
          *(int *)(param_1 + 0x6c4) = iVar7;
          if (*(short *)(param_1 + 0x6e4) == 0) {
            iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
          }
          else {
            iVar6 = Game.game.unkCFlatData0[1] +
                    ((int)*(short *)(param_1 + 0x6e4) +
                    (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0 +
                    0x10;
          }
          if (*(short *)(iVar6 + 0x10a) == 1) {
            if (*(char *)(param_1 + 0x6bc) == '\0') {
              iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              if (*(float *)(param_1 + *(int *)(param_1 + 0x6c4) * 4 + 0x5d0) <
                  (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(iVar6 + 0xce)) -
                         DOUBLE_803319e0)) {
                if (*(short *)(iVar6 + 0x10c) == 1) {
                  *(undefined4 *)(param_1 + 0x6d8) = 5;
                  *(undefined4 *)(param_1 + 0x6dc) = 0;
                  *(undefined *)(param_1 + 0x6bb) = 1;
                }
                else {
                  SoundBuffer._1252_4_ = 0x1e;
                }
                *(undefined *)(param_1 + 0x6bc) = 1;
                return;
              }
            }
            else {
              *(undefined *)(param_1 + 0x6bc) = 0;
            }
          }
          SoundBuffer._1252_4_ = FUN_8011548c(param_1,iVar7);
          if (SoundBuffer._1252_4_ == -2) {
            SoundBuffer._1252_4_ = 0;
            memset(param_1 + 0x70c,0,0x34);
            *(undefined4 *)(param_1 + 0x6d8) = 0;
            *(undefined4 *)(param_1 + 0x6dc) = 0;
            *(undefined *)(param_1 + 0x6bb) = 1;
          }
          else if (SoundBuffer._1252_4_ == -1) {
            SoundBuffer._1252_4_ = 0;
            memset(param_1 + 0x70c,0,0x34);
            *(undefined4 *)(param_1 + 0x6d8) = 2;
            *(undefined4 *)(param_1 + 0x6dc) = 0;
            *(undefined *)(param_1 + 0x6bb) = 1;
          }
          else {
            iVar6 = *(int *)(param_1 + 0x58);
            iVar10 = *(int *)(iVar6 + 0x24);
            if (*(short *)(iVar10 + 0x10c) == 1) {
              if ((int)SoundBuffer._1252_4_ < 100) {
                sVar1 = *(short *)(param_1 + 0x6e4);
                iVar5 = (int)sVar1;
                if (sVar1 != 0) {
                  iVar10 = Game.game.unkCFlatData0[1] +
                           (iVar5 + (uint)*(ushort *)(iVar10 + 0x100)) * 0x1d0 + 0x10;
                }
                iVar3 = SoundBuffer._1252_4_ * 0x10;
                if ((*(ushort *)(iVar10 + iVar3 + 0x110) & 0x20) != 0) {
                  SoundBuffer._1252_4_ = 0x21;
                  pCVar14 = Game.game.m_partyObjArr[iVar7];
                  if (*(int *)(param_1 + 0x734) != 4) {
                    memset(param_1 + 0x70c,0,0x34);
                    *(undefined4 *)(param_1 + 0x70c) = 0x855;
                    if ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 4) != 0) {
                      *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x400;
                    }
                    if (*(short *)(param_1 + 0x6e4) == 0) {
                      iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
                    }
                    else {
                      iVar6 = Game.game.unkCFlatData0[1] +
                              ((int)*(short *)(param_1 + 0x6e4) +
                              (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100))
                              * 0x1d0 + 0x10;
                    }
                    if ((*(ushort *)(iVar6 + 0x102) & 0x80) != 0) {
                      *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x20000;
                    }
                    dVar15 = DOUBLE_803319e0;
                    *(undefined4 *)(param_1 + 0x70c) = *(undefined4 *)(param_1 + 0x70c);
                    *(undefined4 *)(param_1 + 0x734) = 4;
                    *(float *)(param_1 + 0x728) =
                         (float)((double)CONCAT44(0x43300000,
                                                  (uint)*(ushort *)
                                                         (*(int *)(*(int *)(param_1 + 0x58) + 0x24)
                                                         + 0xd6)) - dVar15);
                    *(uint *)(param_1 + 0x72c) =
                         (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x1b6);
                  }
                  *(CGPartyObj **)(param_1 + 0x714) = pCVar14;
                  *(undefined4 *)(param_1 + 0x6d8) = 5;
                  *(undefined4 *)(param_1 + 0x6dc) = 0;
                  *(undefined *)(param_1 + 0x6bb) = 1;
                  return;
                }
                if (sVar1 == 0) {
                  iVar10 = *(int *)(iVar6 + 0x24);
                }
                else {
                  iVar10 = Game.game.unkCFlatData0[1] +
                           (iVar5 + (uint)*(ushort *)(*(int *)(iVar6 + 0x24) + 0x100)) * 0x1d0 +
                           0x10;
                }
                dVar15 = (double)(float)((double)CONCAT44(0x43300000,
                                                          (uint)*(ushort *)(iVar10 + iVar3 + 0x11c))
                                        - DOUBLE_803319e0);
                if (sVar1 == 0) {
                  iVar6 = *(int *)(iVar6 + 0x24);
                }
                else {
                  iVar6 = Game.game.unkCFlatData0[1] +
                          (iVar5 + (uint)*(ushort *)(*(int *)(iVar6 + 0x24) + 0x100)) * 0x1d0 + 0x10
                  ;
                }
                sVar1 = *(short *)(iVar6 + iVar3 + 0x11e);
                SoundBuffer._1252_4_ = 0x21;
                pCVar14 = Game.game.m_partyObjArr[iVar7];
                if (*(int *)(param_1 + 0x734) != 2) {
                  memset(param_1 + 0x70c,0,0x34);
                  *(undefined4 *)(param_1 + 0x70c) = 0x325;
                  if (*(short *)(param_1 + 0x6e4) == 0) {
                    iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
                  }
                  else {
                    iVar6 = Game.game.unkCFlatData0[1] +
                            ((int)*(short *)(param_1 + 0x6e4) +
                            (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                            0x1d0 + 0x10;
                  }
                  if ((*(ushort *)(iVar6 + 0x102) & 0x40) != 0) {
                    *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x10000;
                  }
                  *(undefined4 *)(param_1 + 0x70c) = *(undefined4 *)(param_1 + 0x70c);
                  *(undefined4 *)(param_1 + 0x734) = 2;
                }
                *(CGPartyObj **)(param_1 + 0x714) = pCVar14;
                *(float *)(param_1 + 0x728) = (float)dVar15;
                *(int *)(param_1 + 0x738) = (int)sVar1;
              }
            }
            else {
              SoundBuffer._1252_4_ = SoundBuffer._1252_4_ + -0xe;
            }
            *(undefined4 *)(param_1 + 0x6d8) = 1;
            *(undefined4 *)(param_1 + 0x6dc) = 0;
            *(undefined *)(param_1 + 0x6bb) = 1;
          }
        }
      }
    }
    else {
      SoundBuffer._1252_4_ = 0;
      memset(param_1 + 0x70c,0,0x34);
      *(undefined4 *)(param_1 + 0x6d8) = 3;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
    }
  }
  else if (((*(int *)(param_1 + 0x520) == 0x21) &&
           (iVar6 = *(int *)(*(int *)(param_1 + 0x58) + 0x24), *(short *)(iVar6 + 0x10c) == 1)) &&
          (((*(uint *)(param_1 + 0x710) & 1) != 0 ||
           ((int)(uint)*(ushort *)(iVar6 + 0x1bc) <= *(int *)(param_1 + 0x730))))) {
    SoundBuffer._1252_4_ = 0;
    memset(param_1 + 0x70c,0,0x34);
    *(undefined4 *)(param_1 + 0x6d8) = 3;
    *(undefined4 *)(param_1 + 0x6dc) = 0;
    *(undefined *)(param_1 + 0x6bb) = 1;
  }
  return;
}

