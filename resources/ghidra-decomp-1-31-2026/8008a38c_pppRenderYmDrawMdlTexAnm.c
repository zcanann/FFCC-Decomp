// Function: pppRenderYmDrawMdlTexAnm
// Entry: 8008a38c
// Size: 632 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmDrawMdlTexAnm(pppYmDrawMdlTexAnm *pppYmDrawMdlTexAnm,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  pppModelSt *pppModelSt;
  pppFMATRIX local_150;
  pppFMATRIX local_120;
  pppFMATRIX local_f0;
  pppFMATRIX local_c0;
  pppFMATRIX local_90;
  float local_60;
  float local_5c;
  float local_58;
  
  pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
  if (pppModelSt != (pppModelSt *)0x0) {
    iVar1 = *param_3->m_serializedDataOffsets;
    pppUnitMatrix__FR10pppFMATRIX(&local_90);
    local_f0.value[2][2] = local_90.value[2][2] * FLOAT_80330548;
    local_f0.value[0][0] = local_90.value[0][0];
    local_f0.value[0][1] = local_90.value[0][1];
    local_f0.value[0][2] = local_90.value[0][2];
    local_f0.value[0][3] = local_90.value[0][3];
    local_f0.value[1][0] = local_90.value[1][0];
    local_f0.value[1][1] = local_90.value[1][1];
    local_f0.value[1][2] = local_90.value[1][2];
    local_f0.value[1][3] = local_90.value[1][3];
    local_f0.value[2][0] = local_90.value[2][0];
    local_f0.value[2][1] = local_90.value[2][1];
    local_f0.value[2][3] = local_90.value[2][3];
    local_c0.value[0][0] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[0][0];
    local_c0.value[0][1] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[0][1];
    local_c0.value[0][2] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[0][2];
    local_c0.value[0][3] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[0][3];
    local_c0.value[1][0] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[1][0];
    local_c0.value[1][1] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[1][1];
    local_c0.value[1][2] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[1][2];
    local_c0.value[1][3] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[1][3];
    local_c0.value[2][0] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[2][0];
    local_c0.value[2][1] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[2][1];
    local_c0.value[2][2] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[2][2];
    local_c0.value[2][3] = (pppYmDrawMdlTexAnm->field0_0x0).m_localMatrix.value[2][3];
    local_90.value[2][2] = local_f0.value[2][2];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_90,&local_c0,&local_f0);
    local_58 = ppvCameraMatrix0.value[2][0];
    local_120.value[1][2] = ppvCameraMatrix0.value[1][2];
    local_60 = ppvCameraMatrix0.value[2][1];
    local_120.value[2][0] = ppvCameraMatrix0.value[2][0];
    local_120.value[2][1] = ppvCameraMatrix0.value[2][1];
    local_5c = ppvCameraMatrix0.value[2][2];
    local_150.value[0][0] = local_90.value[0][0];
    local_150.value[0][1] = local_90.value[0][1];
    local_150.value[0][2] = local_90.value[0][2];
    local_150.value[0][3] = local_90.value[0][3];
    local_150.value[1][0] = local_90.value[1][0];
    local_150.value[1][1] = local_90.value[1][1];
    local_150.value[1][2] = local_90.value[1][2];
    local_150.value[1][3] = local_90.value[1][3];
    local_150.value[2][0] = local_90.value[2][0];
    local_150.value[2][1] = local_90.value[2][1];
    local_150.value[2][2] = local_90.value[2][2];
    local_150.value[2][3] = local_90.value[2][3];
    local_120.value[0][0] = ppvCameraMatrix0.value[0][0];
    local_120.value[0][1] = ppvCameraMatrix0.value[0][1];
    local_120.value[0][2] = ppvCameraMatrix0.value[0][2];
    local_120.value[0][3] = ppvCameraMatrix0.value[0][3];
    local_120.value[1][0] = ppvCameraMatrix0.value[1][0];
    local_120.value[1][1] = ppvCameraMatrix0.value[1][1];
    local_120.value[1][3] = ppvCameraMatrix0.value[1][3];
    local_120.value[2][2] = ppvCameraMatrix0.value[2][2];
    local_120.value[2][3] = ppvCameraMatrix0.value[2][3];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX
              ((pppFMATRIX *)&pppYmDrawMdlTexAnm->field_0x40,&local_120,&local_150);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              ((float)param_2->m_arg3,(pppCVector *)(&pppYmDrawMdlTexAnm->field_0x88 + iVar1),
               (pppFMATRIX *)&pppYmDrawMdlTexAnm->field_0x40,param_2->m_payload[0xc],
               *(undefined *)((int)&param_2->m_initWOrk + 2),
               *(undefined *)((int)&param_2->m_initWOrk + 1),
               *(undefined *)((int)&param_2->m_initWOrk + 3),*(byte *)&param_2->m_stepValue,
               *(byte *)((int)&param_2->m_stepValue + 1),
               *(undefined *)((int)&param_2->m_stepValue + 2));
    pppSetBlendMode__FUc(*(undefined *)((int)&param_2->m_initWOrk + 1));
    pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppYmDrawMdlTexAnm->field_0x70,1);
  }
  return;
}

