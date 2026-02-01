// Function: C_QUATLerp
// Entry: 801872b8
// Size: 100 bytes

void C_QUATLerp(double alpha,Quat *inQuatA,Quat *inQuatB,Quat *outQuat)

{
  outQuat->x = inQuatA->x + (float)(alpha * (double)(inQuatB->x - inQuatA->x));
  outQuat->y = inQuatA->y + (float)(alpha * (double)(inQuatB->y - inQuatA->y));
  outQuat->z = inQuatA->z + (float)(alpha * (double)(inQuatB->z - inQuatA->z));
  outQuat->w = inQuatA->w + (float)(alpha * (double)(inQuatB->w - inQuatA->w));
  return;
}

