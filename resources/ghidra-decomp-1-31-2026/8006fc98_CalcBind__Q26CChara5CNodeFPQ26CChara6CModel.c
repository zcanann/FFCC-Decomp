// Function: CalcBind__Q26CChara5CNodeFPQ26CChara6CModel
// Entry: 8006fc98
// Size: 600 bytes

void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(CNode *node,CModel *model)

{
  CNodeCRefData *pCVar1;
  CNode *pCVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  CNode *pCVar10;
  uint uVar11;
  CNode *pCVar12;
  
  pCVar1 = node->m_refData;
  if ((short)pCVar1->m_parentIndex < 0) {
    PSMTXCopy(&pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
  }
  else {
    PSMTXConcat(&(model->m_nodes[(short)pCVar1->m_parentIndex].m_refData)->m_bindWorldMtx,
                &pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
  }
  PSMTXCopy(&node->m_refData->m_bindWorldMtx,&node->m_mtx);
  iVar4 = 0;
  for (uVar3 = 0; uVar3 < node->m_refData->m_childCount; uVar3 = uVar3 + 1) {
    pCVar2 = model->m_nodes +
             *(ushort *)
              ((int)model->m_data->m_bank + (short)node->m_refData->m_childBankOffset + iVar4);
    pCVar1 = pCVar2->m_refData;
    if ((short)pCVar1->m_parentIndex < 0) {
      PSMTXCopy(&pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
    }
    else {
      PSMTXConcat(&(model->m_nodes[(short)pCVar1->m_parentIndex].m_refData)->m_bindWorldMtx,
                  &pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
    }
    PSMTXCopy(&pCVar2->m_refData->m_bindWorldMtx,&pCVar2->m_mtx);
    iVar5 = 0;
    for (uVar11 = 0; uVar11 < pCVar2->m_refData->m_childCount; uVar11 = uVar11 + 1) {
      pCVar12 = model->m_nodes +
                *(ushort *)
                 ((int)model->m_data->m_bank + (short)pCVar2->m_refData->m_childBankOffset + iVar5);
      pCVar1 = pCVar12->m_refData;
      if ((short)pCVar1->m_parentIndex < 0) {
        PSMTXCopy(&pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
      }
      else {
        PSMTXConcat(&(model->m_nodes[(short)pCVar1->m_parentIndex].m_refData)->m_bindWorldMtx,
                    &pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
      }
      PSMTXCopy(&pCVar12->m_refData->m_bindWorldMtx,&pCVar12->m_mtx);
      iVar6 = 0;
      for (uVar9 = 0; uVar9 < pCVar12->m_refData->m_childCount; uVar9 = uVar9 + 1) {
        pCVar10 = model->m_nodes +
                  *(ushort *)
                   ((int)model->m_data->m_bank +
                   (short)pCVar12->m_refData->m_childBankOffset + iVar6);
        pCVar1 = pCVar10->m_refData;
        if ((short)pCVar1->m_parentIndex < 0) {
          PSMTXCopy(&pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
        }
        else {
          PSMTXConcat(&(model->m_nodes[(short)pCVar1->m_parentIndex].m_refData)->m_bindWorldMtx,
                      &pCVar1->m_localMtx,&pCVar1->m_bindWorldMtx);
        }
        PSMTXCopy(&pCVar10->m_refData->m_bindWorldMtx,&pCVar10->m_mtx);
        iVar7 = 0;
        for (uVar8 = 0; uVar8 < pCVar10->m_refData->m_childCount; uVar8 = uVar8 + 1) {
          CalcBind__Q26CChara5CNodeFPQ26CChara6CModel
                    (model->m_nodes +
                     *(ushort *)
                      ((int)model->m_data->m_bank +
                      (short)pCVar10->m_refData->m_childBankOffset + iVar7),model);
          iVar7 = iVar7 + 2;
        }
        iVar6 = iVar6 + 2;
      }
      iVar5 = iVar5 + 2;
    }
    iVar4 = iVar4 + 2;
  }
  return;
}

