// Function: C_QUATSlerp
// Entry: 8018731c
// Size: 372 bytes

void C_QUATSlerp(double alpha,Quat *inQuatA,Quat *inQuatB,Quat *outQuat)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = (double)FLOAT_80333740;
  fVar1 = inQuatA->w * inQuatB->w +
          inQuatA->z * inQuatB->z + inQuatA->x * inQuatB->x + inQuatA->y * inQuatB->y;
  if (fVar1 < FLOAT_8033372c) {
    fVar1 = -fVar1;
    dVar5 = -dVar5;
  }
  if (FLOAT_8033374c < fVar1) {
    dVar5 = dVar5 * alpha;
    dVar4 = (double)(float)((double)FLOAT_80333740 - alpha);
  }
  else {
    dVar2 = (double)acosf();
    dVar3 = (double)sinf();
    dVar4 = (double)sinf((double)(float)((double)(float)((double)FLOAT_80333740 - alpha) * dVar2));
    dVar4 = (double)(float)(dVar4 / dVar3);
    dVar2 = (double)sinf((double)(float)(alpha * dVar2));
    dVar5 = dVar5 * (double)(float)(dVar2 / dVar3);
  }
  fVar1 = (float)dVar5;
  outQuat->x = (float)(dVar4 * (double)inQuatA->x) + fVar1 * inQuatB->x;
  outQuat->y = (float)(dVar4 * (double)inQuatA->y) + fVar1 * inQuatB->y;
  outQuat->z = (float)(dVar4 * (double)inQuatA->z) + fVar1 * inQuatB->z;
  outQuat->w = (float)(dVar4 * (double)inQuatA->w) + fVar1 * inQuatB->w;
  return;
}

