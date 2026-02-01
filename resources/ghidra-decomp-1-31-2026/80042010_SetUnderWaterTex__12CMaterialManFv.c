// Function: SetUnderWaterTex__12CMaterialManFv
// Entry: 80042010
// Size: 368 bytes

/* WARNING: Type propagation algorithm not settling */

void SetUnderWaterTex__12CMaterialManFv(int param_1)

{
  undefined4 uVar1;
  uint local_c8;
  uint local_c4 [3];
  Mtx local_b8;
  Mtx MStack_88;
  Mat4x4 local_58;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  local_c4[0] = 0x280;
  local_c4[2] = 0;
  local_c4[1] = 0;
  local_c8 = 0x1c0;
  uVar1 = GetBackBufferRect__8CGraphicFRiRiRiRii
                    (&Graphic,local_c4 + 2,local_c4 + 1,local_c4,&local_c8,1);
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  if (*(int *)(param_1 + 0xc) != 0) {
    PSMTXIdentity(&local_b8);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&local_58);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_88);
    uStack_c = local_c8 ^ 0x80000000;
    uStack_14 = local_c4[0] ^ 0x80000000;
    local_10 = 0x43300000;
    local_18 = 0x43300000;
    local_b8.value[0][0] =
         local_58.value[0][0] *
         (FLOAT_8032fb08 / (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032fb18));
    local_b8.value[1][1] =
         local_58.value[1][1] *
         -(FLOAT_8032fb0c / (float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_8032fb18));
    local_b8.value[1][0] = local_58.value[1][0];
    local_b8.value[2][0] = local_58.value[2][0];
    local_b8.value[0][1] = local_58.value[0][1];
    local_b8.value[2][1] = local_58.value[2][1];
    local_b8.value[0][2] = FLOAT_8032fb10;
    local_b8.value[1][2] = FLOAT_8032fb10;
    local_b8.value[2][2] = FLOAT_8032fb14;
    PSMTXConcat(&local_b8,&MStack_88,(Mtx *)(param_1 + 0x10));
  }
  return;
}

