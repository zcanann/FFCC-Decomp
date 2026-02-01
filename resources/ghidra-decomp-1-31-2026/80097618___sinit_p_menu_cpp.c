// Function: __sinit_p_menu_cpp
// Entry: 80097618
// Size: 328 bytes

void __sinit_p_menu_cpp(void)

{
  MenuPcs.process.manager.vtable = (CManager)&PTR_PTR_s_CMenuPcs_8020f2d0;
  MenuPcs.m_mcCtrl.m_previousState = 0;
  MenuPcs.m_mcCtrl.m_state = 0;
  MenuPcs.m_mcCtrl.m_lastResult = 0;
  MenuPcs.m_mcCtrl.m_iteration = 0;
  MenuPcs.m_mcCtrl.m_userBuffer = (void *)0x0;
  MenuPcs.m_mcCtrl.m_createFlag = 0;
  MenuPcs.m_mcCtrl.m_cardChannel = 0;
  MenuPcs.m_mcCtrl.m_saveIndex = 0;
  __register_global_object(&MenuPcs,__dt__8CMenuPcsFv,ARRAY_802ea1a0);
  DAT_8020ee44 = DAT_8020edf8;
  DAT_8020ee48 = DAT_8020edfc;
  DAT_8020ee4c = PTR_create__8CMenuPcsFv_8020ee00;
  DAT_8020ee50 = DAT_8020ee04;
  DAT_8020ee54 = DAT_8020ee08;
  DAT_8020ee58 = PTR_destroy__8CMenuPcsFv_8020ee0c;
  DAT_8020ee5c = DAT_8020ee10;
  DAT_8020ee60 = DAT_8020ee14;
  DAT_8020ee64 = PTR_calc__8CMenuPcsFv_8020ee18;
  DAT_8020ee70 = DAT_8020ee1c;
  DAT_8020ee74 = DAT_8020ee20;
  DAT_8020ee78 = PTR_draw__8CMenuPcsFv_8020ee24;
  DAT_8020ee84 = DAT_8020ee28;
  DAT_8020ee88 = DAT_8020ee2c;
  DAT_8020ee8c = PTR_loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii_8020ee30;
  DAT_8020ee98 = DAT_8020ee34;
  DAT_8020ee9c = DAT_8020ee38;
  DAT_8020eea0 = PTR_drawSingleMenu__8CMenuPcsFv_8020ee3c;
  return;
}

