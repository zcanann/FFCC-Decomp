// Function: moveCenterTargetParticle__10CGPartyObjFv
// Entry: 8011e870
// Size: 612 bytes

/* WARNING: Removing unreachable block (ram,0x8011eab4) */
/* WARNING: Removing unreachable block (ram,0x8011e880) */

void moveCenterTargetParticle__10CGPartyObjFv(int param_1)

{
  Vec *pVVar1;
  undefined4 *puVar2;
  int iVar3;
  double dVar4;
  Vec local_108;
  Vec local_fc;
  Vec local_f0;
  Vec local_e4;
  CVector CStack_d8;
  CVector CStack_cc;
  float local_c0;
  float local_bc;
  float local_b8;
  CVector CStack_b4;
  CVector CStack_a8;
  Vec local_9c;
  Vec local_90;
  CVector CStack_84;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  Vec local_6c;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (*(int *)(param_1 + 0x530) < 5) {
    uStack_1c = *(int *)(param_1 + 0x530) + 1U ^ 0x80000000;
    local_20 = 0x43300000;
    dVar4 = (double)sin((double)(FLOAT_80331ac8 *
                                ((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80331a60) /
                                FLOAT_80331ac4)));
    dVar4 = (double)(float)dVar4;
    __ct__7CVectorFRC3Vec(&CStack_b4,(Vec *)(param_1 + 0x678));
    pVVar1 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_a8,(Vec *)(param_1 + 0x66c));
    __ct__7CVectorFv(&local_108);
    PSVECSubtract(pVVar1,(Vec *)&CStack_b4,&local_108);
    local_9c.x = local_108.x;
    local_9c.y = local_108.y;
    local_9c.z = local_108.z;
    __ct__7CVectorFv(&local_fc);
    PSVECScale((float)dVar4,&local_9c,&local_fc);
    local_90.x = local_fc.x;
    local_90.y = local_fc.y;
    local_90.z = local_fc.z;
    pVVar1 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_84,(Vec *)(param_1 + 0x678));
    __ct__7CVectorFv(&local_f0);
    PSVECAdd(pVVar1,&local_90,&local_f0);
    local_6c.x = local_f0.x;
    local_6c.y = local_f0.y;
    local_6c.z = local_f0.z;
    puVar2 = (undefined4 *)
             __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331acc,FLOAT_80331a78,&CStack_d8);
    __ct__7CVectorFfff(FLOAT_80331a78,FLOAT_80331ad0,FLOAT_80331a78,&CStack_cc);
    __ct__7CVectorFv(&local_e4);
    PSVECAdd(&local_6c,(Vec *)&CStack_cc,&local_e4);
    local_30 = FLOAT_80331a9c;
    local_34 = FLOAT_80331a9c;
    local_38 = FLOAT_80331a9c;
    local_24 = FLOAT_80331aa0;
    local_28 = FLOAT_80331aa0;
    local_2c = FLOAT_80331aa0;
    local_60 = local_e4.x;
    local_5c = local_e4.y;
    local_58 = local_e4.z;
    local_48 = *puVar2;
    local_c0 = local_e4.x;
    local_44 = puVar2[1];
    local_bc = local_e4.y;
    local_40 = puVar2[2];
    local_b8 = local_e4.z;
    local_3c = FLOAT_80331a78;
    iVar3 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_60,puVar2,0x30);
    if (iVar3 != 0) {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_6c);
      GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&local_78);
      iVar3 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar3 + 3000) = local_78;
      *(undefined4 *)(iVar3 + 0xbbc) = local_74;
      *(undefined4 *)(iVar3 + 0xbc0) = local_70;
    }
    iVar3 = *(int *)(param_1 + 0x58);
    *(float *)(iVar3 + 0xbac) = local_6c.x;
    *(float *)(iVar3 + 0xbb0) = local_6c.y;
    *(float *)(iVar3 + 0xbb4) = local_6c.z;
  }
  return;
}

