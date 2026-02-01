// Function: FavoDraw__8CMenuPcsFv
// Entry: 80162360
// Size: 2488 bytes

/* WARNING: Removing unreachable block (ram,0x80162cfc) */
/* WARNING: Removing unreachable block (ram,0x80162cf4) */
/* WARNING: Removing unreachable block (ram,0x80162cec) */
/* WARNING: Removing unreachable block (ram,0x80162ce4) */
/* WARNING: Removing unreachable block (ram,0x80162cdc) */
/* WARNING: Removing unreachable block (ram,0x80162cd4) */
/* WARNING: Removing unreachable block (ram,0x80162ccc) */
/* WARNING: Removing unreachable block (ram,0x80162cc4) */
/* WARNING: Removing unreachable block (ram,0x80162cbc) */
/* WARNING: Removing unreachable block (ram,0x80162cb4) */
/* WARNING: Removing unreachable block (ram,0x801623b8) */
/* WARNING: Removing unreachable block (ram,0x801623b0) */
/* WARNING: Removing unreachable block (ram,0x801623a8) */
/* WARNING: Removing unreachable block (ram,0x801623a0) */
/* WARNING: Removing unreachable block (ram,0x80162398) */
/* WARNING: Removing unreachable block (ram,0x80162390) */
/* WARNING: Removing unreachable block (ram,0x80162388) */
/* WARNING: Removing unreachable block (ram,0x80162380) */
/* WARNING: Removing unreachable block (ram,0x80162378) */
/* WARNING: Removing unreachable block (ram,0x80162370) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FavoDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  short *psVar7;
  int32_t iVar8;
  int iVar9;
  undefined *puVar10;
  CFont *pCVar11;
  undefined *puVar12;
  char *pcVar13;
  short *psVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  undefined auStack_120 [4];
  undefined4 local_11c;
  undefined auStack_118 [4];
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined auStack_108 [16];
  undefined4 local_f8;
  undefined local_f4;
  undefined local_f3;
  undefined local_f2;
  undefined local_f1;
  undefined local_f0;
  undefined local_ef;
  undefined local_ee;
  undefined local_ed;
  undefined local_ec;
  undefined local_eb;
  undefined local_ea;
  undefined local_e9;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  iVar9 = 0;
  psVar14 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  while( true ) {
    iVar4 = (int)**(short **)&menuPcs->field_0x850;
    if (iVar4 <= iVar9) break;
    if (-1 < *(int *)(psVar14 + 0xe)) {
      local_e8 = (double)CONCAT44(0x43300000,(int)*psVar14 ^ 0x80000000);
      dVar20 = (double)*(float *)(psVar14 + 4);
      dVar22 = (double)(float)(local_e8 - DOUBLE_80333078);
      dVar19 = (double)*(float *)(psVar14 + 6);
      local_e0 = (double)CONCAT44(0x43300000,(int)psVar14[1] ^ 0x80000000);
      dVar18 = (double)(float)(local_e0 - DOUBLE_80333078);
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
      dVar15 = (double)(float)(local_d8 - DOUBLE_80333078);
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar14[3] ^ 0x80000000);
      dVar17 = (double)(float)(local_d0 - DOUBLE_80333078);
      if (iVar9 < 3) {
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar14 + 0xe));
        local_f8 = 0xffffffff;
        local_f4 = 0xff;
        local_f3 = 0xff;
        local_f2 = 0xff;
        local_f1 = 0xff;
        local_f0 = 0xff;
        local_ef = 0xff;
        local_ee = 0xff;
        local_ed = 0xff;
        local_ec = 0xff;
        local_eb = 0xff;
        local_ea = 0xff;
        local_e9 = 0xff;
        local_10c = 0xffffffff;
        GXSetChanMatColor(4,&local_10c);
        dVar15 = (double)(float)((double)*(float *)(psVar14 + 8) * dVar15);
        if ((double)FLOAT_80333040 < dVar15) {
          if (*(int *)(psVar14 + 0xe) == 0x32) {
            uVar6 = (uint)dVar18;
            dVar16 = (double)(float)(dVar18 + dVar17);
            dVar23 = (double)FLOAT_80333044;
            dVar21 = DOUBLE_80333078;
            while (local_d0 = (double)(CONCAT44(0x43300000,uVar6) ^ 0x80000000),
                  (double)(float)(local_d0 - dVar21) < dVar16) {
              local_d0 = (double)(CONCAT44(0x43300000,uVar6) ^ 0x80000000);
              dVar1 = dVar16 - (double)(float)(local_d0 - dVar21);
              if ((double)(float)dVar1 < dVar23) {
                uVar3 = (uint)dVar1;
                local_d8 = (double)(longlong)(int)uVar3;
              }
              else {
                uVar3 = 0x20;
              }
              local_e0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
              local_e8 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar22,(double)(float)(local_e0 - dVar21),dVar15,
                         (double)(float)(local_e8 - dVar21),dVar20,dVar19,
                         (double)*(float *)(psVar14 + 10),(double)FLOAT_80333048,&MenuPcs,
                         *(undefined4 *)(psVar14 + 0xc),&local_f8);
              uVar6 = uVar6 + 0x20;
            }
          }
          else {
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (dVar22,dVar18,dVar15,dVar17,dVar20,dVar19,(double)*(float *)(psVar14 + 10),
                       (double)FLOAT_80333048,&MenuPcs,*(undefined4 *)(psVar14 + 0xc),&local_f8);
          }
          dVar20 = (double)(float)(dVar20 + dVar15);
          dVar22 = (double)(float)(dVar15 * (double)*(float *)(psVar14 + 10) + dVar22);
        }
        if ((double)FLOAT_80333040 < dVar15) {
          local_d0 = (double)(CONCAT44(0x43300000,(int)psVar14[2]) ^ 0x80000000);
          if (dVar15 < (double)(float)(local_d0 - DOUBLE_80333078)) {
            local_f4 = 0xff;
            local_f3 = 0xff;
            local_f2 = 0xff;
            local_f1 = 0;
            local_ec = 0xff;
            local_eb = 0xff;
            local_ea = 0xff;
            local_e9 = 0;
            local_d0 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar14 + 0x14)) ^ 0x80000000);
            local_d8 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
            dVar15 = (double)((float)(DOUBLE_80333050 / (local_d0 - DOUBLE_80333078)) *
                             (float)(local_d8 - DOUBLE_80333078));
            if (*(int *)(psVar14 + 0xe) == 0x32) {
              uVar6 = (uint)dVar18;
              dVar18 = (double)(float)(dVar18 + dVar17);
              dVar21 = (double)FLOAT_80333044;
              dVar17 = DOUBLE_80333078;
              while (local_d0 = (double)(CONCAT44(0x43300000,uVar6) ^ 0x80000000),
                    (double)(float)(local_d0 - dVar17) < dVar18) {
                local_d0 = (double)(CONCAT44(0x43300000,uVar6) ^ 0x80000000);
                dVar16 = dVar18 - (double)(float)(local_d0 - dVar17);
                if ((double)(float)dVar16 < dVar21) {
                  uVar3 = (uint)dVar16;
                  local_d8 = (double)(longlong)(int)uVar3;
                }
                else {
                  uVar3 = 0x20;
                }
                local_e0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
                local_e8 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
                DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                          (dVar22,(double)(float)(local_e0 - dVar17),dVar15,
                           (double)(float)(local_e8 - dVar17),dVar20,dVar19,
                           (double)*(float *)(psVar14 + 10),(double)FLOAT_80333048,&MenuPcs,
                           *(undefined4 *)(psVar14 + 0xc),&local_f8);
                uVar6 = uVar6 + 0x20;
              }
            }
            else {
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar22,dVar18,dVar15,dVar17,dVar20,dVar19,(double)*(float *)(psVar14 + 10),
                         (double)FLOAT_80333048,&MenuPcs,*(undefined4 *)(psVar14 + 0xc),&local_f8);
            }
          }
        }
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      }
      else {
        dVar21 = (double)*(float *)(psVar14 + 8);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar14 + 0xe));
        local_d0 = (double)(longlong)(int)((double)FLOAT_80333058 * dVar21);
        local_f8 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333058 * dVar21));
        local_110 = local_f8;
        GXSetChanMatColor(4,&local_110);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar22,dVar18,dVar15,dVar17,dVar20,dVar19,(double)*(float *)(psVar14 + 10),
                   (double)*(float *)(psVar14 + 10),&MenuPcs,0);
      }
    }
    iVar9 = iVar9 + 1;
    psVar14 = psVar14 + 0x20;
  }
  iVar9 = 0;
  if (0 < iVar4) {
    do {
      psVar14 = (short *)((int)*(short **)&menuPcs->field_0x850 + iVar9 + 8);
      if (*(int *)(psVar14 + 0xe) == 0x37) break;
      iVar9 = iVar9 + 0x40;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  puVar12 = s_rank;
  dVar20 = (double)FLOAT_8033305c;
  iVar9 = 0;
  psVar7 = psVar14;
  puVar10 = puVar12;
  dVar15 = DOUBLE_80333060;
  dVar19 = DOUBLE_80333078;
  do {
    local_d8 = (double)CONCAT44(0x43300000,(int)psVar7[3] ^ 0x80000000);
    local_d0 = (double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000);
    local_e0 = (double)CONCAT44(0x43300000,(int)*psVar7 + psVar7[2] + 0x18 ^ 0x80000000);
    local_e8 = (double)(longlong)(int)(local_e0 - dVar19);
    iVar4 = (int)((double)(float)((double)(float)(local_d8 - dVar19) - dVar20) * dVar15 +
                 (double)(float)(local_d0 - dVar19));
    local_c8 = (double)(longlong)iVar4;
    DrawSingBar__8CMenuPcsFiiif
              ((double)*(float *)(psVar7 + 8),menuPcs,(int)(local_e0 - dVar19),iVar4,
               (int)*(short *)(puVar10 + 2));
    iVar9 = iVar9 + 1;
    puVar10 = puVar10 + 4;
    psVar7 = psVar7 + 0x20;
  } while (iVar9 < 8);
  dVar20 = (double)FLOAT_80333044;
  iVar9 = 0;
  puVar10 = puVar12;
  psVar7 = psVar14;
  dVar15 = DOUBLE_80333060;
  dVar19 = DOUBLE_80333078;
  do {
    local_d0 = (double)CONCAT44(0x43300000,(int)psVar7[3] ^ 0x80000000);
    local_c8 = (double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000);
    local_d8 = (double)CONCAT44(0x43300000,(int)*psVar7 + psVar7[2] + -0x10 ^ 0x80000000);
    local_e0 = (double)(longlong)(int)(local_d8 - dVar19);
    iVar4 = (int)((double)(float)((double)(float)(local_d0 - dVar19) - dVar20) * dVar15 +
                 (double)(float)(local_c8 - dVar19));
    local_e8 = (double)(longlong)iVar4;
    DrawSingleIcon__8CMenuPcsFiiifif
              ((double)*(float *)(psVar7 + 8),(double)FLOAT_80333048,menuPcs,(char)puVar10[1] + 0x14
               ,(int)(local_d8 - dVar19),iVar4,1);
    iVar9 = iVar9 + 1;
    puVar10 = puVar10 + 4;
    psVar7 = psVar7 + 0x20;
  } while (iVar9 < 8);
  pCVar11 = *(CFont **)&menuPcs->field_0xf8;
  SetShadow__5CFontFi(pCVar11,1);
  SetScale__5CFontFf(FLOAT_80333048,pCVar11);
  DrawInit__5CFontFv(pCVar11);
  memset(auStack_108,0,0x10);
  dVar20 = (double)FLOAT_80333058;
  dVar19 = (double)FLOAT_8033306c;
  iVar9 = 0;
  psVar7 = psVar14;
  pcVar13 = puVar12;
  dVar15 = DOUBLE_80333078;
  do {
    SetTlut__5CFontFi(pCVar11,6);
    local_c8 = (double)(longlong)(int)(dVar20 * (double)*(float *)(psVar7 + 8));
    puVar5 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_118,0xff,0xff,0xff,(int)(dVar20 * (double)*(float *)(psVar7 + 8)));
    local_114 = *puVar5;
    SetColor__5CFontF8_GXColor(pCVar11,&local_114);
    fVar2 = FLOAT_80333048;
    local_d0 = (double)(CONCAT44(0x43300000,*psVar7 + -0xc) ^ 0x80000000);
    dVar17 = (double)(float)(local_d0 - dVar15);
    local_d8 = (double)CONCAT44(0x43300000,(int)psVar7[1] + 10U ^ 0x80000000);
    pCVar11->renderFlags = pCVar11->renderFlags & 0xef | 0x10;
    dVar18 = (double)(float)(local_d8 - dVar15);
    SetMargin__5CFontFf(fVar2,pCVar11);
    sprintf(auStack_108,&DAT_80333068,(int)*pcVar13);
    SetPosX__5CFontFf((float)dVar17,pCVar11);
    SetPosY__5CFontFf((float)(dVar18 - dVar19),pCVar11);
    Draw__5CFontFPc(pCVar11,auStack_108);
    SetShadow__5CFontFi(pCVar11,0);
    iVar9 = iVar9 + 1;
    pcVar13 = pcVar13 + 4;
    psVar7 = psVar7 + 0x20;
  } while (iVar9 < 8);
  pCVar11 = *(CFont **)&menuPcs->field_0x108;
  SetShadow__5CFontFi(pCVar11,0);
  SetScale__5CFontFf(FLOAT_80333070,pCVar11);
  SetMargin__5CFontFf(FLOAT_80333048,pCVar11);
  DrawInit__5CFontFv(pCVar11);
  memset(auStack_108,0,0x10);
  dVar20 = (double)FLOAT_80333058;
  dVar19 = (double)FLOAT_8033306c;
  iVar9 = 0;
  dVar15 = DOUBLE_80333078;
  do {
    local_c8 = (double)(longlong)(int)(dVar20 * (double)*(float *)(psVar14 + 8));
    puVar5 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_120,0xff,0xff,0xff,(int)(dVar20 * (double)*(float *)(psVar14 + 8)));
    local_11c = *puVar5;
    SetColor__5CFontF8_GXColor(pCVar11,&local_11c);
    local_d0 = (double)(CONCAT44(0x43300000,psVar14[1] + 0xb) ^ 0x80000000);
    dVar17 = (double)(float)(local_d0 - dVar15);
    local_d8 = (double)CONCAT44(0x43300000,(int)*psVar14 + 0x1cU ^ 0x80000000);
    iVar8 = Game.game.m_cFlatDataArr[1].m_table[0].index[((char)puVar12[1] + 0x17d) * 5 + 4];
    SetPosX__5CFontFf((float)(local_d8 - dVar15),pCVar11);
    SetPosY__5CFontFf((float)(dVar17 - dVar19),pCVar11);
    Draw__5CFontFPc(pCVar11,iVar8);
    iVar9 = iVar9 + 1;
    puVar12 = puVar12 + 4;
    psVar14 = psVar14 + 0x20;
  } while (iVar9 < 8);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

