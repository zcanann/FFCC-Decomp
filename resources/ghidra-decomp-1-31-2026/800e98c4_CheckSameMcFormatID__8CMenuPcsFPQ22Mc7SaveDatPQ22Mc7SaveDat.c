// Function: CheckSameMcFormatID__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDat
// Entry: 800e98c4
// Size: 64 bytes

undefined4
CheckSameMcFormatID__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDat
          (CMenuPcs *menuPcs,int param_2,int param_3)

{
  if ((*(int *)(param_2 + 0x13d4) == *(int *)(param_3 + 0x13d4) &&
       *(int *)(param_2 + 0x13d0) == *(int *)(param_3 + 0x13d0)) &&
     (*(int *)(param_2 + 0x13d8) == *(int *)(param_3 + 0x13d8))) {
    return 1;
  }
  return 0;
}

