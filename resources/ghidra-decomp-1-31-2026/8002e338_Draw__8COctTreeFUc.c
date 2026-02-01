// Function: Draw__8COctTreeFUc
// Entry: 8002e338
// Size: 344 bytes

void Draw__8COctTreeFUc(COctTree *octTree,char param_2)

{
  void *pvVar1;
  
  if (*(char *)&octTree->vtable == '\0') {
    pvVar1 = octTree->field2_0x8;
    if ((*(char *)((int)pvVar1 + 0x15) == param_2) && ((*(byte *)((int)pvVar1 + 0x18) & 1) != 0)) {
      if ((MapMng._141706_1_ != '\0') &&
         ((*(int *)((int)pvVar1 + 0x10) != 0 &&
          (*(char *)(*(int *)((int)pvVar1 + 0x10) + 0xb1) == '\x02')))) {
        SetUnderWaterTex__12CMaterialManFv(&MaterialMan);
        MapMng._141706_1_ = 0;
      }
      pvVar1 = octTree->field2_0x8;
      SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
                (&LightPcs,(int)pvVar1 + 0xb8,*(undefined4 *)((int)pvVar1 + 0x10),(int)pvVar1 + 0x58
                 ,*(undefined *)((int)pvVar1 + 0x1a));
      if (FLOAT_8032f964 != *(float *)((int)octTree->field2_0x8 + 0x40)) {
        SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
      }
      if (*(char *)((int)octTree->field2_0x8 + 0x27) != '\0') {
        GXSetZMode(1,3,0);
      }
      SetRenderArray__8CMapMeshFv(*(CMapMesh **)((int)octTree->field2_0x8 + 0xc));
      DrawTypeMeshFlag_r__8COctTreeFP8COctNode(octTree,octTree->rootNode);
      if (*(char *)((int)octTree->field2_0x8 + 0x27) != '\0') {
        GXSetZMode(1,3,1);
      }
      if (FLOAT_8032f964 != *(float *)((int)octTree->field2_0x8 + 0x40)) {
        SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
      }
    }
  }
  return;
}

