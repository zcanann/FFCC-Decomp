// Function: DstRot__5CMathFff
// Entry: 8001a2f8
// Size: 236 bytes

/* WARNING: Removing unreachable block (ram,0x8001a3cc) */
/* WARNING: Removing unreachable block (ram,0x8001a3c4) */
/* WARNING: Removing unreachable block (ram,0x8001a3bc) */
/* WARNING: Removing unreachable block (ram,0x8001a3b4) */
/* WARNING: Removing unreachable block (ram,0x8001a320) */
/* WARNING: Removing unreachable block (ram,0x8001a318) */
/* WARNING: Removing unreachable block (ram,0x8001a310) */
/* WARNING: Removing unreachable block (ram,0x8001a308) */

double DstRot__5CMathFff(undefined8 param_1,undefined8 param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar1 = (double)sin();
  dVar6 = (double)(float)dVar1;
  dVar1 = (double)cos(param_1);
  dVar5 = (double)(float)dVar1;
  dVar1 = (double)sin(param_2);
  dVar4 = (double)(float)dVar1;
  dVar1 = (double)cos(param_2);
  dVar3 = (double)(float)dVar1;
  dVar2 = (double)FLOAT_8032f740;
  dVar1 = (double)(float)(dVar6 * dVar4 + (double)(float)(dVar5 * dVar3));
  if (dVar2 != dVar1) {
    dVar2 = (double)FLOAT_8032f744;
    if ((dVar2 <= dVar1) && (dVar2 = dVar1, (double)FLOAT_8032f748 < dVar1)) {
      dVar2 = (double)FLOAT_8032f748;
    }
    dVar1 = (double)acos(dVar2);
    dVar2 = (double)(float)dVar1;
    if ((float)(dVar6 * dVar3 - (double)(float)(dVar4 * dVar5)) < FLOAT_8032f740) {
      dVar2 = -dVar2;
    }
  }
  return dVar2;
}

