// Function: pppAccele
// Entry: 8005fb24
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppAccele(pppAccele *pppAccele,UnkB *param_2,UnkC *param_3)

{
  float *pfVar1;
  float *pfVar2;
  
  pfVar1 = (float *)((int)(&pppAccele->pppPObject + 2) + *param_3->m_serializedDataOffsets);
  pfVar2 = (float *)((int)(&pppAccele->pppPObject + 2) + param_3->m_serializedDataOffsets[1]);
  if (DAT_8032ed70 != 0) {
    return;
  }
  if (param_2->m_graphId == (pppAccele->pppPObject).m_graphId) {
    *pfVar2 = *pfVar2 + (float)param_2->m_initWOrk;
    pfVar2[1] = pfVar2[1] + param_2->m_stepValue;
    pfVar2[2] = pfVar2[2] + (float)param_2->m_arg3;
  }
  *pfVar1 = *pfVar1 + *pfVar2;
  pfVar1[1] = pfVar1[1] + pfVar2[1];
  pfVar1[2] = pfVar1[2] + pfVar2[2];
  return;
}

