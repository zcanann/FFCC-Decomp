// Function: calc__10CCameraPcsFv
// Entry: 800394d0
// Size: 1708 bytes

/* WARNING: Removing unreachable block (ram,0x80039b5c) */
/* WARNING: Removing unreachable block (ram,0x80039b54) */
/* WARNING: Removing unreachable block (ram,0x80039b4c) */
/* WARNING: Removing unreachable block (ram,0x80039b44) */
/* WARNING: Removing unreachable block (ram,0x80039b3c) */
/* WARNING: Removing unreachable block (ram,0x80039500) */
/* WARNING: Removing unreachable block (ram,0x800394f8) */
/* WARNING: Removing unreachable block (ram,0x800394f0) */
/* WARNING: Removing unreachable block (ram,0x800394e8) */
/* WARNING: Removing unreachable block (ram,0x800394e0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  ushort uVar6;
  uint uVar5;
  bool bVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  float local_138;
  float local_134;
  float local_130;
  Mtx MStack_12c;
  Mtx MStack_fc;
  Mtx MStack_cc;
  Mtx MStack_9c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  bVar7 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar7 = true;
  }
  if (bVar7) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._54_2_;
  }
  if ((uVar6 & 0x20) != 0) {
    uVar5 = countLeadingZeros(*(undefined4 *)(param_1 + 0x444));
    *(uint *)(param_1 + 0x444) = uVar5 >> 5 & 0xff;
  }
  fVar4 = FLOAT_8032fabc;
  fVar1 = FLOAT_8032fa70;
  if (*(int *)(param_1 + 0x444) == 0) {
    bVar7 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar2 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar2 = (float)Pad._44_4_;
    }
    bVar7 = false;
    *(float *)(param_1 + 0xf8) =
         FLOAT_8032fa70 * FLOAT_8032fa8c * fVar2 + *(float *)(param_1 + 0xf8);
    fVar2 = FLOAT_8032fabc;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar3 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar3 = (float)Pad._48_4_;
    }
    bVar7 = false;
    *(float *)(param_1 + 0x440) = fVar1 * fVar4 * fVar3 + *(float *)(param_1 + 0x440);
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar1 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar1 = (float)Pad._36_4_;
    }
    bVar7 = false;
    *(float *)(param_1 + 0x43c) = fVar2 * fVar1 + *(float *)(param_1 + 0x43c);
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar1 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar1 = (float)Pad._28_4_;
    }
    bVar7 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar4 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar4 = (float)Pad._32_4_;
    }
    dVar11 = (double)*(float *)(param_1 + 0x440);
    dVar10 = -(double)(FLOAT_8032fabc * fVar4 - FLOAT_8032fabc * fVar1);
    dVar9 = (double)*(float *)(param_1 + 0xf8);
    dVar8 = (double)cos(dVar11);
    dVar12 = (double)(float)dVar8;
    dVar8 = (double)sin(dVar9);
    dVar12 = (double)(float)((double)(float)dVar8 * dVar12);
    dVar8 = (double)sin(dVar11);
    dVar13 = (double)(float)dVar8;
    dVar8 = (double)cos(dVar11);
    dVar11 = (double)(float)dVar8;
    dVar8 = (double)cos(dVar9);
    bVar7 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar7 = true;
    }
    fVar1 = FLOAT_8032fa34;
    if (!bVar7) {
      countLeadingZeros(Pad._448_4_);
      fVar1 = (float)Pad._40_4_;
    }
    dVar9 = (double)(FLOAT_8032fa8c * fVar1);
    *(float *)(param_1 + 0xd4) = (float)(dVar12 * dVar9 + (double)*(float *)(param_1 + 0xd4));
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) + (float)(dVar13 * dVar9 + dVar10);
    *(float *)(param_1 + 0xdc) =
         -(float)((double)(float)((double)(float)dVar8 * dVar11) * dVar9 -
                 (double)*(float *)(param_1 + 0xdc));
    *(float *)(param_1 + 0xe0) =
         (float)((double)*(float *)(param_1 + 0x43c) * dVar12 + (double)*(float *)(param_1 + 0xd4));
    *(float *)(param_1 + 0xe4) =
         (float)((double)*(float *)(param_1 + 0x43c) * dVar13 + (double)*(float *)(param_1 + 0xd8));
    *(float *)(param_1 + 0xe8) =
         -(float)((double)*(float *)(param_1 + 0x43c) *
                  (double)(float)((double)(float)dVar8 * dVar11) -
                 (double)*(float *)(param_1 + 0xdc));
  }
  else {
    dVar8 = (double)atan2((double)(*(float *)(param_1 + 0xe0) - *(float *)(param_1 + 0xd4)),
                          (double)(*(float *)(param_1 + 0xdc) - *(float *)(param_1 + 0xe8)));
    *(float *)(param_1 + 0xf8) = (float)dVar8;
  }
  CalcQuake__10CCameraPcsFv(param_1);
  fVar1 = *(float *)(param_1 + 0xfc);
  if ((*(float *)(param_1 + 0xfc) < FLOAT_8032fac8) &&
     (fVar1 = FLOAT_8032fab4, System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801d7928);
    fVar1 = FLOAT_8032fab4;
  }
  C_MTXPerspective(fVar1,FLOAT_8032fa3c,*(float *)(param_1 + 0x100),*(float *)(param_1 + 0x104),
                   (Mtx *)(param_1 + 0x94));
  GXSetProjection(param_1 + 0x94,0);
  local_138 = FLOAT_8032fa34;
  local_134 = FLOAT_8032fa1c;
  local_130 = FLOAT_8032fa34;
  PSVECDistance((Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xd4));
  C_MTXLookAt((Mtx *)(param_1 + 4),(Vec *)(param_1 + 0xe0),&local_138,(Vec *)(param_1 + 0xd4));
  if (Game.game.m_currentMapId == 0x21) {
    PSMTXCopy((Mtx *)(param_1 + 0x34),&MStack_12c);
    if ((*(short *)(param_1 + 0x47e) != 0) && (*(short *)(param_1 + 0x480) != 0)) {
      uStack_64 = (int)*(short *)(param_1 + 0x480) ^ 0x80000000;
      uStack_5c = (int)*(short *)(param_1 + 0x47e) ^ 0x80000000;
      local_68 = 0x43300000;
      local_60 = 0x43300000;
      dVar8 = (double)cos((double)(FLOAT_8032fa18 *
                                  (FLOAT_8032fa1c -
                                  (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8032fa28)
                                  / (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_8032fa28
                                           ))));
      dVar8 = (double)(FLOAT_8032fa20 * (FLOAT_8032fa1c + (float)dVar8));
      PSMTXRotRad((float)((double)*(float *)(param_1 + 0x484) * dVar8),&MStack_fc,0x78);
      PSMTXConcat(&MStack_fc,&MStack_12c,&MStack_12c);
      PSMTXRotRad((float)((double)*(float *)(param_1 + 0x488) * dVar8),&MStack_fc,0x79);
      PSMTXConcat(&MStack_fc,&MStack_12c,&MStack_12c);
      fVar1 = -(float)((double)*(float *)(param_1 + 0x48c) *
                       (double)(float)((double)FLOAT_8032fa1c - dVar8) -
                      (double)(float)((double)FLOAT_8032fa1c + (double)*(float *)(param_1 + 0x48c)))
      ;
      PSMTXScale(fVar1,fVar1,fVar1,&MStack_fc);
      PSMTXConcat(&MStack_fc,&MStack_12c,&MStack_12c);
      if (-1 < (int)((uint)*(byte *)(param_1 + 0x47c) << 0x18)) {
        *(short *)(param_1 + 0x480) = *(short *)(param_1 + 0x480) + -1;
      }
    }
    PSMTXConcat((Mtx *)(param_1 + 4),&MStack_12c,(Mtx *)(param_1 + 4));
  }
  PSMTXRotRad(*(float *)(param_1 + 0x108),&MStack_9c,0x7a);
  PSMTXConcat(&MStack_9c,(Mtx *)(param_1 + 4),(Mtx *)(param_1 + 4));
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_cc);
  fVar4 = FLOAT_8032fa38;
  fVar1 = FLOAT_8032fa34;
  *(float *)(param_1 + 0xec) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar1;
  *(float *)(param_1 + 0xf4) = fVar4;
  PSMTXMultVecSR(&MStack_cc,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  *(undefined4 *)(param_1 + 0x438) = 0;
  return;
}

