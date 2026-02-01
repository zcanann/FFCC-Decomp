// Function: SetExternalTlutColor__8CTextureFPviiR8_GXColor
// Entry: 8003ae30
// Size: 72 bytes

void SetExternalTlutColor__8CTextureFPviiR8_GXColor
               (int param_1,int param_2,int param_3,undefined *param_4)

{
  undefined2 uStack_6;
  
  uStack_6 = CONCAT11(param_4[1],*param_4);
  *(ushort *)(param_1 + (param_3 + param_2) * 2) = CONCAT11(param_4[3],param_4[2]);
  *(undefined2 *)(param_1 + param_3 * 2) = uStack_6;
  return;
}

