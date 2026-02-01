// Function: GetTypeCallback
// Entry: 801851a8
// Size: 664 bytes

void GetTypeCallback(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  
  iVar7 = param_1 * 4;
  puVar8 = (uint *)(&DAT_80217318 + iVar7);
  *puVar8 = *puVar8 & 0xffffff7f;
  *puVar8 = *puVar8 | param_2;
  uVar10 = __OSGetSystemTime();
  *(undefined8 *)(&DAT_8030c870 + param_1 * 8) = uVar10;
  uVar6 = *puVar8;
  uVar1 = DAT_8032f008 & ~(0x80000000U >> param_1);
  uVar4 = DAT_8032f008 & 0x80000000U >> param_1;
  DAT_8032f008 = uVar1;
  if (((((param_2 & 0xf) == 0) && ((uVar6 & 0x18000000) == 0x8000000)) &&
      ((uVar6 & 0x80000000) != 0)) && ((uVar6 & 0x4000000) == 0)) {
    iVar2 = OSGetWirelessID(param_1);
    uVar1 = iVar2 << 8;
    uVar5 = uVar1 & 0xffff00;
    if ((uVar4 == 0) || ((uVar1 & 0x100000) == 0)) {
      if ((uVar6 & 0x100000) == 0) {
        if ((uVar6 & 0x40000000) != 0) {
          OSSetWirelessID(param_1,(uVar6 & 0xcfff00 | 0x100000) >> 8);
          *(uint *)(&DAT_8030c940 + iVar7) = uVar6 & 0xcfff00 | 0x4e100000;
          *puVar8 = 0x80;
          SITransfer(param_1,&DAT_8030c940 + iVar7,3,puVar8,3,GetTypeCallback,0,0);
          return;
        }
        OSSetWirelessID(param_1,0);
      }
      else if ((uVar1 & 0xcfff00) != (uVar6 & 0xcfff00)) {
        if ((uVar1 & 0x100000) == 0) {
          uVar5 = uVar6 & 0xcfff00 | 0x100000;
          OSSetWirelessID(param_1,(uVar6 & 0xcfff00 | 0x100000) >> 8);
        }
        *(uint *)(&DAT_8030c940 + iVar7) = uVar5 | 0x4e000000;
        *puVar8 = 0x80;
        SITransfer(param_1,&DAT_8030c940 + iVar7,3,puVar8,3,GetTypeCallback,0,0);
        return;
      }
      uVar1 = *puVar8;
      iVar7 = 0;
      puVar9 = (undefined4 *)(&DAT_8030c8b0 + param_1 * 0x10);
      do {
        pcVar3 = (code *)*puVar9;
        if (pcVar3 != (code *)0x0) {
          *puVar9 = 0;
          (*pcVar3)(param_1,uVar1);
        }
        iVar7 = iVar7 + 1;
        puVar9 = puVar9 + 1;
      } while (iVar7 < 4);
    }
    else {
      *(uint *)(&DAT_8030c940 + iVar7) = uVar1 & 0xcfff00 | 0x4e100000;
      *puVar8 = 0x80;
      SITransfer(param_1,&DAT_8030c940 + iVar7,3,puVar8,3,GetTypeCallback,0,0);
    }
  }
  else {
    OSSetWirelessID(param_1,0);
    uVar1 = *puVar8;
    iVar7 = 0;
    puVar9 = (undefined4 *)(&DAT_8030c8b0 + param_1 * 0x10);
    do {
      pcVar3 = (code *)*puVar9;
      if (pcVar3 != (code *)0x0) {
        *puVar9 = 0;
        (*pcVar3)(param_1,uVar1);
      }
      iVar7 = iVar7 + 1;
      puVar9 = puVar9 + 1;
    } while (iVar7 < 4);
  }
  return;
}

