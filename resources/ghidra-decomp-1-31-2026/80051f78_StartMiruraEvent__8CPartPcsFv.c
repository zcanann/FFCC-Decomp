// Function: StartMiruraEvent__8CPartPcsFv
// Entry: 80051f78
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void StartMiruraEvent__8CPartPcsFv(CPartPcs *partPcs)

{
  int iVar1;
  undefined auStack_408 [1028];
  
  sprintf(auStack_408,s_dvd_tina_stage_03d_mirura_801d7f78,Game.game.m_currentMapId);
  iVar1 = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng,auStack_408,7,0,0,0);
  if ((iVar1 != 0) &&
     (iVar1 = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,auStack_408,7,0,0,0), iVar1 != 0)) {
    (partPcs->m_usbStreamData).m_miruraEventActive = '\x01';
  }
  return;
}

