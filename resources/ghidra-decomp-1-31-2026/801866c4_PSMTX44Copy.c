// Function: PSMTX44Copy
// Entry: 801866c4
// Size: 68 bytes

/* WARNING: Removing unreachable block (ram,0x80186700) */
/* WARNING: Removing unreachable block (ram,0x801866fc) */
/* WARNING: Removing unreachable block (ram,0x801866f8) */
/* WARNING: Removing unreachable block (ram,0x801866f4) */
/* WARNING: Removing unreachable block (ram,0x801866f0) */
/* WARNING: Removing unreachable block (ram,0x801866ec) */
/* WARNING: Removing unreachable block (ram,0x801866e8) */
/* WARNING: Removing unreachable block (ram,0x801866e4) */
/* WARNING: Removing unreachable block (ram,0x801866e0) */
/* WARNING: Removing unreachable block (ram,0x801866dc) */
/* WARNING: Removing unreachable block (ram,0x801866d8) */
/* WARNING: Removing unreachable block (ram,0x801866d4) */
/* WARNING: Removing unreachable block (ram,0x801866d0) */
/* WARNING: Removing unreachable block (ram,0x801866cc) */
/* WARNING: Removing unreachable block (ram,0x801866c8) */
/* WARNING: Removing unreachable block (ram,0x801866c4) */

void PSMTX44Copy(Mat4x4 *source,Mat4x4 *dest)

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
  fVar1 = source->value[3][1];
  dest->value[3][0] = source->value[3][0];
  dest->value[3][1] = fVar1;
  fVar1 = source->value[3][3];
  dest->value[3][2] = source->value[3][2];
  dest->value[3][3] = fVar1;
  return;
}

