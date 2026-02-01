// Function: EndMiruraEvent__8CPartPcsFv
// Entry: 80051f38
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void EndMiruraEvent__8CPartPcsFv(CPartPcs *partPcs)

{
  pppReleasePdt__8CPartMngFi(&PartMng,7);
  (partPcs->m_usbStreamData).m_miruraEventActive = '\0';
  return;
}

