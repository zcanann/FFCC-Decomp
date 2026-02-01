// Function: createViewer__14CFunnyShapePcsFv
// Entry: 8004e524
// Size: 168 bytes

void createViewer__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  CStage *pCVar1;
  undefined4 local_18;
  undefined4 local_14;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x200000,s_CFunnyShapePcs_801d7e0c,0);
  *(CStage **)&funnyShapePcs->field_0x4 = pCVar1;
  IsBigAlloc__7CUSBPcsFi(&USBPcs,1);
  local_14 = 0x404040ff;
  local_18 = 0x404040ff;
  GXSetCopyClear(&local_18,0xffffff);
  memset(&funnyShapePcs->field_0x6178,0,0x40);
  CreateBuffer__14CUSBStreamDataFv(&funnyShapePcs->m_usbStreamData);
  *(undefined4 *)&funnyShapePcs->field_0x61b8 = 0;
  return;
}

