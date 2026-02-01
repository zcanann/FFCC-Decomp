// Function: __AI_SRC_INIT
// Entry: 8018f52c
// Size: 484 bytes

void __AI_SRC_INIT(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  
  lVar9 = 0;
  bVar1 = false;
  uVar7 = 0;
  uVar8 = 0;
LAB_8018f6c0:
  do {
    while( true ) {
      if (bVar1) {
        lVar9 = lVar9 + CONCAT44(uVar8,uVar7);
        do {
          uVar10 = OSGetTime();
        } while (((uint)((ulonglong)uVar10 >> 0x20) ^ 0x80000000) <
                 (uint)((uint)uVar10 < (uint)lVar9) +
                 ((uint)((ulonglong)lVar9 >> 0x20) ^ 0x80000000));
        return;
      }
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xffffffdf | 0x20;
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xfffffffd;
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xfffffffe | 1;
      iVar3 = DAT_cc006c08;
      do {
        iVar4 = DAT_cc006c08;
      } while (iVar3 == iVar4);
      uVar10 = OSGetTime();
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xfffffffd | 2;
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xfffffffe | 1;
      iVar3 = DAT_cc006c08;
      do {
        iVar4 = DAT_cc006c08;
      } while (iVar3 == iVar4);
      lVar9 = OSGetTime();
      uVar6 = (uint)lVar9 - (uint)uVar10;
      uVar2 = DAT_cc006c00;
      uVar5 = (int)((ulonglong)lVar9 >> 0x20) -
              ((uint)((uint)lVar9 < (uint)uVar10) + (int)((ulonglong)uVar10 >> 0x20)) ^ 0x80000000;
      DAT_cc006c00 = uVar2 & 0xfffffffd;
      uVar2 = DAT_cc006c00;
      DAT_cc006c00 = uVar2 & 0xfffffffe;
      if ((uint)(uVar6 < DAT_8032f17c - DAT_8032f19c) +
          (DAT_8032f178 - ((uint)(DAT_8032f17c < DAT_8032f19c) + DAT_8032f198) ^ 0x80000000) <=
          uVar5) break;
      bVar1 = true;
      uVar7 = DAT_8032f18c;
      uVar8 = DAT_8032f188;
    }
    if ((uint)(uVar6 < DAT_8032f17c + DAT_8032f19c) +
        (DAT_8032f178 + DAT_8032f198 + (uint)CARRY4(DAT_8032f17c,DAT_8032f19c) ^ 0x80000000) <=
        uVar5) {
      if (uVar5 < (uint)(uVar6 < DAT_8032f184 - DAT_8032f19c) +
                  (DAT_8032f180 - ((uint)(DAT_8032f184 < DAT_8032f19c) + DAT_8032f198) ^ 0x80000000)
         ) {
        bVar1 = true;
        uVar7 = DAT_8032f194;
        uVar8 = DAT_8032f190;
        goto LAB_8018f6c0;
      }
    }
    bVar1 = false;
  } while( true );
}

