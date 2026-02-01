// Function: Duplicate__11CTexAnimSetFPQ27CMemory6CStage
// Entry: 80044540
// Size: 352 bytes

CRef * Duplicate__11CTexAnimSetFPQ27CMemory6CStage(CTexAnimSet *texAnims,CStage *stage)

{
  float fVar1;
  CRef *ref;
  int iVar2;
  CRef *ref_00;
  uint uVar3;
  uint uVar4;
  
  ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x28,stage,s_texanim_cpp_801d7adc,0x54);
  if (ref != (CRef *)0x0) {
    __ct__4CRefFv(ref);
    ref->vtable = &PTR_PTR_s_CTexAnimSet_801e9c6c;
    __ct__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)(ref + 1));
    ref[4].refCount = (int)FLOAT_8032fb38;
  }
  SetStage__21CPtrArray<P8CTexAnim>FPQ27CMemory6CStage((CPtrArray *)(ref + 1),stage);
  uVar4 = 0;
  while( true ) {
    uVar3 = GetSize__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnims->texAnims).size);
    if (uVar3 <= uVar4) break;
    iVar2 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnims->texAnims).size,uVar4);
    ref_00 = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x24,stage,s_texanim_cpp_801d7adc,0xf4);
    if (ref_00 != (CRef *)0x0) {
      __ct__4CRefFv(ref_00);
      fVar1 = FLOAT_8032fb38;
      ref_00->vtable = &PTR_PTR_s_CTexAnim_801e9c54;
      ref_00[1].vtable = (void *)0x0;
      ref_00[1].refCount = 0;
      ref_00[2].vtable = (void *)fVar1;
      ref_00[2].refCount = -2;
      ref_00[4].vtable = (void *)fVar1;
      ref_00[3].refCount = (int)fVar1;
      ref_00[3].vtable = (void *)fVar1;
    }
    ref_00[1].vtable = *(void **)(iVar2 + 8);
    *(int *)((int)ref_00[1].vtable + 4) = *(int *)((int)ref_00[1].vtable + 4) + 1;
    ref_00[1].refCount = *(int *)(iVar2 + 0xc);
    ref_00[2].vtable = *(void **)(iVar2 + 0x10);
    ref_00[2].refCount = *(int *)(iVar2 + 0x14);
    ref_00[3].vtable = *(void **)(iVar2 + 0x18);
    ref_00[3].refCount = *(int *)(iVar2 + 0x1c);
    ref_00[4].vtable = *(void **)(iVar2 + 0x20);
    Add__21CPtrArray<P8CTexAnim>FP8CTexAnim((CPtrArray *)(ref + 1),ref_00);
    uVar4 = uVar4 + 1;
  }
  ref[4].refCount = *(int *)&texAnims->field_0x24;
  return ref;
}

