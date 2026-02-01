// Function: GXEndDisplayList
// Entry: 801a60c0
// Size: 212 bytes

undefined4 GXEndDisplayList(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)((int)DAT_80333828 + 0x4f4) != 0) {
    __GXSetDirtyState();
  }
  uVar1 = *(uint *)(DAT_8032f2e8 + 0x14);
  __GXSaveCPUFifoAux(&DAT_80327cf8);
  GXSetCPUFifo(DAT_8032f348);
  if (*(char *)((int)DAT_80333828 + 0x4f1) != '\0') {
    uVar2 = OSDisableInterrupts();
    uVar3 = *(undefined4 *)((int)DAT_80333828 + 8);
    memcpy(DAT_80333828,&DAT_80327d1c,0x4f8);
    *(undefined4 *)((int)DAT_80333828 + 8) = uVar3;
    OSRestoreInterrupts(uVar2);
  }
  *(undefined *)((int)DAT_80333828 + 0x4f0) = 0;
  uVar2 = DAT_80327d14;
  if ((uVar1 >> 0x1a & 1) != 0) {
    uVar2 = 0;
  }
  return uVar2;
}

