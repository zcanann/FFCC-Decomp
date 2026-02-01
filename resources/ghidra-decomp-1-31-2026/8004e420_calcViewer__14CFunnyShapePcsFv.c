// Function: calcViewer__14CFunnyShapePcsFv
// Entry: 8004e420
// Size: 108 bytes

void calcViewer__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  int iVar1;
  
  iVar1 = IsUSBStreamDataDone__14CUSBStreamDataFv(&funnyShapePcs->m_usbStreamData);
  if (iVar1 != 0) {
    SetUSBData__14CFunnyShapePcsFv(funnyShapePcs);
    SetUSBStreamDataDone__14CUSBStreamDataFv(&funnyShapePcs->m_usbStreamData);
  }
  if ((funnyShapePcs->field_0x6124 != '\0') && (*(int *)&funnyShapePcs->field_0x6134 != 0)) {
    Update__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault);
  }
  return;
}

