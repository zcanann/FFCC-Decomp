// Function: putTargetParticle__10CGPartyObjFii
// Entry: 8011f5a4
// Size: 1028 bytes

/* WARNING: Removing unreachable block (ram,0x8011f980) */
/* WARNING: Removing unreachable block (ram,0x8011f5b4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putTargetParticle__10CGPartyObjFii(int param_1,uint param_2,int param_3)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  Vec *pVVar5;
  int iVar6;
  undefined4 *puVar7;
  bool bVar8;
  double dVar9;
  Vec local_128;
  Vec local_11c;
  CVector CStack_110;
  CVector CStack_104;
  CVector CStack_f8;
  Vec local_ec;
  CVector CStack_e0;
  CVector CStack_d4;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  Vec local_b0;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  if (param_3 != 0) {
    *(byte *)(param_1 + 0x6b8) =
         (byte)((int)(char)param_2 << 6) & 0x40 | *(byte *)(param_1 + 0x6b8) & 0xbf;
    *(byte *)(param_1 + 0x6b8) = *(byte *)(param_1 + 0x6b8) & 0xef;
    dVar9 = (double)sin((double)*(float *)(param_1 + 0x1b4));
    local_b0.x = FLOAT_80331a98 * (float)dVar9;
    local_b0.y = FLOAT_80331a78;
    dVar9 = (double)cos((double)*(float *)(param_1 + 0x1b4));
    bVar3 = false;
    bVar2 = false;
    local_b0.z = FLOAT_80331a98 * (float)dVar9;
    bVar8 = false;
    if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
      bVar8 = true;
    }
    if (bVar8) {
      uVar4 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
      uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
      if ((uVar4 >> 5 & 0xff) != 0) {
        bVar2 = true;
      }
    }
    if ((bVar2) && (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)) {
      bVar3 = true;
    }
    fVar1 = FLOAT_80331a88;
    if (bVar3) {
      fVar1 = FLOAT_80331ab0;
    }
    dVar9 = (double)fVar1;
    __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331ad0,FLOAT_80331a78,&CStack_e0);
    pVVar5 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_d4,(Vec *)(param_1 + 0x15c));
    __ct__7CVectorFv(&local_11c);
    PSVECAdd(pVVar5,(Vec *)&CStack_e0,&local_11c);
    local_c8 = local_11c.x;
    local_c4 = local_11c.y;
    local_c0 = local_11c.z;
    local_34 = FLOAT_80331a9c;
    local_38 = FLOAT_80331a9c;
    local_3c = FLOAT_80331a9c;
    local_28 = FLOAT_80331aa0;
    local_2c = FLOAT_80331aa0;
    local_30 = FLOAT_80331aa0;
    local_64 = local_11c.x;
    local_60 = local_11c.y;
    local_5c = local_11c.z;
    local_4c = local_b0.x;
    local_48 = local_b0.y;
    local_44 = local_b0.z;
    local_40 = (float)dVar9;
    iVar6 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_64,&local_b0,0x30);
    if (iVar6 == 0) {
      __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331ad0,FLOAT_80331a78,&CStack_104);
      pVVar5 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_f8,(Vec *)(param_1 + 0x15c));
      __ct__7CVectorFv(&local_128);
      PSVECAdd(pVVar5,(Vec *)&CStack_104,&local_128);
      local_ec.x = local_128.x;
      local_ec.y = local_128.y;
      local_ec.z = local_128.z;
      PSVECAdd(&local_ec,&local_b0,(Vec *)(param_1 + 0x66c));
    }
    else {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,param_1 + 0x66c);
    }
    puVar7 = (undefined4 *)
             __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331acc,FLOAT_80331a78,&CStack_110);
    local_74 = FLOAT_80331a9c;
    local_78 = FLOAT_80331a9c;
    local_7c = FLOAT_80331a9c;
    local_68 = FLOAT_80331aa0;
    local_6c = FLOAT_80331aa0;
    local_70 = FLOAT_80331aa0;
    local_a4 = *(undefined4 *)(param_1 + 0x66c);
    local_a0 = *(undefined4 *)(param_1 + 0x670);
    local_9c = *(undefined4 *)(param_1 + 0x674);
    local_8c = *puVar7;
    local_88 = puVar7[1];
    local_84 = puVar7[2];
    local_80 = FLOAT_80331a78;
    iVar6 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_a4,puVar7,0x30);
    if (iVar6 != 0) {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,param_1 + 0x66c);
      iVar6 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar6 + 0xbac) = *(undefined4 *)(param_1 + 0x66c);
      *(undefined4 *)(iVar6 + 0xbb0) = *(undefined4 *)(param_1 + 0x670);
      *(undefined4 *)(iVar6 + 0xbb4) = *(undefined4 *)(param_1 + 0x674);
      GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&local_bc);
      iVar6 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar6 + 3000) = local_bc;
      *(undefined4 *)(iVar6 + 0xbbc) = local_b8;
      *(undefined4 *)(iVar6 + 0xbc0) = local_b4;
    }
    *(undefined4 *)(param_1 + 0x678) = *(undefined4 *)(param_1 + 0x66c);
    *(undefined4 *)(param_1 + 0x67c) = *(undefined4 *)(param_1 + 0x670);
    *(undefined4 *)(param_1 + 0x680) = *(undefined4 *)(param_1 + 0x674);
  }
  endPSlotBit__10CGCharaObjFi(param_1,0x10);
  ResetParticleWork__13CFlatRuntime2Fii
            ((CFlatRuntime2 *)&CFlat,
             ((int)(-param_2 | param_2) >> 0x1f & 4U) + *(int *)(*(int *)(param_1 + 0x58) + 0x3b4) +
             0x47 | 0x100,*(undefined4 *)(param_1 + 0x574));
  SetParticleWorkPos__13CFlatRuntime2FR3Vecf
            ((double)FLOAT_80331a78,(CFlatRuntime2 *)&CFlat,(Vec *)(param_1 + 0x66c));
  SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
            ((CFlatRuntime2 *)&CFlat,*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x3b4),0);
  PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  return;
}

