// Function: LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
// Entry: 80075920
// Size: 1300 bytes

undefined4
LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
          (CCharaPcsCHandle *handle,undefined4 param_2,int param_3,void *param_4,void *param_5,
          int param_6,void *param_7,int param_8)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  CRef *pCVar4;
  int *piVar5;
  CRef *pCVar6;
  uint uVar7;
  CFileCHandle *fileHandle;
  void *pvVar8;
  undefined4 uVar9;
  void *pvVar10;
  int iVar11;
  uint uVar12;
  CCharaPcsCHandle *pCVar13;
  int32_t iVar14;
  undefined auStack_148 [264];
  
  if (param_3 == -1) {
    iVar11 = 0;
    pCVar13 = handle;
    do {
      pCVar4 = pCVar13->m_animSlot[0];
      if ((pCVar4 != (CRef *)0x0) && (pCVar4 != (CRef *)0x0)) {
        iVar3 = pCVar4->refCount + -1;
        pCVar4->refCount = iVar3;
        if ((iVar3 == 0) && (pCVar4 != (CRef *)0x0)) {
          (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
        }
        pCVar13->m_animSlot[0] = (CRef *)0x0;
      }
      iVar11 = iVar11 + 1;
      pCVar13 = (CCharaPcsCHandle *)&pCVar13->m_charaNo;
    } while (iVar11 < 0x40);
    iVar11 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c);
    while (iVar11 = iVar11 + -1, -1 < iVar11) {
      piVar5 = (int *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,iVar11);
      if ((piVar5[4] < 0) && (piVar5[1] == 1)) {
        piVar5[1] = 0;
        if (piVar5 != (int *)0x0) {
          (**(code **)(*piVar5 + 8))(piVar5,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&CharaPcs.field_0x6c,iVar11);
      }
    }
  }
  else {
    pCVar4 = handle->m_animSlot[param_3];
    if (pCVar4 != (CRef *)0x0) {
      iVar11 = pCVar4->refCount + -1;
      pCVar4->refCount = iVar11;
      if ((iVar11 == 0) && (pCVar4 != (CRef *)0x0)) {
        (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
      }
      pCVar4 = handle->m_animSlot[param_3];
      iVar11 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c);
      do {
        do {
          iVar11 = iVar11 + -1;
          if (iVar11 < 0) goto LAB_80075b28;
          pCVar6 = (CRef *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,iVar11);
        } while (((-1 < (int)pCVar6[2].vtable) || (pCVar6->refCount != 1)) ||
                ((pCVar4 != (CRef *)0x0 && (pCVar4 != pCVar6))));
        iVar3 = pCVar6->refCount + -1;
        pCVar6->refCount = iVar3;
        if ((iVar3 == 0) && (pCVar6 != (CRef *)0x0)) {
          (**(code **)((int)pCVar6->vtable + 8))(pCVar6,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&CharaPcs.field_0x6c,iVar11);
      } while (pCVar4 == (CRef *)0x0);
LAB_80075b28:
      handle->m_animSlot[param_3] = (CRef *)0x0;
    }
  }
  pvVar10 = param_5;
  if (param_5 == (void *)0xffffffff) {
    pvVar10 = (void *)handle->m_charaKind;
  }
  iVar14 = param_6;
  if (param_6 == -1) {
    iVar14 = handle->m_charaNo;
  }
  for (uVar12 = 0;
      uVar7 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c),
      uVar12 < uVar7; uVar12 = uVar12 + 1) {
    iVar11 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,uVar12);
    if (((*(void **)(iVar11 + 8) == pvVar10) && (*(int *)(iVar11 + 0xc) == iVar14)) &&
       (iVar3 = strcmp(param_2,iVar11 + 0x18), iVar3 == 0)) goto LAB_80075bc4;
  }
  iVar11 = 0;
LAB_80075bc4:
  if (iVar11 == 0) {
    sprintf(auStack_148,s_dvd_char__s__s_03d__s_cha_801d9234,(&PTR_DAT_801fd224)[(int)pvVar10 * 3],
            (&PTR_DAT_801fd228)[(int)pvVar10 * 3],iVar14,param_2);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_148,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      bVar1 = false;
      goto LAB_80075d3c;
    }
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    pvVar2 = File.m_readBuffer;
    pvVar8 = (void *)__nw__FUlPQ27CMemory6CStagePci
                               (0x30,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x62a);
    if (pvVar8 != (void *)0x0) {
      pvVar8 = (void *)__ct__Q26CChara5CAnimFv();
    }
    Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(pvVar8,pvVar2,(CStage *)CharaPcs._212_4_);
    pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                               (0x74,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x62d);
    if (pCVar4 != (CRef *)0x0) {
      __ct__4CRefFv(pCVar4);
      pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadAnim_801fd2a8;
      pCVar4[5].vtable = (void *)0x0;
      *(undefined2 *)&pCVar4[5].refCount = 0;
    }
    pCVar4[1].refCount = iVar14;
    pCVar4[1].vtable = pvVar10;
    strcpy(pCVar4 + 3,param_2);
    pCVar4[5].vtable = pvVar8;
    pCVar4[2].vtable = param_7;
    pCVar4[2].refCount = param_8;
    Add__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ29CCharaPcs9CLoadAnim
              ((CPtrArray *)&CharaPcs.field_0x6c,pCVar4);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d9250,param_2,pvVar10,iVar14);
    }
  }
  bVar1 = true;
LAB_80075d3c:
  if (bVar1) {
    if (param_5 == (void *)0xffffffff) {
      param_5 = (void *)handle->m_charaKind;
    }
    if (param_6 == -1) {
      param_6 = handle->m_charaNo;
    }
    for (uVar12 = 0;
        uVar7 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c),
        uVar12 < uVar7; uVar12 = uVar12 + 1) {
      pCVar4 = (CRef *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,uVar12);
      if (((pCVar4[1].vtable == param_5) && (pCVar4[1].refCount == param_6)) &&
         (iVar11 = strcmp(param_2,pCVar4 + 3), iVar11 == 0)) goto LAB_80075dd4;
    }
    pCVar4 = (CRef *)0x0;
LAB_80075dd4:
    uVar9 = 1;
    handle->m_animSlot[param_3] = pCVar4;
    pCVar4->refCount = pCVar4->refCount + 1;
    handle->m_animSlot[param_3][0xe].vtable = param_4;
    pvVar10 = handle->m_animSlot[param_3][5].vtable;
    *(byte *)((int)pvVar10 + 8) = (byte)((int)param_4 << 7) | *(byte *)((int)pvVar10 + 8) & 0x7f;
    pvVar10 = handle->m_animSlot[param_3][5].vtable;
    *(byte *)((int)pvVar10 + 8) =
         (byte)((int)param_4 << 5) & 0x40 | *(byte *)((int)pvVar10 + 8) & 0xbf;
  }
  else {
    uVar9 = 0;
  }
  return uVar9;
}

