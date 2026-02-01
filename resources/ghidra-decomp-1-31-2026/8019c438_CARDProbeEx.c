// Function: CARDProbeEx
// Entry: 8019c438
// Size: 380 bytes

undefined4 CARDProbeEx(int param_1,uint *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint local_1c [2];
  
  if ((-1 < param_1) && (param_1 < 2)) {
    if ((DAT_800030e3 & 0x80) != 0) {
      return 0xfffffffd;
    }
    iVar4 = param_1 * 0x110;
    uVar1 = OSDisableInterrupts();
    iVar2 = EXIProbeEx(param_1);
    if (iVar2 == -1) {
      uVar5 = 0xfffffffd;
    }
    else if (iVar2 == 0) {
      uVar5 = 0xffffffff;
    }
    else if ((&DAT_80327540)[param_1 * 0x44] == 0) {
      uVar3 = EXIGetState(param_1);
      if ((uVar3 & 8) == 0) {
        iVar2 = EXIGetID(param_1,0,local_1c);
        if (iVar2 == 0) {
          uVar5 = 0xffffffff;
        }
        else {
          iVar2 = IsCard(local_1c[0]);
          if (iVar2 == 0) {
            uVar5 = 0xfffffffe;
          }
          else {
            if (param_2 != (uint *)0x0) {
              *param_2 = local_1c[0] & 0xfc;
            }
            if (param_3 != (undefined4 *)0x0) {
              *param_3 = *(undefined4 *)(&DAT_8021c340 + (local_1c[0] >> 9 & 0x1c));
            }
            uVar5 = 0;
          }
        }
      }
      else {
        uVar5 = 0xfffffffe;
      }
    }
    else if (*(int *)(&DAT_80327564 + iVar4) < 1) {
      uVar5 = 0xffffffff;
    }
    else {
      if (param_2 != (uint *)0x0) {
        *param_2 = (uint)*(ushort *)(&DAT_80327548 + iVar4);
      }
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = *(undefined4 *)(&DAT_8032754c + iVar4);
      }
      uVar5 = 0;
    }
    OSRestoreInterrupts(uVar1);
    return uVar5;
  }
  return 0xffffff80;
}

