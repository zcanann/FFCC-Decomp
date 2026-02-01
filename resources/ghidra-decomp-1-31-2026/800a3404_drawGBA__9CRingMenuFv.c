// Function: drawGBA__9CRingMenuFv
// Entry: 800a3404
// Size: 1472 bytes

/* WARNING: Removing unreachable block (ram,0x800a39a8) */
/* WARNING: Removing unreachable block (ram,0x800a39a0) */
/* WARNING: Removing unreachable block (ram,0x800a3998) */
/* WARNING: Removing unreachable block (ram,0x800a3990) */
/* WARNING: Removing unreachable block (ram,0x800a3988) */
/* WARNING: Removing unreachable block (ram,0x800a3980) */
/* WARNING: Removing unreachable block (ram,0x800a3978) */
/* WARNING: Removing unreachable block (ram,0x800a3970) */
/* WARNING: Removing unreachable block (ram,0x800a3968) */
/* WARNING: Removing unreachable block (ram,0x800a3454) */
/* WARNING: Removing unreachable block (ram,0x800a344c) */
/* WARNING: Removing unreachable block (ram,0x800a3444) */
/* WARNING: Removing unreachable block (ram,0x800a343c) */
/* WARNING: Removing unreachable block (ram,0x800a3434) */
/* WARNING: Removing unreachable block (ram,0x800a342c) */
/* WARNING: Removing unreachable block (ram,0x800a3424) */
/* WARNING: Removing unreachable block (ram,0x800a341c) */
/* WARNING: Removing unreachable block (ram,0x800a3414) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawGBA__9CRingMenuFv(CRingMenu *ringMenu)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined auStack_f0 [4];
  undefined auStack_ec [4];
  undefined auStack_e8 [8];
  undefined4 local_e0;
  uint uStack_dc;
  undefined4 local_d8;
  uint uStack_d4;
  undefined4 local_d0;
  uint uStack_cc;
  undefined4 local_c8;
  uint uStack_c4;
  longlong local_c0;
  undefined4 local_b8;
  uint uStack_b4;
  longlong local_b0;
  undefined4 local_a8;
  uint uStack_a4;
  
  if (((Game.game.m_gameWork.m_menuStageMode == '\0') || (ringMenu->menuIndex < 1)) &&
     (Game.game.m_scriptFoodBase[ringMenu->menuIndex] != 0)) {
    uStack_dc = ringMenu->displayCounter ^ 0x80000000;
    local_e0 = 0x43300000;
    dVar11 = (double)((float)((double)CONCAT44(0x43300000,uStack_dc) - DOUBLE_80330a00) *
                     FLOAT_80330a08);
    if (ringMenu->animDirection != 0) {
      dVar11 = (double)(float)((double)FLOAT_803309cc - dVar11);
    }
    if ((double)FLOAT_803309c0 != dVar11) {
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x16);
      local_e0 = 0x43300000;
      uStack_dc = ringMenu->gbaAnimCounter ^ 0x80000000;
      dVar6 = (double)sin((double)((FLOAT_80330a0c *
                                   (float)((double)CONCAT44(0x43300000,uStack_dc) - DOUBLE_80330a00)
                                   ) / FLOAT_80330a10));
      dVar6 = (double)(float)dVar6;
      if (ringMenu->gbaConnectedFlag == 1) {
        dVar6 = (double)(float)((double)FLOAT_803309cc - dVar6);
      }
      uStack_d4 = 0x30;
      if ((ringMenu->menuIndex & 1U) != 0) {
        uStack_d4 = 0x250;
      }
      uStack_d4 = uStack_d4 ^ 0x80000000;
      uStack_cc = 0x30;
      local_d8 = 0x43300000;
      dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_d4) - DOUBLE_80330a00);
      if ((ringMenu->menuIndex & 2U) != 0) {
        uStack_cc = 400;
      }
      uStack_cc = uStack_cc ^ 0x80000000;
      local_d0 = 0x43300000;
      dVar9 = (double)(float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80330a00);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      dVar7 = (double)FLOAT_803309cc;
      uStack_c4 = ringMenu->commonFrameCounter ^ 0x80000000;
      local_c8 = 0x43300000;
      dVar8 = (double)(float)((double)FLOAT_80330a14 * (double)(float)(dVar7 - dVar6) + dVar7);
      dVar7 = (double)fmod((double)(float)((double)FLOAT_80330a18 *
                                          (double)(float)((double)CONCAT44(0x43300000,uStack_c4) -
                                                         DOUBLE_80330a00)),DOUBLE_80330a20,
                           (double)FLOAT_80330a18,dVar7,(double)FLOAT_80330a14);
      fVar2 = (float)dVar7;
      if (FLOAT_803309cc < fVar2) {
        fVar2 = FLOAT_80330a28 - fVar2;
      }
      dVar12 = (double)(FLOAT_80330a2c * fVar2);
      dVar7 = (double)sin(dVar12);
      dVar13 = (double)(float)dVar7;
      dVar7 = (double)sin((double)(float)((double)FLOAT_80330a30 + dVar12));
      dVar12 = (double)(float)dVar7;
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
      dVar7 = (double)(float)((double)FLOAT_80330a34 * dVar6);
      iVar1 = (int)((double)(float)((double)FLOAT_803309c4 * dVar7) * dVar11);
      local_c0 = (longlong)iVar1;
      uVar3 = __ct__6CColorFUcUcUcUc(auStack_e8,0,0,0,iVar1);
      SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar3);
      dVar6 = (double)(float)((double)FLOAT_803309cc - dVar8);
      local_b8 = 0x43300000;
      dVar10 = (double)(float)(dVar10 + (double)(FLOAT_80330a3c * (float)(dVar8 * dVar12)));
      dVar9 = (double)(float)(dVar9 - (double)(FLOAT_80330a40 * (float)(dVar8 * dVar13)));
      uStack_b4 = ringMenu->menuIndex * 0x30 ^ 0x80000000;
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)((double)FLOAT_80330a38 + dVar10),
                 (double)(float)((double)FLOAT_80330a38 + dVar9),(double)FLOAT_80330a44,
                 (double)FLOAT_80330a48,(double)FLOAT_803309c0,
                 (double)(float)((double)CONCAT44(0x43300000,uStack_b4) - DOUBLE_80330a00),
                 (double)(FLOAT_80330a4c * (float)((double)FLOAT_803309cc + dVar6)),
                 (double)(FLOAT_80330a4c * (float)(dVar8 + dVar6)),&MenuPcs,3);
      dVar6 = (double)(float)(dVar7 * dVar11);
      iVar1 = (int)(dVar7 * dVar11);
      local_b0 = (longlong)iVar1;
      uVar3 = __ct__6CColorFUcUcUcUc(auStack_ec,0xff,0xff,0xff,iVar1);
      SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar3);
      local_a8 = 0x43300000;
      uStack_a4 = ringMenu->menuIndex * 0x30 ^ 0x80000000;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar10,dVar9,(double)FLOAT_80330a44,(double)FLOAT_80330a48,(double)FLOAT_803309c0,
                 (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330a00),
                 (double)(float)((double)FLOAT_80330a4c * dVar8),
                 (double)(float)((double)FLOAT_80330a4c * dVar8),&MenuPcs,3);
      if (((CFlat._4768_4_ & CFlat._4772_4_ & 8) != 0) &&
         (cVar4 = GetGBAStart__6JoyBusFi(&Joybus,ringMenu->menuIndex), cVar4 == '\0')) {
        cVar4 = IsInitSend__6JoyBusFi(&Joybus,ringMenu->menuIndex);
        if (cVar4 == '\0') {
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1d);
          local_a8 = 0x43300000;
          uStack_a4 = ringMenu->commonFrameCounter ^ 0x80000000;
          dVar11 = (double)sin((double)(FLOAT_80330a54 *
                                       (float)((double)CONCAT44(0x43300000,uStack_a4) -
                                              DOUBLE_80330a00)));
          uVar5 = (uint)(FLOAT_803309c4 * (float)(dVar6 * (double)(FLOAT_803309cc + (float)dVar11)))
          ;
          local_b0 = (longlong)(int)uVar5;
          uVar3 = __ct__6CColorFUcUcUcUc(auStack_f0,0xff,0xff,0xff,uVar5 & 0xff);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar3);
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar10,dVar9,(double)FLOAT_80330a48,(double)FLOAT_80330a48,
                     (double)FLOAT_803309c0,(double)FLOAT_80330a58,(double)FLOAT_803309cc,
                     (double)FLOAT_803309cc,&MenuPcs,3);
        }
        else {
          iVar1 = (int)System.m_frameCounter >> 0x1f;
          uVar5 = (iVar1 * 0x10 |
                  (uint)(((int)System.m_frameCounter >> 1) * 0x10000000 + iVar1) >> 0x1c) - iVar1;
          if (3 < (int)uVar5) {
            uVar5 = uVar5 & 1;
          }
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1d);
          uStack_a4 = uVar5 * 0x30 ^ 0x80000000;
          local_a8 = 0x43300000;
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar10,dVar9,(double)FLOAT_80330a48,(double)FLOAT_80330a48,
                     (double)FLOAT_803309c0,
                     (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330a00),
                     (double)FLOAT_803309cc,(double)FLOAT_803309cc,&MenuPcs,3);
        }
      }
      DrawInit__8CMenuPcsFv(&MenuPcs);
    }
  }
  return;
}

