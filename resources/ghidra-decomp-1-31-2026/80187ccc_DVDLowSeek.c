// Function: DVDLowSeek
// Entry: 80187ccc
// Size: 148 bytes

undefined4 DVDLowSeek(uint param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_8032f018 = 0;
  DAT_cc006008 = 0xab000000;
  DAT_cc00600c = param_1 >> 2;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_8032f020 = param_2;
  OSCreateAlarm(&DAT_8030c9b8);
  OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 10,AlarmHandlerForTimeout);
  return 1;
}

