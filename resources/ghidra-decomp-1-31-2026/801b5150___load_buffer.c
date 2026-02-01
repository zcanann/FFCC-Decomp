// Function: __load_buffer
// Entry: 801b5150
// Size: 272 bytes

int __load_buffer(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  param_1[9] = param_1[7];
  param_1[10] = param_1[8];
  param_1[10] = param_1[10] - (param_1[6] & param_1[0xb]);
  param_1[0xd] = param_1[6];
  if (param_3 == 1) {
    param_1[10] = param_1[8];
  }
  iVar2 = (*(code *)param_1[0xf])(*param_1,param_1[7],param_1 + 10,param_1[0x12]);
  if (iVar2 == 2) {
    param_1[10] = 0;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_1[10];
  }
  if (iVar2 == 0) {
    param_1[6] = param_1[6] + param_1[10];
    if ((*(byte *)((int)param_1 + 5) >> 3 & 1) == 0) {
      pcVar3 = (char *)param_1[7];
      for (iVar2 = param_1[10]; iVar2 != 0; iVar2 = iVar2 + -1) {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        if (cVar1 == '\n') {
          param_1[6] = param_1[6] + 1;
        }
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}

