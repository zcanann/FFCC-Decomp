// Function: SelectFigure__9CShopMenuFv
// Entry: 80156170
// Size: 2524 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SelectFigure__9CShopMenuFv(CShopMenu *shopMenu)

{
  bool bVar1;
  ushort uVar3;
  int iVar2;
  CCaravanWork *pCVar4;
  int iVar5;
  double local_18;
  double local_10;
  
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
  if ((uVar3 & 1) == 0) {
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
    if ((uVar3 & 2) == 0) {
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
        *(undefined4 *)&shopMenu->field_0x10 = 2;
      }
    }
    else {
      *(int *)&shopMenu->field_0x38 = *(int *)&shopMenu->field_0x38 + -1;
      if (*(int *)&shopMenu->field_0x38 < 0) {
        *(undefined4 *)&shopMenu->field_0x38 = 0;
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
  }
  else {
    *(int *)&shopMenu->field_0x38 = *(int *)&shopMenu->field_0x38 + 1;
    if (*(int *)&shopMenu->field_0x38 < 2) {
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    else {
      *(undefined4 *)&shopMenu->field_0x38 = 1;
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  if (DAT_8032eed0 == 0) {
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._20_2_;
    }
  }
  else {
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._4_2_;
    }
    if ((uVar3 & DAT_8032eed0) == 0) {
      DAT_8032eed0 = 0;
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
  }
  if ((uVar3 & 8) == 0) {
    if (DAT_8032eed0 == 0) {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._20_2_;
      }
    }
    else {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._4_2_;
      }
      if ((uVar3 & DAT_8032eed0) == 0) {
        DAT_8032eed0 = 0;
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
    }
    if ((uVar3 & 4) != 0) {
      iVar2 = *(int *)&shopMenu->field_0x38;
      if (iVar2 == 1) {
        *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + -10;
        if (*(int *)&shopMenu->field_0x44 < 1) {
          *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + 10;
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else if ((iVar2 < 1) && (-1 < iVar2)) {
        *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + -1;
        if (*(int *)&shopMenu->field_0x44 < 1) {
          DAT_8032eed0 = 4;
          *(undefined4 *)&shopMenu->field_0x44 = 1;
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
    }
  }
  else {
    iVar2 = *(int *)&shopMenu->field_0x38;
    if (iVar2 == 1) {
      *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + 10;
      pCVar4 = *(CCaravanWork **)&shopMenu->field_0x20;
      if (*(int *)&shopMenu->field_0x44 <= (int)(0x40 - (uint)(ushort)pCVar4->m_inventoryItemCount))
      {
        iVar2 = *(int *)&shopMenu->field_0x28;
        if (iVar2 == -1) {
          iVar2 = 0;
        }
        else {
          iVar5 = *(int *)&shopMenu->field_0x14;
          if (iVar5 == 0) {
            iVar2 = (int)pCVar4->m_shopList[iVar2];
          }
          else if (iVar5 == 1) {
            iVar2 = (int)(short)pCVar4->m_inventoryItems[iVar2];
          }
          else if (iVar5 == 2) {
            if (*(int *)(&shopMenu->field_0x50 + iVar2 * 4) == -1) {
              iVar2 = -1;
            }
            else {
              iVar2 = (int)(short)pCVar4->m_inventoryItems
                                  [*(int *)(&shopMenu->field_0x50 + iVar2 * 4)];
            }
          }
          else {
            iVar2 = -1;
          }
          if (iVar5 == 0) {
            if (iVar2 < 1) {
              iVar2 = 0;
            }
            else {
              iVar2 = (int)pCVar4->m_shopParam *
                      (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
              iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
              iVar2 = iVar2 - (iVar2 >> 0x1f);
            }
          }
          else if (iVar5 == 1) {
            if (iVar2 < 1) {
              iVar2 = 0;
            }
            else {
              iVar2 = (int)pCVar4->m_shopParam *
                      (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
              iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
              local_10 = (double)(CONCAT44(0x43300000,iVar2 - (iVar2 >> 0x1f)) ^ 0x80000000);
              iVar2 = (int)(FLOAT_80332d60 * (float)(local_10 - DOUBLE_80332d20));
            }
          }
          else {
            iVar2 = -1;
          }
          iVar2 = *(int *)&shopMenu->field_0x44 * iVar2;
        }
        iVar2 = CanAddGil__12CCaravanWorkFi(pCVar4,-iVar2);
        if (iVar2 != 0) {
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          return;
        }
      }
      *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + -10;
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
    else if ((iVar2 < 1) && (-1 < iVar2)) {
      *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + 1;
      pCVar4 = *(CCaravanWork **)&shopMenu->field_0x20;
      if (*(int *)&shopMenu->field_0x44 <= (int)(0x40 - (uint)(ushort)pCVar4->m_inventoryItemCount))
      {
        iVar2 = *(int *)&shopMenu->field_0x28;
        if (iVar2 == -1) {
          iVar2 = 0;
        }
        else {
          iVar5 = *(int *)&shopMenu->field_0x14;
          if (iVar5 == 0) {
            iVar2 = (int)pCVar4->m_shopList[iVar2];
          }
          else if (iVar5 == 1) {
            iVar2 = (int)(short)pCVar4->m_inventoryItems[iVar2];
          }
          else if (iVar5 == 2) {
            if (*(int *)(&shopMenu->field_0x50 + iVar2 * 4) == -1) {
              iVar2 = -1;
            }
            else {
              iVar2 = (int)(short)pCVar4->m_inventoryItems
                                  [*(int *)(&shopMenu->field_0x50 + iVar2 * 4)];
            }
          }
          else {
            iVar2 = -1;
          }
          if (iVar5 == 0) {
            if (iVar2 < 1) {
              iVar2 = 0;
            }
            else {
              iVar2 = (int)pCVar4->m_shopParam *
                      (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
              iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
              iVar2 = iVar2 - (iVar2 >> 0x1f);
            }
          }
          else if (iVar5 == 1) {
            if (iVar2 < 1) {
              iVar2 = 0;
            }
            else {
              iVar2 = (int)pCVar4->m_shopParam *
                      (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
              iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
              local_18 = (double)(CONCAT44(0x43300000,iVar2 - (iVar2 >> 0x1f)) ^ 0x80000000);
              iVar2 = (int)(FLOAT_80332d60 * (float)(local_18 - DOUBLE_80332d20));
            }
          }
          else {
            iVar2 = -1;
          }
          iVar2 = *(int *)&shopMenu->field_0x44 * iVar2;
        }
        iVar2 = CanAddGil__12CCaravanWorkFi(pCVar4,-iVar2);
        if (iVar2 != 0) {
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          return;
        }
      }
      DAT_8032eed0 = 8;
      *(int *)&shopMenu->field_0x44 = *(int *)&shopMenu->field_0x44 + -1;
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  return;
}

