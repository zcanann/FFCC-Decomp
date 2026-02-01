// Function: pppSetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
// Entry: 800574f4
// Size: 100 bytes

void pppSetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
               (pppFMATRIX *pppFMtx,Vec *vecA,Vec *vecB,Vec *vecC,Vec *vecD)

{
  pppFMtx->value[0][0] = vecA->x;
  pppFMtx->value[1][0] = vecA->y;
  pppFMtx->value[2][0] = vecA->z;
  pppFMtx->value[0][1] = vecB->x;
  pppFMtx->value[1][1] = vecB->y;
  pppFMtx->value[2][1] = vecB->z;
  pppFMtx->value[0][2] = vecC->x;
  pppFMtx->value[1][2] = vecC->y;
  pppFMtx->value[2][2] = vecC->z;
  pppFMtx->value[0][3] = vecD->x;
  pppFMtx->value[1][3] = vecD->y;
  pppFMtx->value[2][3] = vecD->z;
  return;
}

