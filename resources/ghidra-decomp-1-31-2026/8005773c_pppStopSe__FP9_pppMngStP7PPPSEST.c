// Function: pppStopSe__FP9_pppMngStP7PPPSEST
// Entry: 8005773c
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

_pppMngSt * pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt *pppMngSt,PPPSEST *pppSest)

{
  if ((-1 < pppSest->m_soundEffectSlot) && (-1 < pppSest->m_soundEffectHandle)) {
    pppMngSt = (_pppMngSt *)
               FadeOutSe3D__6CSoundFii
                         (&Sound,pppSest->m_soundEffectHandle,pppSest->m_soundEffectFadeFrames);
    pppSest->m_soundEffectHandle = -1;
  }
  return pppMngSt;
}

