// Function: pppDumpCacheIdx__8CPartMngFv
// Entry: 8005a6c0
// Size: 512 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDumpCacheIdx__8CPartMngFv(CPartMng *partMng)

{
  uint8_t uVar1;
  uint8_t uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  _pppMngSt *pppMngSt;
  int iVar6;
  
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&ppvScreenMatrix);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&ppvCameraMatrix0);
  uVar2 = Game.game.m_gameWork.m_gamePaused;
  iVar6 = 0;
  FLOAT_8032ed58 = ppvScreenMatrix.value[2][0];
  FLOAT_8032ed5c = ppvScreenMatrix.value[2][1];
  FLOAT_8032ed60 = ppvScreenMatrix.value[2][3];
  do {
    pppMngSt = partMng->m_pppMngStArr;
    if ((((uVar2 == '\0') ||
         ((uVar1 = partMng->m_pppMngStArr[0].m_drawMode, '\x05' < (char)uVar1 &&
          ((char)uVar1 < '\b')))) && (partMng->m_pppMngStArr[0].m_baseTime != -0x1000)) &&
       (pppMngStPtr = pppMngSt, partMng->m_pppMngStArr[0].m_endRequested == '\0')) {
      pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
      iVar3 = partMng->m_pppMngStArr[0].m_baseTime;
      if (-1 < iVar3) {
        iVar3 = iVar3 + -1;
        partMng->m_pppMngStArr[0].m_baseTime = iVar3;
        if (-1 < iVar3) goto LAB_8005a89c;
                    /* WARNING: Load size is inaccurate */
        puVar5 = (undefined2 *)
                 (*(int *)(*pppMngSt->m_pppResSet + 0x10) +
                 partMng->m_pppMngStArr[0].m_partIndex * 8);
        iVar3 = IsEnable__13CAmemCacheSetFs((CAmemCacheSet *)CAMemCacheSet,*puVar5);
        if (iVar3 == 0) {
          uVar4 = GetData__13CAmemCacheSetFsPci
                            ((CAmemCacheSet *)CAMemCacheSet,*puVar5,s_partMng_cpp_801d8230,0x9a9);
          *(undefined4 *)(puVar5 + 2) = uVar4;
          pppInitPdt__FPlP7pppProg(*(long **)(puVar5 + 2),pppSysProgTbl.m_progs);
        }
        AddRef__13CAmemCacheSetFs((CAmemCacheSet *)CAMemCacheSet,*puVar5);
        partMng->m_pppMngStArr[0].m_hasMapRef = '\x01';
        _pppStartPart__FP9_pppMngStPli(pppMngSt,*(long **)(puVar5 + 2),1);
      }
      pppSetMatrix__FP9_pppMngSt(pppMngSt);
      pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
      partMng->m_pppMngStArr[0].m_spawnedCount =
           partMng->m_pppMngStArr[0].m_spawnedCount + *(int *)&partMng->m_pppMngStArr[0].m_envColorR
      ;
      DAT_8032ed79 = 0;
      while (0xfff < partMng->m_pppMngStArr[0].m_spawnedCount) {
        _pppCalcPart__FP9_pppMngSt(pppMngSt);
        _pppDeadPart__FP9_pppMngSt(pppMngSt);
        if (partMng->m_pppMngStArr[0].field37_0xe6 != '\0') break;
        DAT_8032ed79 = 1;
        partMng->m_pppMngStArr[0].m_spawnedCount =
             partMng->m_pppMngStArr[0].m_spawnedCount + -0x1000;
      }
      DAT_8032ed79 = 0;
    }
LAB_8005a89c:
    iVar6 = iVar6 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
    if (0x17f < iVar6) {
      return;
    }
  } while( true );
}

