// Function: pppFrameEraseCharaParts
// Entry: 80103ec0
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameEraseCharaParts(pppEraseCharaParts *pppEraseCharaParts,UnkB *param_2,UnkC *param_3)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  if (DAT_8032ed70 == 0) {
    iVar2 = *param_3->m_serializedDataOffsets;
    puVar3 = (undefined *)
             ((int)(&pppEraseCharaParts->field0_0x0 + 2) + param_3->m_serializedDataOffsets[1]);
    handle = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(undefined **)(iVar1 + 0xe4) = puVar3;
    *(UnkB **)(iVar1 + 0xe8) = param_2;
    *puVar3 = (&pppEraseCharaParts->field_0x88)[iVar2];
    puVar3[1] = (&pppEraseCharaParts->field_0x89)[iVar2];
    puVar3[2] = (&pppEraseCharaParts->field_0x8a)[iVar2];
    puVar3[3] = (&pppEraseCharaParts->field_0x8b)[iVar2];
    DCFlushRange(puVar3,4);
  }
  return;
}

