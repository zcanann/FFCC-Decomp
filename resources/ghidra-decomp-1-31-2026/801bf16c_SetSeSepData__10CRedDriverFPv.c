// Function: SetSeSepData__10CRedDriverFPv
// Entry: 801bf16c
// Size: 288 bytes

undefined4 SetSeSepData__10CRedDriverFPv(CRedDriver *redDriver,char *param_2)

{
  void *dstBuffer;
  undefined4 uVar1;
  uint uVar2;
  
  if ((((*param_2 == 'S') && (param_2[1] == 'e')) && (param_2[2] == 'S')) &&
     ((param_2[3] == 'e' && (param_2[4] == 'p')))) {
    uVar2 = *(uint *)(param_2 + 0xc);
    dstBuffer = (void *)RedNew__Fi(uVar2 & 0x7fffffff);
    if (dstBuffer == (void *)0x0) {
      return 0xffffffff;
    }
    memcpy(dstBuffer,param_2,uVar2 & 0x7fffffff);
    uVar1 = *(undefined4 *)((int)dstBuffer + 8);
    _EntryExecCommand__FPFPi_viiiiiii(_SetSeSepData__FPi,(int)dstBuffer,0,0,0,0,0,0);
    return uVar1;
  }
  if (DAT_8032f408 != 0) {
    OSReport(s__s_sSE_Sep_Header_was_broken_____801e7862,&DAT_801e77a8,&DAT_80333d10,&DAT_80333d18);
    fflush(&DAT_8021d1a8);
  }
  return 0xffffffff;
}

