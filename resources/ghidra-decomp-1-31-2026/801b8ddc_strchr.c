// Function: strchr
// Entry: 801b8ddc
// Size: 48 bytes

char * strchr(int param_1,char param_2)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + -1);
  while( true ) {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 == '\0') break;
    if (*pcVar1 == param_2) {
      return pcVar1;
    }
  }
  if (param_2 == '\0') {
    return pcVar1;
  }
  return (char *)0x0;
}

