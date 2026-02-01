// Function: __dt__8CPartPcsFv
// Entry: 80053ca0
// Size: 100 bytes

CPartPcs * __dt__8CPartPcsFv(CPartPcs *partPcs,short param_2)

{
  if (partPcs != (CPartPcs *)0x0) {
    (partPcs->process).manager.vtable = &PTR_PTR_s_CPartPcs_801eada4;
    __dt__14CUSBStreamDataFv(&partPcs->m_usbStreamData,0xffff);
    if (0 < param_2) {
      __dl__FPv(partPcs);
    }
  }
  return partPcs;
}

