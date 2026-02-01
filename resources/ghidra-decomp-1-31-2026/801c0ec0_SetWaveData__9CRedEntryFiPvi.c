// Function: SetWaveData__9CRedEntryFiPvi
// Entry: 801c0ec0
// Size: 720 bytes

int SetWaveData__9CRedEntryFiPvi(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int unaff_r22;
  int iVar4;
  int unaff_r25;
  
  if (param_4 == 0) {
    if ((-1 < param_1[3]) &&
       (iVar1 = SearchWaveSequence__9CRedEntryFi(param_1,param_1[3]), -1 < iVar1)) {
      WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + iVar1 * 0x10);
    }
    iVar1 = -1;
    param_1[3] = -1;
  }
  else {
    iVar1 = 0;
    if (param_1[3] < 0) {
      iVar4 = (int)*(short *)(param_3 + 2);
      if ((-1 < param_2) && (iVar4 != *(int *)(*param_1 + param_2 * 0x10))) {
        WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + param_2 * 0x10);
      }
      iVar2 = SearchWaveSequence__9CRedEntryFi(param_1,iVar4);
      if (iVar2 < 0) {
        param_1[3] = (int)*(short *)(param_3 + 2);
        iVar1 = WaveHeadAdd__9CRedEntryFiP13RedWaveHeadWDi(param_1,param_2,param_3,iVar4);
        if (iVar1 < 0) {
          param_1[4] = 0;
          param_1[3] = -1;
          return -1;
        }
        unaff_r25 = *(int *)(param_3 + 4);
        iVar4 = (*(int *)(param_3 + 8) * 4 + 0x1fU & 0xffffffe0) + *(int *)(param_3 + 0xc) * 0x60 +
                0x20;
        param_4 = param_4 - iVar4;
        param_3 = param_3 + iVar4;
      }
      else {
        if ((-1 < param_2) && (iVar2 != param_2)) {
          *(undefined4 *)(*param_1 + param_2 * 0x10) = *(undefined4 *)(*param_1 + iVar2 * 0x10);
          *(undefined4 *)(*param_1 + param_2 * 0x10 + 4) =
               *(undefined4 *)(*param_1 + iVar2 * 0x10 + 4);
          *(undefined4 *)(*param_1 + param_2 * 0x10 + 8) =
               *(undefined4 *)(*param_1 + iVar2 * 0x10 + 8);
          *(undefined4 *)(*param_1 + param_2 * 0x10 + 0xc) =
               *(undefined4 *)(*param_1 + iVar2 * 0x10 + 0xc);
          iVar2 = param_2;
        }
        WaveHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + iVar2 * 0x10);
        param_3 = unaff_r22;
      }
    }
    else {
      iVar1 = param_1[5];
      unaff_r25 = param_1[4];
    }
    if ((iVar1 != 0) && (0 < param_4)) {
      iVar4 = unaff_r25;
      if (param_4 < unaff_r25) {
        iVar4 = param_4;
      }
      uVar3 = RedDmaEntry__FiiiiiPFPv_vPv(0x8000,0,param_3,iVar1,iVar4,(void *)0x0,(void *)0x0);
      param_1[4] = unaff_r25 - iVar4;
      param_1[5] = iVar1 + iVar4;
      while (iVar1 = RedDmaSearchID__Fi(uVar3), 0 < iVar1) {
        RedSleep__Fi(1000);
      }
      if (param_1[4] < 1) {
        if (DAT_8032f408 != 0) {
          OSReport(s__s_sWave_Entry___wave_4_4u__s_801e79ce,&DAT_801e7905,&DAT_80333d45,param_1[3],
                   &DAT_80333d38);
          fflush(&DAT_8021d1a8);
        }
        param_1[3] = -1;
        return 0;
      }
    }
    iVar1 = param_1[3];
  }
  return iVar1;
}

