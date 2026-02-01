// Function: ExPPC_NextAction__FP14ActionIterator
// Entry: 801b16b8
// Size: 448 bytes

byte ExPPC_NextAction__FP14ActionIterator(int *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  
  do {
    pbVar2 = (byte *)param_1[2];
    if ((pbVar2 != (byte *)0x0) && ((*pbVar2 & 0x80) == 0)) {
      switch(*pbVar2) {
      default:
        terminate__3stdFv();
        break;
      case 2:
        param_1[2] = (int)(pbVar2 + 8);
        break;
      case 3:
        param_1[2] = (int)(pbVar2 + 0xc);
        break;
      case 4:
        param_1[2] = (int)(pbVar2 + 8);
        break;
      case 5:
        param_1[2] = (int)(pbVar2 + 0xc);
        break;
      case 6:
      case 7:
        param_1[2] = param_1[2] + 0xc;
        break;
      case 8:
        param_1[2] = (int)(pbVar2 + 0x10);
        break;
      case 9:
        param_1[2] = (int)(pbVar2 + 0x14);
        break;
      case 10:
        param_1[2] = (int)(pbVar2 + 8);
        break;
      case 0xb:
        param_1[2] = (int)(pbVar2 + 0xc);
        break;
      case 0xc:
        param_1[2] = (int)(pbVar2 + 0xc);
        break;
      case 0xd:
        param_1[2] = (int)(pbVar2 + 4);
        break;
      case 0xf:
        param_1[2] = (int)(pbVar2 + (uint)*(ushort *)(pbVar2 + 2) * 4 + 0xc);
        break;
      case 0x10:
        param_1[2] = (int)(pbVar2 + 0x10);
      }
      break;
    }
    iVar3 = *(int *)param_1[6];
    if ((int)(uint)*(ushort *)*param_1 >> 0xb != 0) {
      param_1[8] = *(int *)((iVar3 - (*(ushort *)*param_1 >> 3 & 0xf8)) + -4);
    }
    ExPPC_FindExceptionRecord__FPcP15MWExceptionInfo(*(undefined4 *)(iVar3 + 4),param_1);
    if (*param_1 == 0) {
      terminate__3stdFv();
    }
    param_1[6] = iVar3;
    if ((*(ushort *)*param_1 >> 4 & 1) == 0) {
      iVar3 = param_1[6];
    }
    else {
      iVar3 = param_1[8];
    }
    param_1[7] = iVar3;
  } while (param_1[2] == 0);
  bVar1 = *(byte *)param_1[2] & 0x7f;
  if (bVar1 == 1) {
    param_1[2] = *param_1 + (uint)*(ushort *)((byte *)param_1[2] + 2);
    bVar1 = *(byte *)param_1[2] & 0x7f;
  }
  return bVar1;
}

