// Function: CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
// Entry: 80072ae4
// Size: 964 bytes

void CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
               (CModel *model,void *param_2,undefined4 param_3)

{
  CNodeCRefData **ppCVar1;
  void *pvVar2;
  undefined4 uVar3;
  uint8_t uVar5;
  int iVar4;
  CNode *pCVar6;
  uint uVar7;
  double dVar8;
  undefined local_e8 [212];
  
  __ct__10CChunkFileFPv((CChunkFile *)(local_e8 + 0x10),param_2);
  do {
    do {
      iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                        ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8);
      if (iVar4 == 0) {
        return;
      }
    } while (local_e8._0_4_ != 0x43484420);
    pvVar2 = model->m_data->m_dynParams;
    if (pvVar2 != (void *)0x0) {
      __dla__FPv(pvVar2);
      model->m_data->m_dynParams = (void *)0x0;
    }
    model->m_data->m_dynCount = 0;
    pCVar6 = model->m_nodes;
    for (uVar7 = 0; uVar7 < model->m_data->m_nodeCount; uVar7 = uVar7 + 1) {
      ppCVar1 = &pCVar6->m_refData;
      pCVar6 = pCVar6 + 1;
      (*ppCVar1)->m_dynParamIndex = 0xff;
    }
    PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
    while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8), iVar4 != 0) {
      if (local_e8._0_4_ == 0x44475250) {
        if (local_e8._4_4_ != 0) {
          model->m_data->m_dynCount = 0;
          pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                     (local_e8._4_4_ * 0x24,param_3,s_chara_cpp_801d90c8,0x1e7);
          model->m_data->m_dynParams = pvVar2;
          PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
          while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
                iVar4 != 0) {
            if (local_e8._0_4_ == 0x44594e20) {
              PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
              while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                       ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
                    iVar4 != 0) {
                if (local_e8._0_4_ == 0x5041524d) {
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams + model->m_data->m_dynCount * 0x24) =
                       (float)dVar8;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams + model->m_data->m_dynCount * 0x24 + 4)
                       = (float)dVar8;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams + model->m_data->m_dynCount * 0x24 + 8)
                       = (float)dVar8;
                  uVar3 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(undefined4 *)
                   ((int)model->m_data->m_dynParams + model->m_data->m_dynCount * 0x24 + 0xc) =
                       uVar3;
                  uVar3 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(undefined4 *)
                   ((int)model->m_data->m_dynParams + model->m_data->m_dynCount * 0x24 + 0x10) =
                       uVar3;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams +
                            model->m_data->m_dynCount * 0x24 + 0x14) = (float)dVar8;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams +
                            model->m_data->m_dynCount * 0x24 + 0x1c) = (float)dVar8;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams +
                            model->m_data->m_dynCount * 0x24 + 0x18) = (float)dVar8;
                  dVar8 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                  *(float *)((int)model->m_data->m_dynParams +
                            model->m_data->m_dynCount * 0x24 + 0x20) = (float)dVar8;
                }
              }
              PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
            }
            model->m_data->m_dynCount = model->m_data->m_dynCount + 1;
          }
          PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        }
      }
      else if (local_e8._0_4_ == 0x4e534554) {
        PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
        uVar7 = 0;
LAB_80072e48:
        iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                          ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8);
        if (iVar4 != 0) {
          if (local_e8._0_4_ == 0x4e414d45) {
            uVar3 = GetString__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
            pCVar6 = model->m_nodes;
            for (uVar7 = 0; uVar7 < model->m_data->m_nodeCount; uVar7 = uVar7 + 1) {
              iVar4 = strcmp(pCVar6->m_refData->m_name,uVar3);
              if (iVar4 == 0) goto LAB_80072e48;
              pCVar6 = pCVar6 + 1;
            }
            uVar7 = 0xffffffff;
          }
          else if (local_e8._0_4_ == 0x44594e20) {
            PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
            while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8),
                  iVar4 != 0) {
              if (local_e8._0_4_ == 0x5041524d) {
                uVar5 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
                (model->m_nodes[uVar7].m_refData)->m_dynParamIndex = uVar5;
              }
            }
            PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
          }
          goto LAB_80072e48;
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
      }
    }
    PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
  } while( true );
}

