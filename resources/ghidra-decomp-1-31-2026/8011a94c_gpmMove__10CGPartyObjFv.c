// Function: gpmMove__10CGPartyObjFv
// Entry: 8011a94c
// Size: 2332 bytes

/* WARNING: Removing unreachable block (ram,0x8011ae1c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void gpmMove__10CGPartyObjFv(CGPrgObj *param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  CGPartyObj *pCVar5;
  uint32_t other;
  int iVar6;
  uint uVar7;
  int iVar8;
  char cVar9;
  undefined uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  float local_78;
  CVector local_74;
  CVector local_68;
  float local_5c;
  float local_58;
  float local_54;
  Vec local_50;
  Vec VStack_44;
  double local_38;
  
  other = Game.game.unk_flat3_0xc7d0;
  pCVar5 = Game.game.m_partyObjArr[0];
  if ((((Game.game.m_partyObjArr[0]->gCharaObj).gPrgObj.m_lastStateId == 0) &&
      ((Game.game.m_partyObjArr[0]->gCharaObj).gPrgObj.object.m_animSlotSel == '\f')) &&
     (*(uint32_t *)&Game.game.m_partyObjArr[0]->field_0x6f0 == Game.game.unk_flat3_0xc7d0)) {
    m_ghostWork__10CGPartyObj._28_4_ = m_ghostWork__10CGPartyObj._28_4_ + 1;
  }
  else {
    m_ghostWork__10CGPartyObj._28_4_ = 0;
  }
  if ((double)FLOAT_80331a70 < (double)(float)m_ghostWork__10CGPartyObj._20_4_) {
    moveVector__8CGObjectFP3Vecfi
              ((double)(float)m_ghostWork__10CGPartyObj._20_4_,&param_1->object,0x803001e4,1);
  }
  m_ghostWork__10CGPartyObj._20_4_ = (float)m_ghostWork__10CGPartyObj._20_4_ * FLOAT_80331a74;
  switch(Game.game.m_gameWork.m_bossArtifactStageIndex) {
  default:
    uVar7 = 0;
    break;
  case 4:
  case 8:
  case 9:
  case 0xb:
  case 0xc:
  case 0xd:
    uVar7 = 2;
    break;
  case 6:
  case 10:
    uVar7 = 1;
  }
  local_38 = (double)(CONCAT44(0x43300000,Chara._8276_4_) ^ 0x80000000);
  fVar2 = (float)(local_38 - DOUBLE_80331a60) / FLOAT_80331a50;
  if (uVar7 == 2) {
    fVar3 = FLOAT_80331a58 * fVar2 + FLOAT_80331a58;
  }
  else {
    fVar3 = FLOAT_80331a54;
    if ((uVar7 < 2) && (uVar7 != 0)) {
      fVar3 = FLOAT_80331a58 * (FLOAT_80331a54 - fVar2) + FLOAT_80331a58;
    }
  }
  iVar6 = (int)(FLOAT_80331a5c * fVar3);
  local_38 = (double)(longlong)iVar6;
  if ((float)m_ghostWork__10CGPartyObj._20_4_ <= FLOAT_80331a58) {
    if (param_1[1].object.m_moveBaseSpeed == 0.0) {
      m_ghostWork__10CGPartyObj._24_4_ = m_ghostWork__10CGPartyObj._24_4_ + -4;
    }
    else {
      m_ghostWork__10CGPartyObj._24_4_ = m_ghostWork__10CGPartyObj._24_4_ + -3;
    }
  }
  else {
    iVar8 = -2;
    if (param_1[1].object.m_moveBaseSpeed != 0.0) {
      iVar8 = 2;
    }
    m_ghostWork__10CGPartyObj._24_4_ = m_ghostWork__10CGPartyObj._24_4_ + iVar8;
  }
  if ((int)m_ghostWork__10CGPartyObj._24_4_ < 0) {
    m_ghostWork__10CGPartyObj._24_4_ = 0;
  }
  else if (iVar6 + 100 < (int)m_ghostWork__10CGPartyObj._24_4_) {
    m_ghostWork__10CGPartyObj._24_4_ = iVar6 + 100;
  }
  if ((int)m_ghostWork__10CGPartyObj._24_4_ < iVar6 / 3) {
    m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0xfb;
  }
  m_ghostWork__10CGPartyObj._32_4_ =
       m_ghostWork__10CGPartyObj._32_4_ - 1 & ~((int)(m_ghostWork__10CGPartyObj._32_4_ - 1) >> 0x1f)
  ;
  gpmCalcDist__10CGPartyObjFP3VecRf(param_1,&VStack_44,&local_78);
  local_50.x = param_1[1].object.m_projection.w;
  local_50.z = param_1[1].object.m_bounceFactor;
  local_50.y = FLOAT_80331a78;
  dVar11 = (double)PSVECMag(&local_50);
  dVar13 = (double)param_1[1].object.m_projection.z;
  dVar12 = dVar13;
  if (dVar11 < dVar13) {
    dVar12 = dVar11;
  }
  if ((param_1->m_lastStateId != 0) ||
     (-1 < (int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18))) {
    if (param_1->m_lastStateId != 2) {
      return;
    }
    if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x18)) {
      changeStat__8CGPrgObjFiii(param_1,0,0,0);
      return;
    }
    iVar6 = (pCVar5->gCharaObj).gPrgObj.m_lastStateId;
    if ((iVar6 == 2) || (iVar6 == 6)) {
      if (param_1->m_subState != 1) {
        return;
      }
      if (param_1[1].object.m_bodyOffset.z == 0.0) {
        return;
      }
      bVar1 = (pCVar5->gCharaObj).field_0x6b8;
      if ((int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0) {
        m_boss__8CGMonObj._132_4_ = 0;
      }
      bVar1 = *(byte *)&param_1[1].object.unk_0x168;
      if (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7))) {
        return;
      }
      uVar7 = (byte)m_boss__8CGMonObj._108_1_ & 0xffffffdf | 0x20;
      m_boss__8CGMonObj._132_4_ = m_boss__8CGMonObj._132_4_ + 1;
      uVar10 = (undefined)uVar7;
      if ((int)m_boss__8CGMonObj._132_4_ < 0x10) {
        m_boss__8CGMonObj._108_1_ = uVar10;
        return;
      }
      bVar1 = (byte)m_boss__8CGMonObj._108_1_ >> 7;
      m_boss__8CGMonObj._108_1_ = uVar10;
      if ((int)(uVar7 << 0x19 | (uint)bVar1) < 0) {
        return;
      }
    }
    else if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x1a |
                       (uint)((byte)m_boss__8CGMonObj._108_1_ >> 6))) {
      changeStat__8CGPrgObjFiii(param_1,0,0,0);
      return;
    }
    if (m_ghostWork__10CGPartyObj._16_4_ == 0) {
      m_ghostWork__10CGPartyObj._4_4_ = 0;
    }
    else {
      m_ghostWork__10CGPartyObj._4_4_ = (int)m_ghostWork__10CGPartyObj._4_4_ / 2;
    }
    if (m_ghostWork__10CGPartyObj._16_4_ == 1) {
      m_ghostWork__10CGPartyObj._8_4_ = 0;
    }
    else {
      m_ghostWork__10CGPartyObj._8_4_ = (int)m_ghostWork__10CGPartyObj._8_4_ / 2;
    }
    if (m_ghostWork__10CGPartyObj._16_4_ == 2) {
      m_ghostWork__10CGPartyObj._12_4_ = 0;
    }
    else {
      m_ghostWork__10CGPartyObj._12_4_ = (int)m_ghostWork__10CGPartyObj._12_4_ / 2;
    }
    m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0xaf | 0x40;
    return;
  }
  iVar8 = 0;
  if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x18)) {
    if (((param_1[1].object.m_moveBaseSpeed == 0.0) &&
        ((int)((uint)*(byte *)(other + 0x9a) << 0x18) < 0)) && (*(int *)(other + 0x550) == 0)) {
      if (dVar13 < (double)(FLOAT_80331a84 *
                           ((pCVar5->gCharaObj).gPrgObj.object.m_bodyEllipsoidRadius +
                           *(float *)(other + 0x144)))) {
        CancelMove__8CGObjectFi(&param_1->object,1);
        rotTarget__8CGPrgObjFP8CGPrgObj(param_1,(CGPrgObj *)other);
        m_ghostWork__10CGPartyObj._20_4_ = FLOAT_80331a78;
        carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)param_1,0,(CGObject *)other,0);
        return;
      }
      iVar8 = 1;
    }
    if (iVar8 == 0) {
      fVar2 = FLOAT_80331a58;
      if (m_ghostWork__10CGPartyObj._32_4_ != 0) {
        fVar2 = FLOAT_80331a7c;
      }
      if (local_78 < Game.game.unkFloat_0xca10 * fVar2) {
        return;
      }
    }
    if ((iVar8 == 1) &&
       (dVar12 < (double)(((pCVar5->gCharaObj).gPrgObj.object.m_bodyEllipsoidRadius +
                          *(float *)(other + 0x144)) * FLOAT_80331a58))) {
      return;
    }
LAB_8011af74:
    if (m_boss__8CGMonObj._112_4_ != iVar8) {
      m_boss__8CGMonObj._116_4_ = 0;
      m_boss__8CGMonObj._112_4_ = iVar8;
    }
    __ct__7CVectorFv(&local_5c);
    if (iVar8 == 0) {
      __ct__7CVectorFRC3Vec(&local_68,&VStack_44);
      local_5c = local_68.x;
      local_58 = local_68.y;
      local_54 = local_68.z;
    }
    else {
      __ct__7CVectorFRC3Vec(&local_74,&local_50);
      local_5c = local_74.x;
      local_58 = local_74.y;
      local_54 = local_74.z;
    }
    fVar2 = (float)m_ghostWork__10CGPartyObj._20_4_ + FLOAT_80331a70;
    fVar3 = FLOAT_80331a88;
    if (iVar6 <= (int)m_ghostWork__10CGPartyObj._24_4_) {
      fVar3 = FLOAT_80331a54;
    }
    m_ghostWork__10CGPartyObj._20_4_ = FLOAT_80331a78;
    if ((FLOAT_80331a78 <= fVar2) &&
       (fVar3 = fVar3 * (param_1->object).m_moveBaseSpeed *
                        *(float *)&(Game.game.m_partyObjArr[0]->gCharaObj).field_0x690,
       m_ghostWork__10CGPartyObj._20_4_ = fVar2, fVar3 < fVar2)) {
      m_ghostWork__10CGPartyObj._20_4_ = fVar3;
    }
    if (m_boss__8CGMonObj._116_4_ + 1 != 4) {
      m_boss__8CGMonObj._116_4_ = m_boss__8CGMonObj._116_4_ + 1;
      m_boss__8CGMonObj._120_4_ = local_5c;
      m_boss__8CGMonObj._124_4_ = local_58;
      m_boss__8CGMonObj._128_4_ = local_54;
      return;
    }
    m_boss__8CGMonObj._116_4_ = 0;
    m_boss__8CGMonObj._120_4_ = local_5c;
    m_boss__8CGMonObj._124_4_ = local_58;
    m_boss__8CGMonObj._128_4_ = local_54;
    return;
  }
  iVar8 = 0;
  if (param_1[1].object.m_moveBaseSpeed != 0.0) {
    m_ghostWork__10CGPartyObj._20_4_ = FLOAT_80331a78;
    carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)param_1,1,(CGObject *)0x0,0);
    return;
  }
  fVar2 = FLOAT_80331a80;
  if (m_ghostWork__10CGPartyObj._32_4_ != 0) {
    fVar2 = FLOAT_80331a7c;
  }
  if (Game.game.unkFloat_0xca10 * fVar2 <= local_78) goto LAB_8011af74;
  iVar6 = (pCVar5->gCharaObj).gPrgObj.m_lastStateId;
  if ((iVar6 != 2) && (iVar6 != 6)) {
    return;
  }
  if ((pCVar5->gCharaObj).gPrgObj.m_subState != 1) {
    return;
  }
  if (*(int *)&(pCVar5->gCharaObj).field_0x668 == 0) {
    return;
  }
  if (*(int *)&(pCVar5->gCharaObj).field_0x660 != 0) {
    return;
  }
  if ((((int)m_ghostWork__10CGPartyObj._4_4_ < (int)Chara._8264_4_) &&
      ((int)m_ghostWork__10CGPartyObj._8_4_ < (int)Chara._8268_4_)) &&
     ((int)m_ghostWork__10CGPartyObj._12_4_ < (int)Chara._8272_4_)) {
    bVar4 = false;
  }
  else {
    bVar4 = true;
  }
  if (!bVar4) {
    return;
  }
  cVar9 = (int)Chara._8264_4_ <= (int)m_ghostWork__10CGPartyObj._4_4_;
  if ((int)Chara._8268_4_ <= (int)m_ghostWork__10CGPartyObj._8_4_) {
    cVar9 = cVar9 + '\x01';
  }
  if ((int)Chara._8272_4_ <= (int)m_ghostWork__10CGPartyObj._12_4_) {
    cVar9 = cVar9 + '\x01';
  }
  iVar6 = Rand__5CMathFUl(&Math,cVar9);
  iVar8 = 0;
  if ((int)Chara._8264_4_ <= (int)m_ghostWork__10CGPartyObj._4_4_) {
    if (iVar6 == 0) {
      m_ghostWork__10CGPartyObj._16_4_ = 0;
      goto LAB_8011adfc;
    }
    iVar8 = 1;
  }
  if ((int)Chara._8268_4_ <= (int)m_ghostWork__10CGPartyObj._8_4_) {
    if (iVar8 == iVar6) {
      m_ghostWork__10CGPartyObj._16_4_ = 1;
      goto LAB_8011adfc;
    }
    iVar8 = iVar8 + 1;
  }
  if (((int)m_ghostWork__10CGPartyObj._12_4_ < (int)Chara._8272_4_) || (iVar8 != iVar6)) {
    m_ghostWork__10CGPartyObj._16_4_ = 0;
  }
  else {
    m_ghostWork__10CGPartyObj._16_4_ = 2;
  }
LAB_8011adfc:
  if (m_ghostWork__10CGPartyObj._16_4_ == 1) {
    param_1[1].object.base_object.object.m_thisBase = (uint32_t *)0x20f;
  }
  else if (m_ghostWork__10CGPartyObj._16_4_ == 0) {
    param_1[1].object.base_object.object.m_thisBase = (uint32_t *)0x207;
  }
  else if ((uint)m_ghostWork__10CGPartyObj._16_4_ < 3) {
    param_1[1].object.base_object.object.m_thisBase = (uint32_t *)0x20b;
  }
  changeStat__8CGPrgObjFiii(param_1,2,0,0);
  m_boss__8CGMonObj._132_4_ = 0;
  m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0x9f;
  return;
}

