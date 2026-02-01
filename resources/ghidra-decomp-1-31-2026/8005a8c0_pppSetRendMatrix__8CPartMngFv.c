// Function: pppSetRendMatrix__8CPartMngFv
// Entry: 8005a8c0
// Size: 108 bytes

void pppSetRendMatrix__8CPartMngFv(void)

{
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&ppvScreenMatrix);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&ppvCameraMatrix0);
  FLOAT_8032ed58 = ppvScreenMatrix.value[2][0];
  FLOAT_8032ed5c = ppvScreenMatrix.value[2][1];
  FLOAT_8032ed60 = ppvScreenMatrix.value[2][3];
  return;
}

