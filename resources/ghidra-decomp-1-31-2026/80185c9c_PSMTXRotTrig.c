// Function: PSMTXRotTrig
// Entry: 80185c9c
// Size: 176 bytes

/* WARNING: Removing unreachable block (ram,0x80185cf0) */
/* WARNING: Removing unreachable block (ram,0x80185cec) */
/* WARNING: Removing unreachable block (ram,0x80185ce8) */
/* WARNING: Removing unreachable block (ram,0x80185ce4) */
/* WARNING: Removing unreachable block (ram,0x80185cdc) */
/* WARNING: Removing unreachable block (ram,0x80185cd4) */
/* WARNING: Removing unreachable block (ram,0x80185cd0) */
/* WARNING: Removing unreachable block (ram,0x80185d44) */
/* WARNING: Removing unreachable block (ram,0x80185d40) */
/* WARNING: Removing unreachable block (ram,0x80185d3c) */
/* WARNING: Removing unreachable block (ram,0x80185d34) */
/* WARNING: Removing unreachable block (ram,0x80185d30) */
/* WARNING: Removing unreachable block (ram,0x80185d24) */
/* WARNING: Removing unreachable block (ram,0x80185d1c) */
/* WARNING: Removing unreachable block (ram,0x80185d18) */
/* WARNING: Removing unreachable block (ram,0x80185d14) */
/* WARNING: Removing unreachable block (ram,0x80185d10) */
/* WARNING: Removing unreachable block (ram,0x80185d04) */
/* WARNING: Removing unreachable block (ram,0x80185d00) */

void PSMTXRotTrig(float sinA,float cosA,Mtx *destination,uint axis)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_803336e4;
  fVar1 = FLOAT_803336e0;
  uVar3 = axis | 0x20;
  if (uVar3 == 0x78) {
    destination->value[0][0] = FLOAT_803336e0;
    destination->value[0][1] = fVar2;
    destination->value[0][2] = fVar2;
    destination->value[0][3] = fVar2;
    destination->value[1][0] = fVar2;
    destination->value[1][3] = fVar2;
    destination->value[2][0] = fVar2;
    destination->value[2][3] = fVar2;
    destination->value[2][1] = sinA;
    destination->value[2][2] = cosA;
    destination->value[1][1] = cosA;
    destination->value[1][2] = -sinA;
  }
  else if (uVar3 == 0x79) {
    destination->value[1][2] = FLOAT_803336e4;
    destination->value[1][3] = fVar2;
    destination->value[0][0] = cosA;
    destination->value[0][1] = fVar2;
    destination->value[2][2] = cosA;
    destination->value[2][3] = fVar2;
    destination->value[1][0] = fVar2;
    destination->value[1][1] = fVar2;
    destination->value[0][2] = sinA;
    destination->value[0][3] = sinA;
    destination->value[2][0] = -sinA;
    destination->value[2][1] = fVar2;
  }
  else if (uVar3 == 0x7a) {
    destination->value[0][2] = FLOAT_803336e4;
    destination->value[0][3] = fVar2;
    destination->value[1][2] = fVar2;
    destination->value[1][3] = fVar2;
    destination->value[2][0] = fVar2;
    destination->value[2][1] = fVar2;
    destination->value[1][0] = sinA;
    destination->value[1][1] = cosA;
    destination->value[0][0] = cosA;
    destination->value[0][1] = cosA;
    destination->value[2][2] = fVar1;
    destination->value[2][3] = fVar2;
  }
  return;
}

