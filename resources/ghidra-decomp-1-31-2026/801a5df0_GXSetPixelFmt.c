// Function: GXSetPixelFmt
// Entry: 801a5df0
// Size: 232 bytes

void GXSetPixelFmt(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_80333828;
  uVar3 = *(uint *)(DAT_80333828 + 0x1dc);
  *(uint *)(DAT_80333828 + 0x1dc) = uVar3 & 0xfffffff8 | *(uint *)(&DAT_8021c9d0 + param_1 * 4);
  *(uint *)(iVar1 + 0x1dc) = *(uint *)(iVar1 + 0x1dc) & 0xffffffc7 | param_2 << 3;
  iVar2 = DAT_80333828;
  if (uVar3 != *(uint *)(iVar1 + 0x1dc)) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(iVar1 + 0x1dc);
    *(uint *)(DAT_80333828 + 0x204) =
         *(uint *)(DAT_80333828 + 0x204) & 0xfffffdff | (uint)(param_1 == 2) << 9;
    *(uint *)(iVar2 + 0x4f4) = *(uint *)(iVar2 + 0x4f4) | 4;
  }
  iVar1 = DAT_80333828;
  if (*(uint *)(&DAT_8021c9d0 + param_1 * 4) == 4) {
    *(uint *)(DAT_80333828 + 0x1d4) =
         (param_1 + -4) * 0x200 & 0x600U | *(uint *)(DAT_80333828 + 0x1d4) & 0xfffff9ff;
    *(uint *)(iVar1 + 0x1d4) = *(uint *)(iVar1 + 0x1d4) & 0xffffff | 0x42000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 0x1d4);
  }
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

