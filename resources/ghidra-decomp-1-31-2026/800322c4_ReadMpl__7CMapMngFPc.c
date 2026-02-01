// Function: ReadMpl__7CMapMngFPc
// Entry: 800322c4
// Size: 1216 bytes

undefined4 ReadMpl__7CMapMngFPc(CMapMng *mapMng,undefined4 param_2)

{
  bool bVar1;
  CFileCHandle *pCVar2;
  undefined4 uVar3;
  void *buffer;
  int iVar4;
  int iVar5;
  undefined local_118 [20];
  uint8_t *local_104;
  CChunkFile aCStack_f8 [4];
  
  iVar5 = 0;
  MapMng._141707_1_ = 1;
  do {
    sprintf(StrTmp,s__s__d_mpl_801d759c,param_2,iVar5);
    if (*(int *)&mapMng->field_0x229a8 == 1) {
      bVar1 = true;
    }
    else {
      pCVar2 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,StrTmp,0,0);
      if (pCVar2 == (CFileCHandle *)0x0) {
        bVar1 = false;
      }
      else {
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        bVar1 = true;
      }
    }
    if (!bVar1) {
      if (*(int *)&mapMng->field_0x229a8 == 3) {
        return 1;
      }
      if (iVar5 == 0) {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,s_CAN_NOT_READ_OPEN__s________801d75a8,StrTmp);
        }
        return 0;
      }
      return 1;
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s_ReadMpl_fn__s_801d75c8,StrTmp);
    }
    buffer = File.m_readBuffer;
    if (*(int *)&mapMng->field_0x229a8 == 1) {
      iVar4 = *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4);
      CopyFromAMemorySync__7CMemoryFPvPvUl
                (&Memory,File.m_readBuffer,*(undefined4 *)&mapMng->field_0x22998,
                 iVar4 + 0x1fU & 0xffffffe0);
      *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar4;
      CheckSum__FPvi(buffer,iVar4);
      *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
    }
    else {
      pCVar2 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,StrTmp,0,0);
      if (pCVar2 == (CFileCHandle *)0x0) {
        buffer = (void *)0x0;
      }
      else {
        iVar4 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        if (*(int *)&mapMng->field_0x229a8 == 3) {
          ReadASync__5CFileFPQ25CFile7CHandle(&File,pCVar2);
          buffer = (void *)0x1;
          *(CFileCHandle **)(&mapMng->field_0x22a2c + *(int *)&mapMng->field_0x229a4 * 4) = pCVar2;
          *(int *)&mapMng->field_0x229a4 = *(int *)&mapMng->field_0x229a4 + 1;
        }
        else {
          Read__5CFileFPQ25CFile7CHandle(&File,pCVar2);
          SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar2);
          buffer = File.m_readBuffer;
          Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
          if (*(int *)&mapMng->field_0x229a8 == 2) {
            CopyToAMemorySync__7CMemoryFPvPvUl
                      (&Memory,buffer,*(undefined4 *)&mapMng->field_0x22998,iVar4);
            *(int *)(&mapMng->field_0x229ac + *(int *)&mapMng->field_0x229a0 * 4) = iVar4;
            uVar3 = CheckSum__FPvi(buffer,iVar4);
            *(undefined4 *)(&mapMng->field_0x229ec + *(int *)&mapMng->field_0x229a0 * 4) = uVar3;
            *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
            *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar4;
          }
        }
      }
    }
    if (buffer == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d7410,StrTmp);
      }
      return 0;
    }
    if (*(int *)&mapMng->field_0x229a8 != 3) {
      __ct__10CChunkFileFv(aCStack_f8);
      SetBuf__10CChunkFileFPv(aCStack_f8,buffer);
      if (*(int *)&mapMng->field_0x229a8 == 2) {
        while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_f8,(CChunkFile *)(local_118 + 0x10)), iVar4 != 0) {
          if (((uint8_t *)local_118._16_4_ == (uint8_t *)0x4d455348) &&
             (local_104 == (uint8_t *)0x1)) {
            return 1;
          }
        }
      }
      else {
        while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_f8,(CChunkFile *)(local_118 + 0x10)), iVar4 != 0) {
          if ((uint8_t *)local_118._16_4_ == (uint8_t *)0x4d455348) {
            PushChunk__10CChunkFileFv(aCStack_f8);
            while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     (aCStack_f8,(CChunkFile *)local_118), iVar4 != 0) {
              if (local_118._0_4_ == 0x56534554) {
                if (0x9f < *(short *)&mapMng->field_0xe) {
                  return 0;
                }
                ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
                          (mapMng->mapMeshArr + *(short *)&mapMng->field_0xe,aCStack_f8,
                           (CStage *)MapMng._0_4_,1,1);
              }
              else if (((int)local_118._0_4_ < 0x56534554) && (local_118._0_4_ == 0x44534554)) {
                ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
                          (mapMng->mapMeshArr + *(short *)&mapMng->field_0xe,aCStack_f8,
                           (CStage *)MapMng._0_4_,1,1);
                *(short *)&mapMng->field_0xe = *(short *)&mapMng->field_0xe + 1;
              }
            }
            PopChunk__10CChunkFileFv(aCStack_f8);
            if (local_104 == (uint8_t *)0x1) {
              return 1;
            }
          }
        }
      }
    }
    iVar5 = iVar5 + 1;
  } while( true );
}

