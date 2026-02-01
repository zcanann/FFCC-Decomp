// Function: TRKValidMemory32
// Entry: 801ad404
// Size: 676 bytes

int TRKValidMemory32(uint param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (param_2 + param_1) - 1;
  iVar1 = 0x700;
  if (uVar2 < param_1) {
    iVar1 = 0x700;
  }
  else if ((param_1 <= DAT_801e6afc) && (DAT_801e6af8 <= uVar2)) {
    if (((param_3 == 0) && (DAT_801e6b00 == 0)) || ((param_3 == 1 && (DAT_801e6b04 == 0)))) {
      iVar1 = 0x700;
    }
    else {
      iVar1 = 0;
      if (param_1 < DAT_801e6af8) {
        iVar1 = 0x700;
        uVar3 = DAT_801e6af8 - 1;
        if (((param_1 <= uVar3) && (param_1 <= DAT_801e6afc)) && (DAT_801e6af8 <= uVar3)) {
          if (((param_3 == 0) && (DAT_801e6b00 == 0)) || ((param_3 == 1 && (DAT_801e6b04 == 0)))) {
            iVar1 = 0x700;
          }
          else {
            iVar1 = 0;
            if (param_1 < DAT_801e6af8) {
              iVar1 = TRKValidMemory32(param_1,DAT_801e6af8 - param_1,param_3);
            }
            if ((iVar1 == 0) && (DAT_801e6afc < uVar3)) {
              iVar1 = TRKValidMemory32(DAT_801e6afc,uVar3 - DAT_801e6afc,param_3);
            }
          }
        }
      }
      if ((iVar1 == 0) && (DAT_801e6afc < uVar2)) {
        iVar1 = 0x700;
        uVar2 = (param_2 + param_1) - 2;
        if ((DAT_801e6afc <= uVar2) && (DAT_801e6af8 <= uVar2)) {
          if (((param_3 == 0) && (DAT_801e6b00 == 0)) || ((param_3 == 1 && (DAT_801e6b04 == 0)))) {
            iVar1 = 0x700;
          }
          else {
            iVar1 = 0;
            if (DAT_801e6afc < DAT_801e6af8) {
              iVar1 = TRKValidMemory32(DAT_801e6afc,DAT_801e6af8 - DAT_801e6afc,param_3);
            }
            if ((iVar1 == 0) && (DAT_801e6afc < uVar2)) {
              iVar1 = TRKValidMemory32(DAT_801e6afc,uVar2 - DAT_801e6afc,param_3);
            }
          }
        }
      }
    }
  }
  return iVar1;
}

