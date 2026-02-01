// Function: __sinit_p_tina_cpp
// Entry: 80053960
// Size: 832 bytes

void __sinit_p_tina_cpp(void)

{
  undefined4 uVar1;
  
  PartPcs.process.manager.vtable = (CManager)&PTR_PTR_s_CPartPcs_801eada4;
  __ct__14CUSBStreamDataFv(&PartPcs.m_usbStreamData);
  __register_global_object(&PartPcs,__dt__8CPartPcsFv,ARRAY_80273928);
  DAT_801eab18 = DAT_801eaa08;
  DAT_801eab28 = DAT_801eaa10;
  DAT_801eab2c = DAT_801eaa14;
  DAT_801eaa98 = DAT_801ea9b0;
  DAT_801eaa9c = DAT_801ea9b4;
  DAT_801eaaa0 = PTR_create__8CPartPcsFv_801ea9b8;
  DAT_801eaaa4 = DAT_801ea9bc;
  DAT_801eaaa8 = DAT_801ea9c0;
  DAT_801eaaac = PTR_destroy__8CPartPcsFv_801ea9c4;
  DAT_801eaab0 = DAT_801ea9c8;
  DAT_801eaab4 = DAT_801ea9cc;
  DAT_801eaab8 = PTR_calcInit__8CPartPcsFv_801ea9d0;
  DAT_801eaac4 = DAT_801ea9d4;
  DAT_801eaac8 = DAT_801ea9d8;
  DAT_801eaacc = PTR_calc__8CPartPcsFv_801ea9dc;
  DAT_801eaad8 = DAT_801ea9e0;
  DAT_801eaadc = DAT_801ea9e4;
  DAT_801eaae0 = PTR_calcDead__8CPartPcsFv_801ea9e8;
  DAT_801eaaec = DAT_801ea9ec;
  DAT_801eaaf0 = DAT_801ea9f0;
  DAT_801eaaf4 = PTR_ClearOt__8CPartPcsFv_801ea9f4;
  DAT_801eab00 = DAT_801ea9f8;
  DAT_801eab04 = DAT_801ea9fc;
  DAT_801eab08 = PTR_drawShadow__8CPartPcsFv_801eaa00;
  DAT_801eab14 = DAT_801eaa04;
  DAT_801eab1c = PTR_drawCharaBefore__8CPartPcsFv_801eaa0c;
  DAT_801eab30 = PTR_draw__8CPartPcsFv_801eaa18;
  DAT_801eab3c = DAT_801eaa1c;
  DAT_801eab40 = DAT_801eaa20;
  DAT_801eab44 = PTR_drawAfter__8CPartPcsFv_801eaa24;
  DAT_801eac70 = DAT_801eaa7c;
  DAT_801eac74 = DAT_801eaa80;
  DAT_801eabf4 = DAT_801eaa28;
  DAT_801eabf8 = DAT_801eaa2c;
  DAT_801eabfc = PTR_createViewer__8CPartPcsFv_801eaa30;
  DAT_801eac00 = DAT_801eaa34;
  DAT_801eac04 = DAT_801eaa38;
  DAT_801eac08 = PTR_destroy__8CPartPcsFv_801eaa3c;
  DAT_801eac0c = DAT_801eaa40;
  DAT_801eac10 = DAT_801eaa44;
  DAT_801eac14 = PTR_calcInit__8CPartPcsFv_801eaa48;
  DAT_801eac20 = DAT_801eaa4c;
  DAT_801eac24 = DAT_801eaa50;
  DAT_801eac28 = PTR_calcViewer__8CPartPcsFv_801eaa54;
  DAT_801eac34 = DAT_801eaa58;
  DAT_801eac38 = DAT_801eaa5c;
  DAT_801eac3c = PTR_calcDead__8CPartPcsFv_801eaa60;
  DAT_801eac48 = DAT_801eaa64;
  DAT_801eac4c = DAT_801eaa68;
  DAT_801eac50 = PTR_ClearOt__8CPartPcsFv_801eaa6c;
  DAT_801eac5c = DAT_801eaa70;
  DAT_801eac60 = DAT_801eaa74;
  DAT_801eac64 = PTR_drawShadowViewer__8CPartPcsFv_801eaa78;
  DAT_801eac78 = PTR_drawViewer__8CPartPcsFv_801eaa84;
  DAT_801eac84 = DAT_801eaa88;
  DAT_801eac88 = DAT_801eaa8c;
  DAT_801eac8c = PTR_drawAfterViewer__8CPartPcsFv_801eaa90;
  uVar1 = __ct__8CProfileFPc(g_par_calc_prof,s_no_name_8032fdcc);
  __register_global_object(uVar1,__dt__8CProfileFv,ARRAY_80273968);
  uVar1 = __ct__8CProfileFPc(g_par_draw_prof,s_no_name_8032fdcc);
  __register_global_object(uVar1,__dt__8CProfileFv,ARRAY_802739e8);
  return;
}

