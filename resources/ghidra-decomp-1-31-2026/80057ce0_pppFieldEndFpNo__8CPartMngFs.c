// Function: pppFieldEndFpNo__8CPartMngFs
// Entry: 80057ce0
// Size: 140 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFieldEndFpNo__8CPartMngFs(CPartMng *partMng,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = partMng->m_pppMngStArr[0].m_baseTime;
    if (((iVar1 != -0x1000) && (partMng->m_pppMngStArr[0].m_kind == 0)) &&
       (partMng->m_pppMngStArr[0].m_nodeIndex == param_2)) {
      if (iVar1 < 0) {
        partMng->m_pppMngStArr[0].m_stopRequested = '\x01';
        pppStopSe__FP9_pppMngStP7PPPSEST
                  (partMng->m_pppMngStArr,&partMng->m_pppMngStArr[0].m_soundEffectData);
      }
      else {
        partMng->m_pppMngStArr[0].m_baseTime = -0x1000;
      }
    }
    iVar2 = iVar2 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar2 < 0x180);
  return;
}

