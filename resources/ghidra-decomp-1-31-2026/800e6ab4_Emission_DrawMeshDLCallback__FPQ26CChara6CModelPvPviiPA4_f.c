// Function: Emission_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 800e6ab4
// Size: 228 bytes

void Emission_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (CModel *model,undefined4 param_2,undefined4 param_3,int meshIndex,int param_5)

{
  int iVar1;
  CDisplayList *pCVar2;
  CMeshCRefData *pCVar3;
  
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,100);
  pCVar3 = model->m_meshes[meshIndex].m_data;
  pCVar2 = pCVar3->m_displayLists + param_5;
  iVar1 = strcmp(pCVar3,&DAT_803311fc);
  if (iVar1 == 0) {
    *pCVar3->m_colors = '\0';
    pCVar3->m_colors[1] = '\0';
    pCVar3->m_colors[2] = '\0';
    pCVar3->m_colors[3] = '\0';
  }
  else {
    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
              (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar2->m_material,0,0);
    GXCallDisplayList(pCVar2->m_data,pCVar2->m_size);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x65);
  }
  return;
}

