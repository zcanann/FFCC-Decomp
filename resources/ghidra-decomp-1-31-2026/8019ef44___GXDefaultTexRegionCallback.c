// Function: __GXDefaultTexRegionCallback
// Entry: 8019ef44
// Size: 124 bytes

int __GXDefaultTexRegionCallback(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = GXGetTexObjFmt();
  iVar1 = DAT_80333828;
  if (((iVar2 == 8) || (iVar2 == 9)) || (iVar2 == 10)) {
    uVar3 = *(uint *)(DAT_80333828 + 0x2cc);
    *(uint *)(DAT_80333828 + 0x2cc) = uVar3 + 1;
    iVar2 = (uVar3 & 3) * 0x10 + 0x288;
  }
  else {
    uVar3 = *(uint *)(DAT_80333828 + 0x2c8);
    *(uint *)(DAT_80333828 + 0x2c8) = uVar3 + 1;
    iVar2 = (uVar3 & 7) * 0x10 + 0x208;
  }
  return iVar1 + iVar2;
}

