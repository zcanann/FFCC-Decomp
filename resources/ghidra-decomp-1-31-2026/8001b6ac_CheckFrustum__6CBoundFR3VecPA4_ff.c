// Function: CheckFrustum__6CBoundFR3VecPA4_ff
// Entry: 8001b6ac
// Size: 124 bytes

/* WARNING: Removing unreachable block (ram,0x8001b70c) */
/* WARNING: Removing unreachable block (ram,0x8001b6bc) */

void CheckFrustum__6CBoundFR3VecPA4_ff
               (undefined8 param_1,undefined4 param_2,float *param_3,Mtx *param_4)

{
  s_f_vpos.x = *param_3;
  s_f_vpos.y = param_3[1];
  s_f_vpos.z = param_3[2];
  PSMTXCopy(param_4,&s_f_lvmtx);
  CheckFrustum0__6CBoundFf(param_1,param_2);
  return;
}

