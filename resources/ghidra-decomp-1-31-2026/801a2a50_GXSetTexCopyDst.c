// Function: GXSetTexCopyDst
// Entry: 801a2a50
// Size: 340 bytes

void GXSetTexCopyDst(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  int local_18;
  undefined auStack_14 [4];
  int local_10 [2];
  
  uVar5 = param_3 & 0xf;
  *(undefined *)(DAT_80333828 + 0x200) = 0;
  if (param_3 == 0x13) {
    uVar5 = 0xb;
  }
  if ((param_3 == 0x26) || ((((int)param_3 < 0x26 && ((int)param_3 < 4)) && (-1 < (int)param_3)))) {
    *(uint *)(DAT_80333828 + 0x1fc) = *(uint *)(DAT_80333828 + 0x1fc) & 0xfffe7fff | 0x18000;
  }
  else {
    *(uint *)(DAT_80333828 + 0x1fc) = *(uint *)(DAT_80333828 + 0x1fc) & 0xfffe7fff | 0x10000;
  }
  iVar1 = DAT_80333828;
  uVar2 = countLeadingZeros((param_3 & 0x10) - 0x10);
  *(char *)(DAT_80333828 + 0x200) = (char)(uVar2 >> 5);
  *(uint *)(iVar1 + 0x1fc) = uVar5 & 8 | *(uint *)(iVar1 + 0x1fc) & 0xfffffff7;
  __GetImageTileCount(param_3,param_1,param_2,local_10,auStack_14,&local_18);
  iVar1 = DAT_80333828;
  *(undefined4 *)(DAT_80333828 + 0x1f8) = 0;
  puVar3 = (uint *)(iVar1 + 0x1f8);
  puVar4 = (uint *)(iVar1 + 0x1fc);
  *puVar3 = *puVar3 & 0xfffffc00 | local_10[0] * local_18;
  *puVar3 = *puVar3 & 0xffffff | 0x4d000000;
  *puVar4 = *puVar4 & 0xfffffdff | (param_4 & 0xff) << 9;
  *puVar4 = *puVar4 & 0xffffff8f | (uVar5 & 7) << 4;
  return;
}

