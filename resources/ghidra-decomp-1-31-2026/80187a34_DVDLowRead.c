// Function: DVDLowRead
// Entry: 80187a34
// Size: 664 bytes

undefined4 DVDLowRead(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  bool bVar2;
  DVDDiskId *pDVar3;
  int iVar4;
  undefined4 extraout_r4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined8 uVar8;
  
  DAT_cc006018 = param_2;
  DAT_8030ca14 = param_1;
  DAT_8030ca18 = param_2;
  DAT_8030ca1c = param_3;
  if (DAT_8032f03c == 0) {
    DAT_8030c950 = 0xffffffff;
    DAT_8032f05c = 0;
    Read(param_1,param_2,param_3,param_4);
  }
  else if (DAT_8032f03c == 1) {
    if (DAT_8032ead0 == 0) {
      uVar5 = (uint)(DAT_8030ca10 + DAT_8030ca0c + -1) >> 0xf;
      pDVar3 = DVDGetCurrentDiskID();
      if (pDVar3->streaming == '\0') {
        iVar4 = 0xf;
      }
      else {
        iVar4 = 5;
      }
      if ((uVar5 - 2 < param_3 >> 0xf) || (param_3 >> 0xf < uVar5 + iVar4 + 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        uVar5 = (uint)(DAT_8030ca10 + DAT_8030ca0c + -1) >> 0xf;
        if ((uVar5 == DAT_8030ca1c >> 0xf) || (uVar5 + 1 == DAT_8030ca1c >> 0xf)) {
          uVar8 = __OSGetSystemTime();
          uVar7 = (uint)uVar8 - DAT_8032f04c;
          uVar6 = (int)((ulonglong)uVar8 >> 0x20) -
                  ((uint)((uint)uVar8 < DAT_8032f04c) + DAT_8032f048);
          uVar5 = ((DAT_800000f8 >> 2) / 1000) * 5;
          if ((uint)(uVar5 < uVar7) + (uVar6 ^ 0x80000000) < 0x80000001) {
            DAT_8030c950 = 1;
            DAT_8030c964 = 0xffffffff;
            uVar1 = ((DAT_800000f8 >> 2) / 0x1e848) * 500 >> 3;
            DAT_8032f05c = 0;
            DAT_8030c954 = param_1;
            DAT_8030c958 = param_2;
            DAT_8030c95c = param_3;
            DAT_8030c960 = param_4;
            OSCreateAlarm(&DAT_8030c990);
            OSSetAlarm((OSAlarm *)&DAT_8030c990,extraout_r4,
                       (uint)CARRY4(uVar5 - uVar7,uVar1) - ((uVar5 < uVar7) + uVar6),
                       (uVar5 - uVar7) + uVar1,AlarmHandler);
          }
          else {
            DAT_8030c950 = 0xffffffff;
            DAT_8032f05c = 0;
            Read(param_1,param_2,param_3,param_4);
          }
        }
        else {
          SeekTwiceBeforeRead(param_1,param_2,param_3,param_4);
        }
      }
      else {
        DAT_8030c950 = 0xffffffff;
        DAT_8032f05c = 0;
        Read(param_1,param_2,param_3,param_4);
      }
    }
    else {
      SeekTwiceBeforeRead(param_1,param_2,param_3,param_4);
    }
  }
  return 1;
}

