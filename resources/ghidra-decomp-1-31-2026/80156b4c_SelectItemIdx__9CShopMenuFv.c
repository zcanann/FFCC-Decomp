// Function: SelectItemIdx__9CShopMenuFv
// Entry: 80156b4c
// Size: 3168 bytes

/* WARNING: Removing unreachable block (ram,0x801574f8) */
/* WARNING: Removing unreachable block (ram,0x801570a4) */
/* WARNING: Removing unreachable block (ram,0x801570c0) */
/* WARNING: Removing unreachable block (ram,0x801570f8) */
/* WARNING: Removing unreachable block (ram,0x801570ac) */
/* WARNING: Removing unreachable block (ram,0x801570c8) */
/* WARNING: Removing unreachable block (ram,0x801570e4) */
/* WARNING: Removing unreachable block (ram,0x801570dc) */
/* WARNING: Removing unreachable block (ram,0x80157410) */
/* WARNING: Removing unreachable block (ram,0x8015738c) */
/* WARNING: Removing unreachable block (ram,0x80157514) */
/* WARNING: Removing unreachable block (ram,0x80157560) */
/* WARNING: Removing unreachable block (ram,0x801573c4) */
/* WARNING: Removing unreachable block (ram,0x801573e0) */
/* WARNING: Removing unreachable block (ram,0x801573d8) */
/* WARNING: Removing unreachable block (ram,0x801573bc) */
/* WARNING: Removing unreachable block (ram,0x801573f4) */
/* WARNING: Removing unreachable block (ram,0x80157420) */
/* WARNING: Removing unreachable block (ram,0x80157450) */
/* WARNING: Removing unreachable block (ram,0x8015744c) */
/* WARNING: Removing unreachable block (ram,0x8015757c) */
/* WARNING: Removing unreachable block (ram,0x80157124) */
/* WARNING: Removing unreachable block (ram,0x80157154) */
/* WARNING: Removing unreachable block (ram,0x80157150) */
/* WARNING: Removing unreachable block (ram,0x8015711c) */
/* WARNING: Removing unreachable block (ram,0x8015715c) */
/* WARNING: Removing unreachable block (ram,0x80157178) */
/* WARNING: Removing unreachable block (ram,0x80157188) */
/* WARNING: Removing unreachable block (ram,0x80157180) */
/* WARNING: Removing unreachable block (ram,0x80157170) */
/* WARNING: Removing unreachable block (ram,0x801575c4) */
/* WARNING: Removing unreachable block (ram,0x801575e0) */
/* WARNING: Removing unreachable block (ram,0x801575f0) */
/* WARNING: Removing unreachable block (ram,0x801575e8) */
/* WARNING: Removing unreachable block (ram,0x801575d8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SelectItemIdx__9CShopMenuFv(CShopMenu *shopMenu)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  CCaravanWork *caravanWork;
  char cVar6;
  undefined4 uVar5;
  int iVar7;
  
  *(undefined4 *)&shopMenu->field_0x44 = 1;
  iVar7 = *(int *)&shopMenu->field_0x14;
  if (iVar7 == 0) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
  }
  else if (iVar7 == 1) {
    iVar4 = 0x40;
  }
  else if (iVar7 == 2) {
    iVar4 = *(int *)&shopMenu->field_0x4c;
  }
  else {
    iVar4 = -1;
  }
  if (iVar4 <= *(int *)&shopMenu->field_0x28) {
    if (iVar7 == 0) {
      iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
    }
    else if (iVar7 == 1) {
      iVar7 = 0x40;
    }
    else if (iVar7 == 2) {
      iVar7 = *(int *)&shopMenu->field_0x4c;
    }
    else {
      iVar7 = -1;
    }
    *(int *)&shopMenu->field_0x28 = iVar7 + -1;
  }
  if (DAT_8032eed0 == 0) {
    bVar2 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar2 = true;
    }
    if (bVar2) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._20_2_;
    }
  }
  else {
    bVar2 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar2 = true;
    }
    if (bVar2) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._4_2_;
    }
    if ((uVar3 & DAT_8032eed0) == 0) {
      DAT_8032eed0 = 0;
    }
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
  }
  if ((uVar3 & 8) == 0) {
    if (DAT_8032eed0 == 0) {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._20_2_;
      }
    }
    else {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._4_2_;
      }
      if ((uVar3 & DAT_8032eed0) == 0) {
        DAT_8032eed0 = 0;
      }
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
    }
    if ((uVar3 & 4) == 0) {
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
      if ((uVar3 & 0x100) != 0) {
        bVar2 = false;
        *(undefined4 *)&shopMenu->field_0x38 = 0;
        *(undefined4 *)&shopMenu->field_0x3c = 0;
        iVar7 = *(int *)&shopMenu->field_0x14;
        if (iVar7 == 0) {
          if (*(int *)&shopMenu->field_0x28 != -1) {
            if (*(short *)(*(int *)&shopMenu->field_0x20 + *(int *)&shopMenu->field_0x28 * 2 + 0xbe6
                          ) < 1) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
          }
          if (bVar2) {
            caravanWork = *(CCaravanWork **)&shopMenu->field_0x20;
            if (*(int *)&shopMenu->field_0x44 <=
                (int)(0x40 - (uint)(ushort)caravanWork->m_inventoryItemCount)) {
              iVar7 = *(int *)&shopMenu->field_0x28;
              if (iVar7 == -1) {
                iVar7 = 0;
              }
              else {
                iVar4 = *(int *)&shopMenu->field_0x14;
                if (iVar4 == 0) {
                  iVar7 = (int)caravanWork->m_shopList[iVar7];
                }
                else if (iVar4 == 1) {
                  iVar7 = (int)(short)caravanWork->m_inventoryItems[iVar7];
                }
                else if (iVar4 == 2) {
                  if (*(int *)(&shopMenu->field_0x50 + iVar7 * 4) == -1) {
                    iVar7 = -1;
                  }
                  else {
                    iVar7 = (int)(short)caravanWork->m_inventoryItems
                                        [*(int *)(&shopMenu->field_0x50 + iVar7 * 4)];
                  }
                }
                else {
                  iVar7 = -1;
                }
                if (iVar4 == 0) {
                  if (iVar7 < 1) {
                    iVar7 = 0;
                  }
                  else {
                    iVar7 = (int)caravanWork->m_shopParam *
                            (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar7 * 0x48 + 0x20);
                    iVar7 = iVar7 / 100 + (iVar7 >> 0x1f);
                    iVar7 = iVar7 - (iVar7 >> 0x1f);
                  }
                }
                else if (iVar4 == 1) {
                  if (iVar7 < 1) {
                    iVar7 = 0;
                  }
                  else {
                    iVar7 = (int)caravanWork->m_shopParam *
                            (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar7 * 0x48 + 0x20);
                    iVar7 = iVar7 / 100 + (iVar7 >> 0x1f);
                    iVar7 = (int)(FLOAT_80332d60 *
                                 (float)((double)CONCAT44(0x43300000,
                                                          iVar7 - (iVar7 >> 0x1f) ^ 0x80000000) -
                                        DOUBLE_80332d20));
                  }
                }
                else {
                  iVar7 = -1;
                }
                iVar7 = *(int *)&shopMenu->field_0x44 * iVar7;
              }
              iVar7 = CanAddGil__12CCaravanWorkFi(caravanWork,-iVar7);
              if (iVar7 != 0) {
                *(undefined4 *)&shopMenu->field_0x10 = 1;
                PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                goto LAB_801576d8;
              }
            }
          }
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
        else if (iVar7 == 1) {
          iVar7 = *(int *)&shopMenu->field_0x28;
          if (iVar7 != -1) {
            sVar1 = *(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xb6);
            if (sVar1 < 1) {
              bVar2 = false;
            }
            else {
              cVar6 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar7);
              if (cVar6 == '\0') {
                if (sVar1 < 0x9f) {
                  bVar2 = false;
                }
                else {
                  bVar2 = true;
                }
              }
              else {
                bVar2 = false;
              }
            }
          }
          if (bVar2) {
            *(undefined4 *)&shopMenu->field_0x10 = 2;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
        else if (iVar7 == 2) {
          if (*(int *)&shopMenu->field_0x28 != -1) {
            if (*(int *)(&shopMenu->field_0x50 + *(int *)&shopMenu->field_0x28 * 4) == -1) {
              iVar7 = -1;
            }
            else {
              iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                      *(int *)(&shopMenu->field_0x50 +
                                              *(int *)&shopMenu->field_0x28 * 4) * 2 + 0xb6);
            }
            if (iVar7 < 1) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
              if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar7 - 0x191U) >> 5) * 4 +
                            0xc08) & 1 << (iVar7 - 0x191U & 0x1f)) == 0) {
                bVar2 = false;
              }
            }
          }
          if (bVar2) {
            *(undefined4 *)&shopMenu->field_0x8 = 0xc;
            iVar4 = *(int *)&shopMenu->field_0x14;
            iVar7 = *(int *)&shopMenu->field_0x28;
            if (iVar4 == 0) {
              iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xbe6);
            }
            else if (iVar4 == 1) {
              iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xb6);
            }
            else if (iVar4 == 2) {
              if (*(int *)(&shopMenu->field_0x50 + iVar7 * 4) == -1) {
                iVar7 = -1;
              }
              else {
                iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                        *(int *)(&shopMenu->field_0x50 + iVar7 * 4) * 2 + 0xb6);
              }
            }
            else {
              iVar7 = -1;
            }
            uVar5 = GetSmithItem__8CMenuPcsFi(&MenuPcs,iVar7);
            *(undefined4 *)&shopMenu->field_0x150 = uVar5;
            SetMode__9CShopMenuFi(shopMenu,0xb);
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
      }
    }
    else {
      *(int *)&shopMenu->field_0x28 = *(int *)&shopMenu->field_0x28 + 1;
      iVar7 = *(int *)&shopMenu->field_0x14;
      if (iVar7 == 0) {
        iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
      }
      else if (iVar7 == 1) {
        iVar7 = 0x40;
      }
      else if (iVar7 == 2) {
        iVar7 = *(int *)&shopMenu->field_0x4c;
      }
      else {
        iVar7 = -1;
      }
      if (*(int *)&shopMenu->field_0x28 < iVar7) {
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      else {
        DAT_8032eed0 = 4;
        iVar7 = *(int *)&shopMenu->field_0x14;
        if (iVar7 == 0) {
          iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
        }
        else if (iVar7 == 1) {
          iVar7 = 0x40;
        }
        else if (iVar7 == 2) {
          iVar7 = *(int *)&shopMenu->field_0x4c;
        }
        else {
          iVar7 = -1;
        }
        *(int *)&shopMenu->field_0x28 = iVar7 + -1;
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
    }
  }
  else {
    *(int *)&shopMenu->field_0x28 = *(int *)&shopMenu->field_0x28 + -1;
    if (*(int *)&shopMenu->field_0x28 < 0) {
      DAT_8032eed0 = 8;
      *(undefined4 *)&shopMenu->field_0x28 = 0;
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
    else {
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
  }
LAB_801576d8:
  if (*(int *)&shopMenu->field_0x28 < *(int *)&shopMenu->field_0x24) {
    *(int *)&shopMenu->field_0x24 = *(int *)&shopMenu->field_0x28;
  }
  if (*(int *)&shopMenu->field_0x24 + *(int *)&shopMenu->field_0x2c <= *(int *)&shopMenu->field_0x28
     ) {
    *(int *)&shopMenu->field_0x24 =
         (*(int *)&shopMenu->field_0x28 - *(int *)&shopMenu->field_0x2c) + 1;
  }
  if (*(int *)&shopMenu->field_0x24 < 1) {
    *(undefined4 *)&shopMenu->field_0x30 = 0;
  }
  else {
    *(undefined4 *)&shopMenu->field_0x30 = 1;
  }
  iVar7 = *(int *)&shopMenu->field_0x14;
  if (iVar7 == 0) {
    iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
  }
  else if (iVar7 == 1) {
    iVar7 = 0x40;
  }
  else if (iVar7 == 2) {
    iVar7 = *(int *)&shopMenu->field_0x4c;
  }
  else {
    iVar7 = -1;
  }
  if (*(int *)&shopMenu->field_0x24 + *(int *)&shopMenu->field_0x2c < iVar7) {
    *(undefined4 *)&shopMenu->field_0x34 = 1;
  }
  else {
    *(undefined4 *)&shopMenu->field_0x34 = 0;
  }
  return;
}

