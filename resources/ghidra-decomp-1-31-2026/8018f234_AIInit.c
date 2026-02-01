// Function: AIInit
// Entry: 8018f234
// Size: 364 bytes

void AIInit(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_8032f170 != 1) {
    OSRegisterVersion(DAT_8032eb38);
    uVar1 = DAT_800000f8 / 500000;
    DAT_8032f17c = (uVar1 * 0x7b24) / 8000;
    DAT_8032f184 = (uVar1 * 0xa428) / 8000;
    DAT_8032f18c = (uVar1 * 42000) / 8000;
    DAT_8032f194 = (uVar1 * 63000) / 8000;
    DAT_8032f19c = (uVar1 * 3000) / 8000;
    uVar1 = DAT_cc006c00;
    DAT_8032f178 = 0;
    DAT_8032f180 = 0;
    DAT_8032f188 = 0;
    DAT_8032f190 = 0;
    DAT_8032f198 = 0;
    uVar2 = DAT_cc006c04;
    DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
    DAT_cc006c04 = uVar2 & 0xffff00ff;
    uVar1 = DAT_cc006c04;
    DAT_cc006c04 = uVar1 & 0xffffff00;
    DAT_cc006c0c = 0;
    __AI_set_stream_sample_rate(1);
    AISetDSPSampleRate(0);
    DAT_8032f160 = 0;
    DAT_8032f164 = 0;
    DAT_8032f168 = param_1;
    __OSSetInterruptHandler(5,__AIDHandler);
    __OSUnmaskInterrupts(0x4000000);
    __OSSetInterruptHandler(8,__AISHandler);
    __OSUnmaskInterrupts(0x800000);
    DAT_8032f170 = 1;
  }
  return;
}

