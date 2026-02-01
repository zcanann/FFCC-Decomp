// Function: pppRenderFilter
// Entry: 801432e0
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderFilter(pppFilter *pppFilter,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14 [4];
  
  iVar2 = *param_3->m_serializedDataOffsets;
  if (param_2->m_dataValIndex == 0xffff) {
    local_18 = *(undefined4 *)(&pppFilter->field_0x88 + iVar2);
    RenderColorQuad__5CUtilFffff8_GXColor
              ((double)FLOAT_803320c8,(double)FLOAT_803320c8,(double)FLOAT_803320cc,
               (double)FLOAT_803320d0,&DAT_8032ec70,&local_18);
  }
  else {
    local_14[0] = 0;
    iVar1 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      (pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],
                       pppEnvStPtr->m_materialSetPtr,local_14);
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)FLOAT_803320c8,(double)FLOAT_803320c8,(double)FLOAT_803320cc,
               (double)FLOAT_803320d0,&DAT_8032ec70,iVar1 + 0x28,0,0,&pppFilter->field_0x88 + iVar2,
               4,5);
  }
  return;
}

