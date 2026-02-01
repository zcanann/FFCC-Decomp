// Function: DBWrite
// Entry: 801bc494
// Size: 608 bytes

undefined4 DBWrite(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_3c [2];
  uint local_34 [2];
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  
  uVar3 = OSDisableInterrupts();
  do {
    uVar5 = DAT_cc006828;
    DAT_cc006828 = uVar5 & 0x405 | 0xc0;
    local_28 = 0x40000000;
    uVar4 = DBGEXIImm(&local_28,2,1);
    countLeadingZeros(uVar4);
    do {
      uVar5 = DAT_cc006834;
    } while ((uVar5 & 1) != 0);
    DBGEXIImm(&local_24,4,0);
    do {
      uVar5 = DAT_cc006834;
    } while ((uVar5 & 1) != 0);
    uVar5 = DAT_cc006828;
    DAT_cc006828 = uVar5 & 0x405;
  } while ((local_24 & 2) != 0);
  DAT_8032ec28 = DAT_8032ec28 + 1;
  if ((DAT_8032ec28 & 1) == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0x1000;
  }
  do {
    iVar6 = DBGWrite(uVar5 | 0x1c000,param_1,param_2 + 3 & 0xfffffffc);
  } while (iVar6 == 0);
  do {
    uVar5 = DAT_cc006828;
    DAT_cc006828 = uVar5 & 0x405 | 0xc0;
    local_2c = 0x40000000;
    uVar4 = DBGEXIImm(&local_2c,2,1);
    countLeadingZeros(uVar4);
    do {
      uVar5 = DAT_cc006834;
    } while ((uVar5 & 1) != 0);
    DBGEXIImm(&local_24,4,0);
    do {
      uVar5 = DAT_cc006834;
    } while ((uVar5 & 1) != 0);
    uVar5 = DAT_cc006828;
    DAT_cc006828 = uVar5 & 0x405;
  } while ((local_24 & 2) != 0);
  uVar5 = (uint)DAT_8032ec28;
  do {
    uVar2 = DAT_cc006828;
    DAT_cc006828 = uVar2 & 0x405 | 0xc0;
    local_34[0] = uVar5 << 0x10 | 0x1f000000 | param_2 & 0x1fffffff | 0xc0000000;
    uVar4 = DBGEXIImm(local_34,4,1);
    uVar2 = countLeadingZeros(uVar4);
    do {
      uVar1 = DAT_cc006834;
    } while ((uVar1 & 1) != 0);
    uVar1 = DAT_cc006828;
    DAT_cc006828 = uVar1 & 0x405;
  } while (uVar2 >> 5 != 0);
  do {
    uVar5 = DAT_cc006828;
    DAT_cc006828 = uVar5 & 0x405 | 0xc0;
    local_3c[0] = 0x40000000;
    uVar4 = DBGEXIImm(local_3c,2,1);
    uVar5 = countLeadingZeros(uVar4);
    do {
      uVar2 = DAT_cc006834;
    } while ((uVar2 & 1) != 0);
    uVar4 = DBGEXIImm(&local_24,4,0);
    uVar2 = countLeadingZeros(uVar4);
    do {
      uVar1 = DAT_cc006834;
    } while ((uVar1 & 1) != 0);
    uVar1 = DAT_cc006828;
    DAT_cc006828 = uVar1 & 0x405;
  } while ((uVar5 >> 5 != 0 || uVar2 >> 5 != 0) || ((local_24 & 2) != 0));
  OSRestoreInterrupts(uVar3);
  return 0;
}

