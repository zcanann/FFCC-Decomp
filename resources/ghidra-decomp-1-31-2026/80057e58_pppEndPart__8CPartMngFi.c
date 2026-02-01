// Function: pppEndPart__8CPartMngFi
// Entry: 80057e58
// Size: 60 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEndPart__8CPartMngFi(CPartMng *partMng,int param_2)

{
  _pppMngSt *pppMngSt;
  
  pppMngSt = partMng->m_pppMngStArr + param_2;
  pppMngSt->m_stopRequested = '\x01';
  pppStopSe__FP9_pppMngStP7PPPSEST(pppMngSt,&pppMngSt->m_soundEffectData);
  return;
}

