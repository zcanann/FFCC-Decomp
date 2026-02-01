// Function: AXFXChorusSettings
// Entry: 80196104
// Size: 196 bytes

undefined4 AXFXChorusSettings(int param_1)

{
  OSDisableInterrupts();
  *(int *)(param_1 + 0x5c) = (*(int *)(param_1 + 0x90) + -5) * -0x20 + 0x140;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(uint *)(param_1 + 0x5c) =
       (*(int *)(param_1 + 0x5c) + (*(byte *)(param_1 + 0x24) - 1) * 0xa0) % 0x1e0;
  *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x98) / 5 + 1 & 0xfffffffe;
  *(uint *)(param_1 + 100) = *(uint *)(param_1 + 0x68) >> 1;
  *(uint *)(param_1 + 0x60) =
       (uint)(*(int *)(param_1 + 0x94) << 0x10) / (uint)(*(int *)(param_1 + 0x68) * 5);
  OSRestoreInterrupts();
  return 1;
}

