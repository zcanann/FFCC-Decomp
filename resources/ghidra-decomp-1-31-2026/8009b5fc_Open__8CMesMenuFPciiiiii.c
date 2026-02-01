// Function: Open__8CMesMenuFPciiiiii
// Entry: 8009b5fc
// Size: 744 bytes

void Open__8CMesMenuFPciiiiii
               (int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5,
               undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  double dVar4;
  
  fVar1 = FLOAT_803308d8;
  *(float *)(param_1 + 0x3d78) = FLOAT_803308d8;
  *(float *)(param_1 + 0x3d74) = fVar1;
  *(undefined4 *)(param_1 + 8) = 1;
  *(undefined4 *)(param_1 + 0x3da4) = 0;
  *(uint *)(param_1 + 0x3d8c) = param_5;
  dVar4 = DOUBLE_80330900;
  fVar1 = FLOAT_803308dc;
  if (*(int *)(param_1 + 0x18) < 4) {
    SetFade__9CRingMenuFi(*(undefined4 *)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4),0);
    fVar1 = FLOAT_803308e4;
    *(float *)(param_1 + 0x3d9c) = FLOAT_803308e0;
    *(float *)(param_1 + 0x3da0) = fVar1;
  }
  else {
    uVar2 = countLeadingZeros(param_5 & 2);
    *(float *)(param_1 + 0x3d6c) =
         (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80330900);
    *(float *)(param_1 + 0x3d70) =
         (float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - dVar4);
    *(undefined4 *)(param_1 + 0x3d88) = 1;
    *(float *)(param_1 + 0x3d9c) = fVar1;
    *(float *)(param_1 + 0x3da0) = fVar1;
    *(uint *)(param_1 + 0x3d50) = -(param_5 >> 1 & 1) & 0x1c;
    *(uint *)(param_1 + 0x3d54) = uVar2 >> 5;
  }
  *(undefined4 *)(param_1 + 0x3d90) = param_6;
  *(undefined4 *)(param_1 + 0x3d94) = param_7;
  *(undefined4 *)(param_1 + 0x3d98) = param_8;
  Set__4CMesFPci(param_1 + 0x1c,param_2,param_5 & 0x20);
  fVar1 = FLOAT_803308e8;
  *(float *)(param_1 + 0x3d7c) =
       FLOAT_803308e8 * *(float *)(param_1 + 0x3d9c) + *(float *)(param_1 + 0x3cc0);
  *(float *)(param_1 + 0x3d80) = fVar1 * *(float *)(param_1 + 0x3da0) + *(float *)(param_1 + 0x3cc4)
  ;
  fVar1 = FLOAT_803308ec;
  if (*(int *)(param_1 + 0x18) < 4) {
    if ((param_5 & 0x100) == 0) {
      fVar1 = *(float *)(param_1 + 0x3d7c);
      if (fVar1 < FLOAT_803308f0) {
        fVar1 = FLOAT_803308f0;
      }
      *(float *)(param_1 + 0x3d7c) = fVar1;
    }
  }
  else if ((param_5 & 8) == 0) {
    if ((param_5 & 0x8000) != 0) {
      *(float *)(param_1 + 0x3d6c) = *(float *)(param_1 + 0x3d6c) - *(float *)(param_1 + 0x3d7c);
    }
  }
  else {
    *(float *)(param_1 + 0x3d6c) =
         -(FLOAT_803308ec * *(float *)(param_1 + 0x3d7c) - *(float *)(param_1 + 0x3d6c));
    *(float *)(param_1 + 0x3d70) =
         -(fVar1 * *(float *)(param_1 + 0x3d80) - *(float *)(param_1 + 0x3d70));
  }
  uVar2 = *(uint *)(param_1 + 0x18);
  if ((int)uVar2 < 4) {
    if ((uVar2 & 2) == 0) {
      dVar4 = (double)(FLOAT_803308f8 +
                      *(float *)(param_1 + 0x3da0) +
                      *(float *)(param_1 + 0x3d70) + *(float *)(param_1 + 0x3d78));
    }
    else {
      dVar4 = (double)((*(float *)(param_1 + 0x3da0) +
                       (*(float *)(param_1 + 0x3d70) - FLOAT_803308f4) +
                       *(float *)(param_1 + 0x3d78)) - *(float *)(param_1 + 0x3d80));
    }
  }
  else {
    dVar4 = (double)(*(float *)(param_1 + 0x3da0) +
                    *(float *)(param_1 + 0x3d70) + *(float *)(param_1 + 0x3d78));
  }
  bVar3 = false;
  if (((int)uVar2 < 4) && ((uVar2 & 1) != 0)) {
    bVar3 = true;
  }
  if (bVar3) {
    fVar1 = (*(float *)(param_1 + 0x3d9c) +
            *(float *)(param_1 + 0x3d6c) + *(float *)(param_1 + 0x3d74)) -
            *(float *)(param_1 + 0x3d7c);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x3d9c) +
            *(float *)(param_1 + 0x3d6c) + *(float *)(param_1 + 0x3d74);
  }
  SetPosition__4CMesFff((double)fVar1,dVar4,param_1 + 0x1c);
  *(uint *)(param_1 + 0xc) = param_5 >> 4 & 1;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 8;
  if (((param_5 & 0x11) == 0) && ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0)) {
    PlaySe__6CSoundFiiii(&Sound,5,0x40,0x7f,0);
  }
  return;
}

