// Function: CalcMatrix__Q26CChara6CModelFv
// Entry: 800723a4
// Size: 276 bytes

void CalcMatrix__Q26CChara6CModelFv(CModel *model)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_803301bc;
  fVar1 = FLOAT_803301b0;
  (model->m_worldBaseMtx).value[0][0] = (model->m_localMtx).value[0][0];
  (model->m_worldBaseMtx).value[1][0] = (model->m_localMtx).value[1][0];
  (model->m_worldBaseMtx).value[2][0] = (model->m_localMtx).value[2][0];
  (model->m_worldBaseMtx).value[0][1] = (model->m_localMtx).value[0][1];
  (model->m_worldBaseMtx).value[1][1] = (model->m_localMtx).value[1][1];
  (model->m_worldBaseMtx).value[2][1] = (model->m_localMtx).value[2][1];
  (model->m_worldBaseMtx).value[0][2] = (model->m_localMtx).value[0][2];
  (model->m_worldBaseMtx).value[1][2] = (model->m_localMtx).value[1][2];
  (model->m_worldBaseMtx).value[2][2] = (model->m_localMtx).value[2][2];
  (model->m_worldBaseMtx).value[0][3] = fVar1;
  (model->m_worldBaseMtx).value[1][3] = fVar1;
  (model->m_worldBaseMtx).value[2][3] = fVar1;
  (model->m_drawMtx).value[0][0] = fVar2;
  (model->m_drawMtx).value[1][0] = fVar1;
  (model->m_drawMtx).value[2][0] = fVar1;
  (model->m_drawMtx).value[0][1] = fVar1;
  (model->m_drawMtx).value[1][1] = fVar2;
  (model->m_drawMtx).value[2][1] = fVar1;
  (model->m_drawMtx).value[0][2] = fVar1;
  (model->m_drawMtx).value[1][2] = fVar1;
  (model->m_drawMtx).value[2][2] = fVar2;
  (model->m_drawMtx).value[0][3] = (model->m_localMtx).value[0][3];
  (model->m_drawMtx).value[1][3] = (model->m_localMtx).value[1][3];
  (model->m_drawMtx).value[2][3] = (model->m_localMtx).value[2][3];
  if (model->m_blendCur != 0) {
    model->m_blendCur = model->m_blendCur - 1;
  }
  if (((code *)model->m_beforeCalcMatrixCallback == (code *)0x0) ||
     (iVar3 = (*(code *)model->m_beforeCalcMatrixCallback)(model,model->m_cbUser0,model->m_cbUser1),
     iVar3 != 0)) {
    calcMatrix__Q26CChara6CModelFv(model);
    if (model->m_texAnimSet != (CTexAnimSet *)0x0) {
      AddFrame__11CTexAnimSetFv(model->m_texAnimSet);
    }
  }
  return;
}

