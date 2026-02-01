// Function: LoadMergeFile__9CCharaPcsFiii
// Entry: 800778dc
// Size: 2804 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadMergeFile__9CCharaPcsFiii(int param_1,void *param_2,int param_3,int param_4)

{
  bool bVar1;
  undefined4 uVar2;
  CPtrArray *ptrArray;
  CPtrArray *ptrArray_00;
  CPtrArray *ptrArray_01;
  uint uVar3;
  CRef *pCVar4;
  undefined4 uVar5;
  CModel *model;
  undefined4 uVar6;
  CTextureSet *textureSet;
  int iVar7;
  void *pvVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  CStage *pCVar12;
  uint uVar13;
  void *pvVar14;
  int iVar15;
  void *pvVar16;
  undefined local_274 [204];
  undefined auStack_1a8 [256];
  undefined4 local_a8;
  int local_a4;
  CFileCHandle *local_a0;
  int local_9c;
  int local_98;
  CPtrArray *local_94;
  CPtrArray *local_90;
  CPtrArray *local_8c;
  _pppEnvSt *local_88;
  CStage **local_84;
  int *local_80;
  undefined4 *local_7c;
  CPtrArray *local_78;
  CPtrArray *local_74;
  CFile *local_70;
  CFile *local_6c;
  CFile *local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  CFile *local_58;
  
  for (uVar13 = 0;
      uVar3 = GetSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)(param_1 + 0x50)),
      uVar13 < uVar3; uVar13 = uVar13 + 1) {
    iVar11 = __vc__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl(param_1 + 0x50,uVar13);
    if (*(void **)(iVar11 + 0x10) == param_2) {
      bVar1 = true;
      goto LAB_800779f8;
    }
  }
  for (uVar13 = 0;
      uVar3 = GetSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv((CPtrArray *)(param_1 + 0x88)),
      uVar13 < uVar3; uVar13 = uVar13 + 1) {
    iVar11 = __vc__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(param_1 + 0x88,uVar13);
    if (*(void **)(iVar11 + 0x10) == param_2) {
      bVar1 = true;
      goto LAB_800779f8;
    }
  }
  for (uVar13 = 0;
      uVar3 = GetSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)(param_1 + 0xa4)),
      uVar13 < uVar3; uVar13 = uVar13 + 1) {
    iVar11 = __vc__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(param_1 + 0xa4,uVar13);
    if (*(void **)(iVar11 + 0x18) == param_2) {
      bVar1 = true;
      goto LAB_800779f8;
    }
  }
  for (uVar13 = 0;
      uVar3 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c)),
      uVar13 < uVar3; uVar13 = uVar13 + 1) {
    iVar11 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,uVar13);
    if (*(void **)(iVar11 + 0x10) == param_2) {
      bVar1 = true;
      goto LAB_800779f8;
    }
  }
  bVar1 = false;
LAB_800779f8:
  if (bVar1) {
    Printf__7CSystemFPce(&System,&DAT_801d94f0,param_2);
  }
  else {
    local_70 = &File;
    local_78 = (CPtrArray *)&CharaPcs.field_0x50;
    local_8c = (CPtrArray *)&CharaPcs.field_0x88;
    local_90 = (CPtrArray *)&CharaPcs.field_0x6c;
    local_94 = (CPtrArray *)&CharaPcs.loadPdtArray;
    local_6c = &File;
    local_68 = &File;
    local_58 = &File;
    local_7c = (undefined4 *)&CharaPcs.field_0xcc;
    local_80 = (int *)&CharaPcs.field_0xe4;
    local_84 = &PartPcs.m_usbStreamData.m_stageLoad;
    local_64 = 0x4d524720;
    local_88 = &PartMng.m_pppEnvSt;
    local_98 = 1;
    for (local_9c = 0; local_9c < local_98; local_9c = local_9c + 1) {
      sprintf(auStack_1a8,s_dvd_mrg_m_04d__02d_mrg_801d9530,param_2,local_9c);
      local_a0 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(local_70,auStack_1a8,0,0);
      if (local_a0 == (CFileCHandle *)0x0) {
        Printf__7CSystemFPce(&System,&DAT_801d9548,param_2);
        break;
      }
      Read__5CFileFPQ25CFile7CHandle(local_6c,local_a0);
      SyncCompleted__5CFileFPQ25CFile7CHandle(local_68,local_a0);
      __ct__10CChunkFileFPv((CChunkFile *)(local_274 + 0x10),local_70->m_readBuffer);
      while (iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                ((CChunkFile *)(local_274 + 0x10),(CChunkFile *)local_274),
            iVar11 != 0) {
        if (local_274._0_4_ == local_64) {
          PushChunk__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
          local_60 = 0x494e464f;
          while (iVar11 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                    ((CChunkFile *)(local_274 + 0x10),(CChunkFile *)local_274),
                iVar11 != 0) {
            if (local_274._0_4_ == local_60) {
              local_98 = Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
            }
            else if (((int)local_274._0_4_ < (int)local_60) && (local_274._0_4_ == 0x44415441)) {
              local_a4 = 0;
              iVar11 = -1;
              pvVar16 = (void *)0xffffffff;
              local_a8 = 0;
              iVar15 = -1;
              pvVar14 = (void *)0xffffffff;
              PushChunk__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
              ptrArray_01 = local_8c;
              ptrArray_00 = local_90;
              ptrArray = local_94;
              local_74 = local_78;
              local_5c = 0x4e414d45;
              while (iVar10 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                        ((CChunkFile *)(local_274 + 0x10),(CChunkFile *)local_274),
                    iVar10 != 0) {
                if (local_274._0_4_ == local_5c) {
                  local_a8 = GetString__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                }
                else if ((int)local_274._0_4_ < (int)local_5c) {
                  if (local_274._0_4_ == 0x494e464f) {
                    iVar11 = Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    pvVar16 = (void *)Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    iVar15 = Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    pvVar14 = (void *)Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    local_a4 = Get4__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                  }
                }
                else if (local_274._0_4_ == 0x52415720) {
                  if (iVar11 == 3) {
                    uVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    LoadSe__6CSoundFPv(&Sound,uVar6);
                  }
                  else if (iVar11 < 3) {
                    if (iVar11 == 1) {
                      for (uVar13 = 0;
                          uVar3 = GetSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv(ptrArray_01),
                          uVar13 < uVar3; uVar13 = uVar13 + 1) {
                        iVar10 = __vc__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl
                                           (ptrArray_01,uVar13);
                        if (((*(void **)(iVar10 + 8) == pvVar16) &&
                            (*(int *)(iVar10 + 0xc) == iVar15)) &&
                           (*(void **)(iVar10 + 0x18) == pvVar14)) goto LAB_80077f34;
                      }
                      iVar10 = 0;
LAB_80077f34:
                      uVar6 = local_274._12_4_;
                      if (iVar10 == 0) {
                        uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                        pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                                   (0x2c,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,
                                                    0x609);
                        if (pCVar4 != (CRef *)0x0) {
                          __ct__4CRefFv(pCVar4);
                          pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadTexture_801fd290;
                          pCVar4[3].refCount = 0;
                          pCVar4[4].vtable = (void *)0x0;
                        }
                        pCVar4[1].vtable = pvVar16;
                        pCVar4[1].refCount = iVar15;
                        pCVar4[3].vtable = pvVar14;
                        pCVar4[2].vtable = param_2;
                        pCVar4[2].refCount = param_3;
                        Add__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ29CCharaPcs12CLoadTexture
                                  (ptrArray_01,pCVar4);
                        if (param_4 == 0) {
                          textureSet = (CTextureSet *)
                                       __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                                                 ((CTextureSet *)0x24,CharaPcs._192_4_,
                                                  s_p_chara_cpp_801d91bc,0x397);
                          if (textureSet != (CTextureSet *)0x0) {
                            textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
                          }
                          iVar10 = 1;
                          iVar7 = *local_80;
                          if (pvVar16 == (void *)0x4) {
                            iVar10 = 3;
                          }
                          if (iVar7 == 3) {
                            pCVar12 = local_88->m_stagePtr;
                          }
                          else if (iVar7 < 3) {
                            pCVar12 = (CStage *)MapMng._0_4_;
                            if ((iVar7 != 1) &&
                               (pCVar12 = *(CStage **)(&CharaPcs.field_0xcc + iVar10 * 4), 0 < iVar7
                               )) {
                              pCVar12 = *local_84;
                            }
                          }
                          else {
                            pCVar12 = *(CStage **)(&CharaPcs.field_0xcc + iVar10 * 4);
                            if (iVar7 < 5) {
                              pCVar12 = (CStage *)CharaPcs._212_4_;
                            }
                          }
                          Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                                    (textureSet,uVar5,pCVar12,0,0,0,0);
                          pCVar4[3].refCount = (int)textureSet;
                        }
                        else {
                          pCVar4[4].refCount = *(int *)(param_1 + 0x714);
                          pCVar4[5].vtable = (void *)uVar6;
                          pCVar4[4].vtable = (void *)0x1;
                          CopyToAMemorySync__7CMemoryFPvPvUl
                                    (&Memory,uVar5,
                                     *(int *)(param_1 + 0x714) +
                                     *(int *)(*(int *)(param_1 + 200) + 8),uVar6);
                          *(uint8_t **)(param_1 + 0x714) =
                               (uint8_t *)(uVar6 + *(int *)(param_1 + 0x714));
                        }
                      }
                    }
                    else if (iVar11 < 1) {
                      if (-1 < iVar11) {
                        for (uVar13 = 0;
                            uVar3 = GetSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv(local_74),
                            uVar13 < uVar3; uVar13 = uVar13 + 1) {
                          pCVar4 = (CRef *)__vc__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl
                                                     (local_74,uVar13);
                          if ((pCVar4[1].vtable == pvVar16) && (pCVar4[1].refCount == iVar15))
                          goto LAB_80077cf0;
                        }
                        pCVar4 = (CRef *)0x0;
LAB_80077cf0:
                        uVar6 = local_274._12_4_;
                        if (pCVar4 == (CRef *)0x0) {
                          uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                          pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                                     (0x28,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,
                                                      0x5e8);
                          if (pCVar4 != (CRef *)0x0) {
                            __ct__4CRefFv(pCVar4);
                            pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadModel_801fd2c0;
                            pCVar4[3].vtable = (void *)0x0;
                            pCVar4[3].refCount = 0;
                          }
                          pCVar4[1].vtable = pvVar16;
                          pCVar4[1].refCount = iVar15;
                          pCVar4[2].vtable = param_2;
                          pCVar4[2].refCount = param_3;
                          Add__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ29CCharaPcs10CLoadModel
                                    (local_74,pCVar4);
                          if (param_4 == 0) {
                            model = (CModel *)
                                    __nw__FUlPQ27CMemory6CStagePci
                                              (0x124,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x5f1);
                            if (model != (CModel *)0x0) {
                              model = (CModel *)__ct__Q26CChara6CModelFv(model);
                            }
                            iVar10 = *local_80;
                            if (iVar10 == 3) {
                              pCVar12 = local_88->m_stagePtr;
                            }
                            else if (iVar10 < 3) {
                              pCVar12 = (CStage *)MapMng._0_4_;
                              if ((iVar10 != 1) && (pCVar12 = (CStage *)*local_7c, 0 < iVar10)) {
                                pCVar12 = *local_84;
                              }
                            }
                            else {
                              pCVar12 = (CStage *)*local_7c;
                              if (iVar10 < 5) {
                                pCVar12 = (CStage *)CharaPcs._212_4_;
                              }
                            }
                            Create__Q26CChara6CModelFPvPQ27CMemory6CStage(model,uVar5,pCVar12);
                            pCVar4[3].vtable = model;
                          }
                          else {
                            pCVar4[4].vtable = *(void **)(param_1 + 0x714);
                            pCVar4[4].refCount = uVar6;
                            pCVar4[3].refCount = 1;
                            CopyToAMemorySync__7CMemoryFPvPvUl
                                      (&Memory,uVar5,
                                       *(int *)(param_1 + 0x714) +
                                       *(int *)(*(int *)(param_1 + 200) + 8),uVar6);
                            *(uint8_t **)(param_1 + 0x714) =
                                 (uint8_t *)(uVar6 + *(int *)(param_1 + 0x714));
                          }
                        }
                        if (local_a4 != 0) {
                          GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                    ((CChunkFile *)(local_274 + 0x10),(CChunkFile *)local_274);
                          iVar10 = *local_80;
                          if (iVar10 == 3) {
                            pCVar12 = local_88->m_stagePtr;
                          }
                          else if (iVar10 < 3) {
                            pCVar12 = (CStage *)MapMng._0_4_;
                            if ((iVar10 != 1) && (pCVar12 = (CStage *)*local_7c, 0 < iVar10)) {
                              pCVar12 = *local_84;
                            }
                          }
                          else {
                            pCVar12 = (CStage *)*local_7c;
                            if (iVar10 < 5) {
                              pCVar12 = (CStage *)CharaPcs._212_4_;
                            }
                          }
                          uVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                          CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
                                    ((CModel *)pCVar4[3].vtable,uVar6,pCVar12);
                        }
                      }
                    }
                    else {
                      for (uVar13 = 0;
                          uVar3 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv(ptrArray_00),
                          uVar13 < uVar3; uVar13 = uVar13 + 1) {
                        iVar10 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(ptrArray_00,uVar13);
                        if (((*(void **)(iVar10 + 8) == pvVar16) &&
                            (*(int *)(iVar10 + 0xc) == iVar15)) &&
                           (iVar7 = strcmp(local_a8,iVar10 + 0x18), iVar7 == 0)) goto LAB_8007811c;
                      }
                      iVar10 = 0;
LAB_8007811c:
                      if (iVar10 == 0) {
                        uVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                        pvVar8 = (void *)__nw__FUlPQ27CMemory6CStagePci
                                                   (0x30,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,
                                                    0x62a);
                        if (pvVar8 != (void *)0x0) {
                          pvVar8 = (void *)__ct__Q26CChara5CAnimFv();
                        }
                        Create__Q26CChara5CAnimFPvPQ27CMemory6CStage
                                  (pvVar8,uVar6,(CStage *)CharaPcs._212_4_);
                        pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                                   (0x74,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,
                                                    0x62d);
                        if (pCVar4 != (CRef *)0x0) {
                          __ct__4CRefFv(pCVar4);
                          pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadAnim_801fd2a8;
                          pCVar4[5].vtable = (void *)0x0;
                          *(undefined2 *)&pCVar4[5].refCount = 0;
                        }
                        pCVar4[1].refCount = iVar15;
                        pCVar4[1].vtable = pvVar16;
                        strcpy(pCVar4 + 3,local_a8);
                        pCVar4[5].vtable = pvVar8;
                        pCVar4[2].vtable = param_2;
                        pCVar4[2].refCount = param_3;
                        Add__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ29CCharaPcs9CLoadAnim
                                  (ptrArray_00,pCVar4);
                      }
                    }
                  }
                  else if (iVar11 == 5) {
                    for (uVar13 = 0;
                        uVar3 = GetSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv(ptrArray),
                        uVar13 < uVar3; uVar13 = uVar13 + 1) {
                      iVar10 = __vc__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(ptrArray,uVar13);
                      if (((*(void **)(iVar10 + 8) == pvVar16) && (*(int *)(iVar10 + 0xc) == iVar15)
                          ) && (*(void **)(iVar10 + 0x10) == pvVar14)) goto LAB_8007825c;
                    }
                    iVar10 = 0;
LAB_8007825c:
                    uVar5 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    uVar6 = local_274._12_4_;
                    if (iVar10 == 0) {
                      GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                ((CChunkFile *)(local_274 + 0x10),(CChunkFile *)local_274);
                      uVar9 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                      uVar2 = local_274._12_4_;
                      pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                                 (0x20,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x572
                                                 );
                      if (pCVar4 != (CRef *)0x0) {
                        __ct__4CRefFv(pCVar4);
                        pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadPdt_801fd278;
                        pCVar4[2].refCount = -1;
                      }
                      pCVar4[1].vtable = pvVar16;
                      pCVar4[1].refCount = iVar15;
                      pCVar4[2].vtable = pvVar14;
                      pCVar4[3].vtable = param_2;
                      pCVar4[3].refCount = param_3;
                      iVar10 = LoadMonsterPdt__8CPartPcsFiiPviPvi
                                         (&PartPcs,iVar15,pvVar14,uVar5,uVar6,uVar9,uVar2);
                      pCVar4[2].refCount = iVar10;
                      Add__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FPQ29CCharaPcs8CLoadPdt
                                (ptrArray,pCVar4);
                    }
                  }
                  else if (iVar11 < 5) {
                    uVar6 = GetAddress__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
                    LoadWave__6CSoundFPv(&Sound,uVar6);
                  }
                }
              }
              PopChunk__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
            }
          }
          PopChunk__10CChunkFileFv((CChunkFile *)(local_274 + 0x10));
        }
      }
      Close__5CFileFPQ25CFile7CHandle(local_58,local_a0);
    }
    Printf__7CSystemFPce(&System,s_CCharaPcs_LoadMergeFile___d_0x_0_801d9574,param_2,param_3);
  }
  return;
}

