// Function: __ct__Q26CChara6CModelFv
// Entry: 800736e4
// Size: 308 bytes

CModel * __ct__Q26CChara6CModelFv(CModel *model)

{
  float fVar1;
  float fVar2;
  
  __ct__4CRefFv(&model->ref);
  (model->ref).vtable = &PTR_PTR_s_CChara_CModel_801fccf4;
  __ct__7CVectorFv(&model->m_unkVec_0xC4);
  model->m_data = (CModelCRefData *)0x0;
  model->m_texSet = (CTextureSet *)0x0;
  model->m_anim = (CAnim *)0x0;
  model->m_texAnimSet = (CTexAnimSet *)0x0;
  model->m_nodes = (CNode *)0x0;
  model->m_meshes = (CMesh *)0x0;
  PSMTXIdentity(&model->m_localMtx);
  fVar2 = FLOAT_803301fc;
  model->m_furLenScale = FLOAT_803301e4;
  fVar1 = FLOAT_803301b0;
  model->m_furStep = fVar2;
  fVar2 = FLOAT_803301bc;
  model->m_time = fVar1;
  model->m_curFrame = fVar1;
  (model->m_unkVec_0xC4).x = fVar1;
  (model->m_unkVec_0xC4).y = fVar1;
  (model->m_unkVec_0xC4).z = fVar1;
  model->m_blendCur = 0;
  model->m_blendMax = 0;
  model->m_meshVisibleMask = 0xffffffff;
  model->m_animStart = fVar1;
  model->m_animEnd = fVar1;
  model->m_chestTilt = fVar1;
  model->m_chestAmp = fVar1;
  model->m_lightAlpha = fVar2;
  model->m_cbUser0 = (void *)0x0;
  model->m_cbUser1 = (void *)0x0;
  model->m_beforeDrawModelCallback = (void *)0x0;
  model->m_beforeCalcMatrixCallback = (void *)0x0;
  model->m_beforeMeshCallback = (void *)0x0;
  model->m_customMeshDrawCallback = (void *)0x0;
  model->m_afterMeshDrawCallback = (void *)0x0;
  model->m_unknownCallback0x100 = (void *)0x0;
  model->m_afterMeshEnvCallback = (void *)0x0;
  model->m_afterDrawModelCallback = (void *)0x0;
  model->m_flags0x10C = model->m_flags0x10C & 0x7f | 0x80;
  model->m_flagsA0 = model->m_flagsA0 & 0x7f;
  model->m_flagsA0 = model->m_flagsA0 & 0xbf;
  model->m_flagsA0 = model->m_flagsA0 & 0xdf | 0x20;
  model->m_flags0x10C = model->m_flags0x10C & 0xbf;
  model->m_furTarget = fVar2;
  model->m_furCur = fVar2;
  model->m_attachMode = '\0';
  model->m_twistAngle = fVar1;
  return model;
}

