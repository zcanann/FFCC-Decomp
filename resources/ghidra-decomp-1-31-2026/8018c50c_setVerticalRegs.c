// Function: setVerticalRegs
// Entry: 8018c50c
// Size: 416 bytes

void setVerticalRegs(ushort param_1,ushort param_2,ushort param_3,short param_4,short param_5,
                    short param_6,short param_7,short param_8,int param_9)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  
  if ((DAT_8030cbb4 & 1) == 0) {
    uVar2 = 2;
    sVar3 = 1;
  }
  else {
    uVar2 = 1;
    sVar3 = 2;
  }
  if ((uint)param_1 == ((int)(uint)param_1 >> 1) * 2) {
    sVar1 = sVar3 * (((short)uVar2 * param_4 - param_2) - param_1);
    DAT_8030cb56 = param_5 + sVar3 * param_1;
    DAT_8030cb54 = param_7 + sVar1;
    DAT_8030cb5a = param_6 + sVar3 * param_1;
    DAT_8030cb58 = param_8 + sVar1;
  }
  else {
    sVar1 = sVar3 * (((short)uVar2 * param_4 - param_2) - param_1);
    DAT_8030cb56 = param_6 + sVar3 * param_1;
    DAT_8030cb54 = param_8 + sVar1;
    DAT_8030cb5a = param_5 + sVar3 * param_1;
    DAT_8030cb58 = param_7 + sVar1;
  }
  uVar2 = param_2 / uVar2;
  if (param_9 != 0) {
    sVar3 = (short)uVar2 * 2 + -2;
    DAT_8030cb56 = DAT_8030cb56 + sVar3;
    DAT_8030cb5a = DAT_8030cb5a + sVar3;
    uVar2 = 0;
    DAT_8030cb54 = DAT_8030cb54 + 2;
    DAT_8030cb58 = DAT_8030cb58 + 2;
  }
  DAT_8030cb48 = param_3 & 0xff | (ushort)(uVar2 << 4);
  DAT_8032f108 = DAT_8032f108 | 0x83c00000;
  return;
}

