// Function: pppRotMatrix__FR10pppFMATRIX10pppFMATRIX3Vec
// Entry: 8005767c
// Size: 160 bytes

void pppRotMatrix__FR10pppFMATRIX10pppFMATRIX3Vec
               (pppFMATRIX *pppFMtxA,pppFMATRIX *pppFMtxB,Vec *vec)

{
  Mtx MStack_d8;
  Mtx MStack_a8;
  Mtx MStack_78;
  Mtx MStack_48;
  
  PSMTXRotRad(vec->x,&MStack_48,0x78);
  PSMTXRotRad(vec->y,&MStack_78,0x79);
  PSMTXRotRad(vec->z,&MStack_a8,0x7a);
  PSMTXConcat(&MStack_78,&MStack_a8,&MStack_d8);
  PSMTXConcat(&MStack_48,&MStack_d8,&MStack_d8);
  PSMTXConcat(&MStack_d8,pppFMtxB,pppFMtxA);
  return;
}

