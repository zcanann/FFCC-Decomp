// Function: strlen
// Entry: 801b909c
// Size: 28 bytes

int strlen(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(param_1 + -1);
  iVar1 = -1;
  do {
    pcVar2 = pcVar2 + 1;
    iVar1 = iVar1 + 1;
  } while (*pcVar2 != '\0');
  return iVar1;
}

