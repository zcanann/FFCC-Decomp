// Function: drawShadowBegin__10CCameraPcsFv
// Entry: 80037554
// Size: 2812 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawShadowBegin__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  Vec local_e8;
  Vec VStack_dc;
  Mtx MStack_d0;
  Mtx MStack_a0;
  Mtx MStack_70;
  Mtx MStack_40;
  
  if (*(char *)(param_1 + 0x404) != '\0') {
    GXInvalidateTexAll();
    *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_1 + 0x114) = *(undefined4 *)(param_1 + 0xc);
    *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x11c) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x124) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 300) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x134) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x138) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x4c);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x50);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x54);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x58);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x5c);
    *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x60);
    *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_1 + 0x74);
    *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_1 + 0x7c);
    *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_1 + 0x80);
    *(undefined4 *)(param_1 + 0x18c) = *(undefined4 *)(param_1 + 0x84);
    *(undefined4 *)(param_1 + 400) = *(undefined4 *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0x194) = *(undefined4 *)(param_1 + 0x8c);
    *(undefined4 *)(param_1 + 0x198) = *(undefined4 *)(param_1 + 0x90);
    *(undefined4 *)(param_1 + 0x19c) = *(undefined4 *)(param_1 + 0x94);
    *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x1ac) = *(undefined4 *)(param_1 + 0xa4);
    *(undefined4 *)(param_1 + 0x1b0) = *(undefined4 *)(param_1 + 0xa8);
    *(undefined4 *)(param_1 + 0x1b4) = *(undefined4 *)(param_1 + 0xac);
    *(undefined4 *)(param_1 + 0x1b8) = *(undefined4 *)(param_1 + 0xb0);
    *(undefined4 *)(param_1 + 0x1bc) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(param_1 + 0x1c4) = *(undefined4 *)(param_1 + 0xbc);
    *(undefined4 *)(param_1 + 0x1c8) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(param_1 + 0x1cc) = *(undefined4 *)(param_1 + 0xc4);
    *(undefined4 *)(param_1 + 0x1d0) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_1 + 0xd0);
    *(undefined4 *)(param_1 + 0x1dc) = *(undefined4 *)(param_1 + 0xd4);
    *(undefined4 *)(param_1 + 0x1e0) = *(undefined4 *)(param_1 + 0xd8);
    *(undefined4 *)(param_1 + 0x1e4) = *(undefined4 *)(param_1 + 0xdc);
    *(undefined4 *)(param_1 + 0x1e8) = *(undefined4 *)(param_1 + 0xe0);
    *(undefined4 *)(param_1 + 0x1ec) = *(undefined4 *)(param_1 + 0xe4);
    *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_1 + 0xe8);
    *(undefined4 *)(param_1 + 500) = *(undefined4 *)(param_1 + 0xec);
    *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0xf0);
    *(undefined4 *)(param_1 + 0x1fc) = *(undefined4 *)(param_1 + 0xf4);
    *(undefined4 *)(param_1 + 0x200) = *(undefined4 *)(param_1 + 0xf8);
    *(undefined4 *)(param_1 + 0x204) = *(undefined4 *)(param_1 + 0xfc);
    *(undefined4 *)(param_1 + 0x208) = *(undefined4 *)(param_1 + 0x100);
    *(undefined4 *)(param_1 + 0x20c) = *(undefined4 *)(param_1 + 0x104);
    *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_1 + 0x108);
    *(undefined4 *)(param_1 + 0x214) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 0x218) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_1 + 0x21c) = *(undefined4 *)(param_1 + 0xc);
    *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x224) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x228) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x22c) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x234) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x23c) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x240) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x244) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0x248) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x24c) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x250) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x254) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 600) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(param_1 + 0x25c) = *(undefined4 *)(param_1 + 0x4c);
    *(undefined4 *)(param_1 + 0x260) = *(undefined4 *)(param_1 + 0x50);
    *(undefined4 *)(param_1 + 0x264) = *(undefined4 *)(param_1 + 0x54);
    *(undefined4 *)(param_1 + 0x268) = *(undefined4 *)(param_1 + 0x58);
    *(undefined4 *)(param_1 + 0x26c) = *(undefined4 *)(param_1 + 0x5c);
    *(undefined4 *)(param_1 + 0x270) = *(undefined4 *)(param_1 + 0x60);
    *(undefined4 *)(param_1 + 0x274) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0x278) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0x27c) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0x280) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x284) = *(undefined4 *)(param_1 + 0x74);
    *(undefined4 *)(param_1 + 0x288) = *(undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x28c) = *(undefined4 *)(param_1 + 0x7c);
    *(undefined4 *)(param_1 + 0x290) = *(undefined4 *)(param_1 + 0x80);
    *(undefined4 *)(param_1 + 0x294) = *(undefined4 *)(param_1 + 0x84);
    *(undefined4 *)(param_1 + 0x298) = *(undefined4 *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0x29c) = *(undefined4 *)(param_1 + 0x8c);
    *(undefined4 *)(param_1 + 0x2a0) = *(undefined4 *)(param_1 + 0x90);
    *(undefined4 *)(param_1 + 0x2a4) = *(undefined4 *)(param_1 + 0x94);
    *(undefined4 *)(param_1 + 0x2a8) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0x2ac) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x2b0) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x2b4) = *(undefined4 *)(param_1 + 0xa4);
    *(undefined4 *)(param_1 + 0x2b8) = *(undefined4 *)(param_1 + 0xa8);
    *(undefined4 *)(param_1 + 700) = *(undefined4 *)(param_1 + 0xac);
    *(undefined4 *)(param_1 + 0x2c0) = *(undefined4 *)(param_1 + 0xb0);
    *(undefined4 *)(param_1 + 0x2c4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x2c8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(param_1 + 0x2cc) = *(undefined4 *)(param_1 + 0xbc);
    *(undefined4 *)(param_1 + 0x2d0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(param_1 + 0x2d4) = *(undefined4 *)(param_1 + 0xc4);
    *(undefined4 *)(param_1 + 0x2d8) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(param_1 + 0x2dc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0x2e0) = *(undefined4 *)(param_1 + 0xd0);
    *(undefined4 *)(param_1 + 0x2e4) = *(undefined4 *)(param_1 + 0xd4);
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0xd8);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0xdc);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0xe0);
    *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0xe4);
    *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0xe8);
    *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0xec);
    *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0xf0);
    *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0xf4);
    *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0xf8);
    *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0xfc);
    *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x100);
    *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x104);
    *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_1 + 0x108);
    fVar3 = FLOAT_8032fa70;
    fVar1 = FLOAT_8032fa4c;
    if (Game.game.m_currentSceneId == 3) {
      fVar2 = FLOAT_8032fa34;
      if (Pad._452_4_ == 0) {
        fVar2 = *(float *)((int)&Pad +
                          ((int)(1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54 + 0x24);
      }
      *(float *)(param_1 + 0x368) =
           FLOAT_8032fa70 * FLOAT_8032fa74 * fVar2 + *(float *)(param_1 + 0x368);
      fVar2 = FLOAT_8032fa34;
      if (Pad._452_4_ == 0) {
        fVar2 = *(float *)((int)&Pad +
                          ((int)(1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54 + 0x28);
      }
      *(float *)(param_1 + 0x364) = fVar3 * fVar1 * fVar2 + *(float *)(param_1 + 0x364);
    }
    PSMTXRotRad(-*(float *)(param_1 + 0x364),&MStack_70,0x78);
    PSMTXRotRad(*(float *)(param_1 + 0x368),&MStack_40,0x79);
    PSMTXConcat(&MStack_40,&MStack_70,&MStack_a0);
    fVar2 = FLOAT_8032fa8c;
    fVar3 = FLOAT_8032fa7c;
    fVar1 = FLOAT_8032fa78;
    if (Game.game.m_currentSceneId == 4) {
      *(float *)(param_1 + 0x41c) = FLOAT_8032fa78;
      *(float *)(param_1 + 0x418) = fVar1;
      *(float *)(param_1 + 0x414) = fVar1;
      *(float *)(param_1 + 0x428) = fVar3;
      *(float *)(param_1 + 0x424) = fVar3;
      *(float *)(param_1 + 0x420) = fVar3;
      if ((*(int *)(param_1 + 0x434) == 1) &&
         (iVar4 = GetShadowRect__10CCameraPcsFR6CBound(param_1,param_1 + 0x414), iVar4 != 0)) {
        fVar1 = (*(float *)(param_1 + 0x41c) + *(float *)(param_1 + 0x428)) * FLOAT_8032fa20;
        *(float *)(param_1 + 0xd4) =
             (*(float *)(param_1 + 0x414) + *(float *)(param_1 + 0x420)) * FLOAT_8032fa20;
        *(float *)(param_1 + 0xdc) = fVar1;
        *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x40c);
        dVar6 = (double)(*(float *)(param_1 + 0x420) - *(float *)(param_1 + 0x414));
        dVar5 = (double)(*(float *)(param_1 + 0x428) - *(float *)(param_1 + 0x41c));
        if (dVar6 < dVar5) {
          dVar6 = dVar5;
        }
        *(float *)(param_1 + 0x36c) = (float)((double)FLOAT_8032fa20 * dVar6);
      }
      else if (*(int *)(param_1 + 0x434) == 2) {
        *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x408);
        *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x40c);
        *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x410);
        PSVECSubtract((Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xe0),&VStack_dc);
        dVar6 = (double)*(float *)(param_1 + 0x430);
        *(float *)(param_1 + 0x36c) = FLOAT_8032fa80 * *(float *)(param_1 + 0x370);
      }
      else {
        *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x408);
        *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x40c);
        *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x410);
        PSVECSubtract((Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xe0),&VStack_dc);
        dVar6 = (double)PSVECMag(&VStack_dc);
        *(float *)(param_1 + 0x36c) = (float)(dVar6 * (double)*(float *)(param_1 + 0x370));
      }
      dVar5 = (double)*(float *)(param_1 + 0x42c);
      if ((double)FLOAT_8032fa34 <= dVar5) {
        *(float *)(param_1 + 0x42c) =
             (float)(dVar5 + (double)((float)(dVar6 - dVar5) * FLOAT_8032fa84));
      }
      else {
        *(float *)(param_1 + 0x42c) = (float)dVar6;
      }
    }
    else {
      *(float *)(param_1 + 0x36c) = FLOAT_8032fa88;
      *(float *)(param_1 + 0x42c) = fVar2;
    }
    local_e8.x = FLOAT_8032fa34;
    local_e8.y = FLOAT_8032fa1c;
    local_e8.z = FLOAT_8032fa34;
    PSMTXMultVecSR(&MStack_a0,&local_e8,&local_e8);
    fVar1 = FLOAT_8032fa34;
    *(float *)(param_1 + 0x2f0) = FLOAT_8032fa34;
    *(float *)(param_1 + 0x2f4) = fVar1;
    *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x42c);
    PSMTXMultVecSR(&MStack_a0,(Vec *)(param_1 + 0x2f0),(Vec *)(param_1 + 0x2f0));
    if (Game.game.m_currentMapId == 0x21) {
      PSMTXCopy((Mtx *)&CameraPcs.field_0x64,&MStack_d0);
      PSMTXMultVecSR(&MStack_d0,(Vec *)(param_1 + 0x2f0),(Vec *)(param_1 + 0x2f0));
    }
    PSVECAdd((Vec *)(param_1 + 0x2f0),(Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0x2f0));
    fVar3 = FLOAT_8032fa8c;
    *(undefined4 *)(param_1 + 0x2e4) = *(undefined4 *)(param_1 + 0xd4);
    fVar1 = FLOAT_8032fa4c;
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0xd8);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0xdc);
    *(float *)(param_1 + 0x310) = fVar3;
    *(float *)(param_1 + 0x314) = fVar1 * *(float *)(param_1 + 0x42c);
    C_MTXLookAt((Mtx *)(param_1 + 0x214),(Vec *)(param_1 + 0x2f0),&local_e8,(Vec *)(param_1 + 0x2e4)
               );
    fVar1 = *(float *)(param_1 + 0x36c);
    C_MTXOrtho(fVar1,-fVar1,-fVar1,fVar1,*(float *)(param_1 + 0x310),*(float *)(param_1 + 0x314),
               (Mtx *)(param_1 + 0x2a4));
    g_shadow_pos.x = *(float *)(param_1 + 0x2f0);
    g_shadow_pos.y = *(float *)(param_1 + 0x2f4);
    g_shadow_pos.z = *(float *)(param_1 + 0x2f8);
    g_shadow_refpos.x = *(float *)(param_1 + 0x2e4);
    g_shadow_refpos.y = *(float *)(param_1 + 0x2e8);
    g_shadow_refpos.z = *(float *)(param_1 + 0x2ec);
    *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 0x214);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0x218);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x21c);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x220);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x224);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x228);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x22c);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x230);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x234);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x238);
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x23c);
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x240);
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x244);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x248);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x24c);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x250);
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x254);
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 600);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x25c);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x260);
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x264);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x268);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x26c);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x270);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x274);
    *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x278);
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x27c);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x280);
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x284);
    *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x288);
    *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x28c);
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x290);
    *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_1 + 0x294);
    *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x298);
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x29c);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x2a0);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x2a4);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x2a8);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x2ac);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x2b0);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x2b4);
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_1 + 0x2b8);
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_1 + 700);
    *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_1 + 0x2c0);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0x2c4);
    *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_1 + 0x2c8);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_1 + 0x2cc);
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0x2d0);
    *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0x2d4);
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x2d8);
    *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x2dc);
    *(undefined4 *)(param_1 + 0xd0) = *(undefined4 *)(param_1 + 0x2e0);
    *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x2e4);
    *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x2e8);
    *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x2ec);
    *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x2f0);
    *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x2f4);
    *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0x2f8);
    *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)(param_1 + 0x2fc);
    *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)(param_1 + 0x300);
    *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(param_1 + 0x304);
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0x308);
    *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0x30c);
    *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0x310);
    *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0x314);
    *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_1 + 0x318);
    GXSetProjection(param_1 + 0x94,1);
    GXSetColorUpdate(0);
    GXSetCullMode(2);
    GXSetViewport((double)FLOAT_8032fa4c,(double)FLOAT_8032fa4c,(double)FLOAT_8032fa90,
                  (double)FLOAT_8032fa90,(double)FLOAT_8032fa34,(double)FLOAT_8032fa1c);
    GXSetScissor(2,2,0x1dc,0x1dc);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,0,0,5);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
    GXSetZCompLoc(1);
    GXSetNumChans(1);
    GXSetChanCtrl(4,0,0,0,0,2,2);
    GXSetNumTevStages(1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    GXSetNumTexGens(0);
    DrawMapShadow__7CMapMngFv(&MapMng);
  }
  return;
}

