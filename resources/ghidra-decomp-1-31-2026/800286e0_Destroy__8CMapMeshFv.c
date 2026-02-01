// Function: Destroy__8CMapMeshFv
// Entry: 800286e0
// Size: 116 bytes

void Destroy__8CMapMeshFv(CMapMesh *mapMesh)

{
  if ((void *)mapMesh->field12_0x24 != (void *)0x0) {
    __dla__FPv((void *)mapMesh->field12_0x24);
    mapMesh->field12_0x24 = 0;
  }
  if ((void *)mapMesh->field13_0x28 != (void *)0x0) {
    __dla__FPv((void *)mapMesh->field13_0x28);
    mapMesh->field13_0x28 = 0;
  }
  mapMesh->field0_0x0 = 0;
  mapMesh->field1_0x2 = 0;
  mapMesh->field2_0x4 = 0;
  mapMesh->field4_0x8 = 0;
  mapMesh->field3_0x6 = 0;
  mapMesh->unkCount = 0;
  return;
}

