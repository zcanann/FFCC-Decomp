// Function: __AXOutNewFrame
// Entry: 801926b4
// Size: 392 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __AXOutNewFrame(undefined4 param_1)

{
  undefined1 *puVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  undefined1 *puVar6;
  undefined8 uVar7;
  
  _DAT_803148b0 = OSGetTime();
  __AXSyncPBs(param_1);
  __AXPrintStudio();
  uVar3 = __AXGetCommandListAddress();
  DSPSendMailToDSP(0xbabe0180);
  do {
    iVar4 = DSPCheckMailToDSP();
  } while (iVar4 != 0);
  DSPSendMailToDSP(uVar3);
  do {
    iVar4 = DSPCheckMailToDSP();
  } while (iVar4 != 0);
  __AXServiceCallbackStack();
  _DAT_803148b8 = OSGetTime();
  __AXProcessAux();
  uVar7 = OSGetTime();
  DAT_803148c0 = (undefined4)((ulonglong)uVar7 >> 0x20);
  DAT_803148c4 = (undefined4)uVar7;
  uVar7 = OSGetTime();
  DAT_803148c8 = (undefined4)((ulonglong)uVar7 >> 0x20);
  DAT_803148cc = (undefined4)uVar7;
  if (DAT_8032f250 != (code *)0x0) {
    (*DAT_8032f250)();
    uVar7 = CONCAT44(DAT_803148c8,DAT_803148cc);
  }
  DAT_803148c8 = (undefined4)((ulonglong)uVar7 >> 0x20);
  DAT_803148cc = (undefined4)uVar7;
  uVar7 = OSGetTime();
  DAT_803148d0 = (undefined4)((ulonglong)uVar7 >> 0x20);
  DAT_803148d4 = (undefined4)uVar7;
  __AXNextFrame(&DAT_803105e0,&DAT_803100e0 + DAT_8032f240 * 0xa0);
  DAT_8032f240 = DAT_8032f240 + 1 & 1;
  AIInitDMA(&DAT_803100e0 + DAT_8032f240 * 0xa0,0x280);
  uVar7 = OSGetTime();
  DAT_803148d8 = (undefined4)((ulonglong)uVar7 >> 0x20);
  DAT_803148dc = (undefined4)uVar7;
  DAT_803148e0 = __AXGetNumVoices();
  puVar5 = (undefined *)__AXGetCurrentProfile();
  uVar7 = _DAT_803148b8;
  uVar2 = _DAT_803148b0;
  if (puVar5 != (undefined *)0x0) {
    iVar4 = 7;
    puVar6 = &DAT_803148b0;
    do {
      *puVar5 = *puVar6;
      puVar5[1] = puVar6[1];
      puVar5[2] = puVar6[2];
      puVar5[3] = puVar6[3];
      puVar5[4] = puVar6[4];
      puVar5[5] = puVar6[5];
      puVar5[6] = puVar6[6];
      puVar1 = puVar6 + 7;
      puVar6 = puVar6 + 8;
      puVar5[7] = *puVar1;
      puVar5 = puVar5 + 8;
      iVar4 = iVar4 + -1;
      uVar7 = _DAT_803148b8;
      uVar2 = _DAT_803148b0;
    } while (iVar4 != 0);
  }
  _DAT_803148b0 = (undefined4)((ulonglong)uVar2 >> 0x20);
  _DAT_803148b4 = (undefined4)uVar2;
  _DAT_803148b8 = (undefined4)((ulonglong)uVar7 >> 0x20);
  _DAT_803148bc = (undefined4)uVar7;
  return;
}

