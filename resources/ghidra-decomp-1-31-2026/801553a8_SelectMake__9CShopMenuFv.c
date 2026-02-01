// Function: SelectMake__9CShopMenuFv
// Entry: 801553a8
// Size: 1420 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SelectMake__9CShopMenuFv(CShopMenu *shopMenu)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  short local_18 [8];
  
  uVar6 = ChkEquipPossible__8CMenuPcsFi(&MenuPcs,*(undefined4 *)&shopMenu->field_0x150);
  uVar6 = -((int)-(uVar6 & 0xff) >> 0x1f);
  if (uVar6 != 0) {
    iVar7 = *(int *)&shopMenu->field_0x14;
    iVar3 = *(int *)&shopMenu->field_0x28;
    if (iVar7 == 0) {
      iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
    }
    else if (iVar7 == 1) {
      iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
    }
    else if (iVar7 == 2) {
      if (*(int *)(&shopMenu->field_0x50 + iVar3 * 4) == -1) {
        iVar3 = -1;
      }
      else {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                *(int *)(&shopMenu->field_0x50 + iVar3 * 4) * 2 + 0xb6);
      }
    }
    else {
      iVar3 = -1;
    }
    uVar6 = *(uint *)(*(int *)&shopMenu->field_0x20 + 0x200);
    if (iVar3 < 1) {
      uVar4 = 0;
    }
    else {
      iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
              (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar3 * 0x48 + 0x24);
      iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
      uVar4 = iVar3 - (iVar3 >> 0x1f);
    }
    uVar6 = ((int)uVar6 >> 0x1f) + ((uint)(uVar4 <= uVar6) - ((int)uVar4 >> 0x1f));
  }
  iVar7 = *(int *)&shopMenu->field_0x14;
  uVar6 = uVar6 & 0xff;
  iVar3 = *(int *)&shopMenu->field_0x28;
  if (iVar7 == 0) {
    iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
  }
  else if (iVar7 == 1) {
    iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
  }
  else if (iVar7 == 2) {
    if (*(int *)(&shopMenu->field_0x50 + iVar3 * 4) == -1) {
      iVar3 = -1;
    }
    else {
      iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                              *(int *)(&shopMenu->field_0x50 + iVar3 * 4) * 2 + 0xb6);
    }
  }
  else {
    iVar3 = -1;
  }
  GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(&MenuPcs,iVar3,local_18);
  iVar3 = 0;
  psVar8 = local_18;
  do {
    sVar1 = *psVar8;
    if (sVar1 < 1) break;
    uVar6 = -((int)-uVar6 >> 0x1f);
    if (uVar6 != 0) {
      iVar7 = 0;
      uVar6 = 0;
      iVar9 = 8;
      do {
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xb6) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xb8) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xba) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xbc) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xbe) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xc0) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xc2) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 + 0xc4) == sVar1) {
          uVar6 = uVar6 + 1;
        }
        iVar7 = iVar7 + 0x10;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      uVar6 = ((int)uVar6 >> 0x1f) +
              ((uint)((uint)(int)psVar8[3] <= uVar6) - ((int)psVar8[3] >> 0x1f));
    }
    iVar3 = iVar3 + 1;
    uVar6 = uVar6 & 0xff;
    psVar8 = psVar8 + 1;
  } while (iVar3 < 3);
  if (uVar6 == 0) {
    *(undefined4 *)&shopMenu->field_0x3c = 1;
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
    uVar5 = Pad._8_2_;
  }
  if ((uVar5 & 0xc) == 0) {
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
    if ((uVar5 & 0x100) != 0) {
      iVar3 = *(int *)&shopMenu->field_0x3c;
      if (iVar3 != 1) {
        if (0 < iVar3) {
          return;
        }
        if (iVar3 < 0) {
          return;
        }
        iVar7 = *(int *)&shopMenu->field_0x14;
        iVar3 = *(int *)&shopMenu->field_0x28;
        if (iVar7 == 0) {
          iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
        }
        else if (iVar7 == 1) {
          iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
        }
        else if (iVar7 == 2) {
          if (*(int *)(&shopMenu->field_0x50 + iVar3 * 4) == -1) {
            iVar3 = -1;
          }
          else {
            iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                    *(int *)(&shopMenu->field_0x50 + iVar3 * 4) * 2 + 0xb6);
          }
        }
        else {
          iVar3 = -1;
        }
        if (iVar3 < 1) {
          iVar3 = 0;
        }
        else {
          iVar3 = (int)(*(CCaravanWork **)&shopMenu->field_0x20)->m_shopParam *
                  (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar3 * 0x48 + 0x24);
          iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
          iVar3 = iVar3 - (iVar3 >> 0x1f);
        }
        iVar3 = CanAddGil__12CCaravanWorkFi(*(CCaravanWork **)&shopMenu->field_0x20,-iVar3);
        if (iVar3 != 0) {
          PlaySe__6CSoundFiiii(&Sound,0x52,0x40,0x7f,0);
          *(undefined4 *)&shopMenu->field_0x8 = 0xf;
          SetMode__9CShopMenuFi(shopMenu,0xe);
          return;
        }
      }
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      *(undefined4 *)&shopMenu->field_0x8 = 9;
      SetMode__9CShopMenuFi(shopMenu,0xe);
    }
  }
  else {
    *(uint *)&shopMenu->field_0x3c = *(uint *)&shopMenu->field_0x3c ^ 1;
    if (uVar6 == 1) {
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    else {
      *(undefined4 *)&shopMenu->field_0x3c = 1;
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  return;
}

