// Function: calcFunnyShape__10CCameraPcsFv
// Entry: 800363e8
// Size: 720 bytes

void calcFunnyShape__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  Mtx MStack_98;
  Mtx MStack_68;
  Mtx MStack_38;
  
  C_MTXPerspective(FLOAT_8032fa30,FLOAT_8032fa3c,FLOAT_8032fa40,FLOAT_8032fa44,
                   (Mtx *)(param_1 + 0x94));
  GXSetProjection(param_1 + 0x94,0);
  if (Pad._452_4_ == 0) {
    uVar4 = *(ushort *)
             (&Pad.field_0x4 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
  }
  else {
    uVar4 = 0;
  }
  fVar1 = FLOAT_8032fa34;
  if ((uVar4 & 8) != 0) {
    fVar1 = FLOAT_8032fa20;
  }
  *(float *)(param_1 + 0x44c) = *(float *)(param_1 + 0x44c) + fVar1;
  fVar2 = FLOAT_8032fa48;
  fVar1 = FLOAT_8032fa34;
  if ((uVar4 & 4) != 0) {
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
  fVar2 = FLOAT_8032fa4c;
  fVar1 = FLOAT_8032fa34;
  if (Pad._452_4_ == 0) {
    fVar1 = *(float *)(&Pad.field_0x28 +
                      (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
  }
  *(float *)(param_1 + 0x454) = -(fVar3 * fVar1 - *(float *)(param_1 + 0x454));
  fVar3 = FLOAT_8032fa4c;
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
  PSMTXTrans(*(float *)(param_1 + 0x448),*(float *)(param_1 + 0x44c),*(float *)(param_1 + 0x450),
             &MStack_98);
  PSMTXRotRad(*(float *)(param_1 + 0x458),&MStack_68,0x79);
  PSMTXConcat(&MStack_68,&MStack_98,&MStack_98);
  PSMTXRotRad(*(float *)(param_1 + 0x454),&MStack_68,0x78);
  PSMTXConcat(&MStack_68,&MStack_98,&MStack_98);
  PSMTXTrans(FLOAT_8032fa34,FLOAT_8032fa34,-*(float *)(param_1 + 0x45c),&MStack_68);
  PSMTXConcat(&MStack_68,&MStack_98,(Mtx *)(param_1 + 4));
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_38);
  fVar2 = FLOAT_8032fa38;
  fVar1 = FLOAT_8032fa34;
  *(float *)(param_1 + 0xec) = FLOAT_8032fa34;
  *(float *)(param_1 + 0xf0) = fVar1;
  *(float *)(param_1 + 0xf4) = fVar2;
  PSMTXMultVecSR(&MStack_38,(Vec *)(param_1 + 0xec),(Vec *)(param_1 + 0xec));
  return;
}

