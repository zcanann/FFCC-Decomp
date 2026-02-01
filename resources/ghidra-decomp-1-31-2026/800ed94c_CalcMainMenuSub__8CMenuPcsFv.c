// Function: CalcMainMenuSub__8CMenuPcsFv
// Entry: 800ed94c
// Size: 3804 bytes

/* WARNING: Removing unreachable block (ram,0x800ee80c) */
/* WARNING: Removing unreachable block (ram,0x800ee804) */
/* WARNING: Removing unreachable block (ram,0x800ee7fc) */
/* WARNING: Removing unreachable block (ram,0x800ee7f4) */
/* WARNING: Removing unreachable block (ram,0x800ed974) */
/* WARNING: Removing unreachable block (ram,0x800ed96c) */
/* WARNING: Removing unreachable block (ram,0x800ed964) */
/* WARNING: Removing unreachable block (ram,0x800ed95c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcMainMenuSub__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  short sVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  uint unaff_r27;
  undefined4 *puVar15;
  uint uVar16;
  CMenuPcs *pCVar17;
  MMenuPos *pMVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  Vec local_198;
  Mtx MStack_18c;
  Mtx MStack_15c;
  Mtx MStack_12c;
  Mtx MStack_fc;
  Mtx MStack_cc;
  Mtx MStack_9c;
  undefined4 local_68;
  uint uStack_64;
  
  fVar2 = FLOAT_80331528;
  fVar1 = FLOAT_803313dc;
  bVar8 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar8 = true;
  }
  if (bVar8) {
    uVar9 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar9 = Pad._8_2_;
  }
  iVar10 = *(int *)&menuPcs->field_0x82c;
  sVar3 = *(short *)(iVar10 + 0x10);
  if (((0 < sVar3) && (sVar3 < 4)) || (*(short *)(iVar10 + 0x26) == 1)) {
    if ((sVar3 == 2) && (*(short *)(iVar10 + 0x18) == 0)) {
      if ((uVar9 & 1) == 0) {
        if ((uVar9 & 2) != 0) {
          *(float *)&menuPcs->field_0x78 = *(float *)&menuPcs->field_0x78 + FLOAT_8033151c;
          if (fVar2 < *(float *)&menuPcs->field_0x78) {
            *(float *)&menuPcs->field_0x78 = *(float *)&menuPcs->field_0x78 - fVar2;
            *(float *)&menuPcs->field_0x7c = *(float *)&menuPcs->field_0x7c - fVar2;
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0xe;
          iVar10 = *(int *)&menuPcs->field_0x82c;
          if (*(short *)(iVar10 + 0x26) < 1) {
            *(undefined2 *)(iVar10 + 0x26) = 4;
          }
          else {
            *(short *)(iVar10 + 0x26) = *(short *)(iVar10 + 0x26) + -1;
          }
          PlaySe__6CSoundFiiii(&Sound,0x37,0x40,0x7f,0);
        }
      }
      else {
        *(float *)&menuPcs->field_0x78 = *(float *)&menuPcs->field_0x78 - FLOAT_8033151c;
        fVar2 = FLOAT_80331528;
        if (*(float *)&menuPcs->field_0x78 < fVar1) {
          *(float *)&menuPcs->field_0x78 = *(float *)&menuPcs->field_0x78 + FLOAT_80331528;
          *(float *)&menuPcs->field_0x7c = *(float *)&menuPcs->field_0x7c + fVar2;
        }
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0xe;
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar10 + 0x26) < 4) {
          *(short *)(iVar10 + 0x26) = *(short *)(iVar10 + 0x26) + 1;
        }
        else {
          *(undefined2 *)(iVar10 + 0x26) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,0x37,0x40,0x7f,0);
      }
      fVar1 = *(float *)&menuPcs->field_0x7c;
      fVar2 = *(float *)&menuPcs->field_0x78;
      fVar4 = fVar2;
      fVar5 = fVar1;
      if (fVar1 < fVar2) {
        fVar4 = fVar1;
        fVar5 = fVar2;
      }
      fVar4 = FLOAT_803315cc * (fVar5 - fVar4);
      if (fVar2 < fVar1) {
        *(float *)&menuPcs->field_0x7c = *(float *)&menuPcs->field_0x7c - fVar4;
      }
      else {
        *(float *)&menuPcs->field_0x7c = *(float *)&menuPcs->field_0x7c + fVar4;
      }
      sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (0 < sVar3) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar3 + -1;
      }
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) == 0) && ((uVar9 & 3) == 0)) {
        if ((uVar9 & 0x100) == 0) {
          if ((uVar9 & 0x200) != 0) {
            iVar11 = 0;
            unaff_r27 = 0;
            *(undefined4 *)&menuPcs->field_0x7c = *(undefined4 *)&menuPcs->field_0x78;
            iVar13 = 4;
            iVar10 = 0;
            do {
              if ((Game.game.m_gameWork.m_menuStageMode != '\0') && (iVar11 != 0)) break;
              if (-1 < *(short *)(*(int *)&menuPcs->field_0x82c + iVar10 + 0x3e)) {
                unaff_r27 = unaff_r27 + 1;
              }
              iVar10 = iVar10 + 2;
              iVar11 = iVar11 + 1;
              iVar13 = iVar13 + -1;
            } while (iVar13 != 0);
            if (unaff_r27 == 0) {
              PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
            }
            else {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            }
          }
        }
        else {
          *(undefined4 *)&menuPcs->field_0x7c = *(undefined4 *)&menuPcs->field_0x78;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0x14;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
    }
    puVar15 = *(undefined4 **)&menuPcs->field_0x814;
    PSMTXRotRad(FLOAT_803315d0,&MStack_9c,0x78);
    PSMTXRotRad(FLOAT_803314bc * -*(float *)&menuPcs->field_0x7c,&MStack_12c,0x79);
    PSMTXConcat(&MStack_9c,&MStack_12c,&MStack_9c);
    iVar10 = *(int *)&menuPcs->field_0x82c;
    fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0x24) ^ 0x80000000) -
                   DOUBLE_80331408) / FLOAT_803314c0;
    if (fVar1 < DAT_8032e8d4[DAT_8032e8d0 * 4 + -4]) {
      iVar11 = 0;
      pfVar12 = DAT_8032e8d4;
      iVar13 = DAT_8032e8d0;
      fVar2 = FLOAT_803313dc;
      if (0 < DAT_8032e8d0) {
        do {
          if (fVar1 <= *pfVar12) {
            if (iVar11 == 0) {
              fVar2 = DAT_8032e8d4[1];
            }
            else {
              pfVar14 = DAT_8032e8d4 + iVar11 * 4;
              pfVar12 = DAT_8032e8d4 + (iVar11 + -1) * 4;
              fVar2 = *pfVar14 - *pfVar12;
              fVar6 = (fVar1 - *pfVar12) / fVar2;
              fVar5 = fVar6 * fVar6;
              fVar4 = fVar5 * fVar6;
              fVar2 = fVar2 * (pfVar12[3] * (fVar6 + -(FLOAT_803314c8 * fVar5 - fVar4)) +
                              pfVar14[2] * (fVar4 - fVar5)) +
                      pfVar12[1] *
                      (FLOAT_803313e8 + (FLOAT_803314c8 * fVar4 - FLOAT_803314c4 * fVar5)) +
                      pfVar14[1] * (FLOAT_803314cc * fVar4 + FLOAT_803314c4 * fVar5);
            }
            break;
          }
          pfVar12 = pfVar12 + 4;
          iVar11 = iVar11 + 1;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
    }
    else {
      fVar2 = DAT_8032e8d4[DAT_8032e8d0 * 4 + -3];
    }
    if (fVar1 < DAT_8032e8dc[DAT_8032e8d8 * 4 + -4]) {
      iVar11 = 0;
      pfVar12 = DAT_8032e8dc;
      iVar13 = DAT_8032e8d8;
      fVar4 = FLOAT_803313dc;
      if (0 < DAT_8032e8d8) {
        do {
          if (fVar1 <= *pfVar12) {
            if (iVar11 == 0) {
              fVar4 = DAT_8032e8dc[1];
            }
            else {
              pfVar14 = DAT_8032e8dc + iVar11 * 4;
              pfVar12 = DAT_8032e8dc + (iVar11 + -1) * 4;
              fVar4 = *pfVar14 - *pfVar12;
              fVar7 = (fVar1 - *pfVar12) / fVar4;
              fVar6 = fVar7 * fVar7;
              fVar5 = fVar6 * fVar7;
              fVar4 = fVar4 * (pfVar12[3] * (fVar7 + -(FLOAT_803314c8 * fVar6 - fVar5)) +
                              pfVar14[2] * (fVar5 - fVar6)) +
                      pfVar12[1] *
                      (FLOAT_803313e8 + (FLOAT_803314c8 * fVar5 - FLOAT_803314c4 * fVar6)) +
                      pfVar14[1] * (FLOAT_803314cc * fVar5 + FLOAT_803314c4 * fVar6);
            }
            break;
          }
          pfVar12 = pfVar12 + 4;
          iVar11 = iVar11 + 1;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
    }
    else {
      fVar4 = DAT_8032e8dc[DAT_8032e8d8 * 4 + -3];
    }
    dVar23 = (double)FLOAT_803313dc;
    if (fVar1 < DAT_8032e8e4[DAT_8032e8e0 * 4 + -4]) {
      iVar11 = 0;
      pfVar12 = DAT_8032e8e4;
      iVar13 = DAT_8032e8e0;
      if (0 < DAT_8032e8e0) {
        do {
          if (fVar1 <= *pfVar12) {
            if (iVar11 == 0) {
              dVar23 = (double)DAT_8032e8e4[1];
            }
            else {
              pfVar14 = DAT_8032e8e4 + iVar11 * 4;
              pfVar12 = DAT_8032e8e4 + (iVar11 + -1) * 4;
              fVar5 = *pfVar14 - *pfVar12;
              fVar7 = (fVar1 - *pfVar12) / fVar5;
              fVar6 = fVar7 * fVar7;
              fVar1 = fVar6 * fVar7;
              dVar23 = (double)(fVar5 * (pfVar12[3] * (fVar7 + -(FLOAT_803314c8 * fVar6 - fVar1)) +
                                        pfVar14[2] * (fVar1 - fVar6)) +
                               pfVar12[1] *
                               (FLOAT_803313e8 + (FLOAT_803314c8 * fVar1 - FLOAT_803314c4 * fVar6))
                               + pfVar14[1] * (FLOAT_803314cc * fVar1 + FLOAT_803314c4 * fVar6));
            }
            break;
          }
          pfVar12 = pfVar12 + 4;
          iVar11 = iVar11 + 1;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
    }
    else {
      dVar23 = (double)DAT_8032e8e4[DAT_8032e8e0 * 4 + -3];
    }
    if (*(short *)(iVar10 + 0x1e) == -1) {
      dVar20 = (double)FLOAT_803313dc;
    }
    else {
      dVar20 = (double)FLOAT_803313dc;
      fVar1 = (float)((double)CONCAT44(0x43300000,
                                       0x14U - (int)*(short *)(iVar10 + 0x18) ^ 0x80000000) -
                     DOUBLE_80331408) / FLOAT_803314c0;
      if (fVar1 < *(float *)(PTR_DAT_8032e8ec + DAT_8032e8e8 * 0x10 + -0x10)) {
        iVar11 = 0;
        pfVar12 = (float *)PTR_DAT_8032e8ec;
        iVar13 = DAT_8032e8e8;
        if (0 < DAT_8032e8e8) {
          do {
            if (fVar1 <= *pfVar12) {
              if (iVar11 == 0) {
                dVar20 = (double)*(float *)(PTR_DAT_8032e8ec + 4);
              }
              else {
                pfVar14 = (float *)(PTR_DAT_8032e8ec + iVar11 * 0x10);
                pfVar12 = (float *)(PTR_DAT_8032e8ec + (iVar11 + -1) * 0x10);
                fVar5 = *pfVar14 - *pfVar12;
                fVar7 = (fVar1 - *pfVar12) / fVar5;
                fVar6 = fVar7 * fVar7;
                fVar1 = fVar6 * fVar7;
                dVar20 = (double)(fVar5 * (pfVar12[3] * (fVar7 + -(FLOAT_803314c8 * fVar6 - fVar1))
                                          + pfVar14[2] * (fVar1 - fVar6)) +
                                 pfVar12[1] *
                                 (FLOAT_803313e8 + (FLOAT_803314c8 * fVar1 - FLOAT_803314c4 * fVar6)
                                 ) + pfVar14[1] * (FLOAT_803314cc * fVar1 + FLOAT_803314c4 * fVar6))
                ;
              }
              break;
            }
            pfVar12 = pfVar12 + 4;
            iVar11 = iVar11 + 1;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
        }
      }
      else {
        dVar20 = (double)*(float *)(PTR_DAT_8032e8ec + DAT_8032e8e8 * 0x10 + -0xc);
      }
    }
    if ((*(short *)(iVar10 + 0x10) == 2) && (*(short *)(iVar10 + 0x18) == 0)) {
      *(short *)(iVar10 + 0x24) = *(short *)(iVar10 + 0x24) + 1;
      if (99 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x24)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
      }
    }
    else {
      *(undefined2 *)(iVar10 + 0x24) = 0;
    }
    pMVar18 = &s_MMenuPos;
    dVar22 = (double)(FLOAT_803314bc * fVar4);
    uVar16 = 0;
    dVar21 = (double)(FLOAT_803314bc * fVar2);
    pCVar17 = menuPcs;
    do {
      sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (((0 < sVar3) && (sVar3 < 4)) || (uVar16 == 1)) {
        *puVar15 = 1;
        dVar19 = (double)FLOAT_803315d4;
        if (uVar16 == 0) {
          dVar19 = (double)(float)(dVar19 * DOUBLE_803315d8);
        }
        puVar15[0xd] = (float)dVar19;
        fVar1 = FLOAT_803313dc;
        uStack_64 = uVar16 ^ 0x80000000;
        puVar15[0xe] = (float)dVar19;
        fVar4 = FLOAT_803315e0;
        puVar15[0xf] = (float)dVar19;
        dVar19 = DOUBLE_80331408;
        puVar15[7] = fVar1;
        fVar5 = FLOAT_803315e4;
        puVar15[8] = fVar1;
        fVar2 = FLOAT_803314bc;
        puVar15[9] = fVar4;
        puVar15[10] = fVar1;
        local_68 = 0x43300000;
        puVar15[0xc] = fVar1;
        puVar15[0xb] = fVar5 * (float)((double)CONCAT44(0x43300000,uStack_64) - dVar19);
        PSMTXRotRad(fVar2 * (float)puVar15[0xb],&MStack_cc,0x79);
        PSMTXMultVecSR(&MStack_cc,(Vec *)(puVar15 + 7),&local_198);
        PSMTXTransApply(local_198.x,local_198.y,local_198.z,&MStack_cc,&MStack_fc);
        PSMTXConcat(&MStack_9c,&MStack_fc,&MStack_cc);
        local_198.x = MStack_cc.value[0][3];
        local_198.y = MStack_cc.value[1][3];
        local_198.z = MStack_cc.value[2][3];
        PSMTXIdentity(&MStack_cc);
        if (uVar16 == 1) {
          iVar13 = *(int *)&menuPcs->field_0x82c;
          iVar10 = (int)*(short *)(iVar13 + 0x10);
          if (iVar10 != 2) {
            if (iVar10 < 2) {
              unaff_r27 = 0x13 - ((int)*(short *)(iVar13 + 0x22) + iVar10 * 10);
              if ((int)unaff_r27 < 0) {
                unaff_r27 = 0;
              }
            }
            else {
              unaff_r27 = (int)*(short *)(iVar13 + 0x22) + (iVar10 + -3) * 10;
            }
          }
        }
        if (uVar16 == 0) {
          PSMTXRotRad(FLOAT_803315e8,&MStack_fc,0x79);
          PSMTXRotRad(FLOAT_803315d0,&MStack_15c,0x78);
          PSMTXConcat(&MStack_fc,&MStack_15c,&MStack_fc);
        }
        else if (uVar16 == 1) {
          iVar10 = *(int *)&menuPcs->field_0x82c;
          if (((*(short *)(iVar10 + 0x1e) == -1) || (*(short *)(iVar10 + 0x26) != 1)) ||
             (*(short *)(iVar10 + 0x10) == 2)) {
            PSMTXRotRad(FLOAT_80331610,&MStack_fc,0x78);
          }
          else {
            uStack_64 = unaff_r27 ^ 0x80000000;
            local_68 = 0x43300000;
            PSMTXRotRad((float)(DOUBLE_803315f0 *
                               (DOUBLE_803315f8 +
                               (double)(float)(DOUBLE_80331600 *
                                              ((double)(float)((double)CONCAT44(0x43300000,uStack_64
                                                                               ) - DOUBLE_80331408)
                                              / DOUBLE_80331608)))),&MStack_fc,0x78);
          }
        }
        else if ((uVar16 - 2 < 2) || (uVar16 == 4)) {
          PSMTXRotRad(FLOAT_80331614,&MStack_fc,0x78);
        }
        if ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) == uVar16) {
          PSMTXRotRad((float)dVar22,&MStack_cc,0x7a);
          PSMTXRotRad((float)dVar21,&MStack_18c,0x79);
          PSMTXConcat(&MStack_cc,&MStack_18c,&MStack_cc);
          PSMTXConcat(&MStack_cc,&MStack_fc,&MStack_fc);
        }
        fVar1 = FLOAT_803313dc;
        dVar19 = DOUBLE_80331418 + (double)local_198.y;
        ((Vec *)&pMVar18->field0_0x0[0].x)->x = local_198.x;
        pMVar18->field0_0x0[0].y = (float)dVar19;
        pMVar18->field0_0x0[0].z = local_198.z;
        PSMTXTransApply(fVar1,fVar1,local_198.z,&MStack_fc,&MStack_cc);
        PSMTXScaleApply((float)puVar15[0xd],(float)puVar15[0xe],(float)puVar15[0xf],&MStack_cc,
                        &MStack_fc);
        if (uVar16 == 0) {
          PSMTXTransApply(FLOAT_80331618,FLOAT_8033161c,FLOAT_803313dc,&MStack_fc,&MStack_fc);
        }
        else if (uVar16 == 1) {
          PSMTXTransApply(FLOAT_80331620,FLOAT_803313dc,FLOAT_803313dc,&MStack_fc,&MStack_fc);
        }
        if ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) == uVar16) {
          MStack_fc.value[1][3] = (float)((double)MStack_fc.value[1][3] + dVar23);
        }
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if ((((*(short *)(iVar10 + 0x1e) != -1) && (uVar16 == 1)) &&
            (*(short *)(iVar10 + 0x26) == 1)) && (*(short *)(iVar10 + 0x10) != 2)) {
          uStack_64 = unaff_r27 ^ 0x80000000;
          local_68 = 0x43300000;
          dVar19 = ((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408) / DOUBLE_80331608;
          MStack_fc.value[0][3] =
               (float)((double)MStack_fc.value[0][3] +
                      (double)(float)((double)(float)(-(double)MStack_fc.value[0][3] * dVar19) *
                                     dVar19));
          MStack_fc.value[1][3] =
               (float)((double)MStack_fc.value[1][3] +
                      (double)(float)((double)(float)-((double)MStack_fc.value[1][3] * dVar19 -
                                                      DOUBLE_80331628) * dVar19));
          MStack_fc.value[2][3] =
               (float)((double)MStack_fc.value[2][3] +
                      (double)(float)((double)(float)(DOUBLE_80331630 -
                                                     (double)MStack_fc.value[2][3]) * dVar19));
        }
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if (((*(short *)(iVar10 + 0x1e) != -1) && ((int)*(short *)(iVar10 + 0x26) == uVar16)) &&
           (*(short *)(iVar10 + 0x18) != 0)) {
          PSMTXScale((float)dVar20,(float)dVar20,(float)dVar20,&MStack_cc);
          PSMTXConcat(&MStack_cc,&MStack_fc,&MStack_fc);
        }
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if (((*(short *)(iVar10 + 0x1e) != -1) && (uVar16 == 1)) &&
           ((*(short *)(iVar10 + 0x26) == 1 && (*(short *)(iVar10 + 0x10) != 2)))) {
          uStack_64 = unaff_r27 ^ 0x80000000;
          local_68 = 0x43300000;
          fVar1 = (float)((double)(float)(DOUBLE_803313f8 *
                                         (((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408)
                                         / DOUBLE_80331608)) + DOUBLE_80331420);
          PSMTXScale(fVar1,fVar1,fVar1,&MStack_cc);
          PSMTXConcat(&MStack_cc,&MStack_fc,&MStack_fc);
        }
        iVar10 = *(int *)&menuPcs->field_0x82c;
        sVar3 = *(short *)(iVar10 + 0x10);
        if (sVar3 == 1) {
          uStack_64 = (int)*(short *)(iVar10 + 0x22) ^ 0x80000000;
          local_68 = 0x43300000;
          *(float *)(*(int *)(*(int *)&pCVar17->field_0x774 + 0x168) + 0x9c) =
               (float)(DOUBLE_803314e8 * ((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408))
          ;
        }
        else if (sVar3 == 2) {
          *(float *)(*(int *)(*(int *)&pCVar17->field_0x774 + 0x168) + 0x9c) = FLOAT_803313e8;
        }
        else if (sVar3 == 3) {
          uStack_64 = (int)*(short *)(iVar10 + 0x22) ^ 0x80000000;
          local_68 = 0x43300000;
          *(float *)(*(int *)(*(int *)&pCVar17->field_0x774 + 0x168) + 0x9c) =
               (float)-(DOUBLE_803314e8 * ((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408)
                       - DOUBLE_80331420);
        }
        else {
          *(float *)(*(int *)(*(int *)&pCVar17->field_0x774 + 0x168) + 0x9c) = FLOAT_803313dc;
        }
        if (((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) != -1) &&
            (*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) == 1)) && (uVar16 == 1)) {
          *(float *)(*(int *)(*(int *)&pCVar17->field_0x774 + 0x168) + 0x9c) = FLOAT_803313e8;
        }
        SetMatrix__Q26CChara6CModelFPA4_f
                  (*(CModel **)(*(int *)&pCVar17->field_0x774 + 0x168),&MStack_fc);
        CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&pCVar17->field_0x774 + 0x168));
        CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&pCVar17->field_0x774 + 0x168));
      }
      uVar16 = uVar16 + 1;
      puVar15 = puVar15 + 0x14;
      pCVar17 = (CMenuPcs *)&pCVar17->field_0x4;
      pMVar18 = (MMenuPos *)((int)pMVar18 + 0xc);
    } while ((int)uVar16 < 5);
  }
  return;
}

