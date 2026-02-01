// Function: TRKTargetAccessARAM
// Entry: 801abef8
// Size: 196 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
TRKTargetAccessARAM(undefined4 param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar4 = _DAT_8021cfe0;
  uVar3 = DAT_8021cfdc;
  uVar2 = DAT_8021cfd8;
  uVar1 = DAT_8021cfd4;
  uVar5 = 0;
  _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
  if (param_4 == 0) {
    TRK__write_aram();
  }
  else {
    TRK__read_aram();
  }
  if (DAT_8021cfe1 != '\0') {
    uVar5 = 0x702;
    *param_3 = 0;
  }
  DAT_8021cfd4 = uVar1;
  DAT_8021cfd8 = uVar2;
  DAT_8021cfdc = uVar3;
  _DAT_8021cfe0 = uVar4;
  return uVar5;
}

