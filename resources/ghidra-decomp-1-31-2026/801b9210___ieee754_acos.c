// Function: __ieee754_acos
// Entry: 801b9210
// Size: 572 bytes

/* WARNING: Removing unreachable block (ram,0x801b9434) */
/* WARNING: Removing unreachable block (ram,0x801b9220) */

double __ieee754_acos(double param_1)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  uint local_28;
  int iStack_24;
  double local_20;
  
  local_28 = (uint)((ulonglong)param_1 >> 0x20);
  uVar1 = local_28 & 0x7fffffff;
  if (uVar1 < 0x3ff00000) {
    if (uVar1 < 0x3fe00000) {
      dVar2 = DOUBLE_80333958;
      if (0x3c600000 < uVar1) {
        dVar2 = param_1 * param_1;
        dVar2 = DOUBLE_80333958 -
                (param_1 -
                -(param_1 * ((dVar2 * (dVar2 * (dVar2 * (dVar2 * (dVar2 * (DOUBLE_80333990 * dVar2 +
                                                                          DOUBLE_80333988) +
                                                                 DOUBLE_80333980) + DOUBLE_80333978)
                                               + DOUBLE_80333970) + DOUBLE_80333968)) /
                            (dVar2 * (dVar2 * (dVar2 * (DOUBLE_803339b8 * dVar2 + DOUBLE_803339b0) +
                                              DOUBLE_803339a8) + DOUBLE_803339a0) + DOUBLE_80333998)
                            ) - DOUBLE_80333960));
      }
    }
    else if ((longlong)param_1 < 0) {
      dVar3 = DOUBLE_803339c0 * (DOUBLE_80333998 + param_1);
      dVar2 = (double)sqrt(dVar3);
      dVar2 = -(DOUBLE_803339c8 *
                (dVar2 + (((dVar3 * (dVar3 * (dVar3 * (dVar3 * (dVar3 * (DOUBLE_80333990 * dVar3 +
                                                                        DOUBLE_80333988) +
                                                               DOUBLE_80333980) + DOUBLE_80333978) +
                                             DOUBLE_80333970) + DOUBLE_80333968)) /
                          (dVar3 * (dVar3 * (dVar3 * (DOUBLE_803339b8 * dVar3 + DOUBLE_803339b0) +
                                            DOUBLE_803339a8) + DOUBLE_803339a0) + DOUBLE_80333998))
                          * dVar2 - DOUBLE_80333960)) - DOUBLE_80333950);
    }
    else {
      dVar3 = DOUBLE_803339c0 * (DOUBLE_80333998 - param_1);
      dVar2 = (double)sqrt(dVar3);
      local_20 = (double)((ulonglong)dVar2 & 0xffffffff00000000);
      dVar2 = DOUBLE_803339c8 *
              (local_20 +
              ((dVar3 * (dVar3 * (dVar3 * (dVar3 * (dVar3 * (DOUBLE_80333990 * dVar3 +
                                                            DOUBLE_80333988) + DOUBLE_80333980) +
                                          DOUBLE_80333978) + DOUBLE_80333970) + DOUBLE_80333968)) /
              (dVar3 * (dVar3 * (dVar3 * (DOUBLE_803339b8 * dVar3 + DOUBLE_803339b0) +
                                DOUBLE_803339a8) + DOUBLE_803339a0) + DOUBLE_80333998)) * dVar2 +
              -(local_20 * local_20 - dVar3) / (dVar2 + local_20));
    }
  }
  else {
    iStack_24 = SUB84(param_1,0);
    if (uVar1 == 0x3ff00000 && iStack_24 == 0) {
      dVar2 = DOUBLE_80333950;
      if (0 < (int)local_28) {
        dVar2 = DOUBLE_80333948;
      }
    }
    else {
      dVar2 = (double)DAT_8032ec20;
    }
  }
  return dVar2;
}

