// Function: checkTargetParticle__10CGPartyObjFv
// Entry: 8011ead4
// Size: 2636 bytes

/* WARNING: Removing unreachable block (ram,0x8011f504) */
/* WARNING: Removing unreachable block (ram,0x8011f4fc) */
/* WARNING: Removing unreachable block (ram,0x8011f4f4) */
/* WARNING: Removing unreachable block (ram,0x8011eaf4) */
/* WARNING: Removing unreachable block (ram,0x8011eaec) */
/* WARNING: Removing unreachable block (ram,0x8011eae4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void checkTargetParticle__10CGPartyObjFv(int param_1)

{
  byte bVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  ushort uVar9;
  Vec *pVVar6;
  int iVar7;
  undefined4 *puVar8;
  bool bVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  Vec local_238;
  Vec local_22c;
  Vec local_220;
  Vec local_214;
  Vec local_208;
  Vec local_1fc;
  Vec VStack_1f0;
  CVector CStack_1e4;
  CVector CStack_1d8;
  CVector CStack_1cc;
  CVector CStack_1c0;
  CVector CStack_1b4;
  Vec local_1a8;
  CVector CStack_19c;
  CVector CStack_190;
  float local_184;
  float local_180;
  float local_17c;
  CVector CStack_178;
  CVector CStack_16c;
  CVector CStack_160;
  CVector CStack_154;
  CVector CStack_148;
  CVector CStack_13c;
  Vec local_130;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  Vec local_118;
  Vec local_10c;
  CVector local_100;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  bVar1 = *(byte *)(param_1 + 0x6b8);
  if ((int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
    putTargetParticle__10CGPartyObjFii
              (param_1,(int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) >> 0x1f,0);
    *(byte *)(param_1 + 0x6b8) = *(byte *)(param_1 + 0x6b8) & 0xef;
  }
  __ct__7CVectorFv(&local_100);
  Identity__7CVectorFv(&local_100);
  if ((((Game.game.m_gameWork.m_menuStageMode == '\0') ||
       (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
      (uVar5 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), (uVar5 & 0x6d) != 0x6d)) ||
     (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) == 0)) {
    if ((MiniGamePcs._25732_4_ & 0x100) != 0) {
      bVar3 = false;
      uVar5 = (uint)*(char *)(param_1 + 0xe2);
      if ((Pad._452_4_ != 0) || ((uVar5 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      fVar2 = FLOAT_80331a78;
      if (!bVar3) {
        fVar2 = *(float *)(&Pad.field_0x24 +
                          (uVar5 & ~((int)~(Pad._448_4_ - uVar5 | uVar5 - Pad._448_4_) >> 0x1f)) *
                          0x54);
      }
      bVar3 = false;
      local_100.x = local_100.x - fVar2;
      uVar5 = (uint)*(char *)(param_1 + 0xe2);
      if ((Pad._452_4_ != 0) || ((uVar5 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      fVar2 = FLOAT_80331a78;
      if (!bVar3) {
        fVar2 = *(float *)(&Pad.field_0x28 +
                          (uVar5 & ~((int)~(Pad._448_4_ - uVar5 | uVar5 - Pad._448_4_) >> 0x1f)) *
                          0x54);
      }
      local_100.z = local_100.z + fVar2;
    }
    if ((FLOAT_80331a78 == local_100.x) && (FLOAT_80331a78 == local_100.z)) {
      bVar3 = false;
      uVar5 = (uint)*(char *)(param_1 + 0xe2);
      if ((Pad._452_4_ != 0) || ((uVar5 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar9 = 0;
      }
      else {
        uVar9 = *(ushort *)
                 (&Pad.field_0x4 +
                 (uVar5 & ~((int)~(Pad._448_4_ - uVar5 | uVar5 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar9 & 1) != 0) {
        local_100.x = local_100.x + FLOAT_80331a54;
      }
      if ((uVar9 & 2) != 0) {
        local_100.x = local_100.x - FLOAT_80331a54;
      }
      if ((uVar9 & 8) != 0) {
        local_100.z = local_100.z + FLOAT_80331a54;
      }
      if ((uVar9 & 4) != 0) {
        local_100.z = local_100.z - FLOAT_80331a54;
      }
    }
  }
  else {
    iVar11 = (Game.game.m_partyObjArr[0]->gCharaObj).gPrgObj.m_lastStateId;
    if (((iVar11 == 2) || (iVar11 == 6)) &&
       (*(int *)&(Game.game.m_partyObjArr[0]->gCharaObj).field_0x668 != 0)) {
      __ct__7CVectorFRC3Vec(&CStack_148,(Vec *)&(Game.game.m_partyObjArr[0]->gCharaObj).field_0x66c)
      ;
      pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_13c,(Vec *)(param_1 + 0x66c));
      __ct__7CVectorFv(&local_214);
      PSVECSubtract(pVVar6,(Vec *)&CStack_148,&local_214);
      local_10c.x = local_214.x;
      local_10c.y = local_214.y;
      local_10c.z = local_214.z;
      dVar12 = (double)PSVECMag(&local_10c);
      if ((double)FLOAT_80331a98 < dVar12) {
        local_100.x = local_10c.x;
        local_100.z = local_10c.z;
      }
    }
  }
  if ((FLOAT_80331a78 == local_100.x) && (FLOAT_80331a78 == local_100.z)) {
    *(byte *)(param_1 + 0x6b8) = *(byte *)(param_1 + 0x6b8) & 0xdf;
  }
  else {
    *(byte *)(param_1 + 0x6b8) = *(byte *)(param_1 + 0x6b8) & 0xdf | 0x20;
    Normalize__7CVectorFv(&local_100);
    PSVECScale(FLOAT_80331ad4,(Vec *)&local_100,(Vec *)&local_100);
    bVar4 = false;
    bVar3 = false;
    bVar10 = false;
    if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
      bVar10 = true;
    }
    if (bVar10) {
      uVar5 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
      uVar5 = countLeadingZeros(0x6d - (uVar5 & 0x6d));
      if ((uVar5 >> 5 & 0xff) != 0) {
        bVar3 = true;
      }
    }
    if ((bVar3) && (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)) {
      bVar4 = true;
    }
    fVar2 = (float)CameraPcs._248_4_;
    if (bVar4) {
      fVar2 = FLOAT_80331ab8;
    }
    dVar13 = (double)fVar2;
    dVar12 = (double)sin(dVar13);
    dVar14 = (double)(float)dVar12;
    dVar12 = (double)cos(dVar13);
    *(float *)(param_1 + 0x66c) =
         *(float *)(param_1 + 0x66c) +
         (float)((double)local_100.x * (double)(float)dVar12 -
                (double)(float)((double)local_100.z * dVar14));
    *(float *)(param_1 + 0x674) =
         *(float *)(param_1 + 0x674) +
         (float)((double)local_100.x * dVar14 +
                (double)(float)((double)local_100.z * (double)(float)dVar12));
    dVar12 = (double)PSVECDistance((Vec *)(param_1 + 0x15c),(Vec *)(param_1 + 0x66c));
    if (*(int *)(param_1 + 0x520) == 2) {
      uStack_64 = (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x19a);
      uStack_6c = (uint)*(ushort *)
                         (Game.game.unkCFlatData0[2] + *(int *)(param_1 + 0x560) * 0x48 + 0x30);
      if ((*(uint *)(*(int *)(param_1 + 0x58) + 0x3b0) & 0x4000) == 0) {
        uStack_5c = 0;
      }
      else {
        uStack_5c = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 10);
      }
      uStack_5c = uStack_5c ^ 0x80000000;
      fVar2 = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331a68) +
              (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331a68) +
              (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331a60);
    }
    else {
      uStack_64 = (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x19c);
      uStack_5c = (uint)*(ushort *)
                         (Game.game.unkCFlatData0[2] + *(int *)(param_1 + 0x560) * 0x48 + 0x30);
      if ((*(uint *)(*(int *)(param_1 + 0x58) + 0x3b0) & 0x8000) == 0) {
        uStack_6c = 0;
      }
      else {
        uStack_6c = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0xc);
      }
      uStack_6c = uStack_6c ^ 0x80000000;
      fVar2 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331a68) +
              (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331a68) +
              (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331a60);
    }
    local_60 = 0x43300000;
    local_68 = 0x43300000;
    local_70 = 0x43300000;
    dVar13 = (double)(FLOAT_80331a78 + fVar2);
    __ct__7CVectorFRC3Vec(&CStack_160,(Vec *)(param_1 + 0x15c));
    pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_154,(Vec *)(param_1 + 0x66c));
    __ct__7CVectorFv(&local_220);
    PSVECSubtract(pVVar6,(Vec *)&CStack_160,&local_220);
    local_118.x = local_220.x;
    local_118.y = local_220.y;
    local_118.z = local_220.z;
    if (dVar13 < dVar12) {
      PSVECScale((float)(dVar13 / dVar12),&local_118,&VStack_1f0);
      PSVECAdd((Vec *)(param_1 + 0x15c),&VStack_1f0,(Vec *)(param_1 + 0x66c));
    }
    __ct__7CVectorFRC3Vec(&CStack_178,(Vec *)(param_1 + 0x678));
    pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_16c,(Vec *)(param_1 + 0x66c));
    __ct__7CVectorFv(&local_22c);
    PSVECSubtract(pVVar6,(Vec *)&CStack_178,&local_22c);
    local_118.x = local_22c.x;
    dVar13 = (double)FLOAT_80331a9c;
    local_118.y = local_22c.y;
    iVar11 = 4;
    dVar12 = (double)FLOAT_80331aa0;
    local_118.z = local_22c.z;
    do {
      bVar10 = false;
      bVar4 = false;
      bVar3 = false;
      if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
         (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar5 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
        uVar5 = countLeadingZeros(0x6d - (uVar5 & 0x6d));
        if ((uVar5 >> 5 & 0xff) != 0) {
          bVar4 = true;
        }
      }
      if ((bVar4) && (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)) {
        bVar10 = true;
      }
      fVar2 = FLOAT_80331a88;
      if (bVar10) {
        fVar2 = FLOAT_80331ab0;
      }
      dVar14 = (double)fVar2;
      __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331ad0,FLOAT_80331a78,&CStack_19c);
      pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_190,(Vec *)(param_1 + 0x678));
      __ct__7CVectorFv(&local_1fc);
      PSVECAdd(pVVar6,(Vec *)&CStack_19c,&local_1fc);
      local_184 = local_1fc.x;
      local_180 = local_1fc.y;
      local_17c = local_1fc.z;
      local_84 = (float)dVar13;
      local_88 = (float)dVar13;
      local_8c = (float)dVar13;
      local_78 = (float)dVar12;
      local_7c = (float)dVar12;
      local_80 = (float)dVar12;
      local_b4 = local_1fc.x;
      local_b0 = local_1fc.y;
      local_ac = local_1fc.z;
      local_9c = local_118.x;
      local_98 = local_118.y;
      local_94 = local_118.z;
      local_90 = (float)dVar14;
      iVar7 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_b4,&local_118,0x30);
      if (iVar7 == 0) break;
      if (iVar11 == 1) {
        local_118.z = FLOAT_80331a78;
        local_118.y = FLOAT_80331a78;
        local_118.x = FLOAT_80331a78;
      }
      else {
        CalcHitSlide__7CMapObjFP3Vecf((CMapObj *)MapMng._141944_4_,&local_118);
      }
      iVar11 = iVar11 + -1;
    } while (0 < iVar11);
    __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331ad0,FLOAT_80331a78,&CStack_1c0);
    pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_1b4,(Vec *)(param_1 + 0x678));
    __ct__7CVectorFv(&local_208);
    PSVECAdd(pVVar6,(Vec *)&CStack_1c0,&local_208);
    local_1a8.x = local_208.x;
    local_1a8.y = local_208.y;
    local_1a8.z = local_208.z;
    PSVECAdd(&local_1a8,&local_118,(Vec *)(param_1 + 0x66c));
    puVar8 = (undefined4 *)
             __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331acc,FLOAT_80331a78,&CStack_1cc);
    local_c4 = FLOAT_80331a9c;
    local_c8 = FLOAT_80331a9c;
    local_cc = FLOAT_80331a9c;
    local_b8 = FLOAT_80331aa0;
    local_bc = FLOAT_80331aa0;
    local_c0 = FLOAT_80331aa0;
    local_f4 = *(undefined4 *)(param_1 + 0x66c);
    local_f0 = *(undefined4 *)(param_1 + 0x670);
    local_ec = *(undefined4 *)(param_1 + 0x674);
    local_dc = *puVar8;
    local_d8 = puVar8[1];
    local_d4 = puVar8[2];
    local_d0 = FLOAT_80331a78;
    iVar11 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_f4,puVar8,0x30);
    if (iVar11 != 0) {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,param_1 + 0x66c);
      iVar11 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar11 + 0xbac) = *(undefined4 *)(param_1 + 0x66c);
      *(undefined4 *)(iVar11 + 0xbb0) = *(undefined4 *)(param_1 + 0x670);
      *(undefined4 *)(iVar11 + 0xbb4) = *(undefined4 *)(param_1 + 0x674);
      GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&local_124);
      iVar11 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar11 + 3000) = local_124;
      *(undefined4 *)(iVar11 + 0xbbc) = local_120;
      *(undefined4 *)(iVar11 + 0xbc0) = local_11c;
    }
    *(undefined4 *)(param_1 + 0x678) = *(undefined4 *)(param_1 + 0x66c);
    *(undefined4 *)(param_1 + 0x67c) = *(undefined4 *)(param_1 + 0x670);
    *(undefined4 *)(param_1 + 0x680) = *(undefined4 *)(param_1 + 0x674);
  }
  __ct__7CVectorFRC3Vec(&CStack_1e4,(Vec *)(param_1 + 0x15c));
  pVVar6 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_1d8,(Vec *)(param_1 + 0x66c));
  __ct__7CVectorFv(&local_238);
  PSVECSubtract(pVVar6,(Vec *)&CStack_1e4,&local_238);
  local_130.x = local_238.x;
  local_130.y = local_238.y;
  local_130.z = local_238.z;
  dVar12 = (double)PSVECMag(&local_130);
  if ((double)FLOAT_80331a78 < dVar12) {
    dVar12 = (double)atan2((double)local_130.x,(double)local_130.z);
    *(float *)(param_1 + 0x1b4) = (float)dVar12;
  }
  return;
}

