// Function: DrawShadow__Q26CChara6CModelFPA4_fi
// Entry: 80070690
// Size: 732 bytes

void DrawShadow__Q26CChara6CModelFPA4_fi(CModel *model,undefined4 param_2,undefined param_3)

{
  uint32_t uVar1;
  CDisplayList *pCVar2;
  uint uVar3;
  CMesh *pCVar4;
  Mtx MStack_58;
  
  if (FLOAT_803301bc == model->m_lightAlpha) {
    SetTextureSet__12CMaterialSetFP11CTextureSet(model->m_data->m_materialSet,model->m_texSet);
    SetAmbientAlpha__9CLightPcsFf((double)FLOAT_803301bc,&LightPcs);
    InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
              (&MaterialMan,0xffffffff,3,model->m_data->m_posQuant,3,model->m_data->m_normQuant,3,
               0xc);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(param_3,3,param_3);
    GXSetCullMode(1);
    pCVar4 = model->m_meshes;
    for (uVar3 = 0; uVar3 < model->m_data->m_meshCount; uVar3 = uVar3 + 1) {
      if ((pCVar4->m_workPositions != (S16Vec *)0x0) &&
         ((model->m_meshVisibleMask >> uVar3 & 1) != 0)) {
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
        if (pCVar4->m_data->m_skinCount == 0) {
          PSMTXConcat(&model->m_drawMtx,&model->m_nodes[pCVar4->m_data->m_nodeIndex].m_mtx,
                      &MStack_58);
        }
        else {
          PSMTXCopy(&model->m_drawMtx,&MStack_58);
        }
        if ((code *)model->m_customMeshDrawCallback != (code *)0x0) {
          (*(code *)model->m_customMeshDrawCallback)(model,model->m_cbUser0,model->m_cbUser1,uVar3);
        }
        MaterialMan._296_4_ = MaterialMan._284_4_;
        MaterialMan._300_4_ = MaterialMan._288_4_;
        MaterialMan._304_4_ = MaterialMan._292_4_;
        MaterialMan._64_4_ = MaterialMan._72_4_;
        SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan,param_2,&MStack_58);
        GXSetArray(9,pCVar4->m_workPositions,6);
        MaterialMan._4_4_ = pCVar4->m_workNormals;
        GXSetArray(0xb,pCVar4->m_data->m_colors,4);
        GXSetArray(0xd,pCVar4->m_data->m_uvs,4);
        GXSetArray(0xe,pCVar4->m_data->m_uvs,4);
        uVar1 = pCVar4->m_data->m_displayListCount;
        pCVar2 = pCVar4->m_data->m_displayLists;
        while (uVar1 = uVar1 - 1, -1 < (int)uVar1) {
          if ((code *)model->m_unknownCallback0x100 == (code *)0x0) {
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                      (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar2->m_material,1,0);
            GXCallDisplayList(pCVar2->m_data,pCVar2->m_size);
          }
          else {
            (*(code *)model->m_unknownCallback0x100)
                      (model,model->m_cbUser0,model->m_cbUser1,uVar3,uVar1,&MStack_58);
          }
          pCVar2 = pCVar2 + 1;
        }
      }
      pCVar4 = pCVar4 + 1;
    }
  }
  return;
}

