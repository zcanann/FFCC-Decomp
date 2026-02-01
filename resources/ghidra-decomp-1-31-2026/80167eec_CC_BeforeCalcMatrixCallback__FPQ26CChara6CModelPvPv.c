// Function: CC_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv
// Entry: 80167eec
// Size: 580 bytes

/* WARNING: Removing unreachable block (ram,0x80168108) */
/* WARNING: Removing unreachable block (ram,0x80168100) */
/* WARNING: Removing unreachable block (ram,0x80167f04) */
/* WARNING: Removing unreachable block (ram,0x80167efc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CC_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(CModel *model,float *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  float local_f8;
  float local_f4;
  float local_f0;
  Vec local_ec;
  Vec local_e0;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  Vec local_bc;
  float local_b0;
  float local_ac;
  float local_a8;
  Vec local_a4;
  Mtx MStack_98;
  Mtx MStack_68;
  
  fVar1 = param_2[0x10];
  local_b0 = (float)CameraPcs._236_4_;
  local_ac = (float)CameraPcs._240_4_;
  local_a8 = (float)CameraPcs._244_4_;
  local_bc.x = (float)CameraPcs._224_4_;
  local_bc.y = (float)CameraPcs._228_4_;
  local_bc.z = (float)CameraPcs._232_4_;
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_68);
  local_a4.z = *param_2;
  local_a4.x = local_a4.z * local_b0;
  local_a4.y = local_a4.z * local_ac;
  local_a4.z = local_a4.z * local_a8;
  if (Game.game.m_currentSceneId == 7) {
    PSMTXInverse(&ppvCameraMatrix0,&MStack_98);
  }
  else {
    PSMTXInverse(&MStack_68,&MStack_98);
  }
  PSMTXIdentity(&model->m_drawMtx);
  PSMTXIdentity(&model->m_worldBaseMtx);
  PSMTXConcat(&MStack_98,&model->m_worldBaseMtx,&model->m_worldBaseMtx);
  PSVECAdd(&local_bc,&local_a4,&local_a4);
  dVar3 = (double)*(float *)((int)fVar1 + 0x1c);
  dVar2 = (double)*(float *)((int)fVar1 + 0x2c);
  local_f8 = local_b0;
  local_f4 = local_ac;
  local_f0 = local_a8;
  GetDirectVector__5CUtilFP3VecP3Vec3Vec((CUtil *)&DAT_8032ec70,&local_c8,&local_d4,&local_f8);
  local_e0.x = (float)(dVar3 * (double)local_c8);
  local_e0.y = (float)(dVar3 * (double)local_c4);
  local_e0.z = (float)(dVar3 * (double)local_c0);
  local_ec.x = (float)(dVar2 * (double)local_d4);
  local_ec.y = (float)(dVar2 * (double)local_d0);
  local_ec.z = (float)(dVar2 * (double)local_cc);
  PSVECAdd(&local_a4,&local_e0,&local_a4);
  PSVECAdd(&local_a4,&local_ec,&local_a4);
  fVar1 = FLOAT_803331a8;
  (model->m_worldBaseMtx).value[0][3] = FLOAT_803331a8;
  (model->m_worldBaseMtx).value[1][3] = fVar1;
  (model->m_worldBaseMtx).value[2][3] = fVar1;
  if (Game.game.m_currentSceneId == 7) {
    (model->m_drawMtx).value[0][3] = fVar1;
    (model->m_drawMtx).value[1][3] = fVar1;
    (model->m_drawMtx).value[2][3] = fVar1;
  }
  else {
    (model->m_drawMtx).value[0][3] = local_a4.x;
    (model->m_drawMtx).value[1][3] = local_a4.y;
    (model->m_drawMtx).value[2][3] = local_a4.z;
  }
  PSMTXCopy(&model->m_worldBaseMtx,(Mtx *)(param_2 + 4));
  param_2[7] = local_a4.x;
  param_2[0xb] = local_a4.y;
  param_2[0xf] = local_a4.z;
  return 1;
}

