// Function: loadModelASyncFrame__Q29CCharaPcs7CHandleFv
// Entry: 80073dbc
// Size: 1440 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadModelASyncFrame__Q29CCharaPcs7CHandleFv(CCharaPcsCHandle *handle)

{
  void *pvVar1;
  int iVar2;
  CFileCHandle *pCVar3;
  CRef *pCVar4;
  CModel *model;
  CTextureSet *textureSet;
  CStage *pCVar5;
  int32_t iVar6;
  void *pvVar7;
  void *pvVar8;
  char acStack_228 [256];
  undefined auStack_128 [264];
  
  iVar2 = handle->m_asyncState;
  if (((iVar2 == 1) || (iVar2 == 3)) || (iVar2 == 5)) {
    iVar2 = handle->m_asyncCharaKind;
    sprintf(auStack_128,s_dvd_char__s__s_03d__s_03d_s_801d91a0,(&PTR_DAT_801fd224)[iVar2 * 3],
            (&PTR_DAT_801fd228)[iVar2 * 3],handle->m_asyncCharaNo,(&PTR_DAT_801fd228)[iVar2 * 3],
            handle->m_asyncCharaNo,(&PTR_s__root_801fd22c)[iVar2 * 3]);
    if (handle->m_asyncState == 1) {
      strcpy(acStack_228,auStack_128);
      strcat(acStack_228,&DAT_80330268);
    }
    else if (handle->m_asyncState == 3) {
      strcpy(acStack_228,auStack_128);
      strcat(acStack_228,&DAT_80330270);
    }
    else {
      if (handle->m_asyncTextureVariant < 1) {
        strcpy(acStack_228,auStack_128);
      }
      else {
        sprintf(acStack_228,&DAT_80330278,auStack_128,handle->m_asyncTextureVariant + 0x61);
      }
      strcat(acStack_228,&DAT_80330280);
    }
    pCVar3 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_228,0,0);
    handle->m_asyncFileHandle = pCVar3;
    if ((handle->m_asyncFileHandle == (CFileCHandle *)0x0) && (handle->m_asyncState == 3)) {
      handle->m_asyncState = 5;
      loadModelASyncFrame__Q29CCharaPcs7CHandleFv(handle);
    }
    else {
      ReadASync__5CFileFPQ25CFile7CHandle(&File,handle->m_asyncFileHandle);
      handle->m_asyncState = handle->m_asyncState + 1;
    }
  }
  else if ((((iVar2 == 2) || (iVar2 == 4)) || (iVar2 == 6)) &&
          (iVar2 = IsCompleted__5CFileFPQ25CFile7CHandle(&File,handle->m_asyncFileHandle),
          pvVar1 = File.m_readBuffer, iVar2 != 0)) {
    if (handle->m_asyncState == 2) {
      iVar6 = handle->m_asyncCharaNo;
      pvVar8 = (void *)handle->m_asyncCharaKind;
      pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                 (0x28,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x5e8);
      if (pCVar4 != (CRef *)0x0) {
        __ct__4CRefFv(pCVar4);
        pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadModel_801fd2c0;
        pCVar4[3].vtable = (void *)0x0;
        pCVar4[3].refCount = 0;
      }
      pCVar4[1].vtable = pvVar8;
      pCVar4[1].refCount = iVar6;
      pCVar4[2].vtable = (void *)0xffffffff;
      pCVar4[2].refCount = 0;
      Add__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ29CCharaPcs10CLoadModel
                ((CPtrArray *)&CharaPcs.field_0x50,pCVar4);
      model = (CModel *)
              __nw__FUlPQ27CMemory6CStagePci(0x124,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x5f1);
      if (model != (CModel *)0x0) {
        model = (CModel *)__ct__Q26CChara6CModelFv(model);
      }
      pCVar5 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar5 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar5 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar5 = (CStage *)CharaPcs._204_4_;
          }
        }
        else {
          pCVar5 = (CStage *)CharaPcs._204_4_;
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar5 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      Create__Q26CChara6CModelFPvPQ27CMemory6CStage(model,pvVar1,pCVar5);
      pCVar4[3].vtable = model;
      handle->m_modelLoadRef = pCVar4;
      handle->m_modelLoadRef->refCount = handle->m_modelLoadRef->refCount + 1;
      handle->m_model = (CModel *)handle->m_modelLoadRef[3].vtable;
      (handle->m_model->ref).refCount = (handle->m_model->ref).refCount + 1;
      handle->m_charaKind = handle->m_asyncCharaKind;
      handle->m_charaNo = handle->m_asyncCharaNo;
    }
    else if (handle->m_asyncState == 4) {
      pCVar5 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar5 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar5 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar5 = (CStage *)CharaPcs._204_4_;
          }
        }
        else {
          pCVar5 = (CStage *)CharaPcs._204_4_;
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar5 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
                (handle->m_model,File.m_readBuffer,pCVar5);
    }
    else {
      pvVar8 = (void *)handle->m_asyncTextureVariant;
      iVar6 = handle->m_asyncCharaNo;
      pvVar7 = (void *)handle->m_asyncCharaKind;
      pCVar4 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                 (0x2c,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x609);
      if (pCVar4 != (CRef *)0x0) {
        __ct__4CRefFv(pCVar4);
        pCVar4->vtable = &PTR_PTR_s_CCharaPcs_CLoadTexture_801fd290;
        pCVar4[3].refCount = 0;
        pCVar4[4].vtable = (void *)0x0;
      }
      pCVar4[1].vtable = pvVar7;
      pCVar4[1].refCount = iVar6;
      pCVar4[3].vtable = pvVar8;
      pCVar4[2].vtable = (void *)0xffffffff;
      pCVar4[2].refCount = 0;
      Add__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ29CCharaPcs12CLoadTexture
                ((CPtrArray *)&CharaPcs.field_0x88,pCVar4);
      textureSet = (CTextureSet *)
                   __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                             ((CTextureSet *)0x24,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x397);
      if (textureSet != (CTextureSet *)0x0) {
        textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
      }
      iVar2 = 1;
      if (pvVar7 == (void *)0x4) {
        iVar2 = 3;
      }
      pCVar5 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar5 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar5 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar5 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          }
        }
        else {
          pCVar5 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar5 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                (textureSet,pvVar1,pCVar5,0,0,0,0);
      pCVar4[3].refCount = (int)textureSet;
      handle->m_texLoadRef = pCVar4;
      handle->m_texLoadRef->refCount = handle->m_texLoadRef->refCount + 1;
      handle->m_textureSet = (CTextureSet *)handle->m_texLoadRef[3].refCount;
      *(int *)&handle->m_textureSet->field_0x4 = *(int *)&handle->m_textureSet->field_0x4 + 1;
      AttachTextureSet__Q26CChara6CModelFP11CTextureSet
                (handle->m_model,(CTexture *)handle->m_textureSet);
      handle->m_textureVariant = handle->m_asyncTextureVariant;
    }
    Close__5CFileFPQ25CFile7CHandle(&File,handle->m_asyncFileHandle);
    handle->m_asyncFileHandle = (CFileCHandle *)0x0;
    if (handle->m_asyncState == 6) {
      handle->m_asyncState = 7;
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801d91c8);
      }
    }
    else {
      handle->m_asyncState = handle->m_asyncState + 1;
      loadModelASyncFrame__Q29CCharaPcs7CHandleFv(handle);
    }
  }
  return;
}

