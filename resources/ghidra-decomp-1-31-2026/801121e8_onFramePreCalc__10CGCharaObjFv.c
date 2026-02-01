// Function: onFramePreCalc__10CGCharaObjFv
// Entry: 801121e8
// Size: 1072 bytes

/* WARNING: Removing unreachable block (ram,0x801125fc) */
/* WARNING: Removing unreachable block (ram,0x801121f8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFramePreCalc__10CGCharaObjFv(int param_1)

{
  float fVar1;
  undefined uVar2;
  uint uVar3;
  undefined2 uVar4;
  int iVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  
  if (Game.game.unk_flat3_0xc7d0 != 0) {
    PSVECSubtract((Vec *)(Game.game.unk_flat3_0xc7d0 + 0x15c),(Vec *)(param_1 + 0x15c),
                  (Vec *)(param_1 + 0x5c0));
    dVar13 = (double)PSVECMag((Vec *)(param_1 + 0x5c0));
    *(float *)(param_1 + 0x5bc) = (float)dVar13;
    dVar13 = (double)GetRotateY__7CVectorFv((CVector *)(param_1 + 0x5c0));
    *(float *)(param_1 + 0x5cc) = (float)dVar13;
  }
  dVar13 = (double)FLOAT_80331988;
  iVar10 = -0x7fde1140;
  iVar7 = 0;
  iVar8 = param_1;
  iVar9 = param_1;
  do {
    fVar1 = FLOAT_80331988;
    if (*(int *)(iVar10 + 0xc5b0) == 0) {
      *(float *)(iVar8 + 0x5d0) = FLOAT_80331988;
      *(float *)(iVar9 + 0x5e8) = fVar1;
      *(float *)(iVar9 + 0x5e4) = fVar1;
      *(float *)(iVar9 + 0x5e0) = fVar1;
      *(float *)(iVar8 + 0x610) = fVar1;
    }
    else {
      PSVECSubtract((Vec *)(*(int *)(iVar10 + 0xc5b0) + 0x15c),(Vec *)(param_1 + 0x15c),
                    (Vec *)(iVar9 + 0x5e0));
      dVar14 = (double)PSVECMag((Vec *)(iVar9 + 0x5e0));
      *(float *)(iVar8 + 0x5d0) = (float)dVar14;
      dVar14 = (double)GetRotateY__7CVectorFv((CVector *)(iVar9 + 0x5e0));
      *(float *)(iVar8 + 0x610) = (float)dVar14;
    }
    *(undefined4 *)(iVar8 + 0x620) = 0;
    iVar5 = param_1;
    iVar12 = iVar7;
    if (0 < iVar7) {
      do {
        if (dVar13 == (double)*(float *)(iVar8 + 0x5d0)) {
          *(int *)(iVar8 + 0x620) = *(int *)(iVar8 + 0x620) + 1;
        }
        else if (dVar13 == (double)*(float *)(iVar5 + 0x5d0)) {
          *(int *)(iVar5 + 0x620) = *(int *)(iVar5 + 0x620) + 1;
        }
        else if ((double)*(float *)(iVar5 + 0x5d0) <= (double)*(float *)(iVar8 + 0x5d0)) {
          *(int *)(iVar8 + 0x620) = *(int *)(iVar8 + 0x620) + 1;
        }
        else {
          *(int *)(iVar5 + 0x620) = *(int *)(iVar5 + 0x620) + 1;
        }
        iVar5 = iVar5 + 4;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    iVar7 = iVar7 + 1;
    iVar9 = iVar9 + 0xc;
    iVar8 = iVar8 + 4;
    iVar10 = iVar10 + 4;
  } while (iVar7 < 4);
  *(float *)(param_1 + 0x690) = FLOAT_80331964;
  if (*(short *)(*(int *)(param_1 + 0x58) + 0x4e) != 0) {
    *(float *)(param_1 + 0x690) =
         *(float *)(param_1 + 0x690) *
         (FLOAT_80331984 *
          (float)((double)CONCAT44(0x43300000,
                                   (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x34)) -
                 DOUBLE_80331978) + FLOAT_80331980);
  }
  if (*(short *)(*(int *)(param_1 + 0x58) + 0x4c) != 0) {
    *(float *)(param_1 + 0x690) =
         *(float *)(param_1 + 0x690) *
         (FLOAT_80331984 *
          (float)((double)CONCAT44(0x43300000,
                                   (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x36)) -
                 DOUBLE_80331978) + FLOAT_80331980);
  }
  if (*(short *)(*(int *)(param_1 + 0x58) + 0x40) != 0) {
    *(float *)(param_1 + 0x690) =
         *(float *)(param_1 + 0x690) *
         (FLOAT_80331984 *
          (float)((double)CONCAT44(0x43300000,
                                   (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x40)) -
                 DOUBLE_80331978) + FLOAT_80331980);
  }
  fVar1 = FLOAT_803319b8;
  if (*(float *)(param_1 + 0x690) < FLOAT_803319b8) {
    fVar1 = *(float *)(param_1 + 0x690);
  }
  *(float *)(param_1 + 0x690) = fVar1;
  uVar11 = 0;
  switch(*(undefined4 *)(param_1 + 0x520)) {
  case 1:
  case 2:
  case 4:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x12:
  case 0x13:
  case 0x16:
  case 0x17:
  case 0x19:
  case 0x1b:
  case 0x22:
    uVar11 = 0x19;
  }
  iVar8 = *(int *)(param_1 + 0x58);
  if (((*(short *)(iVar8 + 0x3e) != 0) || (*(short *)(iVar8 + 0x50) != 0)) ||
     (*(short *)(iVar8 + 0x44) != 0)) {
    uVar11 = uVar11 + 0x19;
  }
  uVar3 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
  if ((uVar3 & 0x6d) == 0x6d) {
    if (*(int *)(param_1 + 0x6f0) != 0) {
      uVar11 = uVar11 + 10;
    }
    bVar6 = false;
    uVar3 = (uint)*(char *)(param_1 + 0xe2);
    if ((Pad._452_4_ != 0) || ((uVar3 == 0 && (Pad._448_4_ != -1)))) {
      bVar6 = true;
    }
    if (bVar6) {
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)(&Pad.field_0x54 +
                      (uVar3 & ~((int)~(Pad._448_4_ - uVar3 | uVar3 - Pad._448_4_) >> 0x1f)) * 0x54)
      ;
    }
    if (iVar8 != 0) {
      uVar11 = uVar11 + 0x19;
    }
    if (-1 < (int)((uint)*(byte *)(param_1 + 0x9b) << 0x18)) {
      uVar11 = uVar11 + 0x19;
    }
  }
  uVar2 = 0x19;
  if (uVar11 < 0x19) {
    uVar2 = (undefined)uVar11;
  }
  *(undefined *)(param_1 + 0xe7) = uVar2;
  uVar11 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
  if (((uVar11 & 0xad) == 0xad) && (*(int *)(param_1 + 0x6d8) == 4)) {
    *(undefined *)(param_1 + 0xe7) = 100;
  }
  if ((DbgMenuPcs._10844_4_ & 1) == 0) {
    *(ushort *)(param_1 + 0x6a4) = (ushort)*(byte *)(param_1 + 0xe8);
  }
  else {
    uVar4 = calcSpecialPolygonGroup__6CAStarFP3Vec
                      ((CAStar *)&DbgMenuPcs.field_0x2a5c,param_1 + 0x15c);
    *(undefined2 *)(param_1 + 0x6a4) = uVar4;
  }
  return;
}

