// Function: __ct__Q28CMenuPcs10EffectInfoFv
// Entry: 80102e9c
// Size: 56 bytes

void __ct__Q28CMenuPcs10EffectInfoFv(CMenuPcs *menuPcs)

{
  *(undefined ***)&menuPcs->field_0x54 = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
  *(byte *)&(menuPcs->m_mcCtrl).m_serialHi = *(byte *)&(menuPcs->m_mcCtrl).m_serialHi & 0xef;
  *(undefined ***)&menuPcs->field_0x54 = &PTR_PTR_s_CGBaseObj_802112f4;
  *(undefined ***)&menuPcs->field_0x54 = &PTR_PTR_s_CGObject_801fd360;
  return;
}

