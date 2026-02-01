// Function: __throw_catch_compare
// Entry: 801afc28
// Size: 556 bytes

undefined4 __throw_catch_compare(char *param_1,char *param_2,int *param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  
  *param_3 = 0;
  if (param_2 == (char *)0x0) {
    return 1;
  }
  if (*param_2 == 'P') {
    pcVar4 = param_2 + 1;
    if (*pcVar4 == 'C') {
      pcVar4 = param_2 + 2;
    }
    if (*pcVar4 == 'V') {
      pcVar4 = pcVar4 + 1;
    }
    if ((*pcVar4 == 'v') && ((*param_1 == 'P' || (*param_1 == '*')))) {
      return 1;
    }
  }
  cVar1 = *param_1;
  if ((cVar1 == '*') || ((cVar1 < '*' && (cVar1 == '!')))) {
    pcVar4 = param_1 + 1;
    pcVar5 = param_2 + 1;
    if (*param_1 != *param_2) {
      return 0;
    }
    while( true ) {
      while( true ) {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        cVar2 = *pcVar4;
        if (cVar2 != cVar1) break;
        pcVar4 = pcVar4 + 1;
        if (cVar2 == '!') {
          iVar3 = 0;
          for (; *pcVar4 != '!'; pcVar4 = pcVar4 + 1) {
            iVar3 = (int)*pcVar4 + iVar3 * 10 + -0x30;
          }
          *param_3 = iVar3;
          return 1;
        }
      }
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '!');
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '!');
      if (*pcVar4 == '\0') break;
      pcVar5 = param_2 + 1;
    }
    return 0;
  }
  while( true ) {
    cVar1 = *param_1;
    if (((cVar1 != 'P') && (cVar1 != 'R')) || (cVar1 != *param_2)) {
      while( true ) {
        if (*param_1 != *param_2) {
          return 0;
        }
        if (*param_1 == '\0') break;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
      }
      return 1;
    }
    pcVar4 = param_1 + 1;
    pcVar5 = param_2 + 1;
    if (param_2[1] == 'C') {
      if (*pcVar4 == 'C') {
        pcVar4 = param_1 + 2;
      }
      pcVar5 = param_2 + 2;
    }
    param_2 = pcVar5;
    param_1 = pcVar4;
    if (*param_1 == 'C') break;
    if (*param_2 == 'V') {
      if (*param_1 == 'V') {
        param_1 = param_1 + 1;
      }
      param_2 = param_2 + 1;
    }
    if (*param_1 == 'V') {
      return 0;
    }
  }
  return 0;
}

