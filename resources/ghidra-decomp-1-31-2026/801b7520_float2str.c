// Function: float2str
// Entry: 801b7520
// Size: 1820 bytes

byte * float2str(double param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  uint uVar10;
  undefined local_48 [2];
  undefined2 local_46;
  char local_44 [2];
  short local_42;
  byte local_40;
  byte local_3f [39];
  
  if (0x1fd < *(int *)(param_3 + 0xc)) {
    return (byte *)0x0;
  }
  local_48[0] = 0;
  local_46 = 0x20;
  __num2dec(local_48,local_44);
  pbVar9 = local_3f + local_40;
  while ((1 < local_40 && (pbVar9 = pbVar9 + -1, *pbVar9 == 0x30))) {
    local_40 = local_40 - 1;
    local_42 = local_42 + 1;
  }
  if (local_3f[0] == 0x49) {
    if (DOUBLE_80333940 <= param_1) {
      pbVar9 = (byte *)(param_2 + -4);
      if (((&DAT_8021d3c0)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
        strcpy(pbVar9,&DAT_801e70c3);
        return pbVar9;
      }
      strcpy(pbVar9,&DAT_801e70c7);
      return pbVar9;
    }
    pbVar9 = (byte *)(param_2 + -5);
    if (((&DAT_8021d3c0)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
      strcpy(pbVar9,&DAT_801e70b9);
      return pbVar9;
    }
    strcpy(pbVar9,&DAT_801e70be);
    return pbVar9;
  }
  if (local_3f[0] < 0x49) {
    if (local_3f[0] == 0x30) {
      local_42 = 0;
    }
  }
  else if (local_3f[0] == 0x4e) {
    if (local_44[0] == '\0') {
      pbVar9 = (byte *)(param_2 + -4);
      if (((&DAT_8021d3c0)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
        strcpy(pbVar9,&DAT_801e70d5);
        return pbVar9;
      }
      strcpy(pbVar9,&DAT_801e70d9);
      return pbVar9;
    }
    pbVar9 = (byte *)(param_2 + -5);
    if (((&DAT_8021d3c0)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
      strcpy(pbVar9,&DAT_801e70cb);
      return pbVar9;
    }
    strcpy(pbVar9,&DAT_801e70d0);
    return pbVar9;
  }
  pbVar9 = (byte *)(param_2 + -1);
  bVar8 = *(byte *)(param_3 + 5);
  local_42 = (ushort)local_40 + local_42 + -1;
  *(undefined *)(param_2 + -1) = 0;
  if (bVar8 == 0x65) goto LAB_801b785c;
  if (bVar8 < 0x65) {
    if (bVar8 != 0x46) {
      if (bVar8 < 0x46) {
        if (bVar8 < 0x45) {
          return pbVar9;
        }
        goto LAB_801b785c;
      }
      if (0x47 < bVar8) {
        return pbVar9;
      }
LAB_801b77a4:
      if (*(int *)(param_3 + 0xc) < (int)(uint)local_40) {
        round_decimal(local_44);
      }
      iVar6 = (int)local_42;
      if ((iVar6 < -4) || (*(int *)(param_3 + 0xc) <= iVar6)) {
        if (*(char *)(param_3 + 3) == '\0') {
          *(uint *)(param_3 + 0xc) = local_40 - 1;
        }
        else {
          *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -1;
        }
        if (*(char *)(param_3 + 5) == 'g') {
          *(undefined *)(param_3 + 5) = 0x65;
        }
        else {
          *(undefined *)(param_3 + 5) = 0x45;
        }
LAB_801b785c:
        if (*(int *)(param_3 + 0xc) + 1 < (int)(uint)local_40) {
          round_decimal(local_44);
        }
        iVar6 = (int)local_42;
        bVar8 = 0x2b;
        if (iVar6 < 0) {
          iVar6 = -iVar6;
          bVar8 = 0x2d;
        }
        for (iVar7 = 0; (iVar6 != 0 || (iVar7 < 2)); iVar7 = iVar7 + 1) {
          iVar3 = iVar6 / 10 + (iVar6 >> 0x1f);
          cVar2 = (char)iVar6;
          iVar6 = iVar3 - (iVar3 >> 0x1f);
          pbVar9[-1] = cVar2 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -10 + 0x30;
          pbVar9 = pbVar9 + -1;
        }
        bVar1 = *(byte *)(param_3 + 5);
        pbVar9[-1] = bVar8;
        iVar6 = *(int *)(param_3 + 0xc);
        pbVar9 = pbVar9 + -2;
        *pbVar9 = bVar1;
        if (0x1fd < iVar6 + (param_2 - (int)pbVar9)) {
          return (byte *)0x0;
        }
        if ((int)(uint)local_40 < iVar6 + 1) {
          iVar6 = (iVar6 + 2) - (uint)local_40;
          while (iVar6 = iVar6 + -1, iVar6 != 0) {
            pbVar9 = pbVar9 + -1;
            *pbVar9 = 0x30;
          }
        }
        uVar4 = (uint)local_40;
        pbVar5 = local_3f + uVar4;
        while (uVar4 = uVar4 - 1, uVar4 != 0) {
          pbVar5 = pbVar5 + -1;
          pbVar9 = pbVar9 + -1;
          *pbVar9 = *pbVar5;
        }
        if ((*(int *)(param_3 + 0xc) != 0) || (*(char *)(param_3 + 3) != '\0')) {
          pbVar9 = pbVar9 + -1;
          *pbVar9 = 0x2e;
        }
        pbVar9[-1] = local_3f[0];
        if (local_44[0] != '\0') {
          pbVar9[-2] = 0x2d;
          return pbVar9 + -2;
        }
        if (*(char *)(param_3 + 1) == '\x01') {
          pbVar9[-2] = 0x2b;
          return pbVar9 + -2;
        }
        if (*(char *)(param_3 + 1) != '\x02') {
          return pbVar9 + -1;
        }
        pbVar9[-2] = 0x20;
        return pbVar9 + -2;
      }
      if (*(char *)(param_3 + 3) == '\0') {
        iVar6 = (uint)local_40 - (iVar6 + 1);
        *(int *)(param_3 + 0xc) = iVar6;
        if (iVar6 < 0) {
          *(undefined4 *)(param_3 + 0xc) = 0;
        }
      }
      else {
        *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) - (iVar6 + 1);
      }
    }
  }
  else {
    if (bVar8 == 0x67) goto LAB_801b77a4;
    if (0x66 < bVar8) {
      return pbVar9;
    }
  }
  iVar6 = ((uint)local_40 - (int)local_42) + -1;
  if (iVar6 < 0) {
    iVar6 = 0;
  }
  if (*(int *)(param_3 + 0xc) < iVar6) {
    round_decimal(local_44,(uint)local_40 - (iVar6 - *(int *)(param_3 + 0xc)));
    iVar6 = ((uint)local_40 - (int)local_42) + -1;
    if (iVar6 < 0) {
      iVar6 = 0;
    }
  }
  iVar7 = local_42 + 1;
  if (iVar7 < 0) {
    iVar7 = 0;
  }
  if (0x1fd < iVar7 + iVar6) {
    return (byte *)0x0;
  }
  uVar4 = *(int *)(param_3 + 0xc) - iVar6;
  pbVar5 = local_3f + local_40;
  if (0 < (int)uVar4) {
    uVar10 = uVar4 >> 3;
    if (uVar10 != 0) {
      do {
        pbVar9[-1] = 0x30;
        pbVar9[-2] = 0x30;
        pbVar9[-3] = 0x30;
        pbVar9[-4] = 0x30;
        pbVar9[-5] = 0x30;
        pbVar9[-6] = 0x30;
        pbVar9[-7] = 0x30;
        pbVar9 = pbVar9 + -8;
        *pbVar9 = 0x30;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_801b7a8c;
    }
    do {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_801b7a8c:
  for (iVar3 = 0; (iVar3 < iVar6 && (iVar3 < (int)(uint)local_40)); iVar3 = iVar3 + 1) {
    pbVar5 = pbVar5 + -1;
    pbVar9 = pbVar9 + -1;
    *pbVar9 = *pbVar5;
  }
  uVar4 = iVar6 - iVar3;
  if (iVar3 < iVar6) {
    uVar10 = uVar4 >> 3;
    if (uVar10 != 0) {
      do {
        pbVar9[-1] = 0x30;
        pbVar9[-2] = 0x30;
        pbVar9[-3] = 0x30;
        pbVar9[-4] = 0x30;
        pbVar9[-5] = 0x30;
        pbVar9[-6] = 0x30;
        pbVar9[-7] = 0x30;
        pbVar9 = pbVar9 + -8;
        *pbVar9 = 0x30;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_801b7b08;
    }
    do {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_801b7b08:
  if ((*(int *)(param_3 + 0xc) != 0) || (*(char *)(param_3 + 3) != '\0')) {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x2e;
  }
  if (iVar7 == 0) {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x30;
  }
  else {
    for (iVar6 = 0; iVar6 < (int)(iVar7 - (uint)local_40); iVar6 = iVar6 + 1) {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
    }
    uVar4 = iVar7 - iVar6;
    if (iVar6 < iVar7) {
      uVar10 = uVar4 >> 3;
      if (uVar10 != 0) {
        do {
          pbVar9[-1] = pbVar5[-1];
          pbVar9[-2] = pbVar5[-2];
          pbVar9[-3] = pbVar5[-3];
          pbVar9[-4] = pbVar5[-4];
          pbVar9[-5] = pbVar5[-5];
          pbVar9[-6] = pbVar5[-6];
          pbVar9[-7] = pbVar5[-7];
          pbVar5 = pbVar5 + -8;
          pbVar9 = pbVar9 + -8;
          *pbVar9 = *pbVar5;
          uVar10 = uVar10 - 1;
        } while (uVar10 != 0);
        uVar4 = uVar4 & 7;
        if (uVar4 == 0) goto LAB_801b7bd4;
      }
      do {
        pbVar5 = pbVar5 + -1;
        pbVar9 = pbVar9 + -1;
        *pbVar9 = *pbVar5;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
  }
LAB_801b7bd4:
  if (local_44[0] == '\0') {
    if (*(char *)(param_3 + 1) == '\x01') {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x2b;
    }
    else if (*(char *)(param_3 + 1) == '\x02') {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x20;
    }
  }
  else {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x2d;
  }
  return pbVar9;
}

