// Function: ?GetCodeInfo__12CFlatRuntimeFPc
// Entry: 800679dc
// Size: 516 bytes

void _GetCodeInfo__12CFlatRuntimeFPc(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float local_20;
  
  *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + -4;
  fVar3 = **(float **)(param_2 + 8);
  if ((((param_3 == 0x20) || (param_3 == 0x23)) || (param_3 == 0x25)) || (param_3 == 0x2b)) {
    switch(param_3) {
    case 0x20:
      local_20 = (float)-(int)fVar3;
      break;
    case 0x23:
      uVar1 = countLeadingZeros(fVar3);
      local_20 = (float)(uVar1 >> 5 & 0xff);
      break;
    case 0x25:
      local_20 = (float)~(uint)fVar3;
      break;
    case 0x2b:
      local_20 = -fVar3;
    }
  }
  else {
    *(float **)(param_2 + 8) = *(float **)(param_2 + 8) + -1;
    fVar2 = **(float **)(param_2 + 8);
    switch(param_3) {
    case 0x19:
      local_20 = (float)((int)fVar2 + (int)fVar3);
      break;
    case 0x1a:
      local_20 = (float)((int)fVar2 - (int)fVar3);
      break;
    case 0x1b:
      local_20 = (float)((int)fVar2 * (int)fVar3);
      break;
    case 0x1c:
      local_20 = (float)((int)fVar2 / (int)fVar3);
      break;
    case 0x1d:
      local_20 = (float)((int)fVar2 - ((int)fVar2 / (int)fVar3) * (int)fVar3);
      break;
    case 0x1e:
      local_20 = (float)((uint)fVar2 | (uint)fVar3);
      break;
    case 0x1f:
      local_20 = (float)((uint)fVar2 & (uint)fVar3);
      break;
    case 0x21:
      local_20 = (float)((int)fVar2 >> ((uint)fVar3 & 0x3f));
      break;
    case 0x22:
      local_20 = (float)((int)fVar2 << (int)fVar3);
      break;
    case 0x24:
      local_20 = (float)((uint)fVar2 ^ (uint)fVar3);
      break;
    case 0x26:
      local_20 = fVar2 + fVar3;
      break;
    case 0x27:
      local_20 = fVar2 - fVar3;
      break;
    case 0x28:
      local_20 = fVar2 * fVar3;
      break;
    case 0x29:
      local_20 = fVar2 / fVar3;
      break;
    case 0x2a:
      dVar4 = (double)fmod((double)fVar2,(double)fVar3);
      local_20 = (float)dVar4;
    }
  }
  **(float **)(param_2 + 8) = local_20;
  *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 4;
  return;
}

