// Function: longlong2str
// Entry: 801b80a0
// Size: 788 bytes

char * longlong2str(uint param_1,int param_2,int param_3,char *param_4)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int extraout_r4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  int unaff_r28;
  int unaff_r29;
  undefined4 uVar8;
  uint uVar9;
  longlong lVar10;
  
  pcVar6 = (char *)(param_3 + -1);
  bVar1 = false;
  iVar5 = 0;
  *(undefined *)(param_3 + -1) = 0;
  if ((param_2 == 0 && param_1 == 0) && (*(int *)(param_4 + 0xc) == 0)) {
    if (param_4[3] == '\0') {
      return pcVar6;
    }
    if (param_4[5] != 'o') {
      return pcVar6;
    }
  }
  lVar10 = CONCAT44(param_1,param_2);
  switch(param_4[5]) {
  case 'X':
  case 'x':
    unaff_r28 = 0x10;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    break;
  case 'd':
  case 'i':
    unaff_r28 = 10;
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    if ((param_1 ^ 0x80000000) < 0x80000000) {
      bVar1 = true;
      lVar10 = CONCAT44(-((param_2 != 0) + param_1),-param_2);
    }
    break;
  case 'o':
    unaff_r28 = 8;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    break;
  case 'u':
    unaff_r28 = 10;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
  }
  do {
    pcVar7 = pcVar6;
    iVar3 = iVar5;
    uVar8 = (undefined4)((ulonglong)lVar10 >> 0x20);
    __mod2u(uVar8,(int)lVar10,unaff_r29,unaff_r28);
    lVar10 = __div2u(uVar8,(int)lVar10,unaff_r29,unaff_r28);
    cVar2 = (char)extraout_r4;
    if (extraout_r4 < 10) {
      cVar2 = cVar2 + '0';
    }
    else if (param_4[5] == 'x') {
      cVar2 = cVar2 + 'W';
    }
    else {
      cVar2 = cVar2 + '7';
    }
    pcVar6 = pcVar7 + -1;
    *pcVar6 = cVar2;
    iVar5 = iVar3 + 1;
  } while (lVar10 != 0);
  if (((unaff_r28 == 8 && unaff_r29 == 0) && (param_4[3] != '\0')) && (*pcVar6 != '0')) {
    iVar5 = iVar3 + 2;
    pcVar6 = pcVar7 + -2;
    *pcVar6 = '0';
  }
  if (*param_4 == '\x02') {
    *(undefined4 *)(param_4 + 0xc) = *(undefined4 *)(param_4 + 8);
    if ((bVar1) || (param_4[1] != '\0')) {
      *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + -1;
    }
    if ((unaff_r28 == 0x10 && unaff_r29 == 0) && (param_4[3] != '\0')) {
      *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + -2;
    }
  }
  iVar3 = *(int *)(param_4 + 0xc);
  if (0x1fd < iVar3 + (param_3 - (int)pcVar6)) {
    return (char *)0x0;
  }
  uVar4 = iVar3 - iVar5;
  if (iVar5 < iVar3) {
    uVar9 = uVar4 >> 3;
    if (uVar9 != 0) {
      do {
        builtin_strncpy(pcVar6 + 0xfffffff8,"00000000",8);
        pcVar6 = pcVar6 + -8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_801b832c;
    }
    do {
      pcVar6 = pcVar6 + -1;
      *pcVar6 = '0';
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_801b832c:
  if ((unaff_r28 == 0x10 && unaff_r29 == 0) && (param_4[3] != '\0')) {
    pcVar6[-1] = param_4[5];
    pcVar6 = pcVar6 + -2;
    *pcVar6 = '0';
  }
  if (bVar1) {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = '-';
  }
  else if (param_4[1] == '\x01') {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = '+';
  }
  else if (param_4[1] == '\x02') {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = ' ';
  }
  return pcVar6;
}

