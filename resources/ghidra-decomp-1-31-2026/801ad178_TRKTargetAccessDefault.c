// Function: TRKTargetAccessDefault
// Entry: 801ad178
// Size: 244 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
TRKTargetAccessDefault(int param_1,uint param_2,undefined4 param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  uVar4 = _DAT_8021cfe0;
  uVar3 = DAT_8021cfdc;
  uVar2 = DAT_8021cfd8;
  uVar1 = DAT_8021cfd4;
  if (param_2 < 0x25) {
    iVar6 = (param_2 - param_1) + 1;
    _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
    *param_4 = iVar6 * 4;
    if (param_5 == 0) {
      uVar5 = TRKReadBuffer_ui32(param_3,&DAT_8032a1c8 + param_1,iVar6);
    }
    else {
      uVar5 = TRKAppendBuffer_ui32(param_3,&DAT_8032a1c8 + param_1,iVar6);
    }
    if (DAT_8021cfe1 != '\0') {
      uVar5 = 0x702;
      *param_4 = 0;
    }
  }
  else {
    uVar5 = 0x701;
  }
  DAT_8021cfd4 = uVar1;
  DAT_8021cfd8 = uVar2;
  DAT_8021cfdc = uVar3;
  _DAT_8021cfe0 = uVar4;
  return uVar5;
}

