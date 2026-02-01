// Function: GXBeginDisplayList
// Entry: 801a5ff8
// Size: 200 bytes

void GXBeginDisplayList(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = GXGetCPUFifo();
  if (*(int *)(DAT_80333828 + 0x4f4) != 0) {
    __GXSetDirtyState();
  }
  if (*(char *)(DAT_80333828 + 0x4f1) != '\0') {
    memcpy(&DAT_80327d1c,DAT_80333828,0x4f8);
  }
  DAT_80327cfc = param_1 + param_2 + -4;
  DAT_80327d14 = 0;
  DAT_80327cf8 = param_1;
  DAT_80327d00 = param_2;
  DAT_80327d0c = param_1;
  DAT_80327d10 = param_1;
  *(undefined *)(DAT_80333828 + 0x4f0) = 1;
  GXSaveCPUFifo(uVar1);
  DAT_8032f348 = uVar1;
  GXSetCPUFifo(&DAT_80327cf8);
  return;
}

