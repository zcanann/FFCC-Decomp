// Function: __ct__14PPPCREATEPARAMFv
// Entry: 800b9538
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __ct__14PPPCREATEPARAMFv(PPPCREATEPARAM *pppCreateParam)

{
  float fVar1;
  
  (pppCreateParam->m_soundEffectParams).m_soundEffectHandle = -1;
  fVar1 = FLOAT_80330b34;
  (pppCreateParam->m_soundEffectParams).m_soundEffectSlot = -1;
  (pppCreateParam->m_soundEffectParams).m_soundEffectStopFlag = '\0';
  (pppCreateParam->m_soundEffectParams).m_soundEffectKind = '\x01';
  (pppCreateParam->m_soundEffectParams).m_soundEffectStartFrame = 0;
  (pppCreateParam->m_soundEffectParams).m_soundEffectStartedOnce = '\0';
  (pppCreateParam->m_soundEffectParams).m_soundEffectFadeFrames = 0x1e;
  pppCreateParam->m_hitParamA = 0;
  pppCreateParam->m_hitParamB = 0;
  pppCreateParam->m_hitObjectCount = '\0';
  pppCreateParam->m_hitFlags = '\0';
  pppCreateParam->m_positionOffsetPtr = (Vec *)0x0;
  pppCreateParam->m_rotationPtr = (Vec *)0x0;
  pppCreateParam->m_scalePtr = (Vec *)0x0;
  pppCreateParam->m_extraPositionPtr = (Vec *)0x0;
  pppCreateParam->m_paramA = 0;
  pppCreateParam->m_paramB = (CGObject *)0x0;
  pppCreateParam->m_lookTargetPtr = (CGObject *)0x0;
  pppCreateParam->m_objectHitMask = 0;
  pppCreateParam->m_cylinderAttribute = 0;
  pppCreateParam->m_paramC = fVar1;
  pppCreateParam->m_paramD = fVar1;
  *(undefined *)&pppCreateParam->m_owner = 0;
  return;
}

