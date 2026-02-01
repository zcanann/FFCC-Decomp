// Function: CalcHitPosition__7CMapHitFP3Vec
// Entry: 80025984
// Size: 200 bytes

void CalcHitPosition__7CMapHitFP3Vec(CMapHit *mapHit,Vec *position)

{
  double dVar1;
  
  if (DAT_8032ec78 == -1) {
    dVar1 = (double)PSVECMag((Vec *)&g_hit_cyl_min.m_radius);
    PSVECScale(FLOAT_8032ec84 - (float)((double)FLOAT_8032f8c8 / dVar1),
               (Vec *)&g_hit_cyl_min.m_radius,position);
    PSVECAdd(&g_hit_cyl_min.m_bottom,position,position);
  }
  else {
    dVar1 = (double)PSVECMag((Vec *)&g_hit_cyl_min.m_radius);
    PSVECScale(FLOAT_8032ec84 - (float)((double)FLOAT_8032f8c4 / dVar1),
               (Vec *)&g_hit_cyl_min.m_radius,position);
    PSVECAdd(&g_hit_cyl_min.m_bottom,position,position);
  }
  return;
}

