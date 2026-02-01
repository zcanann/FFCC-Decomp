// Function: GXSetTevOp
// Entry: 801a51d8
// Size: 140 bytes

void GXSetTevOp(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  
  iVar1 = DAT_80333828;
  if (param_1 == 0) {
    puVar3 = (uint *)(&DAT_8021c958 + param_2 * 4);
    puVar5 = (uint *)(&DAT_8021c980 + param_2 * 4);
  }
  else {
    puVar3 = (uint *)(&DAT_8021c96c + param_2 * 4);
    puVar5 = (uint *)(&DAT_8021c994 + param_2 * 4);
  }
  iVar4 = DAT_80333828 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = *puVar3 & 0xffffff | *(uint *)(iVar4 + 0x130) & 0xff000000;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar4 + 0x130) = uVar2;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = *puVar5 & 0xfffff0 | *(uint *)(iVar4 + 0x170) & 0xff00000f;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar4 + 0x170) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

