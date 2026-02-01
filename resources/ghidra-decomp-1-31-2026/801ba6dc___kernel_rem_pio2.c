// Function: __kernel_rem_pio2
// Entry: 801ba6dc
// Size: 3668 bytes

void __kernel_rem_pio2(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                      int param_6)

{
  double *pdVar1;
  double *pdVar2;
  double *pdVar3;
  double *pdVar4;
  double *pdVar5;
  double *pdVar6;
  double *pdVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  uint *puVar14;
  bool bVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  uint uVar24;
  uint *puVar25;
  double *pdVar26;
  undefined4 *puVar27;
  uint *puVar28;
  double *pdVar29;
  double *pdVar30;
  double *pdVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  uint uVar39;
  int iVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  double dVar44;
  double dVar45;
  double dVar46;
  double dVar47;
  double dVar48;
  double dVar49;
  double dVar50;
  double dVar51;
  double dVar52;
  double dVar53;
  undefined8 uVar54;
  uint auStack_2cc [21];
  double local_278 [20];
  double local_1d8 [20];
  double local_138 [20];
  double local_98;
  undefined4 local_90;
  uint uStack_8c;
  double local_88;
  undefined8 local_80;
  
  uVar54 = func_0x801affcc();
  pdVar30 = (double *)((ulonglong)uVar54 >> 0x20);
  pdVar26 = (double *)uVar54;
  uVar39 = *(uint *)(&DAT_801e7638 + param_5 * 4);
  iVar16 = (param_3 + -3) / 0x18 + (param_3 + -3 >> 0x1f);
  iVar40 = param_4 + -1;
  iVar16 = iVar16 - (iVar16 >> 0x1f);
  if (iVar16 < 0) {
    iVar16 = 0;
  }
  iVar32 = iVar16 - iVar40;
  param_3 = param_3 + (iVar16 + 1) * -0x18;
  iVar17 = iVar40 + uVar39 + 1;
  puVar27 = (undefined4 *)(param_6 + iVar32 * 4);
  pdVar31 = local_138;
  if (-1 < (int)(iVar40 + uVar39)) {
    do {
      dVar47 = DOUBLE_80333bd8;
      if (-1 < iVar32) {
        local_98 = (double)(CONCAT44(0x43300000,*puVar27) ^ 0x80000000);
        dVar47 = local_98 - DOUBLE_80333c10;
      }
      *pdVar31 = dVar47;
      pdVar31 = pdVar31 + 1;
      puVar27 = puVar27 + 1;
      iVar32 = iVar32 + 1;
      iVar17 = iVar17 + -1;
    } while (iVar17 != 0);
  }
  pdVar31 = local_278;
  for (iVar17 = 0; iVar17 <= (int)uVar39; iVar17 = iVar17 + 1) {
    iVar32 = 0;
    dVar47 = DOUBLE_80333bd8;
    if (-1 < iVar40) {
      if (8 < param_4) {
        uVar41 = param_4 - 1U >> 3;
        iVar33 = iVar40 + iVar17;
        pdVar29 = pdVar30;
        if (-1 < param_4 + -9) {
          do {
            iVar34 = iVar33 - iVar32;
            iVar36 = iVar32 + 1;
            dVar48 = *pdVar29;
            iVar19 = iVar32 + 2;
            iVar20 = iVar32 + 3;
            pdVar1 = pdVar29 + 1;
            pdVar2 = pdVar29 + 2;
            iVar21 = iVar32 + 4;
            pdVar3 = pdVar29 + 3;
            iVar22 = iVar32 + 5;
            pdVar4 = pdVar29 + 4;
            iVar37 = iVar32 + 6;
            pdVar5 = pdVar29 + 5;
            iVar35 = iVar32 + 7;
            pdVar6 = pdVar29 + 6;
            iVar32 = iVar32 + 8;
            pdVar7 = pdVar29 + 7;
            pdVar29 = pdVar29 + 8;
            dVar47 = *pdVar7 * local_138[iVar33 - iVar35] +
                     *pdVar6 * local_138[iVar33 - iVar37] +
                     *pdVar5 * local_138[iVar33 - iVar22] +
                     *pdVar4 * local_138[iVar33 - iVar21] +
                     *pdVar3 * local_138[iVar33 - iVar20] +
                     *pdVar2 * local_138[iVar33 - iVar19] +
                     *pdVar1 * local_138[iVar33 - iVar36] + dVar48 * local_138[iVar34] + dVar47;
            uVar41 = uVar41 - 1;
          } while (uVar41 != 0);
        }
      }
      iVar33 = param_4 - iVar32;
      pdVar29 = pdVar30 + iVar32;
      if (iVar32 <= iVar40) {
        do {
          iVar34 = (iVar40 + iVar17) - iVar32;
          dVar48 = *pdVar29;
          pdVar29 = pdVar29 + 1;
          iVar32 = iVar32 + 1;
          dVar47 = dVar48 * local_138[iVar34] + dVar47;
          iVar33 = iVar33 + -1;
        } while (iVar33 != 0);
      }
    }
    *pdVar31 = dVar47;
    pdVar31 = pdVar31 + 1;
  }
  puVar25 = auStack_2cc + 1;
  uVar41 = uVar39;
  dVar47 = DOUBLE_80333be0;
  dVar48 = DOUBLE_80333c10;
  dVar52 = DOUBLE_80333be8;
  dVar50 = DOUBLE_80333bf8;
  dVar51 = DOUBLE_80333bf0;
  dVar53 = DOUBLE_80333bd8;
  do {
    pdVar31 = local_278 + uVar41;
    dVar45 = *pdVar31;
    if (0 < (int)uVar41) {
      uVar42 = uVar41 >> 1;
      puVar28 = puVar25;
      uVar23 = uVar41;
      if (uVar42 != 0) {
        do {
          local_90 = 0x43300000;
          local_98 = (double)(longlong)(int)(dVar47 * dVar45);
          uStack_8c = (int)(dVar47 * dVar45) ^ 0x80000000;
          dVar49 = (double)CONCAT44(0x43300000,uStack_8c) - dVar48;
          local_90 = 0x43300000;
          dVar46 = dVar49 + pdVar31[-1];
          pdVar31 = pdVar31 + -2;
          dVar44 = *pdVar31;
          uVar23 = (uint)(dVar47 * dVar46);
          *puVar28 = (int)-(dVar52 * dVar49 - dVar45);
          local_98 = (double)(longlong)(int)uVar23;
          uStack_8c = uVar23 ^ 0x80000000;
          dVar49 = (double)(CONCAT44(local_90,uVar23) ^ 0x80000000) - dVar48;
          dVar45 = dVar49 + dVar44;
          uVar23 = (uint)-(dVar52 * dVar49 - dVar46);
          local_88 = (double)(longlong)(int)uVar23;
          puVar28[1] = uVar23;
          puVar28 = puVar28 + 2;
          uVar42 = uVar42 - 1;
        } while (uVar42 != 0);
        uVar23 = uVar41 & 1;
        if (uVar23 == 0) goto LAB_801baa50;
      }
      do {
        local_90 = 0x43300000;
        pdVar31 = pdVar31 + -1;
        local_98 = (double)(longlong)(int)(dVar47 * dVar45);
        uStack_8c = (int)(dVar47 * dVar45) ^ 0x80000000;
        dVar46 = (double)CONCAT44(0x43300000,uStack_8c) - dVar48;
        dVar44 = dVar52 * dVar46 - dVar45;
        dVar45 = dVar46 + *pdVar31;
        uVar42 = (uint)-dVar44;
        local_88 = (double)(longlong)(int)uVar42;
        *puVar28 = uVar42;
        uVar23 = uVar23 - 1;
        puVar28 = puVar28 + 1;
      } while (uVar23 != 0);
    }
LAB_801baa50:
    dVar45 = (double)ldexp(param_3);
    dVar44 = (double)floor(dVar50 * dVar45);
    dVar45 = -(dVar51 * dVar44 - dVar45);
    local_90 = 0x43300000;
    iVar17 = 0;
    uVar42 = (uint)dVar45;
    local_88 = (double)(longlong)(int)uVar42;
    uStack_8c = uVar42 ^ 0x80000000;
    dVar45 = dVar45 - ((double)CONCAT44(0x43300000,uVar42 ^ 0x80000000) - dVar48);
    if (param_3 < 1) {
      if (param_3 == 0) {
        iVar17 = (int)auStack_2cc[uVar41] >> 0x17;
      }
      else if (DOUBLE_80333c00 <= dVar45) {
        iVar17 = 2;
      }
    }
    else {
      iVar17 = (int)auStack_2cc[uVar41] >> (0x18U - param_3 & 0x3f);
      uVar42 = uVar42 + iVar17;
      auStack_2cc[uVar41] = auStack_2cc[uVar41] - (iVar17 << 0x18U - param_3);
      iVar17 = (int)auStack_2cc[uVar41] >> (0x17U - param_3 & 0x3f);
    }
    if (0 < iVar17) {
      bVar15 = false;
      uVar42 = uVar42 + 1;
      puVar28 = puVar25;
      uVar23 = uVar41;
      if (0 < (int)uVar41) {
        do {
          uVar24 = *puVar28;
          if (bVar15) {
            *puVar28 = 0xffffff - uVar24;
          }
          else if (uVar24 != 0) {
            bVar15 = true;
            *puVar28 = 0x1000000 - uVar24;
          }
          puVar28 = puVar28 + 1;
          uVar23 = uVar23 - 1;
        } while (uVar23 != 0);
      }
      if (0 < param_3) {
        if (param_3 == 2) {
          auStack_2cc[uVar41] = auStack_2cc[uVar41] & 0x3fffff;
        }
        else if ((param_3 < 2) && (0 < param_3)) {
          auStack_2cc[uVar41] = auStack_2cc[uVar41] & 0x7fffff;
        }
      }
      if ((iVar17 == 2) && (dVar45 = DOUBLE_80333c08 - dVar45, bVar15)) {
        dVar44 = (double)ldexp(param_3);
        dVar45 = dVar45 - dVar44;
      }
    }
    if (dVar53 != dVar45) break;
    uVar24 = 0;
    puVar28 = auStack_2cc + uVar41;
    uVar23 = uVar41 - uVar39;
    if ((int)uVar39 <= (int)(uVar41 - 1)) {
      uVar43 = uVar23 >> 3;
      if (uVar43 != 0) {
        do {
          uVar18 = *puVar28;
          puVar8 = puVar28 + -1;
          puVar9 = puVar28 + -2;
          puVar10 = puVar28 + -3;
          puVar11 = puVar28 + -4;
          puVar12 = puVar28 + -5;
          puVar13 = puVar28 + -6;
          puVar14 = puVar28 + -7;
          puVar28 = puVar28 + -8;
          uVar24 = uVar24 | uVar18 | *puVar8 | *puVar9 | *puVar10 | *puVar11 | *puVar12 | *puVar13 |
                   *puVar14;
          uVar43 = uVar43 - 1;
        } while (uVar43 != 0);
        uVar23 = uVar23 & 7;
        if (uVar23 == 0) goto LAB_801bac68;
      }
      do {
        uVar43 = *puVar28;
        puVar28 = puVar28 + -1;
        uVar24 = uVar24 | uVar43;
        uVar23 = uVar23 - 1;
      } while (uVar23 != 0);
    }
LAB_801bac68:
    if (uVar24 != 0) break;
    for (iVar17 = 1; puVar25[uVar39 - iVar17] == 0; iVar17 = iVar17 + 1) {
    }
    iVar32 = uVar41 + 1;
    pdVar31 = local_278 + iVar32;
    for (; iVar32 <= (int)(uVar41 + iVar17); iVar32 = iVar32 + 1) {
      iVar33 = iVar40 + iVar32;
      iVar34 = 0;
      local_88 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_6 + (iVar16 + iVar32) * 4)) ^
                         0x80000000);
      local_138[iVar33] = local_88 - dVar48;
      dVar45 = DOUBLE_80333bd8;
      if (-1 < iVar40) {
        if (8 < param_4) {
          uVar42 = param_4 - 1U >> 3;
          pdVar29 = pdVar30;
          if (-1 < param_4 + -9) {
            do {
              iVar35 = iVar33 - iVar34;
              iVar19 = iVar34 + 1;
              dVar44 = *pdVar29;
              iVar36 = iVar34 + 2;
              pdVar1 = pdVar29 + 4;
              iVar37 = iVar34 + 3;
              pdVar2 = pdVar29 + 1;
              iVar20 = iVar34 + 4;
              pdVar3 = pdVar29 + 2;
              iVar21 = iVar34 + 5;
              pdVar4 = pdVar29 + 6;
              pdVar5 = pdVar29 + 3;
              iVar38 = iVar34 + 6;
              pdVar6 = pdVar29 + 5;
              iVar22 = iVar34 + 7;
              pdVar7 = pdVar29 + 7;
              pdVar29 = pdVar29 + 8;
              iVar34 = iVar34 + 8;
              dVar45 = *pdVar7 * local_138[iVar33 - iVar22] +
                       *pdVar4 * local_138[iVar33 - iVar38] +
                       *pdVar6 * local_138[iVar33 - iVar21] +
                       *pdVar1 * local_138[iVar33 - iVar20] +
                       *pdVar5 * local_138[iVar33 - iVar37] +
                       *pdVar3 * local_138[iVar33 - iVar36] +
                       *pdVar2 * local_138[iVar33 - iVar19] + dVar44 * local_138[iVar35] + dVar45;
              uVar42 = uVar42 - 1;
            } while (uVar42 != 0);
          }
        }
        iVar19 = param_4 - iVar34;
        pdVar29 = pdVar30 + iVar34;
        if (iVar34 <= iVar40) {
          do {
            iVar20 = iVar33 - iVar34;
            dVar44 = *pdVar29;
            pdVar29 = pdVar29 + 1;
            iVar34 = iVar34 + 1;
            dVar45 = dVar44 * local_138[iVar20] + dVar45;
            iVar19 = iVar19 + -1;
          } while (iVar19 != 0);
        }
      }
      *pdVar31 = dVar45;
      pdVar31 = pdVar31 + 1;
    }
    uVar41 = uVar41 + iVar17;
  } while( true );
  if (DOUBLE_80333bd8 == dVar45) {
    for (puVar25 = auStack_2cc + uVar41; uVar41 = uVar41 - 1, param_3 = param_3 + -0x18,
        *puVar25 == 0; puVar25 = puVar25 + -1) {
    }
  }
  else {
    dVar47 = (double)ldexp(dVar45,-param_3);
    if (dVar47 < DOUBLE_80333be8) {
      local_80 = (double)(longlong)(int)dVar47;
      auStack_2cc[uVar41 + 1] = (int)dVar47;
    }
    else {
      local_90 = 0x43300000;
      param_3 = param_3 + 0x18;
      local_88 = (double)(longlong)(int)(DOUBLE_80333be0 * dVar47);
      uStack_8c = (int)(DOUBLE_80333be0 * dVar47) ^ 0x80000000;
      dVar48 = (double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80333c10;
      uVar23 = (uint)dVar48;
      local_80 = (double)(longlong)(int)uVar23;
      uVar24 = (uint)-(DOUBLE_80333be8 * dVar48 - dVar47);
      local_98 = (double)(longlong)(int)uVar24;
      auStack_2cc[uVar41 + 1] = uVar24;
      auStack_2cc[uVar41 + 2] = uVar23;
      uVar41 = uVar41 + 1;
    }
  }
  dVar47 = (double)ldexp(DOUBLE_80333c08,param_3);
  puVar25 = auStack_2cc + uVar41 + 1;
  pdVar30 = local_278 + uVar41;
  uVar23 = uVar41 + 1;
  if (-1 < (int)uVar41) {
    uVar24 = uVar23 >> 2;
    if (uVar24 != 0) {
      do {
        local_80 = (double)CONCAT44(0x43300000,local_80._4_4_);
        local_80 = (double)CONCAT44(0x43300000,*puVar25 ^ 0x80000000);
        dVar48 = local_80;
        puVar28 = puVar25 + -2;
        local_80 = (double)CONCAT44(0x43300000,puVar25[-1] ^ 0x80000000);
        uVar43 = puVar25[-3];
        local_80 = (double)CONCAT44(0x43300000,puVar25[-1] ^ 0x80000000);
        puVar25 = puVar25 + -4;
        dVar50 = local_80 - DOUBLE_80333c10;
        local_80 = (double)CONCAT44(0x43300000,*puVar28 ^ 0x80000000);
        dVar52 = local_80;
        *pdVar30 = dVar47 * (dVar48 - DOUBLE_80333c10);
        dVar48 = dVar47 * DOUBLE_80333be0 * DOUBLE_80333be0;
        local_80 = (double)CONCAT44(0x43300000,uVar43 ^ 0x80000000);
        pdVar30[-1] = dVar47 * DOUBLE_80333be0 * dVar50;
        dVar50 = dVar48 * DOUBLE_80333be0;
        dVar51 = local_80 - DOUBLE_80333c10;
        pdVar30[-2] = dVar48 * (dVar52 - DOUBLE_80333c10);
        dVar47 = dVar50 * DOUBLE_80333be0;
        pdVar30[-3] = dVar50 * dVar51;
        pdVar30 = pdVar30 + -4;
        uVar24 = uVar24 - 1;
      } while (uVar24 != 0);
      uVar23 = uVar23 & 3;
      if (uVar23 == 0) goto LAB_801bb034;
    }
    do {
      uVar24 = *puVar25;
      puVar25 = puVar25 + -1;
      local_80 = (double)(CONCAT44(0x43300000,uVar24) ^ 0x80000000);
      dVar48 = dVar47 * (local_80 - DOUBLE_80333c10);
      dVar47 = dVar47 * DOUBLE_80333be0;
      *pdVar30 = dVar48;
      pdVar30 = pdVar30 + -1;
      uVar23 = uVar23 - 1;
    } while (uVar23 != 0);
  }
LAB_801bb034:
  iVar16 = uVar41 + 1;
  uVar23 = uVar41;
  if (-1 < (int)uVar41) {
    do {
      iVar40 = uVar41 - uVar23;
      pdVar30 = (double *)&DAT_801e7648;
      dVar47 = DOUBLE_80333bd8;
      for (iVar32 = 0; (iVar32 <= (int)uVar39 && (iVar32 <= iVar40)); iVar32 = iVar32 + 1) {
        dVar48 = *pdVar30;
        pdVar30 = pdVar30 + 1;
        dVar47 = dVar48 * local_278[uVar23 + iVar32] + dVar47;
      }
      uVar23 = uVar23 - 1;
      local_1d8[iVar40] = dVar47;
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
  }
  if (param_5 != 3) {
    if (2 < param_5) goto LAB_801bb510;
    if (param_5 != 0) {
      if (param_5 < 0) goto LAB_801bb510;
      pdVar30 = local_1d8 + uVar41;
      uVar39 = uVar41 + 1;
      dVar47 = DOUBLE_80333bd8;
      if (-1 < (int)uVar41) {
        uVar23 = uVar39 >> 3;
        if (uVar23 != 0) {
          do {
            dVar48 = *pdVar30;
            pdVar31 = pdVar30 + -1;
            pdVar29 = pdVar30 + -2;
            pdVar1 = pdVar30 + -3;
            pdVar2 = pdVar30 + -4;
            pdVar3 = pdVar30 + -5;
            pdVar4 = pdVar30 + -6;
            pdVar5 = pdVar30 + -7;
            pdVar30 = pdVar30 + -8;
            dVar47 = dVar47 + dVar48 + *pdVar31 + *pdVar29 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                     *pdVar5;
            uVar23 = uVar23 - 1;
          } while (uVar23 != 0);
          uVar39 = uVar39 & 7;
          if (uVar39 == 0) goto LAB_801bb1ec;
        }
        do {
          dVar48 = *pdVar30;
          pdVar30 = pdVar30 + -1;
          dVar47 = dVar47 + dVar48;
          uVar39 = uVar39 - 1;
        } while (uVar39 != 0);
      }
LAB_801bb1ec:
      dVar48 = dVar47;
      if (iVar17 != 0) {
        dVar48 = -dVar47;
      }
      *pdVar26 = dVar48;
      iVar16 = 1;
      local_1d8[0] = local_1d8[0] - dVar47;
      if (0 < (int)uVar41) {
        if (8 < (int)uVar41) {
          pdVar30 = local_1d8 + 1;
          uVar39 = uVar41 - 1 >> 3;
          if (0 < (int)(uVar41 - 8)) {
            do {
              dVar47 = *pdVar30;
              iVar16 = iVar16 + 8;
              pdVar31 = pdVar30 + 1;
              pdVar29 = pdVar30 + 2;
              pdVar1 = pdVar30 + 3;
              pdVar2 = pdVar30 + 4;
              pdVar3 = pdVar30 + 5;
              pdVar4 = pdVar30 + 6;
              pdVar5 = pdVar30 + 7;
              pdVar30 = pdVar30 + 8;
              local_1d8[0] = local_1d8[0] + dVar47 + *pdVar31 + *pdVar29 + *pdVar1 + *pdVar2 +
                             *pdVar3 + *pdVar4 + *pdVar5;
              uVar39 = uVar39 - 1;
            } while (uVar39 != 0);
          }
        }
        iVar40 = (uVar41 + 1) - iVar16;
        pdVar30 = local_1d8 + iVar16;
        if (iVar16 <= (int)uVar41) {
          do {
            dVar47 = *pdVar30;
            pdVar30 = pdVar30 + 1;
            local_1d8[0] = local_1d8[0] + dVar47;
            iVar40 = iVar40 + -1;
          } while (iVar40 != 0);
        }
      }
      if (iVar17 != 0) {
        local_1d8[0] = -local_1d8[0];
      }
      pdVar26[1] = local_1d8[0];
      goto LAB_801bb510;
    }
    pdVar30 = local_1d8 + uVar41;
    uVar39 = uVar41 + 1;
    dVar47 = DOUBLE_80333bd8;
    if (-1 < (int)uVar41) {
      uVar41 = uVar39 >> 3;
      if (uVar41 != 0) {
        do {
          dVar48 = *pdVar30;
          pdVar31 = pdVar30 + -1;
          pdVar29 = pdVar30 + -2;
          pdVar1 = pdVar30 + -3;
          pdVar2 = pdVar30 + -4;
          pdVar3 = pdVar30 + -5;
          pdVar4 = pdVar30 + -6;
          pdVar5 = pdVar30 + -7;
          pdVar30 = pdVar30 + -8;
          dVar47 = dVar47 + dVar48 + *pdVar31 + *pdVar29 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                   *pdVar5;
          uVar41 = uVar41 - 1;
        } while (uVar41 != 0);
        uVar39 = uVar39 & 7;
        if (uVar39 == 0) goto LAB_801bb14c;
      }
      do {
        dVar48 = *pdVar30;
        pdVar30 = pdVar30 + -1;
        dVar47 = dVar47 + dVar48;
        uVar39 = uVar39 - 1;
      } while (uVar39 != 0);
    }
LAB_801bb14c:
    if (iVar17 != 0) {
      dVar47 = -dVar47;
    }
    *pdVar26 = dVar47;
    goto LAB_801bb510;
  }
  pdVar30 = local_1d8 + uVar41;
  if (0 < (int)uVar41) {
    uVar39 = uVar41 >> 2;
    pdVar31 = pdVar30;
    uVar23 = uVar41;
    if (uVar39 != 0) {
      do {
        dVar47 = pdVar31[-1] + *pdVar31;
        *pdVar31 = *pdVar31 + (pdVar31[-1] - dVar47);
        pdVar31[-1] = dVar47;
        dVar47 = pdVar31[-2] + pdVar31[-1];
        pdVar31[-1] = pdVar31[-1] + (pdVar31[-2] - dVar47);
        pdVar31[-2] = dVar47;
        dVar47 = pdVar31[-3] + pdVar31[-2];
        pdVar31[-2] = pdVar31[-2] + (pdVar31[-3] - dVar47);
        pdVar31[-3] = dVar47;
        dVar47 = pdVar31[-4] + pdVar31[-3];
        pdVar31[-3] = pdVar31[-3] + (pdVar31[-4] - dVar47);
        pdVar31 = pdVar31 + -4;
        *pdVar31 = dVar47;
        uVar39 = uVar39 - 1;
      } while (uVar39 != 0);
      uVar23 = uVar41 & 3;
      if (uVar23 == 0) goto LAB_801bb394;
    }
    do {
      dVar47 = pdVar31[-1] + *pdVar31;
      *pdVar31 = *pdVar31 + (pdVar31[-1] - dVar47);
      pdVar31[-1] = dVar47;
      uVar23 = uVar23 - 1;
      pdVar31 = pdVar31 + -1;
    } while (uVar23 != 0);
  }
LAB_801bb394:
  uVar39 = uVar41 - 1;
  if (1 < (int)uVar41) {
    uVar23 = uVar39 >> 2;
    pdVar31 = pdVar30;
    if (uVar23 != 0) {
      do {
        dVar47 = pdVar31[-1] + *pdVar31;
        *pdVar31 = *pdVar31 + (pdVar31[-1] - dVar47);
        pdVar31[-1] = dVar47;
        dVar47 = pdVar31[-2] + pdVar31[-1];
        pdVar31[-1] = pdVar31[-1] + (pdVar31[-2] - dVar47);
        pdVar31[-2] = dVar47;
        dVar47 = pdVar31[-3] + pdVar31[-2];
        pdVar31[-2] = pdVar31[-2] + (pdVar31[-3] - dVar47);
        pdVar31[-3] = dVar47;
        dVar47 = pdVar31[-4] + pdVar31[-3];
        pdVar31[-3] = pdVar31[-3] + (pdVar31[-4] - dVar47);
        pdVar31 = pdVar31 + -4;
        *pdVar31 = dVar47;
        uVar23 = uVar23 - 1;
      } while (uVar23 != 0);
      uVar39 = uVar39 & 3;
      if (uVar39 == 0) goto LAB_801bb450;
    }
    do {
      dVar47 = pdVar31[-1] + *pdVar31;
      *pdVar31 = *pdVar31 + (pdVar31[-1] - dVar47);
      pdVar31[-1] = dVar47;
      uVar39 = uVar39 - 1;
      pdVar31 = pdVar31 + -1;
    } while (uVar39 != 0);
  }
LAB_801bb450:
  uVar39 = uVar41 - 1;
  dVar47 = DOUBLE_80333bd8;
  if (1 < (int)uVar41) {
    uVar41 = uVar39 >> 3;
    if (uVar41 != 0) {
      do {
        dVar48 = *pdVar30;
        pdVar31 = pdVar30 + -1;
        pdVar29 = pdVar30 + -2;
        pdVar1 = pdVar30 + -3;
        pdVar2 = pdVar30 + -4;
        pdVar3 = pdVar30 + -5;
        pdVar4 = pdVar30 + -6;
        pdVar5 = pdVar30 + -7;
        pdVar30 = pdVar30 + -8;
        dVar47 = dVar47 + dVar48 + *pdVar31 + *pdVar29 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                 *pdVar5;
        uVar41 = uVar41 - 1;
      } while (uVar41 != 0);
      uVar39 = uVar39 & 7;
      if (uVar39 == 0) goto LAB_801bb4d0;
    }
    do {
      dVar48 = *pdVar30;
      pdVar30 = pdVar30 + -1;
      dVar47 = dVar47 + dVar48;
      uVar39 = uVar39 - 1;
    } while (uVar39 != 0);
  }
LAB_801bb4d0:
  if (iVar17 == 0) {
    *pdVar26 = local_1d8[0];
    pdVar26[1] = local_1d8[1];
    pdVar26[2] = dVar47;
  }
  else {
    *pdVar26 = -local_1d8[0];
    pdVar26[1] = -local_1d8[1];
    pdVar26[2] = -dVar47;
  }
LAB_801bb510:
  func_0x801b0018(uVar42 & 7);
  return;
}

