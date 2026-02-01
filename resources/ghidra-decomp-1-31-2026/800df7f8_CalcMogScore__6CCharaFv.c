// Function: CalcMogScore__6CCharaFv
// Entry: 800df7f8
// Size: 2224 bytes

/* WARNING: Removing unreachable block (ram,0x800e008c) */
/* WARNING: Removing unreachable block (ram,0x800df808) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcMogScore__6CCharaFv(CChara *chara)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  void ***pppvVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  byte local_b0;
  byte local_af;
  byte local_ae;
  byte local_ac;
  byte local_ab;
  byte local_aa;
  byte local_a9;
  byte local_a8;
  byte local_a7;
  byte local_a6;
  byte local_a4;
  byte local_a3;
  byte local_a2;
  byte local_a1;
  byte local_a0;
  byte local_9f;
  byte local_9e;
  byte local_9c;
  byte local_9b;
  byte local_9a;
  byte local_99;
  undefined auStack_98 [4];
  undefined *local_94 [4];
  uint local_84 [5];
  undefined8 local_70;
  undefined8 local_68;
  
  memset(&chara->field_0x2018,0,0x40);
  iVar22 = 0;
  iVar21 = 0;
  iVar20 = 0;
  uVar19 = 0;
  dVar25 = DOUBLE_80331100;
  do {
    uVar16 = uVar19 - 0x20;
    iVar11 = (int)uVar19 >> 0x1f;
    uVar18 = 0;
    do {
      uVar17 = uVar18 - 0x20;
      local_84[3] = 0x43300000;
      local_84[4] = uVar17 * uVar17 + uVar16 * uVar16 ^ 0x80000000;
      dVar23 = (double)sqrt((double)CONCAT44(0x43300000,local_84[4]) - dVar25);
      iVar15 = (int)dVar23;
      local_70 = (double)(longlong)iVar15;
      if (iVar15 < 0x40) {
        iVar2 = (int)uVar18 >> 0x1f;
        uVar1 = *(ushort *)
                 ((int)chara +
                 (((iVar2 * 4 | uVar18 * 0x40000000 + iVar2 >> 0x1e) - iVar2) +
                 ((iVar11 * 4 | uVar19 * 0x40000000 + iVar11 >> 0x1e) - iVar11) * 4 +
                 (((int)uVar18 >> 2) + (uint)((int)uVar18 < 0 && (uVar18 & 3) != 0)) * 0x10 +
                 (((int)uVar19 >> 2) + (uint)((int)uVar19 < 0 && (uVar19 & 3) != 0)) * 0x100) * 2 +
                 4);
        uVar14 = uVar1 >> 0xc & 7;
        __ct__6CColorFUcUcUcUc(auStack_98,uVar1 >> 8 & 0xf,uVar1 >> 4 & 0xf,uVar1 & 0xf,uVar14);
        __ct__6CColorFUcUcUcUc(&local_a0,0xf,4,4,2);
        __ct__6CColorFR6CColor(&local_9c,auStack_98);
        uVar10 = (uint)local_99;
        uVar6 = (int)((uint)local_9c - (uint)local_a0) >> 0x1f;
        uVar6 = ((uVar6 ^ (uint)local_9c - (uint)local_a0) - uVar6) + (7 - uVar10);
        uVar7 = (int)((uint)local_9b - (uint)local_9f) >> 0x1f;
        uVar7 = ((uVar7 ^ (uint)local_9b - (uint)local_9f) - uVar7) + (7 - uVar10);
        uVar12 = (int)((uint)local_9a - (uint)local_9e) >> 0x1f;
        uVar10 = ((uVar12 ^ (uint)local_9a - (uint)local_9e) - uVar12) + (7 - uVar10);
        local_84[0] = countLeadingZeros(3 - (((uint)(uVar6 < 6) - ((int)uVar6 >> 0x1f)) +
                                             ((uint)(uVar7 < 6) - ((int)uVar7 >> 0x1f)) +
                                            ((uint)(uVar10 < 6) - ((int)uVar10 >> 0x1f))));
        local_84[0] = local_84[0] >> 5;
        __ct__6CColorFUcUcUcUc(&local_a8,4,0xf,4,2);
        __ct__6CColorFR6CColor(&local_a4,auStack_98);
        uVar10 = (uint)local_a1;
        uVar6 = (int)((uint)local_a4 - (uint)local_a8) >> 0x1f;
        uVar6 = ((uVar6 ^ (uint)local_a4 - (uint)local_a8) - uVar6) + (7 - uVar10);
        uVar7 = (int)((uint)local_a3 - (uint)local_a7) >> 0x1f;
        uVar7 = ((uVar7 ^ (uint)local_a3 - (uint)local_a7) - uVar7) + (7 - uVar10);
        uVar12 = (int)((uint)local_a2 - (uint)local_a6) >> 0x1f;
        uVar10 = ((uVar12 ^ (uint)local_a2 - (uint)local_a6) - uVar12) + (7 - uVar10);
        local_84[1] = countLeadingZeros(3 - (((uint)(uVar6 < 6) - ((int)uVar6 >> 0x1f)) +
                                             ((uint)(uVar7 < 6) - ((int)uVar7 >> 0x1f)) +
                                            ((uint)(uVar10 < 6) - ((int)uVar10 >> 0x1f))));
        local_84[1] = local_84[1] >> 5;
        __ct__6CColorFUcUcUcUc(&local_b0,4,8,0xf,2);
        __ct__6CColorFR6CColor(&local_ac,auStack_98);
        uVar12 = (uint)local_a9;
        uVar6 = (int)((uint)local_ac - (uint)local_b0) >> 0x1f;
        local_84[4] = uVar16 ^ 0x80000000;
        uVar10 = ((uVar6 ^ (uint)local_ac - (uint)local_b0) - uVar6) + (7 - uVar12);
        uVar6 = (int)((uint)local_ab - (uint)local_af) >> 0x1f;
        uVar7 = ((uVar6 ^ (uint)local_ab - (uint)local_af) - uVar6) + (7 - uVar12);
        uVar6 = (int)((uint)local_aa - (uint)local_ae) >> 0x1f;
        uVar6 = ((uVar6 ^ (uint)local_aa - (uint)local_ae) - uVar6) + (7 - uVar12);
        local_70 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        local_84[3] = 0x43300000;
        iVar2 = iVar15 / 0xc + (iVar15 >> 0x1f);
        dVar23 = local_70 - DOUBLE_80331100;
        local_84[2] = countLeadingZeros(3 - (((uint)(uVar10 < 6) - ((int)uVar10 >> 0x1f)) +
                                             ((uint)(uVar7 < 6) - ((int)uVar7 >> 0x1f)) +
                                            ((uint)(uVar6 < 6) - ((int)uVar6 >> 0x1f))));
        dVar24 = (double)CONCAT44(0x43300000,local_84[4]) - DOUBLE_80331100;
        local_84[2] = local_84[2] >> 5;
        *(uint *)&chara->field_0x2054 = *(int *)&chara->field_0x2054 + uVar14;
        iVar15 = iVar15 + (iVar2 - (iVar2 >> 0x1f)) * -0xc;
        dVar23 = (double)atan2(dVar23,dVar24);
        iVar3 = 0;
        iVar8 = 0;
        puVar5 = local_84;
        iVar9 = 0;
        local_68 = (double)(longlong)(int)(DOUBLE_803310f0 * dVar23);
        iVar13 = (int)(DOUBLE_803310f0 * dVar23) + 0x168;
        iVar2 = iVar13 / 0x2d + (iVar13 >> 0x1f);
        iVar13 = iVar13 + (iVar2 - (iVar2 >> 0x1f)) * -0x2d;
        iVar2 = 3;
        pppvVar4 = (void ***)chara;
        do {
          if ((iVar15 < iVar3) || ((iVar9 + 1) * 4 <= iVar15)) {
            if ((iVar13 < iVar8) || ((iVar9 + 1) * 0xf <= iVar13)) {
              iVar22 = iVar22 + 1;
              pppvVar4[0x809] = (void **)((int)pppvVar4[0x809] + *puVar5);
            }
            else {
              iVar20 = iVar20 + 1;
              pppvVar4[0x80c] = (void **)((int)pppvVar4[0x80c] + *puVar5);
            }
          }
          else {
            iVar21 = iVar21 + 1;
            pppvVar4[0x80f] = (void **)((int)pppvVar4[0x80f] + *puVar5);
          }
          iVar3 = iVar3 + 4;
          puVar5 = puVar5 + 1;
          pppvVar4 = pppvVar4 + 1;
          iVar8 = iVar8 + 0xf;
          iVar9 = iVar9 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      uVar18 = uVar18 + 1;
    } while ((int)uVar18 < 0x40);
    uVar19 = uVar19 + 1;
  } while ((int)uVar19 < 0x40);
  iVar11 = *(int *)&chara->field_0x2054 * 100;
  iVar11 = iVar11 / 0x7000 + (iVar11 >> 0x1f);
  *(int *)&chara->field_0x2054 = iVar11 - (iVar11 >> 0x1f);
  iVar22 = iVar22 / 3;
  *(int *)&chara->field_0x2024 = (*(int *)&chara->field_0x2024 * 100) / iVar22;
  iVar21 = iVar21 / 3;
  *(int *)&chara->field_0x203c = (*(int *)&chara->field_0x203c * 100) / iVar21;
  iVar20 = iVar20 / 3;
  *(int *)&chara->field_0x2030 = (*(int *)&chara->field_0x2030 * 100) / iVar20;
  *(int *)&chara->field_0x2028 = (*(int *)&chara->field_0x2028 * 100) / iVar22;
  *(int *)&chara->field_0x2040 = (*(int *)&chara->field_0x2040 * 100) / iVar21;
  *(int *)&chara->field_0x2034 = (*(int *)&chara->field_0x2034 * 100) / iVar20;
  *(int *)&chara->field_0x202c = (*(int *)&chara->field_0x202c * 100) / iVar22;
  *(int *)&chara->field_0x2044 = (*(int *)&chara->field_0x2044 * 100) / iVar21;
  *(int *)&chara->field_0x2038 = (*(int *)&chara->field_0x2038 * 100) / iVar20;
  iVar22 = 3;
  pppvVar4 = (void ***)chara;
  do {
    pppvVar4[0x806] =
         (void **)(((int)pppvVar4[0x80c] + (int)pppvVar4[0x80f] * 2 + (int)pppvVar4[0x809] * -2) / 3
                  );
    iVar21 = (int)pppvVar4[0x806];
    if (iVar21 < 0) {
      iVar20 = 0;
    }
    else {
      iVar20 = 100;
      if (iVar21 < 0x65) {
        iVar20 = iVar21;
      }
    }
    pppvVar4[0x806] = (void **)iVar20;
    iVar21 = (100 - (int)pppvVar4[0x806]) / 5 + (100 - (int)pppvVar4[0x806] >> 0x1f);
    pppvVar4[0x812] = (void **)(iVar21 - (iVar21 >> 0x1f));
    iVar21 = (int)pppvVar4[0x812];
    if (iVar21 < 5) {
      iVar20 = 5;
    }
    else {
      iVar20 = 0xf;
      if (iVar21 < 0x10) {
        iVar20 = iVar21;
      }
    }
    pppvVar4[0x812] = (void **)iVar20;
    pppvVar4 = pppvVar4 + 1;
    iVar22 = iVar22 + -1;
  } while (iVar22 != 0);
  uVar19 = *(uint *)&chara->field_0x2018;
  if (2 < (int)uVar19) {
    local_68 = (double)(CONCAT44(0x43300000,
                                 *(int *)&chara->field_0x201c + *(int *)&chara->field_0x2020) ^
                       0x80000000);
    local_70 = (double)CONCAT44(0x43300000,uVar19 ^ 0x80000000);
    if (FLOAT_803310f8 * (float)(local_68 - DOUBLE_80331100) < (float)(local_70 - DOUBLE_80331100))
    {
      Game.game.m_gameWork.m_mogScoreRadarType = '\x01';
      goto LAB_800dffb8;
    }
  }
  uVar16 = *(uint *)&chara->field_0x201c;
  if (2 < (int)uVar16) {
    local_68 = (double)(CONCAT44(0x43300000,uVar19 + *(int *)&chara->field_0x2020) ^ 0x80000000);
    local_70 = (double)CONCAT44(0x43300000,uVar16 ^ 0x80000000);
    if (FLOAT_803310f8 * (float)(local_68 - DOUBLE_80331100) < (float)(local_70 - DOUBLE_80331100))
    {
      Game.game.m_gameWork.m_mogScoreRadarType = '\x02';
      goto LAB_800dffb8;
    }
  }
  if (2 < (int)*(uint *)&chara->field_0x2020) {
    local_68 = (double)CONCAT44(0x43300000,uVar19 + uVar16 ^ 0x80000000);
    local_70 = (double)CONCAT44(0x43300000,*(uint *)&chara->field_0x2020 ^ 0x80000000);
    if (FLOAT_803310f8 * (float)(local_68 - DOUBLE_80331100) < (float)(local_70 - DOUBLE_80331100))
    {
      Game.game.m_gameWork.m_mogScoreRadarType = '\x03';
      goto LAB_800dffb8;
    }
  }
  Game.game.m_gameWork.m_mogScoreRadarType = '\0';
LAB_800dffb8:
  local_94[0] = PTR_DAT_801db6a4;
  local_94[1] = PTR_DAT_801db6a8;
  local_94[2] = PTR_DAT_801db6ac;
  local_94[3] = PTR_DAT_801db6b0;
  Printf__8CGraphicFUlUlPce
            (&Graphic,5,0xb,s_SCORE_BIT__d__d__d_a__d_all___d__801db6cc,
             *(undefined4 *)&chara->field_0x2048,*(undefined4 *)&chara->field_0x204c,
             *(undefined4 *)&chara->field_0x2050,*(undefined4 *)&chara->field_0x2054,
             *(undefined4 *)&chara->field_0x2018,*(undefined4 *)&chara->field_0x201c,
             *(undefined4 *)&chara->field_0x2020,*(undefined4 *)&chara->field_0x2024,
             *(undefined4 *)&chara->field_0x2028,*(undefined4 *)&chara->field_0x202c);
  Printf__8CGraphicFUlUlPce
            (&Graphic,5,0xc,s_line___d__d__d__circle___d__d__d_801db700,
             *(undefined4 *)&chara->field_0x2030,*(undefined4 *)&chara->field_0x2034,
             *(undefined4 *)&chara->field_0x2038,*(undefined4 *)&chara->field_0x203c,
             *(undefined4 *)&chara->field_0x2040,*(undefined4 *)&chara->field_0x2044,
             local_94[Game.game.m_gameWork.m_mogScoreRadarType]);
  return;
}

