// Function: ReadOtm__7CMapMngFPc
// Entry: 800319ec
// Size: 2264 bytes

undefined4 ReadOtm__7CMapMngFPc(CMapMng *mapMng,undefined4 param_2)

{
  CFileCHandle *fileHandle;
  undefined4 uVar1;
  CMaterialSet *materialSet;
  CRef *ref;
  CMapAnim *mapAnim;
  undefined *item;
  undefined uVar4;
  CMapMng *pCVar2;
  CMapShadow *mapShadow;
  uint uVar3;
  void *pvVar5;
  CMapMng *pCVar6;
  CMapObj *pCVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  double dVar12;
  undefined local_258 [64];
  CChunkFile aCStack_218 [3];
  undefined4 local_15c;
  Vec local_158;
  Vec local_14c [2];
  undefined4 local_130;
  undefined4 local_12c;
  Vec VStack_124;
  undefined4 local_114;
  undefined local_108;
  undefined local_107;
  undefined local_106;
  undefined local_105;
  undefined4 local_f4;
  
  MapMng._141707_1_ = 1;
  sprintf(StrTmp,&DAT_8032f9c8,param_2);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadOtm_fn__s_801d756c,StrTmp);
  }
  *(undefined4 *)&mapMng->field_0x22a6c = 0;
  pvVar5 = File.m_readBuffer;
  if (*(int *)&mapMng->field_0x229a8 == 1) {
    iVar9 = *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4);
    CopyFromAMemorySync__7CMemoryFPvPvUl
              (&Memory,File.m_readBuffer,*(undefined4 *)&mapMng->field_0x22998,
               iVar9 + 0x1fU & 0xffffffe0);
    *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar9;
    CheckSum__FPvi(pvVar5,iVar9);
    *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
  }
  else {
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,StrTmp,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      pvVar5 = (void *)0x0;
    }
    else {
      iVar9 = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      if (*(int *)&mapMng->field_0x229a8 == 3) {
        ReadASync__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        pvVar5 = (void *)0x1;
        *(CFileCHandle **)(&mapMng->field_0x22a2c + *(int *)&mapMng->field_0x229a4 * 4) = fileHandle
        ;
        *(int *)&mapMng->field_0x229a4 = *(int *)&mapMng->field_0x229a4 + 1;
      }
      else {
        Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        pvVar5 = File.m_readBuffer;
        Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        if (*(int *)&mapMng->field_0x229a8 == 2) {
          CopyToAMemorySync__7CMemoryFPvPvUl
                    (&Memory,pvVar5,*(undefined4 *)&mapMng->field_0x22998,iVar9);
          *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4) = iVar9;
          uVar1 = CheckSum__FPvi(pvVar5,iVar9);
          *(undefined4 *)(&mapMng->field_0x229ec + *(int *)&mapMng->field_0x229a0 * 4) = uVar1;
          *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
          *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar9;
        }
      }
    }
  }
  if (pvVar5 == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d7410,StrTmp);
    }
    uVar1 = 0;
  }
  else if (*(int *)&mapMng->field_0x229a8 == 2) {
    uVar1 = 1;
  }
  else if (*(int *)&mapMng->field_0x229a8 == 3) {
    uVar1 = 1;
  }
  else {
    __ct__10CChunkFileFv(aCStack_218);
    SetBuf__10CChunkFileFPv(aCStack_218,pvVar5);
    while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_218,(CChunkFile *)local_258), iVar9 != 0) {
      if (local_258._0_4_ == 0x4f544d20) {
        PushChunk__10CChunkFileFv(aCStack_218);
        while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_218,(CChunkFile *)local_258), iVar9 != 0) {
          if (local_258._0_4_ == 0x4f43544d) {
            if (0xf < mapMng->field8_0x8) {
              return 0;
            }
            ReadOtmOctTree__8COctTreeFR10CChunkFile
                      (mapMng->octTreeArr + mapMng->field8_0x8,aCStack_218);
            mapMng->field8_0x8 = mapMng->field8_0x8 + 1;
          }
          else if ((int)local_258._0_4_ < 0x4f43544d) {
            if (local_258._0_4_ != 0x4c495448) break;
            item = (undefined *)
                   __nw__FUlPQ27CMemory6CStagePci(0x10,MapMng._0_4_,&DAT_8032f9d0,0x4d3);
            uVar4 = Get1__10CChunkFileFv(aCStack_218);
            *item = uVar4;
            uVar4 = Get1__10CChunkFileFv(aCStack_218);
            item[1] = uVar4;
            uVar4 = Get1__10CChunkFileFv(aCStack_218);
            item[2] = uVar4;
            uVar4 = Get1__10CChunkFileFv(aCStack_218);
            item[3] = uVar4;
            dVar12 = (double)GetF4__10CChunkFileFv(aCStack_218);
            *(float *)(item + 4) = (float)dVar12;
            dVar12 = (double)GetF4__10CChunkFileFv(aCStack_218);
            *(float *)(item + 8) = (float)dVar12;
            dVar12 = (double)GetF4__10CChunkFileFv(aCStack_218);
            *(float *)(item + 0xc) = (float)dVar12;
            Add__29CPtrArray<P15CMapLightHolder>FP15CMapLightHolder
                      (mapMng->mapLightHolderArr + local_258._4_4_,item);
          }
          else {
            if (local_258._0_4_ != 0x5343454e) break;
            PushChunk__10CChunkFileFv(aCStack_218);
            while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     (aCStack_218,(CChunkFile *)local_258), iVar9 != 0) {
              if (local_258._0_4_ == 0x4d455348) {
                if (0x9f < *(short *)&mapMng->field_0xe) {
                  return 0;
                }
                ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
                          (mapMng->mapMeshArr + *(short *)&mapMng->field_0xe,aCStack_218,
                           (CStage *)MapMng._0_4_,0,1);
                *(short *)&mapMng->field_0xe = *(short *)&mapMng->field_0xe + 1;
              }
              else if ((int)local_258._0_4_ < 0x4d455348) {
                if (local_258._0_4_ == 0x41534554) {
                  ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                          (0x114,MapMng._0_4_,&DAT_8032f9d0,0x49a);
                  if (ref != (CRef *)0x0) {
                    __ct__4CRefFv(ref);
                    ref->vtable = &PTR_PTR_s_CMapTexAnimSet_801e896c;
                    *(undefined2 *)&ref[1].vtable = 0;
                  }
                  *(CRef **)&mapMng->field_0x213dc = ref;
                  Create__14CMapTexAnimSetFR10CChunkFileP12CMaterialSetP11CTextureSet
                            (*(undefined4 *)&mapMng->field_0x213dc,aCStack_218,
                             *(CMaterialSet **)&mapMng->field_0x213d4,
                             *(CTextureSet **)&mapMng->field_0x213d8);
                }
                else if ((int)local_258._0_4_ < 0x41534554) {
                  if (local_258._0_4_ == 0x414e494d) {
                    mapAnim = (CMapAnim *)
                              __nw__FUlPQ27CMemory6CStagePci(0x24,MapMng._0_4_,&DAT_8032f9d0,0x4bf);
                    if (mapAnim != (CMapAnim *)0x0) {
                      mapAnim = (CMapAnim *)__ct__8CMapAnimFv(mapAnim);
                    }
                    ReadOtmAnim__8CMapAnimFR10CChunkFile(mapAnim,aCStack_218);
                    Add__21CPtrArray<P8CMapAnim>FP8CMapAnim(&mapMng->g_CMapAnimArray,mapAnim);
                  }
                }
                else if (local_258._0_4_ == 0x48495420) {
                  if (0x1f < mapMng->field9_0xa) {
                    return 0;
                  }
                  ReadOtmHit__7CMapHitFR10CChunkFile
                            (mapMng->mapHits + mapMng->field9_0xa,aCStack_218);
                  mapMng->field9_0xa = mapMng->field9_0xa + 1;
                }
              }
              else if (local_258._0_4_ == 0x4e4f4445) {
                if (0x1ff < mapMng->field10_0xc) {
                  return 0;
                }
                ReadOtmObj__7CMapObjFR10CChunkFile
                          (mapMng->mapObjArr + mapMng->field10_0xc,aCStack_218);
                mapMng->field10_0xc = mapMng->field10_0xc + 1;
              }
              else if (((int)local_258._0_4_ < 0x4e4f4445) && (local_258._0_4_ == 0x4d534554)) {
                materialSet = (CMaterialSet *)
                              __nw__12CMaterialSetFUlPQ27CMemory6CStagePci
                                        ((CMaterialSet *)0x24,MapMng._0_4_,&DAT_8032f9d0,0x482);
                if (materialSet != (CMaterialSet *)0x0) {
                  materialSet = (CMaterialSet *)__ct__12CMaterialSetFv(materialSet);
                }
                *(CMaterialSet **)&mapMng->field_0x213d4 = materialSet;
                iVar9 = *(int *)&mapMng->field_0x213d4;
                SetDefaultSize__22CPtrArray<P9CMaterial>FUl((CPtrArray *)(iVar9 + 8),0x180);
                SetGrow__22CPtrArray<P9CMaterial>Fi((CPtrArray *)(iVar9 + 8),0);
                Create__12CMaterialSetFR10CChunkFileP11CTextureSetQ212CMaterialMan7TEV_BITPQ29CLightPcs10CBumpLight
                          (*(undefined4 *)&mapMng->field_0x213d4,aCStack_218,
                           *(undefined4 *)&mapMng->field_0x213d8,0xfff53060,0);
              }
            }
            PopChunk__10CChunkFileFv(aCStack_218);
          }
        }
        PopChunk__10CChunkFileFv(aCStack_218);
      }
    }
    pCVar2 = mapMng;
    for (iVar9 = 0; iVar9 < mapMng->field8_0x8; iVar9 = iVar9 + 1) {
      pvVar5 = pCVar2->octTreeArr[0].field2_0x8;
      if (pvVar5 != (void *)0x0) {
        *(char *)((int)pvVar5 + 0x1f) = (char)iVar9;
      }
      pCVar2 = (CMapMng *)&pCVar2->octTreeArr[0].field_0x38;
    }
    for (uVar10 = 0; uVar3 = GetSize__24CPtrArray<P10CMapShadow>Fv(&mapMng->m_mapShadowArray),
        uVar10 < uVar3; uVar10 = uVar10 + 1) {
      mapShadow = (CMapShadow *)
                  __vc__24CPtrArray<P10CMapShadow>FUl(&mapMng->m_mapShadowArray,uVar10);
      Init__10CMapShadowFv(mapShadow);
    }
    pCVar7 = mapMng->mapObjArr;
    uVar10 = (uint)((int)(mapMng->mapObjArr + mapMng->field10_0xc) + (0xef - (int)pCVar7)) / 0xf0;
    if (pCVar7 < mapMng->mapObjArr + mapMng->field10_0xc) {
      do {
        if (*(int *)pCVar7 == 0) goto LAB_80032114;
        pCVar7 = pCVar7 + 1;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
    }
    pCVar7 = (CMapObj *)0x0;
LAB_80032114:
    *(CMapObj **)&mapMng->field_0x228e8 = pCVar7;
    if (*(int *)&mapMng->field_0x228e8 == 0) {
      Printf__7CSystemFPce(&System,s_Error_root_mapobj_not_found_801d757c);
      uVar1 = 0;
    }
    else {
      SetLink__7CMapObjFv();
      PSMTXIdentity((Mtx *)(local_258 + 0x10));
      CalcMtx__7CMapObjFPA4_fUc(*(CMapObj **)&mapMng->field_0x228e8,local_258 + 0x10,1);
      pCVar2 = mapMng;
      for (iVar9 = 0; iVar9 < mapMng->field10_0xc; iVar9 = iVar9 + 1) {
        iVar11 = *(int *)&pCVar2->mapObjArr[0].field_0xec;
        if (((iVar11 != 0) && (*(int *)(iVar11 + 4) == 1)) && (*(int *)(iVar11 + 0x34) != 0)) {
          __ct__Q29CLightPcs10CBumpLightFv(&local_15c);
          local_15c = 1;
          local_158.x = *(float *)&pCVar2->mapObjArr[0].field_0xc4;
          local_158.y = *(float *)&pCVar2->mapObjArr[0].field_0xd4;
          local_158.z = *(float *)&pCVar2->mapObjArr[0].field_0xe4;
          iVar8 = *(int *)(iVar11 + 0x10);
          local_14c[0].x = *(float *)(iVar8 + 0xc4);
          local_14c[0].y = *(float *)(iVar8 + 0xd4);
          local_14c[0].z = *(float *)(iVar8 + 0xe4);
          PSVECSubtract(local_14c,&local_158,&VStack_124);
          PSVECNormalize(&VStack_124,&VStack_124);
          local_f4 = *(undefined4 *)(iVar11 + 0x34);
          local_130 = *(undefined4 *)(iVar11 + 0x20);
          local_12c = *(undefined4 *)(iVar11 + 0x24);
          local_114 = *(undefined4 *)(iVar11 + 0x28);
          local_108 = *(undefined *)(iVar11 + 8);
          local_107 = *(undefined *)(iVar11 + 9);
          local_106 = *(undefined *)(iVar11 + 10);
          local_105 = *(undefined *)(iVar11 + 0xb);
          uVar1 = AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei
                            (&LightPcs,&local_15c,1,*(CStage **)mapMng,1);
          *(undefined4 *)(iVar11 + 0x38) = uVar1;
          pCVar6 = mapMng;
          for (iVar8 = 0; iVar8 < mapMng->field10_0xc; iVar8 = iVar8 + 1) {
            if (*(short *)&pCVar6->mapObjArr[0].field_0x16 == iVar9) {
              *(undefined4 *)&pCVar6->mapObjArr[0].field_0x10 = *(undefined4 *)(iVar11 + 0x38);
            }
            pCVar6 = (CMapMng *)&pCVar6->octTreeArr[2].field51_0x3c.z;
          }
        }
        pCVar2 = (CMapMng *)&pCVar2->octTreeArr[2].field51_0x3c.z;
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}

