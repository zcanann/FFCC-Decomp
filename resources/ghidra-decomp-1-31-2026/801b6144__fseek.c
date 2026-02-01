// Function: _fseek
// Entry: 801b6144
// Size: 624 bytes

undefined4 _fseek(undefined4 *param_1,uint param_2,int param_3)

{
  char cVar1;
  uint uVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint local_18 [4];
  
  if (((*(ushort *)(param_1 + 1) >> 6 & 7) == 1) && (*(char *)((int)param_1 + 10) == '\0')) {
    local_18[0] = param_2;
    if ((*(byte *)(param_1 + 2) >> 5 == 1) && (iVar5 = __flush_buffer(param_1,0), iVar5 != 0)) {
      *(undefined *)((int)param_1 + 10) = 1;
      uVar4 = 0xffffffff;
      param_1[10] = 0;
      DAT_8032f390 = 0x28;
    }
    else {
      if (param_3 == 1) {
        param_3 = 0;
        iVar5 = 0;
        uVar3 = *(ushort *)(param_1 + 1) >> 6 & 7;
        if (((uVar3 == 1) || (uVar3 == 2)) && (*(char *)((int)param_1 + 10) == '\0')) {
          uVar2 = (uint)(*(byte *)(param_1 + 2) >> 5);
          if (uVar2 == 0) {
            iVar6 = param_1[6];
          }
          else {
            pcVar7 = (char *)param_1[7];
            iVar6 = param_1[0xd] + (param_1[9] - (int)pcVar7);
            if (2 < uVar2) {
              iVar5 = uVar2 - 2;
              iVar6 = iVar6 - iVar5;
            }
            if ((*(byte *)((int)param_1 + 5) >> 3 & 1) == 0) {
              for (iVar5 = (param_1[9] - (int)pcVar7) - iVar5; iVar5 != 0; iVar5 = iVar5 + -1) {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
                if (cVar1 == '\n') {
                  iVar6 = iVar6 + 1;
                }
              }
            }
          }
        }
        else {
          iVar6 = -1;
          DAT_8032f390 = 0x28;
        }
        local_18[0] = local_18[0] + iVar6;
      }
      if (((param_3 == 2) || ((*(byte *)(param_1 + 1) >> 3 & 7) == 3)) ||
         ((*(byte *)(param_1 + 2) >> 5 != 2 && (*(byte *)(param_1 + 2) >> 5 != 3)))) {
        *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
      }
      else if ((local_18[0] < (uint)param_1[6]) && ((uint)param_1[0xd] <= local_18[0])) {
        param_1[9] = param_1[7] + (local_18[0] - param_1[0xd]);
        param_1[10] = param_1[6] - local_18[0];
        *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f | 0x40;
      }
      else {
        *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
      }
      if (*(byte *)(param_1 + 2) >> 5 == 0) {
        if (((code *)param_1[0xe] != (code *)0x0) &&
           (iVar5 = (*(code *)param_1[0xe])(*param_1,local_18,param_3,param_1[0x12]), iVar5 != 0)) {
          *(undefined *)((int)param_1 + 10) = 1;
          param_1[10] = 0;
          DAT_8032f390 = 0x28;
          return 0xffffffff;
        }
        *(undefined *)((int)param_1 + 9) = 0;
        param_1[6] = local_18[0];
        param_1[10] = 0;
      }
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 0xffffffff;
    DAT_8032f390 = 0x28;
  }
  return uVar4;
}

