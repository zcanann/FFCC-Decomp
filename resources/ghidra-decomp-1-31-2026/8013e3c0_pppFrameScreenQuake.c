// Function: pppFrameScreenQuake
// Entry: 8013e3c0
// Size: 248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameScreenQuake(pppScreenQuake *pppScreenQuake,UnkB *param_2,UnkC *param_3)

{
  float *value;
  
  if (DAT_8032ed70 == 0) {
    value = (float *)((int)(&pppScreenQuake->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_dataValIndex,&pppScreenQuake->field0_0x0,param_2->m_graphId,value,
               value + 1,value + 2,&param_2->m_initWOrk,&param_2->m_stepValue);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_arg3,&pppScreenQuake->field0_0x0,param_2->m_graphId,value + 3,
               value + 4,value + 5,param_2->m_payload,param_2->m_payload + 4);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 8),&pppScreenQuake->field0_0x0,param_2->m_graphId,
               value + 6,value + 7,value + 8,param_2->m_payload + 0xc,param_2->m_payload + 0x10);
    SetQuakeParameter__10CCameraPcsFiissffffffi
              ((double)*value,(double)value[3],(double)value[6],
               (double)*(float *)(param_2->m_payload + 0x14),
               (double)*(float *)(param_2->m_payload + 0x18),
               (double)*(float *)(param_2->m_payload + 0x1c),&CameraPcs,1,0,0,0,1);
  }
  return;
}

