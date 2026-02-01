// Function: GetDirectVector__5CUtilFP3VecP3Vec3Vec
// Entry: 80022780
// Size: 152 bytes

void GetDirectVector__5CUtilFP3VecP3Vec3Vec(CUtil *util,Vec *param_2,Vec *param_3,Vec *param_4)

{
  Vec local_28 [2];
  
  local_28[0].x = DAT_801d7070;
  local_28[0].y = DAT_801d7074;
  local_28[0].z = DAT_801d7078;
  PSVECCrossProduct(param_4,local_28,param_2);
  PSVECNormalize(param_2,param_2);
  PSVECCrossProduct(param_2,param_4,param_3);
  PSVECNormalize(param_3,param_3);
  return;
}

