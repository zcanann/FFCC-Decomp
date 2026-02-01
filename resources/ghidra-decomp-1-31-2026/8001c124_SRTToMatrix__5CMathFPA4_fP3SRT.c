// Function: SRTToMatrix__5CMathFPA4_fP3SRT
// Entry: 8001c124
// Size: 360 bytes

/* WARNING: Removing unreachable block (ram,0x8001c26c) */
/* WARNING: Removing unreachable block (ram,0x8001c264) */
/* WARNING: Removing unreachable block (ram,0x8001c25c) */
/* WARNING: Removing unreachable block (ram,0x8001c254) */
/* WARNING: Removing unreachable block (ram,0x8001c24c) */
/* WARNING: Removing unreachable block (ram,0x8001c154) */
/* WARNING: Removing unreachable block (ram,0x8001c14c) */
/* WARNING: Removing unreachable block (ram,0x8001c144) */
/* WARNING: Removing unreachable block (ram,0x8001c13c) */
/* WARNING: Removing unreachable block (ram,0x8001c134) */

void SRTToMatrix__5CMathFPA4_fP3SRT(undefined4 param_1,Mtx *param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  Mtx local_88;
  
  PSMTXScale(param_3[6],param_3[7],param_3[8],param_2);
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
  local_88.value[1][0] = (float)(dVar3 * dVar2);
  local_88.value[2][0] = (float)-dVar4;
  local_88.value[0][0] = (float)(dVar3 * dVar1);
  local_88.value[0][1] =
       (float)(dVar1 * (double)(float)(dVar6 * dVar4) - (double)(float)(dVar5 * dVar2));
  local_88.value[1][1] =
       (float)(dVar2 * (double)(float)(dVar6 * dVar4) + (double)(float)(dVar5 * dVar1));
  local_88.value[2][1] = (float)(dVar6 * dVar3);
  local_88.value[2][2] = (float)(dVar5 * dVar3);
  local_88.value[0][2] =
       (float)(dVar1 * (double)(float)(dVar5 * dVar4) + (double)(float)(dVar6 * dVar2));
  local_88.value[1][2] =
       (float)(dVar2 * (double)(float)(dVar5 * dVar4) - (double)(float)(dVar6 * dVar1));
  local_88.value[0][3] = *param_3;
  local_88.value[1][3] = param_3[1];
  local_88.value[2][3] = param_3[2];
  PSMTXConcat(&local_88,param_2,param_2);
  return;
}

