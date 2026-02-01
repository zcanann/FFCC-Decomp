// Function: __GBAHandler
// Entry: 801a8a64
// Size: 220 bytes

void __GBAHandler(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  code *pcVar2;
  undefined auStack_2e0 [724];
  
  iVar1 = param_1 * 0x100;
  if (DAT_8032f350 == 0) {
    if ((param_2 & 0xf) == 0) {
      *(undefined4 *)(&DAT_80328340 + iVar1) = 0;
    }
    else {
      *(undefined4 *)(&DAT_80328340 + iVar1) = 1;
    }
    pcVar2 = *(code **)(&DAT_80328358 + iVar1);
    if (pcVar2 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328358 + iVar1) = 0;
      (*pcVar2)(param_1);
    }
    if (*(int *)(&DAT_8032833c + iVar1) != 0) {
      OSClearContext(auStack_2e0);
      OSSetCurrentContext(auStack_2e0);
      pcVar2 = *(code **)(&DAT_8032833c + iVar1);
      *(undefined4 *)(&DAT_8032833c + iVar1) = 0;
      (*pcVar2)(param_1,*(undefined4 *)(&DAT_80328340 + iVar1));
      OSClearContext(auStack_2e0);
      OSSetCurrentContext(param_3);
    }
  }
  return;
}

