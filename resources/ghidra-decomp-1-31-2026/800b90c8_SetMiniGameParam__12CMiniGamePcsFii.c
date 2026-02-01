// Function: SetMiniGameParam__12CMiniGamePcsFii
// Entry: 800b90c8
// Size: 220 bytes

void SetMiniGameParam__12CMiniGamePcsFii(int param_1,int param_2,int param_3)

{
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_SetMiniGameParam_no_0x_04x_data__801da74c,param_2,param_3);
  }
  if (param_2 == 0x1202) {
    *(byte *)(param_1 + 0x134b) = *(byte *)(param_1 + 0x134b) | (byte)(1 << param_3);
  }
  else if (param_2 < 0x1202) {
    if (param_2 == 0x1102) {
      *(undefined *)(param_1 + 0x1348) = 1;
    }
    else if ((param_2 < 0x1102) && (0x1100 < param_2)) {
      *(char *)(param_1 + 0x1350) = (char)param_3;
    }
  }
  else if (param_2 < 0x1204) {
    *(byte *)(param_1 + 0x134b) = *(byte *)(param_1 + 0x134b) & ~(byte)(1 << param_3);
  }
  return;
}

