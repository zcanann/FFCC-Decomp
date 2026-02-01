// Function: cbForStateMotorStopped
// Entry: 801899f0
// Size: 228 bytes

void cbForStateMotorStopped(void)

{
  undefined *puVar1;
  
  DAT_cc006004 = 0;
  *(undefined4 *)(DAT_8032f080 + 0xc) = 3;
  if (DAT_8032f09c == 0xd) {
LAB_80189a50:
    __DVDClearWaitingQueue();
    puVar1 = DAT_8032f080;
    DAT_8032f080 = &DAT_8030ca60;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xfffffffc);
    }
    stateReady();
  }
  else {
    if (DAT_8032f09c < 0xd) {
      if ((DAT_8032f09c < 6) && (3 < DAT_8032f09c)) goto LAB_80189a50;
    }
    else if (DAT_8032f09c == 0xf) goto LAB_80189a50;
    DVDReset();
    OSCreateAlarm(&DAT_8030ca90);
    OSSetAlarm((OSAlarm *)&DAT_8030ca90,0x10624dd3,0,(DAT_800000f8 / 4000) * 0x47e,AlarmHandler);
  }
  return;
}

