// Function: PSMTXTransApply
// Entry: 80185ea0
// Size: 76 bytes

/* WARNING: Removing unreachable block (ram,0x80185ee4) */
/* WARNING: Removing unreachable block (ram,0x80185ee0) */
/* WARNING: Removing unreachable block (ram,0x80185edc) */
/* WARNING: Removing unreachable block (ram,0x80185ed4) */
/* WARNING: Removing unreachable block (ram,0x80185ed0) */
/* WARNING: Removing unreachable block (ram,0x80185ec8) */
/* WARNING: Removing unreachable block (ram,0x80185ec4) */
/* WARNING: Removing unreachable block (ram,0x80185ebc) */
/* WARNING: Removing unreachable block (ram,0x80185eb8) */
/* WARNING: Removing unreachable block (ram,0x80185eb0) */
/* WARNING: Removing unreachable block (ram,0x80185ea8) */
/* WARNING: Removing unreachable block (ram,0x80185ea0) */

void PSMTXTransApply(float xT,float yT,float zT,Mtx *source,Mtx *dest)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar4 = source->value[0][1];
  fVar1 = source->value[0][2];
  fVar5 = source->value[0][3];
  fVar2 = source->value[1][2];
  fVar6 = source->value[1][3];
  fVar3 = source->value[2][2];
  fVar7 = source->value[2][3];
  dest->value[0][0] = source->value[0][0];
  dest->value[0][1] = fVar4;
  fVar4 = source->value[1][0];
  fVar8 = source->value[1][1];
  dest->value[0][2] = fVar1;
  dest->value[0][3] = xT + fVar5;
  fVar1 = source->value[2][0];
  fVar5 = source->value[2][1];
  dest->value[1][0] = fVar4;
  dest->value[1][1] = fVar8;
  dest->value[1][2] = fVar2;
  dest->value[1][3] = yT + fVar6;
  dest->value[2][0] = fVar1;
  dest->value[2][1] = fVar5;
  dest->value[2][2] = fVar3;
  dest->value[2][3] = zT + fVar7;
  return;
}

