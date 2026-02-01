// Function: onAlphaUpdate__10CGCharaObjFv
// Entry: 801120c0
// Size: 296 bytes

/* WARNING: Removing unreachable block (ram,0x801121cc) */
/* WARNING: Removing unreachable block (ram,0x801120d0) */

double onAlphaUpdate__10CGCharaObjFv(int param_1)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)*(float *)(param_1 + 0x694);
  if ((*(short *)(*(int *)(param_1 + 0x58) + 0x1c) != 0) &&
     (((uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(), (uVar1 & 0x6d) == 0x6d &&
       (*(short *)(*(int *)(param_1 + 0x58) + 0x1c) == 0)) ||
      ((uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), (uVar1 & 0xad) == 0xad &&
       (((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 1) != 0 &&
        (*(char *)(param_1 + 0x6ba) == '\0')))))))) {
    dVar2 = (double)sin((double)(FLOAT_803319b0 *
                                (float)((double)CONCAT44(0x43300000,
                                                         *(uint *)(param_1 + 0x54c) ^ 0x80000000) -
                                       DOUBLE_80331968)));
    dVar3 = (double)(float)(dVar3 + (double)(FLOAT_803319b4 * (float)dVar2));
  }
  dVar2 = (double)FLOAT_80331988;
  if ((dVar2 <= dVar3) && (dVar2 = dVar3, (double)FLOAT_80331964 < dVar3)) {
    dVar2 = (double)FLOAT_80331964;
  }
  return (double)(float)((double)*(float *)(param_1 + 0x4b4) * dVar2);
}

