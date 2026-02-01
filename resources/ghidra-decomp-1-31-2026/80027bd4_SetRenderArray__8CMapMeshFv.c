// Function: SetRenderArray__8CMapMeshFv
// Entry: 80027bd4
// Size: 120 bytes

void SetRenderArray__8CMapMeshFv(CMapMesh *mapMesh)

{
  GXSetArray(9,mapMesh->field14_0x2c,0xc);
  GXSetArray(0xb,mapMesh->field18_0x3c,4);
  GXSetArray(0xd,mapMesh->field17_0x38,4);
  GXSetArray(0xe,mapMesh->field17_0x38,4);
  MaterialMan._4_4_ = mapMesh->field15_0x30;
  return;
}

