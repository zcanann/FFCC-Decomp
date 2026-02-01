// Function: VIGetCurrentLine
// Entry: 8018d15c
// Size: 152 bytes

uint VIGetCurrentLine(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = DAT_8032f120;
  OSDisableInterrupts();
  uVar2 = DAT_cc00202c;
  uVar6 = uVar2 & 0x7ff;
  do {
    uVar2 = DAT_cc00202c;
    uVar3 = DAT_cc00202e;
    uVar5 = uVar2 & 0x7ff;
    bVar1 = uVar6 != uVar5;
    uVar6 = uVar5;
  } while (bVar1);
  uVar6 = (uVar5 - 1) * 2 + ((uVar3 & 0x7ff) - 1) / (uint)*(ushort *)(DAT_8032f120 + 0x1a);
  OSRestoreInterrupts();
  if (*(ushort *)(iVar4 + 0x18) <= uVar6) {
    uVar6 = uVar6 - *(ushort *)(iVar4 + 0x18);
  }
  return uVar6 >> 1;
}

