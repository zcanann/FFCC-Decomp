// Function: Thread__8CGraphicFv
// Entry: 800193c8
// Size: 632 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Thread__8CGraphicFv(CGraphic *graphic)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  OSAlarm OStack_58;
  undefined4 local_30;
  
  iVar7 = -1;
  iVar6 = 5;
  while( true ) {
    if (*(int *)&graphic->field_0x7364 == 0) {
      iVar6 = 5;
    }
    else {
      if (iVar7 != *(int *)&graphic->field_0x7370) {
        iVar6 = 100;
        iVar7 = *(int *)&graphic->field_0x7370;
      }
      iVar6 = iVar6 + -1;
      if (iVar6 == 0) {
        uVar1 = GXReadDrawSync();
        uVar5 = uVar1 & 0xffff;
        if ((uVar1 & 0x8000) != 0) {
          uVar5 = uVar1 & 0x7fff;
          if (uVar5 == 0x7fff) {
            Printf__7CSystemFPce
                      (&System,&DAT_801d637c,*(undefined4 *)&graphic->field_0x7368,
                       *(undefined4 *)&graphic->field_0x736c);
          }
          else if (uVar5 == 0x7ffe) {
            Printf__7CSystemFPce
                      (&System,&DAT_801d63c0,*(undefined4 *)&graphic->field_0x7368,
                       *(undefined4 *)&graphic->field_0x736c);
          }
          else {
            Printf__7CSystemFPce
                      (&System,&DAT_801d6400,*(undefined4 *)&graphic->field_0x7368,
                       *(undefined4 *)&graphic->field_0x736c,pppSysProgTbl.m_progs[uVar5].m_pppName)
            ;
          }
        }
        iVar2 = GetOrder__7CSystemFi(&System,(int)uVar5 >> 8);
        if (iVar2 == 0) {
          uVar4 = 0xffffffff;
          puVar3 = &DAT_8032f714;
        }
        else {
          uVar4 = *(undefined4 *)(iVar2 + 0xc);
          puVar3 = *(undefined **)(iVar2 + 8);
        }
        Printf__7CSystemFPce
                  (&System,&DAT_801d643c,*(undefined4 *)&graphic->field_0x7368,
                   *(undefined4 *)&graphic->field_0x736c,puVar3,uVar4,(int)(char)uVar5);
      }
    }
    if (DAT_8032ec4c == '\0') {
      DAT_8032ec48 = 0;
      DAT_8032ec4c = '\x01';
    }
    if (DAT_8032ec54 == '\0') {
      DAT_8032ec50 = 0;
      DAT_8032ec54 = '\x01';
    }
    iVar2 = OSGetResetButtonState();
    if (iVar2 == 0) {
      if (DAT_8032ec48 != 0) {
        DAT_8032ec50 = 1;
      }
    }
    else {
      DAT_8032ec48 = 1;
    }
    if (((DAT_8032ec50 != 0) && (File.fatal_diskErrorFlag == 0)) &&
       (MemoryCardMan.m_currentSlot == 0xff)) break;
    local_30 = OSGetCurrentThread();
    OSCreateAlarm(&OStack_58);
    OSSetAlarmTag(&OStack_58,1);
    uVar8 = OSDisableInterrupts();
    OSSetAlarm(&OStack_58,(int)uVar8,0,(DAT_800000f8 / 4000) * 0x32,wakeup__FP7OSAlarmP9OSContext);
    OSSuspendThread(local_30);
    OSRestoreInterrupts((int)((ulonglong)uVar8 >> 0x20));
  }
  VISetBlack(1);
  VIFlush();
  VIWaitForRetrace();
  OSCancelAlarms(1);
  OSResetSystem(0,0,0);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

