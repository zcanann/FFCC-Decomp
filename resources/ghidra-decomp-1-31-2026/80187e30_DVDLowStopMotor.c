// Function: DVDLowStopMotor
// Entry: 80187e30
// Size: 140 bytes

undefined4 DVDLowStopMotor(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_8032f018 = 0;
  DAT_cc006008 = 0xe3000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_8032f020 = param_1;
  OSCreateAlarm(&DAT_8030c9b8);
  OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 10,AlarmHandlerForTimeout);
  return 1;
}

