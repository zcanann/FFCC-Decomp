// Function: destroyViewer__14CFunnyShapePcsFv
// Entry: 8004e48c
// Size: 152 bytes

void destroyViewer__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  undefined4 local_18;
  undefined4 local_14;
  
  IsBigAlloc__7CUSBPcsFi(&USBPcs,0);
  local_14 = 0;
  local_18 = 0;
  GXSetCopyClear(&local_18,0xffffff);
  DeleteAndRemoveAll__29CPtrArray<P15OSFS_TEXTURE_ST>Fv((CPtrArray *)&funnyShapePcs->field_0x61bc);
  DeleteAndRemoveAll__22CPtrArray<P9_GXTexObj>Fv(&funnyShapePcs->field_0x61d8);
  DeleteBuffer__14CUSBStreamDataFv(&funnyShapePcs->m_usbStreamData);
  __dt__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault,0xffff);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&funnyShapePcs->field_0x4);
  return;
}

