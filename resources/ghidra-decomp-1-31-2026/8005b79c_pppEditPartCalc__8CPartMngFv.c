// Function: pppEditPartCalc__8CPartMngFv
// Entry: 8005b79c
// Size: 1060 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditPartCalc__8CPartMngFv(CPartMng *partMng)

{
  uint8_t uVar1;
  uint8_t uVar2;
  uint8_t uVar3;
  int iVar4;
  int iVar5;
  _pppMngSt *p_Var6;
  CPartMng *pCVar7;
  int iVar8;
  
  if (DAT_8032ed6c != 0) {
    DAT_8032ed6c = 0;
    DAT_8032ed68 = 0;
  }
  Stop__10CStopWatchFv(g_par_calc_prof);
  if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
    CalcMatrix__Q26CChara6CModelFv
              (*(undefined4 *)(*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 0x168));
    CalcSkin__Q26CChara6CModelFv
              (*(undefined4 *)(*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 0x168));
    SetFrame__Q26CChara6CModelFf
              ((partMng->m_pppEnvSt).m_envParam,
               *(CModel **)(*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 0x168));
    if (DAT_8032ed70 == 0) {
      (partMng->m_pppEnvSt).m_envParam = (partMng->m_pppEnvSt).m_envParam + FLOAT_8032fe18;
    }
  }
  Start__10CStopWatchFv(g_par_calc_prof);
  if (partMng->m_usbEdit[0x18] != '\0') {
    partMng->m_usbEdit[0x18] = '\0';
    partMng->m_usbEdit[0x19] = '\x01';
    partMng->m_usbEdit[0x1a] = '\0';
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3a9);
    pCVar7 = partMng;
    for (iVar5 = 0; iVar5 < partMng->m_editCount; iVar5 = iVar5 + 1) {
      if (pCVar7->m_pppMngStArr[0].m_baseTime != -0x1000) {
        _pppAllFreePObject__FP9_pppMngSt(pCVar7->m_pppMngStArr);
      }
      pCVar7 = (CPartMng *)pCVar7->m_rgbaA;
    }
    partMng->m_editCount = 0;
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x3b3);
    partMng->m_pppMngStArr[0].m_stopRequested = '\0';
    uVar1 = partMng->m_envColorRgba[1];
    uVar2 = partMng->m_envColorRgba[2];
    uVar3 = partMng->m_envColorRgba[3];
    partMng->m_pppMngStArr[0].m_envColorR = partMng->m_envColorRgba[0];
    partMng->m_pppMngStArr[0].m_envColorG = uVar1;
    partMng->m_pppMngStArr[0].m_envColorB = uVar2;
    partMng->m_pppMngStArr[0].m_envColorA = uVar3;
    _pppStartPart__FP9_pppMngStPli
              (partMng->m_pppMngStArr,partMng->m_pppProgOffsetReconstructionTable[0],1);
  }
  if ((DAT_8032ed68 == 0) && (partMng->m_pppProgOffsetReconstructionTable[0] != (long *)0x0)) {
    if ((int)partMng->m_editDrawMode < 4) {
      iVar8 = 0;
      pCVar7 = partMng;
      for (iVar5 = 0; iVar5 < partMng->m_editCount; iVar5 = iVar5 + 1) {
        p_Var6 = pCVar7->m_pppMngStArr;
        iVar4 = pCVar7->m_pppMngStArr[0].m_baseTime;
        pppMngStPtr = p_Var6;
        if (iVar4 != -0x1000) {
          if (-1 < iVar4) {
            pCVar7->m_pppMngStArr[0].m_baseTime = iVar4 + -1;
            if (-1 < iVar4 + -1) goto LAB_8005ba2c;
            pCVar7->m_pppMngStArr[0].m_stopRequested = '\0';
            uVar1 = partMng->m_envColorRgba[1];
            uVar2 = partMng->m_envColorRgba[2];
            uVar3 = partMng->m_envColorRgba[3];
            pCVar7->m_pppMngStArr[0].m_envColorR = partMng->m_envColorRgba[0];
            pCVar7->m_pppMngStArr[0].m_envColorG = uVar1;
            pCVar7->m_pppMngStArr[0].m_envColorB = uVar2;
            pCVar7->m_pppMngStArr[0].m_envColorA = uVar3;
            _pppStartPart__FP9_pppMngStPli
                      (p_Var6,partMng->m_pppProgOffsetReconstructionTable
                              [*(int *)((int)partMng->m_recvBuff + iVar8 + 0x30)],1);
          }
          pppSetMatrix__FP9_pppMngSt(p_Var6);
          pppSetFpMatrix__FP9_pppMngSt(p_Var6);
          _pppCalcPart__FP9_pppMngSt(p_Var6);
          _pppDeadPart__FP9_pppMngSt(p_Var6);
          if ((pCVar7->m_pppMngStArr[0].field37_0xe6 != '\0') ||
             (pCVar7->m_pppMngStArr[0].m_endRequested != '\0')) {
            _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x827);
            _pppAllFreePObject__FP9_pppMngSt(p_Var6);
            _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x82b);
            if (3 < (int)partMng->m_editDrawMode) {
              pppHeapCheckLeak__FPQ27CMemory6CStage(pppEnvStPtr->m_stagePtr);
            }
            if (iVar5 == 0) {
              partMng->m_usbEdit[0x1a] = '\x01';
            }
            DAT_801eae0c = 0;
          }
        }
LAB_8005ba2c:
        pCVar7 = (CPartMng *)pCVar7->m_rgbaA;
        iVar8 = iVar8 + 0x60;
      }
    }
    else {
      iVar8 = 0;
      pCVar7 = partMng;
      for (iVar5 = 0; iVar5 < partMng->m_editCount; iVar5 = iVar5 + 1) {
        p_Var6 = pCVar7->m_pppMngStArr;
        pppMngStPtr = p_Var6;
        if (pCVar7->m_pppMngStArr[0].m_baseTime == -0x1000) {
          pCVar7->m_pppMngStArr[0].m_baseTime = 0;
        }
        iVar4 = pCVar7->m_pppMngStArr[0].m_baseTime;
        if (iVar4 < 0) {
LAB_8005ba88:
          pppSetMatrix__FP9_pppMngSt(p_Var6);
          pppSetFpMatrix__FP9_pppMngSt(p_Var6);
          _pppCalcPart__FP9_pppMngSt(p_Var6);
          if ((pCVar7->m_pppMngStArr[0].m_stopAtLifeEnd != '\0') &&
             (pCVar7->m_pppMngStArr[0].m_currentFrame == pCVar7->m_pppMngStArr[0].m_lifeEnd)) {
            DAT_801eae0c = 0;
          }
          _pppDeadPart__FP9_pppMngSt(p_Var6);
          if ((pCVar7->m_pppMngStArr[0].field37_0xe6 != '\0') ||
             (pCVar7->m_pppMngStArr[0].m_endRequested != '\0')) {
            _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x861);
            _pppAllFreePObject__FP9_pppMngSt(p_Var6);
            _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x865);
            if (3 < (int)partMng->m_editDrawMode) {
              pppHeapCheckLeak__FPQ27CMemory6CStage(pppEnvStPtr->m_stagePtr);
            }
            if (iVar5 == 0) {
              partMng->m_usbEdit[0x1a] = '\x01';
            }
            DAT_801eae0c = 0;
          }
        }
        else {
          iVar4 = iVar4 + -1;
          pCVar7->m_pppMngStArr[0].m_baseTime = iVar4;
          if (iVar4 < 0) {
            pCVar7->m_pppMngStArr[0].m_stopRequested = '\0';
            uVar1 = partMng->m_envColorRgba[1];
            uVar2 = partMng->m_envColorRgba[2];
            uVar3 = partMng->m_envColorRgba[3];
            pCVar7->m_pppMngStArr[0].m_envColorR = partMng->m_envColorRgba[0];
            pCVar7->m_pppMngStArr[0].m_envColorG = uVar1;
            pCVar7->m_pppMngStArr[0].m_envColorB = uVar2;
            pCVar7->m_pppMngStArr[0].m_envColorA = uVar3;
            _pppStartPart__FP9_pppMngStPli
                      (p_Var6,partMng->m_pppProgOffsetReconstructionTable
                              [*(int *)((int)partMng->m_recvBuff + iVar8 + 0x30)],1);
            goto LAB_8005ba88;
          }
        }
        pCVar7 = (CPartMng *)pCVar7->m_rgbaA;
        iVar8 = iVar8 + 0x60;
      }
    }
  }
  return;
}

