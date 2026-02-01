// Function: strcat
// Entry: 801b8f74
// Size: 44 bytes

void strcat(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_2 + -1;
  pcVar2 = param_1 + -1;
  do {
    pcVar4 = pcVar2;
    pcVar2 = pcVar4 + 1;
  } while (pcVar4[1] != '\0');
  do {
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
  } while (cVar1 != '\0');
  return;
}

