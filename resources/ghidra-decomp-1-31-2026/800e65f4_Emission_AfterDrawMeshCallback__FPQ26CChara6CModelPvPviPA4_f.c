// Function: Emission_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
// Entry: 800e65f4
// Size: 1216 bytes

/* WARNING: Removing unreachable block (ram,0x800e6a98) */
/* WARNING: Removing unreachable block (ram,0x800e6604) */

void Emission_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
               (CModel *model,undefined4 *param_2,int param_3,int meshIndex,Mtx *param_5)

{
  float fVar1;
  int iVar2;
  uint32_t uVar3;
  float *pfVar4;
  uint uVar5;
  CDisplayList *pCVar6;
  CMeshCRefData *pCVar7;
  double dVar8;
  Mtx MStack_178;
  Mtx MStack_148;
  Mtx MStack_118;
  Mtx MStack_e8;
  Mtx MStack_b8;
  Mtx MStack_88;
  undefined4 local_58;
  uint uStack_54;
  
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x66);
  pCVar7 = model->m_meshes[meshIndex].m_data;
  iVar2 = strcmp(pCVar7,&DAT_803311fc);
  if ((iVar2 == 0) && (*(char *)((int)param_2 + 0xb) != '\0')) {
    iVar2 = param_2[1];
    pppInitBlendMode__Fv();
    pppSetBlendMode__FUc(*(undefined *)(param_3 + 0x1c));
    MaterialMan._208_4_ = iVar2 + 0x28;
    if (*(char *)(param_3 + 0x1d) == '\0') {
      dVar8 = DOUBLE_803311f0;
      for (uVar5 = 0; (int)uVar5 < (int)(uint)*(byte *)(param_3 + 8); uVar5 = uVar5 + 1) {
        uStack_54 = uVar5 ^ 0x80000000;
        local_58 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_54) - dVar8) * (float)param_2[3] +
                FLOAT_803311e4;
        PSMTXScale(fVar1,fVar1,fVar1,&MStack_b8);
        PSMTXConcat(param_5,&MStack_b8,&MStack_b8);
        PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_88);
        SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan,&MStack_88,&MStack_b8);
        uVar3 = pCVar7->m_displayListCount;
        pCVar6 = pCVar7->m_displayLists;
        while (uVar3 = uVar3 - 1, -1 < (int)uVar3) {
          MaterialMan._68_4_ = 0xffffffff;
          MaterialMan._76_1_ = 0xff;
          MaterialMan._284_4_ = 0;
          MaterialMan._288_4_ = 0x1e;
          MaterialMan._292_4_ = 0;
          MaterialMan._517_1_ = 0xff;
          MaterialMan._518_1_ = 0xff;
          MaterialMan._88_4_ = 0;
          MaterialMan._92_4_ = 0;
          MaterialMan._520_1_ = 0;
          MaterialMan._72_4_ = 0xece0f;
          MaterialMan._296_4_ = 0;
          MaterialMan._300_4_ = 0x1e;
          MaterialMan._304_4_ = 0;
          MaterialMan._64_4_ = 0xece0f;
          SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                    (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar6->m_material,0,0);
          if (*(char *)(param_3 + 0x1e) == '\0') {
            GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
          }
          else {
            PSMTXCopy((Mtx *)&MaterialMan.field_0xe8,&MStack_148);
            GXLoadTexMtxImm(&MStack_148,0x1e,0);
            if (*(char *)(param_3 + 0x1e) == '\x01') {
              GXSetTexCoordGen2(0,0,0,0x1e,0,0x7d);
            }
            else if (*(char *)(param_3 + 0x1e) == '\x02') {
              GXSetTexCoordGen2(0,0,1,0x1e,0,0x7d);
            }
          }
          GXSetArray(0xb,param_2 + 2,4);
          GXSetZMode(1,3,0);
          GXCallDisplayList(pCVar6->m_data,pCVar6->m_size);
          pCVar6 = pCVar6 + 1;
        }
      }
    }
    else if (*(char *)(param_3 + 0x1d) == '\x01') {
      pfVar4 = (float *)*param_2;
      for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(param_3 + 8); iVar2 = iVar2 + 1) {
        fVar1 = *pfVar4;
        PSMTXScale(fVar1,fVar1,fVar1,&MStack_118);
        PSMTXConcat(param_5,&MStack_118,&MStack_118);
        PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_e8);
        PSMTXConcat(&MStack_e8,&MStack_118,&MStack_118);
        GXLoadPosMtxImm(&MStack_118,0);
        uVar3 = pCVar7->m_displayListCount;
        pCVar6 = pCVar7->m_displayLists;
        while (uVar3 = uVar3 - 1, -1 < (int)uVar3) {
          MaterialMan._68_4_ = 0xffffffff;
          MaterialMan._76_1_ = 0xff;
          MaterialMan._284_4_ = 0;
          MaterialMan._288_4_ = 0x1e;
          MaterialMan._292_4_ = 0;
          MaterialMan._517_1_ = 0xff;
          MaterialMan._518_1_ = 0xff;
          MaterialMan._88_4_ = 0;
          MaterialMan._92_4_ = 0;
          MaterialMan._520_1_ = 0;
          MaterialMan._72_4_ = 0xece0f;
          MaterialMan._296_4_ = 0;
          MaterialMan._300_4_ = 0x1e;
          MaterialMan._304_4_ = 0;
          MaterialMan._64_4_ = 0xece0f;
          SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                    (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar6->m_material,0,0);
          if (*(char *)(param_3 + 0x1e) == '\0') {
            GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
          }
          else {
            PSMTXCopy((Mtx *)&MaterialMan.field_0xe8,&MStack_178);
            GXLoadTexMtxImm(&MStack_178,0x1e,0);
            if (*(char *)(param_3 + 0x1e) == '\x01') {
              GXSetTexCoordGen2(0,0,0,0x1e,0,0x7d);
            }
            else if (*(char *)(param_3 + 0x1e) == '\x02') {
              GXSetTexCoordGen2(0,0,1,0x1e,0,0x7d);
            }
          }
          GXSetArray(0xb,(int)pfVar4 + 6,4);
          GXSetZMode(1,3,0);
          GXCallDisplayList(pCVar6->m_data,pCVar6->m_size);
          pCVar6 = pCVar6 + 1;
        }
        pfVar4 = pfVar4 + 4;
      }
    }
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x67);
  }
  return;
}

