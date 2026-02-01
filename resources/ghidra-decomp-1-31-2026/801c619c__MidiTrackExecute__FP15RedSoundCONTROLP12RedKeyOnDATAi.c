// Function: _MidiTrackExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi
// Entry: 801c619c
// Size: 552 bytes

void _MidiTrackExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi
               (int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  int *piVar6;
  
  piVar6 = (int *)*param_1;
  do {
    if (*piVar6 != 0) {
      DAT_8032f4b4 = 0;
      iVar2 = param_3;
      if (piVar6[0x42] < param_3) {
        iVar2 = piVar6[0x42];
      }
      piVar6[0x42] = piVar6[0x42] - param_3;
      _MusicTrackDataExecute__FP12RedTrackDATAi(piVar6,iVar2);
      if (((piVar6[0x41] & 0x200000U) == 0) && (piVar6[0x42] == 1)) {
        KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2,piVar6);
      }
      while ((*piVar6 != 0 && (piVar6[0x42] < 1))) {
        pbVar4 = (byte *)*piVar6;
        *piVar6 = (int)(pbVar4 + 1);
        (*(code *)(&PTR___MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA_8021ea10)
                  [*pbVar4])(param_1,param_2,piVar6);
        if (*piVar6 != 0) {
          if (piVar6[0x42] < 1) {
            iVar2 = DeltaTimeSumup__FPPUc(piVar6);
          }
          else {
            iVar2 = piVar6[0x42];
            piVar6[0x42] = 0;
          }
          if (iVar2 != 0) {
            iVar2 = iVar2 + *(short *)(piVar6 + 0x4e);
            if (iVar2 < 1) {
              iVar2 = 1;
            }
            else if ((piVar6[0x3f] & 0x20000U) != 0) {
              iVar1 = piVar6[0x3b];
              cVar3 = GetRandomData__Fv();
              iVar2 = iVar2 + ((iVar2 * iVar1 >> 8) * (int)cVar3 >> 7);
              if (iVar2 < 1) {
                iVar2 = 1;
              }
            }
          }
          if (piVar6[0x42] < -1) {
            iVar1 = iVar2;
            if (0 < piVar6[0x42] + iVar2) {
              iVar1 = -piVar6[0x42];
            }
            _MusicTrackDataExecute__FP12RedTrackDATAi(piVar6,iVar1);
          }
          piVar6[0x42] = piVar6[0x42] + iVar2;
        }
      }
      puVar5 = DAT_8032f444;
      if (DAT_8032f4b4 != 0) {
        do {
          if ((int *)*puVar5 == piVar6) {
            puVar5[0x2e] = DAT_8032f4b4;
          }
          puVar5 = puVar5 + 0x30;
        } while (puVar5 < DAT_8032f444 + 0xc00);
      }
    }
    piVar6 = piVar6 + 0x55;
  } while ((*(short *)((int)param_1 + 0x48e) != 0) &&
          (piVar6 < (int *)(*param_1 + (uint)*(byte *)((int)param_1 + 0x491) * 0x154)));
  return;
}

