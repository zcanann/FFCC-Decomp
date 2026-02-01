// Function: draw__Q29CCharaPcs7CHandleFii
// Entry: 80074598
// Size: 3556 bytes

/* WARNING: Removing unreachable block (ram,0x80075360) */
/* WARNING: Removing unreachable block (ram,0x80075358) */
/* WARNING: Removing unreachable block (ram,0x80075350) */
/* WARNING: Removing unreachable block (ram,0x80075348) */
/* WARNING: Removing unreachable block (ram,0x800745c0) */
/* WARNING: Removing unreachable block (ram,0x800745b8) */
/* WARNING: Removing unreachable block (ram,0x800745b0) */
/* WARNING: Removing unreachable block (ram,0x800745a8) */

void draw__Q29CCharaPcs7CHandleFii(CCharaPcsCHandle *handle,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  bool bVar5;
  undefined uVar6;
  uint uVar7;
  byte *pbVar8;
  Vec *vecA;
  undefined4 uVar9;
  int iVar10;
  CProcess *pCVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined local_2b8;
  undefined local_2b7;
  undefined local_2b6;
  undefined local_2b5;
  undefined local_2b4;
  undefined local_2b3;
  undefined local_2b2;
  undefined local_2b1;
  char local_2b0;
  char local_2af;
  char local_2ae;
  char local_2ad;
  char local_2ac;
  char local_2ab;
  char local_2aa;
  char local_2a9;
  undefined local_2a8;
  undefined local_2a7;
  undefined local_2a6;
  undefined local_2a5;
  undefined local_2a4;
  undefined local_2a3;
  undefined local_2a2;
  undefined local_2a1;
  undefined local_2a0;
  undefined local_29f;
  undefined local_29e;
  byte local_29d;
  undefined local_29c;
  undefined local_29b;
  undefined local_29a;
  byte local_299;
  undefined auStack_298 [4];
  char local_294;
  char local_293;
  char local_292;
  char local_291;
  undefined auStack_290 [4];
  char local_28c;
  char local_28b;
  char local_28a;
  char local_289;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined auStack_278 [4];
  undefined4 local_274;
  undefined4 local_270;
  undefined auStack_26c [4];
  undefined4 local_268;
  undefined4 local_264;
  char local_260;
  char local_25f;
  char local_25e;
  char local_25d;
  char local_25c;
  char local_25b;
  char local_25a;
  char local_259;
  byte local_258;
  byte local_257;
  byte local_256;
  undefined local_255;
  byte local_254;
  byte local_253;
  byte local_252;
  undefined local_251;
  float local_250;
  float local_24c;
  undefined local_248;
  undefined local_247;
  undefined local_246;
  undefined local_245;
  undefined4 local_244;
  float local_240;
  float local_23c;
  byte local_238;
  byte local_237;
  byte local_236;
  undefined local_235;
  Vec local_234;
  Vec local_228;
  Vec local_21c;
  Vec local_210;
  Vec local_204;
  CVector CStack_1f8;
  Vec local_1ec;
  CVector CStack_1e0;
  CVector CStack_1d4;
  Vec local_1c8;
  Vec local_1bc;
  Vec local_1b0;
  CVector CStack_1a4;
  Vec local_198;
  Vec local_18c;
  float local_180;
  float local_17c;
  float local_178;
  Mtx MStack_174;
  Mtx MStack_144;
  Mtx MStack_114;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  
  if ((((((((handle->m_model != (CModel *)0x0) && (uVar7 = handle->m_flags, (uVar7 & 1) != 0)) &&
          ((uVar7 & 0x400000) == 0)) &&
         ((fVar4 = handle->m_model->m_lightAlpha, FLOAT_80330288 != fVar4 || ((uVar7 & 0x80) != 0)))
         ) && (((uVar7 & 0x100) == 0 || (param_2 == 5)))) &&
       ((param_2 != 1 || ((uVar7 & 0x40) == 0)))) && ((param_2 != 2 || ((uVar7 & 0x200) != 0)))) &&
     ((param_2 != 0 || ((uVar7 & 0x4000) == 0)))) {
    if (((param_3 == 0) || (param_2 != 0)) ||
       ((FLOAT_8033028c <= fVar4 && ((uVar7 & 0x40000) == 0)))) {
      if (((param_2 != 3) || ((uVar7 & 0x81c) != 0)) &&
         (((param_2 != 0 && (param_2 != 4)) || ((uVar7 & 0x10) == 0)))) {
        uVar12 = uVar7 >> 0x13 & 1;
        if (((param_2 != 1) && (param_2 != 2)) && ((uVar7 & 0x200000) == 0)) {
          fVar4 = handle->m_colorPhase * FLOAT_80330290;
          iVar10 = (int)fVar4;
          local_e0 = (double)(longlong)iVar10;
          dVar13 = (double)fmod((double)fVar4,DOUBLE_80330298);
          dVar13 = (double)(float)dVar13;
          __ct__6CColorFv(&local_238);
          if (((handle->m_flags & 0x20000) == 0) || (param_2 == 3)) {
            __ct__6CColorFv(&local_2b4);
            iVar10 = iVar10 * 4;
            local_e0 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x130)[iVar10]);
            local_d0 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x131)[iVar10]);
            local_c0 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x132)[iVar10]);
            iVar1 = (int)((double)(float)(local_e0 - DOUBLE_803302b0) * dVar13);
            local_d8 = (double)(longlong)iVar1;
            iVar2 = (int)((double)(float)(local_d0 - DOUBLE_803302b0) * dVar13);
            local_c8 = (double)(longlong)iVar2;
            local_b0 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x133)[iVar10]);
            iVar3 = (int)((double)(float)(local_c0 - DOUBLE_803302b0) * dVar13);
            local_b8 = (double)(longlong)iVar3;
            local_2b4 = (undefined)iVar1;
            iVar1 = (int)((double)(float)(local_b0 - DOUBLE_803302b0) * dVar13);
            local_a8 = (double)(longlong)iVar1;
            local_2b3 = (undefined)iVar2;
            local_2b2 = (undefined)iVar3;
            local_2b1 = (undefined)iVar1;
            __ct__6CColorFR6CColor(&local_260,&local_2b4);
            __ct__6CColorFv(&local_2b8);
            fVar4 = (float)((double)FLOAT_8033028c - dVar13);
            local_a0 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x12c)[iVar10]);
            local_90 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x12d)[iVar10]);
            local_80 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x12e)[iVar10]);
            iVar1 = (int)((float)(local_a0 - DOUBLE_803302b0) * fVar4);
            local_98 = (double)(longlong)iVar1;
            iVar2 = (int)((float)(local_90 - DOUBLE_803302b0) * fVar4);
            local_88 = (double)(longlong)iVar2;
            local_70 = (double)CONCAT44(0x43300000,(uint)(byte)(&CharaPcs.field_0x12f)[iVar10]);
            iVar10 = (int)((float)(local_80 - DOUBLE_803302b0) * fVar4);
            local_78 = (double)(longlong)iVar10;
            local_2b8 = (undefined)iVar1;
            iVar1 = (int)((float)(local_70 - DOUBLE_803302b0) * fVar4);
            local_68 = (double)(longlong)iVar1;
            local_2b7 = (undefined)iVar2;
            local_2b6 = (undefined)iVar10;
            local_2b5 = (undefined)iVar1;
            __ct__6CColorFR6CColor(&local_25c,&local_2b8);
            __ct__6CColorFv(&local_2b0);
            local_2b0 = local_25c + local_260;
            local_2af = local_25b + local_25f;
            local_2ae = local_25a + local_25e;
            local_2ad = local_259 + local_25d;
            __ct__6CColorFR6CColor(&local_258,&local_2b0);
            local_238 = local_258;
            local_237 = local_257;
            local_236 = local_256;
            local_235 = local_255;
          }
          else {
            __ct__6CColorFUcUcUcUc(&local_254,0xff,0xff,0xff,0xff);
            local_238 = local_254;
            local_237 = local_253;
            local_236 = local_252;
            local_235 = local_251;
          }
          pbVar8 = (byte *)__ct__7CColor3FR8_GXColor(auStack_26c,uVar12 * 4 + -0x7fd165b4);
          __ct__7CColor3Fv(&local_29c);
          local_29c = (undefined)(((uint)*pbVar8 * (uint)local_238) / 0xff);
          local_29b = (undefined)(((uint)pbVar8[1] * (uint)local_237) / 0xff);
          local_29a = (undefined)(((uint)pbVar8[2] * (uint)local_236) / 0xff);
          local_299 = pbVar8[3];
          __ct__7CColor3FR7CColor3(&local_268,&local_29c);
          local_264 = local_268;
          SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_264);
          pCVar11 = &CharaPcs.process + uVar12 * 3;
          uVar7 = 0;
          do {
            pbVar8 = (byte *)__ct__7CColor3FR8_GXColor(auStack_278,pCVar11 + 0x3c);
            __ct__7CColor3Fv(&local_2a0);
            local_2a0 = (undefined)(((uint)*pbVar8 * (uint)local_238) / 0xff);
            local_29f = (undefined)(((uint)pbVar8[1] * (uint)local_237) / 0xff);
            local_29e = (undefined)(((uint)pbVar8[2] * (uint)local_236) / 0xff);
            local_29d = pbVar8[3];
            __ct__7CColor3FR7CColor3(&local_274,&local_2a0);
            local_270 = local_274;
            SetDiffuseColor__9CLightPcsFUl8_GXColor(&LightPcs,uVar7,&local_270);
            uVar7 = uVar7 + 1;
            pCVar11 = pCVar11 + 1;
          } while (uVar7 < 3);
          PSMTXCopy(&handle->m_model->m_localMtx,&MStack_114);
          local_180 = MStack_114.value[0][3];
          local_17c = MStack_114.value[1][3];
          local_178 = MStack_114.value[2][3];
          SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,&local_180,0xffffffff);
        }
        PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_144);
        if (param_2 == 3) {
          if ((handle->m_flags & 4) == 0) {
            if ((handle->m_flags & 8) != 0) {
              PSMTXConcat(&MStack_144,(Mtx *)&CFlat.field_0x12b4,&MStack_144);
            }
          }
          else {
            fVar4 = FLOAT_803302a0 * (handle->m_worldPosY - handle->m_bgCharmPlaneY);
            MStack_144.value[1][3] = MStack_144.value[1][1] * fVar4 + MStack_144.value[1][3];
            MStack_144.value[0][3] = MStack_144.value[0][1] * fVar4 + MStack_144.value[0][3];
            MStack_144.value[2][3] = MStack_144.value[2][1] * fVar4 + MStack_144.value[2][3];
            MStack_144.value[2][1] = MStack_144.value[2][1] * FLOAT_803302a4;
            MStack_144.value[0][1] = MStack_144.value[0][1] * FLOAT_803302a4;
            MStack_144.value[1][1] = MStack_144.value[1][1] * FLOAT_803302a4;
          }
        }
        else if (param_2 == 2) {
          __ct__7CVectorFv(&local_18c);
          PSMTXCopy(&handle->m_model->m_localMtx,&MStack_174);
          local_18c.x = MStack_174.value[0][3];
          local_18c.y = MStack_174.value[1][3];
          local_18c.z = MStack_174.value[2][3];
          vecA = (Vec *)__ct__7CVectorFRC3Vec(&CStack_1a4,(Vec *)&CharaPcs.field_0x17c);
          __ct__7CVectorFv(&local_234);
          PSVECSubtract(vecA,&local_18c,&local_234);
          local_198.x = local_234.x;
          local_198.y = local_234.y;
          local_198.z = local_234.z;
          if ((FLOAT_80330288 == local_234.x) && (FLOAT_80330288 == local_234.z)) {
            return;
          }
          dVar13 = (double)PSVECMag(&local_198);
          if (FLOAT_8033028c < (float)(dVar13 / (double)(float)CharaPcs._392_4_)) {
            return;
          }
          dVar14 = (double)(FLOAT_8033028c - (float)(dVar13 / (double)(float)CharaPcs._392_4_));
          Normalize__7CVectorFv((CVector *)&local_198);
          __ct__7CVectorFfff(FLOAT_80330288,FLOAT_803302a8,FLOAT_80330288,&CStack_1f8);
          __ct__7CVectorFv(&local_228);
          PSVECAdd(&local_18c,(Vec *)&CStack_1f8,&local_228);
          local_1ec.x = local_228.x;
          local_1ec.y = local_228.y;
          local_1ec.z = local_228.z;
          uVar9 = __ct__7CVectorFfff(FLOAT_80330288,FLOAT_8033028c,FLOAT_80330288,&CStack_1e0);
          __ct__7CVectorFfff(FLOAT_80330288,FLOAT_803302a8,FLOAT_80330288,&CStack_1d4);
          local_68 = (double)(CONCAT44(0x43300000,CharaPcs._72_4_) ^ 0x80000000);
          dVar13 = (double)(float)(local_68 - DOUBLE_803302b8);
          __ct__7CVectorFv(&local_204);
          PSVECScale((float)dVar13,&local_198,&local_204);
          local_1c8.x = local_204.x;
          local_1c8.y = local_204.y;
          local_1c8.z = local_204.z;
          __ct__7CVectorFv(&local_210);
          PSVECAdd(&local_18c,&local_1c8,&local_210);
          local_1bc.x = local_210.x;
          local_1bc.y = local_210.y;
          local_1bc.z = local_210.z;
          __ct__7CVectorFv(&local_21c);
          PSVECAdd(&local_1bc,(Vec *)&CStack_1d4,&local_21c);
          local_1b0.x = local_21c.x;
          local_1b0.y = local_21c.y;
          local_1b0.z = local_21c.z;
          C_MTXLookAt(&handle->m_shadowViewMtx,&local_1b0,uVar9,&local_1ec);
          PSMTXCopy(&handle->m_shadowViewMtx,&MStack_144);
          if (&stack0x00000000 != (undefined *)0x23c) {
            local_23c = (float)CameraPcs._256_4_;
          }
          if (&stack0x00000000 != (undefined *)0x240) {
            local_240 = (float)CameraPcs._260_4_;
          }
          __ct__6CColorFv(&local_244);
          dVar13 = (double)local_23c;
          local_70 = (double)(longlong)(int)((double)FLOAT_803302ac * dVar14);
          uVar6 = (undefined)(int)((double)FLOAT_803302ac * dVar14);
          local_244 = CONCAT13(uVar6,CONCAT12(uVar6,CONCAT11(uVar6,0xff)));
          local_27c = local_244;
          GXSetFog(dVar13,(double)(float)((double)FLOAT_8033028c + dVar13),dVar13,(double)local_240,
                   2,&local_27c);
        }
        bVar5 = false;
        if ((FLOAT_80330288 < handle->m_fogBlend) && ((param_2 == 0 || (param_2 == 4)))) {
          fVar4 = FLOAT_8033028c - handle->m_fogBlend;
          dVar13 = (double)(FLOAT_8033028c - fVar4 * fVar4);
          if (&stack0x00000000 != (undefined *)0x24c) {
            local_24c = (float)CameraPcs._256_4_;
          }
          if (&stack0x00000000 != (undefined *)0x250) {
            local_250 = (float)CameraPcs._260_4_;
          }
          dVar16 = (double)DAT_8023804c;
          local_280 = DAT_80238048;
          uVar9 = local_280;
          dVar15 = (double)DAT_80238050;
          local_280._0_1_ = (undefined)((uint)DAT_80238048 >> 0x18);
          local_280._1_1_ = (undefined)((uint)DAT_80238048 >> 0x10);
          local_280._2_1_ = (undefined)((uint)DAT_80238048 >> 8);
          local_280._3_1_ = (undefined)DAT_80238048;
          local_248 = local_280._0_1_;
          local_247 = local_280._1_1_;
          local_246 = local_280._2_1_;
          local_245 = (undefined)local_280;
          local_280 = uVar9;
          pbVar8 = (byte *)__ct__6CColorFUcUcUcUc(auStack_298,0xff,0xff,0xff,0xff);
          __ct__6CColorFv(&local_2a8);
          local_68 = (double)CONCAT44(0x43300000,(uint)*pbVar8);
          iVar10 = (int)((double)(float)(local_68 - DOUBLE_803302b0) * dVar13);
          local_70 = (double)(longlong)iVar10;
          local_2a8 = (undefined)iVar10;
          local_78 = (double)CONCAT44(0x43300000,(uint)pbVar8[1]);
          iVar10 = (int)((double)(float)(local_78 - DOUBLE_803302b0) * dVar13);
          local_80 = (double)(longlong)iVar10;
          local_2a7 = (undefined)iVar10;
          local_88 = (double)CONCAT44(0x43300000,(uint)pbVar8[2]);
          iVar10 = (int)((double)(float)(local_88 - DOUBLE_803302b0) * dVar13);
          local_90 = (double)(longlong)iVar10;
          local_2a6 = (undefined)iVar10;
          local_98 = (double)CONCAT44(0x43300000,(uint)pbVar8[3]);
          iVar10 = (int)((double)(float)(local_98 - DOUBLE_803302b0) * dVar13);
          local_a0 = (double)(longlong)iVar10;
          local_2a5 = (undefined)iVar10;
          __ct__6CColorFR6CColor(&local_294,&local_2a8);
          pbVar8 = (byte *)__ct__6CColorFR8_GXColor(auStack_290,&local_248);
          __ct__6CColorFv(&local_2a4);
          dVar17 = (double)(float)((double)FLOAT_8033028c - dVar13);
          local_a8 = (double)CONCAT44(0x43300000,(uint)*pbVar8);
          iVar10 = (int)((double)(float)(local_a8 - DOUBLE_803302b0) * dVar17);
          local_b0 = (double)(longlong)iVar10;
          local_2a4 = (undefined)iVar10;
          local_b8 = (double)CONCAT44(0x43300000,(uint)pbVar8[1]);
          iVar10 = (int)((double)(float)(local_b8 - DOUBLE_803302b0) * dVar17);
          local_c0 = (double)(longlong)iVar10;
          local_2a3 = (undefined)iVar10;
          local_c8 = (double)CONCAT44(0x43300000,(uint)pbVar8[2]);
          iVar10 = (int)((double)(float)(local_c8 - DOUBLE_803302b0) * dVar17);
          local_d0 = (double)(longlong)iVar10;
          local_2a2 = (undefined)iVar10;
          local_d8 = (double)CONCAT44(0x43300000,(uint)pbVar8[3]);
          iVar10 = (int)((double)(float)(local_d8 - DOUBLE_803302b0) * dVar17);
          local_e0 = (double)(longlong)iVar10;
          local_2a1 = (undefined)iVar10;
          __ct__6CColorFR6CColor(&local_28c,&local_2a4);
          __ct__6CColorFv(&local_2ac);
          local_2ac = local_28c + local_294;
          local_2ab = local_28b + local_293;
          local_2aa = local_28a + local_292;
          local_2a9 = local_289 + local_291;
          __ct__6CColorFR6CColor(&local_288,&local_2ac);
          dVar14 = (double)local_24c;
          local_284 = local_288;
          GXSetFog((double)(float)(dVar16 * dVar17 + (double)(float)(dVar14 * dVar13)),
                   (double)(float)((double)(float)((double)FLOAT_8033028c + dVar15) * dVar17 +
                                  (double)(float)((double)(float)((double)FLOAT_8033028c + dVar14) *
                                                 dVar13)),dVar14,(double)local_250,2,&local_284);
          bVar5 = true;
        }
        if ((param_2 == 1) || (param_2 == 2)) {
          if (param_2 == 2) {
            GXSetTexCopySrc(0,0,CharaPcs._68_4_ & 0xffff,CharaPcs._68_4_ & 0xffff);
            GXSetTexCopyDst(CharaPcs._68_4_ & 0xffff,CharaPcs._68_4_ & 0xffff,0x20,0);
            handle->m_shadowTexturePtr = (void *)(CharaPcs._320_4_ + CharaPcs._328_4_);
            DCInvalidateRange(handle->m_shadowTexturePtr,
                              (int)(CharaPcs._68_4_ * CharaPcs._68_4_) / 2);
            GXCopyTex(handle->m_shadowTexturePtr,1);
          }
          uVar7 = countLeadingZeros(1 - param_2);
          DrawShadow__Q26CChara6CModelFPA4_fi(handle->m_model,&MStack_144,(char)(uVar7 >> 5));
          if (param_2 == 2) {
            GXCopyTex(handle->m_shadowTexturePtr,1);
            CharaPcs._328_4_ = CharaPcs._328_4_ + (int)(CharaPcs._68_4_ * CharaPcs._68_4_) / 2;
            GXPixModeSync();
          }
        }
        else {
          iVar10 = 0;
          if ((param_2 == 3) && ((handle->m_flags & 0xc) != 0)) {
            iVar10 = 1;
          }
          uVar12 = handle->m_flags;
          uVar7 = 0;
          if ((param_2 == 3) && ((uVar12 & 0x8000) != 0)) {
            uVar7 = 1;
          }
          Draw__Q26CChara6CModelFPA4_fii
                    (handle->m_model,&MStack_144,
                     (uint)-iVar10 >> 0x1f | -(uVar12 >> 10 & 1) & 2 | -(uVar12 >> 0xd & 1) & 4 |
                     (int)(-uVar7 | uVar7) >> 0x1f & 8U | -(uVar12 >> 0x14 & 1) & 0x10,0);
        }
        if ((param_2 == 0) || (param_2 == 4)) {
          DrawFur__Q26CChara6CModelFPA4_fi(handle->m_model,&MStack_144,handle->m_flags >> 0x17 & 1);
        }
        if (bVar5) {
          SetFog__8CGraphicFii(&Graphic,1,0);
        }
      }
    }
    else if (param_3 != 0) {
      AddPrim__10pppDrawMngFfPQ29CCharaPcs7CHandle(-handle->m_sortZ,&ppvDrawMng,handle);
    }
  }
  return;
}

