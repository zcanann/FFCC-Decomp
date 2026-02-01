// Function: CreateDebug__12CFlatRuntimeFPvi
// Entry: 80068c04
// Size: 500 bytes

int CreateDebug__12CFlatRuntimeFPvi(CFlatRuntime *flatRuntime,void *param_2,int param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined local_f8 [208];
  
  __ct__10CChunkFileFPv((CChunkFile *)(local_f8 + 0x10),param_2);
  iVar6 = param_3 * 0x50;
  while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8), iVar5 != 0) {
    if (local_f8._0_4_ == 0x43464c54) {
      PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
      iVar5 = iVar6;
      while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8), iVar4 != 0)
      {
        if (((local_f8._0_4_ != 0x4e414d45) && ((int)local_f8._0_4_ < 0x4e414d45)) &&
           (local_f8._0_4_ == 0x46554e43)) {
          PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
          iVar4 = iVar5;
          while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8),
                iVar3 != 0) {
            pvVar1 = flatRuntime->m_funcsPtr;
            if (local_f8._0_4_ == 0x424c434b) {
              PushChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
              while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                       ((CChunkFile *)(local_f8 + 0x10),(CChunkFile *)local_f8),
                    iVar3 != 0) {
                if (((local_f8._0_4_ != 0x4e414d45) && ((int)local_f8._0_4_ < 0x4e414d45)) &&
                   (local_f8._0_4_ == 0x434f4445)) {
                  if (*(int *)((int)pvVar1 + iVar4 + 0x30) == 0) {
                    *(undefined4 *)((int)pvVar1 + iVar4 + 0x3c) = 0;
                    *(undefined4 *)((int)pvVar1 + iVar4 + 0x38) = 0;
                  }
                  else {
                    *(uint *)((int)pvVar1 + iVar4 + 0x38) = (uint)local_f8._12_4_ >> 3;
                    uVar2 = (**(code **)((int)flatRuntime->vtable + 0x48))(flatRuntime);
                    uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                                      (*(int *)((int)pvVar1 + iVar4 + 0x38) << 3,uVar2,
                                       s_cflat_runtime_cpp_801d8ef8,0x181);
                    *(undefined4 *)((int)pvVar1 + iVar4 + 0x3c) = uVar2;
                    uVar2 = GetAddress__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
                    memcpy(*(void **)((int)pvVar1 + iVar4 + 0x3c),uVar2,local_f8._12_4_);
                  }
                }
              }
              PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
              iVar4 = iVar4 + 0x50;
              iVar5 = iVar5 + 0x50;
              iVar6 = iVar6 + 0x50;
              param_3 = param_3 + 1;
            }
          }
          PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
        }
      }
      PopChunk__10CChunkFileFv((CChunkFile *)(local_f8 + 0x10));
    }
  }
  iVar6 = -1;
  if (param_3 < flatRuntime->m_funcCount) {
    iVar6 = param_3;
  }
  return iVar6;
}

