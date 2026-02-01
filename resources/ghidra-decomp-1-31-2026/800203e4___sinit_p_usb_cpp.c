// Function: __sinit_p_usb_cpp
// Entry: 800203e4
// Size: 176 bytes

void __sinit_p_usb_cpp(void)

{
  USBPcs.process.manager.vtable = (CManager)&PTR_PTR_s_CUSBPcs_801e8830;
  DAT_801e86b8 = DAT_801e8690;
  DAT_801e86bc = DAT_801e8694;
  DAT_801e86c0 = PTR_create__7CUSBPcsFv_801e8698;
  DAT_801e86c4 = DAT_801e869c;
  DAT_801e86c8 = DAT_801e86a0;
  DAT_801e86cc = PTR_destroy__7CUSBPcsFv_801e86a4;
  DAT_801e86d0 = DAT_801e86a8;
  DAT_801e86d4 = DAT_801e86ac;
  DAT_801e86d8 = PTR_func__7CUSBPcsFv_801e86b0;
  return;
}

