// Function: pppPartInit__8CPartMngFv
// Entry: 80059a28
// Size: 540 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void * pppPartInit__8CPartMngFv
                 (CPartMng *partMng,undefined4 param_2,uint32_t *param_3,void *param_4,
                 uint32_t param_5)

{
  uint32_t uVar1;
  CFileCHandle *unaff_r31;
  
  if (partMng->m_partLoadMode == 1) {
    *param_3 = partMng->m_partChunkSize[partMng->m_partChunkIndex];
    param_4 = File.m_readBuffer;
    if (*param_3 == 0) {
      param_4 = (void *)0x0;
    }
    else {
      CopyFromAMemorySync__7CMemoryFPvPvUl
                (&Memory,File.m_readBuffer,partMng->m_partAMemCursor,*param_3 + 0x1f & 0xffffffe0);
      partMng->m_partAMemCursor = partMng->m_partAMemCursor + *param_3;
      CheckSum__FPvi(param_4,*param_3);
      partMng->m_partChunkIndex = partMng->m_partChunkIndex + 1;
    }
  }
  else if ((param_4 == (void *)0x0) &&
          (unaff_r31 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_2,0,0),
          unaff_r31 == (CFileCHandle *)0x0)) {
    param_4 = (void *)0x0;
  }
  else if (partMng->m_partLoadMode == 3) {
    ReadASync__5CFileFPQ25CFile7CHandle(&File,unaff_r31);
    param_4 = (void *)0x1;
    partMng->m_partAsyncBusy[partMng->m_asyncHandleCount] = (uint32_t)unaff_r31;
    partMng->m_asyncHandleCount = partMng->m_asyncHandleCount + 1;
  }
  else {
    if (param_4 == (void *)0x0) {
      uVar1 = GetLength__5CFileFPQ25CFile7CHandle(&File,unaff_r31);
      *param_3 = uVar1;
      Read__5CFileFPQ25CFile7CHandle(&File,unaff_r31);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,unaff_r31);
      param_4 = File.m_readBuffer;
      Close__5CFileFPQ25CFile7CHandle(&File,unaff_r31);
    }
    else {
      *param_3 = param_5;
    }
    if (partMng->m_partLoadMode == 2) {
      CopyToAMemorySync__7CMemoryFPvPvUl(&Memory,param_4,partMng->m_partAMemCursor,*param_3);
      partMng->m_partChunkSize[partMng->m_partChunkIndex] = *param_3;
      uVar1 = CheckSum__FPvi(param_4,*param_3);
      partMng->m_partChunkChecksum[partMng->m_partChunkIndex] = uVar1;
      partMng->m_partChunkIndex = partMng->m_partChunkIndex + 1;
      partMng->m_partAMemCursor = partMng->m_partAMemCursor + *param_3;
    }
  }
  return param_4;
}

