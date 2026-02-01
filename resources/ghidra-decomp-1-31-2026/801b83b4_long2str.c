// Function: long2str
// Entry: 801b83b4
// Size: 600 bytes

char * long2str(uint param_1,int param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  uint in_r0;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  
  *(undefined *)(param_2 + -1) = 0;
  bVar2 = false;
  if (((param_1 == 0) && (*(int *)(param_3 + 0xc) == 0)) &&
     ((param_3[3] == '\0' || (param_3[5] != 'o')))) {
    return (char *)(param_2 + -1);
  }
  switch(param_3[5]) {
  case 'X':
  case 'x':
    in_r0 = 0x10;
    param_3[1] = '\0';
    break;
  case 'd':
  case 'i':
    in_r0 = 10;
    if ((int)param_1 < 0) {
      param_1 = -param_1;
      bVar2 = true;
    }
    break;
  case 'o':
    in_r0 = 8;
    param_3[1] = '\0';
    break;
  case 'u':
    in_r0 = 10;
    param_3[1] = '\0';
  }
  cVar1 = param_3[5];
  pcVar5 = (char *)(param_2 + -1);
  iVar7 = 0;
  do {
    iVar6 = iVar7;
    pcVar4 = pcVar5;
    iVar7 = param_1 - (param_1 / in_r0) * in_r0;
    param_1 = param_1 / in_r0;
    cVar8 = (char)iVar7;
    if (iVar7 < 10) {
      cVar8 = cVar8 + '0';
    }
    else if (cVar1 == 'x') {
      cVar8 = cVar8 + 'W';
    }
    else {
      cVar8 = cVar8 + '7';
    }
    pcVar4[-1] = cVar8;
    pcVar5 = pcVar4 + -1;
    iVar7 = iVar6 + 1;
  } while (param_1 != 0);
  if (((in_r0 == 8) && (param_3[3] != '\0')) && (*pcVar5 != '0')) {
    iVar7 = iVar6 + 2;
    pcVar5 = pcVar4 + -2;
    *pcVar5 = '0';
  }
  if (*param_3 == '\x02') {
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_3 + 8);
    if ((bVar2) || (param_3[1] != '\0')) {
      *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -1;
    }
    if ((in_r0 == 0x10) && (param_3[3] != '\0')) {
      *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -2;
    }
  }
  iVar6 = *(int *)(param_3 + 0xc);
  if (0x1fd < iVar6 + (param_2 - (int)pcVar5)) {
    return (char *)0x0;
  }
  uVar3 = iVar6 - iVar7;
  if (iVar7 < iVar6) {
    uVar9 = uVar3 >> 3;
    if (uVar9 != 0) {
      do {
        builtin_strncpy(pcVar5 + 0xfffffff8,"00000000",8);
        pcVar5 = pcVar5 + -8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) goto LAB_801b85a4;
    }
    do {
      pcVar5 = pcVar5 + -1;
      *pcVar5 = '0';
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
LAB_801b85a4:
  if ((in_r0 == 0x10) && (param_3[3] != '\0')) {
    pcVar5[-1] = param_3[5];
    pcVar5 = pcVar5 + -2;
    *pcVar5 = '0';
  }
  if (bVar2) {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = '-';
  }
  else if (param_3[1] == '\x01') {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = '+';
  }
  else if (param_3[1] == '\x02') {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = ' ';
  }
  return pcVar5;
}

