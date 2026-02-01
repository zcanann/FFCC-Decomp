// Function: pppRenderYmMelt
// Entry: 800a538c
// Size: 1716 bytes

/* WARNING: Removing unreachable block (ram,0x800a5a24) */
/* WARNING: Removing unreachable block (ram,0x800a5a1c) */
/* WARNING: Removing unreachable block (ram,0x800a5a14) */
/* WARNING: Removing unreachable block (ram,0x800a5a0c) */
/* WARNING: Removing unreachable block (ram,0x800a5a04) */
/* WARNING: Removing unreachable block (ram,0x800a59fc) */
/* WARNING: Removing unreachable block (ram,0x800a59f4) */
/* WARNING: Removing unreachable block (ram,0x800a59ec) */
/* WARNING: Removing unreachable block (ram,0x800a59e4) */
/* WARNING: Removing unreachable block (ram,0x800a59dc) */
/* WARNING: Removing unreachable block (ram,0x800a59d4) */
/* WARNING: Removing unreachable block (ram,0x800a59cc) */
/* WARNING: Removing unreachable block (ram,0x800a53f4) */
/* WARNING: Removing unreachable block (ram,0x800a53ec) */
/* WARNING: Removing unreachable block (ram,0x800a53e4) */
/* WARNING: Removing unreachable block (ram,0x800a53dc) */
/* WARNING: Removing unreachable block (ram,0x800a53d4) */
/* WARNING: Removing unreachable block (ram,0x800a53cc) */
/* WARNING: Removing unreachable block (ram,0x800a53c4) */
/* WARNING: Removing unreachable block (ram,0x800a53bc) */
/* WARNING: Removing unreachable block (ram,0x800a53b4) */
/* WARNING: Removing unreachable block (ram,0x800a53ac) */
/* WARNING: Removing unreachable block (ram,0x800a53a4) */
/* WARNING: Removing unreachable block (ram,0x800a539c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmMelt(pppYmMelt *pppYmMelt,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  float fVar2;
  CTexture *texture;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  pppShapeSt *pppShapeSt;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  undefined4 local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  Vec local_168;
  Vec local_15c;
  Vec local_150;
  Vec local_144;
  Vec local_138;
  Vec local_12c;
  Vec local_120;
  Vec local_114;
  undefined4 local_108;
  uint uStack_104;
  undefined4 local_100;
  uint uStack_fc;
  
  iVar5 = param_3->m_serializedDataOffsets[1];
  piVar9 = (int *)((int)(&pppYmMelt->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
  if (param_2->m_dataValIndex != 0xffff) {
    pppShapeSt = *(pppShapeSt **)
                  (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                  param_2->m_dataValIndex * 4);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80330af0,(pppCVector *)(&pppYmMelt->field_0x88 + iVar5),&ppvCameraMatrix0,
               param_2->m_payload[0x19],param_2->m_payload[0x18],*(undefined *)&param_2->m_arg3,2,1,
               1,0);
    pppSetBlendMode__FUc(*(undefined *)&param_2->m_arg3);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(7,9,1,4,0);
    GXSetVtxAttrFmt(7,0xb,1,5,0);
    GXSetVtxAttrFmt(7,0xd,1,4,0);
    local_17c = 0;
    texture = (CTexture *)
              GetTexture__10pppShapeStFPlP12CMaterialSetRi
                        (pppShapeSt,pppShapeSt->m_animData,pppEnvStPtr->m_materialSetPtr,&local_17c)
    ;
    if (texture != (CTexture *)0x0) {
      GXLoadTexObj(&texture->field_0x28,0);
      GXSetNumChans(1);
      GXSetNumTexGens(1);
      GXSetNumTevStages(1);
      GXSetTevDirect(0);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      if ((texture->field93_0x60 == 8) || (texture->field93_0x60 == 9)) {
        SetUpPaletteEnv__FP8CTexture(texture);
      }
      dVar15 = (double)(FLOAT_80330af4 - (float)piVar9[3]);
      fVar1 = *(float *)(&pppYmMelt->field_0x88 + iVar5);
      iVar5 = *piVar9;
      dVar22 = (double)(pppMngStPtr->m_matrix).value[0][3];
      dVar21 = (double)(pppMngStPtr->m_matrix).value[1][3];
      dVar20 = (double)(pppMngStPtr->m_matrix).value[2][3];
      pppGetShapeUV__FPlsR5Vec2dR5Vec2di
                (pppShapeSt->m_animData,(int)*(short *)(piVar9 + 2),&local_170,&local_178,0);
      uStack_104 = (uint)*(ushort *)((int)&param_2->m_initWOrk + 2);
      local_108 = 0x43300000;
      local_100 = 0x43300000;
      dVar19 = (double)((local_178 - local_170) /
                       (float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80330af8));
      dVar18 = (double)((local_174 - local_16c) /
                       (float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80330af8));
      uStack_fc = uStack_104;
      GXBegin(0x80,7,uStack_104 * uStack_104 * 4 & 0xfffc);
      dVar23 = (double)FLOAT_80330af4;
      dVar24 = DOUBLE_80330b00;
      for (uVar7 = 0; (int)uVar7 < (int)(uint)*(ushort *)((int)&param_2->m_initWOrk + 2);
          uVar7 = uVar7 + 1) {
        uStack_104 = uVar7 ^ 0x80000000;
        uStack_fc = uVar7 + 1 ^ 0x80000000;
        uVar8 = 0;
        dVar17 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_fc) - dVar24) *
                                dVar18);
        dVar16 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_104) - dVar24) *
                                dVar18);
        while( true ) {
          local_100 = 0x43300000;
          local_108 = 0x43300000;
          uVar4 = (uint)*(ushort *)((int)&param_2->m_initWOrk + 2);
          if ((int)uVar4 <= (int)uVar8) break;
          iVar6 = uVar4 + 1;
          iVar13 = uVar8 + (uVar7 + 1) * iVar6;
          pfVar11 = (float *)(iVar5 + iVar13 * 0x10);
          local_144.x = *pfVar11;
          local_144.y = pfVar11[1];
          iVar6 = uVar8 + uVar7 * iVar6;
          local_144.z = pfVar11[2];
          pppCopyVector__FR3Vec3Vec(&local_114,&local_144);
          pfVar10 = (float *)(iVar5 + iVar6 * 0x10);
          local_150.x = *pfVar10;
          local_150.y = pfVar10[1];
          local_150.z = pfVar10[2];
          pppCopyVector__FR3Vec3Vec(&local_120,&local_150);
          pfVar14 = (float *)(iVar5 + (iVar13 + 1) * 0x10);
          local_15c.x = *pfVar14;
          local_15c.y = pfVar14[1];
          local_15c.z = pfVar14[2];
          pppCopyVector__FR3Vec3Vec(&local_12c,&local_15c);
          pfVar12 = (float *)(iVar5 + (iVar6 + 1) * 0x10);
          local_168.x = *pfVar12;
          local_168.y = pfVar12[1];
          local_168.z = pfVar12[2];
          pppCopyVector__FR3Vec3Vec(&local_138,&local_168);
          local_114.y = (float)((double)local_114.y + dVar21);
          local_120.y = (float)((double)local_120.y + dVar21);
          local_12c.y = (float)((double)local_12c.y + dVar21);
          local_138.y = (float)((double)local_138.y + dVar21);
          if (dVar23 != (double)(float)piVar9[3]) {
            local_114.x = (float)(dVar15 * (double)(float)(dVar22 - (double)local_114.x) +
                                 (double)local_114.x);
            local_114.z = (float)(dVar15 * (double)(float)(dVar20 - (double)local_114.z) +
                                 (double)local_114.z);
            local_120.x = (float)(dVar15 * (double)(float)(dVar22 - (double)local_120.x) +
                                 (double)local_120.x);
            local_120.z = (float)(dVar15 * (double)(float)(dVar20 - (double)local_120.z) +
                                 (double)local_120.z);
            local_12c.x = (float)(dVar15 * (double)(float)(dVar22 - (double)local_12c.x) +
                                 (double)local_12c.x);
            local_12c.z = (float)(dVar15 * (double)(float)(dVar20 - (double)local_12c.z) +
                                 (double)local_12c.z);
            local_138.x = (float)(dVar15 * (double)(float)(dVar22 - (double)local_138.x) +
                                 (double)local_138.x);
            local_138.z = (float)(dVar15 * (double)(float)(dVar20 - (double)local_138.z) +
                                 (double)local_138.z);
          }
          DAT_cc008000 = local_114.x;
          DAT_cc008000 = local_114.y;
          DAT_cc008000 = local_114.z;
          fVar3 = fVar1;
          if (*(char *)((int)pfVar11 + 0xf) == '\0') {
            fVar3 = pfVar11[3];
          }
          uStack_fc = uVar8 ^ 0x80000000;
          DAT_cc008000 = fVar3;
          fVar3 = (float)((double)(float)((double)CONCAT44(0x43300000,uStack_fc) - dVar24) * dVar19
                         + (double)local_170);
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)((double)local_16c + dVar17);
          DAT_cc008000 = local_120.x;
          DAT_cc008000 = local_120.y;
          DAT_cc008000 = local_120.z;
          fVar2 = fVar1;
          if (*(char *)((int)pfVar10 + 0xf) == '\0') {
            fVar2 = pfVar10[3];
          }
          DAT_cc008000 = fVar2;
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)((double)local_16c + dVar16);
          DAT_cc008000 = local_138.x;
          DAT_cc008000 = local_138.y;
          DAT_cc008000 = local_138.z;
          fVar3 = fVar1;
          if (*(char *)((int)pfVar12 + 0xf) == '\0') {
            fVar3 = pfVar12[3];
          }
          uStack_104 = uVar8 + 1 ^ 0x80000000;
          DAT_cc008000 = fVar3;
          fVar3 = (float)((double)(float)((double)CONCAT44(0x43300000,uStack_104) - dVar24) * dVar19
                         + (double)local_170);
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)((double)local_16c + dVar16);
          DAT_cc008000 = local_12c.x;
          DAT_cc008000 = local_12c.y;
          DAT_cc008000 = local_12c.z;
          fVar2 = fVar1;
          if (*(char *)((int)pfVar14 + 0xf) == '\0') {
            fVar2 = pfVar14[3];
          }
          DAT_cc008000 = fVar2;
          uVar8 = uVar8 + 1;
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)((double)local_16c + dVar17);
        }
      }
      if ((texture->field93_0x60 == 8) || (texture->field93_0x60 == 9)) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      }
    }
  }
  return;
}

