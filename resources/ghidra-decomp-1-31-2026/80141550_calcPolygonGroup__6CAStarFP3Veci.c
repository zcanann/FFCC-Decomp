// Function: calcPolygonGroup__6CAStarFP3Veci
// Entry: 80141550
// Size: 468 bytes

undefined calcPolygonGroup__6CAStarFP3Veci(CAStar *aStar,float *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined uVar4;
  uint32_t uVar5;
  CVector CStack_c8;
  CVector CStack_bc;
  CVector CStack_b0;
  CVector CStack_a4;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  
  if ((DbgMenuPcs._10844_4_ & 1) == 0) {
    puVar1 = (undefined4 *)
             __ct__7CVectorFfff(FLOAT_80332088,FLOAT_8033208c,FLOAT_80332088,&CStack_b0);
    puVar2 = (undefined4 *)
             __ct__7CVectorFfff(*param_2,FLOAT_80332090 + param_2[1],param_2[2],&CStack_a4);
    local_28 = FLOAT_80332094;
    local_2c = FLOAT_80332094;
    local_30 = FLOAT_80332094;
    local_1c = FLOAT_80332098;
    local_20 = FLOAT_80332098;
    local_24 = FLOAT_80332098;
    local_58 = *puVar2;
    local_54 = puVar2[1];
    local_50 = puVar2[2];
    local_40 = *puVar1;
    local_3c = puVar1[1];
    local_38 = puVar1[2];
    local_34 = FLOAT_80332088;
    iVar3 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_58,puVar1,param_3);
    if (iVar3 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(undefined *)(DAT_8032ec90 + 0x47);
    }
  }
  else {
    uVar5 = aStar->m_hitAttributeMask;
    puVar1 = (undefined4 *)
             __ct__7CVectorFfff(FLOAT_80332088,FLOAT_8033208c,FLOAT_80332088,&CStack_bc);
    puVar2 = (undefined4 *)
             __ct__7CVectorFfff(*param_2,FLOAT_80332090 + param_2[1],param_2[2],&CStack_c8);
    local_68 = FLOAT_80332094;
    local_6c = FLOAT_80332094;
    local_70 = FLOAT_80332094;
    local_5c = FLOAT_80332098;
    local_60 = FLOAT_80332098;
    local_64 = FLOAT_80332098;
    local_98 = *puVar2;
    local_94 = puVar2[1];
    local_90 = puVar2[2];
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_74 = FLOAT_80332088;
    iVar3 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_98,puVar1,uVar5);
    if (iVar3 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(undefined *)(DAT_8032ec90 + 0x47);
    }
  }
  return uVar4;
}

