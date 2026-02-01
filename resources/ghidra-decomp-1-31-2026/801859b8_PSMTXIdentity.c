// Function: PSMTXIdentity
// Entry: 801859b8
// Size: 44 bytes

/* WARNING: Removing unreachable block (ram,0x801859dc) */
/* WARNING: Removing unreachable block (ram,0x801859d8) */
/* WARNING: Removing unreachable block (ram,0x801859d4) */
/* WARNING: Removing unreachable block (ram,0x801859d0) */
/* WARNING: Removing unreachable block (ram,0x801859c8) */
/* WARNING: Removing unreachable block (ram,0x801859c0) */

void PSMTXIdentity(Mtx *mtx)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_803336e4;
  fVar1 = FLOAT_803336e0;
  mtx->value[0][2] = FLOAT_803336e4;
  mtx->value[0][3] = fVar2;
  mtx->value[1][2] = fVar2;
  mtx->value[1][3] = fVar2;
  mtx->value[2][0] = fVar2;
  mtx->value[2][1] = fVar2;
  mtx->value[1][0] = fVar2;
  mtx->value[1][1] = fVar1;
  mtx->value[0][0] = fVar1;
  mtx->value[0][1] = fVar2;
  mtx->value[2][2] = fVar1;
  mtx->value[2][3] = fVar2;
  return;
}

