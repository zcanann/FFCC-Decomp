// Function: SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl
// Entry: 80048fe0
// Size: 536 bytes

void SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl
               (int param_1,int param_2,Vec *param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30 [5];
  
  *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_1 + 0xac);
  *(undefined4 *)(param_1 + 0xb4) = 0;
  if (param_4 == 0) {
    uVar1 = *(undefined4 *)(param_1 + 0xb4);
    GXSetNumChans(1);
    if (param_2 != 1) {
      GXSetChanCtrl(0,1,0,1,uVar1,2,1);
      GXSetChanCtrl(2,1,0,1,0,0,2);
      local_34 = DAT_8032fc08;
      GXSetChanMatColor(4,&local_34);
    }
  }
  else {
    iVar2 = param_1 + 0xbc;
    *(int *)(param_1 + 0xb4) = (1 << *(int *)(param_1 + 0xb0)) + -1;
    for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0xac); uVar3 = uVar3 + 1) {
      GXLoadLightObjImm(iVar2 + 0x6c,1 << uVar3);
      iVar2 = iVar2 + 0xb0;
    }
    if (param_3 != (Vec *)0x0) {
      iVar2 = param_1 + 0x63c;
      for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0xb8); uVar3 = uVar3 + 1) {
        if (((*(char *)(param_2 + iVar2 + 0x60) != '\0') &&
            ((*(uint *)(iVar2 + 0x34) & param_4) != 0)) &&
           (dVar4 = (double)PSVECSquareDistance(param_3,(Vec *)(iVar2 + 4)),
           dVar4 < (double)*(float *)(iVar2 + 0xac))) {
          local_30[0] = *(undefined4 *)(param_2 * 4 + iVar2 + 0x50);
          GXInitLightColor(iVar2 + 0x6c,local_30);
          GXLoadLightObjImm(iVar2 + 0x6c,1 << *(int *)(param_1 + 0xb0));
          *(uint *)(param_1 + 0xb4) = *(uint *)(param_1 + 0xb4) | 1 << *(int *)(param_1 + 0xb0);
          *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + 1;
          if (7 < *(uint *)(param_1 + 0xb0)) break;
        }
        iVar2 = iVar2 + 0xb0;
      }
    }
    uVar1 = *(undefined4 *)(param_1 + 0xb4);
    GXSetNumChans(1);
    if (param_2 != 1) {
      GXSetChanCtrl(0,1,0,1,uVar1,2,1);
      GXSetChanCtrl(2,1,0,1,0,0,2);
      local_38 = DAT_8032fc08;
      GXSetChanMatColor(4,&local_38);
    }
  }
  return;
}

