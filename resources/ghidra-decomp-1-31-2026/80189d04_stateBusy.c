// Function: stateBusy
// Entry: 80189d04
// Size: 800 bytes

void stateBusy(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  uint uVar3;
  code *pcVar4;
  
  puVar2 = DAT_8032f080;
  DAT_8032f0c4 = stateBusy;
  switch(*(undefined4 *)(param_1 + 8)) {
  default:
    (*DAT_8032eae8)(param_1,cbForStateBusy);
    break;
  case 1:
  case 4:
    if (*(int *)(param_1 + 0x14) == 0) {
      DAT_8032f080 = &DAT_8030ca60;
      *(undefined4 *)(puVar2 + 0xc) = 0;
      pcVar4 = *(code **)(puVar2 + 0x28);
      if (pcVar4 != (code *)0x0) {
        (*pcVar4)(0);
      }
      stateReady();
    }
    else {
      uVar1 = DAT_cc006004;
      DAT_cc006004 = uVar1;
      uVar3 = *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x20);
      if (0x80000 < uVar3) {
        uVar3 = 0x80000;
      }
      *(uint *)(param_1 + 0x1c) = uVar3;
      DVDLowRead(*(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x1c)
                 ,*(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x20),cbForStateBusy);
    }
    break;
  case 2:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowSeek(*(undefined4 *)(param_1 + 0x10),cbForStateBusy);
    break;
  case 3:
    DVDLowStopMotor(cbForStateBusy);
    break;
  case 5:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    *(undefined4 *)(param_1 + 0x1c) = 0x20;
    DVDLowReadDiskID(*(undefined4 *)(param_1 + 0x18),cbForStateBusy);
    break;
  case 6:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    if (DAT_8032f094 == 0) {
      *(undefined4 *)(DAT_8032f080 + 0x1c) = 1;
      DVDLowAudioStream(0,*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10),
                        cbForStateBusy);
    }
    else {
      *(undefined4 *)(DAT_8032f080 + 0x1c) = 0;
      DVDLowRequestAudioStatus(0,cbForStateBusy);
    }
    break;
  case 7:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowAudioStream(0x10000,0,0,cbForStateBusy);
    break;
  case 8:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DAT_8032f094 = 1;
    DVDLowAudioStream(0,0,0,cbForStateBusy);
    break;
  case 9:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowRequestAudioStatus(0,cbForStateBusy);
    break;
  case 10:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowRequestAudioStatus(0x10000,cbForStateBusy);
    break;
  case 0xb:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowRequestAudioStatus(0x20000,cbForStateBusy);
    break;
  case 0xc:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowRequestAudioStatus(0x30000,cbForStateBusy);
    break;
  case 0xd:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DVDLowAudioBufferConfig
              (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),cbForStateBusy);
    break;
  case 0xe:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    *(undefined4 *)(param_1 + 0x1c) = 0x20;
    DVDLowInquiry(*(undefined4 *)(param_1 + 0x18),cbForStateBusy);
    break;
  case 0xf:
    DVDLowStopMotor(cbForStateBusy);
  }
  return;
}

