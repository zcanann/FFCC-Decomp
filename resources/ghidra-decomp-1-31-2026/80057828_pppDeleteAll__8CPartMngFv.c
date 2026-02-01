// Function: pppDeleteAll__8CPartMngFv
// Entry: 80057828
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDeleteAll__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = partMng->m_pppMngStArr[0].m_baseTime;
    if (iVar1 != -0x1000) {
      if (iVar1 < 0) {
        partMng->m_pppMngStArr[0].m_endRequested = '\x01';
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

