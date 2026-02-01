// Function: AISetStreamPlayState
// Entry: 8018ef1c
// Size: 216 bytes

void AISetStreamPlayState(uint param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar1 = AIGetStreamPlayState();
  if (param_1 != uVar1) {
    iVar2 = AIGetStreamSampleRate();
    if ((iVar2 == 0) && (param_1 == 1)) {
      uVar3 = AIGetStreamVolRight();
      uVar4 = AIGetStreamVolLeft();
      AISetStreamVolRight(0);
      AISetStreamVolLeft(0);
      uVar5 = OSDisableInterrupts();
      __AI_SRC_INIT();
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xfffffffe | 1;
      OSRestoreInterrupts(uVar5);
      AISetStreamVolLeft(uVar3);
      AISetStreamVolRight(uVar4);
    }
    else {
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xfffffffe | param_1;
    }
  }
  return;
}

