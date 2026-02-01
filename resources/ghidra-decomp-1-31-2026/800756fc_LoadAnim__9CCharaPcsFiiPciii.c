// Function: LoadAnim__9CCharaPcsFiiPciii
// Entry: 800756fc
// Size: 548 bytes

undefined4
LoadAnim__9CCharaPcsFiiPciii
          (undefined4 param_1,void *param_2,int param_3,undefined4 param_4,undefined4 param_5,
          void *param_6,int param_7)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  CFileCHandle *fileHandle;
  void *pvVar4;
  CRef *ref;
  int iVar5;
  uint uVar6;
  undefined auStack_138 [268];
  
  for (uVar6 = 0;
      uVar3 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c),
      uVar6 < uVar3; uVar6 = uVar6 + 1) {
    iVar5 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,uVar6);
    if (((*(void **)(iVar5 + 8) == param_2) && (*(int *)(iVar5 + 0xc) == param_3)) &&
       (iVar2 = strcmp(param_4,iVar5 + 0x18), iVar2 == 0)) goto LAB_80075794;
  }
  iVar5 = 0;
LAB_80075794:
  if (iVar5 == 0) {
    sprintf(auStack_138,s_dvd_char__s__s_03d__s_cha_801d9234,(&PTR_DAT_801fd224)[(int)param_2 * 3],
            (&PTR_DAT_801fd228)[(int)param_2 * 3],param_3,param_4);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_138,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      return 0;
    }
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    pvVar1 = File.m_readBuffer;
    pvVar4 = (void *)__nw__FUlPQ27CMemory6CStagePci
                               (0x30,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x62a);
    if (pvVar4 != (void *)0x0) {
      pvVar4 = (void *)__ct__Q26CChara5CAnimFv();
    }
    Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(pvVar4,pvVar1,(CStage *)CharaPcs._212_4_);
    ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x74,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x62d)
    ;
    if (ref != (CRef *)0x0) {
      __ct__4CRefFv(ref);
      ref->vtable = &PTR_PTR_s_CCharaPcs_CLoadAnim_801fd2a8;
      ref[5].vtable = (void *)0x0;
      *(undefined2 *)&ref[5].refCount = 0;
    }
    ref[1].refCount = param_3;
    ref[1].vtable = param_2;
    strcpy(ref + 3,param_4);
    ref[5].vtable = pvVar4;
    ref[2].vtable = param_6;
    ref[2].refCount = param_7;
    Add__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ29CCharaPcs9CLoadAnim
              ((CPtrArray *)&CharaPcs.field_0x6c,ref);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d9250,param_4,param_2,param_3);
    }
  }
  return 1;
}

