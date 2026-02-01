// Function: __sinit_p_dbgmenu_cpp
// Entry: 8012d288
// Size: 300 bytes

void __sinit_p_dbgmenu_cpp(void)

{
  MiniGamePcs._25728_4_ = &PTR_PTR_s_CDbgMenuPcs_802126c4;
  memset(0x80306710,0,0x34);
  memset(0x80306744,0,0x20);
  __construct_array(DbgMenuPcs.dbgMenuArr,__ct__Q211CDbgMenuPcs3CDMFv,0,0x54,0x80);
  DAT_802123cc = DAT_80212398;
  DAT_802123d0 = DAT_8021239c;
  DAT_802123d4 = PTR_create__11CDbgMenuPcsFv_802123a0;
  DAT_802123d8 = DAT_802123a4;
  DAT_802123dc = DAT_802123a8;
  DAT_802123e0 = PTR_destroy__11CDbgMenuPcsFv_802123ac;
  DAT_802123e4 = DAT_802123b0;
  DAT_802123e8 = DAT_802123b4;
  DAT_802123ec = PTR_calc__11CDbgMenuPcsFv_802123b8;
  DAT_802123f8 = DAT_802123bc;
  DAT_802123fc = DAT_802123c0;
  DAT_80212400 = PTR_draw__11CDbgMenuPcsFv_802123c4;
  return;
}

