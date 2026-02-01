// Function: SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc
// Entry: 8014636c
// Size: 292 bytes

void SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc
               (CMenuPcs *menuPcs,undefined4 param_2,int param_3,int param_4,int param_5,int param_6
               ,int param_7,int param_8,int param_9,int param_10)

{
  AStar.m_bestPath.m_path._56_4_ = param_2;
  if (param_3 != 0) {
    strcpy(s_DynamicMessStr,param_3);
  }
  if (param_4 != 0) {
    strcpy(0x8030b6c4,param_4);
  }
  if (param_5 != 0) {
    strcpy(0x8030b744,param_5);
  }
  if (param_6 != 0) {
    strcpy(0x8030b7c4,param_6);
  }
  if (param_7 != 0) {
    strcpy(0x8030b844,param_7);
  }
  if (param_8 != 0) {
    strcpy(0x8030b8c4,param_8);
  }
  if (param_9 != 0) {
    strcpy(0x8030b944,param_9);
  }
  if (param_10 != 0) {
    strcpy(0x8030b9c4,param_10);
  }
  return;
}

