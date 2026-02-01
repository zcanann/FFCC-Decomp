// Function: pppRenderChangeTex
// Entry: 8013ef94
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderChangeTex(pppChangeTex *pppChangeTex,int param_2)

{
  undefined4 local_8 [2];
  
  if (*(int *)(param_2 + 4) != 0xffff) {
    local_8[0] = 0;
    GetTexture__8CMapMeshFP12CMaterialSetRi
              (pppEnvStPtr->m_mapMeshPtr[*(int *)(param_2 + 4)],pppEnvStPtr->m_materialSetPtr,
               local_8);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    pppInitBlendMode__Fv();
  }
  return;
}

