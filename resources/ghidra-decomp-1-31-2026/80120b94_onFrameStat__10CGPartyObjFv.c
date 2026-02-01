// Function: onFrameStat__10CGPartyObjFv
// Entry: 80120b94
// Size: 4112 bytes

/* WARNING: Removing unreachable block (ram,0x80121b80) */
/* WARNING: Removing unreachable block (ram,0x80120ba4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameStat__10CGPartyObjFv(CGCharaObj *param_1)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  bool bVar8;
  uint32_t uVar9;
  float fVar10;
  ushort uVar11;
  Vec *vecA;
  int iVar12;
  void **ppvVar13;
  ushort uVar15;
  uint uVar14;
  void *pvVar16;
  uint32_t *puVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  Vec local_58;
  CVector CStack_4c;
  CVector CStack_40;
  float local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  uint uStack_24;
  
  ppvVar13 = (param_1->gPrgObj).object.m_scriptHandle;
  if (ppvVar13 == (void **)0x0) {
    return;
  }
  switch((param_1->gPrgObj).m_lastStateId) {
  case 0:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1e | (uint)((byte)param_1->field_0x6b8 >> 2))
          < 0) {
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x27,0,0);
        param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfd;
      }
      else {
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0xffffffff,0,0);
      }
    }
    if (((((int)((uint)(byte)param_1->field_0x6b8 << 0x18) < 0) ||
         (ppvVar13 = (param_1->gPrgObj).object.m_scriptHandle, *(short *)((int)ppvVar13 + 0x3e) != 0
         )) || (*(short *)(ppvVar13 + 0x14) != 0)) || (*(short *)(ppvVar13 + 0x11) != 0)) {
      *(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1) =
           *(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1) & 0xbf;
      param_1->field_0x63c = param_1->field_0x63c & 0x7f;
    }
    else {
      *(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1) =
           *(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1) & 0xbf | 0x40;
      param_1->field_0x63c = param_1->field_0x63c & 0x7f | 0x80;
    }
    if ((MiniGamePcs._25732_4_ & 8) == 0) {
      if (((Game.game.unk_flat3_0xc7d0 != 0) &&
          (iVar12 = GetCtrlMode__6JoyBusFi
                              (&Joybus,(int)(char)(param_1->gPrgObj).object.m_animStateMisc),
          iVar12 == 1)) && ((int)((uint)(byte)param_1->field_0x63c << 0x18) < 0)) {
        bVar1 = *(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1);
        if ((((int)((uint)bVar1 << 0x18) < 0) &&
            ((int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0)) &&
           (-1 < (int)((uint)(byte)param_1->field_0x6b8 << 0x18))) goto LAB_80120d48;
      }
    }
    else {
LAB_80120d48:
      if ((((FLOAT_80331a74 * Game.game.unkFloat_0xca10 < *(float *)&param_1->field_0x5bc) &&
           (ppvVar13 = (param_1->gPrgObj).object.m_scriptHandle,
           *(short *)((int)ppvVar13 + 0x3e) == 0)) && (*(short *)(ppvVar13 + 0x14) == 0)) &&
         ((*(short *)(ppvVar13 + 0x11) == 0 &&
          (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x17)))) {
        __ct__7CVectorFRC3Vec(&CStack_4c,&(param_1->gPrgObj).object.m_worldPosition);
        vecA = (Vec *)__ct__7CVectorFRC3Vec(&CStack_40,(Vec *)(Game.game.unk_flat3_0xc7d0 + 0x15c));
        __ct__7CVectorFv(&local_58);
        PSVECSubtract(vecA,(Vec *)&CStack_4c,&local_58);
        local_34 = local_58.x;
        local_30 = local_58.y;
        local_2c = local_58.z;
        moveVector__8CGObjectFP3Vecfi
                  ((double)(param_1->gPrgObj).object.m_moveBaseSpeed,(CGObject *)param_1,&local_34,
                   0xf);
      }
    }
    if ((((int)((uint)*(byte *)((int)&(param_1->gPrgObj).object.m_weaponNodeFlags + 1) << 0x18) < 0)
        && (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
       (((param_1->gPrgObj).object.m_scriptHandle[0xed] == (void *)0x0 &&
        ((Game.game.m_partyObjArr[1] != (CGPartyObj *)0x0 &&
         ((Game.game.m_partyObjArr[1]->gCharaObj).gPrgObj.m_lastStateId == 0)))))) {
      bVar8 = false;
      uVar14 = (uint)(char)(param_1->gPrgObj).object.m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
        bVar8 = true;
      }
      if (bVar8) {
        uVar15 = 0;
      }
      else {
        uVar15 = *(ushort *)
                  (&Pad.field_0x4 +
                  (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      bVar8 = false;
      if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
        bVar8 = true;
      }
      if (bVar8) {
        uVar11 = 0;
      }
      else {
        uVar11 = *(ushort *)
                  (&Pad.field_0x12 +
                  (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar11 & 0x400) == 0) {
        if ((uVar15 & 0x400) == 0) {
          m_ghostWork__10CGPartyObj._36_4_ = 0;
        }
        else {
          m_ghostWork__10CGPartyObj._36_4_ = m_ghostWork__10CGPartyObj._36_4_ + 1;
          if ((9 < (int)m_ghostWork__10CGPartyObj._36_4_) && (m_ghostWork__10CGPartyObj._32_4_ == 0)
             ) {
            m_ghostWork__10CGPartyObj._32_4_ = 2;
          }
        }
      }
      else if (((int)m_ghostWork__10CGPartyObj._36_4_ < 10) &&
              (param_1[1].gPrgObj.object.base_object.object.m_codePos != Game.game.unk_flat3_0xc7d0)
              ) {
        m_boss__8CGMonObj._108_1_ =
             (byte)((int)(char)((byte)((byte)((uint)-*(int *)&Game.game.m_partyObjArr[1]->
                                                              field_0x6f0 >> 0x18) |
                                      (byte)((uint)*(int *)&Game.game.m_partyObjArr[1]->field_0x6f0
                                            >> 0x18)) >> 7) << 7) | m_boss__8CGMonObj._108_1_ & 0x7f
        ;
      }
    }
    break;
  case 6:
    statCharge__10CGPartyObjFv();
    break;
  case 7:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      *(undefined4 *)&param_1->field_0x6d0 = 0;
    }
    bVar8 = false;
    uVar14 = (uint)(char)(param_1->gPrgObj).object.m_animStateMisc;
    if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
      bVar8 = true;
    }
    if (bVar8) {
      uVar15 = 0;
    }
    else {
      uVar15 = *(ushort *)
                (&Pad.field_0x4 +
                (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar15 & 0x100) == 0) {
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,1,0,0);
    }
    else {
      *(int *)&param_1->field_0x6d0 = *(int *)&param_1->field_0x6d0 + 1;
      if (*(int *)&param_1->field_0x6d0 < 6) {
        bVar8 = false;
        uVar14 = (uint)(char)(param_1->gPrgObj).object.m_animStateMisc;
        if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
          bVar8 = true;
        }
        if (bVar8) {
          uVar15 = 0;
        }
        else {
          uVar15 = *(ushort *)
                    (&Pad.field_0x8 +
                    (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54
                    );
        }
        if ((uVar15 & 0x200) != 0) {
          changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
        }
      }
      else {
        changeStat__8CGPrgObjFiii(&param_1->gPrgObj,6,0,0);
      }
    }
    break;
  case 0xb:
    if ((((Game.game.m_gameWork.m_menuStageMode != '\0') &&
         (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
        (uVar14 = (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0xc))(),
        uVar9 = Game.game.unk_flat3_0xc7d0, (uVar14 & 0x6d) == 0x6d)) &&
       ((param_1->gPrgObj).object.m_scriptHandle[0xed] != (void *)0x0)) {
      if ((param_1->gPrgObj).m_stateFrame == 0) {
        CancelMove__8CGObjectFi((CGObject *)param_1,1);
        FLOAT_8032ee78 = *(float *)&param_1->field_0x5bc - FLOAT_80331ac4;
        FLOAT_8032ee7c = *(float *)(uVar9 + 0x160) - (param_1->gPrgObj).object.m_worldPosition.y;
      }
      uVar14 = (param_1->gPrgObj).m_stateFrame;
      if ((int)uVar14 < 0xc) {
        uStack_24 = uVar14 ^ 0x80000000;
        local_28 = 0x43300000;
        dVar18 = (double)sin((double)((FLOAT_80331ab8 *
                                      (float)((double)CONCAT44(0x43300000,uStack_24) -
                                             DOUBLE_80331a60)) / FLOAT_80331ac0));
        dVar20 = (double)(float)dVar18;
        dVar18 = (double)sin((double)(param_1->gPrgObj).object.m_rotBaseY);
        (param_1->gPrgObj).object.m_extraMoveVec.x =
             FLOAT_8032ee78 * (float)(dVar20 * (double)(float)dVar18);
        dVar19 = (double)cos((double)(param_1->gPrgObj).object.m_rotBaseY);
        dVar18 = (double)FLOAT_80331a98;
        (param_1->gPrgObj).object.m_extraMoveVec.z =
             FLOAT_8032ee78 * (float)(dVar20 * (double)(float)dVar19);
        (param_1->gPrgObj).object.m_extraMoveVec.y =
             (float)((double)FLOAT_8032ee7c * dVar20 + dVar18);
      }
    }
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0xd,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x22,0x32,0x96,0,0);
    }
    iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
    if (iVar12 != 0) {
      if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
        if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
          sVar4._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar4._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar4 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
        }
        else {
          sVar3._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar3._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar3 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
          }
        }
      }
      else if (CFlat._4780_4_ == 0) {
        sVar2._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar2._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar2 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
        }
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
      fVar10 = FLOAT_80331a78;
      (param_1->gPrgObj).object.m_extraMoveVec.x = FLOAT_80331a78;
      (param_1->gPrgObj).object.m_extraMoveVec.z = fVar10;
    }
    break;
  case 0xc:
  case 0xd:
  case 0x1b:
    statPut__10CGPartyObjFv(param_1);
    break;
  case 0xe:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,9,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x1f,0x32,0x96,0,0);
    }
    iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
    if (iVar12 != 0) {
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
    }
    break;
  case 0xf:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x29,0,0);
    }
    if ((param_1->gPrgObj).m_stateFrame == 4) {
      ppvVar13 = param_1[1].gPrgObj.object.base_object.object.m_freeListNode;
      puVar17 = (uint32_t *)param_1[1].gPrgObj.object.base_object.object.m_id;
      if ((int)ppvVar13 < 1) {
        LoadWeapon__8CGObjectFii((CGObject *)param_1,0xffffffff,0);
      }
      else {
        uVar15 = *(ushort *)(Game.game.unkCFlatData0[2] + (int)ppvVar13 * 0x48 + 2);
        LoadWeapon__8CGObjectFii((CGObject *)param_1,uVar15 & 0xfff,(int)(uint)uVar15 >> 0xc);
      }
      param_1[1].gPrgObj.object.base_object.object.m_stackPointer = puVar17;
      param_1[1].gPrgObj.object.base_object.object.m_localBase = (uint32_t *)ppvVar13;
      SetCurrentWeaponIdx__12CCaravanWorkFi
                ((CCaravanWork *)(param_1->gPrgObj).object.m_scriptHandle,
                 (int)param_1[1].gPrgObj.object.base_object.object.m_stackPointer);
      param_1->field_0x6c4 = param_1->field_0x6c4 & 0xdf;
    }
    iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
    if (iVar12 != 0) {
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
    }
    break;
  case 0x13:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      damageDelete__10CGCharaObjFv();
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x21,0,0);
    }
    iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
    if (iVar12 != 0) {
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
    }
    break;
  case 0x14:
    iVar12 = (param_1->gPrgObj).m_subState;
    if (iVar12 == 1) {
      if ((param_1->gPrgObj).m_subFrame == 0) {
        *(float *)&param_1->field_0x694 = FLOAT_80331abc;
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x16,1,0);
        (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,0);
      }
      bVar8 = false;
      uVar14 = (uint)(char)(param_1->gPrgObj).object.m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
        bVar8 = true;
      }
      if (bVar8) {
        uVar15 = 0;
      }
      else {
        uVar15 = *(ushort *)
                  (&Pad.field_0x4 +
                  (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar15 & 0x100) == 0) {
        if (0x18 < (param_1->gPrgObj).m_subFrame) {
          playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x30,0x32,0x96,0,0);
        }
        *(float *)&param_1->field_0x694 = FLOAT_80331a54;
        changeSubStat__8CGPrgObjFi(&param_1->gPrgObj,2);
        (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
      }
    }
    else if (iVar12 < 1) {
      if (-1 < iVar12) {
        if ((param_1->gPrgObj).m_subFrame == 0) {
          playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x2f,0x32,0x96,0,0);
          reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x15,0,0);
        }
        iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
        if (iVar12 != 0) {
          changeSubStat__8CGPrgObjFi(&param_1->gPrgObj,1);
        }
      }
    }
    else if (iVar12 < 3) {
      if ((param_1->gPrgObj).m_subFrame == 0) {
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x17,0,0);
      }
      iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
      if (iVar12 != 0) {
        changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
      }
    }
    break;
  case 0x15:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x40,0x32,0x96,0,0);
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x15,0,0);
      (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,0);
    }
    if (((param_1->gPrgObj).m_stateFrame == 3) &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x17)) {
      moveVectorHRot__8CGObjectFfffi
                ((double)(FLOAT_80331ab8 + (param_1->gPrgObj).object.m_rotTargetY),
                 (double)FLOAT_80331a78,(double)FLOAT_80331a54,(CGObject *)param_1,10);
    }
    iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
    if (iVar12 != 0) {
      changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
      (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
    }
    break;
  case 0x1a:
    statKorobi__10CGPartyObjFv();
    break;
  case 0x20:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x31,0,0);
    }
    else {
      iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
      if (iVar12 != 0) {
        changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
      }
    }
    break;
  case 0x22:
    if ((param_1->gPrgObj).m_stateFrame == 0) {
      if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1d | (uint)((byte)param_1->field_0x6b8 >> 3))
          < 0) {
        if (*(short *)(ppvVar13 + 7) == 0) {
          addHp__10CGCharaObjFiP8CGPrgObj
                    (param_1,(uint)*(ushort *)((int)ppvVar13 + 0x1a),(CGPrgObj *)0x0);
        }
        param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
      }
      (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
      if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
        if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
          sVar7._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar7._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar7 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
        }
        else {
          sVar6._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar6._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar6 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
          }
        }
      }
      else if (CFlat._4780_4_ == 0) {
        sVar5._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar5._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar5 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
        }
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      if ((param_1->gPrgObj).object.m_currentAnimSlot == '\x06') {
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x26,0,0);
      }
      else {
        reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x27,0,0);
      }
      if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
        *(float *)&param_1->field_0x694 = FLOAT_80331a7c;
        (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask & 0xfffefff1;
        pvVar16 = (param_1->gPrgObj).object.m_scriptHandle[0xed];
        endPSlotBit__10CGCharaObjFi(param_1,0x10000);
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331a54,&param_1->gPrgObj,(int)pvVar16 + 3U | 0x100,
                   *(int *)&param_1->field_0x5a4,(CGObject *)param_1,0);
        playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x2d,0x32,0x96,0,0);
      }
      else {
        endPSlotBit__10CGCharaObjFi(param_1,0x10000);
        *(float *)&param_1->field_0x694 = FLOAT_80331a54;
        (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask | 0x1000e;
        *(undefined2 *)((param_1->gPrgObj).object.m_scriptHandle + 0x12) = 0x5a;
      }
    }
    else {
      iVar12 = isLoopAnim__8CGPrgObjFv(&param_1->gPrgObj);
      if (iVar12 != 0) {
        if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) != 0) {
          param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfd | 2;
        }
        changeStat__8CGPrgObjFiii(&param_1->gPrgObj,0,0,0);
      }
    }
  }
  onFrameStat__10CGCharaObjFv(param_1);
  return;
}

