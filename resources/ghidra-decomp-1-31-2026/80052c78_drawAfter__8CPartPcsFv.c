// Function: drawAfter__8CPartPcsFv
// Entry: 80052c78
// Size: 148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawAfter__8CPartPcsFv(CPartPcs *partPcs)

{
  if ((Game.game.m_gameWork.m_gamePaused == '\0') &&
     ((partPcs->m_usbStreamData).m_disableShokiDraw == '\0')) {
    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
    SetFog__8CGraphicFii(&Graphic,1,0);
    pppInitDrawEnv__FUc(0);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppPartDrawAfter__8CPartMngFv(&PartMng);
    pppClearDrawEnv__Fv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

