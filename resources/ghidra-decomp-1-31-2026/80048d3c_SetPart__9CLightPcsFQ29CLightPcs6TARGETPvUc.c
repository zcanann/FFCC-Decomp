// Function: SetPart__9CLightPcsFQ29CLightPcs6TARGETPvUc
// Entry: 80048d3c
// Size: 444 bytes

void SetPart__9CLightPcsFQ29CLightPcs6TARGETPvUc(int param_1,int param_2,int param_3,char param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_28 [2];
  
  if (param_4 == '\0') {
    GXSetNumChans(1);
    GXSetChanCtrl(0,1,0,1,0,0,2);
    GXSetChanCtrl(2,1,0,1,0,0,2);
  }
  else {
    iVar2 = param_1 + 0x63c;
    *(undefined4 *)(param_1 + 0xb0) = 0;
    uVar3 = 1;
    *(undefined4 *)(param_1 + 0xb4) = 0;
    for (uVar1 = 0; uVar1 < *(uint *)(param_1 + 0xb8); uVar1 = uVar1 + 1) {
      if ((*(char *)(param_2 + iVar2 + 0x60) != '\0') && (*(int *)(iVar2 + 100) == param_3)) {
        local_28[0] = *(undefined4 *)(param_2 * 4 + iVar2 + 0x50);
        GXInitLightColor(iVar2 + 0x6c,local_28);
        GXLoadLightObjImm(iVar2 + 0x6c,1 << *(int *)(param_1 + 0xb0));
        if (*(char *)(iVar2 + 0x4f) != '\0') {
          uVar3 = 0;
        }
        *(uint *)(param_1 + 0xb4) = *(uint *)(param_1 + 0xb4) | 1 << *(int *)(param_1 + 0xb0);
        *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + 1;
        if (7 < *(uint *)(param_1 + 0xb0)) break;
      }
      iVar2 = iVar2 + 0xb0;
    }
    GXSetNumChans(1);
    if (param_4 == '\x01') {
      GXSetChanCtrl(0,1,0,1,*(undefined4 *)(param_1 + 0xb4),2,uVar3);
    }
    else {
      GXSetChanCtrl(0,1,1,0,*(undefined4 *)(param_1 + 0xb4),2,uVar3);
    }
    GXSetChanCtrl(2,1,0,1,0,0,2);
  }
  return;
}

