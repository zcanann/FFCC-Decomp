// Function: pppConstruct2YmTracer
// Entry: 80093c94
// Size: 32 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2YmTracer(pppYmTracer *pppYmTracer,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = *param_2->m_serializedDataOffsets;
  *(undefined2 *)(&pppYmTracer->field_0xae + iVar1) = 0;
  *(undefined2 *)(&pppYmTracer->field_0xac + iVar1) = 0;
  return;
}

