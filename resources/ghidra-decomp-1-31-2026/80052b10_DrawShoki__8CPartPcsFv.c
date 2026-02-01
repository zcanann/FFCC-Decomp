// Function: DrawShoki__8CPartPcsFv
// Entry: 80052b10
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawShoki__8CPartPcsFv(CPartPcs *partPcs)

{
  if (((((partPcs->m_usbStreamData).m_disableShokiDraw == '\0') && (Game.game.m_currentSceneId == 4)
       ) && (SetFog__8CGraphicFii(&Graphic,1,0), Game.game.m_gameWork.m_gamePaused == '\0')) &&
     (CameraPcs._1028_1_ != '\0')) {
    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
    pppInitDrawEnv__FUc(1);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppDrawPrio__8CPartMngFUc(&PartMng,8);
    pppClearDrawEnv__Fv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

