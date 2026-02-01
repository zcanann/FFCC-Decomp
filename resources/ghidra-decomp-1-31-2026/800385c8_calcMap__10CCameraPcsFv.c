// Function: calcMap__10CCameraPcsFv
// Entry: 800385c8
// Size: 1360 bytes

/* WARNING: Removing unreachable block (ram,0x80038af0) */
/* WARNING: Removing unreachable block (ram,0x80038ae8) */
/* WARNING: Removing unreachable block (ram,0x80038ae0) */
/* WARNING: Removing unreachable block (ram,0x800385e8) */
/* WARNING: Removing unreachable block (ram,0x800385e0) */
/* WARNING: Removing unreachable block (ram,0x800385d8) */

void calcMap__10CCameraPcsFv(int param_1)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  ushort uVar6;
  int iVar5;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  Vec local_168;
  Vec local_15c;
  Vec local_150;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  Mtx MStack_104;
  Mtx MStack_d4;
  Mtx MStack_a4;
  Mtx MStack_74;
  
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._4_2_;
  }
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  fVar2 = FLOAT_8032fa34;
  if (!bVar1) {
    countLeadingZeros(Pad._448_4_);
    fVar2 = (float)Pad._44_4_;
  }
  bVar1 = false;
  fVar2 = FLOAT_8032fa70 * (fVar2 / FLOAT_8032fa40);
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  fVar3 = FLOAT_8032fa34;
  if (!bVar1) {
    countLeadingZeros(Pad._448_4_);
    fVar3 = (float)Pad._48_4_;
  }
  bVar1 = false;
  fVar3 = FLOAT_8032fa70 * (fVar3 / FLOAT_8032fa40);
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  fVar4 = FLOAT_8032fa34;
  if (!bVar1) {
    countLeadingZeros(Pad._448_4_);
    fVar4 = (float)Pad._36_4_;
  }
  *(float *)(param_1 + 0xfc) = *(float *)(param_1 + 0xfc) + fVar4;
  *(float *)(param_1 + 0x470) = *(float *)(param_1 + 0x470) + -fVar3;
  *(float *)(param_1 + 0x474) = *(float *)(param_1 + 0x474) - fVar2;
  PSMTXRotRad(*(float *)(param_1 + 0x470),&MStack_a4,0x78);
  PSMTXRotRad(*(float *)(param_1 + 0x474),&MStack_74,0x79);
  PSMTXConcat(&MStack_74,&MStack_a4,&MStack_d4);
  fVar3 = FLOAT_8032fa34;
  fVar2 = FLOAT_8032fa1c;
  *(float *)(param_1 + 0xf4) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar3;
  *(float *)(param_1 + 0xec) = fVar3;
  *(float *)(param_1 + 0xf4) = fVar2;
  PSMTXMultVecSR(&MStack_d4,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  local_150.z = FLOAT_8032fa34;
  local_150.y = FLOAT_8032fa34;
  local_150.x = FLOAT_8032fa34;
  if ((uVar6 & 0x100) != 0) {
    PSVECScale(FLOAT_8032fa74,(Vec *)(param_1 + 0xec),&local_150);
  }
  local_150.y = FLOAT_8032fa34;
  if ((uVar6 & 0x800) != 0) {
    PSVECScale(FLOAT_8032faac,(Vec *)(param_1 + 0xec),&local_150);
    local_150.y = FLOAT_8032fa34;
  }
  FLOAT_8032fa34 = local_150.y;
  if ((uVar6 & 8) == 0) {
    if ((uVar6 & 4) != 0) {
      local_150.y = local_150.y - FLOAT_8032fa74;
    }
  }
  else {
    local_150.y = local_150.y + FLOAT_8032fa74;
  }
  if ((uVar6 & 1) == 0) {
    if ((uVar6 & 2) != 0) {
      local_15c.z = FLOAT_8032fa34;
      local_15c.y = FLOAT_8032fa34;
      local_15c.x = FLOAT_8032faac;
      PSMTXMultVecSR(&MStack_d4,&local_15c,&local_15c);
      local_15c.y = FLOAT_8032fa34;
      PSVECAdd(&local_15c,&local_150,&local_150);
    }
  }
  else {
    local_15c.z = FLOAT_8032fa34;
    local_15c.y = FLOAT_8032fa34;
    local_15c.x = FLOAT_8032fa74;
    PSMTXMultVecSR(&MStack_d4,&local_15c,&local_15c);
    local_15c.y = FLOAT_8032fa34;
    PSVECAdd(&local_15c,&local_150,&local_150);
  }
  if (((FLOAT_8032fa34 != local_150.x) || (FLOAT_8032fa34 != local_150.y)) ||
     (FLOAT_8032fa34 != local_150.z)) {
    iVar7 = 4;
    dVar8 = (double)FLOAT_8032fa78;
    dVar9 = (double)FLOAT_8032fa7c;
    dVar10 = (double)FLOAT_8032fa8c;
    while (bVar1 = iVar7 != 0, iVar7 = iVar7 + -1, bVar1) {
      local_114 = (float)dVar8;
      local_118 = (float)dVar8;
      local_11c = (float)dVar8;
      local_108 = (float)dVar9;
      local_10c = (float)dVar9;
      local_110 = (float)dVar9;
      local_144 = *(undefined4 *)(param_1 + 0xe0);
      local_140 = *(undefined4 *)(param_1 + 0xe4);
      local_13c = *(undefined4 *)(param_1 + 0xe8);
      local_12c = local_150.x;
      local_128 = local_150.y;
      local_124 = local_150.z;
      local_120 = (float)dVar10;
      iVar5 = CheckHitCylinder__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_144,&local_150,0xffffffff);
      if (iVar5 == 0) {
        *(float *)(param_1 + 0xe0) = *(float *)(param_1 + 0xe0) + local_150.x;
        *(float *)(param_1 + 0xe4) = *(float *)(param_1 + 0xe4) + local_150.y;
        *(float *)(param_1 + 0xe8) = *(float *)(param_1 + 0xe8) + local_150.z;
        break;
      }
      CalcHitSlide__7CMapObjFP3Vecf((CMapObj *)MapMng._141944_4_,&local_150);
    }
  }
  C_MTXPerspective(*(float *)(param_1 + 0xfc),FLOAT_8032fa3c,*(float *)(param_1 + 0x100),
                   *(float *)(param_1 + 0x104),(Mtx *)(param_1 + 0x94));
  GXSetProjection(param_1 + 0x94,0);
  PSVECAdd((Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xd4));
  local_168.x = FLOAT_8032fa34;
  local_168.y = FLOAT_8032fa1c;
  local_168.z = FLOAT_8032fa34;
  PSMTXMultVecSR(&MStack_d4,&local_168,&local_168);
  C_MTXLookAt((Mtx *)(param_1 + 4),(Vec *)(param_1 + 0xe0),&local_168,(Vec *)(param_1 + 0xd4));
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_104);
  fVar3 = FLOAT_8032fa38;
  fVar2 = FLOAT_8032fa34;
  *(float *)(param_1 + 0xec) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar2;
  *(float *)(param_1 + 0xf4) = fVar3;
  PSMTXMultVecSR(&MStack_104,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  return;
}

