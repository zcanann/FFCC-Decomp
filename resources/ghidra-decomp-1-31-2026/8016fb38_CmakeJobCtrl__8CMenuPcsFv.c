// Function: CmakeJobCtrl__8CMenuPcsFv
// Entry: 8016fb38
// Size: 1156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CmakeJobCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  short local_18;
  short local_16 [5];
  
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._8_2_;
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
    uVar5 = Pad._20_2_;
  }
  if (uVar5 != 0) {
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
    if (sVar1 == 3) {
      if ((uVar5 & 8) == 0) {
        if ((uVar5 & 4) != 0) {
          iVar7 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar7 + 0x26);
          iVar6 = (int)sVar1 >> 0x1f;
          if ((int)((iVar6 * 4 | (uint)(sVar1 * 0x40000000 + iVar6) >> 0x1e) - iVar6) < 3) {
            *(short *)(iVar7 + 0x26) = sVar1 + 1;
          }
          else {
            *(short *)(iVar7 + 0x26) = sVar1 + -3;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        iVar6 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar6 + 0x26);
        uVar3 = (int)sVar1 >> 0x1f;
        if ((uVar3 * 4 | sVar1 * 0x40000000 + uVar3 >> 0x1e) == uVar3) {
          *(short *)(iVar6 + 0x26) = sVar1 + 3;
        }
        else {
          *(short *)(iVar6 + 0x26) = sVar1 + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar5 & 3) != 0) {
        iVar6 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar6 + 0x26);
        if (sVar1 < 4) {
          *(short *)(iVar6 + 0x26) = sVar1 + 4;
        }
        else {
          *(short *)(iVar6 + 0x26) = sVar1 + -4;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar5 & 0xf) == 0) {
        if ((uVar4 & 0x100) != 0) {
          iVar6 = -0x7fde1140;
          iVar7 = 0;
          iVar9 = 2;
          do {
            if (((((((iVar7 != *(short *)&menuPcs->field_0x86a) && (*(int *)(iVar6 + 0x1794) != 0))
                   && (*(char *)(iVar6 + 0x1f96) != '\x01')) &&
                  (iVar8 = iVar7,
                  *(int *)(iVar6 + 0x179c) == (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))
                  ) || (((iVar7 + 1 != (int)*(short *)&menuPcs->field_0x86a &&
                         (*(int *)(iVar6 + 0x23c4) != 0)) &&
                        ((*(char *)(iVar6 + 0x2bc6) != '\x01' &&
                         (iVar8 = iVar7 + 1,
                         *(int *)(iVar6 + 0x23cc) ==
                         (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))))))) ||
                (((iVar7 + 2 != (int)*(short *)&menuPcs->field_0x86a &&
                  (*(int *)(iVar6 + 0x2ff4) != 0)) &&
                 ((*(char *)(iVar6 + 0x37f6) != '\x01' &&
                  (iVar8 = iVar7 + 2,
                  *(int *)(iVar6 + 0x2ffc) == (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))
                  ))))) ||
               ((((iVar7 + 3 != (int)*(short *)&menuPcs->field_0x86a &&
                  (*(int *)(iVar6 + 0x3c24) != 0)) && (*(char *)(iVar6 + 0x4426) != '\x01')) &&
                (iVar8 = iVar7 + 3,
                *(int *)(iVar6 + 0x3c2c) == (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))))
               ) break;
            iVar6 = iVar6 + 0x30c0;
            iVar7 = iVar7 + 4;
            iVar9 = iVar9 + -1;
            iVar8 = iVar7;
          } while (iVar9 != 0);
          if (7 < iVar8) {
            s_CmakeInfo._21_1_ = (undefined)*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26);
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            return 1;
          }
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          GetWinSize__8CMenuPcsFiPsPsi(menuPcs,0x16,local_16,&local_18,0);
          SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_16[0],(int)local_18);
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
          return 0;
        }
        if ((uVar4 & 0x200) != 0) {
          ChgModel__8CMenuPcsFiiii
                    (menuPcs,(int)*(short *)&menuPcs->field_0x86a,0xffffffff,0xffffffff,0xffffffff);
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          return 1;
        }
      }
    }
    else if ((sVar1 == 1) && ((uVar4 & 0x300) != 0)) {
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
    }
  }
  return 0;
}

