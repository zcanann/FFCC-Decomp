// Function: calcMatrix__Q26CChara6CModelFv
// Entry: 80071b64
// Size: 1936 bytes

/* WARNING: Removing unreachable block (ram,0x800722d8) */
/* WARNING: Removing unreachable block (ram,0x800722d0) */
/* WARNING: Removing unreachable block (ram,0x80071b7c) */
/* WARNING: Removing unreachable block (ram,0x80071b74) */

void calcMatrix__Q26CChara6CModelFv(CModel *model)

{
  float fVar1;
  uint16_t uVar2;
  CModelCRefData *pCVar3;
  float *pfVar4;
  int iVar5;
  uint uVar6;
  CNodeCRefData *source;
  uint uVar7;
  CNode *node;
  uint uVar8;
  CNode *pCVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  CVector CStack_238;
  CVector CStack_22c;
  CVector CStack_220;
  CVector CStack_214;
  CVector CStack_208;
  CVector CStack_1fc;
  Vec VStack_1f0;
  Vec VStack_1e4;
  Vec VStack_1d8;
  Vec VStack_1cc;
  Vec local_1c0;
  Vec local_1b4;
  Vec local_1a8;
  Quat QStack_19c;
  Mtx MStack_18c;
  Mtx MStack_15c;
  Mtx local_12c;
  Mtx MStack_fc;
  Mtx MStack_cc;
  Mtx MStack_9c;
  undefined auStack_6c [12];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (model->m_anim == (CAnim *)0x0) {
    dVar10 = (double)FLOAT_803301b0;
  }
  else {
    dVar12 = (double)model->m_animStart;
    dVar10 = (double)FLOAT_803301bc;
    dVar13 = (double)(float)(dVar10 + (double)(float)((double)model->m_animEnd - dVar12));
    if (((byte)model->m_anim[8] >> 6 & 1) == 0) {
      dVar10 = (double)model->m_time;
      if ((double)FLOAT_803301b0 <= dVar10) {
        dVar10 = (double)fmod(dVar10,dVar13);
        dVar10 = (double)(model->m_animStart + (float)dVar10);
      }
      else {
        dVar10 = (double)fmod(-dVar10,dVar13);
        dVar10 = (double)(((float)((double)model->m_animStart + dVar13) - FLOAT_803301bc) -
                         (float)dVar10);
      }
    }
    else {
      dVar11 = (double)model->m_time;
      if ((double)FLOAT_803301b0 <= dVar11) {
        dVar10 = (double)(float)(dVar13 - dVar10);
        if (dVar11 < dVar10) {
          dVar10 = dVar11;
        }
        dVar10 = (double)(float)(dVar12 + dVar10);
      }
      else {
        dVar10 = (double)(float)(dVar13 - dVar10);
        if (-dVar11 < dVar10) {
          dVar10 = -dVar11;
        }
        dVar10 = (double)(float)((double)((float)(dVar12 + dVar13) - FLOAT_803301bc) - dVar10);
      }
    }
  }
  model->m_curFrame = (float)dVar10;
  if (model->m_anim != (CAnim *)0x0) {
    InitQuantize__Q26CChara5CAnimFv();
  }
  node = model->m_nodes;
  uVar8 = model->m_data->m_nodeCount;
  for (uVar7 = 0; uVar7 < uVar8; uVar7 = uVar7 + 1) {
    source = node->m_refData;
    if ((short)source->m_parentIndex < 0) {
      pCVar9 = (CNode *)0x0;
    }
    else {
      pCVar9 = model->m_nodes + (short)source->m_parentIndex;
    }
    if ((node->m_animNode0 == (void *)0x0) && (node->m_animNode1 == (void *)0x0)) {
      if ((int)((uint)node->m_flags << 0x18) < 0) {
        PSMTXCopy(&source->m_localMtx,(Mtx *)(node->unk_0x8_0x43 + 0xc));
      }
    }
    else {
      if ((pCVar9 == (CNode *)0x0) ||
         ((pCVar9->m_animNode0 == (void *)0x0 || (-1 < *(char *)((int)pCVar9->m_animNode0 + 0x14))))
         ) {
        if ((int)((uint)node->m_flags << 0x18) < 0) {
          if ((pCVar9 == (CNode *)0x0) &&
             (fVar1 = model->m_data->m_baseScale, FLOAT_803301bc != fVar1)) {
            PSMTXScale(fVar1,fVar1,fVar1,(Mtx *)(node->unk_0x8_0x43 + 0xc));
          }
          else {
            PSMTXIdentity((Mtx *)(node->unk_0x8_0x43 + 0xc));
          }
        }
      }
      else if ((int)((uint)node->m_flags << 0x18) < 0) {
        PSMTXScale(FLOAT_803301bc / *(float *)pCVar9->unk_0x8_0x43,
                   FLOAT_803301bc / *(float *)(pCVar9->unk_0x8_0x43 + 4),
                   FLOAT_803301bc / *(float *)(pCVar9->unk_0x8_0x43 + 8),
                   (Mtx *)(node->unk_0x8_0x43 + 0xc));
      }
      if (source->m_useParentLenX != '\0') {
        *(float *)(node->unk_0x8_0x43 + 0x18) = pCVar9->m_refData->m_boneLen;
      }
      if (node->m_animNode1 != (void *)0x0) {
        Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
                  (dVar10,node->m_animNode1,model->m_anim,auStack_6c);
        if (*(char *)((int)node->m_animNode1 + 0x14) < '\0') {
          SRTToMatrix__5CMathFPA4_fP3SRT(&Math,&MStack_9c,auStack_6c);
        }
        else {
          SRTToMatrixRT__5CMathFPA4_fP3SRT(&Math,&MStack_9c,auStack_6c);
        }
        PSMTXConcat((Mtx *)(node->unk_0x8_0x43 + 0xc),&MStack_9c,(Mtx *)(node->unk_0x8_0x43 + 0xc));
        PSMTXScale(FLOAT_803301bc / local_54,FLOAT_803301bc / local_50,FLOAT_803301bc / local_4c,
                   &MStack_9c);
        PSMTXConcat((Mtx *)(node->unk_0x8_0x43 + 0xc),&MStack_9c,(Mtx *)(node->unk_0x8_0x43 + 0xc));
      }
      fVar1 = FLOAT_803301b0;
      if (node->m_animNode0 == (void *)0x0) {
        *(float *)(node->unk_0x8_0x43 + 8) = FLOAT_803301b0;
        *(float *)(node->unk_0x8_0x43 + 4) = fVar1;
        *(float *)node->unk_0x8_0x43 = fVar1;
      }
      else {
        Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
                  (dVar10,node->m_animNode0,model->m_anim,auStack_6c);
        pCVar3 = model->m_data;
        uVar2 = source->m_index;
        if (((uVar2 == pCVar3->m_chest1Index) || (uVar2 == pCVar3->m_chest2Index)) ||
           (uVar2 == pCVar3->m_chest3Index)) {
          if (uVar2 == pCVar3->m_chest3Index) {
            local_5c = -(model->m_chestAmp * FLOAT_803301d0 - local_5c);
            fVar1 = FLOAT_803301d0;
          }
          else {
            local_60 = model->m_chestAmp * FLOAT_803301f8 + local_60;
            fVar1 = FLOAT_803301f8;
          }
          local_58 = model->m_chestTilt * fVar1 + local_58;
        }
        else if ((uVar2 == pCVar3->m_headIndex) && (model->m_texAnimSet != (CTexAnimSet *)0x0)) {
          local_58 = local_58 + *(float *)&model->m_texAnimSet->field_0x24;
        }
        if (*(char *)((int)node->m_animNode0 + 0x14) < '\0') {
          SRTToMatrix__5CMathFPA4_fP3SRT(&Math,&MStack_9c,auStack_6c);
        }
        else {
          SRTToMatrixRT__5CMathFPA4_fP3SRT(&Math,&MStack_9c,auStack_6c);
        }
        if ((int)((uint)node->m_flags << 0x18) < 0) {
          PSMTXConcat((Mtx *)(node->unk_0x8_0x43 + 0xc),&MStack_9c,(Mtx *)(node->unk_0x8_0x43 + 0xc)
                     );
        }
        *(float *)node->unk_0x8_0x43 = local_54;
        *(float *)(node->unk_0x8_0x43 + 4) = local_50;
        *(float *)(node->unk_0x8_0x43 + 8) = local_4c;
      }
    }
    uVar6 = (uint)model->m_blendCur;
    if (uVar6 != 0) {
      uStack_3c = (uint)model->m_blendMax;
      local_1a8.x = *(float *)(node->unk_0x8_0x43 + 0x18);
      local_40 = 0x43300000;
      local_1a8.y = *(float *)(node->unk_0x8_0x43 + 0x28);
      local_48 = 0x43300000;
      local_1a8.z = *(float *)(node->unk_0x8_0x43 + 0x38);
      dVar12 = -(double)((float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_803301f0) *
                         (FLOAT_803301bc /
                         (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_803301f0)) -
                        FLOAT_803301bc);
      uStack_44 = uVar6;
      MTXGetScale__5CMathFPA4_fP3Vec(&Math,(Mtx *)(node->unk_0x8_0x43 + 0xc),&local_1b4);
      if (FLOAT_803301e4 <= local_1b4.x) {
        PSVECScale((float)((double)FLOAT_803301bc - dVar12),&node->m_previousScale,&VStack_1d8);
        PSVECScale((float)dVar12,&local_1b4,&VStack_1cc);
        PSVECAdd(&VStack_1d8,&VStack_1cc,&local_1b4);
      }
      else {
        local_1b4.y = FLOAT_803301e8;
        local_1b4.z = FLOAT_803301e8;
      }
      PSVECScale((float)((double)FLOAT_803301bc - dVar12),&node->m_previousPosition,&VStack_1f0);
      PSVECScale((float)dVar12,&local_1a8,&VStack_1e4);
      PSVECAdd(&VStack_1f0,&VStack_1e4,&local_1a8);
      C_QUATMtx(&QStack_19c,(Mtx *)(node->unk_0x8_0x43 + 0xc));
      C_QUATSlerp(dVar12,&node->m_previousQuat,&QStack_19c,&QStack_19c);
      PSMTXScale(local_1b4.x,local_1b4.y,local_1b4.z,&MStack_cc);
      PSMTXQuat((Mtx *)(node->unk_0x8_0x43 + 0xc),&QStack_19c);
      PSMTXConcat((Mtx *)(node->unk_0x8_0x43 + 0xc),&MStack_cc,(Mtx *)(node->unk_0x8_0x43 + 0xc));
      *(float *)(node->unk_0x8_0x43 + 0x18) = local_1a8.x;
      *(float *)(node->unk_0x8_0x43 + 0x28) = local_1a8.y;
      *(float *)(node->unk_0x8_0x43 + 0x38) = local_1a8.z;
    }
    if (pCVar9 == (CNode *)0x0) {
      PSMTXConcat(&model->m_worldBaseMtx,(Mtx *)(node->unk_0x8_0x43 + 0xc),&node->m_mtx);
    }
    else {
      PSMTXConcat(&pCVar9->m_mtx,(Mtx *)(node->unk_0x8_0x43 + 0xc),&node->m_mtx);
    }
    if (-1 < (char)source->m_dynParamIndex) {
      dynamics__Q26CChara6CModelFPQ26CChara5CNodePQ26CChara5CNode(model,node);
    }
    if ((source->m_index == model->m_data->m_chest1Index) && (FLOAT_803301b0 != model->m_twistAngle)
       ) {
      local_1c0.x = DAT_801d9078;
      local_1c0.y = DAT_801d907c;
      local_1c0.z = DAT_801d9080;
      PSMTXMultVecSR(&model->m_worldBaseMtx,&local_1c0,&local_1c0);
      PSMTXRotAxisRad(model->m_twistAngle,&MStack_fc,&local_1c0);
      PSMTXCopy(&node->m_mtx,&MStack_18c);
      PSMTXCopy(&MStack_fc,&MStack_15c);
      pfVar4 = (float *)__ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_238)
      ;
      MStack_18c.value[0][3] = *pfVar4;
      iVar5 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_22c);
      MStack_18c.value[1][3] = *(float *)(iVar5 + 4);
      iVar5 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_220);
      MStack_18c.value[2][3] = *(float *)(iVar5 + 8);
      pfVar4 = (float *)__ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_214)
      ;
      MStack_15c.value[0][3] = *pfVar4;
      iVar5 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_208);
      MStack_15c.value[1][3] = *(float *)(iVar5 + 4);
      iVar5 = __ct__7CVectorFfff(FLOAT_803301b0,FLOAT_803301b0,FLOAT_803301b0,&CStack_1fc);
      MStack_15c.value[2][3] = *(float *)(iVar5 + 8);
      PSMTXConcat(&MStack_15c,&MStack_18c,&local_12c);
      (node->m_mtx).value[0][0] = local_12c.value[0][0];
      (node->m_mtx).value[1][0] = local_12c.value[1][0];
      (node->m_mtx).value[2][0] = local_12c.value[2][0];
      (node->m_mtx).value[0][1] = local_12c.value[0][1];
      (node->m_mtx).value[1][1] = local_12c.value[1][1];
      (node->m_mtx).value[2][1] = local_12c.value[2][1];
      (node->m_mtx).value[0][2] = local_12c.value[0][2];
      (node->m_mtx).value[1][2] = local_12c.value[1][2];
      (node->m_mtx).value[2][2] = local_12c.value[2][2];
    }
    node = node + 1;
  }
  model->m_flags0x10C = model->m_flags0x10C & 0x7f;
  return;
}

