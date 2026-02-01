// Function: PlayAnim__8CGObjectFiiiiiPSc
// Entry: 8007c700
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void PlayAnim__8CGObjectFiiiiiPSc
               (CGObject *gObject,int param_2,byte param_3,char param_4,int16_t param_5,
               int16_t param_6,int param_7)

{
  float fVar1;
  
  gObject->m_currentAnimSlot = gObject->m_animQueue[param_2 + -0x41];
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       param_3 & 1 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfe;
  gObject->m_animExtraIndex = param_5;
  gObject->m_collisionPushTimer = param_6;
  *(byte *)&gObject->m_shieldNodeFlags =
       (byte)((int)param_4 << 1) & 2 | *(byte *)&gObject->m_shieldNodeFlags & 0xfd;
  if (param_7 == 0) {
    *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
  }
  else {
    *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f | 0x80;
    gObject->m_animQueuePos = '\0';
    memcpy(gObject->m_animQueue,param_7,4);
  }
  fVar1 = FLOAT_80330350;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7 | 8;
  gObject->m_turnSpeed = fVar1;
  return;
}

