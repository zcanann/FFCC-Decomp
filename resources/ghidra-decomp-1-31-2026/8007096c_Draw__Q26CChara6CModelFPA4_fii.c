// Function: Draw__Q26CChara6CModelFPA4_fii
// Entry: 8007096c
// Size: 1192 bytes

void Draw__Q26CChara6CModelFPA4_fii(CModel *model,undefined4 param_2,uint param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint32_t uVar5;
  int iVar6;
  CDisplayList *pCVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  CMesh *pCVar11;
  float local_88;
  float local_84;
  float local_80;
  Mtx MStack_7c;
  
  if (FLOAT_803301b0 != model->m_lightAlpha) {
    uVar2 = param_3 & 1;
    if (((code *)model->m_beforeDrawModelCallback != (code *)0x0) && (param_4 == 0)) {
      (*(code *)model->m_beforeDrawModelCallback)
                (model,model->m_cbUser0,model->m_cbUser1,param_2,uVar2);
    }
    SetTextureSet__12CMaterialSetFP11CTextureSet(model->m_data->m_materialSet,model->m_texSet);
    if (model->m_texAnimSet != (CTexAnimSet *)0x0) {
      SetTexGen__11CTexAnimSetFv(model->m_texAnimSet);
    }
    InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
              (&MaterialMan,0xffffffff,3,model->m_data->m_posQuant,3,model->m_data->m_normQuant,3,
               0xc);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    uVar4 = 1;
    if (uVar2 != 0) {
      uVar4 = 2;
    }
    GXSetCullMode(uVar4);
    SetAmbientAlpha__9CLightPcsFf((double)model->m_lightAlpha,&LightPcs);
    pCVar11 = model->m_meshes;
    iVar10 = 0;
    iVar9 = 0;
    for (uVar8 = 0; uVar8 < model->m_data->m_meshCount; uVar8 = uVar8 + 1) {
      if (pCVar11->m_workPositions != (S16Vec *)0x0) {
        if ((0x1f < (int)uVar8) || ((model->m_meshVisibleMask >> uVar8 & 1) != 0)) {
          MaterialMan._72_4_ = 0xace0f;
          MaterialMan._68_4_ = 0xffffffff;
          MaterialMan._76_1_ = 0xff;
          MaterialMan._296_4_ = 0;
          MaterialMan._284_4_ = 0;
          MaterialMan._300_4_ = 0x1e;
          MaterialMan._288_4_ = 0x1e;
          MaterialMan._304_4_ = 0;
          MaterialMan._292_4_ = 0;
          MaterialMan._517_1_ = 0xff;
          MaterialMan._518_1_ = 0xff;
          MaterialMan._88_4_ = 0;
          MaterialMan._92_4_ = 0;
          MaterialMan._520_1_ = 0;
          if (pCVar11->m_data->m_skinCount == 0) {
            PSMTXConcat(&model->m_drawMtx,&model->m_nodes[pCVar11->m_data->m_nodeIndex].m_mtx,
                        &MStack_7c);
          }
          else {
            PSMTXCopy(&model->m_drawMtx,&MStack_7c);
          }
          if (((uVar2 == 0) && ((param_3 >> 1 & 1) != 1)) ||
             ((uVar2 != 0 && ((param_3 >> 3 & 1) != 0)))) {
            SetFullScreenShadow__10CCameraPcsFPA4_fl(&CameraPcs,&MStack_7c,0);
          }
          if ((param_3 >> 4 & 1) != 1) {
            local_88 = (model->m_drawMtx).value[0][3];
            local_84 = (model->m_drawMtx).value[1][3];
            local_80 = (model->m_drawMtx).value[2][3];
            SetPosition__12CMaterialManFQ210CMapShadow6TARGETP3VecffPA4_fi
                      ((double)FLOAT_803301c8,(double)FLOAT_803301cc,&MaterialMan,0,&local_88,
                       &MStack_7c,(int)((uint)model->m_flagsA0 << 0x18) >> 0x1f);
          }
          iVar6 = (int)((uint)pCVar11->m_data->m_flags << 0x18) >> 0x1f;
          if (iVar10 != iVar6) {
            uVar3 = countLeadingZeros(iVar6);
            EnableLight__9CLightPcsFii(&LightPcs,uVar3 >> 5 & 0xff,0);
            iVar10 = iVar6;
          }
          bVar1 = pCVar11->m_data->m_flags;
          iVar6 = (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) >> 0x1f;
          if (iVar9 != iVar6) {
            uVar3 = countLeadingZeros(iVar6);
            GXSetZMode(1,3,uVar3 >> 5);
            iVar9 = iVar6;
          }
          if ((code *)model->m_beforeMeshCallback != (code *)0x0) {
            (*(code *)model->m_beforeMeshCallback)(model,model->m_cbUser0,model->m_cbUser1,uVar8);
          }
          MaterialMan._296_4_ = MaterialMan._284_4_;
          MaterialMan._300_4_ = MaterialMan._288_4_;
          MaterialMan._304_4_ = MaterialMan._292_4_;
          MaterialMan._64_4_ = MaterialMan._72_4_;
          if (pCVar11->m_data->m_infoWord1 != 0) {
            SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
                      (&LightPcs,&MStack_7c,DAT_8032edc0,0,0);
          }
          SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan,param_2,&MStack_7c);
          GXSetArray(9,pCVar11->m_workPositions,6);
          MaterialMan._4_4_ = pCVar11->m_workNormals;
          GXSetArray(0xb,pCVar11->m_data->m_colors,4);
          GXSetArray(0xd,pCVar11->m_data->m_uvs,4);
          GXSetArray(0xe,pCVar11->m_data->m_uvs,4);
          uVar5 = pCVar11->m_data->m_displayListCount;
          pCVar7 = pCVar11->m_data->m_displayLists;
          while (uVar5 = uVar5 - 1, -1 < (int)uVar5) {
            if ((code *)model->m_afterMeshDrawCallback == (code *)0x0) {
              SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                        (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar7->m_material,
                         param_3 >> 2 & 1,0);
              GXCallDisplayList(pCVar7->m_data,pCVar7->m_size);
            }
            else {
              (*(code *)model->m_afterMeshDrawCallback)
                        (model,model->m_cbUser0,model->m_cbUser1,uVar8,uVar5,&MStack_7c);
            }
            pCVar7 = pCVar7 + 1;
          }
          if ((code *)model->m_afterMeshEnvCallback != (code *)0x0) {
            (*(code *)model->m_afterMeshEnvCallback)
                      (model,model->m_cbUser0,model->m_cbUser1,uVar8,&MStack_7c);
          }
        }
      }
      pCVar11 = pCVar11 + 1;
    }
    if ((code *)model->m_afterDrawModelCallback != (code *)0x0) {
      (*(code *)model->m_afterDrawModelCallback)(model,model->m_cbUser0,model->m_cbUser1);
    }
  }
  return;
}

