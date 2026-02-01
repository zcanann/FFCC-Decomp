// Function: VISetBlack
// Entry: 8018d070
// Size: 124 bytes

void VISetBlack(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8030cc78 = param_1;
  setVerticalRegs(DAT_8030cc42,DAT_8030cc3e,*DAT_8030cc8c,*(undefined2 *)(DAT_8030cc8c + 2),
                  *(undefined2 *)(DAT_8030cc8c + 4),*(undefined2 *)(DAT_8030cc8c + 6),
                  *(undefined2 *)(DAT_8030cc8c + 8),*(undefined2 *)(DAT_8030cc8c + 10),param_1);
  OSRestoreInterrupts(uVar1);
  return;
}

