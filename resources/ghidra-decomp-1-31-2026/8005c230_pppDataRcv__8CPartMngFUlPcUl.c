// Function: pppDataRcv__8CPartMngFUlPcUl
// Entry: 8005c230
// Size: 5168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDataRcv__8CPartMngFUlPcUl(CPartMng *partMng,int param_2,int *param_3,int param_4)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  int *piVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char cVar8;
  uint8_t uVar9;
  uint8_t uVar10;
  uint8_t uVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  CTextureSet *pCVar15;
  CMaterialSet *pCVar16;
  CMaterial *pCVar17;
  float fVar18;
  short sVar23;
  undefined4 uVar19;
  undefined4 *puVar20;
  void *pvVar21;
  long *plVar22;
  int *piVar24;
  CPartMng *pCVar25;
  int iVar26;
  undefined2 *puVar27;
  _pppMngSt *p_Var28;
  int iVar29;
  uint8_t *puVar30;
  int iVar31;
  uint uVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  CMapMesh *pCVar37;
  float *srcBuffer;
  uint uVar38;
  undefined local_268 [204];
  CChunkFile aCStack_19c [3];
  CChunkFile aCStack_e0 [4];
  
  uVar32 = param_4 - 0x20;
  iVar29 = 0x12345678;
  piVar24 = param_3 + 8;
  if (uVar32 != 0) {
    uVar38 = uVar32 >> 3;
    if (uVar38 != 0) {
      do {
        cVar8 = *(char *)piVar24;
        pcVar1 = (char *)((int)piVar24 + 1);
        pcVar2 = (char *)((int)piVar24 + 2);
        pcVar3 = (char *)((int)piVar24 + 3);
        piVar4 = piVar24 + 1;
        pcVar5 = (char *)((int)piVar24 + 5);
        pcVar6 = (char *)((int)piVar24 + 6);
        pcVar7 = (char *)((int)piVar24 + 7);
        piVar24 = piVar24 + 2;
        iVar29 = iVar29 + cVar8 + (int)*pcVar1 + (int)*pcVar2 + (int)*pcVar3 + (int)*(char *)piVar4
                 + (int)*pcVar5 + (int)*pcVar6 + (int)*pcVar7;
        uVar38 = uVar38 - 1;
      } while (uVar38 != 0);
      uVar32 = uVar32 & 7;
      if (uVar32 == 0) goto LAB_8005c2f8;
    }
    do {
      cVar8 = *(char *)piVar24;
      piVar24 = (int *)((int)piVar24 + 1);
      iVar29 = iVar29 + cVar8;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
LAB_8005c2f8:
  if (iVar29 != *param_3) {
    Printf__8CGraphicFPce(&Graphic,s_CheckSum_ERROR_code_0x_x____801d82f0,param_2);
    DrawDebugString__8CGraphicFv(&Graphic);
  }
  srcBuffer = (float *)(param_3 + 8);
  if (srcBuffer == (float *)0x0) {
    return;
  }
  if (param_2 == 0x14) {
    DAT_8032ed70 = 0;
    return;
  }
  if (0x13 < param_2) {
    if (param_2 == 0x1f) {
      return;
    }
    if (0x1e < param_2) {
      if (param_2 == 0x41) {
        partMng->m_cursorEnable = 0;
        return;
      }
      if (0x40 < param_2) {
        if (param_2 == 0xfe) {
          return;
        }
        if (0xfd < param_2) {
          return;
        }
        if (0x42 < param_2) {
          return;
        }
        memcpy(&partMng->m_cursorPacket,srcBuffer,0x28);
        partMng->m_cursorEnable = 1;
        return;
      }
      if (param_2 == 0x21) {
        ShowMapMeshID__7CMapMngFii(&MapMng,param_3[9],*srcBuffer);
        return;
      }
      if (0x20 < param_2) {
        if (param_2 < 0x40) {
          return;
        }
        partMng->m_cursorEnable = 1;
        return;
      }
      ShowMapObjID__7CMapMngFii(&MapMng,param_3[9],*srcBuffer);
      return;
    }
    if (param_2 == 0x1a) {
      (partMng->m_pppEnvSt).m_lastEnvCmd = 0x1a;
      memcpy(partMng->m_loadAnimName,srcBuffer,0x20);
      return;
    }
    if (0x19 < param_2) {
      if (param_2 == 0x1d) {
        return;
      }
      if (param_2 < 0x1d) {
        if (param_2 < 0x1c) {
          (partMng->m_pppEnvSt).m_lastEnvCmd = 0x1b;
          memcpy(&partMng->m_mapPcsFlag,srcBuffer,4);
          return;
        }
        (partMng->m_pppEnvSt).m_lastEnvCmd = 0x1c;
        memcpy(&partMng->m_charaVisToggle,srcBuffer,4);
        return;
      }
      partMng->m_requestFlag = 1;
      return;
    }
    if (param_2 == 0x17) {
      if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
        return;
      }
      partMng->m_cursorXLatched = partMng->m_cursorX;
      partMng->m_cursorYLatched = partMng->m_cursorY;
      partMng->m_usbEdit[0x18] = '\x01';
      return;
    }
    if (param_2 < 0x17) {
      if (param_2 < 0x16) {
        DAT_8032ed70 = 1;
        return;
      }
      memcpy(partMng->m_cmd16Payload,srcBuffer,8);
      return;
    }
    if (param_2 < 0x19) {
      (partMng->m_pppEnvSt).m_lastEnvCmd = 0x18;
      memcpy(partMng->m_loadMapArgs,srcBuffer,8);
      return;
    }
    (partMng->m_pppEnvSt).m_lastEnvCmd = 0x19;
    memcpy(partMng->m_loadModelArgs,srcBuffer,0xc);
    return;
  }
  if (param_2 == 10) {
LAB_8005cc98:
    if ((partMng->m_pppEnvSt).m_isEditMode == 0) {
      if (*(int *)(partMng->m_usbEdit + 8) == 0) {
        uVar19 = __nwa__FUlPQ27CMemory6CStagePci
                           (0x200,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x60a);
        *(undefined4 *)(partMng->m_usbEdit + 8) = uVar19;
        iVar29 = 0;
        iVar13 = 8;
        do {
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 4) = 0;
          iVar36 = iVar29 + 0x24;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 8) = 0;
          iVar35 = iVar29 + 0x28;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0xc) = 0;
          iVar34 = iVar29 + 0x2c;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0x10) = 0;
          iVar33 = iVar29 + 0x30;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0x14) = 0;
          iVar31 = iVar29 + 0x34;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0x18) = 0;
          iVar26 = iVar29 + 0x38;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0x1c) = 0;
          iVar14 = iVar29 + 0x3c;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29 + 0x20) = 0;
          iVar29 = iVar29 + 0x40;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar36) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar35) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar34) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar33) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar31) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar26) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar14) = 0;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      iVar29 = (int)*srcBuffer * 4;
      piVar24 = *(int **)(*(int *)(partMng->m_usbEdit + 8) + iVar29);
      if (piVar24 != (int *)0x0) {
        sVar23 = *(short *)(piVar24 + 10);
        *(short *)(piVar24 + 10) = sVar23 + -1;
        if ((short)(sVar23 + -1) < 1) {
          if (*piVar24 != 0) {
            __dl__FPv();
            *piVar24 = 0;
          }
          if (piVar24[1] != 0) {
            __dl__FPv();
            piVar24[1] = 0;
          }
          *(undefined2 *)(piVar24 + 10) = 0;
          *(undefined *)((int)piVar24 + 0x2a) = 0;
        }
        *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar29) = 0;
      }
      puVar20 = (undefined4 *)
                __nw__FUlPQ27CMemory6CStagePci
                          (0x2c,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x610);
      if (puVar20 != (undefined4 *)0x0) {
        *(undefined2 *)(puVar20 + 10) = 0;
        *(undefined *)((int)puVar20 + 0x2a) = 0;
        *puVar20 = 0;
        puVar20[1] = 0;
      }
      *(undefined4 **)(*(int *)(partMng->m_usbEdit + 8) + iVar29) = puVar20;
      __ct__10CChunkFileFv(aCStack_19c);
      SetBuf__10CChunkFileFPv(aCStack_19c,param_3 + 0xc);
      pppReadShp__8CPartMngFR10CChunkFileP10pppShapeSt
                (partMng,aCStack_19c,*(pppShapeSt **)(*(int *)(partMng->m_usbEdit + 8) + iVar29));
    }
  }
  else {
    if (9 < param_2) {
      if (param_2 == 0xf) {
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3a9);
        pCVar25 = partMng;
        for (iVar29 = 0; iVar29 < partMng->m_editCount; iVar29 = iVar29 + 1) {
          if (pCVar25->m_pppMngStArr[0].m_baseTime != -0x1000) {
            _pppAllFreePObject__FP9_pppMngSt(pCVar25->m_pppMngStArr);
          }
          pCVar25 = (CPartMng *)pCVar25->m_rgbaA;
        }
        partMng->m_editCount = 0;
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3b3);
        DAT_8032ed68 = 1;
        return;
      }
      if (0xe < param_2) {
        if (param_2 == 0x12) {
          if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
            return;
          }
          uVar32 = partMng->m_selectedId;
          p_Var28 = partMng->m_pppMngStArr;
          pvVar21 = partMng->m_recvBuff;
          for (iVar29 = partMng->m_editCount; iVar29 != 0; iVar29 = iVar29 + -1) {
            if ((uint)*(ushort *)((int)pvVar21 + 0x40) == (uVar32 & 0xffff)) {
              p_Var28->m_baseTime = 0;
            }
            pvVar21 = (void *)((int)pvVar21 + 0x60);
            p_Var28 = p_Var28 + 1;
          }
          return;
        }
        if (0x11 < param_2) {
          if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
            return;
          }
          uVar32 = partMng->m_selectedId;
          p_Var28 = partMng->m_pppMngStArr;
          pvVar21 = partMng->m_recvBuff;
          for (iVar29 = partMng->m_editCount; iVar29 != 0; iVar29 = iVar29 + -1) {
            if ((uint)*(ushort *)((int)pvVar21 + 0x40) == (uVar32 & 0xffff)) {
              p_Var28->m_stopRequested = '\x01';
            }
            pvVar21 = (void *)((int)pvVar21 + 0x60);
            p_Var28 = p_Var28 + 1;
          }
          return;
        }
        if (0x10 < param_2) {
          if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
            return;
          }
          partMng->m_pppMngStArr[0].m_stopRequested = '\x01';
          return;
        }
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        (partMng->m_pppEnvSt).m_envParam = FLOAT_8032fe5c;
        (partMng->m_pppEnvSt).m_mapMeshPtr = *(CMapMesh ***)(partMng->m_usbEdit + 4);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[0].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 8);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[1].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 0xc);
        SetFp__8CPartMngFv(partMng);
        return;
      }
      if (param_2 == 0xd) {
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x673);
        if (partMng->m_pppProgOffsetReconstructionTable[partMng->m_pdtCount] != (long *)0x0) {
          __dl__FPv();
          partMng->m_pppProgOffsetReconstructionTable[partMng->m_pdtCount] = (long *)0x0;
        }
        if (partMng->m_recvBuff != (void *)0x0) {
          __dl__FPv();
          partMng->m_recvBuff = (void *)0x0;
        }
        plVar22 = (long *)__nwa__FUlPQ27CMemory6CStagePci
                                    (param_4 + -0x20,PartPcs.m_usbStreamData.m_stageLoad,
                                     s_partMng_cpp_801d8230,0x678);
        partMng->m_pppProgOffsetReconstructionTable[partMng->m_pdtCount] = plVar22;
        pvVar21 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                    (0x3000,PartPcs.m_usbStreamData.m_stageLoad,
                                     s_partMng_cpp_801d8230,0x679);
        partMng->m_recvBuff = pvVar21;
        memcpy(partMng->m_pppProgOffsetReconstructionTable[partMng->m_pdtCount],srcBuffer,
               param_4 + -0x20);
        pppInitPdt__FPlP7pppProg
                  (partMng->m_pppProgOffsetReconstructionTable[partMng->m_pdtCount],
                   pppSysProgTbl.m_progs);
        partMng->m_pdtCount = partMng->m_pdtCount + 1;
        return;
      }
      if (0xc < param_2) {
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        if (partMng->m_editCount == 0) {
          partMng->m_recvWrite = partMng->m_recvBuff;
        }
        memcpy(partMng->m_recvWrite,srcBuffer,param_4 + -0x20);
        partMng->m_recvWrite = (void *)((int)partMng->m_recvWrite + 0x60);
        partMng->m_editCount = partMng->m_editCount + 1;
        return;
      }
      if (0xb < param_2) {
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x646);
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3a9);
        pCVar25 = partMng;
        for (iVar29 = 0; iVar29 < partMng->m_editCount; iVar29 = iVar29 + 1) {
          if (pCVar25->m_pppMngStArr[0].m_baseTime != -0x1000) {
            _pppAllFreePObject__FP9_pppMngSt(pCVar25->m_pppMngStArr);
          }
          pCVar25 = (CPartMng *)pCVar25->m_rgbaA;
        }
        partMng->m_editCount = 0;
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3b3);
        if (partMng->m_pppProgOffsetReconstructionTable[0] != (long *)0x0) {
          __dl__FPv();
          partMng->m_pppProgOffsetReconstructionTable[0] = (long *)0x0;
        }
        if (partMng->m_recvBuff != (void *)0x0) {
          __dl__FPv();
          partMng->m_recvBuff = (void *)0x0;
        }
        plVar22 = (long *)__nwa__FUlPQ27CMemory6CStagePci
                                    (param_4 + -0x20,PartPcs.m_usbStreamData.m_stageLoad,
                                     s_partMng_cpp_801d8230,0x64d);
        partMng->m_pppProgOffsetReconstructionTable[0] = plVar22;
        pvVar21 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                    (0x3000,PartPcs.m_usbStreamData.m_stageLoad,
                                     s_partMng_cpp_801d8230,0x64e);
        partMng->m_recvBuff = pvVar21;
        memcpy(partMng->m_pppProgOffsetReconstructionTable[0],srcBuffer,param_4 + -0x20);
        pppInitPdt__FPlP7pppProg
                  (partMng->m_pppProgOffsetReconstructionTable[0],pppSysProgTbl.m_progs);
        fVar18 = FLOAT_8032fe6c;
        *(undefined4 *)((int)partMng->m_recvBuff + 0x2c) = 0;
        fVar12 = FLOAT_8032fe70;
        partMng->m_pppMngStArr[0].m_baseTime = 0;
        *(float *)((int)partMng->m_recvBuff + 0x34) = fVar18;
        partMng->m_pppMngStArr[0].m_cullRadiusSq = fVar18;
        *(float *)((int)partMng->m_recvBuff + 0x3c) = fVar12;
        *(float *)((int)partMng->m_recvBuff + 0x38) = fVar12;
        partMng->m_pppMngStArr[0].m_cullYOffset = fVar12;
        partMng->m_pppMngStArr[0].m_cullRadius = fVar12;
        *(undefined4 *)((int)partMng->m_recvBuff + 0x30) = 0;
        partMng->m_editCount = 1;
        partMng->m_pdtCount = 1;
        partMng->m_pppMngStArr[0].m_objHitMask = 0xffffffff;
        partMng->m_pppMngStArr[0].m_cylinderAttribute = 0xffffffff;
        *(undefined4 *)&partMng->m_pppMngStArr[0].field_0x100 = 0;
        partMng->m_pppMngStArr[0].m_isVisible = '\x01';
        partMng->m_pppMngStArr[0].m_ownerVisible = '\x01';
        partMng->m_pppMngStArr[0].m_pppResSet = &partMng->m_unk0x23518;
        partMng->m_pppMngStArr[0].m_nodeIndex = 0;
        partMng->m_pppMngStArr[0].field49_0xf2 = '\x01';
        (partMng->m_pppEnvSt).m_mapMeshPtr = *(CMapMesh ***)(partMng->m_usbEdit + 4);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[0].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 8);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[1].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 0xc);
        return;
      }
      if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
        return;
      }
      __ct__10CChunkFileFv(local_268 + 0x10);
      SetBuf__10CChunkFileFPv((CChunkFile *)(local_268 + 0x10),srcBuffer);
      while (iVar29 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                ((CChunkFile *)(local_268 + 0x10),(CChunkFile *)local_268),
            iVar29 != 0) {
        if (local_268._0_4_ == 0x54584944) {
          if (partMng->m_textureSet == (CTextureSet *)0x0) {
            pCVar15 = (CTextureSet *)
                      __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                                ((CTextureSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                                 s_partMng_cpp_801d8230,0x447);
            if (pCVar15 != (CTextureSet *)0x0) {
              pCVar15 = (CTextureSet *)__ct__11CTextureSetFv(pCVar15);
            }
            partMng->m_textureSet = pCVar15;
            pCVar15 = partMng->m_textureSet;
            SetDefaultSize__21CPtrArray<P8CTexture>FUl(&pCVar15->textures,0x180);
            SetGrow__21CPtrArray(&pCVar15->textures,0);
          }
          if (partMng->m_materialSet == (CMaterialSet *)0x0) {
            pCVar16 = (CMaterialSet *)
                      __nw__12CMaterialSetFUlPQ27CMemory6CStagePci
                                ((CMaterialSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                                 s_partMng_cpp_801d8230,1099);
            if (pCVar16 != (CMaterialSet *)0x0) {
              pCVar16 = (CMaterialSet *)__ct__12CMaterialSetFv(pCVar16);
            }
            partMng->m_materialSet = pCVar16;
            pCVar16 = partMng->m_materialSet;
            SetDefaultSize__22CPtrArray<P9CMaterial>FUl(&pCVar16->materials,0x180);
            SetGrow__22CPtrArray<P9CMaterial>Fi(&pCVar16->materials,0);
            (partMng->m_pppEnvSt).m_materialSetPtr = partMng->m_materialSet;
            pCVar17 = (CMaterial *)
                      __nw__9CMaterialFUlPQ27CMemory6CStagePci
                                (0xa8,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,
                                 0x44e);
            if (pCVar17 != (CMaterial *)0x0) {
              pCVar17 = (CMaterial *)__ct__9CMaterialFv(pCVar17);
            }
            Create__9CMaterialFUlQ212CMaterialMan7TEV_BIT(pCVar17,0,0xfff531f0);
            *(uint *)&pCVar17->field_0x24 = *(uint *)&pCVar17->field_0x24 | 1;
            pCVar16 = partMng->m_materialSet;
            iVar29 = _UnkMaterialSetGetter((CMaterial *)&pCVar16->materials);
            if (iVar29 == 0) {
              Add__22CPtrArray<P9CMaterial>FP9CMaterial(&pCVar16->materials,pCVar17);
            }
            else {
              SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&pCVar16->materials,0,pCVar17);
            }
          }
          Create__11CTextureSetFR10CChunkFilePQ27CMemory6CStageiP13CAmemCacheSetii
                    (partMng->m_textureSet,local_268 + 0x10,PartPcs.m_usbStreamData.m_stageLoad,1,0,
                     0,0);
          SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti
                    (partMng->m_materialSet,partMng->m_textureSet,0);
          SetTextureSet__12CMaterialSetFP11CTextureSet(partMng->m_materialSet,partMng->m_textureSet)
          ;
        }
      }
      return;
    }
    if (param_2 != 5) {
      if (param_2 < 5) {
        if (param_2 == 2) {
          if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
            return;
          }
          (partMng->m_pppEnvSt).m_lastEnvCmd = 2;
          puVar30 = partMng->m_editCameraExtra + 4;
          piVar24 = param_3 + 0x15;
          (partMng->m_pppEnvSt).m_mapMeshPtr = *(CMapMesh ***)(partMng->m_usbEdit + 4);
          *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[0].m_colorRGBA =
               *(undefined4 *)(partMng->m_usbEdit + 8);
          *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[1].m_colorRGBA =
               *(undefined4 *)(partMng->m_usbEdit + 0xc);
          fVar18 = (float)param_3[9];
          (partMng->m_editCameraMatrix).value[0][0] = *srcBuffer;
          (partMng->m_editCameraMatrix).value[0][1] = fVar18;
          fVar18 = (float)param_3[0xb];
          (partMng->m_editCameraMatrix).value[0][2] = (float)param_3[10];
          (partMng->m_editCameraMatrix).value[0][3] = fVar18;
          fVar18 = (float)param_3[0xd];
          (partMng->m_editCameraMatrix).value[1][0] = (float)param_3[0xc];
          (partMng->m_editCameraMatrix).value[1][1] = fVar18;
          fVar18 = (float)param_3[0xf];
          (partMng->m_editCameraMatrix).value[1][2] = (float)param_3[0xe];
          (partMng->m_editCameraMatrix).value[1][3] = fVar18;
          fVar18 = (float)param_3[0x11];
          (partMng->m_editCameraMatrix).value[2][0] = (float)param_3[0x10];
          (partMng->m_editCameraMatrix).value[2][1] = fVar18;
          fVar18 = (float)param_3[0x13];
          (partMng->m_editCameraMatrix).value[2][2] = (float)param_3[0x12];
          (partMng->m_editCameraMatrix).value[2][3] = fVar18;
          *(int *)partMng->m_editCameraExtra = param_3[0x14];
          *(int *)(partMng->m_editCameraExtra + 4) = param_3[0x15];
          iVar29 = 0x1c;
          do {
            piVar4 = piVar24 + 1;
            piVar24 = piVar24 + 2;
            iVar13 = *piVar24;
            *(int *)(puVar30 + 4) = *piVar4;
            puVar30 = puVar30 + 8;
            *(int *)puVar30 = iVar13;
            ppvChrScl.z = FLOAT_8032fe18;
            iVar29 = iVar29 + -1;
          } while (iVar29 != 0);
          partMng->m_rgbaA[0] = *(uint8_t *)(param_3 + 0x4e);
          partMng->m_rgbaA[1] = *(uint8_t *)((int)param_3 + 0x139);
          partMng->m_rgbaA[2] = *(uint8_t *)((int)param_3 + 0x13a);
          partMng->m_rgbaA[3] = *(uint8_t *)((int)param_3 + 0x13b);
          partMng->m_rgbaB[0] = *(uint8_t *)(param_3 + 0x4f);
          partMng->m_rgbaB[1] = *(uint8_t *)((int)param_3 + 0x13d);
          partMng->m_rgbaB[2] = *(uint8_t *)((int)param_3 + 0x13e);
          partMng->m_rgbaB[3] = *(uint8_t *)((int)param_3 + 0x13f);
          partMng->m_fogNearRaw = param_3[0x50];
          partMng->m_fogFarRaw = param_3[0x51];
          *(int *)partMng->m_envColorRgba = param_3[0x52];
          partMng->m_heapCheckInterval = param_3[0x53];
          partMng->m_editEnvFlags = param_3[0x54];
          partMng->m_editDrawMode = param_3[0x55];
          ppvChrScl.y = ppvChrScl.z;
          ppvChrScl.x = ppvChrScl.z;
          pCVar25 = partMng;
          for (iVar29 = 0; iVar29 < partMng->m_editCount; iVar29 = iVar29 + 1) {
            uVar9 = partMng->m_envColorRgba[1];
            uVar10 = partMng->m_envColorRgba[2];
            uVar11 = partMng->m_envColorRgba[3];
            pCVar25->m_pppMngStArr[0].m_envColorR = partMng->m_envColorRgba[0];
            pCVar25->m_pppMngStArr[0].m_envColorG = uVar9;
            pCVar25->m_pppMngStArr[0].m_envColorB = uVar10;
            pCVar25->m_pppMngStArr[0].m_envColorA = uVar11;
            pCVar25 = (CPartMng *)pCVar25->m_rgbaA;
          }
          return;
        }
        if (1 < param_2) {
          if (param_2 < 4) {
            if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
              return;
            }
            partMng->m_pppMngStArr[0].m_position.x = *srcBuffer;
            partMng->m_pppMngStArr[0].m_position.y = (float)param_3[9];
            partMng->m_pppMngStArr[0].m_position.z = (float)param_3[10];
            iVar29 = param_3[0xc];
            partMng->m_pppMngStArr[0].m_rotation.x = (short)((uint)iVar29 >> 0x10);
            partMng->m_pppMngStArr[0].m_rotation.y = (short)iVar29;
            iVar29 = param_3[0xd];
            partMng->m_pppMngStArr[0].m_rotation.z = (short)((uint)iVar29 >> 0x10);
            partMng->m_pppMngStArr[0].m_rotation.w = (short)iVar29;
            partMng->m_pppMngStArr[0].m_rotationSpeed = param_3[0xe];
            partMng->m_pppMngStArr[0].m_scale.x = (float)param_3[0x10];
            partMng->m_pppMngStArr[0].m_scale.y = (float)param_3[0x11];
            partMng->m_pppMngStArr[0].m_scale.z = (float)param_3[0x12];
            partMng->m_pppMngStArr[0].m_savedPosition.x = (float)param_3[0x18];
            partMng->m_pppMngStArr[0].m_savedPosition.y = (float)param_3[0x19];
            partMng->m_pppMngStArr[0].m_savedPosition.z = (float)param_3[0x1a];
            partMng->m_pppMngStArr[0].m_paramVec0.x = (float)param_3[0x1c];
            partMng->m_pppMngStArr[0].m_paramVec0.y = (float)param_3[0x1d];
            partMng->m_pppMngStArr[0].m_paramVec0.z = (float)param_3[0x1e];
            ppvChrScl.x = (float)param_3[0x14];
            ppvChrScl.y = (float)param_3[0x15];
            ppvChrScl.z = (float)param_3[0x16];
            partMng->m_pppMngStArr[0].m_paramC = (float)param_3[0x1f];
            partMng->m_pppMngStArr[0].m_paramD = (float)param_3[0x20];
            partMng->m_pppMngStArr[0].m_endRequested = '\0';
            return;
          }
          _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x554);
          _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3a9);
          pCVar25 = partMng;
          for (iVar29 = 0; iVar29 < partMng->m_editCount; iVar29 = iVar29 + 1) {
            if (pCVar25->m_pppMngStArr[0].m_baseTime != -0x1000) {
              _pppAllFreePObject__FP9_pppMngSt(pCVar25->m_pppMngStArr);
            }
            pCVar25 = (CPartMng *)pCVar25->m_rgbaA;
          }
          partMng->m_editCount = 0;
          _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3b3);
          pppEditAllReleaseResource__8CPartMngFv(partMng);
          DAT_8032ed68 = 1;
          partMng->m_usbEdit[0x10] = '\0';
          partMng->m_usbEdit[0x11] = '\0';
          partMng->m_usbEdit[0x12] = '\0';
          partMng->m_usbEdit[0x13] = '\0';
          partMng->m_usbEdit[0x14] = 0xff;
          partMng->m_usbEdit[0x15] = 0xff;
          partMng->m_usbEdit[0x16] = 0xff;
          partMng->m_usbEdit[0x17] = 0xff;
          partMng->m_editCount = 0;
          partMng->m_pdtCount = 0;
          (partMng->m_pppEnvSt).m_isEditMode = 0;
          if (partMng->m_textureSet == (CTextureSet *)0x0) {
            pCVar15 = (CTextureSet *)
                      __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                                ((CTextureSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                                 s_partMng_cpp_801d8230,0x447);
            if (pCVar15 != (CTextureSet *)0x0) {
              pCVar15 = (CTextureSet *)__ct__11CTextureSetFv(pCVar15);
            }
            partMng->m_textureSet = pCVar15;
            pCVar15 = partMng->m_textureSet;
            SetDefaultSize__21CPtrArray<P8CTexture>FUl(&pCVar15->textures,0x180);
            SetGrow__21CPtrArray(&pCVar15->textures,0);
          }
          if (partMng->m_materialSet != (CMaterialSet *)0x0) {
            return;
          }
          pCVar16 = (CMaterialSet *)
                    __nw__12CMaterialSetFUlPQ27CMemory6CStagePci
                              ((CMaterialSet *)0x24,PartPcs.m_usbStreamData.m_stageLoad,
                               s_partMng_cpp_801d8230,1099);
          if (pCVar16 != (CMaterialSet *)0x0) {
            pCVar16 = (CMaterialSet *)__ct__12CMaterialSetFv(pCVar16);
          }
          partMng->m_materialSet = pCVar16;
          pCVar16 = partMng->m_materialSet;
          SetDefaultSize__22CPtrArray<P9CMaterial>FUl(&pCVar16->materials,0x180);
          SetGrow__22CPtrArray<P9CMaterial>Fi(&pCVar16->materials,0);
          (partMng->m_pppEnvSt).m_materialSetPtr = partMng->m_materialSet;
          pCVar17 = (CMaterial *)
                    __nw__9CMaterialFUlPQ27CMemory6CStagePci
                              (0xa8,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x44e
                              );
          if (pCVar17 != (CMaterial *)0x0) {
            pCVar17 = (CMaterial *)__ct__9CMaterialFv(pCVar17);
          }
          Create__9CMaterialFUlQ212CMaterialMan7TEV_BIT(pCVar17,0,0xfff531f0);
          *(uint *)&pCVar17->field_0x24 = *(uint *)&pCVar17->field_0x24 | 1;
          pCVar16 = partMng->m_materialSet;
          iVar29 = _UnkMaterialSetGetter((CMaterial *)&pCVar16->materials);
          if (iVar29 == 0) {
            Add__22CPtrArray<P9CMaterial>FP9CMaterial(&pCVar16->materials,pCVar17);
            return;
          }
          SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&pCVar16->materials,0,pCVar17);
          return;
        }
        if (param_2 < 1) {
          return;
        }
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        (partMng->m_pppEnvSt).m_lastEnvCmd = 1;
        puVar30 = partMng->m_editCameraExtra + 4;
        piVar24 = param_3 + 0x15;
        (partMng->m_pppEnvSt).m_mapMeshPtr = *(CMapMesh ***)(partMng->m_usbEdit + 4);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[0].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 8);
        *(undefined4 *)(partMng->m_pppEnvSt).m_particleColors[1].m_colorRGBA =
             *(undefined4 *)(partMng->m_usbEdit + 0xc);
        fVar18 = (float)param_3[9];
        (partMng->m_editCameraMatrix).value[0][0] = *srcBuffer;
        (partMng->m_editCameraMatrix).value[0][1] = fVar18;
        fVar18 = (float)param_3[0xb];
        (partMng->m_editCameraMatrix).value[0][2] = (float)param_3[10];
        (partMng->m_editCameraMatrix).value[0][3] = fVar18;
        fVar18 = (float)param_3[0xd];
        (partMng->m_editCameraMatrix).value[1][0] = (float)param_3[0xc];
        (partMng->m_editCameraMatrix).value[1][1] = fVar18;
        fVar18 = (float)param_3[0xf];
        (partMng->m_editCameraMatrix).value[1][2] = (float)param_3[0xe];
        (partMng->m_editCameraMatrix).value[1][3] = fVar18;
        fVar18 = (float)param_3[0x11];
        (partMng->m_editCameraMatrix).value[2][0] = (float)param_3[0x10];
        (partMng->m_editCameraMatrix).value[2][1] = fVar18;
        fVar18 = (float)param_3[0x13];
        (partMng->m_editCameraMatrix).value[2][2] = (float)param_3[0x12];
        (partMng->m_editCameraMatrix).value[2][3] = fVar18;
        *(int *)partMng->m_editCameraExtra = param_3[0x14];
        *(int *)(partMng->m_editCameraExtra + 4) = param_3[0x15];
        iVar29 = 0x1c;
        do {
          piVar4 = piVar24 + 1;
          piVar24 = piVar24 + 2;
          iVar13 = *piVar24;
          *(int *)(puVar30 + 4) = *piVar4;
          puVar30 = puVar30 + 8;
          *(int *)puVar30 = iVar13;
          fVar18 = FLOAT_8032fe18;
          iVar29 = iVar29 + -1;
        } while (iVar29 != 0);
        partMng->m_rgbaA[0] = *(uint8_t *)(param_3 + 0x4e);
        partMng->m_rgbaA[1] = *(uint8_t *)((int)param_3 + 0x139);
        partMng->m_rgbaA[2] = *(uint8_t *)((int)param_3 + 0x13a);
        partMng->m_rgbaA[3] = *(uint8_t *)((int)param_3 + 0x13b);
        partMng->m_rgbaB[0] = *(uint8_t *)(param_3 + 0x4f);
        partMng->m_rgbaB[1] = *(uint8_t *)((int)param_3 + 0x13d);
        partMng->m_rgbaB[2] = *(uint8_t *)((int)param_3 + 0x13e);
        partMng->m_rgbaB[3] = *(uint8_t *)((int)param_3 + 0x13f);
        partMng->m_fogNearRaw = param_3[0x50];
        partMng->m_fogFarRaw = param_3[0x51];
        *(int *)partMng->m_envColorRgba = param_3[0x52];
        partMng->m_heapCheckInterval = param_3[0x53];
        partMng->m_editEnvFlags = param_3[0x54];
        partMng->m_editDrawMode = param_3[0x55];
        partMng->m_pppMngStArr[0].m_ownerScale = fVar18;
        partMng->m_pppMngStArr[0].m_scaleFactor = fVar18;
        partMng->m_pppMngStArr[0].m_userFloat1 = fVar18;
        partMng->m_pppMngStArr[0].m_userFloat0 = fVar18;
        partMng->m_pppMngStArr[0].m_ownerScaleMode = '\0';
        partMng->m_pppMngStArr[0].field38_0xe7 = '\0';
        pCVar25 = partMng;
        for (iVar29 = 0; iVar29 < partMng->m_editCount; iVar29 = iVar29 + 1) {
          uVar9 = partMng->m_envColorRgba[1];
          uVar10 = partMng->m_envColorRgba[2];
          uVar11 = partMng->m_envColorRgba[3];
          pCVar25->m_pppMngStArr[0].m_envColorR = partMng->m_envColorRgba[0];
          pCVar25->m_pppMngStArr[0].m_envColorG = uVar9;
          pCVar25->m_pppMngStArr[0].m_envColorB = uVar10;
          pCVar25->m_pppMngStArr[0].m_envColorA = uVar11;
          pCVar25 = (CPartMng *)pCVar25->m_rgbaA;
        }
        return;
      }
      if (param_2 == 8) {
        if ((partMng->m_pppEnvSt).m_isEditMode != 0) {
          return;
        }
        if (*(int *)(partMng->m_usbEdit + 0xc) == 0) {
          uVar19 = __nwa__FUlPQ27CMemory6CStagePci
                             (0x400,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x61f
                             );
          *(undefined4 *)(partMng->m_usbEdit + 0xc) = uVar19;
        }
        fVar18 = *srcBuffer;
        if (partMng->m_streamTextRaw[(int)fVar18] == (void *)0x0) {
          pvVar21 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                      (param_4 + -0x20,PartPcs.m_usbStreamData.m_stageLoad,
                                       s_partMng_cpp_801d8230,0x625);
          partMng->m_streamTextRaw[(int)fVar18] = pvVar21;
        }
        memcpy(partMng->m_streamTextRaw[(int)fVar18],srcBuffer,param_4 + -0x20);
        puVar27 = (undefined2 *)(*(int *)(partMng->m_usbEdit + 0xc) + (int)fVar18 * 8);
        *puVar27 = (short)*(undefined4 *)((int)partMng->m_streamTextRaw[(int)fVar18] + 4);
        puVar27[1] = (short)*(undefined4 *)((int)partMng->m_streamTextRaw[(int)fVar18] + 8);
        *(int *)(puVar27 + 2) = (int)partMng->m_streamTextRaw[(int)fVar18] + 0xc;
        return;
      }
      if (param_2 < 8) {
        if (6 < param_2) {
          return;
        }
        goto LAB_8005cc98;
      }
    }
    if ((partMng->m_pppEnvSt).m_isEditMode == 0) {
      __ct__10CChunkFileFv(aCStack_e0);
      SetBuf__10CChunkFileFPv(aCStack_e0,param_3 + 0x10);
      if (*(int *)(partMng->m_usbEdit + 4) == 0) {
        uVar19 = __nwa__FUlPQ27CMemory6CStagePci
                           (0x220,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x5f8);
        *(undefined4 *)(partMng->m_usbEdit + 4) = uVar19;
        iVar29 = 0;
        iVar13 = 0x11;
        do {
          iVar36 = iVar29 + 4;
          iVar35 = iVar29 + 8;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar29) = 0;
          iVar34 = iVar29 + 0xc;
          iVar33 = iVar29 + 0x10;
          iVar31 = iVar29 + 0x14;
          iVar26 = iVar29 + 0x18;
          iVar14 = iVar29 + 0x1c;
          iVar29 = iVar29 + 0x20;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar36) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar35) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar34) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar33) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar31) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar26) = 0;
          *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar14) = 0;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      pCVar37 = *(CMapMesh **)(*(int *)(partMng->m_usbEdit + 4) + *(short *)srcBuffer * 4);
      if (pCVar37 != (CMapMesh *)0x0) {
        sVar23 = *(short *)&pCVar37[1].field11_0x20 + -1;
        *(short *)&pCVar37[1].field11_0x20 = sVar23;
        if (sVar23 < 1) {
          iVar29 = (int)*(short *)((int)&pCVar37[1].field11_0x20 + 2);
          if (iVar29 != -1) {
            DestroyCache__13CAmemCacheSetFi((CAmemCacheSet *)CAMemCacheSet,iVar29);
            pCVar37->field12_0x24 = 0;
            pCVar37->field13_0x28 = 0;
          }
          Destroy__8CMapMeshFv(pCVar37);
          *(undefined2 *)&pCVar37[1].field11_0x20 = 0;
          *(undefined *)&pCVar37[1].field12_0x24 = 0;
        }
        *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + *(short *)srcBuffer * 4) = 0;
      }
      pCVar37 = (CMapMesh *)
                __nw__FUlPQ27CMemory6CStagePci
                          (0x6c,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x5fc);
      if (pCVar37 != (CMapMesh *)0x0) {
        __ct__8CMapMeshFv(pCVar37);
        *(undefined2 *)&pCVar37[1].field11_0x20 = 0;
        *(undefined *)&pCVar37[1].field12_0x24 = 0;
      }
      *(CMapMesh **)(*(int *)(partMng->m_usbEdit + 4) + *(short *)srcBuffer * 4) = pCVar37;
      pppReadRsd__8CPartMngFR10CChunkFileP10pppModelSt
                (partMng,aCStack_e0,
                 *(pppModelSt **)(*(int *)(partMng->m_usbEdit + 4) + *(short *)srcBuffer * 4));
      partMng->m_usbEdit[0x14] = 0xff;
      partMng->m_usbEdit[0x15] = 0xff;
      partMng->m_usbEdit[0x16] = 0xff;
      partMng->m_usbEdit[0x17] = 0xff;
    }
  }
  return;
}

