// Function: __sinit_partMng_cpp
// Entry: 8005f624
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __sinit_partMng_cpp(void)

{
  __construct_array(PartMng.m_pppMngStArr,__ct__9_pppMngStFv,0,0x158,0x180);
  g_dcp.m_soundEffectParams.m_soundEffectHandle = -1;
  g_dcp.m_soundEffectParams.m_soundEffectSlot = -1;
  g_dcp.m_soundEffectParams.m_soundEffectStopFlag = '\0';
  g_dcp.m_soundEffectParams.m_soundEffectKind = '\x01';
  g_dcp.m_soundEffectParams.m_soundEffectStartFrame = 0;
  g_dcp.m_soundEffectParams.m_soundEffectStartedOnce = '\0';
  g_dcp.m_soundEffectParams.m_soundEffectFadeFrames = 0x1e;
  g_dcp.m_hitParamA = 0;
  g_dcp.m_hitParamB = 0;
  g_dcp.m_hitObjectCount = '\0';
  g_dcp.m_hitFlags = '\0';
  g_dcp.m_positionOffsetPtr = (Vec *)0x0;
  g_dcp.m_rotationPtr = (Vec *)0x0;
  g_dcp.m_scalePtr = (Vec *)0x0;
  g_dcp.m_extraPositionPtr = (Vec *)0x0;
  g_dcp.m_paramA = 0;
  g_dcp.m_paramB = (CGObject *)0x0;
  g_dcp.m_lookTargetPtr = (CGObject *)0x0;
  g_dcp.m_objectHitMask = 0;
  g_dcp.m_cylinderAttribute = 0;
  g_dcp.m_paramC = FLOAT_8032fe18;
  g_dcp.m_paramD = FLOAT_8032fe18;
  g_dcp.m_owner._0_1_ = 0;
  return;
}

