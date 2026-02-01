// Function: ArtiDraw__8CMenuPcsFv
// Entry: 8015fd54
// Size: 2308 bytes

/* WARNING: Removing unreachable block (ram,0x8016063c) */
/* WARNING: Removing unreachable block (ram,0x80160634) */
/* WARNING: Removing unreachable block (ram,0x8016062c) */
/* WARNING: Removing unreachable block (ram,0x80160624) */
/* WARNING: Removing unreachable block (ram,0x8016061c) */
/* WARNING: Removing unreachable block (ram,0x80160614) */
/* WARNING: Removing unreachable block (ram,0x8016060c) */
/* WARNING: Removing unreachable block (ram,0x8015fd94) */
/* WARNING: Removing unreachable block (ram,0x8015fd8c) */
/* WARNING: Removing unreachable block (ram,0x8015fd84) */
/* WARNING: Removing unreachable block (ram,0x8015fd7c) */
/* WARNING: Removing unreachable block (ram,0x8015fd74) */
/* WARNING: Removing unreachable block (ram,0x8015fd6c) */
/* WARNING: Removing unreachable block (ram,0x8015fd64) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ArtiDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint uVar1;
  short sVar2;
  short sVar3;
  bool bVar4;
  uint32_t uVar5;
  undefined4 *puVar6;
  int32_t iVar7;
  undefined4 uVar8;
  short *psVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  CFont *pCVar13;
  int unaff_r27;
  short *psVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double in_f29;
  double dVar19;
  double dVar20;
  undefined auStack_110 [4];
  undefined4 local_10c;
  undefined auStack_108 [4];
  undefined4 local_104;
  undefined auStack_100 [4];
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined local_ec;
  undefined local_eb;
  undefined local_ea;
  undefined local_e9;
  undefined local_e8;
  undefined local_e7;
  undefined local_e6;
  undefined local_e5;
  undefined local_e4;
  undefined local_e3;
  undefined local_e2;
  undefined local_e1;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  double local_c0;
  longlong local_b8;
  
  bVar4 = false;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar5 = Game.game.m_scriptFoodBase[0];
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  psVar14 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar12 = 0;
  for (iVar11 = 0; iVar11 < **(short **)&menuPcs->field_0x850; iVar11 = iVar11 + 1) {
    iVar10 = *(int *)(psVar14 + 0xe);
    if (-1 < iVar10) {
      local_e0 = (double)CONCAT44(0x43300000,(int)*psVar14 ^ 0x80000000);
      dVar17 = (double)*(float *)(psVar14 + 4);
      dVar20 = (double)(float)(local_e0 - DOUBLE_80332fe0);
      dVar16 = (double)*(float *)(psVar14 + 6);
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar14[1] ^ 0x80000000);
      dVar19 = (double)(float)(local_d8 - DOUBLE_80332fe0);
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
      in_f29 = (double)(float)(local_d0 - DOUBLE_80332fe0);
      local_c8 = (double)CONCAT44(0x43300000,(int)psVar14[3] ^ 0x80000000);
      dVar18 = (double)(float)(local_c8 - DOUBLE_80332fe0);
      if (iVar11 == 0) {
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar14 + 0xe));
        local_f0 = 0xffffffff;
        local_ec = 0xff;
        local_eb = 0xff;
        local_ea = 0xff;
        local_e9 = 0xff;
        local_e8 = 0xff;
        local_e7 = 0xff;
        local_e6 = 0xff;
        local_e5 = 0xff;
        local_e4 = 0xff;
        local_e3 = 0xff;
        local_e2 = 0xff;
        local_e1 = 0xff;
        local_f4 = 0xffffffff;
        GXSetChanMatColor(4,&local_f4);
        in_f29 = (double)(float)((double)*(float *)(psVar14 + 8) * in_f29);
        if ((double)FLOAT_80332fa8 < in_f29) {
          DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                    (dVar20,dVar19,in_f29,dVar18,dVar17,dVar16,(double)FLOAT_80332fac,
                     (double)FLOAT_80332fac,&MenuPcs,0,&local_f0);
          dVar20 = (double)(float)(dVar20 + in_f29);
          dVar17 = (double)(float)(dVar17 + in_f29);
        }
        if ((double)FLOAT_80332fa8 < in_f29) {
          local_c8 = (double)(CONCAT44(0x43300000,(int)psVar14[2]) ^ 0x80000000);
          if (in_f29 < (double)(float)(local_c8 - DOUBLE_80332fe0)) {
            local_ec = 0xff;
            local_eb = 0xff;
            local_ea = 0xff;
            local_e9 = 0;
            local_e4 = 0xff;
            local_e3 = 0xff;
            local_e2 = 0xff;
            local_e1 = 0;
            local_c8 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar14 + 0x14)) ^ 0x80000000);
            local_d0 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
            in_f29 = (double)((float)(DOUBLE_80332fb0 / (local_c8 - DOUBLE_80332fe0)) *
                             (float)(local_d0 - DOUBLE_80332fe0));
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (dVar20,dVar19,in_f29,dVar18,dVar17,dVar16,(double)FLOAT_80332fac,
                       (double)FLOAT_80332fac,&MenuPcs,0,&local_f0);
          }
        }
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      }
      else {
        dVar15 = (double)*(float *)(psVar14 + 8);
        if (iVar10 == 0x37) {
          if (*(short *)(uVar5 + (iVar12 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34)) * 2 +
                                 0x136) < 1) {
            iVar10 = 0x34;
            dVar15 = (double)(float)(DOUBLE_80332fb8 * dVar15);
          }
          if ((iVar10 == 0x37) && (iVar12 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
            dVar16 = (double)(float)(dVar16 + dVar18);
          }
          iVar12 = iVar12 + 1;
        }
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar10);
        local_c8 = (double)(longlong)(int)((double)FLOAT_80332fc0 * dVar15);
        local_f0 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332fc0 * dVar15));
        local_f8 = local_f0;
        GXSetChanMatColor(4,&local_f8);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar20,dVar19,in_f29,dVar18,dVar17,dVar16,(double)*(float *)(psVar14 + 10),
                   (double)*(float *)(psVar14 + 10),&MenuPcs,0);
      }
    }
    psVar14 = psVar14 + 0x20;
  }
  pCVar13 = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332fac,pCVar13);
  SetShadow__5CFontFi(pCVar13,0);
  SetScale__5CFontFf(FLOAT_80332fc4,pCVar13);
  DrawInit__5CFontFv(pCVar13);
  iVar12 = 0;
  iVar11 = (int)**(short **)&menuPcs->field_0x850;
  if (0 < iVar11) {
    do {
      psVar14 = (short *)((int)*(short **)&menuPcs->field_0x850 + iVar12 + 8);
      if (*(int *)(psVar14 + 0xe) == 0x37) break;
      iVar12 = iVar12 + 0x40;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  dVar18 = (double)FLOAT_80332fc0;
  dVar17 = (double)FLOAT_80332fc8;
  iVar11 = 0;
  psVar9 = psVar14;
  dVar16 = DOUBLE_80332fe0;
  do {
    local_c8 = (double)(longlong)(int)(dVar18 * (double)*(float *)(psVar14 + 8));
    iVar12 = iVar11 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
    puVar6 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_100,0xff,0xff,0xff,(int)(dVar18 * (double)*(float *)(psVar14 + 8)));
    local_fc = *puVar6;
    SetColor__5CFontF8_GXColor(pCVar13,&local_fc);
    sVar3 = *(short *)(uVar5 + iVar12 * 2 + 0x136);
    if (sVar3 < 1) {
      iVar7 = GetMenuStr__8CMenuPcsFi(menuPcs,0x14);
    }
    else {
      iVar7 = Game.game.m_cFlatDataArr[1].m_table[0].index[sVar3 * 5 + 4];
      if (iVar12 == (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) +
                    (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34)) {
        bVar4 = true;
        unaff_r27 = (int)sVar3;
      }
    }
    GetWidth__5CFontFPc(pCVar13,iVar7);
    local_c8 = (double)(CONCAT44(0x43300000,psVar9[1] + 0xb) ^ 0x80000000);
    local_d0 = (double)(CONCAT44(0x43300000,*psVar9 + 0x1c) ^ 0x80000000);
    dVar19 = (double)(float)(local_c8 - dVar16);
    SetPosX__5CFontFf((float)(local_d0 - dVar16),pCVar13);
    SetPosY__5CFontFf((float)(dVar19 - dVar17),pCVar13);
    Draw__5CFontFPc(pCVar13,iVar7);
    iVar11 = iVar11 + 1;
    psVar9 = psVar9 + 0x20;
  } while (iVar11 < 8);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar11 = 0;
  psVar9 = psVar14;
  do {
    sVar3 = *(short *)(uVar5 + (iVar11 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34)) * 2 +
                               0x136);
    if (0 < sVar3) {
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar9[1] + 6U ^ 0x80000000);
      local_c8 = (double)CONCAT44(0x43300000,(int)*psVar9 + psVar9[2] + -0x10 ^ 0x80000000);
      iVar12 = (int)((float)(local_d8 - DOUBLE_80332fe0) - FLOAT_80332fac);
      local_e0 = (double)(longlong)iVar12;
      local_d0 = (double)(longlong)(int)(local_c8 - DOUBLE_80332fe0);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)*(float *)(psVar14 + 8),menuPcs,(int)sVar3,
                 (int)(local_c8 - DOUBLE_80332fe0),iVar12,0);
    }
    iVar11 = iVar11 + 1;
    psVar9 = psVar9 + 0x20;
  } while (iVar11 < 8);
  if (sVar2 == 1) {
    iVar11 = *(int *)&menuPcs->field_0x850;
    psVar14 = (short *)(iVar11 + 8);
    dVar16 = (double)CalcListPos__8CMenuPcsFiii
                               (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34),0x49,0
                               );
    if ((double)FLOAT_80332fa8 < dVar16) {
      local_c8 = (double)(CONCAT44(0x43300000,(int)*psVar14) ^ 0x80000000);
      local_d0 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar11 + 10) ^ 0x80000000);
      DrawListPosMark__8CMenuPcsFfff
                ((double)(float)(local_c8 - DOUBLE_80332fe0),
                 (double)(float)(local_d0 - DOUBLE_80332fe0),dVar16,menuPcs);
    }
  }
  if (sVar2 == 1) {
    psVar9 = *(short **)&menuPcs->field_0x850;
    iVar12 = 0;
    iVar11 = (int)*psVar9;
    if (0 < iVar11) {
      do {
        psVar14 = (short *)((int)psVar9 + iVar12 + 8);
        if (*(int *)((int)psVar9 + iVar12 + 0x24) == 0x37) break;
        iVar12 = iVar12 + 0x40;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    psVar14 = psVar14 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x20;
    iVar11 = (int)System.m_frameCounter >> 0x1f;
    local_e0 = (double)(CONCAT44(0x43300000,psVar14[3] + -0x20) ^ 0x80000000);
    local_c0 = (double)(CONCAT44(0x43300000,(int)psVar14[1]) ^ 0x80000000);
    local_c8 = (double)CONCAT44(0x43300000,(int)*psVar14 - 0x14U ^ 0x80000000);
    local_d0 = (double)CONCAT44(0x43300000,
                                (iVar11 * 8 | System.m_frameCounter * 0x20000000 + iVar11 >> 0x1d) -
                                iVar11 ^ 0x80000000);
    iVar11 = (int)((local_e0 - DOUBLE_80332fe0) * DOUBLE_80332fb8 + (local_c0 - DOUBLE_80332fe0));
    local_b8 = (longlong)iVar11;
    iVar12 = (int)((float)(local_c8 - DOUBLE_80332fe0) + (float)(local_d0 - DOUBLE_80332fe0));
    local_d8 = (double)(longlong)iVar12;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80332fac,menuPcs,iVar12,iVar11);
  }
  pCVar13 = *(CFont **)&menuPcs->field_0xf8;
  uVar1 = (uint)(FLOAT_80332fc0 * *(float *)(*(int *)&menuPcs->field_0x850 + 0x18));
  local_b8 = (longlong)(int)uVar1;
  if (!bVar4) {
    unaff_r27 = -1;
  }
  if (unaff_r27 == -1) {
    uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,0x14);
    puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_108,0xff,0xff,0xff,uVar1 & 0xff);
    local_104 = *puVar6;
    dVar16 = (double)CalcCenteringPos__8CMenuPcsFPcP5CFont(menuPcs,uVar8,pCVar13);
    local_b8 = (longlong)(int)dVar16;
    local_c0 = (double)(longlong)(int)FLOAT_80332fcc;
    DrawFont__8CMenuPcsFii8_GXColoriPcff
              ((double)FLOAT_80332fac,(double)FLOAT_80332fd0,menuPcs,(int)dVar16,(int)FLOAT_80332fcc
               ,&local_104,10,uVar8);
  }
  else {
    puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_110,0xff,0xff,0xff,uVar1 & 0xff);
    local_10c = *puVar6;
    local_c0 = (double)(longlong)(int)FLOAT_80332fcc;
    local_b8 = (longlong)(int)-(float)(in_f29 * (double)FLOAT_80332fd8 - (double)FLOAT_80332fd4);
    DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,unaff_r27);
  }
  return;
}

