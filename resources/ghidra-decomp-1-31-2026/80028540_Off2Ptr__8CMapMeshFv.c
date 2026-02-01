// Function: Off2Ptr__8CMapMeshFv
// Entry: 80028540
// Size: 156 bytes

void Off2Ptr__8CMapMeshFv(CMapMesh *mapMesh)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  mapMesh->field14_0x2c = mapMesh->field14_0x2c + mapMesh->field12_0x24;
  mapMesh->field15_0x30 = mapMesh->field15_0x30 + mapMesh->field12_0x24;
  mapMesh->field16_0x34 = mapMesh->field16_0x34 + mapMesh->field12_0x24;
  mapMesh->field17_0x38 = mapMesh->field17_0x38 + mapMesh->field12_0x24;
  mapMesh->field18_0x3c = mapMesh->field18_0x3c + mapMesh->field12_0x24;
  mapMesh->field19_0x40 = mapMesh->field19_0x40 + mapMesh->field12_0x24;
  for (iVar3 = 0; iVar3 < (int)(uint)(ushort)mapMesh->unkCount; iVar3 = iVar3 + 1) {
    iVar2 = mapMesh->field19_0x40 + iVar1;
    iVar1 = iVar1 + 0x10;
    *(int *)(iVar2 + 4) = mapMesh->field12_0x24 + *(int *)(iVar2 + 0xc);
  }
  return;
}

