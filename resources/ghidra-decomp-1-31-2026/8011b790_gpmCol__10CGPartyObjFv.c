// Function: gpmCol__10CGPartyObjFv
// Entry: 8011b790
// Size: 568 bytes

/* WARNING: Removing unreachable block (ram,0x8011b9ac) */
/* WARNING: Removing unreachable block (ram,0x8011b9a4) */
/* WARNING: Removing unreachable block (ram,0x8011b99c) */
/* WARNING: Removing unreachable block (ram,0x8011b994) */
/* WARNING: Removing unreachable block (ram,0x8011b7b8) */
/* WARNING: Removing unreachable block (ram,0x8011b7b0) */
/* WARNING: Removing unreachable block (ram,0x8011b7a8) */
/* WARNING: Removing unreachable block (ram,0x8011b7a0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void gpmCol__10CGPartyObjFv(int param_1)

{
  CGPartyObj *pCVar1;
  uint uVar2;
  float fVar3;
  Vec *vecA;
  undefined4 *puVar4;
  int iVar5;
  Vec *vec3;
  uint uVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  Vec local_e8;
  CVector CStack_dc;
  CVector CStack_d0;
  CVector CStack_c4;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  
  pCVar1 = Game.game.m_partyObjArr[0];
  dVar8 = (double)FLOAT_80331a98;
  dVar9 = (double)FLOAT_80331a9c;
  dVar10 = (double)FLOAT_80331aa0;
  uVar6 = 0;
  do {
    if (uVar6 == 0) {
      vec3 = (Vec *)(param_1 + 0x15c);
    }
    else {
      vec3 = (Vec *)(&m_ghostWork__10CGPartyObj.field_0x24 + uVar6 * 0xc);
    }
    __ct__7CVectorFRC3Vec(&CStack_d0,vec3);
    vecA = (Vec *)__ct__7CVectorFRC3Vec
                            (&CStack_c4,&(pCVar1->gCharaObj).gPrgObj.object.m_worldPosition);
    __ct__7CVectorFv(&local_e8);
    PSVECSubtract(vecA,(Vec *)&CStack_d0,&local_e8);
    local_b8 = local_e8.x;
    local_b4 = local_e8.y;
    local_b0 = local_e8.z;
    fVar3 = (pCVar1->gCharaObj).gPrgObj.object.m_moveVec.x;
    dVar7 = (double)*(float *)(param_1 + 0x134);
    puVar4 = (undefined4 *)
             __ct__7CVectorFfff(vec3->x,(float)(dVar8 + (double)vec3->y),vec3->z,&CStack_dc);
    local_7c = (float)dVar9;
    local_80 = (float)dVar9;
    local_84 = (float)dVar9;
    local_70 = (float)dVar10;
    local_74 = (float)dVar10;
    local_78 = (float)dVar10;
    local_ac = *puVar4;
    local_a8 = puVar4[1];
    local_a4 = puVar4[2];
    local_94 = local_b8;
    local_90 = local_b4;
    local_8c = local_b0;
    local_88 = (float)dVar7;
    iVar5 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_ac,&local_b8,(uint)fVar3 & 0xffffffef);
    if (iVar5 == 0) {
      iVar5 = uVar6 * 0xc;
      m_ghostWork__10CGPartyObj._40_4_ = uVar6 + 1;
      *(float *)(&m_ghostWork__10CGPartyObj.field_0x30 + iVar5) =
           (pCVar1->gCharaObj).gPrgObj.object.m_worldPosition.x;
      *(float *)(&m_ghostWork__10CGPartyObj.field_0x34 + iVar5) =
           (pCVar1->gCharaObj).gPrgObj.object.m_worldPosition.y;
      *(float *)(&m_ghostWork__10CGPartyObj.field_0x38 + iVar5) =
           (pCVar1->gCharaObj).gPrgObj.object.m_worldPosition.z;
      uVar2 = uVar6;
      if ((int)m_ghostWork__10CGPartyObj._44_4_ < (int)uVar6) {
        uVar2 = m_ghostWork__10CGPartyObj._44_4_;
      }
      break;
    }
    iVar5 = uVar6 + 1;
    if ((int)m_ghostWork__10CGPartyObj._40_4_ < (int)(uVar6 + 1)) {
      iVar5 = m_ghostWork__10CGPartyObj._40_4_;
    }
    uVar6 = uVar6 + 1;
    m_ghostWork__10CGPartyObj._40_4_ = iVar5;
    uVar2 = m_ghostWork__10CGPartyObj._44_4_;
  } while (uVar6 < 5);
  m_ghostWork__10CGPartyObj._44_4_ = uVar2;
  uVar6 = m_ghostWork__10CGPartyObj._40_4_ - 1;
  if ((int)(uVar6 & ~((int)uVar6 >> 0x1f)) <= (int)m_ghostWork__10CGPartyObj._44_4_) {
    m_ghostWork__10CGPartyObj._44_4_ = uVar6 & ~((int)uVar6 >> 0x1f);
  }
  return;
}

