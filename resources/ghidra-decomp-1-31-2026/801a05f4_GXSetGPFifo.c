// Function: GXSetGPFifo
// Entry: 801a05f4
// Size: 376 bytes

void GXSetGPFifo(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  __GXFifoReadDisable();
  __GXWriteFifoIntEnable(0,0);
  DAT_8032f314 = param_1;
  *(short *)(DAT_8032f2ec + 0x20) = (short)*param_1;
  *(short *)(DAT_8032f2ec + 0x24) = (short)param_1[1];
  *(short *)(DAT_8032f2ec + 0x30) = (short)param_1[7];
  *(short *)(DAT_8032f2ec + 0x34) = (short)param_1[6];
  *(short *)(DAT_8032f2ec + 0x38) = (short)param_1[5];
  *(short *)(DAT_8032f2ec + 0x28) = (short)param_1[3];
  *(short *)(DAT_8032f2ec + 0x2c) = (short)param_1[4];
  *(ushort *)(DAT_8032f2ec + 0x22) = (ushort)((uint)*param_1 >> 0x10) & 0x3fff;
  *(ushort *)(DAT_8032f2ec + 0x26) = (ushort)((uint)param_1[1] >> 0x10) & 0x3fff;
  *(short *)(DAT_8032f2ec + 0x32) = (short)((uint)param_1[7] >> 0x10);
  *(ushort *)(DAT_8032f2ec + 0x36) = (ushort)((uint)param_1[6] >> 0x10) & 0x3fff;
  *(ushort *)(DAT_8032f2ec + 0x3a) = (ushort)((uint)param_1[5] >> 0x10) & 0x3fff;
  *(short *)(DAT_8032f2ec + 0x2a) = (short)((uint)param_1[3] >> 0x10);
  *(short *)(DAT_8032f2ec + 0x2e) = (short)((uint)param_1[4] >> 0x10);
  PPCSync();
  if (DAT_8032f310 == DAT_8032f314) {
    DAT_8032f31c = 1;
    __GXWriteFifoIntEnable(1,0);
    __GXFifoLink(1);
  }
  else {
    DAT_8032f31c = 0;
    __GXWriteFifoIntEnable(0,0);
    __GXFifoLink(0);
  }
  __GXWriteFifoIntReset(1,1);
  __GXFifoReadEnable();
  OSRestoreInterrupts(uVar1);
  return;
}

