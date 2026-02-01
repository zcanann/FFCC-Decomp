// Function: CalcGoOutCharaSelect__8CMenuPcsFUc
// Entry: 800fc4bc
// Size: 1392 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcGoOutCharaSelect__8CMenuPcsFUc(CMenuPcs *menuPcs,char param_2)

{
  bool bVar1;
  ushort uVar3;
  int iVar2;
  int iVar4;
  undefined uVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) {
    if (menuPcs->field_0x888 == '\x01') {
      uVar6 = (uint)(*(int *)(*(int *)&menuPcs->field_0x88c + 0x1a84) != 0);
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x2444) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x2e04) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x37c4) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x4184) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x4b44) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x5504) != 0) {
        uVar6 = uVar6 + 1;
      }
      if (*(int *)(*(int *)&menuPcs->field_0x88c + 0x5ec4) != 0) {
        uVar6 = uVar6 + 1;
      }
    }
    else {
      uVar6 = (uint)(Game.game.m_caravanWorkArr[0].m_shopState != 0);
      if (Game.game.m_caravanWorkArr[1].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[2].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[3].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[4].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[5].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[6].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
      if (Game.game.m_caravanWorkArr[7].m_shopState != 0) {
        uVar6 = uVar6 + 1;
      }
    }
    uVar8 = 0;
    iVar9 = 0;
    do {
      if (((*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar9 * 4))->m_charaKind != 3) &&
         (iVar4 = IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv
                            (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar9 * 4)), iVar4 != 0)
         ) {
        uVar8 = uVar8 + 1;
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < 8);
    if ((uVar8 == uVar6) &&
       (piVar7 = *(int **)&menuPcs->field_0x828, *(char *)((int)piVar7 + 10) == '\0')) {
      iVar9 = GetPadType__6JoyBusFi(&Joybus,0);
      *piVar7 = iVar9;
      iVar9 = *piVar7;
      if ((iVar9 == 0x9000000) || ((iVar9 == -0x74f00000 || (iVar9 == -0x78000000)))) {
        *(undefined *)((int)piVar7 + 0xd) = 1;
      }
      else if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        uVar5 = GetGBAConnect__6JoyBusFi(&Joybus,0);
        *(undefined *)((int)piVar7 + 0xd) = uVar5;
      }
      else {
        *(undefined *)((int)piVar7 + 0xd) = 0;
      }
      if ((*(char *)((int)piVar7 + 0xd) == '\x01') && (*(char *)((int)piVar7 + 0xb) == '\0')) {
        bVar1 = true;
        if ((Pad._452_4_ == 0) && (Pad._448_4_ == -1)) {
          bVar1 = false;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._20_2_;
        }
        bVar1 = true;
        if ((Pad._452_4_ == 0) && (Pad._448_4_ == -1)) {
          bVar1 = false;
        }
        if (bVar1) {
          uVar10 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar10 = Pad._8_2_;
        }
      }
      else {
        uVar3 = 0;
        uVar10 = 0;
      }
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) == 0)) {
        iVar4 = *(int *)&menuPcs->field_0x828;
        iVar9 = (int)*(short *)(iVar4 + 4);
        if ((uVar3 & 0xc) != 0) {
          if (iVar9 < 4) {
            iVar9 = iVar9 + 4;
          }
          else {
            iVar9 = iVar9 + -4;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        uVar6 = iVar9 >> 2;
        if ((uVar3 & 1) == 0) {
          if ((uVar3 & 2) != 0) {
            iVar2 = 3;
            if (uVar6 != 0) {
              iVar2 = 7;
            }
            if (iVar9 < iVar2) {
              iVar9 = iVar9 + 1;
            }
            else {
              iVar9 = iVar9 + -3;
            }
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
        }
        else {
          if ((int)((int)(-uVar6 | uVar6) >> 0x1f & 4U) < iVar9) {
            iVar9 = iVar9 + -1;
          }
          else {
            iVar9 = iVar9 + 3;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        *(short *)(iVar4 + 4) = (short)iVar9;
        if ((uVar3 & 0x6f) == 0) {
          if ((uVar10 & 0x100) == 0) {
            if ((uVar10 & 0x200) != 0) {
              *(undefined *)(iVar4 + 0xe) = 1;
              PlaySe__6CSoundFiiii(&Sound,0x34,0x40,0x7f,0);
            }
          }
          else {
            if ((menuPcs->field_0x888 == '\x01') && (*(int *)&menuPcs->field_0x88c != 0)) {
              iVar2 = *(int *)(*(int *)&menuPcs->field_0x88c + *(short *)(iVar4 + 4) * 0x9c0 +
                              0x1a84);
            }
            else {
              iVar2 = Game.game.m_caravanWorkArr[*(short *)(iVar4 + 4)].m_shopState;
            }
            if (iVar2 == 0) {
              PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
            }
            else {
              *(undefined *)(iVar4 + 10) = 1;
              PlaySe__6CSoundFiiii(&Sound,0x33,0x40,0x7f,0);
              if (param_2 != '\0') {
                *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar9 * 0x14 + 4) = 3;
              }
            }
          }
        }
      }
    }
  }
  return;
}

