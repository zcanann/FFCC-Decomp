// Function: GXSetIndTexOrder
// Entry: 801a4ebc
// Size: 276 bytes

void GXSetIndTexOrder(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = DAT_80333828;
  if (param_1 == 2) {
    *(uint *)(DAT_80333828 + 0x120) = *(uint *)(DAT_80333828 + 0x120) & 0xffff8fff | param_3 << 0xc;
    *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) & 0xfffc7fff | param_2 << 0xf;
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      puVar2 = (uint *)(DAT_80333828 + 0x120);
      *puVar2 = *(uint *)(DAT_80333828 + 0x120) & 0xfffffff8 | param_3;
      *puVar2 = *puVar2 & 0xffffffc7 | param_2 << 3;
    }
    else if (-1 < param_1) {
      *(uint *)(DAT_80333828 + 0x120) = *(uint *)(DAT_80333828 + 0x120) & 0xfffffe3f | param_3 << 6;
      *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) & 0xfffff1ff | param_2 << 9;
    }
  }
  else if (param_1 < 4) {
    *(uint *)(DAT_80333828 + 0x120) = *(uint *)(DAT_80333828 + 0x120) & 0xffe3ffff | param_3 << 0x12
    ;
    *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) & 0xff1fffff | param_2 << 0x15;
  }
  iVar1 = DAT_80333828;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x120);
  *(uint *)(DAT_80333828 + 0x4f4) = *(uint *)(DAT_80333828 + 0x4f4) | 3;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

