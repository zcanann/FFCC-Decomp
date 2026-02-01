// Function: LetterMessDraw__8CMenuPcsFv
// Entry: 80164ee0
// Size: 1652 bytes

/* WARNING: Removing unreachable block (ram,0x80165538) */
/* WARNING: Removing unreachable block (ram,0x80165530) */
/* WARNING: Removing unreachable block (ram,0x80165528) */
/* WARNING: Removing unreachable block (ram,0x80165520) */
/* WARNING: Removing unreachable block (ram,0x80165518) */
/* WARNING: Removing unreachable block (ram,0x80165510) */
/* WARNING: Removing unreachable block (ram,0x80164f18) */
/* WARNING: Removing unreachable block (ram,0x80164f10) */
/* WARNING: Removing unreachable block (ram,0x80164f08) */
/* WARNING: Removing unreachable block (ram,0x80164f00) */
/* WARNING: Removing unreachable block (ram,0x80164ef8) */
/* WARNING: Removing unreachable block (ram,0x80164ef0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LetterMessDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  undefined4 *puVar3;
  void *ptr;
  undefined *ptr_00;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  undefined *puVar7;
  int iVar8;
  short *psVar9;
  short *psVar10;
  int iVar11;
  CFont *font;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_c0;
  uint uStack_bc;
  undefined4 local_b8;
  uint uStack_b4;
  undefined8 local_b0;
  undefined8 local_a8;
  double local_a0;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar2 = Game.game.m_scriptFoodBase[0];
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x32);
  psVar9 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  for (iVar11 = 0; psVar10 = *(short **)&menuPcs->field_0x850, iVar11 < *psVar10;
      iVar11 = iVar11 + 1) {
    if (-1 < *(int *)(psVar9 + 0xe)) {
      uStack_bc = (int)*psVar9 ^ 0x80000000;
      uStack_b4 = (int)psVar9[1] ^ 0x80000000;
      local_a0 = (double)(longlong)(int)(FLOAT_803330a0 * *(float *)(psVar9 + 8));
      dVar17 = (double)*(float *)(psVar9 + 4);
      local_c0 = 0x43300000;
      dVar12 = (double)*(float *)(psVar9 + 6);
      dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_803330c8);
      local_b8 = 0x43300000;
      dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_b4) - DOUBLE_803330c8);
      local_b0 = (double)CONCAT44(0x43300000,(int)psVar9[2] ^ 0x80000000);
      dVar15 = (double)(float)(local_b0 - DOUBLE_803330c8);
      local_a8 = (double)CONCAT44(0x43300000,(int)psVar9[3] ^ 0x80000000);
      dVar14 = (double)(float)(local_a8 - DOUBLE_803330c8);
      local_d4 = CONCAT31(0xffffff,(char)(int)(FLOAT_803330a0 * *(float *)(psVar9 + 8)));
      local_d8 = local_d4;
      GXSetChanMatColor(DOUBLE_803330c8,4,&local_d8);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar9 + 0xe));
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar16,dVar13,dVar15,dVar14,dVar17,dVar12,(double)*(float *)(psVar9 + 10),
                 (double)*(float *)(psVar9 + 10),&MenuPcs,0);
    }
    psVar9 = psVar9 + 0x20;
  }
  font = *(CFont **)&menuPcs->field_0xf8;
  SetShadow__5CFontFi(font,0);
  SetMargin__5CFontFf(FLOAT_8033313c,font);
  SetScale__5CFontFf(FLOAT_80333140,font);
  DrawInit__5CFontFv(font);
  SetTlut__5CFontFi(font,0x1c);
  local_a0 = (double)(longlong)(int)(FLOAT_803330a0 * *(float *)(psVar10 + 0xc));
  puVar3 = (undefined4 *)
           __ct__6CColorFUcUcUcUc
                     (auStack_e0,0xff,0xff,0xff,(int)(FLOAT_803330a0 * *(float *)(psVar10 + 0xc)));
  local_dc = *puVar3;
  SetColor__5CFontF8_GXColor(font,&local_dc);
  uVar6 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar6 = MenuPcs._244_4_;
  }
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uVar6,s_menu_letter_cpp_801dedf8,0x535);
  uVar6 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar6 = MenuPcs._244_4_;
  }
  ptr_00 = (undefined *)
           __nwa__FUlPQ27CMemory6CStagePci(0x400,uVar6,s_menu_letter_cpp_801dedf8,0x537);
  memset(ptr,0,0x400);
  memset(ptr_00,0,0x400);
  strcpy(ptr,*(undefined4 *)
              ((int)Game.game.m_cFlatDataArr[1].m_mesPtr +
              (*(ushort *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) & 0x7fc) * 2 + 0x40));
  MakeAgbString__4CMesFPcPcii(ptr_00,ptr,*(undefined2 *)(uVar2 + 0x3e2),0);
  dVar17 = (double)FLOAT_80333144;
  iVar11 = 0;
  iVar8 = 0x58;
  puVar7 = ptr_00;
  dVar12 = DOUBLE_803330c8;
  do {
    puVar4 = (undefined *)strchr(puVar7,10);
    local_a0 = (double)(CONCAT44(0x43300000,iVar8) ^ 0x80000000);
    dVar14 = (double)(float)(local_a0 - dVar12);
    if (puVar4 != (undefined *)0x0) {
      *puVar4 = 0;
    }
    iVar5 = strlen(puVar7);
    if (iVar5 != 0) {
      SetPosX__5CFontFf(FLOAT_80333144,font);
      SetPosY__5CFontFf((float)(dVar14 - (double)FLOAT_80333148),font);
      Draw__5CFontFPc(font,puVar7);
    }
    if (puVar4 == (undefined *)0x0) break;
    iVar11 = iVar11 + 1;
    puVar7 = puVar4 + 1;
    iVar8 = iVar8 + 0x20;
  } while (iVar11 < 7);
  __dla__FPv(ptr);
  __dla__FPv(ptr_00);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar11 = uVar2 + DAT_8032eee8 * 0xc;
  if ((*(ushort *)(iVar11 + 0x3ee) & 0x1ff) != 0) {
    dVar17 = (double)FLOAT_8033314c;
    dVar14 = (double)FLOAT_80333150;
    local_a0 = (double)(longlong)(int)FLOAT_8033314c;
    local_a8 = (double)(longlong)(int)FLOAT_80333150;
    DrawSingleIcon__8CMenuPcsFiiifif
              ((double)*(float *)(psVar10 + 0xc),(double)FLOAT_80333154,menuPcs,
               0x26 - ((int)-(*(byte *)(iVar11 + 0x3ec) >> 6 & 1) >> 0x1f),(int)FLOAT_8033314c,
               (int)FLOAT_80333150,1);
  }
  if (1 < sVar1) {
    DrawSingWin__8CMenuPcsFs(menuPcs,0xffff);
    if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1) &&
       (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1)) {
      iVar11 = (int)*(char *)(*(int *)&menuPcs->field_0x82c + 9);
      if (sVar1 == 4) {
        DrawSingWinMess__8CMenuPcsFiii(menuPcs,2,iVar11,0);
      }
      else {
        DrawSingWinMess__8CMenuPcsFiii(menuPcs,0,iVar11,1);
      }
      if ((sVar1 == 2) || (sVar1 == 5)) {
        iVar11 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
        local_a0 = (double)(CONCAT44(0x43300000,**(short **)&menuPcs->field_0x848 + 0x14) ^
                           0x80000000);
        dVar17 = (double)(float)(local_a0 - DOUBLE_803330c8);
        if (sVar1 == 2) {
          iVar11 = iVar11 + 1;
        }
        else {
          iVar11 = iVar11 + ((int)~((int)DAT_8032eeed - 2U | 2U - (int)DAT_8032eeed) >> 0x1f) + 4;
        }
        iVar8 = SingWinMessHeight__8CMenuPcsFv(menuPcs);
        local_a0 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                                     iVar11 * iVar8 + 0x20) ^ 0x80000000);
        dVar14 = (double)(float)(local_a0 - DOUBLE_803330c8);
      }
      else if ((sVar1 == 3) || (sVar1 == 4)) {
        local_a0 = (double)(CONCAT44(0x43300000,**(short **)&menuPcs->field_0x848 + -8) ^ 0x80000000
                           );
        dVar17 = (double)(float)(local_a0 - DOUBLE_803330c8);
        if (sVar1 == 4) {
          dVar17 = (double)(float)(dVar17 + (double)FLOAT_80333110);
        }
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
        iVar11 = SingWinMessHeight__8CMenuPcsFv(menuPcs);
        local_a8 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                                     sVar1 * iVar11 + 0x20) ^ 0x80000000);
        dVar14 = (double)(float)(local_a8 - DOUBLE_803330c8);
      }
      local_b0 = (double)(longlong)(int)dVar14;
      iVar11 = (int)System.m_frameCounter >> 0x1f;
      local_a0 = (double)(CONCAT44(0x43300000,
                                   (iVar11 * 8 | System.m_frameCounter * 0x20000000 + iVar11 >> 0x1d
                                   ) - iVar11) ^ 0x80000000);
      iVar11 = (int)(dVar17 + (double)(float)(local_a0 - DOUBLE_803330c8));
      local_a8 = (double)(longlong)iVar11;
      DrawCursor__8CMenuPcsFiif((double)FLOAT_803330f8,menuPcs,iVar11,(int)dVar14);
    }
  }
  return;
}

