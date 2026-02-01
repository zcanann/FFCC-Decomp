// Function: F37
// Entry: 801a85b8
// Size: 252 bytes

void F37(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  code *pcVar3;
  
  iVar1 = param_1 * 0x100;
  if (param_2 == 0) {
    uVar2 = *(uint *)(&DAT_803283c0 + iVar1);
    if ((((byte)(&DAT_80328378)[iVar1] ^ uVar2 |
         (uint)(byte)(&DAT_80328379)[iVar1] ^ uVar2 >> 8 |
         (uint)(byte)(&DAT_8032837b)[iVar1] ^ uVar2 >> 0x18 |
         (uint)(byte)(&DAT_8032837a)[iVar1] ^ uVar2 >> 0x10) & 0xff) == 0) {
      param_2 = GBAWriteAsync(param_1,&DAT_80328378 + iVar1,*(undefined4 *)(&DAT_80328370 + iVar1),
                              F39);
    }
    else {
      param_2 = 3;
    }
  }
  if (param_2 != 0) {
    *(undefined4 *)(&DAT_8032838c + iVar1) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar1) = 0;
    pcVar3 = *(code **)(&DAT_80328374 + iVar1);
    if (pcVar3 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
      (*pcVar3)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar1) = param_2;
  return;
}

