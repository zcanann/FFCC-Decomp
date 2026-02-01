// Function: pppFrameYmDeformationMdl
// Entry: 800d1f58
// Size: 308 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmDeformationMdl(pppYmDeformationMdl *pppYmDeformationMdl,UnkB *param_2,UnkC *param_3)

{
  short *psVar1;
  
  if ((DAT_8032ed70 == 0) &&
     (psVar1 = (short *)(&pppYmDeformationMdl->field_0x80 + param_3->m_serializedDataOffsets[2]),
     param_2->m_dataValIndex != 0xffff)) {
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_initWOrk,(_pppPObject *)pppYmDeformationMdl,param_2->m_graphId,
               psVar1 + 2,psVar1 + 4,psVar1 + 6,&param_2->m_stepValue,&param_2->m_arg3);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)param_2->m_payload,(_pppPObject *)pppYmDeformationMdl,param_2->m_graphId,
               psVar1 + 8,psVar1 + 10,psVar1 + 0xc,param_2->m_payload + 4,param_2->m_payload + 8);
    if (DAT_8032ed78 == '\0') {
      if (*(char *)(psVar1 + 1) == '\0') {
        *psVar1 = *psVar1 - (short)(int)*(float *)(psVar1 + 8);
        if ((int)*psVar1 < -(int)*(short *)(param_2->m_payload + 0xc)) {
          *(undefined *)(psVar1 + 1) = 1;
        }
      }
      else {
        *psVar1 = *psVar1 + (short)(int)*(float *)(psVar1 + 8);
        if (*(short *)(param_2->m_payload + 0xc) < *psVar1) {
          *(undefined *)(psVar1 + 1) = 0;
        }
      }
    }
  }
  return;
}

