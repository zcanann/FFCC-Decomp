// Function: __THPReadScaneHeader
// Entry: 801cdcb8
// Size: 284 bytes

undefined4 __THPReadScaneHeader(void)

{
  byte bVar1;
  char *pcVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte bVar7;
  
  *(int *)(DAT_8032f5f0 + 0x69c) = *(int *)(DAT_8032f5f0 + 0x69c) + 2;
  pcVar2 = *(char **)(DAT_8032f5f0 + 0x69c);
  *(char **)(DAT_8032f5f0 + 0x69c) = pcVar2 + 1;
  if (*pcVar2 != '\x03') {
    return 0xc;
  }
  bVar7 = 0;
  iVar6 = 0;
  while( true ) {
    if (2 < bVar7) {
      *(int *)(DAT_8032f5f0 + 0x69c) = *(int *)(DAT_8032f5f0 + 0x69c) + 3;
      *(short *)(DAT_8032f5f0 + 0x696) =
           (short)((int)(*(ushort *)(DAT_8032f5f0 + 0x692) + 0xf) >> 4);
      *(undefined2 *)(DAT_8032f5f0 + 0x684) = 0;
      *(undefined2 *)(DAT_8032f5f0 + 0x68a) = 0;
      *(undefined2 *)(DAT_8032f5f0 + 0x690) = 0;
      return 0;
    }
    *(int *)(DAT_8032f5f0 + 0x69c) = *(int *)(DAT_8032f5f0 + 0x69c) + 1;
    pbVar3 = *(byte **)(DAT_8032f5f0 + 0x69c);
    *(byte **)(DAT_8032f5f0 + 0x69c) = pbVar3 + 1;
    bVar1 = *pbVar3;
    iVar4 = (int)(uint)bVar1 >> 4;
    *(char *)(DAT_8032f5f0 + iVar6 + 0x681) = (char)iVar4;
    uVar5 = bVar1 & 0xf;
    *(char *)(DAT_8032f5f0 + iVar6 + 0x682) = (char)uVar5;
    if (((uint)*(byte *)(DAT_8032f5f0 + 0x6a8) & 1 << iVar4) == 0) break;
    if (((uint)*(byte *)(DAT_8032f5f0 + 0x6a8) & 1 << uVar5 + 1) == 0) {
      return 0xf;
    }
    iVar6 = iVar6 + 6;
    bVar7 = bVar7 + 1;
  }
  return 0xf;
}

