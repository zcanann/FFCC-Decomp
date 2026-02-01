// Function: WriteUARTN
// Entry: 80183e44
// Size: 540 bytes

/* WARNING: Type propagation algorithm not settling */

undefined4 WriteUARTN(char *param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint local_28 [3];
  
  if (DAT_8032eff8 == -0x5a00ffa6) {
    uVar3 = OSDisableInterrupts();
    iVar4 = EXILock(DAT_8032eff0,DAT_8032eff4,0);
    pcVar5 = param_1;
    if (iVar4 == 0) {
      OSRestoreInterrupts(uVar3);
      uVar2 = 0;
    }
    else {
      for (; (uint)((int)pcVar5 - (int)param_1) < param_2; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          *pcVar5 = '\r';
        }
      }
      local_28[1] = 0xa0010000;
      uVar2 = 0;
      while (param_2 != 0) {
        iVar4 = EXISelect(DAT_8032eff0,DAT_8032eff4,3);
        if (iVar4 == 0) {
          uVar1 = 0xffffffff;
        }
        else {
          local_28[0] = 0x20010000;
          EXIImm(DAT_8032eff0,local_28,4,1,0);
          EXISync(DAT_8032eff0);
          EXIImm(DAT_8032eff0,local_28,1,0,0);
          EXISync(DAT_8032eff0);
          EXIDeselect(DAT_8032eff0);
          uVar1 = 0x10 - (local_28[0] >> 0x18);
        }
        if ((int)uVar1 < 0) {
          uVar2 = 3;
          break;
        }
        if ((0xb < (int)uVar1) || (param_2 <= uVar1)) {
          iVar4 = EXISelect(DAT_8032eff0,DAT_8032eff4,3);
          if (iVar4 == 0) {
            uVar2 = 3;
            break;
          }
          EXIImm(DAT_8032eff0,local_28 + 1,4,1,0);
          EXISync(DAT_8032eff0);
          for (; ((uVar1 != 0 && (param_2 != 0)) && ((3 < (int)uVar1 || (param_2 <= uVar1))));
              param_2 = param_2 - uVar6) {
            uVar6 = param_2;
            if (3 < param_2) {
              uVar6 = 4;
            }
            EXIImm(DAT_8032eff0,param_1,uVar6,1,0);
            param_1 = param_1 + uVar6;
            uVar1 = uVar1 - uVar6;
            EXISync(DAT_8032eff0);
          }
          EXIDeselect(DAT_8032eff0);
        }
      }
      EXIUnlock(DAT_8032eff0);
      OSRestoreInterrupts(uVar3);
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

