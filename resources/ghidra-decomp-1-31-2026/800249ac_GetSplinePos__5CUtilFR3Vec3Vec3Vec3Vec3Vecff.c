// Function: GetSplinePos__5CUtilFR3Vec3Vec3Vec3Vec3Vecff
// Entry: 800249ac
// Size: 396 bytes

/* WARNING: Removing unreachable block (ram,0x80024b10) */
/* WARNING: Removing unreachable block (ram,0x80024b08) */
/* WARNING: Removing unreachable block (ram,0x800249c4) */
/* WARNING: Removing unreachable block (ram,0x800249bc) */

void GetSplinePos__5CUtilFR3Vec3Vec3Vec3Vec3Vecff
               (double param_1,double param_2,undefined4 param_3,float *param_4,Vec *param_5,
               Vec *param_6,Vec *param_7,Vec *param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  Vec local_48;
  Vec local_3c;
  
  PSVECSubtract(param_7,param_5,&local_3c);
  PSVECScale((float)param_2,&local_3c,&local_3c);
  PSVECSubtract(param_8,param_6,&local_48);
  PSVECScale((float)param_2,&local_48,&local_48);
  dVar5 = (double)(float)(param_1 * param_1);
  dVar6 = (double)(float)(dVar5 * param_1);
  fVar2 = (float)((double)FLOAT_8032f8b4 * dVar6 + (double)(float)((double)FLOAT_8032f8b0 * dVar5));
  fVar4 = FLOAT_8032f88c +
          (float)((double)FLOAT_8032f8ac * dVar6 - (double)(float)((double)FLOAT_8032f8b0 * dVar5));
  fVar1 = (float)(param_1 + -(double)(float)((double)FLOAT_8032f8ac * dVar5 - dVar6));
  fVar3 = (float)(dVar6 - dVar5);
  *param_4 = fVar3 * local_48.x + fVar1 * local_3c.x + fVar4 * param_6->x + fVar2 * param_7->x;
  param_4[1] = fVar3 * local_48.y + fVar1 * local_3c.y + fVar4 * param_6->y + fVar2 * param_7->y;
  param_4[2] = fVar3 * local_48.z + fVar1 * local_3c.z + fVar4 * param_6->z + fVar2 * param_7->z;
  return;
}

