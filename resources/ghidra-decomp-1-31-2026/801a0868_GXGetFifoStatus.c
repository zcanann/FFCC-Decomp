// Function: GXGetFifoStatus
// Entry: 801a0868
// Size: 272 bytes

void GXGetFifoStatus(int param_1,undefined *param_2,undefined *param_3,undefined4 *param_4,
                    undefined *param_5,undefined *param_6,byte *param_7)

{
  uint uVar1;
  
  *param_3 = 0;
  *param_2 = 0;
  *param_4 = 0;
  *param_7 = 0;
  if (param_1 == DAT_8032f314) {
    *(int *)(param_1 + 0x14) =
         CONCAT22(*(undefined2 *)(DAT_8032f2ec + 0x3a),*(undefined2 *)(DAT_8032f2ec + 0x38)) +
         -0x80000000;
    *(uint *)(param_1 + 0x1c) =
         CONCAT22(*(undefined2 *)(DAT_8032f2ec + 0x32),*(undefined2 *)(DAT_8032f2ec + 0x30));
  }
  if (param_1 == DAT_8032f310) {
    __GXSaveCPUFifoAux(param_1);
    *param_7 = (byte)((uint)*(undefined4 *)(DAT_8032f2e8 + 0x14) >> 0x1a) & 1;
  }
  *param_2 = *(uint *)(param_1 + 0xc) < *(uint *)(param_1 + 0x1c);
  *param_3 = *(uint *)(param_1 + 0x1c) < *(uint *)(param_1 + 0x10);
  *param_4 = *(undefined4 *)(param_1 + 0x1c);
  uVar1 = countLeadingZeros(param_1 - DAT_8032f310);
  *param_5 = (char)(uVar1 >> 5);
  uVar1 = countLeadingZeros(param_1 - DAT_8032f314);
  *param_6 = (char)(uVar1 >> 5);
  return;
}

