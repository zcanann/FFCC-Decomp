// Function: DrawItemList__9CShopMenuFv
// Entry: 80151f98
// Size: 1324 bytes

/* WARNING: Removing unreachable block (ram,0x801524a8) */
/* WARNING: Removing unreachable block (ram,0x80151fa8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawItemList__9CShopMenuFv(CShopMenu *shopMenu)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char cVar8;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  int32_t iVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  void **ppvVar15;
  int iVar16;
  double dVar17;
  undefined auStack_68 [4];
  undefined4 local_64;
  double local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  iVar13 = 0x4c;
  uVar10 = 10;
  iVar12 = *(int *)&shopMenu->field_0x24;
  if (*(int *)&shopMenu->field_0x14 == 2) {
    uVar10 = 0xf;
  }
  iVar16 = iVar12 << 1;
  ppvVar15 = &(shopMenu->field0_0x0).ref.vtable + iVar12;
  for (iVar14 = 0; iVar14 < *(int *)&shopMenu->field_0x2c; iVar14 = iVar14 + 1) {
    iVar2 = *(int *)&shopMenu->field_0x14;
    if (iVar2 == 0) {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe4);
    }
    else if (iVar2 == 1) {
      iVar4 = 0x40;
    }
    else if (iVar2 == 2) {
      iVar4 = *(int *)&shopMenu->field_0x4c;
    }
    else {
      iVar4 = -1;
    }
    if (iVar4 <= iVar12) break;
    if (iVar2 == 0) {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar16 + 0xbe6);
    }
    else if (iVar2 == 1) {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar16 + 0xb6);
    }
    else if (iVar2 == 2) {
      if (ppvVar15[0x14] == (void *)0xffffffff) {
        iVar4 = -1;
      }
      else {
        iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + (int)ppvVar15[0x14] * 2 + 0xb6);
      }
    }
    else {
      iVar4 = -1;
    }
    if (iVar12 == -1) {
      bVar1 = false;
    }
    else {
      if (iVar2 == 0) {
        iVar11 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar16 + 0xbe6);
      }
      else if (iVar2 == 1) {
        iVar11 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar16 + 0xb6);
      }
      else if (iVar2 == 2) {
        if (ppvVar15[0x14] == (void *)0xffffffff) {
          iVar11 = -1;
        }
        else {
          iVar11 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + (int)ppvVar15[0x14] * 2 + 0xb6);
        }
      }
      else {
        iVar11 = -1;
      }
      if (iVar11 < 1) {
        bVar1 = false;
      }
      else if (iVar2 == 0) {
        bVar1 = true;
      }
      else if (iVar2 == 2) {
        bVar1 = true;
        if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar11 - 0x191U) >> 5) * 4 + 0xc08) &
            1 << (iVar11 - 0x191U & 0x1f)) == 0) {
          bVar1 = false;
        }
      }
      else {
        cVar8 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar12);
        if (cVar8 == '\0') {
          if (iVar11 < 0x9f) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
        }
        else {
          bVar1 = false;
        }
      }
    }
    uVar5 = 0xe;
    if (bVar1) {
      uVar5 = uVar10;
    }
    if (*(int *)&shopMenu->field_0x28 == iVar12) {
      iVar2 = 0x198;
      drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,uVar5,1,0x198,iVar13 + -4,0xff,0,0,0);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      if (*(int *)&shopMenu->field_0x10 == 0) {
        iVar11 = (int)System.m_frameCounter >> 0x1f;
        DrawCursor__8CMenuPcsFiif
                  ((double)FLOAT_80332d28,&MenuPcs,
                   ((iVar11 * 8 | System.m_frameCounter * 0x20000000 + iVar11 >> 0x1d) - iVar11) +
                   0x114,iVar13 + -0x14);
      }
      else if ((System.m_frameCounter & 1) == 0) {
        DrawCursor__8CMenuPcsFiif((double)FLOAT_80332d28,&MenuPcs,0x114,iVar13 + -0x14);
      }
    }
    else {
      iVar2 = 0x1b8;
      drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,uVar5,0,0x1b8,iVar13,0xff,0,0,0);
    }
    uVar5 = MenuPcs._264_4_;
    if (0 < iVar4) {
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._264_4_);
      SetShadow__5CFontFi((CFont *)uVar5,0);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar5);
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_68,0xff,0xff,0xff,0xff);
      local_64 = *puVar6;
      SetColor__5CFontF8_GXColor((CFont *)uVar5,&local_64);
      DrawInit__5CFontFv((CFont *)uVar5);
      local_60 = (double)(CONCAT44(0x43300000,iVar2 + -0x54) ^ 0x80000000);
      SetPosX__5CFontFf((float)(local_60 - DOUBLE_80332d20),(CFont *)uVar5);
      uStack_54 = iVar13 - 0x14U ^ 0x80000000;
      local_58 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20),
                        (CFont *)uVar5);
      if (iVar4 < 1) {
        iVar9 = 0;
      }
      else {
        iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar4 * 5 + 4];
      }
      Draw__5CFontFPc((CFont *)uVar5,iVar9);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)FLOAT_80332d28,(double)FLOAT_80332d28,&MenuPcs,iVar4,iVar2 + 0x54,
                 iVar13 + -0x18,0);
    }
    iVar16 = iVar16 + 2;
    ppvVar15 = ppvVar15 + 1;
    iVar12 = iVar12 + 1;
    iVar13 = iVar13 + 0x1c;
  }
  local_58 = 0x43300000;
  local_50 = 0x43300000;
  iVar12 = (int)System.m_frameCounter / 0x14 + ((int)System.m_frameCounter >> 0x1f);
  uVar7 = (System.m_frameCounter + (iVar12 - (iVar12 >> 0x1f)) * -0x14) - 10;
  uVar3 = (int)uVar7 >> 0x1f;
  uStack_54 = (uVar3 ^ uVar7) - uVar3 ^ 0x80000000;
  iVar12 = (int)(DOUBLE_80332da0 *
                (DOUBLE_80332db0 * ((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20) +
                DOUBLE_80332da8));
  local_60 = (double)(longlong)iVar12;
  dVar17 = (double)(float)(DOUBLE_80332da8 *
                          (DOUBLE_80332dc0 *
                           ((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20) +
                          DOUBLE_80332db8));
  uStack_4c = uStack_54;
  if (*(int *)&shopMenu->field_0x30 != 0) {
    drawShapeSeqScale__FiiiiffUc(dVar17,-dVar17,2,0,0x24e,0x6a,iVar12);
  }
  if (*(int *)&shopMenu->field_0x34 != 0) {
    drawShapeSeqScale__FiiiiffUc(dVar17,dVar17,2,0,0x24e,0xec,iVar12);
  }
  return;
}

