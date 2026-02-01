// Function: CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
// Entry: 80070604
// Size: 140 bytes

void CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
               (CModel *model,Mtx *param_2,CNode *param_3)

{
  if ((int)((uint)model->m_flagsA0 << 0x1a | (uint)(model->m_flagsA0 >> 6)) < 0) {
    PSMTXCopy(&param_3->m_mtx,param_2);
    param_2->value[0][3] = param_2->value[0][3] + (model->m_drawMtx).value[0][3];
    param_2->value[1][3] = param_2->value[1][3] + (model->m_drawMtx).value[1][3];
    param_2->value[2][3] = param_2->value[2][3] + (model->m_drawMtx).value[2][3];
  }
  else {
    PSMTXCopy(&model->m_localMtx,param_2);
  }
  return;
}

