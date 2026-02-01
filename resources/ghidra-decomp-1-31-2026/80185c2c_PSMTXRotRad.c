// Function: PSMTXRotRad
// Entry: 80185c2c
// Size: 112 bytes

void PSMTXRotRad(float radians,Mtx *destionation,undefined4 axis)

{
  double dVar1;
  double dVar2;
  
  dVar2 = (double)radians;
  dVar1 = (double)sinf(dVar2);
  dVar2 = (double)cosf(dVar2);
  PSMTXRotTrig((float)dVar1,(float)dVar2,destionation,axis);
  return;
}

