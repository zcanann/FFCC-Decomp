// Function: pppDestructCharaBreak
// Entry: 8013ff14
// Size: 364 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructCharaBreak(pppCharaBreak *pppCharaBreak,UnkC *param_2)

{
  int *piVar1;
  int iVar2;
  CStage *stage;
  uint uVar3;
  uint uVar4;
  int iVar5;
  CStage *stage_00;
  CStage *pCVar6;
  int iVar7;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppCharaBreak_cpp_801dd690,0x319);
  iVar2 = param_2->m_serializedDataOffsets[2];
  iVar5 = *(int *)(&pppCharaBreak->field_0xc0 + iVar2);
  *(undefined4 *)(iVar5 + 0xe4) = 0;
  *(undefined4 *)(iVar5 + 0xe8) = 0;
  *(undefined4 *)(iVar5 + 0xf4) = 0;
  *(undefined4 *)(iVar5 + 0xfc) = 0;
  *(undefined4 *)(iVar5 + 0x104) = 0;
  *(undefined4 *)(iVar5 + 0xec) = 0;
  stage_00 = *(CStage **)(&pppCharaBreak->field_0x9c + iVar2);
  iVar2 = *(int *)(iVar5 + 0xac);
  if (stage_00 != (CStage *)0x0) {
    pCVar6 = stage_00;
    for (uVar4 = 0; uVar4 < *(uint *)(*(int *)(iVar5 + 0xa4) + 0xc); uVar4 = uVar4 + 1) {
      piVar1 = *(int **)pCVar6;
      iVar7 = *(int *)(iVar2 + 8);
      if (piVar1 != (int *)0x0) {
        for (uVar3 = 0; uVar3 < *(uint *)(iVar7 + 0x4c); uVar3 = uVar3 + 1) {
          if ((undefined4 *)*piVar1 != (undefined4 *)0x0) {
            stage = *(CStage **)*piVar1;
            if (stage != (CStage *)0x0) {
              pppHeapUseRate__FPQ27CMemory6CStage(stage);
              *(undefined4 *)*piVar1 = 0;
            }
            if (*(CStage **)(*piVar1 + 0xc) != (CStage *)0x0) {
              pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(*piVar1 + 0xc));
              *(undefined4 *)(*piVar1 + 0xc) = 0;
            }
          }
          if ((CStage *)*piVar1 != (CStage *)0x0) {
            pppHeapUseRate__FPQ27CMemory6CStage((CStage *)*piVar1);
            *piVar1 = 0;
          }
          piVar1 = piVar1 + 1;
        }
      }
      if (*(CStage **)pCVar6 != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)pCVar6);
        *(undefined4 *)pCVar6 = 0;
      }
      pCVar6 = (CStage *)&pCVar6->field_0x4;
      iVar2 = iVar2 + 0x14;
    }
  }
  if (stage_00 != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(stage_00);
  }
  return;
}

