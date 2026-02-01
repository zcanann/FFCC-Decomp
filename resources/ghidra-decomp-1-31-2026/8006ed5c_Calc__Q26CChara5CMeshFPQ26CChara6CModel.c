// Function: Calc__Q26CChara5CMeshFPQ26CChara6CModel
// Entry: 8006ed5c
// Size: 652 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__Q26CChara5CMeshFPQ26CChara6CModel(CMesh *mesh,CModel *model)

{
  int iVar1;
  S16Vec *pSVar2;
  int *piVar3;
  S16Vec *pSVar4;
  S16Vec *pSVar5;
  CMeshCRefData *pCVar6;
  float *ab;
  uint uVar7;
  
  pCVar6 = mesh->m_data;
  if (pCVar6->m_skinCount == 0) {
    mesh->m_workPositions = pCVar6->m_vertices;
    mesh->m_workNormals = mesh->m_data->m_normals;
  }
  else {
    iVar1 = Chara._8288_4_ * 8;
    piVar3 = (int *)(&Chara.field_0x2064 + iVar1);
    if (0x58000U - *piVar3 < (pCVar6->m_vertexCount + pCVar6->m_normalCount) * 6 + 0x40) {
      mesh->m_workPositions = (S16Vec *)0x0;
      mesh->m_workNormals = (S16Vec *)0x0;
      if (DAT_8032eda4 == '\0') {
        DAT_8032eda0 = 1;
        DAT_8032eda4 = '\x01';
      }
      if ((DAT_8032eda0 != 0) && (DAT_8032eda0 = 0, 1 < (uint)System.m_execParam)) {
        Printf__7CSystemFPce(&System,&DAT_801d9094);
      }
    }
    else {
      mesh->m_workPositions = (S16Vec *)(*(int *)(&Chara.field_0x2068 + iVar1) + *piVar3);
      *piVar3 = *piVar3 + (mesh->m_data->m_vertexCount * 6 + 0x1f & 0xffffffe0);
      mesh->m_workNormals = (S16Vec *)(*(int *)(&Chara.field_0x2068 + iVar1) + *piVar3);
      *piVar3 = *piVar3 + (mesh->m_data->m_normalCount * 6 + 0x1f & 0xffffffe0);
      ab = (float *)mesh->m_data->m_skins;
      for (uVar7 = 0; pCVar6 = mesh->m_data, uVar7 < pCVar6->m_skinCount; uVar7 = uVar7 + 1) {
        PSMTXConcat(&model->m_nodes[(int)((Mtx *)(ab + 0x18))->value[0][0]].m_mtx,(Mtx *)(ab + 0xc),
                    (Mtx *)ab);
        ab = ab + 0x19;
      }
      if (pCVar6->m_infoWord1 != 0) {
        pSVar4 = pCVar6->m_normals;
        pSVar5 = mesh->m_workNormals;
        for (uVar7 = 0; uVar7 < mesh->m_data->m_infoWord1; uVar7 = uVar7 + 1) {
          pSVar5[1].x = pSVar4[1].x;
          pSVar5[1].y = pSVar4[1].y;
          pSVar5[1].z = pSVar4[1].z;
          pSVar5[2].x = pSVar4[2].x;
          pSVar5[2].y = pSVar4[2].y;
          pSVar2 = pSVar4 + 2;
          pSVar4 = pSVar4 + 3;
          pSVar5[2].z = pSVar2->z;
          pSVar5 = pSVar5 + 3;
        }
      }
      pCVar6 = mesh->m_data;
      skin__Q26CChara5CMeshFiiiPQ26CChara5CSkinPvPvPvP6S16VecP6S16VecP6S16VecP6S16Vec
                (mesh,pCVar6->m_oneWeightCountOrSize,pCVar6->m_twoWeightCountOrSize,
                 pCVar6->threeWeightCountOrSize,pCVar6->m_skins,pCVar6->m_oneWeightData,
                 pCVar6->m_twoWeightData,pCVar6->m_threeWeightData,pCVar6->m_vertices,
                 mesh->m_workPositions,pCVar6->m_normals,mesh->m_workNormals);
      DCFlushRange(mesh->m_workPositions,mesh->m_data->m_vertexCount * 6);
      DCFlushRange(mesh->m_workNormals,mesh->m_data->m_normalCount * 6);
    }
  }
  return;
}

