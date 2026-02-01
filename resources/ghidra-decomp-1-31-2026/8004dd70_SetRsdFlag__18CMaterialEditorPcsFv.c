// Function: SetRsdFlag__18CMaterialEditorPcsFv
// Entry: 8004dd70
// Size: 80 bytes

bool SetRsdFlag__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  int iVar1;
  
  iVar1 = GetDataIdx__5ZLISTFi
                    (&materialEditorPcs->zlistB,*(undefined4 *)&materialEditorPcs->field_0xc4);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)&materialEditorPcs->field_0xc0;
  }
  return iVar1 != 0;
}

