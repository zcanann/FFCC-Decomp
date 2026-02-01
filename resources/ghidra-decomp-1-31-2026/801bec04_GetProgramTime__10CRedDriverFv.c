// Function: GetProgramTime__10CRedDriverFv
// Entry: 801bec04
// Size: 68 bytes

int GetProgramTime__10CRedDriverFv(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = DAT_8032f3cc;
  do {
    iVar1 = *piVar3;
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + iVar1;
  } while (piVar3 < DAT_8032f3cc + 100);
  return iVar2;
}

