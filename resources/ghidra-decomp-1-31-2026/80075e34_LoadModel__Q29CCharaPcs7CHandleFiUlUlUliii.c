// Function: LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
// Entry: 80075e34
// Size: 2352 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
          (CCharaPcsCHandle *handle,void *param_2,int param_3,void *param_4,undefined4 param_5,
          void *param_6,int param_7,int param_8)

{
  void *pvVar1;
  int iVar2;
  CModel *pCVar3;
  CTextureSet *pCVar4;
  CRef *pCVar5;
  uint uVar6;
  CFileCHandle *pCVar7;
  CStage *pCVar8;
  uint uVar9;
  char acStack_238 [256];
  undefined auStack_138 [256];
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_cpp_801d91bc,0x8c9);
  pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
  pCVar3 = handle->m_model;
  if (pCVar3 != (CModel *)0x0) {
    iVar2 = (pCVar3->ref).refCount + -1;
    (pCVar3->ref).refCount = iVar2;
    if ((iVar2 == 0) && (pCVar3 != (CModel *)0x0)) {
      (**(code **)((int)(pCVar3->ref).vtable + 8))(pCVar3,1);
    }
    handle->m_model = (CModel *)0x0;
  }
  pCVar4 = handle->m_textureSet;
  if (pCVar4 != (CTextureSet *)0x0) {
    iVar2 = *(int *)&pCVar4->field_0x4 + -1;
    *(int *)&pCVar4->field_0x4 = iVar2;
    if ((iVar2 == 0) && (pCVar4 != (CTextureSet *)0x0)) {
      (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
    }
    handle->m_textureSet = (CTextureSet *)0x0;
  }
  pCVar5 = handle->m_modelLoadRef;
  if (pCVar5 != (CRef *)0x0) {
    iVar2 = pCVar5->refCount + -1;
    pCVar5->refCount = iVar2;
    if ((iVar2 == 0) && (pCVar5 != (CRef *)0x0)) {
      (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
    }
    handle->m_modelLoadRef = (CRef *)0x0;
  }
  pCVar5 = handle->m_texLoadRef;
  if (pCVar5 != (CRef *)0x0) {
    iVar2 = pCVar5->refCount + -1;
    pCVar5->refCount = iVar2;
    if ((iVar2 == 0) && (pCVar5 != (CRef *)0x0)) {
      (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
    }
    handle->m_texLoadRef = (CRef *)0x0;
  }
  pCVar5 = handle->m_pdtLoadRef;
  if (pCVar5 != (CRef *)0x0) {
    iVar2 = pCVar5->refCount + -1;
    pCVar5->refCount = iVar2;
    if ((iVar2 == 0) && (pCVar5 != (CRef *)0x0)) {
      (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
    }
    handle->m_pdtLoadRef = (CRef *)0x0;
  }
  releaseUnuseLoadModel__9CCharaPcsFi(&CharaPcs,0);
  handle->m_charaKind = (int32_t)param_2;
  handle->m_charaNo = param_3;
  handle->m_textureVariant = (int32_t)param_4;
  sprintf(auStack_138,s_dvd_char__s__s_03d__s_03d_s_801d91a0,(&PTR_DAT_801fd224)[(int)param_2 * 3],
          (&PTR_DAT_801fd228)[(int)param_2 * 3],param_3,(&PTR_DAT_801fd228)[(int)param_2 * 3],
          param_3,(&PTR_s__root_801fd22c)[(int)param_2 * 3]);
  for (uVar9 = 0;
      uVar6 = GetSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)&CharaPcs.field_0x50),
      uVar9 < uVar6; uVar9 = uVar9 + 1) {
    pCVar5 = (CRef *)__vc__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl(0x802e99b4,uVar9);
    if ((pCVar5[1].vtable == param_2) && (pCVar5[1].refCount == param_3)) goto LAB_8007607c;
  }
  pCVar5 = (CRef *)0x0;
LAB_8007607c:
  if (pCVar5 == (CRef *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d92f0,param_2,param_3);
    }
    strcpy(acStack_238,auStack_138);
    strcat(acStack_238,&DAT_80330268);
    pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_238,0,0);
    if (pCVar7 == (CFileCHandle *)0x0) {
      return 0;
    }
    Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
    pvVar1 = File.m_readBuffer;
    pCVar5 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                               (0x28,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x5e8);
    if (pCVar5 != (CRef *)0x0) {
      __ct__4CRefFv(pCVar5);
      pCVar5->vtable = &PTR_PTR_s_CCharaPcs_CLoadModel_801fd2c0;
      pCVar5[3].vtable = (void *)0x0;
      pCVar5[3].refCount = 0;
    }
    pCVar5[1].vtable = param_2;
    pCVar5[1].refCount = param_3;
    pCVar5[2].vtable = param_6;
    pCVar5[2].refCount = param_7;
    Add__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ29CCharaPcs10CLoadModel
              ((CPtrArray *)&CharaPcs.field_0x50,pCVar5);
    pCVar3 = (CModel *)
             __nw__FUlPQ27CMemory6CStagePci(0x124,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x5f1);
    if (pCVar3 != (CModel *)0x0) {
      pCVar3 = (CModel *)__ct__Q26CChara6CModelFv(pCVar3);
    }
    pCVar8 = PartMng.m_pppEnvSt.m_stagePtr;
    if (CharaPcs._228_4_ != 3) {
      if ((int)CharaPcs._228_4_ < 3) {
        pCVar8 = (CStage *)MapMng._0_4_;
        if ((CharaPcs._228_4_ != 1) &&
           (pCVar8 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
          pCVar8 = (CStage *)CharaPcs._204_4_;
        }
      }
      else {
        pCVar8 = (CStage *)CharaPcs._204_4_;
        if ((int)CharaPcs._228_4_ < 5) {
          pCVar8 = (CStage *)CharaPcs._212_4_;
        }
      }
    }
    Create__Q26CChara6CModelFPvPQ27CMemory6CStage(pCVar3,pvVar1,pCVar8);
    pCVar5[3].vtable = pCVar3;
    handle->m_modelLoadRef = pCVar5;
    Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
    handle->m_modelLoadRef->refCount = handle->m_modelLoadRef->refCount + 1;
    handle->m_model = (CModel *)handle->m_modelLoadRef[3].vtable;
    (handle->m_model->ref).refCount = (handle->m_model->ref).refCount + 1;
    strcpy(acStack_238,auStack_138);
    strcat(acStack_238,&DAT_80330270);
    pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_238,0,0);
    if (pCVar7 != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      pCVar8 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar8 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar8 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar8 = (CStage *)CharaPcs._204_4_;
          }
        }
        else {
          pCVar8 = (CStage *)CharaPcs._204_4_;
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar8 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
                (handle->m_model,File.m_readBuffer,pCVar8);
      Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801d9338,param_2,param_3);
      }
    }
  }
  else {
    handle->m_modelLoadRef = pCVar5;
    if (param_8 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = 4;
      if (handle->m_charaKind == 3) {
        iVar2 = 5;
      }
    }
    if (pCVar5->refCount == 1) {
      if (pCVar5[3].refCount != 0) {
        LockBuffer__5CFileFv(&File);
        CopyFromAMemorySync__7CMemoryFPvPvUl
                  (&Memory,File.m_readBuffer,(int)pCVar5[4].vtable + *(int *)(CharaPcs._200_4_ + 8),
                   pCVar5[4].refCount);
        pCVar3 = (CModel *)
                 __nw__FUlPQ27CMemory6CStagePci(0x124,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x7c7)
        ;
        if (pCVar3 != (CModel *)0x0) {
          pCVar3 = (CModel *)__ct__Q26CChara6CModelFv(pCVar3);
        }
        pCVar8 = PartMng.m_pppEnvSt.m_stagePtr;
        if (CharaPcs._228_4_ != 3) {
          if ((int)CharaPcs._228_4_ < 3) {
            pCVar8 = (CStage *)MapMng._0_4_;
            if ((CharaPcs._228_4_ != 1) &&
               (pCVar8 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
              pCVar8 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
            }
          }
          else {
            pCVar8 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
            if ((int)CharaPcs._228_4_ < 5) {
              pCVar8 = (CStage *)CharaPcs._212_4_;
            }
          }
        }
        Create__Q26CChara6CModelFPvPQ27CMemory6CStage(pCVar3,File.m_readBuffer,pCVar8);
        pCVar5[3].vtable = pCVar3;
        UnlockBuffer__5CFileFv(&File);
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801d92a8,param_2,param_3);
        }
      }
      pCVar5->refCount = pCVar5->refCount + 1;
      handle->m_model = (CModel *)pCVar5[3].vtable;
      (handle->m_model->ref).refCount = (handle->m_model->ref).refCount + 1;
      Init__Q26CChara6CModelFv(handle->m_model);
    }
    else {
      pCVar5->refCount = pCVar5->refCount + 1;
      pCVar8 = PartMng.m_pppEnvSt.m_stagePtr;
      if (CharaPcs._228_4_ != 3) {
        if ((int)CharaPcs._228_4_ < 3) {
          pCVar8 = (CStage *)MapMng._0_4_;
          if ((CharaPcs._228_4_ != 1) &&
             (pCVar8 = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
            pCVar8 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          }
        }
        else {
          pCVar8 = *(CStage **)(&CharaPcs.field_0xcc + iVar2 * 4);
          if ((int)CharaPcs._228_4_ < 5) {
            pCVar8 = (CStage *)CharaPcs._212_4_;
          }
        }
      }
      pCVar3 = (CModel *)
               Duplicate__Q26CChara6CModelFPQ27CMemory6CStage((CModel *)pCVar5[3].vtable,pCVar8);
      handle->m_model = pCVar3;
    }
  }
  ChangeTexture__Q29CCharaPcs7CHandleFiUlUlii(handle,param_2,param_3,param_4,param_6,param_7);
  if ((handle->m_textureSet != (CTextureSet *)0x0) &&
     (iVar2 = Find__11CTextureSetFPc(handle->m_textureSet,&DAT_803302c0), -1 < iVar2)) {
    InitMogFurTex__Q26CChara6CModelFv(handle->m_model);
  }
  if ((Game.game.m_currentSceneId != 7) && (param_2 == (void *)0x1)) {
    for (uVar9 = 0;
        uVar6 = GetSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)&CharaPcs.loadPdtArray),
        uVar9 < uVar6; uVar9 = uVar9 + 1) {
      pCVar5 = (CRef *)__vc__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(0x802e9a08,uVar9);
      if (((pCVar5[1].vtable == (void *)0x1) && (pCVar5[1].refCount == param_3)) &&
         (pCVar5[2].vtable == param_4)) goto LAB_8007664c;
    }
    pCVar5 = (CRef *)0x0;
LAB_8007664c:
    if (pCVar5 == (CRef *)0x0) {
      pCVar5 = (CRef *)__nw__FUlPQ27CMemory6CStagePci
                                 (0x20,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x868);
      if (pCVar5 != (CRef *)0x0) {
        __ct__4CRefFv(pCVar5);
        pCVar5->vtable = &PTR_PTR_s_CCharaPcs_CLoadPdt_801fd278;
        pCVar5[2].refCount = -1;
      }
      handle->m_pdtLoadRef = pCVar5;
      handle->m_pdtLoadRef[1].vtable = (void *)0x1;
      handle->m_pdtLoadRef[1].refCount = param_3;
      handle->m_pdtLoadRef[2].vtable = param_4;
      handle->m_pdtLoadRef[3].vtable = param_6;
      handle->m_pdtLoadRef[3].refCount = param_7;
      iVar2 = LoadMonsterPdt__8CPartPcsFiiPviPvi(&PartPcs,param_3,param_4,0,0,0,0);
      handle->m_pdtLoadRef[2].refCount = iVar2;
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801d9380,1,param_3,param_4);
      }
      Add__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FPQ29CCharaPcs8CLoadPdt
                ((CPtrArray *)&CharaPcs.loadPdtArray,handle->m_pdtLoadRef);
      handle->m_pdtLoadRef->refCount = handle->m_pdtLoadRef->refCount + 1;
    }
    else {
      handle->m_pdtLoadRef = pCVar5;
      handle->m_pdtLoadRef->refCount = handle->m_pdtLoadRef->refCount + 1;
    }
  }
  return 1;
}

