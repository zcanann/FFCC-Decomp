// Function: Create__9CFlatDataFPv
// Entry: 80097be8
// Size: 1228 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Create__9CFlatDataFPv(CFlatData *cflatData,void *param_2)

{
  int iVar1;
  void *pvVar2;
  int32_t *piVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  CFlatData *pCVar9;
  int iVar10;
  undefined local_f8 [220];
  
  pCVar9 = cflatData;
  for (iVar10 = 0; iVar10 < cflatData->m_dataCount; iVar10 = iVar10 + 1) {
    if (pCVar9->m_data[0].m_data != (void *)0x0) {
      __dl__FPv();
      pCVar9->m_data[0].m_data = (void *)0x0;
    }
    if (pCVar9->m_data[0].m_index != (int32_t *)0x0) {
      __dl__FPv();
      pCVar9->m_data[0].m_index = (int32_t *)0x0;
    }
    if (pCVar9->m_data[0].m_names != (char *)0x0) {
      __dl__FPv();
      pCVar9->m_data[0].m_names = (char *)0x0;
    }
    pCVar9 = (CFlatData *)&pCVar9->m_data[0].m_names;
  }
  cflatData->m_dataCount = 0;
  pCVar9 = cflatData;
  for (iVar10 = 0; iVar10 < cflatData->m_tableCount; iVar10 = iVar10 + 1) {
    if (pCVar9->m_table[0].index != (int32_t *)0x0) {
      __dl__FPv();
      pCVar9->m_table[0].index = (int32_t *)0x0;
    }
    if (pCVar9->m_table[0].data != (void *)0x0) {
      __dl__FPv();
      pCVar9->m_table[0].data = (void *)0x0;
    }
    pCVar9 = (CFlatData *)&pCVar9->m_data[0].m_count;
  }
  cflatData->m_tableCount = 0;
  if (cflatData->m_mesBuffer != (char *)0x0) {
    __dl__FPv();
    cflatData->m_mesBuffer = (char *)0x0;
  }
  cflatData->m_mesCount = 0;
  __ct__10CChunkFileFPv((CChunkFile *)(local_f8 + 0x10),param_2);
  while (iVar10 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                            ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8), iVar10 != 0) {
    if (local_f8._0_4_ == 0x43464c44) {
      PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
      while (iVar10 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8),
            iVar10 != 0) {
        if (local_f8._0_4_ == 0x4d455320) {
          cflatData->m_mesCount = local_f8._4_4_;
          pcVar4 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                     (local_f8._12_4_,Game.game.m_mainStage,
                                      s_cflat_data_cpp_801d9e00,0x76);
          cflatData->m_mesBuffer = pcVar4;
          uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          memcpy(cflatData->m_mesBuffer,uVar5,local_f8._12_4_);
          iVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          pCVar9 = cflatData;
          for (iVar7 = 0; iVar7 < cflatData->m_mesCount; iVar7 = iVar7 + 1) {
            iVar8 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
            pCVar9->m_mesPtr[0] = cflatData->m_mesBuffer + (iVar8 - iVar10);
            GetString__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
            pCVar9 = (CFlatData *)pCVar9->m_data;
          }
        }
        else if ((int)local_f8._0_4_ < 0x4d455320) {
          if (local_f8._0_4_ == 0x44415441) {
            cflatData->m_data[cflatData->m_dataCount].m_size = local_f8._4_4_;
            pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                       (local_f8._4_4_,Game.game.m_mainStage,
                                        s_cflat_data_cpp_801d9e00,0x45);
            cflatData->m_data[cflatData->m_dataCount].m_data = pvVar2;
            Get__10CChunkFileFPvl
                      ((CChunkFile *)(local_f8 + 0x10),
                       cflatData->m_data[cflatData->m_dataCount].m_data,local_f8._4_4_);
            if (local_f8._8_4_ == 0) {
              cflatData->m_data[cflatData->m_dataCount].m_count = 0;
              cflatData->m_data[cflatData->m_dataCount].m_names = (char *)0x0;
              cflatData->m_data[cflatData->m_dataCount].m_index = (int32_t *)0x0;
            }
            else {
              iVar10 = Get4__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
              cflatData->m_data[cflatData->m_dataCount].m_count = iVar10;
              piVar3 = (int32_t *)
                       __nwa__FUlPQ27CMemory6CStagePci
                                 (iVar10 << 2,Game.game.m_mainStage,s_cflat_data_cpp_801d9e00,0x4c);
              cflatData->m_data[cflatData->m_dataCount].m_index = piVar3;
              pcVar4 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                         (iVar10,Game.game.m_mainStage,s_cflat_data_cpp_801d9e00,
                                          0x4d);
              cflatData->m_data[cflatData->m_dataCount].m_names = pcVar4;
              uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
              memcpy(cflatData->m_data[cflatData->m_dataCount].m_names,uVar5,iVar10);
              iVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
              iVar8 = 0;
              for (iVar7 = 0; iVar1 = cflatData->m_dataCount,
                  iVar7 < cflatData->m_data[iVar1].m_count; iVar7 = iVar7 + 1) {
                iVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
                *(char **)((int)cflatData->m_data[iVar1].m_index + iVar8) =
                     cflatData->m_data[iVar1].m_names + (iVar6 - iVar10);
                GetString__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
                iVar8 = iVar8 + 4;
              }
            }
            cflatData->m_dataCount = cflatData->m_dataCount + 1;
          }
        }
        else if (local_f8._0_4_ == 0x5441424c) {
          cflatData->m_table[cflatData->m_tableCount].count = local_f8._4_4_;
          piVar3 = (int32_t *)
                   __nwa__FUlPQ27CMemory6CStagePci
                             (local_f8._4_4_ << 2,Game.game.m_mainStage,s_cflat_data_cpp_801d9e00,
                              0x65);
          cflatData->m_table[cflatData->m_tableCount].index = piVar3;
          pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                     (local_f8._12_4_,Game.game.m_mainStage,
                                      s_cflat_data_cpp_801d9e00,0x66);
          cflatData->m_table[cflatData->m_tableCount].data = pvVar2;
          uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          memcpy(cflatData->m_table[cflatData->m_tableCount].data,uVar5,local_f8._12_4_);
          iVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          iVar7 = 0;
          iVar8 = 0;
          while( true ) {
            iVar1 = cflatData->m_tableCount;
            if (cflatData->m_table[iVar1].count <= iVar7) break;
            iVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
            *(int *)((int)cflatData->m_table[iVar1].index + iVar8) =
                 (int)cflatData->m_table[iVar1].data + (iVar6 - iVar10);
            GetString__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
            iVar8 = iVar8 + 4;
            iVar7 = iVar7 + 1;
          }
          cflatData->m_tableCount = iVar1 + 1;
        }
      }
      PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
    }
  }
  return;
}

