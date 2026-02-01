// Function: MemFree__18CMaterialEditorPcsFPv
// Entry: 8004dcb8
// Size: 48 bytes

CMaterialEditorPcs *
MemFree__18CMaterialEditorPcsFPv(CMaterialEditorPcs *materialEditorPcs,int param_2)

{
  if (param_2 != 0) {
    materialEditorPcs = (CMaterialEditorPcs *)Free__7CMemoryFPv(&Memory);
  }
  return materialEditorPcs;
}

