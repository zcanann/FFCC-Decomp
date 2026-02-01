// Function: pppConScreenBlur
// Entry: 8013e368
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConScreenBlur(pppScreenBlur *pppScreenBlur,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[1];
  InitBlurParameter__8CGraphicFv(&Graphic);
  *(undefined *)((int)(&pppScreenBlur->field0_0x0 + 2) + iVar1) = 0;
  return;
}

