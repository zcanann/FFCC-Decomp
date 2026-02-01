// Function: onFramePreCalc__10CGPartyObjFv
// Entry: 801230a0
// Size: 844 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFramePreCalc__10CGPartyObjFv(CGPrgObj *param_1)

{
  byte bVar1;
  ushort uVar2;
  float fVar3;
  bool bVar4;
  short sVar5;
  void **ppvVar6;
  uint uVar7;
  double dVar8;
  float local_28;
  CGObject *local_24 [6];
  
  if ((param_1->object).m_scriptHandle != (void **)0x0) {
    onFramePreCalc__10CGCharaObjFv();
    if (Game.game.unk_flat3_0xc7d0 != 0) {
      dVar8 = (double)PSVECDistance(&(param_1->object).m_worldPosition,
                                    (Vec *)(Game.game.unk_flat3_0xc7d0 + 0x15c));
      param_1[1].object.m_projection.z = (float)dVar8;
    }
    if (((int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18) < 0) &&
       (-1 < (int)((uint)*(byte *)&param_1[1].object.unk_0x168 << 0x18))) {
      bVar1 = *(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1);
      if (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7))) {
        bVar4 = false;
        uVar7 = (uint)(char)(param_1->object).m_animStateMisc;
        if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
          bVar4 = true;
        }
        if (bVar4) {
          sVar5 = 0;
        }
        else {
          sVar5 = *(short *)(&Pad.field_0x4 +
                            (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) *
                            0x54);
        }
        if (sVar5 != 0) {
          changeStat__8CGPrgObjFiii(param_1,0,0,0);
        }
      }
      if ((CFlat._4780_4_ == 0) &&
         ((_GetCurrentWeaponItem__12CCaravanWorkFRiRi
                     ((CCaravanWork *)(param_1->object).m_scriptHandle,local_24,&local_28),
          param_1[1].object.m_attachOwner != local_24[0] ||
          ((float)param_1[1].object.m_attachNode != local_28)))) {
        bVar4 = false;
        if ((-1 < (int)((uint)*(byte *)&(param_1->object).m_weaponNodeFlags << 0x18)) ||
           ((((-1 < (int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18) ||
              (param_1[1].object.m_moveBaseSpeed != 0.0)) ||
             (ppvVar6 = (param_1->object).m_scriptHandle, *(short *)((int)ppvVar6 + 0x3e) != 0)) ||
            ((*(short *)(ppvVar6 + 0x14) != 0 || (*(short *)(ppvVar6 + 0x11) != 0)))))) {
          bVar4 = true;
        }
        if (bVar4) {
          if ((int)local_28 < 1) {
            LoadWeapon__8CGObjectFii(&param_1->object,0xffffffff,0);
          }
          else {
            uVar2 = *(ushort *)(Game.game.unkCFlatData0[2] + (int)local_28 * 0x48 + 2);
            LoadWeapon__8CGObjectFii(&param_1->object,uVar2 & 0xfff,(int)(uint)uVar2 >> 0xc);
          }
          param_1[1].object.m_attachOwner = local_24[0];
          param_1[1].object.m_attachNode = (int32_t)local_28;
          SetCurrentWeaponIdx__12CCaravanWorkFi
                    ((CCaravanWork *)(param_1->object).m_scriptHandle,
                     (int)param_1[1].object.m_attachOwner);
          *(byte *)&param_1[1].object.m_rotationX = *(byte *)&param_1[1].object.m_rotationX & 0xdf;
        }
        else {
          param_1[1].object.unk_0x184 = (float)local_24[0];
          param_1[1].object.unk_0x188 = local_28;
          *(byte *)&param_1[1].object.m_rotationX =
               *(byte *)&param_1[1].object.m_rotationX & 0xdf | 0x20;
          changeStat__8CGPrgObjFiii(param_1,0xf,0,0);
        }
      }
    }
    (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x4c))(param_1,2,0,0);
    if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
      if ((param_1[1].object.m_moveBaseSpeed == 0.0) &&
         (*(short *)((param_1->object).m_scriptHandle + 7) != 0)) {
        (param_1->object).m_moveBaseSpeed = FLOAT_80331ad4;
      }
      else {
        fVar3 = FLOAT_80331a54;
        if (CFlat._4780_4_ == 0) {
          fVar3 = FLOAT_80331b08;
        }
        (param_1->object).m_moveBaseSpeed =
             (float)((double)CONCAT44(0x43300000,(int)(FLOAT_80331b04 * fVar3) ^ 0x80000000) -
                    DOUBLE_80331a60);
      }
      (param_1->object).m_moveBaseSpeed =
           (param_1->object).m_moveBaseSpeed * param_1[1].object.m_extraMoveVec.z;
    }
  }
  return;
}

