// Function: Set__4CMesFPci
// Entry: 8009b168
// Size: 436 bytes

/* WARNING: Removing unreachable block (ram,0x8009b2f8) */
/* WARNING: Removing unreachable block (ram,0x8009b178) */

void Set__4CMesFPci(int param_1,int param_2,undefined4 param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  undefined auStack_78 [92];
  
  fVar2 = FLOAT_8033089c;
  fVar1 = FLOAT_80330898;
  *(int *)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 0x3c74) = 0;
  *(float *)(param_1 + 0x3ca8) = fVar2;
  *(float *)(param_1 + 0x3ca4) = fVar2;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x3c10) = 0;
  *(undefined4 *)(param_1 + 0x3c0c) = 0;
  *(undefined4 *)(param_1 + 0x3d10) = 0;
  *(undefined4 *)(param_1 + 0x3d30) = param_3;
  *(float *)(param_1 + 0x3d3c) = fVar2;
  *(undefined4 *)(param_1 + 0x3d40) = 0;
  *(float *)(param_1 + 0x3d44) = fVar1;
  *(float *)(param_1 + 0x3d48) = fVar1;
  *(undefined4 *)(param_1 + 0x3d4c) = 1;
  if (param_2 != 0) {
    memcpy(auStack_78,param_1 + 0x3cc0,0x50);
    dVar5 = (double)FLOAT_8033089c;
    while (*(int *)(param_1 + 0x3c74) == 0) {
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0x3c10) = 0;
      *(undefined4 *)(param_1 + 0x3c0c) = 0;
      *(float *)(param_1 + 0x3c88) = (float)dVar5;
      *(float *)(param_1 + 0x3c84) = (float)dVar5;
      *(float *)(param_1 + 0x3c90) = (float)dVar5;
      *(float *)(param_1 + 0x3c8c) = (float)dVar5;
      addString__4CMesFPPci(param_1,param_1 + 4,1);
      fVar1 = *(float *)(param_1 + 0x3c8c);
      if (fVar1 < *(float *)(param_1 + 0x3ca4)) {
        fVar1 = *(float *)(param_1 + 0x3ca4);
      }
      *(float *)(param_1 + 0x3ca4) = fVar1;
      fVar1 = *(float *)(param_1 + 0x3c90);
      if (fVar1 < *(float *)(param_1 + 0x3ca8)) {
        fVar1 = *(float *)(param_1 + 0x3ca8);
      }
      *(float *)(param_1 + 0x3ca8) = fVar1;
    }
    memcpy((void *)(param_1 + 0x3cc0),auStack_78,0x50);
    fVar3 = FLOAT_803308a4;
    fVar2 = FLOAT_8033089c;
    fVar1 = FLOAT_80330898;
    uVar4 = countLeadingZeros(param_3);
    *(float *)(param_1 + 0x3ca4) = *(float *)(param_1 + 0x3ca4) - *(float *)(param_1 + 0x3d3c);
    *(float *)(param_1 + 0x3ca8) = *(float *)(param_1 + 0x3ca8) - fVar3;
    *(int *)(param_1 + 4) = param_2;
    *(undefined4 *)(param_1 + 0x3c74) = 0;
    *(uint *)(param_1 + 0x3cb0) = uVar4 >> 5;
    *(undefined4 *)(param_1 + 0x3cb4) = 3;
    *(undefined4 *)(param_1 + 0x3cb8) = 0;
    *(undefined4 *)(param_1 + 0x3d10) = 0;
    *(undefined4 *)(param_1 + 0x3d2c) = 0;
    *(undefined4 *)(param_1 + 0x3d28) = 7;
    *(float *)(param_1 + 0x3d3c) = fVar2;
    *(undefined4 *)(param_1 + 0x3d40) = 0;
    *(float *)(param_1 + 0x3d44) = fVar1;
    *(float *)(param_1 + 0x3d48) = fVar1;
    *(undefined4 *)(param_1 + 0x3d4c) = 1;
    Next__4CMesFv(param_1);
  }
  return;
}

