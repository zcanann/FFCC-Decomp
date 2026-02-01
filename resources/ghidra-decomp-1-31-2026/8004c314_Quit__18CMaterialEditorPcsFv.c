// Function: Quit__18CMaterialEditorPcsFv
// Entry: 8004c314
// Size: 176 bytes

void Quit__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  CMaterialEditorPcs *pCVar1;
  uint uVar2;
  
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
  if (*(int *)&materialEditorPcs->field_0xbc != 0) {
    MemFree__18CMaterialEditorPcsFPv(materialEditorPcs,*(int *)&materialEditorPcs->field_0xbc);
  }
  return;
}

