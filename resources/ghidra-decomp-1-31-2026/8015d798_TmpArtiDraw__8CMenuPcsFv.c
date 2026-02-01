// Function: TmpArtiDraw__8CMenuPcsFv
// Entry: 8015d798
// Size: 1056 bytes

/* WARNING: Removing unreachable block (ram,0x8015db9c) */
/* WARNING: Removing unreachable block (ram,0x8015db94) */
/* WARNING: Removing unreachable block (ram,0x8015db8c) */
/* WARNING: Removing unreachable block (ram,0x8015db84) */
/* WARNING: Removing unreachable block (ram,0x8015db7c) */
/* WARNING: Removing unreachable block (ram,0x8015db74) */
/* WARNING: Removing unreachable block (ram,0x8015db6c) */
/* WARNING: Removing unreachable block (ram,0x8015d7d8) */
/* WARNING: Removing unreachable block (ram,0x8015d7d0) */
/* WARNING: Removing unreachable block (ram,0x8015d7c8) */
/* WARNING: Removing unreachable block (ram,0x8015d7c0) */
/* WARNING: Removing unreachable block (ram,0x8015d7b8) */
/* WARNING: Removing unreachable block (ram,0x8015d7b0) */
/* WARNING: Removing unreachable block (ram,0x8015d7a8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void TmpArtiDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  undefined4 *puVar2;
  uint32_t uVar3;
  int32_t iVar4;
  int iVar5;
  short *psVar6;
  uint32_t uVar7;
  CFont *font;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined auStack_d0 [4];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined8 local_b0;
  undefined4 local_a8;
  uint uStack_a4;
  undefined8 local_a0;
  undefined8 local_98;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar7 = Game.game.m_scriptFoodBase[0];
  psVar6 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  uVar3 = Game.game.m_scriptFoodBase[0];
  for (iVar5 = 0; iVar5 < **(short **)&menuPcs->field_0x850; iVar5 = iVar5 + 1) {
    iVar1 = *(int *)(psVar6 + 0xe);
    if (-1 < iVar1) {
      uStack_a4 = (int)psVar6[1] ^ 0x80000000;
      dVar8 = (double)*(float *)(psVar6 + 8);
      local_b0 = (double)CONCAT44(0x43300000,(int)*psVar6 ^ 0x80000000);
      local_a8 = 0x43300000;
      dVar13 = (double)(float)(local_b0 - DOUBLE_80332f40);
      dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80332f40);
      dVar9 = (double)*(float *)(psVar6 + 4);
      local_a0 = (double)CONCAT44(0x43300000,(int)psVar6[2] ^ 0x80000000);
      dVar14 = (double)*(float *)(psVar6 + 6);
      dVar11 = (double)(float)(local_a0 - DOUBLE_80332f40);
      local_98 = (double)CONCAT44(0x43300000,(int)psVar6[3] ^ 0x80000000);
      dVar10 = (double)(float)(local_98 - DOUBLE_80332f40);
      if (*(short *)(uVar3 + 0x1f6) < 0) {
        iVar1 = 0x34;
        dVar8 = (double)(float)(DOUBLE_80332f20 * dVar8);
      }
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar1);
      local_98 = (double)(longlong)(int)((double)FLOAT_80332f28 * dVar8);
      local_c4 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332f28 * dVar8));
      local_c8 = local_c4;
      GXSetChanMatColor(4,&local_c8);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar13,dVar12,dVar11,dVar10,dVar9,dVar14,(double)*(float *)(psVar6 + 10),
                 (double)*(float *)(psVar6 + 10),&MenuPcs,0);
    }
    uVar3 = uVar3 + 2;
    psVar6 = psVar6 + 0x20;
  }
  psVar6 = *(short **)&menuPcs->field_0x850 + 4;
  iVar5 = 0;
  uVar3 = uVar7;
  do {
    if (-1 < *(short *)(uVar3 + 0x1f6)) {
      uStack_a4 = (int)psVar6[1] + 6U ^ 0x80000000;
      local_a8 = 0x43300000;
      local_98 = (double)CONCAT44(0x43300000,(int)*psVar6 + psVar6[2] + -0x10 ^ 0x80000000);
      iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80332f40) -
                   FLOAT_80332f30);
      local_b0 = (double)(longlong)iVar1;
      local_a0 = (double)(longlong)(int)(local_98 - DOUBLE_80332f40);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)*(float *)(psVar6 + 8),menuPcs,(int)*(short *)(uVar3 + 0x1f6),
                 (int)(local_98 - DOUBLE_80332f40),iVar1,0);
    }
    iVar5 = iVar5 + 1;
    psVar6 = psVar6 + 0x20;
    uVar3 = uVar3 + 2;
  } while (iVar5 < 4);
  font = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332f30,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80332f34,font);
  DrawInit__5CFontFv(font);
  psVar6 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar5 = 0;
  do {
    if (-1 < *(short *)(uVar7 + 0x1f6)) {
      local_98 = (double)(longlong)(int)(FLOAT_80332f28 * *(float *)(psVar6 + 8));
      puVar2 = (undefined4 *)
               __ct__6CColorFUcUcUcUc
                         (auStack_d0,0xff,0xff,0xff,(int)(FLOAT_80332f28 * *(float *)(psVar6 + 8)));
      local_cc = *puVar2;
      SetColor__5CFontF8_GXColor(font,&local_cc);
      iVar4 = Game.game.m_cFlatDataArr[1].m_table[0].index[*(short *)(uVar7 + 0x1f6) * 5 + 4];
      dVar8 = (double)GetWidth__5CFontFPc(font,iVar4);
      uStack_a4 = (int)psVar6[2] ^ 0x80000000;
      local_a8 = 0x43300000;
      local_b0 = (double)CONCAT44(0x43300000,(int)*psVar6 ^ 0x80000000);
      local_a0 = (double)CONCAT44(0x43300000,(int)psVar6[1] + 0xbU ^ 0x80000000);
      dVar14 = (double)(float)(local_a0 - DOUBLE_80332f40);
      SetPosX__5CFontFf((float)((double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_a4) -
                                                               DOUBLE_80332f40) - dVar8) *
                                DOUBLE_80332f20 + (local_b0 - DOUBLE_80332f40)),font);
      SetPosY__5CFontFf((float)(dVar14 - (double)FLOAT_80332f38),font);
      Draw__5CFontFPc(font,iVar4);
    }
    iVar5 = iVar5 + 1;
    psVar6 = psVar6 + 0x20;
    uVar7 = uVar7 + 2;
  } while (iVar5 < 4);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

