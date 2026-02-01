// Function: PSQUATNormalize
// Entry: 80186f80
// Size: 84 bytes

/* WARNING: Removing unreachable block (ram,0x80186fcc) */
/* WARNING: Removing unreachable block (ram,0x80186fc8) */
/* WARNING: Removing unreachable block (ram,0x80186f94) */
/* WARNING: Removing unreachable block (ram,0x80186f8c) */

void PSQUATNormalize(Quat *inQuat,Quat *outQuat)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar1 = inQuat->x;
  fVar3 = inQuat->y;
  fVar2 = inQuat->z;
  fVar4 = inQuat->w;
  fVar5 = fVar2 * fVar2 + fVar1 * fVar1 + fVar4 * fVar4 + fVar3 * fVar3;
  fVar6 = 1.0 / SQRT(fVar5);
  fVar6 = -(fVar6 * fVar6 * fVar5 - FLOAT_80333748) * fVar6 * FLOAT_80333744;
  if (fVar5 - FLOAT_80333728 < 0.0) {
    fVar6 = FLOAT_80333728 - FLOAT_80333728;
  }
  outQuat->x = fVar1 * fVar6;
  outQuat->y = fVar3 * fVar6;
  outQuat->z = fVar2 * fVar6;
  outQuat->w = fVar4 * fVar6;
  return;
}

