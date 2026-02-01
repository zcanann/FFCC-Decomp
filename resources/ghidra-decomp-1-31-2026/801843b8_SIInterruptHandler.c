// Function: SIInterruptHandler
// Entry: 801843b8
// Size: 836 bytes

void SIInterruptHandler(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  bool bVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint *puVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  undefined8 uVar12;
  
  uVar6 = DAT_80217304;
  uVar1 = DAT_cc006434;
  if ((uVar1 & 0xc0000000) == 0xc0000000) {
    uVar4 = CompleteTransfer();
    pcVar3 = DAT_80217314;
    iVar11 = 0;
    DAT_80217314 = (code *)0x0;
    uVar10 = uVar6;
    do {
      uVar10 = uVar10 + 1;
      uVar10 = uVar10 + (((int)uVar10 >> 2) + (uint)((int)uVar10 < 0 && (uVar10 & 3) != 0)) * -4;
      piVar9 = FatalContext + uVar10 * 8 + 0x2c7;
      if ((*piVar9 != -1) &&
         (uVar12 = __OSGetSystemTime(),
         (uint)((uint)uVar12 < (uint)(&DAT_8030c76c)[uVar10 * 8]) +
         ((&DAT_8030c768)[uVar10 * 8] ^ 0x80000000) <=
         ((uint)((ulonglong)uVar12 >> 0x20) ^ 0x80000000))) {
        iVar11 = __SITransfer(*piVar9,(&DAT_8030c754)[uVar10 * 8],(&DAT_8030c758)[uVar10 * 8],
                              (&DAT_8030c75c)[uVar10 * 8],(&DAT_8030c760)[uVar10 * 8],
                              (&DAT_8030c764)[uVar10 * 8]);
        if (iVar11 != 0) {
          OSCancelAlarm(&DAT_8030c7d0 + uVar10 * 0x28);
          *piVar9 = -1;
        }
        break;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 4);
    if (pcVar3 != (code *)0x0) {
      (*pcVar3)(uVar6,uVar4,param_2);
    }
    uVar10 = DAT_cc006438;
    DAT_cc006438 = uVar10 & 0xf000000 >> ((uVar6 & 7) << 3);
    if (*(int *)(&DAT_80217318 + uVar6 * 4) == 0x80) {
      bVar2 = true;
      if ((FatalContext[uVar6 * 8 + 0x2c7] == -1) && (DAT_80217304 != uVar6)) {
        bVar2 = false;
      }
      if (!bVar2) {
        SITransfer(uVar6,&DAT_8032f000,1,&DAT_80217318 + uVar6 * 4,3,GetTypeCallback,0,
                   (DAT_800000f8 / 500000) * 0x41 >> 3);
      }
    }
  }
  if ((uVar1 & 0x18000000) == 0x18000000) {
    iVar11 = VIGetCurrentLine();
    puVar8 = (uint *)&DAT_8030c930;
    uVar6 = iVar11 + 1;
    uVar1 = DAT_80217308 >> 0x10;
    iVar11 = 0;
    do {
      iVar5 = SIGetResponseRaw(iVar11);
      if (iVar5 != 0) {
        *puVar8 = uVar6;
      }
      iVar11 = iVar11 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar11 < 4);
    uVar1 = (uVar1 & 0x3ff) >> 1;
    if ((((((DAT_80217308 & 0x80) == 0) || ((DAT_8030c930 != 0 && (uVar6 <= uVar1 + DAT_8030c930))))
         && (((DAT_80217308 & 0x40) == 0 || ((DAT_8030c934 != 0 && (uVar6 <= uVar1 + DAT_8030c934)))
             ))) &&
        (((DAT_80217308 & 0x20) == 0 || ((DAT_8030c938 != 0 && (uVar6 <= uVar1 + DAT_8030c938))))))
       && (((DAT_80217308 & 0x10) == 0 || ((DAT_8030c93c != 0 && (uVar6 <= uVar1 + DAT_8030c93c)))))
       ) {
      iVar11 = 0;
      DAT_8030c930 = 0;
      puVar7 = &DAT_8030c8f0;
      DAT_8030c934 = 0;
      DAT_8030c938 = 0;
      DAT_8030c93c = 0;
      do {
        if ((code *)*puVar7 != (code *)0x0) {
          (*(code *)*puVar7)(param_1,param_2);
        }
        iVar11 = iVar11 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar11 < 4);
    }
  }
  return;
}

