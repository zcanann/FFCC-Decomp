// Function: GXSetIndTexMtx
// Entry: 801a4be0
// Size: 352 bytes

void GXSetIndTexMtx(int param_1,float *param_2,char param_3)

{
  uint uVar1;
  
  if (param_1 != 8) {
    if (param_1 < 8) {
      if (param_1 != 4) {
        if (3 < param_1) {
          param_1 = param_1 + -5;
          goto LAB_801a4c30;
        }
        if (0 < param_1) {
          param_1 = param_1 + -1;
          goto LAB_801a4c30;
        }
      }
    }
    else if (param_1 < 0xc) {
      param_1 = param_1 + -9;
      goto LAB_801a4c30;
    }
  }
  param_1 = 0;
LAB_801a4c30:
  param_1 = param_1 * 3;
  uVar1 = (uint)(char)(param_3 + '\x11');
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (uVar1 & 3) << 0x16 |
                 (int)(FLOAT_803338d0 * *param_2) & 0x7ffU |
                 ((int)(FLOAT_803338d0 * param_2[3]) & 0x7ffU) << 0xb | (param_1 + 6) * 0x1000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 + 7) * 0x1000000 |
                 (uVar1 & 0xc) << 0x14 |
                 (int)(FLOAT_803338d0 * param_2[1]) & 0x7ffU |
                 ((int)(FLOAT_803338d0 * param_2[4]) & 0x7ffU) << 0xb;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 + 8) * 0x1000000 |
                 (uVar1 & 0x30) << 0x12 |
                 (int)(FLOAT_803338d0 * param_2[2]) & 0x7ffU |
                 ((int)(FLOAT_803338d0 * param_2[5]) & 0x7ffU) << 0xb;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

