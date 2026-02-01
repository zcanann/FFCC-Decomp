// Function: strstr
// Entry: 801b8bf0
// Size: 104 bytes

char * strstr(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  if (param_2 == (char *)0x0) {
    return param_1;
  }
  pcVar1 = param_1 + -1;
  if (*param_2 == '\0') {
    return param_1;
  }
  do {
    do {
      pcVar2 = pcVar1;
      pcVar1 = pcVar2 + 1;
      if (*pcVar1 == '\0') {
        return (char *)0x0;
      }
    } while (*pcVar1 != *param_2);
    pcVar3 = param_2 + -1;
    do {
      pcVar2 = pcVar2 + 1;
      pcVar3 = pcVar3 + 1;
      if (*pcVar2 != *pcVar3) break;
    } while (*pcVar2 != '\0');
    if (*pcVar3 == '\0') {
      return pcVar1;
    }
  } while( true );
}

