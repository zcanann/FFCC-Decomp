// Function: pppRenderLocationTitle2
// Entry: 800da0b4
// Size: 836 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderLocationTitle2(pppLocationTitle2 *pppLocationTitle2,UnkB *param_2,UnkC *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  Vec *source;
  undefined4 *puVar4;
  float local_b0;
  Vec local_ac;
  Vec local_a0;
  Vec local_94;
  Vec local_88;
  Vec local_7c;
  Vec local_70;
  Vec local_64;
  Mtx local_58;
  
  iVar2 = *param_3->m_serializedDataOffsets;
  if (param_2->m_dataValIndex != 0xffff) {
    uVar1 = (pppLocationTitle2->field0_0x0).m_graphId;
    source = *(Vec **)((int)(&pppLocationTitle2->field0_0x0 + 2) + iVar2);
    puVar4 = *(undefined4 **)
              (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA + param_2->m_dataValIndex * 4);
    pppSetBlendMode__FUc(*(undefined *)((int)&param_2->m_stepValue + 1));
    if (Game.game.m_currentSceneId != 7) {
      local_a0.x = (pppMngStPtr->m_matrix).value[0][3];
      local_a0.y = (pppMngStPtr->m_matrix).value[1][3];
      local_a0.z = (pppMngStPtr->m_matrix).value[2][3];
      local_64.x = (float)CameraPcs._224_4_;
      local_64.y = (float)CameraPcs._228_4_;
      local_64.z = (float)CameraPcs._232_4_;
      PSVECSubtract(&local_64,&local_a0,&local_70);
      if (((FLOAT_80330f48 == local_70.x) && (FLOAT_80330f48 == local_70.y)) &&
         (FLOAT_80330f48 == local_70.z)) {
        return;
      }
      PSVECNormalize(&local_70,&local_94);
      local_7c.z = -local_94.x;
      local_7c.x = local_94.z;
      local_7c.y = FLOAT_80330f48;
      if ((FLOAT_80330f48 == local_94.z) && (FLOAT_80330f48 == local_7c.z)) {
        local_7c.x = FLOAT_80330f4c;
        local_7c.z = FLOAT_80330f48;
        local_88.x = FLOAT_80330f48;
        local_88.y = FLOAT_80330f48;
        local_88.z = FLOAT_80330f4c;
      }
      else {
        PSVECNormalize(&local_7c,&local_7c);
        PSVECCrossProduct(&local_94,&local_7c,&local_88);
        PSVECNormalize(&local_88,&local_88);
      }
      (pppMngStPtr->m_matrix).value[0][0] = local_7c.x;
      (pppMngStPtr->m_matrix).value[1][0] = local_7c.y;
      (pppMngStPtr->m_matrix).value[2][0] = local_7c.z;
      (pppMngStPtr->m_matrix).value[0][1] = local_88.x;
      (pppMngStPtr->m_matrix).value[1][1] = local_88.y;
      (pppMngStPtr->m_matrix).value[2][1] = local_88.z;
      (pppMngStPtr->m_matrix).value[0][2] = local_94.x;
      (pppMngStPtr->m_matrix).value[1][2] = local_94.y;
      (pppMngStPtr->m_matrix).value[2][2] = local_94.z;
    }
    for (iVar3 = 0;
        iVar3 < (int)(uint)*(ushort *)
                            ((undefined4 *)((int)(&pppLocationTitle2->field0_0x0 + 2) + iVar2) + 1);
        iVar3 = iVar3 + 1) {
      if ((int)(((int)uVar1 >> 0xc) + (uint)((int)uVar1 < 0 && (uVar1 & 0xfff) != 0)) <=
          (int)(uint)*(ushort *)&source[2].y) {
        local_ac.z = FLOAT_80330f48;
        local_ac.y = FLOAT_80330f48;
        local_ac.x = FLOAT_80330f48;
        PSMTXIdentity(&local_58);
        local_58.value[0][0] =
             (pppMngStPtr->m_scale).x * (pppLocationTitle2->field0_0x0).m_localMatrix.value[0][0];
        local_58.value[1][1] =
             (pppMngStPtr->m_scale).y * (pppLocationTitle2->field0_0x0).m_localMatrix.value[1][1];
        local_58.value[2][2] =
             (pppMngStPtr->m_scale).z * (pppLocationTitle2->field0_0x0).m_localMatrix.value[2][2];
        PSMTXMultVec(&pppMngStPtr->m_matrix,source,&local_ac);
        PSMTXMultVec(&ppvCameraMatrix0,&local_ac,&local_ac);
        local_58.value[0][3] = local_ac.x;
        local_58.value[1][3] = local_ac.y;
        local_58.value[2][3] = local_ac.z;
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                  (FLOAT_80330f48,(pppCVector *)(source + 1),(pppFMATRIX *)0x0,0,0,0,0,1,1,1);
        GXSetCullMode(0);
        GXSetColorUpdate(0);
        GXLoadPosMtxImm(&local_58,0);
        if (param_2->m_payload[0xe] != '\0') {
          GXSetColorUpdate(1);
        }
        local_b0 = source[1].x;
        GXSetChanMatColor(4,&local_b0);
        pppDrawShp__FPlsP12CMaterialSetUc
                  (*puVar4,(int)*(short *)((int)&source[2].z + 2),pppEnvStPtr->m_materialSetPtr,
                   *(undefined *)((int)&param_2->m_stepValue + 1));
      }
      source = source + 3;
    }
    GXSetColorUpdate(1);
    GXSetZMode(1,3,0);
  }
  return;
}

