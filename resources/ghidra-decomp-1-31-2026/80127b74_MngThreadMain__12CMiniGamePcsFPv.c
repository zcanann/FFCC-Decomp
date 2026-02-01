// Function: MngThreadMain__12CMiniGamePcsFPv
// Entry: 80127b74
// Size: 2560 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MngThreadMain__12CMiniGamePcsFPv(int param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  OSAlarm OStack_128;
  undefined4 local_100;
  OSAlarm OStack_f8;
  undefined4 local_d0;
  OSAlarm OStack_c8;
  undefined4 local_a0;
  OSAlarm OStack_98;
  undefined4 local_70;
  OSAlarm OStack_68;
  undefined4 local_40;
  
  iVar9 = -0x7fde1140;
  iVar13 = 0;
  iVar12 = 0x1000;
  iVar10 = param_1;
  iVar11 = param_1;
  do {
    if (*(char *)(iVar9 + 10) == '\0') {
      uVar6 = *(undefined4 *)(param_1 + 0x1358);
      uVar8 = *(undefined4 *)(param_1 + 0x1354);
    }
    else {
      uVar6 = *(undefined4 *)(param_1 + 0x1360);
      uVar8 = *(undefined4 *)(param_1 + 0x135c);
    }
    memset(iVar10 + 0x138c,0,200);
    *(char *)(iVar10 + 0x1448) = (char)iVar13;
    *(code **)(iVar10 + 0x13b0) = _OpenCallback__FP16MgGbaThreadParamPv;
    *(undefined4 *)(iVar10 + 0x1418) = uVar8;
    *(undefined4 *)(iVar10 + 0x141c) = uVar6;
    memset(iVar11 + 0x1830,0,0x318);
    OSInitMessageQueue(iVar10 + 0x138c,iVar10 + 0x13ac,1);
    OSCreateThread(iVar11 + 0x1830,_GbaThreadMain__FPv,iVar10 + 0x138c,param_1 + iVar12 + 0x2490,
                   0x1000,7,1);
    OSResumeThread(iVar11 + 0x1830);
    iVar13 = iVar13 + 1;
    iVar10 = iVar10 + 200;
    iVar11 = iVar11 + 0x318;
    iVar12 = iVar12 + 0x1000;
    iVar9 = iVar9 + 1;
  } while (iVar13 < 4);
  uVar15 = OSGetTime();
  uVar14 = 0;
  do {
    uVar5 = DAT_800000f8 / 4000;
    OSCreateAlarm(&OStack_68);
    OSSetAlarmTag(&OStack_68,1);
    local_40 = OSGetCurrentThread();
    uVar16 = OSDisableInterrupts();
    OSSetAlarm(&OStack_68,(int)uVar16,0,uVar5,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_40);
    OSRestoreInterrupts((int)((ulonglong)uVar16 >> 0x20));
    if (*(char *)(param_1 + 0x649c) != '\0') {
      *(undefined *)(param_1 + 0x649d) = 0;
      iVar11 = 0;
      iVar10 = param_1;
      do {
        uVar14 = DAT_800000f8 / 4000;
        OSCreateAlarm(&OStack_98);
        OSSetAlarmTag(&OStack_98,1);
        local_70 = OSGetCurrentThread();
        uVar15 = OSDisableInterrupts();
        OSSetAlarm(&OStack_98,(int)uVar15,0,uVar14 * 100,
                   GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
        OSSuspendThread(local_70);
        OSRestoreInterrupts((int)((ulonglong)uVar15 >> 0x20));
        OSSendMessage(iVar10 + 0x138c,1,1);
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 200;
      } while (iVar11 < 4);
      uVar14 = DAT_800000f8 / 4000;
      OSCreateAlarm(&OStack_c8);
      OSSetAlarmTag(&OStack_c8,1);
      local_a0 = OSGetCurrentThread();
      uVar6 = OSDisableInterrupts();
      OSSetAlarm(&OStack_c8,0x80130000,0,uVar14 * 200,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
      OSSuspendThread(local_a0);
      OSRestoreInterrupts(uVar6);
      while (*(char *)(param_1 + 0x649d) != '\x0f') {
        uVar14 = DAT_800000f8 / 4000;
        OSCreateAlarm(&OStack_f8);
        OSSetAlarmTag(&OStack_f8,1);
        local_d0 = OSGetCurrentThread();
        uVar15 = OSDisableInterrupts();
        OSSetAlarm(&OStack_f8,(int)uVar15,0,uVar14 * 100,
                   GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
        OSSuspendThread(local_d0);
        OSRestoreInterrupts((int)((ulonglong)uVar15 >> 0x20));
      }
      do {
        iVar11 = 0;
        iVar10 = param_1;
        while (iVar9 = OSIsThreadTerminated(iVar10 + 0x1830), iVar9 != 0) {
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 0x318;
          if (3 < iVar11) {
            uVar14 = DAT_800000f8 / 4000;
            OSCreateAlarm(&OStack_128);
            OSSetAlarmTag(&OStack_128,1);
            local_100 = OSGetCurrentThread();
            uVar6 = OSDisableInterrupts();
            OSSetAlarm(&OStack_128,0x80130000,0,uVar14 * 100,
                       GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
            OSSuspendThread(local_100);
            OSRestoreInterrupts(uVar6);
            *(undefined *)(param_1 + 0x649c) = 0;
            OSExitThread(0);
            return;
          }
        }
      } while( true );
    }
    if (*(char *)(param_1 + 0x134b) != '\0') {
      uVar5 = 0;
      iVar9 = 0;
      iVar10 = param_1;
      iVar11 = param_1;
      do {
        uVar7 = 1 << iVar9;
        if (((*(byte *)(param_1 + 0x134b) & uVar7) != 0) && (*(char *)(iVar11 + 0x1449) == '\0')) {
          if (*(int *)(iVar11 + 0x1420) == 0x40000) {
            bVar1 = *(byte *)(iVar11 + 0x144b);
            if (bVar1 == 3) {
              *(undefined4 *)(iVar11 + 0x1420) = 0;
            }
            else if ((bVar1 < 3) && (bVar1 == 0)) {
              if (*(char *)(iVar11 + 0x1450) == '\0') {
                if (*(char *)(iVar11 + 0x1452) != '\0') goto LAB_80128174;
                *(undefined2 *)(param_1 + 0x134e) = 0;
                if (iVar9 == -1) {
                  OSSendMessage(iVar11 + 0x138c,8,1);
                }
                else {
                  OSSendMessage(iVar11 + 0x138c,7,1);
                }
              }
              else if (*(char *)(iVar11 + 0x1451) == '\0') {
                if (*(char *)(iVar11 + 0x144e) != '\0') {
                  uVar4 = *(uint *)(iVar11 + 0x142c);
                  uVar3 = 0;
                  for (uVar2 = 0x80; uVar2 != 0; uVar2 = uVar2 >> 1) {
                    uVar3 = uVar3 * 2;
                    if ((uVar4 >> 0x10 & 0xff & uVar2) == 0) {
                      if ((uVar3 & 0x100) != 0) {
                        uVar3 = uVar3 ^ 0xcd;
                      }
                    }
                    else if ((uVar3 & 0x100) == 0) {
                      uVar3 = uVar3 + 1;
                    }
                    else {
                      uVar3 = uVar3 ^ 0xcc;
                    }
                  }
                  for (uVar2 = 0x80; uVar2 != 0; uVar2 = uVar2 >> 1) {
                    uVar3 = uVar3 * 2;
                    if (((uVar4 & 0xff00) >> 8 & uVar2) == 0) {
                      if ((uVar3 & 0x100) != 0) {
                        uVar3 = uVar3 ^ 0xcd;
                      }
                    }
                    else if ((uVar3 & 0x100) == 0) {
                      uVar3 = uVar3 + 1;
                    }
                    else {
                      uVar3 = uVar3 ^ 0xcc;
                    }
                  }
                  uVar2 = 0;
                  do {
                    uVar3 = uVar3 << 1;
                    if ((uVar3 & 0x100) != 0) {
                      uVar3 = uVar3 ^ 0xcd;
                    }
                    uVar2 = uVar2 + 1;
                  } while (uVar2 < 8);
                  if ((uVar4 & 0xff) == (uVar3 & 0xff)) {
                    *(char *)(param_1 + iVar9 + 0x6490) = *(char *)(iVar11 + 0x144e);
                    uVar5 = uVar5 | uVar7 & 0xff;
                    *(uint *)(iVar10 + 0x1368) = *(uint *)(iVar11 + 0x142c) & 0xffff00;
                  }
                }
              }
              else {
                *(undefined *)(iVar11 + 0x1452) = 1;
                *(undefined *)(param_1 + iVar9 + 0x6490) = 1;
                uVar5 = uVar5 | uVar7 & 0xff;
                *(undefined4 *)(iVar10 + 0x1368) = 0;
              }
            }
            else {
              *(undefined4 *)(iVar11 + 0x1420) = 0;
            }
          }
          else if ((*(int *)(iVar11 + 0x1420) == 0) || ((uVar14 & 0x1f) == 0)) {
            uVar16 = OSGetTime();
            if (0x80000000 <
                (uint)((DAT_800000f8 / 4000) * 5000 < (uint)uVar16 - (uint)uVar15) +
                ((int)((ulonglong)uVar16 >> 0x20) -
                 ((uint)((uint)uVar16 < (uint)uVar15) + (int)((ulonglong)uVar15 >> 0x20)) ^
                0x80000000)) {
LAB_80128174:
              if ((*(byte *)(param_1 + 0x134b) & uVar7) != 0) {
                *(byte *)(param_1 + 0x134b) = *(byte *)(param_1 + 0x134b) & ~(byte)uVar7;
                if (*(char *)(param_1 + 0x134b) == '\0') {
                  *(undefined *)(param_1 + 0x6495) = 1;
                  goto LAB_801282a0;
                }
                *(undefined *)(param_1 + iVar9 + 0x6490) = 1;
                uVar7 = 0;
                *(undefined4 *)(iVar10 + 0x1368) = 0x40000000;
                *(uint *)(iVar10 + 0x1368) = *(uint *)(iVar10 + 0x1368) | 0x12000;
                for (uVar3 = 0x80; uVar3 != 0; uVar3 = uVar3 >> 1) {
                  uVar7 = uVar7 * 2;
                  if ((*(uint *)(iVar10 + 0x1368) >> 0x10 & 0xff & uVar3) == 0) {
                    if ((uVar7 & 0x100) != 0) {
                      uVar7 = uVar7 ^ 0xcd;
                    }
                  }
                  else if ((uVar7 & 0x100) == 0) {
                    uVar7 = uVar7 + 1;
                  }
                  else {
                    uVar7 = uVar7 ^ 0xcc;
                  }
                }
                for (uVar3 = 0x80; uVar3 != 0; uVar3 = uVar3 >> 1) {
                  uVar7 = uVar7 * 2;
                  if (((*(uint *)(iVar10 + 0x1368) & 0xff00) >> 8 & uVar3) == 0) {
                    if ((uVar7 & 0x100) != 0) {
                      uVar7 = uVar7 ^ 0xcd;
                    }
                  }
                  else if ((uVar7 & 0x100) == 0) {
                    uVar7 = uVar7 + 1;
                  }
                  else {
                    uVar7 = uVar7 ^ 0xcc;
                  }
                }
                uVar3 = 0;
                do {
                  uVar7 = uVar7 << 1;
                  if ((uVar7 & 0x100) != 0) {
                    uVar7 = uVar7 ^ 0xcd;
                  }
                  uVar3 = uVar3 + 1;
                } while (uVar3 < 8);
                *(uint *)(iVar10 + 0x1368) = *(uint *)(iVar10 + 0x1368) | uVar7 & 0xff;
              }
            }
            OSSendMessage(iVar11 + 0x138c,6,1);
          }
        }
LAB_801282a0:
        iVar9 = iVar9 + 1;
        iVar10 = iVar10 + 4;
        iVar11 = iVar11 + 200;
      } while (iVar9 < 4);
      if (uVar5 == (*(byte *)(param_1 + 0x134b) & 0xf)) {
        *(undefined *)(param_1 + 0x6494) = 1;
        iVar11 = 0;
        iVar10 = param_1;
        do {
          uVar7 = *(uint *)(iVar10 + 0x1368);
          if ((uVar7 & 0x8000) != 0) {
            PadCodeProc__12CMiniGamePcsFiUs
                      (param_1,iVar11,uVar7 & 0xff00 | (int)((uVar7 & 0xffff00) >> 8) >> 8);
          }
          uVar3 = 0;
          *(int *)(iVar10 + 0x1378) = (iVar11 + 0x40) * 0x1000000;
          *(uint *)(iVar10 + 0x1378) = *(uint *)(iVar10 + 0x1378) | uVar7 & 0xffff00;
          for (uVar7 = 0x80; uVar7 != 0; uVar7 = uVar7 >> 1) {
            uVar3 = uVar3 * 2;
            if ((*(uint *)(iVar10 + 0x1378) >> 0x10 & 0xff & uVar7) == 0) {
              if ((uVar3 & 0x100) != 0) {
                uVar3 = uVar3 ^ 0xcd;
              }
            }
            else if ((uVar3 & 0x100) == 0) {
              uVar3 = uVar3 + 1;
            }
            else {
              uVar3 = uVar3 ^ 0xcc;
            }
          }
          for (uVar7 = 0x80; uVar7 != 0; uVar7 = uVar7 >> 1) {
            uVar3 = uVar3 * 2;
            if (((*(uint *)(iVar10 + 0x1378) & 0xff00) >> 8 & uVar7) == 0) {
              if ((uVar3 & 0x100) != 0) {
                uVar3 = uVar3 ^ 0xcd;
              }
            }
            else if ((uVar3 & 0x100) == 0) {
              uVar3 = uVar3 + 1;
            }
            else {
              uVar3 = uVar3 ^ 0xcc;
            }
          }
          uVar7 = 0;
          do {
            uVar3 = uVar3 << 1;
            if ((uVar3 & 0x100) != 0) {
              uVar3 = uVar3 ^ 0xcd;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < 8);
          iVar11 = iVar11 + 1;
          *(uint *)(iVar10 + 0x1378) = *(uint *)(iVar10 + 0x1378) | uVar3 & 0xff;
          iVar10 = iVar10 + 4;
        } while (iVar11 < 4);
        uVar7 = 0;
        *(undefined4 *)(param_1 + 5000) = 0x44000000;
        *(uint *)(param_1 + 5000) =
             *(uint *)(param_1 + 5000) |
             ((*(ushort *)(param_1 + 0x134e) & 0xff) << 8 |
             (int)(uint)*(ushort *)(param_1 + 0x134e) >> 8) << 8;
        for (uVar3 = 0x80; uVar3 != 0; uVar3 = uVar3 >> 1) {
          uVar7 = uVar7 * 2;
          if ((*(uint *)(param_1 + 5000) >> 0x10 & 0xff & uVar3) == 0) {
            if ((uVar7 & 0x100) != 0) {
              uVar7 = uVar7 ^ 0xcd;
            }
          }
          else if ((uVar7 & 0x100) == 0) {
            uVar7 = uVar7 + 1;
          }
          else {
            uVar7 = uVar7 ^ 0xcc;
          }
        }
        for (uVar3 = 0x80; uVar3 != 0; uVar3 = uVar3 >> 1) {
          uVar7 = uVar7 * 2;
          if (((*(uint *)(param_1 + 5000) & 0xff00) >> 8 & uVar3) == 0) {
            if ((uVar7 & 0x100) != 0) {
              uVar7 = uVar7 ^ 0xcd;
            }
          }
          else if ((uVar7 & 0x100) == 0) {
            uVar7 = uVar7 + 1;
          }
          else {
            uVar7 = uVar7 ^ 0xcc;
          }
        }
        uVar3 = 0;
        do {
          uVar7 = uVar7 << 1;
          if ((uVar7 & 0x100) != 0) {
            uVar7 = uVar7 ^ 0xcd;
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 < 8);
        iVar11 = 0;
        *(uint *)(param_1 + 5000) = *(uint *)(param_1 + 5000) | uVar7 & 0xff;
        iVar10 = param_1;
        do {
          if ((uVar5 & 1 << iVar11) != 0) {
            *(undefined *)(iVar10 + 0x1451) = 0;
            memcpy((void *)(iVar10 + 0x1434),param_1 + 0x1378,0x14);
            OSSendMessage(iVar10 + 0x138c,10,1);
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 200;
        } while (iVar11 < 4);
        *(short *)(param_1 + 0x134e) = *(short *)(param_1 + 0x134e) + 1;
        if (0xffe < *(ushort *)(param_1 + 0x134e)) {
          *(undefined2 *)(param_1 + 0x134e) = 0xfff;
        }
      }
    }
    uVar14 = uVar14 + 1;
  } while( true );
}

