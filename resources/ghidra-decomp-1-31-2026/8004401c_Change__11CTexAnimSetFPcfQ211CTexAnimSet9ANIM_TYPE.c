// Function: Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE
// Entry: 8004401c
// Size: 208 bytes

void Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE
               (double param_1,CTexAnimSet *texAnimSet,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  do {
    uVar4 = GetSize__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size);
    if (uVar4 <= uVar5) {
      return;
    }
    iVar1 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar5);
    for (uVar4 = 0;
        uVar3 = GetSize__25CPtrArray<P11CTexAnimSeq>Fv((CPtrArray *)(*(int *)(iVar1 + 8) + 0x110)),
        uVar4 < uVar3; uVar4 = uVar4 + 1) {
      iVar2 = __vc__25CPtrArray<P11CTexAnimSeq>FUl(*(int *)(iVar1 + 8) + 0x110,uVar4);
      iVar2 = strcmp(param_3,iVar2 + 8);
      if (iVar2 == 0) goto LAB_800440a8;
    }
    uVar4 = 0xffffffff;
LAB_800440a8:
    if (-1 < (int)uVar4) {
      *(uint *)(iVar1 + 0xc) = uVar4;
      *(float *)(iVar1 + 0x10) = (float)param_1;
      *(undefined4 *)(iVar1 + 0x14) = param_4;
      return;
    }
    uVar5 = uVar5 + 1;
  } while( true );
}

