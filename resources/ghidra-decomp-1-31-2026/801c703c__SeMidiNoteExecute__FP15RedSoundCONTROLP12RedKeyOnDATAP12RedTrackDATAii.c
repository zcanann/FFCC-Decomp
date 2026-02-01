// Function: _SeMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATAii
// Entry: 801c703c
// Size: 572 bytes

int _SeMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATAii
              (int *param_1,undefined4 param_2,int *param_3,int param_4,short param_5)

{
  int iVar1;
  int iVar2;
  char cVar3;
  byte *pbVar4;
  
  do {
    if ((*param_3 != 0) && ((param_3[0x3f] & 8U) == 0)) {
      *(short *)((int)param_3 + 0x146) = *(short *)((int)param_3 + 0x146) + param_5 * -0x78;
      while (*(short *)((int)param_3 + 0x146) < 1) {
        *(short *)((int)param_3 + 0x146) = *(short *)((int)param_3 + 0x146) + 0xfa;
        iVar2 = param_4;
        if (param_3[0x42] < param_4) {
          iVar2 = param_3[0x42];
        }
        param_3[0x42] = param_3[0x42] - param_4;
        _SeTrackDataExecute__FP12RedTrackDATAi(param_3,iVar2);
        if (((param_3[0x41] & 0x200000U) == 0) && (param_3[0x42] == 1)) {
          KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2,param_3);
        }
        DAT_8032f4b4 = 0;
        while ((*param_3 != 0 && (param_3[0x42] < 1))) {
          *(short *)(param_3 + 0x51) = *(short *)(param_3 + 0x51) + 1;
          pbVar4 = (byte *)*param_3;
          *param_3 = (int)(pbVar4 + 1);
          (*(code *)(&
                    PTR___MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA_8021ea10)
                    [*pbVar4])(param_1,param_2,param_3);
          if (*param_3 != 0) {
            iVar2 = DeltaTimeSumup__FPPUc(param_3);
            if (iVar2 != 0) {
              iVar2 = iVar2 + *(short *)(param_3 + 0x4e);
              if (iVar2 < 1) {
                iVar2 = 1;
              }
              else if ((param_3[0x3f] & 0x20000U) != 0) {
                iVar1 = param_3[0x3b];
                cVar3 = GetRandomData__Fv();
                iVar2 = iVar2 + ((iVar2 * iVar1 >> 8) * (int)cVar3 >> 7);
                if (iVar2 < 1) {
                  iVar2 = 1;
                }
              }
            }
            if (param_3[0x42] < -1) {
              iVar1 = iVar2;
              if (0 < param_3[0x42] + iVar2) {
                iVar1 = -param_3[0x42];
              }
              _SeTrackDataExecute__FP12RedTrackDATAi(param_3,iVar1);
            }
            param_3[0x42] = param_3[0x42] + iVar2;
          }
        }
        if (DAT_8032f4b4 != 0) {
          *(int *)(DAT_8032f444 + *(char *)((int)param_3 + 0x14e) * 0xc0 + 0xb8) = DAT_8032f4b4;
        }
      }
    }
    param_3 = param_3 + 0x55;
  } while (param_3 < (int *)(*param_1 + 0x2a80));
  param_1[0x11d] = 1;
  return (int)*(short *)((int)param_1 + 0x48e);
}

