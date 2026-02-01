// Function: onFrameStat__9CGItemObjFv
// Entry: 80125fb0
// Size: 3416 bytes

/* WARNING: Removing unreachable block (ram,0x80126cec) */
/* WARNING: Removing unreachable block (ram,0x80126ce4) */
/* WARNING: Removing unreachable block (ram,0x80125fc8) */
/* WARNING: Removing unreachable block (ram,0x80125fc0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameStat__9CGItemObjFv(CGItemObj *gItemObj)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  float fVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  Vec *pVVar13;
  CCharaPcsCHandle *pCVar14;
  CModel *pCVar15;
  char *pcVar16;
  uint uVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  undefined4 local_a8;
  undefined4 local_a4;
  Vec local_a0;
  CVector CStack_94;
  float local_88;
  float local_84;
  float local_80;
  CVector CStack_7c;
  CVector CStack_70;
  CVector CStack_64;
  CVector local_58;
  Vec local_4c;
  undefined4 local_40;
  uint uStack_3c;
  
  fVar2 = FLOAT_80331bbc;
  fVar4 = FLOAT_80331bb0;
  fVar3 = FLOAT_80331b20;
  fVar9 = FLOAT_80331b18;
  switch((gItemObj->prgObj).m_lastStateId) {
  case 0:
    if ((*(int *)&gItemObj->field_0x550 == 0) &&
       (bVar1 = (gItemObj->prgObj).object.m_stateFlags0,
       (int)((uint)bVar1 << 0x1c | (uint)(bVar1 >> 4)) < 0)) {
      dVar19 = (double)FLOAT_80331b20;
      if (Game.game.unk_flat3_0xc7d0 == 0) {
        if (CFlat._4780_4_ == 1) {
          local_4c.x = (Game.game.m_partyMinX + Game.game.m_partyMaxX) * FLOAT_80331b3c;
          local_4c.y = (Game.game.m_partyMinY + Game.game.m_partyMaxY) * FLOAT_80331b3c;
          local_4c.z = (Game.game.m_partyMinZ + Game.game.m_partyMaxZ) * FLOAT_80331b3c;
          dVar19 = (double)PSVECDistance(&(gItemObj->prgObj).object.m_worldPosition,&local_4c);
        }
      }
      else {
        dVar19 = (double)PSVECDistance(&(gItemObj->prgObj).object.m_worldPosition,
                                       (Vec *)(Game.game.unk_flat3_0xc7d0 + 0x15c));
      }
      iVar11._0_1_ = (gItemObj->prgObj).object.m_moveAnimState;
      iVar11._1_1_ = (gItemObj->prgObj).object.m_moveAnimSubState;
      iVar11._2_1_ = (gItemObj->prgObj).object.m_randSeedLo;
      iVar11._3_1_ = (gItemObj->prgObj).object.m_randSeedHi;
      if ((iVar11 < 1) || (DOUBLE_80331ba0 < dVar19)) {
        Printf__7CSystemFPce(&System,&DAT_801dcf80);
        fVar9 = FLOAT_80331b20;
        (gItemObj->prgObj).object.m_bgDownDist = FLOAT_80331b54;
        (gItemObj->prgObj).object.m_stepSlopeLimit = fVar9;
        (gItemObj->prgObj).object.m_bgColMask = 1;
        EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle
                  ((CFlatRuntime2 *)&CFlat,(gItemObj->prgObj).object.m_charaModelHandle);
        changeStat__8CGPrgObjFiii(&gItemObj->prgObj,9,0,0);
      }
    }
    break;
  case 9:
    if ((gItemObj->prgObj).m_stateFrame == 8) {
      (gItemObj->prgObj).object.base_object.object.m_flags =
           (gItemObj->prgObj).object.base_object.object.m_flags & 0x7f | 0x80;
    }
    break;
  case 0xb:
    if ((gItemObj->prgObj).m_stateFrame == *(int *)&gItemObj->field_0x554) {
      pVVar13 = (Vec *)__ct__7CVectorFfff(FLOAT_80331b20,FLOAT_80331b20,FLOAT_80331b20,&CStack_64);
      bVar8 = false;
      if (Game.game.m_gameWork.m_menuStageMode != '\0') {
        bVar7 = false;
        bVar6 = false;
        bVar5 = false;
        if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
           (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
          bVar5 = true;
        }
        if (bVar5) {
          uVar10 = (**(code **)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x48) + 0xc))();
          uVar10 = countLeadingZeros(0x6d - (uVar10 & 0x6d));
          if ((uVar10 >> 5 & 0xff) != 0) {
            bVar6 = true;
          }
        }
        if ((bVar6) && (*(int *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3b4) != 0)) {
          bVar7 = true;
        }
        if (bVar7) {
          bVar8 = true;
        }
      }
      pcVar16 = &DAT_80331b84;
      if (bVar8) {
        pcVar16 = &DAT_80331b7c;
      }
      Attach__8CGObjectFP8CGObjectPcP3Vec
                ((CGObject *)gItemObj,*(int *)&gItemObj->field_0x550,pcVar16,pVVar13);
      changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0,0,0);
      (gItemObj->prgObj).object.m_bodyEllipsoidRadius = FLOAT_80331b20;
    }
    break;
  case 0xc:
  case 0xd:
    if ((gItemObj->prgObj).m_stateFrame == *(int *)&gItemObj->field_0x554) {
      if (((Game.game.m_gameWork.m_menuStageMode == '\0') ||
          (Game.game.m_gameWork.m_menuStageMode == '\0')) ||
         ((0xe < Game.game.m_gameWork.m_bossArtifactStageIndex ||
          ((uVar10 = (**(code **)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x48) + 0xc))(),
           (uVar10 & 0x6d) != 0x6d ||
           (*(int *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3b4) == 0)))))) {
        if (CFlat._4780_4_ == 1) {
          uVar10 = (**(code **)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x48) + 0xc))();
          if (((uVar10 & 0x6d) == 0x6d) &&
             (1 < *(ushort *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3e0))) {
            dVar19 = (double)FLOAT_80331b18;
          }
          else {
            dVar19 = (double)FLOAT_80331ba8;
          }
        }
        else {
          dVar19 = (double)FLOAT_80331b90;
        }
      }
      else {
        dVar19 = (double)FLOAT_80331b18;
      }
      dVar18 = (double)CalcSafePos__8CGObjectFiP8CGObjectP3Vec
                                 ((CGObject *)gItemObj,0x41,*(CGObject **)&gItemObj->field_0x550,
                                  &local_88);
      if ((double)FLOAT_80331b20 < dVar18) {
        moveVectorHRot__8CGObjectFfffi
                  ((double)(FLOAT_80331b8c + (*(CGObject **)&gItemObj->field_0x550)->m_rotBaseY),
                   (double)FLOAT_80331b20,(double)(float)(dVar18 / (double)FLOAT_80331b90),
                   *(CGObject **)&gItemObj->field_0x550,3);
      }
      Detach__8CGObjectFv((CGObject *)gItemObj);
      (gItemObj->prgObj).object.m_worldPosition.x = local_88;
      (gItemObj->prgObj).object.m_worldPosition.y = local_84;
      (gItemObj->prgObj).object.m_worldPosition.z = local_80;
      if ((gItemObj->prgObj).m_lastStateId != 0xc) {
        dVar19 = (double)FLOAT_80331b40;
      }
      dVar18 = (double)cos((double)*(float *)(*(int *)&gItemObj->field_0x550 + 0x1b4));
      dVar20 = (double)(float)dVar18;
      dVar18 = (double)sin((double)*(float *)(*(int *)&gItemObj->field_0x550 + 0x1b4));
      uVar12 = __ct__7CVectorFfff((float)dVar18,FLOAT_80331b54,(float)dVar20,&CStack_7c);
      MoveVector__8CGObjectFP3Vecfiiii(dVar19,(CGObject *)gItemObj,uVar12,1,0,1,0);
      *(undefined4 *)&gItemObj->field_0x550 = 0;
      fVar9 = FLOAT_80331b20;
      *(undefined4 *)&gItemObj->field_0x56c = 8;
      (gItemObj->prgObj).object.m_bodyEllipsoidRadius = fVar9;
    }
    if (*(int *)&gItemObj->field_0x554 <= (gItemObj->prgObj).m_stateFrame) {
      fVar9 = (gItemObj->prgObj).object.m_worldParamA;
      if ((fVar9 == 1.82169e-44) || (fVar9 == 1.96182e-44)) {
        if ((int)((uint)(gItemObj->prgObj).object.m_stateFlags0 << 0x18) < 0) {
          changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0x1f,0,0);
        }
      }
      else if ((int)((uint)(gItemObj->prgObj).object.m_stateFlags0 << 0x18) < 0) {
        changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0,0,0);
      }
    }
    break;
  case 0xe:
    iVar11 = (gItemObj->prgObj).m_stateFrame;
    if (iVar11 == 0) {
      (gItemObj->prgObj).object.m_bgColMask = 0;
      *(byte *)&(gItemObj->prgObj).object.m_weaponNodeFlags =
           *(byte *)&(gItemObj->prgObj).object.m_weaponNodeFlags & 0xef;
      (gItemObj->prgObj).object.m_groundHitOffset.z = fVar3;
      (gItemObj->prgObj).object.m_groundHitOffset.y = fVar3;
      (gItemObj->prgObj).object.m_groundHitOffset.x = fVar3;
    }
    else if (iVar11 == 4) {
      (gItemObj->prgObj).object.m_bgDownDist = FLOAT_80331b68;
      (gItemObj->prgObj).object.m_stepSlopeLimit = fVar3;
      EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle
                ((CFlatRuntime2 *)&CFlat,(gItemObj->prgObj).object.m_charaModelHandle);
    }
    else if (iVar11 == 0xc) {
      (gItemObj->prgObj).object.base_object.object.m_flags =
           (gItemObj->prgObj).object.base_object.object.m_flags & 0x7f | 0x80;
    }
    fVar4 = FLOAT_80331bac;
    fVar3 = FLOAT_80331b54;
    fVar9 = FLOAT_80331b3c;
    if (7 < (gItemObj->prgObj).m_stateFrame) {
      (gItemObj->prgObj).object.m_rotTargetY =
           (gItemObj->prgObj).object.m_rotTargetY + FLOAT_80331b54;
      fVar2 = (gItemObj->prgObj).object.m_worldPosition.x;
      (gItemObj->prgObj).object.m_worldPosition.x =
           fVar3 * (*(float *)(*(int *)&gItemObj->field_0x550 + 0x15c) - fVar2) + fVar2;
      fVar2 = (gItemObj->prgObj).object.m_worldPosition.y;
      (gItemObj->prgObj).object.m_worldPosition.y =
           fVar3 * ((fVar9 * *(float *)(*(int *)&gItemObj->field_0x550 + 0x188) +
                    *(float *)(*(int *)&gItemObj->field_0x550 + 0x160)) - fVar2) + fVar2;
      fVar9 = (gItemObj->prgObj).object.m_worldPosition.z;
      (gItemObj->prgObj).object.m_worldPosition.z =
           fVar3 * (*(float *)(*(int *)&gItemObj->field_0x550 + 0x164) - fVar9) + fVar9;
      (gItemObj->prgObj).object.m_rotationX = (gItemObj->prgObj).object.m_rotationX * fVar4;
      (gItemObj->prgObj).object.m_rotationY = (gItemObj->prgObj).object.m_rotationY * fVar4;
      (gItemObj->prgObj).object.m_rotationZ = (gItemObj->prgObj).object.m_rotationZ * fVar4;
    }
    break;
  case 0x1b:
    uStack_3c = (gItemObj->prgObj).m_stateFrame;
    if ((int)uStack_3c < 9) {
      uStack_3c = uStack_3c ^ 0x80000000;
      local_40 = 0x43300000;
      dVar19 = (double)sin((double)(FLOAT_80331b9c *
                                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331b70
                                           ) * FLOAT_80331b68));
      fVar9 = (float)dVar19;
      (gItemObj->prgObj).object.m_rotationZ = fVar9;
      (gItemObj->prgObj).object.m_rotationY = fVar9;
      (gItemObj->prgObj).object.m_rotationX = fVar9;
      if ((gItemObj->prgObj).m_stateFrame == 8) {
        changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0,0,0);
      }
    }
    break;
  case 0x1f:
    pppSetLocSlot__8CPartMngFiP3Vec
              (&PartMng,*(undefined4 *)&gItemObj->field_0x55c,
               &(gItemObj->prgObj).object.m_worldPosition);
    iVar11 = (gItemObj->prgObj).m_subState;
    if (iVar11 == 1) {
      if ((gItemObj->prgObj).m_subFrame == 0x7d) {
        EndParticleSlot__13CFlatRuntime2Fii
                  ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&gItemObj->field_0x55c);
      }
    }
    else if (((iVar11 < 1) && (-1 < iVar11)) && ((gItemObj->prgObj).m_subFrame == 0)) {
      if ((gItemObj->prgObj).object.m_worldParamA == 1.96182e-44) {
        uVar10 = 0x19;
        uVar17 = 0x1e;
      }
      else {
        uVar10 = 0x18;
        uVar17 = 0x1d;
      }
      putParticle__8CGPrgObjFiiP3Vecfi
                ((double)FLOAT_80331b18,&gItemObj->prgObj,uVar10 | 0x100,0,
                 &(gItemObj->prgObj).object.m_worldPosition,0);
      putParticle__8CGPrgObjFiiP3Vecfi
                ((double)FLOAT_80331b18,&gItemObj->prgObj,uVar17 | 0x100,
                 *(undefined4 *)&gItemObj->field_0x55c,&(gItemObj->prgObj).object.m_worldPosition,0)
      ;
      playSe3D__8CGPrgObjFiiiiP3Vec(&gItemObj->prgObj,0x1a,0x32,0x96,0,0);
      fVar9 = FLOAT_80331b20;
      (gItemObj->prgObj).object.m_displayFlags =
           (gItemObj->prgObj).object.m_displayFlags & 0xfffffffe;
      (gItemObj->prgObj).object.m_bgColMask = (gItemObj->prgObj).object.m_bgColMask & 0xfffffff1;
      (gItemObj->prgObj).object.m_moveOffset.z = fVar9;
      (gItemObj->prgObj).object.m_moveOffset.x = fVar9;
      (gItemObj->prgObj).object.m_bgColMask = (gItemObj->prgObj).object.m_bgColMask | 0x80000;
      pVVar13 = (Vec *)__ct__7CVectorFfff(fVar9,fVar9,fVar9,&CStack_94);
      SetDamageCol__8CGObjectFiPcffP3Vec
                ((double)FLOAT_80331b78,(double)FLOAT_80331b78,(CGObject *)gItemObj,0,
                 s_f051_root_801dceb4,pVVar13);
      (gItemObj->prgObj).object.m_damageColliders[1].m_localPosition.x = 1.26117e-44;
    }
    break;
  case 0x23:
    iVar11 = (gItemObj->prgObj).m_subState;
    if ((iVar11 != 0) && (iVar11 == 1)) {
      pCVar14 = (gItemObj->prgObj).object.m_charaModelHandle;
      if ((pCVar14 != (CCharaPcsCHandle *)0x0) &&
         (pCVar15 = pCVar14->m_model, pCVar15 != (CModel *)0x0)) {
        pCVar15->m_flags0x10C = pCVar15->m_flags0x10C & 0x7f | 0x80;
      }
      uStack_3c = (gItemObj->prgObj).m_subFrame;
      if ((int)uStack_3c < 9) {
        uStack_3c = uStack_3c ^ 0x80000000;
        local_40 = 0x43300000;
        dVar19 = (double)sin((double)(FLOAT_80331b9c *
                                      (float)((double)CONCAT44(0x43300000,uStack_3c) -
                                             DOUBLE_80331b70) * FLOAT_80331b68));
        fVar9 = (float)dVar19;
        (gItemObj->prgObj).object.m_rotationZ = fVar9;
        (gItemObj->prgObj).object.m_rotationY = fVar9;
        (gItemObj->prgObj).object.m_rotationX = fVar9;
        if ((gItemObj->prgObj).m_subFrame == 8) {
          (gItemObj->prgObj).object.m_bgColMask = (gItemObj->prgObj).object.m_bgColMask | 0x80000;
          changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0x24,0,0);
        }
      }
    }
    break;
  case 0x24:
    (gItemObj->prgObj).object.m_moveOffset.x = FLOAT_80331bb0;
    fVar3 = FLOAT_80331b1c;
    (gItemObj->prgObj).object.m_moveOffset.y = fVar9;
    (gItemObj->prgObj).object.m_moveOffset.z = fVar4;
    fVar9 = (gItemObj->prgObj).object.m_worldPosition.y;
    if (fVar3 <= fVar9) {
      if (FLOAT_80331bb8 < fVar9) {
        (gItemObj->prgObj).object.m_groundHitOffset.y =
             -(FLOAT_80331bb4 * (float)(gItemObj->prgObj).object.m_moveTimer -
              (gItemObj->prgObj).object.m_groundHitOffset.y);
      }
    }
    else {
      (gItemObj->prgObj).object.m_groundHitOffset.y =
           FLOAT_80331bb4 * (float)(gItemObj->prgObj).object.m_moveTimer +
           (gItemObj->prgObj).object.m_groundHitOffset.y;
    }
    fVar9 = (float)(gItemObj->prgObj).object.m_moveTimer;
    fVar3 = (gItemObj->prgObj).object.m_groundHitOffset.y;
    fVar4 = FLOAT_80331ba8 * -fVar9;
    if ((fVar4 <= fVar3) && (fVar9 = FLOAT_80331ba8 * fVar9, fVar4 = fVar3, fVar9 < fVar3)) {
      fVar4 = fVar9;
    }
    (gItemObj->prgObj).object.m_groundHitOffset.y = fVar4;
    fVar9 = FLOAT_80331b50;
    (gItemObj->prgObj).object.m_rotTargetY = (gItemObj->prgObj).object.m_rotTargetY + FLOAT_80331b50
    ;
    (gItemObj->prgObj).object.m_groundHitOffset.x =
         fVar9 * -((gItemObj->prgObj).object.m_worldPosition.x -
                  *(float *)(*(int *)&gItemObj->field_0x550 + 0x15c));
    (gItemObj->prgObj).object.m_groundHitOffset.z =
         fVar9 * -((gItemObj->prgObj).object.m_worldPosition.z -
                  *(float *)(*(int *)&gItemObj->field_0x550 + 0x164));
    break;
  case 0x25:
    (gItemObj->prgObj).object.m_moveOffset.y = FLOAT_80331bb0;
    (gItemObj->prgObj).object.m_rotTargetY = (gItemObj->prgObj).object.m_rotTargetY + fVar2;
    __ct__7CVectorFRC3Vec(&local_58,(Vec *)&m_aiWork__8CGMonObj.field_0x4);
    __ct__7CVectorFRC3Vec(&CStack_70,&(gItemObj->prgObj).object.m_worldPosition);
    __ct__7CVectorFv(&local_a0);
    PSVECSubtract((Vec *)&local_58,(Vec *)&CStack_70,&local_a0);
    local_58.x = local_a0.x;
    local_58.y = local_a0.y;
    local_58.z = local_a0.z;
    dVar19 = (double)PSVECMag((Vec *)&local_58);
    fVar3 = FLOAT_80331bc4;
    fVar9 = FLOAT_80331b20;
    if ((double)FLOAT_80331bb8 <= dVar19) {
      if (dVar19 <= (double)FLOAT_80331b20) {
        (gItemObj->prgObj).object.m_groundHitOffset.z = FLOAT_80331b20;
        (gItemObj->prgObj).object.m_groundHitOffset.y = fVar9;
        (gItemObj->prgObj).object.m_groundHitOffset.x = fVar9;
      }
      else {
        fVar9 = FLOAT_80331bc0 * (float)(gItemObj->prgObj).object.m_moveTimer;
        (gItemObj->prgObj).object.m_groundHitOffset.x =
             FLOAT_80331bc4 * local_58.x * fVar9 + (gItemObj->prgObj).object.m_groundHitOffset.x;
        (gItemObj->prgObj).object.m_groundHitOffset.y =
             fVar3 * local_58.y * fVar9 + (gItemObj->prgObj).object.m_groundHitOffset.y;
        (gItemObj->prgObj).object.m_groundHitOffset.z =
             fVar3 * local_58.z * fVar9 + (gItemObj->prgObj).object.m_groundHitOffset.z;
      }
    }
    else {
      changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0x27,0,0);
    }
    break;
  case 0x26:
    (gItemObj->prgObj).object.m_groundHitOffset.z = FLOAT_80331b20;
    (gItemObj->prgObj).object.m_groundHitOffset.y = fVar3;
    (gItemObj->prgObj).object.m_groundHitOffset.x = fVar3;
    iVar11 = (gItemObj->prgObj).m_stateFrame;
    if (iVar11 == 0) {
      (gItemObj->prgObj).object.m_stepSlopeLimit = fVar3;
      EndParticleSlot__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&gItemObj->field_0x55c);
      iVar11 = *(int *)(*(int *)(SoundBuffer._1260_4_ + 0xf8) + 0x178);
      if (iVar11 == 0) {
        iVar11 = -1;
      }
      else {
        iVar11 = *(int *)(iVar11 + 0x14);
      }
      local_40 = 0x43300000;
      uStack_3c = (uint)*(ushort *)
                         (Game.game.unkCFlatData0[2] +
                          (int)(gItemObj->prgObj).object.m_worldParamB * 0x48 + 0x10);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_80331b50 *
                          (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331b60) +
                         FLOAT_80331b4c),&gItemObj->prgObj,iVar11 << 8 | 4,
                 *(int *)&gItemObj->field_0x55c,(CGObject *)gItemObj,0x12908);
    }
    else if (iVar11 == 0xd) {
      iVar11 = *(int *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3b4);
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcfc8,iVar11);
      }
      dVar19 = (double)FLOAT_80331b20;
      *(undefined4 *)(SoundBuffer + iVar11 * 4 + 0x4f4) = 0;
      iVar11 = CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(dVar19,0,0,0x103,0,0);
      if (iVar11 == 0) {
        if (1 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801dcfec);
        }
      }
      else {
        *(float *)(iVar11 + 0x168) = (gItemObj->prgObj).object.m_worldPosition.x;
        *(float *)(iVar11 + 0x16c) = (gItemObj->prgObj).object.m_worldPosition.y;
        *(float *)(iVar11 + 0x170) = (gItemObj->prgObj).object.m_worldPosition.z;
        *(undefined4 *)(iVar11 + 0x15c) = *(undefined4 *)(iVar11 + 0x168);
        *(undefined4 *)(iVar11 + 0x160) = *(undefined4 *)(iVar11 + 0x16c);
        *(undefined4 *)(iVar11 + 0x164) = *(undefined4 *)(iVar11 + 0x170);
        local_a8 = 1;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,*(undefined4 *)&gItemObj->field_0x550,2,0x16,1,&local_a8,(CStack *)0x0);
      }
      (gItemObj->prgObj).object.base_object.object.m_flags =
           (gItemObj->prgObj).object.base_object.object.m_flags & 0x7f | 0x80;
    }
    break;
  case 0x27:
    (gItemObj->prgObj).object.m_groundHitOffset.z = FLOAT_80331b20;
    (gItemObj->prgObj).object.m_groundHitOffset.y = fVar3;
    (gItemObj->prgObj).object.m_groundHitOffset.x = fVar3;
    iVar11 = (gItemObj->prgObj).m_stateFrame;
    if (iVar11 == 0) {
      (gItemObj->prgObj).object.m_stepSlopeLimit = fVar3;
      EndParticleSlot__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&gItemObj->field_0x55c);
      iVar11 = *(int *)(*(int *)(SoundBuffer._1260_4_ + 0xf8) + 0x178);
      if (iVar11 == 0) {
        iVar11 = -1;
      }
      else {
        iVar11 = *(int *)(iVar11 + 0x14);
      }
      local_40 = 0x43300000;
      uStack_3c = (uint)*(ushort *)
                         (Game.game.unkCFlatData0[2] +
                          (int)(gItemObj->prgObj).object.m_worldParamB * 0x48 + 0x10);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_80331b50 *
                          (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331b60) +
                         FLOAT_80331b4c),&gItemObj->prgObj,iVar11 << 8 | 0x13,
                 *(int *)&gItemObj->field_0x55c,(CGObject *)gItemObj,0x12903);
    }
    else if (iVar11 == 0xd) {
      iVar11 = *(int *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3b4);
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcfa4,iVar11);
      }
      local_a4 = 0;
      *(undefined4 *)(SoundBuffer + iVar11 * 4 + 0x4f4) = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,*(undefined4 *)&gItemObj->field_0x550,2,0x16,1,&local_a4,(CStack *)0x0);
      (gItemObj->prgObj).object.base_object.object.m_flags =
           (gItemObj->prgObj).object.base_object.object.m_flags & 0x7f | 0x80;
    }
  }
  return;
}

