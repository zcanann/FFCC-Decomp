// Function: GetOrder__7CSystemFi
// Entry: 800214d8
// Size: 56 bytes

int GetOrder__7CSystemFi(CSystem *system,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 < 0) {
    return 0;
  }
  iVar1 = *(int *)((int)&(system->m_stopwatch).max + 4);
  iVar2 = 0;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (iVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x14);
    iVar2 = iVar2 + 1;
  }
  return iVar1;
}

