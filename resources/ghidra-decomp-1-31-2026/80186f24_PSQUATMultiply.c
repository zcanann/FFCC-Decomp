// Function: PSQUATMultiply
// Entry: 80186f24
// Size: 92 bytes

/* WARNING: Removing unreachable block (ram,0x80186f78) */
/* WARNING: Removing unreachable block (ram,0x80186f70) */
/* WARNING: Removing unreachable block (ram,0x80186f34) */
/* WARNING: Removing unreachable block (ram,0x80186f2c) */
/* WARNING: Removing unreachable block (ram,0x80186f28) */
/* WARNING: Removing unreachable block (ram,0x80186f24) */

void PSQUATMultiply(Quat *inQuatA,Quat *inQuatB,Quat *outQuat)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar1 = inQuatA->x;
  fVar3 = inQuatA->y;
  fVar2 = inQuatA->z;
  fVar4 = inQuatA->w;
  fVar5 = inQuatB->y;
  fVar6 = inQuatB->w;
  fVar7 = fVar3 * inQuatB->z + fVar4 * inQuatB->x;
  fVar8 = fVar4 * inQuatB->z + -fVar3 * inQuatB->x;
  outQuat->x = fVar7 + fVar1 * fVar6 + -fVar2 * fVar5;
  outQuat->y = fVar7 + fVar3 * fVar6 + fVar4 * fVar5;
  outQuat->z = fVar8 - (-fVar2 * fVar6 + -fVar1 * fVar5);
  outQuat->w = fVar8 - (-fVar4 * fVar6 + fVar3 * fVar5);
  return;
}

