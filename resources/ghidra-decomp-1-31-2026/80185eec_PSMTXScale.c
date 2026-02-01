// Function: PSMTXScale
// Entry: 80185eec
// Size: 40 bytes

/* WARNING: Removing unreachable block (ram,0x80185f04) */
/* WARNING: Removing unreachable block (ram,0x80185f00) */
/* WARNING: Removing unreachable block (ram,0x80185ef8) */
/* WARNING: Removing unreachable block (ram,0x80185ef4) */

void PSMTXScale(float xS,float yS,float zS,Mtx *dest)

{
  float fVar1;
  
  fVar1 = FLOAT_803336e4;
  dest->value[0][0] = xS;
  dest->value[0][1] = fVar1;
  dest->value[0][2] = fVar1;
  dest->value[0][3] = fVar1;
  dest->value[1][0] = fVar1;
  dest->value[1][1] = yS;
  dest->value[1][2] = fVar1;
  dest->value[1][3] = fVar1;
  dest->value[2][0] = fVar1;
  dest->value[2][1] = fVar1;
  dest->value[2][2] = zS;
  dest->value[2][3] = fVar1;
  return;
}

