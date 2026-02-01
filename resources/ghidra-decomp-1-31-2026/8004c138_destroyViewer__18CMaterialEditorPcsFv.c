// Function: destroyViewer__18CMaterialEditorPcsFv
// Entry: 8004c138
// Size: 252 bytes

void destroyViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  CMaterialEditorPcs *pCVar1;
  uint uVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  IsBigAlloc__7CUSBPcsFi(&USBPcs,0);
  local_14 = 0;
  local_18 = 0;
  GXSetCopyClear(&local_18,0xffffff);
  DeleteBuffer__14CUSBStreamDataFv(&materialEditorPcs->m_usbStream);
  MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&materialEditorPcs->field_0xbc);
  uVar2 = 0;
  materialEditorPcs->field_0x3bc = 0;
  pCVar1 = materialEditorPcs;
  do {
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x2bc);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x2fc);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x23c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x33c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x37c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar1->field_0x27c);
    uVar2 = uVar2 + 1;
    pCVar1 = (CMaterialEditorPcs *)&pCVar1->field_0x4;
  } while (uVar2 < 0x10);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&materialEditorPcs->field_0x4);
  return;
}

