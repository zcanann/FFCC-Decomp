// Function: calcInit__8CPartPcsFv
// Entry: 800531c8
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcInit__8CPartPcsFv(void)

{
  pppRefCnt0Up__8CPartMngFv(&PartMng);
  if (Game.game.m_currentSceneId == 7) {
    ProfStart__8CProfileFv(g_par_calc_prof);
    ProfStart__8CProfileFv(g_par_draw_prof);
  }
  pppPartInit__8CPartMngFv(&PartMng);
  return;
}

