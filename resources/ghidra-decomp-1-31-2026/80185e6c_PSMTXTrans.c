// Function: PSMTXTrans
// Entry: 80185e6c
// Size: 52 bytes

/* WARNING: Removing unreachable block (ram,0x80185e80) */
/* WARNING: Removing unreachable block (ram,0x80185e7c) */

void PSMTXTrans(float xT,float yT,float zT,Mtx *mtx)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_803336e4;
  fVar1 = FLOAT_803336e0;
  mtx->value[0][3] = xT;
  mtx->value[1][3] = yT;
  mtx->value[0][1] = fVar2;
  mtx->value[0][2] = fVar2;
  mtx->value[2][0] = fVar2;
  mtx->value[2][1] = fVar2;
  mtx->value[1][0] = fVar2;
  mtx->value[1][1] = fVar1;
  mtx->value[1][2] = fVar2;
  mtx->value[2][2] = fVar1;
  mtx->value[2][3] = zT;
  mtx->value[0][0] = fVar1;
  return;
}

