// Function: LoadCam__9CCharaPcsFiPc
// Entry: 800783d0
// Size: 488 bytes

void LoadCam__9CCharaPcsFiPc(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  void *ptr;
  CFileCHandle *fileHandle;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  undefined local_1e8 [204];
  undefined auStack_11c [260];
  
  iVar3 = param_1 + param_2 * 4;
  ptr = *(void **)(iVar3 + 0x14);
  if (ptr != (void *)0x0) {
    __dla__FPv(ptr);
    *(undefined4 *)(iVar3 + 0x14) = 0;
  }
  sprintf(auStack_11c,s_dvd_cft__s_cmd_801d9598,param_3);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_11c,0,0);
  if (fileHandle != (CFileCHandle *)0x0) {
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    __ct__10CChunkFileFPv((CChunkFile *)(local_1e8 + 0x10),File.m_readBuffer);
    param_1 = param_1 + param_2 * 4;
    while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             ((CChunkFile *)(local_1e8 + 0x10),(CChunkFile *)local_1e8), iVar3 != 0)
    {
      if (local_1e8._0_4_ == 0x43414d20) {
        *(undefined4 *)(param_1 + 4) = local_1e8._4_4_;
        uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                          (*(int *)(param_1 + 4) << 5,CharaPcs._212_4_,s_p_chara_cpp_801d91bc,0x4d4)
        ;
        *(undefined4 *)(param_1 + 0x14) = uVar2;
        iVar4 = 0;
        for (iVar3 = 0; iVar3 < *(int *)(param_1 + 4); iVar3 = iVar3 + 1) {
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 4) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 8) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 0xc) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 0x10) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 0x14) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          *(float *)(*(int *)(param_1 + 0x14) + iVar4 + 0x18) = (float)dVar5;
          dVar5 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_1e8 + 0x10));
          iVar1 = iVar4 + 0x1c;
          iVar4 = iVar4 + 0x20;
          *(float *)(*(int *)(param_1 + 0x14) + iVar1) = (float)dVar5;
        }
      }
    }
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  }
  return;
}

