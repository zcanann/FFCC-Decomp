// Function: PSMTXTranspose
// Entry: 80185ae4
// Size: 80 bytes

/* WARNING: Removing unreachable block (ram,0x80185b28) */
/* WARNING: Removing unreachable block (ram,0x80185b20) */
/* WARNING: Removing unreachable block (ram,0x80185b18) */
/* WARNING: Removing unreachable block (ram,0x80185b10) */
/* WARNING: Removing unreachable block (ram,0x80185b08) */
/* WARNING: Removing unreachable block (ram,0x80185b04) */
/* WARNING: Removing unreachable block (ram,0x80185b00) */
/* WARNING: Removing unreachable block (ram,0x80185af8) */
/* WARNING: Removing unreachable block (ram,0x80185af0) */
/* WARNING: Removing unreachable block (ram,0x80185ae8) */

void PSMTXTranspose(Mtx *source,Mtx *dest)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar6 = FLOAT_803336e4;
  fVar1 = source->value[0][0];
  fVar4 = source->value[0][1];
  dest->value[2][3] = FLOAT_803336e4;
  fVar2 = source->value[1][0];
  fVar5 = source->value[1][1];
  fVar3 = source->value[0][2];
  dest->value[0][0] = fVar1;
  dest->value[0][1] = fVar2;
  fVar1 = source->value[2][0];
  fVar2 = source->value[2][1];
  dest->value[1][0] = fVar4;
  dest->value[1][1] = fVar5;
  dest->value[2][0] = fVar3;
  dest->value[2][1] = fVar3;
  dest->value[0][2] = fVar1;
  dest->value[0][3] = fVar6;
  fVar1 = source->value[2][2];
  dest->value[1][2] = fVar2;
  dest->value[1][3] = fVar6;
  dest->value[2][2] = fVar1;
  return;
}

