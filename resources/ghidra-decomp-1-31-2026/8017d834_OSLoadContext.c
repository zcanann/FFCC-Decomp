// Function: OSLoadContext
// Entry: 8017d834
// Size: 216 bytes

undefined8 OSLoadContext(int param_1)

{
  uint in_MSR;
  
  if ((OSDisableInterrupts < *(code **)(param_1 + 0x198)) &&
     (*(code **)(param_1 + 0x198) < (code *)0x8017e34c)) {
    *(code **)(param_1 + 0x198) = OSDisableInterrupts;
  }
  if ((*(ushort *)(param_1 + 0x1a2) & 2) != 0) {
    *(ushort *)(param_1 + 0x1a2) = *(ushort *)(param_1 + 0x1a2) & 0xfffd;
  }
  returnFromInterrupt(in_MSR & 0x9000,*(undefined4 *)(param_1 + 0x19c));
  return *(undefined8 *)(param_1 + 0xc);
}

