// Function: calcChara__10CCameraPcsFv
// Entry: 80038b68
// Size: 916 bytes

void calcChara__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  Vec *pVVar4;
  ushort uVar5;
  Vec local_e8;
  Vec local_dc;
  CVector CStack_d0;
  Vec local_c4;
  CVector aCStack_b8 [2];
  Mtx MStack_a0;
  Mtx MStack_70;
  Mtx MStack_40;
  
  C_MTXPerspective(*(float *)(param_1 + 0xfc),FLOAT_8032fa3c,*(float *)(param_1 + 0x100),
                   *(float *)(param_1 + 0x104),(Mtx *)(param_1 + 0x94));
  GXSetProjection(param_1 + 0x94,0);
  if (*(int *)(param_1 + 0x46c) == 0) {
    if (Pad._452_4_ == 0) {
      uVar5 = *(ushort *)
               (&Pad.field_0x4 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54)
      ;
    }
    else {
      uVar5 = 0;
    }
    fVar1 = FLOAT_8032fa34;
    if ((uVar5 & 4) != 0) {
      fVar1 = FLOAT_8032fa20;
    }
    *(float *)(param_1 + 0x44c) = *(float *)(param_1 + 0x44c) + fVar1;
    fVar2 = FLOAT_8032fa48;
    fVar1 = FLOAT_8032fa34;
    if ((uVar5 & 8) != 0) {
      fVar1 = FLOAT_8032fa20;
    }
    *(float *)(param_1 + 0x44c) = *(float *)(param_1 + 0x44c) - fVar1;
    fVar3 = FLOAT_8032fa48;
    fVar1 = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
      fVar1 = *(float *)(&Pad.field_0x24 +
                        (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
    }
    *(float *)(param_1 + 0x458) = fVar2 * fVar1 + *(float *)(param_1 + 0x458);
    fVar2 = FLOAT_8032fabc;
    fVar1 = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
      fVar1 = *(float *)(&Pad.field_0x28 +
                        (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
    }
    *(float *)(param_1 + 0x454) = -(fVar3 * fVar1 - *(float *)(param_1 + 0x454));
    fVar3 = FLOAT_8032fabc;
    fVar1 = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
      fVar1 = *(float *)(&Pad.field_0x1c +
                        (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
    }
    *(float *)(param_1 + 0x45c) = -(fVar2 * fVar1 - *(float *)(param_1 + 0x45c));
    fVar1 = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
      fVar1 = *(float *)(&Pad.field_0x20 +
                        (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
    }
    *(float *)(param_1 + 0x45c) = fVar3 * fVar1 + *(float *)(param_1 + 0x45c);
  }
  else {
    *(undefined4 *)(param_1 + 0x46c) = 0;
  }
  PSMTXTrans(*(float *)(param_1 + 0x448),*(float *)(param_1 + 0x44c),*(float *)(param_1 + 0x450),
             &MStack_a0);
  PSMTXRotRad(*(float *)(param_1 + 0x458),&MStack_70,0x79);
  PSMTXConcat(&MStack_70,&MStack_a0,&MStack_a0);
  PSMTXRotRad(*(float *)(param_1 + 0x454),&MStack_70,0x78);
  PSMTXConcat(&MStack_70,&MStack_a0,&MStack_a0);
  PSMTXTrans(FLOAT_8032fa34,FLOAT_8032fa34,-*(float *)(param_1 + 0x45c),&MStack_70);
  PSMTXConcat(&MStack_70,&MStack_a0,(Mtx *)(param_1 + 4));
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_40);
  fVar2 = FLOAT_8032fa38;
  fVar1 = FLOAT_8032fa34;
  *(float *)(param_1 + 0xec) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar1;
  *(float *)(param_1 + 0xf4) = fVar2;
  PSMTXMultVecSR(&MStack_40,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x448);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x44c);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x450);
  pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_d0,(Vec *)(param_1 + 0xec));
  __ct__7CVectorFv(&local_dc);
  PSVECScale(FLOAT_8032fa88,pVVar4,&local_dc);
  local_c4.x = local_dc.x;
  local_c4.y = local_dc.y;
  local_c4.z = local_dc.z;
  pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(aCStack_b8,(Vec *)(param_1 + 0xd4));
  __ct__7CVectorFv(&local_e8);
  PSVECAdd(pVVar4,&local_c4,&local_e8);
  *(float *)(param_1 + 0xe0) = local_e8.x;
  *(float *)(param_1 + 0xe4) = local_e8.y;
  *(float *)(param_1 + 0xe8) = local_e8.z;
  return;
}

