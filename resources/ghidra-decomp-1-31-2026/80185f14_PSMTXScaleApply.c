// Function: PSMTXScaleApply
// Entry: 80185f14
// Size: 88 bytes

/* WARNING: Removing unreachable block (ram,0x80185f64) */
/* WARNING: Removing unreachable block (ram,0x80185f60) */
/* WARNING: Removing unreachable block (ram,0x80185f5c) */
/* WARNING: Removing unreachable block (ram,0x80185f54) */
/* WARNING: Removing unreachable block (ram,0x80185f4c) */
/* WARNING: Removing unreachable block (ram,0x80185f48) */
/* WARNING: Removing unreachable block (ram,0x80185f40) */
/* WARNING: Removing unreachable block (ram,0x80185f3c) */
/* WARNING: Removing unreachable block (ram,0x80185f34) */
/* WARNING: Removing unreachable block (ram,0x80185f2c) */
/* WARNING: Removing unreachable block (ram,0x80185f20) */
/* WARNING: Removing unreachable block (ram,0x80185f18) */

void PSMTXScaleApply(float xS,float yS,float zS,Mtx *source,Mtx *dest)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  fVar5 = source->value[0][1];
  fVar1 = source->value[0][2];
  fVar6 = source->value[0][3];
  fVar2 = source->value[1][0];
  fVar7 = source->value[1][1];
  fVar3 = source->value[1][2];
  fVar8 = source->value[1][3];
  fVar4 = source->value[2][0];
  fVar9 = source->value[2][1];
  dest->value[0][0] = source->value[0][0] * xS;
  dest->value[0][1] = fVar5 * xS;
  fVar5 = source->value[2][2];
  fVar10 = source->value[2][3];
  dest->value[0][2] = fVar1 * xS;
  dest->value[0][3] = fVar6 * xS;
  dest->value[1][0] = fVar2 * yS;
  dest->value[1][1] = fVar7 * yS;
  dest->value[1][2] = fVar3 * yS;
  dest->value[1][3] = fVar8 * yS;
  dest->value[2][0] = fVar4 * zS;
  dest->value[2][1] = fVar9 * zS;
  dest->value[2][2] = fVar5 * zS;
  dest->value[2][3] = fVar10 * zS;
  return;
}

