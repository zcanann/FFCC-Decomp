// Function: dynamics__Q26CChara6CModelFPQ26CChara5CNodePQ26CChara5CNode
// Entry: 80071078
// Size: 1612 bytes

/* WARNING: Removing unreachable block (ram,0x800716a0) */
/* WARNING: Removing unreachable block (ram,0x80071698) */
/* WARNING: Removing unreachable block (ram,0x80071690) */
/* WARNING: Removing unreachable block (ram,0x80071098) */
/* WARNING: Removing unreachable block (ram,0x80071090) */
/* WARNING: Removing unreachable block (ram,0x80071088) */

void dynamics__Q26CChara6CModelFPQ26CChara5CNodePQ26CChara5CNode(CModel *model,CNode *node)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  Vec local_2e8;
  Vec local_2dc;
  Vec local_2d0;
  Vec local_2c4;
  Vec local_2b8;
  Vec local_2ac;
  Vec local_2a0;
  Vec local_294;
  Vec local_288;
  Vec local_27c;
  Vec local_270;
  CVector CStack_264;
  CVector CStack_258;
  CVector CStack_24c;
  CVector CStack_240;
  CVector CStack_234;
  CVector CStack_228;
  Vec local_21c;
  Vec local_210;
  Vec local_204;
  Vec local_1f8;
  Vec local_1ec;
  Vec local_1e0;
  CVector local_1d4;
  CVector local_1c8;
  CVector local_1bc;
  CVector local_1b0;
  Vec VStack_1a4;
  Vec local_198;
  Vec local_18c;
  Vec local_180;
  Vec local_174;
  Vec local_168;
  Vec local_15c;
  Vec local_150;
  CVector local_144;
  Mtx MStack_138;
  Mtx MStack_108;
  Mtx local_d8;
  Mtx MStack_a8;
  Mtx MStack_78;
  
  pfVar4 = (float *)((int)model->m_data->m_dynParams + (char)node->m_refData->m_dynParamIndex * 0x24
                    );
  __ct__7CVectorFfff((node->m_mtx).value[0][0],(node->m_mtx).value[1][0],(node->m_mtx).value[2][0],
                     &local_1b0);
  local_144.x = local_1b0.x;
  local_144.y = local_1b0.y;
  local_144.z = local_1b0.z;
  __ct__7CVectorFfff((node->m_mtx).value[0][1],(node->m_mtx).value[1][1],(node->m_mtx).value[2][1],
                     &local_1bc);
  local_150.x = local_1bc.x;
  local_150.y = local_1bc.y;
  local_150.z = local_1bc.z;
  __ct__7CVectorFfff((node->m_mtx).value[0][2],(node->m_mtx).value[1][2],(node->m_mtx).value[2][2],
                     &local_1c8);
  local_15c.x = local_1c8.x;
  local_15c.y = local_1c8.y;
  local_15c.z = local_1c8.z;
  Normalize__7CVectorFv(&local_144);
  __ct__7CVectorFfff((node->m_mtx).value[0][3],(node->m_mtx).value[1][3],(node->m_mtx).value[2][3],
                     &local_1d4);
  local_168.x = local_1d4.x;
  local_168.y = local_1d4.y;
  local_168.z = local_1d4.z;
  dVar9 = (double)node->m_refData->m_boneLen;
  __ct__7CVectorFv(&local_2ac);
  PSVECScale((float)dVar9,(Vec *)&local_144,&local_2ac);
  local_1e0.x = local_2ac.x;
  local_1e0.y = local_2ac.y;
  local_1e0.z = local_2ac.z;
  __ct__7CVectorFv(&local_270);
  PSVECAdd(&local_168,&local_1e0,&local_270);
  local_174.x = local_270.x;
  local_174.y = local_270.y;
  local_174.z = local_270.z;
  if ((int)((uint)model->m_flags0x10C << 0x18) < 0) {
    (node->m_dynPosition).x = local_270.x;
    (node->m_dynPosition).y = local_270.y;
    (node->m_dynPosition).z = local_270.z;
    Identity__7CVectorFv(&node->m_dynVel);
  }
  else {
    dVar5 = (double)RandF__5CMathFv(&Math);
    dVar8 = (double)pfVar4[2];
    dVar5 = (double)(float)((double)FLOAT_803301d0 * dVar5 + (double)FLOAT_803301d0);
    __ct__7CVectorFv(&local_2e8);
    PSVECScale((float)dVar5,(Vec *)&model->m_unkVec_0xC4,&local_2e8);
    local_204.x = local_2e8.x;
    local_204.y = local_2e8.y;
    local_204.z = local_2e8.z;
    __ct__7CVectorFv(&local_2b8);
    PSVECScale((float)dVar8,&local_204,&local_2b8);
    local_1f8.x = local_2b8.x;
    local_1f8.y = local_2b8.y;
    local_1f8.z = local_2b8.z;
    __ct__7CVectorFv(&local_2c4);
    PSVECSubtract(&local_174,(Vec *)&node->m_dynPosition,&local_2c4);
    local_1ec.x = local_2c4.x;
    local_1ec.y = local_2c4.y;
    local_1ec.z = local_2c4.z;
    __ct__7CVectorFv(&local_27c);
    PSVECAdd(&local_1ec,&local_1f8,&local_27c);
    local_180.x = local_27c.x;
    local_180.y = local_27c.y;
    local_180.z = local_27c.z;
    PSVECAdd((Vec *)&node->m_dynVel,&local_180,(Vec *)&node->m_dynVel);
    dVar5 = (double)*pfVar4;
    __ct__7CVectorFv(&local_2d0);
    PSVECScale((float)dVar5,(Vec *)&node->m_dynVel,&local_2d0);
    local_210.x = local_2d0.x;
    local_210.y = local_2d0.y;
    local_210.z = local_2d0.z;
    __ct__7CVectorFv(&local_288);
    PSVECAdd((Vec *)&node->m_dynPosition,&local_210,&local_288);
    local_18c.x = local_288.x;
    local_18c.y = local_288.y;
    local_18c.z = local_288.z;
    PSVECScale(pfVar4[1],(Vec *)&node->m_dynVel,(Vec *)&node->m_dynVel);
    __ct__7CVectorFv(&local_294);
    PSVECSubtract(&local_18c,&local_168,&local_294);
    iVar3 = 0;
    local_198.x = local_294.x;
    local_198.y = local_294.y;
    local_198.z = local_294.z;
    do {
      if (pfVar4[3] != 0.0) {
        if (iVar3 == 0) {
          uVar6 = PSVECDotProduct((Vec *)&local_144,&local_198);
          uVar7 = PSVECDotProduct(&local_15c,&local_198);
          dVar5 = (double)atan2(uVar7,uVar6);
          fVar1 = -(float)dVar5;
        }
        else {
          uVar6 = PSVECDotProduct((Vec *)&local_144,&local_198);
          uVar7 = PSVECDotProduct(&local_150,&local_198);
          dVar5 = (double)atan2(uVar7,uVar6);
          fVar1 = (float)dVar5;
        }
        fVar2 = FLOAT_803301d4 * pfVar4[5];
        if ((fVar1 <= fVar2) || (FLOAT_803301d4 * pfVar4[7] <= fVar1)) {
          if (fVar2 < fVar1) {
            fVar2 = FLOAT_803301d4 * pfVar4[7];
          }
          if (iVar3 == 0) {
            PSMTXRotAxisRad(fVar2 - fVar1,&MStack_78,&local_150);
          }
          else {
            PSMTXRotAxisRad(fVar2 - fVar1,&MStack_78,&local_15c);
          }
          PSMTXMultVecSR(&MStack_78,&local_198,&local_198);
        }
      }
      iVar3 = iVar3 + 1;
      pfVar4 = pfVar4 + 1;
    } while (iVar3 < 2);
    Normalize__7CVectorFv((CVector *)&local_198);
    dVar5 = (double)PSVECDotProduct((Vec *)&local_144,&local_198);
    if (dVar5 <= (double)FLOAT_803301d8) {
      fVar1 = FLOAT_803301e0;
      if ((double)FLOAT_803301dc <= dVar5) {
        dVar5 = (double)acos();
        fVar1 = (float)dVar5;
      }
      dVar5 = (double)fVar1;
      __ct__7CVectorFv(&VStack_1a4);
      PSVECCrossProduct((Vec *)&local_144,&local_198,&VStack_1a4);
      PSMTXRotAxisRad((float)dVar5,&MStack_a8,&VStack_1a4);
      PSMTXCopy(&node->m_mtx,&MStack_138);
      PSMTXCopy(&MStack_a8,&MStack_108);
      pfVar4 = (float *)__ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_264)
      ;
      MStack_138.value[0][3] = *pfVar4;
      iVar3 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_258);
      MStack_138.value[1][3] = *(float *)(iVar3 + 4);
      iVar3 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_24c);
      MStack_138.value[2][3] = *(float *)(iVar3 + 8);
      pfVar4 = (float *)__ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_240)
      ;
      MStack_108.value[0][3] = *pfVar4;
      iVar3 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_234);
      MStack_108.value[1][3] = *(float *)(iVar3 + 4);
      iVar3 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_228);
      MStack_108.value[2][3] = *(float *)(iVar3 + 8);
      PSMTXConcat(&MStack_108,&MStack_138,&local_d8);
      (node->m_mtx).value[0][0] = local_d8.value[0][0];
      (node->m_mtx).value[1][0] = local_d8.value[1][0];
      (node->m_mtx).value[2][0] = local_d8.value[2][0];
      (node->m_mtx).value[0][1] = local_d8.value[0][1];
      (node->m_mtx).value[1][1] = local_d8.value[1][1];
      (node->m_mtx).value[2][1] = local_d8.value[2][1];
      (node->m_mtx).value[0][2] = local_d8.value[0][2];
      (node->m_mtx).value[1][2] = local_d8.value[1][2];
      (node->m_mtx).value[2][2] = local_d8.value[2][2];
    }
    __ct__7CVectorFv(&local_2dc);
    PSVECScale((float)dVar9,&local_198,&local_2dc);
    local_21c.x = local_2dc.x;
    local_21c.y = local_2dc.y;
    local_21c.z = local_2dc.z;
    __ct__7CVectorFv(&local_2a0);
    PSVECAdd(&local_168,&local_21c,&local_2a0);
    (node->m_dynPosition).x = local_2a0.x;
    (node->m_dynPosition).y = local_2a0.y;
    (node->m_dynPosition).z = local_2a0.z;
  }
  return;
}

