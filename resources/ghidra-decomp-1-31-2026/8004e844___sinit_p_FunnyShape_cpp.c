// Function: __sinit_p_FunnyShape_cpp
// Entry: 8004e844
// Size: 288 bytes

void __sinit_p_FunnyShape_cpp(void)

{
  FunnyShapePcs.process.manager.vtable = (CManager)&PTR_PTR_s_CFunnyShapePcs_801ea924;
  __ct__14CUSBStreamDataFv(&FunnyShapePcs.m_usbStreamData);
  __ct__11CFunnyShapeFv((CFunnyShape *)&FunnyShapePcs.m_usbStreamData.m_stageDefault);
  __ct__29CPtrArray<P15OSFS_TEXTURE_ST>Fv((CPtrArray *)&FunnyShapePcs.field_0x61bc);
  __ct__22CPtrArray<P9_GXTexObj>Fv((CPtrArray *)&FunnyShapePcs.field_0x61d8);
  __register_global_object(&FunnyShapePcs,__dt__14CFunnyShapePcsFv,ARRAY_8026d728);
  DAT_801ea7ac = DAT_801ea778;
  DAT_801ea7b0 = DAT_801ea77c;
  DAT_801ea7b4 = PTR_createViewer__14CFunnyShapePcsFv_801ea780;
  DAT_801ea7b8 = DAT_801ea784;
  DAT_801ea7bc = DAT_801ea788;
  DAT_801ea7c0 = PTR_destroyViewer__14CFunnyShapePcsFv_801ea78c;
  DAT_801ea7c4 = DAT_801ea790;
  DAT_801ea7c8 = DAT_801ea794;
  DAT_801ea7cc = PTR_calcViewer__14CFunnyShapePcsFv_801ea798;
  DAT_801ea7d8 = DAT_801ea79c;
  DAT_801ea7dc = DAT_801ea7a0;
  DAT_801ea7e0 = PTR_drawViewer__14CFunnyShapePcsFv_801ea7a4;
  return;
}

