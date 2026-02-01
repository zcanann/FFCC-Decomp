// Function: SetMusicData__10CRedDriverFPv
// Entry: 801becd8
// Size: 276 bytes

int SetMusicData__10CRedDriverFPv(CRedDriver *redDriver,char *param_2)

{
  void *dstBuffer;
  undefined auStack_38 [4];
  short local_34;
  undefined4 local_28;
  
  if (((*param_2 == 'B') && (param_2[1] == 'G')) && (param_2[2] == 'M')) {
    memcpy(auStack_38,param_2,0x20);
    dstBuffer = (void *)RedNew__Fi(local_28);
    if (dstBuffer == (void *)0x0) {
      return -1;
    }
    memcpy(dstBuffer,param_2,local_28);
    _EntryExecCommand__FPFPi_viiiiiii(_SetMusicData__FPi,(int)dstBuffer,0,0,0,0,0,0);
    return (int)local_34;
  }
  if (DAT_8032f408 != 0) {
    OSReport(s__s_sMusic_Header_was_broken____s_801e7840,&DAT_801e77a8,&DAT_80333d10,&DAT_80333d18);
    fflush(&DAT_8021d1a8);
  }
  return -1;
}

