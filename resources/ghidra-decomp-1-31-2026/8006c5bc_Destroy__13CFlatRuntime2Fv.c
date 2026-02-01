// Function: Destroy__13CFlatRuntime2Fv
// Entry: 8006c5bc
// Size: 160 bytes

void Destroy__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  int *piVar1;
  int iVar2;
  
  Destroy__12CFlatRuntimeFv();
  Destroy__9CFlatDataFv((CFlatData *)&flatRuntime2->field_0xcf20);
  iVar2 = 0;
  do {
    if (*(CFileCHandle **)&flatRuntime2->field_0x1778 != (CFileCHandle *)0x0) {
      Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&flatRuntime2->field_0x1778);
      *(undefined4 *)&flatRuntime2->field_0x1778 = 0;
    }
    piVar1 = *(int **)&flatRuntime2->field_0x1774;
    if (piVar1 != (int *)0x0) {
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)&flatRuntime2->field_0x1774 = 0;
    }
    iVar2 = iVar2 + 1;
    flatRuntime2 = (CFlatRuntime2 *)&(flatRuntime2->flatRuntimeBase).m_variableValuesPtr;
  } while (iVar2 < 8);
  return;
}

