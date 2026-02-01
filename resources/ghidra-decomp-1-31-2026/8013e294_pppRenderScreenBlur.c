// Function: pppRenderScreenBlur
// Entry: 8013e294
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderScreenBlur(pppScreenBlur *pppScreenBlur,UnkB *param_2,UnkC *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_3->m_serializedDataOffsets[1];
  iVar2 = *param_3->m_serializedDataOffsets;
  *(undefined *)((int)&param_2->m_dataValIndex + 2) = 0;
  uVar1 = countLeadingZeros((uint)*(byte *)((int)(&pppScreenBlur->field0_0x0 + 2) + iVar3));
  RenderBlur__8CGraphicFiUcUcUcUcs
            (&Graphic,uVar1 >> 5,*(undefined *)&param_2->m_dataValIndex,
             (uint)*(byte *)((int)&param_2->m_dataValIndex + 1),
             *(undefined *)((int)&param_2->m_dataValIndex + 2),(&pppScreenBlur->field_0x8b)[iVar2],
             *(undefined2 *)&param_2->m_initWOrk);
  pppInitBlendMode__Fv();
  GXSetProjection(&ppvScreenMatrix,0);
  *(undefined *)((int)(&pppScreenBlur->field0_0x0 + 2) + iVar3) = 1;
  return;
}

