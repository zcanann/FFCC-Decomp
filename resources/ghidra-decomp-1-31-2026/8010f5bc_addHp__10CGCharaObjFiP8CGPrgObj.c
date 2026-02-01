// Function: addHp__10CGCharaObjFiP8CGPrgObj
// Entry: 8010f5bc
// Size: 796 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void addHp__10CGCharaObjFiP8CGPrgObj(CGCharaObj *gCharaObj,int param_2,CGPrgObj *gPrgObj)

{
  float fVar1;
  uint uVar2;
  void **ppvVar3;
  uint uVar4;
  int iVar5;
  ushort uVar6;
  int iVar7;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar2 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))();
  if (((uVar2 & 0x6d) != 0x6d) || ((MiniGamePcs._25732_4_ & 4) == 0)) {
    ppvVar3 = (gCharaObj->gPrgObj).object.m_scriptHandle;
    uVar2 = (uint)*(ushort *)(ppvVar3 + 7);
    if ((uVar2 == 0) || (-1 < param_2)) {
      if (0 < param_2) {
        uVar6 = *(ushort *)((int)ppvVar3 + 0x1a);
        if ((int)(uVar2 + param_2) < (int)(uint)uVar6) {
          uVar6 = (ushort)(uVar2 + param_2);
        }
        *(ushort *)(ppvVar3 + 7) = uVar6;
      }
    }
    else {
      uVar4 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                        (gCharaObj);
      if ((((uVar4 & 0x6d) == 0x6d) && ((CFlat._4836_1_ & 1) != 0)) && ((int)(uVar2 + param_2) < 1))
      {
        param_2 = -(uVar2 - 1);
      }
      uVar4 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                        (gCharaObj);
      fVar1 = FLOAT_80331964;
      if ((uVar4 & 0xad) == 0xad) {
        if (((gCharaObj->gPrgObj).object.m_scriptHandle[4] == (void *)0x9a) &&
           (*(int *)&gCharaObj->field_0x6d0 == 0)) {
          m_boss__8CGMonObj._4_4_ = m_boss__8CGMonObj._4_4_ - param_2;
          param_2 = 0;
        }
        if ((gCharaObj->gPrgObj).object.m_scriptHandle[4] == (void *)0x88) {
          m_boss__8CGMonObj._104_4_ = m_boss__8CGMonObj._104_4_ - param_2;
        }
        if (((gCharaObj->gPrgObj).object.m_scriptHandle[4] == (void *)0x70) &&
           ((int)(uVar2 + param_2) < 1)) {
          param_2 = -(uVar2 - 1);
        }
      }
      uVar4 = uVar2 + param_2 & ~((int)(uVar2 + param_2) >> 0x1f);
      *(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7) = (short)uVar4;
      (gCharaObj->gPrgObj).object.m_worldParam = fVar1;
      uVar2 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                        (gCharaObj);
      if ((uVar2 & 0x6d) == 0x6d) {
        if ((int)((uint)(byte)gCharaObj->field_0x6b8 << 0x18) < 0) {
          local_18 = 0xffffffff;
          local_14 = 0;
          SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                    (&CFlat,gCharaObj,2,0x14,2,&local_18,(CStack *)0x0);
        }
        carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)gCharaObj,1,(CGObject *)0x0,1);
      }
      if (gPrgObj != (CGPrgObj *)0x0) {
        (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x74))
                  (gCharaObj,gPrgObj);
      }
      if (uVar4 == 0) {
        iVar7 = 0;
        do {
          setSta__10CGCharaObjFii(gCharaObj,iVar7,0);
          iVar7 = iVar7 + 1;
        } while (iVar7 < 0x27);
        (gCharaObj->gPrgObj).object.m_displayFlags = (gCharaObj->gPrgObj).object.m_displayFlags | 2;
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,9,0,0);
        uVar2 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                          (gCharaObj);
        if ((uVar2 & 0x6d) == 0x6d) {
          for (iVar7 = 2; ppvVar3 = (gCharaObj->gPrgObj).object.m_scriptHandle,
              iVar7 < *(short *)((int)ppvVar3 + 0xbaa); iVar7 = iVar7 + 1) {
            iVar5 = _DelCmdListAndItem__12CCaravanWorkFii(ppvVar3,iVar7);
            if (iVar5 == 0x125) {
              _GetNumCombi__12CCaravanWorkFi
                        ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,iVar7,1);
              gCharaObj->field_0x6b8 = gCharaObj->field_0x6b8 & 0xfb | 4;
              return;
            }
          }
        }
      }
    }
  }
  return;
}

