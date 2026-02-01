// Function: __dt__18CMaterialEditorPcsFv
// Entry: 8004c6a0
// Size: 124 bytes

CMaterialEditorPcs *
__dt__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs,short param_2)

{
  if (materialEditorPcs != (CMaterialEditorPcs *)0x0) {
    (materialEditorPcs->process).manager.vtable = &PTR_PTR_s_CMaterialEditorPcs_801ea644;
    __dt__5ZLISTFv(&materialEditorPcs->zlistB,0xffff);
    __dt__5ZLISTFv(&materialEditorPcs->zlistA,0xffff);
    __dt__14CUSBStreamDataFv(&materialEditorPcs->m_usbStream,0xffff);
    if (0 < param_2) {
      __dl__FPv(materialEditorPcs);
    }
  }
  return materialEditorPcs;
}

