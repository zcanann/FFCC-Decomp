// Function: SB_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 8012de28
// Size: 776 bytes

void SB_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (CModel *model,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  CDisplayList *pCVar3;
  undefined auStack_28 [4];
  undefined4 local_24;
  undefined auStack_20 [4];
  undefined4 local_1c [4];
  
  pCVar3 = (model->m_meshes[param_4].m_data)->m_displayLists + param_5;
  if (*(char *)(param_2 + 0x24) != '\0') {
    iVar1 = __vc__22CPtrArray<P9CMaterial>FUl
                      (&model->m_data->m_materialSet->materials,pCVar3->m_material);
    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
              (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar3->m_material,1,0);
    GXSetArray(0xb,param_2 + 0x28,4);
    if (*(short *)(iVar1 + 0x18) == 1) {
      GXSetNumChans(1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_20,0xa0,0xa0,0xa0,0xa0);
      local_1c[0] = *puVar2;
      GXSetTevKColor(0,local_1c);
      GXSetTevKColorSel(0,0xc);
      GXSetTevKAlphaSel(0,0x1c);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,10,0xe,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0xc,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,4,5,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,0,4);
      puVar2 = (undefined4 *)
               __ct__6CColorFUcUcUcUc(auStack_28,0x60,0x60,0x60,*(undefined *)(param_2 + 0x2b));
      local_24 = *puVar2;
      GXSetTevKColor(1,&local_24);
      GXSetTevKColorSel(1,0xd);
      GXSetTevKAlphaSel(1,0x1d);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,0xf,0xe,0,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,7,4,5,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0,0,4);
      GXSetTevKAlphaSel(2,0x1d);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (2,0xf,0xc,8,0);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (2,7,7,7,6);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      GXSetNumTevStages(3);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      GXLoadTexObj(*(undefined4 *)(param_2 + 0x10),0);
    }
    GXCallDisplayList(pCVar3->m_data,pCVar3->m_size);
  }
  return;
}

