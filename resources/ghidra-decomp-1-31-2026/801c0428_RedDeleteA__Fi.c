// Function: RedDeleteA__Fi
// Entry: 801c0428
// Size: 216 bytes

void RedDeleteA__Fi(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int *dstBuffer;
  
  if (param_1 != 0) {
    uVar2 = OSDisableInterrupts();
    dstBuffer = DAT_8032f4a4;
    if (DAT_8032f4a4 != (int *)0x0) {
      while( true ) {
        if ((dstBuffer[1] == 0) || (DAT_8032f4a4 + 0x800 <= dstBuffer)) goto LAB_801c04d8;
        if (*dstBuffer == param_1) break;
        dstBuffer = dstBuffer + 2;
      }
      uVar1 = (int)DAT_8032f4a4 + (0x2000 - (int)(dstBuffer + 2));
      iVar3 = ((int)uVar1 >> 3) + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
      if (0 < iVar3) {
        memcpy(dstBuffer,dstBuffer + 2,iVar3 * 8);
        memset(DAT_8032f4a4 + 0x7fe,0,8);
      }
    }
LAB_801c04d8:
    OSRestoreInterrupts(uVar2);
  }
  return;
}

