// Function: TRKTargetAccessExtended1
// Entry: 801acafc
// Size: 368 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint TRKTargetAccessExtended1(uint param_1,uint param_2,undefined4 param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  uVar4 = _DAT_8021cfe0;
  uVar3 = DAT_8021cfdc;
  uVar2 = DAT_8021cfd8;
  uVar1 = DAT_8021cfd4;
  if (param_2 < 0x61) {
    _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
    *param_4 = 0;
    if (param_1 <= param_2) {
      iVar6 = param_2 - param_1;
      iVar5 = iVar6 + 1;
      *param_4 = *param_4 + iVar5 * 4;
      puVar7 = &DAT_8032a370 + param_1;
      if (param_5 == 0) {
        if ((puVar7 < (undefined4 *)0x8032a3b5) && ((undefined4 *)0x8032a3af < puVar7 + iVar6)) {
          DAT_8021cfc8 = 1;
        }
        if ((puVar7 < (undefined4 *)0x8032a441) && ((undefined4 *)0x8032a43f < puVar7 + iVar6)) {
          DAT_8021cfc9 = 1;
        }
        param_1 = TRKReadBuffer_ui32(param_3,puVar7,iVar5);
      }
      else {
        param_1 = TRKAppendBuffer_ui32(param_3,puVar7,iVar5);
      }
    }
    if (DAT_8021cfe1 != '\0') {
      param_1 = 0x702;
      *param_4 = 0;
    }
  }
  else {
    param_1 = 0x701;
  }
  DAT_8021cfd4 = uVar1;
  DAT_8021cfd8 = uVar2;
  DAT_8021cfdc = uVar3;
  _DAT_8021cfe0 = uVar4;
  return param_1;
}

