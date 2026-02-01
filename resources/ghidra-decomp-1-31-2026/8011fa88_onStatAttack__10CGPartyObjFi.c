// Function: onStatAttack__10CGPartyObjFi
// Entry: 8011fa88
// Size: 800 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatAttack__10CGPartyObjFi(CGPrgObj *param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  void **ppvVar5;
  uint uVar6;
  float fVar7;
  double dVar8;
  
  fVar7 = FLOAT_80331ad4;
  if (param_2 != 0) {
    ppvVar5 = (param_1->object).m_scriptHandle;
    fVar7 = param_1[1].object.m_rotationZ;
    iVar4 = Game.game.unk_flat3_field_30_0xc7e0 +
            ((uint)*(ushort *)((int)ppvVar5 + 0x3e2) + (uint)*(ushort *)(ppvVar5 + 0xf8) * 2) *
            0x1ca + (int)fVar7 * 0x12;
    if (((0 < (int)fVar7) && (param_1->m_stateFrame == (uint)*(ushort *)(iVar4 + 4))) &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x17)) {
      moveVectorRot__8CGObjectFfffi
                ((double)(param_1->object).m_rotTargetY,(double)FLOAT_80331a78,
                 (double)(FLOAT_80331adc *
                         (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(iVar4 + 8)) -
                                DOUBLE_80331a68)),&param_1->object,
                 ((uint)*(ushort *)(iVar4 + 6) - (uint)*(ushort *)(iVar4 + 4)) + 1);
    }
    if ((param_1->m_stateFrame < (int)(uint)*(ushort *)(iVar4 + 0xc)) ||
       ((int)(uint)*(ushort *)(iVar4 + 0xe) < param_1->m_stateFrame)) {
      bVar2 = false;
      uVar6 = (uint)(char)(param_1->object).m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar3 = 0;
      }
      else {
        uVar3 = *(ushort *)
                 (&Pad.field_0x8 +
                 (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar3 & 0x100) != 0) {
        *(byte *)&param_1[1].object.m_rotationX =
             *(byte *)&param_1[1].object.m_rotationX & 0xbf | 0x40;
      }
    }
    else {
      bVar2 = false;
      uVar6 = (uint)(char)(param_1->object).m_animStateMisc;
      if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar3 = 0;
      }
      else {
        uVar3 = *(ushort *)
                 (&Pad.field_0x8 +
                 (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar3 & 0x100) != 0) {
        *(byte *)&param_1[1].object.m_rotationX =
             *(byte *)&param_1[1].object.m_rotationX & 0x7f | 0x80;
      }
    }
    if (param_1->m_stateFrame == (uint)*(ushort *)(iVar4 + 0x10)) {
      bVar1 = *(byte *)&param_1[1].object.m_rotationX;
      if ((((int)((uint)bVar1 << 0x18) < 0) &&
          (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
         (fVar7 = param_1[1].object.m_rotationZ, (int)fVar7 < 2)) {
        param_1[1].object.m_rotationY = (float)((int)fVar7 + 1);
        changeStat__8CGPrgObjFiii(param_1,1,0,0);
        return;
      }
    }
    uVar6._0_2_ = param_1[1].object.m_lastBgGroup;
    uVar6._2_2_ = param_1[1].object.m_weaponAttachNode;
    if (param_1->m_stateFrame == uVar6) {
      *(byte *)&param_1[1].object.m_shieldAttachNodeIndex =
           *(byte *)&param_1[1].object.m_shieldAttachNodeIndex & 0x7f | 0x80;
    }
    iVar4 = isLoopAnim__8CGPrgObjFv(param_1);
    if (iVar4 != 0) {
      changeStat__8CGPrgObjFiii(param_1,0,0,0);
    }
    return;
  }
  if (param_1->m_stateFrame != 0) {
    return;
  }
  param_1[1].object.m_rotationZ = param_1[1].object.m_rotationY;
  dVar8 = (double)FLOAT_80331ad8;
  param_1[1].object.m_rotationY = 0.0;
  *(byte *)&param_1[1].object.m_rotationX = *(byte *)&param_1[1].object.m_rotationX & 0x7f;
  *(byte *)&param_1[1].object.m_rotationX = *(byte *)&param_1[1].object.m_rotationX & 0xbf;
  iVar4 = getBestAngleObject__10CGPartyObjFff
                    ((double)(fVar7 * (param_1->object).m_bodyEllipsoidRadius),dVar8);
  if (iVar4 == 0) {
    return;
  }
  dVar8 = (double)atan2((double)(*(float *)(iVar4 + 0x15c) - (param_1->object).m_worldPosition.x),
                        (double)(*(float *)(iVar4 + 0x164) - (param_1->object).m_worldPosition.z));
  (param_1->object).m_rotTargetY = (float)dVar8;
  return;
}

