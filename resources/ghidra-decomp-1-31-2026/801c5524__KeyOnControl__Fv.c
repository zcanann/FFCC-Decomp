// Function: _KeyOnControl__Fv
// Entry: 801c5524
// Size: 1304 bytes

void _KeyOnControl__Fv(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  int *piVar6;
  uint local_28;
  uint local_24;
  
  _VoiceEnvelopeCheck__Fv();
  local_24 = 0;
  local_28 = 0;
  piVar6 = DAT_8032f3fc;
  puVar1 = DAT_8032f444;
  if (DAT_8032f3f8 != 0) {
    do {
      if ((*piVar6 != 0) && (*(int *)(*piVar6 + 0x1c) != 0)) {
        puVar1 = (uint *)_VoiceDataSelect__FP12RedTrackDATAP11RedNoteDATAPi
                                   (*piVar6,piVar6 + 1,&local_28);
      }
      piVar6 = piVar6 + 2;
    } while ((puVar1 != (uint *)0x0) && (piVar6 < DAT_8032f3fc + 0x180));
  }
  puVar1 = DAT_8032f3f0;
  if ((*(short *)((int)DAT_8032f3f0 + 0x48e) != 0) && ((DAT_8032f3f0[0x11b] & 0x10) == 0)) {
    piVar6 = (int *)*DAT_8032f3f0;
    do {
      if ((*piVar6 != 0) && (piVar6[0x2d] != 0)) {
        iVar2 = piVar6[0x30];
        iVar3 = (*(code *)piVar6[0x2d])((uint)piVar6[0x32] >> 0xc);
        piVar6[0x33] = ((iVar2 >> 0xc) + 1) * iVar3 >> 0x10;
        piVar6[0x32] = piVar6[0x32] + piVar6[0x2e];
      }
      piVar6 = piVar6 + 0x55;
    } while (piVar6 < (int *)(*puVar1 + (uint)*(byte *)((int)puVar1 + 0x491) * 0x154));
  }
  puVar1 = DAT_8032f3f0;
  if ((*(short *)((int)DAT_8032f3f0 + 0x922) != 0) && ((DAT_8032f3f0[0x240] & 0x10) == 0)) {
    piVar6 = (int *)DAT_8032f3f0[0x125];
    puVar5 = DAT_8032f3f0 + 0x125;
    do {
      if ((*piVar6 != 0) && (piVar6[0x2d] != 0)) {
        iVar2 = piVar6[0x30];
        iVar3 = (*(code *)piVar6[0x2d])((uint)piVar6[0x32] >> 0xc);
        piVar6[0x33] = ((iVar2 >> 0xc) + 1) * iVar3 >> 0x10;
        piVar6[0x32] = piVar6[0x32] + piVar6[0x2e];
      }
      piVar6 = piVar6 + 0x55;
    } while (piVar6 < (int *)(*puVar5 + (uint)*(byte *)((int)puVar1 + 0x925) * 0x154));
  }
  puVar1 = DAT_8032f3f0 + 0x36f;
  piVar6 = (int *)DAT_8032f3f0[0x36f];
  do {
    if ((*piVar6 != 0) && (piVar6[0x2d] != 0)) {
      iVar2 = piVar6[0x30];
      iVar3 = (*(code *)piVar6[0x2d])((uint)piVar6[0x32] >> 0xc);
      piVar6[0x33] = ((iVar2 >> 0xc) + 1) * iVar3 >> 0x10;
      piVar6[0x32] = piVar6[0x32] + piVar6[0x2e];
    }
    piVar6 = piVar6 + 0x55;
    puVar5 = DAT_8032f444;
  } while (piVar6 < (int *)(*puVar1 + 0x2a80));
  do {
    if (((puVar5[0x23] != 0) && (*puVar5 != 0)) && ((*(uint *)(*puVar5 + 0xfc) & 9) == 0)) {
      if ((((puVar5[0x2e] & 2) != 0) || (*(int *)(*puVar5 + 0x94) != 0)) ||
         (*(int *)(*puVar5 + 0xb4) != 0)) {
        if ((*puVar5 < *DAT_8032f3f0) ||
           (*DAT_8032f3f0 + (uint)*(byte *)((int)DAT_8032f3f0 + 0x491) * 0x154 <= *puVar5)) {
          iVar2 = DAT_8032f434;
          if ((DAT_8032f3f0[0x125] <= *puVar5) &&
             (*puVar5 < DAT_8032f3f0[0x125] + (uint)*(byte *)((int)DAT_8032f3f0 + 0x925) * 0x154)) {
            uVar4 = (uint)*(char *)(*puVar5 + 0x14e);
            iVar2 = (int)*(char *)(*puVar5 + 0x14e) >> 0x1f;
            if ((1 << (iVar2 * 0x20 | (uint)(*(char *)(*puVar5 + 0x14e) * 0x8000000 + iVar2) >> 0x1b
                      ) - iVar2 &
                (&DAT_8032f478)[((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)])
                == 0) {
              iVar2 = (*(char *)((int)DAT_8032f3f0 + 0x926) + 1) * ((int)DAT_8032f3f0[300] >> 0xc)
                      >> 7;
              if (DAT_8032f3f0[0x23c] != 0) {
                iVar2 = iVar2 * ((int)DAT_8032f3f0[0x23a] >> 0xc) >> 9;
              }
              iVar2 = iVar2 * DAT_8032f430 >> 9;
            }
            else {
              iVar2 = 0;
            }
          }
        }
        else {
          uVar4 = (uint)*(char *)(*puVar5 + 0x14e);
          iVar2 = (int)*(char *)(*puVar5 + 0x14e) >> 0x1f;
          if ((1 << (iVar2 * 0x20 | (uint)(*(char *)(*puVar5 + 0x14e) * 0x8000000 + iVar2) >> 0x1b)
                    - iVar2 &
              (&DAT_8032f478)[((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)]) ==
              0) {
            iVar2 = (*(char *)((int)DAT_8032f3f0 + 0x492) + 1) * ((int)DAT_8032f3f0[7] >> 0xc) >> 7;
            if (DAT_8032f3f0[0x117] != 0) {
              iVar2 = iVar2 * ((int)DAT_8032f3f0[0x115] >> 0xc) >> 9;
            }
            iVar2 = iVar2 * DAT_8032f430 >> 9;
          }
          else {
            iVar2 = 0;
          }
        }
        _VolumeExecute__FP12RedVoiceDATAi(puVar5,iVar2);
      }
      if ((puVar5[0x2e] & 1) != 0 || *(int *)(*puVar5 + 0x74) != 0) {
        _PitchExecute__FP12RedVoiceDATA(puVar5);
      }
      puVar5[0x2e] = 0;
    }
    puVar5 = puVar5 + 0x30;
  } while (puVar5 < DAT_8032f444 + 0xc00);
  uVar4 = 1;
  puVar1 = DAT_8032f444;
  do {
    if ((local_28 & uVar4) != 0) {
      local_28 = local_28 & ~uVar4;
      puVar1[0x24] = puVar1[0x24] | 1;
    }
    uVar4 = uVar4 << 1;
    puVar1 = puVar1 + 0x30;
  } while (local_28 != 0);
  uVar4 = 1;
  puVar1 = DAT_8032f444 + 0x600;
  do {
    if ((local_24 & uVar4) != 0) {
      local_24 = local_24 & ~uVar4;
      puVar1[0x24] = puVar1[0x24] | 1;
    }
    uVar4 = uVar4 << 1;
    puVar1 = puVar1 + 0x30;
  } while (local_24 != 0);
  return;
}

