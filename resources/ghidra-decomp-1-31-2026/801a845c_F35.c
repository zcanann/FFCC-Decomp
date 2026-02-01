// Function: F35
// Entry: 801a845c
// Size: 348 bytes

void F35(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  code *pcVar4;
  
  iVar1 = param_1 * 0x100;
  if (param_2 == 0) {
    iVar2 = OSGetTick();
    if ((uint)(iVar2 - *(int *)(&DAT_80328384 + iVar1)) < (DAT_800000f8 >> 2) * 10) {
      pbVar3 = *(byte **)(&DAT_80328370 + iVar1);
      if ((*pbVar3 & 0x32) == 0) {
        if (*pbVar3 == 8) {
          __GBASetDelay(param_1,pbVar3,0,(DAT_800000f8 >> 2) / 0x7d & 0x1ffffff8);
          param_2 = GBAReadAsync(param_1,&DAT_80328378 + iVar1,
                                 *(undefined4 *)(&DAT_80328370 + iVar1),F37);
          __GBASetDelay(param_1,0x431bde83,0,(DAT_800000f8 / 500000) * 0x3c >> 3);
        }
        else {
          param_2 = GBAGetStatusAsync(param_1,pbVar3,F35);
        }
      }
      else {
        param_2 = 3;
      }
    }
    else {
      param_2 = 3;
    }
  }
  if (param_2 != 0) {
    *(undefined4 *)(&DAT_8032838c + iVar1) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar1) = 0;
    pcVar4 = *(code **)(&DAT_80328374 + iVar1);
    if (pcVar4 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
      (*pcVar4)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar1) = param_2;
  return;
}

