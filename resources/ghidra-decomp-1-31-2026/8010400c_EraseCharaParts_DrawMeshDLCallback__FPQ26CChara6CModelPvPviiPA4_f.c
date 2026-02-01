// Function: EraseCharaParts_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 8010400c
// Size: 188 bytes

void EraseCharaParts_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (CModel *model,undefined4 param_2,int param_3,int meshIndex,int param_5)

{
  CDisplayList *pCVar1;
  
  pCVar1 = (model->m_meshes[meshIndex].m_data)->m_displayLists + param_5;
  SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
            (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar1->m_material,0,0);
  if ((*(char *)(param_3 + 4) != 0xff) && (meshIndex == *(char *)(param_3 + 4))) {
    GXSetArray(0xb,param_2,4);
  }
  GXCallDisplayList(pCVar1->m_data,pCVar1->m_size);
  return;
}

