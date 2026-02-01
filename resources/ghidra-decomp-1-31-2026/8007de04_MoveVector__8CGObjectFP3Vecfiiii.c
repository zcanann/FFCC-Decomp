// Function: MoveVector__8CGObjectFP3Vecfiiii
// Entry: 8007de04
// Size: 112 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MoveVector__8CGObjectFP3Vecfiiii
               (double param_1,CGObject *gObject,float *param_3,uint32_t param_4,char param_5,
               char param_6,char param_7)

{
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf | 0x20;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xef | 0x10;
  gObject->m_turnFrames = param_4;
  (gObject->m_moveVec).y = *param_3;
  (gObject->m_moveVec).z = param_3[1];
  gObject->m_moveSpeed = param_3[2];
  gObject->m_moveTimer = (int32_t)(float)param_1;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_5 << 3) & 8 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xf7;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_6 << 1) & 2 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       (byte)((int)param_7 << 2) & 4 | *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfb;
  return;
}

