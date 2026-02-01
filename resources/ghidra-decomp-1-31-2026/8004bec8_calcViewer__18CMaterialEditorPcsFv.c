// Function: calcViewer__18CMaterialEditorPcsFv
// Entry: 8004bec8
// Size: 464 bytes

void calcViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEdtiorPcs)

{
  int iVar1;
  Mtx MStack_98;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  Mtx MStack_44;
  
  mccReadData__7CUSBPcsFv(&USBPcs);
  iVar1 = IsUSBStreamDataDone__14CUSBStreamDataFv(&materialEdtiorPcs->m_usbStream);
  if (iVar1 != 0) {
    SetUSBData__18CMaterialEditorPcsFv(materialEdtiorPcs);
    SetUSBStreamDataDone__14CUSBStreamDataFv(&materialEdtiorPcs->m_usbStream);
  }
  local_54 = FLOAT_8032fcd8;
  local_58 = FLOAT_8032fcd8;
  local_5c = FLOAT_8032fcd8;
  local_48 = FLOAT_8032fcc8;
  local_4c = FLOAT_8032fcc8;
  local_50 = FLOAT_8032fcc8;
  local_68 = (materialEdtiorPcs->field268_0x15c).x;
  local_64 = (materialEdtiorPcs->field268_0x15c).y;
  local_60 = -(materialEdtiorPcs->field268_0x15c).z;
  SetViewerSRT__10CCameraPcsFPC3SRT(&CameraPcs,&local_68);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_44);
  (materialEdtiorPcs->m_unkMatrix).value[0][0] = *(float *)&materialEdtiorPcs->field_0x12c;
  (materialEdtiorPcs->m_unkMatrix).value[0][1] = *(float *)&materialEdtiorPcs->field_0x130;
  (materialEdtiorPcs->m_unkMatrix).value[0][2] = *(float *)&materialEdtiorPcs->field_0x134;
  (materialEdtiorPcs->m_unkMatrix).value[0][3] = *(float *)&materialEdtiorPcs->field_0x138;
  (materialEdtiorPcs->m_unkMatrix).value[1][0] = *(float *)&materialEdtiorPcs->field_0x13c;
  (materialEdtiorPcs->m_unkMatrix).value[1][1] = *(float *)&materialEdtiorPcs->field_0x140;
  (materialEdtiorPcs->m_unkMatrix).value[1][2] = *(float *)&materialEdtiorPcs->field_0x144;
  (materialEdtiorPcs->m_unkMatrix).value[1][3] = *(float *)&materialEdtiorPcs->field_0x148;
  (materialEdtiorPcs->m_unkMatrix).value[2][0] = *(float *)&materialEdtiorPcs->field_0x14c;
  (materialEdtiorPcs->m_unkMatrix).value[2][1] = *(float *)&materialEdtiorPcs->field_0x150;
  (materialEdtiorPcs->m_unkMatrix).value[2][2] = *(float *)&materialEdtiorPcs->field_0x154;
  (materialEdtiorPcs->m_unkMatrix).value[2][3] = *(float *)&materialEdtiorPcs->field_0x158;
  PSMTXTranspose(&materialEdtiorPcs->m_unkMatrix,&materialEdtiorPcs->m_unkMatrix);
  (materialEdtiorPcs->m_unkMatrix).value[0][1] = -(materialEdtiorPcs->m_unkMatrix).value[0][1];
  (materialEdtiorPcs->m_unkMatrix).value[1][1] = -(materialEdtiorPcs->m_unkMatrix).value[1][1];
  (materialEdtiorPcs->m_unkMatrix).value[2][1] = -(materialEdtiorPcs->m_unkMatrix).value[2][1];
  (materialEdtiorPcs->m_unkMatrix).value[2][0] = -(materialEdtiorPcs->m_unkMatrix).value[2][0];
  (materialEdtiorPcs->m_unkMatrix).value[2][1] = -(materialEdtiorPcs->m_unkMatrix).value[2][1];
  (materialEdtiorPcs->m_unkMatrix).value[2][2] = -(materialEdtiorPcs->m_unkMatrix).value[2][2];
  PSMTXIdentity(&MStack_98);
  MStack_98.value[1][1] = FLOAT_8032fcdc;
  PSMTXConcat(&materialEdtiorPcs->m_unkMatrix,&MStack_98,&materialEdtiorPcs->m_unkMatrix);
  PSMTXIdentity(&MStack_98);
  MStack_98.value[2][2] = FLOAT_8032fcdc;
  PSMTXConcat(&materialEdtiorPcs->m_unkMatrix,&MStack_98,&materialEdtiorPcs->m_unkMatrix);
  PSMTXConcat(&MStack_44,&materialEdtiorPcs->m_unkMatrix,&MStack_44);
  GXLoadPosMtxImm(&MStack_44,0);
  return;
}

