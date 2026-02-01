// Function: GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f
// Entry: 800e591c
// Size: 1808 bytes

/* WARNING: Removing unreachable block (ram,0x800e6008) */
/* WARNING: Removing unreachable block (ram,0x800e5ac4) */
/* WARNING: Removing unreachable block (ram,0x800e592c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(double param_1,undefined4 *param_2,Vec *param_3)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  void *pvVar5;
  CModel *model;
  double dVar6;
  Vec local_118;
  Vec local_10c;
  Vec local_100;
  Vec local_f4;
  Vec local_e8;
  Vec local_dc;
  Vec local_d0;
  Vec local_c4;
  Vec local_b8;
  Vec local_ac;
  Vec local_a0;
  Vec local_94;
  Vec local_88;
  pppFMATRIX local_78;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  
  if (Game.game.m_currentSceneId == 7) {
    pvVar5 = (void *)((int)PartMng.m_recvBuff + *(short *)((int)param_2 + 0x76) * 0x60);
  }
  else {
    pvVar5 = (void *)(*(int *)*param_2 + *(short *)((int)param_2 + 0x76) * 0x60 + 0x20);
  }
  if (param_2[0x36] == 0) {
    return 0;
  }
  iVar4 = *(int *)(param_2[0x36] + 0xf8);
  if (iVar4 == 0) {
    return 0;
  }
  model = *(CModel **)(iVar4 + 0x168);
  if (model == (CModel *)0x0) {
    return 0;
  }
  iVar4 = SearchNodeSk__Q26CChara6CModelFPc(model,(int)pvVar5 + 0x50);
  if (iVar4 == -1) {
    return 0;
  }
  if (model->m_anim == (CAnim *)0x0) {
    uStack_3c = 0;
  }
  else {
    uStack_3c = (uint)*(ushort *)(model->m_anim + 0x10);
  }
  iVar1 = (int)model->m_time;
  local_48 = (longlong)iVar1;
  local_40 = 0x43300000;
  local_30 = 0x43300000;
  iVar2 = (int)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_803311a8);
  local_38 = (longlong)iVar2;
  uStack_2c = iVar1 - (iVar1 / iVar2) * iVar2 ^ 0x80000000;
  dVar6 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803311d8);
  if (dVar6 < (double)FLOAT_80331190) {
    return 0;
  }
  if (dVar6 != (double)FLOAT_80331180) {
    dVar6 = (double)(float)(dVar6 - (double)FLOAT_80331184);
  }
  CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f
            ((double)(float)(dVar6 + param_1),model,model->m_nodes + iVar4,param_3);
  bVar3 = *(byte *)(param_2 + 0x3b);
  if (bVar3 == 3) {
    pppGetRotMatrixYZX__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
  }
  else if (bVar3 < 3) {
    if (bVar3 == 1) {
      pppGetRotMatrixXZY__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
    }
    else if (bVar3 == 0) {
      pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
    }
    else {
      pppGetRotMatrixYXZ__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
    }
  }
  else if (bVar3 == 5) {
    pppGetRotMatrixZYX__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
  }
  else if (bVar3 < 5) {
    pppGetRotMatrixZXY__FR10pppFMATRIXP11pppIVECTOR4(&local_78,(pppIVECTOR4 *)(param_2 + 6));
  }
  bVar3 = *(byte *)((int)param_2 + 0xe7);
  if (bVar3 == 5) {
    if (param_2[0x38] != 0) {
      param_3[1].x = param_3[1].x + (pppMngStPtr->m_position).x;
      param_3[2].y = param_3[2].y + (pppMngStPtr->m_position).y;
      param_3[3].z = param_3[3].z + (pppMngStPtr->m_position).z;
      PSMTXConcat((Mtx *)param_3,&local_78,&local_78);
      if (FLOAT_80331184 != (float)param_2[10]) {
        local_b8.x = local_78.value[0][0];
        local_b8.y = local_78.value[1][0];
        local_b8.z = local_78.value[2][0];
        PSVECScale((float)param_2[10],&local_b8,&local_b8);
        local_78.value[0][0] = local_b8.x;
        local_78.value[1][0] = local_b8.y;
        local_78.value[2][0] = local_b8.z;
      }
      if (FLOAT_80331184 != (float)param_2[0xb]) {
        local_c4.x = local_78.value[0][1];
        local_c4.y = local_78.value[1][1];
        local_c4.z = local_78.value[2][1];
        PSVECScale((float)param_2[0xb],&local_c4,&local_c4);
        local_78.value[0][1] = local_c4.x;
        local_78.value[1][1] = local_c4.y;
        local_78.value[2][1] = local_c4.z;
      }
      if (FLOAT_80331184 != (float)param_2[0xc]) {
        local_d0.x = local_78.value[0][2];
        local_d0.y = local_78.value[1][2];
        local_d0.z = local_78.value[2][2];
        PSVECScale((float)param_2[0xc],&local_d0,&local_d0);
        local_78.value[0][2] = local_d0.x;
        local_78.value[1][2] = local_d0.y;
        local_78.value[2][2] = local_d0.z;
      }
      goto LAB_800e5ff8;
    }
  }
  else if (bVar3 < 5) {
    if ((bVar3 == 3) && (param_2[0x38] != 0)) {
      PSMTXMultVecSR((Mtx *)param_3,&pppMngStPtr->m_position,&local_88);
      param_3[1].x = param_3[1].x + local_88.x;
      param_3[2].y = param_3[2].y + local_88.y;
      param_3[3].z = param_3[3].z + local_88.z;
      PSMTXConcat((Mtx *)param_3,&local_78,&local_78);
      local_94.x = local_78.value[0][0];
      local_94.y = local_78.value[1][0];
      local_94.z = local_78.value[2][0];
      PSVECScale((float)param_2[10],&local_94,&local_94);
      local_78.value[0][0] = local_94.x;
      local_78.value[1][0] = local_94.y;
      local_78.value[2][0] = local_94.z;
      local_a0.x = local_78.value[0][1];
      local_a0.y = local_78.value[1][1];
      local_a0.z = local_78.value[2][1];
      PSVECScale((float)param_2[0xb],&local_a0,&local_a0);
      local_78.value[0][1] = local_a0.x;
      local_78.value[1][1] = local_a0.y;
      local_78.value[2][1] = local_a0.z;
      local_ac.x = local_78.value[0][2];
      local_ac.y = local_78.value[1][2];
      local_ac.z = local_78.value[2][2];
      PSVECScale((float)param_2[0xc],&local_ac,&local_ac);
      local_78.value[0][2] = local_ac.x;
      local_78.value[1][2] = local_ac.y;
      local_78.value[2][2] = local_ac.z;
      goto LAB_800e5ff8;
    }
  }
  else if ((bVar3 < 7) && (param_2[0x38] != 0)) {
    PSVECNormalize(param_3,param_3);
    PSVECNormalize((Vec *)&param_3[1].y,(Vec *)&param_3[1].y);
    PSVECNormalize((Vec *)&param_3[2].z,(Vec *)&param_3[2].z);
    PSMTXMultVecSR((Mtx *)param_3,&pppMngStPtr->m_position,&local_88);
    PSMTXConcat((Mtx *)param_3,&local_78,&local_78);
    if (FLOAT_80331184 != (float)param_2[10]) {
      local_dc.x = local_78.value[0][0];
      local_dc.y = local_78.value[1][0];
      local_dc.z = local_78.value[2][0];
      PSVECScale((float)param_2[10],&local_dc,&local_dc);
      local_78.value[0][0] = local_dc.x;
      local_78.value[1][0] = local_dc.y;
      local_78.value[2][0] = local_dc.z;
    }
    if (FLOAT_80331184 != (float)param_2[0xb]) {
      local_e8.x = local_78.value[0][1];
      local_e8.y = local_78.value[1][1];
      local_e8.z = local_78.value[2][1];
      PSVECScale((float)param_2[0xb],&local_e8,&local_e8);
      local_78.value[0][1] = local_e8.x;
      local_78.value[1][1] = local_e8.y;
      local_78.value[2][1] = local_e8.z;
    }
    if (FLOAT_80331184 != (float)param_2[0xc]) {
      local_f4.x = local_78.value[0][2];
      local_f4.y = local_78.value[1][2];
      local_f4.z = local_78.value[2][2];
      PSVECScale((float)param_2[0xc],&local_f4,&local_f4);
      local_78.value[0][2] = local_f4.x;
      local_78.value[1][2] = local_f4.y;
      local_78.value[2][2] = local_f4.z;
    }
    goto LAB_800e5ff8;
  }
  if (FLOAT_80331184 != (float)param_2[10]) {
    local_100.x = local_78.value[0][0];
    local_100.y = local_78.value[1][0];
    local_100.z = local_78.value[2][0];
    PSVECScale((float)param_2[10],&local_100,&local_100);
    local_78.value[0][0] = local_100.x;
    local_78.value[1][0] = local_100.y;
    local_78.value[2][0] = local_100.z;
  }
  if (FLOAT_80331184 != (float)param_2[0xb]) {
    local_10c.x = local_78.value[0][1];
    local_10c.y = local_78.value[1][1];
    local_10c.z = local_78.value[2][1];
    PSVECScale((float)param_2[0xb],&local_10c,&local_10c);
    local_78.value[0][1] = local_10c.x;
    local_78.value[1][1] = local_10c.y;
    local_78.value[2][1] = local_10c.z;
  }
  if (FLOAT_80331184 != (float)param_2[0xc]) {
    local_118.x = local_78.value[0][2];
    local_118.y = local_78.value[1][2];
    local_118.z = local_78.value[2][2];
    PSVECScale((float)param_2[0xc],&local_118,&local_118);
    local_78.value[0][2] = local_118.x;
    local_78.value[1][2] = local_118.y;
    local_78.value[2][2] = local_118.z;
  }
  local_78.value[0][3] = (float)param_2[2];
  local_78.value[1][3] = (float)param_2[3];
  local_78.value[2][3] = (float)param_2[4];
LAB_800e5ff8:
  PSMTXCopy(&local_78,(Mtx *)param_3);
  return 1;
}

