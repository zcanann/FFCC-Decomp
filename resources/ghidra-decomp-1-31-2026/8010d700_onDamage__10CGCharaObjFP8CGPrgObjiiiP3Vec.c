// Function: onDamage__10CGCharaObjFP8CGPrgObjiiiP3Vec
// Entry: 8010d700
// Size: 6984 bytes

/* WARNING: Removing unreachable block (ram,0x8010f22c) */
/* WARNING: Removing unreachable block (ram,0x8010df70) */
/* WARNING: Removing unreachable block (ram,0x8010d710) */
/* WARNING: Removing unreachable block (ram,0x8010e5d8) */
/* WARNING: Removing unreachable block (ram,0x8010e918) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDamage__10CGCharaObjFP8CGPrgObjiiiP3Vec
               (CGCharaObj *gCharaObj,CGPrgObj *gPrgObj,int param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar8;
  int iVar6;
  float fVar7;
  uint uVar9;
  Vec *pVVar10;
  uint uVar11;
  uint uVar12;
  undefined4 uVar13;
  uint uVar14;
  float fVar15;
  bool bVar18;
  void **ppvVar16;
  void *pvVar17;
  CGPrgObj *pCVar19;
  uint uVar20;
  short sVar22;
  int iVar21;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  uint uVar23;
  int iVar24;
  double dVar25;
  int local_148;
  int local_144;
  int local_140;
  Vec local_13c;
  Vec local_130;
  Vec local_124;
  Vec local_118;
  CVector CStack_10c;
  CVector CStack_100;
  CVector CStack_f4;
  CVector CStack_e8;
  CVector CStack_dc;
  CVector CStack_d0;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  Vec local_ac;
  Vec local_a0;
  undefined8 local_90;
  undefined4 local_88;
  uint uStack_84;
  undefined8 local_80;
  undefined8 local_78;
  undefined4 local_70;
  uint uStack_6c;
  undefined8 local_68;
  int local_60;
  uint local_5c;
  
  DAT_8032ee60 = param_6;
  DAT_8032ee64 = param_4;
  uVar9 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))();
  if (((uVar9 & 0x6d) == 0x6d) &&
     (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x12) != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801dc638);
    return;
  }
  uVar9 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                    (gCharaObj);
  if (((uVar9 & 0x6d) == 0x6d) && ((MiniGamePcs._25732_4_ & 4) != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801dc660);
    return;
  }
  uVar9 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                    (gCharaObj);
  if (((uVar9 & 0x6d) == 0x6d) &&
     (sVar2._0_1_ = (gCharaObj->gPrgObj).object.m_lastMapIdHit,
     sVar2._1_1_ = (gCharaObj->gPrgObj).object.m_lastMapIdExtra, sVar2 != 1)) {
    Printf__7CSystemFPce(&System,&DAT_801dc680);
    return;
  }
  if (-1 < (int)((uint)*(byte *)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags << 0x18)) {
    Printf__7CSystemFPce(&System,&DAT_801dc6a8);
    return;
  }
  iVar24 = param_3 * 0x48;
  uVar9 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 8);
  if ((((uVar9 != 0x67) && (uVar9 != 0x65)) && (uVar9 != 0x66)) &&
     ((int)((uint)(byte)CFlat._4836_1_ << 0x1a | (uint)((byte)CFlat._4836_1_ >> 6)) < 0)) {
    Printf__7CSystemFPce(&System,&DAT_801dc6c4);
    return;
  }
  local_5c = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 0xe);
  sVar3 = *(short *)(Game.game.unkCFlatData0[2] + iVar24);
  sVar2 = *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e);
  calcRegist__10CGCharaObjFiiRiRiRii(gCharaObj,uVar9,param_3,&local_140,&local_144,&local_148,0);
  if (local_140 == 3) {
    if ((((uVar9 == 4) || (uVar9 == 0x1c)) || (uVar9 < 3)) ||
       (((uVar9 - 8 < 3 || (uVar9 == 6)) || (uVar9 == 3)))) {
      putParticle__8CGPrgObjFiiP3Vecfi
                ((double)(FLOAT_803319a8 *
                         FLOAT_803319ac * (gCharaObj->gPrgObj).object.m_attackColRadius),
                 &gCharaObj->gPrgObj,0x201,0,param_6,0x65);
    }
    else if (((uVar9 - 0x24 < 2) || (uVar9 == 0x69)) || (uVar9 == 0x6a)) {
      putParticle__8CGPrgObjFiiP3Vecfi
                ((double)(FLOAT_803319a8 *
                         FLOAT_803319ac * (gCharaObj->gPrgObj).object.m_attackColRadius),
                 &gCharaObj->gPrgObj,0x200,0,param_6,0x1d);
    }
  }
  else if (((1 < local_140) ||
           ((local_140 == 1 && ((*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 0x32) & 1) == 0))
           )) && ((uVar9 - 8 < 2 || ((uVar9 == 6 || (uVar9 == 3)))))) {
    putParticle__8CGPrgObjFiiP3Vecfi
              ((double)(FLOAT_803319a8 *
                       FLOAT_803319ac * (gCharaObj->gPrgObj).object.m_attackColRadius),
               &gCharaObj->gPrgObj,0x201,0,param_6,0x65);
  }
  local_60 = 0;
  if ((((gCharaObj->gPrgObj).m_lastStateId == 8) && ((gCharaObj->gPrgObj).m_subState == 1)) &&
     ((*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 0x2c) & 8) == 0)) {
    __ct__7CVectorFRC3Vec(&CStack_dc,&(gCharaObj->gPrgObj).object.m_worldPosition);
    pVVar10 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_d0,&(gPrgObj->object).m_worldPosition);
    __ct__7CVectorFv(&local_118);
    PSVECSubtract(pVVar10,(Vec *)&CStack_dc,&local_118);
    local_a0.x = local_118.x;
    local_a0.y = local_118.y;
    local_a0.z = local_118.z;
    dVar25 = (double)PSVECMag(&local_a0);
    if ((double)FLOAT_80331988 < dVar25) {
      __ct__7CVectorFv(&local_124);
      PSVECScale((float)((double)FLOAT_80331964 / dVar25),&local_a0,&local_124);
      local_a0.x = local_124.x;
      local_a0.y = local_124.y;
      local_a0.z = local_124.z;
      __ct__7CVectorFv(&local_ac);
      dVar25 = (double)sin((double)(gCharaObj->gPrgObj).object.m_rotBaseY);
      local_ac.x = (float)dVar25;
      local_ac.y = FLOAT_80331988;
      dVar25 = (double)cos((double)(gCharaObj->gPrgObj).object.m_rotBaseY);
      local_ac.z = (float)dVar25;
      dVar25 = (double)PSVECDotProduct(&local_a0,&local_ac);
      if ((double)FLOAT_80331988 < dVar25) {
        playSe3D__8CGPrgObjFiiiiP3Vec(&gCharaObj->gPrgObj,0x1d,0x32,0x96,0,0);
        putParticle__8CGPrgObjFiiP3Vecfi
                  ((double)(FLOAT_803319ac * (gCharaObj->gPrgObj).object.m_attackColRadius),
                   &gCharaObj->gPrgObj,0x200,0,param_6,0);
        uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
        if ((uVar11 & 0x6d) == 0x6d) {
          changeStat__8CGPrgObjFiii(gPrgObj,0x13,0,0);
        }
        uVar11 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                           (gCharaObj);
        if ((uVar11 & 0x6d) == 0x6d) {
          changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,2);
          if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0xf8) == 0) {
            local_148 = 0;
          }
          else {
            local_60 = 1;
          }
        }
        else {
          local_148 = 0;
        }
        local_144 = 0;
      }
    }
  }
  if (((gCharaObj->gPrgObj).m_lastStateId == 6) &&
     (bVar1 = *(byte *)((int)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags + 1),
     (int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0)) {
    uVar8 = *(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gCharaObj->field_0x560 * 0x48 + 10) &
            0xff;
    if (uVar8 == 2) {
      if (((uVar9 != 0x66) && (uVar9 != 0x67)) && (uVar9 != 7)) {
        __ct__7CVectorFRC3Vec(&CStack_f4,&(gPrgObj->object).m_worldPosition);
        pVVar10 = (Vec *)__ct__7CVectorFRC3Vec
                                   (&CStack_e8,&(gCharaObj->gPrgObj).object.m_worldPosition);
        __ct__7CVectorFv(&local_130);
        PSVECSubtract(pVVar10,(Vec *)&CStack_f4,&local_130);
        local_b8 = local_130.x;
        local_b4 = local_130.y;
        local_b0 = local_130.z;
        moveVectorH__8CGObjectFP3Vecfi((double)FLOAT_803319a8,(CGObject *)gCharaObj,&local_b8,10);
        dVar25 = (double)atan2(-(double)local_b8,-(double)local_b0);
        (gCharaObj->gPrgObj).object.m_rotTargetY = (float)dVar25;
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1a,0,0);
      }
    }
    else if (uVar8 == 3) {
      local_148 = 0;
      local_144 = 0;
    }
  }
  if (((sVar3 == 0x1f8) &&
      (bVar1 = *(byte *)((int)&(gPrgObj->object).m_weaponNodeFlags + 1),
      (int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0)) &&
     ((*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gCharaObj->field_0x560 * 0x48 + 10) & 0xff)
      == 3)) {
    __ct__7CVectorFRC3Vec(&CStack_10c,&(gPrgObj->object).m_worldPosition);
    pVVar10 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_100,&(gCharaObj->gPrgObj).object.m_worldPosition)
    ;
    __ct__7CVectorFv(&local_13c);
    PSVECSubtract(pVVar10,(Vec *)&CStack_10c,&local_13c);
    local_c4 = local_13c.x;
    local_c0 = local_13c.y;
    local_bc = local_13c.z;
    moveVectorH__8CGObjectFP3Vecfi((double)FLOAT_803319a8,(CGObject *)gCharaObj,&local_c4,10);
    dVar25 = (double)atan2(-(double)local_c4,-(double)local_bc);
    (gCharaObj->gPrgObj).object.m_rotTargetY = (float)dVar25;
    changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x19,0,0);
  }
  if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x1d) != 0) {
    local_144 = 0;
    local_148 = 0;
  }
  if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x11) != 0) {
    local_144 = 0;
  }
  if ((*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x14) != 0) &&
     ((uVar9 == 8 || (uVar9 == 7)))) {
    local_144 = 0;
    local_148 = 0;
  }
  if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7) == 0) {
    if (uVar9 == 0x65) {
      local_144 = 1;
      local_148 = 0;
    }
    else {
      local_144 = 0;
      local_148 = 0;
    }
  }
  else if (uVar9 == 0x65) {
    local_144 = 0;
    local_148 = 0;
  }
  else if ((uVar9 - 0x66 < 2) || (uVar9 == 7)) {
    local_144 = 1;
    local_148 = 0;
  }
  if (local_144 != 0) {
    effective__10CGCharaObjFiiP8CGPrgObjRi(gCharaObj,uVar9,param_3,gPrgObj,&local_148);
  }
  uVar11 = 0;
  if (local_148 == 0) goto LAB_8010f174;
  if (param_3 < 0x1f5) {
    sVar22 = 1;
  }
  else {
    sVar22 = *(short *)(Game.game.unkCFlatData0[2] + iVar24 + 2);
  }
  if ((sVar22 == 1) ||
     (((sVar22 == 9 &&
       (uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                           (gCharaObj), (uVar12 & 0xad) == 0xad)) &&
      (uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj),
      (uVar12 & 0x6d) == 0x6d)))) {
    if (uVar9 == 0x1c) {
LAB_8010e278:
      bVar5 = false;
      bVar4 = false;
      bVar18 = false;
      uVar12 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 6);
      if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
         (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
        bVar18 = true;
      }
      if (bVar18) {
        uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
        uVar11 = countLeadingZeros(0x6d - (uVar11 & 0x6d));
        if ((uVar11 >> 5 & 0xff) != 0) {
          bVar4 = true;
        }
      }
      if ((bVar4) && ((gPrgObj->object).m_scriptHandle[0xed] != (void *)0x0)) {
        bVar5 = true;
      }
      pCVar19 = gPrgObj;
      if (bVar5) {
        pCVar19 = (CGPrgObj *)Game.game.m_partyObjArr[0];
      }
      uVar23 = (uint)*(ushort *)
                      ((((CGCharaObj *)&pCVar19->object)->gPrgObj).object.m_scriptHandle + 8);
      uStack_84 = uVar12 + uVar23 ^ 0x80000000;
      local_80 = (double)CONCAT44(0x43300000,
                                  (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x2e));
      local_88 = 0x43300000;
      dVar25 = (double)(FLOAT_80331984 * (float)(local_80 - DOUBLE_80331978) + FLOAT_80331980);
      uVar14 = (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x22);
      iVar6 = (int)(dVar25 * (double)(float)((double)CONCAT44(0x43300000,uStack_84) -
                                            DOUBLE_80331968));
      local_90 = (double)(longlong)iVar6;
      iVar6 = iVar6 - uVar14;
      iVar21 = 1;
      if (0 < iVar6) {
        iVar21 = iVar6;
      }
      uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
      uVar11 = countLeadingZeros(0x6d - (uVar11 & 0x6d));
      if ((uVar11 >> 5 & 0xff) == 0) {
        uVar20 = 0;
      }
      else {
        uVar20 = (uint)*(byte *)((int)(gPrgObj->object).m_scriptHandle + 0xbde);
      }
      uVar11 = iVar21 + uVar20;
      Printf__7CSystemFPce(dVar25,&System,&DAT_801dc724,uVar12,uVar23,uVar14,uVar20,uVar11);
    }
    else {
      if (uVar9 < 0x1c) {
        if (uVar9 == 4) goto LAB_8010e278;
        if (uVar9 < 4) {
          if (uVar9 < 2) goto LAB_8010e278;
        }
        else if (uVar9 == 10) {
          uVar11 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                             (gCharaObj);
          if (((uVar11 & 0xad) == 0xad) && (gCharaObj->field_0x6c2 != '\0')) {
            uVar11 = 1;
          }
          else {
            local_88 = 0x43300000;
            uStack_84 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + local_140 * 2 + 0x26)
            ;
            local_80 = (double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)
                                               ((gCharaObj->gPrgObj).object.m_scriptHandle + 7));
            uVar12 = (uint)((float)(local_80 - DOUBLE_80331978) *
                           (FLOAT_80331984 *
                            (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331978) +
                           FLOAT_80331980));
            local_90 = (double)(longlong)(int)uVar12;
            uVar11 = 1;
            if (0 < (int)uVar12) {
              uVar11 = uVar12;
            }
            uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc
                                 ))(gCharaObj);
            if ((uVar12 & 0xad) == 0xad) {
              gCharaObj->field_0x6c2 = 1;
            }
          }
          Printf__7CSystemFPce(&System,&DAT_801dc760,uVar11);
          uVar13 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,10,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,10,uVar13);
          goto LAB_8010ea88;
        }
      }
      else {
        if (uVar9 == 100) {
LAB_8010dfb4:
          if (sVar3 == 0x1f8) {
            uVar12 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 6);
          }
          else {
            uVar12 = 0;
          }
          uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
          if (((uVar11 & 0x6d) == 0x6d) && (param_3 == 0x206)) {
            fVar7 = gPrgObj[1].object.m_extraMoveVec.y;
            fVar15 = gPrgObj[1].object.m_bodyOffset.y;
            if ((int)fVar15 < (int)fVar7 * 3) {
              if ((int)fVar7 << 1 <= (int)fVar15) {
                uVar12 = uVar12 << 1;
              }
            }
            else {
              uVar12 = uVar12 << 2;
            }
          }
          uVar23 = (uint)*(ushort *)((int)(gPrgObj->object).m_scriptHandle + 0x1e);
          uStack_84 = uVar12 + uVar23 ^ 0x80000000;
          local_90 = (double)CONCAT44(0x43300000,
                                      (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x2c));
          local_88 = 0x43300000;
          dVar25 = (double)(FLOAT_80331984 * (float)(local_90 - DOUBLE_80331978) + FLOAT_80331980);
          uVar14 = (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x22);
          iVar6 = (int)(dVar25 * (double)(float)((double)CONCAT44(0x43300000,uStack_84) -
                                                DOUBLE_80331968));
          local_80 = (double)(longlong)iVar6;
          iVar6 = iVar6 - uVar14;
          iVar21 = 1;
          if (0 < iVar6) {
            iVar21 = iVar6;
          }
          bVar4 = false;
          uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
          uVar11 = countLeadingZeros(0x6d - (uVar11 & 0x6d));
          if (((uVar11 >> 5 & 0xff) != 0) && (sVar3 == 0x1f8)) {
            bVar4 = true;
          }
          if (bVar4) {
            uVar20 = (uint)*(byte *)((int)(gPrgObj->object).m_scriptHandle + 0xbdd);
          }
          else {
            uVar20 = 0;
          }
          uVar11 = iVar21 + uVar20;
          if (sVar2 != 0) {
            local_88 = 0x43300000;
            uStack_84 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x42);
            local_80 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
            uVar11 = (uint)((float)(local_80 - DOUBLE_80331968) *
                           (FLOAT_80331984 *
                            (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331978) +
                           FLOAT_80331980));
            local_90 = (double)(longlong)(int)uVar11;
          }
          Printf__7CSystemFPce(dVar25,&System,&DAT_801dc6e8,uVar12,uVar23,uVar14,uVar20,uVar11);
          if ((((((uVar9 != 0x6a) &&
                 (uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))
                                     (gPrgObj), (uVar12 & 0x6d) == 0x6d)) &&
                (uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable
                                      + 0xc))(gCharaObj), (uVar12 & 0xad) == 0xad)) &&
               (((*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle[9] + 0xfe) & 0x100) !=
                 0 && ((Game.game.m_gameWork.m_chaliceElement & 4U) == 0)))) &&
              (*(short *)((int)(gPrgObj->object).m_scriptHandle + 0x2e) == 0)) &&
             ((gPrgObj->m_lastStateId != 6 ||
              (1 < (*(ushort *)
                     (Game.game.unkCFlatData0[2] +
                      (int)gPrgObj[1].object.base_object.object.m_thisBase * 0x48 + 10) & 0xff)))))
          {
            setSta__10CGCharaObjFii(gPrgObj,4,0x19);
            changeStat__8CGPrgObjFiii(gPrgObj,10,0,0);
            addHp__10CGCharaObjFiP8CGPrgObj((CGCharaObj *)gPrgObj,0xffffffff,(CGPrgObj *)0x0);
          }
          goto LAB_8010ea88;
        }
        if (uVar9 < 100) {
          if ((uVar9 < 0x26) && (0x23 < uVar9)) goto LAB_8010dfb4;
        }
        else if ((uVar9 < 0x6b) && (0x68 < uVar9)) goto LAB_8010dfb4;
      }
      Printf__7CSystemFPce(&System,&DAT_801dc778,uVar9);
    }
  }
  else if ((sVar22 == 8) ||
          (((sVar22 == 9 &&
            (uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable +
                                  0xc))(gCharaObj), (uVar12 & 0x6d) == 0x6d)) &&
           (uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))
                               (gPrgObj), (uVar12 & 0xad) == 0xad)))) {
    if (uVar9 == 0x1c) {
LAB_8010e724:
      uStack_6c = *(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x22) ^ 0x80000000;
      local_68 = (double)CONCAT44(0x43300000,
                                  (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x32));
      local_70 = 0x43300000;
      iVar6 = (int)((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331968) *
                   (FLOAT_80331984 * (float)(local_68 - DOUBLE_80331978) + FLOAT_80331980));
      local_78 = (double)(longlong)iVar6;
      uVar12 = ((uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 6) +
               (uint)*(ushort *)((gPrgObj->object).m_scriptHandle + 8)) - iVar6;
      uVar11 = 1;
      if (0 < (int)uVar12) {
        uVar11 = uVar12;
      }
      Printf__7CSystemFPce(&System,&DAT_801dc7bc);
    }
    else {
      if (uVar9 < 0x1c) {
        if (uVar9 == 4) goto LAB_8010e724;
        if (uVar9 < 4) {
          if (uVar9 < 3) goto LAB_8010e724;
        }
        else if (uVar9 == 10) {
          local_70 = 0x43300000;
          uStack_6c = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + local_140 * 2 + 0x26);
          local_68 = (double)CONCAT44(0x43300000,
                                      (uint)*(ushort *)((gPrgObj->object).m_scriptHandle + 7));
          uVar12 = (uint)((float)(local_68 - DOUBLE_80331978) *
                         (FLOAT_80331984 *
                          (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331978) +
                         FLOAT_80331980));
          local_78 = (double)(longlong)(int)uVar12;
          uVar11 = 1;
          if (0 < (int)uVar12) {
            uVar11 = uVar12;
          }
          Printf__7CSystemFPce(&System,&DAT_801dc7ec,uVar11);
          goto LAB_8010ea88;
        }
      }
      else {
        if (uVar9 == 100) {
LAB_8010e61c:
          uStack_84 = *(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x22) ^
                      0x80000000;
          local_80 = (double)CONCAT44(0x43300000,
                                      (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x30));
          local_88 = 0x43300000;
          iVar6 = (int)((float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331968) *
                       (FLOAT_80331984 * (float)(local_80 - DOUBLE_80331978) + FLOAT_80331980));
          local_90 = (double)(longlong)iVar6;
          uVar12 = ((uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 6) +
                   (uint)*(ushort *)((int)(gPrgObj->object).m_scriptHandle + 0x1e)) - iVar6;
          uVar11 = 1;
          if (0 < (int)uVar12) {
            uVar11 = uVar12;
          }
          if (sVar2 != 0) {
            uStack_6c = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x42);
            local_70 = 0x43300000;
            local_78 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
            uVar11 = (uint)((float)(local_78 - DOUBLE_80331968) *
                           (FLOAT_80331984 *
                            (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331978) +
                           FLOAT_80331980));
            local_68 = (double)(longlong)(int)uVar11;
          }
          Printf__7CSystemFPce(&System,&DAT_801dc788);
          goto LAB_8010ea88;
        }
        if (uVar9 < 100) {
          if ((uVar9 < 0x26) && (0x23 < uVar9)) goto LAB_8010e61c;
        }
        else if ((uVar9 < 0x6b) && (0x68 < uVar9)) goto LAB_8010e61c;
      }
      Printf__7CSystemFPce(&System,&DAT_801dc778,uVar9);
    }
  }
  else if (((sVar22 == 9) &&
           (uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc
                                 ))(gCharaObj), (uVar12 & 0x2d) == 0x2d)) &&
          ((uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))
                               (gPrgObj), (uVar12 & 0xad) == 0xad ||
           (uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))
                               (gPrgObj), (uVar12 & 0x1d) == 0x1d)))) {
    if (uVar9 == 4) {
LAB_8010e928:
      uVar12 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 6);
      uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
      uVar11 = countLeadingZeros(0xad - (uVar11 & 0xad));
      if ((uVar11 >> 5 & 0xff) == 0) {
        uVar8 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 0x30);
      }
      else {
        uVar8 = *(ushort *)((gPrgObj->object).m_scriptHandle + 8);
      }
      uVar14 = (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x22);
      uVar11 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
      uVar11 = countLeadingZeros(0xad - (uVar11 & 0xad));
      fVar7 = FLOAT_80331964;
      if ((uVar11 >> 5 & 0xff) != 0) {
        local_68 = (double)CONCAT44(0x43300000,
                                    (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x32));
        fVar7 = FLOAT_80331984 * (float)(local_68 - DOUBLE_80331978) + FLOAT_80331980;
      }
      uStack_6c = uVar14 ^ 0x80000000;
      local_70 = 0x43300000;
      iVar6 = (int)((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331968) * fVar7);
      local_78 = (double)(longlong)iVar6;
      uVar23 = (uVar12 + uVar8) - iVar6;
      uVar11 = 1;
      if (0 < (int)uVar23) {
        uVar11 = uVar23;
      }
      Printf__7CSystemFPce(&System,&DAT_801dc804,uVar12,(uint)uVar8,uVar14,uVar11);
    }
    else {
      if (uVar9 < 4) {
        if (uVar9 < 2) goto LAB_8010e928;
      }
      else if (uVar9 == 0x25) {
        uVar11 = 10;
        if (param_3 == 0x4aa) {
          uVar11 = 1;
        }
        goto LAB_8010ea88;
      }
      Printf__7CSystemFPce(&System,&DAT_801dc778,uVar9);
    }
  }
LAB_8010ea88:
  if (((uVar9 != 4) &&
      (((uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj),
        (uVar12 & 0xad) != 0xad || ((gPrgObj->object).m_scriptHandle[4] != (void *)0x6)) ||
       (uVar9 != 0x6a)))) &&
     (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x46) != 0)) {
    setSta__10CGCharaObjFii(gCharaObj,4,0);
  }
  if (((*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) != 0) && (uVar9 != 2)) &&
     (uVar9 != 0)) {
    setSta__10CGCharaObjFii(gCharaObj,0,0);
  }
  if (local_60 != 0) {
    if ((int)uVar11 < 2) {
      uVar11 = 0;
    }
    else {
      uVar11 = 1;
    }
  }
  uVar14 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                     (gCharaObj);
  uVar12 = uVar11;
  if ((((uVar14 & 0xad) == 0xad) &&
      (ppvVar16 = (gCharaObj->gPrgObj).object.m_scriptHandle,
      (*(ushort *)((int)ppvVar16[9] + 0xfe) & 4) != 0)) &&
     ((*(short *)((int)ppvVar16 + 0x52) == 0 && (uVar12 = 1, (int)uVar11 < 1)))) {
    uVar12 = uVar11;
  }
  uVar11 = uVar12;
  if ((((*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x76) == 0) &&
       (uVar14 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                           (gCharaObj), (uVar14 & 0xad) == 0xad)) &&
      ((*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle[9] + 0xfe) & 1) != 0)) &&
     ((uVar9 != 0x1c && (uVar11 = 1, (int)uVar12 < 1)))) {
    uVar11 = uVar12;
  }
  uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
  if ((((uVar12 & 0x2d) == 0x2d) && (-1 < (int)gPrgObj[1].object.m_capsuleHalfHeight)) &&
     (gPrgObj[1].object.m_nearColRadius != 0.0)) {
    Printf__7CSystemFPce(&System,&DAT_801dc840);
    uVar11 = uVar11 * (int)gPrgObj[1].object.m_nearColRadius;
  }
  if (uVar11 != 0) {
    addHp__10CGCharaObjFiP8CGPrgObj(gCharaObj,-uVar11,gPrgObj);
    uVar12 = countLeadingZeros((uint)*(ushort *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7));
    uVar12 = uVar12 >> 5 & 0xff;
    if (uVar12 != 0) {
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
                (gCharaObj,0,param_3,gPrgObj);
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                (gPrgObj,1,param_3,gCharaObj);
    }
    if (((*(ushort *)(Game.game.unkCFlatData0[2] + iVar24 + 0x32) & 1) == 0) &&
       ((uVar14 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj),
        (uVar14 & 0x6d) != 0x6d || ((int)gPrgObj[1].object.m_capsuleHalfHeight < 0)))) {
      if ((sVar3 == 0x1f8) || (local_5c != 2)) {
        if (sVar3 == 0x1f8) {
          (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
                    (gCharaObj,0x13,param_3,gPrgObj);
          (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                    (gPrgObj,0xf,param_3,gCharaObj);
          if (uVar12 != 0) {
            (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                      (gPrgObj,10,param_3,gCharaObj);
          }
        }
        else {
          (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
                    (gCharaObj,0x12,param_3,gPrgObj);
          (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                    (gPrgObj,0xe,param_3,gCharaObj);
          if (uVar12 != 0) {
            (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                      (gPrgObj,9,param_3,gCharaObj);
          }
        }
      }
    }
    else {
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
                (gCharaObj,0x15,param_3,gPrgObj);
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                (gPrgObj,0x11,param_3,gCharaObj);
      if (uVar12 != 0) {
        (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                  (gPrgObj,0xc,param_3,gCharaObj);
      }
      pCVar19 = gPrgObj;
      for (iVar24 = 0; iVar24 < (int)gPrgObj[1].object.m_nearColRadius; iVar24 = iVar24 + 1) {
        fVar7 = pCVar19[1].object.m_worldPosition.x;
        (**(code **)(*(int *)((int)fVar7 + 0x48) + 0x4c))(fVar7,0x11,param_3,gCharaObj);
        if (uVar12 != 0) {
          fVar7 = pCVar19[1].object.m_worldPosition.x;
          (**(code **)(*(int *)((int)fVar7 + 0x48) + 0x4c))(fVar7,0xc,param_3,gCharaObj);
        }
        pCVar19 = (CGPrgObj *)&(pCVar19->object).base_object.object.m_freeListNode;
      }
    }
    putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
    uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                       (gCharaObj);
    if ((uVar12 & 0xad) == 0xad) {
      ppvVar16 = (gCharaObj->gPrgObj).object.m_scriptHandle;
      iVar24 = Rand__5CMathFUl(&Math,3);
      pvVar17 = ppvVar16[9];
      playSe3D__8CGPrgObjFiiiiP3Vec
                (&gCharaObj->gPrgObj,
                 (uint)*(ushort *)((int)pvVar17 + 0x192) +
                 (uint)*(ushort *)((int)pvVar17 + 400) * 1000 + 6 + iVar24,0x32,0x96,0,0);
    }
  }
  uVar12 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
  if (((uVar12 & 0x6d) == 0x6d) && (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7) != 0)
     ) {
    fVar7 = gPrgObj[1].object.m_capsuleHalfHeight;
    if ((int)fVar7 < 0) {
      if ((((MiniGamePcs._25732_4_ & 0x20) != 0) || (gPrgObj[1].object.m_rotationZ == 2.8026e-45))
         && (calcRegist__10CGCharaObjFiiRiRiRii
                       (gCharaObj,0x69,param_3,&local_140,&local_144,&local_148,0), local_144 != 0))
      {
        uVar12 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                           (gCharaObj);
        uVar12 = countLeadingZeros(0xad - (uVar12 & 0xad));
        if ((uVar12 >> 5 & 0xff) == 0) {
          uVar12 = 0x32;
        }
        else {
          uVar12 = (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle[9] + 0x19a);
        }
        if ((uVar12 != 0) && ((MiniGamePcs._25732_4_ & 0x20) != 0)) {
          uVar12 = 100;
        }
        if ((uVar12 != 0) && (uVar14 = Rand__5CMathFUl(&Math,100), uVar14 <= uVar12)) {
          if (((gCharaObj->gPrgObj).object.m_bgColMask & 0x80000) == 0) {
            Printf__7CSystemFPce(&System,&DAT_801dc890);
          }
          else {
            effective__10CGCharaObjFiiP8CGPrgObjRi(gCharaObj,0x69,param_3,gPrgObj,&local_148);
          }
        }
      }
    }
    else {
      if (fVar7 == 1.4013e-45) {
        unaff_r18 = 0;
        unaff_r17 = 0x20b;
        unaff_r16 = 0x7e2;
      }
      else if ((int)fVar7 < 1) {
        if (-1 < (int)fVar7) {
          unaff_r18 = 1;
          unaff_r17 = 0x207;
          unaff_r16 = 0x7e1;
        }
      }
      else if ((int)fVar7 < 3) {
        unaff_r18 = 4;
        unaff_r17 = 0x20f;
        unaff_r16 = 0x7e3;
      }
      calcRegist__10CGCharaObjFiiRiRiRii
                (gCharaObj,unaff_r18,unaff_r17,&local_140,&local_144,&local_148,1);
      if (local_144 != 0) {
        if (((gCharaObj->gPrgObj).object.m_bgColMask & 0x80000) == 0) {
          Printf__7CSystemFPce(&System,&DAT_801dc858);
        }
        else {
          effective__10CGCharaObjFiiP8CGPrgObjRi(gCharaObj,unaff_r18,unaff_r17,gPrgObj,&local_148);
          playSe3D__8CGPrgObjFiiiiP3Vec(&gCharaObj->gPrgObj,unaff_r16,0x32,0x96,0,0);
        }
      }
    }
  }
  (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x78))(gPrgObj,gCharaObj);
LAB_8010f174:
  if ((((sVar3 != 0x1f8) && (local_5c == 2)) && ((local_144 != 0 || (uVar11 != 0)))) &&
     (((uVar9 != 0x66 && (uVar9 != 0x67)) && (uVar9 != 0x65)))) {
    uVar9 = countLeadingZeros((uint)*(ushort *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7));
    (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
              (gCharaObj,0x14,param_3,gPrgObj);
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
              (gPrgObj,0x10,param_3,gCharaObj);
    if ((uVar9 >> 5 & 0xff) != 0) {
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
                (gPrgObj,0xb,param_3,gCharaObj);
    }
  }
  return;
}

