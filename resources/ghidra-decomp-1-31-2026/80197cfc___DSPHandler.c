// Function: __DSPHandler
// Entry: 80197cfc
// Size: 1060 bytes

void __DSPHandler(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined auStack_2d8 [724];
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xffd7 | 0x80;
  OSClearContext(auStack_2d8);
  OSSetCurrentContext(auStack_2d8);
  do {
    iVar2 = DSPCheckMailFromDSP();
  } while (iVar2 == 0);
  iVar2 = DSPReadMailFromDSP();
  if (((DAT_8032f2dc[2] & 2) != 0) && (iVar2 == -0x232efffe)) {
    iVar2 = -0x232efffd;
  }
  if (iVar2 == -0x232efffe) {
    if (DAT_8032f2c8 == 0) {
      if (DAT_8032f2dc[0xe] == 0) {
        if (DAT_8032f2dc == DAT_8032f2d8) {
          DSPSendMailToDSP(0xcdd10003);
          do {
            iVar2 = DSPCheckMailToDSP();
          } while (iVar2 != 0);
          if ((code *)DAT_8032f2dc[0xb] != (code *)0x0) {
            (*(code *)DAT_8032f2dc[0xb])();
          }
        }
        else {
          DSPSendMailToDSP(0xcdd10001);
          do {
            iVar2 = DSPCheckMailToDSP();
          } while (iVar2 != 0);
          __DSP_exec_task(DAT_8032f2dc,DAT_8032f2d8);
          *DAT_8032f2dc = 2;
          DAT_8032f2dc = DAT_8032f2d8;
        }
      }
      else {
        DSPSendMailToDSP(0xcdd10001);
        do {
          iVar2 = DSPCheckMailToDSP();
        } while (iVar2 != 0);
        __DSP_exec_task(DAT_8032f2dc,DAT_8032f2dc[0xe]);
        *DAT_8032f2dc = 2;
        DAT_8032f2dc = (undefined4 *)DAT_8032f2dc[0xe];
      }
    }
    else if (DAT_8032f2dc == DAT_8032f2cc) {
      DSPSendMailToDSP(0xcdd10003);
      do {
        iVar2 = DSPCheckMailToDSP();
      } while (iVar2 != 0);
      DAT_8032f2cc = (undefined4 *)0x0;
      DAT_8032f2c8 = 0;
      if ((code *)DAT_8032f2dc[0xb] != (code *)0x0) {
        (*(code *)DAT_8032f2dc[0xb])();
      }
    }
    else {
      DSPSendMailToDSP(0xcdd10001);
      do {
        iVar2 = DSPCheckMailToDSP();
      } while (iVar2 != 0);
      __DSP_exec_task(DAT_8032f2dc,DAT_8032f2cc);
      *DAT_8032f2dc = 2;
      DAT_8032f2c8 = 0;
      DAT_8032f2dc = DAT_8032f2cc;
      DAT_8032f2cc = (undefined4 *)0x0;
    }
  }
  else if (iVar2 < -0x232efffe) {
    if (iVar2 == -0x232f0000) {
      *DAT_8032f2dc = 1;
      if ((code *)DAT_8032f2dc[10] != (code *)0x0) {
        (*(code *)DAT_8032f2dc[10])();
      }
    }
    else if (-0x232f0001 < iVar2) {
      *DAT_8032f2dc = 1;
      if ((code *)DAT_8032f2dc[0xb] != (code *)0x0) {
        (*(code *)DAT_8032f2dc[0xb])();
      }
    }
  }
  else if (iVar2 == -0x232efffc) {
    if ((code *)DAT_8032f2dc[0xd] != (code *)0x0) {
      (*(code *)DAT_8032f2dc[0xd])(DAT_8032f2dc);
    }
  }
  else if (iVar2 < -0x232efffc) {
    if (DAT_8032f2c8 == 0) {
      if (DAT_8032f2dc[0xe] == 0) {
        if (DAT_8032f2dc == DAT_8032f2d8) {
          if ((code *)DAT_8032f2dc[0xc] != (code *)0x0) {
            (*(code *)DAT_8032f2dc[0xc])(DAT_8032f2dc);
          }
          DSPSendMailToDSP(0xcdd10002);
          do {
            iVar2 = DSPCheckMailToDSP();
          } while (iVar2 != 0);
          *DAT_8032f2dc = 3;
          __DSP_remove_task(DAT_8032f2dc);
        }
        else {
          if ((code *)DAT_8032f2dc[0xc] != (code *)0x0) {
            (*(code *)DAT_8032f2dc[0xc])(DAT_8032f2dc);
          }
          DSPSendMailToDSP(0xcdd10001);
          do {
            iVar2 = DSPCheckMailToDSP();
          } while (iVar2 != 0);
          *DAT_8032f2dc = 3;
          __DSP_exec_task(0,DAT_8032f2d8);
          DAT_8032f2dc = DAT_8032f2d8;
          __DSP_remove_task(DAT_8032f2d4);
        }
      }
      else {
        if ((code *)DAT_8032f2dc[0xc] != (code *)0x0) {
          (*(code *)DAT_8032f2dc[0xc])(DAT_8032f2dc);
        }
        DSPSendMailToDSP(0xcdd10001);
        do {
          iVar2 = DSPCheckMailToDSP();
        } while (iVar2 != 0);
        *DAT_8032f2dc = 3;
        __DSP_exec_task(0,DAT_8032f2dc[0xe]);
        DAT_8032f2dc = (undefined4 *)DAT_8032f2dc[0xe];
        __DSP_remove_task(DAT_8032f2dc[0xf]);
      }
    }
    else {
      if ((code *)DAT_8032f2dc[0xc] != (code *)0x0) {
        (*(code *)DAT_8032f2dc[0xc])(DAT_8032f2dc);
      }
      DSPSendMailToDSP(0xcdd10001);
      do {
        iVar2 = DSPCheckMailToDSP();
      } while (iVar2 != 0);
      __DSP_exec_task(0,DAT_8032f2cc);
      __DSP_remove_task(DAT_8032f2dc);
      DAT_8032f2c8 = 0;
      DAT_8032f2dc = DAT_8032f2cc;
      DAT_8032f2cc = (undefined4 *)0x0;
    }
  }
  OSClearContext(auStack_2d8);
  OSSetCurrentContext(param_2);
  return;
}

