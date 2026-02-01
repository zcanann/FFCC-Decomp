// Function: ChangeTexture__Q29CCharaPcs7CHandleFiUlUlii
// Entry: 80076764
// Size: 1424 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChangeTexture__Q29CCharaPcs7CHandleFiUlUlii
               (CCharaPcsCHandle *handle,void *param_2,int param_3,void *param_4,void *param_5,
               int param_6)

{
  void *pvVar1;
  int iVar2;
  CTextureSet *pCVar3;
  CRef *pCVar4;
  uint uVar5;
  CFileCHandle *fileHandle;
  CStage *pCVar6;
  uint uVar7;
  char acStack_238 [256];
  undefined auStack_138 [264];
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_cpp_801d91bc,0x749);
  AttachTextureSet__Q26CChara6CModelFP11CTextureSet(handle->m_model,(CTexture *)0x0);
  pCVar3 = handle->m_textureSet;
  if (pCVar3 != (CTextureSet *)0x0) {
    iVar2 = *(int *)&pCVar3->field_0x4 + -1;
    *(int *)&pCVar3->field_0x4 = iVar2;
    if ((iVar2 == 0) && (pCVar3 != (CTextureSet *)0x0)) {
      (**(code **)((int)pCVar3->vtable + 8))(pCVar3,1);
    }
    handle->m_textureSet = (CTextureSet *)0x0;
  }
  pCVar4 = handle->m_texLoadRef;
  if (pCVar4 != (CRef *)0x0) {
    iVar2 = pCVar4->refCount + -1;
    pCVar4->refCount = iVar2;
    if ((iVar2 == 0) && (pCVar4 != (CRef *)0x0)) {
      (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
    }
    handle->m_texLoadRef = (CRef *)0x0;
  }
  sprintf(auStack_138,s_dvd_char__s__s_03d__s_03d_s_801d91a0,(&PTR_DAT_801fd224)[(int)param_2 * 3],
          (&PTR_DAT_801fd228)[(int)param_2 * 3],param_3,(&PTR_DAT_801fd228)[(int)param_2 * 3],
          param_3,(&PTR_s__root_801fd22c)[(int)param_2 * 3]);
  for (uVar7 = 0;
      uVar5 = GetSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv((CPtrArray *)&CharaPcs.field_0x88)
      , uVar7 < uVar5; uVar7 = uVar7 + 1) {
    pCVar4 = (CRef *)__vc__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(0x802e99ec,uVar7);
    if (((pCVar4[1].vtable == param_2) && (pCVar4[1].refCount == param_3)) &&
       (pCVar4[3].vtable == param_4)) goto LAB_800768d4;
  }
  pCVar4 = (CRef *)0x0;
LAB_800768d4:
  if (pCVar4 == (CRef *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d9434,param_2,param_3,param_4);
    }
    if (param_4 == (void *)0x0) {
      strcpy(acStack_238,auStack_138);
    }
    else {
      sprintf(acStack_238,&DAT_80330278,auStack_138,(int)param_4 + 0x61);
    }
    strcat(acStack_238,&DAT_80330280);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_238,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      handle->m_textureSet = (CTextureSet *)0x0;
      if ((param_2 != (void *)0x5) && (1 < (uint)System.m_execParam)) {
        Printf__7CSystemFPce(&System,&DAT_801d9488,acStack_238);
      }
    }
    else {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      pvVar1 = File.m_readBuffer;
      pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                 (0x2c,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x609);
      if (pCVar4 != (CRef *)0x0) {
        __ct__4CRefFv(pCVar4);
        pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadTexture_801fd290;
        pCVar4[3].refCount = 0;
        pCVar4[4].vtable = (void *)0x0;
      }
      pCVar4[1].vtable = param_2;
      pCVar4[1].refCount = param_3;
      pCVar4[3].vtable = param_4;
      pCVar4[2].vtable = param_5;
      pCVar4[2].refCount = param_6;
      Add__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ29CCharaPcs12CLoadTexture
                ((CPtrArray *)&CharaPcs.field_0x88,pCVar4);
      pCVar3 = (CTextureSet *)
               __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                         ((CTextureSet *)0x24,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x397);
      if (pCVar3 != (CTextureSet *)0x0) {
        pCVar3 = (CTextureSet *)__ct__11CTextureSetFv(pCVar3);
      }
      iVar2 = 1;
      if (param_2 == (void *)0x4) {
        iVar2 = 3;
      }
      pCVar6 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar6 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar6 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar6 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          }
        }
        else {
          pCVar6 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar6 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(pCVar3,pvVar1,pCVar6,0,0,0,0);
      pCVar4[3].refCount = (int)pCVar3;
      handle->m_texLoadRef = pCVar4;
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      handle->m_texLoadRef->refCount = handle->m_texLoadRef->refCount + 1;
      handle->m_textureSet = (CTextureSet *)handle->m_texLoadRef[3].refCount;
      *(int *)&handle->m_textureSet->field_0x4 = *(int *)&handle->m_textureSet->field_0x4 + 1;
    }
  }
  else {
    if ((pCVar4[4].vtable != (void *)0x0) && (pCVar4->refCount == 1)) {
      LockBuffer__5CFileFv(&File);
      CopyFromAMemorySync__7CMemoryFPvPvUl
                (&Memory,File.m_readBuffer,pCVar4[4].refCount + *(int *)(CharaPcs._200_4_ + 8),
                 pCVar4[5].vtable);
      pvVar1 = File.m_readBuffer;
      pCVar3 = (CTextureSet *)
               __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                         ((CTextureSet *)0x24,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x397);
      if (pCVar3 != (CTextureSet *)0x0) {
        pCVar3 = (CTextureSet *)__ct__11CTextureSetFv(pCVar3);
      }
      iVar2 = 1;
      if (param_2 == (void *)0x4) {
        iVar2 = 3;
      }
      pCVar6 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar6 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar6 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar6 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          }
        }
        else {
          pCVar6 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar6 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(pCVar3,pvVar1,pCVar6,0,0,0,0);
      pCVar4[3].refCount = (int)pCVar3;
      UnlockBuffer__5CFileFv(&File);
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801d93e0,param_2,param_3,param_4);
      }
    }
    handle->m_texLoadRef = pCVar4;
    pCVar4->refCount = pCVar4->refCount + 1;
    handle->m_textureSet = (CTextureSet *)pCVar4[3].refCount;
    *(int *)&handle->m_textureSet->field_0x4 = *(int *)&handle->m_textureSet->field_0x4 + 1;
  }
  AttachTextureSet__Q26CChara6CModelFP11CTextureSet
            (handle->m_model,(CTexture *)handle->m_textureSet);
  return;
}

