// Function: SetAmbientAlpha__9CLightPcsFf
// Entry: 80049428
// Size: 76 bytes

void SetAmbientAlpha__9CLightPcsFf(double param_1)

{
  undefined4 local_18 [2];
  longlong local_10;
  
  local_10 = (longlong)(int)((double)FLOAT_8032fc7c * param_1);
  DAT_8032ed14 = CONCAT31(DAT_8032ed14._0_3_,(char)(int)((double)FLOAT_8032fc7c * param_1));
  local_18[0] = DAT_8032ed14;
  GXSetChanAmbColor(2,local_18);
  return;
}

