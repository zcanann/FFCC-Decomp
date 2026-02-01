// Function: pppEditGetViewMatrix__FPA4_f
// Entry: 8005d900
// Size: 44 bytes

void pppEditGetViewMatrix__FPA4_f(Mtx *viewMatrix)

{
  PSMTXCopy(&ppvCameraMatrix0,viewMatrix);
  return;
}

