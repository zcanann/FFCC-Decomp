// Function: SRTToMatrixRT__5CMathFPA4_fP3SRT
// Entry: 8001bfe0
// Size: 324 bytes

/* WARNING: Removing unreachable block (ram,0x8001c104) */
/* WARNING: Removing unreachable block (ram,0x8001c0fc) */
/* WARNING: Removing unreachable block (ram,0x8001c0f4) */
/* WARNING: Removing unreachable block (ram,0x8001c0ec) */
/* WARNING: Removing unreachable block (ram,0x8001c0e4) */
/* WARNING: Removing unreachable block (ram,0x8001c010) */
/* WARNING: Removing unreachable block (ram,0x8001c008) */
/* WARNING: Removing unreachable block (ram,0x8001c000) */
/* WARNING: Removing unreachable block (ram,0x8001bff8) */
/* WARNING: Removing unreachable block (ram,0x8001bff0) */

void SRTToMatrixRT__5CMathFPA4_fP3SRT(undefined4 param_1,float *param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar1 = (double)sin((double)param_3[3]);
  dVar6 = (double)(float)dVar1;
  dVar1 = (double)cos((double)param_3[3]);
  dVar5 = (double)(float)dVar1;
  dVar1 = (double)sin((double)param_3[4]);
  dVar4 = (double)(float)dVar1;
  dVar1 = (double)cos((double)param_3[4]);
  dVar3 = (double)(float)dVar1;
  dVar1 = (double)sin((double)param_3[5]);
  dVar2 = (double)(float)dVar1;
  dVar1 = (double)cos((double)param_3[5]);
  dVar1 = (double)(float)dVar1;
  *param_2 = (float)(dVar3 * dVar1);
  param_2[4] = (float)(dVar3 * dVar2);
  param_2[8] = (float)-dVar4;
  param_2[1] = (float)(dVar1 * (double)(float)(dVar6 * dVar4) - (double)(float)(dVar5 * dVar2));
  param_2[5] = (float)(dVar2 * (double)(float)(dVar6 * dVar4) + (double)(float)(dVar5 * dVar1));
  param_2[9] = (float)(dVar6 * dVar3);
  param_2[2] = (float)(dVar1 * (double)(float)(dVar5 * dVar4) + (double)(float)(dVar6 * dVar2));
  param_2[6] = (float)(dVar2 * (double)(float)(dVar5 * dVar4) - (double)(float)(dVar6 * dVar1));
  param_2[10] = (float)(dVar5 * dVar3);
  param_2[3] = *param_3;
  param_2[7] = param_3[1];
  param_2[0xb] = param_3[2];
  return;
}

