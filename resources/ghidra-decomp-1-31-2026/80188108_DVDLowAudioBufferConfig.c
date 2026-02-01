// Function: DVDLowAudioBufferConfig
// Entry: 80188108
// Size: 156 bytes

undefined4 DVDLowAudioBufferConfig(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  uVar1 = 0;
  DAT_8032f018 = 0;
  if (param_1 != 0) {
    uVar1 = 0x10000;
  }
  DAT_cc006008 = param_2 | uVar1 | 0xe4000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_8032f020 = param_3;
  OSCreateAlarm(&DAT_8030c9b8);
  OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 10,AlarmHandlerForTimeout);
  return 1;
}

