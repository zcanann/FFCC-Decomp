// Function: GXSetCPUFifo
// Entry: 801a04e4
// Size: 272 bytes

void GXSetCPUFifo(uint *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8032f310 = param_1;
  if (param_1 == DAT_8032f314) {
    *(uint *)(DAT_8032f2e8 + 0xc) = *param_1 & 0x3fffffff;
    *(uint *)(DAT_8032f2e8 + 0x10) = param_1[1] & 0x3fffffff;
    *(uint *)(DAT_8032f2e8 + 0x14) = param_1[6] & 0x3bffffe0;
    DAT_8032f31c = '\x01';
    __GXWriteFifoIntReset(1,1);
    __GXWriteFifoIntEnable(1,0);
    __GXFifoLink(1);
  }
  else {
    if (DAT_8032f31c != '\0') {
      __GXFifoLink(0);
      DAT_8032f31c = '\0';
    }
    __GXWriteFifoIntEnable(0,0);
    *(uint *)(DAT_8032f2e8 + 0xc) = *param_1 & 0x3fffffff;
    *(uint *)(DAT_8032f2e8 + 0x10) = param_1[1] & 0x3fffffff;
    *(uint *)(DAT_8032f2e8 + 0x14) = param_1[6] & 0x3bffffe0;
  }
  PPCSync();
  OSRestoreInterrupts(uVar1);
  return;
}

