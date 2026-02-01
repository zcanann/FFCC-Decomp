// Function: RedNew__Fi
// Entry: 801bff80
// Size: 360 bytes

int RedNew__Fi(int param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  
  if (((0 < param_1) && (DAT_8032f4a0 != (int *)0x0)) && (DAT_8032f490 != 0)) {
    uVar4 = OSDisableInterrupts();
    uVar2 = param_1 + 0x1fU & 0xffffffe0;
    iVar5 = DAT_8032f490;
    piVar7 = DAT_8032f4a0;
    do {
      if ((piVar7[1] == 0) || ((int)(iVar5 + uVar2) <= *piVar7)) {
        if (DAT_8032f4a0[0x7ff] < 1) {
          if (iVar5 + uVar2 <= (uint)(DAT_8032f490 + DAT_8032f498)) {
            if (0 < piVar7[1]) {
              uVar3 = (int)DAT_8032f4a0 + (0x2000 - (int)(piVar7 + 2));
              iVar6 = ((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0);
              if (0 < iVar6) {
                memmove(piVar7 + 2,piVar7,iVar6 * 8);
              }
            }
            *piVar7 = iVar5;
            piVar7[1] = uVar2;
            OSRestoreInterrupts(uVar4);
            return iVar5;
          }
        }
        else if (DAT_8032f408 != 0) {
          OSReport(s__s_sMemory_Bank_Full____s_801e7888,&DAT_801e78a3,&DAT_80333d20,&DAT_80333d28);
          fflush(&DAT_8021d1a8);
        }
        break;
      }
      iVar5 = *piVar7;
      piVar1 = piVar7 + 1;
      piVar7 = piVar7 + 2;
      iVar5 = iVar5 + *piVar1;
    } while (piVar7 < DAT_8032f4a0 + 0x800);
    OSRestoreInterrupts(uVar4);
  }
  return 0;
}

