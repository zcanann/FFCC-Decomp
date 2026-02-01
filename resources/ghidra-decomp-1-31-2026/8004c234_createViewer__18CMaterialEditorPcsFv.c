// Function: createViewer__18CMaterialEditorPcsFv
// Entry: 8004c234
// Size: 204 bytes

void createViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  float fVar1;
  CStage *pCVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  pCVar2 = CreateStage__7CMemoryFUlPci(&Memory,0x200000,s_CMaterialEditorPcs_801d7d34,0);
  *(CStage **)&materialEditorPcs->field_0x4 = pCVar2;
  IsBigAlloc__7CUSBPcsFi(&USBPcs,1);
  local_14 = 0x404040ff;
  local_18 = 0x404040ff;
  GXSetCopyClear(&local_18,0xffffff);
  (materialEditorPcs->m_usbStream).m_stageDefault = (CStage *)0x1;
  *(undefined4 *)&materialEditorPcs->field_0xe8 = 0;
  memset(&materialEditorPcs->field_0xec,0,0x120);
  fVar1 = FLOAT_8032fcc8;
  *(float *)&materialEditorPcs->field_0x128 = FLOAT_8032fcc8;
  *(float *)&materialEditorPcs->field_0x114 = fVar1;
  *(float *)&materialEditorPcs->field_0x100 = fVar1;
  *(float *)&materialEditorPcs->field_0xec = fVar1;
  PSMTXIdentity(&materialEditorPcs->m_unkMatrix);
  CreateBuffer__14CUSBStreamDataFv(&materialEditorPcs->m_usbStream);
  return;
}

