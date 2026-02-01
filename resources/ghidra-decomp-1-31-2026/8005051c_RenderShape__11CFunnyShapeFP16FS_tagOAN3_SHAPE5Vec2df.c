// Function: RenderShape__11CFunnyShapeFP16FS_tagOAN3_SHAPE5Vec2df
// Entry: 8005051c
// Size: 2820 bytes

/* WARNING: Removing unreachable block (ram,0x80051004) */
/* WARNING: Removing unreachable block (ram,0x80050ffc) */
/* WARNING: Removing unreachable block (ram,0x80050ff4) */
/* WARNING: Removing unreachable block (ram,0x80050fec) */
/* WARNING: Removing unreachable block (ram,0x80050fe4) */
/* WARNING: Removing unreachable block (ram,0x80050fdc) */
/* WARNING: Removing unreachable block (ram,0x80050fd4) */
/* WARNING: Removing unreachable block (ram,0x80050fcc) */
/* WARNING: Removing unreachable block (ram,0x80050fc4) */
/* WARNING: Removing unreachable block (ram,0x80050fbc) */
/* WARNING: Removing unreachable block (ram,0x80050fb4) */
/* WARNING: Removing unreachable block (ram,0x80050fac) */
/* WARNING: Removing unreachable block (ram,0x80050fa4) */
/* WARNING: Removing unreachable block (ram,0x80050f9c) */
/* WARNING: Removing unreachable block (ram,0x80050f94) */
/* WARNING: Removing unreachable block (ram,0x8005059c) */
/* WARNING: Removing unreachable block (ram,0x80050594) */
/* WARNING: Removing unreachable block (ram,0x8005058c) */
/* WARNING: Removing unreachable block (ram,0x80050584) */
/* WARNING: Removing unreachable block (ram,0x8005057c) */
/* WARNING: Removing unreachable block (ram,0x80050574) */
/* WARNING: Removing unreachable block (ram,0x8005056c) */
/* WARNING: Removing unreachable block (ram,0x80050564) */
/* WARNING: Removing unreachable block (ram,0x8005055c) */
/* WARNING: Removing unreachable block (ram,0x80050554) */
/* WARNING: Removing unreachable block (ram,0x8005054c) */
/* WARNING: Removing unreachable block (ram,0x80050544) */
/* WARNING: Removing unreachable block (ram,0x8005053c) */
/* WARNING: Removing unreachable block (ram,0x80050534) */
/* WARNING: Removing unreachable block (ram,0x8005052c) */

void RenderShape__11CFunnyShapeFP16FS_tagOAN3_SHAPE5Vec2df
               (double param_1,CFunnyShape *funnyShape,ushort *param_3,float *param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  undefined4 local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  undefined4 local_1b0;
  uint uStack_1ac;
  undefined4 local_1a8;
  uint uStack_1a4;
  undefined4 local_1a0;
  uint uStack_19c;
  undefined4 local_198;
  uint uStack_194;
  undefined4 local_190;
  uint uStack_18c;
  undefined4 local_188;
  uint uStack_184;
  undefined4 local_180;
  uint uStack_17c;
  undefined4 local_178;
  uint uStack_174;
  undefined4 local_170;
  uint uStack_16c;
  undefined4 local_168;
  uint uStack_164;
  undefined4 local_160;
  uint uStack_15c;
  undefined4 local_158;
  uint uStack_154;
  undefined4 local_150;
  uint uStack_14c;
  undefined4 local_148;
  uint uStack_144;
  undefined4 local_140;
  uint uStack_13c;
  undefined4 local_138;
  uint uStack_134;
  undefined4 local_130;
  uint uStack_12c;
  undefined4 local_128;
  uint uStack_124;
  undefined4 local_120;
  uint uStack_11c;
  undefined4 local_118;
  uint uStack_114;
  
  iVar9 = 0;
  iVar8 = 0;
  iVar7 = 0;
  while (iVar7 < (short)param_3[1]) {
    if ((*param_3 & 8) == 0) {
      uVar2 = (uint)*(byte *)((int)param_3 + iVar8 + 0x30);
      if ((int)uVar2 < (int)(char)funnyShape->field_0x60d4) {
        GXLoadTexObj(*(undefined4 *)(funnyShape->UnkBuffA + uVar2 * 4 + 0x14),0);
      }
      cVar1 = *(char *)((int)param_3 + iVar8 + 0x1c);
      if (cVar1 == 'H') {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,3);
      }
      else if (cVar1 == 'B') {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,4,1,3);
      }
      else if (cVar1 == -0x78) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,3);
      }
      uVar3 = (uint)*(short *)((int)param_3 + iVar8 + 0x20);
      uVar2 = (uint)*(short *)((int)param_3 + iVar8 + 0x24);
      uVar4 = (uint)*(short *)((int)param_3 + iVar8 + 0x22);
      iVar6 = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0);
      uVar3 = (uint)*(short *)((int)param_3 + iVar8 + 0x26);
      local_120 = 0x43300000;
      iVar5 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
      uStack_124 = iVar6 * 2 ^ 0x80000000;
      local_118 = 0x43300000;
      uStack_114 = ((((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0)) - iVar6) * 2
                   ^ 0x80000000;
      uStack_11c = ((((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0)) - iVar5) * 2
                   ^ 0x80000000;
      uStack_12c = iVar5 * 2 ^ 0x80000000;
      local_128 = 0x43300000;
      local_130 = 0x43300000;
      GXSetViewport((double)(*param_4 +
                            (float)((double)CONCAT44(0x43300000,uStack_124) - DOUBLE_8032fd88)),
                    (double)(param_4[1] +
                            (float)((double)CONCAT44(0x43300000,uStack_12c) - DOUBLE_8032fd88)),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_114) - DOUBLE_8032fd88),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_11c) - DOUBLE_8032fd88),
                    (double)FLOAT_8032fd6c,(double)FLOAT_8032fd74);
      uStack_13c = (int)*(short *)((int)param_3 + iVar8 + 0x2a) ^ 0x80000000;
      uStack_134 = (int)*(short *)((int)param_3 + iVar8 + 0x28) ^ 0x80000000;
      uStack_144 = (int)*(short *)((int)param_3 + iVar8 + 0x2c) ^ 0x80000000;
      uStack_14c = (int)*(short *)((int)param_3 + iVar8 + 0x2e) ^ 0x80000000;
      local_140 = 0x43300000;
      local_138 = 0x43300000;
      local_148 = 0x43300000;
      local_150 = 0x43300000;
      local_200 = FLOAT_8032fd74 -
                  (float)((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1e4 = FLOAT_8032fd80;
      local_204 = (float)((double)CONCAT44(0x43300000,uStack_134) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1e0 = FLOAT_8032fd74;
      local_1dc = FLOAT_8032fd6c;
      local_1d8 = FLOAT_8032fd74;
      local_1d4 = FLOAT_8032fd74;
      local_1d0 = FLOAT_8032fd6c;
      local_1cc = FLOAT_8032fd74;
      local_1fc = local_204 +
                  (float)((double)CONCAT44(0x43300000,uStack_144) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1c8 = FLOAT_8032fd80;
      local_1c4 = FLOAT_8032fd6c;
      local_1c0 = FLOAT_8032fd80;
      local_1bc = FLOAT_8032fd80;
      local_1f0 = local_200 -
                  (float)((double)CONCAT44(0x43300000,uStack_14c) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1b8 = FLOAT_8032fd6c;
      local_1f8 = local_200;
      local_1f4 = local_1fc;
      local_1ec = local_204;
      local_1e8 = local_1f0;
      memcpy(&local_208,(int)param_3 + iVar8 + 0x18,4);
      local_208 = *(undefined4 *)((int)param_3 + iVar8 + 0x18);
    }
    else {
      dVar24 = (double)FLOAT_8032fd64;
      dVar23 = (double)FLOAT_8032fd68;
      uVar2 = (uint)*(byte *)((int)param_3 + iVar9 + 0x38);
      dVar11 = dVar23;
      dVar12 = dVar24;
      if ((int)uVar2 < (int)(char)funnyShape->field_0x60d4) {
        GXLoadTexObj(*(undefined4 *)(funnyShape->UnkBuffA + uVar2 * 4 + 0x14),0);
      }
      cVar1 = *(char *)((int)param_3 + iVar9 + 0x1c);
      if (cVar1 == 'H') {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,3);
      }
      else if (cVar1 == 'B') {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,1,1,3);
      }
      else if (cVar1 == -0x78) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,3);
      }
      if ((*(uint *)funnyShape->UnkBuff3 & 0x100) == 0) {
        param_1 = (double)FLOAT_8032fd6c;
      }
      dVar10 = (double)sin(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)cos(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x20);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x22);
      local_1a8 = 0x43300000;
      uStack_1ac = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_1a4 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_1b0 = 0x43300000;
      dVar22 = (double)((float)((double)CONCAT44(0x43300000,uStack_1ac) - DOUBLE_8032fd88) *
                        (float)dVar10 -
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_1a4) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)cos(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)sin(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x20);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x22);
      local_198 = 0x43300000;
      uStack_19c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_194 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_1a0 = 0x43300000;
      dVar21 = (double)((float)((double)CONCAT44(0x43300000,uStack_19c) - DOUBLE_8032fd88) *
                        (float)dVar10 +
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_194) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)sin(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)cos(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x24);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x26);
      local_188 = 0x43300000;
      uStack_18c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_184 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_190 = 0x43300000;
      dVar20 = (double)((float)((double)CONCAT44(0x43300000,uStack_18c) - DOUBLE_8032fd88) *
                        (float)dVar10 -
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_184) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)cos(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)sin(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x24);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x26);
      local_178 = 0x43300000;
      uStack_17c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_174 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_180 = 0x43300000;
      dVar19 = (double)((float)((double)CONCAT44(0x43300000,uStack_17c) - DOUBLE_8032fd88) *
                        (float)dVar10 +
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_174) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)sin(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)cos(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x28);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x2a);
      local_168 = 0x43300000;
      uStack_16c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_164 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_170 = 0x43300000;
      dVar18 = (double)((float)((double)CONCAT44(0x43300000,uStack_16c) - DOUBLE_8032fd88) *
                        (float)dVar10 -
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_164) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)cos(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)sin(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x28);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x2a);
      local_158 = 0x43300000;
      uStack_15c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_154 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_160 = 0x43300000;
      dVar17 = (double)((float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_8032fd88) *
                        (float)dVar10 +
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_154) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)sin(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)cos(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x2c);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x2e);
      local_148 = 0x43300000;
      uStack_14c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_144 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_150 = 0x43300000;
      dVar16 = (double)((float)((double)CONCAT44(0x43300000,uStack_14c) - DOUBLE_8032fd88) *
                        (float)dVar10 -
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_144) -
                                              DOUBLE_8032fd88) * dVar13));
      dVar10 = (double)cos(param_1);
      dVar13 = (double)(float)dVar10;
      dVar10 = (double)sin(param_1);
      uVar3 = (uint)*(short *)((int)param_3 + iVar9 + 0x2c);
      uVar2 = (uint)*(short *)((int)param_3 + iVar9 + 0x2e);
      local_138 = 0x43300000;
      uStack_13c = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) ^ 0x80000000;
      uStack_134 = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0) ^ 0x80000000;
      local_140 = 0x43300000;
      dVar10 = (double)((float)((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_8032fd88) *
                        (float)dVar10 +
                       (float)((double)(float)((double)CONCAT44(0x43300000,uStack_134) -
                                              DOUBLE_8032fd88) * dVar13));
      if (dVar22 < dVar24) {
        dVar24 = dVar22;
      }
      if (dVar20 < dVar24) {
        dVar24 = dVar20;
      }
      if (dVar18 < dVar24) {
        dVar24 = dVar18;
      }
      if (dVar16 < dVar24) {
        dVar24 = dVar16;
      }
      if (dVar21 < (double)FLOAT_8032fd64) {
        dVar12 = dVar21;
      }
      if (dVar19 < dVar12) {
        dVar12 = dVar19;
      }
      if (dVar17 < dVar12) {
        dVar12 = dVar17;
      }
      if (dVar10 < dVar12) {
        dVar12 = dVar10;
      }
      if (dVar23 < dVar22) {
        dVar23 = dVar22;
      }
      if (dVar23 < dVar20) {
        dVar23 = dVar20;
      }
      if (dVar23 < dVar18) {
        dVar23 = dVar18;
      }
      if (dVar23 < dVar16) {
        dVar23 = dVar16;
      }
      if ((double)FLOAT_8032fd68 < dVar21) {
        dVar11 = dVar21;
      }
      if (dVar11 < dVar19) {
        dVar11 = dVar19;
      }
      if (dVar11 < dVar17) {
        dVar11 = dVar17;
      }
      if (dVar11 < dVar10) {
        dVar11 = dVar10;
      }
      dVar13 = (double)FLOAT_8032fd70;
      dVar15 = (double)(float)(dVar13 * (double)(float)(dVar23 - dVar24));
      dVar14 = (double)(float)(dVar13 * (double)(float)(dVar11 - dVar12));
      GXSetViewport((double)(float)(dVar24 * dVar13 + (double)*param_4),
                    (double)(float)(dVar12 * dVar13 + (double)param_4[1]),dVar15,dVar14,
                    (double)FLOAT_8032fd6c,(double)FLOAT_8032fd74);
      dVar24 = (double)FLOAT_8032fd7c;
      uStack_124 = (int)*(short *)((int)param_3 + iVar9 + 0x32) ^ 0x80000000;
      uStack_12c = (int)*(short *)((int)param_3 + iVar9 + 0x30) ^ 0x80000000;
      uStack_11c = (int)*(short *)((int)param_3 + iVar9 + 0x34) ^ 0x80000000;
      uStack_114 = (int)*(short *)((int)param_3 + iVar9 + 0x36) ^ 0x80000000;
      local_128 = 0x43300000;
      dVar13 = (double)(float)((double)(float)(dVar15 * dVar24) * dVar24);
      dVar12 = (double)FLOAT_8032fd74;
      dVar24 = (double)(float)((double)(float)(dVar14 * dVar24) * dVar24);
      local_130 = 0x43300000;
      dVar23 = (double)(float)(dVar23 - dVar13);
      local_120 = 0x43300000;
      dVar11 = (double)(float)(dVar11 - dVar24);
      local_118 = 0x43300000;
      local_1dc = FLOAT_8032fd6c;
      local_1d0 = FLOAT_8032fd6c;
      local_1c4 = FLOAT_8032fd6c;
      local_1fc = (float)((double)CONCAT44(0x43300000,uStack_12c) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1b8 = FLOAT_8032fd6c;
      local_1f0 = (float)(dVar12 - (double)((float)((double)CONCAT44(0x43300000,uStack_124) -
                                                   DOUBLE_8032fd88) / FLOAT_8032fd78));
      local_204 = local_1fc +
                  (float)((double)CONCAT44(0x43300000,uStack_11c) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_200 = local_1f0 -
                  (float)((double)CONCAT44(0x43300000,uStack_114) - DOUBLE_8032fd88) /
                  FLOAT_8032fd78;
      local_1bc = (float)(dVar12 / dVar24);
      local_1e0 = local_1bc * (float)(dVar21 - dVar11);
      local_1d4 = local_1bc * (float)(dVar19 - dVar11);
      local_1c8 = local_1bc * (float)(dVar10 - dVar11);
      local_1bc = local_1bc * (float)(dVar17 - dVar11);
      local_1c0 = -(float)(dVar12 / dVar13);
      local_1e4 = local_1c0 * (float)(dVar22 - dVar23);
      local_1d8 = local_1c0 * (float)(dVar20 - dVar23);
      local_1cc = local_1c0 * (float)(dVar16 - dVar23);
      local_1c0 = local_1c0 * (float)(dVar18 - dVar23);
      local_1f8 = local_200;
      local_1f4 = local_1fc;
      local_1ec = local_204;
      local_1e8 = local_1f0;
      memcpy(&local_208,(int)param_3 + iVar9 + 0x18,4);
      local_208 = *(undefined4 *)((int)param_3 + iVar9 + 0x18);
    }
    DCStoreRange(&local_208,4);
    GXBegin(0x80,0,4);
    iVar9 = iVar9 + 0x2c;
    iVar8 = iVar8 + 0x24;
    DAT_cc008000 = local_1e4;
    iVar7 = iVar7 + 1;
    DAT_cc008000 = local_1e0;
    DAT_cc008000 = local_1dc;
    DAT_cc008000 = local_208;
    DAT_cc008000 = local_204;
    DAT_cc008000 = local_200;
    DAT_cc008000 = local_1d8;
    DAT_cc008000 = local_1d4;
    DAT_cc008000 = local_1d0;
    DAT_cc008000 = local_208;
    DAT_cc008000 = local_1fc;
    DAT_cc008000 = local_1f8;
    DAT_cc008000 = local_1cc;
    DAT_cc008000 = local_1c8;
    DAT_cc008000 = local_1c4;
    DAT_cc008000 = local_208;
    DAT_cc008000 = local_1f4;
    DAT_cc008000 = local_1f0;
    DAT_cc008000 = local_1c0;
    DAT_cc008000 = local_1bc;
    DAT_cc008000 = local_1b8;
    DAT_cc008000 = local_208;
    DAT_cc008000 = local_1ec;
    DAT_cc008000 = local_1e8;
  }
  return;
}

