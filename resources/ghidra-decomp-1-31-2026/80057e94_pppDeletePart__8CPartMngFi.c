// Function: pppDeletePart__8CPartMngFi
// Entry: 80057e94
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDeletePart__8CPartMngFi(CPartMng *partMng,int param_2)

{
  _pppMngSt *pppMngSt;
  
  pppMngSt = partMng->m_pppMngStArr + param_2;
  if (pppMngSt->m_baseTime < 0) {
    pppMngSt->m_endRequested = '\x01';
    pppStopSe__FP9_pppMngStP7PPPSEST(pppMngSt,&pppMngSt->m_soundEffectData);
  }
  else {
    pppMngSt->m_baseTime = -0x1000;
  }
  return;
}

