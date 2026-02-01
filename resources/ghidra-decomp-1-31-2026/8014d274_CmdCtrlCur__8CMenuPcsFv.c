// Function: CmdCtrlCur__8CMenuPcsFv
// Entry: 8014d274
// Size: 2836 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CmdCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  ushort uVar6;
  ushort uVar7;
  uint uVar5;
  int iVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined auStack_78 [40];
  int local_50;
  undefined4 local_4c;
  int local_48;
  
  iVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,0);
  uVar3 = Game.game.m_scriptFoodBase[0];
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._8_2_;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar7 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar7 = Pad._20_2_;
  }
  if (uVar7 == 0) {
    return 0;
  }
  iVar9 = *(int *)&menuPcs->field_0x82c;
  iVar14 = (int)*(short *)(iVar9 + 0x30);
  if (iVar14 == 0) {
    sVar1 = *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa);
    if ((uVar7 & 8) == 0) {
      if ((uVar7 & 4) != 0) {
        if ((int)*(short *)(iVar9 + 0x26) < sVar1 + -1) {
          *(short *)(iVar9 + 0x26) = *(short *)(iVar9 + 0x26) + 1;
        }
        else {
          *(undefined2 *)(iVar9 + 0x26) = 2;
        }
        iVar8 = *(int *)&menuPcs->field_0x82c;
        iVar9 = (int)*(short *)(iVar8 + 0x26);
        if (*(short *)(uVar3 + iVar9 * 2 + 0x214) < 0) {
          if (*(short *)(uVar3 + (iVar9 + 1) * 2 + 0x214) < 0) {
            if (-1 < *(short *)(uVar3 + (iVar9 + 2) * 2 + 0x214)) {
              *(short *)(iVar8 + 0x26) = (short)(iVar9 + 2);
            }
          }
          else {
            *(short *)(iVar8 + 0x26) = (short)(iVar9 + 1);
          }
          if (sVar1 + -1 < (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 2;
          }
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      if (*(short *)(iVar9 + 0x26) < 3) {
        *(short *)(iVar9 + 0x26) = sVar1 + -1;
      }
      else {
        *(short *)(iVar9 + 0x26) = *(short *)(iVar9 + 0x26) + -1;
      }
      iVar8 = *(int *)&menuPcs->field_0x82c;
      iVar9 = (int)*(short *)(iVar8 + 0x26);
      if (*(short *)(uVar3 + iVar9 * 2 + 0x214) < 0) {
        if (*(short *)(uVar3 + (iVar9 + -1) * 2 + 0x214) < 0) {
          if (-1 < *(short *)(uVar3 + (iVar9 + -2) * 2 + 0x214)) {
            *(short *)(iVar8 + 0x26) = (short)(iVar9 + -2);
          }
        }
        else {
          *(short *)(iVar8 + 0x26) = (short)(iVar9 + -1);
        }
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar7 & 0xc) == 0) {
      if ((uVar6 & 0x20) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        return 1;
      }
      if ((uVar6 & 0x40) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        return 1;
      }
      if ((uVar6 & 0x100) == 0) {
        if ((uVar6 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          return 1;
        }
      }
      else {
        iVar8 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(uVar3 + *(short *)(iVar8 + 0x26) * 2 + 0x214) == 0) {
          *(undefined2 *)(iVar8 + 0x30) = 1;
        }
        else {
          *(undefined *)(iVar8 + 0xc) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 2;
        }
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
  }
  else if (iVar14 == 1) {
    psVar10 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    sVar1 = *psVar10;
    iVar9 = (int)sVar1;
    if ((uVar7 & 8) == 0) {
      if ((uVar7 & 4) != 0) {
        if (((iVar9 < 9) || (6 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x28))) &&
           ((8 < iVar9 || (iVar9 + -1 <= (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28))))) {
          if (iVar9 < 9) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
          }
          else {
            iVar14 = *(int *)&menuPcs->field_0x82c;
            if ((int)*(short *)(iVar14 + 0x34) < iVar9 + -1) {
              *(short *)(iVar14 + 0x34) = *(short *)(iVar14 + 0x34) + 1;
            }
            else {
              *(undefined2 *)(iVar14 + 0x34) = 0;
            }
          }
        }
        else {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) + 1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x28) == 0) {
        if (iVar9 < 9) {
          *(short *)(iVar14 + 0x28) = sVar1 + -1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        else if (*(short *)(iVar14 + 0x34) == 0) {
          *(short *)(iVar14 + 0x34) = sVar1 + -1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        else {
          *(short *)(iVar14 + 0x34) = *(short *)(iVar14 + 0x34) + -1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(iVar14 + 0x28) = *(short *)(iVar14 + 0x28) + -1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    uVar4 = Game.game.m_scriptFoodBase[0];
    if ((uVar7 & 0xc) == 0) {
      if ((uVar6 & 0x100) == 0) {
        if ((uVar6 & 0x200) != 0) {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
          CmdInit2__8CMenuPcsFv(menuPcs);
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
      else {
        iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34) +
                 (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
        if (iVar9 <= iVar14) {
          iVar14 = iVar14 - iVar9;
        }
        psVar10 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
        if ((iVar14 < 0) || (*psVar10 <= iVar14)) {
          uVar5 = 0;
        }
        else if (iVar14 == 0) {
          uVar5 = (uint)(int)*(short *)(uVar4 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 2
                                       + 0x204) >> 0x1f ^ 1;
        }
        else if (iVar14 == 1) {
          uVar5 = ChkUnite__8CMenuPcsFiPA2_i
                            (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),
                             auStack_78);
          uVar5 = (-uVar5 | uVar5) >> 0x1f;
        }
        else {
          uVar5 = EquipChk__8CMenuPcsFi(menuPcs,(int)psVar10[iVar14 + -1]);
          uVar5 = countLeadingZeros(uVar5 & 0xff);
          uVar5 = uVar5 >> 5;
        }
        if ((uVar5 & 0xff) == 0) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          if (iVar14 == 0) {
            ChgCmdLst__12CCaravanWorkFii
                      (uVar3,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),0xffffffff);
          }
          else if (iVar14 != 1) {
            ChgCmdLst__12CCaravanWorkFii
                      (uVar3,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),
                       (int)*(short *)(iVar8 + iVar14 * 2 + -2));
          }
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
          if (iVar14 != 0) {
            iVar8 = ChkUnite__8CMenuPcsFiPA2_i
                              (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),
                               &local_50);
            if (iVar8 == 1) {
              UniteComList__12CCaravanWorkFiii
                        ((CCaravanWork *)Game.game.m_scriptFoodBase[0],local_4c,
                         (int)(short)(&DAT_801de914)[local_50 * 6],(&DAT_801de912)[local_50 * 6]);
            }
            else if (1 < iVar8) {
              if ((&DAT_801de914)[local_48 * 6] == 2) {
                *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
              }
              else {
                UniteComList__12CCaravanWorkFiii
                          ((CCaravanWork *)Game.game.m_scriptFoodBase[0],local_4c,
                           (int)(short)(&DAT_801de914)[local_50 * 6],(&DAT_801de912)[local_50 * 6]);
              }
            }
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          CmdInit2__8CMenuPcsFv(menuPcs);
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
    }
  }
  else if (iVar14 == 2) {
    if (DOUBLE_80332a58 ==
        (double)*(float *)(*(int *)&menuPcs->field_0x850 +
                          (*(short *)(*(int *)&menuPcs->field_0x850 + 2) + 3) * 0x40 + 0x1c)) {
      iVar8 = 2;
    }
    else {
      iVar8 = 3;
    }
    if ((uVar7 & 8) == 0) {
      if ((uVar7 & 4) != 0) {
        if ((int)*(short *)(iVar9 + 0x2a) < iVar8 + -1) {
          *(short *)(iVar9 + 0x2a) = *(short *)(iVar9 + 0x2a) + 1;
        }
        else {
          *(undefined2 *)(iVar9 + 0x2a) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      if (*(short *)(iVar9 + 0x2a) == 0) {
        *(short *)(iVar9 + 0x2a) = (short)iVar8 + -1;
      }
      else {
        *(short *)(iVar9 + 0x2a) = *(short *)(iVar9 + 0x2a) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar7 & 0xc) == 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 0;
      if ((uVar6 & 0x100) == 0) {
        if ((uVar6 & 0x200) != 0) {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
  }
  else {
    if ((uVar7 & 0xc) != 0) {
      iVar12 = (int)*(short *)(iVar9 + 0x26);
      iVar13 = iVar12 + -1;
      iVar8 = iVar12 + -3;
      iVar11 = Game.game.m_scriptFoodBase[0] + iVar13 * 2;
      if (2 < iVar13) {
        do {
          if (-1 < *(short *)(iVar11 + 0x214)) break;
          iVar11 = iVar11 + -2;
          iVar13 = iVar13 + -1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      iVar12 = iVar12 + 1;
      iVar8 = *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa) - iVar12;
      iVar11 = Game.game.m_scriptFoodBase[0] + iVar12 * 2;
      if (iVar12 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
        do {
          if (-1 < *(short *)(iVar11 + 0x214)) break;
          iVar11 = iVar11 + 2;
          iVar12 = iVar12 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      iVar9 = iVar9 + iVar14 * 2;
      if (*(short *)(iVar9 + 0x26) == iVar13) {
        *(short *)(iVar9 + 0x26) = (short)iVar12;
      }
      else {
        *(short *)(iVar9 + 0x26) = (short)iVar13;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar7 & 0xc) == 0) {
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 0;
      if ((uVar6 & 0x100) == 0) {
        if ((uVar6 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
  }
  return 0;
}

