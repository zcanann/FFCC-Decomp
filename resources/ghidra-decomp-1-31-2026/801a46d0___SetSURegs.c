// Function: __SetSURegs
// Entry: 801a46d0
// Size: 184 bytes

void __SetSURegs(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = DAT_80333828;
  param_2 = param_2 * 4;
  iVar2 = DAT_80333828 + param_1 * 4;
  uVar3 = *(uint *)(iVar2 + 0x45c);
  iVar5 = DAT_80333828 + param_2;
  iVar6 = DAT_80333828 + param_2;
  *(uint *)(DAT_80333828 + param_2 + 0xb8) =
       uVar3 & 0x3ff | *(uint *)(DAT_80333828 + param_2 + 0xb8) & 0xffff0000;
  *(uint *)(iVar5 + 0xd8) = uVar3 >> 10 & 0x3ff | *(uint *)(iVar5 + 0xd8) & 0xffff0000;
  uVar4 = *(uint *)(iVar2 + 0x47c);
  uVar3 = countLeadingZeros(1 - (uVar4 & 3));
  *(uint *)(iVar6 + 0xb8) = *(uint *)(iVar6 + 0xb8) & 0xfffeffff | (uVar3 & 0x1fe0) << 0xb;
  uVar3 = countLeadingZeros(1 - (uVar4 >> 2 & 3));
  *(uint *)(iVar1 + param_2 + 0xd8) =
       *(uint *)(iVar1 + param_2 + 0xd8) & 0xfffeffff | (uVar3 & 0x1fe0) << 0xb;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + param_2 + 0xb8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + param_2 + 0xd8);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

