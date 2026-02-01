// Function: Draw__8CMapMeshFP12CMaterialSet
// Entry: 800279c4
// Size: 184 bytes

void Draw__8CMapMeshFP12CMaterialSet(CMapMesh *mapMesh,CMaterialSet *param_2)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  
  if (param_2 == (CMaterialSet *)0x0) {
    param_2 = (CMaterialSet *)MapMng._136148_4_;
  }
  uVar3 = (uint)(ushort)mapMesh->unkCount;
  piVar2 = (int *)mapMesh->field19_0x40;
  while (bVar1 = uVar3 != 0, uVar3 = uVar3 - 1, bVar1) {
    if (*piVar2 != 0) {
      SetBlendMode__12CMaterialManFP12CMaterialSeti
                (&MaterialMan,param_2,(uint)*(ushort *)(piVar2 + 2));
      SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                (&MaterialMan,param_2,(uint)*(ushort *)(piVar2 + 2),0,1);
      GXCallDisplayList(piVar2[1],*piVar2);
    }
    piVar2 = piVar2 + 4;
  }
  return;
}

