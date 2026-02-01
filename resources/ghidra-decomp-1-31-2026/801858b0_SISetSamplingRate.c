// Function: SISetSamplingRate
// Entry: 801858b0
// Size: 228 bytes

void SISetSamplingRate(uint param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  
  puVar4 = &DAT_802173d8;
  if (0xb < param_1) {
    param_1 = 0xb;
  }
  uVar2 = OSDisableInterrupts();
  DAT_8032f010 = param_1;
  iVar3 = VIGetTvFormat();
  if (iVar3 == 2) {
LAB_80185918:
    puVar4 = &DAT_802173d8;
  }
  else {
    if (iVar3 < 2) {
      if (iVar3 == 0) goto LAB_80185918;
      if (-1 < iVar3) {
        puVar4 = (undefined2 *)0x80217408;
        goto LAB_8018593c;
      }
    }
    else if (iVar3 == 5) goto LAB_80185918;
    OSReport(s_SISetSamplingRate__unknown_TV_fo_80217438);
    param_1 = 0;
  }
LAB_8018593c:
  uVar1 = DAT_cc00206c;
  if ((uVar1 & 1) == 0) {
    iVar3 = 1;
  }
  else {
    iVar3 = 2;
  }
  SISetXY(iVar3 * (uint)(ushort)puVar4[param_1 * 2],*(undefined *)(puVar4 + param_1 * 2 + 1));
  OSRestoreInterrupts(uVar2);
  return;
}

