// Function: pppDestructEmission
// Entry: 800e6490
// Size: 160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructEmission(pppEmission *pppEmission,UnkC *param_2)

{
  float fVar1;
  CCharaPcsCHandle *handle;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)((int)(&pppEmission->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2])
  ;
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(undefined4 *)(iVar2 + 0xe4) = 0;
  *(undefined4 *)(iVar2 + 0xe8) = 0;
  *(undefined4 *)(iVar2 + 0xfc) = 0;
  *(undefined4 *)(iVar2 + 0x104) = 0;
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppEmission_cpp_801db7e8,0x118);
  if ((CStage *)*puVar3 != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)*puVar3);
    *puVar3 = 0;
  }
  fVar1 = FLOAT_803311f8;
  puVar3[5] = FLOAT_803311f8;
  puVar3[4] = fVar1;
  puVar3[3] = fVar1;
  return;
}

