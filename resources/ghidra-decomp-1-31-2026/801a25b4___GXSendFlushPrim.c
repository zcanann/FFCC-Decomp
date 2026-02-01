// Function: __GXSendFlushPrim
// Entry: 801a25b4
// Size: 136 bytes

void __GXSendFlushPrim(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = (uint)*(ushort *)(DAT_80333828 + 4) * (uint)*(ushort *)(DAT_80333828 + 6);
  DAT_cc008000._0_1_ = 0x98;
  DAT_cc008000._0_2_ = *(ushort *)(DAT_80333828 + 4);
  uVar1 = iVar3 + 3;
  uVar2 = uVar1 >> 2;
  if (iVar3 != 0) {
    uVar1 = uVar1 >> 5;
    if (uVar1 != 0) {
      do {
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
      uVar2 = uVar2 & 7;
      if (uVar2 == 0) goto LAB_801a262c;
    }
    do {
      DAT_cc008000 = 0;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
LAB_801a262c:
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

