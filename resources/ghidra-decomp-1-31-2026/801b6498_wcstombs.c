// Function: wcstombs
// Entry: 801b6498
// Size: 280 bytes

uint wcstombs(int param_1,ushort *param_2,uint param_3)

{
  ushort uVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_28;
  byte local_24 [16];
  
  uVar6 = 0;
  if ((param_1 == 0) || (param_2 == (ushort *)0x0)) {
    uVar6 = 0;
  }
  else {
    for (; uVar6 <= param_3; uVar6 = uVar6 + uVar5) {
      uVar1 = *param_2;
      uVar4 = (uint)uVar1;
      if (uVar4 == 0) {
        *(undefined *)(param_1 + uVar6) = 0;
        return uVar6;
      }
      param_2 = param_2 + 1;
      local_28 = DAT_80333938;
      if (uVar4 < 0x80) {
        uVar5 = 1;
      }
      else if (uVar4 < 0x800) {
        uVar5 = 2;
      }
      else {
        uVar5 = 3;
      }
      pbVar3 = local_24 + uVar5;
      if (uVar5 == 2) {
LAB_801b6550:
        bVar2 = (byte)uVar4;
        uVar4 = uVar4 >> 6;
        pbVar3 = pbVar3 + -1;
        *pbVar3 = bVar2 & 0x3f | 0x80;
LAB_801b6560:
        pbVar3[-1] = (byte)uVar4 | local_24[uVar5 - 4];
      }
      else if (uVar5 < 2) {
        if (uVar5 != 0) goto LAB_801b6560;
      }
      else if (uVar5 < 4) {
        uVar4 = (uint)(uVar1 >> 6);
        pbVar3 = local_24 + (uVar5 - 1);
        *pbVar3 = (byte)uVar1 & 0x3f | 0x80;
        goto LAB_801b6550;
      }
      if (param_3 < uVar6 + uVar5) {
        return uVar6;
      }
      strncpy(param_1 + uVar6,local_24,uVar5);
    }
  }
  return uVar6;
}

