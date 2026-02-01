// Function: WmInit__8CMenuPcsFv
// Entry: 80102ed8
// Size: 220 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void WmInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  FLOAT_8032ee18 = FLOAT_803313dc;
  *(undefined4 *)&menuPcs->field_0x814 = 0;
  *(undefined4 *)&menuPcs->field_0x818 = 0;
  *(undefined4 *)&menuPcs->field_0x81c = 0;
  *(undefined4 *)&menuPcs->field_0x820 = 0;
  *(undefined4 *)&menuPcs->field_0x824 = 0;
  *(undefined4 *)&menuPcs->field_0x828 = 0;
  *(undefined4 *)&menuPcs->field_0x82c = 0;
  menuPcs->m_unk0x838 = (uint32_t *)0x0;
  *(undefined4 *)&menuPcs->field_0x83c = 0;
  *(undefined4 *)&menuPcs->field_0x840 = 0;
  *(undefined4 *)&menuPcs->field_0x854 = 0;
  menuPcs->field_0x858 = 0;
  menuPcs->field_0x86e = 0;
  memset(&menuPcs->field_0x4,0,0x1c);
  menuPcs->field_0xd = 0;
  menuPcs->field_0x10 = 0;
  menuPcs->field_0x12 = 0;
  menuPcs->field_0x13 = 0;
  menuPcs->field_0xd = 1;
  menuPcs->field_0x16 = 0;
  DAT_8032ee20 = 0xff;
  uRam8032ee21 = 0xff;
  DAT_8032ee24 = 0xff;
  uRam8032ee25 = 0xff;
  DAT_8032ee2c = 0xffffffff;
  DAT_8032ee28 = 0xffffffff;
  DAT_8032ee30 = (uint8_t)Game.game.m_gameWork._8_4_;
  if (99 < (int)Game.game.m_gameWork._8_4_) {
    DAT_8032ee30 = 'd';
  }
  return;
}

