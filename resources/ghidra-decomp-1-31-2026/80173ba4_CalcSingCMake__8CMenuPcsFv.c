// Function: CalcSingCMake__8CMenuPcsFv
// Entry: 80173ba4
// Size: 2984 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcSingCMake__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  undefined uVar3;
  undefined uVar4;
  ushort uVar5;
  ushort uVar6;
  undefined4 uVar7;
  int iVar8;
  ushort unaff_r27;
  int iVar9;
  CCaravanWork *caravanWork;
  double dVar10;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    InitFrame0Info__8CMenuPcsFv(menuPcs);
    memset(&s_CmakeInfo,0,0x16);
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
    DAT_8032ef10 = 0xffffffff;
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
  }
  iVar8 = *(int *)&menuPcs->field_0x82c;
  switch(*(undefined2 *)(iVar8 + 0x16)) {
  case 0:
    if (*(short *)(iVar8 + 0x10) == 0) {
      CalcWMFrame0__8CMenuPcsFi(menuPcs,*(short *)(iVar8 + 0x22) + -10);
      iVar8 = *(int *)&menuPcs->field_0x82c;
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      else {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2a) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2c) = 0;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      unaff_r27 = 0;
    }
    else {
      CalcWMFrame0__8CMenuPcsFi(menuPcs,-(int)*(short *)(iVar8 + 0x22));
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    break;
  case 1:
    if (*(short *)(iVar8 + 0x10) == 0) {
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      unaff_r27 = CmakeNameCtrl__8CMenuPcsFv(menuPcs);
    }
    else if (*(short *)(iVar8 + 0x22) < 10) {
      unaff_r27 = 0;
      *(short *)(iVar8 + 0x22) = *(short *)(iVar8 + 0x22) + 1;
    }
    else {
      if (*(short *)(iVar8 + 0x1e) < 0) {
        ChgModel__8CMenuPcsFiiii
                  (menuPcs,(int)*(short *)&menuPcs->field_0x86a,0xffffffff,0xffffffff,0xffffffff);
      }
      unaff_r27 = 1;
    }
    break;
  case 2:
    if (*(short *)(iVar8 + 0x10) == 0) {
      if (*(char *)(iVar8 + 0xc) == '\0') {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar5 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar5 = Pad._8_2_;
      }
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar6 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar6 = Pad._20_2_;
      }
      if (uVar6 == 0) {
        unaff_r27 = 0;
      }
      else {
        if ((uVar6 & 0xc) != 0) {
          *(ushort *)(iVar8 + 0x26) = *(ushort *)(iVar8 + 0x26) ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        if ((uVar6 & 0xc) == 0) {
          if ((uVar5 & 0x100) != 0) {
            s_CmakeInfo._18_1_ = (undefined)*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26);
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            unaff_r27 = 1;
            break;
          }
          if ((uVar5 & 0x200) != 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            unaff_r27 = 1;
            break;
          }
        }
        unaff_r27 = 0;
      }
    }
    else {
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    break;
  case 3:
    if (*(short *)(iVar8 + 0x10) == 0) {
      if (*(char *)(iVar8 + 0xc) == '\0') {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      unaff_r27 = CmakeTribeCtrl__8CMenuPcsFv(menuPcs);
    }
    else {
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    break;
  case 4:
    if (*(short *)(iVar8 + 0x10) == 0) {
      if (*(char *)(iVar8 + 0xc) == '\0') {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      unaff_r27 = CmakeJobCtrl__8CMenuPcsFv(menuPcs);
    }
    else {
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    break;
  case 5:
    if (*(short *)(iVar8 + 0x10) == 0) {
      if (*(char *)(iVar8 + 0xc) == '\0') {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar5 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar5 = Pad._8_2_;
      }
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar6 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar6 = Pad._20_2_;
      }
      if (uVar6 == 0) {
        unaff_r27 = 0;
      }
      else {
        if ((uVar6 & 3) != 0) {
          *(ushort *)(iVar8 + 0x26) = *(ushort *)(iVar8 + 0x26) ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        if ((uVar6 & 3) == 0) {
          if ((uVar5 & 0x100) != 0) {
            iVar8 = *(int *)&menuPcs->field_0x82c;
            if (*(short *)(iVar8 + 0x26) == 0) {
              *(undefined2 *)(iVar8 + 0x1e) = 1;
              *(undefined4 *)
               (*(int *)&menuPcs->field_0x844 + *(short *)&menuPcs->field_0x86a * 0x14 + 4) = 3;
              iVar9 = (int)*(short *)&menuPcs->field_0x86a;
              uVar7 = GetModelNo__8CMenuPcsFiii
                                (menuPcs,(int)(char)s_CmakeInfo._19_1_,(int)(char)s_CmakeInfo._20_1_
                                 ,(int)(char)s_CmakeInfo._18_1_);
              *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar9 * 0x34 + 8) = uVar7;
              caravanWork = Game.game.m_caravanWorkArr + iVar9;
              *(undefined *)(*(int *)&menuPcs->field_0x828 + 10) = 1;
              LoadInit__12CCaravanWorkFv(caravanWork);
              Game.game.m_caravanWorkArr[iVar9].m_shopState = 1;
              uVar3 = s_CmakeInfo._21_1_;
              Game.game.m_caravanWorkArr[iVar9].unk_0x3a8 = 0x101;
              Game.game.m_caravanWorkArr[iVar9].unk_0x3ac = (int)(char)uVar3;
              memset(iVar9 * 0xc30 + -0x7fddf986,0,0x11);
              strcpy(iVar9 * 0xc30 + -0x7fddf986,&s_CmakeInfo);
              uVar4 = s_CmakeInfo._20_1_;
              uVar3 = s_CmakeInfo._18_1_;
              Game.game.m_caravanWorkArr[iVar9].m_tribeId = (short)(char)s_CmakeInfo._19_1_;
              Game.game.m_caravanWorkArr[iVar9].m_appearanceVariant = (short)(char)uVar4;
              Game.game.m_caravanWorkArr[iVar9].m_genderFlag = (short)(char)uVar3;
              Game.game.m_caravanWorkArr[iVar9].gObjWork.m_id = (uint16_t)uVar7;
              iVar8 = (uint)Game.game.m_caravanWorkArr[iVar9].m_genderFlag +
                      (uint)Game.game.m_caravanWorkArr[iVar9].m_tribeId * 2;
              (**(code **)((int)(caravanWork->gObjWork).vtable + 0xc))
                        (caravanWork,iVar8,Game.game.unkCFlatData0[0] + iVar8 * 0x1d0,
                         Game.game.m_caravanWorkArr[iVar9].m_appearanceVariant);
              LoadFinished__12CCaravanWorkFv(caravanWork);
              CallWorldParam__8CMenuPcsFiii(menuPcs,0,iVar9,0);
              dVar10 = GetMaxAnimWait__8CMenuPcsFv(menuPcs);
              *(short *)(*(int *)&menuPcs->field_0x82c + 0x18) = (short)(int)dVar10;
            }
            else {
              *(undefined2 *)(iVar8 + 0x1e) = 0xffff;
            }
            PlaySe__6CSoundFiiii(&Sound,0x33,0x40,0x7f,0);
            unaff_r27 = 1;
            break;
          }
          if ((uVar5 & 0x200) != 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            unaff_r27 = 1;
            break;
          }
        }
        unaff_r27 = 0;
      }
    }
    else if (*(short *)(iVar8 + 0x18) == 0) {
      if (*(short *)(iVar8 + 0x22) < 10) {
        unaff_r27 = 0;
        *(short *)(iVar8 + 0x22) = *(short *)(iVar8 + 0x22) + 1;
      }
      else {
        unaff_r27 = 1;
      }
    }
    else {
      unaff_r27 = 0;
      *(short *)(iVar8 + 0x18) = *(short *)(iVar8 + 0x18) + -1;
    }
    break;
  case 6:
    if (*(short *)(iVar8 + 0x10) == 0) {
      if (*(char *)(iVar8 + 0xc) == '\0') {
        *(undefined2 *)(iVar8 + 0x26) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      if (sVar1 < 10) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
    else if (*(short *)(iVar8 + 0x10) == 1) {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar5 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar5 = Pad._8_2_;
      }
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar6 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar6 = Pad._20_2_;
      }
      if (uVar6 == 0) {
        unaff_r27 = 0;
      }
      else {
        if ((uVar6 & 8) == 0) {
          if ((uVar6 & 4) != 0) {
            if (*(short *)(iVar8 + 0x26) < 3) {
              *(short *)(iVar8 + 0x26) = *(short *)(iVar8 + 0x26) + 1;
            }
            else {
              *(undefined2 *)(iVar8 + 0x26) = 0;
            }
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
        }
        else {
          if (*(short *)(iVar8 + 0x26) == 0) {
            *(undefined2 *)(iVar8 + 0x26) = 3;
          }
          else {
            *(short *)(iVar8 + 0x26) = *(short *)(iVar8 + 0x26) + -1;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        if ((uVar6 & 0xc) == 0) {
          if ((uVar5 & 0x100) != 0) {
            if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) < 3) {
              ChgModel__8CMenuPcsFiiii
                        (menuPcs,(int)*(short *)&menuPcs->field_0x86a,0xffffffff,0xffffffff,
                         0xffffffff);
            }
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            unaff_r27 = 1;
            break;
          }
          if ((uVar5 & 0x200) != 0) {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
        unaff_r27 = 0;
      }
    }
    else {
      sVar1 = *(short *)(iVar8 + 0x22);
      if (sVar1 < 10) {
        *(short *)(iVar8 + 0x22) = sVar1 + 1;
      }
      unaff_r27 = (ushort)(sVar1 >= 10);
    }
  }
  CalcSingleCMakeChara__8CMenuPcsFv(menuPcs);
  *(ushort *)(*(int *)&menuPcs->field_0x82c + 0x2e) = unaff_r27;
  return;
}

