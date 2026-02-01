// Function: CheckCross__6CBoundFR6CBound
// Entry: 8002cc28
// Size: 272 bytes

undefined4 CheckCross__6CBoundFR6CBound(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  undefined4 uVar5;
  
  fVar1 = *param_1;
  uVar5 = 0;
  fVar2 = *param_2;
  bVar4 = false;
  if (fVar2 <= fVar1) {
    if (fVar1 <= fVar2) {
      bVar3 = true;
    }
    else {
      bVar3 = fVar1 <= param_2[3];
    }
  }
  else {
    bVar3 = fVar2 <= param_1[3];
  }
  if (bVar3) {
    fVar1 = param_1[1];
    fVar2 = param_2[1];
    if (fVar2 <= fVar1) {
      if (fVar1 <= fVar2) {
        bVar3 = true;
      }
      else {
        bVar3 = fVar1 <= param_2[4];
      }
    }
    else {
      bVar3 = fVar2 <= param_1[4];
    }
    if (bVar3) {
      bVar4 = true;
    }
  }
  if (bVar4) {
    fVar1 = param_1[2];
    fVar2 = param_2[2];
    if (fVar2 <= fVar1) {
      if (fVar1 <= fVar2) {
        bVar4 = true;
      }
      else {
        bVar4 = fVar1 <= param_2[5];
      }
    }
    else {
      bVar4 = fVar2 <= param_1[5];
    }
    if (bVar4) {
      uVar5 = 1;
    }
  }
  return uVar5;
}

