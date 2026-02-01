// Function: DrawCharaShadow__8COctTreeFUc
// Entry: 8002e27c
// Size: 188 bytes

void DrawCharaShadow__8COctTreeFUc(COctTree *octTree,char param_2)

{
  void *pvVar1;
  
  if ((*(char *)&octTree->vtable == '\0') &&
     (pvVar1 = octTree->field2_0x8, *(char *)((int)pvVar1 + 0x15) == param_2)) {
    SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
              (&LightPcs,(int)pvVar1 + 0xb8,0,(int)pvVar1 + 0x58,*(undefined *)((int)pvVar1 + 0x1a))
    ;
    if (FLOAT_8032f964 != *(float *)((int)octTree->field2_0x8 + 0x40)) {
      SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
    }
    SetRenderArray__8CMapMeshFv(*(CMapMesh **)((int)octTree->field2_0x8 + 0xc));
    DrawCharaShadowTypeMeshFlag_r__8COctTreeFP8COctNode(octTree,octTree->rootNode);
    if (FLOAT_8032f964 != *(float *)((int)octTree->field2_0x8 + 0x40)) {
      SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
    }
  }
  return;
}

