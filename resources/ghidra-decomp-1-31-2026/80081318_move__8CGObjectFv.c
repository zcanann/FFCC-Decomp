// Function: move__8CGObjectFv
// Entry: 80081318
// Size: 2752 bytes

/* WARNING: Removing unreachable block (ram,0x80081db0) */
/* WARNING: Removing unreachable block (ram,0x80081da8) */
/* WARNING: Removing unreachable block (ram,0x80081da0) */
/* WARNING: Removing unreachable block (ram,0x80081d98) */
/* WARNING: Removing unreachable block (ram,0x80081340) */
/* WARNING: Removing unreachable block (ram,0x80081338) */
/* WARNING: Removing unreachable block (ram,0x80081330) */
/* WARNING: Removing unreachable block (ram,0x80081328) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void move__8CGObjectFv(CGObject *gObject)

{
  byte bVar1;
  uint8_t uVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  ushort uVar9;
  bool bVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  uint local_148;
  Vec VStack_144;
  Vec VStack_138;
  Vec local_12c;
  Vec VStack_120;
  Vec local_114;
  Vec VStack_108;
  Vec local_fc;
  Vec local_f0;
  Mtx MStack_e4;
  Mtx MStack_b4;
  Mtx MStack_84;
  
  bVar4 = false;
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    bVar4 = true;
  }
  if (!bVar4) {
    return;
  }
  if (Game.game.m_currentMapId == 0x21) {
LAB_800813e4:
    if ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1d |
             (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 3)) < 0) {
      (gObject->m_groundHitOffset).y = FLOAT_80330350;
    }
  }
  else {
    bVar1 = *(byte *)&gObject->m_weaponNodeFlags;
    if ((-1 < (int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5))) ||
       ((int)((uint)bVar1 << 0x1c | (uint)(bVar1 >> 4)) < 0)) goto LAB_800813e4;
    PSVECAdd(&gObject->m_groundHitOffset,&gObject->m_bodyOffset,&gObject->m_groundHitOffset);
    if ((gObject->m_groundHitOffset).y < FLOAT_80330428) {
      (gObject->m_groundHitOffset).y = FLOAT_80330428;
    }
  }
  bVar5 = false;
  bVar4 = false;
  (gObject->m_groundHitOffset).y = (gObject->m_groundHitOffset).y + gObject->m_gravityY;
  bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1);
  uVar7 = (uint)bVar1;
  if ((int)(uVar7 << 0x1a | (uint)(bVar1 >> 6)) < 0) {
    iVar11 = 0;
    if ((int)(uVar7 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
      local_f0.x = (gObject->m_moveVec).y;
      local_f0.y = (gObject->m_moveVec).z;
      local_f0.z = gObject->m_moveSpeed;
    }
    else {
      PSVECSubtract((Vec *)&(gObject->m_moveVec).y,&gObject->m_worldPosition,&local_f0);
    }
    if ((Game.game.m_currentMapId != 0x21) &&
       (bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1),
       -1 < (int)((uint)bVar1 << 0x1e | (uint)(bVar1 >> 2)))) {
      local_f0.y = FLOAT_80330350;
    }
    dVar13 = (double)PSVECMag(&local_f0);
    if ((double)FLOAT_80330350 == dVar13) {
      iVar11 = 1;
    }
    else {
      bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1);
      if ((int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
        PSVECNormalize(&local_f0,&local_f0);
        PSVECScale((float)gObject->m_moveTimer,&local_f0,&local_f0);
      }
      else if ((double)(float)gObject->m_moveTimer <= dVar13) {
        PSVECNormalize(&local_f0,&local_f0);
        PSVECScale((float)gObject->m_moveTimer,&local_f0,&local_f0);
      }
      else {
        iVar11 = 1;
      }
    }
    gObject->m_turnFrames = gObject->m_turnFrames - 1;
    if ((int)gObject->m_turnFrames < 1) {
      iVar11 = 2;
    }
    bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1);
    uVar7 = (uint)bVar1 << 0x1b | (uint)(bVar1 >> 5);
    if (((-1 < (int)uVar7) && (iVar11 != 0)) || (((int)uVar7 < 0 && (iVar11 == 2)))) {
      *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
           *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf;
      local_148 = countLeadingZeros(2 - iVar11);
      local_148 = local_148 >> 5;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,gObject,2,7,1,&local_148,(CStack *)0x0);
    }
    bVar5 = true;
  }
  else {
    uVar2 = gObject->m_animStateMisc;
    if ((((((char)uVar2 < '\0') || ('\x03' < (char)uVar2)) || (-1 < (int)(uVar7 << 0x18))) ||
        (-1 < (int)(uVar7 << 0x19 | (uint)(bVar1 >> 7)))) ||
       ((Game.game.m_gameWork.m_menuStageMode != '\0' &&
        ((Game.game.m_gameWork.m_menuStageMode == '\0' || (uVar2 != '\0')))))) goto LAB_80081d58;
    uVar7 = (uint)(char)uVar2;
    bVar10 = false;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar10 = true;
    }
    if (bVar10) {
      uVar6 = 0;
    }
    else {
      uVar6 = *(ushort *)
               (&Pad.field_0x4 +
               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    bVar10 = false;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar10 = true;
    }
    if (bVar10) {
      uVar8 = 0;
    }
    else {
      uVar8 = *(ushort *)
               (&Pad.field_0x8 +
               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    bVar10 = false;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar10 = true;
    }
    if (bVar10) {
      uVar9 = 0;
    }
    else {
      uVar9 = *(ushort *)
               (&Pad.field_0x12 +
               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar6 != 0) && (uVar9 != 0)) {
      uVar6 = uVar6 | uVar9;
    }
    local_f0.z = FLOAT_80330350;
    local_f0.y = FLOAT_80330350;
    local_f0.x = FLOAT_80330350;
    if ((MiniGamePcs._25732_4_ & 0x100) != 0) {
      bVar10 = false;
      uVar7 = (uint)(char)gObject->m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
        bVar10 = true;
      }
      if (!bVar10) {
        local_f0.x = *(float *)(&Pad.field_0x24 +
                               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)
                               ) * 0x54);
      }
      bVar10 = false;
      local_f0.x = FLOAT_80330350 - local_f0.x;
      uVar7 = (uint)(char)gObject->m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
        bVar10 = true;
      }
      if (!bVar10) {
        local_f0.z = *(float *)(&Pad.field_0x28 +
                               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)
                               ) * 0x54);
      }
      local_f0.z = FLOAT_80330350 + local_f0.z;
      if ((local_f0.x != FLOAT_80330350) || (local_f0.z != FLOAT_80330350)) {
        bVar4 = true;
      }
    }
    if (!bVar4) {
      if ((uVar6 & 1) != 0) {
        local_f0.x = local_f0.x + FLOAT_80330338;
      }
      if ((uVar6 & 2) != 0) {
        local_f0.x = local_f0.x - FLOAT_80330338;
      }
      if ((uVar6 & 8) != 0) {
        local_f0.z = local_f0.z + FLOAT_80330338;
      }
      if ((uVar6 & 4) != 0) {
        local_f0.z = local_f0.z - FLOAT_80330338;
      }
    }
    if (((MiniGamePcs._25732_4_ & 0x40) == 0) && ((uVar8 & 0x1000) != 0)) {
      if ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1b |
               (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 5)) < 0) {
        PSVECAdd(&gObject->m_groundHitOffset,&gObject->m_jumpOffset,&gObject->m_groundHitOffset);
      }
      else {
        (gObject->m_worldPosition).y = (gObject->m_worldPosition).y + FLOAT_80330418;
      }
    }
    if (Game.game.m_currentMapId == 0x21) {
      PSMTXCopy((Mtx *)&CameraPcs.field_0x64,&MStack_84);
      local_f0.x = -local_f0.x;
      local_f0.z = -local_f0.z;
      local_f0.y = FLOAT_80330350;
      PSMTXMultVec(&MStack_84,&local_f0,&local_f0);
    }
  }
  dVar13 = (double)FLOAT_80330350;
  if ((((double)local_f0.x != dVar13) || ((double)local_f0.z != dVar13)) ||
     ((double)local_f0.y != dVar13)) {
    fVar3 = (float)CameraPcs._248_4_;
    if (bVar5) {
      fVar3 = FLOAT_80330350;
    }
    dVar16 = (double)fVar3;
    dVar13 = (double)atan2((double)local_f0.x,(double)local_f0.z);
    dVar17 = (double)(float)dVar13;
    dVar13 = (double)sin(dVar16);
    dVar15 = (double)(float)dVar13;
    dVar13 = (double)cos(dVar16);
    if (Game.game.m_currentMapId != 0x21) {
      dVar12 = (double)local_f0.z;
      local_f0.z = (float)((double)local_f0.x * dVar15 +
                          (double)(float)(dVar12 * (double)(float)dVar13));
      local_f0.x = (float)((double)local_f0.x * (double)(float)dVar13 -
                          (double)(float)(dVar12 * dVar15));
    }
    if (!bVar5) {
      dVar13 = (double)gObject->m_moveBaseSpeed;
      if ((bVar4) && ((MiniGamePcs._25732_4_ & 0x200) != 0)) {
        dVar15 = (double)PSVECMag(&local_f0);
        dVar13 = (double)(float)(dVar13 * (double)(float)((double)FLOAT_8033042c * dVar15));
      }
      PSVECNormalize(&local_f0,&local_f0);
      bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1);
      if ((((int)((uint)bVar1 << 0x18) < 0) && ((int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0)
          ) && (gObject->m_ownerType == '\0')) {
        if ((MiniGamePcs._25732_4_ & 2) != 0) {
          dVar13 = (double)(float)(dVar13 * (double)FLOAT_8033042c);
        }
        if (CFlat._4780_4_ == 1) {
          local_fc.x = (Game.game.m_partyMinX + Game.game.m_partyMaxX) * FLOAT_80330368;
          local_fc.y = (Game.game.m_partyMinY + Game.game.m_partyMaxY) * FLOAT_80330368;
          local_fc.z = (Game.game.m_partyMinZ + Game.game.m_partyMaxZ) * FLOAT_80330368;
          PSVECSubtract(&gObject->m_worldPosition,&local_fc,&VStack_108);
          dVar12 = (double)PSVECMag(&VStack_108);
          PSVECNormalize(&VStack_108,&VStack_108);
          dVar14 = (double)PSVECDotProduct(&local_f0,&VStack_108);
          dVar15 = (double)FLOAT_80330350;
          if (dVar15 < dVar14) {
            dVar12 = (double)(float)(dVar12 / (double)(float)CFlat._4784_4_);
            if ((dVar15 <= dVar12) && (dVar15 = dVar12, (double)FLOAT_80330338 < dVar12)) {
              dVar15 = (double)FLOAT_80330338;
            }
            dVar13 = (double)(float)(dVar13 * -(double)(float)(dVar15 * dVar15 -
                                                              (double)FLOAT_80330338));
          }
        }
      }
      if (((uint)(gObject->m_radiusCtrl).x & 0x400000) != 0) {
        dVar13 = (double)(float)(dVar13 * (double)FLOAT_80330364);
      }
      PSVECScale((float)dVar13,&local_f0,&local_f0);
    }
    PSVECAdd(&gObject->m_groundHitOffset,&local_f0,&gObject->m_groundHitOffset);
    if ((!bVar5) ||
       (bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1),
       (int)((uint)bVar1 << 0x1c | (uint)(bVar1 >> 4)) < 0)) {
      if (Game.game.m_currentMapId == 0x21) {
        dVar13 = (double)PSVECSquareMag(&gObject->m_groundHitOffset);
        if ((double)FLOAT_80330430 < dVar13) {
          dVar13 = (double)atan2((double)(gObject->m_worldPosition).x,
                                 (double)(gObject->m_worldPosition).z);
          PSMTXRotRad((float)dVar13,&MStack_b4,0x79);
          local_114.x = DAT_801d9b70;
          local_114.y = DAT_801d9b74;
          local_114.z = DAT_801d9b78;
          local_12c.x = DAT_801d9b7c;
          local_12c.y = DAT_801d9b80;
          local_12c.z = DAT_801d9b84;
          PSVECNormalize(&gObject->m_worldPosition,&VStack_120);
          PSVECDotProduct(&local_114,&VStack_120);
          dVar13 = (double)acos();
          PSMTXRotRad((float)dVar13,&MStack_e4,0x78);
          PSMTXConcat(&MStack_b4,&MStack_e4,&MStack_b4);
          PSVECNormalize(&gObject->m_groundHitOffset,&VStack_138);
          PSMTXMultVec(&MStack_b4,&local_12c,&local_12c);
          PSVECDotProduct(&local_12c,&VStack_138);
          dVar13 = (double)acos();
          dVar15 = (double)(float)dVar13;
          PSVECCrossProduct(&local_12c,&VStack_138,&VStack_144);
          dVar13 = (double)PSVECDotProduct(&VStack_120,&VStack_144);
          if (dVar13 < (double)FLOAT_80330350) {
            dVar15 = -dVar15;
          }
          gObject->m_rotTargetY = (float)dVar15;
        }
      }
      else {
        gObject->m_rotTargetY = (float)(dVar17 - dVar16);
      }
    }
    if ((bVar5) &&
       (bVar1 = *(byte *)((int)&gObject->m_weaponNodeFlags + 1),
       -1 < (int)((uint)bVar1 << 0x1d | (uint)(bVar1 >> 3)))) {
      gObject->m_animSlotSel = *(int8_t *)((int)&gObject->m_shieldNodeFlags + 1);
      return;
    }
    gObject->m_animSlotSel = *(int8_t *)&gObject->m_animStartFrame;
    return;
  }
LAB_80081d58:
  dVar13 = (double)DstRot__5CMathFff((double)gObject->m_rotTargetY,(double)gObject->m_rotBaseY,&Math
                                    );
  gObject->m_animSlotSel = gObject->m_animQueue[(DOUBLE_803303e8 < ABS(dVar13)) - 0x41];
  return;
}

