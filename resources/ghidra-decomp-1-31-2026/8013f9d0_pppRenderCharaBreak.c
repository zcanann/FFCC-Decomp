// Function: pppRenderCharaBreak
// Entry: 8013f9d0
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderCharaBreak(pppCharaBreak *pppCharaBreak,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = *param_3->m_serializedDataOffsets;
  puVar2 = (undefined *)
           ((int)(&pppCharaBreak->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  if (*(int *)(puVar2 + 0x44) != 0) {
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    pppInitBlendMode__Fv();
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80332048,(pppCVector *)(&pppCharaBreak->field_0x88 + iVar1),
               (pppFMATRIX *)&pppCharaBreak->field_0x40,0,0,0,0,1,1,0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,2,2,3);
    *puVar2 = 0xff;
    puVar2[1] = 0xff;
    puVar2[2] = 0xff;
    puVar2[3] = (&pppCharaBreak->field_0x8b)[iVar1];
  }
  return;
}

