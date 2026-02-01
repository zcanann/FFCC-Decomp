// Function: OSSwitchFPUContext
// Entry: 8017dc9c
// Size: 132 bytes

undefined8 OSSwitchFPUContext(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int extraout_r4;
  uint uVar3;
  uint in_MSR;
  uint uVar4;
  
  uVar4 = in_MSR & 0x9000;
  instructionSynchronize();
  uVar3 = *(uint *)(param_2 + 0x19c) | 0x2000;
  iVar2 = param_2;
  if (DAT_800000d8 != param_2) {
    bVar1 = DAT_800000d8 != 0;
    DAT_800000d8 = param_2;
    if (bVar1) {
      __OSSaveFPUContext();
    }
    __OSLoadFPUContext();
    param_2 = extraout_r4;
    iVar2 = DAT_800000d8;
  }
  DAT_800000d8 = iVar2;
  *(ushort *)(param_2 + 0x1a2) = *(ushort *)(param_2 + 0x1a2) & 0xfffd;
  returnFromInterrupt(uVar4,uVar3);
  return *(undefined8 *)(param_2 + 0xc);
}

