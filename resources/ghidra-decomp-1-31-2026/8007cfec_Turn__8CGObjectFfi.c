// Function: Turn__8CGObjectFfi
// Entry: 8007cfec
// Size: 248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Turn__8CGObjectFfi(float param_1,CGObject *gObject,float param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xbf | 0x40;
  gObject->m_rotTargetY = param_1;
  dVar4 = (double)DstRot__5CMathFff((double)gObject->m_rotBaseY,(double)gObject->m_rotTargetY,&Math)
  ;
  fVar1 = FLOAT_80330350;
  gObject->m_turnBaseSpeed =
       (float)(dVar4 / (double)(float)((double)CONCAT44(0x43300000,-param_3) - DOUBLE_80330348));
  gObject->m_attackColliders[0].m_localStart.x = param_3;
  fVar2 = FLOAT_80330350;
  if (fVar1 <= gObject->m_turnBaseSpeed) {
    iVar3 = 3;
  }
  else {
    iVar3 = 2;
  }
  gObject->m_currentAnimSlot = gObject->m_animQueue[iVar3 + -0x41];
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfe;
  gObject->m_animExtraIndex = -1;
  gObject->m_collisionPushTimer = -1;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xfd;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7 | 8;
  gObject->m_turnSpeed = fVar2;
  return;
}

