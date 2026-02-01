// Function: memchr
// Entry: 801b6628
// Size: 44 bytes

char * memchr(int param_1,char param_2,int param_3)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + -1);
  param_3 = param_3 + 1;
  do {
    param_3 = param_3 + -1;
    if (param_3 == 0) {
      return (char *)0x0;
    }
    pcVar1 = pcVar1 + 1;
  } while (*pcVar1 != param_2);
  return pcVar1;
}

