// Function: ExPPC_ThrowHandler__FP12ThrowContext
// Entry: 801b0944
// Size: 1040 bytes

/* WARNING: Removing unreachable block (ram,0x801b0a28) */

void ExPPC_ThrowHandler__FP12ThrowContext(int param_1)

{
  bool bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  byte bVar4;
  char cVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  int iVar8;
  undefined auStack_68 [4];
  int local_64;
  ushort *local_60;
  int local_5c;
  byte *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  ushort *local_48;
  int local_44;
  byte *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  
  ExPPC_FindExceptionRecord__FPcP15MWExceptionInfo(*(undefined4 *)(param_1 + 0x290),&local_60);
  if (local_60 == (ushort *)0x0) {
    terminate__3stdFv();
  }
  if ((*local_60 >> 4 & 1) == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x284);
  }
  else {
    uVar3 = *(undefined4 *)(param_1 + 0x27c);
  }
  *(undefined4 *)(param_1 + 0x288) = uVar3;
  if (*(int *)(param_1 + 0x294) == 0) {
    local_48 = local_60;
    local_44 = local_5c;
    local_40 = local_58;
    local_3c = local_54;
    local_38 = local_50;
    local_34 = local_4c;
    local_30 = *(undefined4 *)(param_1 + 0x284);
    local_2c = *(int *)(param_1 + 0x288);
    local_28 = *(undefined4 *)(param_1 + 0x27c);
    if (local_58 == (byte *)0x0) {
      bVar4 = 0;
    }
    else {
      bVar4 = *local_58 & 0x7f;
    }
    while (bVar4 != 0xd) {
      if (bVar4 < 0xd) {
        if (bVar4 == 1) goto LAB_801b0a3c;
      }
      else if ((0x10 < bVar4) || (bVar4 < 0xf)) {
LAB_801b0a3c:
        terminate__3stdFv();
        break;
      }
      bVar4 = ExPPC_NextAction__FP14ActionIterator(&local_48);
    }
    puVar6 = (undefined4 *)(local_2c + *(short *)(local_40 + 2));
    *(undefined4 *)(param_1 + 0x294) = puVar6[1];
    *(undefined4 *)(param_1 + 0x298) = *puVar6;
    *(undefined4 *)(param_1 + 0x29c) = 0;
    *(undefined4 **)(param_1 + 0x2a0) = puVar6;
  }
  else {
    *(undefined4 *)(param_1 + 0x2a0) = 0;
  }
  local_48 = local_60;
  local_44 = local_5c;
  local_40 = local_58;
  local_3c = local_54;
  local_38 = local_50;
  local_34 = local_4c;
  local_30 = *(undefined4 *)(param_1 + 0x284);
  local_2c = *(undefined4 *)(param_1 + 0x288);
  local_28 = *(undefined4 *)(param_1 + 0x27c);
  if (local_58 == (byte *)0x0) {
    bVar4 = 0;
  }
  else {
    bVar4 = *local_58 & 0x7f;
  }
  do {
    pbVar2 = local_40;
    switch(bVar4) {
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xd:
      break;
    default:
      terminate__3stdFv();
LAB_801b0c10:
      pbVar2 = local_40;
      if (bVar4 == 0x10) {
        ExPPC_UnwindStack__FP12ThrowContextP15MWExceptionInfoPv(param_1,&local_60,local_40);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x288) + *(int *)(pbVar2 + 0xc));
        *puVar6 = *(undefined4 *)(param_1 + 0x298);
        puVar6[1] = *(undefined4 *)(param_1 + 0x294);
        puVar6[2] = *(undefined4 *)(param_1 + 0x29c);
        if (**(char **)(param_1 + 0x294) == '*') {
          puVar6[3] = puVar6 + 4;
          puVar6[4] = **(int **)(param_1 + 0x298) + local_64;
        }
        else {
          puVar6[3] = *(int *)(param_1 + 0x298) + local_64;
        }
        ExPPC_LongJump__FP12ThrowContextPvPv(param_1,local_4c,local_5c + *(int *)(pbVar2 + 8));
      }
      else {
        ExPPC_UnwindStack__FP12ThrowContextP15MWExceptionInfoPv(param_1,&local_60,local_40);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x288) + (int)*(short *)(pbVar2 + 10));
        *puVar6 = *(undefined4 *)(param_1 + 0x298);
        puVar6[1] = *(undefined4 *)(param_1 + 0x294);
        puVar6[2] = *(undefined4 *)(param_1 + 0x29c);
        if (**(char **)(param_1 + 0x294) == '*') {
          puVar6[3] = puVar6 + 4;
          puVar6[4] = **(int **)(param_1 + 0x298) + local_64;
        }
        else {
          puVar6[3] = *(int *)(param_1 + 0x298) + local_64;
        }
        ExPPC_LongJump__FP12ThrowContextPvPv
                  (param_1,local_4c,local_5c + (uint)*(ushort *)(pbVar2 + 8));
      }
      return;
    case 0xc:
      cVar5 = __throw_catch_compare
                        (*(undefined4 *)(param_1 + 0x294),*(undefined4 *)(local_40 + 4),&local_64);
      goto joined_r0x801b0b24;
    case 0xf:
      uVar3 = *(undefined4 *)(param_1 + 0x294);
      pbVar7 = local_40;
      for (iVar8 = 0; iVar8 < (int)(uint)*(ushort *)(pbVar2 + 2); iVar8 = iVar8 + 1) {
        cVar5 = __throw_catch_compare(uVar3,*(undefined4 *)(pbVar7 + 0xc),auStack_68);
        if (cVar5 != '\0') {
          bVar1 = true;
          goto LAB_801b0b98;
        }
        pbVar7 = pbVar7 + 4;
      }
      bVar1 = false;
LAB_801b0b98:
      pbVar2 = local_40;
      if (!bVar1) {
        ExPPC_UnwindStack__FP12ThrowContextP15MWExceptionInfoPv(param_1,&local_60,local_40);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x288) + *(int *)(pbVar2 + 8));
        *puVar6 = *(undefined4 *)(param_1 + 0x298);
        puVar6[1] = *(undefined4 *)(param_1 + 0x294);
        puVar6[2] = *(undefined4 *)(param_1 + 0x29c);
        puVar6[5] = pbVar2;
        ExPPC_LongJump__FP12ThrowContextPvPv(param_1,local_4c,local_5c + *(int *)(pbVar2 + 4));
      }
      break;
    case 0x10:
      cVar5 = __throw_catch_compare
                        (*(undefined4 *)(param_1 + 0x294),*(undefined4 *)(local_40 + 4),&local_64);
joined_r0x801b0b24:
      if (cVar5 != '\0') goto LAB_801b0c10;
    }
    bVar4 = ExPPC_NextAction__FP14ActionIterator(&local_48);
  } while( true );
}

