// Function: draw__9CLightPcsFv
// Entry: 80049ed4
// Size: 420 bytes

void draw__9CLightPcsFv(int param_1)

{
  float fVar1;
  uint uVar2;
  int *piVar3;
  double dVar4;
  Vec local_58;
  Mtx MStack_4c;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_4c);
  piVar3 = (int *)(param_1 + 0x63c);
  for (uVar2 = 0; uVar2 < *(uint *)(param_1 + 0xb8); uVar2 = uVar2 + 1) {
    if (*(char *)((int)piVar3 + 0x4f) == '\0') {
      if (*(char *)((int)piVar3 + 0x4e) == '\0') {
        PSMTXMultVec(&MStack_4c,(Vec *)(piVar3 + 1),&local_58);
        GXInitLightPos((double)local_58.x,(double)local_58.y,(double)local_58.z,piVar3 + 0x1b);
        PSMTXMultVecSR(&MStack_4c,(Vec *)(piVar3 + 0xe),&local_58);
        GXInitLightDir((double)local_58.x,(double)local_58.y,(double)local_58.z,piVar3 + 0x1b);
      }
      else {
        PSMTXMultVec(&MStack_4c,(Vec *)(piVar3 + 1),&local_58);
        GXInitLightPos((double)local_58.x,(double)local_58.y,(double)local_58.z,piVar3 + 0x1b);
        GXInitLightDir((double)(float)piVar3[0xe],(double)(float)piVar3[0xf],
                       (double)(float)piVar3[0x10],piVar3 + 0x1b);
      }
      fVar1 = FLOAT_8032fc74;
      if (*piVar3 == 1) {
        fVar1 = FLOAT_8032fc94 * (float)piVar3[0x11];
      }
      GXInitLightSpot((double)fVar1,piVar3 + 0x1b,*(undefined *)((int)piVar3 + 0x4d));
      GXInitLightAttnK((double)(FLOAT_8032fc84 / (float)piVar3[8]),
                       (double)(FLOAT_8032fc84 / (float)piVar3[7]),
                       (double)(FLOAT_8032fc84 / (float)piVar3[7]),piVar3 + 0x1b);
    }
    else {
      PSMTXMultVecSR(&MStack_4c,(Vec *)(piVar3 + 0xe),&local_58);
      GXInitSpecularDir((double)local_58.x,(double)local_58.y,(double)local_58.z,piVar3 + 0x1b);
      dVar4 = (double)FLOAT_8032fc14;
      GXInitLightAttn(dVar4,dVar4,(double)FLOAT_8032fc1c,
                      (double)((float)piVar3[0x12] * FLOAT_8032fc18),dVar4,
                      (double)(float)((double)FLOAT_8032fc1c -
                                     (double)((float)piVar3[0x12] * FLOAT_8032fc18)),piVar3 + 0x1b);
    }
    piVar3 = piVar3 + 0x2c;
  }
  return;
}

