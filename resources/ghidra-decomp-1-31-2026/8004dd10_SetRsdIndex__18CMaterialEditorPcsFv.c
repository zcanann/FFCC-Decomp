// Function: SetRsdIndex__18CMaterialEditorPcsFv
// Entry: 8004dd10
// Size: 96 bytes

undefined4 SetRsdIndex__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)GetDataIdx__5ZLISTFi
                            (&materialEditorPcs->zlistB,
                             *(undefined4 *)&materialEditorPcs->field_0xc4);
  if (piVar1 == (int *)0x0) {
    uVar2 = 0;
  }
  else if (*piVar1 == 0) {
    uVar2 = 0;
  }
  else {
    *(int *)&materialEditorPcs->field_0xbc = *piVar1;
    uVar2 = 1;
  }
  return uVar2;
}

