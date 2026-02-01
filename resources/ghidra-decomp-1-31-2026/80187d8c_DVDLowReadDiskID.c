// Function: DVDLowReadDiskID
// Entry: 80187d8c
// Size: 164 bytes

undefined4 DVDLowReadDiskID(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_8032f018 = 0;
  DAT_cc006008 = 0xa8000040;
  DAT_cc00600c = 0;
  DAT_cc006010 = 0x20;
  DAT_cc006014 = param_1;
  DAT_cc006018 = 0x20;
  DAT_cc00601c = 3;
  uVar1 = DAT_800000f8 >> 2;
  DAT_8032f020 = param_2;
  OSCreateAlarm(&DAT_8030c9b8);
  OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 10,AlarmHandlerForTimeout);
  return 1;
}

