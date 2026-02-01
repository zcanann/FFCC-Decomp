// Function: Calc__9CShopMenuFv
// Entry: 801577ac
// Size: 4352 bytes

/* WARNING: Removing unreachable block (ram,0x80157b38) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__9CShopMenuFv(CShopMenu *shopMenu)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  ushort uVar6;
  int iVar4;
  undefined4 uVar5;
  short *psVar7;
  short local_28 [8];
  undefined4 local_18;
  uint uStack_14;
  
  switch((shopMenu->field0_0x0).ref.refCount) {
  case 0:
    if (*(int *)&shopMenu->field_0xc == 1) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,1);
    }
    break;
  case 1:
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
    if ((uVar6 & 4) == 0) {
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
      if ((uVar6 & 8) == 0) {
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
        if ((uVar6 & 0x100) != 0) {
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          SetMode__9CShopMenuFi(shopMenu,2);
        }
      }
      else {
        shopMenu->field_0x48 = shopMenu->field_0x48 + -1;
        if (2 < (byte)shopMenu->field_0x48) {
          shopMenu->field_0x48 = 2;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      shopMenu->field_0x48 = shopMenu->field_0x48 + '\x01';
      if (2 < (byte)shopMenu->field_0x48) {
        shopMenu->field_0x48 = 0;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
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
      uVar6 = Pad._8_2_;
    }
    if ((uVar6 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetMode__9CShopMenuFi(shopMenu,2);
      shopMenu->field_0x48 = 2;
    }
    break;
  case 2:
    local_18 = 0x43300000;
    uStack_14 = 8U - *(int *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      bVar1 = shopMenu->field_0x48;
      if (bVar1 == 1) {
        SetMode__9CShopMenuFi(shopMenu,6);
      }
      else if (bVar1 == 0) {
        SetMode__9CShopMenuFi(shopMenu,3);
      }
      else if (bVar1 < 3) {
        ReleasePdt__8CPartPcsFi(&PartPcs,*(undefined4 *)&shopMenu->field_0x18);
        CallShop__12CCaravanWorkFiiiii((CCaravanWork *)Game.game.m_scriptFoodBase[0],0,0,0,0,0);
        *(undefined2 *)(MenuPcs._2128_4_ + 6) = 1;
        __dl__FPv(MenuPcs.m_shopMenuPtr);
        MenuPcs.m_shopMenuPtr = (CShopMenu *)0x0;
        return;
      }
    }
    break;
  case 3:
    if (*(int *)&shopMenu->field_0xc == 0) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,4);
    }
    break;
  case 4:
    iVar3 = *(int *)&shopMenu->field_0x10;
    if (iVar3 == 1) {
      SelectFigure__9CShopMenuFv(shopMenu);
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
      if ((uVar6 & 0x200) != 0) {
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        *(undefined4 *)&shopMenu->field_0x10 = 0;
      }
    }
    else if (iVar3 < 1) {
      if (-1 < iVar3) {
        SelectItemIdx__9CShopMenuFv(shopMenu);
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
        if ((uVar6 & 0x200) != 0) {
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          SetMode__9CShopMenuFi(shopMenu,5);
        }
      }
    }
    else if (iVar3 < 3) {
      SelectYesNo__9CShopMenuFv(shopMenu);
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
      if ((uVar6 & 0x200) != 0) {
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        *(undefined4 *)&shopMenu->field_0x10 = 1;
      }
    }
    break;
  case 5:
  case 8:
    local_18 = 0x43300000;
    uStack_14 = 8U - *(int *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,0);
    }
    break;
  case 6:
    if (*(int *)&shopMenu->field_0xc == 0) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,7);
    }
    break;
  case 7:
    iVar3 = *(int *)&shopMenu->field_0x10;
    if (iVar3 != 1) {
      if (iVar3 < 1) {
        if (-1 < iVar3) {
          SelectItemIdx__9CShopMenuFv(shopMenu);
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
          if ((uVar6 & 0x200) != 0) {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            SetMode__9CShopMenuFi(shopMenu,8);
          }
        }
      }
      else if (iVar3 < 3) {
        SelectYesNo__9CShopMenuFv(shopMenu);
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
        if ((uVar6 & 0x200) != 0) {
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          *(undefined4 *)&shopMenu->field_0x10 = 0;
        }
      }
    }
    break;
  case 9:
    if (*(int *)&shopMenu->field_0xc == 1) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,10);
    }
    break;
  case 10:
    SelectItemIdx__9CShopMenuFv(shopMenu);
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
    if ((uVar6 & 0x200) != 0) {
      *(undefined4 *)&shopMenu->field_0x8 = 0xffffffff;
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetMode__9CShopMenuFi(shopMenu,0xb);
    }
    break;
  case 0xb:
    local_18 = 0x43300000;
    uStack_14 = 8U - *(int *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      if (*(int *)&shopMenu->field_0x8 == -1) {
        ReleasePdt__8CPartPcsFi(&PartPcs,*(undefined4 *)&shopMenu->field_0x18);
        CallShop__12CCaravanWorkFiiiii((CCaravanWork *)Game.game.m_scriptFoodBase[0],0,0,0,0,0);
        *(undefined2 *)(MenuPcs._2128_4_ + 6) = 1;
        __dl__FPv(MenuPcs.m_shopMenuPtr);
        MenuPcs.m_shopMenuPtr = (CShopMenu *)0x0;
        return;
      }
      SetMode__9CShopMenuFi(shopMenu,*(int *)&shopMenu->field_0x8);
    }
    break;
  case 0xc:
    if (*(int *)&shopMenu->field_0xc == 1) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,0xd);
    }
    break;
  case 0xd:
    SelectMake__9CShopMenuFv(shopMenu);
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
    if ((uVar6 & 0x200) != 0) {
      *(undefined4 *)&shopMenu->field_0x8 = 9;
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetMode__9CShopMenuFi(shopMenu,0xe);
    }
    break;
  case 0xe:
    local_18 = 0x43300000;
    uStack_14 = 8U - *(int *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,*(undefined4 *)&shopMenu->field_0x8);
    }
    break;
  case 0xf:
    if (*(int *)&shopMenu->field_0xc == 1) {
      PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
    }
    local_18 = 0x43300000;
    uStack_14 = *(uint *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      iVar4 = *(int *)&shopMenu->field_0x14;
      iVar3 = *(int *)&shopMenu->field_0x28;
      if (iVar4 == 0) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
      }
      else if (iVar4 == 1) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
      }
      else if (iVar4 == 2) {
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
      GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(&MenuPcs,iVar3,local_28);
      iVar4 = *(int *)&shopMenu->field_0x14;
      iVar3 = *(int *)&shopMenu->field_0x28;
      if (iVar4 == 0) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
      }
      else if (iVar4 == 1) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
      }
      else if (iVar4 == 2) {
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
      AddGil__12CCaravanWorkFi(*(CCaravanWork **)&shopMenu->field_0x20,-iVar3);
      iVar4 = *(int *)&shopMenu->field_0x14;
      iVar3 = *(int *)&shopMenu->field_0x28;
      if (iVar4 == 0) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xbe6);
      }
      else if (iVar4 == 1) {
        iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar3 * 2 + 0xb6);
      }
      else if (iVar4 == 2) {
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
      DeleteItem__12CCaravanWorkFii(*(CCaravanWork **)&shopMenu->field_0x20,iVar3,0);
      iVar3 = 0;
      psVar7 = local_28;
      do {
        if (*psVar7 < 1) break;
        for (iVar4 = 0; iVar4 < psVar7[3]; iVar4 = iVar4 + 1) {
          DeleteItem__12CCaravanWorkFii(*(CCaravanWork **)&shopMenu->field_0x20,(int)*psVar7,0);
        }
        iVar3 = iVar3 + 1;
        psVar7 = psVar7 + 1;
      } while (iVar3 < 3);
      AddItem__12CCaravanWorkFiPi
                (*(CCaravanWork **)&shopMenu->field_0x20,
                 (short)*(undefined4 *)&shopMenu->field_0x150,&shopMenu->field_0x154);
      SetMode__9CShopMenuFi(shopMenu,0x10);
    }
    break;
  case 0x10:
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
    if ((uVar6 & 0xc) == 0) {
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
      if ((uVar6 & 0x100) != 0) {
        *(undefined4 *)&shopMenu->field_0x8 = 9;
        SetMode__9CShopMenuFi(shopMenu,0x11);
        iVar3 = *(int *)&shopMenu->field_0x3c;
        if (iVar3 == 1) {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else if ((iVar3 < 1) && (-1 < iVar3)) {
          uVar5 = GetEquipType__8CMenuPcsFi(&MenuPcs,*(undefined4 *)&shopMenu->field_0x150);
          ChgEquipPos__12CCaravanWorkFii
                    (*(CCaravanWork **)&shopMenu->field_0x20,uVar5,
                     (short)*(undefined4 *)&shopMenu->field_0x154);
          PlaySe__6CSoundFiiii(&Sound,0x51,0x40,0x7f,0);
        }
      }
    }
    else {
      *(uint *)&shopMenu->field_0x3c = *(uint *)&shopMenu->field_0x3c ^ 1;
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
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
      uVar6 = Pad._8_2_;
    }
    if ((uVar6 & 0x200) != 0) {
      *(undefined4 *)&shopMenu->field_0x8 = 9;
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetMode__9CShopMenuFi(shopMenu,0x11);
    }
    break;
  case 0x11:
    local_18 = 0x43300000;
    uStack_14 = 8U - *(int *)&shopMenu->field_0xc ^ 0x80000000;
    *(float *)&shopMenu->field_0x1c =
         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80332d20) * FLOAT_80332e50;
    if (*(int *)&shopMenu->field_0xc == 8) {
      SetMode__9CShopMenuFi(shopMenu,*(undefined4 *)&shopMenu->field_0x8);
    }
  }
  *(int *)&shopMenu->field_0xc = *(int *)&shopMenu->field_0xc + 1;
  return;
}

