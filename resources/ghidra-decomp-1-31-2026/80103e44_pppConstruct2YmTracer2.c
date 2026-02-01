// Function: pppConstruct2YmTracer2
// Entry: 80103e44
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2YmTracer2(pppYmTracer2 *pppYmTracer2,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = *param_2->m_serializedDataOffsets;
  (pppYmTracer2->m_serializedData + iVar1 + 0x2e)[0] = '\0';
  (pppYmTracer2->m_serializedData + iVar1 + 0x2e)[1] = '\0';
  (pppYmTracer2->m_serializedData + iVar1 + 0x2c)[0] = '\0';
  (pppYmTracer2->m_serializedData + iVar1 + 0x2c)[1] = '\0';
  (pppYmTracer2->m_serializedData + iVar1 + 0x32)[0] = '\0';
  (pppYmTracer2->m_serializedData + iVar1 + 0x32)[1] = '\0';
  return;
}

