// Function: drawAfterViewer__8CPartPcsFv
// Entry: 80052764
// Size: 504 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawAfterViewer__8CPartPcsFv(void)

{
  int iVar1;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_tina_cpp_801d8008,0x3f1);
  Start__10CStopWatchFv(g_par_draw_prof);
  Start__10CStopWatchFv(g_par_calc_prof);
  SetFog__8CGraphicFii(&Graphic,1,0);
  pppInitDrawEnv__FUc(0);
  pppEditPartDrawAfter__8CPartMngFv(&PartMng);
  Stop__10CStopWatchFv(g_par_calc_prof);
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_tina_cpp_801d8008,0x3fb);
  Stop__10CStopWatchFv(g_par_draw_prof);
  pppGet2Dpos__8CPartMngFv(&PartMng);
  pppClearDrawEnv__Fv();
  if (DAT_8032ed44 == '\0') {
    DAT_8032ed40 = &DAT_8032fdb0;
    DAT_8032ed44 = '\x01';
  }
  if (DAT_8032ed4c == '\0') {
    DAT_8032ed48 = 0;
    DAT_8032ed4c = '\x01';
  }
  DAT_8032ed48 = DAT_8032ed48 + 1;
  iVar1 = DAT_8032ed48 >> 0x1f;
  Printf__8CGraphicFPce
            (&Graphic,s_Tina___c__801d8014,
             (int)(char)DAT_8032ed40
                        [(iVar1 * 4 | (uint)((DAT_8032ed48 >> 4) * 0x40000000 + iVar1) >> 0x1e) -
                         iVar1]);
  ProfEnd__8CProfileFv(g_par_calc_prof);
  ProfEnd__8CProfileFv(g_par_draw_prof);
  Printf__8CGraphicFPce
            ((double)(float)g_par_calc_prof._96_4_,(double)(float)g_par_calc_prof._100_4_,&Graphic,
             s_clc___3f___max___3f___801d8020);
  Printf__8CGraphicFPce
            ((double)(float)g_par_draw_prof._96_4_,(double)(float)g_par_draw_prof._100_4_,&Graphic,
             s_drw___3f___max___3f___801d8038);
  Printf__8CGraphicFPce
            ((double)((float)((double)CONCAT44(0x43300000,DAT_801eae08 ^ 0x80000000) -
                             DOUBLE_8032fdc0) / FLOAT_8032fdb8),
             (double)((float)((double)CONCAT44(0x43300000,DAT_801eae0c ^ 0x80000000) -
                             DOUBLE_8032fdc0) / FLOAT_8032fdb8),&Graphic,
             s_hpm___3f___max___3f___801d8050);
  return;
}

