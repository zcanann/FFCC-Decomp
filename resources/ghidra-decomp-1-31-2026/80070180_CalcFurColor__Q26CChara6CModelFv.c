// Function: CalcFurColor__Q26CChara6CModelFv
// Entry: 80070180
// Size: 108 bytes

void CalcFurColor__Q26CChara6CModelFv(CModel *model)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_803301b0;
  fVar1 = model->m_furTarget - model->m_furCur;
  fVar2 = FLOAT_803301b4;
  if ((FLOAT_803301b4 <= fVar1) && (fVar2 = fVar1, FLOAT_803301b8 < fVar1)) {
    fVar2 = FLOAT_803301b8;
  }
  model->m_furCur = model->m_furCur + fVar2;
  fVar1 = model->m_furCur;
  if ((fVar3 <= fVar1) && (fVar3 = fVar1, FLOAT_803301bc < fVar1)) {
    fVar3 = FLOAT_803301bc;
  }
  model->m_furCur = fVar3;
  return;
}

