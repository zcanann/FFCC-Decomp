// Function: F33
// Entry: 801a82e8
// Size: 372 bytes

void F33(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte *pbVar3;
  code *pcVar4;
  int iVar5;
  
  iVar1 = param_1 * 0x100;
  if (param_2 == 0) {
    *(undefined4 *)(&DAT_80328380 + iVar1) = 0x21;
    iVar5 = 0;
    while( true ) {
      if (0x23 < *(int *)(&DAT_80328380 + iVar1)) break;
      pbVar3 = &DAT_8021cb48 + *(int *)(&DAT_80328380 + iVar1);
      iVar5 = ((uint)(byte)(&DAT_80328378)[iVar1] ^
               *(uint *)(&DAT_80328360 + (uint)*pbVar3 * 4 + 0x3c + iVar1) |
              (uint)(byte)(&DAT_80328379)[iVar1] ^
              *(uint *)(&DAT_80328360 + (uint)*pbVar3 * 4 + 0x3c + iVar1) >> 8 |
              (uint)(byte)(&DAT_8032837b)[iVar1] ^
              *(uint *)(&DAT_80328360 + (uint)*pbVar3 * 4 + 0x3c + iVar1) >> 0x18 |
              (uint)(byte)(&DAT_8032837a)[iVar1] ^
              *(uint *)(&DAT_80328360 + (uint)*pbVar3 * 4 + 0x3c + iVar1) >> 0x10) << 0x18;
      if (iVar5 == 0) break;
      *(int *)(&DAT_80328380 + iVar1) = *(int *)(&DAT_80328380 + iVar1) + 1;
    }
    if (iVar5 == 0) {
      uVar2 = OSGetTick();
      *(undefined4 *)(&DAT_80328384 + iVar1) = uVar2;
      param_2 = GBAGetStatusAsync(param_1,*(undefined4 *)(&DAT_80328370 + iVar1),F35);
    }
    else {
      param_2 = 3;
    }
  }
  if (param_2 != 0) {
    *(undefined4 *)(&DAT_8032838c + iVar1) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar1) = 0;
    pcVar4 = *(code **)(&DAT_80328374 + iVar1);
    if (pcVar4 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
      (*pcVar4)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar1) = param_2;
  return;
}

