// Function: calcViewer__8CPartPcsFv
// Entry: 8005309c
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcViewer__8CPartPcsFv(CPartPcs *partPcs)

{
  int iVar1;
  uint32_t uVar2;
  
  Start__10CStopWatchFv(g_par_calc_prof);
  pppEditBeforeCalc__8CPartMngFv(&PartMng);
  pppEditPartCalc__8CPartMngFv(&PartMng);
  Stop__10CStopWatchFv(g_par_calc_prof);
  mccReadData__7CUSBPcsFv(&USBPcs);
  iVar1 = IsUSBStreamDataDone__14CUSBStreamDataFv(&partPcs->m_usbStreamData);
  if (iVar1 != 0) {
    uVar2 = (partPcs->m_usbStreamData).m_packetCode;
    if (uVar2 != 0) {
      pppDataRcv__8CPartMngFUlPcUl
                (&PartMng,uVar2,(partPcs->m_usbStreamData).m_data,
                 (partPcs->m_usbStreamData).m_sizeBytes);
    }
    SetUSBStreamDataDone__14CUSBStreamDataFv(&partPcs->m_usbStreamData);
  }
  return;
}

