// Function: Read
// Entry: 801878a4
// Size: 272 bytes

void Read(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar2;
  
  DAT_8032f018 = 0;
  DAT_8032f058 = 1;
  DAT_8032f020 = param_4;
  uVar2 = __OSGetSystemTime();
  DAT_8032f050 = (undefined4)((ulonglong)uVar2 >> 0x20);
  DAT_8032f054 = (undefined4)uVar2;
  DAT_cc006008 = 0xa8000000;
  DAT_cc00600c = param_3 >> 2;
  DAT_cc006010 = param_2;
  DAT_cc006014 = param_1;
  DAT_cc006018 = param_2;
  DAT_cc00601c = 3;
  DAT_8032f01c = param_2;
  if (param_2 < 0xa00001) {
    uVar1 = DAT_800000f8 >> 2;
    OSCreateAlarm(&DAT_8030c9b8);
    OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4_00,0,uVar1 * 10,AlarmHandlerForTimeout);
  }
  else {
    uVar1 = DAT_800000f8 >> 2;
    OSCreateAlarm(&DAT_8030c9b8);
    OSSetAlarm((OSAlarm *)&DAT_8030c9b8,extraout_r4,0,uVar1 * 0x14,AlarmHandlerForTimeout);
  }
  return;
}

