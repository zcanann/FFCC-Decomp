// Function: GXSetChanMatColor
// Entry: 801a3974
// Size: 240 bytes

void GXSetChanMatColor(int param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 == 3) {
    iVar1 = 1;
    uVar2 = *(uint *)(DAT_80333828 + 0xb4) & 0xffffff00 | (uint)*(byte *)((int)param_2 + 3);
  }
  else if (param_1 < 3) {
    if (param_1 == 1) {
      iVar1 = 1;
      uVar2 = *(uint *)(DAT_80333828 + 0xb4) & 0xff | *param_2 & 0xffffff00;
    }
    else if (param_1 < 1) {
      if (param_1 < 0) {
        return;
      }
      iVar1 = 0;
      uVar2 = *(uint *)(DAT_80333828 + 0xb0) & 0xff | *param_2 & 0xffffff00;
    }
    else {
      iVar1 = 0;
      uVar2 = *(uint *)(DAT_80333828 + 0xb0) & 0xffffff00 | (uint)*(byte *)((int)param_2 + 3);
    }
  }
  else if (param_1 == 5) {
    uVar2 = *param_2;
    iVar1 = 1;
  }
  else {
    if (4 < param_1) {
      return;
    }
    uVar2 = *param_2;
    iVar1 = 0;
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = iVar1 + 0x100c;
  iVar1 = DAT_80333828 + iVar1 * 4;
  DAT_cc008000 = uVar2;
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  *(uint *)(iVar1 + 0xb0) = uVar2;
  return;
}

