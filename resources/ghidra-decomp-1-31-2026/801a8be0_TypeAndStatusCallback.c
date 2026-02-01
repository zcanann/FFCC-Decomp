// Function: TypeAndStatusCallback
// Entry: 801a8be0
// Size: 292 bytes

void TypeAndStatusCallback(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  undefined auStack_2e0 [724];
  
  iVar1 = param_1 * 0x100;
  if (DAT_8032f350 == 0) {
    if (((param_2 & 0xff) == 0) && ((param_2 & 0xffff0000) == 0x40000)) {
      iVar2 = SITransfer(param_1,&DAT_80328320 + iVar1,*(undefined4 *)(&DAT_8032832c + iVar1),
                         &DAT_80328325 + iVar1,*(undefined4 *)(&DAT_80328330 + iVar1),__GBAHandler,
                         (&DAT_80328350)[param_1 * 0x40],(&DAT_80328354)[param_1 * 0x40]);
      if (iVar2 != 0) {
        return;
      }
      *(undefined4 *)(&DAT_80328340 + iVar1) = 2;
    }
    else {
      *(undefined4 *)(&DAT_80328340 + iVar1) = 1;
    }
    pcVar4 = *(code **)(&DAT_80328358 + iVar1);
    if (pcVar4 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328358 + iVar1) = 0;
      (*pcVar4)(param_1);
    }
    if (*(int *)(&DAT_8032833c + iVar1) != 0) {
      uVar3 = OSGetCurrentContext();
      OSClearContext(auStack_2e0);
      OSSetCurrentContext(auStack_2e0);
      pcVar4 = *(code **)(&DAT_8032833c + iVar1);
      *(undefined4 *)(&DAT_8032833c + iVar1) = 0;
      (*pcVar4)(param_1,*(undefined4 *)(&DAT_80328340 + iVar1));
      OSClearContext(auStack_2e0);
      OSSetCurrentContext(uVar3);
      __OSReschedule();
    }
  }
  return;
}

