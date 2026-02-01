// Function: pppDestructYmChangeTex
// Entry: 800d3da4
// Size: 500 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmChangeTex(pppYmChangeTex *pppYmChangeTex,UnkC *param_2)

{
  CCharaPcsCHandle *handle;
  CCharaPcsCHandle *handle_00;
  CCharaPcsCHandle *handle_01;
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  CStage *stage;
  CStage *pCVar7;
  CStage *stage_00;
  CStage *pCVar8;
  
  iVar2 = param_2->m_serializedDataOffsets[2];
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl(*(CGObject **)(&pppYmChangeTex->field_0x98 + iVar2),0);
  handle_00 = (CCharaPcsCHandle *)
              GetCharaHandlePtr__FP8CGObjectl(*(CGObject **)(&pppYmChangeTex->field_0x98 + iVar2),1)
  ;
  handle_01 = (CCharaPcsCHandle *)
              GetCharaHandlePtr__FP8CGObjectl(*(CGObject **)(&pppYmChangeTex->field_0x98 + iVar2),2)
  ;
  iVar6 = 0;
  if (handle != (CCharaPcsCHandle *)0x0) {
    iVar6 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(undefined4 *)(iVar6 + 0xe4) = 0;
    *(undefined4 *)(iVar6 + 0xe8) = 0;
    *(undefined4 *)(iVar6 + 0xf4) = 0;
    *(undefined4 *)(iVar6 + 0xfc) = 0;
    *(undefined4 *)(iVar6 + 0x104) = 0;
  }
  if ((handle_00 != (CCharaPcsCHandle *)0x0) &&
     (iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle_00), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 0xe4) = 0;
    *(undefined4 *)(iVar1 + 0xe8) = 0;
    *(undefined4 *)(iVar1 + 0xf4) = 0;
    *(undefined4 *)(iVar1 + 0xfc) = 0;
    *(undefined4 *)(iVar1 + 0x104) = 0;
  }
  if ((handle_01 != (CCharaPcsCHandle *)0x0) &&
     (iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle_01), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 0xe4) = 0;
    *(undefined4 *)(iVar1 + 0xe8) = 0;
    *(undefined4 *)(iVar1 + 0xf4) = 0;
    *(undefined4 *)(iVar1 + 0xfc) = 0;
    *(undefined4 *)(iVar1 + 0x104) = 0;
  }
  stage = *(CStage **)(&pppYmChangeTex->field_0x90 + iVar2);
  if ((stage != (CStage *)0x0) &&
     (stage_00 = *(CStage **)(&pppYmChangeTex->field_0x8c + iVar2), stage_00 != (CStage *)0x0)) {
    iVar2 = *(int *)(iVar6 + 0xac);
    pCVar7 = stage;
    pCVar8 = stage_00;
    for (uVar5 = 0; uVar5 < *(uint *)(*(int *)(iVar6 + 0xa4) + 0xc); uVar5 = uVar5 + 1) {
      iVar1 = *(int *)(iVar2 + 8);
      puVar4 = *(undefined4 **)pCVar7;
      for (uVar3 = 0; uVar3 < *(uint *)(iVar1 + 0x4c); uVar3 = uVar3 + 1) {
        if (*(CStage **)*puVar4 != (CStage *)0x0) {
          pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)*puVar4);
          *(undefined4 *)*puVar4 = 0;
        }
        if ((CStage *)*puVar4 != (CStage *)0x0) {
          pppHeapUseRate__FPQ27CMemory6CStage((CStage *)*puVar4);
          *puVar4 = 0;
        }
        puVar4 = puVar4 + 1;
      }
      if (*(CStage **)pCVar7 != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)pCVar7);
        *(undefined4 *)pCVar7 = 0;
      }
      if (*(CStage **)pCVar8 != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)pCVar8);
        *(undefined4 *)pCVar8 = 0;
      }
      pCVar7 = (CStage *)&pCVar7->field_0x4;
      pCVar8 = (CStage *)&pCVar8->field_0x4;
      iVar2 = iVar2 + 0x14;
    }
    if (stage != (CStage *)0x0) {
      pppHeapUseRate__FPQ27CMemory6CStage(stage);
    }
    if (stage_00 != (CStage *)0x0) {
      pppHeapUseRate__FPQ27CMemory6CStage(stage_00);
    }
  }
  return;
}

