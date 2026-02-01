// Function: pppLoadPdt__8CPartMngFPCciiPvi
// Entry: 800588e0
// Size: 1400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppLoadPdt__8CPartMngFPCciiPvi
          (CPartMng *partMng,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  int16_t iVar7;
  int iVar3;
  int iVar4;
  _pppDataHead *p_Var5;
  _pppDataHead *p_Var6;
  pppModelSt *ppVar8;
  pppShapeSt *pppShapeSt;
  uint uVar9;
  pppModelSt *ppVar10;
  pppPdtSlot *ppVar11;
  int iVar12;
  undefined auStack_2a8 [4];
  undefined local_2a4 [32];
  undefined local_284 [204];
  CChunkFile aCStack_1b8 [3];
  CChunkFile aCStack_fc [4];
  
  CacheClear__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  setDefaultParam__Q27CMemory6CStageFUl(PartPcs.m_usbStreamData.m_stageLoad,param_3);
  sprintf(StrTmp,s__s_pdt_8032fe20,param_2);
  ppVar11 = partMng->m_pdtSlots + param_3;
  strncpy(ppVar11->m_name,param_2,0x20);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadPdt_fn__s_801d8298,StrTmp);
  }
  iVar1 = pppPartInit__8CPartMngFv(partMng,StrTmp,auStack_2a8,param_5,param_6);
  if (iVar1 == 0) {
    ppVar11->m_pppDataHead = (_pppDataHead *)0x0;
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
    __ct__10CChunkFileFv(aCStack_fc);
    SetBuf__10CChunkFileFPv(aCStack_fc,iVar1);
    while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_fc,(CChunkFile *)local_284), iVar1 != 0) {
      PushChunk__10CChunkFileFv(aCStack_fc);
      if (local_284._0_4_ == 0x50445420) {
        while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_fc,(CChunkFile *)local_284), iVar1 != 0) {
          PushChunk__10CChunkFileFv(aCStack_fc);
          if (local_284._0_4_ == 0x52534554) {
            ppVar10 = partMng->m_pppModelStArr;
            ppVar8 = (pppModelSt *)0x0;
            while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     (aCStack_fc,(CChunkFile *)(local_2a4 + 0x10)), iVar1 != 0) {
              if ((uint8_t *)local_2a4._16_4_ == (uint8_t *)0x5253444d) {
                if (ppVar8 != (pppModelSt *)0x0) {
                  __ct__10CChunkFileFv(aCStack_1b8);
                  uVar2 = GetAddress__10CChunkFileFv(aCStack_fc);
                  SetBuf__10CChunkFileFPv(aCStack_1b8,uVar2);
                  uVar2 = pppReadRsd__8CPartMngFR10CChunkFileP10pppModelSt
                                    (&PartMng,aCStack_1b8,ppVar8);
                  Ptr2Off__8CMapMeshFv(ppVar8);
                  iVar7 = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
                                    ((CAmemCacheSet *)CAMemCacheSet,(ppVar8->m_mapMesh).field12_0x24
                                     ,uVar2,1,param_4);
                  ppVar8->m_cacheId = iVar7;
                  if ((ppVar8->m_mapMesh).field12_0x24 != 0) {
                    __dl__FPv();
                    (ppVar8->m_mapMesh).field12_0x24 = 0;
                  }
                  ppVar8 = (pppModelSt *)0x0;
                }
              }
              else if (((int)local_2a4._16_4_ < 0x5253444d) &&
                      ((uint8_t *)local_2a4._16_4_ == (uint8_t *)0x4e414d45)) {
                uVar2 = GetString__10CChunkFileFv(aCStack_fc);
                uVar9 = 0;
                ppVar8 = ppVar10;
                do {
                  if ((ppVar8->m_isUsed != '\0') &&
                     (iVar1 = strcmp(ppVar8->m_name,uVar2), iVar1 == 0)) goto LAB_80058b30;
                  uVar9 = uVar9 + 1;
                  ppVar8 = ppVar8 + 1;
                } while (uVar9 < 0x100);
                ppVar8 = (pppModelSt *)0x0;
LAB_80058b30:
                if (ppVar8 == (pppModelSt *)0x0) {
                  iVar1 = 0;
                  iVar4 = 0x100;
                  ppVar8 = ppVar10;
                  do {
                    if (ppVar8->m_isUsed == '\0') {
                      ppVar8 = ppVar10 + iVar1;
                      goto LAB_80058b78;
                    }
                    ppVar8 = ppVar8 + 1;
                    iVar1 = iVar1 + 1;
                    iVar4 = iVar4 + -1;
                  } while (iVar4 != 0);
                  ppVar8 = (pppModelSt *)0x0;
LAB_80058b78:
                  ppVar8->m_refCount = 0;
                  ppVar8->m_isUsed = '\x01';
                  strcpy(ppVar8->m_name,uVar2);
                }
                else {
                  ppVar8 = (pppModelSt *)0x0;
                }
              }
            }
          }
          else if ((int)local_284._0_4_ < 0x52534554) {
            if (local_284._0_4_ == 0x50445453) {
              p_Var5 = (_pppDataHead *)GetAddress__10CChunkFileFv(aCStack_fc);
              pppInitData__FP12_pppDataHeadP7pppProgi(p_Var5,pppSysProgTbl.m_progs,param_4);
              p_Var6 = (_pppDataHead *)
                       __nwa__FUlPQ27CMemory6CStagePci
                                 ((uint)p_Var5->m_partCount * 0x60 + 0x20,
                                  PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0xd56);
              ppVar11->m_pppDataHead = p_Var6;
              memcpy(ppVar11->m_pppDataHead,p_Var5,(uint)p_Var5->m_partCount * 0x60 + 0x20);
              p_Var5 = ppVar11->m_pppDataHead;
              pppEnvStPtr = (_pppEnvSt *)ppVar11->field1_0x4;
              ppVar11->field1_0x4[1] = (uint32_t)partMng->m_materialSet;
              if (p_Var5 != (_pppDataHead *)0x0) {
                ppVar11->field1_0x4[2] = p_Var5->m_modelNames;
                ppVar11->field1_0x4[3] = p_Var5->m_shapeNames;
                ppVar11->field1_0x4[4] = p_Var5->m_shapeGroups;
              }
              ppVar11->field1_0x4[0] = (uint32_t)PartMng.m_pppEnvSt.m_stagePtr;
            }
          }
          else if (local_284._0_4_ == 0x53534554) {
            iVar1 = *(int *)partMng->m_usbEdit;
            pppShapeSt = (pppShapeSt *)0x0;
            while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     (aCStack_fc,(CChunkFile *)local_2a4), iVar4 != 0) {
              if (local_2a4._0_4_ == 0x5348504d) {
                if (pppShapeSt != (pppShapeSt *)0x0) {
                  __ct__10CChunkFileFv(local_284 + 0x10);
                  uVar2 = GetAddress__10CChunkFileFv(aCStack_fc);
                  SetBuf__10CChunkFileFPv((CChunkFile *)(local_284 + 0x10),uVar2);
                  pppReadShp__8CPartMngFR10CChunkFileP10pppShapeSt
                            (&PartMng,local_284 + 0x10,pppShapeSt);
                  pppShapeSt = (pppShapeSt *)0x0;
                }
              }
              else if (((int)local_2a4._0_4_ < 0x5348504d) && (local_2a4._0_4_ == 0x4e414d45)) {
                uVar2 = GetString__10CChunkFileFv(aCStack_fc);
                uVar9 = 0;
                iVar4 = iVar1;
                do {
                  if ((*(char *)(iVar4 + 0x2a) != '\0') &&
                     (iVar3 = strcmp(iVar4 + 8,uVar2), iVar3 == 0)) goto LAB_80058cb4;
                  uVar9 = uVar9 + 1;
                  iVar4 = iVar4 + 0x2c;
                } while (uVar9 < 0x100);
                iVar4 = 0;
LAB_80058cb4:
                if (iVar4 == 0) {
                  iVar3 = 0;
                  iVar12 = 0x100;
                  iVar4 = iVar1;
                  do {
                    if (*(char *)(iVar4 + 0x2a) == '\0') {
                      pppShapeSt = (pppShapeSt *)(iVar1 + iVar3 * 0x2c);
                      goto LAB_80058cfc;
                    }
                    iVar4 = iVar4 + 0x2c;
                    iVar3 = iVar3 + 1;
                    iVar12 = iVar12 + -1;
                  } while (iVar12 != 0);
                  pppShapeSt = (pppShapeSt *)0x0;
LAB_80058cfc:
                  pppShapeSt->m_refCount = 0;
                  pppShapeSt->m_inUse = '\x01';
                  strcpy(pppShapeSt->m_name,uVar2);
                }
                else {
                  pppShapeSt = (pppShapeSt *)0x0;
                }
              }
            }
          }
          PopChunk__10CChunkFileFv(aCStack_fc);
        }
      }
      PopChunk__10CChunkFileFv(aCStack_fc);
    }
    resDefaultParam__Q27CMemory6CStageFv(PartPcs.m_usbStreamData.m_stageLoad);
    uVar2 = 1;
  }
  return uVar2;
}

