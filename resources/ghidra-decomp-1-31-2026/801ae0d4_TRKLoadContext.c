// Function: TRKLoadContext
// Entry: 801ae0d4
// Size: 136 bytes

void TRKLoadContext(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(ushort *)(param_1 + 0x1a2);
  uVar2 = (uint)uVar1;
  uVar3 = uVar1 & 2;
  if ((uVar1 & 2) != 0) {
    *(ushort *)(param_1 + 0x1a2) = uVar1 & 0xfffd;
    uVar2 = *(uint *)(param_1 + 0x14);
    uVar3 = *(uint *)(param_1 + 0x18);
    param_5 = *(undefined4 *)(param_1 + 0x1c);
    param_6 = *(undefined4 *)(param_1 + 0x20);
    param_7 = *(undefined4 *)(param_1 + 0x24);
    param_8 = *(undefined4 *)(param_1 + 0x28);
  }
  TRKInterruptHandler(param_2,*(undefined4 *)(param_1 + 0x19c),uVar2,uVar3,param_5,param_6,param_7,
                      param_8);
  return;
}

