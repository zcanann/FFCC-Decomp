// Function: MoneyDraw__8CMenuPcsFv
// Entry: 8015eda8
// Size: 1636 bytes

/* WARNING: Removing unreachable block (ram,0x8015f3f0) */
/* WARNING: Removing unreachable block (ram,0x8015f3e8) */
/* WARNING: Removing unreachable block (ram,0x8015f3e0) */
/* WARNING: Removing unreachable block (ram,0x8015f3d8) */
/* WARNING: Removing unreachable block (ram,0x8015f3d0) */
/* WARNING: Removing unreachable block (ram,0x8015f3c8) */
/* WARNING: Removing unreachable block (ram,0x8015ede0) */
/* WARNING: Removing unreachable block (ram,0x8015edd8) */
/* WARNING: Removing unreachable block (ram,0x8015edd0) */
/* WARNING: Removing unreachable block (ram,0x8015edc8) */
/* WARNING: Removing unreachable block (ram,0x8015edc0) */
/* WARNING: Removing unreachable block (ram,0x8015edb8) */

void MoneyDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  CFont *font;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined8 local_b8;
  undefined4 local_b0;
  uint uStack_ac;
  undefined4 local_a8;
  uint uStack_a4;
  undefined4 local_a0;
  uint uStack_9c;
  undefined8 local_98;
  longlong local_90;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
  psVar6 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  for (iVar7 = 0; psVar5 = *(short **)&menuPcs->field_0x850, iVar7 < *psVar5; iVar7 = iVar7 + 1) {
    if (-1 < *(int *)(psVar6 + 0xe)) {
      uStack_ac = (int)psVar6[1] ^ 0x80000000;
      uStack_a4 = (int)psVar6[2] ^ 0x80000000;
      local_b8 = (double)CONCAT44(0x43300000,(int)*psVar6 ^ 0x80000000);
      uStack_9c = (int)psVar6[3] ^ 0x80000000;
      dVar14 = (double)(float)(local_b8 - DOUBLE_80332f88);
      dVar11 = (double)*(float *)(psVar6 + 4);
      local_b0 = 0x43300000;
      dVar12 = (double)*(float *)(psVar6 + 6);
      dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_ac) - DOUBLE_80332f88);
      local_a8 = 0x43300000;
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80332f88);
      local_a0 = 0x43300000;
      dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_80332f88);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar6 + 0xe));
      local_98 = (double)(longlong)(int)(FLOAT_80332f60 * *(float *)(psVar6 + 8));
      local_cc = CONCAT31(0xffffff,(char)(int)(FLOAT_80332f60 * *(float *)(psVar6 + 8)));
      local_d0 = local_cc;
      GXSetChanMatColor(4,&local_d0);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar14,dVar13,dVar15,dVar16,dVar11,dVar12,(double)*(float *)(psVar6 + 10),
                 (double)*(float *)(psVar6 + 10),&MenuPcs,0);
    }
    psVar6 = psVar6 + 0x20;
  }
  psVar6 = psVar5 + 4;
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x5d);
  local_98 = (double)(longlong)(int)(FLOAT_80332f60 * *(float *)(psVar5 + 0xc));
  local_cc = CONCAT31(0xffffff,(char)(int)(FLOAT_80332f60 * *(float *)(psVar5 + 0xc)));
  local_d4 = local_cc;
  GXSetChanMatColor(4,&local_d4);
  dVar13 = (double)FLOAT_80332f74;
  puVar9 = s_place;
  dVar15 = (double)FLOAT_80332f68;
  uVar8 = 0;
  dVar14 = DOUBLE_80332f88;
  do {
    uStack_a4 = uVar8 ^ 0x80000000;
    local_a8 = 0x43300000;
    uStack_9c = (int)psVar5[5] + 0x18U ^ 0x80000000;
    iVar7 = 0;
    local_a0 = 0x43300000;
    dVar11 = (double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_a4) -
                                                     dVar14));
    local_98 = (double)CONCAT44(0x43300000,(int)*psVar6 + 0x20U ^ 0x80000000);
    dVar12 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_9c) - dVar14) +
                            dVar11);
    dVar16 = local_98 - dVar14;
    pcVar10 = (char *)puVar9;
    do {
      dVar16 = (double)(float)dVar16;
      if (-1 < *pcVar10) {
        local_98 = (double)CONCAT44(0x43300000,(int)*pcVar10 ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar16,dVar12,(double)FLOAT_80332f6c,(double)FLOAT_80332f68,
                   (double)(float)((double)FLOAT_80332f6c *
                                  (double)(float)(local_98 - DOUBLE_80332f88)),dVar11,
                   (double)FLOAT_80332f70,(double)FLOAT_80332f70,&MenuPcs,0);
      }
      iVar7 = iVar7 + 1;
      dVar16 = dVar16 + dVar13;
      pcVar10 = pcVar10 + 1;
    } while (iVar7 < 8);
    uVar8 = uVar8 + 1;
    puVar9 = (undefined4 *)((int)puVar9 + 8);
  } while ((int)uVar8 < 2);
  if ((sVar2 == 0) && (sVar1 == 1)) {
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x48);
    local_98 = (double)(longlong)(int)(FLOAT_80332f60 * *(float *)(psVar5 + 0xc));
    local_cc = CONCAT31(0xffffff,(char)(int)(FLOAT_80332f60 * *(float *)(psVar5 + 0xc)));
    local_d8 = local_cc;
    GXSetChanMatColor(4,&local_d8);
    psVar6 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
    local_a8 = 0x43300000;
    uStack_a4 = (int)*(short *)(*(int *)&menuPcs->field_0x850 + 10) + 0x5cU ^ 0x80000000;
    uStack_9c = (int)*psVar6 + (7 - *(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) * 0x12 + 0x24U
                ^ 0x80000000;
    local_a0 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_80332f88),
               (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80332f88),
               (double)FLOAT_80332f78,(double)FLOAT_80332f6c,(double)FLOAT_80332f64,
               (double)FLOAT_80332f64,(double)FLOAT_80332f70,(double)FLOAT_80332f70,&MenuPcs,0);
  }
  font = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332f70,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80332f7c,font);
  DrawInit__5CFontFv(font);
  local_98 = (double)(longlong)(int)(FLOAT_80332f60 * *(float *)(psVar6 + 8));
  puVar9 = (undefined4 *)
           __ct__6CColorFUcUcUcUc
                     (auStack_e0,0xff,0xff,0xff,(int)(FLOAT_80332f60 * *(float *)(psVar6 + 8)));
  local_dc = *puVar9;
  SetColor__5CFontF8_GXColor(font,&local_dc);
  uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x15);
  dVar13 = (double)FLOAT_80332f68;
  uVar8 = 0;
  dVar15 = (double)FLOAT_80332f80;
  dVar16 = (double)FLOAT_80332f84;
  dVar14 = DOUBLE_80332f88;
  do {
    uStack_9c = (int)psVar6[1] + 0x18U ^ 0x80000000;
    local_98 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    uStack_a4 = (int)*psVar6 + 0xb6U ^ 0x80000000;
    local_a0 = 0x43300000;
    local_a8 = 0x43300000;
    dVar11 = (double)(float)((double)(float)(dVar13 + (double)(float)(dVar13 * (double)(float)(
                                                  local_98 - dVar14) +
                                                  (double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_9c) -
                                                                 dVar14))) - dVar15);
    SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_a4) - dVar14),font);
    SetPosY__5CFontFf((float)(dVar11 - dVar16),font);
    Draw__5CFontFPc(font,uVar3);
    uVar8 = uVar8 + 1;
  } while ((int)uVar8 < 2);
  DrawInit__8CMenuPcsFv(menuPcs);
  if (sVar2 == 1) {
    DrawSingWin__8CMenuPcsFs(menuPcs,0xffff);
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1) {
      DrawSingWinMess__8CMenuPcsFiii(menuPcs,1,(int)*(char *)(*(int *)&menuPcs->field_0x82c + 9),0);
    }
  }
  if ((sVar2 != 0) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)) {
    local_a0 = 0x43300000;
    uStack_9c = (int)(*(short **)&menuPcs->field_0x848)[1] + 0x20U ^ 0x80000000;
    local_98 = (double)(CONCAT44(0x43300000,(int)**(short **)&menuPcs->field_0x848) ^ 0x80000000);
    dVar14 = (double)(float)(local_98 - DOUBLE_80332f88);
    dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_80332f88);
    iVar4 = SingWinMessHeight__8CMenuPcsFv(menuPcs);
    local_a8 = 0x43300000;
    local_b0 = 0x43300000;
    iVar7 = (int)System.m_frameCounter >> 0x1f;
    uStack_a4 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) * iVar4 ^ 0x80000000;
    uStack_ac = (iVar7 * 8 | System.m_frameCounter * 0x20000000 + iVar7 >> 0x1d) - iVar7 ^
                0x80000000;
    iVar7 = (int)(dVar13 + (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80332f88)
                 );
    local_90 = (longlong)iVar7;
    iVar4 = (int)(dVar14 + (double)(float)((double)CONCAT44(0x43300000,uStack_ac) - DOUBLE_80332f88)
                 );
    local_b8 = (double)(longlong)iVar4;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80332f70,menuPcs,iVar4,iVar7);
  }
  return;
}

