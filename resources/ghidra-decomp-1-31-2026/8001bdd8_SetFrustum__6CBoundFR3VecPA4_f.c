// Function: SetFrustum__6CBoundFR3VecPA4_f
// Entry: 8001bdd8
// Size: 80 bytes

void SetFrustum__6CBoundFR3VecPA4_f(float *param_1,Mtx *param_2)

{
  s_f_vpos.x = *param_1;
  s_f_vpos.y = param_1[1];
  s_f_vpos.z = param_1[2];
  PSMTXCopy(param_2,&s_f_lvmtx);
  return;
}

