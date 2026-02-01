// Function: CalcOptionMenu__8CMenuPcsFv
// Entry: 80179328
// Size: 2560 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcOptionMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  ushort uVar10;
  int iVar8;
  uint uVar9;
  ushort uVar11;
  double local_38;
  
  fVar7 = FLOAT_8033364c;
  fVar6 = FLOAT_80333598;
  fVar5 = FLOAT_8033356c;
  fVar4 = FLOAT_8033354c;
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar10 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar10 = Pad._8_2_;
  }
  cVar1 = menuPcs->field_0x9c;
  bVar2 = false;
  if (cVar1 == '\0') {
    *(float *)&menuPcs->field_0x98 = *(float *)&menuPcs->field_0x98 + FLOAT_80333648;
    if (*(float *)&menuPcs->field_0x98 < fVar5) {
      return;
    }
    menuPcs->field_0x9c = 1;
    *(float *)&menuPcs->field_0x98 = fVar5;
    return;
  }
  if (cVar1 == '\x02') {
    *(float *)&menuPcs->field_0x98 = *(float *)&menuPcs->field_0x98 - FLOAT_80333648;
    *(float *)&menuPcs->field_0xa0 = *(float *)&menuPcs->field_0xa0 - fVar6;
    *(float *)&menuPcs->field_0xa8 = *(float *)&menuPcs->field_0xa8 - fVar7;
    if (*(float *)&menuPcs->field_0xa0 <= fVar4) {
      *(float *)&menuPcs->field_0xa0 = fVar4;
    }
    if (*(float *)&menuPcs->field_0xa8 <= FLOAT_8033354c) {
      *(float *)&menuPcs->field_0xa8 = FLOAT_8033354c;
    }
    if ((int)(*(float *)&menuPcs->field_0x98 / FLOAT_80333648) == 5) {
      PlaySe__6CSoundFiiii(&Sound,0x32,0x40,0x7f,0);
    }
    fVar4 = FLOAT_8033354c;
    if (FLOAT_8033354c < *(float *)&menuPcs->field_0x98) {
      return;
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 1;
    menuPcs->field_0x8e = 0;
    menuPcs->field_0x9c = 0;
    *(float *)&menuPcs->field_0x98 = fVar4;
    *(float *)&menuPcs->field_0xa0 = fVar4;
    *(float *)&menuPcs->field_0xa8 = fVar4;
    menuPcs->field_0xac = 0;
    menuPcs->field_0xa4 = 0;
    return;
  }
  if (cVar1 == '\x03') {
    return;
  }
  if (menuPcs->field_0xa4 == '\0') {
    *(float *)&menuPcs->field_0xa0 = *(float *)&menuPcs->field_0xa0 + FLOAT_80333598;
    menuPcs->field_0xac = menuPcs->field_0xac + '\x01';
    if (fVar5 <= *(float *)&menuPcs->field_0xa0) {
      menuPcs->field_0xa4 = 1;
      *(float *)&menuPcs->field_0xa0 = fVar5;
    }
  }
  else if ((menuPcs->field_0xa4 == '\x01') &&
          (*(float *)&menuPcs->field_0xa8 = *(float *)&menuPcs->field_0xa8 + FLOAT_8033364c,
          fVar5 <= *(float *)&menuPcs->field_0xa8)) {
    menuPcs->field_0xa4 = 2;
    *(float *)&menuPcs->field_0xa8 = fVar5;
  }
  if ('\0' < (char)menuPcs->field_0x93) {
    menuPcs->field_0x93 = menuPcs->field_0x93 + -1;
  }
  if ('\0' < (char)menuPcs->field_0x94) {
    menuPcs->field_0x94 = menuPcs->field_0x94 + -1;
  }
  if ((*(int *)&menuPcs->field_0xb0 == 0) && ((uVar10 & 8) != 0)) {
    menuPcs->field_0x93 = 0;
    menuPcs->field_0x94 = 0;
    menuPcs->field_0x8e = menuPcs->field_0x8e + -1;
    if ((char)menuPcs->field_0x8e < '\0') {
      menuPcs->field_0x8e = 4;
    }
    fVar4 = FLOAT_8033354c;
    *(float *)&menuPcs->field_0xa0 = FLOAT_8033354c;
    *(float *)&menuPcs->field_0xa8 = fVar4;
    menuPcs->field_0xac = 0;
    menuPcs->field_0xa4 = 0;
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
  }
  else if ((*(int *)&menuPcs->field_0xb0 == 0) && ((uVar10 & 4) != 0)) {
    menuPcs->field_0x93 = 0;
    menuPcs->field_0x94 = 0;
    menuPcs->field_0x8e = menuPcs->field_0x8e + '\x01';
    if ('\x04' < (char)menuPcs->field_0x8e) {
      menuPcs->field_0x8e = 0;
    }
    fVar4 = FLOAT_8033354c;
    *(float *)&menuPcs->field_0xa0 = FLOAT_8033354c;
    *(float *)&menuPcs->field_0xa8 = fVar4;
    menuPcs->field_0xac = 0;
    menuPcs->field_0xa4 = 0;
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
  }
  iVar8 = *(int *)&menuPcs->field_0xb0;
  if (iVar8 == 0) {
    bVar3 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar11 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar11 = Pad._8_2_;
    }
    if ((uVar11 & 0x200) != 0) {
      menuPcs->field_0x9c = 2;
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      return;
    }
  }
  if (menuPcs->field_0xa4 == '\0') {
    return;
  }
  if (menuPcs->field_0xa4 == '\x01') {
    return;
  }
  if ((uVar10 & 1) == 0) {
    if ((uVar10 & 2) != 0) {
      cVar1 = menuPcs->field_0x8e;
      if (cVar1 == '\x02') {
        menuPcs->field_0x94 = 3;
        menuPcs->field_0x93 = 0;
        menuPcs->field_0x91 = menuPcs->field_0x91 + '\x01';
        if ('\f' < (char)menuPcs->field_0x91) {
          menuPcs->field_0x91 = 0xc;
        }
      }
      else if (cVar1 < '\x02') {
        if (cVar1 == '\0') {
          menuPcs->field_0x8f = menuPcs->field_0x8f + '\x01';
          if ('\x01' < (char)menuPcs->field_0x8f) {
            menuPcs->field_0x8f = 0;
          }
        }
        else if ((-1 < cVar1) &&
                (menuPcs->field_0x90 = menuPcs->field_0x90 + '\x01',
                '\x01' < (char)menuPcs->field_0x90)) {
          menuPcs->field_0x90 = 0;
        }
      }
      else if (cVar1 == '\x04') {
        if (iVar8 != 0) {
          (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] =
               (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] + '\x01';
          if ('\x01' < (char)(&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4]) {
            (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] = 0;
          }
        }
      }
      else if (cVar1 < '\x04') {
        menuPcs->field_0x94 = 3;
        menuPcs->field_0x93 = 0;
        menuPcs->field_0x92 = menuPcs->field_0x92 + '\x01';
        if ('\f' < (char)menuPcs->field_0x92) {
          menuPcs->field_0x92 = 0xc;
        }
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      bVar2 = true;
    }
  }
  else {
    cVar1 = menuPcs->field_0x8e;
    if (cVar1 == '\x02') {
      menuPcs->field_0x93 = 3;
      menuPcs->field_0x94 = 0;
      menuPcs->field_0x91 = menuPcs->field_0x91 + -1;
      if ((char)menuPcs->field_0x91 < '\0') {
        menuPcs->field_0x91 = 0;
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        menuPcs->field_0x8f = menuPcs->field_0x8f + -1;
        if ((char)menuPcs->field_0x8f < '\0') {
          menuPcs->field_0x8f = 1;
        }
      }
      else if ((-1 < cVar1) &&
              (menuPcs->field_0x90 = menuPcs->field_0x90 + -1, (char)menuPcs->field_0x90 < '\0')) {
        menuPcs->field_0x90 = 1;
      }
    }
    else if (cVar1 == '\x04') {
      if (iVar8 != 0) {
        (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] =
             (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] + -1;
        if ((char)(&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] < '\0') {
          (&menuPcs->field_0xb5)[(char)menuPcs->field_0xb4] = 1;
        }
      }
    }
    else if (cVar1 < '\x04') {
      menuPcs->field_0x93 = 3;
      menuPcs->field_0x94 = 0;
      menuPcs->field_0x92 = menuPcs->field_0x92 + -1;
      if ((char)menuPcs->field_0x92 < '\0') {
        menuPcs->field_0x92 = 0;
      }
    }
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    bVar2 = true;
  }
  if (menuPcs->field_0x8e == '\x04') {
    bVar3 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar11 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar11 = Pad._8_2_;
    }
    if ((uVar11 & 0x100) == 0) {
      iVar8 = *(int *)&menuPcs->field_0xb0;
      if (iVar8 != 0) {
        bVar3 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar3 = true;
        }
        if (bVar3) {
          uVar11 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar11 = Pad._8_2_;
        }
        if ((uVar11 & 0x200) != 0) {
          menuPcs->field_0xb4 = 0;
          *(undefined4 *)&menuPcs->field_0xb0 = 0;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          uVar9 = countLeadingZeros(1 - (char)menuPcs->field_0xb5);
          Game.game.m_gameWork.m_spModeFlags[0] = (uint8_t)(uVar9 >> 5);
          uVar9 = countLeadingZeros(1 - (char)menuPcs->field_0xb6);
          Game.game.m_gameWork.m_spModeFlags[1] = (uint8_t)(uVar9 >> 5);
          uVar9 = countLeadingZeros(1 - (char)menuPcs->field_0xb7);
          Game.game.m_gameWork.m_spModeFlags[2] = (uint8_t)(uVar9 >> 5);
          uVar9 = countLeadingZeros(1 - (char)menuPcs->field_0xb8);
          Game.game.m_gameWork.m_spModeFlags[3] = (uint8_t)(uVar9 >> 5);
          goto LAB_80179c40;
        }
      }
      if ((iVar8 == 0) || ((uVar10 & 8) == 0)) {
        if ((iVar8 != 0) && ((uVar10 & 4) != 0)) {
          menuPcs->field_0xb4 = menuPcs->field_0xb4 + '\x01';
          if ('\x03' < (char)menuPcs->field_0xb4) {
            menuPcs->field_0xb4 = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        menuPcs->field_0xb4 = menuPcs->field_0xb4 + -1;
        if ((char)menuPcs->field_0xb4 < '\0') {
          menuPcs->field_0xb4 = 3;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else if (*(int *)&menuPcs->field_0xb0 == 0) {
      menuPcs->field_0xb4 = 0;
      *(undefined4 *)&menuPcs->field_0xb0 = 1;
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
    }
  }
LAB_80179c40:
  if (bVar2) {
    uVar9 = countLeadingZeros((int)(char)menuPcs->field_0x8f);
    Game.game.m_gameWork.m_gameInitFlag = (uint8_t)(uVar9 >> 5);
    uVar9 = countLeadingZeros((int)(char)menuPcs->field_0x90);
    SetStereo__6CSoundFi(&Sound,uVar9 >> 5);
    local_38 = (double)(CONCAT44(0x43300000,(int)(char)menuPcs->field_0x92) ^ 0x80000000);
    SetSeMasterVolume__6CSoundFi(&Sound,(int)(FLOAT_80333650 * (float)(local_38 - DOUBLE_80333640)))
    ;
    SetBgmMasterVolume__6CSoundFi
              (&Sound,(int)(FLOAT_80333650 *
                           (float)((double)CONCAT44(0x43300000,
                                                    (int)(char)menuPcs->field_0x91 ^ 0x80000000) -
                                  DOUBLE_80333640)));
  }
  return;
}

