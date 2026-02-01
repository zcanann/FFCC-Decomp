// Function: brush__FPUsiiffi8_GXColorP8_GXColorP8_GXColor
// Entry: 800e2174
// Size: 1140 bytes

/* WARNING: Removing unreachable block (ram,0x800e25cc) */
/* WARNING: Removing unreachable block (ram,0x800e25c4) */
/* WARNING: Removing unreachable block (ram,0x800e218c) */
/* WARNING: Removing unreachable block (ram,0x800e2184) */

void brush__FPUsiiffi8_GXColorP8_GXColorP8_GXColor
               (double param_1,double param_2,int param_3,uint param_4,uint param_5,int param_6,
               byte *param_7,undefined *param_8,undefined *param_9)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  double dVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  undefined auStack_e8 [4];
  undefined4 local_e4;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  undefined auStack_d8 [4];
  undefined4 local_d4;
  undefined4 local_d0;
  uint uStack_cc;
  undefined8 local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  undefined8 local_b8;
  longlong local_b0;
  undefined4 local_a8;
  uint uStack_a4;
  undefined4 local_a0;
  uint uStack_9c;
  longlong local_98;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  longlong local_80;
  int local_78;
  int local_74;
  
  puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_d8,0xf,0xf,0xf,0);
  dVar7 = DOUBLE_80331100;
  uVar8 = *puVar10;
  uStack_cc = param_4 ^ 0x80000000;
  uStack_bc = param_5 ^ 0x80000000;
  local_d4._0_1_ = (undefined)((uint)uVar8 >> 0x18);
  local_d4._1_1_ = (undefined)((uint)uVar8 >> 0x10);
  *param_9 = local_d4._0_1_;
  param_9[1] = local_d4._1_1_;
  local_74 = param_4 * param_5 * 2;
  local_d4._2_1_ = (undefined)((uint)uVar8 >> 8);
  local_d4._3_1_ = (undefined)uVar8;
  param_9[2] = local_d4._2_1_;
  param_9[3] = (undefined)local_d4;
  local_d0 = 0x43300000;
  *param_8 = *param_9;
  local_c0 = 0x43300000;
  iVar1 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_cc) - dVar7) * param_1);
  local_c8 = (double)(longlong)iVar1;
  param_8[1] = param_9[1];
  param_8[2] = param_9[2];
  local_78 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_bc) - dVar7) * param_2);
  local_b8 = (double)(longlong)local_78;
  param_8[3] = param_9[3];
  local_d4 = uVar8;
  DCInvalidateRange(param_3,local_74);
  uVar15 = 0xfffffffe;
  do {
    uVar14 = 0xfffffffe;
    uVar18 = local_78 + uVar15;
    do {
      uVar11 = iVar1 + uVar14;
      if ((((-1 < (int)uVar11) && ((int)uVar11 < (int)param_4)) && (-1 < (int)uVar18)) &&
         ((int)uVar18 < (int)param_5)) {
        iVar3 = (int)uVar18 >> 0x1f;
        iVar6 = (int)uVar11 >> 0x1f;
        uVar13 = (((int)uVar14 >> 0x1f ^ uVar14) - ((int)uVar14 >> 0x1f)) +
                 (((int)uVar15 >> 0x1f ^ uVar15) - ((int)uVar15 >> 0x1f));
        iVar3 = (((iVar6 * 4 | uVar11 * 0x40000000 + iVar6 >> 0x1e) - iVar6) +
                ((iVar3 * 4 | uVar18 * 0x40000000 + iVar3 >> 0x1e) - iVar3) * 4 +
                (((int)uVar11 >> 2) + (uint)((int)uVar11 < 0 && (uVar11 & 3) != 0)) * 0x10 +
                (((int)uVar18 >> 2) + (uint)((int)uVar18 < 0 && (uVar18 & 3) != 0)) * param_4 * 4) *
                2;
        uVar2 = *(ushort *)(param_3 + iVar3);
        uVar17 = uVar2 & 0xf;
        uVar16 = uVar2 >> 4 & 0xf;
        uVar11 = uVar2 >> 8 & 0xf;
        uVar12 = uVar2 >> 0xc & 7;
        if (uVar13 == 0) {
          puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e0,uVar11,uVar16,uVar17,uVar12);
          uVar8 = *puVar10;
          local_dc._0_1_ = (undefined)((uint)uVar8 >> 0x18);
          local_dc._1_1_ = (undefined)((uint)uVar8 >> 0x10);
          *param_8 = local_dc._0_1_;
          local_dc._2_1_ = (undefined)((uint)uVar8 >> 8);
          param_8[1] = local_dc._1_1_;
          local_dc._3_1_ = (undefined)uVar8;
          param_8[2] = local_dc._2_1_;
          param_8[3] = (undefined)local_dc;
          local_dc = uVar8;
        }
        if (param_6 == 0) {
          local_c0 = 0x43300000;
          uStack_bc = 7 - param_7[3] ^ 0x80000000;
          local_b8 = (double)CONCAT44(0x43300000,
                                      ((int)uVar13 >> 2) +
                                      (uint)((int)uVar13 < 0 && (uVar13 & 3) != 0) ^ 0x80000000);
          fVar4 = (float)(local_b8 - DOUBLE_80331100) +
                  (float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80331100) / FLOAT_80331120
          ;
          fVar5 = FLOAT_80331138;
          if (fVar4 < FLOAT_80331138) {
            fVar5 = fVar4;
          }
          uStack_cc = (uint)*param_7;
          uStack_9c = (uint)param_7[1];
          uStack_a4 = uVar16 ^ 0x80000000;
          uStack_84 = (uint)param_7[2];
          uStack_8c = uVar17 ^ 0x80000000;
          local_d0 = 0x43300000;
          fVar4 = FLOAT_80331138 - fVar5;
          local_c8 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
          local_a0 = 0x43300000;
          local_88 = 0x43300000;
          uVar16 = (uint)((float)(local_c8 - DOUBLE_80331100) * fVar5 +
                         (float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80331128) * fVar4);
          local_b0 = (longlong)(int)uVar16;
          local_a8 = 0x43300000;
          local_90 = 0x43300000;
          uVar17 = (uint)((float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80331100) * fVar5
                         + (float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_80331128) * fVar4
                         );
          local_98 = (longlong)(int)uVar17;
          uVar9 = (uint)((float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331100) * fVar5 +
                        (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331128) * fVar4);
          local_80 = (longlong)(int)uVar9;
          if ((int)uVar16 < 0) {
            uVar11 = 0;
          }
          else {
            uVar11 = 0xf;
            if ((int)uVar16 < 0x10) {
              uVar11 = uVar16;
            }
          }
          if ((int)uVar17 < 0) {
            uVar16 = 0;
          }
          else {
            uVar16 = 0xf;
            if ((int)uVar17 < 0x10) {
              uVar16 = uVar17;
            }
          }
          if ((int)uVar9 < 0) {
            uVar17 = 0;
          }
          else {
            uVar17 = 0xf;
            if ((int)uVar9 < 0x10) {
              uVar17 = uVar9;
            }
          }
        }
        else {
          uVar9 = (uint)param_7[3] * (4 - uVar13);
          uVar12 = uVar12 - (((int)uVar9 >> 2) + (uint)((int)uVar9 < 0 && (uVar9 & 3) != 0));
          uVar12 = uVar12 & ~((int)uVar12 >> 0x1f);
        }
        *(ushort *)(param_3 + iVar3) =
             (ushort)uVar17 |
             (ushort)(uVar16 << 4) | (ushort)(uVar12 << 0xc) | (ushort)(uVar11 << 8);
        if (uVar13 == 0) {
          puVar10 = (undefined4 *)
                    __ct__6CColorFUcUcUcUc
                              (auStack_e8,uVar11 & 0xff,uVar16 & 0xff,uVar17 & 0xff,uVar12 & 0xff);
          uVar8 = *puVar10;
          local_e4._0_1_ = (undefined)((uint)uVar8 >> 0x18);
          local_e4._1_1_ = (undefined)((uint)uVar8 >> 0x10);
          *param_9 = local_e4._0_1_;
          local_e4._2_1_ = (undefined)((uint)uVar8 >> 8);
          param_9[1] = local_e4._1_1_;
          local_e4._3_1_ = (undefined)uVar8;
          param_9[2] = local_e4._2_1_;
          param_9[3] = (undefined)local_e4;
          local_e4 = uVar8;
        }
      }
      uVar14 = uVar14 + 1;
    } while ((int)uVar14 < 3);
    uVar15 = uVar15 + 1;
  } while ((int)uVar15 < 3);
  DCFlushRange(param_3,local_74);
  GXInvalidateTexAll();
  return;
}

