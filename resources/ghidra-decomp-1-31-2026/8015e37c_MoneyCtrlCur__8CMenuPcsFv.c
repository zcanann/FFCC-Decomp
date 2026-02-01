// Function: MoneyCtrlCur__8CMenuPcsFv
// Entry: 8015e37c
// Size: 2604 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 MoneyCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint32_t caravanWork;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined2 local_28;
  undefined2 local_26 [3];
  
  caravanWork = Game.game.m_scriptFoodBase[0];
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
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._20_2_;
  }
  if (uVar4 == 0) {
    return 0;
  }
  iVar11 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
  iVar12 = 1;
  iVar5 = *(int *)(Game.game.m_scriptFoodBase[0] + 0x200);
  if ((((((0 < iVar5 / 10) && (iVar12 = 2, 0 < iVar5 / 100)) && (iVar12 = 3, 0 < iVar5 / 1000)) &&
       ((iVar12 = 4, 0 < iVar5 / 10000 && (iVar12 = 5, 0 < iVar5 / 100000)))) &&
      (iVar12 = 6, 0 < iVar5 / 1000000)) && (iVar12 = 7, 0 < iVar5 / 10000000)) {
    iVar12 = 8;
  }
  iVar5 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
  if (iVar11 != 0) {
    if ((uVar4 & 8) == 0) {
      if ((uVar4 & 4) != 0) {
        iVar5 = *(int *)&menuPcs->field_0x82c + iVar11 * 2;
        if (*(short *)(iVar5 + 0x26) < 1) {
          *(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + 1;
        }
        else {
          *(undefined2 *)(iVar5 + 0x26) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      iVar5 = *(int *)&menuPcs->field_0x82c + iVar11 * 2;
      if (*(short *)(iVar5 + 0x26) == 0) {
        *(undefined2 *)(iVar5 + 0x26) = 1;
      }
      else {
        *(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar4 & 0xc) != 0) {
      return 0;
    }
    if ((uVar3 & 0x100) == 0) {
      if ((uVar3 & 0x200) == 0) {
        return 0;
      }
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      return 0;
    }
    iVar5 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + iVar11 * 2 + 0x26);
    if (((int)*(char *)(*(int *)&menuPcs->field_0x82c + 9) & 1 << iVar5) == 0) {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      return 0;
    }
    if (iVar5 == 0) {
      FGPutGil__12CCaravanWorkFi((CCaravanWork *)caravanWork,DAT_8032eee0);
      bVar2 = false;
      iVar8 = 0;
      iVar11 = 10000000;
      DAT_8032eee0 = 0;
      puVar10 = s_place;
      iVar12 = *(int *)(Game.game.m_scriptFoodBase[0] + 0x200);
      iVar5 = 8;
      do {
        if ((!bVar2) && (iVar11 <= iVar12)) {
          bVar2 = true;
        }
        if (((bVar2) || (iVar11 <= iVar12)) || (6 < iVar8)) {
          iVar9 = iVar12 / iVar11;
          if (9 < iVar9) {
            iVar9 = 9;
          }
          *(char *)puVar10 = (char)iVar9;
          iVar12 = iVar12 - (iVar12 / iVar11) * iVar11;
        }
        else {
          *(undefined *)puVar10 = 0xff;
        }
        puVar10 = (undefined4 *)((int)puVar10 + 1);
        iVar8 = iVar8 + 1;
        iVar11 = iVar11 / 10 + (iVar11 >> 0x1f);
        iVar11 = iVar11 - (iVar11 >> 0x1f);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar12 = 0;
      iVar8 = 0;
      iVar11 = 10000000;
      bVar2 = false;
      puVar10 = s_place;
      iVar5 = 8;
      do {
        if ((!bVar2) && (iVar11 <= iVar12)) {
          bVar2 = true;
        }
        if (((bVar2) || (iVar11 <= iVar12)) || (6 < iVar8)) {
          iVar9 = iVar12 / iVar11;
          if (9 < iVar9) {
            iVar9 = 9;
          }
          *(char *)(puVar10 + 2) = (char)iVar9;
          iVar12 = iVar12 - (iVar12 / iVar11) * iVar11;
        }
        else {
          *(undefined *)(puVar10 + 2) = 0xff;
        }
        puVar10 = (undefined4 *)((int)puVar10 + 1);
        iVar8 = iVar8 + 1;
        iVar11 = iVar11 / 10 + (iVar11 >> 0x1f);
        iVar11 = iVar11 - (iVar11 >> 0x1f);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
    *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
    return 0;
  }
  iVar11 = 1;
  uVar6 = (uint)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  if (0 < (int)uVar6) {
    uVar13 = uVar6 >> 3;
    if (uVar13 != 0) {
      do {
        iVar11 = iVar11 * 100000000;
        uVar13 = uVar13 - 1;
      } while (uVar13 != 0);
      uVar6 = uVar6 & 7;
      if (uVar6 == 0) goto LAB_8015e55c;
    }
    do {
      iVar11 = iVar11 * 10;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
LAB_8015e55c:
  if ((uVar4 & 8) == 0) {
    if ((uVar4 & 4) != 0) {
      uVar6 = *(uint *)(caravanWork + 0x200);
      if (uVar6 == 0) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      else {
        if (-1 < (int)(DAT_8032eee0 - iVar11)) {
          uVar6 = DAT_8032eee0 - iVar11;
        }
        iVar9 = 0;
        iVar8 = 10000000;
        puVar10 = s_place;
        iVar11 = 8;
        bVar2 = false;
        DAT_8032eee0 = uVar6;
        do {
          if ((!bVar2) && (iVar8 <= (int)uVar6)) {
            bVar2 = true;
          }
          if (((bVar2) || (iVar8 <= (int)uVar6)) || (6 < iVar9)) {
            iVar7 = (int)uVar6 / iVar8;
            if (9 < iVar7) {
              iVar7 = 9;
            }
            *(char *)(puVar10 + 2) = (char)iVar7;
            uVar6 = uVar6 - ((int)uVar6 / iVar8) * iVar8;
          }
          else {
            *(undefined *)(puVar10 + 2) = 0xff;
          }
          puVar10 = (undefined4 *)((int)puVar10 + 1);
          iVar9 = iVar9 + 1;
          iVar8 = iVar8 / 10 + (iVar8 >> 0x1f);
          iVar8 = iVar8 - (iVar8 >> 0x1f);
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
  }
  else if (*(int *)(caravanWork + 0x200) == 0) {
    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
  }
  else {
    uVar6 = DAT_8032eee0 + iVar11;
    DAT_8032eee0 = uVar6 & -(uint)!CARRY4(*(int *)(caravanWork + 0x200) - uVar6,uVar6 ^ 0x80000000);
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    iVar9 = 0;
    iVar8 = 10000000;
    puVar10 = s_place;
    iVar11 = 8;
    bVar2 = false;
    uVar6 = DAT_8032eee0;
    do {
      if ((!bVar2) && (iVar8 <= (int)uVar6)) {
        bVar2 = true;
      }
      if (((bVar2) || (iVar8 <= (int)uVar6)) || (6 < iVar9)) {
        iVar7 = (int)uVar6 / iVar8;
        if (9 < iVar7) {
          iVar7 = 9;
        }
        *(char *)(puVar10 + 2) = (char)iVar7;
        uVar6 = uVar6 - ((int)uVar6 / iVar8) * iVar8;
      }
      else {
        *(undefined *)(puVar10 + 2) = 0xff;
      }
      puVar10 = (undefined4 *)((int)puVar10 + 1);
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 / 10 + (iVar8 >> 0x1f);
      iVar8 = iVar8 - (iVar8 >> 0x1f);
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  if ((uVar4 & 1) == 0) {
    if ((uVar4 & 2) != 0) {
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
      if (sVar1 == 0) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      else {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = sVar1 + -1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
  }
  else {
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
    if ((int)sVar1 < iVar12 + -1) {
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = sVar1 + 1;
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    else {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  if ((uVar4 & 0xf) == 0) {
    if ((uVar3 & 0x20) == 0) {
      if ((uVar3 & 0x40) == 0) {
        if ((uVar3 & 0x100) == 0) {
          if ((uVar3 & 0x200) != 0) {
            if (iVar5 < 0) {
              *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
              return 1;
            }
            LetterSetAttachItem__8CMenuPcsFUii(menuPcs,0,0xffffffff);
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            return 1;
          }
        }
        else if ((int)DAT_8032eee0 < 1) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          if (-1 < iVar5) {
            LetterSetAttachItem__8CMenuPcsFUii(menuPcs,DAT_8032eee0,1);
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            return 1;
          }
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 2;
          iVar5 = CanPlayerPutItem__12CCaravanWorkFv((CCaravanWork *)caravanWork);
          if (iVar5 != 0) {
            *(byte *)(*(int *)&menuPcs->field_0x82c + 9) =
                 *(byte *)(*(int *)&menuPcs->field_0x82c + 9) | 1;
          }
          GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,1,local_26,&local_28,0);
          SetSingWinInfo__8CMenuPcsFiiii(menuPcs,0xf0,0xd0,local_26[0],local_28);
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
      else {
        if (iVar5 < 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
          PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
          return 1;
        }
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
    }
    else {
      if (iVar5 < 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        return 1;
      }
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  return 0;
}

