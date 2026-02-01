// Function: __dt__14CFunnyShapePcsFv
// Entry: 8004e964
// Size: 136 bytes

CFunnyShapePcs * __dt__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs,short param_2)

{
  if (funnyShapePcs != (CFunnyShapePcs *)0x0) {
    (funnyShapePcs->process).manager.vtable = &PTR_PTR_s_CFunnyShapePcs_801ea924;
    __dt__22CPtrArray<P9_GXTexObj>Fv((CPtrArray *)&funnyShapePcs->field_0x61d8,0xffff);
    __dt__29CPtrArray<P15OSFS_TEXTURE_ST>Fv((CPtrArray *)&funnyShapePcs->field_0x61bc,0xffff);
    __dt__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault,0xffff);
    __dt__14CUSBStreamDataFv(&funnyShapePcs->m_usbStreamData,0xffff);
    if (0 < param_2) {
      __dl__FPv(funnyShapePcs);
    }
  }
  return funnyShapePcs;
}

