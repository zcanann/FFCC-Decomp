// Function: calcPart__10CCameraPcsFv
// Entry: 800362e4
// Size: 244 bytes

void calcPart__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  Vec local_48;
  Mtx MStack_3c;
  
  if (*(int *)(param_1 + 0x494) != 0) {
    CalcQuake__10CCameraPcsFv();
    local_48.x = ppvCameraMatrix0.value[0][3];
    local_48.y = ppvCameraMatrix0.value[1][3];
    local_48.z = ppvCameraMatrix0.value[2][3];
    PSVECAdd((Vec *)(param_1 + 0x4a4),&local_48,&local_48);
    ppvCameraMatrix0.value[0][3] = local_48.x;
    ppvCameraMatrix0.value[1][3] = local_48.y;
    ppvCameraMatrix0.value[2][3] = local_48.z;
  }
  *(float *)(param_1 + 0xfc) = FLOAT_8032fa30;
  pppEditGetViewPos__FP3Vec((Vec *)(param_1 + 0xe0));
  pppEditGetViewMatrix__FPA4_f(param_1 + 4);
  pppEditGetProjectionMatrix__FPA4_f(param_1 + 0x94);
  GXSetProjection(param_1 + 0x94,0);
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_3c);
  fVar2 = FLOAT_8032fa38;
  fVar1 = FLOAT_8032fa34;
  *(float *)(param_1 + 0xec) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar1;
  *(float *)(param_1 + 0xf4) = fVar2;
  PSMTXMultVecSR(&MStack_3c,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  PSVECAdd((Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xd4));
  return;
}

