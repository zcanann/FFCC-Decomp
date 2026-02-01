// Function: SetManaWaterEffect__8CMenuPcsFv
// Entry: 80179e28
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetManaWaterEffect__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)&menuPcs->field_0x840 + 0x19b8);
  if (iVar1 != -1) {
    pppDeletePart__8CPartMngFi(&PartMng,iVar1);
  }
  BindEffect__8CMenuPcsFiii(menuPcs,5,Game.game.m_gameWork.m_timerA + 0x13,0xffffffff);
  *(int32_t *)&menuPcs->field_0x70 = Game.game.m_gameWork.m_timerA;
  return;
}

