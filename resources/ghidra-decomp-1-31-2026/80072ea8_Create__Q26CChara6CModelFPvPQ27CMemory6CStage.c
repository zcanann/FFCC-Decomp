// Function: Create__Q26CChara6CModelFPvPQ27CMemory6CStage
// Entry: 80072ea8
// Size: 1496 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Create__Q26CChara6CModelFPvPQ27CMemory6CStage(CModel *model,void *param_2,CStage *stage)

{
  float fVar1;
  CModelCRefData *ref;
  uint32_t uVar2;
  CMaterialSet *pCVar3;
  CTexAnimSet *texAnimSet;
  undefined4 uVar4;
  CNodeCRefData *pCVar5;
  CNode *pCVar6;
  CMeshCRefData *pCVar7;
  CMesh *pCVar8;
  uint16_t *puVar9;
  undefined4 uVar10;
  int iVar11;
  double dVar12;
  undefined local_e8 [216];
  
  ref = (CModelCRefData *)__nw__FUlPQ27CMemory6CStagePci(0x44,stage,s_chara_cpp_801d90c8,0x111);
  if (ref != (CModelCRefData *)0x0) {
    __ct__4CRefFv((CRef *)ref);
    (ref->ref).vtable = &PTR_PTR_s_CChara_CModel_CRefData_801fcd0c;
    fVar1 = FLOAT_803301bc;
    ref->m_nodeCount = 0;
    ref->m_meshCount = 0;
    ref->m_nodeRef = (CNodeCRefData *)0x0;
    ref->m_meshRef = (CMeshCRefData *)0x0;
    ref->m_bank = (uint16_t *)0x0;
    ref->m_headIndex = 0xffff;
    ref->m_chest3Index = 0xffff;
    ref->m_chest2Index = 0xffff;
    ref->m_chest1Index = 0xffff;
    ref->m_materialSet = (CMaterialSet *)0x0;
    ref->m_baseScale = fVar1;
    ref->m_posQuant = 7;
    ref->m_normQuant = 0xc;
    ref->m_dynParams = (void *)0x0;
    ref->m_dynCount = 0;
  }
  model->m_data = ref;
  __ct__10CChunkFileFPv((CChunkFile *)(local_e8 + 0x10),param_2);
  while( true ) {
    do {
      iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                         ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8);
      if (iVar11 == 0) {
        setup__Q26CChara6CModelFv(model);
        if (model->m_texAnimSet != (CTexAnimSet *)0x0) {
          AttachMaterialSet__11CTexAnimSetFP12CMaterialSet
                    (model->m_texAnimSet,model->m_data->m_materialSet);
        }
        return;
      }
    } while (local_e8._0_4_ != 0x43484d20);
    if ((uint)local_e8._8_4_ < 5) break;
    PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
    while (iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                              ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
          uVar10 = local_e8._4_4_, iVar11 != 0) {
      if (local_e8._0_4_ == 0x494e464f) {
        dVar12 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        model->m_data->m_baseScale = (float)dVar12;
        dVar12 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        model->m_furLenScale = (float)dVar12;
        dVar12 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        model->m_furStep = (float)dVar12;
      }
      else if (local_e8._0_4_ == 0x5155414e) {
        uVar2 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        model->m_data->m_posQuant = uVar2;
        uVar2 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        model->m_data->m_normQuant = uVar2;
      }
      else if (local_e8._0_4_ == 0x4d534554) {
        pCVar3 = (CMaterialSet *)
                 __nw__12CMaterialSetFUlPQ27CMemory6CStagePci
                           ((CMaterialSet *)0x24,Chara._8280_4_,s_chara_cpp_801d90c8,0x132);
        if (pCVar3 != (CMaterialSet *)0x0) {
          pCVar3 = (CMaterialSet *)__ct__12CMaterialSetFv(pCVar3);
        }
        model->m_data->m_materialSet = pCVar3;
        pCVar3 = model->m_data->m_materialSet;
        SetDefaultSize__22CPtrArray<P9CMaterial>FUl(&pCVar3->materials,0x20);
        SetGrow__22CPtrArray<P9CMaterial>Fi(&pCVar3->materials,0);
        Create__12CMaterialSetFR10CChunkFileP11CTextureSetQ212CMaterialMan7TEV_BITPQ29CLightPcs10CBumpLight
                  (model->m_data->m_materialSet,local_e8 + 0x10,0,0xfff531f0,DAT_8032edc0);
      }
      else if (local_e8._0_4_ == 0x54415354) {
        if (local_e8._4_4_ != 0) {
          texAnimSet = (CTexAnimSet *)
                       __nw__FUlPQ27CMemory6CStagePci
                                 (0x28,Chara._8280_4_,s_chara_cpp_801d90c8,0x13a);
          if (texAnimSet != (CTexAnimSet *)0x0) {
            texAnimSet = (CTexAnimSet *)__ct__11CTexAnimSetFv(texAnimSet);
          }
          model->m_texAnimSet = texAnimSet;
          Create__11CTexAnimSetFR10CChunkFilePQ27CMemory6CStage
                    (model->m_texAnimSet,(CChunkFile *)(local_e8 + 0x10),stage);
        }
      }
      else if (local_e8._0_4_ == 0x4e534554) {
        model->m_data->m_nodeCount = 0;
        uVar4 = __nwa__FUlPQ27CMemory6CStagePci
                          (local_e8._4_4_ * 0x94 + 0x10,stage,s_chara_cpp_801d90c8,0x143);
        pCVar5 = (CNodeCRefData *)
                 __construct_new_array
                           (uVar4,__ct__Q36CChara5CNode8CRefDataFv,__dt__Q36CChara5CNode8CRefDataFv,
                            0x94,uVar10);
        uVar10 = local_e8._4_4_;
        model->m_data->m_nodeRef = pCVar5;
        uVar4 = __nwa__FUlPQ27CMemory6CStagePci
                          (local_e8._4_4_ * 0xc0 + 0x10,stage,s_chara_cpp_801d90c8,0x145);
        pCVar6 = (CNode *)__construct_new_array
                                    (uVar4,__ct__Q26CChara5CNodeFv,__dt__Q26CChara5CNodeFv,0xc0,
                                     uVar10);
        model->m_nodes = pCVar6;
        PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        while (iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                  ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
              iVar11 != 0) {
          if (local_e8._0_4_ == 0x4e4f4445) {
            pCVar6 = model->m_nodes + model->m_data->m_nodeCount;
            Create__Q26CChara5CNodeFR10CChunkFilePQ26CChara6CModelQ36CChara5CNode4TYPEPQ27CMemory6CStage
                      (pCVar6,(CChunkFile *)(local_e8 + 0x10),model,local_e8._4_4_,stage);
            iVar11 = strcmp(pCVar6->m_refData->m_name,s_chest1_80330200);
            if (iVar11 == 0) {
              model->m_data->m_chest1Index = pCVar6->m_refData->m_index;
            }
            else {
              iVar11 = strcmp(pCVar6->m_refData->m_name,s_chest2_80330208);
              if (iVar11 == 0) {
                model->m_data->m_chest2Index = pCVar6->m_refData->m_index;
              }
              else {
                iVar11 = strcmp(pCVar6->m_refData->m_name,&DAT_80330210);
                if (iVar11 == 0) {
                  model->m_data->m_chest3Index = pCVar6->m_refData->m_index;
                }
                else {
                  iVar11 = strcmp(pCVar6->m_refData->m_name,&DAT_80330218);
                  if (iVar11 == 0) {
                    model->m_data->m_headIndex = pCVar6->m_refData->m_index;
                  }
                }
              }
            }
            model->m_data->m_nodeCount = model->m_data->m_nodeCount + 1;
          }
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
      }
      else if (local_e8._0_4_ == 0x4d535354) {
        model->m_data->m_meshCount = 0;
        uVar4 = __nwa__FUlPQ27CMemory6CStagePci
                          (local_e8._4_4_ * 100 + 0x10,stage,s_chara_cpp_801d90c8,0x171);
        pCVar7 = (CMeshCRefData *)
                 __construct_new_array
                           (uVar4,__ct__Q36CChara5CMesh8CRefDataFv,__dt__Q36CChara5CMesh8CRefDataFv,
                            100,uVar10);
        uVar10 = local_e8._4_4_;
        model->m_data->m_meshRef = pCVar7;
        uVar4 = __nwa__FUlPQ27CMemory6CStagePci
                          (local_e8._4_4_ * 0x14 + 0x10,stage,s_chara_cpp_801d90c8,0x173);
        pCVar8 = (CMesh *)__construct_new_array
                                    (uVar4,__ct__Q26CChara5CMeshFv,__dt__Q26CChara5CMeshFv,0x14,
                                     uVar10);
        model->m_meshes = pCVar8;
        PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        while (iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                  ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
              iVar11 != 0) {
          if (local_e8._0_4_ == 0x4d455348) {
            Create__Q26CChara5CMeshFPQ26CChara6CModelR10CChunkFilePQ27CMemory6CStage
                      ((CModel *)(model->m_meshes + model->m_data->m_meshCount),model,
                       local_e8 + 0x10,stage);
            model->m_data->m_meshCount = model->m_data->m_meshCount + 1;
          }
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
      }
      else if (local_e8._0_4_ == 0x42414e4b) {
        puVar9 = (uint16_t *)
                 __nwa__FUlPQ27CMemory6CStagePci(local_e8._12_4_,stage,s_chara_cpp_801d90c8,0x187);
        model->m_data->m_bank = puVar9;
        uVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        memcpy(model->m_data->m_bank,uVar10,local_e8._12_4_);
      }
    }
    PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
  }
  if ((uint)System.m_execParam < 2) {
    return;
  }
  Printf__7CSystemFPce(&System,&DAT_801d90d4);
  return;
}

