// Function: StreamPlay__FiPviii
// Entry: 801cc034
// Size: 1280 bytes

int StreamPlay__FiPviii(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  
  piVar1 = (int *)_SearchEmptyStreamData__Fv();
  if (piVar1 != (int *)0x0) {
    memcpy(piVar1 + 4,param_2,0x20);
    iVar2 = SearchSeEmptyTrack__Fiii((int)*(short *)((int)piVar1 + 0x2a),0xff,0);
    *piVar1 = iVar2;
    iVar2 = RedNew__Fi(0x4000);
    piVar1[3] = iVar2;
    iVar2 = (int)*(short *)((int)piVar1 + 0x2a) << 0xd;
    iVar3 = GetABufferSize__10CRedMemoryFv(&DAT_8032f480);
    if (iVar3 < 0x800000) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0x300000;
    }
    iVar3 = RedNewA__Fiii(iVar2,0,uVar4);
    piVar1[0x4b] = iVar3;
    if (piVar1[0x4b] == 0) {
      WaveOldClear__9CRedEntryFii(&DAT_8032e154,0,uVar4);
      iVar2 = RedNewA__Fiii(iVar2,0,uVar4);
      piVar1[0x4b] = iVar2;
    }
    if (((*piVar1 == 0) || (piVar1[3] == 0)) || (piVar1[0x4b] == 0)) {
      if (DAT_8032f408 != 0) {
        OSReport(s__s_sStream_Buffer_didn_t_secure__801e7f20,&DAT_801e7f44,&DAT_80333d80,
                 &DAT_80333d88);
        fflush(&DAT_8021d1a8);
      }
      if (piVar1[3] == 0) {
        if (DAT_8032f408 != 0) {
          OSReport(s__s_sM_Memory_didn_t_create__need_801e7f56,&DAT_801e7f44,&DAT_80333d8d,0x4000,
                   &DAT_80333d88);
          fflush(&DAT_8021d1a8);
        }
      }
      else {
        RedDelete__FPv(piVar1[3]);
      }
      if (piVar1[0x4b] == 0) {
        if (DAT_8032f408 != 0) {
          OSReport(s__s_sA_Memory_didn_t_create__need_801e7f83,&DAT_801e7f44,&DAT_80333d8d,
                   (int)*(short *)((int)piVar1 + 0x2a) << 0xd,&DAT_80333d88);
          fflush(&DAT_8021d1a8);
        }
      }
      else {
        RedDeleteA__Fi(piVar1[0x4b]);
      }
    }
    else {
      *(short *)(param_2 + 0x42) = (short)*(char *)(param_2 + 0x1000);
      *(undefined2 *)(param_2 + 0x46) = 0;
      *(undefined2 *)(param_2 + 0x44) = 0;
      if (*(short *)((int)piVar1 + 0x2a) == 2) {
        if (piVar1[8] < 0) {
          iVar2 = 0x2000;
        }
        else {
          iVar2 = 0x1008;
        }
        *(short *)(param_2 + 0x70) = (short)*(char *)(param_2 + iVar2);
        *(undefined2 *)(param_2 + 0x74) = 0;
        *(undefined2 *)(param_2 + 0x72) = 0;
      }
      piVar1[0x43] = param_1;
      piVar1[0x47] = 0;
      piVar1[0x48] = 0x1000;
      piVar1[0x49] = 0;
      piVar1[1] = DAT_8032f444 + *(char *)(*piVar1 + 0x14e) * 0xc0;
      piVar1[2] = param_2;
      piVar1[0x46] = param_3;
      if (param_5 != 0) {
        param_5 = ((param_5 + 1) * 0x100 + -1) * 0x1000;
      }
      piVar1[0x3c] = param_5;
      piVar1[0x3e] = 0;
      iVar3 = PitchCompute__Fiiii(0x3c00000,0,piVar1[9],0);
      iVar2 = 0;
      do {
        piVar6 = (int *)(piVar1[1] + iVar2 * 0xc0);
        *piVar6 = *piVar1 + iVar2 * 0x154;
        *(byte *)(*piVar6 + 0x26) = *(byte *)(*piVar6 + 0x26) | 2;
        *(byte *)((int)piVar6 + 0x1a) = *(byte *)((int)piVar6 + 0x1a) | 2;
        piVar6[0x25] = 0xc01;
        if (*(short *)(piVar1 + 0xb) != 0) {
          piVar6[0x25] = piVar6[0x25] | 0x3000;
        }
        *(undefined4 *)(*piVar6 + 0xfc) = 1;
        piVar6[0x2c] = 0x8000;
        piVar6[1] = (int)(piVar1 + iVar2 * 0x18 + 0xc);
        piVar6[0x27] = iVar3;
        *(undefined4 *)(*piVar6 + 0x68) = *(undefined4 *)(DAT_8032f474 + 0xc);
        *(undefined4 *)(*piVar6 + 0x70) = 0;
        if (*(short *)((int)piVar1 + 0x2a) == 2) {
          if (iVar2 == 0) {
            piVar1[0x40] = 0;
            piVar1[0x42] = 0;
          }
          else {
            piVar1[0x40] = 0x7f000;
            piVar1[0x42] = 0;
          }
        }
        else {
          piVar1[0x40] = param_4 << 0xc;
          piVar1[0x42] = 0;
        }
        SetVoiceVolumeMix__FP12RedVoiceDATAii
                  (piVar1[1] + iVar2 * 0xc0,piVar1[0x40] >> 0xc,piVar1[0x3c] >> 0xc);
        *(int *)(*piVar1 + iVar2 * 0x154 + 0x11c) = piVar1[0x4b] + iVar2 * 0x2000;
        memset(piVar1 + iVar2 * 0x18 + 0xc,0,0x60);
        memcpy((void *)((int)piVar1 + iVar2 * 0x60 + 0x52),param_2 + 0x20 + iVar2 * 0x2e,0x2e);
        *(undefined *)((int)piVar6 + 0x5a) = 0;
        *(undefined *)((int)piVar6 + 0x59) = 0;
        *(undefined *)(piVar6 + 0x16) = 0;
        *(undefined *)((int)piVar6 + 0x5b) = 0x7f;
        *(undefined2 *)(piVar6 + 0x15) = 0;
        iVar5 = iVar2 + 1;
        *(undefined2 *)((int)piVar6 + 0x52) = 0;
        *(undefined2 *)(piVar6 + 0x14) = 0;
        *(undefined2 *)((int)piVar6 + 0x56) = 10;
        piVar1[iVar2 * 0x18 + 0xd] = 0;
        piVar1[iVar2 * 0x18 + 0xf] = 0x3fff;
        piVar1[iVar2 * 0x18 + 0xe] = 2;
        iVar2 = iVar5;
      } while (iVar5 < *(short *)((int)piVar1 + 0x2a));
      if (piVar1[8] < 0) {
        iVar2 = _ArrangeStreamDataNoLoop__FP13RedStreamDATAii(piVar1,0,0x2000);
      }
      else {
        iVar2 = _ArrangeStreamDataLoop__FP13RedStreamDATAii(piVar1,0,0x2000);
      }
      piVar1[0x45] = iVar2;
      piVar1[0x4a] = 0x1000;
      piVar1[0x44] = 3;
    }
  }
  return param_1;
}

