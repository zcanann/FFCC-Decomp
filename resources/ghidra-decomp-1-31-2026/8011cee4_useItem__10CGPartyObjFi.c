// Function: useItem__10CGPartyObjFi
// Entry: 8011cee4
// Size: 652 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 useItem__10CGPartyObjFi(CGPartyObj *gPartyObj,void *param_2)

{
  ushort uVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  void **ppvVar6;
  uint uVar7;
  void *local_18;
  undefined4 local_14;
  
  if (((((int)((uint)*(byte *)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags << 0x18) < 0)
       && ((int)((uint)*(byte *)((int)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1)
                << 0x18) < 0)) &&
      ((int)((uint)(byte)(gPartyObj->gCharaObj).field_0x63c << 0x18) < 0)) &&
     (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + (int)param_2 * 0x48);
    if (((param_2 == (void *)0x17d) || (param_2 == (void *)0x186)) &&
       (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0)) {
      uVar5 = 0;
    }
    else {
      Printf__7CSystemFPce(&System,&DAT_801dcbb8,param_2,uVar1);
      (**(code **)((int)(gPartyObj->gCharaObj).gPrgObj.object.base_object.object.m_vtable + 0x4c))
                (gPartyObj,5,param_2,0);
      if (uVar1 == 0x186) {
        if ((param_2 == (void *)0x188) &&
           (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0xf8) == 2)) {
          uVar5 = 4;
        }
        else {
          uVar5 = 2;
        }
        addHp__10CGCharaObjFiP8CGPrgObj(&gPartyObj->gCharaObj,uVar5,(CGPrgObj *)0x0);
        Printf__7CSystemFPce(&System,&DAT_801dcbf4,uVar5);
      }
      else if ((uVar1 < 0x186) && (uVar1 == 0x17d)) {
        iVar4 = (int)param_2 + -0x17d;
        if ((iVar4 < 0) || (7 < iVar4)) {
          uVar7 = 4;
        }
        else {
          ppvVar6 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
          uVar3 = *(ushort *)((int)ppvVar6 + iVar4 * 2 + 0x3b8) / 10;
          uVar7 = 1;
          if (uVar3 != 0) {
            uVar7 = uVar3;
          }
          ppvVar6[0x2f4] = (void *)(uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x68);
          (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0x2f5] = param_2;
        }
        addHp__10CGCharaObjFiP8CGPrgObj(&gPartyObj->gCharaObj,uVar7,(CGPrgObj *)0x0);
        Printf__7CSystemFPce(&System,&DAT_801dcbdc,uVar7);
      }
      local_14 = 0;
      if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
         (Game.game.m_gameWork.m_gamePaused != '\0')) {
        local_14 = 1;
      }
      local_18 = param_2;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,gPartyObj,2,0x15,2,&local_18,(CStack *)0x0);
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

