// Function: __AI_set_stream_sample_rate
// Entry: 8018f0f8
// Size: 212 bytes

void __AI_set_stream_sample_rate(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  iVar4 = AIGetStreamSampleRate();
  if (param_1 != iVar4) {
    uVar1 = DAT_cc006c00;
    uVar5 = AIGetStreamVolLeft();
    uVar6 = AIGetStreamVolRight();
    AISetStreamVolRight(0);
    AISetStreamVolLeft(0);
    uVar2 = DAT_cc006c00;
    uVar3 = DAT_cc006c00;
    DAT_cc006c00 = uVar3 & 0xffffffbf;
    uVar7 = OSDisableInterrupts();
    __AI_SRC_INIT();
    uVar3 = DAT_cc006c00;
    DAT_cc006c00 = uVar3 | uVar2 & 0x40;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xffffffdf | 0x20;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffd | param_1 << 1;
    OSRestoreInterrupts(uVar7);
    AISetStreamPlayState(uVar1 & 1);
    AISetStreamVolLeft(uVar5);
    AISetStreamVolRight(uVar6);
  }
  return;
}

