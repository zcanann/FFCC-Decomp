// Function: __DSP_exec_task
// Entry: 80198120
// Size: 416 bytes

void __DSP_exec_task(int param_1,int *param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
  }
  else {
    DSPSendMailToDSP(*(undefined4 *)(param_1 + 0x18));
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(*(undefined4 *)(param_1 + 0x1c));
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(*(undefined4 *)(param_1 + 0x20));
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
  }
  DSPSendMailToDSP(param_2[3]);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(param_2[4]);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(param_2[5]);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  if (*param_2 == 0) {
    DSPSendMailToDSP(*(undefined2 *)(param_2 + 9));
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(0);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
  }
  else {
    DSPSendMailToDSP(*(undefined2 *)((int)param_2 + 0x26));
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(param_2[6]);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(param_2[7]);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
    DSPSendMailToDSP(param_2[8]);
    do {
      iVar1 = DSPCheckMailToDSP();
    } while (iVar1 != 0);
  }
  return;
}

