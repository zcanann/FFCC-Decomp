// Function: WaveHeadAdd__9CRedEntryFiP13RedWaveHeadWDi
// Entry: 801c0b80
// Size: 832 bytes

int WaveHeadAdd__9CRedEntryFiP13RedWaveHeadWDi(int *param_1,uint param_2,char *param_3,int param_4)

{
  int iVar1;
  void *dstBuffer;
  undefined4 uVar2;
  undefined4 uVar3;
  int count;
  int *piVar4;
  
  if ((*param_3 == 'W') && (param_3[1] == 'D')) {
    if (*(int *)(param_3 + 0x14) < *(int *)(param_3 + 4)) {
      *(undefined4 *)(param_3 + 0x14) = *(undefined4 *)(param_3 + 4);
    }
    if ((param_4 < 100) || (299 < param_4)) {
      if ((param_4 < 10) || (0x45 < param_4)) {
        if ((((0x153 < param_4) && (param_4 < 0x17a)) || ((0x17e < param_4 && (param_4 < 0x182))))
           || (param_4 == 0x183)) {
          param_3[0x14] = '\0';
          param_3[0x15] = '\x10';
          param_3[0x16] = '\0';
          param_3[0x17] = '\0';
        }
      }
      else {
        *(int *)(param_3 + 0x14) = *(int *)(param_3 + 0x14) + 0x27fff;
        iVar1 = *(int *)(param_3 + 0x14) / 0x28000 + (*(int *)(param_3 + 0x14) >> 0x1f);
        *(int *)(param_3 + 0x14) = iVar1 - (iVar1 >> 0x1f);
        *(int *)(param_3 + 0x14) = *(int *)(param_3 + 0x14) * 0x28000;
      }
    }
    else if (*(int *)(param_3 + 0x14) < 0x200001) {
      param_3[0x14] = '\0';
      param_3[0x15] = ' ';
      param_3[0x16] = '\0';
      param_3[0x17] = '\0';
    }
    else if (*(int *)(param_3 + 0x14) < 0x400001) {
      param_3[0x14] = '\0';
      param_3[0x15] = '@';
      param_3[0x16] = '\0';
      param_3[0x17] = '\0';
    }
    if ((param_4 < 100) || (299 < param_4)) {
      if (((param_4 < 0x154) || (0x179 < param_4)) &&
         (((param_4 < 0x17f || (0x181 < param_4)) && (param_4 != 0x183)))) {
        uVar3 = 0;
        uVar2 = 0x300000;
      }
      else {
        uVar3 = 0x300000;
        uVar2 = 0x400000;
      }
    }
    else {
      uVar3 = 0x400000;
      uVar2 = 0x800000;
    }
    do {
      if ((int)param_2 < 0) {
        for (piVar4 = (int *)(*param_1 + 0x100);
            (piVar4[3] != 0 && (piVar4 < (int *)(*param_1 + 0x400U))); piVar4 = piVar4 + 4) {
        }
      }
      else {
        param_2 = param_2 & 0xf;
        piVar4 = (int *)(*param_1 + param_2 * 0x10);
        if (piVar4[3] != 0) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar4);
        }
      }
      if ((piVar4 < (int *)(*param_1 + 0x400U)) &&
         (iVar1 = RedNewA__Fiii(*(undefined4 *)(param_3 + 0x14),uVar3,uVar2), iVar1 != 0)) {
        count = (*(int *)(param_3 + 8) * 4 + 0x1fU & 0xffffffe0) + *(int *)(param_3 + 0xc) * 0x60 +
                0x20;
        dstBuffer = (void *)RedNew__Fi(count);
        if (dstBuffer != (void *)0x0) {
          piVar4[2] = (int)dstBuffer;
          piVar4[3] = count;
          *(int *)(param_3 + 0x10) = iVar1;
          *piVar4 = param_4;
          *(short *)(param_3 + 2) = (short)param_4;
          if ((int)param_2 < 0) {
            WaveHistoryAdd__9CRedEntryFi(param_1,1);
            piVar4[1] = 1;
          }
          else {
            piVar4[1] = 0;
          }
          memcpy(dstBuffer,param_3,count);
          return iVar1;
        }
        RedDeleteA__FPv(iVar1);
      }
      iVar1 = WaveOldClear__9CRedEntryFii(param_1,uVar3,uVar2);
    } while (iVar1 != 0);
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991,&DAT_801e7905,&DAT_80333d30,
               (int)*(short *)(param_3 + 2),*(undefined4 *)(param_3 + 4),&DAT_80333d38);
      fflush(&DAT_8021d1a8);
    }
  }
  else if (DAT_8032f408 != 0) {
    OSReport(s__s_sWave_Header_was_broken__s_801e7972,&DAT_801e7905,&DAT_80333d3d,&DAT_80333d38);
    fflush(&DAT_8021d1a8);
  }
  return -1;
}

