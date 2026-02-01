// Function: __sinit_p_MaterialEditor_cpp
// Entry: 8004c588
// Size: 280 bytes

void __sinit_p_MaterialEditor_cpp(void)

{
  MaterialEditorPcs.process.manager.vtable = (CManager)&PTR_PTR_s_CMaterialEditorPcs_801ea644;
  __ct__14CUSBStreamDataFv(&MaterialEditorPcs.m_usbStream);
  __ct__5ZLISTFv(&MaterialEditorPcs.zlistA);
  __ct__5ZLISTFv(&MaterialEditorPcs.zlistB);
  __register_global_object(&MaterialEditorPcs,__dt__18CMaterialEditorPcsFv,ARRAY_8026d338);
  DAT_801ea4cc = DAT_801ea498;
  DAT_801ea4d0 = DAT_801ea49c;
  DAT_801ea4d4 = PTR_createViewer__18CMaterialEditorPcsFv_801ea4a0;
  DAT_801ea4d8 = DAT_801ea4a4;
  DAT_801ea4dc = DAT_801ea4a8;
  DAT_801ea4e0 = PTR_destroyViewer__18CMaterialEditorPcsFv_801ea4ac;
  DAT_801ea4e4 = DAT_801ea4b0;
  DAT_801ea4e8 = DAT_801ea4b4;
  DAT_801ea4ec = PTR_calcViewer__18CMaterialEditorPcsFv_801ea4b8;
  DAT_801ea4f8 = DAT_801ea4bc;
  DAT_801ea4fc = DAT_801ea4c0;
  DAT_801ea500 = PTR_drawViewer__18CMaterialEditorPcsFv_801ea4c4;
  return;
}

