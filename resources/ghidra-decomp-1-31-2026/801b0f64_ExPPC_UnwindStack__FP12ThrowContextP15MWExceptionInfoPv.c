// Function: ExPPC_UnwindStack__FP12ThrowContextP15MWExceptionInfoPv
// Entry: 801b0f64
// Size: 1292 bytes

void ExPPC_UnwindStack__FP12ThrowContextP15MWExceptionInfoPv(int param_1,int *param_2,byte *param_3)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  char cVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  code *pcVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  byte *pbVar12;
  
  do {
    while (pbVar12 = (byte *)param_2[2], pbVar12 == (byte *)0x0) {
      uVar5 = ExPPC_PopStackFrame__FP12ThrowContextP15MWExceptionInfo(param_1,param_2);
      ExPPC_FindExceptionRecord__FPcP15MWExceptionInfo(uVar5,param_2);
      if (*param_2 == 0) {
        terminate__3stdFv();
      }
      if ((*(ushort *)*param_2 >> 4 & 1) == 0) {
        uVar5 = *(undefined4 *)(param_1 + 0x284);
      }
      else {
        uVar5 = *(undefined4 *)(param_1 + 0x27c);
      }
      *(undefined4 *)(param_1 + 0x288) = uVar5;
    }
    bVar1 = *pbVar12;
    switch(bVar1 & 0x7f) {
    default:
      terminate__3stdFv();
      break;
    case 1:
      param_2[2] = *param_2 + (uint)*(ushort *)(pbVar12 + 2);
      break;
    case 2:
      (**(code **)(pbVar12 + 4))
                (*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2),0xffffffff);
      param_2[2] = param_2[2] + 8;
      break;
    case 3:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        cVar4 = *(char *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        cVar4 = (char)*(undefined4 *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      if (cVar4 != '\0') {
        (**(code **)(pbVar12 + 8))
                  (*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 4),0xffffffff);
      }
      param_2[2] = param_2[2] + 0xc;
      break;
    case 4:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        uVar5 = *(undefined4 *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      (**(code **)(pbVar12 + 4))(uVar5,0xffffffff);
      param_2[2] = param_2[2] + 8;
      break;
    case 5:
      uVar10 = (uint)*(ushort *)(pbVar12 + 4);
      uVar2 = *(ushort *)(pbVar12 + 6);
      iVar7 = *(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2) + uVar2 * uVar10;
      for (; 0 < (int)uVar10; uVar10 = uVar10 - 1) {
        iVar7 = iVar7 - (uint)uVar2;
        (**(code **)(pbVar12 + 8))(iVar7,0xffffffff);
      }
      param_2[2] = param_2[2] + 0xc;
      break;
    case 6:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        iVar7 = *(int *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        iVar7 = *(int *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      (**(code **)(pbVar12 + 8))(iVar7 + *(int *)(pbVar12 + 4),0);
      param_2[2] = param_2[2] + 0xc;
      break;
    case 7:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        iVar7 = *(int *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        iVar7 = *(int *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      (**(code **)(pbVar12 + 8))(iVar7 + *(int *)(pbVar12 + 4),0xffffffff);
      param_2[2] = param_2[2] + 0xc;
      break;
    case 8:
      if ((pbVar12[1] >> 6 & 1) == 0) {
        iVar7 = *(int *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 4));
      }
      else {
        iVar7 = *(int *)(param_1 + *(short *)(pbVar12 + 4) * 4 + 0x200);
      }
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        sVar3 = *(short *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        sVar3 = (short)*(undefined4 *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      if (sVar3 != 0) {
        (**(code **)(pbVar12 + 0xc))(iVar7 + *(int *)(pbVar12 + 8),0);
      }
      param_2[2] = param_2[2] + 0x10;
      break;
    case 9:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        iVar7 = *(int *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        iVar7 = *(int *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      iVar11 = *(int *)(pbVar12 + 8);
      iVar9 = *(int *)(pbVar12 + 0xc);
      iVar7 = iVar7 + *(int *)(pbVar12 + 4) + iVar9 * iVar11;
      for (; 0 < iVar11; iVar11 = iVar11 + -1) {
        iVar7 = iVar7 - iVar9;
        (**(code **)(pbVar12 + 0x10))(iVar7,0xffffffff);
      }
      param_2[2] = param_2[2] + 0x14;
      break;
    case 10:
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        uVar5 = *(undefined4 *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      (**(code **)(pbVar12 + 4))(uVar5);
      param_2[2] = param_2[2] + 8;
      break;
    case 0xb:
      if ((pbVar12[1] >> 6 & 1) == 0) {
        uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 4));
      }
      else {
        uVar5 = *(undefined4 *)(param_1 + *(short *)(pbVar12 + 4) * 4 + 0x200);
      }
      if ((int)(uint)pbVar12[1] >> 7 == 0) {
        cVar4 = *(char *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      }
      else {
        cVar4 = (char)*(undefined4 *)(param_1 + *(short *)(pbVar12 + 2) * 4 + 0x200);
      }
      if (cVar4 != '\0') {
        (**(code **)(pbVar12 + 8))(uVar5);
      }
      param_2[2] = param_2[2] + 0xc;
      break;
    case 0xc:
      if (param_3 == pbVar12) {
        return;
      }
      param_2[2] = (int)(pbVar12 + 0xc);
      break;
    case 0xd:
      piVar6 = (int *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar12 + 2));
      pcVar8 = (code *)piVar6[2];
      if (pcVar8 != (code *)0x0) {
        iVar7 = *piVar6;
        if (*(int *)(param_1 + 0x298) == iVar7) {
          *(code **)(param_1 + 0x29c) = pcVar8;
        }
        else {
          (*pcVar8)(iVar7,0xffffffff);
        }
      }
      param_2[2] = param_2[2] + 4;
      break;
    case 0xf:
      if (param_3 == pbVar12) {
        return;
      }
      param_2[2] = (int)(pbVar12 + (uint)*(ushort *)(pbVar12 + 2) * 4 + 0xc);
      break;
    case 0x10:
      if (param_3 == pbVar12) {
        return;
      }
      param_2[2] = (int)(pbVar12 + 0x10);
    }
    if ((bVar1 & 0x80) != 0) {
      param_2[2] = 0;
    }
  } while( true );
}

