// Function: TRKTargetAccessMemory
// Entry: 801ad2b8
// Size: 332 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int TRKTargetAccessMemory
              (undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar4 = _DAT_8021cfe0;
  uVar3 = DAT_8021cfdc;
  uVar2 = DAT_8021cfd8;
  uVar1 = DAT_8021cfd4;
  _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
  iVar6 = TRKTargetTranslate(param_2);
  uVar5 = countLeadingZeros(param_5);
  iVar7 = TRKValidMemory32(iVar6,*param_3,uVar5 >> 5);
  if (iVar7 == 0) {
    uVar5 = __TRK_get_MSR();
    if (param_5 == 0) {
      TRK_ppc_memcpy(iVar6,param_1,*param_3,uVar5 | DAT_8032a3c0 & 0x10,uVar5);
      TRK_flush_cache(iVar6,*param_3);
      if (param_2 != iVar6) {
        TRK_flush_cache(param_2,*param_3);
      }
    }
    else {
      TRK_ppc_memcpy(param_1,iVar6,*param_3,uVar5);
    }
  }
  else {
    *param_3 = 0;
  }
  if (DAT_8021cfe1 != '\0') {
    iVar7 = 0x702;
    *param_3 = 0;
  }
  DAT_8021cfd4 = uVar1;
  DAT_8021cfd8 = uVar2;
  DAT_8021cfdc = uVar3;
  _DAT_8021cfe0 = uVar4;
  return iVar7;
}

