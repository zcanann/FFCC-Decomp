// Function: PSMTXRotAxisRad
// Entry: 80185dfc
// Size: 112 bytes

void PSMTXRotAxisRad(float radians,Mtx *destination,Vec *axis)

{
  double dVar1;
  double dVar2;
  
  dVar2 = (double)radians;
  dVar1 = (double)sinf(dVar2);
  dVar2 = (double)cosf(dVar2);
  __PSMTXRotAxisRadInternal((float)dVar1,(float)dVar2,destination,axis);
  return;
}

