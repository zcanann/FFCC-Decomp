// Function: DrawIcon__9CRingMenuFv
// Entry: 800a2dd4
// Size: 1388 bytes

/* WARNING: Removing unreachable block (ram,0x800a3318) */
/* WARNING: Removing unreachable block (ram,0x800a3310) */
/* WARNING: Removing unreachable block (ram,0x800a3308) */
/* WARNING: Removing unreachable block (ram,0x800a2df4) */
/* WARNING: Removing unreachable block (ram,0x800a2dec) */
/* WARNING: Removing unreachable block (ram,0x800a2de4) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawIcon__9CRingMenuFv(CRingMenu *ringMenu)

{
  undefined uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  Vec *vecA;
  undefined4 uVar5;
  uint uVar6;
  CGPartyObj *pCVar7;
  uint32_t uVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  undefined auStack_120 [4];
  undefined auStack_11c [4];
  undefined auStack_118 [4];
  Vec local_114;
  CVector CStack_108;
  CVector CStack_fc;
  Vec local_f0;
  Vec4d local_e4;
  Vec VStack_d4;
  Mat4x4 MStack_c8;
  Mtx MStack_88;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  drawGBA__9CRingMenuFv(ringMenu);
  if (((Game.game.m_gameWork.m_menuStageMode == '\0') || (ringMenu->menuIndex < 2)) &&
     ((CFlat._4768_4_ & CFlat._4772_4_ & 1) != 0)) {
    pCVar7 = Game.game.m_partyObjArr[ringMenu->menuIndex];
    if ((pCVar7 != (CGPartyObj *)0x0) &&
       ((int)((uint)*(byte *)((int)&(pCVar7->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1) <<
             0x18) < 0)) {
      uVar8 = Game.game.m_scriptFoodBase[ringMenu->menuIndex];
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_88);
      __ct__7CVectorFfff(FLOAT_803309c0,
                         FLOAT_803309c4 * (pCVar7->gCharaObj).gPrgObj.object.unk_0x188,
                         FLOAT_803309c0,&CStack_108);
      vecA = (Vec *)__ct__7CVectorFRC3Vec
                              (&CStack_fc,&(pCVar7->gCharaObj).gPrgObj.object.m_worldPosition);
      __ct__7CVectorFv(&local_114);
      PSVECAdd(vecA,(Vec *)&CStack_108,&local_114);
      local_f0.x = local_114.x;
      local_f0.y = local_114.y;
      local_f0.z = local_114.z;
      PSMTXMultVec(&MStack_88,&local_f0,&VStack_d4);
      fVar2 = FLOAT_803309c8;
      if (VStack_d4.z < FLOAT_803309c8) {
        fVar2 = VStack_d4.z;
      }
      VStack_d4.z = fVar2;
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_c8);
      MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(&Math,&MStack_c8,&VStack_d4,&local_e4);
      fVar2 = local_e4.x * (FLOAT_803309cc / local_e4.w);
      fVar3 = local_e4.y * (FLOAT_803309cc / local_e4.w);
      if (((fVar2 <= FLOAT_803309d0) || (FLOAT_803309cc <= fVar2)) ||
         ((fVar3 <= FLOAT_803309d0 || (FLOAT_803309cc <= fVar3)))) {
        local_e4.x = FLOAT_803309d4;
        if ((FLOAT_803309d4 <= fVar2) && (local_e4.x = fVar2, FLOAT_803309d8 < fVar2)) {
          local_e4.x = FLOAT_803309d8;
        }
        local_e4.y = FLOAT_803309dc;
        if ((FLOAT_803309dc <= fVar3) && (local_e4.y = fVar3, FLOAT_803309e0 < fVar3)) {
          local_e4.y = FLOAT_803309e0;
        }
        atan2((double)local_e4.x,(double)local_e4.y);
        iVar4 = (int)System.m_frameCounter >> 0x1f;
        dVar11 = (double)(FLOAT_803309e4 * local_e4.x + FLOAT_803309e4);
        uVar1 = (&DAT_8020fab8)
                [(iVar4 * 0x10 | System.m_frameCounter * 0x10000000 + iVar4 >> 0x1c) - iVar4];
        dVar10 = -(double)(FLOAT_803309e8 * local_e4.y - FLOAT_803309e8);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x19);
        if ((Game.game.m_gameWork.m_menuStageMode == '\0') || (ringMenu->menuIndex < 1)) {
          iVar9 = *(int *)(uVar8 + 0x3b4);
          iVar4 = *(ushort *)(uVar8 + 0x14) - 100;
          iVar4 = iVar4 / 100 + (iVar4 >> 0x1f);
          uVar6 = (uint)*(ushort *)(uVar8 + 0x14) % 100 + (iVar4 - (iVar4 >> 0x1f)) * 4;
        }
        else {
          iVar9 = 1;
          uVar6 = 0x65;
        }
        uVar5 = __ct__6CColorFUcUcUcUc(auStack_118,0,0,0,0x80);
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar5);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)((double)FLOAT_803309ec + dVar11),
                   (double)(float)((double)FLOAT_803309ec + dVar10),(double)FLOAT_803309f0,
                   (double)FLOAT_803309f0,(double)FLOAT_803309c0,(double)FLOAT_803309c0,
                   (double)FLOAT_803309cc,(double)FLOAT_803309cc,&MenuPcs,3);
        uVar5 = __ct__6CColorFUcUcUcUc(auStack_11c,0xff,0xff,0xff,0xff);
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar5);
        uStack_54 = iVar9 * 0x38 ^ 0x80000000;
        local_58 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar11,dVar10,(double)FLOAT_803309f0,(double)FLOAT_803309f0,
                   (double)FLOAT_803309c0,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330a00),
                   (double)FLOAT_803309cc,(double)FLOAT_803309cc,&MenuPcs,3);
        iVar4 = (int)uVar6 >> 0x1f;
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x18);
        uVar5 = 0x802ea500;
        if (*(short *)(uVar8 + 0x1c) != 0) {
          uVar5 = 0;
        }
        SetExternalTlut__8CTextureFPvi((CTexture *)MenuPcs._492_4_,uVar5,1);
        GXSetTevDirect(2);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (2,0xf,0,0xc,0xb);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (2,7,0,6,7);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,3,1,0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,0,1,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
        uVar5 = __ct__6CColorFUcUcUcUc(auStack_120,0xff,0xff,0xff,uVar1);
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar5);
        uStack_4c = ((iVar4 * 8 | uVar6 * 0x20000000 + iVar4 >> 0x1d) - iVar4) * 0x30 ^ 0x80000000;
        uStack_44 = (((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0)) * 0x30 ^
                    0x80000000;
        local_50 = 0x43300000;
        local_48 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar11,dVar10,(double)FLOAT_803309f4,(double)FLOAT_803309f4,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330a00),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330a00),
                   (double)FLOAT_803309f8,(double)FLOAT_803309f8,&MenuPcs,3);
      }
    }
  }
  return;
}

