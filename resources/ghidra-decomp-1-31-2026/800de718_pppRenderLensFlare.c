// Function: pppRenderLensFlare
// Entry: 800de718
// Size: 428 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderLensFlare(pppLensFlare *pppLensFlare,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  pppCVector local_70;
  Vec local_6c;
  Vec local_60;
  Mtx local_54;
  
  iVar2 = param_3->m_serializedDataOffsets[2];
  iVar1 = param_3->m_serializedDataOffsets[1];
  if ((param_2->m_dataValIndex != 0xffff) &&
     (puVar3 = *(undefined4 **)
                (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA + param_2->m_dataValIndex * 4)
     , (&pppLensFlare->field_0xb2)[iVar2] != '\0')) {
    PSMTXIdentity(&local_54);
    local_54.value[2][2] = param_2->m_stepValue;
    local_54.value[0][0] =
         local_54.value[2][2] * (pppMngStPtr->m_scale).x * *(float *)&pppLensFlare->field_0x40;
    local_54.value[1][1] =
         local_54.value[2][2] * (pppMngStPtr->m_scale).y * *(float *)&pppLensFlare->field_0x54;
    local_54.value[2][2] =
         local_54.value[2][2] * (pppMngStPtr->m_scale).z * *(float *)&pppLensFlare->field_0x68;
    local_60.x = (pppMngStPtr->m_matrix).value[0][3];
    local_60.y = (pppMngStPtr->m_matrix).value[1][3];
    local_60.z = (pppMngStPtr->m_matrix).value[2][3];
    PSMTXMultVec(&ppvCameraMatrix0,&local_60,&local_60);
    local_54.value[0][3] = local_60.x;
    local_54.value[1][3] = local_60.y;
    local_54.value[2][3] = local_60.z;
    local_6c.x = local_60.x;
    local_6c.y = local_60.y;
    local_6c.z = local_60.z;
    pppCopyVector__FR3Vec3Vec((Vec *)(&pppLensFlare->field_0xa0 + iVar2),&local_6c);
    GXLoadPosMtxImm(&local_54,0);
    local_70.m_rgba[0] = (&pppLensFlare->field_0x88)[iVar1];
    local_70.m_rgba[1] = (&pppLensFlare->field_0x89)[iVar1];
    local_70.m_rgba[2] = (&pppLensFlare->field_0x8a)[iVar1];
    local_70.m_rgba[3] = (&pppLensFlare->field_0xb2)[iVar2];
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80331060,&local_70,(pppFMATRIX *)0x0,param_2->m_payload[0],
               *(undefined *)((int)&param_2->m_arg3 + 3),*(undefined *)((int)&param_2->m_arg3 + 2),0
               ,1,1,0);
    pppSetBlendMode__FUc(*(undefined *)((int)&param_2->m_arg3 + 2));
    pppDrawShp__FPlsP12CMaterialSetUc
              (*puVar3,(int)*(short *)(&pppLensFlare->field_0xae + iVar2),
               pppEnvStPtr->m_materialSetPtr,*(undefined *)((int)&param_2->m_arg3 + 2));
    pppSetBlendMode__FUc(3);
  }
  return;
}

