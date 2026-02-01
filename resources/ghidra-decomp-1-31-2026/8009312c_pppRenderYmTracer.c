// Function: pppRenderYmTracer
// Entry: 8009312c
// Size: 920 bytes

/* WARNING: Removing unreachable block (ram,0x800934a8) */
/* WARNING: Removing unreachable block (ram,0x800934a0) */
/* WARNING: Removing unreachable block (ram,0x80093498) */
/* WARNING: Removing unreachable block (ram,0x8009314c) */
/* WARNING: Removing unreachable block (ram,0x80093144) */
/* WARNING: Removing unreachable block (ram,0x8009313c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmTracer(pppYmTracer *pppYmTracer,UnkB *param_2,UnkC *param_3)

{
  CTexture *texture;
  int iVar1;
  int iVar2;
  uint uVar3;
  CMapMesh *mapMesh;
  float *pfVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [2];
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  
  iVar1 = *param_3->m_serializedDataOffsets;
  iVar2 = param_3->m_serializedDataOffsets[1];
  pfVar4 = *(float **)(&pppYmTracer->field_0xa8 + iVar1);
  mapMesh = pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
  if (param_2->m_dataValIndex != 0xffff) {
    pppSetBlendMode__FUc(param_2->m_payload[10]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_803306e8,(pppCVector *)(&pppYmTracer->field_0x88 + iVar2),&ppvCameraMatrix0,
               param_2->m_payload[0xc],param_2->m_payload[0xb],param_2->m_payload[10],0,1,1,0);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    local_68[0] = 0;
    texture = (CTexture *)
              GetTexture__8CMapMeshFP12CMaterialSetRi
                        (mapMesh,pppEnvStPtr->m_materialSetPtr,local_68);
    if (texture != (CTexture *)0x0) {
      GXLoadTexObj(&texture->field_0x28,0);
      GXSetNumChans(1);
      GXSetNumTexGens(1);
      GXSetNumTevStages(1);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
      if ((texture->field93_0x60 == 8) || (texture->field93_0x60 == 9)) {
        SetUpPaletteEnv__FP8CTexture(texture);
      }
      uStack_5c = (uint)*(ushort *)(&pppYmTracer->field_0xac + iVar1);
      local_60 = 0x43300000;
      dVar7 = (double)(FLOAT_803306ec /
                      (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_803306f0));
      GXSetCullMode(0);
      for (uVar3 = 0; (int)uVar3 < (int)(*(ushort *)(&pppYmTracer->field_0xac + iVar1) - 1);
          uVar3 = uVar3 + 1) {
        if (((((0 < *(short *)(pfVar4 + 0x12)) && (FLOAT_803306e8 != pfVar4[4])) &&
             (FLOAT_803306e8 != pfVar4[5])) &&
            (((FLOAT_803306e8 != pfVar4[6] && (FLOAT_803306e8 != *pfVar4)) &&
             ((FLOAT_803306e8 != pfVar4[1] &&
              ((FLOAT_803306e8 != pfVar4[2] && (FLOAT_803306e8 != pfVar4[0xe])))))))) &&
           ((FLOAT_803306e8 != pfVar4[0xf] &&
            ((((FLOAT_803306e8 != pfVar4[0x10] && (FLOAT_803306e8 != pfVar4[10])) &&
              (FLOAT_803306e8 != pfVar4[0xb])) && (FLOAT_803306e8 != pfVar4[0xc])))))) {
          uStack_5c = uVar3 ^ 0x80000000;
          uStack_54 = uVar3 + 1 ^ 0x80000000;
          local_60 = 0x43300000;
          local_58 = 0x43300000;
          dVar6 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                 DOUBLE_803306f8) * dVar7);
          dVar5 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                 DOUBLE_803306f8) * dVar7);
          local_6c = CONCAT31((int3)((uint)DAT_803306e0 >> 8),*(undefined *)((int)pfVar4 + 0x1f));
          local_70 = CONCAT31((int3)((uint)DAT_803306e4 >> 8),*(undefined *)((int)pfVar4 + 0x47));
          GXBegin(0x98,7,4);
          DAT_cc008000 = pfVar4[4];
          DAT_cc008000 = pfVar4[5];
          DAT_cc008000 = pfVar4[6];
          DAT_cc008000 = local_6c;
          DAT_cc008000 = (float)dVar6;
          DAT_cc008000 = FLOAT_803306ec;
          DAT_cc008000 = *pfVar4;
          DAT_cc008000 = pfVar4[1];
          DAT_cc008000 = pfVar4[2];
          DAT_cc008000 = local_6c;
          DAT_cc008000 = (float)dVar6;
          DAT_cc008000 = FLOAT_803306e8;
          DAT_cc008000 = pfVar4[0xe];
          DAT_cc008000 = pfVar4[0xf];
          DAT_cc008000 = pfVar4[0x10];
          DAT_cc008000 = local_70;
          DAT_cc008000 = (float)dVar5;
          DAT_cc008000 = FLOAT_803306ec;
          DAT_cc008000 = pfVar4[10];
          DAT_cc008000 = pfVar4[0xb];
          DAT_cc008000 = pfVar4[0xc];
          DAT_cc008000 = local_70;
          DAT_cc008000 = (float)dVar5;
          DAT_cc008000 = FLOAT_803306e8;
        }
        pfVar4 = pfVar4 + 10;
      }
    }
  }
  return;
}

