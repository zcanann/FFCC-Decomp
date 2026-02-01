// Function: SetCMakeEnd__8CMenuPcsFi
// Entry: 800eee34
// Size: 108 bytes

void SetCMakeEnd__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  *(undefined *)(*(int *)&menuPcs->field_0x828 + param_2 * 0x10 + 0xc) = 1;
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce
              (&System,s_SetCMakeEnd___chan____d_cur____d_801dc3b4,param_2,
               (int)*(short *)(*(int *)&menuPcs->field_0x828 + param_2 * 0x10 + 4));
  }
  return;
}

