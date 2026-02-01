// Function: __dt__8CMenuPcsFv
// Entry: 80097760
// Size: 120 bytes

CMenuPcs * __dt__8CMenuPcsFv(CMenuPcs *menuPcs,short param_2)

{
  if (menuPcs != (CMenuPcs *)0x0) {
    (menuPcs->process).manager.vtable = &PTR_PTR_s_CMenuPcs_8020f2d0;
    if (menuPcs != (CMenuPcs *)0xffffffe0) {
      (menuPcs->m_mcCtrl).m_previousState = 0;
      (menuPcs->m_mcCtrl).m_state = 0;
      (menuPcs->m_mcCtrl).m_lastResult = 0;
      (menuPcs->m_mcCtrl).m_iteration = 0;
      (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
      (menuPcs->m_mcCtrl).m_createFlag = 0;
      (menuPcs->m_mcCtrl).m_cardChannel = 0;
      (menuPcs->m_mcCtrl).m_saveIndex = 0;
    }
    if (0 < param_2) {
      __dl__FPv(menuPcs);
    }
  }
  return menuPcs;
}

