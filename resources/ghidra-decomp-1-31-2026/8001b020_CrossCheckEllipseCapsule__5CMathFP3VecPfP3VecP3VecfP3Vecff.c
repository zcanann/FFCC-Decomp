// Function: CrossCheckEllipseCapsule__5CMathFP3VecPfP3VecP3VecfP3Vecff
// Entry: 8001b020
// Size: 544 bytes

/* WARNING: Removing unreachable block (ram,0x8001b224) */
/* WARNING: Removing unreachable block (ram,0x8001b21c) */
/* WARNING: Removing unreachable block (ram,0x8001b214) */
/* WARNING: Removing unreachable block (ram,0x8001b20c) */
/* WARNING: Removing unreachable block (ram,0x8001b048) */
/* WARNING: Removing unreachable block (ram,0x8001b040) */
/* WARNING: Removing unreachable block (ram,0x8001b038) */
/* WARNING: Removing unreachable block (ram,0x8001b030) */

void CrossCheckEllipseCapsule__5CMathFP3VecPfP3VecP3VecfP3Vecff
               (float a,float b,float c,float radius,float scale,Mat4x4 *matrix,float *outCoeffs,
               Vec *p0,Vec *p1,Vec *p2,Vec *p3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  Vec VStack_c8;
  Vec local_bc;
  Vec4d local_b0;
  Mat4x4 local_a0;
  
  dVar4 = (double)scale;
  dVar3 = (double)c;
  dVar2 = (double)b;
  fVar1 = radius * radius;
  local_b0.w = fVar1 * radius;
  dVar5 = (double)(float)((double)a + dVar2);
  dVar6 = (double)FLOAT_8032f740;
  local_b0.z = FLOAT_8032f760 * local_b0.w + FLOAT_8032f758 * fVar1;
  local_b0.x = FLOAT_8032f748 + (FLOAT_8032f75c * local_b0.w - FLOAT_8032f758 * fVar1);
  local_b0.y = radius + -(FLOAT_8032f75c * fVar1 - local_b0.w);
  local_b0.w = local_b0.w - fVar1;
  local_a0.value[0][0] = p1->x;
  local_a0.value[1][0] = p1->y;
  local_a0.value[2][0] = p1->z;
  local_a0.value[3][0] = FLOAT_8032f748;
  local_a0.value[0][2] = p2->x;
  local_a0.value[1][2] = p2->y;
  local_a0.value[2][2] = p2->z;
  local_a0.value[3][2] = FLOAT_8032f748;
  if (dVar6 != dVar5) {
    dVar6 = (double)(float)((double)a / dVar5);
  }
  PSVECSubtract(p2,p1,&local_bc);
  PSVECSubtract(p1,p0,&VStack_c8);
  PSVECAdd(&local_bc,&VStack_c8,&local_bc);
  PSVECScale((float)(dVar6 * dVar4),&local_bc,&local_bc);
  dVar5 = (double)FLOAT_8032f740;
  local_a0.value[0][1] = local_bc.x;
  local_a0.value[1][1] = local_bc.y;
  local_a0.value[2][1] = local_bc.z;
  local_a0.value[3][1] = FLOAT_8032f748;
  if (dVar5 != (double)(float)(dVar2 + dVar3)) {
    dVar5 = (double)(float)(dVar2 / (double)(float)(dVar2 + dVar3));
  }
  PSVECSubtract(p3,p2,&local_bc);
  PSVECSubtract(p2,p1,&VStack_c8);
  PSVECAdd(&local_bc,&VStack_c8,&local_bc);
  PSVECScale((float)(dVar5 * dVar4),&local_bc,&local_bc);
  local_a0.value[0][3] = local_bc.x;
  local_a0.value[1][3] = local_bc.y;
  local_a0.value[2][3] = local_bc.z;
  local_a0.value[3][3] = FLOAT_8032f748;
  MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(matrix,&local_a0,&local_b0,&local_b0);
  *outCoeffs = local_b0.x;
  outCoeffs[1] = local_b0.y;
  outCoeffs[2] = local_b0.z;
  return;
}

