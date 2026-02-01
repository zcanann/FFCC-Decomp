// Function: setup__Q26CChara6CModelFv
// Entry: 80072928
// Size: 444 bytes

/* WARNING: Removing unreachable block (ram,0x80072a5c) */
/* WARNING: Removing unreachable block (ram,0x80072a64) */
/* WARNING: Removing unreachable block (ram,0x80072a74) */
/* WARNING: Removing unreachable block (ram,0x80072a7c) */
/* WARNING: Removing unreachable block (ram,0x80072a94) */
/* WARNING: Removing unreachable block (ram,0x80072a9c) */
/* WARNING: Removing unreachable block (ram,0x80072aac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setup__Q26CChara6CModelFv(CModel *model)

{
  uint8_t uVar1;
  CSkin *pCVar2;
  CMaterialSet *pCVar3;
  uint uVar4;
  uint uVar5;
  CMesh *pCVar6;
  CNode *pCVar7;
  int iVar8;
  
  pCVar7 = model->m_nodes;
  for (uVar5 = 0; uVar5 < model->m_data->m_nodeCount; uVar5 = uVar5 + 1) {
    PSMTXCopy(&pCVar7->m_refData->m_localMtx,(Mtx *)(pCVar7->unk_0x8_0x43 + 0xc));
    uVar1 = pCVar7->m_refData->m_displayIndex;
    if ((-1 < (char)uVar1) && ((uint)(int)(char)uVar1 < model->m_data->m_meshCount)) {
      pCVar7->field1_0x4 = model->m_meshes + (char)uVar1;
    }
    pCVar7 = pCVar7 + 1;
  }
  calcBindMatrix__Q26CChara6CModelFv(model);
  pCVar6 = model->m_meshes;
  for (uVar5 = 0; uVar5 < model->m_data->m_meshCount; uVar5 = uVar5 + 1) {
    iVar8 = 0;
    for (uVar4 = 0; uVar4 < pCVar6->m_data->m_skinCount; uVar4 = uVar4 + 1) {
      pCVar2 = pCVar6->m_data->m_skins;
      PSMTXInverse(&(model->m_nodes[*(int *)(pCVar2 + iVar8 + 0x60)].m_refData)->m_bindWorldMtx,
                   (Mtx *)(pCVar2 + iVar8 + 0x30));
      PSMTXConcat((Mtx *)(pCVar2 + iVar8 + 0x30),
                  &(model->m_nodes[pCVar6->m_data->m_nodeIndex].m_refData)->m_bindWorldMtx,
                  (Mtx *)(pCVar2 + iVar8 + 0x30));
      iVar8 = iVar8 + 100;
    }
    pCVar6 = pCVar6 + 1;
  }
  AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
            (model,(CChara *)model->m_anim,0xffffffff,0xffffffff,0);
  pCVar3 = model->m_data->m_materialSet;
  if (pCVar3 != (CMaterialSet *)0x0) {
    SetTextureSet__12CMaterialSetFP11CTextureSet(pCVar3,model->m_texSet);
  }
  return;
}

