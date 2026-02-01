// Function: SetFullScreenShadow__12CMaterialManFR17CFullScreenShadowPA4_fl
// Entry: 8003e904
// Size: 164 bytes

void SetFullScreenShadow__12CMaterialManFR17CFullScreenShadowPA4_fl
               (int param_1,int param_2,Mtx *param_3,int param_4)

{
  int iVar1;
  
  if (CameraPcs._1028_1_ != '\0') {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x80;
    PSMTXConcat((Mtx *)(param_2 + 0x58),param_3,(Mtx *)(param_1 + 100));
    iVar1 = param_2 + param_4 * 0x20;
    *(int *)(param_1 + 0xc4) = iVar1 + 8;
    PSMTXConcat((Mtx *)(param_2 + 0x88),param_3,(Mtx *)(param_1 + 0x94));
    *(int *)(param_1 + 200) = iVar1 + 0x28;
  }
  return;
}

