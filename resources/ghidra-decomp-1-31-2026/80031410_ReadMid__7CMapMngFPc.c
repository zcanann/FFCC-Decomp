// Function: ReadMid__7CMapMngFPc
// Entry: 80031410
// Size: 1500 bytes

undefined4 ReadMid__7CMapMngFPc(CMapMng *mapMng,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  CFileCHandle *fileHandle;
  undefined4 uVar3;
  float **ppfVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  CMapMng *pCVar8;
  CMapObj *pCVar9;
  CMapObj *pCVar10;
  undefined local_f8 [212];
  
  sprintf(StrTmp,&DAT_8032f9c0,param_2);
  bVar2 = true;
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadMid_fn__s_801d7400,StrTmp);
  }
  pvVar6 = File.m_readBuffer;
  if (*(int *)&mapMng->field_0x229a8 == 1) {
    iVar7 = *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4);
    CopyFromAMemorySync__7CMemoryFPvPvUl
              (&Memory,File.m_readBuffer,*(undefined4 *)&mapMng->field_0x22998,
               iVar7 + 0x1fU & 0xffffffe0);
    *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar7;
    CheckSum__FPvi(pvVar6,iVar7);
    *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
  }
  else {
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,StrTmp,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      pvVar6 = (void *)0x0;
    }
    else {
      iVar7 = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      if (*(int *)&mapMng->field_0x229a8 == 3) {
        ReadASync__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        pvVar6 = (void *)0x1;
        *(CFileCHandle **)(&mapMng->field_0x22a2c + *(int *)&mapMng->field_0x229a4 * 4) = fileHandle
        ;
        *(int *)&mapMng->field_0x229a4 = *(int *)&mapMng->field_0x229a4 + 1;
      }
      else {
        Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        pvVar6 = File.m_readBuffer;
        Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        if (*(int *)&mapMng->field_0x229a8 == 2) {
          CopyToAMemorySync__7CMemoryFPvPvUl
                    (&Memory,pvVar6,*(undefined4 *)&mapMng->field_0x22998,iVar7);
          *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4) = iVar7;
          uVar3 = CheckSum__FPvi(pvVar6,iVar7);
          *(undefined4 *)(&mapMng->field_0x229ec + *(int *)&mapMng->field_0x229a0 * 4) = uVar3;
          *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
          *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar7;
        }
      }
    }
  }
  if (pvVar6 == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d7410,StrTmp);
    }
    uVar3 = 0;
  }
  else if (*(int *)&mapMng->field_0x229a8 == 2) {
    uVar3 = 1;
  }
  else if (*(int *)&mapMng->field_0x229a8 == 3) {
    uVar3 = 1;
  }
  else {
    __ct__10CChunkFileFv(local_f8 + 0x10);
    SetBuf__10CChunkFileFPv((CChunkFile *)(local_f8 + 0x10),pvVar6);
    pCVar10 = mapMng->mapObjArr;
    while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8), iVar7 != 0) {
      if (local_f8._0_4_ == 0x4d494420) {
        PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
        while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8),
              iVar7 != 0) {
          if (local_f8._0_4_ == 0x5343454e) {
            PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
            while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8),
                  iVar7 != 0) {
              if (local_f8._0_4_ == 0x48495420) {
                if (0x1f < mapMng->field9_0xa) {
                  return 0;
                }
                ReadOtmHit__7CMapHitFR10CChunkFile
                          (mapMng->mapHits + mapMng->field9_0xa,local_f8 + 0x10);
                mapMng->field9_0xa = mapMng->field9_0xa + 1;
              }
            }
            PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          }
          else {
            if ((0x5343454d < (int)local_f8._0_4_) || (local_f8._0_4_ != 0x4f43544d)) break;
            do {
              pCVar9 = pCVar10;
              if ((pCVar9->field_0x1e == '\x01') || (pCVar9->field_0x1e == '\x02')) {
                if (0xf < mapMng->field8_0x8) {
                  return 0;
                }
                ReadOtmOctTree__8COctTreeFR10CChunkFile
                          (mapMng->octTreeArr + mapMng->field8_0x8,local_f8 + 0x10);
                mapMng->octTreeArr[mapMng->field8_0x8].field2_0x8 = pCVar9;
                pvVar6 = mapMng->octTreeArr[mapMng->field8_0x8].field2_0x8;
                if (*(int *)((int)pvVar6 + 0xc) == 0) {
                  if (System.m_execParam != 0) {
                    Printf__7CSystemFPce(&System,s_Error_CMapMng__ReadMid_m_mapobj__801d7468);
                  }
                }
                else {
                  cVar1 = *(char *)((int)pvVar6 + 0x1e);
                  if ((cVar1 == '\x01') || (cVar1 == '\x02')) goto LAB_8003188c;
                }
                goto LAB_8003184c;
              }
              iVar7 = ((int)(pCVar9 + 0x8861bb) + 0xe8) / 0xf0 +
                      ((int)(pCVar9 + 0x8861bb) + 0xe8 >> 0x1f);
              pCVar10 = pCVar9 + 1;
            } while (iVar7 - (iVar7 >> 0x1f) < (int)mapMng->field10_0xc);
            if (System.m_execParam != 0) {
              Printf__7CSystemFPce(&System,&DAT_801d7428);
            }
LAB_8003184c:
            if (System.m_execParam != 0) {
              Printf__7CSystemFPce(&System,&DAT_801d7498);
            }
            bVar2 = false;
LAB_8003188c:
            pCVar10 = pCVar9 + 1;
            mapMng->field8_0x8 = mapMng->field8_0x8 + 1;
          }
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
      }
    }
    pCVar8 = &MapMng;
    for (iVar7 = 0; iVar7 < mapMng->field10_0xc; iVar7 = iVar7 + 1) {
      cVar1 = pCVar8->mapObjArr[0].field_0x1d;
      if (((cVar1 == '\x02') || (cVar1 == '\x03')) &&
         (ppfVar4 = &pCVar8->mapObjArr[0].field12_0xc[0x38d3653].m_vertices,
         iVar5 = (int)ppfVar4 / 0x24 + ((int)ppfVar4 >> 0x1f),
         (int)mapMng->field9_0xa <= iVar5 - (iVar5 >> 0x1f))) {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,&DAT_801d750c);
        }
        pCVar8->mapObjArr[0].field12_0xc = (CMapHit *)0x0;
      }
      pCVar8 = (CMapMng *)&pCVar8->octTreeArr[2].field51_0x3c.z;
    }
    if (bVar2) {
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,s_ReadMid_OK_801d7550);
      }
    }
    else if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_ReadMid_Error_801d755c);
    }
    pCVar8 = mapMng;
    for (iVar7 = 0; iVar7 < mapMng->field8_0x8; iVar7 = iVar7 + 1) {
      pvVar6 = pCVar8->octTreeArr[0].field2_0x8;
      if (pvVar6 != (void *)0x0) {
        *(char *)((int)pvVar6 + 0x1f) = (char)iVar7;
      }
      pCVar8 = (CMapMng *)&pCVar8->octTreeArr[0].field_0x38;
    }
    uVar3 = 1;
  }
  return uVar3;
}

