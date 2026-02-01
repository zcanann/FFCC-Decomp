// Function: PSMTXCopy
// Entry: 801859e4
// Size: 52 bytes

/* WARNING: Removing unreachable block (ram,0x80185a10) */
/* WARNING: Removing unreachable block (ram,0x80185a0c) */
/* WARNING: Removing unreachable block (ram,0x80185a08) */
/* WARNING: Removing unreachable block (ram,0x80185a04) */
/* WARNING: Removing unreachable block (ram,0x80185a00) */
/* WARNING: Removing unreachable block (ram,0x801859fc) */
/* WARNING: Removing unreachable block (ram,0x801859f8) */
/* WARNING: Removing unreachable block (ram,0x801859f4) */
/* WARNING: Removing unreachable block (ram,0x801859f0) */
/* WARNING: Removing unreachable block (ram,0x801859ec) */
/* WARNING: Removing unreachable block (ram,0x801859e8) */
/* WARNING: Removing unreachable block (ram,0x801859e4) */

void PSMTXCopy(Mtx *source,Mtx *dest)

{
  float fVar1;
  
  fVar1 = source->value[0][1];
  dest->value[0][0] = source->value[0][0];
  dest->value[0][1] = fVar1;
  fVar1 = source->value[0][3];
  dest->value[0][2] = source->value[0][2];
  dest->value[0][3] = fVar1;
  fVar1 = source->value[1][1];
  dest->value[1][0] = source->value[1][0];
  dest->value[1][1] = fVar1;
  fVar1 = source->value[1][3];
  dest->value[1][2] = source->value[1][2];
  dest->value[1][3] = fVar1;
  fVar1 = source->value[2][1];
  dest->value[2][0] = source->value[2][0];
  dest->value[2][1] = fVar1;
  fVar1 = source->value[2][3];
  dest->value[2][2] = source->value[2][2];
  dest->value[2][3] = fVar1;
  return;
}

