// Function: moveVectorHRot__8CGObjectFfffi
// Entry: 8007d9ac
// Size: 316 bytes

/* WARNING: Removing unreachable block (ram,0x8007dac8) */
/* WARNING: Removing unreachable block (ram,0x8007dac0) */
/* WARNING: Removing unreachable block (ram,0x8007dab8) */
/* WARNING: Removing unreachable block (ram,0x8007dab0) */
/* WARNING: Removing unreachable block (ram,0x8007daa8) */
/* WARNING: Removing unreachable block (ram,0x8007daa0) */
/* WARNING: Removing unreachable block (ram,0x8007d9e4) */
/* WARNING: Removing unreachable block (ram,0x8007d9dc) */
/* WARNING: Removing unreachable block (ram,0x8007d9d4) */
/* WARNING: Removing unreachable block (ram,0x8007d9cc) */
/* WARNING: Removing unreachable block (ram,0x8007d9c4) */
/* WARNING: Removing unreachable block (ram,0x8007d9bc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveVectorHRot__8CGObjectFfffi
               (undefined8 param_1,undefined8 param_2,double param_3,CGObject *gObject,
               uint32_t param_5)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  dVar1 = (double)cos(param_2);
  dVar5 = (double)(float)dVar1;
  dVar1 = (double)sin(param_1);
  dVar4 = (double)(float)dVar1;
  dVar1 = (double)sin(param_2);
  dVar3 = (double)(float)dVar1;
  dVar1 = (double)cos(param_2);
  dVar2 = (double)(float)dVar1;
  dVar1 = (double)cos(param_1);
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf | 0x20;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xef | 0x10;
  gObject->m_turnFrames = param_5;
  (gObject->m_moveVec).y = (float)(dVar4 * dVar5);
  (gObject->m_moveVec).z = (float)dVar3;
  gObject->m_moveSpeed = (float)((double)(float)dVar1 * dVar2);
  gObject->m_moveTimer = (int32_t)(float)param_3;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xf7;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfb;
  return;
}

