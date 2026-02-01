// Function: DrawPart__8CMapMeshFP12CMaterialSeti
// Entry: 80027940
// Size: 132 bytes

void DrawPart__8CMapMeshFP12CMaterialSeti(CMapMesh *mapMesh,CMaterialSet *materialSet,int param_3)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = (uint)(ushort)mapMesh->unkCount;
  piVar2 = (int *)mapMesh->field19_0x40;
  while (bVar1 = uVar3 != 0, uVar3 = uVar3 - 1, bVar1) {
    if (*piVar2 != 0) {
      if (param_3 != 0) {
        SetMaterialPart__12CMaterialManFP12CMaterialSetii
                  (&MaterialMan,materialSet,(uint)*(ushort *)(piVar2 + 2),1);
      }
      GXCallDisplayList(piVar2[1],*piVar2);
    }
    piVar2 = piVar2 + 4;
  }
  return;
}

