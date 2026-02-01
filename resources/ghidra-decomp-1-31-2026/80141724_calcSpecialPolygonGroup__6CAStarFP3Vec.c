// Function: calcSpecialPolygonGroup__6CAStarFP3Vec
// Entry: 80141724
// Size: 252 bytes

undefined calcSpecialPolygonGroup__6CAStarFP3Vec(CAStar *aStar,float *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined uVar4;
  uint32_t uVar5;
  CVector CStack_68;
  CVector CStack_5c;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  uVar5 = aStar->m_hitAttributeMask;
  puVar1 = (undefined4 *)__ct__7CVectorFfff(FLOAT_80332088,FLOAT_8033208c,FLOAT_80332088,&CStack_68)
  ;
  puVar2 = (undefined4 *)
           __ct__7CVectorFfff(*param_2,FLOAT_80332090 + param_2[1],param_2[2],&CStack_5c);
  local_20 = FLOAT_80332094;
  local_24 = FLOAT_80332094;
  local_28 = FLOAT_80332094;
  local_14 = FLOAT_80332098;
  local_18 = FLOAT_80332098;
  local_1c = FLOAT_80332098;
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_2c = FLOAT_80332088;
  iVar3 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_50,puVar1,uVar5);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined *)(DAT_8032ec90 + 0x47);
  }
  return uVar4;
}

