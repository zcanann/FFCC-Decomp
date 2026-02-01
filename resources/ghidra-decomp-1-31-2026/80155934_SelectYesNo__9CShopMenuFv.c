// Function: SelectYesNo__9CShopMenuFv
// Entry: 80155934
// Size: 2108 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SelectYesNo__9CShopMenuFv(CShopMenu *shopMenu)

{
  bool bVar1;
  ushort uVar4;
  int iVar2;
  int iVar3;
  int iVar5;
  CCaravanWork *caravanWork;
  char cVar6;
  int iVar7;
  double local_28;
  double local_20;
  
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._8_2_;
  }
  if ((uVar4 & 0xc) == 0) {
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar4 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar4 = Pad._8_2_;
    }
    if ((uVar4 & 0x100) != 0) {
      iVar2 = *(int *)&shopMenu->field_0x3c;
      if (iVar2 == 1) {
        if (*(int *)&shopMenu->field_0x14 == 0) {
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          *(undefined4 *)&shopMenu->field_0x10 = 1;
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          *(undefined4 *)&shopMenu->field_0x10 = 0;
        }
      }
      else if ((iVar2 < 1) && (-1 < iVar2)) {
        bVar1 = false;
        *(undefined4 *)&shopMenu->field_0x10 = 0;
        iVar2 = *(int *)&shopMenu->field_0x14;
        if (iVar2 == 0) {
          PlaySe__6CSoundFiiii(&Sound,0x50,0x40,0x7f,0);
          iVar5 = *(int *)&shopMenu->field_0x14;
          iVar2 = *(int *)&shopMenu->field_0x28;
          if (iVar5 == 0) {
            iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar2 * 2 + 0xbe6);
          }
          else if (iVar5 == 1) {
            iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar2 * 2 + 0xb6);
          }
          else if (iVar5 == 2) {
            if (*(int *)(&shopMenu->field_0x50 + iVar2 * 4) == -1) {
              iVar2 = -1;
            }
            else {
              iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                      *(int *)(&shopMenu->field_0x50 + iVar2 * 4) * 2 + 0xb6);
            }
          }
          else {
            iVar2 = -1;
          }
          iVar5 = 0;
          iVar7 = iVar2 * 0x48;
          while ((iVar5 < *(int *)&shopMenu->field_0x44 &&
                 (caravanWork = *(CCaravanWork **)&shopMenu->field_0x20,
                 (ushort)caravanWork->m_inventoryItemCount + 1 < 0x41))) {
            if (*(int *)&shopMenu->field_0x14 == 0) {
              if (iVar2 < 1) {
                iVar3 = 0;
              }
              else {
                iVar3 = (int)caravanWork->m_shopParam *
                        (uint)*(ushort *)(iVar7 + Game.game.unkCFlatData0[2] + 0x20);
                iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
                iVar3 = iVar3 - (iVar3 >> 0x1f);
              }
            }
            else if (*(int *)&shopMenu->field_0x14 == 1) {
              if (iVar2 < 1) {
                iVar3 = 0;
              }
              else {
                iVar3 = (int)caravanWork->m_shopParam *
                        (uint)*(ushort *)(iVar7 + Game.game.unkCFlatData0[2] + 0x20);
                iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
                local_28 = (double)(CONCAT44(0x43300000,iVar3 - (iVar3 >> 0x1f)) ^ 0x80000000);
                iVar3 = (int)(FLOAT_80332d60 * (float)(local_28 - DOUBLE_80332d20));
              }
            }
            else {
              iVar3 = -1;
            }
            iVar3 = CanAddGil__12CCaravanWorkFi(caravanWork,-iVar3);
            if (iVar3 == 0) {
              return;
            }
            AddItem__12CCaravanWorkFiPi(*(CCaravanWork **)&shopMenu->field_0x20,(short)iVar2,0);
            if (*(int *)&shopMenu->field_0x14 == 0) {
              if (iVar2 < 1) {
                iVar3 = 0;
              }
              else {
                iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                        (uint)*(ushort *)(iVar7 + Game.game.unkCFlatData0[2] + 0x20);
                iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
                iVar3 = iVar3 - (iVar3 >> 0x1f);
              }
            }
            else if (*(int *)&shopMenu->field_0x14 == 1) {
              if (iVar2 < 1) {
                iVar3 = 0;
              }
              else {
                iVar3 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                        (uint)*(ushort *)(iVar7 + Game.game.unkCFlatData0[2] + 0x20);
                iVar3 = iVar3 / 100 + (iVar3 >> 0x1f);
                local_20 = (double)(CONCAT44(0x43300000,iVar3 - (iVar3 >> 0x1f)) ^ 0x80000000);
                iVar3 = (int)(FLOAT_80332d60 * (float)(local_20 - DOUBLE_80332d20));
              }
            }
            else {
              iVar3 = -1;
            }
            AddGil__12CCaravanWorkFi(*(CCaravanWork **)&shopMenu->field_0x20,-iVar3);
            iVar5 = iVar5 + 1;
          }
        }
        else {
          iVar5 = *(int *)&shopMenu->field_0x28;
          if (iVar5 != -1) {
            if (iVar2 == 0) {
              iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xbe6);
            }
            else if (iVar2 == 1) {
              iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xb6);
            }
            else if (iVar2 == 2) {
              if (*(int *)(&shopMenu->field_0x50 + iVar5 * 4) == -1) {
                iVar7 = -1;
              }
              else {
                iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                        *(int *)(&shopMenu->field_0x50 + iVar5 * 4) * 2 + 0xb6);
              }
            }
            else {
              iVar7 = -1;
            }
            if (iVar7 < 1) {
              bVar1 = false;
            }
            else if (iVar2 == 0) {
              bVar1 = true;
            }
            else if (iVar2 == 2) {
              bVar1 = true;
              if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar7 - 0x191U) >> 5) * 4 +
                            0xc08) & 1 << (iVar7 - 0x191U & 0x1f)) == 0) {
                bVar1 = false;
              }
            }
            else {
              cVar6 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar5);
              if (cVar6 == '\0') {
                if (iVar7 < 0x9f) {
                  bVar1 = false;
                }
                else {
                  bVar1 = true;
                }
              }
              else {
                bVar1 = false;
              }
            }
          }
          if (bVar1) {
            PlaySe__6CSoundFiiii(&Sound,0x50,0x40,0x7f,0);
            iVar5 = *(int *)&shopMenu->field_0x14;
            iVar2 = *(int *)&shopMenu->field_0x28;
            if (iVar5 == 0) {
              iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar2 * 2 + 0xbe6);
            }
            else if (iVar5 == 1) {
              iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar2 * 2 + 0xb6);
            }
            else if (iVar5 == 2) {
              if (*(int *)(&shopMenu->field_0x50 + iVar2 * 4) == -1) {
                iVar2 = -1;
              }
              else {
                iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                        *(int *)(&shopMenu->field_0x50 + iVar2 * 4) * 2 + 0xb6);
              }
            }
            else {
              iVar2 = -1;
            }
            if (iVar5 == 0) {
              if (iVar2 < 1) {
                iVar5 = 0;
              }
              else {
                iVar5 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                        (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
                iVar5 = iVar5 / 100 + (iVar5 >> 0x1f);
                iVar5 = iVar5 - (iVar5 >> 0x1f);
              }
            }
            else if (iVar5 == 1) {
              if (iVar2 < 1) {
                iVar5 = 0;
              }
              else {
                iVar5 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                        (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
                iVar5 = iVar5 / 100 + (iVar5 >> 0x1f);
                local_20 = (double)(CONCAT44(0x43300000,iVar5 - (iVar5 >> 0x1f)) ^ 0x80000000);
                iVar5 = (int)(FLOAT_80332d60 * (float)(local_20 - DOUBLE_80332d20));
              }
            }
            else {
              iVar5 = -1;
            }
            iVar5 = CanAddGil__12CCaravanWorkFi(*(CCaravanWork **)&shopMenu->field_0x20,iVar5);
            if (iVar5 != 0) {
              DeleteItemIdx__12CCaravanWorkFii
                        (*(CCaravanWork **)&shopMenu->field_0x20,
                         *(undefined4 *)&shopMenu->field_0x28,0);
              if (*(int *)&shopMenu->field_0x14 == 0) {
                if (iVar2 < 1) {
                  iVar2 = 0;
                }
                else {
                  iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                          (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
                  iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
                  iVar2 = iVar2 - (iVar2 >> 0x1f);
                }
              }
              else if (*(int *)&shopMenu->field_0x14 == 1) {
                if (iVar2 < 1) {
                  iVar2 = 0;
                }
                else {
                  iVar2 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                          (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar2 * 0x48 + 0x20);
                  iVar2 = iVar2 / 100 + (iVar2 >> 0x1f);
                  local_20 = (double)(CONCAT44(0x43300000,iVar2 - (iVar2 >> 0x1f)) ^ 0x80000000);
                  iVar2 = (int)(FLOAT_80332d60 * (float)(local_20 - DOUBLE_80332d20));
                }
              }
              else {
                iVar2 = -1;
              }
              AddGil__12CCaravanWorkFi(*(CCaravanWork **)&shopMenu->field_0x20,iVar2);
            }
          }
          else {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
      }
    }
  }
  else {
    *(uint *)&shopMenu->field_0x3c = *(uint *)&shopMenu->field_0x3c ^ 1;
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
  }
  return;
}

