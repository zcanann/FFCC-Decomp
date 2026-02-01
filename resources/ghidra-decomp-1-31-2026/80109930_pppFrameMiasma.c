// Function: pppFrameMiasma
// Entry: 80109930
// Size: 368 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameMiasma(pppMiasma *pppMiasma,UnkB *param_2,UnkC *param_3)

{
  short *psVar1;
  
  if (DAT_8032ed70 != 0) {
    return;
  }
  psVar1 = (short *)((int)(&pppMiasma->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  psVar1[4] = psVar1[4] + psVar1[8];
  *psVar1 = *psVar1 + psVar1[4];
  psVar1[5] = psVar1[5] + psVar1[9];
  psVar1[1] = psVar1[1] + psVar1[5];
  psVar1[6] = psVar1[6] + psVar1[10];
  psVar1[2] = psVar1[2] + psVar1[6];
  psVar1[7] = psVar1[7] + psVar1[0xb];
  psVar1[3] = psVar1[3] + psVar1[7];
  if ((pppMiasma->field0_0x0).m_graphId != param_2->m_graphId) {
    return;
  }
  *psVar1 = *psVar1 + *(short *)(param_2->m_payload + 4);
  psVar1[1] = psVar1[1] + *(short *)(param_2->m_payload + 6);
  psVar1[2] = psVar1[2] + *(short *)(param_2->m_payload + 8);
  psVar1[3] = psVar1[3] + *(short *)(param_2->m_payload + 10);
  psVar1[4] = psVar1[4] + *(short *)(param_2->m_payload + 0xc);
  psVar1[5] = psVar1[5] + *(short *)(param_2->m_payload + 0xe);
  psVar1[6] = psVar1[6] + *(short *)(param_2->m_payload + 0x10);
  psVar1[7] = psVar1[7] + *(short *)(param_2->m_payload + 0x12);
  psVar1[8] = psVar1[8] + *(short *)(param_2->m_payload + 0x14);
  psVar1[9] = psVar1[9] + *(short *)(param_2->m_payload + 0x16);
  psVar1[10] = psVar1[10] + *(short *)(param_2->m_payload + 0x18);
  psVar1[0xb] = psVar1[0xb] + *(short *)(param_2->m_payload + 0x1a);
  return;
}

