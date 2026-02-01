// Function: PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec
// Entry: 800e13fc
// Size: 3448 bytes

/* WARNING: Removing unreachable block (ram,0x800e2158) */
/* WARNING: Removing unreachable block (ram,0x800e2150) */
/* WARNING: Removing unreachable block (ram,0x800e2148) */
/* WARNING: Removing unreachable block (ram,0x800e2140) */
/* WARNING: Removing unreachable block (ram,0x800e2138) */
/* WARNING: Removing unreachable block (ram,0x800e2130) */
/* WARNING: Removing unreachable block (ram,0x800e2128) */
/* WARNING: Removing unreachable block (ram,0x800e2120) */
/* WARNING: Removing unreachable block (ram,0x800e17a4) */
/* WARNING: Removing unreachable block (ram,0x800e17b8) */
/* WARNING: Removing unreachable block (ram,0x800e17c8) */
/* WARNING: Removing unreachable block (ram,0x800e17a8) */
/* WARNING: Removing unreachable block (ram,0x800e1444) */
/* WARNING: Removing unreachable block (ram,0x800e143c) */
/* WARNING: Removing unreachable block (ram,0x800e1434) */
/* WARNING: Removing unreachable block (ram,0x800e142c) */
/* WARNING: Removing unreachable block (ram,0x800e1424) */
/* WARNING: Removing unreachable block (ram,0x800e141c) */
/* WARNING: Removing unreachable block (ram,0x800e1414) */
/* WARNING: Removing unreachable block (ram,0x800e140c) */
/* WARNING: Removing unreachable block (ram,0x800e17ac) */
/* WARNING: Removing unreachable block (ram,0x800e17c4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec
              (CModel *model,Mtx *param_2,undefined4 *param_3,int param_4,undefined4 param_5,
              undefined *param_6,undefined *param_7,Vec *param_8)

{
  float *pfVar1;
  bool bVar2;
  byte bVar3;
  short *psVar4;
  float fVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  Vec *inVecB;
  Vec *source;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  Vec *pVVar12;
  undefined4 uVar13;
  ushort *puVar14;
  S16Vec *pSVar15;
  uint32_t uVar16;
  int iVar17;
  uint32_t uVar18;
  CTextureSet *textureSet;
  byte bVar19;
  int iVar20;
  double dVar21;
  double extraout_f1;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  undefined4 local_4fc;
  undefined local_4f8;
  undefined local_4f7;
  undefined local_4f6;
  undefined local_4f5;
  undefined local_4f4;
  undefined local_4f3;
  undefined local_4f2;
  undefined local_4f1;
  float local_4f0;
  float local_4ec;
  Vec local_4e8;
  Vec local_4dc;
  Vec local_4d0;
  Vec local_4c4;
  Vec local_4b8;
  Vec local_4ac;
  Vec VStack_4a0;
  CVector CStack_494;
  CVector CStack_488;
  CVector CStack_47c;
  CVector CStack_470;
  CVector CStack_464;
  CVector local_458;
  CVector local_44c;
  CVector local_440;
  Vec local_434;
  Vec local_428;
  Vec VStack_41c;
  Vec VStack_410;
  Vec local_404;
  Vec local_3f8;
  Vec local_3ec;
  CVector local_3e0;
  Vec local_3d4;
  Vec local_3c8;
  Mtx MStack_3bc;
  Vec VStack_38c;
  Vec VStack_380;
  Vec VStack_374;
  Vec local_368;
  Vec local_35c;
  Vec local_350;
  Mat4x4 MStack_344;
  uint local_304;
  Vec local_300;
  Vec4d local_2f4;
  float local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  Mtx MStack_2d4;
  Mtx MStack_2a4;
  Mat4x4 MStack_274;
  uint local_234;
  Vec local_230;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214 [4];
  uint local_204;
  Vec local_200;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  uint local_1d4;
  Vec local_1d0;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  undefined4 local_1a0;
  uint uStack_19c;
  undefined4 local_198;
  uint uStack_194;
  uint local_190;
  uint32_t local_18c;
  int local_188;
  uint32_t local_184;
  CDisplayList *local_180;
  uint local_17c;
  CMesh *local_178;
  int local_174;
  undefined4 local_170;
  Vec *local_16c;
  Vec *local_168;
  Vec *local_164;
  Vec *local_160;
  Vec *local_15c;
  Vec *local_158;
  Vec *local_154;
  Vec *local_150;
  Vec *local_14c;
  Vec *local_148;
  Vec *local_144;
  Vec *local_140;
  Vec *local_13c;
  Vec *local_138;
  Vec *local_134;
  Vec *local_130;
  Vec *local_12c;
  Vec *local_128;
  int local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  uint local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  
  if ((int)((uint)model->m_flags0x10C << 0x19 | (uint)(model->m_flags0x10C >> 7)) < 0) {
    dVar25 = (double)FLOAT_8033110c;
    uStack_19c = Chara._8204_4_ ^ 0x80000000;
    local_1a0 = 0x43300000;
    uStack_194 = Chara._8208_4_ ^ 0x80000000;
    dVar24 = (double)FLOAT_80331130;
    dVar27 = (double)(float)((double)CONCAT44(0x43300000,uStack_19c) - DOUBLE_80331100);
    local_198 = 0x43300000;
    dVar26 = (double)(float)((double)CONCAT44(0x43300000,uStack_194) - DOUBLE_80331100);
    dVar22 = dVar25;
    __ct__7CVectorFv(&local_3e0);
    Identity__7CVectorFv(&local_3e0);
    local_170 = 0;
    local_174 = 0;
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_274);
    local_178 = model->m_meshes;
    dVar28 = -(double)(float)(dVar26 - (double)FLOAT_80331134);
    for (local_17c = 0; local_17c < model->m_data->m_meshCount; local_17c = local_17c + 1) {
      if ((local_178->m_workPositions != (S16Vec *)0x0) &&
         ((model->m_meshVisibleMask >> local_17c & 1) != 0)) {
        if (local_178->m_data->m_skinCount == 0) {
          PSMTXConcat(&model->m_drawMtx,&model->m_nodes[local_178->m_data->m_nodeIndex].m_mtx,
                      &MStack_2a4);
        }
        else {
          PSMTXCopy(&model->m_drawMtx,&MStack_2a4);
        }
        PSMTXConcat(param_2,&MStack_2a4,&MStack_2d4);
        uVar18 = model->m_data->m_posQuant;
        uVar16 = model->m_data->m_normQuant;
        local_180 = local_178->m_data->m_displayLists;
        dVar21 = (double)gqrInit__6CCharaFUlUlUl
                                   (&Chara,uVar18 << 0x18 | 0x70000 | uVar18 << 8 | 7,
                                    uVar16 << 0x18 | 0x70000 | uVar16 << 8 | 7,0xc070c07);
        local_14c = &local_3c8;
        local_150 = &local_35c;
        local_184 = local_178->m_data->m_displayListCount;
        local_154 = &local_350;
        local_158 = &VStack_380;
        local_15c = &VStack_374;
        local_160 = &local_35c;
        local_164 = &local_350;
        local_168 = &VStack_380;
        local_16c = &VStack_374;
        local_148 = local_14c;
        while (local_184 = local_184 - 1, -1 < (int)local_184) {
          local_124 = __vc__22CPtrArray<P9CMaterial>FUl
                                (dVar21,&model->m_data->m_materialSet->materials,
                                 local_180->m_material);
          local_188 = 0;
          if ((*(int *)(local_124 + 0x40) != 0) &&
             (*(int *)(*(int *)(local_124 + 0x40) + 0x60) == 5)) {
            local_188 = 1;
          }
          puVar14 = (ushort *)local_180->m_data;
          dVar21 = extraout_f1;
          if ((*(byte *)puVar14 & 7) == 0) {
            local_18c = local_180->m_size;
            do {
              while( true ) {
                source = local_14c;
                inVecB = local_164;
                if (local_18c == 0) goto LAB_800e1f94;
                bVar3 = *(byte *)puVar14;
                uVar9 = 0;
                local_190 = (uint)*(ushort *)((int)puVar14 + 1);
                puVar14 = (ushort *)((int)puVar14 + 3);
                bVar19 = bVar3 & 0xf8;
                local_18c = local_18c - (local_190 * 8 + 3);
                if ((bVar19 != 0x90) && (bVar19 != 0x98)) break;
                dVar29 = (double)FLOAT_8033110c;
                local_128 = local_148;
                local_12c = local_150;
                local_130 = local_154;
                local_134 = local_158;
                local_138 = local_15c;
                local_13c = local_160;
                local_140 = local_168;
                local_144 = local_16c;
                while (bVar2 = local_190 != 0, local_190 = local_190 - 1, bVar2) {
                  pSVar15 = local_178->m_workPositions + *puVar14;
                  local_3ec.x = *(float *)pSVar15;
                  local_3ec.y = *(float *)&pSVar15->z;
                  psVar4 = &local_178->m_data->m_uvs->x + (uint)puVar14[3] * 2;
                  local_4f0 = *(float *)psVar4;
                  local_4ec = *(float *)(psVar4 + 2);
                  local_3ec.z = *(float *)&pSVar15->z;
                  dVar21 = (double)PSMTXMultVec(&MStack_2d4,&local_3ec,&local_300);
                  if ((double)local_300.z < dVar29) {
                    local_304 = local_304 & 0x7fffffff | 0x80000000;
                    MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(&Math,&MStack_274,&local_300,&local_2f4)
                    ;
                    local_2dc = local_4f0;
                    dVar21 = (double)(float)((double)FLOAT_80331134 * (double)local_2f4.y);
                    local_2d8 = local_4ec;
                    local_2e4 = (float)((double)(float)((double)FLOAT_8033113c * (double)local_2f4.x
                                                       ) * (double)(FLOAT_80331138 / local_2f4.w) +
                                       (double)FLOAT_8033113c);
                    local_2e0 = -(float)(dVar21 * (double)(FLOAT_80331138 / local_2f4.w) -
                                        (double)FLOAT_80331134);
                  }
                  else {
                    local_304 = local_304 & 0x7fffffff;
                  }
                  fVar8 = local_1c4;
                  fVar7 = local_1d0.y;
                  fVar5 = local_1d0.x;
                  uVar6 = local_1d4;
                  local_214[3] = local_1d8;
                  local_214[2] = local_1dc;
                  local_214[1] = local_1e0;
                  local_214[0] = local_1e4;
                  local_218 = local_1e8;
                  local_21c = local_1ec;
                  local_220 = local_1f0;
                  local_230.z = local_200.z;
                  local_d8 = local_1c0;
                  local_120 = local_1bc;
                  local_200.z = local_1d0.z;
                  local_11c = local_1b8;
                  local_1f0 = local_1c0;
                  local_118 = local_1b4;
                  local_1ec = local_1bc;
                  local_114 = local_1b0;
                  local_1e8 = local_1b8;
                  local_110 = local_1ac;
                  local_1e4 = local_1b4;
                  local_10c = local_1a8;
                  local_1e0 = local_1b0;
                  local_108 = local_304;
                  local_1dc = local_1ac;
                  local_104 = local_300.x;
                  local_1d8 = local_1a8;
                  local_100 = local_300.y;
                  local_1d4 = local_304;
                  local_fc = local_300.z;
                  local_1d0.x = local_300.x;
                  local_f8 = local_2f4.x;
                  local_1d0.y = local_300.y;
                  local_f4 = local_2f4.y;
                  local_1d0.z = local_300.z;
                  local_f0 = local_2f4.z;
                  local_1c4 = local_2f4.x;
                  local_ec = local_2f4.w;
                  local_1c0 = local_2f4.y;
                  local_e8 = local_2e4;
                  local_1bc = local_2f4.z;
                  local_e4 = local_2e0;
                  local_1b8 = local_2f4.w;
                  local_e0 = local_2dc;
                  local_1b4 = local_2e4;
                  local_dc = local_2d8;
                  local_1b0 = local_2e0;
                  local_234 = local_204;
                  local_1ac = local_2dc;
                  local_230.x = local_200.x;
                  local_230.y = local_200.y;
                  local_224 = local_1f4;
                  local_204 = uVar6;
                  local_200.x = fVar5;
                  local_200.y = fVar7;
                  local_1f4 = fVar8;
                  local_1a8 = local_2d8;
                  if (((bVar19 != 0x90) || ((int)uVar9 % 3 != 2)) &&
                     ((bVar19 != 0x98 || ((int)uVar9 < 2)))) goto LAB_800e1f58;
                  puVar11 = &local_234;
                  iVar10 = 0;
                  iVar20 = 3;
                  fVar5 = FLOAT_8033110c;
                  do {
                    if (-1 < (int)((uint)*(byte *)puVar11 << 0x18)) break;
                    iVar17 = (iVar10 + 1) % 3;
                    dVar21 = (double)((float)(dVar26 - (double)(float)puVar11[9]) *
                                      (float)((double)local_214[iVar17 * 0xc] -
                                             (double)(float)puVar11[8]) -
                                     (float)(dVar27 - (double)(float)puVar11[8]) *
                                     (float)((double)local_214[iVar17 * 0xc + 1] -
                                            (double)(float)puVar11[9]));
                    if ((bVar19 == 0x90) || ((uVar9 & 1) == 0)) {
                      *(byte *)puVar11 = *(byte *)puVar11 & 0xbf;
                      if ((double)FLOAT_8033110c < dVar21) break;
                    }
                    else {
                      *(byte *)puVar11 = *(byte *)puVar11 & 0xbf | 0x40;
                      if (dVar21 < (double)FLOAT_8033110c) break;
                    }
                    pfVar1 = (float *)(puVar11 + 7);
                    puVar11 = puVar11 + 0xc;
                    iVar10 = iVar10 + 1;
                    fVar5 = fVar5 + *pfVar1;
                    iVar20 = iVar20 + -1;
                  } while (iVar20 != 0);
                  if ((iVar10 != 3) || (dVar23 = (double)(fVar5 / FLOAT_80331140), dVar24 <= dVar23)
                     ) goto LAB_800e1f58;
                  local_170 = 1;
                  PSMTX44Copy(&MStack_274,&MStack_344);
                  C_MTX44Inverse(&MStack_344,&MStack_344);
                  __ct__7CVectorFv(&local_3d4);
                  __ct__7CVectorFv(local_128);
                  __ct__7CVectorFfff((float)((double)(float)(dVar27 - (double)FLOAT_8033113c) /
                                            (double)FLOAT_8033113c),
                                     (float)(dVar28 / (double)FLOAT_80331134),FLOAT_8033110c,
                                     &local_440);
                  local_3d4.x = local_440.x;
                  local_3d4.y = local_440.y;
                  local_3d4.z = local_440.z;
                  __ct__7CVectorFfff(local_440.x,local_440.y,FLOAT_80331144,&local_44c);
                  source->x = local_44c.x;
                  local_3c8.y = local_44c.y;
                  local_3c8.z = local_44c.z;
                  PSMTX44MultVec(&MStack_344,&local_3d4,&local_3d4);
                  PSMTX44MultVec(&MStack_344,source,source);
                  __ct__7CVectorFv(&local_4ac);
                  PSVECSubtract(source,&local_3d4,&local_4ac);
                  local_3f8.x = local_4ac.x;
                  local_3f8.y = local_4ac.y;
                  local_3f8.z = local_4ac.z;
                  __ct__7CVectorFv(&local_404);
                  __ct__7CVectorFv(&VStack_410);
                  __ct__7CVectorFv(&VStack_41c);
                  PSVECCrossProduct(&local_200,&local_230,&VStack_410);
                  PSVECCrossProduct(&local_1d0,&local_230,&VStack_41c);
                  PSVECCrossProduct(&VStack_410,&VStack_41c,&local_404);
                  if ((int)((uint)local_1d4._0_1_ << 0x19 | (uint)(local_1d4._0_1_ >> 7)) < 0) {
                    __ct__7CVectorFfff(-local_404.x,-local_404.y,-local_404.z,&local_458);
                    local_404.x = local_458.x;
                    local_404.y = local_458.y;
                    local_404.z = local_458.z;
                  }
                  Normalize__7CVectorFv((CVector *)&local_404);
                  pVVar12 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_464,&local_230);
                  __ct__7CVectorFv(&local_4b8);
                  PSVECSubtract(pVVar12,&local_3d4,&local_4b8);
                  local_428.x = local_4b8.x;
                  local_428.y = local_4b8.y;
                  local_428.z = local_4b8.z;
                  dVar22 = (double)PSVECDotProduct(&local_404,&local_3f8);
                  dVar25 = (double)PSVECDotProduct(&local_404,&local_428);
                  PSVECScale((float)(dVar25 / dVar22),&local_3f8,&VStack_4a0);
                  PSVECAdd(&local_3d4,&VStack_4a0,(Vec *)&local_3e0);
                  __ct__7CVectorFv(&local_368);
                  __ct__7CVectorFv(local_12c);
                  __ct__7CVectorFv(local_130);
                  __ct__7CVectorFv(&VStack_38c);
                  __ct__7CVectorFv(local_134);
                  __ct__7CVectorFv(local_138);
                  pVVar12 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_470,&local_230);
                  __ct__7CVectorFv(&local_4c4);
                  PSVECSubtract(pVVar12,(Vec *)&local_3e0,&local_4c4);
                  local_368.x = local_4c4.x;
                  local_368.y = local_4c4.y;
                  local_368.z = local_4c4.z;
                  pVVar12 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_47c,&local_200);
                  __ct__7CVectorFv(&local_4d0);
                  PSVECSubtract(pVVar12,(Vec *)&local_3e0,&local_4d0);
                  local_35c.y = local_4d0.y;
                  local_13c->x = local_4d0.x;
                  local_35c.z = local_4d0.z;
                  pVVar12 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_488,&local_1d0);
                  __ct__7CVectorFv(&local_4dc);
                  PSVECSubtract(pVVar12,(Vec *)&local_3e0,&local_4dc);
                  pVVar12 = local_13c;
                  inVecB->x = local_4dc.x;
                  local_350.y = local_4dc.y;
                  local_350.z = local_4dc.z;
                  PSVECCrossProduct(&local_368,pVVar12,&VStack_38c);
                  PSVECCrossProduct(local_13c,inVecB,local_140);
                  PSVECCrossProduct(inVecB,&local_368,local_144);
                  dVar22 = (double)PSVECMag(&VStack_38c);
                  dVar25 = (double)PSVECMag(local_144);
                  dVar21 = (double)PSVECMag(local_140);
                  pVVar12 = (Vec *)__ct__7CVectorFfff((float)dVar21,(float)dVar25,(float)dVar22,
                                                      &CStack_494);
                  __ct__7CVectorFv(&local_4e8);
                  PSVECScale(FLOAT_80331148,pVVar12,&local_4e8);
                  local_434.x = local_4e8.x;
                  local_434.y = local_4e8.y;
                  local_434.z = local_4e8.z;
                  PSVECScale(FLOAT_80331138 / (local_4e8.z + local_4e8.x + local_4e8.y),&local_434,
                             &local_434);
                  dVar21 = (double)local_1a8;
                  dVar22 = (double)(float)((double)local_1ac * (double)local_434.z +
                                          (double)(local_214[2] * local_434.x +
                                                  local_1dc * local_434.y));
                  dVar25 = (double)(float)(dVar21 * (double)local_434.z +
                                          (double)(local_214[3] * local_434.x +
                                                  local_1d8 * local_434.y));
                  if (param_8 != (Vec *)0x0) {
                    param_8->x = local_3e0.x;
                    param_8->y = local_3e0.y;
                    param_8->z = local_3e0.z;
                  }
                  if (*(char *)(local_124 + 0xa7) != '\0') {
                    local_174 = local_188;
                    dVar24 = dVar23;
LAB_800e1f58:
                    uVar9 = uVar9 + 1;
                    puVar14 = puVar14 + 4;
                  }
                }
              }
            } while ((bVar3 & 0xf8) != 0);
          }
LAB_800e1f94:
          local_180 = local_180 + 1;
        }
      }
      local_178 = local_178 + 1;
    }
    if ((param_4 != 0) && (local_174 != 0)) {
      textureSet = model->m_texSet;
      uVar13 = Find__11CTextureSetFPc(textureSet,&DAT_80331114);
      iVar10 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar13);
      if (iVar10 != 0) {
        if ((*(int *)(iVar10 + 0x60) == 5) && (dVar24 != (double)FLOAT_8033110c)) {
          local_4fc = *param_3;
          brush__FPUsiiffi8_GXColorP8_GXColorP8_GXColor
                    (dVar22,dVar25,*(undefined4 *)(iVar10 + 0x78),*(undefined4 *)(iVar10 + 100),
                     *(undefined4 *)(iVar10 + 0x68),param_5,&local_4fc,&local_4f4,&local_4f8);
          if (param_6 != (undefined *)0x0) {
            *param_6 = local_4f4;
            param_6[1] = local_4f3;
            param_6[2] = local_4f2;
            param_6[3] = local_4f1;
          }
          if (param_7 != (undefined *)0x0) {
            *param_7 = local_4f8;
            param_7[1] = local_4f7;
            param_7[2] = local_4f6;
            param_7[3] = local_4f5;
          }
        }
      }
    }
    if (param_8 != (Vec *)0x0) {
      PSMTXInverse(param_2,&MStack_3bc);
      PSMTXMultVec(&MStack_3bc,param_8,param_8);
    }
    if ((double)FLOAT_80331130 == dVar24) {
      uVar9 = countLeadingZeros(local_170);
      iVar10 = -(uVar9 >> 5 & 1);
    }
    else {
      iVar10 = 1;
    }
  }
  else {
    iVar10 = -1;
  }
  return iVar10;
}

