// Function: F29
// Entry: 801a7bf4
// Size: 128 bytes

void F29(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1 * 0x100;
  if (param_2 == 0) {
    __GBAX02(param_1,&DAT_80328378 + iVar1);
  }
  else {
    *(undefined4 *)(&DAT_8032838c + iVar1) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar1) = 0;
    pcVar2 = *(code **)(&DAT_80328374 + iVar1);
    if (pcVar2 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
      (*pcVar2)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar1) = param_2;
  return;
}

