// Function: pppRenderColum
// Entry: 800dec5c
// Size: 1292 bytes

/* WARNING: Removing unreachable block (ram,0x800df14c) */
/* WARNING: Removing unreachable block (ram,0x800df144) */
/* WARNING: Removing unreachable block (ram,0x800df13c) */
/* WARNING: Removing unreachable block (ram,0x800df134) */
/* WARNING: Removing unreachable block (ram,0x800df12c) */
/* WARNING: Removing unreachable block (ram,0x800df124) */
/* WARNING: Removing unreachable block (ram,0x800dec94) */
/* WARNING: Removing unreachable block (ram,0x800dec8c) */
/* WARNING: Removing unreachable block (ram,0x800dec84) */
/* WARNING: Removing unreachable block (ram,0x800dec7c) */
/* WARNING: Removing unreachable block (ram,0x800dec74) */
/* WARNING: Removing unreachable block (ram,0x800dec6c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderColum(pppColum *column,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  pppShapeSt *pppShapeSt;
  float *pfVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  uint8_t local_14c [4];
  pppCVector local_148;
  undefined4 local_144;
  undefined auStack_140 [8];
  undefined auStack_138 [8];
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  Vec local_118;
  Vec local_10c;
  Vec VStack_100;
  Vec local_f4;
  Vec local_e8;
  Mtx MStack_dc;
  undefined8 local_a8;
  undefined4 local_a0;
  uint uStack_9c;
  
  iVar7 = param_3->m_serializedDataOffsets[3];
  iVar5 = param_3->m_serializedDataOffsets[2];
  local_144 = 0;
  if (param_2->m_dataValIndex != 0xffff) {
    pppShapeSt = *(pppShapeSt **)
                  (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                  param_2->m_dataValIndex * 4);
    iVar3 = GetTexture__10pppShapeStFPlP12CMaterialSetRi
                      (pppShapeSt,pppShapeSt->m_animData,pppEnvStPtr->m_materialSetPtr,&local_144);
    if ((&column->field_0xb2)[iVar5] != '\0') {
      PSMTXIdentity(&MStack_dc);
      dVar16 = (double)*(float *)(&column->field_0x90 + iVar5);
      dVar15 = (double)*(float *)(&column->field_0x94 + iVar5);
      local_e8.x = (float)((double)FLOAT_80331078 - dVar16);
      local_e8.y = (float)((double)FLOAT_8033107c - dVar15);
      local_e8.z = FLOAT_80331080 + *(float *)(&column->field_0x98 + iVar5);
      fVar1 = local_e8.x * local_e8.x + local_e8.y * local_e8.y;
      dVar17 = (double)fVar1;
      if (dVar17 <= (double)FLOAT_80331084) {
        if (DOUBLE_80331098 <= dVar17) {
          uVar4 = (uint)fVar1 & 0x7f800000;
          if (uVar4 == 0x7f800000) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar9 = 2;
            }
            else {
              iVar9 = 1;
            }
          }
          else if ((uVar4 < 0x7f800000) && (uVar4 == 0)) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar9 = 3;
            }
            else {
              iVar9 = 5;
            }
          }
          else {
            iVar9 = 4;
          }
          if (iVar9 == 1) {
            dVar17 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar17 = (double)DAT_8032ec20;
        }
      }
      else {
        dVar11 = 1.0 / SQRT(dVar17);
        dVar11 = DOUBLE_80331088 * dVar11 * -(dVar17 * dVar11 * dVar11 - DOUBLE_80331090);
        dVar11 = DOUBLE_80331088 * dVar11 * -(dVar17 * dVar11 * dVar11 - DOUBLE_80331090);
        dVar17 = (double)(float)(dVar17 * DOUBLE_80331088 * dVar11 *
                                          -(dVar17 * dVar11 * dVar11 - DOUBLE_80331090));
      }
      dVar11 = (double)FLOAT_80331084;
      if ((double)FLOAT_803310a0 < dVar17) {
        PSVECScale((float)((double)FLOAT_803310a4 / dVar17),&local_e8,&local_e8);
      }
      pppInitBlendMode__Fv();
      local_a8 = (double)CONCAT44(0x43300000,(uint)*(byte *)((int)&param_2->m_arg3 + 1));
      pfVar10 = *(float **)(&column->field_0x88 + iVar7);
      dVar13 = (double)FLOAT_80331084;
      dVar14 = (double)((float)((double)FLOAT_803310a8 * dVar17) /
                       (float)(local_a8 - DOUBLE_803310b0));
      dVar17 = DOUBLE_803310b8;
      for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)((int)&param_2->m_arg3 + 1); iVar9 = iVar9 + 1) {
        uStack_9c = iVar9 + 1U ^ 0x80000000;
        local_a8 = (double)(CONCAT44(0x43300000,iVar9 + 1U) ^ 0x80000000);
        local_a0 = 0x43300000;
        local_f4.z = (float)dVar13;
        local_f4.x = (float)((double)(float)(dVar14 * (double)pfVar10[1]) *
                             (double)(local_e8.x * (float)(local_a8 - dVar17)) + dVar16);
        local_f4.y = (float)((double)(float)(dVar14 * (double)pfVar10[1]) *
                             (double)(local_e8.y *
                                     (float)((double)CONCAT44(0x43300000,uStack_9c) - dVar17)) +
                            dVar15);
        PSVECSubtract(&local_f4,(Vec *)(&column->field_0x90 + iVar5),&VStack_100);
        dVar12 = (double)PSVECMag(&VStack_100);
        local_148.m_rgba[3] = (&column->field_0xb2)[iVar5];
        uVar4 = (uint)local_148.m_rgba[3];
        fVar1 = (float)(dVar12 / (double)*(float *)(param_2->m_payload + 0x10));
        if ((dVar12 < (double)*(float *)(param_2->m_payload + 0x10)) && (FLOAT_80331084 < fVar1)) {
          local_a0 = 0x43300000;
          iVar8 = (int)((float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_803310b0) * fVar1);
          local_a8 = (double)(longlong)iVar8;
          local_148.m_rgba[3] = (uint8_t)iVar8;
          uStack_9c = uVar4;
        }
        local_148.m_rgba[0] = *(char *)&param_2->m_stepValue + *(char *)(pfVar10 + 2);
        local_148.m_rgba[1] =
             *(char *)((int)&param_2->m_stepValue + 1) + *(char *)((int)pfVar10 + 9);
        local_148.m_rgba[2] =
             *(char *)((int)&param_2->m_stepValue + 2) + *(char *)((int)pfVar10 + 10);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                  (FLOAT_80331084,&local_148,(pppFMATRIX *)0x0,param_2->m_payload[0x15],
                   param_2->m_payload[0x14],*(undefined *)&param_2->m_arg3,0,0,1,0);
        BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
        SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
        GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
        GXLoadTexObj(iVar3 + 0x28,0);
        pppSetBlendMode__FUc(*(undefined *)&param_2->m_arg3);
        pvVar6 = pppShapeSt->m_animData;
        dVar11 = (double)(float)(dVar11 + (double)*pfVar10);
        sVar2 = *(short *)((int)pvVar6 + *(short *)(&column->field_0x82 + iVar7) * 8 + 0x10);
        for (iVar8 = 0; iVar8 < *(short *)((int)pvVar6 + sVar2 + 2); iVar8 = iVar8 + 1) {
          pppGetShapePos__FPlsR3VecR3Veci
                    (pppShapeSt->m_animData,*(undefined2 *)(&column->field_0x82 + iVar7),&local_10c,
                     &local_118,iVar8);
          pppGetShapeUV__FPlsR5Vec2dR5Vec2di
                    (pppShapeSt->m_animData,(int)*(short *)(&column->field_0x82 + iVar7),auStack_138
                     ,auStack_140,iVar8);
          PSVECScale((float)dVar11,&local_10c,&local_10c);
          PSVECScale((float)dVar11,&local_118,&local_118);
          PSVECAdd(&local_10c,&local_f4,&local_10c);
          PSVECAdd(&local_118,&local_f4,&local_118);
          local_14c[0] = local_148.m_rgba[0];
          local_14c[1] = local_148.m_rgba[1];
          local_14c[2] = local_148.m_rgba[2];
          local_14c[3] = local_148.m_rgba[3];
          local_130 = local_118.x;
          local_12c = local_118.y;
          local_128 = local_118.z;
          local_124 = local_10c.x;
          local_120 = local_10c.y;
          local_11c = local_10c.z;
          RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                    (&DAT_8032ec70,&local_124,&local_130,local_14c,auStack_138,auStack_140);
        }
        EndQuadEnv__5CUtilFv(&DAT_8032ec70);
        pppSetBlendMode__FUc(0);
        pfVar10 = pfVar10 + 3;
      }
    }
  }
  return;
}

