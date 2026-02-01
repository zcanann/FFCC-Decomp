// Function: strrchr
// Entry: 801b8d94
// Size: 72 bytes

char * strrchr(int param_1,char param_2)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(param_1 + -1);
  pcVar1 = (char *)0x0;
  while( true ) {
    pcVar2 = pcVar2 + 1;
    if (*pcVar2 == '\0') break;
    if (*pcVar2 == param_2) {
      pcVar1 = pcVar2;
    }
  }
  if (pcVar1 != (char *)0x0) {
    return pcVar1;
  }
  if (param_2 != '\0') {
    return (char *)0x0;
  }
  return pcVar2;
}

