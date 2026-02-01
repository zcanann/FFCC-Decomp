// Function: CheckHitFaceCylinder__7CMapHitFUl
// Entry: 80025df4
// Size: 2300 bytes

/* WARNING: Removing unreachable block (ram,0x800266d4) */
/* WARNING: Removing unreachable block (ram,0x800266cc) */
/* WARNING: Removing unreachable block (ram,0x800266c4) */
/* WARNING: Removing unreachable block (ram,0x800266bc) */
/* WARNING: Removing unreachable block (ram,0x80025e1c) */
/* WARNING: Removing unreachable block (ram,0x80025e14) */
/* WARNING: Removing unreachable block (ram,0x80025e0c) */
/* WARNING: Removing unreachable block (ram,0x80025e04) */
/* WARNING: Removing unreachable block (ram,0x800260a8) */

undefined4 CheckHitFaceCylinder__7CMapHitFUl(CMapHit *mapHit,uint param_2)

{
  byte bVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  undefined4 uVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  Vec local_14c;
  Vec local_140;
  Vec local_134;
  Vec VStack_128;
  Vec VStack_11c;
  Vec VStack_110;
  float local_104;
  float local_100;
  float local_fc;
  Vec local_f8;
  Vec local_ec;
  Vec VStack_e0;
  Vec local_d4;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  
  if ((*(uint *)(MapMng.mapIdGrpArr + *(byte *)((int)&DAT_8032ec8c[5].z + 3)) & param_2) == 0) {
    uVar6 = 0;
  }
  else {
    bVar3 = false;
    fVar2 = DAT_8032ec8c[1].y;
    bVar5 = false;
    if (g_hit_cyl.m_top.z <= fVar2) {
      if (fVar2 <= g_hit_cyl.m_top.z) {
        bVar4 = true;
      }
      else {
        bVar4 = fVar2 <= g_hit_cyl.m_direction2.z;
      }
    }
    else {
      bVar4 = g_hit_cyl.m_top.z <= DAT_8032ec8c[2].y;
    }
    if (bVar4) {
      fVar2 = DAT_8032ec8c[1].z;
      if (g_hit_cyl.m_direction2.x <= fVar2) {
        if (fVar2 <= g_hit_cyl.m_direction2.x) {
          bVar4 = true;
        }
        else {
          bVar4 = fVar2 <= g_hit_cyl.m_radius2;
        }
      }
      else {
        bVar4 = g_hit_cyl.m_direction2.x <= DAT_8032ec8c[2].z;
      }
      if (bVar4) {
        bVar5 = true;
      }
    }
    if (bVar5) {
      fVar2 = DAT_8032ec8c[2].x;
      if (g_hit_cyl.m_direction2.y <= fVar2) {
        if (fVar2 <= g_hit_cyl.m_direction2.y) {
          bVar5 = true;
        }
        else {
          bVar5 = fVar2 <= g_hit_cyl.m_height2;
        }
      }
      else {
        bVar5 = g_hit_cyl.m_direction2.y <= DAT_8032ec8c[3].x;
      }
      if (bVar5) {
        bVar3 = true;
      }
    }
    if (bVar3) {
      dVar13 = (double)PSVECDotProduct((Vec *)&g_hit_cyl.m_radius,DAT_8032ec8c);
      if (dVar13 < (double)FLOAT_8032f8d0) {
        dVar14 = (double)PSVECDotProduct(&g_hit_cyl.m_bottom,DAT_8032ec8c);
        iVar11 = -1;
        FLOAT_8032ec7c =
             -(float)((double)(float)(dVar14 - (double)(DAT_8032ec8c[1].x + g_hit_cyl.m_top.y)) /
                     dVar13);
        dVar13 = (double)FLOAT_8032ec7c;
        if (dVar13 <= DOUBLE_8032f8e0) {
          if ((dVar13 < (double)FLOAT_8032f8e8) || ((double)FLOAT_8032ec80 <= dVar13)) {
LAB_80026504:
            if (DAT_8032ecb8 != '\0') {
              *(undefined *)((int)&DAT_8032ec8c[6].y + 3) = DAT_8032ecb9;
            }
            if (*(char *)&DAT_8032ec8c[5].z == '\0') {
              uVar6 = 0;
            }
            else {
              iVar8 = 0;
              pfVar7 = mapHit->m_vertices +
                       (uint)*(ushort *)
                              ((int)&DAT_8032ec8c[5].z +
                              (uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2) * 2 + 2) * 3;
              local_134.x = *pfVar7;
              local_134.y = pfVar7[1];
              local_134.z = pfVar7[2];
              for (iVar11 = 0; iVar11 < (int)(uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2);
                  iVar11 = iVar11 + 1) {
                pfVar7 = mapHit->m_vertices + (uint)*(ushort *)((int)&DAT_8032ec8c[6].x + iVar8) * 3
                ;
                local_140.x = *pfVar7;
                local_140.y = pfVar7[1];
                local_140.z = pfVar7[2];
                if (((uint)*(byte *)&DAT_8032ec8c[5].z & 1 << iVar11) != 0) {
                  PSVECSubtract(&local_140,&local_134,&local_14c);
                  local_164 = g_hit_cyl.m_bottom.x;
                  local_160 = g_hit_cyl.m_bottom.y;
                  local_15c = g_hit_cyl.m_bottom.z;
                  local_158 = g_hit_cyl.m_radius;
                  local_154 = g_hit_cyl.m_height;
                  local_150 = g_hit_cyl.m_top.x;
                  local_98 = FLOAT_8032f8ec;
                  local_9c = FLOAT_8032f8ec;
                  local_a0 = FLOAT_8032f8ec;
                  local_8c = FLOAT_8032f8f0;
                  local_90 = FLOAT_8032f8f0;
                  local_94 = FLOAT_8032f8f0;
                  local_c8 = local_134.x;
                  local_c4 = local_134.y;
                  local_c0 = local_134.z;
                  local_b0 = local_14c.x;
                  local_ac = local_14c.y;
                  local_a8 = local_14c.z;
                  local_a4 = g_hit_cyl.m_top.y;
                  iVar9 = FindIntersection__FRC3VecRC3VecRC12CMapCylinderRf
                                    (&local_164,&local_158,&local_c8,&local_168);
                  if ((iVar9 != 0) && (fVar2 = local_168, local_168 < FLOAT_8032ec80))
                  goto LAB_800263fc;
                }
                iVar8 = iVar8 + 2;
                local_134.x = local_140.x;
                local_134.y = local_140.y;
                local_134.z = local_140.z;
              }
              uVar6 = 0;
            }
          }
          else {
            PSVECScale(FLOAT_8032ec7c,(Vec *)&g_hit_cyl.m_radius,&g_hit_hpv);
            PSVECAdd(&g_hit_cyl.m_bottom,&g_hit_hpv,&g_hit_hpv);
            PSVECScale(g_hit_cyl.m_top.y,DAT_8032ec8c,&VStack_e0);
            PSVECSubtract(&g_hit_hpv,&VStack_e0,&local_d4);
            uVar10 = 3;
            bVar1 = *(byte *)((int)&DAT_8032ec8c[5].z + 1);
            pfVar7 = mapHit->m_vertices +
                     (uint)*(ushort *)
                            ((int)&DAT_8032ec8c[5].z +
                            (uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2) * 2 + 2) * 3;
            local_104 = *pfVar7;
            local_100 = pfVar7[1];
            local_fc = pfVar7[2];
            if (bVar1 == 1) {
              dVar13 = (double)FLOAT_8032f8d0;
              iVar8 = 0;
              local_d4.y = local_d4.z;
              iVar9 = 0;
              local_d4.z = FLOAT_8032f8d0;
              for (iVar12 = 0; fVar2 = FLOAT_8032ec7c,
                  iVar12 < (int)(uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2); iVar12 = iVar12 + 1) {
                pfVar7 = mapHit->m_vertices + (uint)*(ushort *)((int)&DAT_8032ec8c[6].x + iVar8) * 3
                ;
                local_ec.x = local_104 + *(float *)((int)&DAT_8032ec8c[3].z + iVar9);
                dVar14 = (double)*pfVar7;
                dVar15 = (double)pfVar7[1];
                dVar16 = (double)pfVar7[2];
                local_ec.y = local_fc + *(float *)((int)&DAT_8032ec8c[4].x + iVar9);
                local_ec.z = (float)dVar13;
                local_f8.x = (float)(dVar14 + (double)*(float *)((int)&DAT_8032ec8c[3].z + iVar9));
                local_f8.y = (float)(dVar16 + (double)*(float *)((int)&DAT_8032ec8c[4].x + iVar9));
                local_f8.z = (float)dVar13;
                PSVECSubtract(&local_f8,&local_ec,&VStack_110);
                PSVECSubtract(&local_d4,&local_f8,&VStack_11c);
                PSVECCrossProduct(&VStack_110,&VStack_11c,&VStack_128);
                if ((double)VStack_128.z < dVar13) {
                  if ((double)VStack_128.z <= dVar13) {
                    uVar10 = uVar10 & 2;
                    goto joined_r0x800262c0;
                  }
                }
                else {
                  uVar10 = uVar10 & 1;
joined_r0x800262c0:
                  if (uVar10 == 0) goto LAB_80026504;
                }
                local_104 = (float)dVar14;
                iVar8 = iVar8 + 2;
                iVar9 = iVar9 + 8;
                local_100 = (float)dVar15;
                local_fc = (float)dVar16;
              }
            }
            else if (bVar1 == 0) {
              iVar8 = 0;
              iVar9 = 0;
              dVar13 = (double)FLOAT_8032f8d0;
              local_d4.x = local_d4.y;
              local_d4.y = local_d4.z;
              local_d4.z = FLOAT_8032f8d0;
              for (iVar12 = 0; fVar2 = FLOAT_8032ec7c,
                  iVar12 < (int)(uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2); iVar12 = iVar12 + 1) {
                pfVar7 = mapHit->m_vertices + (uint)*(ushort *)((int)&DAT_8032ec8c[6].x + iVar8) * 3
                ;
                local_ec.x = local_100 + *(float *)((int)&DAT_8032ec8c[3].z + iVar9);
                dVar16 = (double)*pfVar7;
                dVar15 = (double)pfVar7[1];
                dVar14 = (double)pfVar7[2];
                local_ec.y = local_fc + *(float *)((int)&DAT_8032ec8c[4].x + iVar9);
                local_ec.z = (float)dVar13;
                local_f8.x = (float)(dVar15 + (double)*(float *)((int)&DAT_8032ec8c[3].z + iVar9));
                local_f8.y = (float)(dVar14 + (double)*(float *)((int)&DAT_8032ec8c[4].x + iVar9));
                local_f8.z = (float)dVar13;
                PSVECSubtract(&local_f8,&local_ec,&VStack_110);
                PSVECSubtract(&local_d4,&local_f8,&VStack_11c);
                PSVECCrossProduct(&VStack_110,&VStack_11c,&VStack_128);
                if ((double)VStack_128.z < dVar13) {
                  if ((double)VStack_128.z <= dVar13) {
                    uVar10 = uVar10 & 2;
                    goto joined_r0x800261a8;
                  }
                }
                else {
                  uVar10 = uVar10 & 1;
joined_r0x800261a8:
                  if (uVar10 == 0) goto LAB_80026504;
                }
                local_104 = (float)dVar16;
                iVar8 = iVar8 + 2;
                iVar9 = iVar9 + 8;
                local_100 = (float)dVar15;
                local_fc = (float)dVar14;
              }
            }
            else {
              fVar2 = FLOAT_8032ec7c;
              if (bVar1 < 3) {
                dVar13 = (double)FLOAT_8032f8d0;
                iVar8 = 0;
                local_d4.z = FLOAT_8032f8d0;
                iVar9 = 0;
                for (iVar12 = 0; fVar2 = FLOAT_8032ec7c,
                    iVar12 < (int)(uint)*(byte *)((int)&DAT_8032ec8c[5].z + 2); iVar12 = iVar12 + 1)
                {
                  pfVar7 = mapHit->m_vertices +
                           (uint)*(ushort *)((int)&DAT_8032ec8c[6].x + iVar8) * 3;
                  local_ec.x = local_104 + *(float *)((int)&DAT_8032ec8c[3].z + iVar9);
                  dVar14 = (double)*pfVar7;
                  dVar15 = (double)pfVar7[1];
                  dVar16 = (double)pfVar7[2];
                  local_ec.y = local_100 + *(float *)((int)&DAT_8032ec8c[4].x + iVar9);
                  local_ec.z = (float)dVar13;
                  local_f8.x = (float)(dVar14 + (double)*(float *)((int)&DAT_8032ec8c[3].z + iVar9))
                  ;
                  local_f8.y = (float)(dVar15 + (double)*(float *)((int)&DAT_8032ec8c[4].x + iVar9))
                  ;
                  local_f8.z = (float)dVar13;
                  PSVECSubtract(&local_f8,&local_ec,&VStack_110);
                  PSVECSubtract(&local_d4,&local_f8,&VStack_11c);
                  PSVECCrossProduct(&VStack_110,&VStack_11c,&VStack_128);
                  if ((double)VStack_128.z < dVar13) {
                    if ((double)VStack_128.z <= dVar13) {
                      uVar10 = uVar10 & 2;
                      goto joined_r0x800263d0;
                    }
                  }
                  else {
                    uVar10 = uVar10 & 1;
joined_r0x800263d0:
                    if (uVar10 == 0) goto LAB_80026504;
                  }
                  local_104 = (float)dVar14;
                  iVar8 = iVar8 + 2;
                  iVar9 = iVar9 + 8;
                  local_100 = (float)dVar15;
                  local_fc = (float)dVar16;
                }
              }
            }
LAB_800263fc:
            FLOAT_8032ec7c = fVar2;
            if (DAT_8032ecb8 != '\0') {
              *(undefined *)((int)&DAT_8032ec8c[6].y + 3) = DAT_8032ecb9;
            }
            uVar6 = 1;
            FLOAT_8032ec84 = FLOAT_8032ec7c;
            FLOAT_8032ec80 = FLOAT_8032ec7c;
            DAT_8032ec90 = DAT_8032ec8c;
            g_hit_cyl_min.m_bottom.x = g_hit_cyl.m_bottom.x;
            g_hit_cyl_min.m_bottom.y = g_hit_cyl.m_bottom.y;
            g_hit_cyl_min.m_bottom.z = g_hit_cyl.m_bottom.z;
            g_hit_cyl_min.m_direction.x = g_hit_cyl.m_direction.x;
            g_hit_cyl_min.m_direction.y = g_hit_cyl.m_direction.y;
            g_hit_cyl_min.m_direction.z = g_hit_cyl.m_direction.z;
            g_hit_cyl_min.m_radius = g_hit_cyl.m_radius;
            g_hit_cyl_min.m_height = g_hit_cyl.m_height;
            g_hit_cyl_min.m_top.x = g_hit_cyl.m_top.x;
            g_hit_cyl_min.m_top.y = g_hit_cyl.m_top.y;
            g_hit_cyl_min.m_top.z = g_hit_cyl.m_top.z;
            g_hit_cyl_min.m_direction2.x = g_hit_cyl.m_direction2.x;
            g_hit_cyl_min.m_direction2.y = g_hit_cyl.m_direction2.y;
            g_hit_cyl_min.m_direction2.z = g_hit_cyl.m_direction2.z;
            g_hit_cyl_min.m_radius2 = g_hit_cyl.m_radius2;
            g_hit_cyl_min.m_height2 = g_hit_cyl.m_height2;
            g_hit_mvec_min.x = g_hit_mvec.x;
            g_hit_mvec_min.y = g_hit_mvec.y;
            g_hit_mvec_min.z = g_hit_mvec.z;
            g_hit_hpv_min.x = g_hit_hpv.x;
            g_hit_hpv_min.y = g_hit_hpv.y;
            g_hit_hpv_min.z = g_hit_hpv.z;
            DAT_8032ec88 = 1;
            DAT_8032ec78 = iVar11;
          }
        }
        else {
          uVar6 = 0;
        }
      }
      else {
        uVar6 = 0;
      }
    }
    else {
      uVar6 = 0;
    }
  }
  return uVar6;
}

