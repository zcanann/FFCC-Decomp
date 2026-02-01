// Function: SaveScript__5CGameFPc
// Entry: 8001462c
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SaveScript__5CGameFPc(CGame *game,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  memset(param_2,0,0x800);
  iVar1 = 0;
  iVar2 = 0;
  iVar3 = 0;
  while( true ) {
    if ((int)CFlat._4_4_ <= iVar3) break;
    if ((*(byte *)(CFlat._8_4_ + iVar2 + 1) & 0x20) != 0) {
      *(undefined4 *)(param_2 + iVar1) = *(undefined4 *)(CFlat._12_4_ + iVar2);
      iVar1 = iVar1 + 4;
    }
    iVar2 = iVar2 + 4;
    iVar3 = iVar3 + 1;
  }
  return;
}

