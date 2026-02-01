// Function: DrawMesh__8CMapMeshFUsUs
// Entry: 80027b24
// Size: 176 bytes

void DrawMesh__8CMapMeshFUsUs(CMapMesh *mapMesh,uint param_2,uint param_3)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = param_3 & 0xffff;
  piVar2 = (int *)(mapMesh->field19_0x40 + (param_2 & 0xffff) * 0x10);
  while (bVar1 = uVar3 != 0, uVar3 = uVar3 - 1, bVar1) {
    if (*piVar2 != 0) {
      SetBlendMode__12CMaterialManFP12CMaterialSeti
                (&MaterialMan,(CMaterialSet *)MapMng._136148_4_,(uint)*(ushort *)(piVar2 + 2));
      SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                (&MaterialMan,(CMaterialSet *)MapMng._136148_4_,(uint)*(ushort *)(piVar2 + 2),0,1);
      GXCallDisplayList(piVar2[1],*piVar2);
    }
    piVar2 = piVar2 + 4;
  }
  return;
}

