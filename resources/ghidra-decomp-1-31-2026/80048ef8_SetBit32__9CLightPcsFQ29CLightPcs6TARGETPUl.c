// Function: SetBit32__9CLightPcsFQ29CLightPcs6TARGETPUl
// Entry: 80048ef8
// Size: 232 bytes

void SetBit32__9CLightPcsFQ29CLightPcs6TARGETPUl(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 local_28 [4];
  
  iVar2 = param_1 + 0x63c;
  uVar1 = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0xb4) = 0;
  do {
    if (*(uint *)(param_1 + 0xb8) <= uVar1) {
      return;
    }
    if ((*(char *)(param_2 + iVar2 + 0x60) != '\0') &&
       ((1 << (uVar1 & 0x1f) & *(uint *)(param_3 + (uVar1 >> 3 & 0x1ffffffc))) != 0)) {
      local_28[0] = *(undefined4 *)(param_2 * 4 + iVar2 + 0x50);
      GXInitLightColor(iVar2 + 0x6c,local_28);
      GXLoadLightObjImm(iVar2 + 0x6c,1 << *(int *)(param_1 + 0xb0));
      *(uint *)(param_1 + 0xb4) = *(uint *)(param_1 + 0xb4) | 1 << *(int *)(param_1 + 0xb0);
      *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + 1;
      if (7 < *(uint *)(param_1 + 0xb0)) {
        return;
      }
    }
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 0xb0;
  } while( true );
}

