// Function: pppLoadPtx__8CPartMngFPCciiPvi
// Entry: 80059658
// Size: 724 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppLoadPtx__8CPartMngFPCciiPvi
          (CPartMng *partMng,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  CTextureSet *pCVar3;
  CMaterialSet *pCVar4;
  CMaterial *material;
  int iVar5;
  undefined auStack_f8 [4];
  undefined local_f4 [208];
  
  CacheClear__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  setDefaultParam__Q27CMemory6CStageFUl(PartPcs.m_usbStreamData.m_stageLoad,param_3);
  sprintf(StrTmp,s__s_ptx_8032fe38,param_2);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadPtx_fn__s_801d82e0,StrTmp);
  }
  iVar1 = pppPartInit__8CPartMngFv(partMng,StrTmp,auStack_f8,param_5,param_6);
  if (iVar1 == 0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d82a8,StrTmp);
    }
    resDefaultParam__Q27CMemory6CStageFv(PartPcs.m_usbStreamData.m_stageLoad);
    uVar2 = 0;
  }
  else if (partMng->m_partLoadMode == 2) {
    uVar2 = 1;
  }
  else if (partMng->m_partLoadMode == 3) {
    uVar2 = 1;
  }
  else {
    if (partMng->m_textureSet == (CTextureSet *)0x0) {
      pCVar3 = (CTextureSet *)
               __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                         ((CTextureSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                          s_partMng_cpp_801d8230,0xc10);
      if (pCVar3 != (CTextureSet *)0x0) {
        pCVar3 = (CTextureSet *)__ct__11CTextureSetFv(pCVar3);
      }
      partMng->m_textureSet = pCVar3;
      pCVar3 = partMng->m_textureSet;
      SetDefaultSize__21CPtrArray<P8CTexture>FUl(&pCVar3->textures,0x180);
      SetGrow__21CPtrArray(&pCVar3->textures,0);
    }
    if (partMng->m_materialSet == (CMaterialSet *)0x0) {
      pCVar4 = (CMaterialSet *)
               __nw__12CMaterialSetFUlPQ27CMemory6CStagePci
                         ((CMaterialSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                          s_partMng_cpp_801d8230,0xc14);
      if (pCVar4 != (CMaterialSet *)0x0) {
        pCVar4 = (CMaterialSet *)__ct__12CMaterialSetFv(pCVar4);
      }
      partMng->m_materialSet = pCVar4;
      pCVar4 = partMng->m_materialSet;
      SetDefaultSize__22CPtrArray<P9CMaterial>FUl(&pCVar4->materials,0x180);
      SetGrow__22CPtrArray<P9CMaterial>Fi(&pCVar4->materials,0);
      (partMng->m_pppEnvSt).m_materialSetPtr = partMng->m_materialSet;
      material = (CMaterial *)
                 __nw__9CMaterialFUlPQ27CMemory6CStagePci
                           (0xa8,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0xc17);
      if (material != (CMaterial *)0x0) {
        material = (CMaterial *)__ct__9CMaterialFv(material);
      }
      Create__9CMaterialFUlQ212CMaterialMan7TEV_BIT(material,0,0xfff531f0);
      pCVar4 = partMng->m_materialSet;
      iVar5 = _UnkMaterialSetGetter((CMaterial *)&pCVar4->materials);
      if (iVar5 == 0) {
        Add__22CPtrArray<P9CMaterial>FP9CMaterial(&pCVar4->materials,material);
      }
      else {
        SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&pCVar4->materials,0,material);
      }
    }
    __ct__10CChunkFileFv(local_f4 + 0x10);
    SetBuf__10CChunkFileFPv((CChunkFile *)(local_f4 + 0x10),iVar1);
    while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             ((CChunkFile *)(local_f4 + 0x10),(CChunkFile *)local_f4), iVar1 != 0) {
      if (local_f4._0_4_ == 0x54534554) {
        Create__11CTextureSetFR10CChunkFilePQ27CMemory6CStageiP13CAmemCacheSetii
                  (partMng->m_textureSet,local_f4 + 0x10,PartPcs.m_usbStreamData.m_stageLoad,1,
                   CAMemCacheSet,param_4,0);
      }
    }
    SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti
              (partMng->m_materialSet,partMng->m_textureSet,param_3);
    SetTextureSet__12CMaterialSetFP11CTextureSet(partMng->m_materialSet,partMng->m_textureSet);
    resDefaultParam__Q27CMemory6CStageFv(PartPcs.m_usbStreamData.m_stageLoad);
    uVar2 = 1;
  }
  return uVar2;
}

