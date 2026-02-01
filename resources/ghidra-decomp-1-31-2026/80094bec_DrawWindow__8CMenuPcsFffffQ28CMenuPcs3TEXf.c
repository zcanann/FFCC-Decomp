// Function: DrawWindow__8CMenuPcsFffffQ28CMenuPcs3TEXf
// Entry: 80094bec
// Size: 2544 bytes

/* WARNING: Removing unreachable block (ram,0x800955b8) */
/* WARNING: Removing unreachable block (ram,0x800955b0) */
/* WARNING: Removing unreachable block (ram,0x800955a8) */
/* WARNING: Removing unreachable block (ram,0x800955a0) */
/* WARNING: Removing unreachable block (ram,0x80095598) */
/* WARNING: Removing unreachable block (ram,0x80095590) */
/* WARNING: Removing unreachable block (ram,0x80095588) */
/* WARNING: Removing unreachable block (ram,0x80095580) */
/* WARNING: Removing unreachable block (ram,0x80095578) */
/* WARNING: Removing unreachable block (ram,0x80095570) */
/* WARNING: Removing unreachable block (ram,0x80095568) */
/* WARNING: Removing unreachable block (ram,0x80095560) */
/* WARNING: Removing unreachable block (ram,0x80095558) */
/* WARNING: Removing unreachable block (ram,0x80095550) */
/* WARNING: Removing unreachable block (ram,0x80094c64) */
/* WARNING: Removing unreachable block (ram,0x80094c5c) */
/* WARNING: Removing unreachable block (ram,0x80094c54) */
/* WARNING: Removing unreachable block (ram,0x80094c4c) */
/* WARNING: Removing unreachable block (ram,0x80094c44) */
/* WARNING: Removing unreachable block (ram,0x80094c3c) */
/* WARNING: Removing unreachable block (ram,0x80094c34) */
/* WARNING: Removing unreachable block (ram,0x80094c2c) */
/* WARNING: Removing unreachable block (ram,0x80094c24) */
/* WARNING: Removing unreachable block (ram,0x80094c1c) */
/* WARNING: Removing unreachable block (ram,0x80094c14) */
/* WARNING: Removing unreachable block (ram,0x80094c0c) */
/* WARNING: Removing unreachable block (ram,0x80094c04) */
/* WARNING: Removing unreachable block (ram,0x80094bfc) */

void DrawWindow__8CMenuPcsFffffQ28CMenuPcs3TEXf
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               int param_6,int param_7)

{
  float fVar1;
  float fVar2;
  CTexture *pCVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  Mtx MStack_2b0;
  Mtx MStack_280;
  Mtx MStack_250;
  Mtx MStack_220;
  Mtx MStack_1f0;
  Mtx MStack_1c0;
  Mtx MStack_190;
  Mtx MStack_160;
  Mtx MStack_130;
  undefined4 local_100;
  uint uStack_fc;
  undefined4 local_f8;
  uint uStack_f4;
  
  dVar12 = (double)FLOAT_8033080c;
  if ((dVar12 < param_3) && (dVar12 < param_4)) {
    dVar5 = (double)(float)((double)FLOAT_80330830 * param_5);
    dVar4 = (double)(float)(param_3 - dVar5);
    if (dVar4 < dVar12) {
      dVar4 = dVar12;
    }
    dVar12 = (double)(float)(param_4 - dVar5);
    if (dVar12 < (double)FLOAT_8033080c) {
      dVar12 = (double)FLOAT_8033080c;
    }
    fVar1 = (float)(dVar5 - param_3);
    if (fVar1 < FLOAT_8033080c) {
      fVar1 = FLOAT_8033080c;
    }
    fVar2 = (float)(dVar5 - param_4);
    dVar5 = (double)(fVar1 * FLOAT_8033084c);
    if (fVar2 < FLOAT_8033080c) {
      fVar2 = FLOAT_8033080c;
    }
    dVar11 = (double)(fVar2 * FLOAT_8033084c);
    if (param_7 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + param_7 * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_fc = pCVar3->field94_0x64;
      uStack_f4 = pCVar3->field95_0x68;
      local_100 = 0x43300000;
      local_f8 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_130);
      GXLoadTexMtxImm(&MStack_130,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    dVar10 = (double)(float)(param_5 - dVar5);
    dVar13 = (double)(float)(param_5 - dVar11);
    DrawRect__8CMenuPcsFUlfffffffff
              (param_1,param_2,dVar10,dVar13,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_6,0);
    if (param_7 + 1 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 1) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_160);
      GXLoadTexMtxImm(&MStack_160,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    dVar8 = (double)(float)(param_1 + param_5);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar8,param_2,dVar4,dVar13,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_6,0);
    if (param_7 + 2 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 2) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_190);
      GXLoadTexMtxImm(&MStack_190,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    dVar9 = (double)(float)((double)(float)(param_1 + param_3) - param_5);
    dVar6 = (double)(float)(dVar5 + dVar9);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar6,param_2,dVar10,dVar13,dVar5,(double)FLOAT_8033080c,(double)FLOAT_80330808,
               (double)FLOAT_80330808,param_6,0);
    if (param_7 + 3 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 3) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_1c0);
      GXLoadTexMtxImm(&MStack_1c0,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    dVar7 = (double)(float)(param_2 + param_5);
    DrawRect__8CMenuPcsFUlfffffffff
              (param_1,dVar7,param_5,dVar12,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_6,0);
    if (param_7 + 4 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 4) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_1f0);
      GXLoadTexMtxImm(&MStack_1f0,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar8,dVar7,dVar4,dVar12,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_6,0);
    if (param_7 + 5 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 5) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_220);
      GXLoadTexMtxImm(&MStack_220,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar9,dVar7,param_5,dVar12,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_6,0);
    if (param_7 + 6 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 6) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_250);
      GXLoadTexMtxImm(&MStack_250,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    dVar12 = (double)(float)(dVar11 + (double)(float)((double)(float)(param_2 + param_4) - param_5))
    ;
    DrawRect__8CMenuPcsFUlfffffffff
              (param_1,dVar12,dVar10,dVar13,(double)FLOAT_8033080c,dVar11,(double)FLOAT_80330808,
               (double)FLOAT_80330808,param_6,0);
    if (param_7 + 7 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 7) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_280);
      GXLoadTexMtxImm(&MStack_280,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar8,dVar12,dVar4,dVar13,(double)FLOAT_8033080c,dVar11,(double)FLOAT_80330808,
               (double)FLOAT_80330808,param_6,0);
    if (param_7 + 8 == -1) {
      pCVar3 = (CTexture *)0x0;
    }
    else {
      pCVar3 = *(CTexture **)(param_6 + (param_7 + 8) * 4 + 0x18c);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,pCVar3);
      uStack_f4 = pCVar3->field94_0x64;
      uStack_fc = pCVar3->field95_0x68;
      local_f8 = 0x43300000;
      local_100 = 0x43300000;
      PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80330840),
                 FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80330840),
                 FLOAT_80330808,&MStack_2b0);
      GXLoadTexMtxImm(&MStack_2b0,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    }
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,pCVar3);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar6,dVar12,dVar10,dVar13,dVar5,dVar11,(double)FLOAT_80330808,(double)FLOAT_80330808
               ,param_6,0);
  }
  return;
}

