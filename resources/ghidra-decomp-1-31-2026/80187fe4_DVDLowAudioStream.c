// Function: DVDLowAudioStream
// Entry: 80187fe4
// Size: 152 bytes

undefined4 DVDLowAudioStream(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_8032f018 = 0;
  DAT_cc006008 = param_1 | 0xe1000000;
  DAT_cc00600c = param_3 >> 2;
  DAT_cc006010 = param_2;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_8032f020 = param_4;
  OSCreateAlarm(&DAT_8030c9b8);
  OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 10,AlarmHandlerForTimeout);
  return 1;
}

