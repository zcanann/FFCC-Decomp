// Function: ClearTextureData__18CMaterialEditorPcsFv
// Entry: 8004c098
// Size: 160 bytes

void ClearTextureData__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  uint uVar1;
  CMaterialEditorPcs *pCVar2;
  
  uVar1 = 0;
  materialEditorPcs->field_0x3bc = 0;
  pCVar2 = materialEditorPcs;
  do {
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x2bc);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x2fc);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x23c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x33c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x37c);
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(undefined4 *)&pCVar2->field_0x27c);
    uVar1 = uVar1 + 1;
    pCVar2 = (CMaterialEditorPcs *)&pCVar2->field_0x4;
  } while (uVar1 < 0x10);
  return;
}

