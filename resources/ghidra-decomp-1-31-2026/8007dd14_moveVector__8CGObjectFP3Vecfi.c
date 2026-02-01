// Function: moveVector__8CGObjectFP3Vecfi
// Entry: 8007dd14
// Size: 240 bytes

/* WARNING: Removing unreachable block (ram,0x8007dde0) */
/* WARNING: Removing unreachable block (ram,0x8007dd24) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveVector__8CGObjectFP3Vecfi(double param_1,CGObject *gObject,Vec *param_3,uint32_t param_4)

{
  double dVar1;
  Vec local_38 [2];
  
  dVar1 = (double)PSVECMag(param_3);
  if ((double)FLOAT_80330350 == dVar1) {
    local_38[0].x = FLOAT_80330350;
    local_38[0].y = FLOAT_80330350;
    local_38[0].z = FLOAT_80330350;
  }
  else {
    PSVECScale((float)((double)FLOAT_80330338 / dVar1),param_3,local_38);
  }
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf | 0x20;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xef | 0x10;
  gObject->m_turnFrames = param_4;
  (gObject->m_moveVec).y = local_38[0].x;
  (gObject->m_moveVec).z = local_38[0].y;
  gObject->m_moveSpeed = local_38[0].z;
  gObject->m_moveTimer = (int32_t)(float)param_1;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xf7 | 8;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfb | 4;
  return;
}

