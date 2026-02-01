// Function: moveVectorRot__8CGObjectFfffi
// Entry: 8007dae8
// Size: 316 bytes

/* WARNING: Removing unreachable block (ram,0x8007dc04) */
/* WARNING: Removing unreachable block (ram,0x8007dbfc) */
/* WARNING: Removing unreachable block (ram,0x8007dbf4) */
/* WARNING: Removing unreachable block (ram,0x8007dbec) */
/* WARNING: Removing unreachable block (ram,0x8007dbe4) */
/* WARNING: Removing unreachable block (ram,0x8007dbdc) */
/* WARNING: Removing unreachable block (ram,0x8007db20) */
/* WARNING: Removing unreachable block (ram,0x8007db18) */
/* WARNING: Removing unreachable block (ram,0x8007db10) */
/* WARNING: Removing unreachable block (ram,0x8007db08) */
/* WARNING: Removing unreachable block (ram,0x8007db00) */
/* WARNING: Removing unreachable block (ram,0x8007daf8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveVectorRot__8CGObjectFfffi
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
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xf7 | 8;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfd;
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfb | 4;
  return;
}

