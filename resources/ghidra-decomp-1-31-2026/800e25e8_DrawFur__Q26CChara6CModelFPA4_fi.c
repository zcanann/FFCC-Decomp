// Function: DrawFur__Q26CChara6CModelFPA4_fi
// Entry: 800e25e8
// Size: 3296 bytes

/* WARNING: Removing unreachable block (ram,0x800e32ac) */
/* WARNING: Removing unreachable block (ram,0x800e32a4) */
/* WARNING: Removing unreachable block (ram,0x800e329c) */
/* WARNING: Removing unreachable block (ram,0x800e3294) */
/* WARNING: Removing unreachable block (ram,0x800e30fc) */
/* WARNING: Removing unreachable block (ram,0x800e3168) */
/* WARNING: Removing unreachable block (ram,0x800e31ec) */
/* WARNING: Removing unreachable block (ram,0x800e3108) */
/* WARNING: Removing unreachable block (ram,0x800e31e0) */
/* WARNING: Removing unreachable block (ram,0x800e31f8) */
/* WARNING: Removing unreachable block (ram,0x800e3170) */
/* WARNING: Removing unreachable block (ram,0x800e2610) */
/* WARNING: Removing unreachable block (ram,0x800e2608) */
/* WARNING: Removing unreachable block (ram,0x800e2600) */
/* WARNING: Removing unreachable block (ram,0x800e25f8) */
/* WARNING: Removing unreachable block (ram,0x800e3164) */
/* WARNING: Removing unreachable block (ram,0x800e31e4) */
/* WARNING: Removing unreachable block (ram,0x800e3100) */
/* WARNING: Removing unreachable block (ram,0x800e3104) */
/* WARNING: Removing unreachable block (ram,0x800e31e8) */
/* WARNING: Removing unreachable block (ram,0x800e3184) */
/* WARNING: Removing unreachable block (ram,0x800e311c) */
/* WARNING: Removing unreachable block (ram,0x800e3200) */
/* WARNING: Removing unreachable block (ram,0x800e3114) */
/* WARNING: Removing unreachable block (ram,0x800e317c) */
/* WARNING: Removing unreachable block (ram,0x800e316c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawFur__Q26CChara6CModelFPA4_fi(CModel *model,Mtx *param_2,int param_3)

{
  ushort *puVar1;
  bool bVar2;
  byte bVar3;
  ushort uVar4;
  float fVar5;
  uint32_t uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  byte bVar10;
  ushort *puVar11;
  S16Vec *pSVar12;
  S16Vec *pSVar13;
  uint32_t uVar14;
  int iVar15;
  CTexture *texture;
  int *piVar16;
  int iVar17;
  int *piVar18;
  uint uVar19;
  int iVar20;
  CDisplayList *pCVar21;
  uint uVar22;
  CMesh *pCVar23;
  uint uVar24;
  uint uVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  undefined auStack_208 [4];
  undefined4 local_204;
  int local_200 [4];
  float local_1f0;
  float local_1ec;
  float local_1e8;
  Vec4d VStack_1e4;
  Vec local_1d4;
  Vec VStack_1c8;
  undefined auStack_1bc [32];
  Mtx MStack_19c;
  Mtx MStack_16c;
  Mtx MStack_13c;
  Mtx MStack_10c;
  Mtx local_dc;
  double local_a8;
  double local_a0;
  undefined8 local_98;
  
  if ((int)((uint)model->m_flags0x10C << 0x19 | (uint)(model->m_flags0x10C >> 7)) < 0) {
    iVar8 = _UnkMaterialSetGetter((CMaterial *)&model->m_data->m_materialSet->materials);
    bVar2 = false;
    for (iVar17 = 0; iVar17 < iVar8; iVar17 = iVar17 + 1) {
      iVar15 = __vc__22CPtrArray<P9CMaterial>FUl(&model->m_data->m_materialSet->materials,iVar17);
      if (*(char *)(iVar15 + 0xa7) != '\0') {
        bVar2 = true;
        break;
      }
    }
    if (bVar2) {
      __ct__7CVectorFv(&VStack_1c8);
      __ct__7CVectorFv(&local_1d4);
      local_1d4.x = (model->m_localMtx).value[0][3];
      local_1d4.y = (model->m_localMtx).value[1][3];
      local_1d4.z = (model->m_localMtx).value[2][3];
      PSMTXMultVec(param_2,&local_1d4,&VStack_1c8);
      fVar5 = FLOAT_8033110c;
      if (VStack_1c8.z < FLOAT_8033114c) {
        MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d
                  (&Math,&CameraPcs.m_screenMatrix,&VStack_1c8,&VStack_1e4);
        fVar5 = -VStack_1e4.z / VStack_1e4.w;
      }
      dVar27 = (double)model->m_furStep;
      dVar26 = (double)(model->m_furLenScale * (FLOAT_80331138 - fVar5) + model->m_furLenScale);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      GXSetZCompLoc(0);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
      GXSetZMode(1,3,0);
      GXSetCullMode(1);
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xd,3);
      GXSetVtxAttrFmt(0,9,1,4,0);
      GXSetVtxAttrFmt(0,10,0,3,model->m_data->m_normQuant & 0xff);
      GXSetVtxAttrFmt(0,0xd,1,3,0xc);
      EnableLight__9CLightPcsFii(&LightPcs,1,1);
      GXSetZMode(1,3,0);
      iVar8 = (int)(FLOAT_80331150 * model->m_furCur);
      local_a8 = (double)(longlong)iVar8;
      local_a0 = local_a8;
      local_98 = local_a8;
      puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_208,iVar8,iVar8,iVar8,0xff);
      local_204 = *puVar9;
      GXSetChanMatColor(4,&local_204);
      SetAmbientAlpha__9CLightPcsFf((double)model->m_lightAlpha,&LightPcs);
      GXSetNumIndStages(0);
      GXSetNumTevStages(2);
      GXSetTevDirect(0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,8,10,0xf);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,6,4,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      GXSetTevDirect(1);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,0xf,0,8,0xf);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,7,0,4,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,1,4);
      PSMTXIdentity(&local_dc);
      local_dc.value[0][0] = (float)dVar27;
      local_dc.value[1][1] = (float)dVar27;
      GXLoadTexMtxImm(&local_dc,0x1e,1);
      pCVar23 = model->m_meshes;
      uVar24 = 0xffffffff;
      iVar8 = -1;
      for (uVar22 = 0; uVar22 < model->m_data->m_meshCount; uVar22 = uVar22 + 1) {
        if ((pCVar23->m_workPositions != (S16Vec *)0x0) &&
           ((model->m_meshVisibleMask >> uVar22 & 1) != 0)) {
          if (pCVar23->m_data->m_skinCount == 0) {
            PSMTXConcat(&model->m_drawMtx,&model->m_nodes[pCVar23->m_data->m_nodeIndex].m_mtx,
                        &MStack_10c);
          }
          else {
            PSMTXCopy(&model->m_drawMtx,&MStack_10c);
          }
          iVar17 = 0;
          if (param_3 != 0) {
            local_200[2] = g__chara_fur_1;
            local_200[3] = g__chara_fur_2;
            local_200[0] = g__chara_fur_3;
            local_200[1] = g__chara_fur_4;
            iVar17 = GetCharaShadow__12CMaterialManFiPP9CMaterialPPA4_fP3Vecffi
                               ((double)FLOAT_80331154,(double)FLOAT_80331158,&MaterialMan,2,
                                local_200 + 2,local_200,&local_1d4,0);
            piVar16 = local_200 + 2;
            piVar18 = local_200;
            iVar15 = 0;
            for (iVar20 = 0; iVar20 < iVar17; iVar20 = iVar20 + 1) {
              SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
                        (&TextureMan,iVar20 + 3,*(CTexture **)(*piVar16 + 0x3c));
              PSMTXConcat((Mtx *)*piVar18,&MStack_10c,&MStack_13c);
              GXLoadTexMtxImm(&MStack_13c,iVar15 + 0x21,0);
              GXSetTexCoordGen2(iVar20 + 3,0,0,iVar15 + 0x21,0,0x7d);
              iVar15 = iVar15 + 3;
              piVar16 = piVar16 + 1;
              piVar18 = piVar18 + 1;
            }
          }
          PSMTXConcat(param_2,&MStack_10c,&MStack_16c);
          GXLoadPosMtxImm(&MStack_16c,0);
          PSMTXCopy(&MStack_16c,&MStack_19c);
          MStack_19c.value[0][3] = FLOAT_8033110c;
          MStack_19c.value[1][3] = FLOAT_8033110c;
          MStack_19c.value[2][3] = FLOAT_8033110c;
          GXLoadNrmMtxImm(&MStack_19c,0);
          GXSetArray(10,pCVar23->m_workNormals,6);
          GXSetArray(0xd,pCVar23->m_data->m_uvs,4);
          uVar14 = model->m_data->m_posQuant;
          uVar6 = model->m_data->m_normQuant;
          pCVar21 = pCVar23->m_data->m_displayLists;
          gqrInit__6CCharaFUlUlUl
                    (&Chara,uVar14 << 0x18 | 0x70000 | uVar14 << 8 | 7,
                     uVar6 << 0x18 | 0x70000 | uVar6 << 8 | 7,0xc070c07);
          uVar6 = pCVar23->m_data->m_displayListCount;
          while (uVar6 = uVar6 - 1, -1 < (int)uVar6) {
            iVar15 = __vc__22CPtrArray<P9CMaterial>FUl
                               (&model->m_data->m_materialSet->materials,pCVar21->m_material);
            if (*(char *)(iVar15 + 0xa7) != '\0') {
              SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
                        (&TextureMan,0,*(CTexture **)(iVar15 + 0x3c));
              bVar2 = *(short *)(iVar15 + 0x1c) == -1;
              if (bVar2) {
                iVar15 = -1;
              }
              else {
                texture = *(CTexture **)(iVar15 + 0x40);
                SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,2,texture);
                iVar15 = texture->field93_0x60;
              }
              uVar19 = (uint)!bVar2;
              if ((uVar24 != uVar19) || (iVar8 != iVar15)) {
                GXSetTevDirect(0);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                          (0,0xf,8,10,0xf);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                          (0,7,6,4,7);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (0,0,0,0,1,0);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (0,0,0,0,1,0);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
                iVar8 = 1;
                for (iVar20 = 0; iVar20 < iVar17; iVar20 = iVar20 + 1) {
                  GXSetTevDirect(iVar8);
                  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(iVar8,0,0);
                  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                            (iVar8,0,8,9,0xf);
                  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                            (iVar8,7,7,7,0);
                  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                            (iVar8,0,0,0,1,0);
                  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                            (iVar8,0,0,0,1,0);
                  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                            (iVar8,iVar20 + 3,iVar20 + 3,0xff);
                  iVar8 = iVar8 + 1;
                }
                GXSetTevDirect(iVar8);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(iVar8,0,0);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                          (iVar8,0xf,0,8,0xf);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                          (iVar8,7,0,4,7);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar8,0,0,1,1,0);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar8,0,0,0,1,0);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                          (iVar8,1,1,0xff);
                uVar24 = iVar8 + 1;
                if (uVar19 == 0) {
                  GXSetNumTexGens(iVar17 + 2U & 0xff);
                  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
                  GXSetTexCoordGen2(1,1,4,0x1e,0,0x7d);
                }
                else {
                  GXSetTevDirect(uVar24);
                  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(uVar24,0,0);
                  if (iVar15 == 5) {
                    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                              (uVar24,0xf,0,8,0xf);
                    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                              (uVar24,7,0,4,7);
                    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                              (uVar24,0,0,0,1,0);
                    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                              (uVar24,0,0,0,1,0);
                  }
                  else {
                    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                              (uVar24,0xf,0xf,0xf,0);
                    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                              (uVar24,7,0,4,7);
                    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                              (uVar24,0,0,0,1,0);
                    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                              (uVar24,0,0,0,1,0);
                  }
                  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                            (uVar24,2,2,0xff);
                  uVar24 = iVar8 + 2;
                  GXSetNumTexGens(iVar17 + 3U & 0xff);
                  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
                  GXSetTexCoordGen2(1,1,4,0x1e,0,0x7d);
                  GXSetTexCoordGen2(2,1,4,0x3c,0,0x7d);
                }
                GXSetNumTevStages(uVar24 & 0xff);
                iVar8 = iVar15;
                uVar24 = uVar19;
              }
                    /* WARNING: Load size is inaccurate */
              if ((*pCVar21->m_data & 7) == 0) {
                uVar19 = 0;
                dVar28 = (double)FLOAT_8033115c;
                iVar15 = 0;
                dVar27 = DOUBLE_80331100;
                do {
                  local_98 = (double)CONCAT44(0x43300000,uVar19 ^ 0x80000000);
                  dVar29 = (double)(float)((double)(float)((double)(float)(local_98 - dVar27) *
                                                          dVar28) * dVar26);
                  dVar30 = dVar29;
                  GXInitTexObj(auStack_1bc,DAT_8032edf0 + iVar15,0x80,0x80,2,1,1,0);
                  GXLoadTexObj(auStack_1bc,1);
                  uVar14 = pCVar21->m_size;
                  puVar11 = (ushort *)pCVar21->m_data;
LAB_800e3240:
                  do {
                    if (uVar14 == 0) break;
                    bVar3 = *(byte *)puVar11;
                    uVar4 = *(ushort *)((int)puVar11 + 1);
                    uVar7 = (uint)uVar4;
                    puVar11 = (ushort *)((int)puVar11 + 3);
                    bVar10 = bVar3 & 0xf8;
                    uVar14 = uVar14 - (uVar7 * 8 + 3);
                    if ((bVar10 == 0x90) || (bVar10 == 0x98)) {
                      GXBegin(bVar10,0,uVar4);
                      if (uVar7 != 0) {
                        uVar25 = (uint)(uVar4 >> 1);
                        if (uVar4 >> 1 != 0) {
                          do {
                            pSVar13 = pCVar23->m_workPositions + *puVar11;
                            pSVar12 = pCVar23->m_workNormals + puVar11[1];
                            DAT_cc008000 = (float)((double)*(float *)pSVar12 * dVar29 +
                                                  (double)*(float *)pSVar13);
                            DAT_cc008000 = (float)((double)*(float *)&pSVar12->z * dVar30 +
                                                  (double)*(float *)&pSVar13->z);
                            DAT_cc008000 = (float)((double)*(float *)&pSVar12->z * dVar29 +
                                                  (double)*(float *)&pSVar13->z);
                            DAT_cc008000._0_2_ = puVar11[1];
                            DAT_cc008000._0_2_ = puVar11[3];
                            pSVar13 = pCVar23->m_workPositions + puVar11[4];
                            pSVar12 = pCVar23->m_workNormals + puVar11[5];
                            local_1f0 = (float)((double)*(float *)pSVar12 * dVar29 +
                                               (double)*(float *)pSVar13);
                            local_1ec = (float)((double)*(float *)&pSVar12->z * dVar30 +
                                               (double)*(float *)&pSVar13->z);
                            local_1e8 = (float)((double)*(float *)&pSVar12->z * dVar29 +
                                               (double)*(float *)&pSVar13->z);
                            DAT_cc008000 = local_1f0;
                            DAT_cc008000 = local_1ec;
                            DAT_cc008000 = local_1e8;
                            DAT_cc008000._0_2_ = puVar11[5];
                            puVar1 = puVar11 + 7;
                            puVar11 = puVar11 + 8;
                            DAT_cc008000._0_2_ = *puVar1;
                            uVar25 = uVar25 - 1;
                          } while (uVar25 != 0);
                          uVar7 = uVar7 & 1;
                          if ((uVar4 & 1) == 0) goto LAB_800e3240;
                        }
                        do {
                          pSVar13 = pCVar23->m_workPositions + *puVar11;
                          pSVar12 = pCVar23->m_workNormals + puVar11[1];
                          local_1f0 = (float)((double)*(float *)pSVar12 * dVar29 +
                                             (double)*(float *)pSVar13);
                          local_1ec = (float)((double)*(float *)&pSVar12->z * dVar30 +
                                             (double)*(float *)&pSVar13->z);
                          local_1e8 = (float)((double)*(float *)&pSVar12->z * dVar29 +
                                             (double)*(float *)&pSVar13->z);
                          DAT_cc008000 = local_1f0;
                          DAT_cc008000 = local_1ec;
                          DAT_cc008000 = local_1e8;
                          DAT_cc008000._0_2_ = puVar11[1];
                          puVar1 = puVar11 + 3;
                          puVar11 = puVar11 + 4;
                          DAT_cc008000._0_2_ = *puVar1;
                          uVar7 = uVar7 - 1;
                        } while (uVar7 != 0);
                      }
                      goto LAB_800e3240;
                    }
                  } while ((bVar3 & 0xf8) != 0);
                  uVar19 = uVar19 + 1;
                  iVar15 = iVar15 + 0x4000;
                } while ((int)uVar19 < 8);
              }
            }
            pCVar21 = pCVar21 + 1;
          }
        }
        pCVar23 = pCVar23 + 1;
      }
      EnableLight__9CLightPcsFii(&LightPcs,1,0);
    }
  }
  return;
}

