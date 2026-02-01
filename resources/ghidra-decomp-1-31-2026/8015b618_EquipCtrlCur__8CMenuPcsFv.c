// Function: EquipCtrlCur__8CMenuPcsFv
// Entry: 8015b618
// Size: 1592 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 EquipCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint32_t caravanWork;
  uint32_t uVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  short *psVar7;
  char cVar8;
  int iVar9;
  undefined2 uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  
  caravanWork = Game.game.m_scriptFoodBase[0];
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._8_2_;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar5 = Pad._20_2_;
  }
  if (uVar5 == 0) {
    return 0;
  }
  iVar6 = *(int *)&menuPcs->field_0x82c;
  iVar12 = (int)*(short *)(iVar6 + 0x30);
  if (iVar12 == 0) {
    if ((uVar5 & 8) == 0) {
      if ((uVar5 & 4) != 0) {
        if (*(short *)(iVar6 + 0x26) < 3) {
          *(short *)(iVar6 + 0x26) = *(short *)(iVar6 + 0x26) + 1;
        }
        else {
          *(undefined2 *)(iVar6 + 0x26) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      if (*(short *)(iVar6 + 0x26) == 0) {
        *(undefined2 *)(iVar6 + 0x26) = 3;
      }
      else {
        *(short *)(iVar6 + 0x26) = *(short *)(iVar6 + 0x26) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar5 & 0xc) == 0) {
      if ((uVar4 & 0x20) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        return 1;
      }
      if ((uVar4 & 0x40) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        return 1;
      }
      if ((uVar4 & 0x100) == 0) {
        if ((uVar4 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          return 1;
        }
      }
      else {
        iVar6 = CanPlayerPutItem__12CCaravanWorkFv((CCaravanWork *)caravanWork);
        if (iVar6 == 0) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
    }
  }
  else {
    psVar7 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    if ((uVar5 & 8) == 0) {
      if ((uVar5 & 4) != 0) {
        iVar9 = *(int *)&menuPcs->field_0x82c;
        iVar6 = iVar9 + iVar12 * 2;
        sVar1 = *(short *)(iVar6 + 0x26);
        if (sVar1 < 7) {
          *(short *)(iVar6 + 0x26) = sVar1 + 1;
        }
        else if ((int)*(short *)(iVar9 + 0x34) + (int)sVar1 < *psVar7 + -1) {
          *(short *)(iVar9 + 0x34) = *(short *)(iVar9 + 0x34) + 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      iVar9 = *(int *)&menuPcs->field_0x82c;
      iVar6 = iVar9 + iVar12 * 2;
      sVar1 = *(short *)(iVar6 + 0x26);
      if (sVar1 == 0) {
        if (*(short *)(iVar9 + 0x34) == 0) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          *(short *)(iVar9 + 0x34) = *(short *)(iVar9 + 0x34) + -1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(iVar6 + 0x26) = sVar1 + -1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    if ((uVar5 & 0xc) == 0) {
      if ((uVar4 & 0x100) == 0) {
        if ((uVar4 & 0x200) != 0) {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          CmdInit2__8CMenuPcsFv(menuPcs);
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
      else {
        iVar12 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34) +
                 (int)*(short *)(*(int *)&menuPcs->field_0x82c + iVar12 * 2 + 0x26);
        iVar6 = GetLetterBuffer__6JoyBusFi(&Joybus,0);
        uVar3 = Game.game.m_scriptFoodBase[0];
        psVar7 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
        iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
        if ((iVar12 < 0) || (*psVar7 <= iVar12)) {
          uVar13 = 0;
        }
        else if (iVar12 == 0) {
          if (iVar9 < 3) {
            uVar13 = 0;
          }
          else {
            uVar13 = (uint)(int)*(short *)(uVar3 + iVar9 * 2 + 0xac) >> 0x1f ^ 1;
          }
        }
        else {
          iVar11 = (int)*(short *)(uVar3 + psVar7[iVar12] * 2 + 0xb6);
          uVar13 = ChkEquipPossible__8CMenuPcsFi(menuPcs,iVar11);
          if (((uVar13 & 0xff) != 0) &&
             (iVar11 = GetEquipType__8CMenuPcsFi(menuPcs,iVar11), iVar11 != iVar9)) {
            uVar13 = 0;
          }
        }
        if (((uVar13 & 0xff) == 0) ||
           ((iVar12 != 0 &&
            (cVar8 = EquipChk__8CMenuPcsFi(menuPcs,(int)*(short *)(iVar6 + iVar12 * 2)),
            cVar8 != '\0')))) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          if (iVar12 == 0) {
            uVar10 = 0xffff;
          }
          else {
            uVar10 = *(undefined2 *)(iVar6 + iVar12 * 2);
          }
          ChgEquipPos__12CCaravanWorkFii
                    ((CCaravanWork *)caravanWork,
                     (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),uVar10);
          CalcStatus__12CCaravanWorkFv(caravanWork);
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          CmdInit2__8CMenuPcsFv(menuPcs);
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
    }
  }
  return 0;
}

