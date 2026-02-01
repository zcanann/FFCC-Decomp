// Function: SearchNode__Q26CChara6CModelFPc
// Entry: 80070fc0
// Size: 140 bytes

uint SearchNode__Q26CChara6CModelFPc(CModel *model,char *param_2)

{
  int iVar1;
  uint uVar2;
  CNode *pCVar3;
  
  uVar2 = 0;
  pCVar3 = model->m_nodes;
  while( true ) {
    if (model->m_data->m_nodeCount <= uVar2) {
      return 0xffffffff;
    }
    iVar1 = strcmp(pCVar3->m_refData->m_name,param_2);
    if (iVar1 == 0) break;
    uVar2 = uVar2 + 1;
    pCVar3 = pCVar3 + 1;
  }
  return uVar2;
}

