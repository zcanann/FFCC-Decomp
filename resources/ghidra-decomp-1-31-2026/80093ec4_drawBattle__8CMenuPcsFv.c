// Function: drawBattle__8CMenuPcsFv
// Entry: 80093ec4
// Size: 1864 bytes

/* WARNING: Removing unreachable block (ram,0x800945e4) */
/* WARNING: Removing unreachable block (ram,0x800945dc) */
/* WARNING: Removing unreachable block (ram,0x800945d4) */
/* WARNING: Removing unreachable block (ram,0x800945cc) */
/* WARNING: Removing unreachable block (ram,0x800945c4) */
/* WARNING: Removing unreachable block (ram,0x80093ef4) */
/* WARNING: Removing unreachable block (ram,0x80093eec) */
/* WARNING: Removing unreachable block (ram,0x80093ee4) */
/* WARNING: Removing unreachable block (ram,0x80093edc) */
/* WARNING: Removing unreachable block (ram,0x80093ed4) */

void drawBattle__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  CMenuPcs *pCVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  Vec4d local_1f8;
  Mtx MStack_1e8;
  Mtx MStack_1b8;
  Mtx MStack_188;
  Mat4x4 MStack_158;
  Mat4x4 MStack_118;
  Mtx MStack_d8;
  undefined4 local_a8;
  uint uStack_a4;
  undefined8 local_a0;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined8 local_80;
  undefined4 local_78;
  uint uStack_74;
  undefined8 local_70;
  
  bVar1 = *(int *)&menuPcs->field_0x48 != 0;
  if (bVar1) {
    local_a8 = 0x43300000;
    uStack_a4 = *(uint *)&menuPcs->field_0x58 ^ 0x80000000;
    dVar11 = (double)((float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330838) *
                     FLOAT_80330804);
    if (bVar1) {
      dVar11 = (double)(float)((double)FLOAT_80330808 - dVar11);
    }
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_d8);
    PSMTXCopy(&MStack_d8,(Mtx *)&MStack_118);
    MStack_118.value[3][2] = FLOAT_8033080c;
    MStack_118.value[3][1] = FLOAT_8033080c;
    MStack_118.value[3][0] = FLOAT_8033080c;
    MStack_118.value[3][3] = FLOAT_80330808;
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_158);
    PSMTX44Concat(&MStack_158,&MStack_118,&MStack_158);
    MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d
              (&Math,&MStack_158,(Vec *)&menuPcs->field_0x4c,&local_1f8);
    if (FLOAT_8033080c < local_1f8.w) {
      local_a8 = 0x43300000;
      uStack_a4 = *(uint *)&menuPcs->field_0x60 ^ 0x80000000;
      uVar3 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330838) *
                    dVar11);
      dVar9 = (double)(FLOAT_80330810 + (FLOAT_80330810 * local_1f8.x) / local_1f8.w);
      uStack_94 = (int)uVar3 / 2;
      dVar8 = (double)(FLOAT_80330814 - (FLOAT_80330814 * local_1f8.y) / local_1f8.w);
      if ((double)(float)((double)CONCAT44(0x43300000,uStack_94 ^ 0x80000000) - DOUBLE_80330838) <=
          dVar9) {
        uVar6 = 0x280 - uStack_94 ^ 0x80000000;
        if ((double)(float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80330838) < dVar9) {
          local_a0 = (double)CONCAT44(0x43300000,uVar6);
          dVar9 = (double)(float)(local_a0 - DOUBLE_80330838);
        }
      }
      else {
        dVar9 = (double)(float)((double)CONCAT44(0x43300000,uStack_94 ^ 0x80000000) -
                               DOUBLE_80330838);
      }
      dVar13 = (double)FLOAT_80330818;
      if ((dVar13 <= dVar8) && (dVar13 = dVar8, (double)FLOAT_8033081c < dVar8)) {
        dVar13 = (double)FLOAT_8033081c;
      }
      uStack_94 = uStack_94 ^ 0x80000000;
      uVar6 = (int)((uVar3 - 0x10) * *(int *)&menuPcs->field_0x6c) / *(int *)&menuPcs->field_0x64;
      local_98 = 0x43300000;
      dVar12 = (double)(float)((double)FLOAT_80330824 * dVar11);
      dVar8 = (double)(float)((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_80330838);
      iVar7 = (int)((double)FLOAT_80330824 * dVar11);
      local_a0 = (double)(longlong)iVar7;
      dVar10 = (double)(float)(dVar9 - dVar8);
      dVar11 = (double)(float)((double)FLOAT_80330820 + dVar10);
      __ct__6CColorFUcUcUcUc((double)FLOAT_80330820,dVar8,dVar9,&local_1fc,0xff,0xff,0xff,iVar7);
      local_208 = local_1fc;
      GXSetChanMatColor(4,&local_208);
      uVar2 = MenuPcs._500_4_;
      uStack_a4 = uVar3 ^ 0x80000000;
      local_a8 = 0x43300000;
      dVar8 = (double)FLOAT_8033080c;
      if (dVar8 < (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330838)) {
        local_98 = 0x43300000;
        dVar9 = (double)((float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330838) -
                        FLOAT_80330818);
        if (dVar9 < dVar8) {
          dVar9 = dVar8;
        }
        uStack_94 = uStack_a4;
        SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,(CTexture *)MenuPcs._500_4_)
        ;
        uStack_a4 = *(uint *)(uVar2 + 0x68);
        local_a0 = (double)CONCAT44(0x43300000,*(undefined4 *)(uVar2 + 100));
        local_a8 = 0x43300000;
        PSMTXScale(FLOAT_80330808 / (float)(local_a0 - DOUBLE_80330840),
                   FLOAT_80330808 /
                   (float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330840),FLOAT_80330808,
                   &MStack_188);
        GXLoadTexMtxImm(&MStack_188,0x1e,1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
        SetTextureTev__11CTextureManFP8CTexture(&TextureMan,(CTexture *)uVar2);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar10,dVar13,(double)FLOAT_80330820,(double)FLOAT_80330820,
                   (double)FLOAT_8033080c,(double)FLOAT_8033080c,(double)FLOAT_80330808,
                   (double)FLOAT_80330808,&MenuPcs,0);
        uVar2 = MenuPcs._504_4_;
        SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,(CTexture *)MenuPcs._504_4_)
        ;
        uStack_8c = *(undefined4 *)(uVar2 + 100);
        uStack_84 = *(uint *)(uVar2 + 0x68);
        local_90 = 0x43300000;
        local_88 = 0x43300000;
        PSMTXScale(FLOAT_80330808 /
                   (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80330840),
                   FLOAT_80330808 /
                   (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80330840),FLOAT_80330808,
                   &MStack_1b8);
        GXLoadTexMtxImm(&MStack_1b8,0x1e,1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
        SetTextureTev__11CTextureManFP8CTexture(&TextureMan,(CTexture *)uVar2);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)(dVar10 + (double)FLOAT_80330820),dVar13,dVar9,
                   (double)FLOAT_80330820,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
                   (double)FLOAT_80330808,(double)FLOAT_80330808,&MenuPcs,0);
        uVar2 = MenuPcs._508_4_;
        SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,(CTexture *)MenuPcs._508_4_)
        ;
        uStack_74 = *(uint *)(uVar2 + 0x68);
        local_80 = (double)CONCAT44(0x43300000,*(undefined4 *)(uVar2 + 100));
        local_78 = 0x43300000;
        PSMTXScale(FLOAT_80330808 / (float)(local_80 - DOUBLE_80330840),
                   FLOAT_80330808 /
                   (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330840),FLOAT_80330808,
                   &MStack_1e8);
        GXLoadTexMtxImm(&MStack_1e8,0x1e,1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
        SetTextureTev__11CTextureManFP8CTexture(&TextureMan,(CTexture *)uVar2);
        local_70 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
        dVar8 = (double)FLOAT_80330820;
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)((double)(float)(dVar10 + (double)(float)(local_70 -
                                                                           DOUBLE_80330838)) - dVar8
                                  ),dVar13,dVar8,dVar8,(double)FLOAT_8033080c,(double)FLOAT_8033080c
                   ,(double)FLOAT_80330808,(double)FLOAT_80330808,&MenuPcs,0);
      }
      local_70 = (double)(longlong)(int)dVar12;
      uVar3 = *(int *)&menuPcs->field_0x5c * 0xff;
      uVar3 = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) & 0xff;
      __ct__6CColorFUcUcUcUc(&local_200,0xff,uVar3,uVar3,(int)dVar12);
      local_20c = local_200;
      GXSetChanMatColor(4,&local_20c);
      SetTextureTev__11CTextureManFP8CTexture(&TextureMan,(CTexture *)0x0);
      uStack_74 = uVar6 ^ 0x80000000;
      dVar9 = (double)(float)((double)FLOAT_80330828 + dVar13);
      dVar8 = (double)FLOAT_80330808;
      local_78 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,(double)(float)(dVar9 - dVar8),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330838),
                 (double)FLOAT_8033082c,(double)FLOAT_8033080c,(double)FLOAT_8033080c,dVar8,dVar8,
                 menuPcs,0);
      local_80 = (double)(longlong)(int)dVar12;
      uVar3 = *(int *)&menuPcs->field_0x5c * 0x7f;
      uVar4 = *(int *)&menuPcs->field_0x5c * 0xff;
      __ct__6CColorFUcUcUcUc
                (&local_204,0xff,
                 ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0) + 0x80 & 0xff,
                 ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0) & 0xff,(int)dVar12
                );
      local_210 = local_204;
      GXSetChanMatColor(4,&local_210);
      uStack_84 = uVar6 ^ 0x80000000;
      local_88 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar9,
                 (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80330838),
                 (double)FLOAT_80330830,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
                 (double)FLOAT_80330808,(double)FLOAT_80330808,menuPcs,0);
    }
  }
  iVar7 = 0;
  pCVar5 = menuPcs;
  do {
    Draw__5CMenuFv(*(CMenuPcs **)&pCVar5->field_0x13c);
    iVar7 = iVar7 + 1;
    pCVar5 = (CMenuPcs *)&pCVar5->field_0x4;
  } while (iVar7 < 4);
  iVar7 = 0;
  pCVar5 = menuPcs;
  do {
    Draw__5CMenuFv(*(CMenuPcs **)&pCVar5->field_0x10c);
    iVar7 = iVar7 + 1;
    pCVar5 = (CMenuPcs *)&pCVar5->field_0x4;
  } while (iVar7 < 0xc);
  iVar7 = 0;
  do {
    DrawIcon__9CRingMenuFv(*(undefined4 *)&menuPcs->field_0x13c);
    iVar7 = iVar7 + 1;
    menuPcs = (CMenuPcs *)&menuPcs->field_0x4;
  } while (iVar7 < 4);
  return;
}

