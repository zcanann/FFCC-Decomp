// Function: InitMetroTRKCommTable
// Entry: 801ae388
// Size: 620 bytes

undefined4 InitMetroTRKCommTable(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  OSReport(s_Devkit_set_to____ld_801e6ba8,param_1);
  DAT_8032a6b0 = 0;
  if (param_1 == 2) {
    OSReport(s_MetroTRK___Set_to_BBA_801e6bc0);
    DAT_8032a6b0 = 1;
    uVar1 = 0;
    DAT_8021d038 = udp_cc_initialize;
    DAT_8021d050 = udp_cc_open;
    DAT_8021d054 = udp_cc_open;
    DAT_8021d048 = udp_cc_read;
    DAT_8021d04c = udp_cc_write;
    DAT_8021d040 = udp_cc_shutdown;
    DAT_8021d044 = udp_cc_peek;
    DAT_8021d058 = udp_cc_pre_continue;
    DAT_8021d05c = udp_cc_post_stop;
    DAT_8021d03c = (code *)0x0;
  }
  else if (param_1 == 1) {
    OSReport(s_MetroTRK___Set_to_GDEV_hardware_801e6bd8);
    uVar1 = Hu_IsStub();
    DAT_8021d038 = gdev_cc_initialize;
    DAT_8021d050 = gdev_cc_open;
    DAT_8021d054 = gdev_cc_close;
    DAT_8021d048 = gdev_cc_read;
    DAT_8021d04c = gdev_cc_write;
    DAT_8021d040 = gdev_cc_shutdown;
    DAT_8021d044 = gdev_cc_peek;
    DAT_8021d058 = gdev_cc_pre_continue;
    DAT_8021d05c = gdev_cc_post_stop;
    DAT_8021d03c = gdev_cc_initinterrupts;
  }
  else if (param_1 == 0) {
    OSReport(s_MetroTRK___Set_to_AMC_DDH_hardwa_801e6bfc);
    uVar1 = AMC_IsStub();
    DAT_8021d038 = ddh_cc_initialize;
    DAT_8021d050 = ddh_cc_open;
    DAT_8021d054 = ddh_cc_close;
    DAT_8021d048 = ddh_cc_read;
    DAT_8021d04c = ddh_cc_write;
    DAT_8021d040 = ddh_cc_shutdown;
    DAT_8021d044 = ddh_cc_peek;
    DAT_8021d058 = ddh_cc_pre_continue;
    DAT_8021d05c = ddh_cc_post_stop;
    DAT_8021d03c = ddh_cc_initinterrupts;
  }
  else {
    OSReport(s_MetroTRK___Set_to_UNKNOWN_hardwa_801e6c20,param_1);
    OSReport(s_MetroTRK___Invalid_hardware_ID_p_801e6c4c);
    OSReport(s_MetroTRK___Defaulting_to_GDEV_Ha_801e6c7c);
  }
  return uVar1;
}

