// Function: calcBindMatrix__Q26CChara6CModelFv
// Entry: 800724b8
// Size: 120 bytes

void calcBindMatrix__Q26CChara6CModelFv(CModel *model)

{
  uint uVar1;
  CNode *node;
  
  node = model->m_nodes;
  for (uVar1 = 0; uVar1 < model->m_data->m_nodeCount; uVar1 = uVar1 + 1) {
    if ((short)node->m_refData->m_parentIndex < 0) {
      CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(node,model);
    }
    node = node + 1;
  }
  return;
}

