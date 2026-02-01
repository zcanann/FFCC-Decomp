// Function: pppFrameYmDeformationShp
// Entry: 80090438
// Size: 292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmDeformationShp(pppYmDeformationShp *pppYmDeformationShp,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  
  if (DAT_8032ed70 == 0) {
    iVar1 = param_3->m_serializedDataOffsets[2];
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (param_2->m_stepValue,(_pppPObject *)pppYmDeformationShp,param_2->m_graphId,
               &pppYmDeformationShp->field_0x90 + iVar1,&pppYmDeformationShp->field_0x94 + iVar1,
               &pppYmDeformationShp->field_0x98 + iVar1,&param_2->m_arg3,param_2->m_payload);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 4),(_pppPObject *)pppYmDeformationShp,
               param_2->m_graphId,&pppYmDeformationShp->field_0x9c + iVar1,
               &pppYmDeformationShp->field_0xa0 + iVar1,&pppYmDeformationShp->field_0xa4 + iVar1,
               param_2->m_payload + 8,param_2->m_payload + 0xc);
    if (DAT_8032ed78 == '\0') {
      if ((&pppYmDeformationShp->field_0x8e)[iVar1] == '\0') {
        *(short *)(&pppYmDeformationShp->field_0x8c + iVar1) =
             *(short *)(&pppYmDeformationShp->field_0x8c + iVar1) -
             (short)(int)*(float *)(&pppYmDeformationShp->field_0x9c + iVar1);
        if ((int)*(short *)(&pppYmDeformationShp->field_0x8c + iVar1) <
            -(int)*(short *)(param_2->m_payload + 0x10)) {
          (&pppYmDeformationShp->field_0x8e)[iVar1] = 1;
        }
      }
      else {
        *(short *)(&pppYmDeformationShp->field_0x8c + iVar1) =
             *(short *)(&pppYmDeformationShp->field_0x8c + iVar1) +
             (short)(int)*(float *)(&pppYmDeformationShp->field_0x9c + iVar1);
        if (*(short *)(param_2->m_payload + 0x10) <
            *(short *)(&pppYmDeformationShp->field_0x8c + iVar1)) {
          (&pppYmDeformationShp->field_0x8e)[iVar1] = 0;
        }
      }
    }
  }
  return;
}

