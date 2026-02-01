// Function: onDamaged__8CGMonObjFP8CGPrgObj
// Entry: 801170e0
// Size: 724 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDamaged__8CGMonObjFP8CGPrgObj(CGMonObj *gMonObj,CGPrgObj *gPrgObj)

{
  ushort uVar1;
  uint uVar2;
  void *pvVar3;
  CGMonObj *monObj;
  void **ppvVar4;
  int iVar5;
  void *pvVar6;
  
  gMonObj->field_0x6bf = 1;
  uVar2 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
  if ((uVar2 & 0x6d) != 0x6d) goto LAB_80117310;
  if (*(short *)&gMonObj->field_0x6e4 == 0) {
    pvVar3 = (gMonObj->gObject).m_scriptHandle[9];
  }
  else {
    pvVar3 = (void *)(Game.game.unkCFlatData0[1] +
                     ((int)*(short *)&gMonObj->field_0x6e4 +
                     (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x100)) * 0x1d0 +
                     0x10);
  }
  pvVar6 = (gPrgObj->object).m_scriptHandle[0xed];
  if (*(short *)((int)pvVar3 + 0x106) == 1) {
LAB_80117188:
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
        uVar2 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
        if ((uVar2 & 0x6d) == 0x6d) {
          if ((gPrgObj->object).m_scriptHandle[0xed] != (void *)0x0) goto LAB_801171e0;
        }
      }
    }
    *(void **)&gMonObj->field_0x6c4 = pvVar6;
  }
  else if (*(int *)&gMonObj->field_0x6c4 < 0) goto LAB_80117188;
LAB_801171e0:
  pvVar3 = (gMonObj->gObject).m_scriptHandle[2];
  gPrgObj[1].object.unk_0x170 = (float)pvVar3;
  SetHitEnemy__8GbaQueueFii(&GbaQue,(gPrgObj->object).m_scriptHandle[0xed],pvVar3);
  uVar1 = *(ushort *)&gMonObj->field_0x6d4;
  if ((uVar1 & 0x7fff) != 0) {
    for (monObj = (CGMonObj *)FindGMonObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        monObj != (CGMonObj *)0x0;
        monObj = (CGMonObj *)
                 FindGMonObjNext__13CFlatRuntime2FP8CGMonObj((CFlatRuntime2 *)&CFlat,monObj)) {
      if (monObj != gMonObj) {
        if ((((((*(ushort *)&monObj->field_0x6d4 & 0x7fff) != 0) &&
              ((uVar1 & 0x7fff) == (*(ushort *)&monObj->field_0x6d4 & 0x7fff))) &&
             (ppvVar4 = (monObj->gObject).m_scriptHandle, *(short *)(ppvVar4 + 7) != 0)) &&
            ((*(short *)((int)ppvVar4 + 0x3e) == 0 && (*(short *)(ppvVar4 + 0x14) == 0)))) &&
           (*(short *)(ppvVar4 + 0x11) == 0)) {
          *(void **)&monObj->field_0x6c4 = (gPrgObj->object).m_scriptHandle[0xed];
          monObj->field_0x6bd = 1;
          if (*(int *)&monObj->field_0x6d8 == 4) {
            if ((monObj->_bossBranchRelated == 0) &&
               ((monObj->gObject).m_scriptHandle[4] == (void *)0x55)) {
              changeStat__8CGPrgObjFiii((CGPrgObj *)monObj,0x18,0,0);
              *(undefined4 *)&monObj->field_0x6d8 = 2;
              *(undefined4 *)&monObj->field_0x6dc = 0;
              monObj->field_0x6bb = 1;
            }
          }
          else {
            *(undefined4 *)&monObj->field_0x6d8 = 2;
            *(undefined4 *)&monObj->field_0x6dc = 0;
            monObj->field_0x6bb = 1;
          }
        }
      }
    }
  }
LAB_80117310:
  if (*(int *)&gMonObj->field_0x520 == 0x11) {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
  }
  if ((gMonObj->_bossBranchRelated == 0) && ((gMonObj->gObject).m_scriptHandle[4] == (void *)0x55))
  {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x18,0,0);
  }
  *(undefined4 *)&gMonObj->field_0x6d8 = 2;
  *(undefined4 *)&gMonObj->field_0x6dc = 0;
  gMonObj->field_0x6bb = 1;
  iVar5 = __ptmf_test(*(int *)&gMonObj->field_0x708 + 0x6c);
  if (iVar5 != 0) {
    __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
  }
  return;
}

