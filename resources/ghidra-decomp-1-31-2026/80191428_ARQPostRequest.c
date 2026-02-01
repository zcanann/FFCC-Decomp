// Function: ARQPostRequest
// Entry: 80191428
// Size: 348 bytes

void ARQPostRequest(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4,
                   undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  
  *param_1 = 0;
  param_1[1] = param_2;
  param_1[2] = param_3;
  param_1[4] = param_5;
  param_1[5] = param_6;
  param_1[6] = param_7;
  if (param_8 == 0) {
    param_1[7] = __ARQCallbackHack;
  }
  else {
    param_1[7] = param_8;
  }
  uVar5 = OSDisableInterrupts();
  puVar3 = DAT_8032f1c8;
  puVar4 = DAT_8032f1cc;
  if (param_4 == 1) {
    puVar1 = param_1;
    puVar2 = param_1;
    if (DAT_8032f1c0 != (undefined4 *)0x0) {
      *DAT_8032f1c4 = param_1;
      puVar1 = DAT_8032f1c0;
      puVar2 = param_1;
      puVar3 = DAT_8032f1c8;
      puVar4 = DAT_8032f1cc;
    }
  }
  else {
    puVar1 = DAT_8032f1c0;
    puVar2 = DAT_8032f1c4;
    if (((param_4 < 1) && (-1 < param_4)) &&
       (puVar3 = param_1, puVar4 = param_1, DAT_8032f1c8 != (undefined4 *)0x0)) {
      *DAT_8032f1cc = param_1;
      puVar1 = DAT_8032f1c0;
      puVar2 = DAT_8032f1c4;
      puVar3 = DAT_8032f1c8;
      puVar4 = param_1;
    }
  }
  DAT_8032f1cc = puVar4;
  DAT_8032f1c8 = puVar3;
  DAT_8032f1c4 = puVar2;
  DAT_8032f1c0 = puVar1;
  if ((DAT_8032f1d0 == (undefined4 *)0x0) && (DAT_8032f1d4 == 0)) {
    if (DAT_8032f1c0 != (undefined4 *)0x0) {
      if (DAT_8032f1c0[2] == 0) {
        ARStartDMA(0,DAT_8032f1c0[4],DAT_8032f1c0[5],DAT_8032f1c0[6]);
      }
      else {
        ARStartDMA(DAT_8032f1c0[2],DAT_8032f1c0[5],DAT_8032f1c0[4],DAT_8032f1c0[6]);
      }
      DAT_8032f1d8 = DAT_8032f1c0[7];
      DAT_8032f1d0 = DAT_8032f1c0;
      DAT_8032f1c0 = (undefined4 *)*DAT_8032f1c0;
    }
    if (DAT_8032f1d0 == (undefined4 *)0x0) {
      __ARQServiceQueueLo();
    }
  }
  OSRestoreInterrupts(uVar5);
  return;
}

