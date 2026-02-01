// Function: Create__12CFlatRuntimeFPv
// Entry: 80068df8
// Size: 2052 bytes

void Create__12CFlatRuntimeFPv(CFlatRuntime *flatRuntime,void *param_2)

{
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  undefined uVar11;
  undefined2 uVar8;
  uint16_t *puVar5;
  char *pcVar6;
  short sVar9;
  short sVar10;
  int iVar7;
  int *piVar12;
  int *piVar13;
  undefined *puVar14;
  int iVar15;
  undefined local_108 [220];
  
  (**(code **)((int)flatRuntime->vtable + 0x10))();
  __ct__10CChunkFileFPv((CChunkFile *)(local_108 + 0x10),param_2);
  while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108), iVar7 != 0) {
    if (local_108._0_4_ == 0x43464c54) {
      PushChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
      while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
            iVar7 != 0) {
        if (local_108._0_4_ == 0x4e414d45) {
          uVar1 = GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
          strcpy(flatRuntime->m_name,uVar1);
        }
        else if ((int)local_108._0_4_ < 0x4e414d45) {
          if (local_108._0_4_ == 0x46535452) {
            flatRuntime->m_fstrCount = local_108._4_4_;
            uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
            puVar5 = (uint16_t *)
                     __nwa__FUlPQ27CMemory6CStagePci
                               (flatRuntime->m_fstrCount << 1,uVar1,s_cflat_runtime_cpp_801d8ef8,
                                0x12f);
            flatRuntime->m_fstrOffs = puVar5;
            uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
            pcVar6 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                       (local_108._12_4_,uVar1,s_cflat_runtime_cpp_801d8ef8,0x130);
            flatRuntime->m_fstrBlob = pcVar6;
            uVar1 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            memcpy(flatRuntime->m_fstrBlob,uVar1,local_108._12_4_);
            sVar9 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            iVar15 = 0;
            for (iVar7 = 0; iVar7 < flatRuntime->m_fstrCount; iVar7 = iVar7 + 1) {
              sVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
              *(short *)((int)flatRuntime->m_fstrOffs + iVar15) = sVar10 - sVar9;
              GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
              iVar15 = iVar15 + 2;
            }
          }
          else if ((int)local_108._0_4_ < 0x46535452) {
            if (local_108._0_4_ == 0x434c4153) {
              flatRuntime->m_classCount = local_108._4_4_;
              iVar7 = flatRuntime->m_classCount;
              uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
              uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                                (iVar7 * 0x22c + 0x10,uVar1,s_cflat_runtime_cpp_801d8ef8,0x9e);
              pvVar2 = (void *)__construct_new_array
                                         (uVar1,__ct__Q212CFlatRuntime6CClassFv,0,0x22c,iVar7);
              flatRuntime->m_classesPtr = pvVar2;
              iVar7 = 0;
              PushChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
              iVar15 = 0;
              while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                       ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
                    iVar4 != 0) {
                piVar13 = (int *)((int)flatRuntime->m_classesPtr + iVar15);
                *piVar13 = iVar7;
                if (local_108._0_4_ == 0x424c434b) {
                  PushChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                  while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                           ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108
                                           ), iVar4 != 0) {
                    if (local_108._0_4_ == 0x56414c20) {
                      piVar13[0x89] = local_108._4_4_;
                    }
                    else if ((int)local_108._0_4_ < 0x56414c20) {
                      if (local_108._0_4_ == 0x4e414d45) {
                        uVar1 = GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                        strcpy(piVar13 + 1,uVar1);
                      }
                      else if (((int)local_108._0_4_ < 0x4e414d45) &&
                              (local_108._0_4_ == 0x494e464f)) {
                        iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                        piVar13[0x8a] = iVar4;
                      }
                    }
                    else if (local_108._0_4_ == 0x5654424c) {
                      iVar4 = 0;
                      piVar12 = piVar13;
                      do {
                        iVar3 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                        iVar4 = iVar4 + 1;
                        piVar12[9] = iVar3;
                        piVar12 = piVar12 + 1;
                      } while (iVar4 < 0x80);
                    }
                  }
                  PopChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                  iVar15 = iVar15 + 0x22c;
                  iVar7 = iVar7 + 1;
                }
              }
              PopChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            }
          }
          else if (local_108._0_4_ == 0x46554e43) {
            flatRuntime->m_funcCount = local_108._4_4_;
            uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
            pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                       (flatRuntime->m_funcCount * 0x50,uVar1,
                                        s_cflat_runtime_cpp_801d8ef8,0xd9);
            flatRuntime->m_funcsPtr = pvVar2;
            iVar7 = 0;
            PushChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            iVar15 = 0;
            while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
                  iVar4 != 0) {
              piVar13 = (int *)((int)flatRuntime->m_funcsPtr + iVar15);
              *piVar13 = iVar7;
              if (local_108._0_4_ == 0x424c434b) {
                PushChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                         ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
                      iVar4 != 0) {
                  if (local_108._0_4_ == 0x4e414d45) {
                    uVar1 = GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                    strcpy(piVar13 + 1,uVar1);
                  }
                  else if ((int)local_108._0_4_ < 0x4e414d45) {
                    if (local_108._0_4_ == 0x494e464f) {
                      iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                      piVar13[9] = iVar4;
                      iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                      piVar13[0x10] = iVar4;
                      iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                      piVar13[0x11] = iVar4;
                      iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                      piVar13[0x12] = iVar4;
                      iVar4 = Get4__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                      piVar13[0x13] = iVar4;
                    }
                    else if (((int)local_108._0_4_ < 0x494e464f) && (local_108._0_4_ == 0x434f4445))
                    {
                      piVar13[0xc] = local_108._12_4_;
                      piVar13[0xf] = 0;
                      piVar13[0xe] = 0;
                      if (piVar13[0xc] == 0) {
                        piVar13[0xd] = 0;
                      }
                      else {
                        uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
                        iVar4 = __nwa__FUlPQ27CMemory6CStagePci
                                          (local_108._12_4_,uVar1,s_cflat_runtime_cpp_801d8ef8,0x109
                                          );
                        piVar13[0xd] = iVar4;
                        uVar1 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                        memcpy((void *)piVar13[0xd],uVar1,local_108._12_4_);
                      }
                    }
                  }
                  else if (local_108._0_4_ == 0x56414c20) {
                    piVar13[10] = local_108._4_4_;
                  }
                  else if (((int)local_108._0_4_ < 0x56414c20) && (local_108._0_4_ == 0x52455420)) {
                    uVar11 = Get1__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                    *(undefined *)(piVar13 + 0xb) = uVar11;
                    uVar11 = Get1__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                    *(undefined *)((int)piVar13 + 0x2d) = uVar11;
                    uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                    *(undefined2 *)((int)piVar13 + 0x2e) = uVar8;
                  }
                }
                PopChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
                iVar15 = iVar15 + 0x50;
                iVar7 = iVar7 + 1;
              }
            }
            PopChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
          }
        }
        else if (local_108._0_4_ == 0x56414c20) {
          flatRuntime->m_variableCount = local_108._4_4_;
          uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
          pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                     (flatRuntime->m_variableCount << 2,uVar1,
                                      s_cflat_runtime_cpp_801d8ef8,0x96);
          flatRuntime->m_variableDefs = pvVar2;
          puVar14 = (undefined *)flatRuntime->m_variableDefs;
          iVar15 = flatRuntime->m_variableCount;
          for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
            uVar11 = Get1__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            *puVar14 = uVar11;
            uVar11 = Get1__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            puVar14[1] = uVar11;
            uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            *(undefined2 *)(puVar14 + 2) = uVar8;
            puVar14 = puVar14 + 4;
          }
        }
        else if ((int)local_108._0_4_ < 0x56414c20) {
          if (local_108._0_4_ == 0x53545220) {
            flatRuntime->m_strCount = local_108._4_4_;
            uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
            puVar5 = (uint16_t *)
                     __nwa__FUlPQ27CMemory6CStagePci
                               (flatRuntime->m_strCount << 1,uVar1,s_cflat_runtime_cpp_801d8ef8,
                                0x121);
            flatRuntime->m_strOffs = puVar5;
            uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
            pcVar6 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                       (local_108._12_4_,uVar1,s_cflat_runtime_cpp_801d8ef8,0x122);
            flatRuntime->m_strBlob = pcVar6;
            uVar1 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            memcpy(flatRuntime->m_strBlob,uVar1,local_108._12_4_);
            sVar9 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            iVar15 = 0;
            for (iVar7 = 0; iVar7 < flatRuntime->m_strCount; iVar7 = iVar7 + 1) {
              sVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
              *(short *)((int)flatRuntime->m_strOffs + iVar15) = sVar10 - sVar9;
              GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
              iVar15 = iVar15 + 2;
            }
          }
        }
        else if (local_108._0_4_ == 0x56535452) {
          flatRuntime->m_vstrCount = local_108._4_4_;
          uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
          puVar5 = (uint16_t *)
                   __nwa__FUlPQ27CMemory6CStagePci
                             (flatRuntime->m_vstrCount << 1,uVar1,s_cflat_runtime_cpp_801d8ef8,0x13d
                             );
          flatRuntime->m_vstrOffs = puVar5;
          uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
          pcVar6 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                     (local_108._12_4_,uVar1,s_cflat_runtime_cpp_801d8ef8,0x13e);
          flatRuntime->m_vstrBlob = pcVar6;
          uVar1 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
          memcpy(flatRuntime->m_vstrBlob,uVar1,local_108._12_4_);
          sVar9 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
          iVar15 = 0;
          for (iVar7 = 0; iVar7 < flatRuntime->m_vstrCount; iVar7 = iVar7 + 1) {
            sVar10 = GetAddress__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            *(short *)((int)flatRuntime->m_vstrOffs + iVar15) = sVar10 - sVar9;
            GetString__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
            iVar15 = iVar15 + 2;
          }
        }
      }
      PopChunk__10CChunkFileFv((CChunkFile *)(local_108 + 0x10));
    }
  }
  createObject__12CFlatRuntimeFi(flatRuntime,0xffffffff);
  flatRuntime->m_isCreated = 1;
  flatRuntime->m_unk0x974 = 1;
  return;
}

