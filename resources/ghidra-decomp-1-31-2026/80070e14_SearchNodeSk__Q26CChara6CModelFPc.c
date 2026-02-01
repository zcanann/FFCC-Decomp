// Function: SearchNodeSk__Q26CChara6CModelFPc
// Entry: 80070e14
// Size: 428 bytes

uint SearchNodeSk__Q26CChara6CModelFPc(CModel *model,char *param_2)

{
  int iVar1;
  CNode *pCVar2;
  uint uVar3;
  
  if (*param_2 == '_') {
    if ((param_2[1] == 's') && (param_2[2] == 'k')) {
      pCVar2 = model->m_nodes;
      for (uVar3 = 0; uVar3 < model->m_data->m_nodeCount; uVar3 = uVar3 + 1) {
        iVar1 = strlen(pCVar2->m_refData->m_name);
        if ((0 < iVar1 + -3) &&
           (iVar1 = strcmp(pCVar2->m_refData->m_name + iVar1 + -3,param_2), iVar1 == 0)) {
          return uVar3;
        }
        pCVar2 = pCVar2 + 1;
      }
    }
    else if ((param_2[1] == 'r') &&
            (((param_2[2] == 'o' && (param_2[3] == 'o')) && (param_2[4] == 't')))) {
      pCVar2 = model->m_nodes;
      for (uVar3 = 0; uVar3 < model->m_data->m_nodeCount; uVar3 = uVar3 + 1) {
        iVar1 = strlen(pCVar2->m_refData->m_name);
        if ((0 < iVar1 + -5) &&
           (iVar1 = strcmp(pCVar2->m_refData->m_name + iVar1 + -5,param_2), iVar1 == 0)) {
          return uVar3;
        }
        pCVar2 = pCVar2 + 1;
      }
    }
  }
  else {
    pCVar2 = model->m_nodes;
    for (uVar3 = 0; uVar3 < model->m_data->m_nodeCount; uVar3 = uVar3 + 1) {
      iVar1 = strcmp(pCVar2->m_refData->m_name,param_2);
      if (iVar1 == 0) {
        return uVar3;
      }
      pCVar2 = pCVar2 + 1;
    }
  }
  return 0xffffffff;
}

