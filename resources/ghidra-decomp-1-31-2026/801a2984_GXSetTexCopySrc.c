// Function: GXSetTexCopySrc
// Entry: 801a2984
// Size: 144 bytes

void GXSetTexCopySrc(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(undefined4 *)(DAT_80333828 + 0x1f0) = 0;
  *(uint *)(iVar1 + 0x1f0) = *(uint *)(iVar1 + 0x1f0) & 0xfffffc00 | param_1 & 0xffff;
  *(uint *)(iVar1 + 0x1f0) = *(uint *)(iVar1 + 0x1f0) & 0xfff003ff | (param_2 & 0xffff) << 10;
  *(uint *)(iVar1 + 0x1f0) = *(uint *)(iVar1 + 0x1f0) & 0xffffff | 0x49000000;
  *(undefined4 *)(iVar1 + 500) = 0;
  *(uint *)(iVar1 + 500) = *(uint *)(iVar1 + 500) & 0xfffffc00 | (param_3 & 0xffff) - 1;
  *(uint *)(iVar1 + 500) = *(uint *)(iVar1 + 500) & 0xfff003ff | ((param_4 & 0xffff) - 1) * 0x400;
  *(uint *)(iVar1 + 500) = *(uint *)(iVar1 + 500) & 0xffffff | 0x4a000000;
  return;
}

