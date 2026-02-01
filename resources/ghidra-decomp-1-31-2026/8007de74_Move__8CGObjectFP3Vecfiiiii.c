// Function: Move__8CGObjectFP3Vecfiiiii
// Entry: 8007de74
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Move__8CGObjectFP3Vecfiiiii
               (double param_1,CGObject *gObject,float *param_3,uint32_t param_4,char param_5,
               char param_6,char param_7,char param_8)

{
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf | 0x20;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xef;
  gObject->m_turnFrames = param_4;
  (gObject->m_moveVec).y = *param_3;
  (gObject->m_moveVec).z = param_3[1];
  gObject->m_moveSpeed = param_3[2];
  gObject->m_moveTimer = (int32_t)(float)param_1;
  *(byte *)&gObject->m_weaponNodeFlags =
       (byte)((int)param_5 << 1) & 2 | *(byte *)&gObject->m_weaponNodeFlags & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_6 << 3) & 8 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xf7;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_7 << 1) & 2 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_8 << 2) & 4 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfb;
  return;
}

