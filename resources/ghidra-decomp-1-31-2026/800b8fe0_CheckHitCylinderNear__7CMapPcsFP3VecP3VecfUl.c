// Function: CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
// Entry: 800b8fe0
// Size: 128 bytes

void CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
               (double param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 param_5)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  local_18 = FLOAT_80330ba0;
  local_1c = FLOAT_80330ba0;
  local_20 = FLOAT_80330ba0;
  local_c = FLOAT_80330ba4;
  local_10 = FLOAT_80330ba4;
  local_14 = FLOAT_80330ba4;
  local_48 = *param_3;
  local_44 = param_3[1];
  local_40 = param_3[2];
  local_30 = *param_4;
  local_2c = param_4[1];
  local_28 = param_4[2];
  local_24 = (float)param_1;
  CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_48,param_4,param_5);
  return;
}

