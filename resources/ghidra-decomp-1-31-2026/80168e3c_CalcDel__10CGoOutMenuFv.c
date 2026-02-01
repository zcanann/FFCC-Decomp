// Function: CalcDel__10CGoOutMenuFv
// Entry: 80168e3c
// Size: 3548 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcDel__10CGoOutMenuFv(CGoOutMenu *goOutMenu)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  
  uVar2 = countLeadingZeros(2 - (char)goOutMenu->field_0x24);
  uVar4 = CalcGoOutSelChar__8CMenuPcsFUcUc(&MenuPcs,uVar2 >> 5 & 0xff,0);
  switch(goOutMenu->field_0x24) {
  case 0:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      if ((uVar3 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        if (goOutMenu->field_0x25 == -1) {
          SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
        }
        else {
          SetDelMode__10CGoOutMenuFUc(goOutMenu,goOutMenu->field_0x25);
        }
      }
    }
    break;
  case 2:
    *(undefined4 *)&goOutMenu->field_0x28 = uVar4;
    iVar5 = *(int *)&goOutMenu->field_0x28;
    if (iVar5 == -2) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,1);
    }
    else if (iVar5 != -1) {
      if (Game.game.m_caravanWorkArr[iVar5].m_shopBusyFlag == '\0') {
        SetDelMode__10CGoOutMenuFUc(goOutMenu,3);
      }
      else {
        SetDelMode__10CGoOutMenuFUc(goOutMenu,6);
      }
    }
    break;
  case 3:
    if (goOutMenu->field_0x45 == '\0') {
      return;
    }
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._8_2_;
    }
    if ((uVar3 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    goOutMenu->field_0x47 = 1;
    bVar6 = 0;
    goOutMenu->field74_0x4a = 0xad;
    goOutMenu->field75_0x4c = 0xbc;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar6 = 1;
      }
      if (bVar6 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      else {
        uVar3 = 0;
      }
      if ((uVar3 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar6 = goOutMenu->field_0x46 + 1;
          goto LAB_80169228;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar6 = 0;
    }
LAB_80169228:
    if (bVar6 == 2) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    else if ((bVar6 < 2) && (bVar6 != 0)) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,4);
    }
    break;
  case 4:
    if (goOutMenu->field_0x45 == '\0') {
      return;
    }
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._8_2_;
    }
    if ((uVar3 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    goOutMenu->field_0x47 = 1;
    bVar6 = 0;
    goOutMenu->field74_0x4a = 0xc2;
    goOutMenu->field75_0x4c = 0xd1;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar6 = 1;
      }
      if (bVar6 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      else {
        uVar3 = 0;
      }
      if ((uVar3 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar6 = goOutMenu->field_0x46 + 1;
          goto LAB_801694b4;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar6 = 0;
    }
LAB_801694b4:
    if (bVar6 == 2) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    else if ((bVar6 < 2) && (bVar6 != 0)) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,5);
    }
    break;
  case 5:
    if ((goOutMenu->field_0x45 != '\0') &&
       (iVar5 = IsMenuCharaAnimIdle__8CMenuPcsFi(&MenuPcs,*(undefined4 *)&goOutMenu->field_0x28),
       iVar5 != 0)) {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      if ((uVar3 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        iVar5 = *(int *)&goOutMenu->field_0x28 * 0xc30;
        Game.game.m_caravanWorkArr[*(int *)&goOutMenu->field_0x28].m_shopState = 0;
        memset(iVar5 + -0x7fddf4ac,0,0x100);
        memset(iVar5 + -0x7fddf3ac,0,0x200);
        SetDelMode__10CGoOutMenuFUc(goOutMenu,1);
      }
    }
    break;
  case 6:
    if (goOutMenu->field_0x45 == '\0') {
      return;
    }
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._8_2_;
    }
    if ((uVar3 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    goOutMenu->field_0x47 = 1;
    bVar6 = 0;
    goOutMenu->field74_0x4a = 0x97;
    goOutMenu->field75_0x4c = 0xe9;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar6 = 1;
      }
      if (bVar6 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      else {
        uVar3 = 0;
      }
      if ((uVar3 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar6 = goOutMenu->field_0x46 + 1;
          goto LAB_80169850;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar6 = 0;
    }
LAB_80169850:
    if (bVar6 == 2) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    else if ((bVar6 < 2) && (bVar6 != 0)) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,7);
    }
    break;
  case 7:
    if (goOutMenu->field_0x45 == '\0') {
      return;
    }
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._8_2_;
    }
    if ((uVar3 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    goOutMenu->field_0x47 = 1;
    bVar6 = 0;
    goOutMenu->field74_0x4a = 0x9f;
    goOutMenu->field75_0x4c = 0xdb;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar6 = 1;
      }
      if (bVar6 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      else {
        uVar3 = 0;
      }
      if ((uVar3 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar6 = goOutMenu->field_0x46 + 1;
          goto LAB_80169adc;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar6 = 0;
    }
LAB_80169adc:
    if (bVar6 == 2) {
      SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
    }
    else if ((bVar6 < 2) && (bVar6 != 0)) {
      Game.game.m_caravanWorkArr[*(int *)&goOutMenu->field_0x28].m_shopBusyFlag = '\0';
      SetDelMode__10CGoOutMenuFUc(goOutMenu,8);
    }
    break;
  case 8:
    if ((goOutMenu->field_0x45 != '\0') &&
       (iVar5 = IsMenuCharaAnimIdle__8CMenuPcsFi(&MenuPcs,*(undefined4 *)&goOutMenu->field_0x28),
       iVar5 != 0)) {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      if ((uVar3 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        SetDelMode__10CGoOutMenuFUc(goOutMenu,1);
      }
    }
  }
  return;
}

