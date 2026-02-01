// Function: pppDeleteSlot__8CPartMngFii
// Entry: 80058030
// Size: 176 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDeleteSlot__8CPartMngFii(CPartMng *partMng,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = partMng->m_pppMngStArr[0].m_baseTime;
    if ((iVar1 != -0x1000) && (*(int *)&partMng->m_pppMngStArr[0].field_0x100 == param_2)) {
      if ((param_3 == 0) || ((partMng->m_pppMngStArr[0].m_hitParams.m_hitFlags & 1) == 0)) {
        if (iVar1 < 0) {
          partMng->m_pppMngStArr[0].m_endRequested = '\x01';
          pppStopSe__FP9_pppMngStP7PPPSEST
                    (partMng->m_pppMngStArr,&partMng->m_pppMngStArr[0].m_soundEffectData);
        }
        else {
          partMng->m_pppMngStArr[0].m_baseTime = -0x1000;
        }
      }
    }
    iVar2 = iVar2 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar2 < 0x180);
  return;
}

