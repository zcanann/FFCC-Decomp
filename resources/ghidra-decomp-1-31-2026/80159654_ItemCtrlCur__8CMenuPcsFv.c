// Function: ItemCtrlCur__8CMenuPcsFv
// Entry: 80159654
// Size: 1952 bytes

/* WARNING: Removing unreachable block (ram,0x801597f8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 ItemCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint32_t caravanWork;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined2 local_28;
  undefined2 local_26 [7];
  
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
  if (uVar4 != 0) {
    iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
    sVar5 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
    if (iVar7 == 0) {
      if ((uVar4 & 8) == 0) {
        if ((uVar4 & 4) != 0) {
          iVar7 = *(int *)&menuPcs->field_0x82c;
          if (*(short *)(iVar7 + 0x26) < 7) {
            *(short *)(iVar7 + 0x26) = *(short *)(iVar7 + 0x26) + 1;
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
          else {
            sVar1 = *(short *)(iVar7 + 0x34);
            if (0x3e < sVar1) {
              if (0x3e < sVar1) {
                *(undefined2 *)(iVar7 + 0x34) = 0;
                PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
              }
              else {
                *(short *)(iVar7 + 0x34) = sVar1 + 1;
                PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
              }
            }
            else {
              *(short *)(iVar7 + 0x34) = sVar1 + 1;
              PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
            }
          }
        }
      }
      else {
        iVar7 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar7 + 0x26) == 0) {
          if (*(short *)(iVar7 + 0x34) == 0) {
            *(undefined2 *)(iVar7 + 0x34) = 0x3f;
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
          else {
            *(short *)(iVar7 + 0x34) = *(short *)(iVar7 + 0x34) + -1;
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
        }
        else {
          *(short *)(iVar7 + 0x26) = *(short *)(iVar7 + 0x26) + -1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      if ((uVar4 & 0xc) == 0) {
        if ((uVar3 & 0x20) == 0) {
          if ((uVar3 & 0x40) == 0) {
            if ((uVar3 & 0x100) == 0) {
              if ((uVar3 & 0x200) != 0) {
                if (-1 < sVar5) {
                  LetterSetAttachItem__8CMenuPcsFUii(menuPcs,0,0xffffffff);
                  PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
                  return 1;
                }
                *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
                PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
                return 1;
              }
            }
            else {
              iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34) +
                      (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
              if (0x3f < iVar7) {
                iVar7 = iVar7 + -0x40;
              }
              iVar8 = caravanWork + iVar7 * 2;
              if (((*(short *)(iVar8 + 0xb6) < 1) ||
                  (cVar6 = EquipChk__8CMenuPcsFi(menuPcs,iVar7), cVar6 != '\0')) ||
                 ((-1 < sVar5 && (*(short *)(iVar8 + 0xb6) < 0x125)))) {
                PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
              }
              else {
                if (-1 < sVar5) {
                  LetterSetAttachItem__8CMenuPcsFUii(menuPcs,iVar7,1);
                  PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                  return 1;
                }
                *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0xc;
                iVar7 = GetItemType__8CMenuPcsFii(menuPcs,iVar7,0);
                if ((iVar7 == 7) &&
                   (iVar8 = CanPlayerUseItem__12CCaravanWorkFv((CCaravanWork *)caravanWork),
                   iVar8 != 0)) {
                  *(byte *)(*(int *)&menuPcs->field_0x82c + 9) =
                       *(byte *)(*(int *)&menuPcs->field_0x82c + 9) | 1;
                }
                if ((iVar7 != 1) &&
                   (iVar7 = CanPlayerPutItem__12CCaravanWorkFv((CCaravanWork *)caravanWork),
                   iVar7 != 0)) {
                  *(byte *)(*(int *)&menuPcs->field_0x82c + 9) =
                       *(byte *)(*(int *)&menuPcs->field_0x82c + 9) | 2;
                }
                GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,0,local_26,&local_28,0);
                SetSingWinInfo__8CMenuPcsFiiii(menuPcs,0xf0,0xa0,local_26[0],local_28);
                *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
                *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
                *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
                PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
              }
            }
          }
          else {
            if (sVar5 < 0) {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
              PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
              return 1;
            }
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
        else {
          if (sVar5 < 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
            return 1;
          }
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
      }
    }
    else {
      if ((uVar4 & 8) == 0) {
        if ((uVar4 & 4) != 0) {
          iVar8 = *(int *)&menuPcs->field_0x82c + iVar7 * 2;
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
        iVar8 = *(int *)&menuPcs->field_0x82c + iVar7 * 2;
        if (*(short *)(iVar8 + 0x26) == 0) {
          *(undefined2 *)(iVar8 + 0x26) = 3;
        }
        else {
          *(short *)(iVar8 + 0x26) = *(short *)(iVar8 + 0x26) + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar4 & 0xc) == 0) {
        if ((uVar3 & 0x100) == 0) {
          if ((uVar3 & 0x200) != 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
        else {
          iVar8 = *(int *)&menuPcs->field_0x82c;
          iVar7 = (int)*(short *)(iVar8 + iVar7 * 2 + 0x26);
          if (((int)*(char *)(iVar8 + 9) & 1 << iVar7) == 0) {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
          else {
            iVar8 = (int)*(short *)(iVar8 + 0x34) + (int)*(short *)(iVar8 + 0x26);
            if (0x3f < iVar8) {
              iVar8 = iVar8 + -0x40;
            }
            if (iVar7 == 0) {
              FGUseItem__12CCaravanWorkFii((CCaravanWork *)caravanWork,iVar8,0);
              SingLifeInit__8CMenuPcsFi(menuPcs,0);
              CalcStatus__12CCaravanWorkFv(caravanWork);
            }
            else if (iVar7 == 1) {
              FGPutItem__12CCaravanWorkFii((CCaravanWork *)caravanWork,iVar8,0);
            }
            else if (iVar7 == 2) {
              DeleteItemIdx__12CCaravanWorkFii((CCaravanWork *)caravanWork,iVar8,0);
            }
            *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
        }
      }
    }
    return 0;
  }
  return 0;
}

