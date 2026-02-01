// Function: drawShadow__8CPartPcsFv
// Entry: 80052fb4
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawShadow__8CPartPcsFv(CPartPcs *partPcs)

{
  if (((Game.game.m_gameWork.m_gamePaused == '\0') &&
      ((partPcs->m_usbStreamData).m_disableShokiDraw == '\0')) && (CameraPcs._1028_1_ != '\0')) {
    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
    pppInitDrawEnv__FUc(1);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppDrawPrio__8CPartMngFUc(&PartMng,3);
    pppClearDrawEnv__Fv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

