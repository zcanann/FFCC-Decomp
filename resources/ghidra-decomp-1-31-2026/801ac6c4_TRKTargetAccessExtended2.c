// Function: TRKTargetAccessExtended2
// Entry: 801ac6c4
// Size: 1080 bytes

/* WARNING: Removing unreachable block (ram,0x801aca48) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int TRKTargetAccessExtended2(uint param_1,uint param_2,undefined4 param_3,int *param_4,int param_5)

{
  int iVar1;
  undefined4 extraout_r4;
  uint uVar2;
  uint local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  uint local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  uint local_e4;
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
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  
  if (param_2 < 0x20) {
    local_11c = DAT_8021cfd4;
    local_118 = DAT_8021cfd8;
    local_114 = DAT_8021cfdc;
    local_110 = _DAT_8021cfe0;
    _DAT_8021cfe1 = (uint3)DAT_8021cfe0_1._1_2_;
    local_64 = DAT_801e6b10;
    local_60 = DAT_801e6b14;
    local_5c = DAT_801e6b18;
    local_58 = DAT_801e6b1c;
    local_54 = DAT_801e6b20;
    local_50 = DAT_801e6b24;
    local_4c = DAT_801e6b28;
    local_6c = 0x7c98e2a6;
    local_68 = 0x90830000;
    local_48 = 0x4e800020;
    TRK_flush_cache(&local_6c,0x28);
    (*(code *)&local_6c)(&local_128,&DAT_8032a68c);
    local_128 = local_128 | 0xa0000000;
    local_8c = DAT_801e6b10;
    local_88 = DAT_801e6b14;
    local_84 = DAT_801e6b18;
    local_80 = DAT_801e6b1c;
    local_7c = DAT_801e6b20;
    local_78 = DAT_801e6b24;
    local_74 = DAT_801e6b28;
    local_94 = 0x80830000;
    local_90 = 0x7c98e3a6;
    local_70 = 0x4e800020;
    TRK_flush_cache(&local_94,0x28);
    (*(code *)&local_94)(&local_128,&DAT_8032a68c);
    local_128 = 0;
    local_b4 = DAT_801e6b10;
    local_b0 = DAT_801e6b14;
    local_ac = DAT_801e6b18;
    local_a8 = DAT_801e6b1c;
    local_a4 = DAT_801e6b20;
    local_a0 = DAT_801e6b24;
    local_9c = DAT_801e6b28;
    local_bc = 0x80830000;
    local_b8 = 0x7c90e3a6;
    local_98 = 0x4e800020;
    TRK_flush_cache(&local_bc,0x28);
    (*(code *)&local_bc)(&local_128,&DAT_8032a68c);
    uVar2 = param_1 << 0x15;
    *param_4 = 0;
    iVar1 = 0;
    while ((param_1 <= param_2 && (iVar1 == 0))) {
      if (param_5 == 0) {
        TRKReadBuffer1_ui64(param_3,&local_124);
        local_10c = uVar2 | 0xe0030000;
        local_108 = DAT_801e6b34;
        local_104 = DAT_801e6b38;
        local_100 = DAT_801e6b3c;
        local_fc = DAT_801e6b40;
        local_f8 = DAT_801e6b44;
        local_f4 = DAT_801e6b48;
        local_f0 = DAT_801e6b4c;
        local_ec = DAT_801e6b50;
        local_e8 = 0x4e800020;
        TRK_flush_cache(&local_10c,0x28);
        (*(code *)&local_10c)(&local_124,&DAT_8032a68c);
        iVar1 = 0;
      }
      else {
        local_e4 = uVar2 | 0xe0030000;
        local_e0 = DAT_801e6b34;
        local_dc = DAT_801e6b38;
        local_d8 = DAT_801e6b3c;
        local_d4 = DAT_801e6b40;
        local_d0 = DAT_801e6b44;
        local_cc = DAT_801e6b48;
        local_c8 = DAT_801e6b4c;
        local_c4 = DAT_801e6b50;
        if (param_5 != 0) {
          local_e4 = uVar2 | 0xf0030000;
        }
        local_c0 = 0x4e800020;
        TRK_flush_cache(&local_e4,0x28);
        (*(code *)&local_e4)(&local_124,&DAT_8032a68c);
        iVar1 = TRKAppendBuffer1_ui64(param_3,extraout_r4,local_124,local_120);
      }
      uVar2 = uVar2 + 0x200000;
      param_1 = param_1 + 1;
      *param_4 = *param_4 + 8;
    }
    if (DAT_8021cfe1 != '\0') {
      iVar1 = 0x702;
      *param_4 = 0;
    }
    DAT_8021cfd4 = local_11c;
    DAT_8021cfd8 = local_118;
    DAT_8021cfdc = local_114;
    _DAT_8021cfe0 = local_110;
  }
  else {
    iVar1 = 0x701;
  }
  return iVar1;
}

