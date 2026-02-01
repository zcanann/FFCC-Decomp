// Function: MogFurFrame__Q26CChara6CModelFP8CGObject
// Entry: 800e00a8
// Size: 4116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MogFurFrame__Q26CChara6CModelFP8CGObject(CModel *model,CGObject *gObject)

{
  float fVar1;
  bool bVar2;
  uint uVar3;
  ushort uVar8;
  ushort uVar9;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar10;
  CTextureSet *pCVar11;
  void *dstBuffer;
  int iVar12;
  uint uVar13;
  undefined4 uVar14;
  ushort uVar16;
  uint uVar15;
  int iVar17;
  byte local_f8;
  byte local_f7;
  byte local_f6;
  byte local_f5;
  byte local_f4;
  byte local_f3;
  byte local_f2;
  byte local_f1;
  byte local_f0;
  byte local_ef;
  byte local_ee;
  byte local_ed;
  undefined4 local_ec;
  undefined auStack_e8 [4];
  undefined4 local_e4;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  undefined auStack_d8 [4];
  undefined4 local_d4;
  undefined auStack_d0 [4];
  undefined4 local_cc;
  undefined auStack_c8 [4];
  undefined4 local_c4;
  undefined auStack_c0 [4];
  undefined4 local_bc;
  byte local_b8;
  byte local_b7;
  byte local_b6;
  byte local_b5;
  byte local_b4;
  byte local_b3;
  byte local_b2;
  char local_b1;
  byte local_b0;
  byte local_af;
  byte local_ae;
  char local_ad;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  pppFVector4 local_98;
  Vec VStack_88;
  Mtx MStack_7c;
  undefined4 local_48;
  uint uStack_44;
  undefined8 local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined8 local_30;
  
  iVar17 = -1;
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar8 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar8 = Pad._4_2_;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar9 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar9 = Pad._8_2_;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    iVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    iVar5 = Pad._64_4_;
  }
  uVar16 = 0;
  if (iVar5 == 0) {
    bVar2 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar2 = true;
    }
    if (bVar2) {
      uVar16 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar16 = Pad._4_2_;
    }
  }
  if (m_mogWork._40_4_ == 0) {
    if ((uVar8 & 0x100) != 0) {
      return;
    }
    m_mogWork._40_4_ = 1;
  }
  if (m_mogWork._4_4_ == 0) {
    iVar17 = 0;
    m_mogWork._24_4_ = Chara._8216_4_;
    m_mogWork._28_4_ = Chara._8220_4_;
    m_mogWork._32_4_ = Chara._8224_4_;
  }
  if (m_mogWork._0_4_ == 0) {
    if ((uVar16 & 1) == 0) {
      if ((uVar16 & 2) == 0) {
        if (-1 < gObject->m_currentAnimSlot) {
          CancelAnim__8CGObjectFi(gObject,1);
        }
      }
      else {
        gObject->m_rotTargetY = gObject->m_rotTargetY + FLOAT_80331108;
        if (gObject->m_currentAnimSlot < '\0') {
          PlayAnim__8CGObjectFiiiiiPSc(gObject,1,0,0,0xffff,0xffff,0);
        }
      }
    }
    else {
      gObject->m_rotTargetY = gObject->m_rotTargetY - FLOAT_80331108;
      if (gObject->m_currentAnimSlot < '\0') {
        PlayAnim__8CGObjectFiiiiiPSc(gObject,1,0,0,0xffff,0xffff,0);
      }
    }
    if ((uVar16 & 8) != 0) {
      m_mogWork._0_4_ = 1;
      PlayAnim__8CGObjectFiiiiiPSc(gObject,0x37,1,0,0xffff,0xffff,0);
      iVar17 = 7;
    }
  }
  else if (m_mogWork._0_4_ == 1) {
    if (gObject->m_currentAnimSlot == *(char *)&(gObject->m_jumpVelocity).z) {
      iVar5 = IsLoopAnim__8CGObjectFi(gObject,1);
      if (iVar5 != 0) {
        PlayAnim__8CGObjectFiiiiiPSc(gObject,0x38,1,0,0xffff,0xffff,0);
      }
    }
    else if (gObject->m_currentAnimSlot == *(char *)((int)&(gObject->m_jumpVelocity).z + 1)) {
      if ((uVar16 & 4) != 0) {
        PlayAnim__8CGObjectFiiiiiPSc(gObject,0x39,1,0,0xffff,0xffff,0);
      }
    }
    else {
      iVar5 = IsLoopAnim__8CGObjectFi(gObject,1);
      if (iVar5 != 0) {
        CancelAnim__8CGObjectFi(gObject,1);
        m_mogWork._0_4_ = 0;
      }
    }
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  fVar1 = FLOAT_8033110c;
  if (!bVar2) {
    countLeadingZeros(Pad._448_4_);
    fVar1 = (float)Pad._36_4_;
  }
  local_48 = 0x43300000;
  bVar2 = false;
  uStack_44 = Chara._8204_4_ ^ 0x80000000;
  iVar5 = (int)(FLOAT_80331110 * fVar1 +
               (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331100));
  local_40 = (double)(longlong)iVar5;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  fVar1 = FLOAT_8033110c;
  if (!bVar2) {
    countLeadingZeros(Pad._448_4_);
    fVar1 = (float)Pad._40_4_;
  }
  local_38 = 0x43300000;
  uStack_34 = Chara._8208_4_ ^ 0x80000000;
  iVar7 = (int)-(FLOAT_80331110 * fVar1 -
                (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331100));
  local_30 = (double)(longlong)iVar7;
  if (iVar5 < 0) {
    Chara._8204_4_ = 0;
  }
  else {
    Chara._8204_4_ = 0x280;
    if (iVar5 < 0x281) {
      Chara._8204_4_ = iVar5;
    }
  }
  if (iVar7 < 0) {
    Chara._8208_4_ = 0;
  }
  else {
    Chara._8208_4_ = 0x1c0;
    if (iVar7 < 0x1c1) {
      Chara._8208_4_ = iVar7;
    }
  }
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_7c);
  if ((uVar8 & 0x100) == 0) {
    if ((((int)Chara._8196_4_ < 3) && (-1 < (int)Chara._8196_4_)) && (m_mogWork._36_4_ != 0)) {
      StopSe__6CSoundFi(&Sound,m_mogWork._36_4_);
      m_mogWork._36_4_ = 0;
    }
  }
  else {
    if (Chara._8200_4_ != Chara._8196_4_) {
      Chara._8200_4_ = Chara._8196_4_;
      m_mogWork._8_4_ = 0;
      StopSe__6CSoundFi(&Sound,m_mogWork._36_4_);
      m_mogWork._36_4_ = 0;
    }
    uVar14 = 0;
    uVar15 = 1;
    if (Chara._8196_4_ == 2) {
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_d0,4,0xf,4,2);
      local_cc = *puVar6;
      local_ac = local_cc;
    }
    else if ((int)Chara._8196_4_ < 2) {
      if (Chara._8196_4_ == 0) {
        puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c0,0xf,4,4,2);
        local_bc = *puVar6;
        local_ac = local_bc;
      }
      else if (-1 < (int)Chara._8196_4_) {
        puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c8,4,8,0xf,2);
        local_c4 = *puVar6;
        local_ac = local_c4;
      }
    }
    else if (Chara._8196_4_ == 4) {
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e0,0,0,0,2);
      local_dc = *puVar6;
      uVar14 = 1;
      iVar5 = (int)System.m_frameCounter >> 0x1f;
      uVar15 = countLeadingZeros((iVar5 * 4 | System.m_frameCounter * 0x40000000 + iVar5 >> 0x1e) -
                                 iVar5);
      uVar15 = uVar15 >> 5 & 0xff;
      local_ac = local_dc;
    }
    else if ((int)Chara._8196_4_ < 4) {
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_d8,0xf,0xf,0xf,4);
      local_d4 = *puVar6;
      iVar5 = (int)System.m_frameCounter >> 0x1f;
      uVar15 = countLeadingZeros((iVar5 * 4 | System.m_frameCounter * 0x40000000 + iVar5 >> 0x1e) -
                                 iVar5);
      uVar15 = uVar15 >> 5 & 0xff;
      local_ac = local_d4;
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_chara_fur_cpp_801db72c,0x506);
    pCVar11 = model->m_texSet;
    uVar4 = Find__11CTextureSetFPc(pCVar11,&DAT_80331114);
    iVar5 = __vc__21CPtrArray<P8CTexture>FUl(&pCVar11->textures,uVar4);
    if (iVar5 != 0) {
      dstBuffer = *(void **)(iVar5 + 0x78);
      iVar5 = *(int *)(iVar5 + 100) * *(int *)(iVar5 + 0x68) * 2;
      DCInvalidateRange(dstBuffer,iVar5);
      memcpy(dstBuffer,0x802e78e4,0x2000);
      DCFlushRange(dstBuffer,iVar5);
      GXInvalidateTexAll();
    }
    puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e8,0xf,0xf,0xf,0);
    uVar4 = *puVar6;
    local_e4._0_1_ = (byte)((uint)uVar4 >> 0x18);
    local_e4._1_1_ = (byte)((uint)uVar4 >> 0x10);
    local_e4._2_1_ = (byte)((uint)uVar4 >> 8);
    local_e4._3_1_ = (char)uVar4;
    local_b4 = local_e4._0_1_;
    local_b3 = local_e4._1_1_;
    local_b2 = local_e4._2_1_;
    local_b1 = (char)local_e4;
    local_b0 = local_e4._0_1_;
    local_af = local_e4._1_1_;
    local_ae = local_e4._2_1_;
    local_ad = (char)local_e4;
    local_ec = local_ac;
    local_e4 = uVar4;
    iVar5 = PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec
                      (model,&MStack_7c,&local_ec,uVar15,uVar14,&local_b0,&local_b4,&VStack_88);
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_chara_fur_cpp_801db72c,0x506);
    pCVar11 = model->m_texSet;
    uVar14 = Find__11CTextureSetFPc(pCVar11,&DAT_80331114);
    iVar7 = __vc__21CPtrArray<P8CTexture>FUl(&pCVar11->textures,uVar14);
    if (iVar7 != 0) {
      uVar14 = *(undefined4 *)(iVar7 + 0x78);
      iVar12 = *(int *)(iVar7 + 100);
      iVar7 = *(int *)(iVar7 + 0x68);
      memcpy(&Chara.field0_0x0.object.base_object.object.m_freeListNode,uVar14,0x2000);
      DCFlushRange(uVar14,iVar12 * iVar7 * 2);
      GXInvalidateTexAll();
    }
    CalcMogScore__6CCharaFv(&Chara);
    if (-1 < iVar5) {
      m_mogWork._8_4_ = m_mogWork._8_4_ + 1;
      if ((int)Chara._8216_4_ < m_mogWork._24_4_ + 5) {
        if ((int)Chara._8216_4_ < m_mogWork._24_4_ + -5) {
          m_mogWork._24_4_ = Chara._8216_4_;
          iVar17 = 6;
        }
      }
      else {
        m_mogWork._24_4_ = Chara._8216_4_;
        iVar17 = 1;
      }
      if ((int)Chara._8220_4_ < m_mogWork._28_4_ + 5) {
        if ((int)Chara._8220_4_ < m_mogWork._28_4_ + -5) {
          m_mogWork._28_4_ = Chara._8220_4_;
          iVar17 = 6;
        }
      }
      else {
        m_mogWork._28_4_ = Chara._8220_4_;
        iVar17 = 1;
      }
      if ((int)Chara._8224_4_ < m_mogWork._32_4_ + 5) {
        if ((int)Chara._8224_4_ < m_mogWork._32_4_ + -5) {
          m_mogWork._32_4_ = Chara._8224_4_;
          iVar17 = 6;
        }
      }
      else {
        m_mogWork._32_4_ = Chara._8224_4_;
        iVar17 = 1;
      }
      if (iVar5 == 0) {
        m_mogWork._12_4_ = m_mogWork._12_4_ + 1;
        if (m_mogWork._12_4_ == 0x3c) {
          if (iVar17 == -1) {
            iVar17 = 3;
          }
        }
        else if ((m_mogWork._12_4_ == 0xf0) && (iVar17 == -1)) {
          iVar17 = 4;
        }
      }
      else {
        m_mogWork._12_4_ = 0;
      }
      if (uVar15 != 0) {
        uVar13 = 0;
        iVar7 = 0;
        iVar5 = (int)System.m_frameCounter >> 0x1f;
        uVar10 = countLeadingZeros((System.m_frameCounter & 1 ^ -iVar5) + iVar5);
        uVar3 = countLeadingZeros((iVar5 * 4 | System.m_frameCounter * 0x40000000 + iVar5 >> 0x1e) +
                                  -iVar5);
        uVar10 = uVar10 >> 5 & 0xff;
        uVar3 = uVar3 >> 5 & 0xff;
        __ct__6CColorFR8_GXColor(&local_b8,&local_b0);
        if (Chara._8196_4_ == 2) {
          m_mogWork._16_4_ = 0;
          uVar13 = 0x73;
          m_mogWork._20_4_ = 0;
          __ct__6CColorFUcUcUcUc(&local_f8,4,0xf,4,2);
          local_b8 = local_f8;
          local_b7 = local_f7;
          local_b6 = local_f6;
          local_b5 = local_f5;
        }
        else if ((int)Chara._8196_4_ < 2) {
          if (Chara._8196_4_ == 0) {
            m_mogWork._16_4_ = 0;
            uVar13 = 0x73;
            m_mogWork._20_4_ = 0;
            __ct__6CColorFUcUcUcUc(&local_f0,0xf,4,4,2);
            local_b8 = local_f0;
            local_b7 = local_ef;
            local_b6 = local_ee;
            local_b5 = local_ed;
          }
          else if (-1 < (int)Chara._8196_4_) {
            m_mogWork._16_4_ = 0;
            uVar13 = 0x73;
            m_mogWork._20_4_ = 0;
            __ct__6CColorFUcUcUcUc(&local_f4,4,8,0xf,2);
            local_b8 = local_f4;
            local_b7 = local_f3;
            local_b6 = local_f2;
            local_b5 = local_f1;
          }
        }
        else {
          iVar5 = (int)System.m_frameCounter >> 0x1f;
          if (Chara._8196_4_ == 4) {
            m_mogWork._16_4_ = 0;
            if (((uVar15 != 0) && (local_ad != '\0')) && (local_b1 == '\0')) {
              m_mogWork._20_4_ = m_mogWork._20_4_ + 1;
            }
            uVar10 = 1;
            uVar13 = 0x72;
            if (uVar15 == 0) {
              local_b5 = 0;
            }
            iVar7 = 0x249f3;
            uVar3 = countLeadingZeros((iVar5 * 8 |
                                      System.m_frameCounter * 0x20000000 + iVar5 >> 0x1d) - iVar5);
            uVar3 = uVar3 >> 5 & 0xff;
          }
          else if ((int)Chara._8196_4_ < 4) {
            m_mogWork._20_4_ = 0;
            if ((((local_b0 < 0xd) || (local_af < 0xd)) || (local_ae < 0xd)) && (local_ad != '\0'))
            {
              m_mogWork._16_4_ = m_mogWork._16_4_ + 1;
            }
            iVar7 = 0x249f4;
            uVar13 = 0x74;
            uVar10 = countLeadingZeros((iVar5 * 8 |
                                       System.m_frameCounter * 0x20000000 + iVar5 >> 0x1d) + -iVar5)
            ;
            uVar3 = countLeadingZeros((iVar5 * 0x10 |
                                      System.m_frameCounter * 0x10000000 + iVar5 >> 0x1c) + -iVar5);
            uVar10 = uVar10 >> 5 & 0xff;
            uVar3 = uVar3 >> 5 & 0xff;
          }
        }
        if (uVar10 != 0) {
          ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,uVar13 | 0x100,0);
          SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                    ((double)FLOAT_8033110c,(CFlatRuntime2 *)&CFlat,&VStack_88);
          uVar14 = PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          uStack_34 = (uint)local_b7;
          local_30 = (double)CONCAT44(0x43300000,(uint)local_b8);
          uStack_44 = (uint)local_b5;
          local_38 = 0x43300000;
          local_98.m_vector[0] = (float)(local_30 - DOUBLE_80331128) / FLOAT_8033111c;
          local_40 = (double)CONCAT44(0x43300000,(uint)local_b6);
          local_98.m_vector[1] =
               (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331128) / FLOAT_8033111c;
          local_48 = 0x43300000;
          local_98.m_vector[2] = (float)(local_40 - DOUBLE_80331128) / FLOAT_8033111c;
          local_98.m_vector[3] =
               (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331128) / FLOAT_80331120;
          SetParColIdx__8CPartPcsFiR11pppFVECTOR4(&PartPcs,uVar14,&local_98);
        }
        if ((uVar3 != 0) && (iVar7 != 0)) {
          PlaySe__6CSoundFiiii(&Sound,iVar7,0x40,0x7f,0);
        }
        if (m_mogWork._16_4_ == 10) {
          if (iVar17 == -1) {
            iVar17 = 2;
          }
          m_mogWork._16_4_ = 0xb;
        }
        if (m_mogWork._20_4_ == 10) {
          if (iVar17 == -1) {
            iVar17 = 5;
          }
          m_mogWork._20_4_ = 0xb;
        }
        if (m_mogWork._20_4_ == 0x32) {
          if (iVar17 == -1) {
            iVar17 = 6;
          }
          m_mogWork._20_4_ = 0x33;
        }
        if ((((int)Chara._8196_4_ < 3) && (-1 < (int)Chara._8196_4_)) &&
           ((uVar15 != 0 && (m_mogWork._36_4_ == 0)))) {
          m_mogWork._36_4_ = PlaySe__6CSoundFiiii(&Sound,0x249f2,0x40,0x7f,0);
        }
      }
    }
  }
  if ((uVar9 & 0x200) != 0) {
    local_a8 = 2;
    local_a4 = 0;
    local_a0 = 0;
    SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
              (&CFlat,0,1,9,3,&local_a8,(CStack *)0x0);
  }
  if (-1 < iVar17) {
    bVar2 = false;
    if (((*(int *)(MenuPcs._288_4_ + 8) != 0) && (*(int *)(MenuPcs._288_4_ + 0xc) < 2)) &&
       (iVar5 = GetWait__4CMesFv(MenuPcs._288_4_ + 0x1c), iVar5 != 4)) {
      bVar2 = true;
    }
    if (!bVar2) {
      Open__8CMesMenuFPciiiiii
                (MenuPcs._288_4_,Game.game.m_cFlatDataArr[1].m_mesPtr[iVar17 + 8],0x160,0x20,0x220,0
                 ,0xffffffff,0xffffffff);
    }
  }
  m_mogWork._4_4_ = m_mogWork._4_4_ + 1;
  return;
}

