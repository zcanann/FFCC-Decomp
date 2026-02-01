// Function: pppEndSlot__8CPartMngFii
// Entry: 80057fac
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEndSlot__8CPartMngFii(CPartMng *partMng,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[0].field_0x100 == param_2)) {
      if ((param_3 == 0) || ((partMng->m_pppMngStArr[0].m_hitParams.m_hitFlags & 1) == 0)) {
        partMng->m_pppMngStArr[0].m_stopRequested = '\x01';
        pppStopSe__FP9_pppMngStP7PPPSEST
                  (partMng->m_pppMngStArr,&partMng->m_pppMngStArr[0].m_soundEffectData);
      }
    }
    iVar1 = iVar1 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar1 < 0x180);
  return;
}

