// Function: ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 800d4164
// Size: 276 bytes

void ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (CModel *model,int param_2,int param_3,int param_4,int param_5)

{
  CDisplayList *pCVar1;
  
  pCVar1 = (model->m_meshes[param_4].m_data)->m_displayLists + param_5;
  if (*(char *)(param_3 + 0x14) == '\0') {
    MaterialMan._208_4_ = *(int *)(param_2 + 0x1c) + 0x28;
    MaterialMan._68_4_ = 0xffffffff;
    MaterialMan._76_1_ = 0xff;
    MaterialMan._284_4_ = 0;
    MaterialMan._288_4_ = 0x1e;
    MaterialMan._292_4_ = 0;
    MaterialMan._517_1_ = 0xff;
    MaterialMan._518_1_ = 0xff;
    MaterialMan._88_4_ = 0;
    MaterialMan._92_4_ = 0;
    MaterialMan._520_1_ = 0;
    MaterialMan._72_4_ = 0xade0f;
    MaterialMan._296_4_ = 0;
    MaterialMan._300_4_ = 0x1e;
    MaterialMan._304_4_ = 0;
    MaterialMan._64_4_ = 0xade0f;
  }
  SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
            (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar1->m_material,0,0);
  if ((*(char *)(param_3 + 0x14) == '\x01') || (*(char *)(param_3 + 0x14) == '\0')) {
    GXCallDisplayList(pCVar1->m_data,pCVar1->m_size);
  }
  return;
}

