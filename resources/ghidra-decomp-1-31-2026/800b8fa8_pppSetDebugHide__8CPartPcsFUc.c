// Function: pppSetDebugHide__8CPartPcsFUc
// Entry: 800b8fa8
// Size: 8 bytes

void pppSetDebugHide__8CPartPcsFUc(CPartPcs *partPcs,char param_2)

{
  (partPcs->m_usbStreamData).m_disableShokiDraw = param_2;
  return;
}

