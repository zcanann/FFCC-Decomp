// Function: ReadMtx__7CMapMngFPc
// Entry: 80032784
// Size: 1132 bytes

undefined4 ReadMtx__7CMapMngFPc(CMapMng *mapMng,undefined4 param_2)

{
  bool bVar1;
  CTextureSet *textureSet;
  CFileCHandle *pCVar2;
  undefined4 uVar3;
  void *buffer;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined local_108 [212];
  
  uVar6 = 0;
  MapMng._141707_1_ = 1;
  if ((*(int *)&mapMng->field_0x229a8 != 2) && (*(int *)&mapMng->field_0x229a8 != 3)) {
    textureSet = (CTextureSet *)
                 __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                           ((CTextureSet *)0x24,MapMng._0_4_,&DAT_8032f9d0,0x3a9);
    if (textureSet != (CTextureSet *)0x0) {
      textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
    }
    *(CTextureSet **)&mapMng->field_0x213d8 = textureSet;
  }
  iVar5 = 0;
  while( true ) {
    sprintf(StrTmp,s__s__d_mtx_801d75d8,param_2,iVar5);
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
    if (!bVar1) break;
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s_ReadMtx_fn__s_801d75e4,StrTmp);
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
      __ct__10CChunkFileFv(local_108 + 0x10);
      SetBuf__10CChunkFileFPv((CChunkFile *)(local_108 + 0x10),buffer);
      if (*(int *)&mapMng->field_0x229a8 == 2) {
        while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
              iVar4 != 0) {
          if ((local_108._0_4_ == 0x54534554) && (local_108._4_4_ == 1)) {
            return 1;
          }
        }
      }
      else {
        while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 ((CChunkFile *)(local_108 + 0x10),(CChunkFile *)local_108),
              iVar4 != 0) {
          if (local_108._0_4_ == 0x54534554) {
            Create__11CTextureSetFR10CChunkFilePQ27CMemory6CStageiP13CAmemCacheSetii
                      (*(CTextureSet **)&mapMng->field_0x213d8,local_108 + 0x10,
                       *(undefined4 *)mapMng,uVar6,0,0,0);
            uVar6 = 1;
            if (local_108._4_4_ == 1) {
              return 1;
            }
          }
        }
      }
    }
    iVar5 = iVar5 + 1;
  }
  if (*(int *)&mapMng->field_0x229a8 == 2) {
    return 1;
  }
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

