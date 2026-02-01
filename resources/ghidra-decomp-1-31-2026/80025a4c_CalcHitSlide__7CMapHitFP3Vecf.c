// Function: CalcHitSlide__7CMapHitFP3Vecf
// Entry: 80025a4c
// Size: 904 bytes

/* WARNING: Removing unreachable block (ram,0x80025db4) */
/* WARNING: Removing unreachable block (ram,0x80025a5c) */

undefined4 CalcHitSlide__7CMapHitFP3Vecf(double param_1,CMapHit *mapHit,Vec *vec)

{
  float fVar1;
  undefined4 uVar2;
  float *pfVar3;
  double dVar4;
  double dVar5;
  Vec VStack_78;
  Vec VStack_6c;
  Vec VStack_60;
  Vec VStack_54;
  Vec VStack_48;
  Vec VStack_3c;
  Vec local_30;
  Vec local_24;
  
  fVar1 = FLOAT_8032f8d0;
  if (DAT_8032ec78 == -1) {
    if (param_1 <= (double)DAT_8032ec90->y) {
      dVar4 = (double)PSVECMag((Vec *)&g_hit_cyl_min.m_radius);
      PSVECScale(FLOAT_8032ec84 - (float)((double)FLOAT_8032f8c8 / dVar4),
                 (Vec *)&g_hit_cyl_min.m_radius,vec);
      uVar2 = 0;
    }
    else if (FLOAT_8032f8d8 < FLOAT_8032ec84) {
      dVar4 = (double)PSVECDotProduct(&g_hit_cyl_min.m_direction,DAT_8032ec90);
      PSVECScale(FLOAT_8032f8c8 +
                 -(float)(dVar4 - (double)(DAT_8032ec90[1].x + g_hit_cyl_min.m_top.y)),DAT_8032ec90,
                 &VStack_78);
      PSVECAdd(&g_hit_cyl_min.m_direction,&VStack_78,&VStack_78);
      PSVECSubtract(&VStack_78,&g_hit_cyl_min.m_bottom,vec);
      uVar2 = 1;
    }
    else {
      uVar2 = 1;
      vec->z = FLOAT_8032f8d0;
      vec->y = fVar1;
      vec->x = fVar1;
    }
  }
  else if (param_1 <= (double)DAT_8032ec90->y) {
    dVar4 = (double)PSVECMag((Vec *)&g_hit_cyl_min.m_radius);
    PSVECScale(FLOAT_8032ec84 - (float)((double)FLOAT_8032f8c8 / dVar4),
               (Vec *)&g_hit_cyl_min.m_radius,vec);
    uVar2 = 0;
  }
  else {
    if (DAT_8032ec78 == 0) {
      pfVar3 = mapHit->m_vertices +
               (uint)*(ushort *)
                      ((int)&DAT_8032ec90[5].z +
                      (uint)*(byte *)((int)&DAT_8032ec90[5].z + 2) * 2 + 2) * 3;
      local_24.x = *pfVar3;
      local_24.y = pfVar3[1];
      local_24.z = pfVar3[2];
      pfVar3 = mapHit->m_vertices + (uint)*(ushort *)&DAT_8032ec90[6].x * 3;
      local_30.x = *pfVar3;
      local_30.y = pfVar3[1];
      local_30.z = pfVar3[2];
    }
    else {
      pfVar3 = mapHit->m_vertices +
               (uint)*(ushort *)((int)&DAT_8032ec90[5].z + DAT_8032ec78 * 2 + 2) * 3;
      local_24.x = *pfVar3;
      local_24.y = pfVar3[1];
      local_24.z = pfVar3[2];
      pfVar3 = mapHit->m_vertices +
               (uint)*(ushort *)((int)&DAT_8032ec90[6].x + DAT_8032ec78 * 2) * 3;
      local_30.x = *pfVar3;
      local_30.y = pfVar3[1];
      local_30.z = pfVar3[2];
    }
    PSVECSubtract(&local_30,&local_24,&VStack_3c);
    PSVECSubtract(&local_30,&g_hit_cyl_min.m_direction,&VStack_54);
    dVar4 = (double)PSVECDotProduct(&VStack_3c,&VStack_54);
    dVar5 = (double)PSVECDotProduct(&VStack_3c,&VStack_3c);
    PSVECScale((float)(dVar4 / dVar5),&VStack_3c,&VStack_60);
    PSVECSubtract(&local_30,&VStack_60,&VStack_48);
    PSVECSubtract(&g_hit_cyl_min.m_direction,&VStack_48,&VStack_6c);
    dVar4 = (double)PSVECDotProduct((Vec *)&g_hit_cyl_min.m_radius,&VStack_6c);
    dVar5 = (double)PSVECMag(&VStack_6c);
    fVar1 = FLOAT_8032f8d0;
    if (dVar5 < (double)FLOAT_8032f8c4) {
      vec->z = FLOAT_8032f8d0;
      vec->y = fVar1;
      vec->x = fVar1;
    }
    else {
      PSVECScale((float)((double)FLOAT_8032f8cc / dVar5),&VStack_6c,&VStack_6c);
      if ((double)FLOAT_8032f8d0 < dVar4) {
        PSVECScale(FLOAT_8032f8d4 * -g_hit_cyl_min.m_top.y,&VStack_6c,&VStack_6c);
      }
      else {
        PSVECScale(FLOAT_8032f8d4 * g_hit_cyl_min.m_top.y,&VStack_6c,&VStack_6c);
      }
      PSVECAdd(&VStack_48,&VStack_6c,&VStack_48);
      PSVECSubtract(&VStack_48,&g_hit_cyl_min.m_bottom,vec);
    }
    uVar2 = 1;
  }
  return uVar2;
}

