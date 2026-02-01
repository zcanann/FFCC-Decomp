// Function: AISetDSPSampleRate
// Entry: 8018f004
// Size: 224 bytes

void AISetDSPSampleRate(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar3 = AIGetDSPSampleRate();
  if ((param_1 != iVar3) && (uVar1 = DAT_cc006c00, DAT_cc006c00 = uVar1 & 0xffffffbf, param_1 == 0))
  {
    uVar4 = AIGetStreamVolLeft();
    uVar5 = AIGetStreamVolRight();
    uVar1 = DAT_cc006c00;
    iVar3 = AIGetStreamSampleRate();
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    uVar6 = OSDisableInterrupts();
    __AI_SRC_INIT();
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xffffffdf | 0x20;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffd | iVar3 << 1;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffe | uVar1 & 1;
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 | 0x40;
    OSRestoreInterrupts(uVar6);
    AISetStreamVolLeft(uVar4);
    AISetStreamVolRight(uVar5);
  }
  return;
}

