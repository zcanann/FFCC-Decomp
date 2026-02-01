// Function: OSExceptionVector
// Entry: 8017bff8
// Size: 88 bytes

void OSExceptionVector(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint in_MSR;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined4 in_SRR0;
  uint in_SRR1;
  
  iVar1 = iRam000000c0;
  *(undefined4 *)(iRam000000c0 + 0xc) = param_1;
  *(undefined4 *)(iVar1 + 0x10) = param_2;
  *(undefined4 *)(iVar1 + 0x14) = param_3;
  *(ushort *)(iVar1 + 0x1a2) = *(ushort *)(iVar1 + 0x1a2) | 2;
  *(uint *)(iVar1 + 0x80) =
       (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
       (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
       (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  *(undefined4 *)(iVar1 + 0x84) = in_LR;
  *(undefined4 *)(iVar1 + 0x88) = in_CTR;
  *(undefined4 *)(iVar1 + 0x8c) = in_XER;
  *(undefined4 *)(iVar1 + 0x198) = in_SRR0;
  *(uint *)(iVar1 + 0x19c) = in_SRR1;
  if ((in_SRR1 & 2) == 0) {
    returnFromInterrupt(in_MSR,in_MSR | 0x30);
    return;
  }
  returnFromInterrupt(in_MSR,in_MSR | 0x30);
  return;
}

