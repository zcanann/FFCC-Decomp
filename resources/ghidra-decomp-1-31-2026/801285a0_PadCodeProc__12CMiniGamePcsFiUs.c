// Function: PadCodeProc__12CMiniGamePcsFiUs
// Entry: 801285a0
// Size: 592 bytes

void PadCodeProc__12CMiniGamePcsFiUs(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = param_3 & 0x7f00;
  if (uVar1 == 0x1200) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_GBA_PADCODE_MGR_END_801dd158);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    *(undefined *)(param_1 + 0x6495) = 1;
  }
  else if (uVar1 < 0x1200) {
    if (uVar1 == 0x1100) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_GBA_PADCODE_RACE_END_801dd140);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      *(undefined *)(param_1 + 0x6496) = 1;
    }
    else if ((uVar1 < 0x1100) && (uVar1 == 0x1000)) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s_GBA_PADCODE_RACE_RESULT_play__d_r_801dd110,param_2,param_3 & 0xff);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      *(char *)(param_1 + param_2 + 0x6498) = (char)param_3;
    }
  }
  else if (uVar1 == 0x1300) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_GBA_PADCODE_MGR_CONTINUE_801dd170);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    *(undefined *)(param_1 + 0x6497) = 1;
  }
  return;
}

