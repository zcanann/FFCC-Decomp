// Function: pppRenderYmMiasma
// Entry: 800907c4
// Size: 736 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmMiasma(pppYmMiasma *pppYmMiasma,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  float *pfVar2;
  undefined4 local_140;
  undefined4 local_13c;
  Vec local_138;
  Vec local_12c;
  pppFMATRIX local_120;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  pppFMATRIX local_c0;
  pppFMATRIX local_90;
  undefined4 local_60;
  uint uStack_5c;
  int local_58;
  undefined4 *local_54;
  float local_50;
  float local_4c;
  
  pfVar2 = *(float **)((int)(&pppYmMiasma->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  local_58 = -0x7fdd1140;
  for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)&param_2->m_stepValue; iVar1 = iVar1 + 1) {
    if (param_2->m_dataValIndex != 0xffff) {
      local_54 = *(undefined4 **)
                  (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                  param_2->m_dataValIndex * 4);
      pppUnitMatrix__FR10pppFMATRIX(&local_120);
      local_120.value[2][2] = pfVar2[0x10];
      local_60 = 0x43300000;
      local_120.value[0][0] = (pppMngStPtr->m_scale).x * local_120.value[2][2];
      local_120.value[1][1] = (pppMngStPtr->m_scale).y * local_120.value[2][2];
      local_120.value[2][2] = (pppMngStPtr->m_scale).z * local_120.value[2][2];
      uStack_5c = (int)*(short *)(pfVar2 + 0xe) ^ 0x80000000;
      PSMTXRotRad(FLOAT_80330640 * (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330648)
                  ,&local_f0,0x7a);
      local_4c = local_c8;
      local_c0.value[2][0] = local_d0;
      local_c0.value[2][2] = local_c8;
      local_50 = local_c4;
      local_90.value[0][0] = local_120.value[0][0];
      local_90.value[0][1] = local_120.value[0][1];
      local_90.value[0][2] = local_120.value[0][2];
      local_90.value[0][3] = local_120.value[0][3];
      local_90.value[1][0] = local_120.value[1][0];
      local_90.value[1][1] = local_120.value[1][1];
      local_90.value[1][2] = local_120.value[1][2];
      local_90.value[1][3] = local_120.value[1][3];
      local_90.value[2][0] = local_120.value[2][0];
      local_90.value[2][1] = local_120.value[2][1];
      local_90.value[2][2] = local_120.value[2][2];
      local_90.value[2][3] = local_120.value[2][3];
      local_c0.value[0][0] = local_f0;
      local_c0.value[0][1] = local_ec;
      local_c0.value[0][2] = local_e8;
      local_c0.value[0][3] = local_e4;
      local_c0.value[1][0] = local_e0;
      local_c0.value[1][1] = local_dc;
      local_c0.value[1][2] = local_d8;
      local_c0.value[1][3] = local_d4;
      local_c0.value[2][1] = local_cc;
      local_c0.value[2][3] = local_c4;
      pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_120,&local_c0,&local_90);
      local_12c.x = *pfVar2;
      local_12c.y = pfVar2[1];
      local_12c.z = pfVar2[2];
      pppCopyVector__FR3Vec3Vec(&local_138,&local_12c);
      if (*(int *)(local_58 + -0x3810) == 7) {
        PSMTXMultVec(&ppvWorldMatrix,&local_138,&local_138);
      }
      else {
        PSMTXMultVec(&ppvCameraMatrix0,&local_138,&local_138);
      }
      local_120.value[0][3] = local_138.x;
      local_120.value[1][3] = local_138.y;
      local_120.value[2][3] = local_138.z;
      pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                (FLOAT_80330644,(pppCVector *)0x0,&local_120,param_2->m_payload[0x61],
                 param_2->m_payload[0x60],param_2->m_payload[0x1e],0,1,1,0);
      local_140 = CONCAT31(CONCAT21(CONCAT11((char)*(undefined2 *)(pfVar2 + 8),
                                             (char)*(undefined2 *)((int)pfVar2 + 0x22)),
                                    (char)*(undefined2 *)(pfVar2 + 9)),
                           (char)*(undefined2 *)((int)pfVar2 + 0x26));
      local_13c = local_140;
      GXSetChanAmbColor(4,&local_13c);
      pppSetBlendMode__FUc(param_2->m_payload[0x1e]);
      pppDrawShp__FPlsP12CMaterialSetUc
                (*local_54,(int)*(short *)((int)pfVar2 + 0x4e),pppEnvStPtr->m_materialSetPtr,
                 param_2->m_payload[0x1e]);
    }
    pfVar2 = pfVar2 + 0x14;
  }
  return;
}

