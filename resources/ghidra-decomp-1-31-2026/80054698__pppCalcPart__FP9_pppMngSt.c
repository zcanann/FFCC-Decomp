// Function: _pppCalcPart__FP9_pppMngSt
// Entry: 80054698
// Size: 340 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _pppCalcPart__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  uint uVar1;
  int32_t iVar2;
  int iVar3;
  int iVar4;
  _pppPDataVal *pppPDataVal;
  int iVar5;
  Vec local_28;
  
  iVar4 = (pppMngSt->m_soundEffectData).m_soundEffectSlot;
  pppMngStPtr = pppMngSt;
  if (((-1 < iVar4) &&
      ((pppMngSt->m_soundEffectData).m_soundEffectStartFrame <= pppMngSt->m_currentFrame)) &&
     ((pppMngSt->m_soundEffectData).m_soundEffectStopFlag == '\0')) {
    local_28.x = (pppMngSt->m_matrix).value[0][3];
    local_28.y = (pppMngSt->m_matrix).value[1][3];
    local_28.z = (pppMngSt->m_matrix).value[2][3];
    iVar5 = (pppMngSt->m_soundEffectData).m_soundEffectHandle;
    if (iVar5 < 0) {
      if ((pppMngSt->m_soundEffectData).m_soundEffectStartedOnce == '\0') {
        uVar1 = (uint)(pppMngSt->m_soundEffectData).m_soundEffectKind;
        iVar2 = PlaySe3D__6CSoundFiP3Vecffi
                          ((double)PartMng.m_pppEnvSt.m_soundVolumeTable[uVar1 - 3],
                           (double)PartMng.m_pppEnvSt.m_soundPitchTable[uVar1 - 3],&Sound,iVar4,
                           &local_28,0);
        (pppMngSt->m_soundEffectData).m_soundEffectHandle = iVar2;
        (pppMngSt->m_soundEffectData).m_soundEffectStartedOnce = '\x01';
      }
    }
    else {
      ChangeSe3DPos__6CSoundFiP3Vec(&Sound,iVar5,&local_28);
    }
  }
  iVar4 = 0;
  for (iVar5 = 0; iVar5 < pppMngSt->m_numPrograms; iVar5 = iVar5 + 1) {
    pppPDataVal = (_pppPDataVal *)((int)&pppMngSt->m_pppPDataVals->m_pppProgramSetDef + iVar4);
    if (((pppMngSt->m_pppPDataVals != (_pppPDataVal *)0x0) && (pppPDataVal != (_pppPDataVal *)0x0))
       && (pppPDataVal->m_nextSpawnTime <= pppMngSt->m_currentFrame)) {
      pppPDataVal->m_nextSpawnTime = 0x7fffffff;
      iVar3 = pppCreatePObject__FP9_pppMngStP12_pppPDataVal(pppMngSt,pppPDataVal);
      if (iVar3 == 0) break;
      *(undefined *)(iVar3 + 0x7c) = 0;
    }
    iVar4 = iVar4 + 0x10;
  }
  pppCalcPartStd__FP9_pppMngSt(pppMngSt);
  return;
}

