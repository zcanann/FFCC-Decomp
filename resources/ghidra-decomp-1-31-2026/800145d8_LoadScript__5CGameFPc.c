// Function: LoadScript__5CGameFPc
// Entry: 800145d8
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadScript__5CGameFPc(CGame *game,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar3 = 0;
  iVar4 = 0;
  while( true ) {
    if ((int)CFlat._4_4_ <= iVar4) break;
    if ((*(byte *)(CFlat._8_4_ + iVar3 + 1) & 0x20) != 0) {
      puVar1 = (undefined4 *)(param_2 + iVar2);
      iVar2 = iVar2 + 4;
      *(undefined4 *)(CFlat._12_4_ + iVar3) = *puVar1;
    }
    iVar3 = iVar3 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}

