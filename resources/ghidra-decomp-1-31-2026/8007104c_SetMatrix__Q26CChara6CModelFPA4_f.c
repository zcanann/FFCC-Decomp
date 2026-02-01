// Function: SetMatrix__Q26CChara6CModelFPA4_f
// Entry: 8007104c
// Size: 44 bytes

void SetMatrix__Q26CChara6CModelFPA4_f(CModel *model,Mtx *param_2)

{
  PSMTXCopy(param_2,&model->m_localMtx);
  return;
}

