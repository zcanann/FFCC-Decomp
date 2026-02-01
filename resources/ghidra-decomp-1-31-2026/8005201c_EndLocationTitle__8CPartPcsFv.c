// Function: EndLocationTitle__8CPartPcsFv
// Entry: 8005201c
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void EndLocationTitle__8CPartPcsFv(CPartPcs *partPcs)

{
  pppReleasePdt__8CPartMngFi(&PartMng,6);
  (partPcs->m_usbStreamData).m_blockOnFrame = '\0';
  return;
}

