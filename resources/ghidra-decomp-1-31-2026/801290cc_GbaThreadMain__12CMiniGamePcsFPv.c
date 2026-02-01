// Function: GbaThreadMain__12CMiniGamePcsFPv
// Entry: 801290cc
// Size: 5380 bytes

/* WARNING: Removing unreachable block (ram,0x8012a368) */

void GbaThreadMain__12CMiniGamePcsFPv(int param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined uVar9;
  int iVar7;
  int iVar8;
  undefined4 *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined auStack_254 [4];
  int local_250 [2];
  OSAlarm OStack_248;
  undefined4 local_220;
  OSAlarm OStack_218;
  undefined4 local_1f0;
  OSAlarm OStack_1e8;
  undefined4 local_1c0;
  OSAlarm OStack_1b8;
  undefined4 local_190;
  OSAlarm OStack_188;
  undefined4 local_160;
  OSAlarm OStack_158;
  undefined4 local_130;
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
  
switchD_80129548_caseD_0:
  iVar4 = OSReceiveMessage(param_2,local_250,0);
  if (iVar4 == 0) {
    *(undefined *)(param_2 + 0xbd) = 0;
    OSReceiveMessage(param_2,local_250,1);
    *(undefined *)(param_2 + 0xbe) = 0;
  }
  if (local_250[0] == 1) {
    uVar3 = DAT_800000f8 / 4000;
    OSCreateAlarm(&OStack_68);
    OSSetAlarmTag(&OStack_68,1);
    local_40 = OSGetCurrentThread();
    uVar5 = OSDisableInterrupts();
    OSSetAlarm(&OStack_68,0x80130000,0,uVar3 * 10,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_40);
    OSRestoreInterrupts(uVar5);
    local_258 = 0x80000000;
    iVar4 = 0;
    do {
      GBAWrite((int)*(char *)(param_2 + 0xbc),&local_258,param_2 + 0xc0);
      uVar3 = DAT_800000f8 / 4000;
      OSCreateAlarm(&OStack_98);
      OSSetAlarmTag(&OStack_98,1);
      local_70 = OSGetCurrentThread();
      uVar16 = OSDisableInterrupts();
      OSSetAlarm(&OStack_98,(int)uVar16,0,uVar3 * 10,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
      OSSuspendThread(local_70);
      OSRestoreInterrupts((int)((ulonglong)uVar16 >> 0x20));
      iVar4 = iVar4 + 1;
    } while (iVar4 < 100);
    uVar3 = DAT_800000f8 / 4000;
    OSCreateAlarm(&OStack_c8);
    OSSetAlarmTag(&OStack_c8,1);
    local_a0 = OSGetCurrentThread();
    uVar5 = OSDisableInterrupts();
    OSSetAlarm(&OStack_c8,0x80130000,0,uVar3 * 10,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_a0);
    OSRestoreInterrupts(uVar5);
    *(byte *)(param_1 + 0x649d) =
         *(byte *)(param_1 + 0x649d) | (byte)(1 << (int)*(char *)(param_2 + 0xbc));
    OSExitThread(0);
    return;
  }
  if ((local_250[0] == 7) && (*(int *)(param_2 + 0x8c) == 0)) {
    local_250[0] = 8;
  }
  *(undefined *)(param_2 + 0xbd) = 1;
  iVar14 = 0;
  iVar15 = 0;
  *(undefined *)(param_2 + 0xc2) = 0;
  if (local_250[0] == 5) {
    uVar3 = (DAT_800000f8 / 4000) * 1000;
  }
  else if (local_250[0] < 5) {
    if (local_250[0] == 3) {
      uVar3 = (DAT_800000f8 / 4000) * 500;
    }
    else {
LAB_801293b0:
      uVar3 = (DAT_800000f8 / 4000) * 1000;
    }
  }
  else {
    if (local_250[0] != 10) goto LAB_801293b0;
    uVar3 = (DAT_800000f8 / 4000) * 500;
  }
  uVar16 = OSGetTime();
  uVar5 = 0x22c;
LAB_80129458:
  iVar7 = (int)((ulonglong)uVar16 >> 0x20);
  uVar13 = (uint)uVar16;
  if (*(char *)(param_2 + 0xbe) != '\0') goto code_r0x80129464;
  uVar17 = OSGetTime();
  uVar11 = (uint)uVar17 - uVar13;
  uVar12 = (int)((ulonglong)uVar17 >> 0x20) - ((uint)((uint)uVar17 < uVar13) + iVar7);
  if (0x80000000 < (uint)(uVar3 < uVar11) + (uVar12 ^ 0x80000000)) {
    Printf__7CSystemFPce(&System,s_retry__d_chan__d_801dd344,uVar5,(int)*(char *)(param_2 + 0xbc));
    if (iVar4 != 3) {
      iVar4 = 1;
    }
    *(char *)(param_2 + 0xbf) = (char)iVar4;
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x241);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    goto switchD_80129548_caseD_0;
  }
  switch(local_250[0]) {
  default:
    goto switchD_80129548_caseD_0;
  case 2:
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x248);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    uVar9 = GBAReset((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    *(undefined *)(param_2 + 0xbf) = uVar9;
    goto switchD_80129548_caseD_0;
  case 3:
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x24f);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    iVar4 = GBAReset((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    if (iVar4 != 0) {
      *(undefined *)(param_2 + 0xbf) = 0;
      goto switchD_80129548_caseD_0;
    }
    iVar4 = 3;
    uVar5 = 0x256;
    break;
  case 4:
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x25d);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    if (iVar4 != 0) goto LAB_80129718;
    if ((*(byte *)(param_2 + 0xc0) & 2) != 0) {
      uVar5 = 0x266;
      iVar4 = 0;
      goto LAB_80129458;
    }
    if (iVar15 == 1) {
      *(undefined *)(param_2 + 0xbf) = 0;
      goto switchD_80129548_caseD_0;
    }
    local_258 = 0x50000000;
    iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_258,param_2 + 0xc0);
    if (iVar4 == 0) {
      uVar5 = 0x274;
      iVar15 = iVar15 + 1;
      iVar4 = 0;
      goto LAB_80129458;
    }
    goto LAB_80129718;
  case 5:
    Printf__7CSystemFPce
              (&System,s_chan__d_step__d_contextRecvOffse_801dd358,(int)*(char *)(param_2 + 0xbc),
               iVar15,iVar14);
    if (0x5f < iVar14) {
      uVar5 = 0x27a;
      goto LAB_80129458;
    }
    iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    if ((iVar4 == 0) && (bVar1 = *(byte *)(param_2 + 0xc0), (bVar1 & 0x30) == 0x30)) {
      iVar4 = 0;
      if (iVar15 < 0x19) {
        if ((bVar1 & 2) != 0) {
          uVar5 = 0x292;
          goto LAB_80129458;
        }
        if (iVar15 == 0) {
          puVar10 = &local_258;
          local_258 = 0x30000000;
        }
        else {
          puVar10 = (undefined4 *)
                    (param_1 + *(char *)(param_2 + 0xbc) * 0x60 + (iVar15 + -1) * 4 + 0x16ac);
        }
        iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),puVar10,param_2 + 0xc0);
        if ((iVar4 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)) {
          iVar15 = iVar15 + 1;
          goto LAB_801298b0;
        }
        Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x2a1);
      }
      else {
        if ((bVar1 & 8) == 0) {
          uVar5 = 0x2aa;
          goto LAB_80129458;
        }
        iVar4 = GBARead((int)*(char *)(param_2 + 0xbc),param_2 + iVar14 + 0x28,param_2 + 0xc0);
        if ((iVar4 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)) {
          iVar14 = iVar14 + 4;
          if (iVar14 == 0x60) {
            *(undefined *)(param_2 + 0xc4) = 1;
            *(undefined *)(param_2 + 199) = 0;
            *(undefined *)(param_2 + 0xc5) = 1;
            *(undefined *)(param_2 + 0xbf) = 0;
            goto switchD_80129548_caseD_0;
          }
LAB_801298b0:
          iVar4 = 0;
          uVar5 = 0x2bf;
          goto LAB_80129458;
        }
        Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x2b2);
      }
    }
    else {
      Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x27f);
    }
    goto LAB_80129718;
  case 6:
    iVar4 = 1;
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x2c3);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    *(undefined4 *)(param_2 + 0x9c) = 1;
    *(undefined *)(param_2 + 0xc3) = 0;
    iVar7 = SIProbe((int)*(char *)(param_2 + 0xbc));
    *(int *)(param_2 + 0x98) = iVar7;
    if (iVar7 != 0x80) {
      if (iVar7 == 0x40000) {
        *(undefined4 *)(param_2 + 0x94) = 0x40000;
        *(undefined *)(param_2 + 0xbf) = 0;
      }
      else {
        if ((iVar7 != 8) && (iVar7 != 0x40)) {
          *(int *)(param_2 + 0x94) = iVar7;
        }
        *(undefined *)(param_2 + 0xbf) = 1;
      }
      goto switchD_80129548_caseD_0;
    }
    uVar5 = 0x2cb;
    break;
  case 7:
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x2dc);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    *(undefined4 *)(param_2 + 0x9c) = 1;
    *(undefined *)(param_2 + 0xc3) = 0;
    if (*(byte *)(param_2 + 199) < 2) {
      iVar4 = GBAJoyBoot((int)*(char *)(param_2 + 0xbc),(int)*(char *)(param_2 + 0xbc) << 1,2,
                         *(undefined4 *)(param_2 + 0x8c),*(undefined4 *)(param_2 + 0x90),
                         param_2 + 0xc0);
      *(char *)(param_2 + 199) = *(char *)(param_2 + 199) + '\x01';
    }
    else {
      iVar7 = 0;
      do {
        iVar4 = GBAJoyBoot((int)*(char *)(param_2 + 0xbc),(int)*(char *)(param_2 + 0xbc) << 1,2,
                           *(undefined4 *)(param_2 + 0x8c),*(undefined4 *)(param_2 + 0x90),
                           param_2 + 0xc0);
        if (iVar4 == 0) break;
        iVar7 = iVar7 + 1;
      } while (iVar7 < 100);
    }
    if (iVar4 == 0) {
      GbaThreadInitGbaContext__12CMiniGamePcsFP16MgGbaThreadParami(param_1,param_2,0);
      local_250[0] = 8;
      uVar16 = OSGetTime();
      uVar5 = 0x2f7;
      goto LAB_80129458;
    }
    uVar13 = DAT_800000f8 / 4000;
    OSCreateAlarm(&OStack_128);
    OSSetAlarmTag(&OStack_128,1);
    local_100 = OSGetCurrentThread();
    uVar5 = OSDisableInterrupts();
    OSSetAlarm(&OStack_128,0x80130000,0,uVar13 * 500,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_100);
    OSRestoreInterrupts(uVar5);
    if (iVar4 == 3) {
      if ((*(byte *)(param_2 + 0xc0) & 10) == 10) {
        if ((*(byte *)(param_2 + 0xc0) & 0x30) != 0x10) {
          GBARead((int)*(char *)(param_2 + 0xbc),auStack_254,param_2 + 0xc0);
        }
      }
      else {
        iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
        if (iVar7 == 0) {
          if (*(char *)(param_2 + 0xc0) == '(') {
            iVar7 = GBARead((int)*(char *)(param_2 + 0xbc),&local_264,param_2 + 0xc0);
            if (iVar7 == 0) {
              iVar7 = 0;
              *(undefined4 *)(param_2 + 0xa4) = local_264;
              *(undefined *)(param_2 + 0xc3) = 1;
            }
          }
          else {
            iVar7 = 1;
          }
        }
        if ((iVar7 == 0) &&
           ((iVar7 = memcmp(param_2 + 0xa4,param_1 + 0x1344,4), iVar7 == 0 ||
            (*(int *)(param_2 + 0xa4) == 0x414d4752)))) {
          iVar7 = memcmp(param_2 + 0xa4,param_1 + 0x1344,4);
          if (iVar7 == 0) {
            *(undefined4 *)(param_2 + 0x9c) = 0;
          }
          iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
          if (iVar7 == 0) {
            if (*(char *)(param_2 + 0xc0) == ' ') {
              iVar7 = GBAWrite((int)*(char *)(param_2 + 0xbc),param_1 + 0x1344,param_2 + 0xc0);
              if ((iVar7 == 0) &&
                 (iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0), iVar7 == 0))
              {
                if (*(char *)(param_2 + 0xc0) == '0') {
                  iVar7 = 0;
                }
                else {
                  iVar7 = 1;
                }
              }
            }
            else {
              iVar7 = 1;
            }
          }
          if (iVar7 != 0) goto LAB_80129ce4;
          local_25c = 0x60000000;
          iVar7 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_25c,param_2 + 0xc0);
          if ((iVar7 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)) {
            iVar7 = 0;
            do {
              iVar8 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
              if ((iVar8 != 0) || (*(char *)(param_2 + 0xc0) != '8')) {
                bVar2 = true;
                goto LAB_80129ce8;
              }
              iVar8 = GBARead((int)*(char *)(param_2 + 0xbc),param_2 + iVar7 + 0x28,param_2 + 0xc0);
              if ((iVar8 != 0) || ((*(byte *)(param_2 + 0xc0) & 0x30) != 0x30)) {
                bVar2 = true;
                goto LAB_80129ce8;
              }
              iVar7 = iVar7 + 4;
            } while (iVar7 < 0x60);
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
        }
        else {
LAB_80129ce4:
          bVar2 = true;
        }
LAB_80129ce8:
        if (!bVar2) {
          (**(code **)(param_2 + 0x24))(param_2,local_250[0]);
          goto switchD_80129548_caseD_0;
        }
      }
    }
    uVar5 = 0x30f;
    break;
  case 8:
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x312);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    *(undefined4 *)(param_2 + 0x9c) = 1;
    *(undefined *)(param_2 + 0xc3) = 0;
    iVar4 = GBAReset((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    if (iVar4 == 0) {
      iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
      if (iVar7 == 0) {
        if (*(char *)(param_2 + 0xc0) == '(') {
          iVar7 = GBARead((int)*(char *)(param_2 + 0xbc),&local_268,param_2 + 0xc0);
          if (iVar7 == 0) {
            iVar7 = 0;
            *(undefined4 *)(param_2 + 0xa4) = local_268;
            *(undefined *)(param_2 + 0xc3) = 1;
          }
        }
        else {
          iVar7 = 1;
        }
      }
      if ((iVar7 == 0) &&
         ((iVar7 = memcmp(param_2 + 0xa4,param_1 + 0x1344,4), iVar7 == 0 ||
          (*(int *)(param_2 + 0xa4) == 0x414d4752)))) {
        iVar7 = memcmp(param_2 + 0xa4,param_1 + 0x1344,4);
        if (iVar7 == 0) {
          *(undefined4 *)(param_2 + 0x9c) = 0;
        }
        iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
        if (iVar7 == 0) {
          if (*(char *)(param_2 + 0xc0) == ' ') {
            iVar7 = GBAWrite((int)*(char *)(param_2 + 0xbc),param_1 + 0x1344,param_2 + 0xc0);
            if ((iVar7 == 0) &&
               (iVar7 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0), iVar7 == 0)) {
              if (*(char *)(param_2 + 0xc0) == '0') {
                iVar7 = 0;
              }
              else {
                iVar7 = 1;
              }
            }
          }
          else {
            iVar7 = 1;
          }
        }
        if (iVar7 != 0) goto LAB_80129f68;
        local_260 = 0x60000000;
        iVar7 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_260,param_2 + 0xc0);
        if ((iVar7 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)) {
          iVar7 = 0;
          do {
            iVar8 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
            if ((iVar8 != 0) || (*(char *)(param_2 + 0xc0) != '8')) {
              bVar2 = true;
              goto LAB_80129f6c;
            }
            iVar8 = GBARead((int)*(char *)(param_2 + 0xbc),param_2 + iVar7 + 0x28,param_2 + 0xc0);
            if ((iVar8 != 0) || ((*(byte *)(param_2 + 0xc0) & 0x30) != 0x30)) {
              bVar2 = true;
              goto LAB_80129f6c;
            }
            iVar7 = iVar7 + 4;
          } while (iVar7 < 0x60);
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
      }
      else {
LAB_80129f68:
        bVar2 = true;
      }
LAB_80129f6c:
      if (!bVar2) {
        (**(code **)(param_2 + 0x24))(param_2,local_250[0]);
        goto switchD_80129548_caseD_0;
      }
      uVar5 = 0x322;
    }
    else {
      uVar5 = 0x31a;
    }
    break;
  case 10:
    if (iVar15 == 0) {
      if (*(char *)(param_2 + 0xc4) == '\0') {
        *(undefined *)(param_2 + 0xbf) = 1;
        goto switchD_80129548_caseD_0;
      }
      iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
      if ((iVar4 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x10)) {
        local_258 = 0x10000000;
        iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_258,param_2 + 0xc0);
        if (iVar4 != 0) {
          Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x33c);
          goto LAB_80129718;
        }
        uVar16 = OSGetTime();
        uVar5 = 0x341;
        iVar15 = 1;
        iVar4 = 0;
      }
      else {
        uVar13 = DAT_800000f8 / 500000;
        OSCreateAlarm(&OStack_158);
        OSSetAlarmTag(&OStack_158,1);
        local_130 = OSGetCurrentThread();
        uVar5 = OSDisableInterrupts();
        OSSetAlarm(&OStack_158,0x80130000,0,uVar13 * 100 >> 3,
                   GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
        OSSuspendThread(local_130);
        OSRestoreInterrupts(uVar5);
        uVar5 = 0x333;
      }
      goto LAB_80129458;
    }
    if (iVar15 == 1) {
      iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
      if ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30) {
        if ((*(byte *)(param_2 + 0xc0) & 10) == 8) {
          uVar13 = DAT_800000f8 / 500000;
          OSCreateAlarm(&OStack_1e8);
          OSSetAlarmTag(&OStack_1e8,1);
          local_1c0 = OSGetCurrentThread();
          uVar5 = OSDisableInterrupts();
          OSSetAlarm(&OStack_1e8,0x80130000,0,uVar13 * 10 >> 3,
                     GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
          OSSuspendThread(local_1c0);
          OSRestoreInterrupts(uVar5);
          iVar4 = GBARead((int)*(char *)(param_2 + 0xbc),param_2 + 0xa0,param_2 + 0xc0);
          if ((iVar4 != 0) || (*(uint *)(param_2 + 0xa0) >> 0x18 != 0x20)) {
            Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x372);
            goto LAB_80129718;
          }
          uVar5 = 0x376;
          iVar15 = 2;
          iVar4 = 0;
        }
        else {
          uVar5 = 0x367;
        }
      }
      else {
        uVar11 = DAT_800000f8 / 500000;
        OSCreateAlarm(&OStack_188);
        OSSetAlarmTag(&OStack_188,1);
        local_160 = OSGetCurrentThread();
        uVar5 = OSDisableInterrupts();
        OSSetAlarm(&OStack_188,0x80130000,0,uVar11 * 100 >> 3,
                   GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
        OSSuspendThread(local_160);
        OSRestoreInterrupts(uVar5);
        uVar17 = OSGetTime();
        if (0x80000000 <
            (uint)((DAT_800000f8 / 4000) * 200 < (uint)uVar17 - uVar13) +
            ((int)((ulonglong)uVar17 >> 0x20) - ((uint)((uint)uVar17 < uVar13) + iVar7) ^ 0x80000000
            )) {
          Printf__7CSystemFPce
                    (&System,s_GBA_JSTAT_FLAGS_MASK_retry_chan__801dd3d4,
                     (int)*(char *)(param_2 + 0xbc));
          local_258 = 0x10000000;
          iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_258,param_2 + 0xc0);
          uVar16 = OSGetTime();
          uVar13 = DAT_800000f8 / 500000;
          OSCreateAlarm(&OStack_1b8);
          OSSetAlarmTag(&OStack_1b8,1);
          local_190 = OSGetCurrentThread();
          uVar5 = OSDisableInterrupts();
          OSSetAlarm(&OStack_1b8,0x80130000,0,uVar13 * 100 >> 3,
                     GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
          OSSuspendThread(local_190);
          OSRestoreInterrupts(uVar5);
        }
        uVar5 = 0x352;
      }
      goto LAB_80129458;
    }
    iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
    if ((iVar4 != 0) || ((*(byte *)(param_2 + 0xc0) & 2) != 0)) {
      uVar5 = 0x37e;
      goto LAB_80129458;
    }
    if (iVar15 == 7) {
      iVar4 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0);
      if ((iVar4 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) != 0x30)) {
        *(undefined *)(param_2 + 0xc2) = 1;
        *(undefined *)(param_2 + 0xbf) = 0;
        goto switchD_80129548_caseD_0;
      }
      if (0x80000000 < (uint)((DAT_800000f8 / 4000) * 200 < uVar11) + (uVar12 ^ 0x80000000)) {
        Printf__7CSystemFPce
                  (&System,s_GBA_JSTAT_PSF1_retry_chan__d_801dd3f8,(int)*(char *)(param_2 + 0xbc));
        local_258 = 0x70000000;
        iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),&local_258,param_2 + 0xc0);
        if (iVar4 != 0) {
          Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x397);
          goto LAB_80129718;
        }
        uVar16 = OSGetTime();
        iVar15 = 2;
        iVar4 = 0;
      }
      uVar13 = DAT_800000f8 / 500000;
      OSCreateAlarm(&OStack_218);
      OSSetAlarmTag(&OStack_218,1);
      local_1f0 = OSGetCurrentThread();
      uVar5 = OSDisableInterrupts();
      OSSetAlarm(&OStack_218,0x80130000,0,uVar13 * 1000 >> 3,
                 GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
      OSSuspendThread(local_1f0);
      OSRestoreInterrupts(uVar5);
      uVar5 = 0x39e;
      goto LAB_80129458;
    }
    iVar4 = GBAWrite((int)*(char *)(param_2 + 0xbc),param_2 + (iVar15 + -2) * 4 + 0xa8,
                     param_2 + 0xc0);
    uVar13 = DAT_800000f8 / 500000;
    OSCreateAlarm(&OStack_248);
    OSSetAlarmTag(&OStack_248,1);
    local_220 = OSGetCurrentThread();
    uVar5 = OSDisableInterrupts();
    OSSetAlarm(&OStack_248,0x80130000,0,uVar13 * 100 >> 3,
               GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_220);
    OSRestoreInterrupts(uVar5);
    if (iVar4 == 0) {
      uVar5 = 0x3b0;
      iVar15 = iVar15 + 1;
      iVar4 = 0;
      goto LAB_80129458;
    }
    Printf__7CSystemFPce(&System,s__s____d_801dd380,s_p_minigame_cpp_801dd38c,0x3ac);
LAB_80129718:
    Printf__7CSystemFPce
              (&System,s_ret__d_status_0x_02x_step__d_con_801dd39c,iVar4,
               *(byte *)(param_2 + 0xc0) & 0x30,iVar15,iVar14);
    if (iVar4 == 0) {
      iVar4 = 3;
    }
    *(char *)(param_2 + 0xbf) = (char)iVar4;
    if (*(char *)(param_2 + 0xc4) != '\0') {
      Printf__7CSystemFPce
                (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
                 0x287);
    }
    *(undefined *)(param_2 + 0xc4) = 0;
    goto switchD_80129548_caseD_0;
  }
  uVar13 = DAT_800000f8 / 4000;
  OSCreateAlarm(&OStack_f8);
  OSSetAlarmTag(&OStack_f8,1);
  local_d0 = OSGetCurrentThread();
  uVar6 = OSDisableInterrupts();
  OSSetAlarm(&OStack_f8,0x80130000,0,uVar13,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
  OSSuspendThread(local_d0);
  OSRestoreInterrupts(uVar6);
  goto LAB_80129458;
code_r0x80129464:
  *(undefined *)(param_2 + 0xbf) = 3;
  if (*(char *)(param_2 + 0xc4) != '\0') {
    Printf__7CSystemFPce
              (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
               0x234);
  }
  *(undefined *)(param_2 + 0xc4) = 0;
  goto switchD_80129548_caseD_0;
}

