// Function: pppRenderYmTracer2
// Entry: 801035dc
// Size: 984 bytes

/* WARNING: Removing unreachable block (ram,0x80103998) */
/* WARNING: Removing unreachable block (ram,0x80103990) */
/* WARNING: Removing unreachable block (ram,0x801035f4) */
/* WARNING: Removing unreachable block (ram,0x801035ec) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmTracer2(pppYmTracer2 *pppYmTracer2,UnkB *param_2,UnkC *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  float fVar3;
  float fVar4;
  CTexture *texture;
  int iVar5;
  int iVar6;
  CMapMesh *mapMesh;
  uint uVar7;
  undefined4 *puVar8;
  double dVar9;
  double dVar10;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70 [2];
  undefined4 local_68;
  uint uStack_64;
  
  iVar5 = *param_3->m_serializedDataOffsets;
  iVar6 = param_3->m_serializedDataOffsets[1];
  puVar8 = *(undefined4 **)(pppYmTracer2->m_serializedData + iVar5 + 0x28);
  mapMesh = pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
  if (param_2->m_dataValIndex != 0xffff) {
    pppSetBlendMode__FUc(param_2->m_payload[10]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80331840,(pppCVector *)(pppYmTracer2->m_serializedData + iVar6 + 8),
               &ppvCameraMatrix0,param_2->m_payload[0xc],param_2->m_payload[0xb],
               param_2->m_payload[10],0,1,1,0);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    local_70[0] = 0;
    texture = (CTexture *)
              GetTexture__8CMapMeshFP12CMaterialSetRi
                        (mapMesh,pppEnvStPtr->m_materialSetPtr,local_70);
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
      if (param_2->m_payload[0xd] == '\0') {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
      }
      else {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      }
      uStack_64 = (uint)*(ushort *)(pppYmTracer2->m_serializedData + iVar5 + 0x2c);
      local_68 = 0x43300000;
      dVar10 = (double)(FLOAT_80331844 /
                       (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331850));
      GXSetCullMode(0);
      if (1 < *(ushort *)(pppYmTracer2->m_serializedData + iVar5 + 0x2c)) {
        uStack_64 = (uint)pppYmTracer2->m_serializedData[iVar6 + 0xb];
        local_68 = 0x43300000;
        dVar9 = (double)((float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331850) /
                        FLOAT_80331848);
        GXBegin(0x98,7,(*(ushort *)(pppYmTracer2->m_serializedData + iVar5 + 0x2c) - 1) * 4);
        uVar7 = 0;
        while ((int)uVar7 < (int)(*(ushort *)(pppYmTracer2->m_serializedData + iVar5 + 0x2c) - 1)) {
          fVar3 = (float)((double)(float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) -
                                         DOUBLE_80331858) * dVar10);
          fVar4 = (float)((double)(float)((double)CONCAT44(0x43300000,uVar7 + 1 ^ 0x80000000) -
                                         DOUBLE_80331858) * dVar10);
          if (dVar9 < (double)FLOAT_80331840) {
            dVar9 = (double)FLOAT_80331840;
          }
          if ((double)FLOAT_80331844 < dVar9) {
            dVar9 = (double)FLOAT_80331844;
          }
          uVar7 = uVar7 + 1;
          DAT_cc008000 = puVar8[4];
          DAT_cc008000 = puVar8[5];
          local_74 = CONCAT31(*(undefined3 *)(puVar8 + 7),
                              (char)(int)(dVar9 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   (uint)*(byte *)((
                                                  int)puVar8 + 0x1f)) - DOUBLE_80331850)));
          DAT_cc008000 = puVar8[6];
          DAT_cc008000 = local_74;
          DAT_cc008000 = fVar3;
          DAT_cc008000 = FLOAT_80331844;
          DAT_cc008000 = *puVar8;
          DAT_cc008000 = puVar8[1];
          DAT_cc008000 = puVar8[2];
          DAT_cc008000 = local_74;
          DAT_cc008000 = fVar3;
          DAT_cc008000 = FLOAT_80331840;
          DAT_cc008000 = puVar8[0xe];
          DAT_cc008000 = puVar8[0xf];
          local_78 = CONCAT31(*(undefined3 *)(puVar8 + 0x11),
                              (char)(int)(dVar9 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   (uint)*(byte *)((
                                                  int)puVar8 + 0x47)) - DOUBLE_80331850)));
          DAT_cc008000 = puVar8[0x10];
          DAT_cc008000 = local_78;
          DAT_cc008000 = fVar4;
          DAT_cc008000 = FLOAT_80331844;
          puVar1 = puVar8 + 0xc;
          puVar2 = puVar8 + 0xb;
          puVar8 = puVar8 + 10;
          DAT_cc008000 = *puVar8;
          DAT_cc008000 = *puVar2;
          DAT_cc008000 = *puVar1;
          DAT_cc008000 = local_78;
          DAT_cc008000 = fVar4;
          DAT_cc008000 = FLOAT_80331840;
        }
      }
    }
  }
  return;
}

