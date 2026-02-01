// Function: SearchWaveBase__9CRedEntryFi
// Entry: 801c14f8
// Size: 68 bytes

int SearchWaveBase__9CRedEntryFi(int *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  do {
    if (param_2 == *piVar1) {
      return piVar1[2];
    }
    piVar1 = piVar1 + 4;
  } while (piVar1 < (int *)(*param_1 + 0x400));
  return 0;
}

