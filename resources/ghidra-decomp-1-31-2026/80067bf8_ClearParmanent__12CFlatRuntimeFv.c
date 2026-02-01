// Function: ClearParmanent__12CFlatRuntimeFv
// Entry: 80067bf8
// Size: 68 bytes

void ClearParmanent__12CFlatRuntimeFv(CFlatRuntime2 *flatRuntime)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  while( true ) {
    if ((flatRuntime->flatRuntimeBase).m_variableCount <= iVar2) break;
    if ((*(byte *)((int)(flatRuntime->flatRuntimeBase).m_variableDefs + iVar1 + 1) & 0x20) != 0) {
      *(undefined4 *)((int)(flatRuntime->flatRuntimeBase).m_variableValuesPtr + iVar1) = 0;
    }
    iVar1 = iVar1 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}

