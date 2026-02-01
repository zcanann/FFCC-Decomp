// Function: CmakeTribeCtrl__8CMenuPcsFv
// Entry: 801708b0
// Size: 1080 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CmakeTribeCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short local_18;
  short local_16 [3];
  
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
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
    if (sVar1 == 3) {
      iVar5 = *(int *)&menuPcs->field_0x82c;
      iVar7 = (int)*(short *)(iVar5 + 0x30);
      if ((uVar4 & 8) == 0) {
        if ((uVar4 & 4) != 0) {
          iVar5 = iVar5 + iVar7 * 2;
          if (*(short *)(iVar5 + 0x26) < 3) {
            *(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + 1;
          }
          else {
            *(undefined2 *)(iVar5 + 0x26) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        iVar5 = iVar5 + iVar7 * 2;
        if (*(short *)(iVar5 + 0x26) == 0) {
          *(undefined2 *)(iVar5 + 0x26) = 3;
        }
        else {
          *(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar4 & 0xc) == 0) {
        if ((uVar3 & 0x100) == 0) {
          if ((uVar3 & 0x200) != 0) {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            if (iVar7 == 0) {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
              return 1;
            }
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x30) =
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x30) + -1;
          }
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          if (iVar7 != 0) {
            iVar5 = -0x7fde1140;
            iVar7 = 0;
            iVar8 = 4;
            do {
              if (((((*(int *)(iVar5 + 0x1794) != 0) && (*(char *)(iVar5 + 0x1f96) != '\x01')) &&
                   ((uint)*(ushort *)(iVar5 + 0x17d0) ==
                    (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) &&
                  (((uint)*(ushort *)(iVar5 + 0x17d4) ==
                    (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28) &&
                   (iVar6 = iVar7,
                   (uint)*(ushort *)(iVar5 + 0x17d2) == (int)(char)s_CmakeInfo._18_1_)))) ||
                 ((((*(int *)(iVar5 + 0x23c4) != 0 &&
                    ((*(char *)(iVar5 + 0x2bc6) != '\x01' &&
                     ((uint)*(ushort *)(iVar5 + 0x2400) ==
                      (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26))))) &&
                   ((uint)*(ushort *)(iVar5 + 0x2404) ==
                    (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28))) &&
                  (iVar6 = iVar7 + 1,
                  (uint)*(ushort *)(iVar5 + 0x2402) == (int)(char)s_CmakeInfo._18_1_)))) break;
              iVar5 = iVar5 + 0x1860;
              iVar7 = iVar7 + 2;
              iVar8 = iVar8 + -1;
              iVar6 = iVar7;
            } while (iVar8 != 0);
            if (7 < iVar6) {
              s_CmakeInfo._19_1_ = (undefined)*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26);
              s_CmakeInfo._20_1_ = (undefined)*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28);
              ChgModel__8CMenuPcsFiiii
                        (menuPcs,(int)*(short *)&menuPcs->field_0x86a,(int)(char)s_CmakeInfo._19_1_,
                         (int)(char)s_CmakeInfo._20_1_,(int)(char)s_CmakeInfo._18_1_);
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
              return 1;
            }
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
            GetWinSize__8CMenuPcsFiPsPsi(menuPcs,0x15,local_16,&local_18,0);
            SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_16[0],(int)local_18);
            *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
            return 0;
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x30) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x30) + 1;
        }
      }
    }
    else if ((sVar1 == 1) && ((uVar3 & 0x300) != 0)) {
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
    }
  }
  return 0;
}

