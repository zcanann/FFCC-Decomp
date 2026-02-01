// Function: DMAErrorHandler
// Entry: 8017d2a4
// Size: 352 bytes

void DMAErrorHandler(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = PPCMfhid2();
  OSReport(s_Machine_check_received_80216a14);
  OSReport(s_HID2___0x_x_SRR1___0x_x_80216a2c,uVar1,*(undefined4 *)(param_2 + 0x19c));
  if (((uVar1 & 0xf00000) == 0) || ((*(uint *)(param_2 + 0x19c) & 0x200000) == 0)) {
    OSReport(s_Machine_check_was_not_DMA_locked_80216a48);
    OSDumpContext(param_2);
    PPCHalt();
  }
  OSReport(s_DMAErrorHandler____An_error_occu_80216a78);
  OSReport(s_The_following_errors_have_been_d_80216ab4);
  if ((uVar1 & 0x800000) != 0) {
    OSReport(s___Requested_a_locked_cache_tag_t_80216aec);
  }
  if ((uVar1 & 0x400000) != 0) {
    OSReport(s___DMA_attempted_to_access_normal_80216b2c);
  }
  if ((uVar1 & 0x200000) != 0) {
    OSReport(s___DMA_missed_in_data_cache_80216b58);
  }
  if ((uVar1 & 0x100000) != 0) {
    OSReport(s___DMA_queue_overflowed_80216b78);
  }
  PPCMthid2(uVar1);
  return;
}

