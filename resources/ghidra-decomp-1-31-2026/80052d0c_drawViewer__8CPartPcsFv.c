// Function: drawViewer__8CPartPcsFv
// Entry: 80052d0c
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawViewer__8CPartPcsFv(void)

{
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_tina_cpp_801d8008,0x31a);
  Start__10CStopWatchFv(g_par_draw_prof);
  Start__10CStopWatchFv(g_par_calc_prof);
  pppSetProjection__Fv();
  pppInitDrawEnv__FUc(0);
  pppEditDraw__8CPartMngFv(&PartMng);
  Stop__10CStopWatchFv(g_par_calc_prof);
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_tina_cpp_801d8008,0x322);
  Stop__10CStopWatchFv(g_par_draw_prof);
  pppClearDrawEnv__Fv();
  return;
}

