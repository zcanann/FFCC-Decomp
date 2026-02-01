// Function: C_QUATRotAxisRad
// Entry: 80186fd4
// Size: 140 bytes

void C_QUATRotAxisRad(double inRad,Quat *outQuat,Vec *inVec)

{
  double dVar1;
  double dVar2;
  Vec local_24;
  
  PSVECNormalize(inVec,&local_24);
  dVar2 = (double)(float)((double)FLOAT_80333744 * inRad);
  dVar1 = (double)sinf(dVar2);
  dVar2 = (double)cosf(dVar2);
  outQuat->x = (float)(dVar1 * (double)local_24.x);
  outQuat->y = (float)(dVar1 * (double)local_24.y);
  outQuat->z = (float)(dVar1 * (double)local_24.z);
  outQuat->w = (float)dVar2;
  return;
}

