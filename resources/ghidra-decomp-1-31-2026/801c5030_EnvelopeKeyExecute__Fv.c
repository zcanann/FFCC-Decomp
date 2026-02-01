// Function: EnvelopeKeyExecute__Fv
// Entry: 801c5030
// Size: 1268 bytes

void EnvelopeKeyExecute__Fv(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  
  piVar8 = DAT_8032f444;
  do {
    if (piVar8[0x23] == 0) {
      piVar8[0x2c] = 0;
      piVar8[1] = 0;
      iVar1 = piVar8[5];
      if (iVar1 != 0) {
        if (*(short *)(iVar1 + 0x146) == 0) {
          if (*(int *)(iVar1 + 0xc) != 0) {
            AXFreeVoice(iVar1);
          }
          piVar8[5] = 0;
          *piVar8 = 0;
        }
        else {
          *(undefined2 *)(iVar1 + 0x146) = 0;
          *(undefined2 *)(iVar1 + 0x19c) = 0;
          *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 0x204;
        }
      }
    }
    else {
      if ((piVar8[0x24] & 1U) != 0) {
        if ((piVar8[5] != 0) && (*(int *)(piVar8[5] + 0xc) != 0)) {
          AXFreeVoice(piVar8[5]);
          piVar8[5] = 0;
        }
        if ((*(byte *)((int)piVar8 + 0x1a) & 3) == 0) {
          iVar1 = ((int)piVar8 - (int)DAT_8032f444) / 0xc0 +
                  ((int)piVar8 - (int)DAT_8032f444 >> 0x1f);
          iVar1 = (0x40 - (iVar1 - (iVar1 >> 0x1f)) >> 1) + -1;
          if (iVar1 < 1) {
            iVar1 = 1;
          }
          iVar1 = AXAcquireVoice(iVar1,_VoiceDropedCallback__FPv,0);
          piVar8[5] = iVar1;
        }
        else {
          iVar1 = AXAcquireVoice(0x1f,_VoiceDropedCallback__FPv,0);
          piVar8[5] = iVar1;
        }
      }
      iVar1 = piVar8[5];
      if (iVar1 == 0) {
        piVar8[0x24] = 0;
        piVar8[0x23] = 0;
        return;
      }
      uVar6 = 0;
      uVar4 = 0;
      if ((piVar8[0x24] & 0x10U) != 0) {
        iVar3 = piVar8[0x27];
        uVar6 = 0x80000;
        *(ushort *)(iVar1 + 0x1de) = (ushort)((uint)iVar3 >> 0x10) & 3;
        *(short *)(iVar1 + 0x1e0) = (short)iVar3;
      }
      if ((piVar8[0x24] & 8U) != 0) {
        if ((piVar8[0x25] & 8U) == 0) {
          memcpy((void *)(iVar1 + 0x14a),piVar8 + 0x1a,0x24);
        }
        else {
          memset(iVar1 + 0x14a,0,0x24);
        }
        *(undefined2 *)(iVar1 + 0x144) = 3;
        if ((piVar8[0x25] & 0x3000U) != 0) {
          if ((piVar8[0x25] & 2U) == 0) {
            *(ushort *)(iVar1 + 0x144) = *(ushort *)(iVar1 + 0x144) | 0x600;
          }
          else {
            *(ushort *)(iVar1 + 0x144) = *(ushort *)(iVar1 + 0x144) | 0x30;
          }
        }
        uVar6 = uVar6 | 0x12;
      }
      if (((piVar8[0x25] & 8U) == 0) && ((piVar8[0x24] & 0x20U) != 0)) {
        _AdsrStart__FP12RedVoiceDATA(piVar8);
        uVar4 = 1;
      }
      if ((piVar8[0x24] & 1U) == 0) {
        if ((piVar8[0x24] & 2U) == 0) {
          if ((piVar8[0x25] & 8U) == 0) {
            if ((piVar8[0x24] & 0x20U) == 0) {
              uVar2 = _AdsrDataExecute__FP12RedVoiceDATA(piVar8);
              uVar4 = uVar4 | uVar2;
              piVar8[0x2c] = piVar8[0x2b] >> 0xc;
            }
            piVar8[0x24] = piVar8[0x24] & 0xffffffdf;
          }
        }
        else {
          piVar8[0x24] = piVar8[0x24] | 4;
          piVar8[0x17] = 3;
          piVar8[0x18] = (uint)*(ushort *)((int)piVar8 + 0x56);
          if (piVar8[0x18] == 0) {
            piVar8[0x2b] = 0;
          }
          else {
            piVar8[0x19] = -piVar8[0x2b];
            piVar8[0x19] = piVar8[0x19] / piVar8[0x18];
          }
          piVar8[0x2c] = piVar8[0x2b] >> 0xc;
        }
      }
      else {
        piVar8[0x24] = piVar8[0x24] & 0xfffffffb;
        iVar5 = piVar8[1];
        iVar3 = *piVar8;
        if ((iVar5 == 0) || (iVar3 == 0)) {
          piVar8[0x23] = 0;
        }
        else {
          uVar4 = uVar4 + 1;
          *(ushort *)(iVar1 + 0x148) = (ushort)((piVar8[0x25] & 1U) != 0);
          *(undefined2 *)(iVar1 + 0x140) = 1;
          *(undefined2 *)(iVar1 + 0x146) = 1;
          memcpy((void *)(iVar1 + 0x1b6),iVar5 + 0x22,0x28);
          memcpy((void *)(iVar1 + 0x1ec),iVar5 + 0x4a,6);
          memset(iVar1 + 0x1e4,0,8);
          *(undefined2 *)(iVar1 + 0x1a8) = 0;
          iVar3 = (*(int *)(iVar3 + 0x11c) + *(int *)(iVar5 + 4) + 1) * 2;
          iVar7 = iVar3 + -2;
          *(int *)(iVar1 + 0x1b2) = iVar3;
          if (*(int *)(iVar5 + 8) < 0) {
            *(undefined2 *)(iVar1 + 0x1a6) = 0;
            iVar3 = iVar7;
          }
          else {
            *(undefined2 *)(iVar1 + 0x1a6) = 1;
            iVar3 = iVar7 + *(int *)(iVar5 + 8);
          }
          *(short *)(iVar1 + 0x1aa) = (short)((uint)iVar3 >> 0x10);
          *(short *)(iVar1 + 0x1ac) = (short)iVar3;
          uVar6 = uVar6 | 0x16100d;
          *(int *)(iVar1 + 0x1ae) = iVar7 + *(int *)(iVar5 + 0xc);
          piVar8[0x24] = piVar8[0x24] | 0x20;
          piVar8[0x2c] = 0x8000;
          piVar8[0x2b] = 0;
        }
      }
      if (piVar8[0x2c] < 1) {
        piVar8[0x24] = piVar8[0x24] & 0xfffffffb;
        piVar8[0x23] = 0;
        uVar6 = uVar6 | 0x204;
        *piVar8 = 0;
        *(undefined2 *)(iVar1 + 0x146) = 0;
        piVar8[0x2b] = 0;
        piVar8[0x2c] = 0;
        *(undefined2 *)(iVar1 + 0x19c) = 0;
        *(undefined2 *)(iVar1 + 0x19e) = 0;
      }
      else if ((uVar4 != 0) && ((uint)*(ushort *)(iVar1 + 0x19c) != (piVar8[0x2b] >> 0xc & 0xffffU))
              ) {
        uVar6 = uVar6 | 0x200;
        *(undefined2 *)(iVar1 + 0x19e) = 0;
        *(short *)(iVar1 + 0x19c) = (short)(piVar8[0x2b] >> 0xc);
      }
      *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | uVar6;
    }
    piVar8[0x24] = piVar8[0x24] & 0xfffffc24;
    piVar8 = piVar8 + 0x30;
    if (DAT_8032f444 + 0xc00 <= piVar8) {
      return;
    }
  } while( true );
}

