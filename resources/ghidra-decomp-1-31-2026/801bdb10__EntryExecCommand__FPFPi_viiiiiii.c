// Function: _EntryExecCommand__FPFPi_viiiiiii
// Entry: 801bdb10
// Size: 192 bytes

undefined4 *
_EntryExecCommand__FPFPi_viiiiiii
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = OSDisableInterrupts();
  *DAT_8032f3d8 = param_1;
  DAT_8032f3d8[1] = param_2;
  DAT_8032f3d8[2] = param_3;
  DAT_8032f3d8[3] = param_4;
  DAT_8032f3d8[4] = param_5;
  DAT_8032f3d8[5] = param_6;
  DAT_8032f3d8[6] = param_7;
  DAT_8032f3d8[7] = param_8;
  puVar2 = DAT_8032f3d8 + 8;
  if (DAT_8032f3d8 + 8 == DAT_8032f3d4 + 0x800) {
    puVar2 = DAT_8032f3d4;
  }
  DAT_8032f3d8 = puVar2;
  OSRestoreInterrupts(uVar1);
  return puVar2;
}

