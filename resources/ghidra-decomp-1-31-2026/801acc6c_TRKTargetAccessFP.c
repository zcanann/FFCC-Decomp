// Function: TRKTargetAccessFP
// Entry: 801acc6c
// Size: 1292 bytes

/* WARNING: Removing unreachable block (ram,0x801acfcc) */
/* WARNING: Removing unreachable block (ram,0x801ad07c) */
/* WARNING: Removing unreachable block (ram,0x801acf80) */
/* WARNING: Removing unreachable block (ram,0x801ad0e4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int TRKTargetAccessFP(uint param_1,uint param_2,undefined4 param_3,int *param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  uint local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  if (param_2 < 0x22) {
    local_e0 = DAT_8021cfd4;
    local_dc = DAT_8021cfd8;
    local_d8 = DAT_8021cfdc;
    local_d4 = _DAT_8021cfe0;
    _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
    uVar2 = __TRK_get_MSR();
    __TRK_set_MSR(uVar2 | 0x2000);
    *param_4 = 0;
    uVar2 = param_1 << 0x15;
    iVar1 = 0;
    while ((param_1 <= param_2 && (iVar1 == 0))) {
      if (param_5 == 0) {
        TRKReadBuffer1_ui64(param_3,&local_e8);
        local_80 = DAT_801e6b58;
        local_7c = DAT_801e6b5c;
        local_78 = DAT_801e6b60;
        local_74 = DAT_801e6b64;
        local_70 = DAT_801e6b68;
        local_6c = DAT_801e6b6c;
        local_68 = DAT_801e6b70;
        local_64 = DAT_801e6b74;
        local_60 = DAT_801e6b78;
        local_5c = DAT_801e6b7c;
        if (param_1 < 0x20) {
          local_80 = uVar2 | 0xc8030000;
          local_5c = 0x4e800020;
          TRK_flush_cache(&local_80,0x28);
          (*(code *)&local_80)(&local_e8,&DAT_8032a68c);
        }
        else if (param_1 == 0x20) {
          WriteFPSCR(&local_e8);
          local_e8 = 0;
        }
        else if (param_1 == 0x21) {
          local_e8 = local_e4;
          local_c8 = DAT_801e6b10;
          local_c4 = DAT_801e6b14;
          local_c0 = DAT_801e6b18;
          local_bc = DAT_801e6b1c;
          local_b8 = DAT_801e6b20;
          local_b4 = DAT_801e6b24;
          local_b0 = DAT_801e6b28;
          local_cc = 0x7c9efba6;
          local_d0 = 0x80830000;
          local_ac = 0x4e800020;
          TRK_flush_cache(&local_d0,0x28);
          (*(code *)&local_d0)(&local_e8,&DAT_8032a68c);
        }
        iVar1 = 0;
      }
      else {
        local_58 = DAT_801e6b58;
        local_54 = DAT_801e6b5c;
        local_50 = DAT_801e6b60;
        local_4c = DAT_801e6b64;
        local_48 = DAT_801e6b68;
        local_44 = DAT_801e6b6c;
        local_40 = DAT_801e6b70;
        local_3c = DAT_801e6b74;
        local_38 = DAT_801e6b78;
        local_34 = DAT_801e6b7c;
        if (param_1 < 0x20) {
          local_58 = uVar2 | 0xc8030000;
          if (param_5 != 0) {
            local_58 = uVar2 | 0xd8030000;
          }
          local_34 = 0x4e800020;
          TRK_flush_cache(&local_58,0x28);
          (*(code *)&local_58)(&local_e8,&DAT_8032a68c);
          uVar3 = extraout_r4;
        }
        else if (param_1 == 0x20) {
          if (param_5 == 0) {
            WriteFPSCR(&local_e8);
          }
          else {
            ReadFPSCR(&local_e8);
          }
          uVar3 = local_e8;
          local_e8 = 0;
        }
        else {
          uVar3 = DAT_801e6b74;
          if (param_1 == 0x21) {
            if (param_5 == 0) {
              local_e8 = local_e4;
            }
            local_a0 = DAT_801e6b10;
            local_9c = DAT_801e6b14;
            local_98 = DAT_801e6b18;
            local_94 = DAT_801e6b1c;
            local_90 = DAT_801e6b20;
            local_8c = DAT_801e6b24;
            local_88 = DAT_801e6b28;
            if (param_5 == 0) {
              local_a8 = 0x80830000;
              local_a4 = 0x7c9efba6;
            }
            else {
              local_a4 = 0x90830000;
              local_a8 = 0x7c9efaa6;
            }
            local_84 = 0x4e800020;
            TRK_flush_cache(&local_a8,0x28);
            (*(code *)&local_a8)(&local_e8,&DAT_8032a68c);
            uVar3 = extraout_r4_00;
            if (param_5 != 0) {
              uVar3 = 0;
              local_e4 = local_e8;
              local_e8 = 0;
            }
          }
        }
        iVar1 = TRKAppendBuffer1_ui64(param_3,uVar3,local_e8,local_e4);
      }
      uVar2 = uVar2 + 0x200000;
      param_1 = param_1 + 1;
      *param_4 = *param_4 + 8;
    }
    if (DAT_8021cfe1 != '\0') {
      iVar1 = 0x702;
      *param_4 = 0;
    }
    DAT_8021cfd4 = local_e0;
    DAT_8021cfd8 = local_dc;
    DAT_8021cfdc = local_d8;
    _DAT_8021cfe0 = local_d4;
  }
  else {
    iVar1 = 0x701;
  }
  return iVar1;
}

