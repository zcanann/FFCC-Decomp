// Function: Draw__4CMesFv
// Entry: 80098c90
// Size: 1600 bytes

/* WARNING: Removing unreachable block (ram,0x800992b4) */
/* WARNING: Removing unreachable block (ram,0x80098ca0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__4CMesFv(int param_1)

{
  float fVar1;
  bool bVar2;
  uint uVar3;
  undefined uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  CFont *unaff_r28;
  CFont *font;
  float *pfVar12;
  CFont *font_00;
  double dVar13;
  undefined4 local_70;
  undefined auStack_6c [4];
  undefined4 local_68;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  double local_48;
  
  if (*(int *)(param_1 + 8) != 0) {
    bVar2 = false;
    if ((*(int *)(param_1 + 0x3cac) != 0) && (*(int *)(param_1 + 0x3cb8) != 0)) {
      bVar2 = true;
    }
    if (bVar2) {
      uVar10 = 0xff - (*(int *)(param_1 + 0x3cbc) * 0xff) / *(int *)(param_1 + 0x3cb8);
    }
    else {
      uVar10 = 0xff;
    }
    pfVar12 = (float *)(param_1 + 0xc);
    font_00 = (CFont *)0x0;
    uVar8 = 0xffffffff;
    uVar9 = 0xffffffff;
    for (iVar11 = 0; iVar11 < *(int *)(param_1 + 8); iVar11 = iVar11 + 1) {
      font = unaff_r28;
      if ((int)(uint)*(ushort *)(pfVar12 + 3) <= *(int *)(param_1 + 0x3c80)) {
        if (*(byte *)(pfVar12 + 4) < 0x20) {
          if (font_00 != (CFont *)0x0) {
            DrawQuit__5CFontFv(font_00);
          }
          DrawInit__8CMenuPcsFv(&MenuPcs);
          uVar7 = (uint)*(byte *)(pfVar12 + 4);
          uVar3 = uVar7 + 0x48;
          if (uVar3 != 0x51) {
            if (uVar3 < 0x51) {
              if (uVar3 == 0x4f) {
                bVar2 = false;
                if ((Game.game.m_currentMapId == 0x21) &&
                   (iVar5 = GetPadType__6JoyBusFi(&Joybus,0), iVar5 != 0x40)) {
                  bVar2 = true;
                }
                if (bVar2) {
                  iVar5 = GetPadType__6JoyBusFi(&Joybus,0);
                  uVar3 = (0x40000U - iVar5 | iVar5 - 0x40000U) >> 0x1f;
                }
                else {
                  uVar3 = (uint)Game.game.m_gameWork.m_menuStageMode;
                }
                uVar7 = 0xb;
                if (uVar3 != 0) {
                  uVar7 = 7;
                }
              }
              else if (0x4e < uVar3) {
                bVar2 = false;
                if ((Game.game.m_currentMapId == 0x21) &&
                   (iVar5 = GetPadType__6JoyBusFi(&Joybus,0), iVar5 != 0x40)) {
                  bVar2 = true;
                }
                if (bVar2) {
                  iVar5 = GetPadType__6JoyBusFi(&Joybus,0);
                  uVar3 = (0x40000U - iVar5 | iVar5 - 0x40000U) >> 0x1f;
                }
                else {
                  uVar3 = (uint)Game.game.m_gameWork.m_menuStageMode;
                }
                uVar7 = 0xc;
                if (uVar3 != 0) {
                  uVar7 = 8;
                }
              }
            }
            else if (uVar3 == 0x53) {
              bVar2 = false;
              if ((Game.game.m_currentMapId == 0x21) &&
                 (iVar5 = GetPadType__6JoyBusFi(&Joybus,0), iVar5 != 0x40)) {
                bVar2 = true;
              }
              if (bVar2) {
                iVar5 = GetPadType__6JoyBusFi(&Joybus,0);
                uVar3 = (0x40000U - iVar5 | iVar5 - 0x40000U) >> 0x1f;
              }
              else {
                uVar3 = (uint)Game.game.m_gameWork.m_menuStageMode;
              }
              uVar7 = 0xe;
              if (uVar3 != 0) {
                uVar7 = 10;
              }
            }
            else if (uVar3 < 0x53) {
              bVar2 = false;
              if ((Game.game.m_currentMapId == 0x21) &&
                 (iVar5 = GetPadType__6JoyBusFi(&Joybus,0), iVar5 != 0x40)) {
                bVar2 = true;
              }
              if (bVar2) {
                iVar5 = GetPadType__6JoyBusFi(&Joybus,0);
                uVar3 = (0x40000U - iVar5 | iVar5 - 0x40000U) >> 0x1f;
              }
              else {
                uVar3 = (uint)Game.game.m_gameWork.m_menuStageMode;
              }
              uVar7 = 0xd;
              if (uVar3 != 0) {
                uVar7 = 9;
              }
            }
          }
          uVar6 = __ct__6CColorFUcUcUcUc(auStack_6c,0xff,0xff,0xff,0xff);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x15);
          uStack_5c = (int)*(short *)(pfVar12 + 2) ^ 0x80000000;
          local_60 = 0x43300000;
          local_58 = 0x43300000;
          uStack_54 = (uVar7 % 5) * 0x16 ^ 0x80000000;
          local_50 = 0x43300000;
          uStack_4c = (uVar7 / 5) * 0x16 ^ 0x80000000;
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(*(float *)(param_1 + 0x3c9c) + *pfVar12),
                     (double)(FLOAT_80330890 +
                             *(float *)(param_1 + 0x3ca0) +
                             (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330878)),
                     (double)FLOAT_80330894,(double)FLOAT_80330894,
                     (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330878),
                     (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330878),
                     (double)FLOAT_80330898,(double)FLOAT_80330898,&MenuPcs,0);
          if (font_00 != (CFont *)0x0) {
            DrawInit__5CFontFv(font_00);
          }
        }
        else {
          uVar3 = *(byte *)((int)pfVar12 + 0xe) & 0xf;
          if (uVar9 != uVar3) {
            font = (CFont *)MenuPcs._256_4_;
            if (uVar3 != 2) {
              if (uVar3 < 2) {
                font = (CFont *)MenuPcs._248_4_;
                if ((*(byte *)((int)pfVar12 + 0xe) & 0xf) != 0) {
                  font = unaff_r28;
                }
              }
              else {
                font = unaff_r28;
                if (uVar3 < 4) {
                  font = (CFont *)MenuPcs._256_4_;
                }
              }
            }
            SetShadow__5CFontFi(font,(char)*(undefined4 *)(param_1 + 0x3d38));
            SetMargin__5CFontFf(FLOAT_8033089c,font);
            dVar13 = (double)*(float *)(param_1 + 0x3d48);
            SetScaleX__5CFontFf(*(float *)(param_1 + 0x3d44),font);
            SetScaleY__5CFontFf((float)dVar13,font);
            DrawInit__5CFontFv(font);
            uVar9 = uVar3;
            font_00 = font;
          }
          uStack_4c = *(byte *)((int)pfVar12 + 0xf) & 0xf;
          uStack_54 = (uint)(*(byte *)((int)pfVar12 + 0xf) >> 4);
          local_50 = 0x43300000;
          local_58 = 0x43300000;
          fVar1 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330880) /
                  (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330880);
          if (FLOAT_80330898 <= fVar1) {
            uVar4 = (undefined)uVar10;
          }
          else {
            uStack_5c = uVar10 ^ 0x80000000;
            local_60 = 0x43300000;
            iVar5 = (int)(fVar1 * (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330878))
            ;
            local_48 = (double)(longlong)iVar5;
            uVar4 = (undefined)iVar5;
          }
          local_68 = CONCAT31(0xffffff,uVar4);
          local_70 = local_68;
          SetColor__5CFontF8_GXColor(font_00,&local_70);
          uVar3 = (uint)*(byte *)((int)pfVar12 + 0x12);
          if ((uVar8 != uVar3) && ((*(byte *)((int)pfVar12 + 0xe) & 0xf) < 2)) {
            SetTlut__5CFontFi(font_00,uVar3 + *(int *)(param_1 + 0x3d34));
            uVar8 = uVar3;
          }
          SetPosX__5CFontFf(*(float *)(param_1 + 0x3c9c) + *pfVar12,font_00);
          local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(pfVar12 + 2)) ^ 0x80000000);
          SetPosY__5CFontFf(*(float *)(param_1 + 0x3ca0) + (float)(local_48 - DOUBLE_80330878),
                            font_00);
          uStack_4c = (uint)*(byte *)((int)pfVar12 + 0x11);
          uStack_54 = (uint)*(byte *)((int)pfVar12 + 10);
          local_50 = 0x43300000;
          local_58 = 0x43300000;
          dVar13 = (double)(FLOAT_803308a0 *
                           (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330880));
          SetScaleX__5CFontFf(FLOAT_803308a0 *
                              (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330880),
                              font_00);
          SetScaleY__5CFontFf((float)dVar13,font_00);
          font_00->renderFlags = font_00->renderFlags & 0xf7 | 8;
          Draw__5CFontFUs(font_00,(uint)*(byte *)(pfVar12 + 4));
          font_00->renderFlags = font_00->renderFlags & 0xf7;
        }
      }
      pfVar12 = pfVar12 + 5;
      unaff_r28 = font;
    }
    DrawQuit__5CFontFv(font_00);
  }
  return;
}

