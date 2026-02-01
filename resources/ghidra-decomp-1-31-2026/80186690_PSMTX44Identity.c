// Function: PSMTX44Identity
// Entry: 80186690
// Size: 52 bytes

/* WARNING: Removing unreachable block (ram,0x801866b8) */
/* WARNING: Removing unreachable block (ram,0x801866b4) */
/* WARNING: Removing unreachable block (ram,0x801866ac) */
/* WARNING: Removing unreachable block (ram,0x801866a8) */
/* WARNING: Removing unreachable block (ram,0x801866a0) */
/* WARNING: Removing unreachable block (ram,0x8018669c) */

void PSMTX44Identity(Mat4x4 *mtx)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80333708;
  fVar1 = FLOAT_80333700;
  mtx->value[0][0] = FLOAT_80333700;
  mtx->value[0][1] = fVar2;
  mtx->value[0][2] = fVar2;
  mtx->value[0][3] = fVar2;
  mtx->value[1][0] = fVar2;
  mtx->value[1][1] = fVar1;
  mtx->value[1][2] = fVar2;
  mtx->value[1][3] = fVar2;
  mtx->value[2][0] = fVar2;
  mtx->value[2][1] = fVar2;
  mtx->value[2][2] = fVar1;
  mtx->value[2][3] = fVar2;
  mtx->value[3][0] = fVar2;
  mtx->value[3][1] = fVar2;
  mtx->value[3][2] = fVar2;
  mtx->value[3][3] = fVar1;
  return;
}

