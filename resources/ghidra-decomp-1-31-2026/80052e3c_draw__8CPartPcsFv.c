// Function: draw__8CPartPcsFv
// Entry: 80052e3c
// Size: 224 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void draw__8CPartPcsFv(CPartPcs *partPcs)

{
  SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
  if (Game.game.m_gameWork.m_gamePaused == '\0') {
    if ((partPcs->m_usbStreamData).m_disableShokiDraw == '\0') {
      SetFog__8CGraphicFii(&Graphic,1,0);
      pppInitDrawEnv__FUc(0);
      pppSetRendMatrix__8CPartMngFv(&PartMng);
      pppDraw__8CPartMngFv(&PartMng);
      pppClearDrawEnv__Fv();
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
    }
    else {
      DrawOt__10pppDrawMngFv(&ppvDrawMng);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
    }
  }
  else {
    DrawOt__10pppDrawMngFv(&ppvDrawMng);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

