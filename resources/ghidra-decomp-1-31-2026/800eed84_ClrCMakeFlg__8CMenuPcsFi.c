// Function: ClrCMakeFlg__8CMenuPcsFi
// Entry: 800eed84
// Size: 176 bytes

void ClrCMakeFlg__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  int iVar1;
  
  *(undefined *)(*(int *)&menuPcs->field_0x828 + param_2 * 0x10 + 0xb) = 0;
  iVar1 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + param_2 * 0x10 + 4);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ClrCMakeFlg___chan____d_cur____d_801dc390,param_2,iVar1);
  }
  *(undefined *)(*(int *)&menuPcs->field_0x824 + iVar1 * 0x34 + 0xc) = 0;
  LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
            (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar1 * 4),3,0x43,0);
  return;
}

