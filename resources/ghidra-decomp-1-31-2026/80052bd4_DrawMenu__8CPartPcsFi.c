// Function: DrawMenu__8CPartPcsFi
// Entry: 80052bd4
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMenu__8CPartPcsFi(CPartPcs *partPcs,short param_2)

{
  if ((partPcs->m_usbStreamData).m_disableShokiDraw == '\0') {
    SetFog__8CGraphicFii(&Graphic,1,0);
    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
    pppInitDrawEnv__FUc(0);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppDrawPrioPdtFpno__8CPartMngFUcss(&PartMng,6,0,param_2);
    drawEnd__8CPartMngFv(&PartMng);
    pppClearDrawEnv__Fv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

