// Function: ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
// Entry: 800d3fd8
// Size: 396 bytes

void ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
               (CModel *model,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  CMeshCRefData *pCVar5;
  CDisplayList *pCVar6;
  
  if (*(char *)(param_3 + 0x14) != '\0') {
    iVar4 = *(int *)(param_2 + 0x1c);
    pCVar5 = model->m_meshes[param_4].m_data;
    pCVar6 = pCVar5->m_displayLists;
    if (*(int *)(param_2 + 0xc) != 0) {
      iVar1 = *(int *)(*(int *)(param_2 + 0xc) + param_4 * 4);
      if (iVar1 != 0) {
        MaterialMan._4_4_ = pCVar5->m_normals;
        GXSetArray(0xb,iVar1,4);
        if ((*(char *)(param_3 + 0x14) == '\x02') || (*(char *)(param_3 + 0x14) == '\x03')) {
          MaterialMan._208_4_ = 0;
        }
        else {
          MaterialMan._208_4_ = iVar4 + 0x28;
        }
        iVar1 = pCVar5->m_displayListCount - 1;
        iVar4 = iVar1 * 4;
        for (; -1 < iVar1; iVar1 = iVar1 + -1) {
          iVar3 = *(int *)(param_4 * 4 + *(int *)(param_2 + 0x10));
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
          SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                    (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar6->m_material,0,0);
          puVar2 = *(undefined4 **)(iVar3 + iVar4);
          GXCallDisplayList(*puVar2,puVar2[1]);
          iVar4 = iVar4 + -4;
          pCVar6 = pCVar6 + 1;
        }
      }
    }
  }
  return;
}

